#ifndef FORMACTRUN_H
#define FORMACTRUN_H

#include <QWidget>

class CMBProtocol;

namespace Ui {
class FormActRun;
}

class FormActRun : public QWidget
{
    Q_OBJECT
    
public:
	explicit FormActRun(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormActRun();
	void SetDelay(int delay);
    int GetDelay();
    void SetType(int type);
    int GetType();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActRun *ui;
	CMBProtocol *pModbus;

private slots:
	void inputDelay(void);
	void armAdvRet(void);
	void armAscDes(void);
    void armRotHor(void);
    void armRotVer(void);
};

#endif // FORMACTRUN_H
