#include <QApplication>
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QSettings>
#include <QWSServer>
#include "cmbprotocol.h"
#include "xKeyPad.h"
#include "xioport.h"
#include "safeswitch.h"
#include "buzzer.h"
#include "motor.h"
#include "xconfig.h"
#include "indicatorled.h"
#include "ui_dialogframe.h"
#include "dialogframe.h"
#include "formwallpaper.h"
#include "formauto.h"
#include "formmanual.h"
#include "formmenu.h"
#include "formservo.h"
#include "formsystem.h"
#include "formuisetup.h"
#include "formadjust.h"
#include "formmanufacturer.h"
#include "forminformation.h"
#include "formalarm.h"
#include "formpgmexplorer.h"
#include "formalfapgmexplorer.h"
#include "formteach.h"
#include "formsyslog.h"
#include "formoption.h"
#include "formalfaoption.h"
#include "formeditoption.h"
#include "formvarinit.h"
#include "formio.h"
#include "dialogservocontrol.h"
#include "dialogusermanager.h"
#include "dialogdatetime.h"
#include "dialogspeed.h"
#include "xstringresource.h"
#include "xmessagebox.h"
#include "teachtablemodel.h"
#include "xtopinfo.h"
#include "xdelaymessagebox.h"
#include "servoalias.h"
#include "xsystemlog.h"
#include "screensaver.h"
#include "alfamodel.h"
#include <QDebug>
#include "HalBoard.h"


#define SVADJ_STOP		0
#define SVADJ_CW		1
#define SVADJ_CCW		2

quint16 globlecodes[4096];
quint32 globleparas[4096];
bool DialogFrame::runled_state;
extern HardwareInterface *board;

DialogFrame::DialogFrame(CMBProtocol *modbus, xPermissions *usrPerm, QWidget *parent) : QDialog(parent), ui(new Ui::DialogFrame)
{
	// 设置对话框显示效果
	ui->setupUi(this);
#if defined(Q_WS_QWS)
	setWindowFlags(Qt::FramelessWindowHint);
#endif
	if (pModbus->GetTypeMatch())
		ui->labelWarning->setVisible(false);
	else
	{
		ui->labelWarning->setText(xStringResource::GetString(STRRES_MATE_ERROR) +
								  tr("操作器类型："XPAD_TYPE_STR"\n") +
								  tr("主控模块类型：") + xStringResource::GetType(pModbus->GetSverExtra()));
		ui->labelWarning->setVisible(true);
	}
	// 初始化 Modbus 协议
	ComState = true;
	pModbus = modbus;
	// 初始化界面字符串资源
	retranslateUI();
	// 初始化用户权限管理
	pUsrPerm = usrPerm;
	// 构造各个对话框
	ServoCtrl = new DialogServoControl(pModbus);
	dlgUserManager = new DialogUserManager(pModbus, pUsrPerm);
	dlgDateTime = new DialogDateTime();
	// 构造壁纸画面
    Wallpaper = new FormWallpaper(pModbus, this); Wallpaper->move(QPoint(0, 80));
	// 构造自动操作画面
    ScreenAuto = new FormAuto(pModbus, this); ScreenAuto->move(QPoint(0, 80));
	// 构造手动操作画面
    ScreenManual = new FormManual(pModbus, this); ScreenManual->move(QPoint(0, 80));
	// 构造功能菜单画面
    ScreenMenu = new Formmenu(pModbus, this); ScreenMenu->move(QPoint(0, 80));
	// 构造伺服参数画面
    ScreenServo = new Formservo(pModbus, this); ScreenServo->move(QPoint(0, 80));
	// 构造系统参数画面
    ScreenSystem = new Formsystem(pModbus, this); ScreenSystem->move(QPoint(0, 80));
	// 构造界面设置画面
    ScreenUiSetup = new Formuisetup(pModbus, this); ScreenUiSetup->move(QPoint(0, 80));
	// 构造调位操作画面
    ScreenAdjust = new FormAdjust(pModbus, this); ScreenAdjust->move(QPoint(0, 80));
	// 构造报警信息画面
    ScreenAlarm = new FormAlarm(pModbus, this); ScreenAlarm->move(QPoint(0, 80));
	// 构造厂商操作画面
    ScreenManufacturer = new FormManufacturer(pModbus, this); ScreenManufacturer->move(QPoint(0, 80));
	// 构造系统信息画面
    ScreenInformation = new Forminformation(pModbus, this); ScreenInformation->move(QPoint(0, 80));
	// 构造程序文件浏览画面
    ProgramFile = new FormPgmExplorer(pModbus, this); ProgramFile->move(QPoint(0, 80));
	AlfaProgramFile = new FormAlfaPgmExplorer(pModbus, this); AlfaProgramFile->move(QPoint(0, 80));
	// 构造教导程序画面
    TeachProgram = new FormTeach(pModbus, this); TeachProgram->move(QPoint(0, 80));
	Alfaoption = new Formalfaoption(pModbus, this); Alfaoption->move(QPoint(0, 80));
	// 构造系统日志画面
    SystemLog = new FormSysLog(pModbus, this); SystemLog->move(QPoint(0, 80));
	// 构造变量初始化画面
    VarInit = new FormVarInit(pModbus, this); VarInit->move(QPoint(0, 80));
	// 端口设置画面
    IOSetup = new FormIO(pModbus, this); IOSetup->move(QPoint(0, 80));
	// 构造命令配置画面
    Option = new FormOption(pModbus, this); Option->move(QPoint(0, 80));
	EditOption = new FormEditOption(pModbus, this); EditOption->move(QPoint(0, 80));
	// 构造时钟定时器
	pClockTimer = new QTimer(this);
	runled_state = false;
#if defined(Q_WS_QWS)

	pKeyTimer = new QTimer(this);
#endif
	// 启动默认进入待机主画面
	ReturnMain();
	// 初始化系统时间显示
	ui->pushButtonDateTime->setText(QDate::currentDate().toString("yyyy-MM-dd") + "\n" + QTime::currentTime().toString());
	isHoming = 0;
	calFlag = false;
	// 初始化系统是否经过原点复归状态显示
    SvReferState(pModbus->GetHomeState());
    // 初始化系统当前状态显示(手动/自动待机/自动运行/单步/单循环)
    setSysState(pModbus->GetSysState(), pModbus->GetRunState(), pModbus->GetRunType());
    setSafeSwitchFlag(xSafeSw->GetSafeSwState() == SAFE_SWITCH_ON);
	// 初始化当前程序名称显示
	curPgmChange(pModbus->GetCurPgmName());
	// 读取系统当前程序设置
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	srvRelSpd = settings.value(XPAD_SET_SRVSPD, 50).toUInt();
	CMBProtocol::SetSrvSpeed(srvRelSpd);
    CMBProtocol::SetManualSpeed(10);
    CMBProtocol::SetSrvScale(0.01);
    CMBProtocol::SetAdjustSpeed(5);

	ui->pushButtonSpd->setText(QString("%1%").arg(srvRelSpd));
	// 得到原点复归设置
    if (!pModbus->CheckHome())
    {
        pModbus->ResetHome();
        pModbus->GetHome(home);
        try
        {
            if (pModbus->WriteHome(home))
                throw false;
            if (pModbus->CommandWrite(CMD_WRITE_USER))
                throw false;
        }
        catch (bool &)
        {
        }
    }
	// 组织伺服控制按钮
	pBtnSv = new QButtonGroup;
	pBtnSv->addButton(ui->svPhorPos, SRV_PAHOR);
	pBtnSv->addButton(ui->svPverPos, SRV_PAVER);
	pBtnSv->addButton(ui->svTravPos, SRV_TRV);
	pBtnSv->addButton(ui->svRhorPos, SRV_RAHOR);
	pBtnSv->addButton(ui->svRverPos, SRV_RAVER);
	pBtnSv->addButton(ui->svExtePos, SRV_EXT);
	// 初始化信号/槽
	connect(pModbus, SIGNAL(signal_PgmChange(QString)), this, SLOT(curPgmChange(QString)));
	connect(pUsrPerm, SIGNAL(UserChanged()), this, SLOT(slotChangeUser()));
	connect(pUsrPerm, SIGNAL(UserChanged()), this, SIGNAL(userChange()));
	connect(pModbus, SIGNAL(signal_SysStateChange(uint16_t)), this, SLOT(sysStateChanged(uint16_t)));
	connect(pModbus, SIGNAL(signal_RunStateChange(uint16_t)), this, SLOT(runStateChanged(uint16_t)));
	connect(pModbus, SIGNAL(signal_RunTypeChange(uint16_t)), this, SLOT(runTypeChanged(uint16_t)));
	connect(pModbus, SIGNAL(signal_HomeStateChange(uint16_t)), this, SLOT(SvReferState(uint16_t)));
    connect(pModbus, SIGNAL(signal_XPosChange(qint32)), this, SLOT(PhorPosChanged(qint32)));
    connect(pModbus, SIGNAL(signal_YPosChange(qint32)), this, SLOT(PverPosChanged(qint32)));
    connect(pModbus, SIGNAL(signal_ZPosChange(qint32)), this, SLOT(TrvaPosChanged(qint32)));
    connect(pModbus, SIGNAL(signal_APosChange(qint32)), this, SLOT(RverPosChanged(qint32)));
    connect(pModbus, SIGNAL(signal_BPosChange(qint32)), this, SLOT(RhorPosChanged(qint32)));
    connect(pModbus, SIGNAL(signal_CPosChange(qint32)), this, SLOT(ExtePosChanged(qint32)));
	connect(pModbus, SIGNAL(signal_RverSrvUseChange()), this, SLOT(RverSrvUseChanged()));
    connect(pModbus, SIGNAL(signal_ExtSrvUseChange()), this, SLOT(ExtSrvUseChanged()));
    connect(pModbus, SIGNAL(signal_PhorSrvUseChange()), this, SLOT(PhorSrvUseChanged()));
    connect(pModbus, SIGNAL(signal_RhorSrvUseChange()), this, SLOT(RhorSrvUseChanged()));
	connect(pBtnSv,  SIGNAL(buttonClicked(int)), this, SLOT(svBtnClick(int)));
    connect(pModbus, SIGNAL(signal_AlarmChange(qint16, quint32)), this, SLOT(slot_AlmChg(qint16, quint32)));
    connect(pModbus, SIGNAL(signal_PeriodPoll(quint32)), this, SLOT(slot_MsgPoll(quint32)));
	connect(pClockTimer,SIGNAL(timeout()),this,SLOT(clockUpdate()));
#if defined(Q_WS_QWS)
	connect(pKeyTimer,SIGNAL(timeout()),this,SLOT(keyUpdate()));
#endif
    connect(xSafeSw, SIGNAL(SafeSwitchOn()), this, SLOT(safeSwitchOn()));
	connect(xSafeSw, SIGNAL(SafeSwitchOff()), this, SLOT(safeSwitchOff()));
	connect(xLed, SIGNAL(SwitchChanged(quint8)), this, SLOT(switchChanged(quint8)));
	// 初始化按键数组
	keyVector.clear();
	keyVector
            << KEY_SCAN_HOME << KEY_SCAN_RUN << KEY_SCAN_TRVSUB << KEY_SCAN_LEFT1 << KEY_SCAN_ASC1 << KEY_SCAN_ROTHOR
            << KEY_SCAN_RELHOR << KEY_SCAN_LEFT2 << KEY_SCAN_ASC2 << KEY_SCAN_AUX << KEY_SCAN_STOP << KEY_SCAN_TRVADD
            << KEY_SCAN_RIGHT1 << KEY_SCAN_DES1 << KEY_SCAN_ROTVER << KEY_SCAN_RELVER << KEY_SCAN_RIGHT2 << KEY_SCAN_DES2
			<< VKEY_SCAN_DOOR_RESET << VKEY_SCAN_DOOR_QUERY<< ENCODER_CW << ENCODER_CCW;

    funKeys[0] = funKeys[1] = funKeys[2] = funKeys[3] = KEY_NULL;
	// QApplication 安装事件过滤器
	qApp->installEventFilter(this);
	// 启动时钟定时器
	pClockTimer->start(1000);
#if defined(Q_WS_QWS)
	pKeyTimer->start(10);

#endif

#if IS_XEDITOR
    ui->pushButtonF3->setText(tr("语言"));
    ui->pushButtonF1->setText(tr("选项"));
#endif

	setAlarmDisplay();		//全部构建完后判断报警灯状态	修复启动时报警灯不关闭问题

/*
#if defined (IS_CSOFTTECK)
	pxKeyPad->SetAutoRepeat(KEY_SCAN_ASC1);
    pxKeyPad->SetAutoRepeat(KEY_SCAN_DES1);
    pxKeyPad->SetAutoRepeat(KEY_SCAN_LEFT1);
    pxKeyPad->SetAutoRepeat(KEY_SCAN_RIGHT1);

	if (!pModbus->GetRunnerUse())
    {
        pxKeyPad->SetAutoRepeat(KEY_SCAN_ASC2);
        pxKeyPad->SetAutoRepeat(KEY_SCAN_DES2);
        pxKeyPad->SetAutoRepeat(KEY_SCAN_LEFT2);
		pxKeyPad->SetAutoRepeat(KEY_SCAN_RIGHT2);
    }
    pxKeyPad->SetAutoRepeat(KEY_SCAN_TRVADD);
    pxKeyPad->SetAutoRepeat(KEY_SCAN_TRVSUB);
#endif
*/
}

