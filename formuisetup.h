#ifndef FORMUISETUP_H
#define FORMUISETUP_H

#include <QWidget>
#include <QVector>
#include "cmbprotocol.h"

class QPixmap;
class QButtonGroup;

namespace Ui {
class Formuisetup;
}

class Formuisetup : public QWidget
{
	Q_OBJECT
	
public:
	explicit Formuisetup(CMBProtocol *modbus, QWidget *parent = 0);
	~Formuisetup();
	
	bool EnterForm(void);
	bool ExitForm(void);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::Formuisetup *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
	quint16 parModify;						// 参数修改标志
	QButtonGroup *pRadioLan;				// 语言按钮组
	quint8 language;						// 系统语言
	quint16 scrsaver;						// 屏保时间
	quint8 backlight;						// 背光亮度
	bool useKeyBell;						// 使用按键音
	bool useTouchBell;						// 使用触屏音
	bool useSwitchBtn;						// 安全开关使用
	bool checkAlwaysOn;						// 安全开关一直按
	quint8 bellFreq;						// 按键音频率
	void setPermissions(void);				// 设置界面状态
	bool isModified(void);					// 检查参数是否修改
	bool saveSettings(void);				// 保存设置

private slots:
	void userChange(void);					// 当前登录用户更改槽
	void setBellBox(void);					// 根据当前界面状态设置提示音频率设置部件状态
	void inputScrSaver(void);				// 输入屏保时间
	void inputLight(void);					// 输入亮度设置
	void inputBellFreq(void);				// 输入按键音频率
	void lightChange(int light);			// 背光亮度设置改变
	void lanChange(int idx);				// 语言设置信号槽
	void reCalibrate(void);					// 重新校准触摸屏信号槽
	void acceptSettings(void);				// 保存参数设置信号槽
	void stateChange(int state);			// 安全开关使用状态改变
};

#endif // FORMUISETUP_H
