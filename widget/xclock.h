#ifndef XCLOCK_H
#define XCLOCK_H

#include <QWidget>

class QTimer;

class xClock : public QWidget
{
	Q_OBJECT
public:
	explicit xClock(QWidget *parent = 0);
	~xClock();
	
	void StartClock(bool start);

protected:
	void paintEvent(QPaintEvent *);

private:
	QTimer *pTimer;
	void draw(QPainter *painter);

};

#endif // XCLOCK_H
