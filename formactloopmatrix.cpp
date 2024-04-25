#include <stdio.h>
#include <QMovie>
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "formactloopmatrix.h"
#include "ui_formactloopmatrix.h"
#include "servoalias.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"

FormActLoopMatrix::FormActLoopMatrix(QWidget *parent) :	QWidget(parent), ui(new Ui::FormActLoopMatrix)
{
	ui->setupUi(this);
	retranslateUi();
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);

    ui->labelCounter->setEnabled(false);
    ui->lineEditCount->setEnabled(false);
    Axis[0] = AXIS_IDX_PHOR;
    Axis[1] = AXIS_IDX_PVER;
    Axis[2] = AXIS_IDX_TRV;
    // 设置原点第一行默认选中
    ui->tableWidgetAxis->setCurrentCell(0, 0);
    ui->tableWidgetAxis->setFocus();

	QFont font;
	font.setPixelSize(28); // 设置字号为28像素
	for(int i=0;i<ui->tableWidgetAxis->rowCount();i++)
	{
		ui->tableWidgetAxis->item(i,0)->setFont(font);
		ui->tableWidgetAxis->verticalHeaderItem(i)->setFont(font);
	}
}

FormActLoopMatrix::~FormActLoopMatrix()
{
	delete ui;
}

void FormActLoopMatrix::changeEvent(QEvent *e)
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
bool FormActLoopMatrix::EnterForm(bool isinsert)
{
    if (isinsert)
    {
        ui->checkBoxIsRunner->setChecked(false);
        ui->checkBox_xdec->setChecked(false);
        ui->checkBox_rotate->setChecked(true);
        ui->checkBoxTrvRot->setChecked(true);
        ui->BoxHorPos->setValue(0.00);
        ui->BoxVerPos->setValue(0.00);
        ui->BoxTrvPos->setValue(0.00);
        ui->BoxHorCnt->setValue(1);
        ui->BoxVerCnt->setValue(1);
        ui->BoxTrvCnt->setValue(1);
        ui->BoxHorInt->setValue(0.0);
        ui->BoxVerInt->setValue(0.0);
        ui->BoxTrvInt->setValue(0.0);
        ui->BoxHspd->setValue(50);
        ui->BoxHorSpd->setValue(50);
        ui->BoxTrvSpd->setValue(50);
        ui->BoxLspd->setValue(10);
        ui->BoxLowDis->setValue(50.00);
        SetFirstDec(ORDER_MODE_XYZ);
    }
    UpdateWidgetState();
    show();
    return true;
}

void FormActLoopMatrix::retranslateUi(void)
{
    ui->labelHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴："));
    ui->labelVer->setText(GetServoName(AXIS_IDX_PVER) + tr("轴："));
    ui->labelTrv->setText(GetServoName(AXIS_IDX_TRV) + tr("轴："));
}

int FormActLoopMatrix::GetX(int idx)
{
	int ret = 0;
	switch (idx)
	{
	case 0:		// 得到引拔轴第一点位置
        ret = qRound(ui->BoxHorPos->value() * 100.00);
		break;
	case 1:		// 得到引拔轴点距
        if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
            ret = qRound(ui->BoxHorInt->value() * 10.0);
        else
        ret = qRound(ui->BoxHorInt->value() * 100.00);
		break;
	case 2:		// 得到引拔轴点数
		ret = ui->BoxHorCnt->value();
		break;
	}
	return ret;
}

void FormActLoopMatrix::SetX(int idx, int x)
{
	switch (idx)
	{
	case 0:		// 设置引拔轴第一点位置
        ui->BoxHorPos->setValue((double)x / 100.00);
		break;
	case 1:		// 设置引拔轴点距
        if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
            ui->BoxHorInt->setValue((double)x / 10.0);
        else
        ui->BoxHorInt->setValue((double)x / 100.00);
		break;
	case 2:		// 设置引拔轴点数
		ui->BoxHorCnt->setValue(x);
		break;
	}
}

int FormActLoopMatrix::GetY(int idx)
{
	int ret = 0;
	switch (idx)
	{
	case 0:		// 得到上下轴第一点位置
        ret = qRound(ui->BoxVerPos->value() * 100.00);
		break;
	case 1:		// 得到上下轴点距
        if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
            ret = qRound(ui->BoxVerInt->value() * 10.0);
        else
        ret = qRound(ui->BoxVerInt->value() * 100.00);
		break;
	case 2:		// 得到上下轴点数
		ret = ui->BoxVerCnt->value();
		break;
	}
	return ret;
}

