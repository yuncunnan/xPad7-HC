#include "xconfig.h"
#include "dialognumberpad.h"
#include "xioport.h"
#include "xstringresource.h"
#include "formbtnassist.h"
#include "ui_formbtnassist.h"

FormBtnAssist::FormBtnAssist(QWidget *parent) : QWidget(parent), ui(new Ui::FormBtnAssist)
{
    ui->setupUi(this);
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);
#if TIME_BASE == 10
    ui->BoxDelayOil->setDecimals(2);
    ui->BoxDelayOil->setMaximum(360.00);
    ui->BoxDelayConveyor->setDecimals(2);
    ui->BoxDelayConveyor->setMaximum(360.00);
    ui->BoxDelayReject->setDecimals(2);
    ui->BoxDelayReject->setMaximum(360.00);
#else
    ui->BoxDelayOil->setDecimals(1);
    ui->BoxDelayOil->setMaximum(3600.0);
    ui->BoxDelayConveyor->setDecimals(1);
    ui->BoxDelayConveyor->setMaximum(3600.0);
    ui->BoxDelayReject->setDecimals(1);
    ui->BoxDelayReject->setMaximum(3600.0);
#endif
}
FormBtnAssist::~FormBtnAssist()
{
    delete ui;
}

bool FormBtnAssist::EnterForm(void)
{
    init();
    UpdateWidgetState();
    show();
    return true;
}
void FormBtnAssist::init(void)
{
    ui->checkBoxOil->setChecked(false);
    ui->checkBoxConveyor->setChecked(false);
    ui->checkBoxReject->setChecked(false);
    ui->radioBtnOil->setFlat(false);
    ui->radioBtnConveyor->setFlat(false);
    ui->radioBtnReject->setFlat(false);
    ui->BoxDelayOil->setValue(0.0);
    ui->BoxDelayConveyor->setValue(0.0);
    ui->BoxDelayReject->setValue(0.0);
    ui->BoxIntervalOil->setValue(0);
    ui->BoxIntervalConveyor->setValue(0);
    ui->BoxIntervalReject->setValue(0);
}

void FormBtnAssist::changeEvent(QEvent *e)
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

int FormBtnAssist::GetTypeOil()
{
    if (ui->checkBoxOil->isChecked())
    {
        if (ui->radioBtnOil->isFlat())
            return 1;
        return 0;
    }
}
int FormBtnAssist::GetTypeConveyor()
{
    if (ui->checkBoxConveyor->isChecked())
    {
        if (ui->radioBtnConveyor->isFlat())
            return 1;
        return 0;
    }
}
int FormBtnAssist::GetTypeReject()
{
}

int FormBtnAssist::GetVarOil()
{
    if (ui->checkBoxOil->isChecked())
        return EM1_VAR_Y08;
}
int FormBtnAssist::GetVarConveyor()
{
    if (ui->checkBoxConveyor->isChecked())
        return EM1_VAR_Y09;
}
int FormBtnAssist::GetVarReject()
{
    if (ui->checkBoxReject->isChecked())
        return EM1_VAR_Y10;
}

int FormBtnAssist::GetAssistBmp()
{
    int ret = 0;
    if (ui->checkBoxOil->isChecked()) ret |= (1<< 0);
    if (ui->checkBoxConveyor->isChecked()) ret |= (1<< 1);
    if (ui->checkBoxReject->isChecked()) ret |= (1<< 2);
    return ret;
}

int FormBtnAssist::GetDelayOil()
{
    return qRound(ui->BoxDelayOil->value() * (1000.0/TIME_BASE));
}
int FormBtnAssist::GetDelayConveyor()
{
    return qRound(ui->BoxDelayConveyor->value() * (1000.0/TIME_BASE));
}
int FormBtnAssist::GetDelayReject()
{
    return qRound(ui->BoxDelayReject->value() * (1000.0/TIME_BASE));
}
int FormBtnAssist::GetIntervalOil()
{
    return  ui->BoxIntervalOil->value();
}
int FormBtnAssist::GetIntervalConveyor()
{
    return  ui->BoxIntervalConveyor->value();
}
int FormBtnAssist::GetIntervalReject()
{
    return  ui->BoxIntervalReject->value();
}

void FormBtnAssist::inputDelayOil(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayOil->minimum(), ui->BoxDelayOil->maximum()) == QDialog::Accepted)
        ui->BoxDelayOil->setValue(value);
}
void FormBtnAssist::inputDelayConveyor(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayConveyor->minimum(), ui->BoxDelayConveyor->maximum()) == QDialog::Accepted)
        ui->BoxDelayConveyor->setValue(value);
}
void FormBtnAssist::inputDelayReject(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayReject->minimum(), ui->BoxDelayReject->maximum()) == QDialog::Accepted)
        ui->BoxDelayReject->setValue(value);
}

void FormBtnAssist::btnOilclicked(void)
{
    if (ui->radioBtnOil->isFlat())
    {
        ui->radioBtnOil->setOn(false);
        ui->radioBtnOil->setFlat(false);
        ui->radioBtnOil->setText(tr("打油关"));
    }
    else
    {
        ui->radioBtnOil->setOn(true);
        ui->radioBtnOil->setFlat(true);
        ui->radioBtnOil->setText(tr("打油开"));
    }
}
void FormBtnAssist::btnConveyorclicked(void)
{
    if (ui->radioBtnConveyor->isFlat())
    {
        ui->radioBtnConveyor->setOn(false);
        ui->radioBtnConveyor->setFlat(false);
        ui->radioBtnConveyor->setText(tr("传送带关"));
    }
    else
    {
        ui->radioBtnConveyor->setOn(true);
        ui->radioBtnConveyor->setFlat(true);
        ui->radioBtnConveyor->setText(tr("传送带开"));
    }
}
void FormBtnAssist::btnRejectclicked(void)
{
    if (ui->radioBtnReject->isFlat())
    {
        ui->radioBtnReject->setOn(false);
        ui->radioBtnReject->setFlat(false);
        ui->radioBtnReject->setText(tr("不良品"));
    }
    else
    {
        ui->radioBtnReject->setOn(true);
        ui->radioBtnReject->setFlat(true);
        ui->radioBtnReject->setText(tr("不良品"));
    }
}
void FormBtnAssist::inputIntervalOil(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxIntervalOil->minimum(), ui->BoxIntervalOil->maximum()) == QDialog::Accepted)
        ui->BoxIntervalOil->setValue(value);
}
void FormBtnAssist::inputIntervalConveyor(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxIntervalConveyor->minimum(), ui->BoxIntervalConveyor->maximum()) == QDialog::Accepted)
        ui->BoxIntervalConveyor->setValue(value);
}
void FormBtnAssist::inputIntervalReject(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxIntervalReject->minimum(), ui->BoxIntervalReject->maximum()) == QDialog::Accepted)
        ui->BoxIntervalReject->setValue(value);
}
void FormBtnAssist::UpdateWidgetState()
{
}
