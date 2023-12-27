#include "buzzer.h"
#include "xtoolbutton.h"

xToolButton::xToolButton(QWidget *parent) : QToolButton(parent)
{
}

void xToolButton::mousePressEvent(QMouseEvent *e)
{
	xBuzzer->TouchBeep();
	QToolButton::mousePressEvent(e);
}
