#include <fcntl.h>
#include <QSettings>
#include "xconfig.h"
#include "safeswitch.h"
#include "cmbprotocol.h"
#include <QDebug>
#include "HalBoard.h"
#include "HardwareInterface.h"

extern HardwareInterface *board;

SafeSwitch *xSafeSw = 0;

quint8 SafeSwitch::keyState = SAFE_SWITCH_OFF;
quint8 SafeSwitch::keyStateBak = SAFE_SWITCH_OFF;

SafeSwitch::SafeSwitch(QObject *parent) : QObject(parent)
{
    xSafeSw = this;
#if defined(Q_WS_QWS)
    // 初始化安全开关状态
    if(board)
        keyState = keyStateBak = board->ReadSafeSwitch();
    else
        qDebug()<<"SafeSwitch::SafeSwitch board is NULL";
#endif
}

SafeSwitch::~SafeSwitch(void){}

quint8 SafeSwitch::GetSafeSwState(void)
{
//	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
//    if (!settings.value(XPAD_SET_SWITCHUSE, true).toBool()) return SAFE_SWITCH_ON;
    if (!CMBProtocol::GetSwitchUse()) return SAFE_SWITCH_ON;
    return keyState;
}

quint8 SafeSwitch::ReadSafeSwitch(void)
{
#if defined(Q_WS_QWS)
    keyState = board->ReadSafeSwitch();

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
