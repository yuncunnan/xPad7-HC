#include "formwallpaper.h"
#include "ui_formwallpaper.h"
#include "xioport.h"
#include "xmessagebox.h"

FormWallpaper::FormWallpaper(CMBProtocol *modbus, QWidget *parent) :	QWidget(parent), ui(new Ui::FormWallpaper)
{
	setWindowFlags(Qt::FramelessWindowHint);
	ui->setupUi(this);
	pModbus = modbus;
}

FormWallpaper::~FormWallpaper()
{
	delete ui;
}

bool FormWallpaper::EnterForm(void)
{
	// Set the frame background image
	ui->frameWallpaper->setStyleSheet(QString::null);
	ui->frameWallpaper->setStyleSheet("QFrame#frameWallpaper { border-image: url(\"img/Wallpaper.png\"); }");
    ui->stackedWidget->setVisible(false);
//	show();
#if FACTORY == FA_FUSHITONG
    ui->stackedWidget->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);
    connect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(InputIO()));
    connect(pModbus, SIGNAL(signal_OutputChange()), this, SLOT(OutputIO()));
    if(pModbus->GetSysType()==ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        ui->LedX05->setVisible(false);
        ui->LedX06->setVisible(false);
        ui->LedX07->setVisible(false);

        ui->BtnY05->setText(xStringResource::GetVarName(MAIN_VAR_Y01));
        ui->BtnY06->setText(xStringResource::GetVarName(MAIN_VAR_Y02));

        ui->BtnY07->setText(xStringResource::GetVarName(MAIN_VAR_Y15));//输送带
        ui->BtnY02->setText(xStringResource::GetVarName(MAIN_VAR_Y12));//吸具1
        ui->BtnY03->setText(xStringResource::GetVarName(MAIN_VAR_Y13));//夹具1
        ui->BtnY04->setText(xStringResource::GetVarName(MAIN_VAR_Y14));//抱具1

        ui->LedX02->setText(xStringResource::GetVarName(MAIN_VAR_X12));//吸具1
        ui->LedX03->setText(xStringResource::GetVarName(MAIN_VAR_X13));//夹具1
        ui->LedX04->setText(xStringResource::GetVarName(MAIN_VAR_X14));//抱具1

        ui->BtnY02->setOn(xIoPort::GetOut(MAIN_VAR_Y12));
        ui->BtnY03->setOn(xIoPort::GetOut(MAIN_VAR_Y13));
        ui->BtnY04->setOn(xIoPort::GetOut(MAIN_VAR_Y14));
        ui->BtnY05->setOn(xIoPort::GetOut(MAIN_VAR_Y01));
        ui->BtnY06->setOn(xIoPort::GetOut(MAIN_VAR_Y02));

        ui->LedX00->setOn(xIoPort::GetIn(MAIN_VAR_X08));
        ui->LedX01->setOn(xIoPort::GetIn(MAIN_VAR_X09));
        ui->LedX02->setOn(xIoPort::GetIn(MAIN_VAR_X12));
        ui->LedX03->setOn(xIoPort::GetIn(MAIN_VAR_X13));
        ui->LedX04->setOn(xIoPort::GetIn(MAIN_VAR_X14));
    }
    else
    {
        ui->LedX00->setOn(xIoPort::GetIn(EM1_VAR_X00));
        ui->LedX01->setOn(xIoPort::GetIn(EM1_VAR_X01));
        ui->LedX02->setOn(xIoPort::GetIn(EM1_VAR_X02));
        ui->LedX03->setOn(xIoPort::GetIn(EM1_VAR_X03));
        ui->LedX04->setOn(xIoPort::GetIn(EM1_VAR_X04));
        ui->LedX05->setOn(xIoPort::GetIn(EM1_VAR_X05));
        ui->LedX06->setOn(xIoPort::GetIn(EM1_VAR_X06));
        ui->LedX07->setOn(xIoPort::GetIn(EM1_VAR_X07));


        ui->BtnY00->setOn(xIoPort::GetOut(EM1_VAR_Y00));
        ui->BtnY01->setOn(xIoPort::GetOut(EM1_VAR_Y01));
        ui->BtnY02->setOn(xIoPort::GetOut(EM1_VAR_Y02));
        ui->BtnY03->setOn(xIoPort::GetOut(EM1_VAR_Y03));
        ui->BtnY04->setOn(xIoPort::GetOut(EM1_VAR_Y04));
        ui->BtnY05->setOn(xIoPort::GetOut(EM1_VAR_Y05));
        ui->BtnY06->setOn(xIoPort::GetOut(EM1_VAR_Y06));
        ui->BtnY07->setOn(xIoPort::GetOut(EM1_VAR_Y07));

        ui->BtnY00->setText(tr("正臂水平-E1Y01"));
        ui->BtnY01->setText(tr("正臂垂直-E1Y02"));
        ui->BtnY02->setText(xStringResource::GetVarName(EM1_VAR_Y02));
        ui->BtnY03->setText(xStringResource::GetVarName(EM1_VAR_Y03));
        ui->BtnY04->setText(xStringResource::GetVarName(EM1_VAR_Y04));
        ui->BtnY05->setText(xStringResource::GetVarName(EM1_VAR_Y05));
        ui->BtnY06->setText(xStringResource::GetVarName(EM1_VAR_Y06));
        ui->BtnY07->setText(xStringResource::GetVarName(EM1_VAR_Y07));

        ui->LedX00->setText(tr("水平到位-E1X01"));
        ui->LedX01->setText(tr("垂直到位-E1X02"));
        ui->LedX02->setText(xStringResource::GetVarName(EM1_VAR_X02));
        ui->LedX03->setText(xStringResource::GetVarName(EM1_VAR_X03));
        ui->LedX04->setText(xStringResource::GetVarName(EM1_VAR_X04));
        ui->LedX05->setText(xStringResource::GetVarName(EM1_VAR_X05));
        ui->LedX06->setText(xStringResource::GetVarName(EM1_VAR_X06));
        ui->LedX07->setText(xStringResource::GetVarName(EM1_VAR_X07));
        ui->BtnY00->setVisible(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_PRO_HOR));
        ui->BtnY01->setVisible(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_PRO_HOR));
        ui->LedX00->setVisible(xIoPort::IsVisibleInSignal(RBT_VAR_IN_PRO_HOR));
        ui->LedX01->setVisible(xIoPort::IsVisibleInSignal(RBT_VAR_IN_PRO_HOR));
    }
