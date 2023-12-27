#include <QButtonGroup>
#include "xconfig.h"
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "formactoperate.h"
#include "ui_formactoperate.h"

FormActOperate::FormActOperate(QWidget *parent) : QWidget(parent), ui(new Ui::FormActOperate)
{
	ui->setupUi(this);
	pOpr = new QButtonGroup;
    pOpr->addButton(ui->radioAssign, OPR_TYPE_ASSIGN);
    pOpr->addButton(ui->radioPlus, OPR_TYPE_ADD);
    pOpr->addButton(ui->radioSub, OPR_TYPE_SUB);
    pOpr->addButton(ui->radioMul, OPR_TYPE_MUL);
    pOpr->addButton(ui->radioDiv, OPR_TYPE_DIV);
    pOpr->addButton(ui->radioMod, OPR_TYPE_MOD);
    // 连接信号槽
    connect(pOpr, SIGNAL(buttonClicked(int)), this, SLOT(idChanged(int)));
}

FormActOperate::~FormActOperate()
{
	delete ui;
	delete pOpr;
}

void FormActOperate::changeEvent(QEvent *e)
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

void FormActOperate::SetVar(int var)
{
	usrVar = var;
	ui->lineEdit_Var->setText(xStringResource::GetVarName(usrVar));
}

int FormActOperate::GetVar()
{
	return usrVar;
}

void FormActOperate::SetPara(int para)
{
    ui->BoxValue->setValue(para);
}

int FormActOperate::GetPara()
{
    return ui->BoxValue->value();
}

void FormActOperate::SetType(int type)
{
	pOpr->button(type)->setChecked(true);
}

int FormActOperate::GetType()
{
	return pOpr->checkedId();
}

void FormActOperate::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->groupBoxOperate->setEnabled(false);
        ui->labelValue->setEnabled(false);
        ui->labelVar->setEnabled(false);
        ui->lineEdit_Var->setEnabled(false);
    }
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->groupBoxOperate->setEnabled(true);
            ui->labelValue->setEnabled(true);
            ui->labelVar->setEnabled(true);
            ui->lineEdit_Var->setEnabled(true);
            ui->BoxValue->setEnabled(true);
        }
        else
        {
            ui->groupBoxOperate->setEnabled(false);
            ui->labelValue->setEnabled(false);
            ui->labelVar->setEnabled(false);
            ui->lineEdit_Var->setEnabled(false);
            ui->BoxValue->setEnabled(false);
        }
    }
}

// 选择用户变量信号槽
void FormActOperate::selectVar(void)
{
	quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_USER, ret) != QDialog::Accepted)
		return;
	usrVar = ret;
	ui->lineEdit_Var->setText(xStringResource::GetVarName(usrVar));
}
// 输入操作数信号槽
void FormActOperate::inputValue(void)
{

	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxValue->minimum(), ui->BoxValue->maximum()) == QDialog::Accepted)
		ui->BoxValue->setValue(value);
}

void FormActOperate::idChanged(int checkid)
{
    // 如果是加减乘除设置最小值为1， 赋值最小值为0
    if ((checkid == OPR_TYPE_ADD) || (checkid == OPR_TYPE_SUB) || (checkid == OPR_TYPE_MOD) || (checkid == OPR_TYPE_MUL) || (checkid == OPR_TYPE_DIV))
    {
        ui->BoxValue->setMinimum(1);
        ui->BoxValue->setValue(1);
    }
    else
    {
        ui->BoxValue->setMinimum(0);
        ui->BoxValue->setValue(0);
    }
    UpdateWidgetState();
}
