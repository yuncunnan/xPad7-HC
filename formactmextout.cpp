#include "safeswitch.h"
#include "xconfig.h"
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "formactmextout.h"
#include "ui_formactmextout.h"

FormActMExtOut::FormActMExtOut(QWidget *parent) : QWidget(parent), ui(new Ui::FormActMExtOut)
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

FormActMExtOut::~FormActMExtOut()
{
    delete ui;
}

void FormActMExtOut::changeEvent(QEvent *e)
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
void FormActMExtOut::retranslateUi(void)
{
    /*************************pyq*不同主板时多扩展输出显示不同***************************************************************************/
//    ui->checkExtY02->setText(xStringResource::GetVarName(EM1_VAR_Y02));
//    ui->checkExtY03->setText(xStringResource::GetVarName(EM1_VAR_Y03));
//    ui->checkExtY04->setText(xStringResource::GetVarName(EM1_VAR_Y04));
//    ui->checkExtY05->setText(xStringResource::GetVarName(EM1_VAR_Y05));
//    ui->checkExtY06->setText(xStringResource::GetVarName(EM1_VAR_Y06));
//    ui->checkExtY07->setText(xStringResource::GetVarName(EM1_VAR_Y07));
//    ui->checkExtY08->setText(xStringResource::GetVarName(EM1_VAR_Y08));
//    ui->checkExtY09->setText(xStringResource::GetVarName(EM1_VAR_Y09));
//    ui->checkExtY10->setText(xStringResource::GetVarName(EM1_VAR_Y10));
//    ui->checkExtY11->setText(xStringResource::GetVarName(EM1_VAR_Y11));
//    ui->checkExtY12->setText(xStringResource::GetVarName(EM1_VAR_Y12));
//    ui->checkExtY13->setText(xStringResource::GetVarName(EM1_VAR_Y13));
//    ui->checkExtY14->setText(xStringResource::GetVarName(EM1_VAR_Y14));
//    ui->checkExtY15->setText(xStringResource::GetVarName(EM1_VAR_Y15));//pyq注释
    if((CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)||(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H730_5AXIS))
    {
        ui->checkExtY02->setText(xStringResource::GetVarName(MAIN_VAR_Y17));
        ui->checkExtY03->setText(xStringResource::GetVarName(MAIN_VAR_Y18));
        ui->checkExtY04->setText(xStringResource::GetVarName(MAIN_VAR_Y19));
        ui->checkExtY05->setText(xStringResource::GetVarName(MAIN_VAR_Y20));
        ui->checkExtY06->setText(xStringResource::GetVarName(MAIN_VAR_Y21));
        ui->checkExtY07->setText(xStringResource::GetVarName(MAIN_VAR_Y22));
        ui->checkExtY08->setText(xStringResource::GetVarName(MAIN_VAR_Y23));
        ui->checkExtY09->setText(xStringResource::GetVarName(MAIN_VAR_Y24));
        ui->checkExtY10->setText(xStringResource::GetVarName(MAIN_VAR_Y25));
        ui->checkExtY11->setText(xStringResource::GetVarName(MAIN_VAR_Y26));
        ui->checkExtY12->setText(xStringResource::GetVarName(MAIN_VAR_Y27));
        ui->checkExtY13->setText(xStringResource::GetVarName(MAIN_VAR_Y28));
        ui->checkExtY14->setVisible(false);
        ui->checkExtY15->setVisible(false);
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        ui->checkExtY02->setText(xStringResource::GetVarName(MAIN_VAR_Y16));
        ui->checkExtY03->setText(xStringResource::GetVarName(MAIN_VAR_Y17));
        ui->checkExtY04->setText(xStringResource::GetVarName(MAIN_VAR_Y18));
        ui->checkExtY05->setText(xStringResource::GetVarName(MAIN_VAR_Y19));
        ui->checkExtY06->setText(xStringResource::GetVarName(MAIN_VAR_Y20));
        ui->checkExtY07->setText(xStringResource::GetVarName(MAIN_VAR_Y22));
        ui->checkExtY08->setText(xStringResource::GetVarName(MAIN_VAR_Y23));
        ui->checkExtY09->setText(xStringResource::GetVarName(EM4_VAR_Y04));
        ui->checkExtY10->setText(xStringResource::GetVarName(EM4_VAR_Y05));
        ui->checkExtY11->setVisible(false);
        ui->checkExtY12->setVisible(false);
        ui->checkExtY13->setVisible(false);
        ui->checkExtY14->setVisible(false);
        ui->checkExtY15->setVisible(false);
    }
    else
    {
        ui->checkExtY02->setText(xStringResource::GetVarName(EM1_VAR_Y02));
        ui->checkExtY03->setText(xStringResource::GetVarName(EM1_VAR_Y03));
        ui->checkExtY04->setText(xStringResource::GetVarName(EM1_VAR_Y04));
        ui->checkExtY05->setText(xStringResource::GetVarName(EM1_VAR_Y05));
        ui->checkExtY06->setText(xStringResource::GetVarName(EM1_VAR_Y06));
        ui->checkExtY07->setText(xStringResource::GetVarName(EM1_VAR_Y07));
        ui->checkExtY08->setText(xStringResource::GetVarName(EM1_VAR_Y08));
        ui->checkExtY09->setText(xStringResource::GetVarName(EM1_VAR_Y09));
        ui->checkExtY10->setText(xStringResource::GetVarName(EM1_VAR_Y10));
        ui->checkExtY11->setText(xStringResource::GetVarName(EM1_VAR_Y11));
        ui->checkExtY12->setText(xStringResource::GetVarName(EM1_VAR_Y12));
        ui->checkExtY13->setText(xStringResource::GetVarName(EM1_VAR_Y13));
        ui->checkExtY14->setText(xStringResource::GetVarName(EM1_VAR_Y14));
        ui->checkExtY15->setText(xStringResource::GetVarName(EM1_VAR_Y15));
    }

    /*************************pyq end****************************************************************************/
}