void FormActLoopMatrix::SetY(int idx, int y)
{
	switch (idx)
	{
	case 0:		// 设置上下轴第一点位置
        ui->BoxVerPos->setValue((double)y / 100.00);
		break;
	case 1:		// 设置上下轴点距
        if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
            ui->BoxVerInt->setValue((double)y / 10.0);
        else
        ui->BoxVerInt->setValue((double)y / 100.00);
		break;
	case 2:		// 设置上下轴点数
		ui->BoxVerCnt->setValue(y);
		break;
	}
}

int FormActLoopMatrix::GetZ(int idx)
{
	int ret = 0;
	switch (idx)
	{
	case 0:		// 得到横行轴第一点位置
        ret = qRound(ui->BoxTrvPos->value() * 100.00);
		break;
	case 1:		// 得到横行轴点距
        if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
            ret = qRound(ui->BoxTrvInt->value() * 10.0);
        else
        ret = qRound(ui->BoxTrvInt->value() * 100.00);
		break;
	case 2:		// 得到横行轴点数
		ret = ui->BoxTrvCnt->value();
		break;
	}
	return ret;
}

void FormActLoopMatrix::SetZ(int idx, int z)
{
	switch (idx)
	{
	case 0:		// 设置横行轴第一点位置
        ui->BoxTrvPos->setValue((double)z / 100.00);
		break;
	case 1:		// 设置横行轴点距
        if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
            ui->BoxTrvInt->setValue((double)z / 10.0);
        else
        ui->BoxTrvInt->setValue((double)z / 100.00);
		break;
	case 2:		// 设置横行轴点数
		ui->BoxTrvCnt->setValue(z);
		break;
	}
}

// 得到运行速度
quint32 FormActLoopMatrix::GetSpeed()
{
	return ui->BoxHspd->value();
}
// 设置运行速度（引拔）
void FormActLoopMatrix::SetSpeed(int speed)
{
	ui->BoxHspd->setValue(speed);
}
// 设置上下轴速度
quint32 FormActLoopMatrix::GetHorSpeed()
{
    return ui->BoxHorSpd->value();
}
void FormActLoopMatrix::SetHorSpeed(int speed)
{
    ui->BoxHorSpd->setValue(speed);
}
// 设置横行轴速度
quint32 FormActLoopMatrix::GetTrvSpeed()
{
    return ui->BoxTrvSpd->value();
}
void FormActLoopMatrix::SetTrvSpeed(int speed)
{
    ui->BoxTrvSpd->setValue(speed);
}

// 得到减速速度
int FormActLoopMatrix::GetDSpeed()
{
	return ui->BoxLspd->value();
}
// 设置减速速度
void FormActLoopMatrix::SetDSpeed(int dspeed)
{
	ui->BoxLspd->setValue(dspeed);
}

// 得到减速距离
int FormActLoopMatrix::GetDLen()
{
    return qRound(ui->BoxLowDis->value() * 100.00);
}
// 设置减速距离
void FormActLoopMatrix::SetDLen(int len)
{
    ui->BoxLowDis->setValue((double)len / 100.00);
}

// 得到定位时倒角状态
int FormActLoopMatrix::GetRotate()
{
	if (ui->checkBox_rotate->isChecked())
		return 1;
	else
		return 0;
}
// 设置定位时倒角状态
void FormActLoopMatrix::SetRotate(int rotate)
{
	if (rotate != 0)
		ui->checkBox_rotate->setChecked(true);
	else
		ui->checkBox_rotate->setChecked(false);
}

// 得到引拔轴作为减速轴设置
int FormActLoopMatrix::GetXDec()
{
	if (ui->checkBox_xdec->isChecked() == true)
		return 1;
	else
		return 0;
}
// 设置引拔轴作为减速轴设置
void FormActLoopMatrix::SetXDec(int xdec)
{
	if (xdec != 0)
		ui->checkBox_xdec->setChecked(true);
	else
		ui->checkBox_xdec->setChecked(false);
}