DialogFrame::~DialogFrame()
{
	delete ui;
	// 清除各个对话框
	delete ServoCtrl;
	delete dlgUserManager;
	delete dlgDateTime;
	// 清除各个窗口画面
	delete Wallpaper;
	delete ScreenAuto;
	delete ScreenManual;
	delete ScreenMenu;
	delete ScreenServo;
	delete ScreenSystem;
	delete ScreenUiSetup;
	delete ScreenAdjust;
	delete ScreenManufacturer;
	delete ScreenInformation;
	delete ScreenAlarm;
	delete ProgramFile;
    delete AlfaProgramFile;
	delete TeachProgram;
    delete Alfaoption;
	delete SystemLog;
	delete Option;
    delete EditOption;
	// 清理其他资源
	delete pClockTimer;
#if defined(Q_WS_QWS)
	delete pKeyTimer;
#endif
	delete pBtnSv;
}
void DialogFrame::CWCCWKeyHandler(quint32 key)
{
	static int i = 0 ;
	static quint32 tempKey;
    if (!ServoCtrl->isHidden())
        return;
	if(tempKey != key)
	{
		tempKey = key;
	}
	else
	{
		if (TeachProgram)
		{
			if (curScreen==SCR_TEACH)
			{
				i++;
				if((i > 2))
				{
					TeachProgram->keyRelease(key);
					i = 0;
				}
				else
					return;
			}
		}
	}
}
void DialogFrame::btnStatusClick()
{
    if(CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    xMessageBox::DoIMM_OUT(pModbus,tr("塑机信号全输出"),tr("确认是否打开全部塑机信号，点击“打开”，信号全输出。点击“关闭”，关闭窗口"));
}
// ************************************************
// 按钮事件处理
// ************************************************
// 全局事件过滤器
bool DialogFrame::eventFilter(QObject *obj, QEvent *event)
{
    if ((event->type() != QEvent::KeyPress) && (event->type() != QEvent::KeyRelease))
        return QDialog::eventFilter(obj, event);
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyVector.contains(keyEvent->key()) == false)
        return QDialog::eventFilter(obj, event);
	if (event->type() == QEvent::KeyPress)
    {
		if (!keyEvent->isAutoRepeat())
			xBuzzer->KeyBeep();
		keyPress(keyEvent);
    }
    else if (event->type() == QEvent::KeyRelease)
    {
    	keyRelease(keyEvent);
    }
    return true;
}
// 校准触摸屏
void DialogFrame::fixtureKey(int key)
{
	// 如果系统不在手动状态则返回
	if (pModbus->GetSysState() != SYS_STATE_MANUAL)
		return;
    if (curScreen == SCR_MAIN)
	{
		// 在主画面
		funKeys[0] = funKeys[1];
		funKeys[1] = funKeys[2];
		funKeys[2] = funKeys[3];
		funKeys[3] = key;
		if (calFlag)
		{
			if ((funKeys[0] == KEY_SCAN_LEFT2) && (funKeys[1] == KEY_SCAN_RIGHT2) && (funKeys[2] == KEY_SCAN_ASC2) && (funKeys[3] == KEY_SCAN_DES2))
			{
	#if defined(Q_WS_QWS)
				QFile file(XPAD_TOUCH_CAL);
				if (file.exists())
				{
					if (file.remove() == false)
					{
						xMessageBox::DoInformation(tr("系统提示"), tr("删除原有的触摸屏校准文件失败！\n无法执行重新校准触摸屏操作。"));
						return;
					}
					sync();
				}
				xMessageBox::DoInformation(tr("系统提示"), tr("请先关闭系统电源，然后重新启动系统进行触摸屏校准操作。"));
	#endif
			}
		}
    }
}

bool DialogFrame::checkManual(void)
{
    // 只有手动状态才能执行		//Added by zhangjz for v1.11 2012-07-13
	if ((pModbus->GetSysState() != SYS_STATE_MANUAL) && (pModbus->GetSysState() != SYS_STATE_JOG))
        return false;
	if (isHoming) return false;
    // 检查安全开关
    if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
    {
#if UI_SAFESW_TIP
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAFESW_TIP));
#endif
        return false;
    }
#if SELECT_SWITCH_USE
    // 检查选择开关
	if (xLed->GetSwitch() != CUSKEY_SEL_MANUAL)
    {
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SELSW_STOP));
        return false;
}
#endif
    return true;
}

typedef struct tagkeyfun
{

    //servo fun
    bool haveSfun;  // 按键是否支持伺服操作
    quint8 ServoID; // 伺服ID

    //pneumatic fun
    bool havePfun;  // 按键是否支持气动操作
    quint8 act;     // 按键对应的气动动作
} KeyFunTab, *pKeyFunTab;

// 单双臂按键对应功能表
static const KeyFunTab singlekeyfuntable[] =
{
#if FACTORY ==FA_MINGRUI
	{false, 0, false, 0},								//#define KEY_SCAN_HOME					(0x100+0)
	{false, 0, false, 0},								//#define KEY_SCAN_RUN					(0x100+1)
	{true, SRV_TRV, false, 0},							//#define KEY_SCAN_TRVSUB				(0x100+2)
	{true, SRV_PAHOR, false, 0},						//#define KEY_SCAN_LEFT1				(0x100+3)
	{true, SRV_PAVER, false, 0},						//#define KEY_SCAN_ASC1					(0x100+4)

	{false, 0, true, PRO_ACT_HOZIONTAL},				//#define KEY_SCAN_ROTHOR				(0x100+5)
	{true, SRV_EXT, true, RUN_ACT_HORIZONTAL},			//#define KEY_SCAN_RELHOR				(0x100+6)
	{true, SRV_RAHOR, true, RUN_ACT_RETURN},			//#define KEY_SCAN_LEFT2                (0x100+7)
	{true,SRV_RAVER, true, RUN_ACT_ASCENT},				//#define KEY_SCAN_ASC2					(0x100+8)

	{false, 0, false, 0},								//#define KEY_SCAN_AUX					(0x100+9)
	{false, 0, false, 0},								//#define KEY_SCAN_STOP					(0x100+10)

	{true, SRV_TRV, false, 0},							//#define KEY_SCAN_TRVADD				(0x100+11)
	{true, SRV_PAHOR, false, 0},						//#define KEY_SCAN_RIGHT1				(0x100+12)
	{true, SRV_PAVER, false, 0},						//#define KEY_SCAN_DES1					(0x100+13)

	{false, 0, true, PRO_ACT_VERTIACL},					//#define KEY_SCAN_ROTVER				(0x100+14)
	{true, SRV_EXT, true, RUN_ACT_VERTIACL},			//#define KEY_SCAN_RELVER				(0x100+15)
	{true, SRV_RAHOR, true, RUN_ACT_ADVANCE},			//#define KEY_SCAN_RIGHT2				(0x100+16)
	{true, SRV_RAVER, true, RUN_ACT_DESCENT},			//#define KEY_SCAN_DES2					(0x100+17)
#else
    {false, 0, false, 0},                                //#define KEY_SCAN_HOME				(0x100+0)
    {false, 0, false, 0},                                //#define KEY_SCAN_RUN					(0x100+1)
    {true, SRV_TRV, false, 0},                           //#define KEY_SCAN_TRVSUB				(0x100+2)
    {true, SRV_PAHOR, false, 0},                         //#define KEY_SCAN_LEFT1				(0x100+3)
    {true, SRV_PAVER, false, 0},                         //#define KEY_SCAN_ASC1				(0x100+4)

    {true, SRV_RAVER, true, PRO_ACT_HOZIONTAL},          //#define KEY_SCAN_ROTHOR				(0x100+5)
    {true, SRV_RAHOR, true, RUN_ACT_HORIZONTAL},         //#define KEY_SCAN_RELHOR				(0x100+6)
    {true, SRV_EXT, true, RUN_ACT_RETURN},              //#define KEY_SCAN_LEFT2                (0x100+7)
    {false, 0, true, RUN_ACT_ASCENT},                    //#define KEY_SCAN_ASC2				(0x100+8)

    {false, 0, false, 0},                                //#define KEY_SCAN_AUX					(0x100+9)
    {false, 0, false, 0},                                //#define KEY_SCAN_STOP				(0x100+10)

    {true, SRV_TRV, false, 0},                           //#define KEY_SCAN_TRVADD				(0x100+11)
    {true, SRV_PAHOR, false, 0},                         //#define KEY_SCAN_RIGHT1				(0x100+12)
    {true, SRV_PAVER, false, 0},                         //#define KEY_SCAN_DES1				(0x100+13)

    {true, SRV_RAVER, true, PRO_ACT_VERTIACL},           //#define KEY_SCAN_ROTVER				(0x100+14)
    {true, SRV_RAHOR, true, RUN_ACT_VERTIACL},           //#define KEY_SCAN_RELVER				(0x100+15)
    {true, SRV_EXT, true, RUN_ACT_ADVANCE},             //#define KEY_SCAN_RIGHT2           (0x100+16)
    {false, 0, true, RUN_ACT_DESCENT},                   //#define KEY_SCAN_DES2				(0x100+17)
#endif
};

