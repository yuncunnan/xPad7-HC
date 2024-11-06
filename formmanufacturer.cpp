#include <stdlib.h>
#include <QApplication>
#include <QProcess>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QButtonGroup>
#include "xconfig.h"
#include "cmbprotocol.h"
#include "dialogframe.h"
#include "xusb.h"
#include "xpermissions.h"
#include "xstringresource.h"
#include "dialogkeyboard.h"
#include "xmessagebox.h"
#include "xsystemlog.h"
#include "formmanufacturer.h"
#include "ispdialog.h"
#include "ui_formmanufacturer.h"
#include "HalBoard.h"


#define PAGE_INFO			0
#define PAGE_IONAME			1
#define PAGE_PAR			2
#define PAGE_UPDATE			3
#define PAGE_LOG			4

extern HardwareInterface *board;
extern DialogFrame *pDialogMain;

FormManufacturer::FormManufacturer(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormManufacturer)
{
	// 设置界面
    ui->setupUi(this);
	// 初始化协议对象指针
	pModbus = modbus;
	// 如果系统图片不存在则创建
	QDir curDir(QDir::currentPath());
	if (!curDir.exists(QDir::currentPath() + QString("/"IMAGE_PATH"/")))
		curDir.mkdir(IMAGE_PATH);
#if defined(Q_WS_WIN)
    QDir usbDir(QDir::currentPath());
    if (!usbDir.exists(QDir::currentPath() + QString(XPAD_USB_PATH)))
        usbDir.mkdir("usb");
#endif
	// 构造文件系统数据源
	pDirModel = new xFileSystemModel(this);
	// 配置文件过滤器
	pDirModel->setNameFilterDisables(false);
	pDirModel->setFilter(QDir::Files);
	pDirModel->setReadOnly(true);
	// 设置数据源
	ui->fileView->setModel(pDirModel);
	// 设置表头字体
#if SIMULATOR
    ui->fileView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 8));
    ui->fileView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 12pt;}");
    ui->fileView->verticalHeader()->setFont(QFont("Microsoft YaHei", 8));
    ui->fileView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 12pt;}");
#else
	ui->fileView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->fileView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
	ui->fileView->verticalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->fileView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
#endif
    // 设置表头尺寸模式
	ui->fileView->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui->fileView->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
	ui->fileView->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);
	ui->fileView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	// 隐藏文件类型列
    ui->fileView->setColumnHidden(1, true);
    ui->fileView->setColumnHidden(2, true);
    // 设置列宽度
    ui->fileView->setColumnWidth(3, 260);
	// 组织页面选择按钮
	pTab = new QButtonGroup;
	pTab->addButton(ui->radioInfo, PAGE_INFO);
	pTab->addButton(ui->radioIo, PAGE_IONAME);
	pTab->addButton(ui->radioPar, PAGE_PAR);
	pTab->addButton(ui->radioUpdate, PAGE_UPDATE);
	pTab->addButton(ui->radioLog, PAGE_LOG);
	// 设置当前页面
	ui->radioInfo->setChecked(true);
	ui->stackedWidget->setCurrentIndex(0);
    setFileFilter();
    refreshUsb();
#if CONNECT_BY_NET
    ui->BtnIsp->setVisible(false);
#endif
	// 连接信号
	connect(this, SIGNAL(LogModelUpdate()), parent, SIGNAL(LogModelUpdate()));
    m_PortEdit = new DialogPortEdit;
    m_PortEdit->hide();
	m_AxisEdit = new DialogAxisEdit(this);
	m_AxisEdit->hide();
}

FormManufacturer::~FormManufacturer()
{
    delete ui;
	delete pDirModel;
	delete pTab;
	delete m_PortEdit;
	delete m_AxisEdit;
}

void FormManufacturer::changeEvent(QEvent *e)
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

// 根据当前用户权限设置界面
void FormManufacturer::setPermissions(void)
{
	quint16 id = pModbus->GetFactoryId();
	if ((id != 0) && (FACTORY != id))
		ui->labelUdiskTip->setText(tr("厂商代码不一致！"));
	else
		ui->labelUdiskTip->clear();
	if (xPermissions::GetCurrentUser() == xPermissions::SuperUser)
	{
		ui->pageInfo->setEnabled(pModbus->GetTypeMatch());
		ui->pageIo->setEnabled(pModbus->GetTypeMatch());
		ui->pagePar->setEnabled(pModbus->GetTypeMatch());
		ui->pageUpdate->setEnabled(true);
		ui->pageLog->setEnabled(pModbus->GetTypeMatch());
		ui->BtnPopup->setEnabled(true);
		ui->BtnID->setVisible(true);
	}
	else if (xPermissions::GetPermissions(PER_MANUFACTURER))
	{
		if ((id != 0) && (FACTORY != id))
		{
			ui->pageInfo->setEnabled(false);
			ui->pageIo->setEnabled(false);
			ui->pagePar->setEnabled(false);
			ui->pageUpdate->setEnabled(false);
			ui->pageLog->setEnabled(false);
			ui->BtnPopup->setEnabled(false);
		}
		else
		{
			ui->pageInfo->setEnabled(pModbus->GetTypeMatch());
			ui->pageIo->setEnabled(pModbus->GetTypeMatch());
			ui->pagePar->setEnabled(pModbus->GetTypeMatch());
			ui->pageUpdate->setEnabled(true);
			ui->pageLog->setEnabled(pModbus->GetTypeMatch());
			ui->BtnPopup->setEnabled(true);
		}
		ui->BtnID->setVisible(false);
	}
	else
	{
		ui->pageInfo->setEnabled(false);
		ui->pageIo->setEnabled(false);
		ui->pagePar->setEnabled(false);
		ui->pageUpdate->setEnabled(false);
		ui->pageLog->setEnabled(false);
		ui->BtnPopup->setEnabled(false);
		ui->BtnPopup->setEnabled(false);
		ui->BtnID->setVisible(false);
	}
}

bool FormManufacturer::EnterForm(void)
{
    // 检查用户权限
    if (xPermissions::GetPermissions(PER_MANUFACTURER) == false)
    {
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (pDialogMain)
            if (pDialogMain->ScreenSaverUserManager() == 0)
        return false;
    }
	// 初始化界面显示
	ui->labelMsg->clear();
	// 设置目录
	refreshUsb();
	// 连接信号槽
	connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 设置界面状态
	setPermissions();
	// 显示界面
//	show();
	return true;
}

bool FormManufacturer::ExitForm(void)
{
	// 取消信号槽连接
	disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 隐藏界面
//	hide();
	return true;
}

// 设置文件过滤器
void FormManufacturer::setFileFilter(void)
{
	switch (pTab->checkedId())
	{
	case PAGE_INFO:
		pDirModel->setNameFilters(QStringList() << "*"FAINF_FILE_EXT);
		break;
	case PAGE_IONAME:
		pDirModel->setNameFilters(QStringList() << "*"IO_NAME_EXT);
		break;
	case PAGE_PAR:
		pDirModel->setNameFilters(QStringList() << "*"PAR_BAK_EXT);
		break;
	case PAGE_UPDATE:
#if defined(Q_WS_QWS)
        pDirModel->setNameFilters(QStringList() << "*"+board->get_xPad_upg());
#else
        pDirModel->setNameFilters(QStringList() << "*.upg2");
#endif
		break;
	case PAGE_LOG:
		pDirModel->setNameFilters(QStringList() << "*"LOG_FILE_EXT);
		break;
	default:
		pDirModel->setNameFilters(QStringList() << "*");
		break;
	}
}

// 设置当前页面槽
void FormManufacturer::setCurrentPage(void)
{
	// 设置页面
	ui->stackedWidget->setCurrentIndex(pTab->checkedId());
	// 设置文件过滤器
	setFileFilter();
}

