#include <assert.h>
#include <QButtonGroup>
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "formactloopfree.h"
#include "ui_formactloopfree.h"
#include "servoalias.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"

FormActLoopFree::FormActLoopFree(QWidget *parent) :	QWidget(parent), ui(new Ui::FormActLoopFree)
{
	ui->setupUi(this);
	retranslateUi();

    ui->labelCount->setEnabled(false);
    ui->lineEditCount->setEnabled(false);

    currentPos = 1;
    ui->lineEdit->setText(QString::number((currentPos)));
    ui->BoxHorPos->setValue((double)pos[AXES_IDX_X][currentPos-1] /100.00);
    ui->BoxVerPos->setValue((double)pos[AXES_IDX_Y][currentPos-1] /100.00);
    ui->BoxTrvPos->setValue((double)pos[AXES_IDX_Z][currentPos-1] /100.00);
    UpdateWidgetState();
}

FormActLoopFree::~FormActLoopFree()
{
	delete ui;
}

// 设置界面字符串资源
void FormActLoopFree::retranslateUi(void)
{
    ui->labelHorPos->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴："));
    ui->labelVerPos->setText(GetServoName(AXIS_IDX_PVER) + tr("轴："));
    ui->labelTrvPos->setText(GetServoName(AXIS_IDX_TRV) + tr("轴："));

}

void FormActLoopFree::changeEvent(QEvent *e)
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

// 得到定位点数量
int FormActLoopFree::GetPosCount()
{
	return ui->BoxCnt->value();
}
// 设置定位点数量
void FormActLoopFree::SetPosCount(int count)
{
	ui->BoxCnt->setValue(count);
}

// 得到运行速度
quint32 FormActLoopFree::GetSpeed()
{
	return ui->BoxHspd->value();
}
// 设置运行速度
void FormActLoopFree::SetSpeed(int speed)
{
    ui->BoxHspd->setValue(speed);
}

// 得到减速速度
int FormActLoopFree::GetDSpeed()
{
	return ui->BoxLspd->value();
}
// 设置减速速度
void FormActLoopFree::SetDSpeed(int dspeed)
{
	ui->BoxLspd->setValue(dspeed);
}

// 得到减速距离
int FormActLoopFree::GetDLen()
{
    return qRound(ui->BoxLowDis->value() * 100.00);
}
// 设置减速距离
void FormActLoopFree::SetDLen(int len)
{
    ui->BoxLowDis->setValue((double)len / 100.00);
}

// 得到定位时倒角状态设置
int FormActLoopFree::GetRotate()
{
	if (ui->checkBox_rotate->isChecked() == true)
		return 1;
	else
		return 0;
}
// 设置定位时倒角状态设置
void FormActLoopFree::SetRotate(int rotate)
{
	if (rotate != 0)
		ui->checkBox_rotate->setChecked(true);
	else
		ui->checkBox_rotate->setChecked(false);
}

// 得到引拔轴作为减速轴设置
int FormActLoopFree::GetXDec()
{
	if (ui->checkBox_xdec->isChecked() == true)
		return 1;
	else
		return 0;
}
// 设置引拔轴作为减速轴设置
void FormActLoopFree::SetXDec(int xdec)
{
	if (xdec != 0)
		ui->checkBox_xdec->setChecked(true);
	else
		ui->checkBox_xdec->setChecked(false);
}