void FormActMExtOut::SetType(int type)
{
    if (type == 1)
        ui->radioButton_on->setChecked(true);
    else if(type == 0)
        ui->radioButton_off->setChecked(true);
    else
        ui->radioButton_Pulse->setChecked(true);
}

int FormActMExtOut::GetType()
{
    if (ui->radioButton_on->isChecked())
        return 1;
    else if(ui->radioButton_Pulse->isChecked())
        return 2;
    else
        return 0;
}

void FormActMExtOut::SetDelay(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormActMExtOut::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}


void FormActMExtOut::SetOutBmp(int bmp)
{
     outbmp = bmp;
    /*************************pyq*不同主板时多扩展输出显示不同***************************************************************************/
//    ui->checkExtY02->setChecked((outbmp>>2)&1);
//    ui->checkExtY03->setChecked((outbmp>>3)&1);
//    ui->checkExtY04->setChecked((outbmp>>4)&1);
//    ui->checkExtY05->setChecked((outbmp>>5)&1);
//    ui->checkExtY06->setChecked((outbmp>>6)&1);
//    ui->checkExtY07->setChecked((outbmp>>7)&1);
//    ui->checkExtY08->setChecked((outbmp>>8)&1);
//    ui->checkExtY09->setChecked((outbmp>>9)&1);
//    ui->checkExtY10->setChecked((outbmp>>10)&1);
//    ui->checkExtY11->setChecked((outbmp>>11)&1);
//    ui->checkExtY12->setChecked((outbmp>>12)&1);
//    ui->checkExtY13->setChecked((outbmp>>13)&1);
//    ui->checkExtY14->setChecked((outbmp>>14)&1);
//    ui->checkExtY15->setChecked((outbmp>>15)&1);//pyq注释
     if((CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)||(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H730_5AXIS))
    {
        ui->checkExtY02->setChecked((outbmp>>0)&1);
        ui->checkExtY03->setChecked((outbmp>>1)&1);
        ui->checkExtY04->setChecked((outbmp>>2)&1);
        ui->checkExtY05->setChecked((outbmp>>3)&1);
        ui->checkExtY06->setChecked((outbmp>>4)&1);
        ui->checkExtY07->setChecked((outbmp>>5)&1);
        ui->checkExtY08->setChecked((outbmp>>6)&1);
        ui->checkExtY09->setChecked((outbmp>>7)&1);
        ui->checkExtY10->setChecked((outbmp>>8)&1);
        ui->checkExtY11->setChecked((outbmp>>9)&1);
        ui->checkExtY12->setChecked((outbmp>>10)&1);
        ui->checkExtY13->setChecked((outbmp>>11)&1);
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        ui->checkExtY02->setChecked((outbmp>>0)&1);
        ui->checkExtY03->setChecked((outbmp>>1)&1);
        ui->checkExtY04->setChecked((outbmp>>2)&1);
        ui->checkExtY05->setChecked((outbmp>>3)&1);
        ui->checkExtY06->setChecked((outbmp>>4)&1);
        ui->checkExtY07->setChecked((outbmp>>5)&1);
        ui->checkExtY08->setChecked((outbmp>>6)&1);
        ui->checkExtY09->setChecked((outbmp>>7)&1);
        ui->checkExtY10->setChecked((outbmp>>8)&1);
    }
    else
    {
        ui->checkExtY02->setChecked((outbmp>>2)&1);
        ui->checkExtY03->setChecked((outbmp>>3)&1);
        ui->checkExtY04->setChecked((outbmp>>4)&1);
        ui->checkExtY05->setChecked((outbmp>>5)&1);
        ui->checkExtY06->setChecked((outbmp>>6)&1);
        ui->checkExtY07->setChecked((outbmp>>7)&1);
        ui->checkExtY08->setChecked((outbmp>>8)&1);
        ui->checkExtY09->setChecked((outbmp>>9)&1);
        ui->checkExtY10->setChecked((outbmp>>10)&1);
        ui->checkExtY11->setChecked((outbmp>>11)&1);
        ui->checkExtY12->setChecked((outbmp>>12)&1);
        ui->checkExtY13->setChecked((outbmp>>13)&1);
        ui->checkExtY14->setChecked((outbmp>>14)&1);
        ui->checkExtY15->setChecked((outbmp>>15)&1);
    }

    /*************************pyq end****************************************************************************/
}

