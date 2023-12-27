#ifndef XPUSHBUTTON_H
#define XPUSHBUTTON_H

#include <QPushButton>

class xPushButton : public QPushButton
{
	Q_OBJECT
public:
	explicit xPushButton(QWidget *parent = 0);
	
signals:
	
public slots:

protected:
	void focusOutEvent(QFocusEvent *event);
	void mousePressEvent(QMouseEvent *e);
    virtual bool hitButton(const QPoint &pos) const;
};

#endif // XPUSHBUTTON_H