// 当前登录用户更改槽
void FormManufacturer::userChange(void)
{
	if (xPermissions::GetPermissions(PER_MANUFACTURER) == false)
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
	setPermissions();
}
// 刷新U盘
void FormManufacturer::refreshUsb(void)
{
#if defined(Q_WS_QWS)
	ui->fileView->setRootIndex(pDirModel->setRootPath("/root/"));
	if (xUsb::CheckInsert())
		ui->fileView->setRootIndex(pDirModel->setRootPath(XPAD_USB_PATH));
#else
    ui->fileView->setRootIndex(pDirModel->setRootPath(QDir::currentPath().append(XPAD_USB_PATH)));
#endif
}
// 弹出U盘槽
void FormManufacturer::popupUsb(void)
{
#if defined(Q_WS_QWS)
	if (!xUsb::CheckInsert())
		return;
    ui->fileView->setRootIndex(pDirModel->setRootPath("/root/"));
	system("umount "XPAD_USB_PATH);
    changeFont(tr("USB存储器现在可以安全移除。"));
#endif
}
// 导入开机画面槽
void FormManufacturer::loadSplash(void)
{
	QFile fileSrc(pDirModel->filePath(ui->fileView->currentIndex()));
	QFile fileDes(QDir::currentPath() + QString("/"XPAD_SPLASH_NAME));
	QString desName;
	desName = fileDes.fileName();
	// 检查开机画面文件是否存在
	if (fileSrc.exists() == false)
	{
        changeFont(tr("请先选择要导入的开机画面文件！"));
		return;
	}
	// 复制开机画面文件
	if (fileDes.exists())
	{
		// 目标文件如果存在则先删除
		if (fileDes.remove() == false)
		{
            changeFont(tr("无法移除系统原有的开机画面文件！"));
			return;
		}
	}
	if (fileSrc.copy(desName) == false)
        changeFont(tr("复制开机画面文件失败！"));
	else
	{
        changeFont(tr("开机画面导入成功！"));
		// 写入系统日志
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_LD_SPLASH, QFileInfo(fileSrc).fileName());
		xSysLog::SaveChange();
#if defined(Q_OS_LINUX)
		sync();
#endif
	}
}
// 导入待机画面槽
void FormManufacturer::loadWallpaper(void)
{
	QFile fileSrc(pDirModel->filePath(ui->fileView->currentIndex()));
	QFile fileDes(QDir::currentPath() + QString("/"XPAD_WALLPAPER_NAME));
	QString desName;
	desName = fileDes.fileName();
	// 检查待机画面文件是否存在
	if (fileSrc.exists() == false)
	{
        changeFont(tr("请先选择要导入的待机画面文件！"));
		return;
	}
	// 复制待机画面文件
	if (fileDes.exists())
	{
		// 目标文件如果存在则先删除
		if (fileDes.remove() == false)
		{
            changeFont(tr("无法移除系统原有的待机画面文件！"));
			return;
		}
	}
	if (fileSrc.copy(desName) == false)
        changeFont(tr("复制待机画面文件失败！"));
	else
	{
        changeFont(tr("待机画面导入成功！"));
		// 写入系统日志
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_LD_WPAPER, QFileInfo(fileSrc).fileName());
		xSysLog::SaveChange();
#if defined(Q_OS_LINUX)
		sync();
#endif
	}
}
// 导入厂商信息槽
void FormManufacturer::loadInformation(void)
{
	QFile fileSrc(pDirModel->filePath(ui->fileView->currentIndex()));
	QFile fileDes(QDir::currentPath() + QString("/"XPAD_INFORMATION_NAME));
	QString desName;
	desName = fileDes.fileName();
	// 检查厂商信息文件是否存在
	if (fileSrc.exists() == false)
	{
        changeFont(tr("请先选择要导入的厂商信息文件！"));
		return;
	}
	// 复制厂商信息文件
	if (fileDes.exists())
	{
		// 目标文件如果存在则先删除
		if (fileDes.remove() == false)
		{
            changeFont(tr("无法移除系统原有的厂商信息文件！"));
			return;
		}
	}
	if (fileSrc.copy(desName) == false)
        changeFont(tr("复制厂商信息文件失败！"));
	else
	{
        changeFont(tr("厂商信息导入成功！"));
		// 写入系统日志
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_LD_INFOR, QFileInfo(fileSrc).fileName());
		xSysLog::SaveChange();
#if defined(Q_OS_LINUX)
		sync();
#endif
	}
}
// 导入端口名称槽
void FormManufacturer::loadIoNames(void)
{
	QFile fileSrc(pDirModel->filePath(ui->fileView->currentIndex()));
	QFile fileDes(QDir::currentPath() + QString("/"XPAD_IO_NAME));
	// 检查端口名称定义文件是否存在
	if (fileSrc.exists() == false)
	{
        changeFont(tr("请先选择要导入的端口名称定义文件！"));
		return;
	}
	// 复制端口名称定义文件
	if (fileDes.exists())
	{
		// 目标文件如果存在则先删除
		if (!fileDes.remove())
		{
            changeFont(tr("无法移除系统原有的端口名称定义文件！"));
			return;
		}
	}
	if (!fileSrc.copy(QDir::currentPath() + QString("/"XPAD_IO_NAME)))
	{
        changeFont(tr("复制端口名称定义文件失败！"));
		return;
	}
	// 写入系统日志
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_LD_PORTNAME, QFileInfo(fileSrc).fileName());
	xSysLog::SaveChange();
#if defined(Q_OS_LINUX)
	sync();
#endif
	// 更新界面端口名称
	quint8 lan = pModbus->GetLanguage();
	xStringResource::retranslateRes(lan);
    changeFont(tr("端口名称定义导入成功！"));
}
// 重置端口名称设置
void FormManufacturer::resetIoNames(void)
{
    if(xMessageBox::DoQuestion(tr("系统提示"),tr("是否清除端口名称？")) != XMSG_RET_YES)
        return;
	QFile fileName(QDir::currentPath() + QString("/"XPAD_IO_NAME));
	if (fileName.exists())
	{
		fileName.remove();
		// 写入系统日志
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_RST_PORTNAME);
		xSysLog::SaveChange();
#if defined(Q_OS_LINUX)
		sync();
#endif
		// 更新界面端口名称
		quint8 lan = pModbus->GetLanguage();
		xStringResource::retranslateRes(lan);
	}
    changeFont(tr("端口名称已经成功重置为出厂默认值！"));
}
// 升级软件槽
void FormManufacturer::updateSoftware(void)
{
	QFile fileSrc(pDirModel->filePath(ui->fileView->currentIndex()));
	QString desName;
	QFile fileDes(QDir::currentPath() + QString("/"XPAD_PGM_NAME));
	QFile fileBak(QDir::currentPath() + QString("/"XPAD_PGM_NAME".bak"));
	desName = fileDes.fileName();
	if (fileSrc.exists() == false)
	{
        changeFont(tr("请先选择操作器程序文件升级包！"));
		return;
	}
#if defined(Q_WS_QWS) || defined(Q_WS_X11)
	// 备份程序文件
    changeFont(tr("备份原有的程序文件..."));
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	if (fileDes.exists())
	{
		// 备份文件如果存在则先删除
		if (fileBak.exists())
		{
			if (fileBak.remove() == false)
			{
                changeFont(tr("无法删除原有的程序文件备份！"));
				return;
			}
		}
		// 重命名原有的程序文件为备份文件
		if (fileDes.rename(QString(XPAD_PGM_NAME".bak")) == false)
		{
            changeFont(tr("无法备份原有的程序文件！"));
			return;
		}
	}
	// 复制程序文件
    changeFont(tr("复制操作器程序文件..."));
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	if (fileSrc.copy(desName) == false)
	{
        changeFont(tr("复制操作器程序文件失败！恢复备份的程序文件..."));
		if (fileDes.rename(QString(XPAD_PGM_NAME)) == false)
		{
            changeFont(tr("恢复操作器程序文件失败，操作器程序已经损坏，请联系生产厂商维修！"));
			return;
		}
        changeFont(tr("已经恢复程序文件，本次软件升级失败！"));
		sync();
	}
	else
	{
		// 写入系统日志
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_UPDATE, QFileInfo(fileSrc).fileName());
		xSysLog::SaveChange();
        changeFont(tr("操作器软件升级成功！请重新启动系统。"));
		sync();
	}
#endif
}
// 恢复备份的软件槽
void FormManufacturer::restoreSoftware(void)
{
    if (xMessageBox::DoQuestion(tr("系统提示"), tr("本操作将会把系统回退到升级前版本,并且无法撤销.\n如果要重置系统、伺服等参数,请进入系统设置--系统维护页面进行操作！\n确定要恢复到旧版本吗？")) != XMSG_RET_YES)
		return;
	QString desName;
	QFile fileDes(QDir::currentPath() + QString("/"XPAD_PGM_NAME));
	QFile fileBak(QDir::currentPath() + QString("/"XPAD_PGM_NAME".bak"));
	desName = fileDes.fileName();
	if (fileBak.exists() == false)
	{
        changeFont(tr("不存在可供恢复的操作器程序文件备份！"));
		return;
	}
#if defined(Q_WS_QWS) || defined(Q_WS_X11)
	// 当前程序文件如果存在则先删除
	if (fileDes.exists())
	{
		if (fileDes.remove() == false)
		{
            changeFont(tr("无法删除当前程序文件！"));
			return;
		}
	}
	// 恢复程序文件
    changeFont(tr("恢复操作器程序文件..."));
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	if (fileBak.copy(desName) == false)
	{
        changeFont(tr("恢复备份的程序文件失败，操作器当前程序已经损坏，请联系生产厂商维修！"));
		return;
	}
	else
	{
		// 写入系统日志
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_RESTORE);
		xSysLog::SaveChange();
        changeFont(tr("备份的程序文件已经成功恢复！请重新启动系统。"));
		sync();
	}
#endif
}
// 写入厂商 ID
void FormManufacturer::setFactoryId(void)
{
	if (pModbus->WriteFactory(FACTORY) != SENDMSG_RET_ACK)
        changeFont(tr("写入操作器厂商代码到主控模块失败！"));
	else
	{
		pModbus->ReadFactory();
        changeFont(tr("操作器厂商代码已经成功写入主控模块！"));
		setPermissions();
	}
}
// 重新启动软件
void FormManufacturer::restartApp(void)
{
	// 写入系统日志
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_RESTART);
	xSysLog::SaveChange();
	// 重新启动
	qApp->exit(773);
}

// **************************************************
// 从主控模块读取伺服参数设置
// **************************************************
bool FormManufacturer::readSrvPar(ServoParameter &par)
{
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	trvRelPos = settings.value(XPAD_SET_TRVRELPOS, 0).toUInt();					// 横行轴置物位置
	trvCatPos = settings.value(XPAD_SET_TRVCATPOS, 1800).toUInt();					// 横行轴取物位置
	trvWaitPos = settings.value(XPAD_SET_TRVWAIT, 0).toUInt();					// 横行轴原点复归后待机位置
	paVerCatPos = settings.value(XPAD_SET_PAVERCAT, 750).toUInt();					// 正臂上下轴取物位置
	paVerRelPos = settings.value(XPAD_SET_PAVERREL, 750).toUInt();
	paVerWaitPos = settings.value(XPAD_SET_PAVERWAIT, 750).toUInt();
	paHorCatPos = settings.value(XPAD_SET_PAHORCAT, 750).toUInt();
	paHorRelPos = settings.value(XPAD_SET_PAHORREL, 750).toUInt();
	paHorWaitPos = settings.value(XPAD_SET_PAHORWAIT, 750).toUInt();
	raVerCatPos = settings.value(XPAD_SET_RAVERCAT, 750).toUInt();					// 副臂上下轴取物位置
	raVerRelPos = settings.value(XPAD_SET_RAVERREL, 750).toUInt();
	raVerWaitPos = settings.value(XPAD_SET_RAVERWAIT, 750).toUInt();
	raHorCatPos = settings.value(XPAD_SET_RAHORCAT, 750).toUInt();
	raHorRelPos = settings.value(XPAD_SET_RAHORREL, 750).toUInt();
	raHorWaitPos = settings.value(XPAD_SET_RAHORWAIT, 750).toUInt();
	extCatPos = settings.value(XPAD_SET_EXTCAT, 750).toUInt();
	extRelPos = settings.value(XPAD_SET_EXTREL, 750).toUInt();
	extWaitPos = settings.value(XPAD_SET_EXTWAIT, 750).toUInt();
	pModbus->GetServo(par);
	return true;
}

