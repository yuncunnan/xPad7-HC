#include <QSettings>
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "formactpower.h"
#include "ui_formactpower.h"
#include "servoalias.h"
#include "xmessagebox.h"

FormActPower::FormActPower(QWidget *parent) : QWidget(parent), ui(new Ui::FormActPower)
{
	// 初始化界面
    ui->setupUi(this);
	retranslateUi();
}

FormActPower::~FormActPower()
{
    delete ui;
}

void FormActPower::changeEvent(QEvent *e)
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

void FormActPower::retranslateUi(void)
{
	ui->checkPaHor->setText(GetServoName(AXIS_IDX_PHOR));
	ui->checkPaVer->setText(GetServoName(AXIS_IDX_PVER));
	ui->checkTravel->setText(GetServoName(AXIS_IDX_TRV));
	ui->checkRaHor->setText(GetServoName(AXIS_IDX_RHOR));
	ui->checkRaVer->setText(GetServoName(AXIS_IDX_RVER));
	ui->checkOther->setText(GetServoName(AXIS_IDX_EXT));
}

int FormActPower::GetAxes()
{
    int ret = 0;
	if (ui->checkPaVer->isChecked() == true)
		ret |= SRV_PAVER;
	if (ui->checkTravel->isChecked() == true)
		ret |= SRV_TRV;
	if (ui->checkPaHor->isChecked() == true)
		ret |= SRV_PAHOR;
	if (ui->checkRaVer->isChecked() == true)
		ret |= SRV_RAVER;
	if (ui->checkRaHor->isChecked() == true)
		ret |= SRV_RAHOR;
	if (ui->checkOther->isChecked() == true)
		ret |= SRV_EXT;
    return ret;
}

void FormActPower::SetAxes(int axes)
{
	// 正臂上下轴
	ui->checkPaVer->setChecked((axes & SRV_PAVER) != 0);
	// 横行轴
	ui->checkTravel->setChecked((axes & SRV_TRV) != 0);
	// 正臂引拔轴
	ui->checkPaHor->setChecked((axes & SRV_PAHOR) != 0);
	// 副臂上下轴
	ui->checkRaVer->setChecked((axes & SRV_RAVER) != 0);
	// 副臂引拔轴
	ui->checkRaHor->setChecked((axes & SRV_RAHOR) != 0);
	// 扩展轴
	ui->checkOther->setChecked(((axes & SRV_EXT) != 0));
	// 更新界面显示状态
	UpdateWidgetState();
}
void FormActPower::SetPoweroff(bool poweroff)
{
    ui->checkSwitch->setChecked(poweroff);
    UpdateWidgetState();
}

bool FormActPower::GetPoweroff(void)
{
    if (ui->checkSwitch->isChecked())
        return true;
    return false;
}

void FormActPower::UpdateWidgetState(void)
{
    if(CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        // 手动模式
        ui->checkSwitch->setEnabled(true);
        ui->checkPaVer->setEnabled(true);
        ui->checkTravel->setEnabled(true);
        if (!CMBProtocol::GetPaHorNotUse())
            ui->checkPaHor->setEnabled(true);
        else
        {
            ui->checkPaHor->setEnabled(false);
            ui->checkPaHor->setChecked(false);
        }
        if (CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0))
            ui->checkRaHor->setEnabled(true);
        else
        {
            ui->checkRaHor->setEnabled(false);
            ui->checkRaHor->setChecked(false);
        }
        if (CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0))
            ui->checkRaVer->setEnabled(true);
        else
        {
            ui->checkRaVer->setEnabled(false);
            ui->checkRaVer->setChecked(false);
        }
        if (CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0))
            ui->checkOther->setEnabled(true);
        else
        {
            ui->checkOther->setEnabled(false);
            ui->checkOther->setChecked(false);
        }
    }
    else
    {
        // 自动模式
        ui->checkSwitch->setEnabled(false);
        ui->checkPaHor->setEnabled(false);
        ui->checkPaVer->setEnabled(false);
        ui->checkTravel->setEnabled(false);
        ui->checkRaHor->setEnabled(false);
        ui->checkRaVer->setEnabled(false);
        ui->checkOther->setEnabled(false);
    }
}

void FormActPower::checkClick(void)
{
	UpdateWidgetState();
}

void FormActPower::setVisible(bool visible)
{
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	if (visible)
	{
        ui->checkSwitch->setEnabled(!CMBProtocol::GetTemplateUse());
        ui->checkPaHor->setEnabled((!CMBProtocol::GetTemplateUse()) && (!CMBProtocol::GetPaHorNotUse()));
        ui->checkPaVer->setEnabled(!CMBProtocol::GetTemplateUse());
        ui->checkTravel->setEnabled(!CMBProtocol::GetTemplateUse());
        ui->checkRaHor->setEnabled((!CMBProtocol::GetTemplateUse()) && CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
        ui->checkRaVer->setEnabled((!CMBProtocol::GetTemplateUse()) && CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
        ui->checkOther->setEnabled((!CMBProtocol::GetTemplateUse()) && CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
	}
	QWidget::setVisible(visible);
}
