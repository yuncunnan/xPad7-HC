#include <stdlib.h>
#include <time.h>
#include <QDateTime>
#include "xsystemlog.h"
#include "xmessagebox.h"
#include "dialognumberpad.h"
#include "dialogdatetime.h"
#include "ui_dialogdatetime.h"
#ifdef Q_OS_WIN
#include <windows.h>
#endif

DialogDateTime::DialogDateTime(QWidget *parent) : QDialog(parent), ui(new Ui::DialogDateTime)
{
	ui->setupUi(this);
    retranslateUi();
	// 设置对话框显示效果
#if defined(Q_WS_QWS)
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
}

DialogDateTime::~DialogDateTime()
{
	delete ui;
}

int DialogDateTime::DoForm(void)
{
	int ret;
	ui->dateEdit->setDate(QDate::currentDate());
	ui->timeEdit->setTime(QTime::currentTime());
	ui->widgetClock->StartClock(true);
	ret = exec();
	ui->widgetClock->StartClock(false);
	return ret;
}

void DialogDateTime::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        retranslateUi();
        break;
    default:
        break;
    }
}
void DialogDateTime::retranslateUi(void)
{
}
void DialogDateTime::dateClicked(QDateEdit::Section sec)
{
	DialogNumberPad numberPad;
    int value;
	QDate date = ui->dateEdit->date();
	if (sec == QDateEdit::YearSection)
	{
		if (numberPad.DoForm(value, 2000, 7999) == QDialog::Accepted)
		{
			if (QDate::isValid(qRound(value), date.month(), date.day()))
				date.setDate(qRound(value), date.month(), date.day());
			else
			{
				date.setDate(qRound(value), date.month(), 1);
				date.setDate(qRound(value), date.month(), date.daysInMonth());
			}
			ui->dateEdit->setDate(date);
		}
	}
	else if (sec == QDateEdit::MonthSection)
	{
		if (numberPad.DoForm(value, 1, 12) == QDialog::Accepted)
		{
			if (QDate::isValid(date.year(), qRound(value), date.day()))
				date.setDate(date.year(), qRound(value), date.day());
			else
			{
				date.setDate(date.year(), qRound(value), 1);
				date.setDate(date.year(), qRound(value), date.daysInMonth());
			}
			ui->dateEdit->setDate(date);
		}
	}
	else if (sec == QDateEdit::DaySection)
	{
		if (numberPad.DoForm(value, 1, date.daysInMonth()) == QDialog::Accepted)
		{
			date.setDate(date.year(), date.month(), qRound(value));
			ui->dateEdit->setDate(date);
		}
	}
}

void DialogDateTime::timeClicked(QTimeEdit::Section sec)
{
	DialogNumberPad numberPad;
    int value;
	QTime time = ui->timeEdit->time();
	if (sec == QDateEdit::HourSection)
	{
		if (numberPad.DoForm(value, 0, 23) == QDialog::Accepted)
		{
			time.setHMS(qRound(value), time.minute(), time.second());
			ui->timeEdit->setTime(time);
		}
	}
	else if (sec == QDateEdit::MinuteSection)
	{
		if (numberPad.DoForm(value, 0, 59) == QDialog::Accepted)
		{
			time.setHMS(time.hour(), qRound(value), time.second());
			ui->timeEdit->setTime(time);
		}
	}
	else if (sec == QDateEdit::SecondSection)
	{
		if (numberPad.DoForm(value, 0, 59) == QDialog::Accepted)
		{
			time.setHMS(time.hour(), time.minute(), qRound(value));
			ui->timeEdit->setTime(time);
		}
	}
}

void DialogDateTime::SaveExit(void)
{
#ifdef Q_OS_WIN
	SYSTEMTIME st;
	st.wYear = ui->dateEdit->date().year();
	st.wMonth = ui->dateEdit->date().month();
	st.wDay = ui->dateEdit->date().day();
	st.wHour = ui->timeEdit->time().hour();
	st.wMinute = ui->timeEdit->time().minute();
	st.wSecond = ui->timeEdit->time().second();
	st.wMilliseconds = 0;
	SetSystemTime(&st);
#endif
#ifdef Q_OS_LINUX
	QDateTime dt;
	dt.setDate(ui->dateEdit->date());
	dt.setTime(ui->timeEdit->time());
	// 写入系统日志
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_TIME_CHG, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + QString(" -> ") + dt.toString("yyyy-MM-dd hh:mm:ss"));
	xSysLog::SaveChange();
	// 设置时间
	time_t tt = dt.toTime_t();
	stime(&tt);
	// 同步硬件时钟
	system("hwclock -w");
#endif
	done(QDialog::Accepted);
}
