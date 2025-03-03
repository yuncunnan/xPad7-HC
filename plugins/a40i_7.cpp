// a40i_7.cpp
#include <fcntl.h>
#include "a40i_7.h"
#include <QFile>
#include <QDebug>
#include <QWSServer>
#include <QSocketNotifier>
#include <QStringList>
#if defined(Q_WS_QWS)
#include <linux/input.h>
#endif
#include "HardwareInterface.h"

#define EVE_MATRIX_KEY_A40  "/dev/input/event1"
#define EVE_ENCODER_A40		"/dev/input/event2"

#define CUSKEY_NULL			DEV_KEYPAD_MAX_A40_II

A40I_7::A40I_7(QObject *parent) : HardwareInterface(parent){}

A40I_7::~A40I_7(){}

const char* A40I_7::pFreq[Max_pFreq] =
{
	"30000",
	"60000",
	"90000"
};

const char * A40I_7::backLightTab[Max_backLightTab]=				//测试通过0~255由暗到亮,在小于40后基本不可见
{
	"0", "50",	"75", "100", "125",	"150", "175", "200", "225",	"250"
};

int A40I_7::m_fd_MATkey;
int A40I_7::m_fd_encode;

const quint32 A40I_7::keyCode[DEV_KEYPAD_MAX_A40_II] =
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


const quint8 A40I_7::MykeyCode[DEV_KEYPAD_MAX_A40_II - 2] =
{
	5,		// KEY_SCAN_HOME,
	6,		// KEY_SCAN_RUN,
	7,		// KEY_SCAN_TRVSUB,
	8,		// KEY_SCAN_LEFT1,
	9,		// KEY_SCAN_ASC1,
	10,		// KEY_SCAN_ROTHOR,
	16,		// KEY_SCAN_RELHOR,
	17,		// KEY_SCAN_LEFT2,
	18,		// KEY_SCAN_ASC2,
	19,		// KEY_SCAN_AUX,
	3,		// KEY_SCAN_STOP,
	2,		// KEY_SCAN_TRVADD,
	11,		// KEY_SCAN_RIGHT1,
	4,		// KEY_SCAN_DES1,
	13,		// KEY_SCAN_ROTVER,
	20,		// KEY_SCAN_RELVER,
	21,		// KEY_SCAN_RIGHT2,
	22		// KEY_SCAN_DES2,
};

void A40I_7::BuzzerInit()
{
	system("echo 5 > /sys/class/pwm/pwmchip0/export");
	system("echo 366300 > /sys/class/pwm/pwmchip0/pwm5/period");
	system("echo 183150 > /sys/class/pwm/pwmchip0/pwm5/duty_cycle");
	system("echo 100 > /sys/class/pwm/pwmchip0/pwm5/buzzer");
}

// A40I_7类实现的写入蜂鸣器开关的函数
void A40I_7::SetBuzzer()
{
	QFile Buzzer("/sys/class/pwm/pwmchip0/pwm5/enable");
	if(!Buzzer.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		qDebug() << "Unable to open Buzzer file";
		return;
	}
	Buzzer.write("1");
	Buzzer.close();
}

// A40I_7类实现的写入蜂鸣器频率的函数
void A40I_7::SetBuzzer_Gear(quint8 Buzzer_Gear)//Buzzer_Gear : 蜂鸣器频率
{
	static quint8 Buzzer_Gear_temp;
	if(Buzzer_Gear_temp==Buzzer_Gear)
		return;
	Buzzer_Gear_temp=Buzzer_Gear;
	QFile Buzzer("/sys/class/pwm/pwmchip0/pwm5/duty_cycle");
	if(!Buzzer.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		qDebug() << "Unable to open Buzzer_Gear file";
		return;
	}
	if(Buzzer_Gear <= Max_pFreq)
		Buzzer.write(pFreq[Buzzer_Gear-1]);
	Buzzer.close();
	qDebug()<<"buzzer duty_cycle:"<<pFreq[Buzzer_Gear-1];
}

void A40I_7::SetBacklight(quint8 light)	//light : 背光亮度
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

