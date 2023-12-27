#ifndef FORMACTEXTIN_H
#define FORMACTEXTIN_H

#include <QWidget>

namespace Ui {
class FormActExtIn;
}

class FormActExtIn : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActExtIn(QWidget *parent = 0);
    ~FormActExtIn();
    void SetInterval(int interval);
    int GetInterval();
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
    Ui::FormActExtIn *ui;
	quint16 extInport;
	quint16 counter;

private slots:
	void selectPort(void);
	void inputInterval(void);
    void selectCounter(void);
};

#endif // FORMACTEXTIN_H
