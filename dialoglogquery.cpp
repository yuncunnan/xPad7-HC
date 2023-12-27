#include "dialognumberpad.h"
#include "dialoglogquery.h"
#include "ui_dialoglogquery.h"

DialogLogQuery::DialogLogQuery(QWidget *parent) : QDialog(parent), ui(new Ui::DialogLogQuery)
{
	ui->setupUi(this);
#if defined(Q_WS_QWS)
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
}

DialogLogQuery::~DialogLogQuery()
{
	delete ui;
}

int DialogLogQuery::DoForm(quint8 &queryType, QDateTime &begin, QDateTime &end)
{
	ui->radioAll->setChecked(true);
	ui->frameTime->setEnabled(false);
	ui->timeEditBegin->setDate(QDate(2000, 1, 1));
	ui->timeEditBegin->setTime(QTime(0, 0, 0, 0));
	ui->timeEditEnd->setDateTime(QDateTime::currentDateTime());
	int ret = exec();
	if (ret == QDialog::Accepted)
	{
		if (ui->radioNormal->isChecked())
			queryType = Normal;
		else if (ui->radioMsg->isChecked())
			queryType = Message;
		else if (ui->radioAlarm->isChecked())
			queryType = Alarm;
		else if (ui->radioTime->isChecked())
			queryType = Query;
		else
			queryType = All;
		begin.setDate(ui->timeEditBegin->date());
		begin.setTime(ui->timeEditBegin->time());
		end.setDate(ui->timeEditEnd->date());
		end.setTime(ui->timeEditEnd->time());
	}
	return ret;
}

void DialogLogQuery::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}
bool DialogLogQuery::inputDateTime(QDateTime &dateTime, QDateTimeEdit::Section sec)
{
	DialogNumberPad numberPad;
    int value;
	if (sec == QDateTimeEdit::YearSection)
	{
		if (numberPad.DoForm(value, 2000, 7999) == QDialog::Accepted)
		{
			if (QDate::isValid(qRound(value), dateTime.date().month(), dateTime.date().day()))
				dateTime.setDate(QDate(qRound(value), dateTime.date().month(), dateTime.date().day()));
			else
			{
				dateTime.setDate(QDate(qRound(value), dateTime.date().month(), 1));
				dateTime.setDate(QDate(qRound(value), dateTime.date().month(), dateTime.date().daysInMonth()));
			}
			return true;
		}
	}
	else if (sec == QDateTimeEdit::MonthSection)
	{
		if (numberPad.DoForm(value, 1, 12) == QDialog::Accepted)
		{
			if (QDate::isValid(dateTime.date().year(), qRound(value), dateTime.date().day()))
				dateTime.setDate(QDate(dateTime.date().year(), qRound(value), dateTime.date().day()));
			else
			{
				dateTime.setDate(QDate(dateTime.date().year(), qRound(value), 1));
				dateTime.setDate(QDate(dateTime.date().year(), qRound(value), dateTime.date().daysInMonth()));
			}
			return true;
		}
	}
	else if (sec == QDateTimeEdit::DaySection)
	{
		if (numberPad.DoForm(value, 1, dateTime.date().daysInMonth()) == QDialog::Accepted)
		{
			dateTime.setDate(QDate(dateTime.date().year(), dateTime.date().month(), qRound(value)));
			return true;
		}
	}
	else if (sec == QDateTimeEdit::HourSection)
	{
		if (numberPad.DoForm(value, 0, 23) == QDialog::Accepted)
		{
			dateTime.setTime(QTime(qRound(value), dateTime.time().minute(), dateTime.time().second()));
			return true;
		}
	}
	else if (sec == QDateTimeEdit::MinuteSection)
	{
		if (numberPad.DoForm(value, 0, 59) == QDialog::Accepted)
		{
			dateTime.setTime(QTime(dateTime.time().hour(), qRound(value), dateTime.time().second()));
			return true;
		}
	}
	else if (sec == QDateTimeEdit::SecondSection)
	{
		if (numberPad.DoForm(value, 0, 59) == QDialog::Accepted)
		{
			dateTime.setTime(QTime(dateTime.time().hour(), dateTime.time().minute(), qRound(value)));
			return true;
		}
	}
	return false;
}

void DialogLogQuery::beginTimeClicked(QDateTimeEdit::Section sec)
{
	QDateTime dateTime = ui->timeEditBegin->dateTime();
	if (inputDateTime(dateTime, sec))
		ui->timeEditBegin->setDateTime(dateTime);
}

void DialogLogQuery::endTimeClicked(QDateTimeEdit::Section sec)
{
	QDateTime dateTime = ui->timeEditEnd->dateTime();
	if (inputDateTime(dateTime, sec))
		ui->timeEditEnd->setDateTime(dateTime);
}
