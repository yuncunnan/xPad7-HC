#ifndef XCHECKBOX_H
#define XCHECKBOX_H

#include <QCheckBox>

class xCheckBox : public QCheckBox
{
	Q_OBJECT
public:
	explicit xCheckBox(QWidget *parent = 0);
	
protected:
	void mousePressEvent(QMouseEvent *event);

};

#endif // XCHECKBOX_H
