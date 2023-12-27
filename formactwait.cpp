#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "cmbprotocol.h"
#include "xstringresource.h"
#include "formactwait.h"
#include "ui_formactwait.h"

FormActWait::FormActWait(QWidget *parent) : QWidget(parent), ui(new Ui::FormActWait)
{
	ui->setupUi(this);
#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(600.00);
    ui->BoxValid->setDecimals(2);
    ui->BoxValid->setMaximum(600.00);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(6000.0);
    ui->BoxValid->setDecimals(1);
    ui->BoxValid->setMaximum(6000.0);
#endif
    ui->check_Invalid->setVisible(true);
    ui->check_valid->setVisible(true);
    if(CMBProtocol::GetFunctions(SUB_FUN2_WAIT_VAR2))
    {
        ui->check_greater->setVisible(true);
        ui->check_less->setVisible(true);
        ui->check_unequal->setVisible(true);
        ui->check_equal->setVisible(true);
        ui->lineEdit_var2->setVisible(true);
        ui->labelSignal2->setVisible(true);
    }
    else
    {
        ui->check_greater->setVisible(false);
        ui->check_less->setVisible(false);
        ui->check_unequal->setVisible(false);
        ui->check_equal->setVisible(false);
        ui->lineEdit_var2->setVisible(false);
        ui->labelSignal2->setVisible(false);
    }
    ui->check_Invalid->setChecked(true);
}

FormActWait::~FormActWait()
{
	delete ui;
}

void FormActWait::changeEvent(QEvent *e)
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

int FormActWait::GetVar()
{
    return inport;
}

int FormActWait::GetVar2(bool &isconst)
{
    isconst = m_isconst;
    return inport2;
}

void FormActWait::SetVar(int var)
{
	inport = var;
	ui->lineEdit_var->setText(xStringResource::GetVarName(inport));
    ui->lineEdit_var2->setText(xStringResource::GetVarName(inport));
}

void FormActWait::SetVar2(int var, bool isconst)
{
    m_isconst = isconst;
    inport2 = var;
    if (m_isconst)
        // 常数
        ui->lineEdit_var2->setText(QString::number(inport2));
    else
        // 变量
        ui->lineEdit_var2->setText(xStringResource::GetVarName(inport2));
}

int FormActWait::GetInvalidSet(void)
{
    if(CMBProtocol::GetFunctions(SUB_FUN2_WAIT_VAR2))
    {
        if (ui->check_valid->isChecked())
            return 0;
        else if (ui->check_Invalid->isChecked())
            return 1;
        else if (ui->check_greater->isChecked())
            return 2;
        else if (ui->check_less->isChecked())
            return 3;
        else if (ui->check_unequal->isChecked())
            return 4;
        else if (ui->check_equal->isChecked())
            return 5;
    }
    else
    {
        if (ui->check_Invalid->isChecked())
            return 1;
        else
            return 0;
    }
}

void FormActWait::SetInvalidSet(int invalid)
{
    if(invalid==0)
        ui->check_valid->setChecked(true);
    else if(invalid==1)
        ui->check_Invalid->setChecked(true);
    else if(invalid==2)
        ui->check_greater->setChecked(true);
    else if(invalid==3)
        ui->check_less->setChecked(true);
    else if(invalid==4)
        ui->check_unequal->setChecked(true);
    else if(invalid==5)
        ui->check_equal->setChecked(true);
}

int FormActWait::GetTimeout()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

int FormActWait::GetTimevalid()
{
    return qRound(ui->BoxValid->value() * (1000.0/TIME_BASE));
}

void FormActWait::SetTimeOut(int timeout)
{
    ui->BoxDelay->setValue((double)timeout / (1000.0/TIME_BASE));
}

void FormActWait::SetTimevalid(int timevalid)
{
    ui->BoxValid->setValue((double)timevalid / (1000.0/TIME_BASE));
}

void FormActWait::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->lineEdit_var->setEnabled(false);
    }
    else
    {
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
            ui->lineEdit_var->setEnabled(true);
	else
            ui->lineEdit_var->setEnabled(false);
    }
}
/*
// 使用超时设置状态改变信号槽
void FormActWait::checkChanged(int state)
{
	if (state == Qt::Unchecked)
	{
		ui->labelDelay->setEnabled(false);
		ui->BtnDelaySub->setEnabled(false);
		ui->BtnDelayAdd->setEnabled(false);
		ui->BoxDelay->setEnabled(false);
	}
	else if (state == Qt::Checked)
	{
		ui->labelDelay->setEnabled(true);
		ui->BtnDelaySub->setEnabled(true);
		ui->BtnDelayAdd->setEnabled(true);
		ui->BoxDelay->setEnabled(true);
	}
}
*/
// 选择端口信号槽
void FormActWait::selectInport(void)
{
	quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_EIN | VARSEL_MASK_EOUT | VARSEL_MASK_SYSIN | VARSEL_MASK_SYSOUT | VARSEL_MASK_USER, ret) != QDialog::Accepted)
		return;
	inport = ret;
    ui->lineEdit_var->setText(xStringResource::GetVarName(inport));
}

void FormActWait::selectInport2()
{
    quint32 ret;
    if (xSelVar->DoForm((VARSEL_MASK_USER | VARSEL_MASK_COUNTER | VARSEL_MASK_SYS | VARSEL_MASK_CONST), ret, &m_isconst) != QDialog::Accepted)
        return;
    inport2 = ret;
    if (m_isconst)
        // 常数
        ui->lineEdit_var2->setText(QString::number(inport2));
    else
        // 变量
        ui->lineEdit_var2->setText(xStringResource::GetVarName(inport2));


//    quint32 ret;
//       if (xSelVar->DoForm((VARSEL_MASK_USER | VARSEL_MASK_COUNTER | VARSEL_MASK_CONST), ret) != QDialog::Accepted)//VARSEL_MASK_USER
//     return;
//    inport2 = ret;
//    ui->lineEdit_var2->setText(xStringResource::GetVarName(inport2));
}
// 输入超时时间信号槽
void FormActWait::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
        ui->BoxDelay->setValue(value);
}

void FormActWait::inputValid()
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxValid->minimum(), ui->BoxValid->maximum()) == QDialog::Accepted)
        ui->BoxValid->setValue(value);
}
