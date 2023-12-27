#ifndef XLINEEDIT_H
#define XLINEEDIT_H

#include <QLineEdit>

class xLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	explicit xLineEdit(QWidget *parent = 0);
	
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

signals:
	void clicked ();

public slots:
	
};

#endif // XLINEEDIT_H
