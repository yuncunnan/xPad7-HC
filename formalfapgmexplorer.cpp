﻿#include <stdlib.h>
#include <QTextStream>
#include <QSettings>
#include "xconfig.h"
#include "xusb.h"
#include "xpermissions.h"
#include "xstringresource.h"
#include "alfamodel.h"
#include "xsystemlog.h"
#include "xmessagebox.h"
#include "dialogkeyboard.h"
#include "formalfapgmexplorer.h"
#include "ui_formalfapgmexplorer.h"

#define	PGM_DIR	0
#define	USB_DIR	1

FormAlfaPgmExplorer::FormAlfaPgmExplorer(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormAlfaPgmExplorer)
{
	ui->setupUi(this);
	pModbus = modbus;
	// 构造文件系统数据源
	pDirModel = new xFileSystemModel(this);
	uDirModel = new xFileSystemModel(this);
	// 不管程序文件夹是否存在都创建一次程序文件夹
	// 如果程序文件夹已经存在则不会创建返回 false
	// 如果程序文件夹不存在则创建
	QDir pgmDir(QDir::currentPath());
    pgmDir.mkdir(ALFA_PATH);
#if defined(Q_WS_WIN)
    QDir usbDir(QDir::currentPath());
    usbDir.mkdir("usb");
#endif
	// 设置文件过滤器
    pDirModel->setNameFilters(QStringList() << "*"ALFA_FILE_EXT);
	pDirModel->setNameFilterDisables(false);
	pDirModel->setFilter(QDir::Files);
	pDirModel->setReadOnly(true);

    uDirModel->setNameFilters(QStringList() << "*"ALFA_FILE_EXT);
	uDirModel->setNameFilterDisables(false);
	uDirModel->setFilter(QDir::Files);
	uDirModel->setReadOnly(true);
	// 设置数据源
	ui->pgmView->setModel(pDirModel);
	ui->usbView->setModel(uDirModel);
    ui->pgmView->setRootIndex(pDirModel->setRootPath(ALFA_PATH));
	ui->usbView->setRootIndex(uDirModel->setRootPath("/root/"));
	//ui->usbView->setRootIndex(uDirModel->setRootPath(XPAD_USB_PATH));
	// 设置表头字体    
#if SIMULATOR
    ui->pgmView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 8));
    ui->pgmView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 12pt;}");
    ui->usbView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 8));
    ui->usbView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 12pt;}");
    ui->pgmView->verticalHeader()->setFont(QFont("Microsoft YaHei", 8));
    ui->pgmView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 12pt;}");
    ui->usbView->verticalHeader()->setFont(QFont("Microsoft YaHei", 8));
    ui->usbView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 12pt;}");
#else
	ui->pgmView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->pgmView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
	ui->usbView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->usbView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
	ui->pgmView->verticalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->pgmView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
	ui->usbView->verticalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->usbView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
#endif
    // 设置表头尺寸模式
	ui->usbView->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui->usbView->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
	ui->usbView->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);
	ui->usbView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	ui->pgmView->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui->pgmView->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
	ui->pgmView->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);
	ui->pgmView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	// 隐藏文件类型列
    ui->pgmView->setColumnHidden(1, true);
    ui->usbView->setColumnHidden(1, true);
    ui->pgmView->setColumnHidden(2, true);
    ui->usbView->setColumnHidden(2, true);
    // 设置列宽度
    ui->pgmView->setColumnWidth(3, 260);
    ui->usbView->setColumnWidth(3, 260);

#if IS_XEDITOR
    ui->tabWidget->setTabEnabled(USB_DIR, false);
#endif
}

FormAlfaPgmExplorer::~FormAlfaPgmExplorer()
{
	delete pDirModel;
	delete uDirModel;
	delete ui;
}

void FormAlfaPgmExplorer::changeEvent(QEvent *e)
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

bool FormAlfaPgmExplorer::EnterForm(void)
{
    if (!pModbus->IsALFAMode())
    {
        xMessageBox::DoWarning(tr("系统警告"), tr("系统为教导模式，不能进入！"));
        return false;
    }
    setFormState();
	refreshUsb();
	// 连接信号槽
	connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 显示界面
//	show();
	return true;
}

bool FormAlfaPgmExplorer::ExitForm(void)
{
	// 取消信号槽连接
	ui->usbView->setRootIndex(uDirModel->setRootPath("/root/"));
	disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 隐藏界面
//	hide();
	return true;
}

