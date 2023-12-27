#if defined(Q_WS_QWS)
#include <unistd.h>
#endif
#include <QSettings>
#include <QFile>
#include <QButtonGroup>
#include "cmbprotocol.h"
#include "xpermissions.h"
#include "dialogframe.h"
#include "xstringresource.h"
#include "xmessagebox.h"
#include "screensaver.h"
#include "buzzer.h"
#include "motor.h"
#include "safeswitch.h"
#include "xtranslator.h"
#include "xsystemlog.h"
#include "dialognumberpad.h"
#include "formuisetup.h"
#include "ui_formuisetup.h"
#include "QDebug"
#include "HalBoard.h"

extern HardwareInterface *board;
extern DialogFrame *pDialogMain;


Formuisetup::Formuisetup(CMBProtocol *modbus, QWidget *parent) :	QWidget(parent), ui(new Ui::Formuisetup)
{
	ui->setupUi(this);
	pModbus = modbus;
	// 组织语言按钮
	pRadioLan = new QButtonGroup;
	pRadioLan->addButton(ui->radioCHS, LAN_CHINESE_S);
	pRadioLan->addButton(ui->radioCHT, LAN_CHINESE_T);
    pRadioLan->addButton(ui->radioEN, LAN_ENGLISH);
    pRadioLan->addButton(ui->radioTurkish, LAN_TURKISH);
    pRadioLan->addButton(ui->radioViet, LAN_VIETNAM);
    pRadioLan->addButton(ui->radioRussian, LAN_RUSSIAN);
    pRadioLan->addButton(ui->radioPortugal, LAN_PORTUGAL);
    pRadioLan->addButton(ui->radioSpain, LAN_SPAIN);
    pRadioLan->addButton(ui->radioIndonesia, LAN_INDONESIA);
    // 连接信号槽
	connect(pRadioLan, SIGNAL(buttonClicked(int)), this, SLOT(lanChange(int)));
}

Formuisetup::~Formuisetup()
{
	delete ui;
	delete pRadioLan;
}

void Formuisetup::changeEvent(QEvent *e)
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

// 设置界面状态
void Formuisetup::setPermissions(void)
{
	ui->groupBoxLanguage->setEnabled(xPermissions::GetPermissions(PER_UI_SET));
	ui->groupBoxMonitor->setEnabled(xPermissions::GetPermissions(PER_UI_SET));
	ui->groupBoxFeedBack->setEnabled(xPermissions::GetPermissions(PER_UI_SET));
	ui->groupBoxSwitch->setEnabled(xPermissions::GetPermissions(PER_UI_SET));
}

bool Formuisetup::EnterForm(void)
{
	// 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return false;
	}
    // 检查用户权限
    if (xPermissions::GetPermissions(PER_UI_SET) == false)
    {
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (pDialogMain)
            if (pDialogMain->ScreenSaverUserManager() == 0)
        return false;
    }
    // 读取界面设置参数
	language = pModbus->GetLanguage();
	if (pRadioLan->button(language) == 0)
		language = LAN_CHINESE_S;
	pRadioLan->button(language)->setChecked(true);
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
    scrsaver = settings.value(XPAD_SET_SCRSVER, 300).toUInt();
	backlight = settings.value(XPAD_SET_BAKLIGHT, 9).toUInt();
	useKeyBell = settings.value(XPAD_SET_KEYBELL, true).toBool();
	useTouchBell = settings.value(XPAD_SET_TOUCHBELL, true).toBool();
	bellFreq = settings.value(XPAD_SET_BELLFREQ, 2).toUInt();
    useSwitchBtn = CMBProtocol::GetSwitchUse(); // settings.value(XPAD_SET_SWITCHUSE, true).toBool();
    checkAlwaysOn = CMBProtocol::GetAlwaysOn(); // settings.value(XPAD_SET_ALWAYSON, true).toBool();
	// 把参数设置到界面
	ui->BoxScrSaver->setValue(scrsaver);
	ui->BoxLight->setValue(backlight);
	ui->checkBell->setChecked(useKeyBell);
	ui->checkTouchBell->setChecked(useTouchBell);
	ui->BoxBellFreq->setValue(bellFreq);
	ui->checkSwitchUse->setChecked(useSwitchBtn);
	ui->checkAlwaysOn->setChecked(checkAlwaysOn);
    if (ui->checkSwitchUse->isChecked())
        ui->checkAlwaysOn->setEnabled(true);
    else
        ui->checkAlwaysOn->setEnabled(false);
	// 初始化界面显示状态
	setBellBox();
	// 根据用户权限设置界面状态
	setPermissions();
	// 连接信号槽
	connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 显示界面
