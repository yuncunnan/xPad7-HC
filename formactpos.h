#ifndef FORMACTPOS_H
#define FORMACTPOS_H

#include <QWidget>

class QButtonGroup;

namespace Ui {
class FormActPos;
}

class FormActPos : public QWidget
{
	Q_OBJECT

public:
	explicit FormActPos(QWidget *parent = 0);
	~FormActPos();
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

public slots:
    void UpdateWidgetState(void);
	void AxesClick(int axes);

protected:
	void changeEvent(QEvent *e);

private:
	Ui::FormActPos *ui;
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

};

#endif // FORMACTPOS_H
