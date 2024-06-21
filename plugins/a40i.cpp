// a40i.cpp
#include "a40i.h"
#include <QFile>
#include <QDebug>
#if defined(Q_OS_LINUX)
#include <sys/ioctl.h>
#endif
#include <fcntl.h>

#include <QWSServer>
extern bool gnewVersion;

const char* A40i::pFreq[3] =
{
	"1000",
	"2000",
	"3000"
};
#define Max_pFreq 3
const int A40i::newFreq[3] = // 100-20000
{
	1000,
	2000,
	3000
};

const char* A40i::backLightTab[10] =
{
	"0", "50",	"75", "100", "125",	"150", "175", "200", "225",	"250"
};
#define Max_backLightTab 10

int A40i::freqidx = 0;

#define DEV_LCD_POWER			"/sys/devices/virtual/disp/disp/attr/lcd"

qint32 A40i::key_repeat_counter[DEV_KEYPAD_MAX];
quint8 A40i::key_vaild = 0xff;
int	   A40i::fd[DEV_KEYPAD_MAX];
quint8 A40i::key[DEV_KEYPAD_MAX];
quint8 A40i::keyBak[DEV_KEYPAD_MAX];
quint8 A40i::Filter[DEV_KEYPAD_MAX];
const char* A40i::devCfg[DEV_KEYPAD_MAX] =
{
	"/sys/class/gpio_xr/gpio04/cfg",
	"/sys/class/gpio_xr/gpio05/cfg",
	"/sys/class/gpio_xr/gpio06/cfg",
	"/sys/class/gpio_xr/gpio07/cfg",
	"/sys/class/gpio_xr/gpio08/cfg",
	"/sys/class/gpio_xr/gpio09/cfg",
	"/sys/class/gpio_xr/gpio10/cfg",
	"/sys/class/gpio_xr/gpio11/cfg",
	"/sys/class/gpio_xr/gpio12/cfg",
	"/sys/class/gpio_xr/gpio13/cfg",
	"/sys/class/gpio_xr/gpio14/cfg",
	"/sys/class/gpio_xr/gpio15/cfg",
	"/sys/class/gpio_xr/gpio16/cfg",
	"/sys/class/gpio_xr/gpio17/cfg",
	"/sys/class/gpio_xr/gpio18/cfg",
	"/sys/class/gpio_xr/gpio19/cfg",
	"/sys/class/gpio_xr/gpio20/cfg",
	"/sys/class/gpio_xr/gpio21/cfg",
};

const char* A40i::devData[DEV_KEYPAD_MAX] =
{
	"/sys/class/gpio_xr/gpio04/data",
	"/sys/class/gpio_xr/gpio05/data",
	"/sys/class/gpio_xr/gpio06/data",
	"/sys/class/gpio_xr/gpio07/data",
	"/sys/class/gpio_xr/gpio08/data",
	"/sys/class/gpio_xr/gpio09/data",
	"/sys/class/gpio_xr/gpio10/data",
	"/sys/class/gpio_xr/gpio11/data",
	"/sys/class/gpio_xr/gpio12/data",
	"/sys/class/gpio_xr/gpio13/data",
	"/sys/class/gpio_xr/gpio14/data",
	"/sys/class/gpio_xr/gpio15/data",
	"/sys/class/gpio_xr/gpio16/data",
	"/sys/class/gpio_xr/gpio17/data",
	"/sys/class/gpio_xr/gpio18/data",
	"/sys/class/gpio_xr/gpio19/data",
	"/sys/class/gpio_xr/gpio20/data",
	"/sys/class/gpio_xr/gpio21/data",
};

bool A40i::key_repeat[DEV_KEYPAD_MAX] =
{
	false,//KEY_SCAN_RIGHT1,
	false,//KEY_SCAN_TRVADD,
	false,//KEY_SCAN_STOP,
	false,//KEY_SCAN_DES1,
	false,//KEY_SCAN_HOME,
	false,//KEY_SCAN_RUN,
	false,//KEY_SCAN_TRVSUB,
	false,//KEY_SCAN_LEFT1,
	false,//KEY_SCAN_ASC1,
	false,//KEY_SCAN_ROTHOR,
	false,//KEY_SCAN_ROTVER,
	false,//KEY_SCAN_RELHOR,
	false,//KEY_SCAN_LEFT2,
	false,//KEY_SCAN_ASC2,
	false,//KEY_SCAN_AUX,
	false,//KEY_SCAN_RELVER,
	false,//KEY_SCAN_RIGHT2,
	false,//KEY_SCAN_DES2,
};

