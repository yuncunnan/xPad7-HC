#include "cmbprotocol.h"
#include "safeswitch.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "formactextout.h"
#include "ui_formactextout.h"

FormActExtOut::FormActExtOut(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormActExtOut)
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
    ui->labelCounter->setEnabled(false);
    ui->lineEditCounter->setEnabled(false);
}

FormActExtOut::~FormActExtOut()
{
    delete ui;
}

void FormActExtOut::changeEvent(QEvent *e)
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

void FormActExtOut::SetInterval(int interval)
{
	ui->BoxInterval->setValue(interval);
}

int FormActExtOut::GetInterval()
{
	return ui->BoxInterval->value();
}

void FormActExtOut::SetDelay(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormActExtOut::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

void FormActExtOut::SetType(int type)
{
	if (type == 1)
        ui->radioButton_on->setChecked(true);
    else if (type == 2)
        ui->radioButton_pulse->setChecked(true);
    else if (type == 3)
        ui->radioButton_NOT->setChecked(true);
    else
        ui->radioButton_off->setChecked(true);
}

int FormActExtOut::GetType()
{
    if (ui->radioButton_on->isChecked())
        return 1;
    if (ui->radioButton_pulse->isChecked())
        return 2;
    if (ui->radioButton_NOT->isChecked())
        return 3;
    else
		return 0;
}

void FormActExtOut::SetVar(int var)
{
	extOutport = var;
	ui->lineEdit_var->setText(xStringResource::GetVarName(extOutport));
}

int FormActExtOut::GetVar()
{
	return extOutport;
}

// 选择扩展输出端口信号槽
void FormActExtOut::selectPort(void)
{
	quint32 ret;
	if (xSelVar->DoForm(VARSEL_MASK_EOUT, ret) != QDialog::Accepted)
		return;
	extOutport = ret;
	ui->lineEdit_var->setText(xStringResource::GetVarName(extOutport));
}
// 输入输出延时信号槽
void FormActExtOut::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}
// 输入输出间隔信号槽
void FormActExtOut::inputInterval(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxInterval->minimum(), ui->BoxInterval->maximum()) == QDialog::Accepted)
		ui->BoxInterval->setValue(value);
}
// 扩展输出端口打开信号槽
void FormActExtOut::extOutOn(void)
{
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
	// 打开输出端口
	if (ui->lineEdit_var->text().isEmpty())
		return;
	pModbus->ManualExt(true, extOutport);
}
// 扩展输出端口关闭信号槽
void FormActExtOut::extOutOff(void)
{
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
	// 关闭输出端口
	if (ui->lineEdit_var->text().isEmpty())
		return;
	pModbus->ManualExt(false, extOutport);
}
void FormActExtOut::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
	{
        ui->lineEdit_var->setEnabled(false);
        ui->labelPort->setEnabled(false);
        ui->radioButton_on->setEnabled(false);
        ui->radioButton_off->setEnabled(false);
        ui->radioButton_pulse->setEnabled(false);
        ui->radioButton_NOT->setEnabled(false);
        ui->BtnOn->setEnabled(false);
        ui->BtnOff->setEnabled(false);
    }
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->lineEdit_var->setEnabled(true);
            ui->labelPort->setEnabled(true);
            ui->radioButton_on->setEnabled(true);
            ui->radioButton_off->setEnabled(true);
            ui->radioButton_pulse->setEnabled(true);
            ui->radioButton_NOT->setEnabled(true);
            ui->BtnOn->setEnabled(true);
            ui->BtnOff->setEnabled(true);
        }
        else
        {
            ui->lineEdit_var->setEnabled(false);
            ui->labelPort->setEnabled(false);
            ui->radioButton_on->setEnabled(false);
            ui->radioButton_off->setEnabled(false);
            ui->radioButton_pulse->setEnabled(false);
            ui->radioButton_NOT->setEnabled(false);
            ui->BtnOn->setEnabled(false);
            ui->BtnOff->setEnabled(false);
        }
    }
}
// 选择变量
void FormActExtOut::SetCounter(quint16 var)
{
    counter = var;
    ui->lineEditCounter->setText(xStringResource::GetVarName(counter));
}

quint16 FormActExtOut::GetCounter()
{
    return counter;
}
