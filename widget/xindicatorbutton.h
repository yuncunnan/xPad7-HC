#ifndef XINDICATORBUTTON_H
#define XINDICATORBUTTON_H

#include <QPushButton>

class xIndicatorButton : public QPushButton
{
	Q_OBJECT
	Q_PROPERTY(QIcon iconOn READ iconOn WRITE setIconOn)
	Q_PROPERTY(QIcon iconOff READ iconOff WRITE setIconOff)
	Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
	Q_PROPERTY(bool On READ on WRITE setOn)

protected:
	void mousePressEvent(QMouseEvent *e);
    virtual bool hitButton(const QPoint &pos) const;

public:
	xIndicatorButton(QWidget *parent = 0);
	void setIconOn(const QIcon &newIconOn);
	QIcon iconOn(void) const { return onIcon; }
	void setIconOff(const QIcon &newIconOff);
	QIcon iconOff(void) const { return offIcon; }
	void setOn(const bool newStatus);
	bool on(void) const { return status; }

private:
	QIcon onIcon;
	QIcon offIcon;
	bool status;
};

#endif
