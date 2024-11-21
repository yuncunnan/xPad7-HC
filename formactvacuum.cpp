#include "cmbprotocol.h"
#include "safeswitch.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "formactvacuum.h"
#include "ui_formactvacuum.h"
#include "xioport.h"

FormActVacuum::FormActVacuum(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormActVacuum)
{
    ui->setupUi(this);
    retranslateUi();
#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(600.00);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(6000.0);
#endif
    pModbus = modbus;
    ui->stackedWidget->setCurrentIndex(0);
}

FormActVacuum::~FormActVacuum()
{
    delete ui;
}

void FormActVacuum::changeEvent(QEvent *e)
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
void FormActVacuum::retranslateUi(void)
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
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_ECAT_CANOPEN)
    {
        ui->checkBoxJig03->setText(xStringResource::GetVarName(MAIN_VAR_Y16));
        ui->checkBoxJig04->setText(xStringResource::GetVarName(MAIN_VAR_Y17));
        ui->checkBoxJig05->setText(xStringResource::GetVarName(MAIN_VAR_Y18));
        ui->checkBoxJig06->setText(xStringResource::GetVarName(MAIN_VAR_Y19));
        ui->checkBoxJig07->setText(xStringResource::GetVarName(MAIN_VAR_Y20));
        ui->checkBoxJig08->setText(xStringResource::GetVarName(MAIN_VAR_Y21));
        ui->checkBoxJig09->setText(xStringResource::GetVarName(MAIN_VAR_Y22));
        ui->checkBoxJig10->setText(xStringResource::GetVarName(MAIN_VAR_Y23));
        ui->checkBoxJig11->setText(xStringResource::GetVarName(MAIN_VAR_Y24));
        ui->checkBoxJig12->setText(xStringResource::GetVarName(MAIN_VAR_Y25));
        ui->checkBoxJig13->setText(xStringResource::GetVarName(MAIN_VAR_Y26));
        ui->checkBoxJig14->setText(xStringResource::GetVarName(MAIN_VAR_Y27));
        ui->checkBoxJig15->setText(xStringResource::GetVarName(MAIN_VAR_Y28));
        ui->checkBoxJig16->setText(xStringResource::GetVarName(MAIN_VAR_Y29));
    }
    else
    {
        if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0))
        {
            ui->checkBoxJig03->setText(xStringResource::GetVarName(MAIN_VAR_Y12));
            ui->checkBoxJig04->setText(xStringResource::GetVarName(MAIN_VAR_Y13));
            ui->checkBoxJig05->setText(xStringResource::GetVarName(MAIN_VAR_Y14));
            if(pModbus->GetFunctions(SUB_FUN2_CAN_IMM))
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
}

void FormActVacuum::SetInterval(int interval)
{
	ui->BoxInterval->setValue(interval);
}

int FormActVacuum::GetInterval()
{
	return ui->BoxInterval->value();
}