// **************************************************
// 导出机械手设置
// 保存系统参数和伺服参数设置到USB存储器的参数设置文件中
// **************************************************
void FormManufacturer::cfgExport(void)
{
	SystemParameter sysPar;
	ServoParameter srvPar;
	// *** 检测USB存储器是否插入 ***
	if (!xUsb::CheckInsert())
	{
        changeFont(tr("没有检测到USB存储器，无法导出机械手设置数据！"));
		return;
	}
	// *** 输入另存为新文件名 ***
#if defined(Q_WS_WIN)
    QString path = QDir::currentPath().append(XPAD_USB_PATH);
#else
    QString path(XPAD_USB_PATH);
#endif
	QString name;
	if (xKbd->DoForm(name, KEYBOARD_TYPE_FILENAME) != QDialog::Accepted)
		return;
	name = path + name + QString(PAR_BAK_EXT);
	QFile newFile(name);
	if (newFile.exists())
	{
		// 如果文件已经存在则警告并退出
        changeFont(tr("文件已经存在，无法进行参数导出操作！"));
		return;
	}
	// *** 开始导出机械手参数设置 ***
	// 从主控模块读取系统参数设置
	pModbus->GetSystem(sysPar);
	// 从主控模块读取伺服参数设置
	if (!readSrvPar(srvPar))
	{
        changeFont(tr("从主控模块读取伺服参数设置失败！"));
		return;
	}
	// *** 写入参数设置文件 ***
	{
		QSettings saveFile(name, QSettings::IniFormat);
		// 导出系统参数设置
		saveFile.setValue(PARBAK_ALM_TIMES, sysPar.m_alarm_times);				// 报警器鸣叫次数
		saveFile.setValue(PARBAK_ALM_INTERVAL, sysPar.m_alarm_interval);		// 报警器鸣叫间隔
		saveFile.setValue(PARBAK_LANGUAGE, sysPar.m_language);					// 语言设置
		saveFile.setValue(PARBAK_ROTATE, sysPar.m_rotate_out_at_origin);		// 横行时正臂倒角状态
		saveFile.setValue(PARBAK_DOOR, sysPar.m_pause_open_door);				// 自动运行时开安全门
		saveFile.setValue(PARBAK_RVERSRV_USE, sysPar.m_rver_servo_use);			// 副臂上下轴伺服使用
		saveFile.setValue(PARBAK_RHORSRV_USE, sysPar.m_rhor_servo_use);			// 副臂引拔轴伺服使用
		saveFile.setValue(PARBAK_RUNNER_USE, sysPar.m_runner_use);				// 气动副臂使用
		saveFile.setValue(PARBAK_RUNNER_DOWN_USE, sysPar.m_runner_down_use);	// 气动副臂下位电眼使用
        saveFile.setValue(PARBAK_RUNNER_ADVANCE_USE, sysPar.m_runner_advance_use);	// 气动副臂前进电眼使用
        saveFile.setValue(PARBAK_RUNNER_RETURN_USE, sysPar.m_runner_return_use);	// 气动副臂后退电眼使用
		saveFile.setValue(PARBAK_ADJUST_USE, sysPar.m_adjust_use);				// 调位使用
        saveFile.setValue(PARBAK_HOME_INMOLD, sysPar.m_home_inmold);				// 调位使用
		saveFile.setValue(PARBAK_EXTSRV_USE, sysPar.m_ext_servo_use);			// 扩展轴伺服使用
        saveFile.setValue(PARBAK_EXTEND_BIT_USE, sysPar.m_extend_bit_use);      // 扩展控制位
		saveFile.setValue(PARBAK_MCP, sysPar.m_mold_closed_use);				// 关模完成信号配置
		saveFile.setValue(PARBAK_IMOP, sysPar.m_imop_dwn_use);					// 开模中间信号配置
		saveFile.setValue(PARBAK_MMOP, sysPar.m_mid_open_use);					// 开中板模确认信号配置
		saveFile.setValue(PARBAK_ROTATE_IN, sysPar.m_rotate_inmold_use);		// 模内倒角使用
		saveFile.setValue(PARBAK_WAIT_OUTMOULD, sysPar.m_wait_outmould);		// 待机选项
		saveFile.setValue(PARBAK_PLAN, sysPar.m_plan_molding);					// 计划生产数量
		saveFile.setValue(PARBAK_REMIND, sysPar.m_plan_alarm);					// 生产数量提醒
		saveFile.setValue(PARBAK_REJECT, sysPar.m_reject_alarm);				// 不良品数量报警
		saveFile.setValue(PARBAK_RCM_POLARITY, sysPar.m_polary[0]);				// 主控模块信号极性
		saveFile.setValue(PARBAK_EM1_POLARITY, sysPar.m_polary[1]);				// 扩展模块1信号极性
		saveFile.setValue(PARBAK_EM2_POLARITY, sysPar.m_polary[2]);				// 扩展模块2信号极性
		saveFile.setValue(PARBAK_EM3_POLARITY, sysPar.m_polary[3]);				// 扩展模块3信号极性
		saveFile.setValue(PARBAK_EM4_POLARITY, sysPar.m_polary[4]);				// 扩展模块4信号极性
        saveFile.setValue(PARBAK_MAIN_OUTPOLARITY, sysPar.m_outputpolary[0]);				// 扩展模块1信号极性
        saveFile.setValue(PARBAK_EM1_OUTPOLARITY, sysPar.m_outputpolary[1]);				// 扩展模块1信号极性
        saveFile.setValue(PARBAK_EM2_OUTPOLARITY, sysPar.m_outputpolary[2]);				// 扩展模块2信号极性
        saveFile.setValue(PARBAK_EM3_OUTPOLARITY, sysPar.m_outputpolary[3]);				// 扩展模块3信号极性
        saveFile.setValue(PARBAK_EM4_OUTPOLARITY, sysPar.m_outputpolary[4]);				// 扩展模块4信号极性
        saveFile.setValue(PARBAK_RCM_IGNORE, sysPar.m_ignore[0]);				// 主控模块信号报警设置
		saveFile.setValue(PARBAK_EM1_IGNORE, sysPar.m_ignore[1]);				// 扩展模块1信号报警设置
		saveFile.setValue(PARBAK_EM2_IGNORE, sysPar.m_ignore[2]);				// 扩展模块2信号报警设置
		saveFile.setValue(PARBAK_EM3_IGNORE, sysPar.m_ignore[3]);				// 扩展模块3信号报警设置
		saveFile.setValue(PARBAK_EM4_IGNORE, sysPar.m_ignore[4]);				// 扩展模块4信号报警设置
		saveFile.setValue(PARBAK_RCM_NOALM, sysPar.m_noalm[0]);					// 主控模块模内不报警
		saveFile.setValue(PARBAK_EM1_NOALM, sysPar.m_noalm[1]);					// 扩展模块1模内不报警
		saveFile.setValue(PARBAK_EM2_NOALM, sysPar.m_noalm[2]);					// 扩展模块2模内不报警
		saveFile.setValue(PARBAK_EM3_NOALM, sysPar.m_noalm[3]);					// 扩展模块3模内不报警
		saveFile.setValue(PARBAK_EM4_NOALM, sysPar.m_noalm[4]);					// 扩展模块4模内不报警
		saveFile.setValue(PARBAK_JIG_USE, sysPar.m_jig_use);					// 治具使用
        saveFile.setValue(PARBAK_PROC2_USE, sysPar.m_proc2_use);                // 进程2使用
        saveFile.setValue(PARBAK_PROC3_USE, sysPar.m_proc3_use);                // 进程3使用
        saveFile.setValue(PARBAK_IP, sysPar.m_ip);                      // IP地址
        saveFile.setValue(PARBAK_SUBMASK, sysPar.m_submask);
        saveFile.setValue(PARBAK_GATEWAY, sysPar.m_gateway);
        saveFile.setValue(PARBAK_OIL_INTERVAL, sysPar.m_oil_interval);
        saveFile.setValue(PARBAK_OIL_TIME, sysPar.m_oil_time);
        saveFile.setValue(PARBAK_OIL_USE, sysPar.m_oil_use);
        saveFile.setValue(PARBAK_ROTATE_USE, sysPar.m_rotate_use);
        saveFile.setValue(PARBAK_RUN_RATOTE_USE, sysPar.m_run_rotate_use);
        saveFile.setValue(PARBAK_DOOR_RESET_USE, sysPar.m_door_reset_use);
        saveFile.setValue(PARBAK_OIL_USE_CTRL, sysPar.m_oil_ctrl_use);
        saveFile.setValue(PARBAK_VISION1_IP, sysPar.m_visionip1);
        saveFile.setValue(PARBAK_VISION2_IP, sysPar.m_visionip2);
        saveFile.setValue(PARBAK_VISION3_IP, sysPar.m_visionip3);
        saveFile.setValue(PARBAK_VISION4_IP, sysPar.m_visionip4);
        saveFile.setValue(PARBAK_VISION5_IP, sysPar.m_visionip5);
        saveFile.setValue(PARBAK_VISION6_IP, sysPar.m_visionip6);
        saveFile.setValue(PARBAK_VISION7_IP, sysPar.m_visionip7);
        saveFile.setValue(PARBAK_VISION8_IP, sysPar.m_visionip8);
        saveFile.setValue(PARBAK_VISION1_PORT, sysPar.m_vision1port);
        saveFile.setValue(PARBAK_VISION2_PORT, sysPar.m_vision2port);
        saveFile.setValue(PARBAK_VISION3_PORT, sysPar.m_vision3port);
        saveFile.setValue(PARBAK_VISION4_PORT, sysPar.m_vision4port);
        saveFile.setValue(PARBAK_VISION5_PORT, sysPar.m_vision5port);
        saveFile.setValue(PARBAK_VISION6_PORT, sysPar.m_vision6port);
        saveFile.setValue(PARBAK_VISION7_PORT, sysPar.m_vision7port);
        saveFile.setValue(PARBAK_VISION8_PORT, sysPar.m_vision8port);
        saveFile.setValue(PARBAK_VISION1_TRIGGER, sysPar.m_vision1_trigger);
        saveFile.setValue(PARBAK_VISION2_TRIGGER, sysPar.m_vision2_trigger);
        saveFile.setValue(PARBAK_VISION3_TRIGGER, sysPar.m_vision3_trigger);
        saveFile.setValue(PARBAK_VISION4_TRIGGER, sysPar.m_vision4_trigger);
        saveFile.setValue(PARBAK_VISION5_TRIGGER, sysPar.m_vision5_trigger);
        saveFile.setValue(PARBAK_VISION6_TRIGGER, sysPar.m_vision6_trigger);
        saveFile.setValue(PARBAK_VISION7_TRIGGER, sysPar.m_vision7_trigger);
        saveFile.setValue(PARBAK_VISION8_TRIGGER, sysPar.m_vision8_trigger);
        saveFile.setValue(PARBAK_VISION1_OUTVAR, sysPar.m_vision1_outvar);
        saveFile.setValue(PARBAK_VISION2_OUTVAR, sysPar.m_vision2_outvar);
        saveFile.setValue(PARBAK_VISION3_OUTVAR, sysPar.m_vision3_outvar);
        saveFile.setValue(PARBAK_VISION4_OUTVAR, sysPar.m_vision4_outvar);
        saveFile.setValue(PARBAK_VISION5_OUTVAR, sysPar.m_vision5_outvar);
        saveFile.setValue(PARBAK_VISION6_OUTVAR, sysPar.m_vision6_outvar);
        saveFile.setValue(PARBAK_VISION7_OUTVAR, sysPar.m_vision7_outvar);
        saveFile.setValue(PARBAK_VISION8_OUTVAR, sysPar.m_vision8_outvar);

        // 导出伺服参数设置
		// 伺服参数-机械最大行程
		saveFile.setValue(PARBAK_HOR_MAXLEN, srvPar.m_machine_max_len_x);		// 正/副臂原点机械距离
		saveFile.setValue(PARBAK_HOR_MINLEN, srvPar.m_min_safe_dis_x_b);		// 正/副臂最小安全距离
		// 伺服参数-软件最大行程
		saveFile.setValue(PARBAK_PVER_SOFTLEN, srvPar.m_software_max_len_y);	// 正臂上下轴最大软件行程
		saveFile.setValue(PARBAK_TRAV_SOFTLEN, srvPar.m_software_max_len_z);	// 横行轴最大软件行程
		saveFile.setValue(PARBAK_RVER_SOFTLEN, srvPar.m_software_max_len_a);	// 副臂上下轴最大软件行程
		saveFile.setValue(PARBAK_EXTE_SOFTLEN, srvPar.m_software_max_len_c);	// 扩展轴最大软件行程
        // 原点偏移
        saveFile.setValue(PARBAK_X_OFFSET, srvPar.m_origin_offset_x);
        saveFile.setValue(PARBAK_Y_OFFSET, srvPar.m_origin_offset_y);
        saveFile.setValue(PARBAK_Z_OFFSET, srvPar.m_origin_offset_z);
        saveFile.setValue(PARBAK_A_OFFSET, srvPar.m_origin_offset_a);
        saveFile.setValue(PARBAK_B_OFFSET, srvPar.m_origin_offset_b);
        saveFile.setValue(PARBAK_C_OFFSET, srvPar.m_origin_offset_c);
        // 原点待机点
        saveFile.setValue(PARBAK_X_HOME_POS, srvPar.m_home_pos_x);
        saveFile.setValue(PARBAK_Y_HOME_POS, srvPar.m_home_pos_y);
        saveFile.setValue(PARBAK_Z_HOME_POS, srvPar.m_home_pos_z);
        saveFile.setValue(PARBAK_A_HOME_POS, srvPar.m_home_pos_a);
        saveFile.setValue(PARBAK_B_HOME_POS, srvPar.m_home_pos_b);
        saveFile.setValue(PARBAK_C_HOME_POS, srvPar.m_home_pos_c);
        // 模
        saveFile.setValue(PARBAK_X_MOD, srvPar.m_mod_x);
        saveFile.setValue(PARBAK_Y_MOD, srvPar.m_mod_y);
        saveFile.setValue(PARBAK_Z_MOD, srvPar.m_mod_z);
        saveFile.setValue(PARBAK_A_MOD, srvPar.m_mod_a);
        saveFile.setValue(PARBAK_B_MOD, srvPar.m_mod_b);
        saveFile.setValue(PARBAK_C_MOD, srvPar.m_mod_c);
        // 编码器
        saveFile.setValue(PARBAK_ENCODER_X, srvPar.m_encoder_x);
        saveFile.setValue(PARBAK_ENCODER_Y, srvPar.m_encoder_y);
        saveFile.setValue(PARBAK_ENCODER_Z, srvPar.m_encoder_z);
        saveFile.setValue(PARBAK_ENCODER_A, srvPar.m_encoder_a);
        saveFile.setValue(PARBAK_ENCODER_B, srvPar.m_encoder_b);
        saveFile.setValue(PARBAK_ENCODER_C, srvPar.m_encoder_c);

        // 伺服参数-安全区
        saveFile.setValue(PARBAK_PVER_WAIT, srvPar.m_max_wait_pos_inmold_y);	// 正臂上下轴上位安全区
        saveFile.setValue(PARBAK_RVER_WAIT, srvPar.m_max_wait_pos_inmold_a);	// 副臂上下轴上位安全区
        saveFile.setValue(PARBAK_TRAV_OMIN, srvPar.m_min_safe_pos_outmold_z);	// 横行轴模外安全区起点
        saveFile.setValue(PARBAK_TRAV_OMAX, srvPar.m_max_safe_pos_outmold_z);	// 横行轴模外安全区终点
        saveFile.setValue(PARBAK_TRAV_IMIN, srvPar.m_min_safe_pos_inmold_z);	// 横行轴模内安全区起点
        saveFile.setValue(PARBAK_TRAV_IMAX, srvPar.m_max_safe_pos_inmold_z);	// 横行轴模内安全区终点
        saveFile.setValue(PARBAK_TRAV_OMIN2, srvPar.m_min_safe_pos_outmold2_z);	// 横行轴模外安全区起点
        saveFile.setValue(PARBAK_TRAV_OMAX2, srvPar.m_max_safe_pos_outmold2_z);	// 横行轴模外安全区终点
		saveFile.setValue(PARBAK_PHOR_IMIN, srvPar.m_min_safe_pos_inmold_x);	// 正臂引拔轴模内安全区起点
		saveFile.setValue(PARBAK_PHOR_IMAX, srvPar.m_max_safe_pos_inmold_x);	// 正臂引拔轴模内安全区终点
		saveFile.setValue(PARBAK_RHOR_IMIN, srvPar.m_min_safe_pos_inmold_b);	// 副臂引拔轴模内安全区起点
		saveFile.setValue(PARBAK_RHOR_IMAX, srvPar.m_max_safe_pos_inmold_b);	// 副臂引拔轴模内安全区终点
        saveFile.setValue(PARBAK_MIN_ROT, srvPar.m_min_a_inmold);	// 副臂引拔轴模内安全区终点
        saveFile.setValue(PARBAK_MAX_ROT, srvPar.m_max_a_inmold);	// 副臂引拔轴模内安全区终点
        saveFile.setValue(PARBAK_MIN_TRV, srvPar.m_min_a_trv);	// 副臂引拔轴模内安全区终点
        saveFile.setValue(PARBAK_MAX_TRV, srvPar.m_max_a_trv);	// 副臂引拔轴模内安全区终点
        saveFile.setValue(PARBAK_RHOR_ZAMIN, srvPar.m_min_safe_pos_inmold_z_a);
        saveFile.setValue(PARBAK_RHOR_ZAMAX, srvPar.m_max_safe_pos_inmold_z_a);

        saveFile.setValue(PARBAK_TRAV_REL_POS, trvRelPos);							// 横行轴置物位置
        saveFile.setValue(PARBAK_TRAV_CAT_POS, trvCatPos);							// 横行轴取物位置
        saveFile.setValue(PARBAK_TRAV_WAIT_POS, trvWaitPos);
        saveFile.setValue(PARBAK_PVER_CAT_POS, paVerCatPos);						// 正臂上下轴取物位置
        saveFile.setValue(PARBAK_PVER_REL_POS, paVerRelPos);
        saveFile.setValue(PARBAK_PVER_WAIT_POS, paVerWaitPos);
        saveFile.setValue(PARBAK_PHOR_CAT_POS, paHorCatPos);
        saveFile.setValue(PARBAK_PHOR_REL_POS, paHorRelPos);
        saveFile.setValue(PARBAK_PHOR_WAIT_POS, paHorWaitPos);
        saveFile.setValue(PARBAK_RVER_CAT_POS, raVerCatPos);						// 副臂上下轴取物位置
        saveFile.setValue(PARBAK_RVER_REL_POS, raVerRelPos);
        saveFile.setValue(PARBAK_RVER_WAIT_POS, raVerWaitPos);
        saveFile.setValue(PARBAK_RHOR_CAT_POS, raHorCatPos);
        saveFile.setValue(PARBAK_RHOR_REL_POS, raHorRelPos);
        saveFile.setValue(PARBAK_RHOR_WAIT_POS, raHorWaitPos);
        saveFile.setValue(PARBAK_EXT_CAT_POS, extCatPos);
        saveFile.setValue(PARBAK_EXT_REL_POS, extRelPos);
        saveFile.setValue(PARBAK_EXT_WAIT_POS, extWaitPos);

        saveFile.setValue(PARBAK_RHOR_TRVMIN, srvPar.m_min_b_trave);
        saveFile.setValue(PARBAK_RHOR_TRVMAX, srvPar.m_max_b_trave);
        saveFile.setValue(PARBAK_EXT_TRVMIN,  srvPar.m_min_c_trave);
        saveFile.setValue(PARBAK_EXT_TRVMAX,  srvPar.m_max_c_trave);
        saveFile.setValue(PARBAK_EXT_INMOLDMIN,srvPar.m_min_c_inmold);
        saveFile.setValue(PARBAK_EXT_INMOLDMAX, srvPar.m_max_c_inmold);
        saveFile.setValue(PARBAK_PHOR_TRVMIN,  srvPar.m_min_x_trave);
        saveFile.setValue(PARBAK_PHOR_TRVMAX,  srvPar.m_max_x_trave);
        // 原点偏移

		// 伺服参数-正臂引拔轴速度/加速度
		saveFile.setValue(PARBAK_PHOR_SPD, srvPar.m_xmax_speed);				// 正臂引拔轴速度
		saveFile.setValue(PARBAK_PHOR_ACC, srvPar.m_xmax_acceleration);			// 正臂引拔轴加速度
        saveFile.setValue(PARBAK_PHOR_JERK, srvPar.m_xmax_jerk);
		// 伺服参数-正臂上下轴速度/加速度
		saveFile.setValue(PARBAK_PVER_SPD, srvPar.m_ymax_speed);				// 正臂上下轴速度
		saveFile.setValue(PARBAK_PVER_ACC, srvPar.m_ymax_acceleration);			// 正臂上下轴加速度
        saveFile.setValue(PARBAK_PVER_JERK, srvPar.m_ymax_jerk);
		// 伺服参数-横行轴速度/加速度
		saveFile.setValue(PARBAK_TRAV_SPD, srvPar.m_zmax_speed);				// 横行轴速度
		saveFile.setValue(PARBAK_TRAV_ACC, srvPar.m_zmax_acceleration);			// 横行轴加速度
        saveFile.setValue(PARBAK_TRAV_JERK, srvPar.m_zmax_jerk);
		// 伺服参数-副臂引拔轴速度/加速度
		saveFile.setValue(PARBAK_RHOR_SPD, srvPar.m_bmax_speed);				// 副臂引拔轴速度
		saveFile.setValue(PARBAK_RHOR_ACC, srvPar.m_bmax_acceleration);			// 副臂引拔轴加速度
        saveFile.setValue(PARBAK_RHOR_JERK, srvPar.m_bmax_jerk);
		// 伺服参数-副臂上下轴速度/加速度
		saveFile.setValue(PARBAK_RVER_SPD, srvPar.m_amax_speed);				// 副臂上下轴速度
		saveFile.setValue(PARBAK_RVER_ACC, srvPar.m_amax_acceleration);			// 副臂上下轴加速度
        saveFile.setValue(PARBAK_RVER_JERK, srvPar.m_amax_jerk);
		// 伺服参数-扩展轴速度/加速度
		saveFile.setValue(PARBAK_EXTE_SPD, srvPar.m_cmax_speed);				// 扩展轴速度
		saveFile.setValue(PARBAK_EXTE_ACC, srvPar.m_cmax_acceleration);			// 扩展轴加速度
        saveFile.setValue(PARBAK_EXTE_JERK, srvPar.m_cmax_jerk);
        // 马达转动
        saveFile.setValue(PARBAK_PHOR_UNITS, srvPar.m_x_units);
        saveFile.setValue(PARBAK_PHOR_PLUSES, srvPar.m_x_pluses);
        saveFile.setValue(PARBAK_PVER_UNITS, srvPar.m_y_units);
        saveFile.setValue(PARBAK_PVER_PLUSES, srvPar.m_y_pluses);
        saveFile.setValue(PARBAK_RHOR_UNITS, srvPar.m_b_units);
        saveFile.setValue(PARBAK_RHOR_PLUSES, srvPar.m_b_pluses);
        saveFile.setValue(PARBAK_RVER_UNITS, srvPar.m_a_units);
        saveFile.setValue(PARBAK_RVER_PLUSES, srvPar.m_a_pluses);
        saveFile.setValue(PARBAK_TRV_UNITS, srvPar.m_z_units);
        saveFile.setValue(PARBAK_TRV_PLUSES, srvPar.m_z_pluses);
        saveFile.setValue(PARBAK_EXT_UNITS, srvPar.m_c_units);
        saveFile.setValue(PARBAK_EXT_PLUSES, srvPar.m_c_pluses);
        // 轴类型 方向
        saveFile.setValue(PARBAK_ANGLE_BMP, srvPar.m_angle_type);
        // 减速类型
        saveFile.setValue(PARBAK_RAMP_BMP, srvPar.m_dec_type);
        // 原点归位模式
        saveFile.setValue(PARBAK_HOME_MODE, srvPar.m_home_mode);
        saveFile.setValue(PARBAK_HOME_VEL, srvPar.m_home_vel);
        saveFile.setValue(PARBAK_HOME_VEL_SLOW, srvPar.m_home_vel_slow);

        saveFile.sync();
	}
	// 写入系统日志
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_PAR_EXPORT);
	xSysLog::SaveChange();
