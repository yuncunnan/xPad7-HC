#include <QPainter>
#include "xindicator.h"

xIndicator::xIndicator(QWidget *parent) : QWidget(parent), onIcon(), offIcon(), imageSize(16, 16), textString("indicator")
{
	status = false;
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void xIndicator::setIconOn(const QIcon &newIconOn)
{
	onIcon = newIconOn;
	update();
}

void xIndicator::setIconOff(const QIcon &newIconOff)
{
	offIcon = newIconOff;
	update();
}

void xIndicator::setIconSize(const QSize &newSize)
{
	if (imageSize != newSize)
	{
		imageSize = newSize;
		update();
		updateGeometry();
	}
}

void xIndicator::setText(const QString &newText)
{
	textString = newText;
	update();
}

void xIndicator::setOn(const bool newStatus)
{
	if (status != newStatus)
	{
		status = newStatus;
		update();
	}
}

QSize xIndicator::sizeHint(void) const
{
	QSize size;
	size.setWidth(imageSize.width() + fontMetrics().width(textString));
	if (imageSize.height() > fontMetrics().height())
		size.setHeight(imageSize.height());
	else
		size.setHeight(fontMetrics().height());
	return size;
}

void xIndicator::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	int y = (height() - imageSize.height()) / 2;
	QIcon::Mode mode = isEnabled() ? QIcon::Normal : QIcon::Disabled;
	if (status)
		onIcon.paint(&painter, 0, y, imageSize.width(), imageSize.height(), Qt::AlignCenter, mode);
	else
		offIcon.paint(&painter, 0, y, imageSize.width(), imageSize.height(), Qt::AlignCenter, mode);
	painter.setPen(this->palette().windowText().color());
	painter.drawText(imageSize.width(), 0, width() - imageSize.width(), height(), Qt::AlignLeft | Qt::AlignVCenter, textString);
}
