#ifndef FORMVACTVACUUM_H
#define FORMVACTVACUUM_H

#include <QWidget>

class CMBProtocol;

namespace Ui {
class FormVActVacuum;
}

class FormVActVacuum : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormVActVacuum(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormVActVacuum();
    void SetInterval(int interval);
    int GetInterval();
    void SetDelay(int delay);
    int GetDelay();
    void SetType(int type);
    int GetType();
    void SetVar(int var);
    int GetVar();
    void SetInVar(int var);
    int GetInVar();
    void SetOutputCounter(quint16 var);
    quint16 GetOutputCounter();
    void SetInputCounter(quint16 var);
    quint16 GetInputCounter();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormVActVacuum *ui;
	CMBProtocol *pModbus;
    quint16 extOutport;
    quint16 extInport;
    quint16 outputcounter;
    quint16 inputcounter;

private slots:
    void selectPort(void);
    void selectPortIn(void);
    void inputDelay(void);
	void inputInterval(void);
	void extOutOn(void);
	void extOutOff(void);
};

#endif // FORMVACTVACUUM_H