//	show();
	return true;
}

bool Formuisetup::ExitForm(void)
{
	// 如果参数已经修改则提示是否保存参数
	if (isModified() == true)
	{
		int ret = xMessageBox::DoSaveTip(tr("系统提示"), xStringResource::GetString(STRRES_SAVETIP));
		if (ret == XMSG_RET_SAVE)
		{
			// 保存参数
			if (saveSettings() == false)
				return false;
		}
		else if (ret == XMSG_RET_NOSAVE)
		{
#if defined(Q_WS_QWS)
			// 恢复原来的背光亮度
			board->SetBacklight(backlight);
#endif
			// 恢复原来的语言设置
			xLan->SetLanguage(language);
		}
        else
			return false;
	}
	// 取消信号槽连接
	disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 隐藏界面
//	hide();
	return true;
}

// 当前登录用户更改槽
void Formuisetup::userChange(void)
{
	if (xPermissions::GetPermissions(PER_UI_SET) == false)
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
	setPermissions();
}
// 根据当前界面状态设置提示音频率设置部件状态
void Formuisetup::setBellBox(void)
{
	if ((ui->checkBell->isChecked() == false) && (ui->checkTouchBell->isChecked() == false))
	{
		ui->labelBellFreq->setEnabled(false);
		ui->BoxBellFreq->setEnabled(false);
	}
	else
	{
		ui->labelBellFreq->setEnabled(true);
		ui->BoxBellFreq->setEnabled(true);
	}
}

// 输入屏保时间槽
void Formuisetup::inputScrSaver(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxScrSaver->minimum(), ui->BoxScrSaver->maximum()) == QDialog::Accepted)
		ui->BoxScrSaver->setValue(value);
}
// 输入亮度设置槽
void Formuisetup::inputLight(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxLight->minimum(), ui->BoxLight->maximum()) == QDialog::Accepted)
		ui->BoxLight->setValue(value);
}
// 输入按键音频率槽
void Formuisetup::inputBellFreq(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxBellFreq->minimum(), ui->BoxBellFreq->maximum()) == QDialog::Accepted)
		ui->BoxBellFreq->setValue(value);
}

// 检查参数是否修改
bool Formuisetup::isModified(void)
{
	// 如果登录用户没有权限则直接返回没有修改
	if (xPermissions::GetPermissions(PER_UI_SET) == false)
		return false;
	// 检查参数是否修改
	parModify = 0;
	if (language != pRadioLan->checkedId())					parModify |= (1 << LOG_UI_LAN);
	if (scrsaver != ui->BoxScrSaver->value())				parModify |= (1 << LOG_UI_SCRSAVER);
	if (backlight != ui->BoxLight->value())					parModify |= (1 << LOG_UI_BKLIGHT);
	if (useKeyBell != ui->checkBell->isChecked())			parModify |= (1 << LOG_UI_KEYBELL);
	if (useSwitchBtn != ui->checkSwitchUse->isChecked())	parModify |= (1 << LOG_UI_SWITCHUSE);
	if (checkAlwaysOn != ui->checkAlwaysOn->isChecked())	parModify |= (1 << LOG_UI_ALWAYSON);
	if (useTouchBell != ui->checkTouchBell->isChecked())	parModify |= (1 << LOG_UI_TOUCHBELL);
	if (bellFreq != ui->BoxBellFreq->value())				parModify |= (1 << LOG_UI_BELLFREQ);
	if (parModify == 0)
		return false;
	else
		return true;
}

// 背光亮度设置改变
void Formuisetup::lightChange(int light)
{
    if (light < 0)
        light = 0;
    else if (light > 9)
        light = 9;
#if defined(Q_WS_QWS)

//    xSaver->setBackLight(light);
//	BOARD_TYPE board;
//	board.SetBacklight(light);
	board->SetBacklight(light);

#endif
}

// 语言设置信号槽
void Formuisetup::lanChange(int idx)
{
	xLan->SetLanguage(idx);
}

