#include <assert.h>
#include <QButtonGroup>
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "formactsingleloop.h"
#include "ui_formactsingleloop.h"
#include "servoalias.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "xmessagebox.h"

FormActSingleLoop::FormActSingleLoop(QWidget *parent) :	QWidget(parent), ui(new Ui::FormActSingleLoop)
{
	ui->setupUi(this);
	retranslateUi();

    pAxesBtn = new QButtonGroup;
    pAxesBtn->addButton(ui->rBtnPaHor, AXIS_IDX_PHOR);
    pAxesBtn->addButton(ui->rBtnPaVer, AXIS_IDX_PVER);
    pAxesBtn->addButton(ui->rBtnTravel, AXIS_IDX_TRV);
    pAxesBtn->addButton(ui->rBtnRaVer, AXIS_IDX_RVER);
    pAxesBtn->addButton(ui->rBtnRaHor, AXIS_IDX_RHOR);
    pAxesBtn->addButton(ui->rBtnExt, AXIS_IDX_EXT);

    ui->labelCount->setEnabled(false);
    ui->lineEditCount->setEnabled(false);
    connect(pAxesBtn, SIGNAL(buttonClicked(int)), this, SLOT(AxesClick(int)));
    UpdateWidgetState();
}

FormActSingleLoop::~FormActSingleLoop()
{
	delete ui;
    delete pAxesBtn;
}


void FormActSingleLoop::changeEvent(QEvent *e)
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
void FormActSingleLoop::retranslateUi(void)
{
    ui->rBtnPaHor->setText(GetServoName(AXIS_IDX_PHOR));
    ui->rBtnPaVer->setText(GetServoName(AXIS_IDX_PVER));
    ui->rBtnTravel->setText(GetServoName(AXIS_IDX_TRV));
    ui->rBtnExt->setText(GetServoName(AXIS_IDX_EXT));
    ui->rBtnRaHor->setText(GetServoName(AXIS_IDX_RHOR));
    ui->rBtnRaVer->setText(GetServoName(AXIS_IDX_RVER));
/*
    if (CMBProtocol::IsSingleType())
    {
        ui->rBtnRaHor->setText(GetServoName(AXIS_IDX_RHOR));
        ui->rBtnRaVer->setText(GetServoName(AXIS_IDX_RVER));
    }
    else
    {
        ui->rBtnRaHor->setText(GetServoName(AXIS_IDX_RHOR));
        ui->rBtnRaVer->setText(GetServoName(AXIS_IDX_RVER));
    }*/
    UpdateWidgetState();
}

// 得到定位点数量
quint16 FormActSingleLoop::GetPosCount()
{
	return ui->BoxCnt->value();
}
// 设置定位点数量
void FormActSingleLoop::SetPosCount(quint16 count)
{
	ui->BoxCnt->setValue(count);
}

// 得到运行速度
quint8 FormActSingleLoop::GetSpeed()
{
	return ui->BoxHspd->value();
}
// 设置运行速度
void FormActSingleLoop::SetSpeed(quint8 speed)
{
	ui->BoxHspd->setValue(speed);
}

void FormActSingleLoop::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->rBtnPaHor->setEnabled(false);
        ui->rBtnPaVer->setEnabled(false);
        ui->rBtnRaHor->setEnabled(false);
        ui->rBtnRaVer->setEnabled(false);
        ui->rBtnTravel->setEnabled(false);
        ui->rBtnExt->setEnabled(false);
        ui->doubleSpinBox->setEnabled(true);
        ui->BoxHspd->setEnabled(true);
    }
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->BoxCnt->setEnabled(true);
            ui->rBtnPaVer->setEnabled(true);
            ui->rBtnTravel->setEnabled(true);
            if (!CMBProtocol::GetPaHorNotUse())
                ui->rBtnPaHor->setEnabled(true);
            else
                ui->rBtnPaHor->setEnabled(false);
            if (CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0))
                ui->rBtnRaHor->setEnabled(true);
            else
                ui->rBtnRaHor->setEnabled(false);
            if (CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0))
                ui->rBtnRaVer->setEnabled(true);
            else
                ui->rBtnRaVer->setEnabled(false);
            if (CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0))
                ui->rBtnExt->setEnabled(true);
            else
                ui->rBtnExt->setEnabled(false);
            ui->doubleSpinBox->setEnabled(true);
            ui->BoxTimes->setEnabled(true);
            ui->BoxInterval->setEnabled(true);
            ui->BoxHspd->setEnabled(true);
        }
        else
        {
            ui->BoxCnt->setEnabled(false);
            ui->rBtnPaHor->setEnabled(false);
            ui->rBtnPaVer->setEnabled(false);
            ui->rBtnRaHor->setEnabled(false);
            ui->rBtnRaVer->setEnabled(false);
            ui->rBtnTravel->setEnabled(false);
            ui->rBtnExt->setEnabled(false);
            ui->doubleSpinBox->setEnabled(true);
            ui->BoxTimes->setEnabled(false);
            ui->BoxInterval->setEnabled(false);
            ui->BoxHspd->setEnabled(true);
        }
    }
    if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
    {
        ui->BoxInterval->setDecimals(1);
        ui->BoxInterval->setMinimum(-3200.0);
        ui->BoxInterval->setMaximum(3200.0);
    }
    else
    {
        ui->BoxInterval->setDecimals(2);
        ui->BoxInterval->setMinimum(-320.00);
        ui->BoxInterval->setMaximum(320.00);
    }
}

