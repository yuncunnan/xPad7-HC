#include <assert.h>
#include <QButtonGroup>
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "formactsingleloopfree.h"
#include "ui_formactsingleloopfree.h"
#include "servoalias.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "xmessagebox.h"
#include <QDebug>

FormActSingleLoopFree::FormActSingleLoopFree(QWidget *parent) :	QWidget(parent), ui(new Ui::FormActSingleLoopFree)
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

    currentPos = 1;
    ui->lineEdit->setText(QString::number((currentPos)));
    ui->BoxPos->setValue((double)pos[currentPos-1] / 100.0);
    UpdateWidgetState();
}

FormActSingleLoopFree::~FormActSingleLoopFree()
{
	delete ui;
    delete pAxesBtn;
}


void FormActSingleLoopFree::changeEvent(QEvent *e)
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
void FormActSingleLoopFree::retranslateUi(void)
{
    ui->rBtnPaHor->setText(GetServoName(AXIS_IDX_PHOR));
    ui->rBtnPaVer->setText(GetServoName(AXIS_IDX_PVER));
    ui->rBtnTravel->setText(GetServoName(AXIS_IDX_TRV));
    ui->rBtnExt->setText(GetServoName(AXIS_IDX_EXT));
    ui->rBtnRaHor->setText(GetServoName(AXIS_IDX_RHOR));
    ui->rBtnRaVer->setText(GetServoName(AXIS_IDX_RVER));
    UpdateWidgetState();
}

// 得到定位点数量
quint16 FormActSingleLoopFree::GetPosCount()
{
	return ui->BoxCnt->value();
}
// 设置定位点数量
void FormActSingleLoopFree::SetPosCount(quint16 count)
{
	ui->BoxCnt->setValue(count);
}

// 得到运行速度
quint8 FormActSingleLoopFree::GetSpeed()
{
	return ui->BoxHspd->value();
}
// 设置运行速度
void FormActSingleLoopFree::SetSpeed(quint8 speed)
{
	ui->BoxHspd->setValue(speed);
}

void FormActSingleLoopFree::UpdateWidgetState()
{
    ui->BoxPos->setValue((double)pos[currentPos-1] / 100.0);

    if (CMBProtocol::GetTemplateUse())
    {
        ui->rBtnPaHor->setEnabled(false);
        ui->rBtnPaVer->setEnabled(false);
        ui->rBtnRaHor->setEnabled(false);
        ui->rBtnRaVer->setEnabled(false);
        ui->rBtnTravel->setEnabled(false);
        ui->rBtnExt->setEnabled(false);
        ui->BoxCnt->setEnabled(false);
        ui->BoxTimes->setEnabled(false);
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
            ui->BoxTimes->setEnabled(true);
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
             ui->BoxTimes->setEnabled(false);
           ui->BoxHspd->setEnabled(true);
        }
    }
}

// 输入定位点数量信号槽
void FormActSingleLoopFree::inputCnt(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxCnt->minimum(), ui->BoxCnt->maximum()) == QDialog::Accepted)
		ui->BoxCnt->setValue(value);
}
// 输入运行速度信号槽
void FormActSingleLoopFree::inputHspd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxHspd->minimum(), ui->BoxHspd->maximum()) == QDialog::Accepted)
		ui->BoxHspd->setValue(value);
}
void FormActSingleLoopFree::inputTimes(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxTimes->minimum(), ui->BoxTimes->maximum()) == QDialog::Accepted)
        ui->BoxTimes->setValue(value);
}

// 输入位置信号槽
void FormActSingleLoopFree::inputPos(void)
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
    {
        ui->BoxPos->setValue(value);
        pos[currentPos-1] = qRound(ui->BoxPos->value()*100.00);
    }
    else
    {
        double diff = ui->BoxPos->value() - value;
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
        ui->BoxPos->setValue(ui->BoxPos->value() - diff);
        pos[currentPos-1] = qRound(ui->BoxPos->value()*100.00);
    }
}
// 选择变量
void FormActSingleLoopFree::selectVar(void)
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_COUNTER, ret) != QDialog::Accepted)
        return;
    userVar = ret;
    ui->lineEditCount->setText(xStringResource::GetVarName(userVar));
}

quint16 FormActSingleLoopFree::GetVar()
{
    return userVar;
}
void FormActSingleLoopFree::SetVar(quint16 var)
{
    userVar = var;
    ui->lineEditCount->setText(xStringResource::GetVarName(userVar));
}


