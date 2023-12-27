#ifndef FORMACTLOOPMATRIX_H
#define FORMACTLOOPMATRIX_H

#define ORDER_MODE_XYZ	0x80
#define ORDER_MODE_XZY	0x81
#define ORDER_MODE_YXZ	0x82
#define ORDER_MODE_YZX	0x83
#define ORDER_MODE_ZXY	0x84
#define ORDER_MODE_ZYX	0x85


#include <QWidget>

namespace Ui {
class FormActLoopMatrix;
}

class FormActLoopMatrix : public QWidget
{
	Q_OBJECT

public:
	explicit FormActLoopMatrix(QWidget *parent = 0);
	~FormActLoopMatrix();
    bool EnterForm(bool isinsert = false);

	quint32 GetSpeed();		// 运行速度
	void SetSpeed(int speed);
    quint32 GetHorSpeed();  //
    void SetHorSpeed(int speed);
    quint32 GetTrvSpeed();
    void SetTrvSpeed(int speed);
	int GetDSpeed();	// 减速速度
	void SetDSpeed(int dspeed);
	int GetDLen();		// 减速距离
	void SetDLen(int len);
	int GetRotate();	// 是否侧姿
	void SetRotate(int rotate);
	int GetXDec();		// 引拔轴作为减速轴
	void SetXDec(int xdec);
    int GetFirstDec();	// 定位模式
	void SetFirstDec(int fdec);

    bool GetIsRunner(void); // 是否副臂
    void SetIsRunner(int isrunner);
    bool GetTrvRot(void); // 横行自动倒角
    void SetTrvRot(int trvrot);

	int GetConveyor_delay();	// 输送带延时
	void SetConveyor_delay(int delay);
	int GetConveyor_out();	// 输送带端口
	void SetConveyor_out(int out);
    bool GetConveyor_use();	// 输送带端口
    void SetConveyor_use(bool use);

	void SetVar(quint16 var);
	quint16 GetVar();

	int GetX(int idx);
	void SetX(int idx, int x);
	int GetY(int idx);
	void SetY(int idx, int y);
	int GetZ(int idx);
	void SetZ(int idx, int z);

	void UpdateWidgetState();
    quint8 Axis[3];
    void UpdateTab();                                               // 根据数组内容，刷新TAB函数
    QString TranslateAxis(quint8 Step) ;                            // 解析轴名称
    bool MoveTab(quint8 currentselect, quint8 last_range);			// 调整轴顺序

protected:
	void hideEvent(QHideEvent *event);
	void changeEvent(QEvent *e);

private:
	Ui::FormActLoopMatrix *ui;
	void retranslateUi(void);			// 设置界面字符串资源
	quint16 userVar;
    quint16 extOutport;

private slots:
    void AxisGoDown(void);					// 向下一项
    void AxisGoUp(void);					// 向上一项

	void inputHorCnt(void);
	void inputVerCnt(void);
	void inputTrvCnt(void);
	void inputHorInt(void);
	void inputVerInt(void);
	void inputTrvInt(void);
	void inputHorPos(void);
	void inputVerPos(void);
	void inputTrvPos(void);
	void syncHorPos(void);
	void syncVerPos(void);
	void syncTrvPos(void);
	void inputHspd(void);
    void inputHorspd(void);
    void inputTrvspd(void);
	void inputLspd(void);
	void inputLdis(void);
    void selectUser(void);
    void selectPort();
    void inputDelay(void);
    void converorUse();
    void isRunnerClick();

};

#endif // FORMACTLOOPMATRIX_H
