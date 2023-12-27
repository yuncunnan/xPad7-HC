#ifndef FORMACTEXTPOS_H
#define FORMACTEXTPOS_H

#include <QWidget>

class QButtonGroup;

namespace Ui {
class FormActExtPos;
}

class FormActExtPos : public QWidget
{
	Q_OBJECT

public:
	explicit FormActExtPos(QWidget *parent = 0);
	~FormActExtPos();
	void SetType(quint8 type);
	int GetType(void);
	quint32 GetSpeed();
	void SetSpeed(int speed);
	int GetAxes();
	void SetAxes(int axes);
	int GetX();
    void SetX(int pos, int type);
	int GetY();
    void SetY(int pos, int type);
	int GetZ();
    void SetZ(int pos, int type);
	int GetA();
    void SetA(int pos, int type);
	int GetB();
    void SetB(int pos, int type);
	int GetC();
    void SetC(int pos, int type);

    int GetXType(){return m_x_type;}
    int GetYType(){return m_y_type;}
    int GetZType(){return m_z_type;}
    int GetAType(){return m_a_type;}
    int GetBType(){return m_b_type;}
    int GetCType(){return m_c_type;}
    void SetDelay(int delay);
    int GetDelay();

    int GetAdvDec();//提前变速
    int GetAdvSpeed();//变速速度
    int GetAdvFinish();//提前结束
    int GetAdvDis();//变速距离
    int GetEndDis();// 结束距离
    int GetAccSpeed();//加速度
    int GetJerkSpeed();//jerk加加速

    void SetAdvDec(int dec);//提前变速
    void SetAdvSpeed(int speed);//变速速度
    void SetAdvFinish(int finish);//提前结束
    void SetAdvDis(int dist);//变速距离
    void SetEndDis(int dist); // 结束距离
    void SetAccSpeed(int speed);//加速度
    void SetJerkSpeed(int speed);//jerk加加速

public slots:
    void UpdateWidgetState(void);
	void AxesClick(int axes);

protected:
	void changeEvent(QEvent *e);

private:
	Ui::FormActExtPos *ui;
	QButtonGroup *pAxesBtn;
	void retranslateUi(void);			// 设置界面字符串资源
	int m_x_type;
	int m_y_type;
	int m_z_type;
	int m_a_type;
	int m_b_type;
	int m_c_type;
	
	int m_x_pos;
	int m_y_pos;
	int m_z_pos;
	int m_a_pos;
	int m_b_pos;
	int m_c_pos;

private slots:
	void inputSpeed(void);
	void inputPaHor(void);
	void syncPaHor(void);
	void inputPaVer(void);
	void syncPaVer(void);
	void inputTravel(void);
	void syncTravel(void);
	void inputRaHor(void);
	void syncRaHor(void);
	void inputRaVer(void);
	void syncRaVer(void);
	void inputOther(void);
	void syncOther(void);
	void inputDelay(void);
    void inputDeC(void);
    void inputAdvDis(void);
    void inputEndDis(void);
    void inputAcc(void);
    void inputJerk(void);

};

#endif // FORMACTEXTPOS_H
