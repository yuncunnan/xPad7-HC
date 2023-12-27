#ifndef FORMACTEXTOUT_H
#define FORMACTEXTOUT_H

#include <QWidget>

class CMBProtocol;

namespace Ui {
class FormActExtOut;
}

class FormActExtOut : public QWidget
{
    Q_OBJECT
    
public:
	explicit FormActExtOut(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormActExtOut();
    void SetInterval(int interval);
    int GetInterval();
    void SetDelay(int delay);
    int GetDelay();
    void SetType(int type);
    int GetType();
    void SetVar(int var);
    int GetVar();
    void SetCounter(quint16 var);
    quint16 GetCounter();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActExtOut *ui;
	CMBProtocol *pModbus;
	quint16 extOutport;
	quint16 counter;

private slots:
    void selectPort(void);
	void inputDelay(void);
	void inputInterval(void);
	void extOutOn(void);
	void extOutOff(void);
};

#endif // FORMACTEXTOUT_H
