#ifndef FORMACTWAIT_H
#define FORMACTWAIT_H

#include <QWidget>

namespace Ui {
class FormActWait;
}

class FormActWait : public QWidget
{
	Q_OBJECT

public:
	explicit FormActWait(QWidget *parent = 0);
	~FormActWait();
	int GetVar();
    int GetVar2(bool &isconst);
	void SetVar(int var);
    void SetVar2(int var, bool isconst);
	int GetType();
	void SetType(int type);
	int GetInvalidSet(void);
	void SetInvalidSet(int invalid);
	int GetTimeout();
    int GetTimevalid();
	void SetTimeOut(int timeout);
    void SetTimevalid(int timevalid);
    void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
	Ui::FormActWait *ui;
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
