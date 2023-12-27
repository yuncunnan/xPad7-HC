#ifndef FORMACTINTERP_H
#define FORMACTINTERP_H

#include <QWidget>

namespace Ui {
class FormActInterp;
}

class FormActInterp : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActInterp(QWidget *parent = 0);
    ~FormActInterp();
	virtual void setVisible(bool visible);

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

public slots:
	void UpdateWidgetState(void);

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActInterp *ui;
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
	void checkClick(void);
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
};

#endif // FORMACTINTERP_H