// 得到减速轴优先等位设置
int FormActLoopMatrix::GetFirstDec()
{
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_PHOR) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_PVER) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_TRV))
        return ORDER_MODE_XYZ;
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_PHOR) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_TRV) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_PVER))
        return ORDER_MODE_XZY;
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_PVER) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_PHOR) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_TRV))
        return ORDER_MODE_YXZ;
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_PVER) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_TRV) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_PHOR))
        return ORDER_MODE_YZX;
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_TRV) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_PHOR) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_PVER))
        return ORDER_MODE_ZXY;
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_TRV) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_PVER) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_PHOR))
        return ORDER_MODE_ZYX;
        return 0;
}
// 设置减速轴优先定位设置
void FormActLoopMatrix::SetFirstDec(int fdec)
{
    switch (fdec)
    {
    case ORDER_MODE_XYZ:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_PVER));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_TRV));
        break;
    case ORDER_MODE_XZY:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_TRV));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_PVER));
        break;
    case ORDER_MODE_YXZ:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_PVER));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_TRV));
        break;
    case ORDER_MODE_YZX:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_PVER));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_TRV));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        break;
    case ORDER_MODE_ZXY:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_TRV));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_PVER));
        break;
    case ORDER_MODE_ZYX:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_TRV));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_PVER));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        break;
    }
}
// 是否副臂
bool FormActLoopMatrix::GetIsRunner(void)
{
    if (ui->checkBoxIsRunner->isChecked())
        return true;
    return false;
}
void FormActLoopMatrix::SetIsRunner(int isrunner)
{
    if (isrunner)
        ui->checkBoxIsRunner->setChecked(true);
    else
        ui->checkBoxIsRunner->setChecked(false);
}
// 横行自动倒角
bool FormActLoopMatrix::GetTrvRot(void)
{
    if (ui->checkBoxTrvRot->isChecked())
        return true;
    return false;
}
void FormActLoopMatrix::SetTrvRot(int trvrot)
{
    if (trvrot)
        ui->checkBoxTrvRot->setChecked(true);
    else
		ui->checkBoxTrvRot->setChecked(false);
}

int FormActLoopMatrix::GetConveyor_delay()
{
    return qRound(ui->BoxConveyorDelay->value() * (1000.0/TIME_BASE));
}