static const KeyFunTab doublekeyfuntable[] =
{
    {false, 0, false, 0},                                //#define KEY_SCAN_HOME				(0x100+0)
    {false, 0, false, 0},                                //#define KEY_SCAN_RUN					(0x100+1)
#if FACTORY == FA_SINROBOT_SIDE || FACTORY == FA_JIEJIA_SIDE
	{true, SRV_PAVER, false, 0},                           //#define KEY_SCAN_TRVSUB				(0x100+2)
	{true, SRV_PAHOR, false, 0},                         //#define KEY_SCAN_LEFT1				(0x100+3)
	{true, SRV_TRV, false, 0},                         //#define KEY_SCAN_ASC1				(0x100+4)
#else
	{true, SRV_TRV, false, 0},                           //#define KEY_SCAN_TRVSUB				(0x100+2)
    {true, SRV_PAHOR, false, 0},                         //#define KEY_SCAN_LEFT1				(0x100+3)
	{true, SRV_PAVER, false, 0},                         //#define KEY_SCAN_ASC1				(0x100+4)
#endif
    {false, 0, true, PRO_ACT_HOZIONTAL},                 //#define KEY_SCAN_ROTHOR				(0x100+5)
    {true, SRV_EXT, true, RUN_ACT_HORIZONTAL},           //#define KEY_SCAN_RELHOR				(0x100+6)
    {true, SRV_RAHOR, true, RUN_ACT_ADVANCE},            //#define KEY_SCAN_LEFT2				(0x100+7)
    {true, SRV_RAVER, true, RUN_ACT_ASCENT},             //#define KEY_SCAN_ASC2				(0x100+8)

    {false, 0, false, 0},                                //#define KEY_SCAN_AUX					(0x100+9)
    {false, 0, false, 0},                                //#define KEY_SCAN_STOP				(0x100+10)

#if FACTORY == FA_SINROBOT_SIDE || FACTORY == FA_JIEJIA_SIDE
	{true, SRV_PAVER, false, 0},                           //#define KEY_SCAN_TRVADD				(0x100+11)
	{true, SRV_PAHOR, false, 0},                         //#define KEY_SCAN_RIGHT1				(0x100+12)
	{true, SRV_TRV, false, 0},                         //#define KEY_SCAN_DES1				(0x100+13)
#else
    {true, SRV_TRV, false, 0},                           //#define KEY_SCAN_TRVADD				(0x100+11)
    {true, SRV_PAHOR, false, 0},                         //#define KEY_SCAN_RIGHT1				(0x100+12)
    {true, SRV_PAVER, false, 0},                         //#define KEY_SCAN_DES1				(0x100+13)
#endif

    {false, 0, true, PRO_ACT_VERTIACL},                  //#define KEY_SCAN_ROTVER				(0x100+14)
    {true, SRV_EXT, true, RUN_ACT_VERTIACL},             //#define KEY_SCAN_RELVER				(0x100+15)
    {true, SRV_RAHOR, true, RUN_ACT_RETURN},             //#define KEY_SCAN_RIGHT2				(0x100+16)
    {true, SRV_RAVER, true, RUN_ACT_DESCENT},            //#define KEY_SCAN_DES2				(0x100+17)
};

void DialogFrame::ServoKeyFun(quint8 ServoID, qint32 pos, bool ccw)
{
    int speed = pModbus->GetManualSpeed();
    if (xPermissions::GetPermissions(PER_MANUAL_OPR) == false)
    {
            xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
            return;
    }
    if (!checkManual())
        return;
    if (curScreen == SCR_SERVO)
		pModbus->ManualPos(speed, ServoID, pos, SERVO_MODE_FORCE);
    else if (curScreen == SCR_ADJUST)
    {
        if (pModbus->IsHasRefer(pModbus->GetHomeState()))
			pModbus->ManualPos(speed, ServoID, pos, SERVO_MODE_FORCE);
        else
			pModbus->ManualPos(pModbus->GetAdjustSpeed(), ServoID, ccw ? SVADJ_CCW: SVADJ_CW, SERVO_MODE_ADJUST);
    }
    else
        pModbus->ManualPos(speed, ServoID, ccw ? 0 : MAX_DISTANCE, SERVO_MODE_SAFE);
}

void DialogFrame::keyPress(QKeyEvent *event)
{
	static int i = 0;
    int key = event->key();
//	qDebug() << "key" << event->key();
    pKeyFunTab KFunTab;
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        KFunTab = (pKeyFunTab)singlekeyfuntable;
    else
        KFunTab = (pKeyFunTab)doublekeyfuntable;
/*
#if defined(Q_WS_WIN)
    switch(event->key())
        {
    case KEY_SCAN_HOME:     key = (0x100+0); break;
    case KEY_SCAN_RUN:      key = (0x100+1); break;
    case KEY_SCAN_TRVSUB:   key = (0x100+2); break;
    case KEY_SCAN_LEFT1:    key = (0x100+3); break;
    case KEY_SCAN_ASC1:     key = (0x100+4); break;
    case KEY_SCAN_ROTHOR:   key = (0x100+5); break;
    case KEY_SCAN_RELHOR:   key = (0x100+6); break;
    case KEY_SCAN_LEFT2:    key = (0x100+7); break;
    case KEY_SCAN_ASC2:     key = (0x100+8); break;
    case KEY_SCAN_AUX:      key = (0x100+9); break;
    case KEY_SCAN_STOP:     key = (0x100+10); break;
    case KEY_SCAN_TRVADD:   key = (0x100+11); break;
    case KEY_SCAN_RIGHT1:   key = (0x100+12); break;
    case KEY_SCAN_DES1:     key = (0x100+13); break;
    case KEY_SCAN_ROTVER:   key = (0x100+14); break;
    case KEY_SCAN_RELVER:   key = (0x100+15); break;
    case KEY_SCAN_RIGHT2:   key = (0x100+16); break;
    case KEY_SCAN_DES2:     key = (0x100+17); break;
        }
#endif*/
    quint8 funidx = key - 0x100;
    switch (event->key())
        {
	case KEY_SCAN_AUX:
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
		calFlag = true;
        break;
    case KEY_SCAN_STOP:		// 手动/停止
        // 检查用户权限
        if (xPermissions::GetPermissions(PER_AUTO_OPR) == false)
        {
            xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
            break;
        }
        // 如果系统不在手动状态则返回
        if (pModbus->GetSysState() != SYS_STATE_AUTO)
            return;
        if (curScreen == SCR_AUTO)
            ScreenAuto->BtnManualStop();
        else
            ChangeScreen(SCR_AUTO);
        break;
    case KEY_SCAN_TRVSUB:   // 横行-
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (KFunTab[funidx].haveSfun)
            ServoKeyFun(KFunTab[funidx].ServoID, 0, true);
            break;
    case KEY_SCAN_TRVADD:   // 横行+
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (KFunTab[funidx].haveSfun)
			ServoKeyFun(KFunTab[funidx].ServoID, MAX_DISTANCE, false);
        break;
    case KEY_SCAN_LEFT1:   // 主臂引拔-
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (KFunTab[funidx].haveSfun&&(!pModbus->GetPaHorNotUse()))
            ServoKeyFun(KFunTab[funidx].ServoID, 0, true);
            break;
    case KEY_SCAN_RIGHT1:  // 主臂引拔+
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (KFunTab[funidx].haveSfun&&(!pModbus->GetPaHorNotUse()))
			ServoKeyFun(KFunTab[funidx].ServoID, MAX_DISTANCE, false);
        break;
    case KEY_SCAN_ASC1:   // 主臂上下-
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (KFunTab[funidx].haveSfun)
            ServoKeyFun(KFunTab[funidx].ServoID, 0, true);
            break;
    case KEY_SCAN_DES1:  // 主臂上下+
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (KFunTab[funidx].haveSfun)
			ServoKeyFun(KFunTab[funidx].ServoID, MAX_DISTANCE, false);
        break;
    case KEY_SCAN_LEFT2:   // 双臂-副臂引拔-
		if (calFlag)
			return;
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            return;
        if (KFunTab[funidx].haveSfun)
            ServoKeyFun(KFunTab[funidx].ServoID, 0, true);
            break;
    case KEY_SCAN_RIGHT2:  // 双臂-副臂引拔+
		if (calFlag)
            return;
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            return;
        if (KFunTab[funidx].haveSfun)
			ServoKeyFun(KFunTab[funidx].ServoID, MAX_DISTANCE, false);
		break;
    case KEY_SCAN_ASC2:   // 双臂--副臂上下-
		if (calFlag)
			return;
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            return;
        if (KFunTab[funidx].haveSfun)
            ServoKeyFun(KFunTab[funidx].ServoID, 0, true);
            break;
    case KEY_SCAN_DES2:  // 双臂--副臂上下+
		if (calFlag)
                return;
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            return;
        if (KFunTab[funidx].haveSfun)
			ServoKeyFun(KFunTab[funidx].ServoID, MAX_DISTANCE, false);
        break;
    case KEY_SCAN_ROTHOR:	// 姿势，单臂-倒角-
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (KFunTab[funidx].haveSfun)
            ServoKeyFun(KFunTab[funidx].ServoID, 0, true);
            break;
    case KEY_SCAN_ROTVER:	// 姿势，单臂-倒角+
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (KFunTab[funidx].haveSfun)
			ServoKeyFun(KFunTab[funidx].ServoID, MAX_DISTANCE, false);
        break;
    case KEY_SCAN_RELHOR:	// 旋转，单臂-旋转-
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            return;
        if (KFunTab[funidx].haveSfun)			
            ServoKeyFun(KFunTab[funidx].ServoID, 0, true);
            break;
    case KEY_SCAN_RELVER:	// 旋转，单臂-旋转+
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            return;
        if (KFunTab[funidx].haveSfun)
			ServoKeyFun(KFunTab[funidx].ServoID, MAX_DISTANCE, false);
        break;
	case ENCODER_CW:
	case ENCODER_CCW:
		qDebug()<<"ENCODER_CCW--------------001"<<ENCODER_CCW;
        if(!ServoCtrl->isHidden())      // 调位优先级放到最前面
        {
            ServoCtrl->keyRelease(event->key());
            return;
        }
		if (TeachProgram)
		{
			if (curScreen==SCR_TEACH)
			{
				i++;
				if((i > 2))
				{
					qDebug()<<"ENCODER_CCW--------------002"<<ENCODER_CCW;
					TeachProgram->keyRelease(event->key());
					i = 0;
				}
				else
					return;
			}
		}
		if(pModbus->GetSysState() != SYS_STATE_MANUAL)
			return;
        break;
    case VKEY_SCAN_DOOR_RESET:	// 安全门复位
//        if (pModbus->GetSysState() == SYS_STATE_AUTO)
//            return;
        // 检查用户权限
		qDebug() << "VKEY_SCAN_DOOR_RESET";
        if (xMessageBox::DoDoorResetQuestion(tr("系统警告"), tr("请点击选择相应操作？ \n点击复位，关闭治具，程序复位至第一条执行， \n点击继续，程序继续执行。")) == XMSG_RET_YES)
            pModbus->CommandDoorReset(true);
        else
            pModbus->CommandDoorReset(false);
        break;
    case VKEY_SCAN_DOOR_QUERY:	// 安全门询问
        if(pModbus->GetFunctions(SUB_DOOR_QUERY))
        {
            // 检查用户权限
            xMessageBox::ForceQuit();
#if FACTORY == FA_SINROBOT_SIDE
            if (xMessageBox::DoQuestion(tr("系统询问"), tr("取物失败是否继续运行，点击确定，继续运行。点击取消，关闭窗口")) == XMSG_RET_YES)
#else
            if (xMessageBox::DoQuestion(tr("系统询问"), tr("关闭安全门是否继续运行，点击确定，继续运行。点击取消，关闭窗口")) == XMSG_RET_YES)
#endif
                pModbus->CommandDoorQuery();
        }
        break;
        }
}

