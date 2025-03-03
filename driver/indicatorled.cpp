#include <QDebug>
#include "xconfig.h"
#include "indicatorled.h"
#if defined(Q_OS_LINUX)
#include <sys/ioctl.h>
#include <fcntl.h>
#include <QFile>
#endif
#include "HalBoard.h"
#include "HardwareInterface.h"

IndicatorLed *xLed = 0;
extern HardwareInterface *board;

int IndicatorLed::fdData0 = -1;
int IndicatorLed::fdData1 = -1;

#define XLAMP_ON_TIME		3
#define XLAMP_OFF_TIME		3

#define LED_RUN				fdData0
#define LED_ALARM			fdData1


#define SELSW_PERIOD		5

quint8 IndicatorLed::swStatus0 = SELSW_STOP;
quint8 IndicatorLed::swStatus1 = SELSW_STOP;
quint8 IndicatorLed::swStatusBk = SELSW_STOP;

IndicatorLed::IndicatorLed(QObject *parent) : QObject(parent)
{
	xLed = this;
#if defined(Q_WS_QWS)
    // 配置指示灯设备
	board->SetLED(Led_Run,true);
	board->SetLED(Led_Err,true);

	quint8 setCfg = '1';
	fdData0 = open(DEV_LAMP_DATA0, O_RDWR);
	fdData1 = open(DEV_LAMP_DATA1, O_RDWR);
    setCfg = '0';
#endif
}

IndicatorLed::~IndicatorLed(void){}

quint8 IndicatorLed::ReadSwitch(void)
{
#if defined(Q_WS_QWS)
    // 读取周期判断
    static quint8 readPeriod = 0;
    readPeriod ++;
    if (readPeriod < SELSW_PERIOD)
        return swStatusBk;
    readPeriod = 0;
    swStatus0 = board->ReadSelectSwitch();
    if (swStatus0 == 0xFF)
        return SELSW_ERR;
    if (swStatus0 == swStatus1)
    {
        if (swStatusBk != swStatus0)
        {
            swStatusBk = swStatus0;
            emit SwitchChanged(swStatusBk);
        }
    }
    else
    {
        swStatus1 = swStatus0;
    }
    return swStatusBk;
#else
	return SELSW_STOP;
#endif
}
