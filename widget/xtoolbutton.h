#ifndef XTOOLBUTTON_H
#define XTOOLBUTTON_H

#include <QToolButton>

class xToolButton : public QToolButton
{
	Q_OBJECT
public:
	explicit xToolButton(QWidget *parent = 0);

signals:

public slots:

protected:
	void mousePressEvent(QMouseEvent *e);
};

#endif // XTOOLBUTTON_H
