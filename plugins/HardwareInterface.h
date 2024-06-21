#ifndef HARDWAREINTERFACE_H
#define HARDWAREINTERFACE_H
using namespace std;

#define Led_Run 1
#define Led_Err 2

#define KEY_RELEASE		0
#define KEY_PRESS		1

#define KEY_NULL			0

#define KEY_SCAN_HOME					(0x100+0)//回原
#define KEY_SCAN_RUN					(0x100+1)//运行
#define KEY_SCAN_TRVSUB					(0x100+2)//横行－－
#define KEY_SCAN_LEFT1					(0x100+3)//左１
#define KEY_SCAN_ASC1					(0x100+4)//上１
#define KEY_SCAN_ROTHOR					(0x100+5)//水平旋转(姿势-)
#define KEY_SCAN_RELHOR					(0x100+6)//水平相对位置(旋转－)
#define KEY_SCAN_LEFT2					(0x100+7)//左２
#define KEY_SCAN_ASC2					(0x100+8)//上２
#define KEY_SCAN_AUX					(0x100+9)//辅助
#define KEY_SCAN_STOP					(0x100+10)//停止
#define KEY_SCAN_TRVADD					(0x100+11)//横行＋＋
#define KEY_SCAN_RIGHT1					(0x100+12)//右１
#define KEY_SCAN_DES1					(0x100+13)//下１
#define KEY_SCAN_ROTVER					(0x100+14)//垂直旋转(姿势＋)
#define KEY_SCAN_RELVER					(0x100+15)//垂直相对旋转(旋转+)
#define KEY_SCAN_RIGHT2					(0x100+16)//右２
#define KEY_SCAN_DES2					(0x100+17)//下２
#define ENCODER_CW						 0x3C
#define ENCODER_CCW						 0x3B

#define VKEY_SCAN_DOOR_RESET			(0x100+50)//复位
#define VKEY_SCAN_DOOR_QUERY			(0x100+51)//查询

#include <QObject>

class HardwareInterface : public QObject
{
	Q_OBJECT
public:
	inline explicit HardwareInterface(QObject *parent = 0);
	inline virtual ~HardwareInterface();

	virtual void BuzzerInit()=0;
	virtual void SetBuzzer_Gear(quint8 Buzzer_Gear)=0;
	virtual void SetBuzzer() = 0;

	virtual void SetBacklight(quint8 light) = 0;
	virtual void SetLED(quint8 Led_Num, bool Led_Status) = 0;
	virtual void xKey_Init() = 0;
	virtual const char* get_MB_PORT() const = 0;
	virtual QString get_Current() const = 0;		//当前工作路径
	virtual QString get_xPad_upg()=0;

	virtual void ReadKeys(bool Key_State)=0;
};

HardwareInterface::HardwareInterface(QObject *parent)
	: QObject(parent)
{
	// 构造函数的具体实现代码
}

HardwareInterface::~HardwareInterface()
{

}
#endif // HARDWAREINTERFACE_H