void FormActVacuum::SetDelay(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormActVacuum::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

void FormActVacuum::SetType(int type)
{
	if (type == 1)
        ui->radioButton_on->setChecked(true);
    else
        ui->radioButton_off->setChecked(true);
}

int FormActVacuum::GetType()
{
    if (ui->radioButton_on->isChecked())
        return 1;
	else
		return 0;
}

void FormActVacuum::SetOutBmp(int bmp)
{
    outbmp = bmp;
    if((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0) && pModbus->GetFunctions(SUB_FUN2_CAN_IMM))
    {
        ui->checkBoxJig03->setChecked((outbmp>>12)&1);
        ui->checkBoxJig04->setChecked((outbmp>>13)&1);
        ui->checkBoxJig05->setChecked((outbmp>>14)&1);
        ui->checkBoxMain01->setChecked((outbmp>>1)&1);
        ui->checkBoxMain02->setChecked((outbmp>>2)&1);
        ui->checkBoxMain03->setChecked((outbmp>>3)&1);
        ui->checkBoxMain04->setChecked((outbmp>>4)&1);
        ui->checkBoxMain05->setChecked((outbmp>>5)&1);
        ui->checkBoxMain08->setChecked((outbmp>>8)&1);
        ui->checkBoxMain09->setChecked((outbmp>>9)&1);
        ui->checkBoxMain10->setChecked((outbmp>>10)&1);
        ui->checkBoxMain11->setChecked((outbmp>>11)&1);
        ui->checkBoxMain15->setChecked((outbmp>>15)&1);

        ui->checkBoxcheck03->setEnabled((outbmp>>12)&1);
        ui->checkBoxcheck04->setEnabled((outbmp>>13)&1);
        ui->checkBoxcheck05->setEnabled((outbmp>>14)&1);
        ui->checkBoxcheckM01->setEnabled((outbmp>>1)&1);
        ui->checkBoxcheckM02->setEnabled((outbmp>>2)&1);
        ui->checkBoxcheckM03->setEnabled((outbmp>>3)&1);
        ui->checkBoxcheckM04->setEnabled((outbmp>>4)&1);
        ui->checkBoxcheckM05->setEnabled((outbmp>>5)&1);
        ui->checkBoxcheckM08->setEnabled((outbmp>>8)&1);
        ui->checkBoxcheckM09->setEnabled((outbmp>>9)&1);
        ui->checkBoxcheckM10->setEnabled((outbmp>>10)&1);
        ui->checkBoxcheckM11->setEnabled((outbmp>>11)&1);
        ui->checkBoxcheckM15->setEnabled((outbmp>>15)&1);
    }
    else
    {
    ui->checkBoxJig03->setChecked((outbmp>>0)&1);
    ui->checkBoxJig04->setChecked((outbmp>>1)&1);
    ui->checkBoxJig05->setChecked((outbmp>>2)&1);
    ui->checkBoxJig06->setChecked((outbmp>>3)&1);
    ui->checkBoxJig07->setChecked((outbmp>>4)&1);
    ui->checkBoxJig08->setChecked((outbmp>>5)&1);
    ui->checkBoxJig09->setChecked((outbmp>>6)&1);
    ui->checkBoxJig10->setChecked((outbmp>>7)&1);
    ui->checkBoxJig11->setChecked((outbmp>>8)&1);
    ui->checkBoxJig12->setChecked((outbmp>>9)&1);
    ui->checkBoxJig13->setChecked((outbmp>>10)&1);
    ui->checkBoxJig14->setChecked((outbmp>>11)&1);
    ui->checkBoxJig15->setChecked((outbmp>>12)&1);
    ui->checkBoxJig16->setChecked((outbmp>>13)&1);

    ui->checkBoxcheck03->setEnabled((outbmp>>0)&1);
    ui->checkBoxcheck04->setEnabled((outbmp>>1)&1);
    ui->checkBoxcheck05->setEnabled((outbmp>>2)&1);
    ui->checkBoxcheck06->setEnabled((outbmp>>3)&1);
    ui->checkBoxcheck07->setEnabled((outbmp>>4)&1);
    ui->checkBoxcheck08->setEnabled((outbmp>>5)&1);
    ui->checkBoxcheck09->setEnabled((outbmp>>6)&1);
    ui->checkBoxcheck10->setEnabled((outbmp>>7)&1);
    ui->checkBoxcheck11->setEnabled((outbmp>>8)&1);
    ui->checkBoxcheck12->setEnabled((outbmp>>9)&1);
    ui->checkBoxcheck13->setEnabled((outbmp>>10)&1);
    ui->checkBoxcheck14->setEnabled((outbmp>>11)&1);
    ui->checkBoxcheck15->setEnabled((outbmp>>12)&1);
    ui->checkBoxcheck16->setEnabled((outbmp>>13)&1);
    }
}

int FormActVacuum::GetOutBmp()
{
    if((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)&& pModbus->GetFunctions(SUB_FUN2_CAN_IMM))
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

void FormActVacuum::SetInBmp(int bmp)
{
    if((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)&& pModbus->GetFunctions(SUB_FUN2_CAN_IMM))
    {
        ui->checkBoxcheckM01->setChecked((bmp>>1)&1);
        ui->checkBoxcheckM02->setChecked((bmp>>2)&1);
        ui->checkBoxcheckM03->setChecked((bmp>>3)&1);
        ui->checkBoxcheckM04->setChecked((bmp>>4)&1);
        ui->checkBoxcheckM05->setChecked((bmp>>5)&1);
        ui->checkBoxcheckM08->setChecked((bmp>>8)&1);
        ui->checkBoxcheckM09->setChecked((bmp>>9)&1);
        ui->checkBoxcheckM10->setChecked((bmp>>10)&1);
        ui->checkBoxcheckM11->setChecked((bmp>>11)&1);
        ui->checkBoxcheck03->setChecked((bmp>>12)&1);
        ui->checkBoxcheck04->setChecked((bmp>>13)&1);
        ui->checkBoxcheck05->setChecked((bmp>>14)&1);
        ui->checkBoxcheckM15->setChecked((bmp>>15)&1);

    }
    else
    {
        ui->checkBoxcheck03->setChecked((bmp>>0)&1);
        ui->checkBoxcheck04->setChecked((bmp>>1)&1);
        ui->checkBoxcheck05->setChecked((bmp>>2)&1);
        ui->checkBoxcheck06->setChecked((bmp>>3)&1);
        ui->checkBoxcheck07->setChecked((bmp>>4)&1);
        ui->checkBoxcheck08->setChecked((bmp>>5)&1);
        ui->checkBoxcheck09->setChecked((bmp>>6)&1);
        ui->checkBoxcheck10->setChecked((bmp>>7)&1);
        ui->checkBoxcheck11->setChecked((bmp>>8)&1);
        ui->checkBoxcheck12->setChecked((bmp>>9)&1);
        ui->checkBoxcheck13->setChecked((bmp>>10)&1);
        ui->checkBoxcheck14->setChecked((bmp>>11)&1);
        ui->checkBoxcheck15->setChecked((bmp>>12)&1);
        ui->checkBoxcheck16->setChecked((bmp>>13)&1);
    }
}

int FormActVacuum::GetInBmp()
{
  //  quint16 inbmp;
    if(pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
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
        inbmp  = ((quint16)((ui->checkBoxcheck03->isChecked())?1:0)) << 0;
        inbmp |= ((quint16)((ui->checkBoxcheck04->isChecked())?1:0)) << 1;
        inbmp |= ((quint16)((ui->checkBoxcheck05->isChecked())?1:0)) << 2;
        inbmp |= ((quint16)((ui->checkBoxcheck06->isChecked())?1:0)) << 3;
        inbmp |= ((quint16)((ui->checkBoxcheck07->isChecked())?1:0)) << 4;
        inbmp |= ((quint16)((ui->checkBoxcheck08->isChecked())?1:0)) << 5;
        inbmp |= ((quint16)((ui->checkBoxcheck09->isChecked())?1:0)) << 6;
        inbmp |= ((quint16)((ui->checkBoxcheck10->isChecked())?1:0)) << 7;
        inbmp |= ((quint16)((ui->checkBoxcheck11->isChecked())?1:0)) << 8;
        inbmp |= ((quint16)((ui->checkBoxcheck12->isChecked())?1:0)) << 9;
        inbmp |= ((quint16)((ui->checkBoxcheck13->isChecked())?1:0)) << 10;
        inbmp |= ((quint16)((ui->checkBoxcheck14->isChecked())?1:0)) << 11;
        inbmp |= ((quint16)((ui->checkBoxcheck15->isChecked())?1:0)) << 12;
        inbmp |= ((quint16)((ui->checkBoxcheck16->isChecked())?1:0)) << 13;
     }
   return inbmp;
}

void FormActVacuum::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->BoxInterval->setEnabled(false);
        ui->radioButton_on->setEnabled(false);
        ui->radioButton_off->setEnabled(false);
        ui->BtnOn->setEnabled(false);
        ui->BtnOff->setEnabled(false);
    }
//    else
//    {
//        if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
//        {
//            ui->radioButton_on->setEnabled(true);
//            ui->radioButton_off->setEnabled(true);
//            ui->BtnOn->setEnabled(true);
//            ui->BtnOff->setEnabled(true);
//            ui->checkBoxJig03->setEnabled(true);
//            ui->checkBoxJig04->setEnabled(true);
//            ui->checkBoxJig05->setEnabled(true);
//            ui->checkBoxJig06->setEnabled(true);
//            ui->checkBoxJig07->setEnabled(true);
//            ui->checkBoxJig08->setEnabled(true);
//            ui->checkBoxJig09->setEnabled(true);
//            ui->checkBoxJig10->setEnabled(true);
//            ui->checkBoxJig11->setEnabled(true);
//            ui->checkBoxJig12->setEnabled(true);
//            ui->checkBoxJig13->setEnabled(true);
//            ui->checkBoxJig14->setEnabled(true);
//            ui->checkBoxJig15->setEnabled(true);
//            ui->checkBoxJig16->setEnabled(true);
//            ui->checkBoxcheck03->setEnabled(true);
//            ui->checkBoxcheck04->setEnabled(true);
//            ui->checkBoxcheck05->setEnabled(true);
//            ui->checkBoxcheck06->setEnabled(true);
//            ui->checkBoxcheck07->setEnabled(true);
//            ui->checkBoxcheck08->setEnabled(true);
//            ui->checkBoxcheck09->setEnabled(true);
//            ui->checkBoxcheck10->setEnabled(true);
//            ui->checkBoxcheck11->setEnabled(true);
//            ui->checkBoxcheck12->setEnabled(true);
//            ui->checkBoxcheck13->setEnabled(true);
//            ui->checkBoxcheck14->setEnabled(true);
//            ui->checkBoxcheck15->setEnabled(true);
//            ui->checkBoxcheck16->setEnabled(true);
//            ui->BoxInterval->setEnabled(true);
//            {
//                ui->checkBoxMain01->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y01));
//                ui->checkBoxMain02->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y02));
//                ui->checkBoxMain03->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y03));
//                ui->checkBoxMain04->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y04));
//                ui->checkBoxMain05->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y05));
//                ui->checkBoxMain08->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y08));
//                ui->checkBoxMain09->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y09));
//                ui->checkBoxMain10->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y10));
//                ui->checkBoxMain11->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y11));
//        //        ui->checkBoxMain12->setEnabled(false);//xIoPort::IsVisibleExtOut(MAIN_VAR_Y12)
//        //        ui->checkBoxMain13->setEnabled(false);//xIoPort::IsVisibleExtOut(MAIN_VAR_Y13)
//        //        ui->checkBoxMain14->setEnabled(false);//xIoPort::IsVisibleExtOut(MAIN_VAR_Y14)
//                ui->checkBoxMain15->setEnabled(xIoPort::IsVisibleExtOut(MAIN_VAR_Y15));

//                ui->checkBoxcheckM01->setEnabled(ui->checkBoxMain01->isChecked() && ui->checkBoxMain01->isEnabled());
//                ui->checkBoxcheckM02->setEnabled(ui->checkBoxMain02->isChecked() && ui->checkBoxMain02->isEnabled());
//                ui->checkBoxcheckM03->setEnabled(ui->checkBoxMain03->isChecked() && ui->checkBoxMain03->isEnabled());
//                ui->checkBoxcheckM04->setEnabled(ui->checkBoxMain04->isChecked() && ui->checkBoxMain04->isEnabled());
//                ui->checkBoxcheckM05->setEnabled(ui->checkBoxMain05->isChecked() && ui->checkBoxMain05->isEnabled());
//                ui->checkBoxcheckM08->setEnabled(ui->checkBoxMain08->isChecked() && ui->checkBoxMain08->isEnabled());
//                ui->checkBoxcheckM09->setEnabled(ui->checkBoxMain09->isChecked() && ui->checkBoxMain09->isEnabled());
//                ui->checkBoxcheckM10->setEnabled(ui->checkBoxMain10->isChecked() && ui->checkBoxMain10->isEnabled());
//                ui->checkBoxcheckM11->setEnabled(ui->checkBoxMain11->isChecked() && ui->checkBoxMain11->isEnabled());
//        //        ui->checkBoxcheckM12->setEnabled(ui->checkBoxMain12->isChecked() && ui->checkBoxMain12->isEnabled());
//        //        ui->checkBoxcheckM13->setEnabled(ui->checkBoxMain13->isChecked() && ui->checkBoxMain13->isEnabled());
//        //        ui->checkBoxcheckM14->setEnabled(ui->checkBoxMain14->isChecked() && ui->checkBoxMain14->isEnabled());
//                ui->checkBoxcheckM15->setEnabled(ui->checkBoxMain15->isChecked() && ui->checkBoxMain15->isEnabled());
//            }
//        }
//        else
//        {
//            ui->radioButton_on->setEnabled(false);
//            ui->radioButton_off->setEnabled(false);
//            ui->BtnOn->setEnabled(false);
//            ui->BtnOff->setEnabled(false);
//            ui->checkBoxJig03->setEnabled(false);
//            ui->checkBoxJig04->setEnabled(false);
//            ui->checkBoxJig05->setEnabled(false);
//            ui->checkBoxJig06->setEnabled(false);
//            ui->checkBoxJig07->setEnabled(false);
//            ui->checkBoxJig08->setEnabled(false);
//            ui->checkBoxJig09->setEnabled(false);
//            ui->checkBoxJig10->setEnabled(false);
//            ui->checkBoxJig11->setEnabled(false);
//            ui->checkBoxJig12->setEnabled(false);
//            ui->checkBoxJig13->setEnabled(false);
//            ui->checkBoxJig14->setEnabled(false);
//            ui->checkBoxJig15->setEnabled(false);
//            ui->checkBoxJig16->setEnabled(false);
//            ui->checkBoxcheck03->setEnabled(false);
//            ui->checkBoxcheck04->setEnabled(false);
//            ui->checkBoxcheck05->setEnabled(false);
//            ui->checkBoxcheck06->setEnabled(false);
//            ui->checkBoxcheck07->setEnabled(false);
//            ui->checkBoxcheck08->setEnabled(false);
//            ui->checkBoxcheck09->setEnabled(false);
//            ui->checkBoxcheck10->setEnabled(false);
//            ui->checkBoxcheck11->setEnabled(false);
//            ui->checkBoxcheck12->setEnabled(false);
//            ui->checkBoxcheck13->setEnabled(false);
//            ui->checkBoxcheck14->setEnabled(false);
//            ui->checkBoxcheck15->setEnabled(false);
//            ui->checkBoxcheck16->setEnabled(false);
//            ui->BoxInterval->setEnabled(false);
//            {
//                ui->checkBoxMain01->setEnabled(false);
//                ui->checkBoxMain02->setEnabled(false);
//                ui->checkBoxMain03->setEnabled(false);
//                ui->checkBoxMain04->setEnabled(false);
//                ui->checkBoxMain05->setEnabled(false);
//                ui->checkBoxMain08->setEnabled(false);
//                ui->checkBoxMain09->setEnabled(false);
//                ui->checkBoxMain10->setEnabled(false);
//                ui->checkBoxMain11->setEnabled(false);
//                ui->checkBoxMain15->setEnabled(false);

//                ui->checkBoxcheckM01->setEnabled(false);
//                ui->checkBoxcheckM02->setEnabled(false);
//                ui->checkBoxcheckM03->setEnabled(false);
//                ui->checkBoxcheckM04->setEnabled(false);
//                ui->checkBoxcheckM05->setEnabled(false);
//                ui->checkBoxcheckM08->setEnabled(false);
//                ui->checkBoxcheckM09->setEnabled(false);
//                ui->checkBoxcheckM10->setEnabled(false);
//                ui->checkBoxcheckM11->setEnabled(false);
//                ui->checkBoxcheckM15->setEnabled(false);
//            }
//        }
//    }
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
    retranslateUi();
}

