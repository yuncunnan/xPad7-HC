#ifndef FORMACTFOR_H
#define FORMACTFOR_H

#include <QWidget>

namespace Ui {
class FormActFor;
}

class FormActFor : public QWidget
{
	Q_OBJECT

public:
	explicit FormActFor(QWidget *parent = 0);
	~FormActFor();

	void SetValue(int value);
	int GetValue();
	void SetType(int type);
	int GetType();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
	Ui::FormActFor *ui;
	quint16 loopVar;

private slots:
	void selectVar(void);
	void inputConst(void);
};

#endif // FORMACTFOR_H
