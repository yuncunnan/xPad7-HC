#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "cmbprotocol.h"
#include "xstringresource.h"
#include "formactextin.h"
#include "ui_formactextin.h"

FormActExtIn::FormActExtIn(QWidget *parent) : QWidget(parent), ui(new Ui::FormActExtIn)
{
    ui->setupUi(this);
    ui->labelCounter->setEnabled(false);
    ui->lineEditCounter->setEnabled(false);
}

FormActExtIn::~FormActExtIn()
{
    delete ui;
}

void FormActExtIn::changeEvent(QEvent *e)
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

void FormActExtIn::SetInterval(int interval)
{
	ui->BoxInterval->setValue(interval);
}

int FormActExtIn::GetInterval()
{
	return ui->BoxInterval->value();
}

void FormActExtIn::SetType(int type)
{
    if (type == 1)
        ui->radioButton_check->setChecked(true);
    else if (type == 3)
        ui->radioButton_checkUseless->setChecked(true);
    else
        ui->radioButton_uncheck->setChecked(true);
}

int FormActExtIn::GetType()
{
    if (ui->radioButton_check->isChecked())
		return 1;
    else if (ui->radioButton_checkUseless->isChecked())
        return 3;
	else
        return 0;
}

void FormActExtIn::SetVar(int var)
{
	extInport = var;
	ui->lineEdit_var->setText(xStringResource::GetVarName(extInport));
}

int FormActExtIn::GetVar()
{
	return extInport;
}

// 选择扩展输入端口信号槽
void FormActExtIn::selectPort(void)
{
	quint32 ret;
	if (xSelVar->DoForm(VARSEL_MASK_EIN, ret) != QDialog::Accepted)
		return;
	extInport = ret;
	ui->lineEdit_var->setText(xStringResource::GetVarName(extInport));
}

// 输入间隔参数信号槽
void FormActExtIn::inputInterval(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxInterval->minimum(), ui->BoxInterval->maximum()) == QDialog::Accepted)
		ui->BoxInterval->setValue(value);
}
void FormActExtIn::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
	{
        ui->lineEdit_var->setEnabled(false);
        ui->labelPort->setEnabled(false);
        ui->radioButton_check->setEnabled(false);
        ui->radioButton_uncheck->setEnabled(false);
    }
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->lineEdit_var->setEnabled(true);
            ui->labelPort->setEnabled(true);
            ui->radioButton_check->setEnabled(true);
            ui->radioButton_uncheck->setEnabled(true);
        }
        else
        {
            ui->lineEdit_var->setEnabled(false);
            ui->labelPort->setEnabled(false);
            ui->radioButton_check->setEnabled(false);
            ui->radioButton_uncheck->setEnabled(false);
        }
    }
#if PENDANT_PROTOCOL
    if (CMBProtocol::GetFunctions(SUB_IN_ANTI_CHECK_HOME_TAIL_LOOP_FREE))
        ui->radioButton_checkUseless->setVisible(true);
    else
        ui->radioButton_checkUseless->setVisible(false);
#else
    ui->radioButton_checkUseless->setVisible(true);
#endif
}
// 选择变量
void FormActExtIn::selectCounter(void)
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_COUNTER, ret) != QDialog::Accepted)
        return;
    counter = ret;
    ui->lineEditCounter->setText(xStringResource::GetVarName(counter));
}
void FormActExtIn::SetCounter(quint16 var)
{
    counter = var;
    ui->lineEditCounter->setText(xStringResource::GetVarName(counter));
}

quint16 FormActExtIn::GetCounter()
{
    return counter;
}