// 按键弹起事件处理函数
void DialogFrame::keyRelease(QKeyEvent *event)
{
    int key = event->key();
#if defined(Q_WS_WIN)
    switch(event->key())
    {
    case KEY_SCAN_HOME:     key = (0x100+0); break;
    case KEY_SCAN_RUN:      key = (0x100+1); break;
    case KEY_SCAN_TRVSUB:   key = (0x100+2); break;
    case KEY_SCAN_LEFT1:    key = (0x100+3); break;
    case KEY_SCAN_ASC1:     key = (0x100+4); break;
    case KEY_SCAN_ROTHOR:   key = (0x100+5); break;
    case KEY_SCAN_RELHOR:   key = (0x100+6); break;
    case KEY_SCAN_LEFT2:    key = (0x100+7); break;
    case KEY_SCAN_ASC2:     key = (0x100+8); break;
    case KEY_SCAN_AUX:      key = (0x100+9); break;
    case KEY_SCAN_STOP:     key = (0x100+10); break;
    case KEY_SCAN_TRVADD:   key = (0x100+11); break;
    case KEY_SCAN_RIGHT1:   key = (0x100+12); break;
    case KEY_SCAN_DES1:     key = (0x100+13); break;
    case KEY_SCAN_ROTVER:   key = (0x100+14); break;
    case KEY_SCAN_RELVER:   key = (0x100+15); break;
    case KEY_SCAN_RIGHT2:   key = (0x100+16); break;
    case KEY_SCAN_DES2:     key = (0x100+17); break;
    }
#endif

    pKeyFunTab KFunTab;
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        KFunTab = (pKeyFunTab)singlekeyfuntable;
    else
        KFunTab = (pKeyFunTab)doublekeyfuntable;

    quint8 funidx = key - 0x100;
    switch (event->key())
	{
    case KEY_SCAN_HOME:		// 原点复归
		// 如果系统不在手动状态则返回
		if (pModbus->GetSysState() != SYS_STATE_MANUAL)
			return;
        if (pModbus->GetRunState() == RUN_STATE_RUN)
            return;
		ReturnToOrigin();
		break;
    case KEY_SCAN_RUN:		// 自动/运行
		// 检查用户权限
		if (xPermissions::GetPermissions(PER_AUTO_OPR) == false)
		{
			xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
			break;
		}
        if (pModbus->GetRunState() == RUN_STATE_RUN)
            return;
        if (xMessageBox::IsShow())
            return;
		if (curScreen == SCR_AUTO)
			ScreenAuto->BtnAutoRunClick();
		else
			ChangeScreen(SCR_AUTO);
		break;
	case KEY_SCAN_AUX:		// 复位
		calFlag = false;
		pModbus->CommandClearAlarm();
		break;
	case KEY_SCAN_TRVSUB:   // 横行-
	case KEY_SCAN_TRVADD:   // 横行+
	case KEY_SCAN_LEFT1:   // 引拔-
	case KEY_SCAN_RIGHT1:  // 引拔+
	case KEY_SCAN_ASC1:   // 上下-
	case KEY_SCAN_DES1:  // 上下+
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
//        if ((pModbus->GetSysState() == SYS_STATE_MANUAL) && (pModbus->GetRunState() == RUN_STATE_RUN) && (pModbus->GetRunType() == RUN_TYPE_SINGLE))
//            return;
		if (isHoming)
			return;
        if (!calFlag)
			pModbus->SetRunState(RUN_STATE_PAUSE);
		break;

    case KEY_SCAN_LEFT2:   // 单臂-副臂气动引进
    case KEY_SCAN_RIGHT2:  // 单臂-副臂气动引退
		if (pModbus->GetSysState() == SYS_STATE_AUTO)
			return;
		if (KFunTab[funidx].haveSfun&&(pModbus->GetRhorSrvUse()))
		{
			if (!calFlag)
				pModbus->SetRunState(RUN_STATE_PAUSE);
		}
		else
		{
			if (KFunTab[funidx].havePfun&&pModbus->GetRunnerUse())
			{
				pModbus->ManualRun(KFunTab[funidx].act);
			}
		}
		break;
	case ENCODER_CW:
	case ENCODER_CCW:
		qDebug()<<"ENCODER Release------------------------------"<<ENCODER_CCW;
        break;
    case KEY_SCAN_ASC2:   // 单臂-副臂气动上升
    case KEY_SCAN_DES2:   // 单臂-副臂气动下降
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (KFunTab[funidx].haveSfun&&(pModbus->GetRverSrvUse()))
        {
            if (!calFlag)
                pModbus->SetRunState(RUN_STATE_PAUSE);
        }
        else
        {
            if (KFunTab[funidx].havePfun&&pModbus->GetRunnerUse())
            {
                pModbus->ManualRun(KFunTab[funidx].act);
            }
        }
        break;
    case KEY_SCAN_ROTHOR:	// 双臂-正臂倒角
    case KEY_SCAN_ROTVER:	//
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (KFunTab[funidx].haveSfun&&(pModbus->GetRverSrvUse()))
        {
            if (!calFlag)
                pModbus->SetRunState(RUN_STATE_PAUSE);
        }
        else
        {
            if (KFunTab[funidx].havePfun&&pModbus->GetRotateUse())
            {
                pModbus->ManualPro(KFunTab[funidx].act);
            }
        }
        break;
    case KEY_SCAN_RELHOR:	// 双臂-副臂倒角
    case KEY_SCAN_RELVER:	//
        if (pModbus->GetSysState() == SYS_STATE_AUTO)
            return;
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            return;
        if((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        {

            if ((KFunTab[funidx].haveSfun) && pModbus->GetRhorSrvUse())
            {
                if (!calFlag)
                    pModbus->SetRunState(RUN_STATE_PAUSE);
            }
            else
            {
                if (KFunTab[funidx].havePfun&&pModbus->GetRunRotateUse())//
                {
                    pModbus->ManualRun(KFunTab[funidx].act);
                }
            }
        }
        else//双臂
        {
            if ((KFunTab[funidx].haveSfun)&&pModbus->GetExtSrvUse())
        {
            if (!calFlag)
                pModbus->SetRunState(RUN_STATE_PAUSE);
        }
        else
        {
                if (KFunTab[funidx].havePfun&&pModbus->GetRunRotateUse())//
            {
                pModbus->ManualRun(KFunTab[funidx].act);
            }
        }

        }
        break;
    }
    fixtureKey(event->key());
}

// 执行治具控制指令
void DialogFrame::extOutCtrl(quint16 code)
{
    if (xIoPort::GetOut(code) == true)
		pModbus->ManualExt(false, code);
	else
		pModbus->ManualExt(true, code);
}

void DialogFrame::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		retranslateUI();
		curPgmChange(pModbus->GetCurPgmName());
		break;
	default:
		break;
	}
}
#if defined(Q_WS_QWS)
// 设置当前日期事件
void DialogFrame::keyUpdate(void)
{
	board->ReadKeys(true);//A40I
}
#endif

