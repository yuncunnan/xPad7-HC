#include "formsyslog.h"
#include "dialogframe.h"
#include "ui_formsyslog.h"
#include "xsystemlog.h"
#include "dialoglogquery.h"
#include "xstringresource.h"
#include "xmessagebox.h"

DialogLogQuery *FormSysLog::pQuery = 0;

extern DialogFrame *pDialogMain;

FormSysLog::FormSysLog(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormSysLog)
{
	ui->setupUi(this);
	pModbus = modbus;
	// 设置数据源
	ui->logView->setModel(xSysLog::GetModel());
	ui->logView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// 设置列宽
	ui->logView->horizontalHeader()->setResizeMode(xSysLog::logTime, QHeaderView::Fixed);
	ui->logView->horizontalHeader()->setResizeMode(xSysLog::logType, QHeaderView::Fixed);
	ui->logView->horizontalHeader()->setResizeMode(xSysLog::logUser, QHeaderView::Fixed);
	ui->logView->horizontalHeader()->setResizeMode(xSysLog::logValue, QHeaderView::Stretch);
	ui->logView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	// 隐藏列
	ui->logView->setColumnHidden(xSysLog::logUser, true);
	ui->logView->setColumnHidden(xSysLog::logExt, true);
	ui->logView->setColumnHidden(xSysLog::logID, true);
	ui->logView->setColumnHidden(xSysLog::input, true);
	ui->logView->setColumnHidden(xSysLog::output, true);
	ui->logView->setColumnHidden(xSysLog::parameter, true);
	// 设置列宽度
    ui->logView->setColumnWidth(xSysLog::logTime, 300);
	ui->logView->setColumnWidth(xSysLog::logType, 40);
	ui->logView->setColumnWidth(xSysLog::logUser, 140);

	// 设置表头字体
#if SIMULATOR
	ui->logView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 10));
	ui->logView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 10pt;}");
	ui->logView->verticalHeader()->setFont(QFont("Microsoft YaHei", 10));
	ui->logView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 10pt;}");
#else
	ui->logView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->logView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
	ui->logView->verticalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->logView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
#endif
	// 连接信号槽
	connect(parent, SIGNAL(LogModelUpdate()), this, SLOT(resetModel()));
}

FormSysLog::~FormSysLog()
{
	delete ui;
	if (pQuery)
		delete pQuery;
}

void FormSysLog::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void FormSysLog::resetModel(void)
{
	ui->logView->setModel(xSysLog::GetModel());
}

bool FormSysLog::EnterForm(void)
{
    // 检查用户权限
    if (xPermissions::GetPermissions(PER_SYS_LOG) == false)
    {
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (pDialogMain)
            if (pDialogMain->ScreenSaverUserManager() == 0)
        return false;
    }
	xSysLog::GetModel()->setFilter("");
	xSysLog::GetModel()->select();
	ui->labelQuery->setText(tr("所有记录"));
	// 连接信号槽
	connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 显示界面
//	show();
	return true;
}

bool FormSysLog::ExitForm(void)
{
	// 取消信号槽连接
	disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 隐藏界面
//	hide();
	return true;
}

// 当前登录用户更改槽
void FormSysLog::userChange(void)
{
	if (xPermissions::GetPermissions(PER_SYS_LOG) == false)
	{
		ui->framesyslog->setEnabled(false);
		xMessageBox::DoWarning(tr("警告"), xStringResource::GetString(STRRES_USRCHG_DENY));
	}
	else
		ui->framesyslog->setEnabled(true);
}

// 显示当前选中日志记录的端口状态
void FormSysLog::showPortStatus(void)
{
	QModelIndex curIdx = ui->logView->currentIndex();
	if (!curIdx.isValid())
	{
		xMessageBox::DoInformation(tr("提示"), tr("请先选择日志记录，再查看选中记录的端口状态。"));
		return;
	}
	quint16 input[LOG_INPUT_SIZE], output[LOG_OUTPUT_SIZE];
	QSqlRecord logRecord =  xSysLog::GetModel()->record(curIdx.row());
	QDateTime time = logRecord.value(xSysLog::logTime).toDateTime();
	QByteArray inBuf = logRecord.value(xSysLog::input).toByteArray();
	QByteArray outBuf = logRecord.value(xSysLog::output).toByteArray();
	memcpy(input, inBuf.data(), sizeof(input));
	memcpy(output, outBuf.data(), sizeof(output));
	xSysLog::DoDiaIo(time, input, output);
}

// 显示当前选中日志记录的参数设置
void FormSysLog::showParameter(void)
{
	QModelIndex curIdx = ui->logView->currentIndex();
	if (!curIdx.isValid())
	{
		xMessageBox::DoInformation(tr("提示"), tr("请先选择日志记录，再查看选中记录的参数设置。"));
		return;
	}
	QSqlRecord logRecord =  xSysLog::GetModel()->record(curIdx.row());
	QDateTime time = logRecord.value(xSysLog::logTime).toDateTime();
	quint32 logType = logRecord.value(xSysLog::logValue).toUInt();
	logType >>= 16;
	QByteArray parBuf = logRecord.value(xSysLog::parameter).toByteArray();
	xSysLog::DoDiaPar(time, parBuf, logType);
}

