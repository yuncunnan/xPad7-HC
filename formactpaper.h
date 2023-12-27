#ifndef FORMACTPAPER_H
#define FORMACTPAPER_H

#include <QWidget>
class QButtonGroup;

namespace Ui {
class FormActPaper;
}

class FormActPaper : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActPaper(QWidget *parent = 0);
    ~FormActPaper();
    int GetY();
    void SetY(int y);
    int GetSpeed();
    void SetSpeed(int speed);
    int GetDSpeed();
    void SetDSpeed(int dspeed);

    int GetDecVar();
    void SetDecVar(int var);
    int GetInVar();
    void SetInVar(int var);
    void SetAxes(quint8 axes);
    quint8 GetAxes(void);

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);
public slots:
    void AxesClick(int axes);

private:
    Ui::FormActPaper *ui;
	quint16 inSpd;
	quint16 inCheck;
	quint16 outCatch;
	void retranslateUi(void);			// 设置界面字符串资源
    QButtonGroup *pAxesBtn;

private slots:
	void inputHspd(void);
	void inputLspd(void);
	void selectInSpd(void);
	void selectInCheck(void);
    void inputPos(void);
    void syncPos(void);
};

#endif // FORMACTPAPER_H
