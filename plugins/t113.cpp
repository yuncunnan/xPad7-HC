// t113.cpp
#include <fcntl.h>
#include "t113.h"
#include <QFile>
#include <QDebug>
#include <QWSServer>
#include <QSocketNotifier>

#if defined(Q_WS_QWS)
#include <linux/input.h>
#endif
#include "HardwareInterface.h"

#define EVE_MATRIX_KEY  "/dev/input/event1"
#define EVE_ENCODER		"/dev/input/event2"

#define CUSKEY_NULL						DEV_KEYPAD_MAX_T113

T113::T113(QObject *parent) : HardwareInterface(parent){}

T113::~T113()
{
	// T113类的析构函数
}

#define Max_pFreq 3
const char* T113::pFreq[Max_pFreq] =
{
	"40000",
	"80000",
	"120000"
};

#define Max_backLightTab 10
const char * T113::backLightTab[Max_backLightTab]=
{
	"255", "200","175", "150", "125", "100", "75", "50", "20", "0"
};

int T113::m_fd_MATkey;
int T113::m_fd_encode;

const quint32 T113::keyCode[DEV_KEYPAD_MAX_T113] =
{
	KEY_SCAN_HOME,
	KEY_SCAN_RUN,
	KEY_SCAN_TRVSUB,
	KEY_SCAN_LEFT1,
	KEY_SCAN_ASC1,
	KEY_SCAN_ROTHOR,
	KEY_SCAN_RELHOR,
	KEY_SCAN_LEFT2,
	KEY_SCAN_ASC2,
	KEY_SCAN_AUX,
	KEY_SCAN_STOP,
	KEY_SCAN_TRVADD,
	KEY_SCAN_RIGHT1,
	KEY_SCAN_DES1,
	KEY_SCAN_ROTVER,
	KEY_SCAN_RELVER,
	KEY_SCAN_RIGHT2,
	KEY_SCAN_DES2,
	ENCODER_CW,
	ENCODER_CCW
};

const quint32 T113::MykeyCode[DEV_KEYPAD_MAX_T113 - 2] =
{
	5,	// KEY_SCAN_HOME,
	6,	// KEY_SCAN_RUN,
	7,	// KEY_SCAN_TRVSUB,
	8,	// KEY_SCAN_LEFT1,
	9,	// KEY_SCAN_ASC1,
	10,	// KEY_SCAN_ROTHOR,
	16,	// KEY_SCAN_RELHOR,
	17,	// KEY_SCAN_LEFT2,
	18,	// KEY_SCAN_ASC2,
	19,	// KEY_SCAN_AUX,
	3,	// KEY_SCAN_STOP,
	2,	// KEY_SCAN_TRVADD,
	11,	// KEY_SCAN_RIGHT1,
	4,	// KEY_SCAN_DES1,
	13,	// KEY_SCAN_ROTVER,
	20,	// KEY_SCAN_RELVER,
	21,	// KEY_SCAN_RIGHT2,
	22,	// KEY_SCAN_DES2,
	//	ENCODER_CW,
	//	ENCODER_CCW
};

void T113::BuzzerInit()
{
	system("echo 0 > /sys/class/pwm/pwmchip0/export");
	system("echo 366300 > /sys/class/pwm/pwmchip0/pwm0/period");
	system("echo 183150 > /sys/class/pwm/pwmchip0/pwm0/duty_cycle");
	system("echo 100 > /sys/class/pwm/pwmchip0/pwm0/buzzer");
}

void T113::SetBuzzer()	//Buzzer_Status : 蜂鸣器开关状态
{
	// T113类实现的写入蜂鸣器开关的函数
	QFile Buzzer("/sys/class/pwm/pwmchip0/pwm0/enable");
		if(!Buzzer.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			qDebug() << "Unable to open ledRun file2";
			return;
		}
		Buzzer.write("1");
		Buzzer.close();
}

void T113::SetBuzzer_Gear(quint8 Buzzer_Gear)		//Buzzer_Gear : 蜂鸣器频率
{
	// T113类实现的写入蜂鸣器频率的函数
	static quint8 Buzzer_Gear_temp;
	if(Buzzer_Gear_temp==Buzzer_Gear)
		return;
	Buzzer_Gear_temp=Buzzer_Gear;
	QFile Buzzer("/sys/class/pwm/pwmchip0/pwm0/duty_cycle");
	if(!Buzzer.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		qDebug() << "Unable to open ledRun file2";
	}
	if(Buzzer_Gear <= Max_pFreq)
	{
		Buzzer.write(pFreq[Buzzer_Gear-1]);
	}
	Buzzer.close();
}

