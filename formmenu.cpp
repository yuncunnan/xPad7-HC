#include <QSettings>
#include "cmbprotocol.h"
#include "xpermissions.h"
#include "xstringresource.h"
#include "xmessagebox.h"
#include "formmenu.h"
#include "ui_formmenu.h"

Formmenu::Formmenu(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::Formmenu)
{
	ui->setupUi(this);
	pModbus = modbus;
	connect(this, SIGNAL(EnterServoSetup()), parent, SLOT(MenuServoClick()));
	connect(this, SIGNAL(EnterSystemSetup()), parent, SLOT(MenuSystemClick()));
	connect(this, SIGNAL(EnterUiSetup()), parent, SLOT(MenuUiClick()));
	connect(this, SIGNAL(EnterAdjust()), parent, SLOT(MenuAdjClick()));
	connect(this, SIGNAL(EnterInformation()), parent, SLOT(MenuInfClick()));
	connect(this, SIGNAL(EnterManufacturer()), parent, SLOT(MenuManufactClick()));
	connect(this, SIGNAL(EnterSystemLog()), parent, SLOT(MenuLogClick()));
    connect(this, SIGNAL(EnterOption()), parent, SLOT(MenuOptionClick()));
    connect(this, SIGNAL(EnterVarInit()), parent, SLOT(MenuVarInitClick()));
    connect(this, SIGNAL(EnterIOSetup()), parent, SLOT(MenuIOSetupClick()));
    setStyleSheet("color:black;");
    ui->toolButtonOption->setVisible(false);
}

Formmenu::~Formmenu()
{
	delete ui;
}

void Formmenu::changeEvent(QEvent *e)
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

bool Formmenu::EnterForm(void)
{
	// 显示界面
//	show();
	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::black);
	ui->toolButtonAdj->setPalette(pa);
	ui->toolButtonServo->setPalette(pa);
	ui->toolButtonSystem->setPalette(pa);
	ui->toolButtonManufactory->setPalette(pa);
	ui->toolButtonOption->setPalette(pa);
    ui->toolButtonVarInit->setPalette(pa);
	ui->toolButtonUiSetup->setPalette(pa);
	ui->toolButtonInformation->setPalette(pa);
    ui->toolButtonSyslog->setPalette(pa);
    ui->toolButtonIO->setPalette(pa);
    return true;
}

bool Formmenu::ExitForm(void)
{
	// 隐藏界面
//	hide();
	return true;
}

// 系统设置按钮点击槽
void Formmenu::BtnSystemClick(void)
{
	// 进入系统参数设置
	emit EnterSystemSetup();
}
// 伺服设置按钮点击槽
void Formmenu::BtnServoClick(void)
{
	// 进入伺服参数设置
	emit EnterServoSetup();
}
// 用户界面按钮点击槽
void Formmenu::BtnUiSetup(void)
{
	// 进入用户界面设置
	emit EnterUiSetup();
}
// 调位操作按钮点击槽
void Formmenu::BtnAdjustClick(void)
{
	emit EnterAdjust();
}
// 系统信息
void Formmenu::BtnInformation(void)
{
	// 进入系统信息
	emit EnterInformation();
}
// 厂商操作
void Formmenu::BtnManufacturer(void)
{
	// 进入厂商操作
	emit EnterManufacturer();
}
// 系统日志
void Formmenu::BtnSystemLog(void)
{
	// 进入系统日志
	emit EnterSystemLog();
}

// 进入端口设置
void Formmenu::BtnIOSetup(void)
{
    emit EnterIOSetup();
}
// 系统日志
void Formmenu::BtnOption(void)
{
	// 进入厂商操作
	emit EnterOption();
}
// 变量初始化
void Formmenu::BtnVarInit(void)
{
    // 进入厂商操作
    emit EnterVarInit();
}
