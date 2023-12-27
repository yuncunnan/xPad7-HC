#include <QDir>
#include <QDateTime>
#include "xconfig.h"
#include "cmbprotocol.h"
#include "xpermissions.h"
#include "xstringresource.h"
#include "xsystemlog.h"
#include "dialoglogio.h"
#include "dialoglogpar.h"
#include "dialoglogdetail.h"

#include <QDebug>
#define ALARM_SYSTEM_POWEROFF   212

xSqlTableModel::xSqlTableModel(QObject *parent, QSqlDatabase db) : QSqlTableModel(parent, db)
{
}

QVariant xSqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::TextAlignmentRole)
			return int(Qt::AlignLeft | Qt::AlignVCenter);
		else if (role == Qt::SizeHintRole)
			return QSize(80, 40);
	}
	else if (orientation == Qt::Vertical)
	{
		if (role == Qt::TextAlignmentRole)
			return int(Qt::AlignRight | Qt::AlignVCenter);
	}
	return QSqlTableModel::headerData(section, orientation, role);
}

QVariant xSqlTableModel::data(const QModelIndex &idx, int role) const
{
	if (!idx.isValid())
		return QVariant();
	if (role == Qt::DisplayRole)
	{
		if (idx.column() == xSysLog::logTime)
		{
			QDateTime time = QSqlTableModel::data(idx, role).toDateTime();
            return time.toString("yyyy-MM-dd hh:mm:ss");
		}
		else if (idx.column() == xSysLog::logUser)
		{
			quint8 user = QSqlTableModel::data(idx, role).toUInt();
			return xStringResource::GetUsrName(user);
		}
		else if (idx.column() == xSysLog::logValue)
		{
			quint32 value = QSqlTableModel::data(idx, role).toUInt();
			quint8 type = (value >> 16);
            value &= 0xFF00FFFF;
//			value &= 0xFFFF;
			QString extValue = QSqlTableModel::data(QSqlTableModel::index(idx.row(), 4), role).toString();
			if (type == SYSLOG_TYPE_ALM || type == SYSLOG_TYPE_MSG)
				return xStringResource::GetAlarm(value) + extValue;
			else
			if (type == SYSLOG_TYPE_STATE_CHG)
				return extValue + xStringResource::GetSysStateString(value)+ ">>" + xStringResource::GetSysStateString(value>>8);
			else
				return xStringResource::GetLogString(value) + extValue;
		}
		else
			return QVariant();
	}
	else if (role == Qt::DecorationRole)
	{
		if (idx.column() == xSysLog::logType)
		{
			quint8 type = QSqlTableModel::data(idx, Qt::DisplayRole).toUInt();
			if (type == SYSLOG_TYPE_MSG)
				return QIcon(":img/32X32/LogMessage.png");
			else if (type == SYSLOG_TYPE_ALM)
				return QIcon(":img/32X32/LogAlarm.png");
			else
				return QIcon(":img/32X32/LogRecord.png");
		}
	}
	else if (role == Qt::TextAlignmentRole)
	{
		return int(Qt::AlignLeft | Qt::AlignVCenter);
	}
	return QSqlTableModel::data(idx, role);
}

xSqlTableModel *xSysLog::pModel = 0;
DialogLogIo *xSysLog::pDiaIo = 0;
DialogLogPar *xSysLog::pDiaPar = 0;
DialogLogDetail *xSysLog::pDiaDetail = 0;

xSysLog::xSysLog(QObject *parent) : QObject(parent)
{
	pDiaIo = new DialogLogIo;
    OpenSysLog();
}

xSysLog::~xSysLog()
{
	if (pDiaIo)
		delete pDiaIo;
	if (pDiaPar)
		delete pDiaPar;
	if (pDiaDetail)
		delete pDiaDetail;
	DestroySysLog();
}