// ************************************************
// 设置界面显示
// ************************************************
// 绘制背景图片
/*
void DialogFrame::paintEvent(QPaintEvent * e)
{
	QDialog::paintEvent(e);
	QPainter painter(this);
	painter.drawPixmap(0, 80, 800, 981, QPixmap(XPAD_WALLPAPER_NAME));
}
*/
// 翻译界面字符串
void DialogFrame::retranslateUI(void)
{
    if ((pModbus->GetTemplateUse()) ||(pModbus->GetSysState() == SYS_STATE_AUTO))
		ui->pushButtonF4->setText(tr("修改"));
	else
        ui->pushButtonF4->setText(tr("教导"));
    AlfamodeChanged();
	// 初始化伺服位置显示
	strPhor = GetServoName(AXIS_IDX_PHOR);	strPhor.append(": ");
	strPver = GetServoName(AXIS_IDX_PVER);	strPver.append(": ");
	strTrv = GetServoName(AXIS_IDX_TRV);	strTrv.append(": ");
	strRhor = GetServoName(AXIS_IDX_RHOR);	strRhor.append(": ");
	strRver = GetServoName(AXIS_IDX_RVER);	strRver.append(": ");
	strExt = GetServoName(AXIS_IDX_EXT);	strExt.append(": ");
	quint32 posPhor, posPver, posTrv, posRhor, posRver, posExt;
	pModbus->GetServoPos(posPhor, posPver, posTrv, posRhor, posRver, posExt);
	PhorPosChanged(posPhor);
	PverPosChanged(posPver);
	TrvaPosChanged(posTrv);
	RhorPosChanged(posRhor);
	RverPosChanged(posRver);
	ExtePosChanged(posExt);
	// 窗口标题
	setWinTitle();
	// 当前用户
	slotChangeUser();
#if FACTORY == FA_FUSHITONG
    ui->pushButtonF6->setText(tr("手动"));
#endif
}

// 根据当前界面设置标题
void DialogFrame::setWinTitle(void)
{
    if ((pModbus->GetTemplateUse()) || (pModbus->GetSysState() == SYS_STATE_AUTO))
		ui->pushButtonF4->setText(tr("修改"));
	else
        ui->pushButtonF4->setText(tr("教导"));
    setSysState(pModbus->GetSysState(), pModbus->GetRunState(), pModbus->GetRunType());
    AlfamodeChanged();
}

// 设置界面系统状态显示
void DialogFrame::setSysState(uint16_t sysState, uint16_t runState, uint16_t runType)
{
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	if (sysState == SYS_STATE_MANUAL)
	{
		// 手动状态
        if (!pModbus->GetTemplateUse())
            ui->pushButtonF4->setText(tr("教导"));
		else
            ui->pushButtonF4->setText(tr("修改"));
#if SELECT_SWITCH_USE
		if (xLed->GetSwitch() == SELSW_STOP)
        {
            ui->pushButtonStatus->setText(tr("停止"));
            ui->pushButtonStatus->setIcon(QIcon(":img/32X32/Stop.png"));
        }
		else
#endif
		{
            if (!settings.value(XPAD_SET_SWITCHUSE, true).toBool())
            {
                ui->pushButtonStatus->setIcon(QIcon(":img/32X32/ManualGreen.png"));
                ui->pushButtonStatus->setText(tr("手动"));
            }
            else
            {
                if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
                    ui->pushButtonStatus->setIcon(QIcon(":img/32X32/Manual.png"));
                else
                    ui->pushButtonStatus->setIcon(QIcon(":img/32X32/ManualGreen.png"));
                ui->pushButtonStatus->setText(tr("手动"));
            }
        }
	}
	else if (sysState == SYS_STATE_AUTO)
	{
		ui->pushButtonF4->setText(tr("修改"));
		if (runState == RUN_STATE_RUN)
		{
			if (runType == RUN_TYPE_LOOP)
			{
				// 全自动运行
				ui->pushButtonStatus->setIcon(QIcon(":img/32X32/AutoRun.png"));
                ui->pushButtonStatus->setText(tr("全自动"));
			}
			else if (runType == RUN_TYPE_STEP)
			{
				// 单步运行
				ui->pushButtonStatus->setIcon(QIcon(":img/32X32/AutoStep.png"));
                ui->pushButtonStatus->setText(tr("单步"));
			}
			else if (runType == RUN_TYPE_SINGLE)
			{
				// 单周期运行
				ui->pushButtonStatus->setIcon(QIcon(":img/32X32/AutoPeriod.png"));
                ui->pushButtonStatus->setText(tr("单周期"));
			}
		}
		else
		{
			// 自动待机状态
			ui->pushButtonStatus->setIcon(QIcon(":img/32X32/AutoPause.png"));
            ui->pushButtonStatus->setText(tr("自动暂停"));
		}
	}
}

// 设置界面报警信息显示
void DialogFrame::setAlarmDisplay(void)
{
    uint32_t alm;
	int ret;
	ret = pModbus->GetFirstAlarm(alm);
	if (ret < 0)
	{
		// 系统没有报警
#if defined(Q_WS_QWS)
		board->SetLED(Led_Err,false);
#endif

		ui->pushButtonF5->setIcon(QIcon(":img/48X48/BtnAlmF.png"));
	}
	else
	{
		// 系统存在报警
#if defined(Q_WS_QWS)
		board->SetLED(Led_Err,true);
#endif

		ui->pushButtonF5->setIcon(QIcon(":img/48X48/BtnAlmT.png"));
    }
}
bool DialogFrame::HideShowScreen(unsigned int scrID, bool force)
{
    bool ret = true;
    if (scrID >= SCR_MAX)
        return false;
    switch (scrID)
    {
    case SCR_MAIN:
        ScreenAuto->hide();
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->show();
        break;
    case SCR_AUTO:
#if IS_XEDITOR
        ScreenAuto->hide();
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        EditOption->show();
#else
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->show();
#endif
        break;
    case SCR_MANUAL:
#if IS_XEDITOR
#else
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        ScreenManual->show();
#endif
        break;
    case SCR_MENU:
#if IS_XEDITOR
#else
        ScreenManual->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        ScreenMenu->show();
#endif
        break;
    case SCR_SERVO:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        ScreenServo->show();
        break;
    case SCR_SYSTEM:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        ScreenSystem->show();
        break;
    case SCR_UISETUP:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        ScreenUiSetup->show();
        break;
    case SCR_ADJUST:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        ScreenAdjust->show();
        break;
    case SCR_MANUFACTURER:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        ScreenManufacturer->show();
        break;
    case SCR_INFORMATION:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        ScreenInformation->show();
        break;
    case SCR_TEACH:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        TeachProgram->show();
        break;
    case SCR_ALFAOPTION:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        Alfaoption->show();
        break;
    case SCR_SYSTEMLOG:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        SystemLog->show();
        break;
    case SCR_ALARM:
#if IS_XEDITOR
#else
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        ScreenAlarm->show();
#endif
        break;
    case SCR_PROGRAMFILE:
        if (pModbus->IsALFAMode())
        {
            ScreenManual->hide();
            ScreenMenu->hide();
            ScreenServo->hide();
            ScreenSystem->hide();
            ScreenUiSetup->hide();
            ScreenAdjust->hide();
            ScreenManufacturer->hide();
            ScreenInformation->hide();
            ScreenAlarm->hide();
            ProgramFile->hide();
            TeachProgram->hide();
            Alfaoption->hide();
            SystemLog->hide();
            Option->hide();
            EditOption->hide();
            VarInit->hide();
            IOSetup->hide();
            Wallpaper->hide();
            ScreenAuto->hide();
            AlfaProgramFile->show();
        }
        else
        {
            ScreenManual->hide();
            ScreenMenu->hide();
            ScreenServo->hide();
            ScreenSystem->hide();
            ScreenUiSetup->hide();
            ScreenAdjust->hide();
            ScreenManufacturer->hide();
            ScreenInformation->hide();
            ScreenAlarm->hide();
            AlfaProgramFile->hide();
            TeachProgram->hide();
            Alfaoption->hide();
            SystemLog->hide();
            Option->hide();
            EditOption->hide();
            VarInit->hide();
            IOSetup->hide();
            Wallpaper->hide();
            ScreenAuto->hide();
            ProgramFile->show();
        }
        break;
    case SCR_OPTION:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        EditOption->hide();
        VarInit->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        Option->show();
        break;
    case SCR_VARINIT:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        IOSetup->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        VarInit->show();
        break;
    case SCR_IOSETUP:
        ScreenManual->hide();
        ScreenMenu->hide();
        ScreenServo->hide();
        ScreenSystem->hide();
        ScreenUiSetup->hide();
        ScreenAdjust->hide();
        ScreenManufacturer->hide();
        ScreenInformation->hide();
        ScreenAlarm->hide();
        ProgramFile->hide();
        AlfaProgramFile->hide();
        TeachProgram->hide();
        Alfaoption->hide();
        SystemLog->hide();
        Option->hide();
        EditOption->hide();
        VarInit->hide();
        Wallpaper->hide();
        ScreenAuto->hide();
        IOSetup->show();
        break;
    }
    return ret;
}

