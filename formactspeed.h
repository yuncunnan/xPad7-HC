#ifndef FORMACTSPEED_H
#define FORMACTSPEED_H

#include <QWidget>

namespace Ui {
class FormActSpeed;
}

class FormActSpeed : public QWidget
{
	Q_OBJECT

public:
    explicit FormActSpeed(QWidget *parent = 0);
    ~FormActSpeed();
	quint32 GetSpeed();
	void SetSpeed(int speed);
	int GetAxes();
	void SetAxes(int axes);

public slots:
	void UpdateWidgetState(void);

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActSpeed *ui;
	void retranslateUi(void);			// 设置界面字符串资源

private slots:
	void inputSpeed(void);
};

#endif // FORMACTSPEED_H