#if defined(Q_OS_LINUX)
	sync();
#endif
    changeFont(tr("机械手参数设置已经成功导出！"));
}

// **************************************************
// 导入机械手设置
// 从USB存储器上的参数设置文件中读取系统参数和伺服参数设置并保存到主控模块上
// **************************************************
void FormManufacturer::cfgImport(void)
{
	SystemParameter sysPar;
	ServoParameter srvPar;
	// *** 开始导入机械手参数设置 ***
	// 从主控模块读取系统参数设置
	pModbus->GetSystem(sysPar);
	// 从主控模块读取伺服参数设置
	if (!readSrvPar(srvPar))
	{
        changeFont(tr("从主控模块读取伺服参数设置失败！"));
		return;
	}
	// *** 检查参数设置文件是否存在 ***
	QFile cfgFile(pDirModel->filePath(ui->fileView->currentIndex()));
	if (!cfgFile.exists())
	{
        changeFont(tr("请先选择要导入的参数设置文件！"));
		return;
	}
	// 读取参数设置文件
	QSettings loadFile(cfgFile.fileName(), QSettings::IniFormat);
	// 导入系统参数设置
	sysPar.m_alarm_times = loadFile.value(PARBAK_ALM_TIMES, 10).toUInt();				// 报警器鸣叫次数
	sysPar.m_alarm_interval = loadFile.value(PARBAK_ALM_INTERVAL, 5).toUInt();			// 报警器鸣叫间隔
	sysPar.m_language = loadFile.value(PARBAK_LANGUAGE, LAN_CHINESE_S).toUInt();		// 语言设置
	sysPar.m_rotate_out_at_origin = loadFile.value(PARBAK_ROTATE, 0).toUInt();			// 横行时正臂倒角状态
	sysPar.m_pause_open_door = loadFile.value(PARBAK_DOOR, 1).toUInt();					// 自动运行时开安全门
	sysPar.m_rhor_servo_use = loadFile.value(PARBAK_RHORSRV_USE, 1).toUInt();			// 副臂引拔轴伺服使用
	sysPar.m_rver_servo_use = loadFile.value(PARBAK_RVERSRV_USE, 1).toUInt();			// 副臂上下轴伺服使用
	sysPar.m_runner_use = loadFile.value(PARBAK_RUNNER_USE, 0).toUInt();				// 气动副臂使用
	sysPar.m_runner_down_use = loadFile.value(PARBAK_RUNNER_DOWN_USE, 0).toUInt();		// 气动副臂下位电眼使用
    sysPar.m_runner_advance_use = loadFile.value(PARBAK_RUNNER_ADVANCE_USE, 0).toUInt();		// 气动副臂前进电眼使用
    sysPar.m_runner_return_use = loadFile.value(PARBAK_RUNNER_RETURN_USE, 0).toUInt();		// 气动副臂后退电眼使用
	sysPar.m_adjust_use = loadFile.value(PARBAK_ADJUST_USE, 0).toUInt();				// 调位使用
    sysPar.m_home_inmold = loadFile.value(PARBAK_HOME_INMOLD, 0).toUInt();				// 原点在模内
	sysPar.m_ext_servo_use = loadFile.value(PARBAK_EXTSRV_USE, 0).toUInt();				// 扩展轴伺服使用
    sysPar.m_extend_bit_use = loadFile.value(PARBAK_EXTEND_BIT_USE, 0).toUInt();
	sysPar.m_mold_closed_use = loadFile.value(PARBAK_MCP, 1).toUInt();					// 关模完成信号配置
	sysPar.m_imop_dwn_use = loadFile.value(PARBAK_IMOP, 1).toUInt();					// 开模中间信号配置
	sysPar.m_mid_open_use = loadFile.value(PARBAK_MMOP, 1).toUInt();					// 开中板模确认信号配置
	sysPar.m_rotate_inmold_use = loadFile.value(PARBAK_ROTATE_IN, 0).toUInt();			// 模内倒角使用
	sysPar.m_wait_outmould = loadFile.value(PARBAK_WAIT_OUTMOULD, 0).toUInt();			// 待机选项
	sysPar.m_plan_molding = loadFile.value(PARBAK_PLAN, 0).toUInt();					// 计划生产数量
	sysPar.m_plan_alarm = loadFile.value(PARBAK_REMIND, 0).toUInt();					// 生产数量提醒
	sysPar.m_reject_alarm = loadFile.value(PARBAK_REJECT, 0).toUInt();					// 不良品数量报警
	sysPar.m_polary[0] = loadFile.value(PARBAK_RCM_POLARITY, 0).toUInt();				// 主控模块信号极性
    sysPar.m_polary[1] = loadFile.value(PARBAK_EM1_POLARITY, 0).toUInt();				// 扩展模块1信号极性
    sysPar.m_polary[2] = loadFile.value(PARBAK_EM2_POLARITY, 0).toUInt();				// 扩展模块2信号极性
    sysPar.m_polary[3] = loadFile.value(PARBAK_EM3_POLARITY, 0).toUInt();				// 扩展模块3信号极性
    sysPar.m_polary[4] = loadFile.value(PARBAK_EM4_POLARITY, 0).toUInt();				// 扩展模块4信号极性
    sysPar.m_outputpolary[0] = loadFile.value(PARBAK_MAIN_OUTPOLARITY, 0).toUInt();		// 主控模块信号极性
    sysPar.m_outputpolary[1] = loadFile.value(PARBAK_EM1_OUTPOLARITY, 0).toUInt();		// 扩展模块1信号极性
    sysPar.m_outputpolary[2] = loadFile.value(PARBAK_EM2_OUTPOLARITY, 0).toUInt();		// 扩展模块2信号极性
    sysPar.m_outputpolary[3] = loadFile.value(PARBAK_EM3_OUTPOLARITY, 0).toUInt();		// 扩展模块3信号极性
    sysPar.m_outputpolary[4] = loadFile.value(PARBAK_EM4_OUTPOLARITY, 0).toUInt();		// 扩展模块4信号极性
    sysPar.m_ignore[0] = loadFile.value(PARBAK_RCM_IGNORE, 0).toUInt();					// 主控模块信号报警设置
	sysPar.m_ignore[1] = loadFile.value(PARBAK_EM1_IGNORE, 0).toUInt();					// 扩展模块1信号报警设置
	sysPar.m_ignore[2] = loadFile.value(PARBAK_EM2_IGNORE, 0).toUInt();					// 扩展模块2信号报警设置
	sysPar.m_ignore[3] = loadFile.value(PARBAK_EM3_IGNORE, 0).toUInt();					// 扩展模块3信号报警设置
	sysPar.m_ignore[4] = loadFile.value(PARBAK_EM4_IGNORE, 0).toUInt();					// 扩展模块4信号报警设置
	sysPar.m_noalm[0] = loadFile.value(PARBAK_RCM_NOALM, 0).toUInt();					// 主控模块模内不报警
	sysPar.m_noalm[1] = loadFile.value(PARBAK_EM1_NOALM, 0).toUInt();					// 扩展模块1模内不报警
	sysPar.m_noalm[2] = loadFile.value(PARBAK_EM2_NOALM, 0).toUInt();					// 扩展模块2模内不报警
	sysPar.m_noalm[3] = loadFile.value(PARBAK_EM3_NOALM, 0).toUInt();					// 扩展模块3模内不报警
	sysPar.m_noalm[4] = loadFile.value(PARBAK_EM4_NOALM, 0).toUInt();					// 扩展模块4模内不报警
	sysPar.m_jig_use = loadFile.value(PARBAK_JIG_USE, 0).toUInt();
    sysPar.m_proc2_use = loadFile.value(PARBAK_PROC2_USE, 0).toUInt();                  // 进程2使用
    sysPar.m_proc3_use = loadFile.value(PARBAK_PROC3_USE, 0).toUInt();                  // 进程3使用
    sysPar.m_ip = loadFile.value(PARBAK_IP, qulonglong(3232235777)).toUInt();                       // IP地址
    sysPar.m_submask = loadFile.value(PARBAK_SUBMASK, qulonglong(4294967041)).toUInt();
    sysPar.m_gateway = loadFile.value(PARBAK_GATEWAY, qulonglong(3232235924)).toUInt();
    sysPar.m_oil_interval = loadFile.value(PARBAK_OIL_INTERVAL, 1).toUInt();
    sysPar.m_oil_time = loadFile.value(PARBAK_OIL_TIME, 0).toUInt();
    sysPar.m_oil_use = loadFile.value(PARBAK_OIL_USE, 0).toUInt();
    sysPar.m_rotate_use = loadFile.value(PARBAK_ROTATE_USE, 0).toUInt();
    sysPar.m_run_rotate_use = loadFile.value(PARBAK_RUN_RATOTE_USE, 0).toUInt();
    sysPar.m_door_reset_use = loadFile.value(PARBAK_DOOR_RESET_USE, 0).toUInt();
    sysPar.m_oil_ctrl_use = loadFile.value(PARBAK_OIL_USE_CTRL, 0).toUInt();
    sysPar.m_visionip1 = loadFile.value(PARBAK_VISION1_IP, qulonglong(3232235777)).toUInt();
    sysPar.m_visionip2 = loadFile.value(PARBAK_VISION2_IP, qulonglong(3232235777)).toUInt();
    sysPar.m_visionip3 = loadFile.value(PARBAK_VISION3_IP, qulonglong(3232235777)).toUInt();
    sysPar.m_visionip4 = loadFile.value(PARBAK_VISION4_IP, qulonglong(3232235777)).toUInt();
    sysPar.m_visionip5 = loadFile.value(PARBAK_VISION5_IP, qulonglong(3232235777)).toUInt();
    sysPar.m_visionip6 = loadFile.value(PARBAK_VISION6_IP, qulonglong(3232235777)).toUInt();
    sysPar.m_visionip7 = loadFile.value(PARBAK_VISION7_IP, qulonglong(3232235777)).toUInt();
    sysPar.m_visionip8 = loadFile.value(PARBAK_VISION8_IP, qulonglong(3232235777)).toUInt();
    sysPar.m_vision1port = loadFile.value(PARBAK_VISION1_PORT, 1).toUInt();
    sysPar.m_vision2port = loadFile.value(PARBAK_VISION2_PORT, 1).toUInt();
    sysPar.m_vision3port = loadFile.value(PARBAK_VISION3_PORT, 1).toUInt();
    sysPar.m_vision4port = loadFile.value(PARBAK_VISION4_PORT, 1).toUInt();
    sysPar.m_vision5port = loadFile.value(PARBAK_VISION5_PORT, 1).toUInt();
    sysPar.m_vision6port = loadFile.value(PARBAK_VISION6_PORT, 1).toUInt();
    sysPar.m_vision7port = loadFile.value(PARBAK_VISION7_PORT, 1).toUInt();
    sysPar.m_vision8port = loadFile.value(PARBAK_VISION8_PORT, 1).toUInt();
    sysPar.m_vision1_trigger = loadFile.value(PARBAK_VISION1_TRIGGER, 0).toUInt();
    sysPar.m_vision2_trigger = loadFile.value(PARBAK_VISION2_TRIGGER, 0).toUInt();
    sysPar.m_vision3_trigger = loadFile.value(PARBAK_VISION3_TRIGGER, 0).toUInt();
    sysPar.m_vision4_trigger = loadFile.value(PARBAK_VISION4_TRIGGER, 0).toUInt();
    sysPar.m_vision5_trigger = loadFile.value(PARBAK_VISION5_TRIGGER, 0).toUInt();
    sysPar.m_vision6_trigger = loadFile.value(PARBAK_VISION6_TRIGGER, 0).toUInt();
    sysPar.m_vision7_trigger = loadFile.value(PARBAK_VISION7_TRIGGER, 0).toUInt();
    sysPar.m_vision8_trigger = loadFile.value(PARBAK_VISION8_TRIGGER, 0).toUInt();
    sysPar.m_vision1_outvar = loadFile.value(PARBAK_VISION1_OUTVAR, 2832).toUInt();
    sysPar.m_vision2_outvar = loadFile.value(PARBAK_VISION2_OUTVAR, 2832).toUInt();
    sysPar.m_vision3_outvar = loadFile.value(PARBAK_VISION3_OUTVAR, 2832).toUInt();
    sysPar.m_vision4_outvar = loadFile.value(PARBAK_VISION4_OUTVAR, 2832).toUInt();
    sysPar.m_vision5_outvar = loadFile.value(PARBAK_VISION5_OUTVAR, 2832).toUInt();
    sysPar.m_vision6_outvar = loadFile.value(PARBAK_VISION6_OUTVAR, 2832).toUInt();
    sysPar.m_vision7_outvar = loadFile.value(PARBAK_VISION7_OUTVAR, 2832).toUInt();
    sysPar.m_vision8_outvar = loadFile.value(PARBAK_VISION8_OUTVAR, 2832).toUInt();
    // 导入伺服参数设置
	// 伺服参数-机械最大行程
	srvPar.m_machine_max_len_x = loadFile.value(PARBAK_HOR_MAXLEN, 1000).toUInt();		// 正/副臂原点机械距离
	srvPar.m_min_safe_dis_x_b = loadFile.value(PARBAK_HOR_MINLEN, 300).toUInt();		// 正/副臂最小安全距离
	// 伺服参数-软件最大行程
	srvPar.m_software_max_len_y = loadFile.value(PARBAK_PVER_SOFTLEN, 750).toUInt();	// 正臂上下轴最大软件行程
	srvPar.m_software_max_len_z = loadFile.value(PARBAK_TRAV_SOFTLEN, 2000).toUInt();	// 横行轴最大软件行程
	srvPar.m_software_max_len_a = loadFile.value(PARBAK_RVER_SOFTLEN, 750).toUInt();	// 副臂上下轴最大软件行程
	srvPar.m_software_max_len_c = loadFile.value(PARBAK_EXTE_SOFTLEN, 500).toUInt();	// 扩展轴最大软件行程
	// 伺服参数-安全区
	srvPar.m_max_wait_pos_inmold_y = loadFile.value(PARBAK_PVER_WAIT, 0).toUInt();		// 正臂上下轴上位安全区
	srvPar.m_max_wait_pos_inmold_a = loadFile.value(PARBAK_RVER_WAIT, 0).toUInt();		// 副臂上下轴上位安全区
    srvPar.m_min_safe_pos_outmold_z = loadFile.value(PARBAK_TRAV_OMIN, 0).toUInt();		// 横行轴模外安全区起点
    srvPar.m_max_safe_pos_outmold_z = loadFile.value(PARBAK_TRAV_OMAX, 500).toUInt();	// 横行轴模外安全区终点
    srvPar.m_min_safe_pos_inmold_z = loadFile.value(PARBAK_TRAV_IMIN, 1500).toUInt();	// 横行轴模内安全区起点
    srvPar.m_max_safe_pos_inmold_z = loadFile.value(PARBAK_TRAV_IMAX, 2000).toUInt();	// 横行轴模内安全区终点
    srvPar.m_min_safe_pos_outmold2_z = loadFile.value(PARBAK_TRAV_OMIN2, 0).toUInt();		// 横行轴模外安全区2起点
    srvPar.m_max_safe_pos_outmold2_z = loadFile.value(PARBAK_TRAV_OMAX2, 500).toUInt();	// 横行轴模外安全区2终点
	srvPar.m_min_safe_pos_inmold_x = loadFile.value(PARBAK_PHOR_IMIN, 0).toUInt();		// 正臂引拔轴模内安全区起点
	srvPar.m_max_safe_pos_inmold_x = loadFile.value(PARBAK_PHOR_IMAX, 350).toUInt();	// 正臂引拔轴模内安全区终点
	srvPar.m_min_safe_pos_inmold_b = loadFile.value(PARBAK_RHOR_IMIN, 0).toUInt();		// 副臂引拔轴模内安全区起点
	srvPar.m_max_safe_pos_inmold_b = loadFile.value(PARBAK_RHOR_IMAX, 350).toUInt();	// 副臂引拔轴模内安全区终点

    srvPar.m_min_a_inmold = loadFile.value(PARBAK_MIN_ROT, 0).toUInt();
    srvPar.m_max_a_inmold = loadFile.value(PARBAK_MAX_ROT, 0).toUInt();
    srvPar.m_min_a_trv = loadFile.value(PARBAK_MIN_TRV, 0).toUInt();
    srvPar.m_max_a_trv = loadFile.value(PARBAK_MAX_TRV, 0).toUInt();
    srvPar.m_min_safe_pos_inmold_z_a = loadFile.value(PARBAK_RHOR_ZAMIN, 0).toUInt();
    srvPar.m_max_safe_pos_inmold_z_a = loadFile.value(PARBAK_RHOR_ZAMAX, 350).toUInt();

    srvPar.m_min_b_trave = loadFile.value(PARBAK_RHOR_TRVMIN, 0).toUInt();
    srvPar.m_max_b_trave = loadFile.value(PARBAK_RHOR_TRVMAX, 0).toUInt();
    srvPar.m_min_c_trave = loadFile.value(PARBAK_EXT_TRVMIN, 0).toUInt();
    srvPar.m_max_c_trave = loadFile.value(PARBAK_EXT_TRVMAX, 0).toUInt();
    srvPar.m_min_c_inmold = loadFile.value(PARBAK_EXT_INMOLDMIN, 0).toUInt();
    srvPar.m_max_c_inmold = loadFile.value(PARBAK_EXT_INMOLDMAX, 0).toUInt();
    srvPar.m_min_x_trave = loadFile.value(PARBAK_PHOR_TRVMIN, 0).toUInt();
    srvPar.m_max_x_trave = loadFile.value(PARBAK_PHOR_TRVMAX, 0).toUInt();

    trvRelPos = loadFile.value(PARBAK_TRAV_REL_POS, 0).toUInt();							// 横行轴置物位置
    trvCatPos = loadFile.value(PARBAK_TRAV_CAT_POS, 1800).toUInt();							// 横行轴取物位置
    trvWaitPos = loadFile.value(PARBAK_TRAV_WAIT_POS, 1800).toUInt();
    paVerCatPos = loadFile.value(PARBAK_PVER_CAT_POS, 750).toUInt();						// 正臂上下轴取物位置
    paVerRelPos = loadFile.value(PARBAK_PVER_REL_POS, 750).toUInt();
    paVerWaitPos = loadFile.value(PARBAK_PVER_WAIT_POS, 750).toUInt();
    paHorCatPos = loadFile.value(PARBAK_PHOR_CAT_POS, 750).toUInt();
    paHorRelPos = loadFile.value(PARBAK_PHOR_REL_POS, 750).toUInt();
    paHorWaitPos = loadFile.value(PARBAK_PHOR_REL_POS, 750).toUInt();
    raVerCatPos = loadFile.value(PARBAK_RVER_CAT_POS, 750).toUInt();						// 副臂上下轴取物位置
    raVerRelPos = loadFile.value(PARBAK_RVER_REL_POS, 750).toUInt();
    raVerWaitPos = loadFile.value(PARBAK_RVER_WAIT_POS, 750).toUInt();
    raHorCatPos = loadFile.value(PARBAK_RHOR_CAT_POS, 750).toUInt();
    raHorRelPos = loadFile.value(PARBAK_RHOR_REL_POS, 750).toUInt();
    raHorWaitPos = loadFile.value(PARBAK_RHOR_WAIT_POS, 750).toUInt();
    extCatPos = loadFile.value(PARBAK_EXT_CAT_POS, 750).toUInt();
    extRelPos = loadFile.value(PARBAK_EXT_REL_POS, 750).toUInt();
    extWaitPos = loadFile.value(PARBAK_EXT_WAIT_POS, 750).toUInt();
    // 原点偏移
    srvPar.m_origin_offset_x = loadFile.value(PARBAK_X_OFFSET, 10).toDouble();
    srvPar.m_origin_offset_y = loadFile.value(PARBAK_Y_OFFSET, 10).toDouble();
    srvPar.m_origin_offset_z = loadFile.value(PARBAK_Z_OFFSET, 10).toDouble();
    srvPar.m_origin_offset_a = loadFile.value(PARBAK_A_OFFSET, 10).toDouble();
    srvPar.m_origin_offset_b = loadFile.value(PARBAK_B_OFFSET, 10).toDouble();
    srvPar.m_origin_offset_c = loadFile.value(PARBAK_C_OFFSET, 10).toDouble();
    // 原点待机点
    srvPar.m_home_pos_x = loadFile.value(PARBAK_X_HOME_POS, 0).toDouble();
    srvPar.m_home_pos_y = loadFile.value(PARBAK_Y_HOME_POS, 0).toDouble();
    srvPar.m_home_pos_z = loadFile.value(PARBAK_Z_HOME_POS, 0).toDouble();
    srvPar.m_home_pos_a = loadFile.value(PARBAK_A_HOME_POS, 0).toDouble();
    srvPar.m_home_pos_b = loadFile.value(PARBAK_B_HOME_POS, 0).toDouble();
    srvPar.m_home_pos_c = loadFile.value(PARBAK_C_HOME_POS, 0).toDouble();
    // 模
    srvPar.m_mod_x = loadFile.value(PARBAK_X_MOD, 0).toDouble();
    srvPar.m_mod_y = loadFile.value(PARBAK_Y_MOD, 0).toDouble();
    srvPar.m_mod_z = loadFile.value(PARBAK_Z_MOD, 0).toDouble();
    srvPar.m_mod_a = loadFile.value(PARBAK_A_MOD, 0).toDouble();
    srvPar.m_mod_b = loadFile.value(PARBAK_B_MOD, 0).toDouble();
    srvPar.m_mod_c = loadFile.value(PARBAK_C_MOD, 0).toDouble();
    // 编码器
    srvPar.m_encoder_x = loadFile.value(PARBAK_ENCODER_X, 10).toUInt();
    srvPar.m_encoder_y = loadFile.value(PARBAK_ENCODER_Y, 10).toUInt();
    srvPar.m_encoder_z = loadFile.value(PARBAK_ENCODER_Z, 10).toUInt();
    srvPar.m_encoder_a = loadFile.value(PARBAK_ENCODER_A, 10).toUInt();
    srvPar.m_encoder_b = loadFile.value(PARBAK_ENCODER_B, 10).toUInt();
    srvPar.m_encoder_c = loadFile.value(PARBAK_ENCODER_C, 10).toUInt();
	// 伺服参数-正臂引拔轴速度/加速度
	srvPar.m_xmax_speed = loadFile.value(PARBAK_PHOR_SPD, 10).toUInt();					// 正臂引拔轴速度
	srvPar.m_xmax_acceleration = loadFile.value(PARBAK_PHOR_ACC, 10).toUInt();			// 正臂引拔轴加速度
    srvPar.m_xmax_jerk = loadFile.value(PARBAK_PHOR_JERK, 10).toUInt();
	// 伺服参数-正臂上下轴速度/加速度
	srvPar.m_ymax_speed = loadFile.value(PARBAK_PVER_SPD, 10).toUInt();					// 正臂上下轴速度
	srvPar.m_ymax_acceleration = loadFile.value(PARBAK_PVER_ACC, 10).toUInt();			// 正臂上下轴加速度
    srvPar.m_ymax_jerk = loadFile.value(PARBAK_PVER_JERK, 10).toUInt();
	// 伺服参数-横行轴速度/加速度
	srvPar.m_zmax_speed = loadFile.value(PARBAK_TRAV_SPD, 10).toUInt();					// 横行轴速度
	srvPar.m_zmax_acceleration = loadFile.value(PARBAK_TRAV_ACC, 10).toUInt();			// 横行轴加速度
    srvPar.m_zmax_jerk = loadFile.value(PARBAK_TRAV_JERK, 10).toUInt();
	// 伺服参数-副臂引拔轴速度/加速度
	srvPar.m_bmax_speed = loadFile.value(PARBAK_RHOR_SPD, 10).toUInt();					// 副臂引拔轴速度
	srvPar.m_bmax_acceleration = loadFile.value(PARBAK_RHOR_ACC, 10).toUInt();			// 副臂引拔轴加速度
    srvPar.m_bmax_jerk = loadFile.value(PARBAK_RHOR_JERK, 10).toUInt();
    // 伺服参数-副臂上下轴速度/加m_bmax_speed速度
	srvPar.m_amax_speed = loadFile.value(PARBAK_RVER_SPD, 10).toUInt();					// 副臂上下轴速度
	srvPar.m_amax_acceleration = loadFile.value(PARBAK_RVER_ACC, 10).toUInt();			// 副臂上下轴加速度
    srvPar.m_amax_jerk = loadFile.value(PARBAK_RVER_JERK, 10).toUInt();
	// 伺服参数-扩展轴速度/加速度
	srvPar.m_cmax_speed = loadFile.value(PARBAK_EXTE_SPD, 10).toUInt();					// 扩展轴速度
	srvPar.m_cmax_acceleration = loadFile.value(PARBAK_EXTE_ACC, 10).toUInt();			// 扩展轴加速度
    srvPar.m_cmax_jerk = loadFile.value(PARBAK_EXTE_JERK, 10).toUInt();
    // 马达转动
    srvPar.m_x_units = loadFile.value(PARBAK_PHOR_UNITS, 10.00).toDouble();
    srvPar.m_x_pluses = loadFile.value(PARBAK_PHOR_PLUSES, 10.00).toDouble();
    srvPar.m_y_units = loadFile.value(PARBAK_PVER_UNITS, 10.00).toDouble();
    srvPar.m_y_pluses = loadFile.value(PARBAK_PVER_PLUSES, 10.00).toDouble();
    srvPar.m_z_units = loadFile.value(PARBAK_TRV_UNITS, 10.00).toDouble();
    srvPar.m_z_pluses = loadFile.value(PARBAK_TRV_PLUSES, 10.00).toDouble();
    srvPar.m_b_units = loadFile.value(PARBAK_RHOR_UNITS, 10.00).toDouble();
    srvPar.m_b_pluses = loadFile.value(PARBAK_RHOR_PLUSES, 10.00).toDouble();
    srvPar.m_a_units = loadFile.value(PARBAK_RVER_UNITS, 10.00).toDouble();
    srvPar.m_a_pluses = loadFile.value(PARBAK_RVER_PLUSES, 10.00).toDouble();
    srvPar.m_c_units = loadFile.value(PARBAK_EXT_UNITS, 10.00).toDouble();
    srvPar.m_c_pluses = loadFile.value(PARBAK_EXT_PLUSES, 10.00).toDouble();
    // 轴类型
    srvPar.m_angle_type = loadFile.value(PARBAK_ANGLE_BMP, 0).toUInt();
    srvPar.m_dec_type = loadFile.value(PARBAK_RAMP_BMP, 0).toUInt();
    // 原点归位模式
    srvPar.m_home_mode = loadFile.value(PARBAK_HOME_MODE, 0).toUInt();
    srvPar.m_home_vel = loadFile.value(PARBAK_HOME_VEL, 0).toUInt();
    srvPar.m_home_vel_slow = loadFile.value(PARBAK_HOME_VEL_SLOW, 0).toUInt();
    // *** 保存参数设置到主控模块 ***
	// 保存系统参数
	try
	{
		if (pModbus->WriteSystem(sysPar, 0))
			throw false;
		if (pModbus->CommandWrite(CMD_WRITE_SYSTEM))
			throw false;
	}
	catch (bool &)
	{
        changeFont(tr("保存系统参数失败！"));
		return;
	}
	// 保存伺服参数
	try
	{
		if (pModbus->WriteServo(srvPar, 0xFFFFFFFFFFFFFFFF))
			throw false;
		if (pModbus->CommandWrite(CMD_WRITE_SERVO))
			throw false;
		QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
		settings.setValue(XPAD_SET_TRVRELPOS, trvRelPos);
		settings.setValue(XPAD_SET_TRVCATPOS, trvCatPos);
		settings.setValue(XPAD_SET_TRVWAIT, trvWaitPos);
		settings.setValue(XPAD_SET_PAVERCAT, paVerCatPos);
		settings.setValue(XPAD_SET_PAVERREL, paVerRelPos);
		settings.setValue(XPAD_SET_PAVERWAIT, paVerWaitPos);
		settings.setValue(XPAD_SET_PAHORCAT, paHorCatPos);
		settings.setValue(XPAD_SET_PAHORREL, paHorRelPos);
		settings.setValue(XPAD_SET_PAHORWAIT, paHorWaitPos);
		settings.setValue(XPAD_SET_RAVERCAT, raVerCatPos);
		settings.setValue(XPAD_SET_RAVERREL, raVerRelPos);
		settings.setValue(XPAD_SET_RAVERWAIT, raVerWaitPos);
		settings.setValue(XPAD_SET_RAHORCAT, raHorCatPos);
		settings.setValue(XPAD_SET_RAHORREL, raHorRelPos);
		settings.setValue(XPAD_SET_RAHORWAIT, raHorWaitPos);
		settings.setValue(XPAD_SET_EXTCAT, extCatPos);
		settings.setValue(XPAD_SET_EXTREL, extRelPos);
		settings.setValue(XPAD_SET_EXTWAIT, extWaitPos);
		settings.sync();
	}
	catch (bool &)
	{
        changeFont(tr("保存伺服参数失败！"));
		return;
	}
	// 写入系统日志
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_PAR_IMPORT);
	xSysLog::SaveChange();