#endif
    ui->frameWallpaper->setStyleSheet(QString::null);
    ui->frameWallpaper->setStyleSheet("QFrame#frameWallpaper { border-image: url(\"img/Wallpaper.png\"); }");

	return true;
}

bool FormWallpaper::ExitForm(void)
{
//	hide();
#if FACTORY == FA_FUSHITONG
    disconnect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(InputIO()));
    disconnect(pModbus, SIGNAL(signal_OutputChange()), this, SLOT(OutputIO()));
#endif

    return true;
}

void FormWallpaper::setPermissions()
{
}

void FormWallpaper::InputIO()
{
    if(pModbus->GetSysType()==ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        if ((xIoPort::GetIn(MAIN_VAR_X08) != ui->LedX00->on()))
            ui->LedX00->setOn(xIoPort::GetIn(MAIN_VAR_X08));
        if ((xIoPort::GetIn(MAIN_VAR_X09) != ui->LedX01->on()))
            ui->LedX01->setOn(xIoPort::GetIn(MAIN_VAR_X09));
        if ((xIoPort::GetIn(MAIN_VAR_X12) != ui->LedX02->on()))
            ui->LedX02->setOn(xIoPort::GetIn(MAIN_VAR_X12));
        if ((xIoPort::GetIn(MAIN_VAR_X13) != ui->LedX03->on()))
            ui->LedX03->setOn(xIoPort::GetIn(MAIN_VAR_X13));
        if ((xIoPort::GetIn(MAIN_VAR_X14) != ui->LedX04->on()))
            ui->LedX04->setOn(xIoPort::GetIn(MAIN_VAR_X14));
    }
    else
    {
        if ((xIoPort::GetIn(EM1_VAR_X00) != ui->LedX00->on()))
            ui->LedX00->setOn(xIoPort::GetIn(EM1_VAR_X00));
        if ((xIoPort::GetIn(EM1_VAR_X01) != ui->LedX01->on()))
            ui->LedX01->setOn(xIoPort::GetIn(EM1_VAR_X01));
        if ((xIoPort::GetIn(EM1_VAR_X02) != ui->LedX02->on()))
            ui->LedX02->setOn(xIoPort::GetIn(EM1_VAR_X02));
        if ((xIoPort::GetIn(EM1_VAR_X03) != ui->LedX03->on()))
            ui->LedX03->setOn(xIoPort::GetIn(EM1_VAR_X03));
        if ((xIoPort::GetIn(EM1_VAR_X04) != ui->LedX04->on()))
            ui->LedX04->setOn(xIoPort::GetIn(EM1_VAR_X04));
        if ((xIoPort::GetIn(EM1_VAR_X05) != ui->LedX05->on()))
            ui->LedX05->setOn(xIoPort::GetIn(EM1_VAR_X05));
        if ((xIoPort::GetIn(EM1_VAR_X06) != ui->LedX06->on()))
            ui->LedX06->setOn(xIoPort::GetIn(EM1_VAR_X06));
        if ((xIoPort::GetIn(EM1_VAR_X07) != ui->LedX07->on()))
            ui->LedX07->setOn(xIoPort::GetIn(EM1_VAR_X07));
    }
}

void FormWallpaper::userChange()
{
    if (xPermissions::GetPermissions(PER_SYS_NORMAL) == false)
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
    setPermissions();
}