quint8 FormActSingleLoopFree::GetAxes()
{
    return pAxesBtn->checkedId();
}
void FormActSingleLoopFree::SetAxes(quint8 idx)
{
    pAxesBtn->button(idx)->setChecked(true);
}

void FormActSingleLoopFree::AxesClick(int axes)
{
    UpdateWidgetState();
}
// 每次点数
quint8 FormActSingleLoopFree::GetTimes()
{
    return ui->BoxTimes->value();
}
void FormActSingleLoopFree::SetTimes(quint8 times)
{
    ui->BoxTimes->setValue(times);
}
// 输入低速速度信号槽
void FormActSingleLoopFree::inputLspd(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxLspd->minimum(), ui->BoxLspd->maximum()) == QDialog::Accepted)
        ui->BoxLspd->setValue(value);
}
// 输入减速距离信号槽
void FormActSingleLoopFree::inputLdis(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxLowDis->minimum(), ui->BoxLowDis->maximum()) == QDialog::Accepted)
        ui->BoxLowDis->setValue(value);
}
// 得到减速速度
int FormActSingleLoopFree::GetDSpeed()
{
    return ui->BoxLspd->value();
}
// 设置减速速度
void FormActSingleLoopFree::SetDSpeed(int dspeed)
{
    ui->BoxLspd->setValue(dspeed);
}

// 得到减速距离
int FormActSingleLoopFree::GetDLen()
{
    return qRound(ui->BoxLowDis->value() * 100.00);
}
// 设置减速距离
void FormActSingleLoopFree::SetDLen(int len)
{
    ui->BoxLowDis->setValue((double)len / 100.00);
}
// 位置点
void FormActSingleLoopFree::posPrev(void)
{
    if (currentPos <= 1)
        currentPos = ui->BoxCnt->value();
    else
        currentPos--;
    ui->lineEdit->setText(QString::number((currentPos)));
    ui->BoxPos->setValue((double)pos[currentPos-1] / 100.0);
}
void FormActSingleLoopFree::posNext(void)
{
    if (currentPos >= ui->BoxCnt->value())
        currentPos = 1;
    else
        currentPos++;
    ui->lineEdit->setText(QString::number((currentPos)));
    ui->BoxPos->setValue((double)pos[currentPos-1] / 100.0);
}
// 同步位置
void FormActSingleLoopFree::syncPos(void)
{
    if (pAxesBtn->checkedId() == AXIS_IDX_PHOR)
    {
        ui->BoxPos->setValue((double)CMBProtocol::GetPaHorPos() / 100.00);
        pos[currentPos-1] = qRound(ui->BoxPos->value()*100.00);
    }
    if (pAxesBtn->checkedId() == AXIS_IDX_PVER)
    {
        ui->BoxPos->setValue((double)CMBProtocol::GetPaVerPos() / 100.00);
        pos[currentPos-1] = qRound(ui->BoxPos->value()*100.00);
    }
    if (pAxesBtn->checkedId() == AXIS_IDX_RHOR)
    {
        ui->BoxPos->setValue((double)CMBProtocol::GetRaHorPos() / 100.00);
        pos[currentPos-1] = qRound(ui->BoxPos->value()*100.00);
    }
    if (pAxesBtn->checkedId() == AXIS_IDX_RVER)
    {
        ui->BoxPos->setValue((double)CMBProtocol::GetRaVerPos() / 100.00);
        pos[currentPos-1] = qRound(ui->BoxPos->value()*100.00);
    }
    if (pAxesBtn->checkedId() == AXIS_IDX_TRV)
    {
        ui->BoxPos->setValue((double)CMBProtocol::GetTravelPos() / 100.00);
        pos[currentPos-1] = qRound(ui->BoxPos->value()*100.00);
    }
    if (pAxesBtn->checkedId() == AXIS_IDX_EXT)
    {
        ui->BoxPos->setValue((double)CMBProtocol::GetExtendPos() / 100.00);
        pos[currentPos-1] = qRound(ui->BoxPos->value()*100.00);
    }
}
int FormActSingleLoopFree::GetPos(int idx)
{
    return qRound(pos[idx]);
}

void FormActSingleLoopFree::SetPos(int idx, int position)
{
    pos[idx] = position;
}

