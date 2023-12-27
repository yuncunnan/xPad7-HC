#include <QtGui>
#include "buzzer.h"
#include "xdatetimeedit.h"

xDateTimeEdit::xDateTimeEdit(QWidget *parent) : QDateTimeEdit(parent)
{
	lineEdit()->installEventFilter(this);
}

bool xDateTimeEdit::eventFilter(QObject *obj, QEvent *event)
{
	if ((event->type() != QEvent::MouseButtonRelease) && (event->type() != QEvent::MouseButtonPress))
		return QWidget::eventFilter(obj, event);
	if (this->isEnabled() == false)
		return QWidget::eventFilter(obj, event);
	if (event->type() == QEvent::MouseButtonPress)
		xBuzzer->TouchBeep();
	else if (obj == lineEdit())
		emit clicked(currentSection());
	return QWidget::eventFilter(obj, event);
}