// A40I_7类实现的写入led灯内容的函数
void A40I_7::SetLED(quint8 Led_Name,bool Led_Status)
{
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

void A40I_7::xKey_Init()
{
	m_fd_MATkey = open(EVE_MATRIX_KEY_A40,O_RDONLY);
	m_fd_encode = open(EVE_ENCODER_A40,O_RDONLY);
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

void A40I_7::ReadKeys(bool Key_State){}

void A40I_7::xSafeSwitch_Init(){}


quint8 A40I_7::getKeyValue(quint8 key)
{
	quint8 ret = SAFE_SWITCH_OFF;
    QFile safeSwitch("/sys/devices/platform/soc@1c00000/soc@1c00000:gpio-keys/key_value");
	if (!safeSwitch.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Unable to open SafeSwitch file2:" << safeSwitch.errorString();
		return ret;
	}
	QTextStream in(&safeSwitch);
	QString content = in.readLine();  // 读取文件内容（假设文件只有一行）

    // 将内容按逗号分割
    QStringList values = content.split(',', QString::SkipEmptyParts);

    // 检查是否读取到足够的值
    if (values.size() < 3) {
        qDebug() << "Not enough values in the file.";
        return -1;
    }

	// 获取第几个值（索引为 key）
    QString thirdValue = values.at(key);
	safeSwitch.close();

	// 判断内容是否为 "1"
    if (thirdValue == "1") {
		ret = SAFE_SWITCH_ON;
    } else if (thirdValue == "0"){
		ret = SAFE_SWITCH_OFF;
	}
	else{
		qDebug() << "ReadSafeSwitch ERROR";
	}
    return ret;
}

quint8 A40I_7::ReadSafeSwitch()
{
    return getKeyValue(KEYSAFE);
}

quint8 A40I_7::ReadSelectSwitch()
{
    quint8 read0 = getKeyValue(KEYSEL0);
    quint8 read1 = getKeyValue(KEYSEL1);
    quint8 ret = 0xFF;
    if (read0 == SAFE_SWITCH_ON)
    {
        if (read1 == SAFE_SWITCH_OFF)
            ret = SELSW_MANUAL;
    }
    else if (read0 == SAFE_SWITCH_OFF)
    {
        if (read1 == SAFE_SWITCH_OFF)
            ret = SELSW_STOP;
        else if (read1 == SAFE_SWITCH_ON)
            ret = SELSW_AUTO;
    }
	return ret;
}

void A40I_7::readMATKeyData(int type)
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
		for(quint8 i = 0; i < DEV_KEYPAD_MAX_A40_II - 2; i++)
		{
			if(in_ev.code == MykeyCode[i])
			{
				if( (in_ev.value == VALUE_KEY_PRESS)&&(in_ev.type ==1))
				{
					if(cur_mat_key == i)
						return;
					if(cur_mat_key == CUSKEY_NULL)
					{
						cur_mat_key = i;
						qwsServer->sendKeyEvent(0, keyCode[cur_mat_key], Qt::KeypadModifier, KEY_PRESS, false);
					}
				}
				else if((in_ev.value == VALUE_KEY_RELESE)&&(in_ev.type ==1))
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

void A40I_7::readEncodeData(int type)
{
#if defined(Q_WS_QWS)
	struct input_event in_ev;
	static quint8 encoderfilter[2];
	if (sizeof(struct input_event) !=read(m_fd_encode, &in_ev, sizeof(struct input_event)))
	{
		qDebug() << "ENCODE_KEY open fail-----" <<  "code: " << in_ev.code << " value: " << in_ev.value <<"type"<<in_ev.type<< endl;
		return;
	}
	if(in_ev.value == VALUE_ENCODE_CCW)//ccw
	{
		encoderfilter[1] <<= 1;
		encoderfilter[1] |= 1;
	}
	else if(in_ev.value == VALUE_ENCODE_CW)//Cw
	{
		encoderfilter[0] <<= 1;
		encoderfilter[0] |= 1;
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

const char* A40I_7::get_MB_PORT() const		//A40I_7串口参数设置
{
	return "/dev/ttyS2";
}

QString A40I_7::get_Current() const
{
	return "/bin/";
}

QString A40I_7::get_xPad_upg() {
	return ".upg2";
}


