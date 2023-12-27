#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "formactpaper.h"
#include "ui_formactpaper.h"
#include "servoalias.h"
#include "xmessagebox.h"

FormActPaper::FormActPaper(QWidget *parent) : QWidget(parent), ui(new Ui::FormActPaper)
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

    connect(pAxesBtn, SIGNAL(buttonClicked(int)), this, SLOT(AxesClick(int)));
}

FormActPaper::~FormActPaper()
{
    delete ui;
    delete pAxesBtn;
}

void FormActPaper::changeEvent(QEvent *e)
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

void FormActPaper::retranslateUi(void)
{
    ui->rBtnPaHor->setText(GetServoName(AXIS_IDX_PHOR));
    ui->rBtnPaVer->setText(GetServoName(AXIS_IDX_PVER));
    ui->rBtnTravel->setText(GetServoName(AXIS_IDX_TRV));
    ui->rBtnExt->setText(GetServoName(AXIS_IDX_EXT));
    ui->rBtnRaHor->setText(GetServoName(AXIS_IDX_RHOR));
    ui->rBtnRaVer->setText(GetServoName(AXIS_IDX_RVER));
}

// 得到上下轴取纸位置
int FormActPaper::GetY()
{
    return qRound(ui->BoxVerPos->value() * 100.00);
}
// 设置上下轴取纸位置
void FormActPaper::SetY(int y)
{
    ui->BoxVerPos->setValue((double)y / 100.00);
}

// 得到运行速度
int FormActPaper::GetSpeed()
{
	return ui->BoxHspd->value();
}
// 设置运行速度
void FormActPaper::SetSpeed(int speed)
{
	ui->BoxHspd->setValue(speed);
}

// 得到减速速度
int FormActPaper::GetDSpeed()
{
	return ui->BoxLspd->value();
}
// 设置减速速度
void FormActPaper::SetDSpeed(int dspeed)
{
	ui->BoxLspd->setValue(dspeed);
}

int FormActPaper::GetDecVar()
{
	return inSpd;
}

void FormActPaper::SetDecVar(int var)
{
	inSpd = var;
	ui->lineEdit_dvar->setText(xStringResource::GetVarName(inSpd));
}

int FormActPaper::GetInVar()
{
	return inCheck;
}

void FormActPaper::SetInVar(int var)
{
	inCheck = var;
	ui->lineEdit_invar->setText(xStringResource::GetVarName(inCheck));
}

void FormActPaper::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->rBtnPaHor->setEnabled(false);
        ui->rBtnPaVer->setEnabled(false);
        ui->rBtnRaHor->setEnabled(false);
        ui->rBtnRaVer->setEnabled(false);
        ui->rBtnTravel->setEnabled(false);
        ui->rBtnExt->setEnabled(false);
        ui->lineEdit_dvar->setEnabled(false);
        ui->lineEdit_invar->setEnabled(false);
    }
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->BoxVerPos->setEnabled((true));
            ui->rBtnPaHor->setEnabled((!CMBProtocol::GetPaHorNotUse()));
            ui->rBtnPaVer->setEnabled((true));
            ui->rBtnRaHor->setEnabled(CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
            ui->rBtnRaVer->setEnabled(CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
            ui->rBtnTravel->setEnabled((true));
            ui->rBtnExt->setEnabled(CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
            ui->lineEdit_dvar->setEnabled((true));
            ui->lineEdit_invar->setEnabled((true));
        }
        else
        {
            ui->BoxVerPos->setEnabled(false);
            ui->rBtnPaHor->setEnabled(false);
            ui->rBtnPaVer->setEnabled(false);
            ui->rBtnRaHor->setEnabled(false);
            ui->rBtnRaVer->setEnabled(false);
            ui->rBtnTravel->setEnabled(false);
            ui->rBtnExt->setEnabled(false);
            ui->lineEdit_dvar->setEnabled(false);
            ui->lineEdit_invar->setEnabled(false);
        }
    }
}

// 输入运行速度信号槽
void FormActPaper::inputHspd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxHspd->minimum(), ui->BoxHspd->maximum()) == QDialog::Accepted)
		ui->BoxHspd->setValue(value);
}
// 输入减速速度信号槽
void FormActPaper::inputLspd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxLspd->minimum(), ui->BoxLspd->maximum()) == QDialog::Accepted)
		ui->BoxLspd->setValue(value);
}
// 选择减速检测输入端口信号槽
void FormActPaper::selectInSpd(void)
{
	quint32 ret;
	if (xSelVar->DoForm(VARSEL_MASK_EIN, ret) != QDialog::Accepted)
		return;
	inSpd = ret;
	ui->lineEdit_dvar->setText(xStringResource::GetVarName(inSpd));
}
// 选择取纸检测输入端口信号槽
void FormActPaper::selectInCheck(void)
{
	quint32 ret;
	if (xSelVar->DoForm(VARSEL_MASK_EIN, ret) != QDialog::Accepted)
		return;
	inCheck = ret;
	ui->lineEdit_invar->setText(xStringResource::GetVarName(inCheck));
}
// 输入位置信号槽
void FormActPaper::inputPos(void)
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
        if (numberPad.DoFormPos(value, 0.0, (CMBProtocol::GetHorLen() - CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
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
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4) || (!CMBProtocol::GetRhorSrvUse()))
        {
            if (numberPad.DoFormPos(value, 0.0, CMBProtocol::GetHorInt() / 100.00) != QDialog::Accepted)
                return;
        }
        else
        {
        if (numberPad.DoFormPos(value, 0.0, (CMBProtocol::GetHorLen() - CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
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
        ui->BoxVerPos->setValue(value);
    else
    {
        double diff = ui->BoxVerPos->value() - value;
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
        ui->BoxVerPos->setValue(ui->BoxVerPos->value() - diff);
    }
}
// 同步上下位置信号槽
void FormActPaper::syncPos(void)
{
    if (pAxesBtn->checkedId() == AXIS_IDX_PHOR)
        ui->BoxVerPos->setValue((double)CMBProtocol::GetPaHorPos() / 100.00);
    if (pAxesBtn->checkedId() == AXIS_IDX_PVER)
        ui->BoxVerPos->setValue((double)CMBProtocol::GetPaVerPos() / 100.00);
    if (pAxesBtn->checkedId() == AXIS_IDX_TRV)
        ui->BoxVerPos->setValue((double)CMBProtocol::GetTravelPos() / 100.00);
    if (pAxesBtn->checkedId() == AXIS_IDX_RHOR)
        ui->BoxVerPos->setValue((double)CMBProtocol::GetRaHorPos() / 100.00);
    if (pAxesBtn->checkedId() == AXIS_IDX_RVER)
        ui->BoxVerPos->setValue((double)CMBProtocol::GetRaVerPos() / 100.00);
    if (pAxesBtn->checkedId() == AXIS_IDX_EXT)
        ui->BoxVerPos->setValue((double)CMBProtocol::GetExtendPos() / 100.00);
}
void FormActPaper::SetAxes(quint8 axes)
{
    pAxesBtn->button(axes)->setChecked(true);
}

quint8 FormActPaper::GetAxes(void)
{
    return pAxesBtn->checkedId();
}
void FormActPaper::AxesClick(int axes)
{
    UpdateWidgetState();
}