void T113::SetBacklight(quint8 light)	//light : 背光亮度
{
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

void T113::SetLED(quint8 Led_Name,bool Led_Status)
{
	// T113类实现的写入led灯内容的函数
	if(Led_Name==Led_Run)
	{
		QFile ledRun("/sys/class/leds/LED0_KEY/brightness");
		if(!ledRun.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			qDebug() << "Unable to open ledRun file2";
		}
		if(Led_Status)
			ledRun.write("1");
		else
			ledRun.write("0");
		ledRun.close();
		return;
	}
	if(Led_Name==Led_Err)
	{
		QFile ledRun("/sys/class/leds/LED1_KEY/brightness");
		if(!ledRun.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			qDebug() << "Unable to open ledErr file2";
		}
		if(Led_Status)
			ledRun.write("1");
		else
			ledRun.write("0");
		ledRun.close();
		return;
	}
}

void T113::xKey_Init()
{
	m_fd_MATkey = open(EVE_MATRIX_KEY,O_RDONLY);
	m_fd_encode = open(EVE_ENCODER,O_RDONLY);
	if(m_fd_MATkey>0)
	{
		m_notify_MATkey = new QSocketNotifier(m_fd_MATkey, QSocketNotifier::Read, this);
		connect(m_notify_MATkey, SIGNAL(activated(int)), this, SLOT(readMATKeyData(int)));
	}
	if(m_fd_encode>0)
	{
		m_notify_encode = new QSocketNotifier(m_fd_encode, QSocketNotifier::Read, this);
		connect(m_notify_encode, SIGNAL(activated(int)), this, SLOT(readEncodeData(int)));
	}
}

void T113::ReadKeys(bool Key_State){}

void T113::readMATKeyData(int type)
{
#if defined(Q_WS_QWS)
	struct input_event in_ev;
	static int cur_mat_key = CUSKEY_NULL;
	if (sizeof(struct input_event) !=read(m_fd_MATkey, &in_ev, sizeof(struct input_event)))
	{
		qDebug() << "MAT_KEY Exit-----" <<  "code: " << in_ev.code << " value: " << in_ev.value <<"type"<<in_ev.type<< endl;
		return;
	}
	if(in_ev.type == 1)
	{
		for(quint8 i = 0; i < DEV_KEYPAD_MAX_T113 - 2; i++)
		{
			if(in_ev.code == MykeyCode[i])
			{
				if( (in_ev.value == 0)&&(in_ev.type ==1))
				{
					if(cur_mat_key == i)
						return;
					if(cur_mat_key == CUSKEY_NULL)
					{
						cur_mat_key = i;
						qwsServer->sendKeyEvent(0, keyCode[cur_mat_key], Qt::KeypadModifier, KEY_PRESS, false);
					}
				}
				else if((in_ev.value == 1)&&(in_ev.type ==1))
				{
					qwsServer->sendKeyEvent(0, keyCode[cur_mat_key], Qt::KeypadModifier, KEY_RELEASE, false);
					cur_mat_key = CUSKEY_NULL;
				}
				break;
			}
		}
	}
#endif

}

void T113::readEncodeData(int type)
{
#if defined(Q_WS_QWS)
	struct input_event in_ev;
	static quint8 encoderfilter[2];
	if (sizeof(struct input_event) !=read(m_fd_encode, &in_ev, sizeof(struct input_event)))
	{
		qDebug() << "ENCODE_KEY open fail-----" <<  "code: " << in_ev.code << " value: " << in_ev.value <<"type"<<in_ev.type<< endl;
		return;
	}
	if(in_ev.value == -1)//ccw
	{
		encoderfilter[1]<<=1;
		encoderfilter[1]|=1;
	}
	else if(in_ev.value == 1)//Cw
	{
		encoderfilter[0]<<=1;
		encoderfilter[0]|=1;
	}
	if((encoderfilter[0] & 3) == 3)
	{
		qwsServer->sendKeyEvent(0, keyCode[CUSKEY_CW], Qt::KeypadModifier, KEY_PRESS, false);
		encoderfilter[0] = 0;
	}
	if((encoderfilter[1] & 3) == 3)
	{
		qwsServer->sendKeyEvent(0, keyCode[CUSKEY_CCW], Qt::KeypadModifier, KEY_PRESS, false);
		encoderfilter[1] = 0;
	}
#endif

}

const char* T113::get_MB_PORT() const		//T113串口参数设置
{
	return "/dev/ttyS1";
}

QString T113::get_Current() const
{
	return "/bin/";
}

QString T113::get_xPad_upg()
{
	return ".upg2";
}
