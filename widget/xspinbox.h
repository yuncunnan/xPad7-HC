#ifndef XSPINBOX_H
#define XSPINBOX_H

#include <QSpinBox>

class xSpinBox : public QSpinBox
{
	Q_OBJECT
public:
	explicit xSpinBox(QWidget *parent = 0);
	
protected:
	bool eventFilter(QObject *obj, QEvent *event);

signals:
	void clicked ();

public slots:
	
};

#endif // XSPINBOX_H
