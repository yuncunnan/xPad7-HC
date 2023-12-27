#ifndef DIALOGFRAME1_H
#define DIALOGFRAME1_H

#include <QtGlobal>
#include <QDialog>
#include <QVector>
#include "cmbprotocol.h"
#include "xpermissions.h"

class QButtonGroup;

class FormWallpaper;
class FormAuto;
class FormManual;
class Formmenu;
class FormAlarm;
class Formservo;
class Formuisetup;
class Formsystem;
class FormAdjust;
class FormManufacturer;
class Forminformation;
class FormPgmExplorer;
class FormAlfaPgmExplorer;
class FormTeach;
class FormSysLog;
class FormOption;
class FormEditOption;
class FormVarInit;
class FormIO;
class Formalfaoption;

class DialogServoControl;
class DialogUserManager;
class DialogDateTime;

#define SCR_MAIN			0
#define SCR_AUTO			1
#define SCR_MANUAL			2
#define SCR_MENU			3
#define SCR_TEACH			4
#define SCR_ALARM			5
#define SCR_SERVO			6
#define SCR_UISETUP			7
#define SCR_ADJUST			8
#define SCR_SYSTEM			9
#define SCR_MANUFACTURER	10
#define SCR_INFORMATION		11
#define SCR_PROGRAMFILE		12
#define SCR_SYSTEMLOG		13
#define SCR_OPTION			14
#define SCR_VARINIT         15
#define SCR_IOSETUP         16
#define SCR_ALFAOPTION      17

#define SCR_MAX				18

namespace Ui {
class DialogFrame;
}

class DialogFrame : public QDialog
{
	Q_OBJECT
	
public:
	explicit DialogFrame(CMBProtocol *modbus, xPermissions *usrPerm, QWidget *parent = 0);
	~DialogFrame();
    void CWCCWKeyHandler(quint32 key);
    int ScreenSaverUserManager(void);

protected:
	bool eventFilter(QObject *obj, QEvent *event);
	void changeEvent(QEvent *e);
//	void paintEvent(QPaintEvent *e);

signals:
	void userChange(void);
	void LogModelUpdate(void);

private:
	Ui::DialogFrame *ui;
	xPermissions *pUsrPerm;

	// *** 定义各个窗口画面 ***
	FormWallpaper *Wallpaper;
	FormAuto *ScreenAuto;
	FormManual *ScreenManual;
	Formmenu *ScreenMenu;
	Formservo *ScreenServo;
	Formsystem *ScreenSystem;
	Formuisetup *ScreenUiSetup;
	FormAdjust *ScreenAdjust;
	FormManufacturer *ScreenManufacturer;
	Forminformation *ScreenInformation;
	FormAlarm *ScreenAlarm;
	FormPgmExplorer *ProgramFile;
    FormAlfaPgmExplorer *AlfaProgramFile;
	FormTeach *TeachProgram;
	FormSysLog *SystemLog;
	FormOption *Option;
    FormEditOption *EditOption;
    FormVarInit *VarInit;
    FormIO *IOSetup;
    Formalfaoption *Alfaoption;
	unsigned int curScreen;					// 当前窗口索引
	void ChangeScreen(unsigned int scrID, bool force = false);	// 切换窗口
    bool HideShowScreen(unsigned int scrID, bool force = false);	// 先隐藏后显示窗口

	// *** 定义各个对话框 ***
	DialogServoControl *ServoCtrl;
	DialogUserManager *dlgUserManager;
	DialogDateTime *dlgDateTime;

private:
	CMBProtocol *pModbus;					// Modbus 协议对象
	bool ComState;							// 当前通讯状态
	QTimer *pClockTimer;					// 时钟定时器
#if defined(Q_WS_QWS)
	QTimer *pKeyTimer;						// 按键定时器
#endif
	QVector<quint32> keyVector;				// 键盘按键数组
	QButtonGroup *pBtnSv;					// 伺服控制按钮组
	quint8 srvRelSpd;						// 伺服相对速度
	QString strPhor, strPver, strTrv, strRhor, strRver, strExt;
	int funKeys[4];
	quint16 bakhome[HOME_DEF_MAX];
	quint16 home[HOME_DEF_MAX];
	quint8 isHoming;						// 是否正在原點歸位
    quint8 m_key_servo_opr;                 // 正在按键操作的伺服
	bool calFlag;							// 校准按键标志

	void fixtureKey(int key);
    void keyRelease(QKeyEvent *event);			// 按键弹起事件处理函数
    void keyPress(QKeyEvent *event);			// 按键事件处理函数
    void extOutCtrl(quint16 code);			// 执行治具控制指令
	void retranslateUI(void);				// 设置界面字符串资源
	void setAlarmDisplay(void);				// 设置界面报警信息显示
	void setWinTitle(void);					// 根据当前界面设置标题
	void setSysState(uint16_t sysState, uint16_t runState, uint16_t runType);
	void setSafeSwitchFlag(bool on);

    bool checkManual(void);                 // 按键事件检查安全
	static bool runled_state;

private slots:
	// 当前程序改变槽
	void curPgmChange(QString name);
	// 时钟信号槽
	void clockUpdate(void);
#if defined(Q_WS_QWS)
	void keyUpdate(void);
#endif
	// 当前用户改变信号槽
	void slotChangeUser(void);
	// 安全开关关闭信号槽
	void safeSwitchOff(void);
	// 安全开关开启信号槽
	void safeSwitchOn(void);
	// 选择开关改变信号槽
	void switchChanged(quint8 status);
	// 系统状态改变信号槽
	void SvReferState(uint16_t state);
	void sysStateChanged(uint16_t state);
	void runStateChanged(uint16_t state);
	void runTypeChanged(uint16_t type);
    void PhorPosChanged(qint32 pos);
    void PverPosChanged(qint32 pos);
    void TrvaPosChanged(qint32 pos);
    void RverPosChanged(qint32 pos);
    void RhorPosChanged(qint32 pos);
    void ExtePosChanged(qint32 pos);
    void PhorSrvUseChanged(void);
    void ExtSrvUseChanged(void);
    void RhorSrvUseChanged(void);
	void RverSrvUseChanged(void);
   void AlfamodeChanged(void);
	// 伺服控制信号槽
	void svBtnClick(int id);
	// 报警状态改变信号槽
    void slot_AlmChg(qint16 idx, quint32 alarm);
	// 系统消息状态轮询信号槽
    void slot_MsgPoll(quint32 msg);
	// 界面操作信号槽
	void BtnAutoClick(void);
	void BtnManualClick(void);
	void BtnMenuClick(void);
	void BtnTeachClick(void);
	void BtnAlmClick(void);
	void BtnEscClick(void);
	void MenuServoClick(void);
	void MenuSystemClick(void);
	void MenuUiClick(void);
	void MenuAdjClick(void);
	void MenuInfClick(void);
	void MenuManufactClick(void);
	void MenuLogClick(void);
	void MenuOptionClick(void);
    void MenuVarInitClick(void);
    void MenuIOSetupClick(void);

	void ReturnToOrigin(void);
	void programFiles(void);
	void UserManager(void);
	void SetupDateTime(void);
	void SetupSpeed(void);

	void ReturnMain(void);
    void btnStatusClick(void);
    void ServoKeyFun(quint8 ServoID, qint32 pos, bool ccw);
};

#endif // DIALOGFRAME1_H