void FormActLoopFree::UpdateWidgetState()
{
    ui->BoxHorPos->setValue((double)pos[AXES_IDX_X][currentPos-1] /100.00);
    ui->BoxVerPos->setValue((double)pos[AXES_IDX_Y][currentPos-1] /100.00);
    ui->BoxTrvPos->setValue((double)pos[AXES_IDX_Z][currentPos-1] /100.00);

    if (CMBProtocol::GetTemplateUse())
    {
        ui->checkBox_xdec->setEnabled(false);
        ui->checkBox_rotate->setEnabled(false);
        ui->checkBoxIsRunner->setEnabled(false);
        ui->checkBoxTrvRot->setEnabled(false);
    }
    else
    {
        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            ui->checkBox_xdec->setEnabled(true);
            ui->checkBox_rotate->setEnabled(true);
            ui->checkBoxIsRunner->setEnabled(true);
            ui->BoxCnt->setEnabled(true);
            ui->BoxLowDis->setEnabled(true);
            ui->checkBoxTrvRot->setEnabled(true);
        }
        else
        {
            ui->checkBox_xdec->setEnabled(false);
            ui->checkBox_rotate->setEnabled(false);
            ui->checkBoxIsRunner->setEnabled(false);
            ui->BoxCnt->setEnabled(false);
            ui->BoxLowDis->setEnabled(false);
            ui->checkBoxTrvRot->setEnabled(false);
        }
    }
}

// 上一页信号槽
void FormActLoopFree::pageUp(void)
{
    if (currentPos <= 1)
        currentPos = ui->BoxCnt->value();
		else
        currentPos--;
    ui->lineEdit->setText(QString::number((currentPos)));
    ui->BoxHorPos->setValue((double)pos[AXES_IDX_X][currentPos-1] /100.00);
    ui->BoxVerPos->setValue((double)pos[AXES_IDX_Y][currentPos-1] /100.00);
    ui->BoxTrvPos->setValue((double)pos[AXES_IDX_Z][currentPos-1] /100.00);
}
// 下一页信号槽
void FormActLoopFree::pageDwn(void)
{
    if (currentPos >= ui->BoxCnt->value())
        currentPos = 1;
		else
        currentPos++;
    ui->lineEdit->setText(QString::number((currentPos)));
    ui->BoxHorPos->setValue((double)pos[AXES_IDX_X][currentPos-1] /100.00);
    ui->BoxVerPos->setValue((double)pos[AXES_IDX_Y][currentPos-1] /100.00);
    ui->BoxTrvPos->setValue((double)pos[AXES_IDX_Z][currentPos-1] /100.00);
}

// 输入定位点数量信号槽
void FormActLoopFree::inputCnt(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxCnt->minimum(), ui->BoxCnt->maximum()) == QDialog::Accepted)
		ui->BoxCnt->setValue(value);
}
// 输入运行速度信号槽
void FormActLoopFree::inputHspd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxHspd->minimum(), ui->BoxHspd->maximum()) == QDialog::Accepted)
		ui->BoxHspd->setValue(value);
}
// 输入减速速度信号槽
void FormActLoopFree::inputLspd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxLspd->minimum(), ui->BoxLspd->maximum()) == QDialog::Accepted)
		ui->BoxLspd->setValue(value);
}
// 输入减速距离信号槽
void FormActLoopFree::inputLdis(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormPos(value, ui->BoxLowDis->minimum(), ui->BoxLowDis->maximum()) == QDialog::Accepted)
		ui->BoxLowDis->setValue(value);
}

// 同步引拔位置
void FormActLoopFree::syncHorPos(void)
{
    if(ui->checkBoxIsRunner->isChecked())
        ui->BoxHorPos->setValue((double)CMBProtocol::GetRaHorPos() / 100.00);
    else
        ui->BoxHorPos->setValue((double)CMBProtocol::GetPaHorPos() / 100.00);
    pos[AXES_IDX_X][currentPos-1] = qRound(ui->BoxHorPos->value()*100.00);
}
// 同步上下位置
void FormActLoopFree::syncVerPos(void)
{
    if(ui->checkBoxIsRunner->isChecked())
        ui->BoxVerPos->setValue((double)CMBProtocol::GetRaVerPos() / 100.00);
    else
        ui->BoxVerPos->setValue((double)CMBProtocol::GetPaVerPos() / 100.00);
    pos[AXES_IDX_Y][currentPos-1] = qRound(ui->BoxVerPos->value()*100.00);
}
// 同步横行位置
void FormActLoopFree::syncTrvPos(void)
{
    ui->BoxTrvPos->setValue((double)CMBProtocol::GetTravelPos() / 100.00);
    pos[AXES_IDX_Z][currentPos-1] = qRound(ui->BoxTrvPos->value()*100.00);
}

