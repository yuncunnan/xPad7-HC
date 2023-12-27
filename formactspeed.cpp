#include <QButtonGroup>
#include "dialognumberpad.h"
#include "formactspeed.h"
#include "cmbprotocol.h"
#include "ui_formactspeed.h"
#include "servoalias.h"
#include "xmessagebox.h"

FormActSpeed::FormActSpeed(QWidget *parent) : QWidget(parent), ui(new Ui::FormActSpeed)
{
	// 初始化界面
	ui->setupUi(this);
	retranslateUi();
}

FormActSpeed::~FormActSpeed()
{
	delete ui;
}

void FormActSpeed::changeEvent(QEvent *e)
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

void FormActSpeed::retranslateUi(void)
{
	ui->CheckBoxPaHor->setText(GetServoName(AXIS_IDX_PHOR));
	ui->CheckBoxPaVer->setText(GetServoName(AXIS_IDX_PVER));
	ui->CheckBoxTravel->setText(GetServoName(AXIS_IDX_TRV));
	ui->CheckBoxRaHor->setText(GetServoName(AXIS_IDX_RHOR));
	ui->CheckBoxRaVer->setText(GetServoName(AXIS_IDX_RVER));
	ui->CheckBoxOther->setText(GetServoName(AXIS_IDX_EXT));
}

quint32 FormActSpeed::GetSpeed()
{
	return ui->BoxSpeed->value();
}

void FormActSpeed::SetSpeed(int speed)
{
	ui->BoxSpeed->setValue((double)speed);
}

int FormActSpeed::GetAxes()
{
    int ret = 0;
    if (ui->CheckBoxPaHor->isChecked()) ret |= SRV_PAHOR;
    if (ui->CheckBoxPaVer->isChecked()) ret |= SRV_PAVER;
    if (ui->CheckBoxRaVer->isChecked()) ret |= SRV_RAVER;
    if (ui->CheckBoxRaHor->isChecked()) ret |= SRV_RAHOR;
    if (ui->CheckBoxTravel->isChecked()) ret |= SRV_TRV;
    if (ui->CheckBoxOther->isChecked()) ret |= SRV_EXT;
    return ret;
}

void FormActSpeed::SetAxes(int axes)
{
    ui->CheckBoxPaHor->setChecked((axes & SRV_PAHOR) != 0);
    ui->CheckBoxPaVer->setChecked((axes & SRV_PAVER) != 0);
    ui->CheckBoxRaVer->setChecked((axes & SRV_RAVER) != 0);
    ui->CheckBoxRaHor->setChecked((axes & SRV_RAHOR) != 0);
    ui->CheckBoxTravel->setChecked((axes & SRV_TRV) != 0);
    ui->CheckBoxOther->setChecked((axes & SRV_EXT) != 0);
    UpdateWidgetState();
}

void FormActSpeed::UpdateWidgetState(void)
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->CheckBoxRaHor->setEnabled(false);
        ui->CheckBoxRaVer->setEnabled(false);
        ui->CheckBoxTravel->setEnabled(false);
        ui->CheckBoxOther->setEnabled(false);
        ui->CheckBoxPaHor->setEnabled(false);
        ui->CheckBoxPaVer->setEnabled(false);
    }
    else
    {
        if(CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            // 手动模式
            ui->CheckBoxTravel->setEnabled(true);
            ui->CheckBoxPaVer->setEnabled(true);
            if (!CMBProtocol::GetPaHorNotUse())
                ui->CheckBoxPaHor->setEnabled(true);
            else
                ui->CheckBoxPaHor->setEnabled(false);
            if (CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0))
                ui->CheckBoxRaHor->setEnabled(true);
            else
                ui->CheckBoxRaHor->setEnabled(false);
            if (CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0))
            {
                ui->CheckBoxRaVer->setEnabled(true);
            }
            else
            {
                ui->CheckBoxRaVer->setEnabled(false);
            }
            if (CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0))
            {
                ui->CheckBoxOther->setEnabled(true);
            }
            else
            {
                ui->CheckBoxOther->setEnabled(false);
            }
        }
        else
        {
            // 自动模式
            ui->CheckBoxRaHor->setEnabled(false);
            ui->CheckBoxRaVer->setEnabled(false);
            ui->CheckBoxTravel->setEnabled(false);
            ui->CheckBoxOther->setEnabled(false);
            ui->CheckBoxPaHor->setEnabled(false);
            ui->CheckBoxPaVer->setEnabled(false);
       }
    }
}

// 输入伺服速度槽
void FormActSpeed::inputSpeed(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxSpeed->minimum(), ui->BoxSpeed->maximum()) == QDialog::Accepted)
        ui->BoxSpeed->setValue(value);
}
