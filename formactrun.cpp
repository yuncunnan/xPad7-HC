﻿#include "xconfig.h"
#include "safeswitch.h"
#include "xioport.h"
#include "dialognumberpad.h"
#include "cmbprotocol.h"
#include "formactrun.h"
#include "ui_formactrun.h"
#include "HardwareInterface.h"

FormActRun::FormActRun(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormActRun)
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

#if (FACTORY == FA_KAIBOER)
    ui->radioButton_adv->setText(tr("引拔退"));
    ui->radioButton_ret->setText(tr("引拔进"));
#else
    ui->radioButton_adv->setText(tr("引拔进"));
    ui->radioButton_ret->setText(tr("引拔退"));
#endif
}

FormActRun::~FormActRun()
{
	delete ui;
}

void FormActRun::changeEvent(QEvent *e)
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

void FormActRun::SetDelay(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormActRun::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

void FormActRun::SetType(int type)
{
	if (type == RUN_ACT_ASCENT)
		ui->radioButton_asc->setChecked(true);
    if (type == RUN_ACT_ADVANCE)
		ui->radioButton_adv->setChecked(true);
	if (type == RUN_ACT_RETURN)
		ui->radioButton_ret->setChecked(true);
    if (type == RUN_ACT_DESCENT)
        ui->radioButton_des->setChecked(true);
    if (type == RUN_ACT_VERTIACL)
        ui->radioVer->setChecked(true);
    if (type == RUN_ACT_HORIZONTAL)
        ui->radioHor->setChecked(true);

}

int FormActRun::GetType()
{
	if (ui->radioButton_asc->isChecked())
		return RUN_ACT_ASCENT;
    if (ui->radioButton_adv->isChecked())
		return RUN_ACT_ADVANCE;
	if (ui->radioButton_ret->isChecked())
		return RUN_ACT_RETURN;
    if (ui->radioHor->isChecked())
        return RUN_ACT_HORIZONTAL;
    if (ui->radioVer->isChecked())
        return RUN_ACT_VERTIACL;
    return RUN_ACT_DESCENT;
}

void FormActRun::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->BtnRotateHor->setEnabled(false);
        ui->BtnRotateVer->setEnabled(false);
        ui->radioVer->setEnabled(false);
        ui->radioHor->setEnabled(false);
        ui->BtnRaHor->setEnabled(false);
        ui->BtnVer->setEnabled(false);
        ui->radioButton_asc->setEnabled(false);
        ui->radioButton_adv->setEnabled(false);
        ui->radioButton_des->setEnabled(false);
        ui->radioButton_ret->setEnabled(false);
    }
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->BtnRotateHor->setEnabled(CMBProtocol::GetRunRotateUse());
            ui->BtnRotateVer->setEnabled(CMBProtocol::GetRunRotateUse());
            ui->radioVer->setEnabled(CMBProtocol::GetRunRotateUse());
            ui->radioHor->setEnabled(CMBProtocol::GetRunRotateUse());
            ui->BtnRaHor->setEnabled(CMBProtocol::GetRunnerUse());
            ui->BtnVer->setEnabled(CMBProtocol::GetRunnerUse());
            ui->radioButton_asc->setEnabled(CMBProtocol::GetRunnerUse());
            ui->radioButton_adv->setEnabled(CMBProtocol::GetRunnerUse());
            ui->radioButton_des->setEnabled(CMBProtocol::GetRunnerUse());
            ui->radioButton_ret->setEnabled(CMBProtocol::GetRunnerUse());
            }
            else
            {
                ui->BtnRotateHor->setEnabled(false);
                ui->BtnRotateVer->setEnabled(false);
                ui->radioVer->setEnabled(false);
                ui->radioHor->setEnabled(false);
                ui->BtnRaHor->setEnabled(false);
                ui->BtnVer->setEnabled(false);
                ui->radioButton_asc->setEnabled(false);
                ui->radioButton_adv->setEnabled(false);
                ui->radioButton_des->setEnabled(false);
                ui->radioButton_ret->setEnabled(false);
            }
        }
#if (FACTORY == FA_VICTOR_SPECIAL)              //2023-12-06
    ui->BtnRotateVer->setVisible(false);
    ui->BtnRotateHor->setVisible(false);
    ui->radioVer->setText(tr("毛坯旋转"));
    ui->radioHor->setText(tr("成品旋转"));
#endif
}

void FormActRun::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}

// 副臂引拔控制信号槽
void FormActRun::armAdvRet(void)
{
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
	// 执行副臂引拔控制指令
	if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
	{
		if (xIoPort::GetOut(RBT_VAR_OUT_RUN_ADV) == true)
			pModbus->ManualRun(RUN_ACT_RETURN);
		else
			pModbus->ManualRun(RUN_ACT_ADVANCE);
	}
	else
	{
    if (xIoPort::GetOut(RBT_VAR_OUT_RUN_RET) == true)
		pModbus->ManualRun(RUN_ACT_ADVANCE);
	else
		pModbus->ManualRun(RUN_ACT_RETURN);
	}
}
// 副臂上下控制信号槽
void FormActRun::armAscDes(void)
{	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
	// 执行副臂上下控制指令
    if (xIoPort::GetOut(RBT_VAR_OUT_RUN_DES) == true)
		pModbus->ManualRun(RUN_ACT_ASCENT);
	else
		pModbus->ManualRun(RUN_ACT_DESCENT);
}
// 副臂倒角控制信号槽
void FormActRun::armRotHor(void)
{	// 检查安全开关
    if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
        return;
        pModbus->ManualRun(RUN_ACT_HORIZONTAL);
}
void FormActRun::armRotVer(void)
{	// 检查安全开关
    if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
        return;
        pModbus->ManualRun(RUN_ACT_VERTIACL);
}
