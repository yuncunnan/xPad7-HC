#ifndef DIALOGSERVOCONTROL_H
#define DIALOGSERVOCONTROL_H

#include <QDesktopWidget>
#include <QDialog>
#include "cmbprotocol.h"

class QButtonGroup;

namespace Ui {
class DialogServoControl;
}

class DialogServoControl : public QDialog
{
	Q_OBJECT
    
public:
	explicit DialogServoControl(CMBProtocol *modbus, QWidget *parent = 0);
	~DialogServoControl();

	int DoForm(uint8_t curServo, bool svSet, quint32 Pver, quint32 Rver, quint32 trv, quint32 ext, quint32 disHomP_R, quint32 MinDisP_R);
//	quint8 GetServoSpd(void);			// 得到伺服手动速度

protected:
	void changeEvent(QEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QTimer * m_ptimer;
    bool m_havesendservocmd;

    Ui::DialogServoControl *ui;
    CMBProtocol *pModbus;
	uint8_t CurServoIdx;				// 当前控制的伺服索引
	bool ServoSetup;					// 伺服参数设置标志
	QString strTitleSuffix;				// 标题字符串显示后缀
	QButtonGroup *pSrvAxies;			// 伺服轴选择按钮组
	quint32 paHorSafeBegin;				// 正臂模内安全区起点
	quint32 paHorSafeEnd;				// 正臂模内安全区终点
	quint32 paVerWaitPos;				// 正臂模内上位待机点
	quint32 paVerCatPos;				// 正臂模内下行取物点
	quint32 raHorSafeBegin;				// 副臂模内安全区起点
	quint32 raHorSafeEnd;				// 副臂模内安全区终点
	quint32 raVerWaitPos;				// 副臂模内上位待机点
	quint32 raVerCatPos;				// 副臂模内下行取物点
	quint32 trvCatPos;					// 横行模内取物点
	quint32 trvRelPos;					// 横行模外置物点
	quint32 MinDisP_RLen;
	quint32 PverLen;
	quint32 disHomP_RLen;
	quint32 RverLen;
	quint32 TrvLen;
	quint32 ExtLen;
	bool posChanged;						// 设置参数修改标志
	bool checkManual(void);
    QVector<quint32> keyVector;				// 键盘按键数组
    void retranslateUi(void);				// 更新界面字符串翻译
public:
	void keyRelease(quint32 key);			// 按键弹起事件处理函数

private slots:
	bool setCurServo(void);				// 设置当前伺服轴
	void SvMoveCcw(void);					// 伺服反向运行
	void SvMoveCw(void);					// 伺服正向运行
    void SvMoveCwStop(void);				// 伺服运行停止
    void SvMoveCcwStop(void);				// 伺服运行停止
    void SvShiftCcw(void);				// 伺服反向微调
	void SvShiftCw(void);					// 伺服正向微调
	void SafeInputChg(void);	// 安全区检测信号槽
	void inputSpeed(void);				// 输入手动速度
	void inputShift(void);				// 输入微调距离
	// 快速定位槽
	void toPaHorSafeBegin(void);
	void toPaHorSafeEnd(void);
	void toPaVerWaitPos(void);
	void toPaVetCatPos(void);
	void toRaHorSafeBegin(void);
	void toRaHorSafeEnd(void);
	void toRaVerWaitPos(void);
    void toRaVerCatPos(void);
	void toTrvCatPos(void);
	void toTrvRelPos(void);

    void StopTimer(void);
};

#endif // DIALOGSERVOCONTROL_H