// 切换主框架上的显示画面
void DialogFrame::ChangeScreen(unsigned int scrID, bool force)
{
    unsigned int curScreenbak = curScreen;
	bool ret = true;
	if (scrID >= SCR_MAX)
		return;
	if (curScreen == scrID)
		return;
	// 退出当前画面
	switch (curScreen)
	{
	case SCR_AUTO:
#if IS_XEDITOR
        ret = EditOption->ExitForm();
#else
		ret = ScreenAuto->ExitForm();
#endif
		break;
	case SCR_MANUAL:
#if IS_XEDITOR
#else
		ret = ScreenManual->ExitForm();
#endif
		break;
	case SCR_MENU:
#if IS_XEDITOR
#else
		ret = ScreenMenu->ExitForm();
#endif
		break;
	case SCR_SERVO:
		ret = ScreenServo->ExitForm();
		break;
	case SCR_SYSTEM:
		ret = ScreenSystem->ExitForm();
		break;
	case SCR_UISETUP:
		ret = ScreenUiSetup->ExitForm();
		break;
	case SCR_ADJUST:
		ret = ScreenAdjust->ExitForm();
		break;
	case SCR_MANUFACTURER:
		ret = ScreenManufacturer->ExitForm();
		break;
	case SCR_INFORMATION:
		ret = ScreenInformation->ExitForm();
		break;
	case SCR_TEACH:
		ret = TeachProgram->ExitForm();
		break;
    case SCR_ALFAOPTION:
        ret = Alfaoption->ExitForm();
        break;
	case SCR_SYSTEMLOG:
		ret = SystemLog->ExitForm();
		break;
	case SCR_ALARM:
#if IS_XEDITOR
#else
		ret = ScreenAlarm->ExitForm();
#endif
		break;
	case SCR_PROGRAMFILE:
        if (pModbus->IsALFAMode())
            ret = AlfaProgramFile->ExitForm();
        else
		ret = ProgramFile->ExitForm();
		break;
    case SCR_OPTION:
        ret = Option->ExitForm();
        break;
    case SCR_VARINIT:
        ret = VarInit->ExitForm();
        break;
    case SCR_IOSETUP:
        ret = IOSetup->ExitForm();
        break;
    case SCR_MAIN:
        ret = Wallpaper->ExitForm();
        break;
    }
	if (ret == false)
		return;
	// 进入指定画面
	switch (scrID)
	{
	case SCR_MAIN:
		Wallpaper->EnterForm();
		break;
	case SCR_AUTO:
#if IS_XEDITOR
        ret = EditOption->EnterForm();
#else
		ret = ScreenAuto->EnterForm();
#endif
		break;
	case SCR_MANUAL:
#if IS_XEDITOR
#else
		ret = ScreenManual->EnterForm();
#endif
		break;
	case SCR_MENU:
#if IS_XEDITOR
#else
		ret = ScreenMenu->EnterForm();
#endif
		break;
	case SCR_SERVO:
		ret = ScreenServo->EnterForm();
		break;
	case SCR_SYSTEM:
		ret = ScreenSystem->EnterForm();
		break;
	case SCR_UISETUP:
		ret = ScreenUiSetup->EnterForm();
		break;
	case SCR_ADJUST:
		ret = ScreenAdjust->EnterForm();
		break;
	case SCR_MANUFACTURER:
		ret = ScreenManufacturer->EnterForm();
		break;
	case SCR_INFORMATION:
		ret = ScreenInformation->EnterForm();
		break;
	case SCR_TEACH:
		ret = TeachProgram->EnterForm();
		break;
    case SCR_ALFAOPTION:
        ret = Alfaoption->EnterForm();
        break;
	case SCR_SYSTEMLOG:
		ret = SystemLog->EnterForm();
		break;
	case SCR_ALARM:
#if IS_XEDITOR
#else
		ret = ScreenAlarm->EnterForm();
#endif
		break;
	case SCR_PROGRAMFILE:
        if (pModbus->IsALFAMode())
            ret = AlfaProgramFile->EnterForm();
        else
		ret = ProgramFile->EnterForm();
		break;
    case SCR_OPTION:
        ret = Option->EnterForm();
        break;
    case SCR_VARINIT:
        ret = VarInit->EnterForm();
        break;
    case SCR_IOSETUP:
        ret = IOSetup->EnterForm();
        break;
    }
    if (curScreenbak==curScreen)
    {
	if (ret)
	{
        HideShowScreen(scrID);
        curScreen = scrID;
	}
	else
	{
		funKeys[0] = funKeys[1] = funKeys[2] = funKeys[3] = KEY_NULL;
	}
    }
    else
    {
        if (ret)
        {
            HideShowScreen(scrID);
            curScreen = scrID;
        }
    }
	setWinTitle();
}

// 返回待机画面
void DialogFrame::ReturnMain(void)
{
	ScreenAuto->hide();
	ScreenManual->hide();
	ScreenMenu->hide();
	ScreenServo->hide();
	ScreenSystem->hide();
	ScreenUiSetup->hide();
	ScreenAdjust->hide();
	ScreenManufacturer->hide();
	ScreenInformation->hide();
	ScreenAlarm->hide();
	ProgramFile->hide();
    AlfaProgramFile->hide();
	TeachProgram->hide();
    Alfaoption->hide();
	SystemLog->hide();
	Option->hide();
    EditOption->hide();
    VarInit->hide();
    IOSetup->hide();

    Wallpaper->EnterForm();
    Wallpaper->show();
    curScreen = SCR_MAIN;
	setWinTitle();
}
// 设置当前程序名称
void DialogFrame::curPgmChange(QString name)
{
//	QString name = pModbus->GetCurPgmName();
    if (pModbus->IsALFAMode())
    {
        name = pModbus->GetAlfaPgmName();
    }
	ui->pushButtonPgm->setStyleSheet("QPushButton{text-align : left;}");
	if (name.isEmpty())
		ui->pushButtonPgm->setText(xStringResource::GetString(STRRES_NO_CURPGM));
	else
	{
		QFileInfo fileInfo(name);
		ui->pushButtonPgm->setText(tr("当前程序:") + "\n" + fileInfo.baseName());
	}
    // 金博跃每次将program下程序拷贝temp目录
#if (FACTORY == FA_JINBOYUE_SPECIAL)
    QFile tmpFile(CMBProtocol::GetCurPgmName(true));
    if (tmpFile.exists())
        tmpFile.remove();
    QFile::copy(CMBProtocol::GetCurPgmName(), CMBProtocol::GetCurPgmName(true));
 #endif
}
// 设置当前日期事件
void DialogFrame::clockUpdate(void)
{
	ui->pushButtonDateTime->setText(QDate::currentDate().toString("yyyy-MM-dd") + "\n" + QTime::currentTime().toString());
#if defined(Q_WS_QWS)                                                                 //yun0926
    board->SetLED(Led_Run,runled_state);
    runled_state = !runled_state;
#endif
}
// 当前用户改变信号槽
void DialogFrame::slotChangeUser(void)
{
	switch (xPermissions::GetCurrentUser())
	{
	case xPermissions::Operater:
		ui->pushButtonUsr->setText(tr("操作员"));
		break;
	case xPermissions::AdvOperater:
		ui->pushButtonUsr->setText(tr("高级操作员"));
		break;
	case xPermissions::Administrator:
		ui->pushButtonUsr->setText(tr("管理员"));
		break;
	case xPermissions::AdvAdministrator:
		ui->pushButtonUsr->setText(tr("高级管理员"));
		break;
	case xPermissions::SuperUser:
		ui->pushButtonUsr->setText(tr("超级用户"));
		break;
	default:
		ui->pushButtonUsr->setText(tr("操作员"));
		break;
	}
}

// 安全开关关闭信号槽
void DialogFrame::safeSwitchOff(void)
{
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	setSafeSwitchFlag(false);
	// 如果系统在自动状态则返回
	if (pModbus->GetSysState() == SYS_STATE_AUTO)
		return;
	if ((settings.value(XPAD_SET_ALWAYSON, true).toBool() == false) && isHoming == 1)
		return;
	else
	// 停止伺服运转
//	pModbus->CommandStop();
        pModbus->SetRunState(RUN_STATE_PAUSE);
}
// 安全开关开启信号槽
void DialogFrame::safeSwitchOn(void)
{
	setSafeSwitchFlag(true);
}
// 选择开关改变信号槽
void DialogFrame::switchChanged(quint8 status)
{
#if SELECT_SWITCH_USE
	quint16 sysStatus = pModbus->GetSysState();
	if ((status == CUSKEY_SEL_STOP) || (status == CUSKEY_SEL_MANUAL))
	{
		// 进入停止/手动模式
		if (sysStatus == SYS_STATE_AUTO)
		{
			// 如果系统当前在自动状态(运行/等待)则进入手动状态
			if (pModbus->GetRunState() != RUN_STATE_PAUSE)
			{
                //pModbus->SetRunType(RUN_TYPE_SINGLE);
                if (pModbus->SetRunState(RUN_STATE_PAUSE) == SENDMSG_RET_ACK)
                {
                    if (pModbus->GetRunType() == RUN_TYPE_LOOP)
                    {
                        xMessageBox::DoWaiting(pModbus, tr("系统提示"), tr("正在停止系统全自动运行，请稍候..."));
                        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_RUN2WAIT);
                    }
                    else if (pModbus->GetRunType() == RUN_TYPE_SINGLE)
                    {
                        xMessageBox::DoWaiting(pModbus, tr("系统提示"), tr("正在停止系统单周期运行，请稍候..."));
                        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_PERIOD2WAIT);
                    }
                    else if (pModbus->GetRunType() == RUN_TYPE_STEP)
                    {
                        xMessageBox::DoWaiting(pModbus, tr("系统提示"), tr("正在停止系统单步运行，请稍候..."));
                        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_STEP2WAIT);
                    }
                }
			}
			if (pModbus->SetSysState(SYS_STATE_MANUAL) == SENDMSG_RET_ACK)
				xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_WAIT2MANUL);
			// 写入系统日志
			xSysLog::SaveChange();
		}
		else
		{
			// 停止伺服运转
			pModbus->CommandStop();
		}
	}
	else if (status == SELSW_AUTO)
	{
		// 进入自动运行模式
		if (sysStatus != SYS_STATE_AUTO)
		{
			if (curScreen != SCR_AUTO)
				ChangeScreen(SCR_AUTO, true);
			if (pModbus->GetRunState() != RUN_STATE_PAUSE)
			{
				// 停止伺服运转
				pModbus->CommandStop();
				xMessageBox::DoWaiting(pModbus, tr("系统提示"), tr("正在停止当前动作执行，请稍候..."));
			}
			if (curScreen == SCR_AUTO)
				ScreenAuto->TransAutoCode();
			if (pModbus->SetSysState(SYS_STATE_AUTO) == SENDMSG_RET_ACK)
			{
				xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL2AUTO);
				// 写入系统日志
				xSysLog::SaveChange();
			}
		}
	}
	setSysState(pModbus->GetSysState(), pModbus->GetRunState(), pModbus->GetRunType());
#endif
}

