#ifndef XTIMEEDIT_H
#define XTIMEEDIT_H

#include <QTimeEdit>

class xTimeEdit : public QTimeEdit
{
	Q_OBJECT
public:
	explicit xTimeEdit(QWidget *parent = 0);
	
protected:
	bool eventFilter(QObject *obj, QEvent *event);

signals:
	void clicked(QTimeEdit::Section);

};

#endif // XTIMEEDIT_H