bool xSysLog::OpenSysLog(void)
{
    int tryconut = 0;
    bool ret = true;
    // 如果系统日志目录不存在则创建
    QDir curDir(QDir::currentPath());
    if (!curDir.exists(QDir::currentPath() + QString("/"SYSLOG_PATH"/")))
    {
        curDir.mkdir(SYSLOG_PATH);
    }
//    qDebug() << "OpenSysLog{{{{{{{{{{{{{{{" << endl;
    // 数据库备份文件
    QFile filedb(QDir::currentPath() + QString("/"SYSLOG_PATH"/"XPAD_SYSLOG_FILE));
    QFile filedbbak(QDir::currentPath() + QString("/"SYSLOG_PATH"/"XPAD_SYSLOG_FILE".bak"));
    // 增加日志数据库连接
    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");

Retry:
    dataBase.setDatabaseName(QDir::currentPath() + QString("/"SYSLOG_PATH"/"XPAD_SYSLOG_FILE));
    if (dataBase.open())
    {
//        qDebug() << "Open log table ok" << endl;
        // 日志数据库连接成功
        QSqlQuery sqlQuery;
        // 如果日志数据库中没有数据表则创建
        if (!sqlQuery.exec("create table if not exists log ("
                           "logTime datetime,"								// 0:日志记录时间
                           "logType integer,"								// 1:日志记录类型
                           "logUser integer,"								// 2:日志记录用户
                           "logValue integer,"								// 3:日志记录内容
                           "logExt varchar,"								// 4:日志记录扩展内容
                           "logID integer primary key autoincrement,"		// 5:日志记录唯一ID
                           // *************************************************************************
                           "input blob,"									// 6:系统输入状态
                           "output	blob,"									// 7:系统输出状态
                           // *************************************************************************
                           "parameter blob"									// 8:参数状态
                           ")"))
        {
//            qDebug() << "Create log table error: " << sqlQuery.lastError().databaseText() << endl;
            ret = false;
        }
        else
        {
//            qDebug() << "Create log table ok" << endl;
            // 有log数据表,查询log表内数据
            if (!sqlQuery.exec("select count(*) from sqlite_master where type = 'table' and name = 'log'"))
            {
//                qDebug() << "select log table error: " << sqlQuery.lastError().databaseText() << endl;
                ret = false;
            }
            else
            {
//                qDebug() << "select log table ok" << endl;
            }
        }
    }
    else
    {
//        qDebug() << "Open log table error" << endl;
        ret = false;
    }

    if (!ret)
    {
        // 删除原有数据库文件,并启用备用数据库
//        qDebug() << "Remove error log table" << endl;
        filedb.remove();
        if (filedbbak.exists())
        {
            if (!QFile::copy((QDir::currentPath() + QString("/"SYSLOG_PATH"/"XPAD_SYSLOG_FILE".bak")), (QDir::currentPath() + QString("/"SYSLOG_PATH"/"XPAD_SYSLOG_FILE))))
            {
//                qDebug() << "Restore bak log table error" << endl;
            }
#if defined(Q_OS_LINUX)
            sync();
#endif
        }
        tryconut++;
        if (tryconut<5)
        {
            ret = true;
            goto Retry;
        }
    }

    if (ret)
    {
        // log表内有数据
        // 删除原有备份数据库文件,建立数据库备份
        if (filedbbak.exists())
        {
//            qDebug() << "Remove bak log table" << endl;
            filedbbak.remove();
        }
        if (!QFile::copy((QDir::currentPath() + QString("/"SYSLOG_PATH"/"XPAD_SYSLOG_FILE)), (QDir::currentPath() + QString("/"SYSLOG_PATH"/"XPAD_SYSLOG_FILE".bak"))))
        {
//            qDebug() << "Backup log table error" << endl;
        }
#if defined(Q_OS_LINUX)
        sync();
#endif
//        qDebug() << "New Sql table Model************" << endl;
        pModel = new xSqlTableModel();
        pModel->setTable("log");
        pModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        pModel->setSort(5, Qt::DescendingOrder);
    }
//    qDebug() << "OpenSysLog}}}}}}}}}}}}}}}}}}}" << ret << endl;
    return ret;
}

