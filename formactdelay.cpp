#include "dialognumberpad.h"
#include "formactdelay.h"
#include "ui_formactdelay.h"
#include "xconfig.h"

FormActDelay::FormActDelay(QWidget *parent) : QWidget(parent), ui(new Ui::FormActDelay)
{
    ui->setupUi(this);
#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(600.00);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(6000.0);
#endif

}

FormActDelay::~FormActDelay()
{
    delete ui;
}

void FormActDelay::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void FormActDelay::SetDelay(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormActDelay::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

// 输入延时参数信号槽
void FormActDelay::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}