void FormAlfaPgmExplorer::setFormState()
{
	if (xPermissions::GetPermissions(PER_CHG_PGM) == true)
		ui->BtnPgmLoad->setEnabled(true);
	// 没有加载程序文件权限
	else
		ui->BtnPgmLoad->setEnabled(false);
	if (xPermissions::GetPermissions(PER_OPR_PGM) == true)
	{
			ui->BtnPgmNew->setEnabled(true);
			ui->BtnPgmRename->setEnabled(true);
			ui->BtnPgmCopyAs->setEnabled(true);
			ui->BtnPgmExport->setEnabled(true);
			ui->BtnPgmDelete->setEnabled(true);
			ui->BtnUsbExport_pgm->setEnabled(true);
			ui->BtnRefresh->setEnabled(true);
			ui->BtnPopup->setEnabled(true);
	}
	else
	{
		// 没有操作程序文件权限
		ui->BtnPgmNew->setEnabled(false);
		ui->BtnPgmRename->setEnabled(false);
		ui->BtnPgmCopyAs->setEnabled(false);
		ui->BtnPgmExport->setEnabled(false);
		ui->BtnPgmDelete->setEnabled(false);
		ui->BtnUsbExport_pgm->setEnabled(false);
		ui->BtnRefresh->setEnabled(false);
		ui->BtnPopup->setEnabled(false);
	}

}
// 当前登录用户更改槽
void FormAlfaPgmExplorer::userChange(void)
{
	// 检查用户权限
	if ((xPermissions::GetPermissions(PER_CHG_PGM) == false) || (xPermissions::GetPermissions(PER_OPR_PGM) == false))
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
	setFormState();
}
// **********************************
// 载入文件槽
// **********************************
void FormAlfaPgmExplorer::loadPgmFile(void)
{
	QString pathName = getFilePath();
	if (pathName.isEmpty())
	{
		// 如果没有选择源文件则警报并退出
		xMessageBox::DoWarning(tr("系统警告"),  tr("没有选择要载入的程序文件！"));
		return;
	}
	// 写入系统日志
	QFileInfo fileInfo(pathName);
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_PGMLOAD, fileInfo.fileName());
	xSysLog::SaveChange();
    pModbus->SetAlfaPgmName(pathName);
}
// **********************************
// 新建文件槽
// **********************************
void FormAlfaPgmExplorer::newPgmFile(void)
{
	QString name, newPathName;
	// 输入文件名
	if (xKbd->DoForm(name, KEYBOARD_TYPE_FILENAME) != QDialog::Accepted)
		return;
	// 检查新文件名是否已经输入
	if (name == "")
	{
		// 如果没有输入文件名则警告并退出
		xMessageBox::DoWarning(tr("系统警告"), tr("没有输入新文件名，无法创建新程序文件！"));
		return;
	}
	// 检查新文件名是否已经存在
	newPathName = QDir::currentPath();
    newPathName.append("/"ALFA_PATH"/");
	newPathName = newPathName + name;
    newPathName.append(ALFA_FILE_EXT);
	QFile newFile(newPathName);
	if (newFile.exists())
	{
		// 如果文件已经存在则警告并退出
		xMessageBox::DoWarning(tr("系统警告"), tr("新文件名已经存在，系统不允许同名文件，无法创建新程序文件！"));
		return;
	}
	// 写入系统日志
	QFileInfo fileInfo(newPathName);
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_PGMNEW, fileInfo.fileName());
	xSysLog::SaveChange();
	// 创建新程序文件
    AlfaModel alfa;
    alfa.NewProgram(newPathName);
    alfa.SaveProgram();
    pModbus->SetAlfaPgmName(newPathName);
}
// **********************************
// 重命名槽
// USB存储器上的程序文件不允许改名
// **********************************
void FormAlfaPgmExplorer::renamePgmFile(void)
{
	QString oldPathName, newPathName, name;
	oldPathName = getFilePath();
	if (oldPathName.isEmpty())
	{
		// 如果没有选择源文件则警报并退出
		xMessageBox::DoWarning(tr("系统警告"),  tr("没有选择要改名的文件，无法进行重命名操作！"));
		return;
	}
	QFileInfo finfo(oldPathName);
	name = finfo.baseName();
	// 输入文件名
	if (xKbd->DoForm(name, KEYBOARD_TYPE_FILENAME) != QDialog::Accepted)
		return;
	if (name == "")
	{
		// 如果没有输入文件名则警告并退出
		xMessageBox::DoWarning(tr("系统警告"), tr("没有输入新文件名，无法进行重命名操作！"));
		return;
	}
	// 检查新文件名是否已经存在
	newPathName = QDir::currentPath();
    newPathName.append("/"ALFA_PATH"/");
	newPathName = newPathName + name;
    newPathName.append(ALFA_FILE_EXT);
	QFile newFile(newPathName);
	if (newFile.exists())
	{
		// 如果文件已经存在则警告并退出
		xMessageBox::DoWarning(tr("系统警告"), tr("新文件名已经存在，系统不允许同名文件，无法进行重命名操作！"));
		return;
	}
	// 重命名所选择的文件
	if (QFile::rename(oldPathName, newPathName) == false)
		return;
	// 如果重命名的是当前程序文件则更新当前程序文件
    if (oldPathName == pModbus->GetAlfaPgmName())
        pModbus->SetAlfaPgmName(newPathName);
	// 写入系统日志
	QFileInfo oldInfo(oldPathName);
	QFileInfo newInfo(newPathName);
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_PGMRENAME, oldInfo.fileName() + QString(" -> ") + newInfo.fileName());
	xSysLog::SaveChange();
