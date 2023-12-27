#include <fcntl.h>
#include <QSettings>
#include "xconfig.h"
#include "safeswitch.h"
#include "cmbprotocol.h"
#include <QDebug>

SafeSwitch *xSafeSw = 0;

int SafeSwitch::fd = -1;
quint8 SafeSwitch::keyState = SAFE_SWITCH_OFF;
quint8 SafeSwitch::keyStateBak = SAFE_SWITCH_OFF;

SafeSwitch::SafeSwitch(QObject *parent) : QObject(parent)
{
	xSafeSw = this;
#if defined(Q_WS_QWS)
	// 打开安全开关驱动设备
    unsigned char set = '0';
    // 设置安全开关驱动设备
    fd = open(DEV_SAFESWITCH_CFG, O_WRONLY);
    if (fd >= 0)
    {
        write(fd, &set, sizeof(set));
        close(fd);
        fd = -1;
    }
    fd = open(DEV_SAFESWITCH_DATA, O_RDONLY);
#endif
	// 初始化安全开关状态
	keyState = keyStateBak = ReadSwitch();
}

SafeSwitch::~SafeSwitch(void)
{
#if defined(Q_WS_QWS)
	if (fd >= 0)
		close(fd);
#endif
}

quint8 SafeSwitch::GetSafeSwState(void)
{
//	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
//    if (!settings.value(XPAD_SET_SWITCHUSE, true).toBool()) return SAFE_SWITCH_ON;
    if (!CMBProtocol::GetSwitchUse()) return SAFE_SWITCH_ON;
    return keyState;
}

quint8 SafeSwitch::ReadSwitch(void)
{
#if defined(Q_WS_QWS)
	if (fd < 0)
		return SAFE_SWITCH_OFF;
    quint8 key;
    lseek(fd, 0, SEEK_SET);
    read(fd, &key, sizeof(key));
    if (key=='0')
        keyState = SAFE_SWITCH_ON;
    else
        keyState = SAFE_SWITCH_OFF;

    if (keyState != keyStateBak)
    {
        keyStateBak = keyState;
        QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
        if (!settings.value(XPAD_SET_SWITCHUSE, true).toBool())
        {
            emit SafeSwitchOn();
        }
        else
        {
            if (keyState == SAFE_SWITCH_ON)
                emit SafeSwitchOn();
            else
                emit SafeSwitchOff();
        }
    }
#else
    keyStateBak = keyState = SAFE_SWITCH_ON;
#endif
	return keyState;
}

void SafeSwitch::UseSwitch(bool use)
{
    CMBProtocol::SetSwitchUse(use);
    if(use)
    {
        if (keyState == SAFE_SWITCH_ON)
            emit SafeSwitchOn();
        else
            emit SafeSwitchOff();
    }
    else
    {
        emit SafeSwitchOn();
    }
}
