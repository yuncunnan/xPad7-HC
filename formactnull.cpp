#include "formactnull.h"
#include "ui_formactnull.h"

FormActNull::FormActNull(QWidget *parent) : QWidget(parent), ui(new Ui::FormActNull)
{
    ui->setupUi(this);
}

FormActNull::~FormActNull()
{
    delete ui;
}

void FormActNull::changeEvent(QEvent *e)
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
