#include "xconfig.h"
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "formactfor.h"
#include "ui_formactfor.h"

FormActFor::FormActFor(QWidget *parent) : QWidget(parent), ui(new Ui::FormActFor)
{
	ui->setupUi(this);
	ui->radioConst->setChecked(true);
	loopVar = VAR_TYPE_USR;
	ui->lineEditVar->setText(xStringResource::GetVarName(loopVar));
}

FormActFor::~FormActFor()
{
	delete ui;
}

void FormActFor::changeEvent(QEvent *e)
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

void FormActFor::SetValue(int value)
{
    if (ui->radioConst->isChecked() == true)
	{
		// 常数
		ui->BoxConst->setValue(value & 0x0000ffff);
	}
	else
	{
		// 变量
		loopVar = value;
		ui->lineEditVar->setText(xStringResource::GetVarName(loopVar));
	}
}

int FormActFor::GetValue()
{
	if (ui->radioConst->isChecked() == true)
	{
		// 常数
        return ui->BoxConst->value();
	}
	else
	{
		// 变量
		return loopVar;
	}
}

void FormActFor::SetType(int type)
{
	if (type == CODE_FOR_CONST)
	{
		ui->radioConst->setChecked(true);
		ui->BoxConst->setEnabled(true);
		ui->lineEditVar->setEnabled(false);
	}
	else
	{
		ui->radioVar->setChecked(true);
		ui->BoxConst->setEnabled(false);
		ui->lineEditVar->setEnabled(true);
	}
}

int FormActFor::GetType()
{
	if (ui->radioConst->isChecked() == true)
		return CODE_FOR_CONST;
	else
		return CODE_FOR_VAR;
}

// 选择循环变量信号槽
void FormActFor::selectVar(void)
{
	quint32 ret;
    if (xSelVar->DoForm((VARSEL_MASK_USER | VARSEL_MASK_COUNTER), ret) != QDialog::Accepted)
		return;
	loopVar = ret;
	ui->lineEditVar->setText(xStringResource::GetVarName(loopVar));
}
// 输入循环常数信号槽
void FormActFor::inputConst(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxConst->minimum(), ui->BoxConst->maximum()) == QDialog::Accepted)
		ui->BoxConst->setValue(value);
}
void FormActFor::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
	{
        ui->radioConst->setEnabled(false);
        ui->radioVar->setEnabled(false);
        ui->lineEditVar->setEnabled(false);
        ui->BoxConst->setEnabled(false);
	}
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->radioConst->setEnabled(true);
            ui->radioVar->setEnabled(true);
            ui->lineEditVar->setEnabled(true);
            ui->BoxConst->setEnabled(true);
        }
        else
        {
            ui->radioConst->setEnabled(false);
            ui->radioVar->setEnabled(false);
            ui->lineEditVar->setEnabled(false);
            ui->BoxConst->setEnabled(false);
        }
    }
}