#if defined(Q_OS_LINUX)
	sync();
#endif
    changeFont(tr("机械手参数设置已经成功导入！"));
}

// 导出系统日志
void FormManufacturer::logExport(void)
{
	// 检测USB存储器是否插入
	if (!xUsb::CheckInsert())
	{
        changeFont(tr("没有检测到USB存储器，无法导出系统日志文件！"));
		return;
	}
	// 输入另存为新文件名
#if defined(Q_WS_WIN)
    QString path = QDir::currentPath().append(XPAD_USB_PATH);
#else
    QString path(XPAD_USB_PATH);
#endif
	QString name;
	if (xKbd->DoForm(name, KEYBOARD_TYPE_FILENAME) != QDialog::Accepted)
		return;
	name = path + name + QString(LOG_FILE_EXT);
	QFile newFile(name);
	if (newFile.exists())
	{
		// 如果文件已经存在则警告并退出
        changeFont(tr("文件已经存在，无法进行系统日志导出操作！"));
		return;
	}
	if (!QFile::copy(QDir::currentPath() + QString("/"SYSLOG_PATH"/"XPAD_SYSLOG_FILE), name))
	{
        changeFont(tr("系统日志文件复制出错！"));
	}
	else
	{
#if defined(Q_OS_LINUX)
		sync();
#endif
        changeFont(tr("系统日志文件已经成功导出！"));
	}
}
// 清除系统日志
void FormManufacturer::logClear(void)
{
	if (xMessageBox::DoQuestion(tr("系统提示"), tr("本操作将会清除系统日志记录信息并且无法恢复！\n确定要清除系统日志吗？")) != XMSG_RET_YES)
		return;
	xSysLog::DestroySysLog();
	QFile logFile(QDir::currentPath() + QString("/"SYSLOG_PATH"/"XPAD_SYSLOG_FILE));
	if (logFile.exists())
		logFile.remove();
    //if (!xSysLog::CreateSysLog())
    if (!xSysLog::OpenSysLog())
	{
        changeFont(tr("重新初始化系统日志文件失败！"));
		return;
	}
#if defined(Q_OS_LINUX)
	sync();
#endif
    changeFont(tr("系统日志已经成功清除！"));
	emit LogModelUpdate();
}

