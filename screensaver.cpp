#include <QDebug>
#include <QWSServer>
#include <QSettings>
#include "xconfig.h"
//#include "xpermissions.h"
#include "screensaver.h"
#include "dialogframe.h"
#if defined(Q_OS_LINUX)
#include <sys/ioctl.h>
#include <fcntl.h>
#endif
#include "HalBoard.h"


extern DialogFrame *pDialogMain;
extern HardwareInterface *board;

#if defined(Q_WS_QWS)
ScreenSaver *xSaver = 0;

ScreenSaver::ScreenSaver(xPermissions *perm,FormBacklight *bklight)
{
	xSaver = this;
	pPerm = perm;
	pBklght = bklight;

	// 从配置文件中读取LCD背光亮度设置
	quint8 light;
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	light = settings.value(XPAD_SET_BAKLIGHT, 9).toUInt();
	// 设置LCD背光亮度
	board->SetBacklight(light);
	pBklght->ExitForm();
}

ScreenSaver::~ScreenSaver()
{
//	delete pBklght;
}

void ScreenSaver::InitScreenSaver(void)
{
	// 从配置文件中读取屏保时间设置
	quint32 scrsaver;
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	scrsaver = settings.value(XPAD_SET_SCRSVER, 300).toUInt();
	// 设置系统屏保
	qwsServer->setScreenSaver((QWSScreenSaver*)this);
	qwsServer->setScreenSaverInterval(scrsaver * 1000);
	qwsServer->setScreenSaverBlockLevel(0);
}

bool ScreenSaver::save(int level)
{
    if (level > 2)
        return false;
//	FILE *sp;
//	sp = fopen(DEV_LCD_BKLIGHT, "w");
//	if (sp != NULL)
//	{
//		fwrite("0", 1, 1, sp);
//	}
//	fclose(sp);
	if(pBklght)
	pBklght->EnterForm();

	return true;
}

// 设置屏保时间
void ScreenSaver::setInterval(int delay)
{
	qDebug()<<"*************** ScreenSaver::setInterval delay:"<<delay<<" ******************";
	qwsServer->setScreenSaverInterval(delay* 1000);//
}

void ScreenSaver::restore()
{
	if(pBklght)
		pBklght->ExitForm();
//	quint8 light;
//	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
//	light = settings.value(XPAD_SET_BAKLIGHT, 9).toUInt();
//	// 设置LCD背光亮度
//	board->SetBacklight(light);
}
#endif