#if defined(Q_OS_LINUX)
	sync();
#endif
}
// **********************************
// 另存为槽
// **********************************
void FormAlfaPgmExplorer::saveAsPgmFile(void)
{
	QString oldPathName, name, newPathName;
	oldPathName = getFilePath();
	if (oldPathName.isEmpty())
	{
		// 如果没有选择源文件则警报并退出
		xMessageBox::DoWarning(tr("系统警告"),  tr("没有选择要复制的文件，无法进行另存为操作！"));
		return;
	}
	QFileInfo finfo(oldPathName);
	name = finfo.baseName();
	// 输入文件名
	if (xKbd->DoForm(name, KEYBOARD_TYPE_FILENAME) != QDialog::Accepted)
		return;
	if (name == "")
	{
		// 如果没有输入文件名则警告并退出
		xMessageBox::DoWarning(tr("系统警告"), tr("没有输入要保存的新文件名，无法进行另存为操作！"));
		return;
	}
	// 检查新文件名是否已经存在
	newPathName = QDir::currentPath();
    newPathName.append("/"ALFA_PATH"/");
	newPathName = newPathName + name;
    newPathName.append(ALFA_FILE_EXT);
	QFile newFile(newPathName);
	if (newFile.exists())
	{
		// 如果文件已经存在则警告并退出
		xMessageBox::DoWarning(tr("系统警告"), tr("新文件名已经存在，系统不允许同名文件，无法进行另存为操作！"));
		return;
	}
	// 复制所选择的文件
	QFile::copy(oldPathName, newPathName);
	// 写入系统日志
	QFileInfo oldInfo(oldPathName);
	QFileInfo newInfo(newPathName);
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_PGMCOPY, oldInfo.fileName() + QString(" -> ") + newInfo.fileName());
	xSysLog::SaveChange();
#if defined(Q_OS_LINUX)
	sync();
#endif
}
// **********************************
// 删除文件槽
// **********************************
void FormAlfaPgmExplorer::deleteFile(void)
{
	QString pathName;
	if (ui->tabWidget->currentIndex() == PGM_DIR)
		pathName = getFilePath();
	else
		return;
	// 如果没有选择源文件则警报并退出
	if (pathName.isEmpty())
	{
		xMessageBox::DoWarning(tr("系统警告"),  tr("没有选择要删除的文件，无法进行删除操作！"));
		return;
	}
	// 当前程序不允许删除
    if (pathName == pModbus->GetAlfaPgmName())
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("不能删除系统载入的当前程序，无法进行删除操作！"));
		return;
	}
	if (xMessageBox::DoQuestion(tr("系统提示"), tr("删除文件后将无法恢复，是否真的要删除所选择的文件？")) != XMSG_RET_YES)
		return;
	// 删除所选择的文件
	QFile::remove(pathName);
	// 写入系统日志
	QFileInfo fileInfo(pathName);
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_PGMDEL, fileInfo.fileName());
	xSysLog::SaveChange();
#if defined(Q_OS_LINUX)
	sync();
#endif
}

