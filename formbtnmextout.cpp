#include "safeswitch.h"
#include "xconfig.h"
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "formbtnmextout.h"
#include "ui_formbtnmextout.h"

FormBtnMExtOut::FormBtnMExtOut(QWidget *parent) : QWidget(parent), ui(new Ui::FormBtnMExtOut)
{
    ui->setupUi(this);
    retranslateUi();
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);
#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(9.99);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(99.9);
#endif
}

FormBtnMExtOut::~FormBtnMExtOut()
{
    delete ui;
}

void FormBtnMExtOut::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
        retranslateUi();
        break;
	default:
		break;
	}
}
void FormBtnMExtOut::retranslateUi(void)
{
}

void FormBtnMExtOut::selectPort()
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_EOUT, ret) != QDialog::Accepted)
        return;
    extOutport = ret;
    ui->lineEdit_var->setText(xStringResource::GetVarName(extOutport));
}
bool FormBtnMExtOut::EnterForm(void)
{
    init();
    UpdateWidgetState();
    show();
    return true;
}
void FormBtnMExtOut::init(void)
{
    ui->radioButton_on->setChecked(true);
    ui->BoxDelay->setValue(0.5);
    ui->labelCounter->setVisible(false);
    ui->lineEditCounter->setVisible(false);

}

int FormBtnMExtOut::GetType()
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

quint16 FormBtnMExtOut::GetCounter()
{
}

int FormBtnMExtOut::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

int FormBtnMExtOut::GetInterval()
{
    return ui->BoxInterval->value();
}


void FormBtnMExtOut::UpdateWidgetState()
{
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        ui->radioButton_on->setEnabled(true);
        ui->radioButton_off->setEnabled(true);
        ui->radioButton_pulse->setEnabled(true);
    }
    else
    {
        ui->radioButton_on->setEnabled(false);
        ui->radioButton_off->setEnabled(false);
        ui->radioButton_pulse->setEnabled(false);
    }
}

// 输入输出延时信号槽
void FormBtnMExtOut::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
        ui->BoxDelay->setValue(value);
}

void FormBtnMExtOut::inputInterval()
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxInterval->minimum(), ui->BoxInterval->maximum()) == QDialog::Accepted)
        ui->BoxInterval->setValue(value);
}

//void FormBtnMExtOut::extOutOn()
//{
//    // 检查安全开关
//    if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
//        return;
//    // 打开输出端口
//    if (ui->lineEdit_var->text().isEmpty())
//        return;
//    CMBProtocol::ManualExt(true, extOutport);
//}

//void FormBtnMExtOut::extOutOff()
//{
//    // 检查安全开关
//    if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
//        return;
//    // 关闭输出端口
//    if (ui->lineEdit_var->text().isEmpty())
//        return;
//    CMBProtocol::ManualExt(false, extOutport);
//}


int FormBtnMExtOut::GetVar()
{
    return extOutport;
}