void FormActLoopMatrix::SetConveyor_delay(int delay)
{
    ui->BoxConveyorDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormActLoopMatrix::GetConveyor_out()
{
    return extOutport;
}

void FormActLoopMatrix::SetConveyor_out(int out)
{
    extOutport = out;
    ui->lineEditConveyorOut->setText(xStringResource::GetVarName(extOutport));
}

bool FormActLoopMatrix::GetConveyor_use()
{
    if(ui->checkBox_ConveyorUse->isChecked())
        return true;
    else
        return false;
}

void FormActLoopMatrix::SetConveyor_use(bool use)
{
    ui->checkBox_ConveyorUse->setChecked(use);
}

void FormActLoopMatrix::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->checkBoxIsRunner->setEnabled(false);
        ui->checkBox_rotate->setEnabled(false);
        ui->checkBox_xdec->setEnabled(false);
//        ui->checkBox_firstdec->setEnabled(false);
        ui->checkBoxTrvRot->setEnabled(false);
    }
    else
    {
        // 根据系统状态(自动/手动)设置界面状态
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->checkBoxIsRunner->setEnabled(true);
            ui->checkBox_rotate->setEnabled(true);
            ui->checkBox_xdec->setEnabled(true);
//            ui->checkBox_firstdec->setEnabled(true);

            ui->BoxHorCnt->setEnabled(true);
            ui->BoxTrvCnt->setEnabled(true);
            ui->BoxVerCnt->setEnabled(true);
            ui->BoxHorInt->setEnabled(true);
            ui->BoxVerInt->setEnabled(true);
            ui->BoxTrvInt->setEnabled(true);

            ui->BtnHorSync->setEnabled(true);
            ui->BtnTrvSync->setEnabled(true);
            ui->BtnVerSync->setEnabled(true);
            ui->BoxHorPos->setEnabled(true);
            ui->BoxVerPos->setEnabled(true);
            ui->BoxTrvPos->setEnabled(true);
            ui->BoxLowDis->setEnabled(true);
            ui->checkBoxTrvRot->setEnabled(true);
            ui->checkBox_ConveyorUse->setEnabled(true);
            ui->BoxConveyorDelay->setEnabled(true);
            ui->lineEditConveyorOut->setEnabled(true);
        }
        else
        {
            ui->checkBoxIsRunner->setEnabled(false);
            ui->checkBox_rotate->setEnabled(false);
            ui->checkBox_xdec->setEnabled(false);
//            ui->checkBox_firstdec->setEnabled(false);

            ui->BoxHorCnt->setEnabled(false);
            ui->BoxTrvCnt->setEnabled(false);
            ui->BoxVerCnt->setEnabled(false);
            ui->BoxHorInt->setEnabled(false);
            ui->BoxVerInt->setEnabled(false);
            ui->BoxTrvInt->setEnabled(false);
            ui->BtnHorSync->setEnabled(false);
            ui->BtnTrvSync->setEnabled(false);
            ui->BtnVerSync->setEnabled(false);
#if FACTORY != FA_XIONGCHUANG
            ui->BoxHorPos->setEnabled(false);
            ui->BoxVerPos->setEnabled(false);
            ui->BoxTrvPos->setEnabled(false);
#endif
            ui->BoxLowDis->setEnabled(false);
            ui->checkBoxTrvRot->setEnabled(false);
            ui->checkBox_ConveyorUse->setEnabled(false);
            ui->BoxConveyorDelay->setEnabled(false);
            ui->lineEditConveyorOut->setEnabled(false);
        }
    }
    if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
    {
        ui->BoxHorInt->setDecimals(1);
        ui->BoxHorInt->setMinimum(-3200.0);
        ui->BoxHorInt->setMaximum(3200.0);
        ui->BoxVerInt->setDecimals(1);
        ui->BoxVerInt->setMinimum(-3200.0);
        ui->BoxVerInt->setMaximum(3200.0);
        ui->BoxTrvInt->setDecimals(1);
        ui->BoxTrvInt->setMinimum(-3200.0);
        ui->BoxTrvInt->setMaximum(3200.0);
    }
    else
    {
        ui->BoxHorInt->setDecimals(2);
        ui->BoxHorInt->setMinimum(-320.00);
        ui->BoxHorInt->setMaximum(320.00);
        ui->BoxVerInt->setDecimals(2);
        ui->BoxVerInt->setMinimum(-320.00);
        ui->BoxVerInt->setMaximum(320.00);
        ui->BoxTrvInt->setDecimals(2);
        ui->BoxTrvInt->setMinimum(-320.00);
        ui->BoxTrvInt->setMaximum(320.00);
    }
    converorUse();
}

void FormActLoopMatrix::hideEvent(QHideEvent *event)
{
	QWidget::hideEvent(event);
}

// 输入引拔轴点数信号槽
void FormActLoopMatrix::inputHorCnt(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxHorCnt->minimum(), ui->BoxHorCnt->maximum()) == QDialog::Accepted)
		ui->BoxHorCnt->setValue(value);
}
// 输入上下轴点数信号槽
void FormActLoopMatrix::inputVerCnt(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxVerCnt->minimum(), ui->BoxVerCnt->maximum()) == QDialog::Accepted)
		ui->BoxVerCnt->setValue(value);
}
// 输入横行轴点数信号槽
void FormActLoopMatrix::inputTrvCnt(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxTrvCnt->minimum(), ui->BoxTrvCnt->maximum()) == QDialog::Accepted)
		ui->BoxTrvCnt->setValue(value);
}

// 输入引拔轴点距信号槽
void FormActLoopMatrix::inputHorInt(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxHorInt->minimum(), ui->BoxHorInt->maximum()) != QDialog::Accepted)
		return;
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
		ui->BoxHorInt->setValue(value);
	else
	{
		double diff = ui->BoxHorInt->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
		ui->BoxHorInt->setValue(ui->BoxHorInt->value() - diff);
	}
}
// 输入上下轴点距信号槽
void FormActLoopMatrix::inputVerInt(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxVerInt->minimum(), ui->BoxVerInt->maximum()) != QDialog::Accepted)
		return;
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
		ui->BoxVerInt->setValue(value);
	else
	{
		double diff = ui->BoxVerInt->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
		ui->BoxVerInt->setValue(ui->BoxVerInt->value() - diff);
	}
}
// 输入横行轴点距信号槽
void FormActLoopMatrix::inputTrvInt(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvInt->minimum(), ui->BoxTrvInt->maximum()) != QDialog::Accepted)
		return;
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
		ui->BoxTrvInt->setValue(value);
	else
	{
		double diff = ui->BoxTrvInt->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
		ui->BoxTrvInt->setValue(ui->BoxTrvInt->value() - diff);
	}
}

