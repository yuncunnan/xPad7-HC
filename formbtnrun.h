#ifndef FORMBTNRUN_H
#define FORMBTNRUN_H

#include <QWidget>

class CMBProtocol;

namespace Ui {
class FormBtnRun;
}

class FormBtnRun : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormBtnRun(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormBtnRun();
    bool EnterForm(void);
    void init();
    int GetDelay();
    int GetType();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormBtnRun *ui;
	CMBProtocol *pModbus;

private slots:
	void inputDelay(void);
	void armAdvRet(void);
	void armAscDes(void);
    void armRotHor(void);
    void armRotVer(void);
};

#endif // FORMBTNRUN_H
