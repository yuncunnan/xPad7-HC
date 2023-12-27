#ifndef FORMACTPRO_H
#define FORMACTPRO_H

#include <QWidget>

class CMBProtocol;

namespace Ui {
class FormActPro;
}

class FormActPro : public QWidget
{
    Q_OBJECT
    
public:
	explicit FormActPro(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormActPro();
    void SetDelay(int delay);
    int GetDelay();
    void SetType(int type);
    int GetType();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActPro *ui;
	CMBProtocol *pModbus;

private slots:
	void inputDelay(void);
	void armVer(void);
	void armHor(void);
	void armJigR(void);
	void armJigB(void);
};

#endif // FORMACTPRO_H
