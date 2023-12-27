#ifndef FORMACTLOOPFREE_H
#define FORMACTLOOPFREE_H

#include <QWidget>
#include <QVector>
#include "cmbprotocol.h"

class QButtonGroup;
class xDoubleSpinBox;

namespace Ui {
class FormActLoopFree;
}

class FormActLoopFree : public QWidget
{
	Q_OBJECT

public:
	explicit FormActLoopFree(QWidget *parent = 0);
	~FormActLoopFree();
	quint32 GetSpeed();		// 运行速度
    void SetSpeed(int speed);
	int GetDSpeed();	// 减速速度
	void SetDSpeed(int dspeed);
	int GetDLen();		// 减速距离
	void SetDLen(int len);
	int GetRotate();	// 定位时倒角状态
	void SetRotate(int rotate);
	int GetXDec();		// 引拔轴作为减速轴
	void SetXDec(int xdec);

    int GetPosCount();
	void SetPosCount(int count);

    int GetPos(int axisidx, int posidx);
    void SetPos(int axisidx, int posidx, int position);

    bool GetIsRunner(void); // 是否副臂
    void SetIsRunner(int isrunner);
    bool GetTrvRot(void); // 横行自动倒角
    void SetTrvRot(int trvrot);
    void SetVar(quint16 var);
	quint16 GetVar();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private slots:
	void pageUp(void);
	void pageDwn(void);
	void inputCnt(void);
	void inputHspd(void);
	void inputLspd(void);
	void inputLdis(void);
    void syncHorPos(void);
    void syncVerPos(void);
    void syncTrvPos(void);
    // 输入位置信号槽
    void inputHorPos(void);
    void inputVerPos(void);
    void inputTrvPos(void);
    void selectUser(void);
    void isRunnerClick(void);

private:
	Ui::FormActLoopFree *ui;
	quint16 userVar;

    quint32 pos[MAX_LOOP_AXIS][MAX_LOOP_POINTS];
    quint8 currentPos;
	void retranslateUi(void);			// 设置界面字符串资源
};

#endif // FORMACTLOOPFREE_H