// 显示当前选中日志记录的详细信息
void FormSysLog::showDetail(void)
{
    QString detail;
    quint16 input[LOG_INPUT_SIZE], output[LOG_OUTPUT_SIZE];
    quint64 inMain;
    quint32 outMain;
    quint16 inEm1, inEm2, inEm3, inEm4, outEm1, outEm2, outEm3, outEm4;

	QModelIndex curIdx = ui->logView->currentIndex();
	if (!curIdx.isValid())
	{
		xMessageBox::DoInformation(tr("提示"), tr("请先选择日志记录，再查看选中记录的详细内容。"));
		return;
	}
	QModelIndex curTime = curIdx.sibling(curIdx.row(), xSysLog::logTime);
	QString time = xSysLog::GetModel()->data(curTime, Qt::DisplayRole).toString();
	QModelIndex curType = curIdx.sibling(curIdx.row(), xSysLog::logType);
	QIcon type = xSysLog::GetModel()->data(curType, Qt::DecorationRole).value<QIcon>();
	QModelIndex curUser = curIdx.sibling(curIdx.row(), xSysLog::logUser);
	QString user = xSysLog::GetModel()->data(curUser, Qt::DisplayRole).toString();
	QModelIndex curValue = curIdx.sibling(curIdx.row(), xSysLog::logValue);
    detail = xSysLog::GetModel()->data(curValue, Qt::DisplayRole).toString();

    QSqlRecord logRecord =  xSysLog::GetModel()->record(curIdx.row());
    QByteArray inBuf = logRecord.value(xSysLog::input).toByteArray();
    QByteArray outBuf = logRecord.value(xSysLog::output).toByteArray();
    memcpy(input, inBuf.data(), sizeof(input));
    memcpy(output, outBuf.data(), sizeof(output));
    inMain = input[3];	inMain <<= 16;
    inMain |= input[2];	inMain <<= 16;
    inMain |= input[1];	inMain <<= 16;
    inMain |= input[0];
    inEm1 = input[4];
    inEm2 = input[5];
    inEm3 = input[6];
    inEm4 = input[7];
    outMain = output[1];	outMain <<= 16;
    outMain |= output[0];
    outEm1 = output[2];
    outEm2 = output[3];
    outEm3 = output[4];
    outEm4 = output[5];

    detail += ("\n-------------------------------------------------------");
    detail += tr("\n端口编号从右往左依次递增 ");
    detail += tr("\n主控模块输入状态: ") + QString::number(inMain, 2).left(32);
    detail += ("\n") + QString::number(inMain, 2).right(32);
    detail += ("\n") + tr("扩展模块1输入状态: ") + QString::number(inEm1, 2);
    detail += ("\n") +  tr("扩展模块2输入状态: ") + QString::number(inEm2, 2);
    detail += ("\n") +  tr("扩展模块3输入状态: ") + QString::number(inEm3, 2);
    detail += ("\n") +  tr("扩展模块4输入状态: ") + QString::number(inEm4, 2);
    detail += ("\n") +  tr("主控模块输出状态: ") + QString::number(outMain, 2);
    detail += ("\n") +  tr("扩展模块1输出状态: ") + QString::number(outEm1, 2);
    detail += ("\n") +  tr("扩展模块2输出状态: ") + QString::number(outEm2, 2);
    detail += ("\n") +  tr("扩展模块3输出状态: ") + QString::number(outEm3, 2);
    detail += ("\n") +  tr("扩展模块4输出状态: ") + QString::number(outEm4, 2);
    detail += ("\n") +  tr("\n-------------------------------------------------------");
    xSysLog::DoDiaDetail(time, type, user, detail);
}

void FormSysLog::query(void)
{
	if (pQuery == 0)
		pQuery = new DialogLogQuery;
	quint8 type;
	QDateTime begin, end;
	int ret = pQuery->DoForm(type, begin, end);
	if (ret == QDialog::Accepted)
	{
		if (type == DialogLogQuery::Normal)
		{
			// 显示一般记录
			ui->labelQuery->setText(tr("一般记录"));
			xSysLog::GetModel()->setFilter(QString("logType = '%1'").arg(SYSLOG_TYPE_NOR));
		}
		else if (type == DialogLogQuery::Message)
		{
			// 显示系统消息
			ui->labelQuery->setText(tr("系统消息"));
			xSysLog::GetModel()->setFilter(QString("logType = '%1'").arg(SYSLOG_TYPE_MSG));
		}
		else if (type == DialogLogQuery::Alarm)
		{
			// 显示系统报警
			ui->labelQuery->setText(tr("系统报警"));
			xSysLog::GetModel()->setFilter(QString("logType = '%1'").arg(SYSLOG_TYPE_ALM));
		}
		else if (type == DialogLogQuery::Query)
		{
			// 显示时间查询
			ui->labelQuery->setText(tr("按时间查询"));
            QString filter(tr("datetime(logTime) between datetime('%1') and datetime('%2')").arg(begin.toString(Qt::ISODate)).arg(end.toString(Qt::ISODate)));//.arg(begin.toString("yyyy-MM-dd hh:mm:ss")).arg(end.toString("yyyy-MM-dd hh:mm:ss")));
			xSysLog::GetModel()->setFilter(filter);
		}
		else
		{
			// 显示所有记录
			ui->labelQuery->setText(tr("所有记录"));
			xSysLog::GetModel()->setFilter("");
		}
		xSysLog::GetModel()->select();
	}
}
