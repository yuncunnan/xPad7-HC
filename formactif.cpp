#include <QButtonGroup>
#include "cmbprotocol.h"
#include "dialogselectvariable.h"
#include "xconfig.h"
#include "xstringresource.h"
#include "xmessagebox.h"
#include "formactif.h"
#include "ui_formactif.h"
#include "dialognumberpad.h"

// 条件表达式第一个参数允许: 用户变量, 扩展IO, 系统变量, 系统IO
#define VARMASK_VAR		(VARSEL_MASK_USER | VARSEL_MASK_COUNTER | VARSEL_MASK_EIN | VARSEL_MASK_EOUT | VARSEL_MASK_SYS | VARSEL_MASK_SYSIN | VARSEL_MASK_SYSOUT)
// 条件表达式第二个参数允许: 用户变量, 系统变量, 常量
#define VARMASK_PAR		(VARSEL_MASK_USER | VARSEL_MASK_COUNTER | VARSEL_MASK_SYS | VARSEL_MASK_CONST)

FormActIf::FormActIf(QWidget *parent) : QWidget(parent), ui(new Ui::FormActIf)
{
    ui->setupUi(this);
	// 组织运算符按钮
	pOperator = new QButtonGroup;
	pOperator->addButton(ui->radioButton_dir, IF_TYPE_DIR);	// 直接条件
	pOperator->addButton(ui->radioButton_gt, IF_TYPE_GT);		// 大于条件
	pOperator->addButton(ui->radioButton_lt, IF_TYPE_LT);		// 小于条件
	pOperator->addButton(ui->radioButton_ge, IF_TYPE_GE);		// 大于等于条件
	pOperator->addButton(ui->radioButton_le, IF_TYPE_LE);		// 小于等于条件
	pOperator->addButton(ui->radioButton_eq, IF_TYPE_EQ);		// 等于条件
	pOperator->addButton(ui->radioButton_ne, IF_TYPE_NE);		// 不等于条件
	// 初始化界面显示状态
//	ui->lineEdit_para->setEnabled(pOperator->checkedId() != IF_TYPE_DIR);
	// 连接信号槽
	connect(pOperator, SIGNAL(buttonClicked(int)), this, SLOT(operatorClick(int)));
#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(600.00);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(6000.0);
#endif
}

FormActIf::~FormActIf()
{
    delete ui;
	delete pOperator;
}

void FormActIf::changeEvent(QEvent *e)
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

void FormActIf::SetVar(int var)
{
    varSet = var;
    ui->lineEdit_var->setText(xStringResource::GetVarName(varSet));
}

int FormActIf::GetVar()
{
	return varSet;
}

void FormActIf::SetType(int type)
{
	switch(type)
	{
	case IF_TYPE_GE:
		ui->radioButton_ge->setChecked(true);
		break;
	case IF_TYPE_GT:
		ui->radioButton_gt->setChecked(true);
		break;
	case IF_TYPE_LE:
		ui->radioButton_le->setChecked(true);
		break;
	case IF_TYPE_LT:
		ui->radioButton_lt->setChecked(true);
		break;
	case IF_TYPE_NE:
		ui->radioButton_ne->setChecked(true);
		break;
	case IF_TYPE_EQ:
		ui->radioButton_eq->setChecked(true);
		break;
	default:
		ui->radioButton_dir->setChecked(true);
		break;
	}
	operatorClick(type);
}

int FormActIf::GetType()
{
	if (ui->radioButton_ge->isChecked())
		return IF_TYPE_GE;
	if (ui->radioButton_gt->isChecked())
		return IF_TYPE_GT;
	if (ui->radioButton_eq->isChecked())
		return IF_TYPE_EQ;
	if (ui->radioButton_lt->isChecked())
		return IF_TYPE_LT;
	if (ui->radioButton_le->isChecked())
		return IF_TYPE_LE;
	if (ui->radioButton_ne->isChecked())
		return IF_TYPE_NE;
	return IF_TYPE_DIR;
}

void FormActIf::SetPara(int para, bool isconst)
{
    m_isconst = isconst;
    parSet = para;
    if (m_isconst)
		// 常数
        ui->lineEdit_para->setText(QString::number(parSet));
	else
		// 变量
		ui->lineEdit_para->setText(xStringResource::GetVarName(parSet));
}

int FormActIf::GetPara(bool &isconst)
{
    isconst = m_isconst;
    return parSet;
}

// 运算符按钮点击信号槽
void FormActIf::operatorClick(int id)
{
	if (id == IF_TYPE_DIR)
	{
		ui->labelOperator->clear();
		ui->lineEdit_para->setEnabled(false);
	}
	else
	{
		ui->labelOperator->setText(pOperator->button(id)->text());
		ui->lineEdit_para->setEnabled(true);
	}
}

// 选择第一个参数信号槽
void FormActIf::selectVariable(void)
{
	quint32 ret;
	if (xSelVar->DoForm(VARMASK_VAR, ret) != QDialog::Accepted)
		return;
	varSet = ret;
    ui->lineEdit_var->setText(xStringResource::GetVarName(varSet));
}

// 选择第二个参数信号槽
void FormActIf::selectParameter(void)
{
    // 原程序是将parSet前16位分配给变量，后16位分配给常量
    // 现要求常量变量都是32位
	quint32 ret;
    if (xSelVar->DoForm(VARMASK_PAR, ret, &m_isconst) != QDialog::Accepted)
		return;
	parSet = ret;
    if (m_isconst)
		// 常数
        ui->lineEdit_para->setText(QString::number(parSet));
	else
		// 变量
		ui->lineEdit_para->setText(xStringResource::GetVarName(parSet));
}

void FormActIf::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->lineEdit_var->setEnabled(false);
        ui->lineEdit_para->setEnabled(true);
        ui->groupBoxOperator->setEnabled(false);
    }
    else
    {

        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->groupExpression->setEnabled(true);
            ui->groupBoxOperator->setEnabled(true);
        }
        else
        {
            ui->groupExpression->setEnabled(false);
            ui->groupBoxOperator->setEnabled(false);
        }
    }
    if (CMBProtocol::GetFunctions(SUB_FUN2_IFTIME))
    {
        ui->labelDelay->setVisible(true);
        ui->BoxDelay->setVisible(true);
    }
    else
    {
        ui->labelDelay->setVisible(false);
        ui->BoxDelay->setVisible(false);
    }
}

void FormActIf::SetTimeout(int delay)
{
	ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormActIf::GetTimeout()
{
	return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

void FormActIf::InputDelay()
{
	DialogNumberPad numberPad;
	double value;
	if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}