// 输入引拔轴第一点位置信号槽
void FormActLoopMatrix::inputHorPos(void)
{
	DialogNumberPad numberPad;
	double value;
#if PENDANT_PROTOCOL
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4) || (!CMBProtocol::GetRhorSrvUse()))
    {
    if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
            return;
    }
    else
    {
        if (numberPad.DoFormPos(value, 0.00, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
            return;
    }
#else
    if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
		return;
#endif
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
		ui->BoxHorPos->setValue(value);
	else
	{
		double diff = ui->BoxHorPos->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
		ui->BoxHorPos->setValue(ui->BoxHorPos->value() - diff);
	}
}
// 输入上下轴第一点位置信号槽
void FormActLoopMatrix::inputVerPos(void)
{
	DialogNumberPad numberPad;
	double value;
#if PENDANT_PROTOCOL
    if(ui->checkBoxIsRunner->isChecked())
    {
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetRaVerLen() / 100.00) != QDialog::Accepted)
            return;
    }
    else
    {
    if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
			return;
	}
#else
    if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
		return;
#endif
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
		ui->BoxVerPos->setValue(value);
	else
	{
		double diff = ui->BoxVerPos->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
		ui->BoxVerPos->setValue(ui->BoxVerPos->value() - diff);
	}
}
// 输入横行轴第一点位置信号槽
void FormActLoopMatrix::inputTrvPos(void)
{
	DialogNumberPad numberPad;
	double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetTravLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
		return;
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
		ui->BoxTrvPos->setValue(value);
	else
	{
		double diff = ui->BoxTrvPos->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
		ui->BoxTrvPos->setValue(ui->BoxTrvPos->value() - diff);
	}
}

// 同步引拔轴第一点位置信号槽
void FormActLoopMatrix::syncHorPos(void)
{
    if(ui->checkBoxIsRunner->isChecked())
        ui->BoxHorPos->setValue((double)CMBProtocol::GetRaHorPos() / 100.00);
    else
        ui->BoxHorPos->setValue((double)CMBProtocol::GetPaHorPos() / 100.00);
}
// 同步上下轴第一点位置信号槽
void FormActLoopMatrix::syncVerPos(void)
{
    if(ui->checkBoxIsRunner->isChecked())
        ui->BoxVerPos->setValue((double)CMBProtocol::GetRaVerPos() / 100.00);
    else
        ui->BoxVerPos->setValue((double)CMBProtocol::GetPaVerPos() / 100.00);
}
// 同步横行轴第一点位置信号槽
void FormActLoopMatrix::syncTrvPos(void)
{
    ui->BoxTrvPos->setValue((double)CMBProtocol::GetTravelPos() / 100.00);
}

// 输入运行速度信号槽
void FormActLoopMatrix::inputHspd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxHspd->minimum(), ui->BoxHspd->maximum()) == QDialog::Accepted)
		ui->BoxHspd->setValue(value);
}

//输入Ver运行速度信号槽
void FormActLoopMatrix::inputHorspd(void)
{
    DialogNumberPad numberpad;
    int value;
    if (numberpad.DoForm(value, ui->BoxHorSpd->minimum(), ui->BoxHorSpd->maximum()) == QDialog::Accepted)
        ui->BoxHorSpd->setValue(value);
}
//输入Trv运行速度信号槽
void FormActLoopMatrix::inputTrvspd(void)
{
    DialogNumberPad numberpad;
    int value;
    if (numberpad.DoForm(value, ui->BoxTrvSpd->minimum(), ui->BoxTrvSpd->maximum()) == QDialog::Accepted)
        ui->BoxTrvSpd->setValue(value);
}
// 输入低速速度信号槽
void FormActLoopMatrix::inputLspd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxLspd->minimum(), ui->BoxLspd->maximum()) == QDialog::Accepted)
		ui->BoxLspd->setValue(value);
}
// 输入减速距离信号槽
void FormActLoopMatrix::inputLdis(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxLowDis->minimum(), ui->BoxLowDis->maximum()) == QDialog::Accepted)
		ui->BoxLowDis->setValue(value);
}
// 选择变量
void FormActLoopMatrix::selectUser(void)
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_COUNTER, ret) != QDialog::Accepted)
        return;
    userVar = ret;
    ui->lineEditCount->setText(xStringResource::GetVarName(userVar));
}

