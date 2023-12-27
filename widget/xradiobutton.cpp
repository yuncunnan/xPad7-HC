#include "buzzer.h"
#include "xradiobutton.h"

xRadioButton::xRadioButton(QWidget *parent) : QRadioButton(parent)
{
}

void xRadioButton::mousePressEvent(QMouseEvent *event)
{
	xBuzzer->TouchBeep();
	QRadioButton::mousePressEvent(event);
}
