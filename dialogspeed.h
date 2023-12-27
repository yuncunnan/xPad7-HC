#ifndef DIALOGSPEED_H
#define DIALOGSPEED_H

#include <QDialog>

namespace Ui {
class DialogSpeed;
}

class DialogSpeed : public QDialog
{
	Q_OBJECT
	
public:
	explicit DialogSpeed(QWidget *parent = 0);
	~DialogSpeed();
	int DoForm(quint8 &speed, quint8 initSpd);
	
protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::DialogSpeed *ui;

private slots:
	void inputSpeed(void);
};

#endif // DIALOGSPEED_H
