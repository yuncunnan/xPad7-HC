#include <QStyleOptionButton>
#include <QPainter>
#include "buzzer.h"
#include "xpixmapbutton.h"

xPixmapButton::xPixmapButton(QWidget *parent) : QAbstractButton(parent), normalImage(), pressImage(),
	indicatorIcon(), indicatorSize(16, 16)
{
	topBorder = rightBorder = bottomBorder = leftBorder = 0;
	setText("PixmapButton");
	hasIndicator = false;
	indicatorState = false;
	contentAlign = Qt::AlignLeft | Qt::AlignVCenter;
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}

xPixmapButton::xPixmapButton(const QString &text, QWidget *parent) : QAbstractButton(parent), normalImage(), pressImage()
{
	topBorder = rightBorder = bottomBorder = leftBorder = 0;
	setText(text);
	hasIndicator = false;
	indicatorState = false;
	contentAlign = Qt::AlignLeft | Qt::AlignVCenter;
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}

void xPixmapButton::mousePressEvent(QMouseEvent *e)
{
	xBuzzer->TouchBeep();
	QAbstractButton::mousePressEvent(e);
}

void xPixmapButton::setImageNormal(const QPixmap &newImage)
{
	normalImage = newImage;
	update();
}

void xPixmapButton::setImagePress(const QPixmap &newImage)
{
	pressImage = newImage;
	update();
}

void xPixmapButton::setBorderTop(int newBorder)
{
	if (newBorder < 0)
		newBorder = 0;
	if ((newBorder + bottomBorder) > height())
		newBorder = height() - bottomBorder;
	topBorder = newBorder;
	update();
}

void xPixmapButton::setBorderRight(int newBorder)
{
	if (newBorder < 0)
		newBorder = 0;
	if ((newBorder + leftBorder) > width())
		newBorder = width() - leftBorder;
	rightBorder = newBorder;
	update();
}

void xPixmapButton::setBorderBottom(int newBorder)
{
	if (newBorder < 0)
		newBorder = 0;
	if ((newBorder + topBorder) > height())
		newBorder = height() - topBorder;
	bottomBorder = newBorder;
	update();
}

void xPixmapButton::setBorderLeft(int newBorder)
{
	if (newBorder < 0)
		newBorder = 0;
	if ((newBorder + rightBorder) > width())
		newBorder = width() - rightBorder;
	leftBorder = newBorder;
	update();
}

void xPixmapButton::setIndicator(bool on)
{
	if (hasIndicator == on)
		return;
	hasIndicator = on;
	update();
	updateGeometry();
}

void xPixmapButton::setStateOn(bool newState)
{
	if (indicatorState == newState)
		return;
	indicatorState = newState;
	if (hasIndicator)
		update();
}

void xPixmapButton::setIconIndicator(const QIcon &newIcon)
{
	indicatorIcon = newIcon;
	if (hasIndicator)
		update();
}

void xPixmapButton::setIconIndicatorSize(const QSize &newSize)
{
	if (indicatorSize == newSize)
		return;
	indicatorSize = newSize;
	if (hasIndicator)
	{
		update();
		updateGeometry();
	}
}

void xPixmapButton::setContentAlignment(Qt::Alignment newAlign)
{
	if (newAlign == (contentAlign & (Qt::AlignVertical_Mask | Qt::AlignHorizontal_Mask)))
		return;
	contentAlign = (contentAlign & ~(Qt::AlignVertical_Mask | Qt::AlignHorizontal_Mask))
				   | (newAlign & (Qt::AlignVertical_Mask | Qt::AlignHorizontal_Mask));
	update();
}

QSize xPixmapButton::sizeHint(void) const
{
	QSize size;
	int w, h;
	w = fontMetrics().width(text()) + leftBorder + rightBorder;
	h = fontMetrics().height() + topBorder + bottomBorder;
	if (!icon().isNull())
	{
		w += iconSize().width();
		if (iconSize().height() > h)
			h = iconSize().height();
	}
	if (hasIndicator)
	{
		w += indicatorSize.width();
		if (indicatorSize.height() > h)
			h = indicatorSize.height();
	}
	size.setWidth(w);
	size.setHeight(h);
	return size;
}

void xPixmapButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if (normalImage.isNull() || pressImage.isNull())
	{
		QStyleOptionButton option;
		option.initFrom(this);
		option.state = isEnabled() ? QStyle::State_Enabled : QStyle::State_None;
		option.state |= isDown() ? QStyle::State_Sunken : QStyle::State_Raised;
		if (hasFocus())
			option.state |= QStyle::State_HasFocus;
		option.text = text();
		option.icon = icon();
		style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);
	}
	else
	{
		int textWidth = fontMetrics().width(text());
		int iconW = iconSize().width();
		int iconH = iconSize().height();
		int indW = indicatorSize.width();
		QPixmap *drawImage;
		if (isDown() || isChecked())
			drawImage = &pressImage;
		else
			drawImage = &normalImage;
		// Draw the border of button
		int horW = width() - leftBorder - rightBorder;
		int horI = drawImage->width() - leftBorder - rightBorder;
		int verW = height() - topBorder - bottomBorder;
		int verI = drawImage->height() - topBorder - bottomBorder;
		painter.drawPixmap(0, 0, leftBorder, topBorder, *drawImage,
							0, 0, leftBorder, topBorder);
		painter.drawPixmap(leftBorder, 0, horW, topBorder, *drawImage,
							leftBorder, 0, horI, topBorder);
		painter.drawPixmap(width() - rightBorder, 0, rightBorder, topBorder, *drawImage,
							drawImage->width() - rightBorder, 0, rightBorder, topBorder);
		painter.drawPixmap(width() - rightBorder, topBorder, rightBorder, verW, *drawImage,
							drawImage->width() - rightBorder, topBorder, rightBorder, verI);
		painter.drawPixmap(width() - rightBorder, height() - bottomBorder, rightBorder, bottomBorder, *drawImage,
							drawImage->width() - rightBorder, drawImage->height() - bottomBorder, rightBorder, bottomBorder);
		painter.drawPixmap(leftBorder, height() - bottomBorder, horW, bottomBorder, *drawImage,
							leftBorder, drawImage->height() - bottomBorder, horI, bottomBorder);
		painter.drawPixmap(0, height() - bottomBorder, leftBorder, bottomBorder, *drawImage,
							0, drawImage->height() - bottomBorder, leftBorder, bottomBorder);
		painter.drawPixmap(0, topBorder, leftBorder, verW, *drawImage,
							0, topBorder, leftBorder, verI);
		// Draw the content of button
		painter.drawPixmap(leftBorder, topBorder, horW, verW, *drawImage, leftBorder, topBorder, horI, verI);
		// Draw the indicator of button
		if (hasIndicator)
		{
			int indicatorX = leftBorder;
			int indicatorY = (height() - indicatorSize.height()) / 2;
//			if (isDown() || isChecked())
//			{
//				indicatorX += 1;
//				indicatorY += 1;
//			}
			QIcon::Mode mode = isEnabled() ? QIcon::Normal : QIcon::Disabled;
			QIcon::State state = indicatorState ? QIcon::On : QIcon::Off;
			indicatorIcon.paint(&painter, indicatorX, indicatorY, indicatorSize.width(), indicatorSize.height(),
								  Qt::AlignCenter, mode, state);
		}
		else
			indW = 0;
		// Draw the icon of button
		if (!icon().isNull())
		{
			int iconX, iconY;
			if (contentAlign & Qt::AlignLeft)
				iconX = leftBorder + indW;
			else if (contentAlign & Qt::AlignRight)
				iconX = width() - rightBorder - textWidth - iconW;
			else
				iconX = (width() - textWidth - iconW) / 2;
			if (contentAlign & Qt::AlignTop)
				iconY = topBorder;
			else if (contentAlign & Qt::AlignBottom)
				iconY = height() - bottomBorder - iconH;
			else
				iconY = (height() - iconH) / 2;
//			if (isDown() || isChecked())
//			{
//				iconX += 1;
//				iconY += 1;
//			}
			QIcon::Mode mode = isEnabled() ? QIcon::Normal : QIcon::Disabled;
			icon().paint(&painter, iconX, iconY, iconW, iconH, Qt::AlignCenter, mode, QIcon::On);
		}
		else
		{
			iconW = iconH = 0;
		}
		// Draw the text of button
		if (!text().isEmpty())
		{
			int txtX, txtY;
			if (contentAlign & Qt::AlignLeft)
				txtX = leftBorder + indW + iconW;
			else if (contentAlign & Qt::AlignRight)
				txtX = width() - rightBorder - textWidth;
			else
				txtX = (width() - textWidth - iconW) / 2 + iconW;
			if (contentAlign & Qt::AlignTop)
				txtY = topBorder + fontMetrics().ascent();
			else if (contentAlign & Qt::AlignBottom)
				txtY = height() - bottomBorder - fontMetrics().descent();
			else
				txtY = (height() - fontMetrics().height()) / 2 + fontMetrics().ascent();
//			if (isDown() || isChecked())
//			{
//				txtX += 1;
//				txtY += 1;
//			}
			painter.setPen(this->palette().buttonText().color());
			painter.drawText(txtX, txtY, text());
		}
	}
}
bool xPixmapButton::hitButton(const QPoint &pos) const
{
    if (isDown())
        return true;
    return rect().contains(pos);
}
