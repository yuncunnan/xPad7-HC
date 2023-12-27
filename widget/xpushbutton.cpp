#include "buzzer.h"
#include "xpushbutton.h"

xPushButton::xPushButton(QWidget *parent) :	QPushButton(parent)
{
}

void xPushButton::focusOutEvent(QFocusEvent *event)
{
	QPushButton::focusOutEvent(event);
}

void xPushButton::mousePressEvent(QMouseEvent *e)
{
	xBuzzer->TouchBeep();
	QPushButton::mousePressEvent(e);
}
bool xPushButton::hitButton(const QPoint &pos) const
{
    if (isDown())
        return true;
    return rect().contains(pos);
}
