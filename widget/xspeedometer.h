#ifndef XSPEEDOMETER_H
#define XSPEEDOMETER_H

#include <QWidget>

class xSpeedometer : public QWidget
{
	Q_OBJECT
public:
	explicit xSpeedometer(QWidget *parent = 0);
	
public slots:
	void SetSpeed(int var);

protected:
	void paintEvent(QPaintEvent *);

private:
	quint8 speed;
	void draw(QPainter *painter);
};

#endif // XSPEEDOMETER_H