// 输入引拔位置信号槽
void FormActLoopFree::inputHorPos(void)
{
	DialogNumberPad numberPad;
	double value;
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
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
	{
        ui->BoxHorPos->setValue(value);
        pos[AXES_IDX_X][currentPos-1] = qRound(ui->BoxHorPos->value()*100.00);
	}
	else
	{
        double diff = ui->BoxHorPos->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
        ui->BoxHorPos->setValue(ui->BoxHorPos->value() - diff);
        pos[AXES_IDX_X][currentPos-1] = qRound(ui->BoxHorPos->value()*100.00);
	}
}
// 输入上下位置信号槽
void FormActLoopFree::inputVerPos(void)
{
	DialogNumberPad numberPad;
	double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
		return;
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
	{
        ui->BoxVerPos->setValue(value);
        pos[AXES_IDX_Y][currentPos-1] = qRound(ui->BoxVerPos->value()*100.00);
	}
	else
	{
        double diff = ui->BoxVerPos->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
        ui->BoxVerPos->setValue(ui->BoxVerPos->value() - diff);
        pos[AXES_IDX_Y][currentPos-1] = qRound(ui->BoxVerPos->value()*100.00);
	}
}
// 输入横行位置信号槽
void FormActLoopFree::inputTrvPos(void)
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
	{
        ui->BoxTrvPos->setValue(value);
        pos[AXES_IDX_Z][currentPos-1] = qRound(ui->BoxTrvPos->value()*100.00);
	}
	else
	{
        double diff = ui->BoxTrvPos->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
        ui->BoxTrvPos->setValue(ui->BoxTrvPos->value() - diff);
        pos[AXES_IDX_Z][currentPos-1] = qRound(ui->BoxTrvPos->value()*100.00);
	}
}

// 是否副臂
bool FormActLoopFree::GetIsRunner(void)
{
    if (ui->checkBoxIsRunner->isChecked())
        return true;
    return false;
}
void FormActLoopFree::SetIsRunner(int isrunner)
{
    if (isrunner)
        ui->checkBoxIsRunner->setChecked(true);
    else
        ui->checkBoxIsRunner->setChecked(false);
}
// 横行自动倒角
bool FormActLoopFree::GetTrvRot(void)
{
    if (ui->checkBoxTrvRot->isChecked())
        return true;
    return false;
}
void FormActLoopFree::SetTrvRot(int trvrot)
{
    if (trvrot)
        ui->checkBoxTrvRot->setChecked(true);
    else
        ui->checkBoxTrvRot->setChecked(false);
}
// 选择变量
void FormActLoopFree::selectUser(void)
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_COUNTER, ret) != QDialog::Accepted)
        return;
    userVar = ret;
    ui->lineEditCount->setText(xStringResource::GetVarName(userVar));
}
void FormActLoopFree::SetVar(quint16 var)
{
    userVar = var;
    ui->lineEditCount->setText(xStringResource::GetVarName(userVar));
}

quint16 FormActLoopFree::GetVar()
{
    return userVar;
}

int FormActLoopFree::GetPos(int axisidx, int posidx)
{
    return qRound(pos[axisidx][posidx]);
}
void FormActLoopFree::SetPos(int axisidx, int posidx, int position)
{
    pos[axisidx][posidx] = position;
}
void FormActLoopFree::isRunnerClick()
{
    if(ui->checkBoxIsRunner->isChecked())
    {
        ui->labelHorPos->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴："));
        ui->labelVerPos->setText(GetServoName(AXIS_IDX_RVER) + tr("轴："));
        ui->labelTrvPos->setText(GetServoName(AXIS_IDX_TRV) + tr("轴："));
    }
    else
    {
        ui->labelHorPos->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴："));
        ui->labelVerPos->setText(GetServoName(AXIS_IDX_PVER) + tr("轴："));
        ui->labelTrvPos->setText(GetServoName(AXIS_IDX_TRV) + tr("轴："));
    }
}
