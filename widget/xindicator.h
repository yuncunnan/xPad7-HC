#ifndef XINDICATOR_H
#define XINDICATOR_H

#include <QIcon>
#include <QWidget>

class xIndicator : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QIcon iconOn READ iconOn WRITE setIconOn)
	Q_PROPERTY(QIcon iconOff READ iconOff WRITE setIconOff)
	Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
	Q_PROPERTY(QString text READ text WRITE setText)
	Q_PROPERTY(bool On READ on WRITE setOn)
	
public:
	xIndicator(QWidget *parent = 0);
	void setIconOn(const QIcon &newIconOn);
	QIcon iconOn(void) const { return onIcon; }
	void setIconOff(const QIcon &newIconOff);
	QIcon iconOff(void) const { return offIcon; }
	void setIconSize(const QSize &newSize);
	QSize iconSize(void) const { return imageSize; }
	void setText(const QString &newText);
	QString text(void) const { return textString; }
	void setOn(const bool newStatus);
	bool on(void) const { return status; }
	QSize sizeHint(void) const;

protected:
	void paintEvent(QPaintEvent *);

private:
	QIcon onIcon;
	QIcon offIcon;
	QSize imageSize;
	QString textString;
	bool status;
};

#endif
