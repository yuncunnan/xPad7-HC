#include "dialognumberpad.h"
#include "formactpath.h"
#include "ui_formactpath.h"

FormActPath::FormActPath(QWidget *parent) : QWidget(parent), ui(new Ui::FormActPath)
{
	ui->setupUi(this);
}

FormActPath::~FormActPath()
{
	delete ui;
}
void FormActPath::inputPath(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxPath->minimum(), ui->BoxPath->maximum()) == QDialog::Accepted)
		ui->BoxPath->setValue(value);
}
int FormActPath::GetTrajTime()
{
    return qRound(ui->BoxPath->value() * 100.00);
}
void FormActPath::SetTrajTime(int trajtime)
{
    ui->BoxPath->setValue((double)trajtime / 100.00);
}
