#include "buzzer.h"
#include "xindicatorbutton.h"

xIndicatorButton::xIndicatorButton(QWidget *parent) : QPushButton(parent), onIcon(), offIcon()
{
	status = false;
}

void xIndicatorButton::mousePressEvent(QMouseEvent *e)
{
	xBuzzer->TouchBeep();
	QPushButton::mousePressEvent(e);
}

void xIndicatorButton::setIconOn(const QIcon &newIconOn)
{
	onIcon = newIconOn;
	if (status)
		setIcon(onIcon);
}

void xIndicatorButton::setIconOff(const QIcon &newIconOff)
{
	offIcon = newIconOff;
	if (!status)
		setIcon(offIcon);
}

void xIndicatorButton::setOn(const bool newStatus)
{
	if (status == newStatus)
		return;
	status = newStatus;
	if (status)
		setIcon(onIcon);
	else
		setIcon(offIcon);
}
bool xIndicatorButton::hitButton(const QPoint &pos) const
{
    if (isDown())
        return true;
    return rect().contains(pos);
}