// 输入输出延时信号槽
void FormActVacuum::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}
// 输入输出间隔信号槽
void FormActVacuum::inputInterval(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxInterval->minimum(), ui->BoxInterval->maximum()) == QDialog::Accepted)
		ui->BoxInterval->setValue(value);
}
// 扩展输出端口打开信号槽
void FormActVacuum::extOutOn(void)
{
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
	// 打开输出端口
    quint16 outselect;     // 治具选择
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)&& pModbus->GetFunctions(SUB_FUN2_CAN_IMM))
    {
        outselect  = ((quint16)(ui->checkBoxMain01->isChecked()?1:0)) << 1;
        outselect |= ((quint16)(ui->checkBoxMain02->isChecked()?1:0)) << 2;
        outselect |= ((quint16)(ui->checkBoxMain03->isChecked()?1:0)) << 3;
        outselect |= ((quint16)(ui->checkBoxMain04->isChecked()?1:0)) << 4;
        outselect |= ((quint16)(ui->checkBoxMain05->isChecked()?1:0)) << 5;
        outselect |= ((quint16)(ui->checkBoxMain08->isChecked()?1:0)) << 8;
        outselect |= ((quint16)(ui->checkBoxMain09->isChecked()?1:0)) << 9;
        outselect |= ((quint16)(ui->checkBoxMain10->isChecked()?1:0)) << 10;
        outselect |= ((quint16)(ui->checkBoxMain11->isChecked()?1:0)) << 11;
        outselect |= ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 12;
        outselect |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 13;
        outselect |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 14;
        outselect |= ((quint16)(ui->checkBoxMain15->isChecked()?1:0)) << 15;
    }
    else
    {
    outselect  = ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 0;
    outselect |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 1;
    outselect |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 2;
    outselect |= ((quint16)(ui->checkBoxJig06->isChecked()?1:0)) << 3;
    outselect |= ((quint16)(ui->checkBoxJig07->isChecked()?1:0)) << 4;
    outselect |= ((quint16)(ui->checkBoxJig08->isChecked()?1:0)) << 5;
    outselect |= ((quint16)(ui->checkBoxJig09->isChecked()?1:0)) << 6;
    outselect |= ((quint16)(ui->checkBoxJig10->isChecked()?1:0)) << 7;
    outselect |= ((quint16)(ui->checkBoxJig11->isChecked()?1:0)) << 8;
    outselect |= ((quint16)(ui->checkBoxJig12->isChecked()?1:0)) << 9;
    outselect |= ((quint16)(ui->checkBoxJig13->isChecked()?1:0)) << 10;
    outselect |= ((quint16)(ui->checkBoxJig14->isChecked()?1:0)) << 11;
    outselect |= ((quint16)(ui->checkBoxJig15->isChecked()?1:0)) << 12;
    outselect |= ((quint16)(ui->checkBoxJig16->isChecked()?1:0)) << 13;
    }
    if (outselect==0)return;
    pModbus->ManualVacuum(true, outselect);
}
// 扩展输出端口关闭信号槽
void FormActVacuum::extOutOff(void)
{
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
		return;
    quint16 outselect;     // 治具选择
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)&& pModbus->GetFunctions(SUB_FUN2_CAN_IMM))
    {
        outselect  = ((quint16)(ui->checkBoxMain01->isChecked()?1:0)) << 1;
        outselect |= ((quint16)(ui->checkBoxMain02->isChecked()?1:0)) << 2;
        outselect |= ((quint16)(ui->checkBoxMain03->isChecked()?1:0)) << 3;
        outselect |= ((quint16)(ui->checkBoxMain04->isChecked()?1:0)) << 4;
        outselect |= ((quint16)(ui->checkBoxMain05->isChecked()?1:0)) << 5;
        outselect |= ((quint16)(ui->checkBoxMain08->isChecked()?1:0)) << 8;
        outselect |= ((quint16)(ui->checkBoxMain09->isChecked()?1:0)) << 9;
        outselect |= ((quint16)(ui->checkBoxMain10->isChecked()?1:0)) << 10;
        outselect |= ((quint16)(ui->checkBoxMain11->isChecked()?1:0)) << 11;
        outselect |= ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 12;
        outselect |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 13;
        outselect |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 14;
        outselect |= ((quint16)(ui->checkBoxMain15->isChecked()?1:0)) << 15;
    }
    else
    {
    outselect  = ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 0;
    outselect |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 1;
    outselect |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 2;
    outselect |= ((quint16)(ui->checkBoxJig06->isChecked()?1:0)) << 3;
    outselect |= ((quint16)(ui->checkBoxJig07->isChecked()?1:0)) << 4;
    outselect |= ((quint16)(ui->checkBoxJig08->isChecked()?1:0)) << 5;
    outselect |= ((quint16)(ui->checkBoxJig09->isChecked()?1:0)) << 6;
    outselect |= ((quint16)(ui->checkBoxJig10->isChecked()?1:0)) << 7;
    outselect |= ((quint16)(ui->checkBoxJig11->isChecked()?1:0)) << 8;
    outselect |= ((quint16)(ui->checkBoxJig12->isChecked()?1:0)) << 9;
    outselect |= ((quint16)(ui->checkBoxJig13->isChecked()?1:0)) << 10;
    outselect |= ((quint16)(ui->checkBoxJig14->isChecked()?1:0)) << 11;
    outselect |= ((quint16)(ui->checkBoxJig15->isChecked()?1:0)) << 12;
    outselect |= ((quint16)(ui->checkBoxJig16->isChecked()?1:0)) << 13;
    }
    // 关闭输出端口
    if (outselect==0)return;
    pModbus->ManualVacuum(false, outselect);
}
// 治具框状态改变
void FormActVacuum::stateChanged_checkJig03(int state)
{
    if (ui->checkBoxJig03->isChecked())
        ui->checkBoxcheck03->setEnabled(true);
    else
    {
        ui->checkBoxcheck03->setChecked(false);
        ui->checkBoxcheck03->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig04(int state)
{
    if (ui->checkBoxJig04->isChecked())
        ui->checkBoxcheck04->setEnabled(true);
    else
    {
        ui->checkBoxcheck04->setChecked(false);

        ui->checkBoxcheck04->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig05(int state)
{
    if (ui->checkBoxJig05->isChecked())
        ui->checkBoxcheck05->setEnabled(true);
    else
    {
        ui->checkBoxcheck05->setChecked(false);
        ui->checkBoxcheck05->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig06(int state)
{
    if (ui->checkBoxJig06->isChecked())
        ui->checkBoxcheck06->setEnabled(true);
    else
    {
        ui->checkBoxcheck06->setChecked(false);
        ui->checkBoxcheck06->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig07(int state)
{
    if (ui->checkBoxJig07->isChecked())
        ui->checkBoxcheck07->setEnabled(true);
    else
    {
        ui->checkBoxcheck07->setChecked(false);
        ui->checkBoxcheck07->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig08(int state)
{
    if (ui->checkBoxJig08->isChecked())
        ui->checkBoxcheck08->setEnabled(true);
    else
    {
        ui->checkBoxcheck08->setChecked(false);
        ui->checkBoxcheck08->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig09(int state)
{
    if (ui->checkBoxJig09->isChecked())
        ui->checkBoxcheck09->setEnabled(true);
    else
    {
        ui->checkBoxcheck09->setChecked(false);
        ui->checkBoxcheck09->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig10(int state)
{
    if (ui->checkBoxJig10->isChecked())
        ui->checkBoxcheck10->setEnabled(true);
    else
    {
        ui->checkBoxcheck10->setChecked(false);
        ui->checkBoxcheck10->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig11(int state)
{
    if (ui->checkBoxJig11->isChecked())
        ui->checkBoxcheck11->setEnabled(true);
    else
    {
        ui->checkBoxcheck11->setChecked(false);
        ui->checkBoxcheck11->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig12(int state)
{
    if (ui->checkBoxJig12->isChecked())
        ui->checkBoxcheck12->setEnabled(true);
    else
    {
        ui->checkBoxcheck12->setChecked(false);
        ui->checkBoxcheck12->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig13(int state)
{
    if (ui->checkBoxJig13->isChecked())
        ui->checkBoxcheck13->setEnabled(true);
    else
    {
        ui->checkBoxcheck13->setChecked(false);
        ui->checkBoxcheck13->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig14(int state)
{
    if (ui->checkBoxJig14->isChecked())
        ui->checkBoxcheck14->setEnabled(true);
    else
    {
        ui->checkBoxcheck14->setChecked(false);
        ui->checkBoxcheck14->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig15(int state)
{
    if (ui->checkBoxJig15->isChecked())
        ui->checkBoxcheck15->setEnabled(true);
    else
    {
        ui->checkBoxcheck15->setChecked(false);
        ui->checkBoxcheck15->setEnabled(false);
    }
}
void FormActVacuum::stateChanged_checkJig16(int state)
{
    if (ui->checkBoxJig16->isChecked())
        ui->checkBoxcheck16->setEnabled(true);
    else
    {
        ui->checkBoxcheck16->setChecked(false);
        ui->checkBoxcheck16->setEnabled(false);
    }
}

void FormActVacuum::stateChanged(int state)
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
void FormActVacuum::btnNextclicked(void)
{
    if((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)&& pModbus->GetFunctions(SUB_FUN2_CAN_IMM))
        ui->stackedWidget->setCurrentIndex(2);
    else
        ui->stackedWidget->setCurrentIndex(1);
}
void FormActVacuum::btnPrevclicked(void)
{
    ui->stackedWidget->setCurrentIndex(0);
}
