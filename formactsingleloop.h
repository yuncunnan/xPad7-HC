#ifndef FORMACTSINGLELOOP_H
#define FORMACTSINGLELOOP_H

#include <QWidget>
#include <QVector>

class QButtonGroup;
class xDoubleSpinBox;

namespace Ui {
class FormActSingleLoop;
}

class FormActSingleLoop : public QWidget
{
	Q_OBJECT

public:
    explicit FormActSingleLoop(QWidget *parent = 0);
    ~FormActSingleLoop();

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

    qint16 GetInterval();      // 间隔
    void SetInterval(qint16 interval);

    int GetFirstPos();          // 第一点位置
    void SetFirstPos(int pos);

    int GetDSpeed();	// 减速速度
    void SetDSpeed(int dspeed);
    int GetDLen();		// 减速距离
    void SetDLen(int len);


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
    void inputInterval(void);
    void inputLspd(void);
    void inputLdis(void);

private:
    Ui::FormActSingleLoop *ui;
	QVector<QString> strIdx;			// 页面标题
	quint16 userVar;
    QButtonGroup *pAxesBtn;

	void retranslateUi(void);			// 设置界面字符串资源
};

#endif // FORMACTSINGLELOOP_H
