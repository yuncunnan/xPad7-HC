#include <QDebug>
#include "xconfig.h"
#include "indicatorled.h"
#if defined(Q_OS_LINUX)
#include <sys/ioctl.h>
#include <fcntl.h>
#include <QFile>
#endif
#include <t113.h>
#include <a40i.h>

IndicatorLed *xLed = 0;
extern HardwareInterface *board;

int IndicatorLed::fdData0 = -1;
int IndicatorLed::fdData1 = -1;

int IndicatorLed::data0 = -1;
int IndicatorLed::data1 = -1;

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

	int fdCfg0 = -1,fdCfg1 = -1;
	quint8 setCfg = '1';
	fdData0 = open(DEV_LAMP_DATA0, O_RDWR);
	fdData1 = open(DEV_LAMP_DATA1, O_RDWR);
    setCfg = '0';
    // 打开选择开关设备
    fdCfg0 = open(DEV_SWITCH_CFG0, O_WRONLY);
    fdCfg1 = open(DEV_SWITCH_CFG1, O_WRONLY);
    if (fdCfg0 >= 0)
    {
		write(fdCfg0, &setCfg, sizeof(setCfg));
        close(fdCfg0);
    }
    if (fdCfg1 >= 0)
    {
		write(fdCfg1, &setCfg, sizeof(setCfg));
        close(fdCfg1);
    }
    data0 = open(DEV_SWITCH_DATA0, O_RDONLY);
    data1 = open(DEV_SWITCH_DATA1, O_RDONLY);
#endif
}

IndicatorLed::~IndicatorLed(void)
{
#if defined(Q_WS_QWS)
    if (fdData0 >= 0)
    {
        close(fdData0);
        fdData0 = -1;
    }
    if (fdData1 >= 0)
    {
        close(fdData1);
        fdData1 = -1;
    }

	if (data0 >= 0)
    {
        close(data0);
        data0 = -1;
    }
    if (data1 >= 0)
    {
        close(data1);
        data1 = -1;
    }

#endif
}

quint8 IndicatorLed::ReadSwitch(void)
{
#if defined(Q_WS_QWS)
    // 读取周期判断
    static quint8 readPeriod = 0;
    readPeriod ++;
    if (readPeriod < SELSW_PERIOD)
        return swStatusBk;
    readPeriod = 0;
    quint8 read0, read1;
	if (data0 < 0 || data1 < 0)
        return SELSW_STOP;
    // 读取选择开关设备
    lseek(data0, 0, SEEK_SET);
    read(data0, &read0, sizeof(read0));
    lseek(data1, 0, SEEK_SET);
    read(data1, &read1, sizeof(read1));
    // 判断选择开关位置
    swStatus0 = 0xFF;
    if (read0 == '1')
    {
        if (read1 == '0')
			swStatus0 = SELSW_MANUAL;
    }
    else if (read0 == '0')
    {
        if (read1 == '0')
			swStatus0 = SELSW_STOP;
        else if (read1 == '1')
			swStatus0 = SELSW_AUTO;
    }
    if (swStatus0 == 0xFF)
        return SELSW_STOP;

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