// 伺服原点复归状态槽
void DialogFrame::SvReferState(uint16_t state)
{
	if (pModbus->IsHasRefer(state) == false)
	{
		ui->svPhorPos->setEnabled(false);
		ui->svPverPos->setEnabled(false);
		ui->svTravPos->setEnabled(false);
		ui->svRhorPos->setEnabled(false);
		ui->svRverPos->setEnabled(false);
		ui->svExtePos->setEnabled(false);
		ui->pushButtonOrigin->setIcon(QIcon(":/img/32X32/OriginNoRef.png"));
	}
	else
	{
        ui->svPhorPos->setEnabled(!pModbus->GetPaHorNotUse());
		ui->svPverPos->setEnabled(true);
		ui->svTravPos->setEnabled(true);
        ui->svRhorPos->setEnabled(pModbus->GetRhorSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
        ui->svRverPos->setEnabled(pModbus->GetRverSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
        ui->svExtePos->setEnabled(pModbus->GetExtSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
        ui->pushButtonOrigin->setIcon(QIcon(":/img/32X32/OriginHasRef.png"));
	}
    setSafeSwitchFlag(xSafeSw->GetSafeSwState() == SAFE_SWITCH_ON);
}
// 系统模式改变信号槽
void DialogFrame::sysStateChanged(uint16_t state)
{
	setSysState(state, pModbus->GetRunState(), pModbus->GetRunType());
}
// 系统运行状态改变信号槽
void DialogFrame::runStateChanged(uint16_t state)
{
	setSysState(pModbus->GetSysState(), state, pModbus->GetRunType());
}
// 运行方式改变信号槽
void DialogFrame::runTypeChanged(uint16_t type)
{
	setSysState(pModbus->GetSysState(), pModbus->GetRunState(), type);
}
// 设置报警状态
void DialogFrame::slot_AlmChg(qint16 idx, quint32 alarm)
{
    if ((alarm & 0xffff) == ALMRES_NO_ALARM)
	{
		setAlarmDisplay();
	}
	else
	{
#if defined(Q_WS_QWS)
        board->SetLED(Led_Err,true);                                        //yun0926
#endif

		ui->pushButtonF5->setIcon(QIcon(":img/48X48/BtnAlmT.png"));
#if defined(Q_WS_QWS)
        qwsServer->sendKeyEvent(0, -1, Qt::KeypadModifier, true, false);
#endif
        if ((curScreen != SCR_TEACH) && (curScreen != SCR_SERVO) && (curScreen != SCR_SYSTEM) && (curScreen != SCR_UISETUP) && (curScreen != SCR_OPTION) &&
                (curScreen != SCR_MANUFACTURER) && (curScreen != SCR_VARINIT) && (curScreen != SCR_PROGRAMFILE) && (curScreen != SCR_ALFAOPTION) && (curScreen != SCR_IOSETUP))
        ChangeScreen(SCR_ALARM);
    }
}
xDelayMessageBox gdelaymsg;
// 设置系统消息状态
void DialogFrame::slot_MsgPoll(quint32 msg)
{
//  msg = pModbus->GetSysMsg();
	if (msg == ALMRES_NO_ALARM)
		return;
    static quint32 lastmsg = 0;
    quint32 alm;
    quint32 srvPos[6];
    if ((pModbus->GetFirstAlarm(alm) < 0)&& (lastmsg != msg))
    {
        pModbus->GetServoPos(srvPos[AXIS_IDX_PHOR], srvPos[AXIS_IDX_PVER], srvPos[AXIS_IDX_TRV], srvPos[AXIS_IDX_RHOR], srvPos[AXIS_IDX_RVER], srvPos[AXIS_IDX_EXT]);
        lastmsg = msg;
    }
    if (gdelaymsg.DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetAlarm(msg))!=XMSG_HAS_SHOWED)
	{
        if (pModbus->ClrMessage() == SENDMSG_RET_ACK)
		{
            xSysLog::AddRecord(SYSLOG_TYPE_MSG, msg);
            xSysLog::SaveChange();
        }
	}
}
// ************************************************
// 伺服轴位置改变信号槽
// ************************************************
// 正臂引拔轴位置改变槽
void DialogFrame::PhorPosChanged(qint32 pos)
{
    ui->svPhorPos->setText(strPhor + QString::number(pos / 100.00, 'f', 2));
}
// 正臂上下轴位置改变槽
void DialogFrame::PverPosChanged(qint32 pos)
{
    ui->svPverPos->setText(strPver + QString::number(pos / 100.00, 'f', 2));
}
// 横行轴位置改变槽
void DialogFrame::TrvaPosChanged(qint32 pos)
{
    ui->svTravPos->setText(strTrv + QString::number(pos / 100.00, 'f', 2));
}
// 副臂引拔轴位置改变槽
void DialogFrame::RhorPosChanged(qint32 pos)
{
    ui->svRhorPos->setText(strRhor + QString::number(pos / 100.00, 'f', 2));
}
// 副臂上下轴位置改变槽
void DialogFrame::RverPosChanged(qint32 pos)
{
    ui->svRverPos->setText(strRver + QString::number(pos / 100.00, 'f', 2));
}
// 扩展轴位置改变槽
void DialogFrame::ExtePosChanged(qint32 pos)
{
    ui->svExtePos->setText(strExt + QString::number(pos / 100.00, 'f', 2));
}
// 正臂引拔轴伺服使用状态改变槽
void DialogFrame::PhorSrvUseChanged(void)
{
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        ui->svPhorPos->setEnabled(!pModbus->GetPaHorNotUse());
    setSafeSwitchFlag(xSafeSw->GetSafeSwState() == SAFE_SWITCH_ON);
}
// 扩展轴伺服使用状态改变槽
void DialogFrame::ExtSrvUseChanged(void)
{
	if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        ui->svExtePos->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    setSafeSwitchFlag(xSafeSw->GetSafeSwState() == SAFE_SWITCH_ON);
}
// 副臂引拔轴伺服使用状态改变槽
void DialogFrame::RhorSrvUseChanged(void)
{
	if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        ui->svRhorPos->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    setSafeSwitchFlag(xSafeSw->GetSafeSwState() == SAFE_SWITCH_ON);
}
// 扩展轴伺服使用状态改变槽
void DialogFrame::RverSrvUseChanged(void)
{
	if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        ui->svRverPos->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    setSafeSwitchFlag(xSafeSw->GetSafeSwState() == SAFE_SWITCH_ON);
}
// 简易模式
void DialogFrame::AlfamodeChanged(void)
{
    if (pModbus->IsALFAMode())
        ui->pushButtonF4->setText(tr("向导"));
    else
    {
        if ((pModbus->GetTemplateUse()) || (pModbus->GetSysState() == SYS_STATE_AUTO))
            ui->pushButtonF4->setText(tr("修改"));
        else
            ui->pushButtonF4->setText(tr("教导"));
    }
}

// ************************************************
// 伺服控制按钮槽
// ************************************************
void DialogFrame::svBtnClick(int id)
{
#if IS_XEDITOR
#else
	// 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return;
	}
	bool perm = false;
	bool srvSet = false;
    if ((pModbus->GetSysState() == SYS_STATE_AUTO) || ((pModbus->GetSysState() == SYS_STATE_JOG)))
		return;
	if (curScreen == SCR_SERVO)
	{
		perm = xPermissions::GetPermissions(PER_SRV_SAFE);
		srvSet = true;
	}
	else
	{
		perm = xPermissions::GetPermissions(PER_SRV_CTRL);
	}
#if SELECT_SWITCH_USE
	// 检查选择开关
	if (pxKeyPad->GetSwitch() != CUSKEY_SEL_MANUAL)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SELSW_STOP));
		return;
	}
#endif
	if (perm == false)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
		return;
	}
	quint32 Pver, Rver, trv, ext, disHomP_R, MinDisP_R;
	ScreenServo->GetDistance(Pver, Rver, trv, ext, disHomP_R, MinDisP_R);
	ServoCtrl->DoForm(id, srvSet,Pver,Rver,trv,ext,disHomP_R,MinDisP_R);
#endif
}
// ************************************************
// 窗口底部功能按钮槽
// ************************************************
// 自动按钮
void DialogFrame::BtnAutoClick(void)
{
	if (xPermissions::GetPermissions(PER_AUTO_OPR) == false)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
		return;
	}
	ChangeScreen(SCR_AUTO);
}
// 手动按钮
void DialogFrame::BtnManualClick(void)
{
#if IS_XEDITOR
#else
	ChangeScreen(SCR_MANUAL);
#endif
}
// 功能按钮
void DialogFrame::BtnMenuClick(void)
{
#if IS_XEDITOR
    ChangeScreen(SCR_UISETUP);
#else
	ChangeScreen(SCR_MENU);
#endif
}
// 教导按钮
void DialogFrame::BtnTeachClick(void)
{
	// 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return;
	}
	// 检查用户权限
	if (xPermissions::GetPermissions(PER_TEACH) == false)
	{
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (ScreenSaverUserManager() == 0)
		return;
	}
    if (pModbus->IsALFAMode())
        ChangeScreen(SCR_ALFAOPTION);
    else
        ChangeScreen(SCR_TEACH);
}
// 报警按钮
void DialogFrame::BtnAlmClick(void)
{
#if IS_XEDITOR
#else
	// 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return;
	}
	ChangeScreen(SCR_ALARM);
#endif
}
// 返回按钮
void DialogFrame::BtnEscClick(void)
{
	ChangeScreen(SCR_MAIN);
}
// *** 功能菜单画面按钮槽 ***
// 伺服参数
void DialogFrame::MenuServoClick(void)
{
	ChangeScreen(SCR_SERVO);
}
// 系统设置
void DialogFrame::MenuSystemClick(void)
{
	ChangeScreen(SCR_SYSTEM);
}
// 界面设置
void DialogFrame::MenuUiClick(void)
{
	ChangeScreen(SCR_UISETUP);
}
// 调位操作
void DialogFrame::MenuAdjClick(void)
{
	ChangeScreen(SCR_ADJUST);
}
// 厂商操作
void DialogFrame::MenuManufactClick(void)
{
	ChangeScreen(SCR_MANUFACTURER);
}
// 系统信息
void DialogFrame::MenuInfClick(void)
{
	ChangeScreen(SCR_INFORMATION);
}
// 系统日志
void DialogFrame::MenuLogClick(void)
{
	ChangeScreen(SCR_SYSTEMLOG);
}
// 使用配置
void DialogFrame::MenuOptionClick(void)
{
    ChangeScreen(SCR_OPTION);
}
// 进入变量初始化
void DialogFrame::MenuVarInitClick(void)
{
    ChangeScreen(SCR_VARINIT);
}
// 进入端口设置界面
void DialogFrame::MenuIOSetupClick(void)
{
    ChangeScreen(SCR_IOSETUP);
}

// *************************************************
// 窗口标题栏按钮槽
// *************************************************
// 执行原点操作
void DialogFrame::ReturnToOrigin(void)
{
#if IS_XEDITOR
#else
	// 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return;
	}
    // 检查当前窗口，如果是调位窗口，则不能进行原点复归
    if (pModbus->GetSysState() == SYS_STATE_JOG)
    {
        xMessageBox::DoWarning(tr("系统警告"), tr("调位状态下，不允许执行原点复归操作！"));
        return;
    }
	// 只有手动状态才能执行原点复归
	if (pModbus->GetSysState() != SYS_STATE_MANUAL)
		return;
	// 检查安全开关
    if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
	{
#if UI_SAFESW_TIP
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAFESW_TIP));
#endif
		return;
	}
	// 检查用户权限
	if (pUsrPerm->GetPermissions(PER_SRV_ORG) == false)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
		return;
	}
