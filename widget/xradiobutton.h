#ifndef XRADIOBUTTON_H
#define XRADIOBUTTON_H

#include <QRadioButton>

class xRadioButton : public QRadioButton
{
	Q_OBJECT
public:
	explicit xRadioButton(QWidget *parent = 0);
	
protected:
	void mousePressEvent(QMouseEvent *event);

};

#endif // XRADIOBUTTON_H
