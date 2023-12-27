#include "cmbprotocol.h"
#include "safeswitch.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "formvactvacuum.h"
#include "ui_formvactvacuum.h"

FormVActVacuum::FormVActVacuum(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormVActVacuum)
{
    ui->setupUi(this);
#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(9.99);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(99.9);
#endif
    pModbus = modbus;
}

FormVActVacuum::~FormVActVacuum()
{
    delete ui;
}

void FormVActVacuum::changeEvent(QEvent *e)
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

void FormVActVacuum::SetInterval(int interval)
{
	ui->BoxInterval->setValue(interval);
}

int FormVActVacuum::GetInterval()
{
	return ui->BoxInterval->value();
}

void FormVActVacuum::SetDelay(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormVActVacuum::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

void FormVActVacuum::SetType(int type)
{
	if (type == 1)
        ui->radioButton_on->setChecked(true);
    else
        ui->radioButton_off->setChecked(true);
}

int FormVActVacuum::GetType()
{
    if (ui->radioButton_on->isChecked())
        return 1;
	else
		return 0;
}

void FormVActVacuum::SetVar(int var)
{
    extOutport = var;
    ui->lineEdit_var->setText(xStringResource::GetVarName(extOutport));
}

int FormVActVacuum::GetVar()
{
    return extOutport;
}

void FormVActVacuum::SetInVar(int var)
{
    extInport = var;
    ui->lineEdit_var_in->setText(xStringResource::GetVarName(extInport));
}

int FormVActVacuum::GetInVar()
{
    return extInport;
}

void FormVActVacuum::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->lineEdit_var->setEnabled(false);
        ui->lineEdit_var_in->setEnabled(false);
        ui->BoxInterval->setEnabled(false);
    }
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->lineEdit_var->setEnabled(true);
            ui->lineEdit_var_in->setEnabled(true);
            ui->BoxInterval->setEnabled(true);
        }
        else
        {
            ui->lineEdit_var->setEnabled(false);
            ui->lineEdit_var_in->setEnabled(false);
            ui->BoxInterval->setEnabled(false);
        }
    }
}

// 选择扩展输出端口信号槽
void FormVActVacuum::selectPort(void)
{
    quint32 ret;
	if (xSelVar->DoForm(VARSEL_MASK_EOUT, ret) != QDialog::Accepted)
        return;
    extOutport = ret;
    ui->lineEdit_var->setText(xStringResource::GetVarName(extOutport));
}
// 选择扩展输出端口信号槽
void FormVActVacuum::selectPortIn(void)
{
    quint32 ret;
	if (xSelVar->DoForm(VARSEL_MASK_EIN, ret) != QDialog::Accepted)
        return;
    extInport = ret;
    ui->lineEdit_var_in->setText(xStringResource::GetVarName(extInport));
}
// 输入输出延时信号槽
void FormVActVacuum::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}
// 输入输出间隔信号槽
void FormVActVacuum::inputInterval(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxInterval->minimum(), ui->BoxInterval->maximum()) == QDialog::Accepted)
		ui->BoxInterval->setValue(value);
}
// 扩展输出端口打开信号槽
void FormVActVacuum::extOutOn(void)
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
void FormVActVacuum::extOutOff(void)
{
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
	// 关闭输出端口
	if (ui->lineEdit_var->text().isEmpty())
		return;
	pModbus->ManualExt(false, extOutport);
}
void FormVActVacuum::SetOutputCounter(quint16 var)
{
    outputcounter = var;
    ui->lineEditOutputCounter->setText(xStringResource::GetVarName(outputcounter));
}

quint16 FormVActVacuum::GetOutputCounter()
{
    return outputcounter;
}
void FormVActVacuum::SetInputCounter(quint16 var)
{
    inputcounter = var;
    ui->lineEditInputCounter->setText(xStringResource::GetVarName(inputcounter));
}

quint16 FormVActVacuum::GetInputCounter()
{
    return inputcounter;
}
