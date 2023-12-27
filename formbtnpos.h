#ifndef FORMBTNPOS_H
#define FORMBTNPOS_H

#include <QWidget>

class QButtonGroup;

namespace Ui {
class FormBtnPos;
}

class FormBtnPos : public QWidget
{
	Q_OBJECT

public:
    explicit FormBtnPos(QWidget *parent = 0);
    ~FormBtnPos();
    bool EnterForm(void);
    void init(void);
    quint32 GetPaHorSpeed();
    quint32 GetPaVerSpeed();
    quint32 GetTrvSpeed();
    quint32 GetRaHorSpeed();
    quint32 GetRaVerSpeed();
    quint32 GetOtherSpeed();
    int GetAxes();
    int GetPaHorDelay();
    int GetPaVerDelay();
    int GetTrvDelay();
    int GetRaHorDelay();
    int GetRaVerDelay();
    int GetOtherDelay();

    int GetX();
	int GetY();
	int GetZ();
	int GetA();
	int GetB();
	int GetC();

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
    Ui::FormBtnPos *ui;
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
    void syncPaHorPos(void);
    void syncPaVerPos(void);
    void syncTrvPos(void);
    void syncRaHorPos(void);
    void syncRaVerPos(void);
    void syncExtPos(void);
    void inputPaHorSpeed(void);
    void inputPaVerSpeed(void);
    void inputTrvSpeed(void);
    void inputRaHorSpeed(void);
    void inputRaVerSpeed(void);
    void inputOtherSpeed(void);
    void inputPaHorDelay(void);
    void inputPaVerDelay(void);
    void inputTrvDelay(void);
    void inputRaHorDelay(void);
    void inputRaVerDelay(void);
    void inputOtherDelay(void);
    void inputPaHor(void);
	void inputPaVer(void);
	void inputTravel(void);
	void inputRaHor(void);
	void inputRaVer(void);
	void inputOther(void);
};

#endif // FORMACTPOS_H