extern void WaitMethod(int ms);

void FormManufacturer::enterIsp(void)
{
	pModbus->StopPeriodTimer();
	WaitMethod(200);
	pModbus->CommandEnterIsp();
	WaitMethod(100);
	pModbus->CloseSerialPort();
	WaitMethod(100);
    if(pModbus->GetSysTypeHigh() != 0)
        pIspDialog->DoIsp(true);
    else
	pIspDialog->DoIsp();
}
void FormManufacturer::on_fileView_clicked(const QModelIndex &index)
{
    if(pDirModel)
    {
            QModelIndex qn=pDirModel->index(index.row(),0,index.parent());
            QString name=qn.data().toString();
			QFont font_("Microsoft YaHei");
			font_.setPixelSize(28);
            ui->labelMsg->setFont(font_);
            ui->labelMsg->setText(name);
    }

}
void FormManufacturer::changeFont(QString msg){
	QFont font("Microsoft YaHei");
	font.setPixelSize(28);
    ui->labelMsg->setFont(font);
    ui->labelMsg->setText(msg);
}
void FormManufacturer::portEdit()
{
    m_PortEdit->DoForm();
}
void FormManufacturer::axisEdit()
{
    m_AxisEdit->DoForm();
}

void FormManufacturer::on_BtnOutIOName_clicked()
{
    // *** 检测USB存储器是否插入 ***
    if (!xUsb::CheckInsert())
    {
        changeFont(tr("没有检测到USB存储器，无法导出端口数据！"));
        return;
    }
    // *** 输入另存为新文件名 ***
    // 输入另存为新文件名
#if defined(Q_WS_WIN)
    QString path = QDir::currentPath().append(XPAD_USB_PATH);
#else
    QString path(XPAD_USB_PATH);
#endif
    QString name;
    if (xKbd->DoForm(name, KEYBOARD_TYPE_FILENAME) != QDialog::Accepted)
        return;
    name = path + name + QString(IO_NAME_EXT);
    QFile newFile(name);
    if (newFile.exists())
    {
        // 如果文件已经存在则警告并退出
        changeFont(tr("文件已经存在，无法进行端口数据导出操作！"));
        return;
    }
    qDebug()<<"on_BtnOutName_clicked:"<<name;

    if (!QFile::copy(QDir::currentPath() + QString("/"XPAD_IO_NAME), name))
    {
        changeFont(tr("端口数据文件复制出错！"));
    }
    else
    {
#if defined(Q_OS_LINUX)
        sync();
#endif
        changeFont(tr("端口数据文件已经成功导出！"));
    }
}