void FormActLoopMatrix::selectPort()
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_EOUT, ret) != QDialog::Accepted)
        return;
    extOutport = ret;
    ui->lineEditConveyorOut->setText(xStringResource::GetVarName(extOutport));
}

void FormActLoopMatrix::inputDelay()
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxConveyorDelay->minimum(), ui->BoxConveyorDelay->maximum()) == QDialog::Accepted)
        ui->BoxConveyorDelay->setValue(value);
}

void FormActLoopMatrix::converorUse()
{
    if(CMBProtocol::GetFunctions(SUB_FUN2_LOOP_MATRIX))
    {
        ui->checkBox_ConveyorUse->setEnabled(true);
        if(ui->checkBox_ConveyorUse->isChecked())
        {
            ui->BoxConveyorDelay->setEnabled(true);
            ui->lineEditConveyorOut->setEnabled(true);
        }
        else
        {
            ui->BoxConveyorDelay->setEnabled(false);
            ui->lineEditConveyorOut->setEnabled(false);
        }
    }
    else
    {
        ui->checkBox_ConveyorUse->setEnabled(false);
        ui->BoxConveyorDelay->setEnabled(false);
        ui->lineEditConveyorOut->setEnabled(false);
    }
}

void FormActLoopMatrix::isRunnerClick()
{
    if(ui->checkBoxIsRunner->isChecked())
    {
        ui->labelHor->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴："));
        ui->labelVer->setText(GetServoName(AXIS_IDX_RVER) + tr("轴："));
        ui->labelTrv->setText(GetServoName(AXIS_IDX_TRV) + tr("轴："));
    }
    else
    {
        ui->labelHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴："));
        ui->labelVer->setText(GetServoName(AXIS_IDX_PVER) + tr("轴："));
        ui->labelTrv->setText(GetServoName(AXIS_IDX_TRV) + tr("轴："));
    }
}
void FormActLoopMatrix::SetVar(quint16 var)
{
    userVar = var;
    ui->lineEditCount->setText(xStringResource::GetVarName(userVar));
}

quint16 FormActLoopMatrix::GetVar()
{
    return userVar;
}
// 向下一项
void FormActLoopMatrix::AxisGoDown(void)
{
    quint8 current_Select = ui->tableWidgetAxis->currentRow();
    if (MoveTab(current_Select, current_Select + 1))
    {
        UpdateTab();
        ui->tableWidgetAxis->setCurrentCell(current_Select + 1, 0);
    }
    GetFirstDec();
}
// 向上一项
void FormActLoopMatrix::AxisGoUp(void)
{
    quint8 current_Select = ui->tableWidgetAxis->currentRow();
    if (MoveTab(current_Select, current_Select-1))
    {
        UpdateTab();
        ui->tableWidgetAxis->setCurrentCell(current_Select - 1, 0);
    }
    GetFirstDec();
}
// 判断轴原点复归顺序
bool FormActLoopMatrix::MoveTab(quint8 currentselect, quint8 last_range)
{
    int i;
    bool ret = FALSE;
    if (last_range > 2) return ret;

    quint8 tmp = Axis[currentselect];
    if (currentselect > last_range)
    {
        for (i = currentselect; i > last_range; i--)
            Axis[i] = Axis[i-1];
        ret = TRUE;
    }
    if (currentselect < last_range)
    {
        for (i=currentselect; i < last_range; i++)
            Axis[i] = Axis[i+1];
        ret = TRUE;
    }
    Axis[last_range] = tmp;
    return ret;
}
// 根据数组内容，刷新Table参数
void FormActLoopMatrix::UpdateTab()
{
    for(int i = 0;i < 3; i++)
        ui->tableWidgetAxis->item(i, 0)->setText(TranslateAxis(Axis[i]));
}
// 解析轴名称
QString FormActLoopMatrix::TranslateAxis(quint8 Step)
{
    switch (Step)
    {
        case AXIS_IDX_PHOR:		return GetServoName(AXIS_IDX_PHOR);		//*
        case AXIS_IDX_PVER:		return GetServoName(AXIS_IDX_PVER);			//*
        case AXIS_IDX_TRV:		return GetServoName(AXIS_IDX_TRV);			//*
    }
	return QString(" ");
}
