#ifndef XDOUBLESPINBOX_H
#define XDOUBLESPINBOX_H

#include <QDoubleSpinBox>

class xDoubleSpinBox : public QDoubleSpinBox
{
	Q_OBJECT
public:
	explicit xDoubleSpinBox(QWidget *parent = 0);
	
protected:
	bool eventFilter(QObject *obj, QEvent *event);

signals:
	void clicked ();

public slots:
	
};

#endif // XDOUBLESPINBOX_H
