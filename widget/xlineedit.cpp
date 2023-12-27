#include <QEvent>
#include "buzzer.h"
#include "xlineedit.h"

xLineEdit::xLineEdit(QWidget *parent) :	QLineEdit(parent)
{
}

void xLineEdit::mousePressEvent(QMouseEvent *event)
{
	xBuzzer->TouchBeep();
	QLineEdit::mousePressEvent(event);
}

void xLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
	emit clicked();
	QLineEdit::mouseReleaseEvent(event);
}