void FormWallpaper::OutputIO()
{
    if(pModbus->GetSysType()==ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        if ((xIoPort::GetOut(MAIN_VAR_Y12) != ui->BtnY02->on()))
            ui->BtnY02->setOn(xIoPort::GetOut(MAIN_VAR_Y12));
        if ((xIoPort::GetOut(MAIN_VAR_Y13) != ui->BtnY03->on()))
            ui->BtnY03->setOn(xIoPort::GetOut(MAIN_VAR_Y13));
        if ((xIoPort::GetOut(MAIN_VAR_Y14) != ui->BtnY04->on()))
            ui->BtnY04->setOn(xIoPort::GetOut(MAIN_VAR_Y14));
        if ((xIoPort::GetOut(MAIN_VAR_Y15) != ui->BtnY07->on()))
            ui->BtnY07->setOn(xIoPort::GetOut(MAIN_VAR_Y15));
        if ((xIoPort::GetOut(MAIN_VAR_Y01) != ui->BtnY05->on()))
            ui->BtnY05->setOn(xIoPort::GetOut(MAIN_VAR_Y01));
        if ((xIoPort::GetOut(MAIN_VAR_Y02) != ui->BtnY06->on()))
            ui->BtnY06->setOn(xIoPort::GetOut(MAIN_VAR_Y02));

        if ((xIoPort::GetOut(MAIN_VAR_Y08) != ui->BtnY00->on()))
            ui->BtnY00->setOn(xIoPort::GetOut(MAIN_VAR_Y08));
        if ((xIoPort::GetOut(MAIN_VAR_Y09) != ui->BtnY01->on()))
            ui->BtnY01->setOn(xIoPort::GetOut(MAIN_VAR_Y09));

    }
    else
    {
        if ((xIoPort::GetOut(EM1_VAR_Y00) != ui->BtnY00->on()))
            ui->BtnY00->setOn(xIoPort::GetOut(EM1_VAR_Y00));
        if ((xIoPort::GetOut(EM1_VAR_Y01) != ui->BtnY01->on()))
            ui->BtnY01->setOn(xIoPort::GetOut(EM1_VAR_Y01));
        if ((xIoPort::GetOut(EM1_VAR_Y02) != ui->BtnY02->on()))
            ui->BtnY02->setOn(xIoPort::GetOut(EM1_VAR_Y02));
        if ((xIoPort::GetOut(EM1_VAR_Y03) != ui->BtnY03->on()))
            ui->BtnY03->setOn(xIoPort::GetOut(EM1_VAR_Y03));
        if ((xIoPort::GetOut(EM1_VAR_Y04) != ui->BtnY04->on()))
            ui->BtnY04->setOn(xIoPort::GetOut(EM1_VAR_Y04));
        if ((xIoPort::GetOut(EM1_VAR_Y05) != ui->BtnY05->on()))
            ui->BtnY05->setOn(xIoPort::GetOut(EM1_VAR_Y05));
        if ((xIoPort::GetOut(EM1_VAR_Y06) != ui->BtnY06->on()))
            ui->BtnY06->setOn(xIoPort::GetOut(EM1_VAR_Y06));
        if ((xIoPort::GetOut(EM1_VAR_Y07) != ui->BtnY07->on()))
            ui->BtnY07->setOn(xIoPort::GetOut(EM1_VAR_Y07));
    }
}

void FormWallpaper::btnclick()
{
    if(pModbus->GetSysState() != SYS_STATE_MANUAL)
        return;
    int code;
    QObject*btn = (QObject*)sender();
    if(pModbus->GetSysType()==ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        if(btn == ui->BtnY02)
        {
            code = MAIN_VAR_Y12;
        }
        else if(btn == ui->BtnY03)
        {
            code = MAIN_VAR_Y13;
        }
        else if(btn == ui->BtnY04)
        {
            code = MAIN_VAR_Y14;
        }
        else if(btn == ui->BtnY07)
        {
            code = MAIN_VAR_Y15;
        }
        else if(btn == ui->BtnY05)
        {
            code = MAIN_VAR_Y01;
        }
        else if(btn == ui->BtnY06)
        {
            code = MAIN_VAR_Y02;
        }
    }
    else
    {
        if(btn == ui->BtnY02)
        {
            code = EM1_VAR_Y00 + 2;
        }
        else if(btn == ui->BtnY03)
        {
            code = EM1_VAR_Y00 + 3;
        }
        else if(btn == ui->BtnY04)
        {
            code = EM1_VAR_Y00 + 4;
        }
        else if(btn == ui->BtnY05)
        {
            code = EM1_VAR_Y00 + 5;
        }
        else if(btn == ui->BtnY06)
        {
            code = EM1_VAR_Y00 + 6;
        }
        else if(btn == ui->BtnY07)
        {
            code = EM1_VAR_Y00 + 7;
        }
        //    else if(btn == ui->BtnY00)
        //    {
        //        code = EM1_VAR_Y00 + 1;
        //    }
        //    else if(btn == ui->BtnY01)
        //    {
        //        code = EM1_VAR_Y00 + 2;
        //    }
    }
    if (xIoPort::GetOut(code) == true)
        pModbus->ManualExt(false, code);
    else
        pModbus->ManualExt(true, code);

    if((btn == ui->BtnY00) || (btn == ui->BtnY01))
    {
        if (xIoPort::GetOut(RBT_VAR_OUT_PRO_HOR) == true)
            pModbus->ManualPro(PRO_ACT_VERTIACL);
        else
            pModbus->ManualPro(PRO_ACT_HOZIONTAL);
    }
}