int FormActMExtOut::GetOutBmp()
{
    /*************************pyq*不同主板时多扩展输出显示不同***************************************************************************/
//    outbmp  = ((quint16)(ui->checkExtY02->isChecked()?1:0)) << 2;
//    outbmp |= ((quint16)(ui->checkExtY03->isChecked()?1:0)) << 3;
//    outbmp |= ((quint16)(ui->checkExtY04->isChecked()?1:0)) << 4;
//    outbmp |= ((quint16)(ui->checkExtY05->isChecked()?1:0)) << 5;
//    outbmp |= ((quint16)(ui->checkExtY06->isChecked()?1:0)) << 6;
//    outbmp |= ((quint16)(ui->checkExtY07->isChecked()?1:0)) << 7;
//    outbmp |= ((quint16)(ui->checkExtY08->isChecked()?1:0)) << 8;
//    outbmp |= ((quint16)(ui->checkExtY09->isChecked()?1:0)) << 9;
//    outbmp |= ((quint16)(ui->checkExtY10->isChecked()?1:0)) << 10;
//    outbmp |= ((quint16)(ui->checkExtY11->isChecked()?1:0)) << 11;
//    outbmp |= ((quint16)(ui->checkExtY12->isChecked()?1:0)) << 12;
//    outbmp |= ((quint16)(ui->checkExtY13->isChecked()?1:0)) << 13;
//    outbmp |= ((quint16)(ui->checkExtY14->isChecked()?1:0)) << 14;
//    outbmp |= ((quint16)(ui->checkExtY15->isChecked()?1:0)) << 15;//pyq注释

    if((CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)||(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H730_5AXIS))
    {
        outbmp  = ((quint32)(ui->checkExtY02->isChecked()?1:0)) << 0;
        outbmp |= ((quint32)(ui->checkExtY03->isChecked()?1:0)) << 1;
        outbmp |= ((quint32)(ui->checkExtY04->isChecked()?1:0)) << 2;
        outbmp |= ((quint32)(ui->checkExtY05->isChecked()?1:0)) << 3;
        outbmp |= ((quint32)(ui->checkExtY06->isChecked()?1:0)) << 4;
        outbmp |= ((quint32)(ui->checkExtY07->isChecked()?1:0)) << 5;
        outbmp |= ((quint32)(ui->checkExtY08->isChecked()?1:0)) << 6;
        outbmp |= ((quint32)(ui->checkExtY09->isChecked()?1:0)) << 7;
        outbmp |= ((quint32)(ui->checkExtY10->isChecked()?1:0)) << 8;
        outbmp |= ((quint32)(ui->checkExtY11->isChecked()?1:0)) << 9;
        outbmp |= ((quint32)(ui->checkExtY12->isChecked()?1:0)) << 10;
        outbmp |= ((quint32)(ui->checkExtY13->isChecked()?1:0)) << 11;
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        outbmp  = ((quint32)(ui->checkExtY02->isChecked()?1:0)) << 0;
        outbmp |= ((quint32)(ui->checkExtY03->isChecked()?1:0)) << 1;
        outbmp |= ((quint32)(ui->checkExtY04->isChecked()?1:0)) << 2;
        outbmp |= ((quint32)(ui->checkExtY05->isChecked()?1:0)) << 3;
        outbmp |= ((quint32)(ui->checkExtY06->isChecked()?1:0)) << 4;
        outbmp |= ((quint32)(ui->checkExtY07->isChecked()?1:0)) << 5;
        outbmp |= ((quint32)(ui->checkExtY08->isChecked()?1:0)) << 6;
        outbmp |= ((quint32)(ui->checkExtY09->isChecked()?1:0)) << 7;
        outbmp |= ((quint32)(ui->checkExtY10->isChecked()?1:0)) << 8;
    }
    else
    {
        outbmp  = ((quint16)(ui->checkExtY02->isChecked()?1:0)) << 2;
        outbmp |= ((quint16)(ui->checkExtY03->isChecked()?1:0)) << 3;
        outbmp |= ((quint16)(ui->checkExtY04->isChecked()?1:0)) << 4;
        outbmp |= ((quint16)(ui->checkExtY05->isChecked()?1:0)) << 5;
        outbmp |= ((quint16)(ui->checkExtY06->isChecked()?1:0)) << 6;
        outbmp |= ((quint16)(ui->checkExtY07->isChecked()?1:0)) << 7;
        outbmp |= ((quint16)(ui->checkExtY08->isChecked()?1:0)) << 8;
        outbmp |= ((quint16)(ui->checkExtY09->isChecked()?1:0)) << 9;
        outbmp |= ((quint16)(ui->checkExtY10->isChecked()?1:0)) << 10;
        outbmp |= ((quint16)(ui->checkExtY11->isChecked()?1:0)) << 11;
        outbmp |= ((quint16)(ui->checkExtY12->isChecked()?1:0)) << 12;
        outbmp |= ((quint16)(ui->checkExtY13->isChecked()?1:0)) << 13;
        outbmp |= ((quint16)(ui->checkExtY14->isChecked()?1:0)) << 14;
        outbmp |= ((quint16)(ui->checkExtY15->isChecked()?1:0)) << 15;
    }
    return outbmp;
    /*************************pyq end****************************************************************************/

}

void FormActMExtOut::UpdateWidgetState()
{
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        ui->radioButton_on->setEnabled(true);
        ui->radioButton_off->setEnabled(true);
        ui->radioButton_Pulse->setEnabled(true);
    }
    else
    {
        ui->radioButton_on->setEnabled(false);
        ui->radioButton_off->setEnabled(false);
        ui->radioButton_Pulse->setEnabled(true);
    }
}

// 输入输出延时信号槽
void FormActMExtOut::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}
void FormActMExtOut::SetCounter(quint16 var)
{
    counter = var;
}

quint16 FormActMExtOut::GetCounter()
{
    return counter;
}
