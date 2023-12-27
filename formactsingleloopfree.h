#ifndef FORMACTSINGLELOOPFREE_H
#define FORMACTSINGLELOOPFREE_H

#include <QWidget>
#include <QVector>
#include "cmbprotocol.h"

class QButtonGroup;
class xDoubleSpinBox;

namespace Ui {
class FormActSingleLoopFree;
}

class FormActSingleLoopFree : public QWidget
{
	Q_OBJECT

public:
    explicit FormActSingleLoopFree(QWidget *parent = 0);
    ~FormActSingleLoopFree();

    quint8 GetSpeed();          // 运行速度
    void SetSpeed(quint8 speed);

    quint8 GetAxes();          // 得到轴号
    void SetAxes(quint8 idx);

	quint16 GetVar();          // counter
	void SetVar(quint16 var);

    quint16 GetPosCount();          // 点数
    void SetPosCount(quint16 count);

      quint8 GetTimes();          // 每次点数
    void SetTimes(quint8 times);

  int GetDSpeed();	// 减速速度
    void SetDSpeed(int dspeed);
    int GetDLen();		// 减速距离
    void SetDLen(int len);

    int GetPos(int idx);
    void SetPos(int idx, int position);

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

public slots:
    void AxesClick(int axes);

private slots:
	void inputCnt(void);
	// 输入引拔位置信号槽
    void inputPos(void);
    void inputHspd(void);
    void selectVar(void);
    void inputTimes(void);
    void inputLspd(void);
    void inputLdis(void);
    void posPrev(void);
    void posNext(void);
    void syncPos(void);
private:
    Ui::FormActSingleLoopFree *ui;
	QVector<QString> strIdx;			// 页面标题
	quint16 userVar;
    QButtonGroup *pAxesBtn;
    quint32 pos[MAX_SINGLELOOPFREE_POINTS];
    quint8 currentPos;

	void retranslateUi(void);			// 设置界面字符串资源
};

#endif // FORMACTSINGLELOOPFREE_H
