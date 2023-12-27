#ifndef DIALOGLOGQUERY_H
#define DIALOGLOGQUERY_H

#include <QDialog>
#include <QDateTime>
#include <QDateTimeEdit>

namespace Ui {
class DialogLogQuery;
}

class DialogLogQuery : public QDialog
{
	Q_OBJECT
	
public:
	enum QueryType
	{
		All = 0,
		Normal = 1,
		Message = 2,
		Alarm = 3,
		Query = 4
	};

	explicit DialogLogQuery(QWidget *parent = 0);
	~DialogLogQuery();
	
	int DoForm(quint8 &queryType, QDateTime &begin, QDateTime &end);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::DialogLogQuery *ui;
	bool inputDateTime(QDateTime &dateTime, QDateTimeEdit::Section sec);

private slots:
	void beginTimeClicked(QDateTimeEdit::Section sec);
	void endTimeClicked(QDateTimeEdit::Section sec);
};

#endif // DIALOGLOGQUERY_H