quint32 A40i::key_repeat_delay[DEV_KEYPAD_MAX] =
{
	20,//KEY_SCAN_RIGHT1,
	20,//KEY_SCAN_TRVADD,
	0,//KEY_SCAN_STOP,
	20,//KEY_SCAN_DES1,
	0,//KEY_SCAN_HOME,
	0,//KEY_SCAN_RUN,
	20,//KEY_SCAN_TRVSUB,
	20,//KEY_SCAN_LEFT1,
	20,//KEY_SCAN_ASC1,
	0,//KEY_SCAN_ROTHOR,
	0,//KEY_SCAN_ROTVER,
	0,//KEY_SCAN_RELHOR,
	20,//KEY_SCAN_LEFT2,
	20,//KEY_SCAN_ASC2,
	0,//KEY_SCAN_AUX,
	0,//KEY_SCAN_RELVER,
	20,//KEY_SCAN_RIGHT2,
	20,//KEY_SCAN_DES2,
};

quint32 A40i::key_repeat_interval[DEV_KEYPAD_MAX] =
{
	1,//KEY_SCAN_RIGHT1,
	1,//KEY_SCAN_TRVADD,
	0,//KEY_SCAN_STOP,
	1,//KEY_SCAN_DES1,
	0,//KEY_SCAN_HOME,
	0,//KEY_SCAN_RUN,
	1,//KEY_SCAN_TRVSUB,
	1,//KEY_SCAN_LEFT1,
	1,//KEY_SCAN_ASC1,
	0,//KEY_SCAN_ROTHOR,
	0,//KEY_SCAN_ROTVER,
	0,//KEY_SCAN_RELHOR,
	1,//KEY_SCAN_LEFT2,
	1,//KEY_SCAN_ASC2,
	0,//KEY_SCAN_AUX,
	0,//KEY_SCAN_RELVER,
	1,//KEY_SCAN_RIGHT2,
	1,//KEY_SCAN_DES2,
};
const quint32 A40i::keyCode[DEV_KEYPAD_MAX] =
{
	KEY_SCAN_RIGHT1,
	KEY_SCAN_TRVADD,
	KEY_SCAN_STOP,
	KEY_SCAN_DES1,
	KEY_SCAN_HOME,
	KEY_SCAN_RUN,
	KEY_SCAN_TRVSUB,
	KEY_SCAN_LEFT1,
	KEY_SCAN_ASC1,
	KEY_SCAN_ROTHOR,
	KEY_SCAN_ROTVER,
	KEY_SCAN_RELHOR,
	KEY_SCAN_LEFT2,
	KEY_SCAN_ASC2,
	KEY_SCAN_AUX,
	KEY_SCAN_RELVER,
	KEY_SCAN_RIGHT2,
	KEY_SCAN_DES2,
};


A40i::A40i(QObject *parent) : HardwareInterface(parent) {}

A40i::~A40i() {}

void A40i::BuzzerInit(){}

void A40i::SetBuzzer()
{
#if defined(Q_WS_QWS)
    if (gnewVersion)
	{
		int fd = open("/dev/xrpwm", O_WRONLY);
		if(fd<0)
			return;
		int time = 1;
		ioctl(fd, 0x51, &newFreq[freqidx]);
		// set pwmtime
		ioctl(fd, 0x53, &time);
		if (fd >= 0)
			close(fd);
	}
	else
	{
		QFile BuzzerTime("/sys/devices/platform/pwm_xinrui/pwmtime");
		if (BuzzerTime.open(QIODevice::WriteOnly))
		{
			BuzzerTime.write("2");
			qDebug() << "open BuzzerTime success";
			BuzzerTime.close();
		}
	}
#endif
}


void A40i::SetBuzzer_Gear(quint8 Buzzer_Gear)
{
	if(gnewVersion)
		freqidx=Buzzer_Gear;
	static quint8 Buzzer_Gear_temp;
	if(Buzzer_Gear_temp==Buzzer_Gear)
		return;
	Buzzer_Gear_temp=Buzzer_Gear;
	QFile Buzzer("/sys/devices/platform/pwm_xinrui/pwmfreq");
	if(!Buzzer.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		qDebug() << "Unable to open a40i buzzer-gear file2";
	}
	if(Buzzer_Gear <= Max_pFreq)
		Buzzer.write(pFreq[Buzzer_Gear-1]);
	Buzzer.close();
}

// 其他函数的实�?..

void A40i::SetBacklight(quint8 light)
{
	// 在A40i类中实现写入背光函数
	qDebug()<<"A40I_BOARD";
	QFile lcd_bl("/sys/devices/virtual/disp/disp/attr/lcd_bl");
	if(!lcd_bl.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		qDebug() << "Unable to open lcd_bl file";
		return;
	}
	if(light < Max_backLightTab)
		lcd_bl.write(backLightTab[light]);
	lcd_bl.close();
}