// 重新校准触摸屏信号槽
void Formuisetup::reCalibrate(void)
{
	int ret;
	ret = xMessageBox::DoQuestion(tr("系统提示"), tr("当触摸屏定位不准确的时候才需要重新校准触摸屏；\n确定要重新校准触摸屏吗？"));
	if (ret != XMSG_RET_YES)
		return;
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
// 保存参数设置
bool Formuisetup::saveSettings(void)
{
	if (pModbus->WriteLanguage(pRadioLan->checkedId()) != SENDMSG_RET_ACK)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAVE_PARA_ERROR));
		return false;
	}
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	settings.setValue(XPAD_SET_LANGUAGE, pRadioLan->checkedId());
	settings.setValue(XPAD_SET_SCRSVER, ui->BoxScrSaver->value());
	settings.setValue(XPAD_SET_BAKLIGHT, ui->BoxLight->value());
	settings.setValue(XPAD_SET_KEYBELL, ui->checkBell->isChecked());
	settings.setValue(XPAD_SET_ALWAYSON, ui->checkAlwaysOn->isChecked());
//    checkAlwaysOn = ui->checkAlwaysOn->isChecked();
//    CMBProtocol::SetAlwaysOn(checkAlwaysOn);
	settings.setValue(XPAD_SET_SWITCHUSE, ui->checkSwitchUse->isChecked());
    xSafeSw->UseSwitch(ui->checkSwitchUse->isChecked());
	settings.setValue(XPAD_SET_TOUCHBELL, ui->checkTouchBell->isChecked());
	settings.setValue(XPAD_SET_BELLFREQ, ui->BoxBellFreq->value());
	settings.sync();
#if defined(Q_WS_QWS)
    xSaver->setInterval(ui->BoxScrSaver->value());
	xBuzzer->SetKeyBellUsage(ui->checkBell->isChecked());
	xBuzzer->SetTouchBellUsage(ui->checkTouchBell->isChecked());
	board->SetBuzzer_Gear(ui->BoxBellFreq->value());
	board->SetBacklight(ui->BoxLight->value());
#endif
	// 写入系统日志
	quint16 logBuf[LOG_UIPAR_SIZE];
	logBuf[LOG_UI_LAN] = pRadioLan->checkedId();
	logBuf[LOG_UI_SCRSAVER] = ui->BoxScrSaver->value();
	logBuf[LOG_UI_BKLIGHT] = ui->BoxLight->value();
	logBuf[LOG_UI_KEYBELL] = ui->checkBell->isChecked();
	logBuf[LOG_UI_TOUCHBELL] = ui->checkTouchBell->isChecked();
	logBuf[LOG_UI_SWITCHUSE] = ui->checkSwitchUse->isChecked();
	logBuf[LOG_UI_ALWAYSON] = ui->checkAlwaysOn->isChecked();
	logBuf[LOG_UI_BELLFREQ] = ui->BoxBellFreq->value();
	logBuf[LOG_UIPAR_MODIFY] = parModify;
	xSysLog::AddRecord(SYSLOG_TYPE_UI, LOG_PAR_UI, QString(""), QByteArray((char*)logBuf, sizeof(logBuf)));
	xSysLog::SaveChange();
	return true;
}

void Formuisetup::acceptSettings(void)
{
	if (xPermissions::GetPermissions(PER_UI_SET) == false)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
		return;
	}
	if (isModified())
	{
		if (saveSettings() == false)
			return;
		language = pRadioLan->checkedId();
		scrsaver = ui->BoxScrSaver->value();
		backlight = ui->BoxLight->value();
		useKeyBell = ui->checkBell->isChecked();
		useTouchBell = ui->checkTouchBell->isChecked();
		useSwitchBtn = ui->checkSwitchUse->isChecked();
		checkAlwaysOn = ui->checkAlwaysOn->isChecked();
        CMBProtocol::SetAlwaysOn(checkAlwaysOn);
		bellFreq = ui->BoxBellFreq->value();
#if defined(Q_OS_LINUX)
		sync();
#endif
	}
	// 显示保存成功信息
#if UI_SAVED_TIP
	xMessageBox::DoInformation(tr("保存参数"), xStringResource::GetString(STRRES_HAS_SAVED));
#endif
}
// 安全开关使用状态改变
void Formuisetup::stateChange(int state)
{
	if (ui->checkSwitchUse->isChecked())
	{
        ui->checkAlwaysOn->setEnabled(true);
	}
	else
        ui->checkAlwaysOn->setEnabled(false);
}