// 输入定位点数量信号槽
void FormActSingleLoop::inputCnt(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxCnt->minimum(), ui->BoxCnt->maximum()) == QDialog::Accepted)
		ui->BoxCnt->setValue(value);
}
// 输入运行速度信号槽
void FormActSingleLoop::inputHspd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxHspd->minimum(), ui->BoxHspd->maximum()) == QDialog::Accepted)
		ui->BoxHspd->setValue(value);
}
void FormActSingleLoop::inputTimes(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxTimes->minimum(), ui->BoxTimes->maximum()) == QDialog::Accepted)
        ui->BoxTimes->setValue(value);
}
void FormActSingleLoop::inputInterval(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxInterval->minimum(), ui->BoxInterval->maximum()) == QDialog::Accepted)
        ui->BoxInterval->setValue(value);
}

// 输入第一点位置信号槽
void FormActSingleLoop::inputPos(void)
{
	DialogNumberPad numberPad;
	double value;
    if (pAxesBtn->checkedId() == AXIS_IDX_PHOR)
    {
#if PENDANT_PROTOCOL
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4) || (!CMBProtocol::GetRhorSrvUse()))
        {
            if (numberPad.DoFormPos(value, 0.0, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
                return;
        }
        else
        {
        if (numberPad.DoFormPos(value, 0.0, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
                return;
        }
#else
        if (numberPad.DoFormPos(value, 0.0, MAX_DISTANCE / 100.00) != QDialog::Accepted)
            return;
#endif
    }
    if (pAxesBtn->checkedId() == AXIS_IDX_PVER)
    {
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.0, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.0, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
    }
    if (pAxesBtn->checkedId() == AXIS_IDX_RHOR)
    {
#if PENDANT_PROTOCOL
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        {
            if (numberPad.DoFormPos(value, 0.0, CMBProtocol::GetHorInt() / 100.00) != QDialog::Accepted)
                return;
        }
        else
        {
            if (numberPad.DoFormPos(value, 0.0, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
                return;
        }
#else
        if (numberPad.DoFormPos(value, 0.0, MAX_DISTANCE / 100.00) != QDialog::Accepted)
            return;
#endif
    }
    if (pAxesBtn->checkedId() == AXIS_IDX_RVER)
    {
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.0, CMBProtocol::GetRaVerLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.0, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
    }
    if (pAxesBtn->checkedId() == AXIS_IDX_TRV)
    {
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.0, CMBProtocol::GetTravLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.0, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
    }
    if (pAxesBtn->checkedId() == AXIS_IDX_EXT)
    {
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.0, CMBProtocol::GetExteLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.0, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
    }
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        ui->doubleSpinBox->setValue(value);
	else
	{
        double diff = ui->doubleSpinBox->value() - value;
        if (diff < -5.00)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
            diff = -5.00;
            }
        else if (diff > 5.00)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
            diff = 5.00;
            }
        ui->doubleSpinBox->setValue(ui->doubleSpinBox->value() - diff);
	}
}
// 选择变量
void FormActSingleLoop::selectVar(void)
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_COUNTER, ret) != QDialog::Accepted)
        return;
    userVar = ret;
    ui->lineEditCount->setText(xStringResource::GetVarName(userVar));
}

quint16 FormActSingleLoop::GetVar()
{
    return userVar;
}
void FormActSingleLoop::SetVar(quint16 var)
{
    userVar = var;
    ui->lineEditCount->setText(xStringResource::GetVarName(userVar));
}


quint8 FormActSingleLoop::GetAxes()
{
    return pAxesBtn->checkedId();
}
void FormActSingleLoop::SetAxes(quint8 idx)
{
    pAxesBtn->button(idx)->setChecked(true);
}

void FormActSingleLoop::AxesClick(int axes)
{
    UpdateWidgetState();
}
// 每次点数
quint8 FormActSingleLoop::GetTimes()
{
    return ui->BoxTimes->value();
}
void FormActSingleLoop::SetTimes(quint8 times)
{
    ui->BoxTimes->setValue(times);
}
// 间隔
qint16 FormActSingleLoop::GetInterval()
{
    if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
        return qRound(ui->BoxInterval->value()*10.0);
    else
    return qRound(ui->BoxInterval->value()*100.00);
}
void FormActSingleLoop::SetInterval(qint16 interval)
{
    if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
        ui->BoxInterval->setValue((double)interval/10.0);
    else
    ui->BoxInterval->setValue((double)interval/100.00);
}
// 第一点位置
int FormActSingleLoop::GetFirstPos()
{
    return qRound(ui->doubleSpinBox->value() * 100.00);
}
void FormActSingleLoop::SetFirstPos(int pos)
{
    ui->doubleSpinBox->setValue((double)(pos / 100.0));
}
// 输入低速速度信号槽
void FormActSingleLoop::inputLspd(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxLspd->minimum(), ui->BoxLspd->maximum()) == QDialog::Accepted)
        ui->BoxLspd->setValue(value);
}
// 输入减速距离信号槽
void FormActSingleLoop::inputLdis(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxLowDis->minimum(), ui->BoxLowDis->maximum()) == QDialog::Accepted)
        ui->BoxLowDis->setValue(value);
}
// 得到减速速度
int FormActSingleLoop::GetDSpeed()
{
    return ui->BoxLspd->value();
}
// 设置减速速度
void FormActSingleLoop::SetDSpeed(int dspeed)
{
    ui->BoxLspd->setValue(dspeed);
}

// 得到减速距离
int FormActSingleLoop::GetDLen()
{
    return qRound(ui->BoxLowDis->value() * 100.00);
}
// 设置减速距离
void FormActSingleLoop::SetDLen(int len)
{
    ui->BoxLowDis->setValue((double)len / 100.00);
}
