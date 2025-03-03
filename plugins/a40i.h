// a40i.h
#ifndef A40I_H
#define A40I_H
#include "HardwareInterface.h"

#define DEV_KEYPAD_MAX			18
// 按键数量
#define CUSKEY_NULL				DEV_KEYPAD_MAX

class A40i : public HardwareInterface
{
	Q_OBJECT
public:
	explicit A40i(QObject *parent = 0);
	~A40i();

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
	static const char *pFreq[3];
	static const int newFreq[3];
	static const char*backLightTab[10];
	static int freqidx;
    static int fd_safe_switch;

	static const char *devCfg[DEV_KEYPAD_MAX];
	static const char *devData[DEV_KEYPAD_MAX];
	static bool key_repeat[DEV_KEYPAD_MAX];
	static quint32 key_repeat_delay[DEV_KEYPAD_MAX];
	static quint32 key_repeat_interval[DEV_KEYPAD_MAX];
	static qint32 key_repeat_counter[DEV_KEYPAD_MAX];
	static quint8 key_vaild;

	static int fd[DEV_KEYPAD_MAX];
	static quint8 key[DEV_KEYPAD_MAX];
	static quint8 keyBak[DEV_KEYPAD_MAX];
	static quint8 Filter[DEV_KEYPAD_MAX];

    // 选择开关
    static int cfg0;
    static int cfg1;
    static int data0;
    static int data1;
public:
    static const quint32 keyCode[DEV_KEYPAD_MAX];

private:
    void selectSwitchInit();    // 选择开关初始化

};

#endif // A40I_H