// **********************************
// 导出文件到USB存储器
// **********************************
void FormAlfaPgmExplorer::exportToUsb(void)
{
#if defined(Q_WS_WIN)
    QString newPathName = QDir::currentPath().append(XPAD_USB_PATH);
#else
    QString newPathName(XPAD_USB_PATH);
#endif

    QString sourcePathName;
	if (ui->tabWidget->currentIndex() ==PGM_DIR)
		sourcePathName = getFilePath();
	else
		return;
	// 检查是否选择要导出的源文件
	if (sourcePathName.isEmpty())
	{
		xMessageBox::DoWarning(tr("系统警告"),  tr("没有选择要导出的文件！\n请选择要导出的文件，再进行导出文件操作。"));
		return;
	}
	// 检查USB存储器是否挂载
	if (!xUsb::CheckInsert())
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("没有插入USB存储器，不能执行导出程序文件操作！"));
		return;
	}
	QFileInfo finfo(sourcePathName);
	QString name = finfo.baseName();
	// 输入文件名
	if (xKbd->DoForm(name, KEYBOARD_TYPE_FILENAME) != QDialog::Accepted)
		return;
	// 检查新文件名是否已经输入
	if (name == "")
	{
		// 如果没有输入文件名则警告并退出
		xMessageBox::DoWarning(tr("系统警告"), tr("没有输入导出到USB存储器的新文件名，无法执行导出程序文件操作！"));
		return;
	}
	// 检查新文件名是否已经存在
	newPathName = newPathName + name;
    newPathName.append(ALFA_FILE_EXT);
	QFile newFile(newPathName);
	if (newFile.exists())
	{
		// 如果文件已经存在则警告并退出
		xMessageBox::DoWarning(tr("系统警告"), tr("USB存储器上已经存在同名程序文件，系统不允许同名文件，请修改新文件名后再执行导出程序文件操作！"));
		return;
	}
	// 复制所选择的文件
	if (QFile::copy(sourcePathName, newPathName))
	{
#		if defined(Q_OS_LINUX)
		sync();
#		endif
		xMessageBox::DoInformation(tr("系统提示"), tr("所选的系统存储器程序文件已经成功导出到USB存储器中！"));
	}
}
// **********************************
// 导入文件到系统存储器
// **********************************
void FormAlfaPgmExplorer::importUSBFileToPgm(void)
{
	QString sourcePathName, newPathName, name;
	sourcePathName = getFilePath();
	// 检查是否选择要导入的源文件
	if (sourcePathName.isEmpty())
	{
		xMessageBox::DoWarning(tr("系统警告"),  tr("没有选择要导入的USB存储器文件！\n请选择要导入的文件，再进行导入文件操作。"));
		return;
	}
	// 检查USB存储器是否挂载
	if (!xUsb::CheckInsert())
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("没有插入USB存储器，不能执行导入操作！"));
		return;
	}
	QFileInfo finfo(sourcePathName);
	name = finfo.baseName();
	// 输入文件名
	if (xKbd->DoForm(name, KEYBOARD_TYPE_FILENAME) != QDialog::Accepted)
		return;
	// 检查新文件名是否已经输入
	if (name == "")
	{
		// 如果没有输入文件名则警告并退出
		xMessageBox::DoWarning(tr("系统警告"), tr("没有输入导入到系统存储器的新文件名，无法执行导入程序文件操作！"));
		return;
	}
	// 检查新文件名是否已经存在
	newPathName = QDir::currentPath();
    newPathName.append("/"ALFA_PATH"/");
	newPathName = newPathName + name;
    newPathName.append(ALFA_FILE_EXT);
	QFile newFile(newPathName);
	if (newFile.exists())
	{
		// 如果文件已经存在则警告并退出
		xMessageBox::DoWarning(tr("系统警告"), tr("已经存在同名程序文件，系统不允许同名文件，请修改新文件名后再执行导入程序文件操作！"));
		return;
	}
	// 复制所选择的文件
	if (QFile::copy(sourcePathName, newPathName))
	{
#		if defined(Q_OS_LINUX)
		sync();
#		endif
		xMessageBox::DoInformation(tr("系统提示"), tr("所选的文件已经成功导入！"));
	}
}

// 弹出USB存储器
void FormAlfaPgmExplorer::popupUsb(void)
{
#if defined(Q_WS_QWS)
	if (xUsb::CheckInsert() == false)
		return;
	if (system("umount "XPAD_USB_PATH) == 0)
	{
		xMessageBox::DoInformation(tr("系统提示"), tr("USB存储器现在可以安全移除。"));
	}
#endif
}
QString FormAlfaPgmExplorer::getFilePath()
{
	if (ui->tabWidget->currentIndex() == PGM_DIR)
		return pDirModel->filePath(ui->pgmView->currentIndex());
	else
		return uDirModel->filePath(ui->usbView->currentIndex());
}
// 刷新U盘
void FormAlfaPgmExplorer::refreshUsb(void)
{
#if defined(Q_WS_QWS)
	ui->usbView->setRootIndex(uDirModel->setRootPath("/root/"));
	if (xUsb::CheckInsert())
		ui->usbView->setRootIndex(uDirModel->setRootPath(XPAD_USB_PATH));
#else
    ui->usbView->setRootIndex(uDirModel->setRootPath(QDir::currentPath().append(XPAD_USB_PATH)));
#endif
}
