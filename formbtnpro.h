#ifndef FORMBTNPRO_H
#define FORMBTNPRO_H

#include <QWidget>

class CMBProtocol;

namespace Ui {
class FormBtnPro;
}

class FormBtnPro : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormBtnPro(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormBtnPro();
    bool EnterForm(void);
    void init();
    int GetDelay();
    int GetType();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormBtnPro *ui;
	CMBProtocol *pModbus;

private slots:
    void inputDelay(void);
	void armVer(void);
	void armHor(void);
	void armJigR(void);
	void armJigB(void);
};

#endif // FORMBTNPRO_H
