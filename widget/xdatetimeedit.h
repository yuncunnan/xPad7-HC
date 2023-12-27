#ifndef XDATETIMEEDIT_H
#define XDATETIMEEDIT_H

#include <QDateTimeEdit>

class xDateTimeEdit : public QDateTimeEdit
{
	Q_OBJECT
public:
	explicit xDateTimeEdit(QWidget *parent = 0);
	
protected:
	bool eventFilter(QObject *obj, QEvent *event);

signals:
	void clicked(QDateTimeEdit::Section);

};

#endif // XDATETIMEEDIT_H