void xSysLog::DestroySysLog(void)
{
	if (pModel)
		delete pModel;
	QString name;
	{
		name = QSqlDatabase::database().connectionName();
	}
	QSqlDatabase::removeDatabase(name);
}

xSqlTableModel *xSysLog::GetModel(void)
{
	return pModel;
}

void xSysLog::AddRecord(quint8 type, quint16 value, QString ext, QByteArray par, quint16 value2)
{
	if (!pModel)
		return;
    if (CMBProtocol::GetSystemAlarm()==ALARM_SYSTEM_POWEROFF)
        return;
    int rowCnt = pModel->rowCount();
	if (rowCnt >= XPAD_SYSLOG_MAX)
		pModel->removeRows(XPAD_SYSLOG_MAX - 1, rowCnt - XPAD_SYSLOG_MAX + 1);
    quint32 setValue = value2;
	setValue <<= 16;
	setValue |= value;
    setValue &= 0xFF00FFFF;
    setValue |= (((uint32_t)type)<<16);

	// 准备端口输入输出状态数据
	quint16 inBuf[LOG_INPUT_SIZE];
	quint64 inMain = CMBProtocol::GetInMain();
	inBuf[0] = inMain & 0xFFFF;	inMain >>= 16;
	inBuf[1] = inMain & 0xFFFF;	inMain >>= 16;
	inBuf[2] = inMain & 0xFFFF;	inMain >>= 16;
	inBuf[3] = inMain & 0xFFFF;
	inBuf[4] = CMBProtocol::GetInEm1();
	inBuf[5] = CMBProtocol::GetInEm2();
	inBuf[6] = CMBProtocol::GetInEm3();
	inBuf[7] = CMBProtocol::GetInEm4();
	quint16 outBuf[LOG_OUTPUT_SIZE];
	quint32 outMain = CMBProtocol::GetOutMain();
	outBuf[0] = outMain & 0xFFFF;	outMain >>= 16;
	outBuf[1] = outMain & 0xFFFF;
	outBuf[2] = CMBProtocol::GetOutEm1();
	outBuf[3] = CMBProtocol::GetOutEm2();
	outBuf[4] = CMBProtocol::GetOutEm3();
	outBuf[5] = CMBProtocol::GetOutEm4();
	// 写入日志记录
	pModel->insertRow(0);
	pModel->setData(pModel->index(0, logTime), QDateTime::currentDateTime());
	pModel->setData(pModel->index(0, logType), type);
	pModel->setData(pModel->index(0, logUser), xPermissions::GetCurrentUser());
	pModel->setData(pModel->index(0, logValue), setValue);
	pModel->setData(pModel->index(0, logExt), ext);
	pModel->setData(pModel->index(0, input), QByteArray((char*)inBuf, sizeof(inBuf)));
	pModel->setData(pModel->index(0, output), QByteArray((char*)outBuf, sizeof(outBuf)));
	pModel->setData(pModel->index(0, parameter), par);
}

bool xSysLog::SaveChange(void)
{
	if (!pModel)
		return false;
    if (CMBProtocol::GetSystemAlarm()==ALARM_SYSTEM_POWEROFF)
        return false;
    return pModel->submitAll();
}

int xSysLog::DoDiaIo(const QDateTime &time, const quint16 (&input)[LOG_INPUT_SIZE], const quint16 (&output)[LOG_OUTPUT_SIZE])
{
	if (!pDiaIo)
		return QDialog::Rejected;
	return pDiaIo->DoForm(time, input, output);
}

int xSysLog::DoDiaPar(const QDateTime &time, const QByteArray &par, const quint8 type)
{
	if (pDiaPar == 0)
		pDiaPar = new DialogLogPar;
	return pDiaPar->DoForm(time, par, type);
}

int xSysLog::DoDiaDetail(const QString &time, const QIcon &type, const QString &user, const QString &detail)
{
	if (pDiaDetail == 0)
		pDiaDetail = new DialogLogDetail;
	return pDiaDetail->DoForm(time, type, user, detail);
}
