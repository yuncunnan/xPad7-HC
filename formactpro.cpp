#include "xconfig.h"
#include "safeswitch.h"
#include "dialognumberpad.h"
#include "cmbprotocol.h"
#include "formactpro.h"
#include "ui_formactpro.h"
#include "HardwareInterface.h"
FormActPro::FormActPro(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormActPro)
{
    ui->setupUi(this);
#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(600.00);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(6000.0);
#endif
    pModbus = modbus;
    ui->BtnJig_b->setVisible(false);
    ui->BtnJig_r->setVisible(false);
    ui->radioButton_jig_b->setVisible(false);
    ui->radioButton_jig_r->setVisible(false);
}

FormActPro::~FormActPro()
{
    delete ui;
}

void FormActPro::changeEvent(QEvent *e)
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

void FormActPro::SetDelay(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormActPro::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

void FormActPro::SetType(int type)
{
	if (type == PRO_ACT_VERTIACL)
        ui->radioButton_ver->setChecked(true);
	else if (type == PRO_ACT_HOZIONTAL)
		ui->radioButton_hor->setChecked(true);
	else if (type == PRO_ACT_JIG_RELEASE)
		ui->radioButton_jig_r->setChecked(true);
	else
		ui->radioButton_jig_b->setChecked(true);
}

int FormActPro::GetType()
{
	if (ui->radioButton_ver->isChecked() == true)
        return PRO_ACT_VERTIACL;
	if (ui->radioButton_jig_b->isChecked() == true)
		return PRO_ACT_JIG_BIND;
	if (ui->radioButton_jig_r->isChecked() == true)
		return PRO_ACT_JIG_RELEASE;
    return PRO_ACT_HOZIONTAL;
}

void FormActPro::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->radioButton_hor->setEnabled(false);
        ui->radioButton_ver->setEnabled(false);
        ui->radioButton_jig_r->setEnabled(false);
        ui->radioButton_jig_b->setEnabled(false);
        ui->BtnHor->setEnabled(false);
        ui->BtnVer->setEnabled(false);
        ui->BtnJig_r->setEnabled(false);
        ui->BtnJig_b->setEnabled(false);
    }
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->radioButton_hor->setEnabled(true);
            ui->radioButton_ver->setEnabled(true);
            ui->radioButton_jig_r->setEnabled(true);
            ui->radioButton_jig_b->setEnabled(true);
            ui->BtnHor->setEnabled(true);
            ui->BtnVer->setEnabled(true);
            ui->BtnJig_r->setEnabled(true);
            ui->BtnJig_b->setEnabled(true);
        }
        else
        {
            ui->radioButton_hor->setEnabled(false);
            ui->radioButton_ver->setEnabled(false);
            ui->radioButton_jig_r->setEnabled(false);
            ui->radioButton_jig_b->setEnabled(false);
            ui->BtnHor->setEnabled(false);
            ui->BtnVer->setEnabled(false);
            ui->BtnJig_r->setEnabled(false);
            ui->BtnJig_b->setEnabled(false);
        }
    }
#if (FACTORY == FA_VICTOR_SPECIAL)              //2023-12-06
    ui->BtnVer->setVisible(false);
    ui->BtnHor->setVisible(false);
    ui->radioButton_ver->setText(tr("毛坯旋转"));
    ui->radioButton_hor->setText(tr("成品旋转"));
#endif
}

void FormActPro::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}

// 正臂回正信号槽
void FormActPro::armVer(void)
{
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
	// 执行正臂回正动作
	pModbus->ManualPro(PRO_ACT_VERTIACL);
}
// 正臂侧姿信号槽
void FormActPro::armHor(void)
{
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
	// 执行正臂侧姿动作
	pModbus->ManualPro(PRO_ACT_HOZIONTAL);
}
// 治具松开信号槽
void FormActPro::armJigR(void)
{
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
	// 执行正臂回正动作
	pModbus->ManualPro(PRO_ACT_JIG_RELEASE);
}
// 治具夹紧信号槽
void FormActPro::armJigB(void)
{
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
	// 执行正臂回正动作
	pModbus->ManualPro(PRO_ACT_JIG_BIND);
}
