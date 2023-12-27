#include <QtGui>
#include "buzzer.h"
#include "xdoublespinbox.h"

xDoubleSpinBox::xDoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
	lineEdit()->installEventFilter(this);
}

bool xDoubleSpinBox::eventFilter(QObject *obj, QEvent *event)
{
	if ((event->type() != QEvent::MouseButtonRelease) && (event->type() != QEvent::MouseButtonPress))
		return QWidget::eventFilter(obj, event);
	if (this->isEnabled() == false)
		return QWidget::eventFilter(obj, event);
	if (event->type() == QEvent::MouseButtonPress)
	{
		xBuzzer->TouchBeep();
		return QWidget::eventFilter(obj, event);
	}
	if (obj == lineEdit())
	{
		emit clicked();
		return true;
	}
	else
		return QWidget::eventFilter(obj, event);
}
