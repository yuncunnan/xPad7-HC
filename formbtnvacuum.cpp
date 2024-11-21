#include "cmbprotocol.h"
#include "xstringresource.h"
#include "dialognumberpad.h"
#include "xstringresource.h"
#include "formbtnvacuum.h"
#include "ui_formbtnvacuum.h"
#include "xioport.h"

FormBtnVacuum::FormBtnVacuum(QWidget *parent) : QWidget(parent), ui(new Ui::FormBtnVacuum)
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
    ui->stackedWidget->setCurrentIndex(0);
}

FormBtnVacuum::~FormBtnVacuum()
{
    delete ui;
}

void FormBtnVacuum::changeEvent(QEvent *e)
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
bool FormBtnVacuum::EnterForm(void)
{
    init();
    UpdateWidgetState();
    show();
    return true;
}
void FormBtnVacuum::init(void)
{
    ui->BoxDelay->setValue(0.5);
    ui->radioButton_on->setChecked(true);
    ui->checkBoxJig03->setChecked(false);
    ui->checkBoxcheck03->setChecked(false);
    ui->checkBoxJig04->setChecked(false);
    ui->checkBoxcheck04->setChecked(false);
    ui->checkBoxJig05->setChecked(false);
    ui->checkBoxcheck05->setChecked(false);
    ui->checkBoxJig06->setChecked(false);
    ui->checkBoxcheck06->setChecked(false);
    ui->checkBoxJig07->setChecked(false);
    ui->checkBoxcheck07->setChecked(false);
    ui->checkBoxJig08->setChecked(false);
    ui->checkBoxcheck08->setChecked(false);
    ui->checkBoxJig09->setChecked(false);
    ui->checkBoxcheck09->setChecked(false);
    ui->checkBoxJig10->setChecked(false);
    ui->checkBoxcheck10->setChecked(false);
    ui->checkBoxJig11->setChecked(false);
    ui->checkBoxcheck11->setChecked(false);
    ui->checkBoxJig12->setChecked(false);
    ui->checkBoxcheck12->setChecked(false);
    ui->checkBoxJig13->setChecked(false);
    ui->checkBoxcheck13->setChecked(false);
    ui->checkBoxJig14->setChecked(false);
    ui->checkBoxcheck14->setChecked(false);
    ui->checkBoxJig15->setChecked(false);
    ui->checkBoxcheck15->setChecked(false);
    ui->checkBoxJig16->setChecked(false);
    ui->checkBoxcheck16->setChecked(false);
    ui->checkBoxcheck03->setEnabled(false);
    ui->checkBoxcheck04->setEnabled(false);
    ui->checkBoxcheck05->setEnabled(false);
    ui->checkBoxcheck06->setEnabled(false);
    ui->checkBoxcheck07->setEnabled(false);
    ui->checkBoxcheck08->setEnabled(false);
    ui->checkBoxcheck09->setEnabled(false);
    ui->checkBoxcheck10->setEnabled(false);
    ui->checkBoxcheck11->setEnabled(false);
    ui->checkBoxcheck12->setEnabled(false);
    ui->checkBoxcheck13->setEnabled(false);
    ui->checkBoxcheck14->setEnabled(false);
    ui->checkBoxcheck15->setEnabled(false);
    ui->checkBoxcheck16->setEnabled(false);

    ui->checkBoxcheckM01->setChecked(false);
    ui->checkBoxcheckM02->setChecked(false);
    ui->checkBoxcheckM03->setChecked(false);
    ui->checkBoxcheckM04->setChecked(false);
    ui->checkBoxcheckM05->setChecked(false);
    ui->checkBoxcheckM08->setChecked(false);
    ui->checkBoxcheckM09->setChecked(false);
    ui->checkBoxcheckM10->setChecked(false);
    ui->checkBoxcheckM11->setChecked(false);
    ui->checkBoxcheckM15->setChecked(false);
    ui->checkBoxMain01->setChecked(false);
    ui->checkBoxMain02->setChecked(false);
    ui->checkBoxMain03->setChecked(false);
    ui->checkBoxMain04->setChecked(false);
    ui->checkBoxMain05->setChecked(false);
    ui->checkBoxMain08->setChecked(false);
    ui->checkBoxMain09->setChecked(false);
    ui->checkBoxMain10->setChecked(false);
    ui->checkBoxMain11->setChecked(false);
    ui->checkBoxMain15->setChecked(false);
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
		ui->checkBoxJig03->setText(xStringResource::GetVarName(MAIN_VAR_Y08));
		ui->checkBoxJig04->setText(xStringResource::GetVarName(MAIN_VAR_Y09));
		ui->checkBoxJig05->setText(xStringResource::GetVarName(MAIN_VAR_Y10));
		ui->checkBoxJig06->setText(xStringResource::GetVarName(MAIN_VAR_Y11));
		ui->checkBoxJig07->setText(xStringResource::GetVarName(MAIN_VAR_Y12));
		ui->checkBoxJig08->setText(xStringResource::GetVarName(MAIN_VAR_Y13));
		ui->checkBoxJig09->setText(xStringResource::GetVarName(MAIN_VAR_Y14));
		ui->checkBoxJig10->setText(xStringResource::GetVarName(MAIN_VAR_Y15));
		ui->checkBoxJig11->setText(xStringResource::GetVarName(MAIN_VAR_Y16));
		ui->checkBoxJig12->setText(xStringResource::GetVarName(MAIN_VAR_Y17));
		ui->checkBoxJig13->setText(xStringResource::GetVarName(MAIN_VAR_Y18));
		ui->checkBoxJig14->setText(xStringResource::GetVarName(MAIN_VAR_Y19));
		ui->checkBoxJig15->setText(xStringResource::GetVarName(MAIN_VAR_Y20));
		ui->checkBoxJig16->setText(xStringResource::GetVarName(MAIN_VAR_Y22));
    }
}
void FormBtnVacuum::retranslateUi(void)
{

    if((CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)||(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H730_5AXIS))
    {
        ui->checkBoxJig03->setText(xStringResource::GetVarName(MAIN_VAR_Y11));
        ui->checkBoxJig04->setText(xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->checkBoxJig05->setText(xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->checkBoxJig06->setText(xStringResource::GetVarName(MAIN_VAR_Y14));
        ui->checkBoxJig07->setText(xStringResource::GetVarName(MAIN_VAR_Y15));
        ui->checkBoxJig08->setText(xStringResource::GetVarName(MAIN_VAR_Y16));
        ui->checkBoxJig09->setText(xStringResource::GetVarName(MAIN_VAR_Y17));
        ui->checkBoxJig10->setText(xStringResource::GetVarName(MAIN_VAR_Y18));
        ui->checkBoxJig11->setText(xStringResource::GetVarName(MAIN_VAR_Y19));
        ui->checkBoxJig12->setText(xStringResource::GetVarName(MAIN_VAR_Y20));
        ui->checkBoxJig13->setText(xStringResource::GetVarName(MAIN_VAR_Y21));
        ui->checkBoxJig14->setText(xStringResource::GetVarName(MAIN_VAR_Y22));
        ui->checkBoxJig15->setText(xStringResource::GetVarName(MAIN_VAR_Y23));
        ui->checkBoxJig16->setText(xStringResource::GetVarName(MAIN_VAR_Y24));
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        ui->checkBoxJig03->setText(xStringResource::GetVarName(MAIN_VAR_Y08));
        ui->checkBoxJig04->setText(xStringResource::GetVarName(MAIN_VAR_Y09));
        ui->checkBoxJig05->setText(xStringResource::GetVarName(MAIN_VAR_Y10));
        ui->checkBoxJig06->setText(xStringResource::GetVarName(MAIN_VAR_Y11));
        ui->checkBoxJig07->setText(xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->checkBoxJig08->setText(xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->checkBoxJig09->setText(xStringResource::GetVarName(MAIN_VAR_Y14));
        ui->checkBoxJig10->setText(xStringResource::GetVarName(MAIN_VAR_Y15));
        ui->checkBoxJig11->setText(xStringResource::GetVarName(MAIN_VAR_Y16));
        ui->checkBoxJig12->setText(xStringResource::GetVarName(MAIN_VAR_Y17));
        ui->checkBoxJig13->setText(xStringResource::GetVarName(MAIN_VAR_Y18));
        ui->checkBoxJig14->setText(xStringResource::GetVarName(MAIN_VAR_Y19));
        ui->checkBoxJig15->setText(xStringResource::GetVarName(MAIN_VAR_Y20));
        ui->checkBoxJig16->setText(xStringResource::GetVarName(MAIN_VAR_Y22));
    }
    else
    {
        if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
        {
            ui->checkBoxJig03->setText(xStringResource::GetVarName(MAIN_VAR_Y12));
            ui->checkBoxJig04->setText(xStringResource::GetVarName(MAIN_VAR_Y13));
            ui->checkBoxJig05->setText(xStringResource::GetVarName(MAIN_VAR_Y14));
            if(CMBProtocol::GetFunctions(SUB_FUN2_CAN_IMM))
            {
                ui->checkBoxMain01->setText(xStringResource::GetVarName(MAIN_VAR_Y01));
                ui->checkBoxMain02->setText(xStringResource::GetVarName(MAIN_VAR_Y02));
                ui->checkBoxMain03->setText(xStringResource::GetVarName(MAIN_VAR_Y03));
                ui->checkBoxMain04->setText(xStringResource::GetVarName(MAIN_VAR_Y04));
                ui->checkBoxMain05->setText(xStringResource::GetVarName(MAIN_VAR_Y05));
                ui->checkBoxMain08->setText(xStringResource::GetVarName(MAIN_VAR_Y08));
                ui->checkBoxMain09->setText(xStringResource::GetVarName(MAIN_VAR_Y09));
                ui->checkBoxMain10->setText(xStringResource::GetVarName(MAIN_VAR_Y10));
                ui->checkBoxMain11->setText(xStringResource::GetVarName(MAIN_VAR_Y11));
                ui->checkBoxMain15->setText(xStringResource::GetVarName(MAIN_VAR_Y15));
            }
        }
        else
        {
            ui->checkBoxJig03->setText(xStringResource::GetVarName(EM1_VAR_Y02));
            ui->checkBoxJig04->setText(xStringResource::GetVarName(EM1_VAR_Y03));
            ui->checkBoxJig05->setText(xStringResource::GetVarName(EM1_VAR_Y04));
            ui->checkBoxJig06->setText(xStringResource::GetVarName(EM1_VAR_Y05));
            ui->checkBoxJig07->setText(xStringResource::GetVarName(EM1_VAR_Y06));
            ui->checkBoxJig08->setText(xStringResource::GetVarName(EM1_VAR_Y07));
            ui->checkBoxJig09->setText(xStringResource::GetVarName(EM1_VAR_Y08));
            ui->checkBoxJig10->setText(xStringResource::GetVarName(EM1_VAR_Y09));
            ui->checkBoxJig11->setText(xStringResource::GetVarName(EM1_VAR_Y10));
            ui->checkBoxJig12->setText(xStringResource::GetVarName(EM1_VAR_Y11));
            ui->checkBoxJig13->setText(xStringResource::GetVarName(EM1_VAR_Y12));
            ui->checkBoxJig14->setText(xStringResource::GetVarName(EM1_VAR_Y13));
            ui->checkBoxJig15->setText(xStringResource::GetVarName(EM1_VAR_Y14));
            ui->checkBoxJig16->setText(xStringResource::GetVarName(EM1_VAR_Y15));
        }
    }

    UpdateWidgetState();
}

int FormBtnVacuum::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

int FormBtnVacuum::GetType()
{
    if (ui->radioButton_on->isChecked())
        return 1;
    else
        return 0;
}
// 选择治具表
int FormBtnVacuum::GetOutBmp()
{
    if(CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        outbmp  = ((quint16)(ui->checkBoxMain01->isChecked()?1:0)) << 1;
        outbmp |= ((quint16)(ui->checkBoxMain02->isChecked()?1:0)) << 2;
        outbmp |= ((quint16)(ui->checkBoxMain03->isChecked()?1:0)) << 3;
        outbmp |= ((quint16)(ui->checkBoxMain04->isChecked()?1:0)) << 4;
        outbmp |= ((quint16)(ui->checkBoxMain05->isChecked()?1:0)) << 5;
        outbmp |= ((quint16)(ui->checkBoxMain08->isChecked()?1:0)) << 8;
        outbmp |= ((quint16)(ui->checkBoxMain09->isChecked()?1:0)) << 9;
        outbmp |= ((quint16)(ui->checkBoxMain10->isChecked()?1:0)) << 10;
        outbmp |= ((quint16)(ui->checkBoxMain11->isChecked()?1:0)) << 11;
        outbmp |= ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 12;
        outbmp |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 13;
        outbmp |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 14;
        outbmp |= ((quint16)(ui->checkBoxMain15->isChecked()?1:0)) << 15;
    }
    else
    {
        outbmp  = ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 0;
        outbmp |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 1;
        outbmp |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 2;
        outbmp |= ((quint16)(ui->checkBoxJig06->isChecked()?1:0)) << 3;
        outbmp |= ((quint16)(ui->checkBoxJig07->isChecked()?1:0)) << 4;
        outbmp |= ((quint16)(ui->checkBoxJig08->isChecked()?1:0)) << 5;
        outbmp |= ((quint16)(ui->checkBoxJig09->isChecked()?1:0)) << 6;
        outbmp |= ((quint16)(ui->checkBoxJig10->isChecked()?1:0)) << 7;
        outbmp |= ((quint16)(ui->checkBoxJig11->isChecked()?1:0)) << 8;
        outbmp |= ((quint16)(ui->checkBoxJig12->isChecked()?1:0)) << 9;
        outbmp |= ((quint16)(ui->checkBoxJig13->isChecked()?1:0)) << 10;
        outbmp |= ((quint16)(ui->checkBoxJig14->isChecked()?1:0)) << 11;
        outbmp |= ((quint16)(ui->checkBoxJig15->isChecked()?1:0)) << 12;
        outbmp |= ((quint16)(ui->checkBoxJig16->isChecked()?1:0)) << 13;
    }
    return outbmp;
}
// 检测表
int FormBtnVacuum::GetInBmp()
{
    quint16 inbmp;
    if(CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        inbmp  = ((quint16)((ui->checkBoxcheckM01->isChecked())?1:0)) << 1;
        inbmp |= ((quint16)((ui->checkBoxcheckM02->isChecked())?1:0)) << 2;
        inbmp |= ((quint16)((ui->checkBoxcheckM03->isChecked())?1:0)) << 3;
        inbmp |= ((quint16)((ui->checkBoxcheckM04->isChecked())?1:0)) << 4;
        inbmp |= ((quint16)((ui->checkBoxcheckM05->isChecked())?1:0)) << 5;
        inbmp |= ((quint16)((ui->checkBoxcheckM08->isChecked())?1:0)) << 8;
        inbmp |= ((quint16)((ui->checkBoxcheckM09->isChecked())?1:0)) << 9;
        inbmp |= ((quint16)((ui->checkBoxcheckM10->isChecked())?1:0)) << 10;
        inbmp |= ((quint16)((ui->checkBoxcheckM11->isChecked())?1:0)) << 11;
        inbmp |= ((quint16)((ui->checkBoxcheck03->isChecked())?1:0)) << 12;
        inbmp |= ((quint16)((ui->checkBoxcheck04->isChecked())?1:0)) << 13;
        inbmp |= ((quint16)((ui->checkBoxcheck05->isChecked())?1:0)) << 14;
        inbmp |= ((quint16)((ui->checkBoxcheckM15->isChecked())?1:0)) << 15;

    }
    else
    {
        inbmp  = ((quint16)((ui->checkBoxcheck03->isChecked()&&ui->checkBoxcheck03->isEnabled())?1:0)) << 0;
        inbmp |= ((quint16)((ui->checkBoxcheck04->isChecked()&&ui->checkBoxcheck04->isEnabled())?1:0)) << 1;
        inbmp |= ((quint16)((ui->checkBoxcheck05->isChecked()&&ui->checkBoxcheck05->isEnabled())?1:0)) << 2;
        inbmp |= ((quint16)((ui->checkBoxcheck06->isChecked()&&ui->checkBoxcheck06->isEnabled())?1:0)) << 3;
        inbmp |= ((quint16)((ui->checkBoxcheck07->isChecked()&&ui->checkBoxcheck07->isEnabled())?1:0)) << 4;
        inbmp |= ((quint16)((ui->checkBoxcheck08->isChecked()&&ui->checkBoxcheck08->isEnabled())?1:0)) << 5;
        inbmp |= ((quint16)((ui->checkBoxcheck09->isChecked()&&ui->checkBoxcheck09->isEnabled())?1:0)) << 6;
        inbmp |= ((quint16)((ui->checkBoxcheck10->isChecked()&&ui->checkBoxcheck10->isEnabled())?1:0)) << 7;
        inbmp |= ((quint16)((ui->checkBoxcheck11->isChecked()&&ui->checkBoxcheck11->isEnabled())?1:0)) << 8;
        inbmp |= ((quint16)((ui->checkBoxcheck12->isChecked()&&ui->checkBoxcheck11->isEnabled())?1:0)) << 9;
        inbmp |= ((quint16)((ui->checkBoxcheck13->isChecked()&&ui->checkBoxcheck11->isEnabled())?1:0)) << 10;
        inbmp |= ((quint16)((ui->checkBoxcheck14->isChecked()&&ui->checkBoxcheck11->isEnabled())?1:0)) << 11;
        inbmp |= ((quint16)((ui->checkBoxcheck15->isChecked()&&ui->checkBoxcheck11->isEnabled())?1:0)) << 12;
        inbmp |= ((quint16)((ui->checkBoxcheck16->isChecked()&&ui->checkBoxcheck11->isEnabled())?1:0)) << 13;
    }
    return inbmp;
}

void FormBtnVacuum::UpdateWidgetState()
{
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        ui->checkBoxJig06->setVisible(false);
        ui->checkBoxJig07->setVisible(false);
        ui->checkBoxJig08->setVisible(false);
        ui->checkBoxcheck06->setVisible(false);
        ui->checkBoxcheck07->setVisible(false);
        ui->checkBoxcheck08->setVisible(false);
    }
//    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F3) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
//        ui->BtnNext->setVisible(true);
//    else
//        ui->BtnNext->setVisible(false);

    if (CMBProtocol::GetRunRotateUse())
    {
        ui->checkBoxJig10->setEnabled(false);
        ui->checkBoxcheck10->setEnabled(false);
        ui->checkBoxJig11->setEnabled(false);
        ui->checkBoxcheck11->setEnabled(false);
    }
    else
    {
        ui->checkBoxJig10->setEnabled(true);
        ui->checkBoxcheck10->setEnabled(ui->checkBoxJig10->isChecked() && ui->checkBoxJig10->isEnabled());
        ui->checkBoxJig11->setEnabled(true);
        ui->checkBoxcheck11->setEnabled(ui->checkBoxJig11->isChecked() && ui->checkBoxJig11->isEnabled());
    }
    if (CMBProtocol::GetRunnerUse())
    {
        ui->checkBoxJig13->setEnabled(false);
        ui->checkBoxcheck13->setEnabled(false);
        ui->checkBoxJig14->setEnabled(false);
        ui->checkBoxcheck14->setEnabled(false);
    }
    else
    {
        ui->checkBoxJig13->setEnabled(true);
        ui->checkBoxcheck13->setEnabled(ui->checkBoxJig13->isChecked() && ui->checkBoxJig13->isEnabled());
        ui->checkBoxJig14->setEnabled(true);
        ui->checkBoxcheck14->setEnabled(ui->checkBoxJig14->isChecked() && ui->checkBoxJig14->isEnabled());
    }

    {
        ui->checkBoxMain01->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y01));
        ui->checkBoxMain02->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y02));
        ui->checkBoxMain03->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y03));
        ui->checkBoxMain04->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y04));
        ui->checkBoxMain05->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y05));
        ui->checkBoxMain08->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y08));
        ui->checkBoxMain09->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y09));
        ui->checkBoxMain10->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y10));
        ui->checkBoxMain11->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y11));
        ui->checkBoxMain15->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y15));

        ui->checkBoxcheckM01->setEnabled(ui->checkBoxMain01->isChecked() && ui->checkBoxMain01->isEnabled());
        ui->checkBoxcheckM02->setEnabled(ui->checkBoxMain02->isChecked() && ui->checkBoxMain02->isEnabled());
        ui->checkBoxcheckM03->setEnabled(ui->checkBoxMain03->isChecked() && ui->checkBoxMain03->isEnabled());
        ui->checkBoxcheckM04->setEnabled(ui->checkBoxMain04->isChecked() && ui->checkBoxMain04->isEnabled());
        ui->checkBoxcheckM05->setEnabled(ui->checkBoxMain05->isChecked() && ui->checkBoxMain05->isEnabled());
        ui->checkBoxcheckM08->setEnabled(ui->checkBoxMain08->isChecked() && ui->checkBoxMain08->isEnabled());
        ui->checkBoxcheckM09->setEnabled(ui->checkBoxMain09->isChecked() && ui->checkBoxMain09->isEnabled());
        ui->checkBoxcheckM10->setEnabled(ui->checkBoxMain10->isChecked() && ui->checkBoxMain10->isEnabled());
        ui->checkBoxcheckM11->setEnabled(ui->checkBoxMain11->isChecked() && ui->checkBoxMain11->isEnabled());
        ui->checkBoxcheckM15->setEnabled(ui->checkBoxMain15->isChecked() && ui->checkBoxMain15->isEnabled());
    }
}

