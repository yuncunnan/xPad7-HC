#ifndef FORMACTOPERATE_H
#define FORMACTOPERATE_H

#include <QWidget>

class QButtonGroup;

namespace Ui {
class FormActOperate;
}

class FormActOperate : public QWidget
{
	Q_OBJECT

public:
	explicit FormActOperate(QWidget *parent = 0);
	~FormActOperate();
	void SetVar(int var);
	int GetVar();
	void SetType(int type);
	int GetType();
    void SetPara(int para);
    int GetPara();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
	Ui::FormActOperate *ui;
	QButtonGroup *pOpr;
	quint16 usrVar;

private slots:
	void selectVar(void);
	void inputValue(void);
    void idChanged(int checkid);
};

#endif // FORMACTOPERATE_H
