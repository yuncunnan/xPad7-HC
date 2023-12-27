#ifndef FORMBTNWAIT_H
#define FORMBTNWAIT_H

#include <QWidget>

namespace Ui {
class FormBtnWait;
}

class FormBtnWait : public QWidget
{
	Q_OBJECT

public:
    explicit FormBtnWait(QWidget *parent = 0);
    ~FormBtnWait();
    bool EnterForm(void);
    void init();
    int GetVar();
    int GetVar2(bool &isconst);
	int GetType();
	int GetInvalidSet(void);
	int GetTimeout();
    int GetTimevalid();
    void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormBtnWait *ui;
	quint16 inport;
    quint32 inport2;
    bool m_isconst;

private slots:
    void selectInport(void);
    void selectInport2(void);
    void inputDelay(void); 
    void inputValid(void);
};

#endif // FORMACTWAIT_H
