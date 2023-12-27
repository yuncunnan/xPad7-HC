#include "buzzer.h"
#include "xcheckbox.h"

xCheckBox::xCheckBox(QWidget *parent) : QCheckBox(parent)
{
}

void xCheckBox::mousePressEvent(QMouseEvent *event)
{
	xBuzzer->TouchBeep();
	QCheckBox::mousePressEvent(event);
}
