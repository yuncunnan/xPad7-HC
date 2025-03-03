#include <QButtonGroup>
#include "cmbprotocol.h"
#include "safeswitch.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "formactassist.h"
#include "ui_formactassist.h"
#include "HardwareInterface.h"

FormActAssist::FormActAssist(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormActAssist)
{
    ui->setupUi(this);
    retranslateUi();
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);

#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(600.00);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(6000.0);
#endif
    pModbus = modbus;
    // 辅助设备选择按钮
    pAssist = new QButtonGroup;
    pAssist->addButton(ui->checkBoxOil, EM1_VAR_Y08);
    pAssist->addButton(ui->checkBoxConveyor, EM1_VAR_Y09);
    pAssist->addButton(ui->checkBoxReject, EM1_VAR_Y10);
}

FormActAssist::~FormActAssist()
{
    delete ui;
}

void FormActAssist::changeEvent(QEvent *e)
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
void FormActAssist::retranslateUi(void)
{
    if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        ui->checkBoxOil->setText(xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->checkBoxConveyor->setText(xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->checkBoxReject->setText(xStringResource::GetVarName(MAIN_VAR_Y14));
    }
    else
    {
        ui->checkBoxOil->setText(tr("打油") + xStringResource::GetVarName(EM1_VAR_Y08).right(6));
        ui->checkBoxConveyor->setText(tr("传送带") + xStringResource::GetVarName(EM1_VAR_Y09).right(6));
        ui->checkBoxReject->setText(tr("不良品") + xStringResource::GetVarName(EM1_VAR_Y10).right(6));
    }
}

void FormActAssist::SetInterval(int interval)
{
	ui->BoxInterval->setValue(interval);
}

int FormActAssist::GetInterval()
{
	return ui->BoxInterval->value();
}

void FormActAssist::SetDelay(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormActAssist::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

void FormActAssist::SetType(int type)
{
	if (type == 1)
        ui->radioButton_on->setChecked(true);
    else
        ui->radioButton_off->setChecked(true);
}

int FormActAssist::GetType()
{
    if (ui->radioButton_on->isChecked())
        return 1;
	else
		return 0;
}

void FormActAssist::SetOutput(int out)
{
    if (pAssist->button(out) == 0)
        return;
    pAssist->button(out)->setChecked(true);
    UpdateWidgetState();
}
int FormActAssist::GetOutput()
{
    return pAssist->checkedId();
}

void FormActAssist::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->radioButton_on->setEnabled(false);
        ui->BtnOn->setEnabled(false);
        ui->radioButton_off->setEnabled(false);
        ui->BtnOff->setEnabled(false);
        ui->BoxInterval->setEnabled(false);
    }
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->radioButton_on->setEnabled(true);
            ui->BtnOn->setEnabled(true);
            ui->radioButton_off->setEnabled(true);
            ui->BtnOff->setEnabled(true);
        }
        else
        {
            ui->radioButton_on->setEnabled(false);
            ui->BtnOn->setEnabled(false);
            ui->radioButton_off->setEnabled(false);
            ui->BtnOff->setEnabled(false);
        }
    }
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        ui->checkBoxOil->setVisible(false);
        ui->checkBoxConveyor->setVisible(false);
        ui->checkBoxReject->setVisible(false);
    }
    retranslateUi();
}

// 输入输出延时信号槽
void FormActAssist::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}
// 输入输出间隔信号槽
void FormActAssist::inputInterval(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxInterval->minimum(), ui->BoxInterval->maximum()) == QDialog::Accepted)
		ui->BoxInterval->setValue(value);
}
// 扩展输出端口打开信号槽
void FormActAssist::extOutOn(void)
{
    // 检查安全开关
    if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
        return;
    // 打开输出端口
    quint16 outselect;     // 治具选择
    outselect  = ((quint16)(ui->checkBoxOil->isChecked()?1:0)) << 0;
    outselect |= ((quint16)(ui->checkBoxConveyor->isChecked()?1:0)) << 1;
    outselect |= ((quint16)(ui->checkBoxReject->isChecked()?1:0)) << 2;
    if (outselect==0)return;
    pModbus->ManualExt(true, outselect);
}
// 扩展输出端口关闭信号槽
void FormActAssist::extOutOff(void)
{
    // 检查安全开关
    if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
        return;
    quint16 outselect;     // 治具选择
    outselect  = ((quint16)(ui->checkBoxOil->isChecked()?1:0)) << 0;
    outselect |= ((quint16)(ui->checkBoxConveyor->isChecked()?1:0)) << 1;
    outselect |= ((quint16)(ui->checkBoxReject->isChecked()?1:0)) << 2;
    // 关闭输出端口
    if (outselect==0)return;
    pModbus->ManualExt(false, outselect);
}
// 同扩展输出一样，固定到打油Y9 传送带Y10 不良品Y11