// 输入输出延时信号槽
void FormBtnVacuum::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}
// 治具框状态改变
void FormBtnVacuum::stateChanged_checkJig03(int state)
{
    ui->checkBoxcheck03->setEnabled(ui->checkBoxJig03->isChecked());
    ui->checkBoxcheck03->setChecked(ui->checkBoxJig03->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig04(int state)
{
    ui->checkBoxcheck04->setEnabled(ui->checkBoxJig04->isChecked());
    ui->checkBoxcheck04->setChecked(ui->checkBoxJig04->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig05(int state)
{
    ui->checkBoxcheck05->setEnabled(ui->checkBoxJig05->isChecked());
    ui->checkBoxcheck05->setChecked(ui->checkBoxJig05->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig06(int state)
{
    ui->checkBoxcheck06->setEnabled(ui->checkBoxJig06->isChecked());
    ui->checkBoxcheck06->setChecked(ui->checkBoxJig06->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig07(int state)
{
    ui->checkBoxcheck07->setEnabled(ui->checkBoxJig07->isChecked());
    ui->checkBoxcheck07->setChecked(ui->checkBoxJig07->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig08(int state)
{
    ui->checkBoxcheck08->setEnabled(ui->checkBoxJig08->isChecked());
    ui->checkBoxcheck08->setChecked(ui->checkBoxJig08->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig09(int state)
{
    ui->checkBoxcheck09->setEnabled(ui->checkBoxJig09->isChecked());
    ui->checkBoxcheck09->setChecked(ui->checkBoxJig09->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig10(int state)
{
    ui->checkBoxcheck10->setEnabled(ui->checkBoxJig10->isChecked());
    ui->checkBoxcheck10->setChecked(ui->checkBoxJig10->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig11(int state)
{
    ui->checkBoxcheck11->setEnabled(ui->checkBoxJig11->isChecked());
    ui->checkBoxcheck11->setChecked(ui->checkBoxJig11->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig12(int state)
{
    ui->checkBoxcheck12->setEnabled(ui->checkBoxJig12->isChecked());
    ui->checkBoxcheck12->setChecked(ui->checkBoxJig12->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig13(int state)
{
    ui->checkBoxcheck13->setEnabled(ui->checkBoxJig13->isChecked());
    ui->checkBoxcheck13->setChecked(ui->checkBoxJig13->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig14(int state)
{
    ui->checkBoxcheck14->setEnabled(ui->checkBoxJig14->isChecked());
    ui->checkBoxcheck14->setChecked(ui->checkBoxJig14->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig15(int state)
{
    ui->checkBoxcheck15->setEnabled(ui->checkBoxJig15->isChecked());
    ui->checkBoxcheck15->setChecked(ui->checkBoxJig15->isChecked());
}
void FormBtnVacuum::stateChanged_checkJig16(int state)
{
    ui->checkBoxcheck16->setEnabled(ui->checkBoxJig16->isChecked());
    ui->checkBoxcheck16->setChecked(ui->checkBoxJig16->isChecked());
}

void FormBtnVacuum::stateChanged(int state)
{
    QObject*stateChange = (QObject*)sender();
    if(stateChange == ui->checkBoxMain01)
        ui->checkBoxcheckM01->setEnabled(state);

    else if(stateChange == ui->checkBoxMain02)
        ui->checkBoxcheckM02->setEnabled(state);

    else if(stateChange == ui->checkBoxMain03)
        ui->checkBoxcheckM03->setEnabled(state);

    else if(stateChange == ui->checkBoxMain04)
        ui->checkBoxcheckM04->setEnabled(state);

    else if(stateChange == ui->checkBoxMain05)
        ui->checkBoxcheckM05->setEnabled(state);

    else if(stateChange == ui->checkBoxMain08)
        ui->checkBoxcheckM08->setEnabled(state);

    else if(stateChange == ui->checkBoxMain09)
        ui->checkBoxcheckM09->setEnabled(state);

    else if(stateChange == ui->checkBoxMain10)
        ui->checkBoxcheckM10->setEnabled(state);

    else if(stateChange == ui->checkBoxMain11)
        ui->checkBoxcheckM11->setEnabled(state);

//    else if(stateChange == ui->checkBoxMain12)
//        ui->checkBoxcheckM12->setEnabled(state);

//    else if(stateChange == ui->checkBoxMain13)
//        ui->checkBoxcheckM13->setEnabled(state);

//    else if(stateChange == ui->checkBoxMain14)
//        ui->checkBoxcheckM14->setEnabled(state);

    else if(stateChange == ui->checkBoxMain15)
        ui->checkBoxcheckM15->setEnabled(state);

}
void FormBtnVacuum::btnNextclicked(void)
{
    if(CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
        ui->stackedWidget->setCurrentIndex(2);
    else
        ui->stackedWidget->setCurrentIndex(1);
}
void FormBtnVacuum::btnPrevclicked(void)
{
    ui->stackedWidget->setCurrentIndex(0);
}
