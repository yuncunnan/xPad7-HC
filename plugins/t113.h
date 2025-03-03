// t113.h
#ifndef T113_H
#define T113_H
#include "HardwareInterface.h"

#define CUSKEY_HOME						0//回原
#define CUSKEY_RUN						1//运行
#define CUSKEY_TRVSUB					2//横行－－
#define CUSKEY_LEFT1					3//左１
#define CUSKEY_ASC1						4//上１
#define CUSKEY_ROTHOR					5//水平旋转(姿势-)
#define CUSKEY_RELHOR					6//水平相对位置(旋转－)
#define CUSKEY_LEFT2					7//左２
#define CUSKEY_ASC2						8//上２
#define CUSKEY_AUX						9//辅助
#define CUSKEY_STOP						10//停止
#define CUSKEY_TRVADD					11//横行＋＋
#define CUSKEY_RIGHT1					12//右１
#define CUSKEY_DES1						13//下１
#define CUSKEY_ROTVER					14//垂直旋转(姿势＋)
#define CUSKEY_RELVER					15//垂直相对旋转(旋转+)
#define CUSKEY_RIGHT2					16//右２
#define CUSKEY_DES2						17//下２
#define CUSKEY_CW						18//顺时针，编码器＋＋
#define CUSKEY_CCW						19//逆时针，编码器－－
#define DEV_KEYPAD_MAX_T113				20
#define Max_pFreq						3
#define Max_backLightTab				10

#define KEYSEL0                         0
#define KEYSEL1                         1
#define KEYSAFE                         2

class QSocketNotifier;

class T113 : public HardwareInterface
{
	Q_OBJECT

public:
	explicit T113(QObject *parent = 0);
	~T113();
	virtual void BuzzerInit();
	virtual void SetBuzzer();
	virtual void SetBuzzer_Gear(quint8 Buzzer_Gear);

	virtual void SetBacklight(quint8 light);
	virtual void SetLED(quint8 Led_Num,bool Led_Status);

	virtual const char* get_MB_PORT() const;
	virtual QString get_Current() const;
	virtual QString get_xPad_upg();

	virtual void xKey_Init();
	virtual void ReadKeys(bool Key_State);

    virtual void xSafeSwitch_Init();
    virtual quint8 ReadSafeSwitch(void);
	virtual quint8 ReadSelectSwitch(void);

private:
    quint8 getKeyValue(quint8 key);

public:
//	enum Key_code {
//		CODE_HOME	=5,
//		CODE_RUN	=6,		CODE_STOP   =3 ,
//		CODE_TRVSUB	=7,     CODE_TRVADD =2 ,
//		CODE_LEFT1	=8,     CODE_RIGHT1	=11,
//		CODE_ASC1	=9,     CODE_DES1   =4 ,
//		CODE_ROTHOR =10,    CODE_ROTVER =13,
//		CODE_RELHOR =16,    CODE_RELVER =20,
//		CODE_LEFT2  =17,    CODE_RIGHT2	=21,
//		CODE_ASC2	=18,    CODE_DES2   =22,
//		CODE_AUX    =19
//	};

	enum Key_value{
		VALUE_KEY_PRESS  = 0,
		VALUE_KEY_RELESE = 1
	};

	enum encode_value{
		VALUE_ENCODE_CW  = 1,
		VALUE_ENCODE_CCW = -1
	};

private slots:
	void readMATKeyData(int type);
	void readEncodeData(int type);

private:
	static const char *pFreq[Max_pFreq];
	static const char *backLightTab[Max_backLightTab];
	QSocketNotifier *m_notify_MATkey;
	QSocketNotifier *m_notify_encode;
	static int m_fd_MATkey;
	static int m_fd_encode;

public:
	static const quint32 keyCode[DEV_KEYPAD_MAX_T113];
	static const quint32 MykeyCode[DEV_KEYPAD_MAX_T113 - 2];

};
#endif // T113_H