#if SELECT_SWITCH_USE
	// 检查选择开关
	if (pxKeyPad->GetSwitch() != CUSKEY_SEL_MANUAL)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SELSW_STOP));
		return;
	}
#endif

	// 检查机械手位置
    quint64 input;
    input = pModbus->GetInMain();
    if (xIoPort::GetIn(SV_VAR_IN_INMOLD) == true)
    {
        if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        {
            if (!xIoPort::GetIn(SV_VAR_IN_YWPOS))
            {
#if (FACTORY == FA_SHINI)
                xMessageBox::DoWarning(tr("系统警告"), tr("当机械手在模内并且手臂不在上位安全区域时，不允许执行原点复归操作！"));
                return;
#else
                if (xMessageBox::DoQuestion(tr("系统警告"), tr("机械手在模内并且手臂不在上位安全区域，确定要执行原点复归操作吗？")) != XMSG_RET_YES)
                    return;
#endif
            }
        }
        else
        {
            if (!xIoPort::GetIn(SV_VAR_IN_YWPOS) || (!xIoPort::GetIn(SV_VAR_IN_AWPOS)&& pModbus->GetRverSrvUse() && ((((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0))))
            {
#if (FACTORY == FA_SHINI)
                xMessageBox::DoWarning(tr("系统警告"), tr("当机械手在模内并且手臂不在上位安全区域时，不允许执行原点复归操作！"));
                return;
#else
                if (xMessageBox::DoQuestion(tr("系统警告"), tr("机械手在模内并且手臂不在上位安全区域，确定要执行原点复归操作吗？")) != XMSG_RET_YES)
                    return;
#endif
            }
        }
    }
#if (FACTORY == FA_VICTOR)//威特尔回原要检测开模完信号（加工完成）
    if (xIoPort::GetIn(IMM_VAR_IN_MOP) != true)
    {
		xMessageBox::DoWarning(tr("系统警告"), tr("没有加工完成，不允许执行原点复归操作！"));
        return;
    }
#endif
	// 开始执行原点复归操作
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	quint32 trvWaitPos = settings.value(XPAD_SET_TRVWAIT, 0).toUInt();
	bool hasrefer = pModbus->IsHasRefer(pModbus->GetHomeState());
    if(hasrefer)
    {
        if(pModbus->ManualHome(CMBProtocol::GetManualSpeed() * srvRelSpd /100.00) != SENDMSG_RET_ACK)
            return;
    }
    else
    {
        if(pModbus->ManualHome(0) != SENDMSG_RET_ACK)
            return;
    }
    isHoming = 1;
	// 显示等待复归完成消息框
    xMessageBox::DoHomeWaiting(tr("原点复归"));
//    xMessageBox::DoWaiting(pModbus, tr("原点复归"), tr("正在执行原点复归操作，\n请稍候..."));
/*    if (pModbus->GetTravelPos() != trvWaitPos)
    {
        if ((!hasrefer) && pModbus->IsHasRefer(pModbus->GetHomeState()))
        {
            if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
                return;
            if (pModbus->ManualPos(pModbus->GetManualSpeed(), SRV_TRV, trvWaitPos, SERVO_MODE_SAFE) != SENDMSG_RET_ACK)
                return;
            xMessageBox::DoWaiting(pModbus, tr("执行原点复归"), tr("横行轴正在返回待机位置，\n请稍候..."));
        }
    }*/
	isHoming = 0;
#endif
}
// 程序文件管理操作
void DialogFrame::programFiles(void)
{
	// 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return;
	}
	// 检查用户权限
	if ((pUsrPerm->GetPermissions(PER_CHG_PGM) == false) && (pUsrPerm->GetPermissions(PER_OPR_PGM) == false))
	{
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (ScreenSaverUserManager() == 0)
		return;
	}
	// 如果系统不在手动状态则不能进行程序文件管理操作
	if (pModbus->GetSysState() != SYS_STATE_MANUAL)
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("系统只能在手动状态下才能进行程序文件管理操作！"));
		return;
	}
	ChangeScreen(SCR_PROGRAMFILE);
}
// 用户管理操作
void DialogFrame::UserManager(void)
{
#if IS_XEDITOR
#else
	dlgUserManager->DoForm();
#endif
}
int DialogFrame::ScreenSaverUserManager(void)
{
#if IS_XEDITOR
#else
    return dlgUserManager->DoForm();
#endif
}
// 设置日期时间
void DialogFrame::SetupDateTime(void)
{
#if IS_XEDITOR
#else
	// 检查用户权限
	if (pUsrPerm->GetPermissions(PER_SET_TIME) == false)
	{
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (ScreenSaverUserManager() == 0)
		return;
	}
	dlgDateTime->DoForm();
#endif
}
// 设置伺服相对速度
void DialogFrame::SetupSpeed(void)
{
#if IS_XEDITOR
#else
	// 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return;
	}
	// 如果没有载入程序文件则警告并退出
    if (pModbus->IsALFAMode())
    {
        if (pModbus->GetAlfaPgmName().isEmpty())
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("没有载入程序文件，不能修改伺服全局速度设置！"));
            return;
        }
    }
    else
    {
        if (pModbus->GetCurPgmName().isEmpty())
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("没有载入程序文件，不能修改伺服全局速度设置！"));
            return;
        }
    }
	// 设置相对速度
	DialogSpeed spdDlg;
	if (spdDlg.DoForm(srvRelSpd, srvRelSpd) != QDialog::Accepted)
		return;
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	// 保存伺服相对速度
	settings.setValue(XPAD_SET_SRVSPD, srvRelSpd);
	settings.sync();
	CMBProtocol::SetSrvSpeed(srvRelSpd);
#if defined(Q_OS_LINUX)
	sync();
#endif
	ui->pushButtonSpd->setText(QString("%1%").arg(srvRelSpd));
	if (CMBProtocol::GetSysState() != SYS_STATE_AUTO)
		return;
	// 如果加载程序文件出错则警告并退出
    TeachTableModel pgmModel(false);
    if (pModbus->IsALFAMode())
    {
        AlfaModel alfa;
        if (alfa.LoadProgram(pModbus->GetAlfaPgmName()) == false)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("装载程序文件出错，不能修改伺服全局速度设置！"));
            return;
        }
        if (alfa.CreateRunPgm() < 0)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("向导生成运行程序出错！"));
            return;
        }

        if (pgmModel.LoadProgram(alfa.GetRunPgmName()) == false)
        {
            if (pgmModel.GetLastError() == LOADERROR_VERSION)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取程序版本出错，无法装载程序文件！"));
                return;
            }
            if (pgmModel.GetLastError() == LOADERROR_FORMAT)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取文件格式出错，无法装载程序文件！"));
                return;
            }
            if (pgmModel.GetLastError() == LOADERROR_FILE)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取程序文件出错，无法装载程序文件！"));
                return;
            }
        }
    }
    else
    {
        if (pgmModel.LoadProgram(pModbus->GetCurPgmName(true)) == false)
        {
            if (pgmModel.GetLastError() == LOADERROR_VERSION)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取程序版本出错，无法装载程序文件！"));
                return;
            }
            if (pgmModel.GetLastError() == LOADERROR_FORMAT)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取文件格式出错，无法装载程序文件！"));
                return;
            }
            if (pgmModel.GetLastError() == LOADERROR_FILE)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取程序文件出错，无法装载程序文件！"));
                return;
            }
        }
    }
	// 生成程序文件对应的机器代码并上传到主控模块
    int procid;
	quint32 codeCnt;
    // 生成程序文件机器代码
    for (procid=0; procid<MAX_PROCESS; procid++)
    {
        codeCnt = pgmModel.GenerateCodes(procid, globlecodes, globleparas);
        // 上传机器代码参数
        if (pModbus->WriteCodeParas(globleparas, procid*MAX_CODES, codeCnt) != SENDMSG_RET_ACK)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件参数到主控模块出错，不能修改伺服全局速度设置！\n请检查操作器和主控模块的通讯链路。"));
            return;
        }
    }
	// 更新主控模块当前程序
    if (pModbus->CommandUpdate(CMD_UPDATE_PARA1|CMD_UPDATE_PARA2|CMD_UPDATE_PARA3) != SENDMSG_RET_ACK)
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("主控模块更新当前程序失败，不能修改伺服全局速度设置！\n请检查操作器和主控模块的通讯链路。"));
		return;
    }
#endif
}

void DialogFrame::setSafeSwitchFlag(bool on)
{
	if (ui->svPhorPos->isEnabled())
		ui->svPhorPos->setFlat(on);
	else
		ui->svPhorPos->setFlat(false);
	if (ui->svPverPos->isEnabled())
		ui->svPverPos->setFlat(on);
	else
		ui->svPverPos->setFlat(false);
	if (ui->svTravPos->isEnabled())
		ui->svTravPos->setFlat(on);
	else
		ui->svTravPos->setFlat(false);
	if (ui->svRhorPos->isEnabled())
		ui->svRhorPos->setFlat(on);
	else
		ui->svRhorPos->setFlat(false);
	if (ui->svRverPos->isEnabled())
		ui->svRverPos->setFlat(on);
	else
		ui->svRverPos->setFlat(false);
	if (ui->svExtePos->isEnabled())
		ui->svExtePos->setFlat(on);
	else
		ui->svExtePos->setFlat(false);
#if (SELECT_SWITCH_USE)
	if (xLed->GetSwitch() == SELSW_STOP)
	{
		ui->pushButtonStatus->setIcon(QIcon(":img/32X32/Stop.png"));
        ui->pushButtonStatus->setText(tr("停止"));
	}
	else
#endif
	{
		if (on)
		{
            if (pModbus->GetRunState() == RUN_STATE_RUN)        //运行状态
            {
                if (pModbus->GetSysState() == SYS_STATE_MANUAL)
                {
                    ui->pushButtonStatus->setIcon(QIcon(":img/32X32/ManualGreen.png"));
                    ui->pushButtonStatus->setText(tr("手动"));
                }
                else if (pModbus->GetSysState() == SYS_STATE_AUTO)
                {
                    ui->pushButtonStatus->setText(tr("全自动"));
                }
            }
		}
		else
		{
            if(pModbus->GetRunState() == RUN_STATE_PAUSE)
            {
                if (pModbus->GetSysState() == SYS_STATE_MANUAL)
                {
                    ui->pushButtonStatus->setIcon(QIcon(":img/32X32/Manual.png"));
                    ui->pushButtonStatus->setText(tr("手动"));
                }
                else
                {
                    ui->pushButtonStatus->setText(tr("自动暂停"));
                }
            }
		}

	}
}
