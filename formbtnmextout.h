#ifndef FORMBTNMEXTOUT_H
#define FORMBTNMEXTOUT_H

#include <QWidget>

class CMBProtocol;

namespace Ui {
class FormBtnMExtOut;
}

class FormBtnMExtOut : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormBtnMExtOut(QWidget *parent = 0);
    ~FormBtnMExtOut();
    bool EnterForm(void);
    void init(void);
    int GetDelay();
    int GetInterval();
    int GetVar();
    int GetType();
    quint16 GetCounter();

    void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormBtnMExtOut *ui;
	quint16 extOutport;
	quint16 counter;
    void retranslateUi(void);			// 设置界面字符串资源

private slots:
    void selectPort(void);
    void inputDelay(void);
    void inputInterval(void);
//    void extOutOn(void);
//    void extOutOff(void);
};

#endif // FORMBTNMEXTOUT_H
