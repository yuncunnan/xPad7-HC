#ifndef XDATEEDIT_H
#define XDATEEDIT_H

#include <QDateEdit>

class xDateEdit : public QDateEdit
{
	Q_OBJECT
public:
	explicit xDateEdit(QWidget *parent = 0);
	
protected:
	bool eventFilter(QObject *obj, QEvent *event);

signals:
	void clicked(QDateEdit::Section);
	
};

#endif // XDATEEDIT_H
