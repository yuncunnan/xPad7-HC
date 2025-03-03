#include <QSettings>
#include "xconfig.h"
#include "Buzzer.h"
#if defined(Q_OS_LINUX)
#include <sys/ioctl.h>
#include <fcntl.h>
#include <QDebug>
#include <QFile>
#endif

#include "HalBoard.h"
extern HardwareInterface *board;

Buzzer *xBuzzer = 0;

bool Buzzer::useKeyBell = false;
bool Buzzer::useTouchBell = false;

Buzzer::Buzzer(QObject *parent) : QObject(parent)
{
	xBuzzer = this;
#if defined(Q_WS_QWS)
	board->BuzzerInit();
	// 从配置文件中读取提示音设置
    QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
    useKeyBell = settings.value(XPAD_SET_KEYBELL, true).toBool();
    useTouchBell = settings.value(XPAD_SET_TOUCHBELL, true).toBool();
	// 设置提示音频率
	board->SetBuzzer_Gear(settings.value(XPAD_SET_BELLFREQ, 2).toUInt());
#endif
}

Buzzer::~Buzzer(void)
{
}

// 开启蜂鸣器
void Buzzer::Beep(void)
{
#if defined(Q_WS_QWS)
	board->SetBuzzer();
#endif
}

// 开启按键提示音
void Buzzer::KeyBeep(void)
{
	if (useKeyBell == false)
		return;
	Beep();
}

// 开启触屏提示音
void Buzzer::TouchBeep(void)
{
	if (useTouchBell == false)
		return;
	Beep();
}

void Buzzer::SetKeyBellUsage(bool use)
{
	useKeyBell = use;
}

void Buzzer::SetTouchBellUsage(bool use)
{
	useTouchBell = use;
}

