#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "cmbprotocol.h"
#include "xstringresource.h"
#include "formbtnwait.h"
#include "ui_formbtnwait.h"

FormBtnWait::FormBtnWait(QWidget *parent) : QWidget(parent), ui(new Ui::FormBtnWait)
{
	ui->setupUi(this);
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);

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
    inport = EM1_VAR_X06;
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

FormBtnWait::~FormBtnWait()
{
	delete ui;
}

void FormBtnWait::changeEvent(QEvent *e)
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
bool FormBtnWait::EnterForm(void)
{
    init();
    UpdateWidgetState();
    show();
    return true;
}
void FormBtnWait::init()
{
    ui->lineEdit_var->setText(xStringResource::GetVarName(inport));
    ui->check_Invalid->setChecked(true);
    ui->BoxDelay->setValue(0.0);
}

int FormBtnWait::GetVar()
{
    return inport;
}

int FormBtnWait::GetVar2(bool &isconst)
{
    isconst = m_isconst;
    return inport2;
}

int FormBtnWait::GetInvalidSet(void)
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

int FormBtnWait::GetTimeout()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

int FormBtnWait::GetTimevalid()
{
    return qRound(ui->BoxValid->value() * (1000.0/TIME_BASE));
}

void FormBtnWait::UpdateWidgetState()
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
// 选择端口信号槽
void FormBtnWait::selectInport(void)
{
	quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_EIN | VARSEL_MASK_EOUT | VARSEL_MASK_SYSIN | VARSEL_MASK_SYSOUT | VARSEL_MASK_USER, ret) != QDialog::Accepted)
		return;
	inport = ret;
    ui->lineEdit_var->setText(xStringResource::GetVarName(inport));
}

void FormBtnWait::selectInport2()
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
void FormBtnWait::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
        ui->BoxDelay->setValue(value);
}

void FormBtnWait::inputValid()
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxValid->minimum(), ui->BoxValid->maximum()) == QDialog::Accepted)
        ui->BoxValid->setValue(value);
}