void A40i::SetLED(quint8 Led_Num,bool Led_Status)
{
	// 在A40i类中实现写入LCD类型函数
	if(Led_Num==Led_Run)
	{
		QFile ledRun("/sys/class/gpio_xr/gpio22/data");
		if(!ledRun.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			qDebug() << "Unable to open ledRun file2";
		}
		if(Led_Status)
			ledRun.write("0");
		else
			ledRun.write("1");
		ledRun.close();
		return;
	}
	if(Led_Num==Led_Err)
	{
		QFile ledRun("/sys/class/gpio_xr/gpio23/data");
		if(!ledRun.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			qDebug() << "Unable to open ledErr file2";
		}
		if(Led_Status)
			ledRun.write("0");
		else
			ledRun.write("1");
		ledRun.close();
		return;
	}
}

void A40i::xKey_Init()
{
	unsigned char set = '0';
	int fdCfg;
	// 初始化键盘驱动设�?
	for (quint8 i = 0; i < DEV_KEYPAD_MAX; i ++)
	{
		// 配置键盘端口
		fdCfg = -1;
		fdCfg = open(devCfg[i], O_WRONLY);
		if (fdCfg >= 0)
		{
			write(fdCfg, &set, sizeof(set));
			close(fdCfg);
		}
		// 配置键盘数据
		fd[i] = -1;
		fd[i] = open(devData[i], O_RDONLY);

		key[i] = keyBak[i] = KEY_RELEASE;
	}
}


void A40i::ReadKeys(bool Key_State)
{
#if defined(Q_WS_QWS)
	if(Key_State==true)
	{
		quint8 readBuf;
		for (quint8 i = 0; i < DEV_KEYPAD_MAX; i ++)
		{
			readBuf = '1';
			if (fd[i] < 0)
				continue;
			lseek(fd[i], 0, SEEK_SET);
			read(fd[i], &readBuf, sizeof(readBuf));
			key[i] = (readBuf == '0') ? KEY_PRESS : KEY_RELEASE;

			if (key[i] != keyBak[i])
			{
				char buf[30];
				memset(buf, 0, 30);
				keyBak[i] = key[i];
				FILE *sp;
				sp = fopen(DEV_LCD_POWER, "r");
				if (sp != NULL)
				{
					fread(buf, 20, 1, sp);
				}
				fclose(sp);

				if (keyBak[i] == KEY_PRESS)
				{
					if (buf[13] == 'n')
					{
						qwsServer->sendKeyEvent(0, keyCode[i], Qt::KeypadModifier, true, false);
						qDebug()<<"-------------001---------KEY_PRESS:"<<keyCode[i];
						if (key_repeat[i])
						{
							key_vaild = i;
							key_repeat_counter[i] = key_repeat_delay[i];
						}
					}
				}
				else
				{
					if (buf[13] == 'n')
					{
						qwsServer->sendKeyEvent(0, keyCode[i], Qt::KeypadModifier, false, false);
						qDebug()<<"-------------002---------KEY_REPRESS:"<<keyCode[i];
						if (key_repeat[i])
						{
							key_vaild = 0xff;
						}
					}
					else
					{
						qwsServer->sendKeyEvent(0, -1, Qt::KeypadModifier, true, false);
						qDebug()<<"-------------003---------KEY_PRESS:-1";
					}
				}
			}
			else
			{
				if (key_repeat[i]&&(key_vaild==i)&&(key[i] == KEY_PRESS))
				{
					key_repeat_counter[i]--;
					if (key_repeat_counter[i]<=0)
					{
						qwsServer->sendKeyEvent(0, keyCode[i], Qt::KeypadModifier, true, true);
						qDebug()<<"-------------004---------KEY_PRESS:"<<keyCode[i];

						qwsServer->sendKeyEvent(0, keyCode[i], Qt::KeypadModifier, false, true);
						qDebug()<<"-------------005---------KEY_REPRESS:"<<keyCode[i];

						key_repeat_counter[i] = key_repeat_interval[i];
					}
				}
			}
		}
	}
	else
	{
		for (quint8 i = 0; i < DEV_KEYPAD_MAX; i ++)
		{
			if (fd[i] >= 0)
			{
				close(fd[i]);
				fd[i] = -1;
			}
		}
	}
#endif
}


const char* A40i::get_MB_PORT() const
{
	//串口参数设置
	return "/dev/ttyS2";
}

QString A40i::get_xPad_upg()
{
	return ".upg2";
}

QString A40i::get_Current() const		//当前工作路径
{
	return "/usr/xPad/";
}

