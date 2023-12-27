#ifndef XPIXMAPBUTTON_H
#define XPIXMAPBUTTON_H

#include <QAbstractButton>

class xPixmapButton : public QAbstractButton
{
	Q_OBJECT

	Q_PROPERTY(QPixmap imageNormal READ imageNormal WRITE setImageNormal)
	Q_PROPERTY(QPixmap imagePress READ imagePress WRITE setImagePress)
	Q_PROPERTY(int borderTop READ borderTop WRITE setBorderTop)
	Q_PROPERTY(int borderRight READ borderRight WRITE setBorderRight)
	Q_PROPERTY(int borderBottom READ borderBottom WRITE setBorderBottom)
	Q_PROPERTY(int borderLeft READ borderLeft WRITE setBorderLeft)

	Q_PROPERTY(bool indicator READ indicator WRITE setIndicator)
	Q_PROPERTY(bool stateOn READ stateOn WRITE setStateOn)
	Q_PROPERTY(QIcon iconIndicator READ iconIndicator WRITE setIconIndicator)
	Q_PROPERTY(QSize iconIndicatorSize READ iconIndicatorSize WRITE setIconIndicatorSize)
	Q_PROPERTY(Qt::Alignment contentAlignment READ contentAlignment WRITE setContentAlignment)

public:
	explicit xPixmapButton(QWidget *parent = 0);
	explicit xPixmapButton(const QString &text, QWidget *parent = 0);

	QPixmap imageNormal(void) const { return normalImage; }
	void setImageNormal(const QPixmap &newImage);
	QPixmap imagePress(void) const { return pressImage; }
	void setImagePress(const QPixmap &newImage);
	int borderTop(void) const { return topBorder; }
	void setBorderTop(int newBorder);
	int borderRight(void) const { return rightBorder; }
	void setBorderRight(int newBorder);
	int borderBottom(void) const { return bottomBorder; }
	void setBorderBottom(int newBorder);
	int borderLeft(void) const { return leftBorder; }
	void setBorderLeft(int newBorder);

	bool indicator(void) const { return hasIndicator; }
	void setIndicator(bool on);
	bool stateOn(void) const { return indicatorState; }
	void setStateOn(bool newState);
	QIcon iconIndicator(void) const { return indicatorIcon; }
	void setIconIndicator(const QIcon &newIcon);
	QSize iconIndicatorSize(void) const { return indicatorSize; }
	void setIconIndicatorSize(const QSize &newSize);
	Qt::Alignment contentAlignment(void) const { return QFlag(contentAlign & (Qt::AlignVertical_Mask | Qt::AlignHorizontal_Mask));; }
	void setContentAlignment(Qt::Alignment newAlign);
	QSize sizeHint(void) const;

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *e);
    virtual bool hitButton(const QPoint &pos) const;

private:
	QPixmap normalImage;
	QPixmap pressImage;
	int topBorder;
	int rightBorder;
	int bottomBorder;
	int leftBorder;

	bool hasIndicator;
	bool indicatorState;
	QIcon indicatorIcon;
	QSize indicatorSize;
	Qt::Alignment contentAlign;
};

#endif
