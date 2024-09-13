#include <QButtonGroup>
#include <QMessageBox>
#include "xconfig.h"
#include "cmbprotocol.h"
#include "xioport.h"
#include "indicatorled.h"
#include "safeswitch.h"
#include "xpermissions.h"
#include "xmessagebox.h"
#include "xstringresource.h"
#include "servoalias.h"
#include "formmanual.h"
#include "ui_formmanual.h"
#include <QDebug>
#include "xKeyPad.h"
#define RARM_CTRL_HOR			0
#define RARM_CTRL_VER			1

#define EXTEND_MAIN             0
#define EXTEND_BOARD_1          1
#define EXTEND_BOARD_2          2
#define EXTEND_BOARD_3          3
#define EXTEND_BOARD_4          4

FormManual::FormManual(CMBProtocol *modbus, QWidget *parent) : QWidget(parent),	ui(new Ui::FormManual)
{
	ui->setupUi(this);
    retranslateUi();
	pModbus = modbus;
	// 组织输出控制按钮
	// 手臂输出
	pProArm = new QButtonGroup;
	pProArm->addButton(ui->BtnPaVer, PRO_ACT_VERTIACL);
	pProArm->addButton(ui->BtnPaHor, PRO_ACT_HOZIONTAL);
    pRunArm = new QButtonGroup;
    pRunArm->addButton(ui->BtnRaVer, RUN_ACT_VERTIACL);
    pRunArm->addButton(ui->BtnRaHor, RUN_ACT_HORIZONTAL);
	// 注塑机输出
	pImmCtrl = new QButtonGroup;
	pImmCtrl->addButton(ui->swEmo, IMMOUT_EMO);
	pImmCtrl->addButton(ui->swEmc, IMMOUT_EMC);
	pImmCtrl->addButton(ui->swEef, IMMOUT_EEF);
	pImmCtrl->addButton(ui->swEeb, IMMOUT_EEB);
	pImmCtrl->addButton(ui->swC1p1, IMMOUT_C1P1);
	pImmCtrl->addButton(ui->swC1p2, IMMOUT_C1P2);
	pImmCtrl->addButton(ui->swC2p1, IMMOUT_C2P1);
	pImmCtrl->addButton(ui->swC2p2, IMMOUT_C2P2);
    pImmCtrl->addButton(ui->swIMM, IMMOUT_RBT_ON);
	// 扩展输出
    pOutCtrl = new QButtonGroup;
    pOutCtrl->addButton(ui->BtnY00, 0);
    pOutCtrl->addButton(ui->BtnY01, 1);
    pOutCtrl->addButton(ui->BtnY02, 2);
    pOutCtrl->addButton(ui->BtnY03, 3);
    pOutCtrl->addButton(ui->BtnY04, 4);
    pOutCtrl->addButton(ui->BtnY05, 5);
    pOutCtrl->addButton(ui->BtnY06, 6);
    pOutCtrl->addButton(ui->BtnY07, 7);
    pOutCtrl->addButton(ui->BtnY08, 8);
    pOutCtrl->addButton(ui->BtnY09, 9);
    pOutCtrl->addButton(ui->BtnY10, 10);
    pOutCtrl->addButton(ui->BtnY11, 11);
    pOutCtrl->addButton(ui->BtnY12, 12);
    pOutCtrl->addButton(ui->BtnY13, 13);
    pOutCtrl->addButton(ui->BtnY14, 14);
    pOutCtrl->addButton(ui->BtnY15, 15);
    pOutCtrl->addButton(ui->BtnY16, 16);
    pOutCtrl->addButton(ui->BtnY17, 17);
    pOutCtrl->addButton(ui->BtnY18, 18);
    pOutCtrl->addButton(ui->BtnY19, 19);
    pOutCtrl->addButton(ui->BtnY20, 20);
    pOutCtrl->addButton(ui->BtnY21, 21);
    pOutCtrl->addButton(ui->BtnY22, 22);
    pOutCtrl->addButton(ui->BtnY23, 23);
    pOutCtrl->addButton(ui->BtnY24, 24);
    pOutCtrl->addButton(ui->BtnY25, 25);
    pOutCtrl->addButton(ui->BtnY26, 26);
    pOutCtrl->addButton(ui->BtnY27, 27);
    pOutCtrl->addButton(ui->BtnY28, 28);
    pOutCtrl->addButton(ui->BtnY29, 29);
    pOutCtrl->addButton(ui->BtnY30, 30);
    pOutCtrl->addButton(ui->BtnY31, 31);
    pOutCtrl->addButton(ui->BtnY32, 32);
    pOutCtrl->addButton(ui->BtnY33, 33);
    pOutCtrl->addButton(ui->BtnY34, 34);
    pOutCtrl->addButton(ui->BtnY35, 35);
    pOutCtrl->addButton(ui->BtnY36, 36);
    pOutCtrl->addButton(ui->BtnY37, 37);
    pOutCtrl->addButton(ui->BtnY38, 38);
    pOutCtrl->addButton(ui->BtnY39, 39);
    pOutCtrl->addButton(ui->BtnY40, 40);
    pOutCtrl->addButton(ui->BtnY41, 41);
    pOutCtrl->addButton(ui->BtnY42, 42);
    pOutCtrl->addButton(ui->BtnY43, 43);
    pOutCtrl->addButton(ui->BtnY44, 44);
    pOutCtrl->addButton(ui->BtnY45, 45);
    pOutCtrl->addButton(ui->BtnY46, 46);
    pOutCtrl->addButton(ui->BtnY47, 47);

    // 扩展输出选择按钮
    pOutputSelect = new QButtonGroup;
    pOutputSelect->addButton(ui->BtnOMain, EXTEND_MAIN);
    pOutputSelect->addButton(ui->BtnOM1, EXTEND_BOARD_1);
    pOutputSelect->addButton(ui->BtnOM2, EXTEND_BOARD_2);
    pOutputSelect->addButton(ui->BtnOM3, EXTEND_BOARD_3);
    pOutputSelect->addButton(ui->BtnOM4, EXTEND_BOARD_4);
//    pInputSelect = new QButtonGroup;
//    pInputSelect->addButton(ui->BtnIMain, EXTEND_MAIN);
//    pInputSelect->addButton(ui->BtnIM1, EXTEND_BOARD_1);
//    pInputSelect->addButton(ui->BtnIM2, EXTEND_BOARD_2);
//    pInputSelect->addButton(ui->BtnIM3, EXTEND_BOARD_3);
//    pInputSelect->addButton(ui->BtnIM4, EXTEND_BOARD_4);
    if((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0) || (pModbus->GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS) || (pModbus->GetSysTypeHigh() == BOARD_VERSION_H750_DVS))
    {
        m_outidx = 0;
        m_inidx = 0;
    }
    else
    {
        m_outidx = 1;
        m_inidx = 1;
    }

#if FACTORY == FA_SINROBOT_JC
    ui->LedMmop->setVisible(false);
    ui->LedHMaf->setVisible(false);
    ui->LedMaf->setVisible(false);
    ui->LedHEmc->setVisible(false);
    ui->swEef->setVisible(false);
#endif
    // 设置控件隐藏
    ui->LedSafOut->setVisible(false);
    ui->LedSafePaUp->setVisible(false);
    ui->LedSafeRaUp->setVisible(false);
    // 连接输出控制信号槽
	connect(pProArm, SIGNAL(buttonClicked(int)), this, SLOT(ParmCtrl(int)));
    connect(pRunArm, SIGNAL(buttonClicked(int)), this, SLOT(RarmCtrl(int)));
	connect(pImmCtrl, SIGNAL(buttonClicked(int)), this, SLOT(ImmCtrl(int)));
    connect(pOutCtrl, SIGNAL(buttonClicked(int)), this, SLOT(EoCtrl(int)));
    connect(pOutputSelect, SIGNAL(buttonClicked(int)), this, SLOT(OutputSelect(int)));
    //pyq 连接的实时扭矩 实时转速的
    connect(pModbus, SIGNAL(signal_Actual_Servo(int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t)),
            this, SLOT(UpdataActualServo(int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t,int16_t)));
    //pyq end
//    connect(pInputSelect, SIGNAL(buttonClicked(int)), this, SLOT(InputSelect(int)));
}

FormManual::~FormManual()
{
	delete ui;
	delete pProArm;
    delete pRunArm;
	delete pImmCtrl;
    delete pOutCtrl;
    delete pOutputSelect;
//    delete pInputSelect;
}

void FormManual::changeEvent(QEvent *e)
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
void FormManual::retranslateUi(void)
{
    ui->groupBoxPaHor->setTitle(GetServoName(AXIS_IDX_PHOR) + tr("轴"));
    ui->groupBoxPaVer->setTitle(GetServoName(AXIS_IDX_PVER) + tr("轴"));
    ui->groupBoxTrv->setTitle(GetServoName(AXIS_IDX_TRV) + tr("轴"));
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        ui->groupBoxRaHor->setTitle(GetServoName(AXIS_IDX_RHOR) + tr("(旋转)轴"));
        ui->groupBoxRaVer->setTitle(GetServoName(AXIS_IDX_RVER) + tr("(倒角)轴"));
    }
    else
    {
        ui->groupBoxRaHor->setTitle(GetServoName(AXIS_IDX_RHOR) + tr("轴"));
        ui->groupBoxRaVer->setTitle(GetServoName(AXIS_IDX_RVER) + tr("轴"));
    }
    ui->groupBoxExt->setTitle(GetServoName(AXIS_IDX_EXT) + tr("轴"));
}

// 设置界面控件的使能属性
// 如果当前在自动状态则只能观察端口,不能进行手动操作
void FormManual::SetState(uint16_t state)
{
    ui->BtnOM1->setEnabled(CMBProtocol::GetExtBoard(0));
    ui->BtnOM2->setEnabled(CMBProtocol::GetExtBoard(1));
    ui->BtnOM3->setEnabled(CMBProtocol::GetExtBoard(2));
    ui->BtnOM4->setEnabled(CMBProtocol::GetExtBoard(3));
//    ui->BtnIM1->setEnabled(CMBProtocol::GetExtBoard(0));
//    ui->BtnIM2->setEnabled(CMBProtocol::GetExtBoard(1));
//    ui->BtnIM3->setEnabled(CMBProtocol::GetExtBoard(2));
//    ui->BtnIM4->setEnabled(CMBProtocol::GetExtBoard(3));
    ui->swIMM->setEnabled(state == SYS_STATE_MANUAL);
    if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
        ui->LedSafeIn->setVisible(false);
    else
        ui->LedSafeIn->setVisible(true);
}
// 设置端口显示状态
void FormManual::SetPortVisible(void)
{
#if PENDANT_PROTOCOL
    ui->LedSafOut->setVisible(false);
    ui->LedSafePaUp->setVisible(false);
    ui->LedSafeRaUp->setVisible(false);

    ui->LedEbp->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_EBP));
    ui->LedEfp->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_EFP));
    ui->LedC1p1->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_C1P1));
    ui->LedC1p2->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_C1P2));
    ui->LedC2p1->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_C2P1));
    ui->LedC2p2->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_C2P2));
    ui->LedImop->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_IMOP));
    ui->swEeb->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EEB));
    ui->swIMM->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_RBT));
    ui->swC1p1->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P1));
    ui->swC1p2->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P2));
    ui->swC2p1->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P1));
    ui->swC2p2->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P2));

    ui->LedEsm->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_STOP));
    ui->LedRej->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_REJECT));
    ui->LedMop->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_MOP));
    ui->LedAuto->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_AUTO));
    ui->LedMmop->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_MID));
    ui->LedMcp->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_MCP));
    ui->LedSdm->setVisible(xIoPort::IsVisibleInSignal(IMM_VAR_IN_SAFE));
	ui->LedHMaf->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_HMAF));
	ui->LedHEmc->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_HEMC));
	ui->LedMaf->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_MAF));
    ui->swEmo->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EMO));
    ui->swEmc->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EMC));
#if (FACTORY == FA_VICTOR_SPECIAL)              //2023-12-06
    ui->swEef->setVisible(false);
#else
    ui->swEef->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EEF));
#endif

    ui->LedPaHor->setVisible(xIoPort::IsVisibleInSignal(RBT_VAR_IN_PRO_HOR));
    ui->BtnPaHor->setVisible(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_PRO_HOR));
    ui->LedPaVer->setVisible(xIoPort::IsVisibleInSignal(RBT_VAR_IN_PRO_VER));
    ui->BtnPaVer->setVisible(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_PRO_VER));
    ui->LedRaHor->setVisible(CMBProtocol::GetRunRotateUse());
    ui->BtnRaHor->setVisible(CMBProtocol::GetRunRotateUse());
    ui->LedRaVer->setVisible(CMBProtocol::GetRunRotateUse());
    ui->BtnRaVer->setVisible(CMBProtocol::GetRunRotateUse());
    ui->LedRaAsc->setVisible(xIoPort::IsVisibleInSignal(RBT_VAR_IN_RUN_ASC));
    ui->LedRaDes->setVisible(xIoPort::IsVisibleInSignal(RBT_VAR_IN_RUN_DES));
    ui->LedRaAdv->setVisible(xIoPort::IsVisibleInSignal(RBT_VAR_IN_RUN_ADV));
    ui->LedRaRet->setVisible(xIoPort::IsVisibleInSignal(RBT_VAR_IN_RUN_RET));
    ui->BtnRaDes->setVisible(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_RUN_DES));
    ui->BtnRaRet->setVisible(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_RUN_RET));
    ui->BtnRaAdv->setVisible(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_RUN_ADV));

    ui->LedActLed->setVisible(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_LAMP));
    ui->LedAlmLed->setVisible(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_ALM_LAMP));
    ui->LedBeepLed->setVisible(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_ALM_BEEP));

    ui->LedPressure->setVisible(xIoPort::IsVisibleInSignal(RBT_VAR_IN_LOW_AIR));
    ui->LedDwnSafe->setVisible(xIoPort::IsVisibleInSignal(RBT_VAR_IN_DWN_SAF));

	ui->BtnCONV->setVisible(xIoPort::IsVisibleOutSignal(OUT_VAR_CONV));
	ui->BtnCUT->setVisible(xIoPort::IsVisibleOutSignal(OUT_VAR_CUT));
#endif
}
// 设置端口名称
void FormManual::setPortNames(void)
{
	// 伺服输入
	ui->LedSafOut->setText(xStringResource::GetVarName(SV_VAR_IN_OUTMOLD));
    if (pModbus->GetHomeInmold())
        ui->LedSafeIn->setText(xStringResource::GetVarName(SV_VAR_IN_OUTMOLD));
    else
        ui->LedSafeIn->setText(xStringResource::GetVarName(SV_VAR_IN_INMOLD));

	ui->LedSafePaUp->setText(xStringResource::GetVarName(SV_VAR_IN_YWPOS));
	ui->LedSafeRaUp->setText(xStringResource::GetVarName(SV_VAR_IN_AWPOS));
	// 注塑机输入
	ui->LedEsm->setText(xStringResource::GetVarName(IMM_VAR_IN_STOP));
	ui->LedSdm->setText(xStringResource::GetVarName(IMM_VAR_IN_SAFE));
	ui->LedRej->setText(xStringResource::GetVarName(IMM_VAR_IN_REJECT));
	ui->LedMcp->setText(xStringResource::GetVarName(IMM_VAR_IN_MCP));
	ui->LedMop->setText(xStringResource::GetVarName(IMM_VAR_IN_MOP));
	ui->LedImop->setText(xStringResource::GetVarName(IMM_VAR_IN_IMOP));
	ui->LedAuto->setText(xStringResource::GetVarName(IMM_VAR_IN_AUTO));
	ui->LedEbp->setText(xStringResource::GetVarName(IMM_VAR_IN_EBP));
	ui->LedEfp->setText(xStringResource::GetVarName(IMM_VAR_IN_EFP));
	ui->LedC1p1->setText(xStringResource::GetVarName(IMM_VAR_IN_C1P1));
	ui->LedC1p2->setText(xStringResource::GetVarName(IMM_VAR_IN_C1P2));
	ui->LedC2p1->setText(xStringResource::GetVarName(IMM_VAR_IN_C2P1));
	ui->LedC2p2->setText(xStringResource::GetVarName(IMM_VAR_IN_C2P2));
	ui->LedMmop->setText(xStringResource::GetVarName(IMM_VAR_IN_MID));
	// 注塑机输出
	ui->LedHMaf->setText(xStringResource::GetVarName(IMM_VAR_OUT_HMAF));
	ui->LedMaf->setText(xStringResource::GetVarName(IMM_VAR_OUT_MAF));
	ui->LedHEmc->setText(xStringResource::GetVarName(IMM_VAR_OUT_HEMC));
	ui->swEmo->setText(xStringResource::GetVarName(IMM_VAR_OUT_EMO));
#if (FACTORY == FA_VICTOR_SPECIAL)              //2023-12-06
    ui->swEmc->setText(tr("允许加工"));
#else
	ui->swEmc->setText(xStringResource::GetVarName(IMM_VAR_OUT_EMC));
#endif
	ui->swEef->setText(xStringResource::GetVarName(IMM_VAR_OUT_EEF));
	ui->swEeb->setText(xStringResource::GetVarName(IMM_VAR_OUT_EEB));
	ui->swC1p1->setText(xStringResource::GetVarName(IMM_VAR_OUT_C1P1));
	ui->swC1p2->setText(xStringResource::GetVarName(IMM_VAR_OUT_C1P2));
	ui->swC2p1->setText(xStringResource::GetVarName(IMM_VAR_OUT_C2P1));
	ui->swC2p2->setText(xStringResource::GetVarName(IMM_VAR_OUT_C2P2));
    ui->swIMM->setText(xStringResource::GetVarName(IMM_VAR_OUT_RBT));
	// 手臂输入
	ui->LedPaHor->setText(xStringResource::GetVarName(RBT_VAR_IN_PRO_HOR));
	ui->LedPaVer->setText(xStringResource::GetVarName(RBT_VAR_IN_PRO_VER));
	ui->LedRaAsc->setText(xStringResource::GetVarName(RBT_VAR_IN_RUN_ASC));
	ui->LedRaDes->setText(xStringResource::GetVarName(RBT_VAR_IN_RUN_DES));
    ui->LedRaAdv->setText(xStringResource::GetVarName(RBT_VAR_IN_RUN_ADV));
    ui->LedRaRet->setText(xStringResource::GetVarName(RBT_VAR_IN_RUN_RET));
    ui->LedRaHor->setText(xStringResource::GetVarName(RBT_VAR_IN_RUN_HOR));
    ui->LedRaVer->setText(xStringResource::GetVarName(RBT_VAR_IN_RUN_VER));
	// 手臂输出
	ui->BtnPaHor->setText(xStringResource::GetVarName(RBT_VAR_OUT_PRO_HOR));
	ui->BtnPaVer->setText(xStringResource::GetVarName(RBT_VAR_OUT_PRO_VER));
    ui->BtnRaHor->setText(xStringResource::GetVarName(RBT_VAR_OUT_RUN_HOR));
    ui->BtnRaVer->setText(xStringResource::GetVarName(RBT_VAR_OUT_RUN_VER));
	ui->BtnRaDes->setText(xStringResource::GetVarName(RBT_VAR_OUT_RUN_DES));
    ui->BtnRaAdv->setText(xStringResource::GetVarName(RBT_VAR_OUT_RUN_ADV));
    ui->BtnRaRet->setText(xStringResource::GetVarName(RBT_VAR_OUT_RUN_RET));

    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        ui->LedActLed->setText(tr("运行灯-Y21"));
        ui->LedAlmLed->setText(tr("停止灯-Y06"));
    }
    else
    {
      ui->LedActLed->setText(xStringResource::GetVarName(RBT_VAR_OUT_LAMP));
      ui->LedAlmLed->setText(xStringResource::GetVarName(RBT_VAR_OUT_ALM_LAMP));
    }

    ui->LedBeepLed->setText(xStringResource::GetVarName(RBT_VAR_OUT_ALM_BEEP));
	// 其他输入
	ui->LedPressure->setText(xStringResource::GetVarName(RBT_VAR_IN_LOW_AIR));
	ui->LedDwnSafe->setText(xStringResource::GetVarName(RBT_VAR_IN_DWN_SAF));

    ui->BtnCONV->setText(xStringResource::GetVarName(OUT_VAR_CONV));
    ui->BtnCUT->setText(xStringResource::GetVarName(OUT_VAR_CUT));
}

// 设置扩展输出端口名称
void FormManual::setOutPortNames(int idx)
{
    switch (idx)
    {
    case EXTEND_MAIN:
        ui->BtnY00->setText(xStringResource::GetVarName(MAIN_VAR_Y00));
        ui->BtnY01->setText(xStringResource::GetVarName(MAIN_VAR_Y01));
        ui->BtnY02->setText(xStringResource::GetVarName(MAIN_VAR_Y02));
        ui->BtnY03->setText(xStringResource::GetVarName(MAIN_VAR_Y03));
        ui->BtnY04->setText(xStringResource::GetVarName(MAIN_VAR_Y04));
        ui->BtnY05->setText(xStringResource::GetVarName(MAIN_VAR_Y05));
        ui->BtnY06->setText(xStringResource::GetVarName(MAIN_VAR_Y06));
        ui->BtnY07->setText(xStringResource::GetVarName(MAIN_VAR_Y07));
        ui->BtnY08->setText(xStringResource::GetVarName(MAIN_VAR_Y08));
        ui->BtnY09->setText(xStringResource::GetVarName(MAIN_VAR_Y09));
        ui->BtnY10->setText(xStringResource::GetVarName(MAIN_VAR_Y10));
        ui->BtnY11->setText(xStringResource::GetVarName(MAIN_VAR_Y11));
        ui->BtnY12->setText(xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->BtnY13->setText(xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->BtnY14->setText(xStringResource::GetVarName(MAIN_VAR_Y14));
        ui->BtnY15->setText(xStringResource::GetVarName(MAIN_VAR_Y15));

        ui->BtnY16->setText(xStringResource::GetVarName(MAIN_VAR_Y16));
        ui->BtnY17->setText(xStringResource::GetVarName(MAIN_VAR_Y17));
        ui->BtnY18->setText(xStringResource::GetVarName(MAIN_VAR_Y18));
        ui->BtnY19->setText(xStringResource::GetVarName(MAIN_VAR_Y19));
        ui->BtnY20->setText(xStringResource::GetVarName(MAIN_VAR_Y20));
        ui->BtnY21->setText(xStringResource::GetVarName(MAIN_VAR_Y21));
        ui->BtnY22->setText(xStringResource::GetVarName(MAIN_VAR_Y22));
        if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
        {
            if (pModbus->GetOilUse())
                ui->BtnY23->setText(xStringResource::GetVarName(RBT_VAR_OUT_OIL));
            else
                ui->BtnY23->setText(xStringResource::GetVarName(MAIN_VAR_Y23));
        }
        else
        {
          ui->BtnY23->setText(xStringResource::GetVarName(MAIN_VAR_Y23));
        }

        ui->BtnY24->setText(xStringResource::GetVarName(MAIN_VAR_Y24));
        ui->BtnY25->setText(xStringResource::GetVarName(MAIN_VAR_Y25));
        ui->BtnY26->setText(xStringResource::GetVarName(MAIN_VAR_Y26));
        ui->BtnY27->setText(xStringResource::GetVarName(MAIN_VAR_Y27));
        ui->BtnY28->setText(xStringResource::GetVarName(MAIN_VAR_Y28));
        ui->BtnY29->setText(xStringResource::GetVarName(MAIN_VAR_Y29));
        ui->BtnY30->setText(xStringResource::GetVarName(MAIN_VAR_Y30));
        ui->BtnY31->setText(xStringResource::GetVarName(MAIN_VAR_Y31));
        ui->BtnY32->setText(xStringResource::GetVarName(MAIN_VAR_Y32));
        ui->BtnY33->setText(xStringResource::GetVarName(MAIN_VAR_Y33));
        ui->BtnY34->setText(xStringResource::GetVarName(MAIN_VAR_Y34));
        ui->BtnY35->setText(xStringResource::GetVarName(MAIN_VAR_Y35));
        ui->BtnY36->setText(xStringResource::GetVarName(MAIN_VAR_Y36));
        ui->BtnY37->setText(xStringResource::GetVarName(MAIN_VAR_Y37));
        ui->BtnY38->setText(xStringResource::GetVarName(MAIN_VAR_Y38));
        ui->BtnY39->setText(xStringResource::GetVarName(MAIN_VAR_Y39));
        ui->BtnY40->setText(xStringResource::GetVarName(MAIN_VAR_Y40));
        ui->BtnY41->setText(xStringResource::GetVarName(MAIN_VAR_Y41));
        ui->BtnY42->setText(xStringResource::GetVarName(MAIN_VAR_Y42));
        ui->BtnY43->setText(xStringResource::GetVarName(MAIN_VAR_Y43));
        ui->BtnY44->setText(xStringResource::GetVarName(MAIN_VAR_Y44));
        ui->BtnY45->setText(xStringResource::GetVarName(MAIN_VAR_Y45));
        ui->BtnY46->setText(xStringResource::GetVarName(MAIN_VAR_Y46));
        ui->BtnY47->setText(xStringResource::GetVarName(MAIN_VAR_Y47));
        break;
    case EXTEND_BOARD_1:
        ui->BtnY00->setText(xStringResource::GetVarName(EM1_VAR_Y00));
        ui->BtnY01->setText(xStringResource::GetVarName(EM1_VAR_Y01));
        ui->BtnY02->setText(xStringResource::GetVarName(EM1_VAR_Y02));
        ui->BtnY03->setText(xStringResource::GetVarName(EM1_VAR_Y03));
        ui->BtnY04->setText(xStringResource::GetVarName(EM1_VAR_Y04));
        ui->BtnY05->setText(xStringResource::GetVarName(EM1_VAR_Y05));
        ui->BtnY06->setText(xStringResource::GetVarName(EM1_VAR_Y06));
        ui->BtnY07->setText(xStringResource::GetVarName(EM1_VAR_Y07));
        ui->BtnY08->setText(xStringResource::GetVarName(EM1_VAR_Y08));
        ui->BtnY09->setText(xStringResource::GetVarName(EM1_VAR_Y09));
        ui->BtnY10->setText(xStringResource::GetVarName(EM1_VAR_Y10));
        if (pModbus->GetOilUse())
            ui->BtnY11->setText(tr("打油-Y12"));
        else
            ui->BtnY11->setText(xStringResource::GetVarName(EM1_VAR_Y11));
        ui->BtnY12->setText(xStringResource::GetVarName(EM1_VAR_Y12));
        ui->BtnY13->setText(xStringResource::GetVarName(EM1_VAR_Y13));
        ui->BtnY14->setText(xStringResource::GetVarName(EM1_VAR_Y14));
        ui->BtnY15->setText(xStringResource::GetVarName(EM1_VAR_Y15));
        break;
    case EXTEND_BOARD_2:
        ui->BtnY00->setText(xStringResource::GetVarName(EM2_VAR_Y00));
        ui->BtnY01->setText(xStringResource::GetVarName(EM2_VAR_Y01));
        ui->BtnY02->setText(xStringResource::GetVarName(EM2_VAR_Y02));
        ui->BtnY03->setText(xStringResource::GetVarName(EM2_VAR_Y03));
        ui->BtnY04->setText(xStringResource::GetVarName(EM2_VAR_Y04));
        ui->BtnY05->setText(xStringResource::GetVarName(EM2_VAR_Y05));
        ui->BtnY06->setText(xStringResource::GetVarName(EM2_VAR_Y06));
        ui->BtnY07->setText(xStringResource::GetVarName(EM2_VAR_Y07));
        ui->BtnY08->setText(xStringResource::GetVarName(EM2_VAR_Y08));
        ui->BtnY09->setText(xStringResource::GetVarName(EM2_VAR_Y09));
        ui->BtnY10->setText(xStringResource::GetVarName(EM2_VAR_Y10));
        ui->BtnY11->setText(xStringResource::GetVarName(EM2_VAR_Y11));
        ui->BtnY12->setText(xStringResource::GetVarName(EM2_VAR_Y12));
        ui->BtnY13->setText(xStringResource::GetVarName(EM2_VAR_Y13));
        ui->BtnY14->setText(xStringResource::GetVarName(EM2_VAR_Y14));
        ui->BtnY15->setText(xStringResource::GetVarName(EM2_VAR_Y15));
        break;
    case EXTEND_BOARD_3:
        ui->BtnY00->setText(xStringResource::GetVarName(EM3_VAR_Y00));
        ui->BtnY01->setText(xStringResource::GetVarName(EM3_VAR_Y01));
        ui->BtnY02->setText(xStringResource::GetVarName(EM3_VAR_Y02));
        ui->BtnY03->setText(xStringResource::GetVarName(EM3_VAR_Y03));
        ui->BtnY04->setText(xStringResource::GetVarName(EM3_VAR_Y04));
        ui->BtnY05->setText(xStringResource::GetVarName(EM3_VAR_Y05));
        ui->BtnY06->setText(xStringResource::GetVarName(EM3_VAR_Y06));
        ui->BtnY07->setText(xStringResource::GetVarName(EM3_VAR_Y07));
        ui->BtnY08->setText(xStringResource::GetVarName(EM3_VAR_Y08));
        ui->BtnY09->setText(xStringResource::GetVarName(EM3_VAR_Y09));
        ui->BtnY10->setText(xStringResource::GetVarName(EM3_VAR_Y10));
        ui->BtnY11->setText(xStringResource::GetVarName(EM3_VAR_Y11));
        ui->BtnY12->setText(xStringResource::GetVarName(EM3_VAR_Y12));
        ui->BtnY13->setText(xStringResource::GetVarName(EM3_VAR_Y13));
        ui->BtnY14->setText(xStringResource::GetVarName(EM3_VAR_Y14));
        ui->BtnY15->setText(xStringResource::GetVarName(EM3_VAR_Y15));
        break;
    case EXTEND_BOARD_4:
        ui->BtnY00->setText(xStringResource::GetVarName(EM4_VAR_Y00));
        ui->BtnY01->setText(xStringResource::GetVarName(EM4_VAR_Y01));
        ui->BtnY02->setText(xStringResource::GetVarName(EM4_VAR_Y02));
        ui->BtnY03->setText(xStringResource::GetVarName(EM4_VAR_Y03));
        ui->BtnY04->setText(xStringResource::GetVarName(EM4_VAR_Y04));
        ui->BtnY05->setText(xStringResource::GetVarName(EM4_VAR_Y05));
        ui->BtnY06->setText(xStringResource::GetVarName(EM4_VAR_Y06));
        ui->BtnY07->setText(xStringResource::GetVarName(EM4_VAR_Y07));
        ui->BtnY08->setText(xStringResource::GetVarName(EM4_VAR_Y08));
        ui->BtnY09->setText(xStringResource::GetVarName(EM4_VAR_Y09));
        ui->BtnY10->setText(xStringResource::GetVarName(EM4_VAR_Y10));
        ui->BtnY11->setText(xStringResource::GetVarName(EM4_VAR_Y11));
        ui->BtnY12->setText(xStringResource::GetVarName(EM4_VAR_Y12));
        ui->BtnY13->setText(xStringResource::GetVarName(EM4_VAR_Y13));
        ui->BtnY14->setText(xStringResource::GetVarName(EM4_VAR_Y14));
        ui->BtnY15->setText(xStringResource::GetVarName(EM4_VAR_Y15));
        break;
    }
}
// 设置扩展输入端口名称
void FormManual::setInPortNames(int idx)
{
    switch (idx)
    {
    case EXTEND_MAIN:
        ui->LedX00->setText(xStringResource::GetVarName(MAIN_VAR_X00));
        ui->LedX01->setText(xStringResource::GetVarName(MAIN_VAR_X01));
        ui->LedX02->setText(xStringResource::GetVarName(MAIN_VAR_X02));
        ui->LedX03->setText(xStringResource::GetVarName(MAIN_VAR_X03));
        ui->LedX04->setText(xStringResource::GetVarName(MAIN_VAR_X04));
        ui->LedX05->setText(xStringResource::GetVarName(MAIN_VAR_X05));
        ui->LedX06->setText(xStringResource::GetVarName(MAIN_VAR_X06));
        ui->LedX07->setText(xStringResource::GetVarName(MAIN_VAR_X07));
        ui->LedX08->setText(xStringResource::GetVarName(MAIN_VAR_X08));
        if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
        {
            ui->LedX09->setText(xStringResource::GetVarName(MAIN_VAR_X09));
            ui->LedX10->setText(xStringResource::GetVarName(MAIN_VAR_X10));
            ui->LedX11->setText(xStringResource::GetVarName(MAIN_VAR_X11));
        }
        else
        {
            if (CMBProtocol::GetExtraControl())
            {
                ui->LedX09->setText(tr("外部运行-X09"));
                ui->LedX10->setText(tr("外部停止-X10"));
                ui->LedX11->setText(tr("外部原点-X11"));
            }
            else
            {
                ui->LedX09->setText(xStringResource::GetVarName(MAIN_VAR_X09));
                ui->LedX10->setText(xStringResource::GetVarName(MAIN_VAR_X10));
                ui->LedX11->setText(xStringResource::GetVarName(MAIN_VAR_X11));
            }
        }
        ui->LedX12->setText(xStringResource::GetVarName(MAIN_VAR_X12));
        ui->LedX13->setText(xStringResource::GetVarName(MAIN_VAR_X13));
        ui->LedX14->setText(xStringResource::GetVarName(MAIN_VAR_X14));
        ui->LedX15->setText(xStringResource::GetVarName(MAIN_VAR_X15));
        ui->LedX16->setText(xStringResource::GetVarName(MAIN_VAR_X16));
        ui->LedX17->setText(xStringResource::GetVarName(MAIN_VAR_X17));
        ui->LedX18->setText(xStringResource::GetVarName(MAIN_VAR_X18));
        ui->LedX19->setText(xStringResource::GetVarName(MAIN_VAR_X19));
        ui->LedX20->setText(xStringResource::GetVarName(MAIN_VAR_X20));
        ui->LedX21->setText(xStringResource::GetVarName(MAIN_VAR_X21));
        ui->LedX22->setText(xStringResource::GetVarName(MAIN_VAR_X22));
        ui->LedX23->setText(xStringResource::GetVarName(MAIN_VAR_X23));
        ui->LedX24->setText(xStringResource::GetVarName(MAIN_VAR_X24));
        ui->LedX25->setText(xStringResource::GetVarName(MAIN_VAR_X25));
        ui->LedX26->setText(xStringResource::GetVarName(MAIN_VAR_X26));
        ui->LedX27->setText(xStringResource::GetVarName(MAIN_VAR_X27));
        ui->LedX28->setText(xStringResource::GetVarName(MAIN_VAR_X28));
        ui->LedX29->setText(xStringResource::GetVarName(MAIN_VAR_X29));
        ui->LedX30->setText(xStringResource::GetVarName(MAIN_VAR_X30));
        ui->LedX31->setText(xStringResource::GetVarName(MAIN_VAR_X31));
        ui->LedX32->setText(xStringResource::GetVarName(MAIN_VAR_X32));
        ui->LedX33->setText(xStringResource::GetVarName(MAIN_VAR_X33));
        ui->LedX34->setText(xStringResource::GetVarName(MAIN_VAR_X34));
        ui->LedX35->setText(xStringResource::GetVarName(MAIN_VAR_X35));
        ui->LedX36->setText(xStringResource::GetVarName(MAIN_VAR_X36));
        ui->LedX37->setText(xStringResource::GetVarName(MAIN_VAR_X37));
        ui->LedX38->setText(xStringResource::GetVarName(MAIN_VAR_X38));
        ui->LedX39->setText(xStringResource::GetVarName(MAIN_VAR_X39));
        ui->LedX40->setText(xStringResource::GetVarName(MAIN_VAR_X40));
        ui->LedX41->setText(xStringResource::GetVarName(MAIN_VAR_X41));
        ui->LedX42->setText(xStringResource::GetVarName(MAIN_VAR_X42));
        ui->LedX43->setText(xStringResource::GetVarName(MAIN_VAR_X43));
        ui->LedX44->setText(xStringResource::GetVarName(MAIN_VAR_X44));
        ui->LedX45->setText(xStringResource::GetVarName(MAIN_VAR_X45));
        ui->LedX46->setText(xStringResource::GetVarName(MAIN_VAR_X46));
        ui->LedX47->setText(xStringResource::GetVarName(MAIN_VAR_X47));

        break;
    case EXTEND_BOARD_1:
        ui->LedX00->setText(xStringResource::GetVarName(EM1_VAR_X00));
        ui->LedX01->setText(xStringResource::GetVarName(EM1_VAR_X01));
        ui->LedX02->setText(xStringResource::GetVarName(EM1_VAR_X02));
        ui->LedX03->setText(xStringResource::GetVarName(EM1_VAR_X03));
        ui->LedX04->setText(xStringResource::GetVarName(EM1_VAR_X04));
        ui->LedX05->setText(xStringResource::GetVarName(EM1_VAR_X05));
        ui->LedX06->setText(xStringResource::GetVarName(EM1_VAR_X06));
        ui->LedX07->setText(xStringResource::GetVarName(EM1_VAR_X07));
    if (pModbus->GetOilUse())
            ui->LedX08->setText(tr("打油反馈-X09"));
        else
            ui->LedX08->setText(xStringResource::GetVarName(EM1_VAR_X08));
        ui->LedX09->setText(xStringResource::GetVarName(EM1_VAR_X09));
        ui->LedX10->setText(xStringResource::GetVarName(EM1_VAR_X10));
        ui->LedX11->setText(xStringResource::GetVarName(EM1_VAR_X11));
        ui->LedX12->setText(xStringResource::GetVarName(EM1_VAR_X12));
        ui->LedX13->setText(xStringResource::GetVarName(EM1_VAR_X13));
        ui->LedX14->setText(xStringResource::GetVarName(EM1_VAR_X14));
        ui->LedX15->setText(xStringResource::GetVarName(EM1_VAR_X15));
        break;
    case EXTEND_BOARD_2:
        ui->LedX00->setText(xStringResource::GetVarName(EM2_VAR_X00));
        ui->LedX01->setText(xStringResource::GetVarName(EM2_VAR_X01));
        ui->LedX02->setText(xStringResource::GetVarName(EM2_VAR_X02));
        ui->LedX03->setText(xStringResource::GetVarName(EM2_VAR_X03));
        ui->LedX04->setText(xStringResource::GetVarName(EM2_VAR_X04));
        ui->LedX05->setText(xStringResource::GetVarName(EM2_VAR_X05));
        ui->LedX06->setText(xStringResource::GetVarName(EM2_VAR_X06));
        ui->LedX07->setText(xStringResource::GetVarName(EM2_VAR_X07));
        ui->LedX08->setText(xStringResource::GetVarName(EM2_VAR_X08));
        ui->LedX09->setText(xStringResource::GetVarName(EM2_VAR_X09));
        ui->LedX10->setText(xStringResource::GetVarName(EM2_VAR_X10));
        ui->LedX11->setText(xStringResource::GetVarName(EM2_VAR_X11));
        ui->LedX12->setText(xStringResource::GetVarName(EM2_VAR_X12));
        ui->LedX13->setText(xStringResource::GetVarName(EM2_VAR_X13));
        ui->LedX14->setText(xStringResource::GetVarName(EM2_VAR_X14));
        ui->LedX15->setText(xStringResource::GetVarName(EM2_VAR_X15));
        break;
    case EXTEND_BOARD_3:
        ui->LedX00->setText(xStringResource::GetVarName(EM3_VAR_X00));
        ui->LedX01->setText(xStringResource::GetVarName(EM3_VAR_X01));
        ui->LedX02->setText(xStringResource::GetVarName(EM3_VAR_X02));
        ui->LedX03->setText(xStringResource::GetVarName(EM3_VAR_X03));
        ui->LedX04->setText(xStringResource::GetVarName(EM3_VAR_X04));
        ui->LedX05->setText(xStringResource::GetVarName(EM3_VAR_X05));
        ui->LedX06->setText(xStringResource::GetVarName(EM3_VAR_X06));
        ui->LedX07->setText(xStringResource::GetVarName(EM3_VAR_X07));
        ui->LedX08->setText(xStringResource::GetVarName(EM3_VAR_X08));
        ui->LedX09->setText(xStringResource::GetVarName(EM3_VAR_X09));
        ui->LedX10->setText(xStringResource::GetVarName(EM3_VAR_X10));
        ui->LedX11->setText(xStringResource::GetVarName(EM3_VAR_X11));
        ui->LedX12->setText(xStringResource::GetVarName(EM3_VAR_X12));
        ui->LedX13->setText(xStringResource::GetVarName(EM3_VAR_X13));
        ui->LedX14->setText(xStringResource::GetVarName(EM3_VAR_X14));
        ui->LedX15->setText(xStringResource::GetVarName(EM3_VAR_X15));
        break;
    case EXTEND_BOARD_4:
        ui->LedX00->setText(xStringResource::GetVarName(EM4_VAR_X00));
        ui->LedX01->setText(xStringResource::GetVarName(EM4_VAR_X01));
        ui->LedX02->setText(xStringResource::GetVarName(EM4_VAR_X02));
        ui->LedX03->setText(xStringResource::GetVarName(EM4_VAR_X03));
        ui->LedX04->setText(xStringResource::GetVarName(EM4_VAR_X04));
        ui->LedX05->setText(xStringResource::GetVarName(EM4_VAR_X05));
        ui->LedX06->setText(xStringResource::GetVarName(EM4_VAR_X06));
        ui->LedX07->setText(xStringResource::GetVarName(EM4_VAR_X07));
        ui->LedX08->setText(xStringResource::GetVarName(EM4_VAR_X08));
        ui->LedX09->setText(xStringResource::GetVarName(EM4_VAR_X09));
        ui->LedX10->setText(xStringResource::GetVarName(EM4_VAR_X10));
        ui->LedX11->setText(xStringResource::GetVarName(EM4_VAR_X11));
        ui->LedX12->setText(xStringResource::GetVarName(EM4_VAR_X12));
        ui->LedX13->setText(xStringResource::GetVarName(EM4_VAR_X13));
        ui->LedX14->setText(xStringResource::GetVarName(EM4_VAR_X14));
        ui->LedX15->setText(xStringResource::GetVarName(EM4_VAR_X15));
        break;
    }
}
// 设置扩展输出显示状态
void FormManual::SetOutPortVisible(int idx)
{
    switch (idx)
    {
    case EXTEND_MAIN:
        ui->BtnY00->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y00));
        ui->BtnY01->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y01));
        ui->BtnY02->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y02));
        ui->BtnY03->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y03));
        ui->BtnY04->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y04));
        ui->BtnY05->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y05));
        ui->BtnY06->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y06));
        ui->BtnY07->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y07));
        ui->BtnY08->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y08));
        ui->BtnY09->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y09));
        ui->BtnY10->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y10));
        ui->BtnY11->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y11));
        ui->BtnY12->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y12));
        ui->BtnY13->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y13));
        ui->BtnY14->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y14));
        ui->BtnY15->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y15));

        ui->BtnY16->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y16));
        ui->BtnY17->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y17));
        ui->BtnY18->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y18));
        ui->BtnY19->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y19));
        ui->BtnY20->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y20));
        ui->BtnY21->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y21));
        ui->BtnY22->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y22));
        ui->BtnY23->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y23));
        ui->BtnY24->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y24));
        ui->BtnY25->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y25));
        ui->BtnY26->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y26));
        ui->BtnY27->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y27));
        ui->BtnY28->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y28));
        ui->BtnY29->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y29));
        ui->BtnY30->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y30));
        ui->BtnY31->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y31));
        ui->BtnY32->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y32));
        ui->BtnY33->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y33));
        ui->BtnY34->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y34));
        ui->BtnY35->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y35));
        ui->BtnY36->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y36));
        ui->BtnY37->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y37));
        ui->BtnY38->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y38));
        ui->BtnY39->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y39));
        ui->BtnY40->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y40));
        ui->BtnY41->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y41));
        ui->BtnY42->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y42));
        ui->BtnY43->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y43));
        ui->BtnY44->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y44));
        ui->BtnY45->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y45));
        ui->BtnY46->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y46));
        ui->BtnY47->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y47));
        break;
    case EXTEND_BOARD_1:
        ui->BtnY00->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y00));
        ui->BtnY01->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y01));
        ui->BtnY02->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y02));
        ui->BtnY03->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y03));
        ui->BtnY04->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y04));
        ui->BtnY05->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y05));
        ui->BtnY06->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y06));
        ui->BtnY07->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y07));
        ui->BtnY08->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y08));
        ui->BtnY09->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y09));
        ui->BtnY10->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y10));
#if ((FACTORY == FA_BEIYA) || (FACTORY == FA_ZHENJIE) || (FACTORY == FA_KEHUI))
        if (pModbus->GetSysState() == SYS_STATE_MANUAL)
            ui->BtnY11->setEnabled(true);
        else
            ui->BtnY11->setEnabled(false);
#else
        ui->BtnY11->setEnabled(xIoPort::IsVisibleExtOut(EM1_VAR_Y11));
#endif
        ui->BtnY11->setVisible(true);
        ui->BtnY12->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y12));
        ui->BtnY13->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y13));
        ui->BtnY14->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y14));
        ui->BtnY15->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y15));
        ui->BtnY16->setVisible(false);
        ui->BtnY17->setVisible(false);
        ui->BtnY18->setVisible(false);
        ui->BtnY19->setVisible(false);
        ui->BtnY20->setVisible(false);
        ui->BtnY21->setVisible(false);
        ui->BtnY22->setVisible(false);
        ui->BtnY23->setVisible(false);
        ui->BtnY24->setVisible(false);
        ui->BtnY25->setVisible(false);
        ui->BtnY26->setVisible(false);
        ui->BtnY27->setVisible(false);
        ui->BtnY28->setVisible(false);
        ui->BtnY29->setVisible(false);
        ui->BtnY30->setVisible(false);
        ui->BtnY31->setVisible(false);
        ui->BtnY32->setVisible(false);
        ui->BtnY33->setVisible(false);
        ui->BtnY34->setVisible(false);
        ui->BtnY35->setVisible(false);
        ui->BtnY36->setVisible(false);
        ui->BtnY37->setVisible(false);
        ui->BtnY38->setVisible(false);
        ui->BtnY39->setVisible(false);
        ui->BtnY40->setVisible(false);
        ui->BtnY41->setVisible(false);
        ui->BtnY42->setVisible(false);
        ui->BtnY43->setVisible(false);
        ui->BtnY44->setVisible(false);
        ui->BtnY45->setVisible(false);
        ui->BtnY46->setVisible(false);
        ui->BtnY47->setVisible(false);
        break;
    case EXTEND_BOARD_2:
        ui->BtnY00->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y00));
        ui->BtnY01->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y01));
        ui->BtnY02->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y02));
        ui->BtnY03->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y03));
        ui->BtnY04->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y04));
        ui->BtnY05->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y05));
        ui->BtnY06->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y06));
        ui->BtnY07->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y07));
        ui->BtnY08->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y08));
        ui->BtnY09->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y09));
        ui->BtnY10->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y10));
        ui->BtnY11->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y11));
        ui->BtnY12->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y12));
        ui->BtnY13->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y13));
        ui->BtnY14->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y14));
        ui->BtnY15->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y15));
        ui->BtnY11->setEnabled(true);
        ui->BtnY16->setVisible(false);
        ui->BtnY17->setVisible(false);
        ui->BtnY18->setVisible(false);
        ui->BtnY19->setVisible(false);
        ui->BtnY20->setVisible(false);
        ui->BtnY21->setVisible(false);
        ui->BtnY22->setVisible(false);
        ui->BtnY23->setVisible(false);
        ui->BtnY24->setVisible(false);
        ui->BtnY25->setVisible(false);
        ui->BtnY26->setVisible(false);
        ui->BtnY27->setVisible(false);
        ui->BtnY28->setVisible(false);
        ui->BtnY29->setVisible(false);
        ui->BtnY30->setVisible(false);
        ui->BtnY31->setVisible(false);
        ui->BtnY32->setVisible(false);
        ui->BtnY33->setVisible(false);
        ui->BtnY34->setVisible(false);
        ui->BtnY35->setVisible(false);
        ui->BtnY36->setVisible(false);
        ui->BtnY37->setVisible(false);
        ui->BtnY38->setVisible(false);
        ui->BtnY39->setVisible(false);
        ui->BtnY40->setVisible(false);
        ui->BtnY41->setVisible(false);
        ui->BtnY42->setVisible(false);
        ui->BtnY43->setVisible(false);
        ui->BtnY44->setVisible(false);
        ui->BtnY45->setVisible(false);
        ui->BtnY46->setVisible(false);
        ui->BtnY47->setVisible(false);
        break;
    case EXTEND_BOARD_3:
        ui->BtnY00->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y00));
        ui->BtnY01->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y01));
        ui->BtnY02->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y02));
        ui->BtnY03->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y03));
        ui->BtnY04->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y04));
        ui->BtnY05->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y05));
        ui->BtnY06->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y06));
        ui->BtnY07->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y07));
        ui->BtnY08->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y08));
        ui->BtnY09->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y09));
        ui->BtnY10->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y10));
        ui->BtnY11->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y11));
        ui->BtnY12->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y12));
        ui->BtnY13->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y13));
        ui->BtnY14->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y14));
        ui->BtnY15->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y15));
        ui->BtnY11->setEnabled(true);
        ui->BtnY16->setVisible(false);
        ui->BtnY17->setVisible(false);
        ui->BtnY18->setVisible(false);
        ui->BtnY19->setVisible(false);
        ui->BtnY20->setVisible(false);
        ui->BtnY21->setVisible(false);
        ui->BtnY22->setVisible(false);
        ui->BtnY23->setVisible(false);
        ui->BtnY24->setVisible(false);
        ui->BtnY25->setVisible(false);
        ui->BtnY26->setVisible(false);
        ui->BtnY27->setVisible(false);
        ui->BtnY28->setVisible(false);
        ui->BtnY29->setVisible(false);
        ui->BtnY30->setVisible(false);
        ui->BtnY31->setVisible(false);
        ui->BtnY32->setVisible(false);
        ui->BtnY33->setVisible(false);
        ui->BtnY34->setVisible(false);
        ui->BtnY35->setVisible(false);
        ui->BtnY36->setVisible(false);
        ui->BtnY37->setVisible(false);
        ui->BtnY38->setVisible(false);
        ui->BtnY39->setVisible(false);
        ui->BtnY40->setVisible(false);
        ui->BtnY41->setVisible(false);
        ui->BtnY42->setVisible(false);
        ui->BtnY43->setVisible(false);
        ui->BtnY44->setVisible(false);
        ui->BtnY45->setVisible(false);
        ui->BtnY46->setVisible(false);
        ui->BtnY47->setVisible(false);
        break;
    case EXTEND_BOARD_4:
        ui->BtnY00->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y00));
        ui->BtnY01->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y01));
        ui->BtnY02->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y02));
        ui->BtnY03->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y03));
        ui->BtnY04->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y04));
        ui->BtnY05->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y05));
        ui->BtnY06->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y06));
        ui->BtnY07->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y07));
        ui->BtnY08->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y08));
        ui->BtnY09->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y09));
        ui->BtnY10->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y10));
        ui->BtnY11->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y11));
        ui->BtnY12->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y12));
        ui->BtnY13->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y13));
        ui->BtnY14->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y14));
        ui->BtnY15->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y15));
        ui->BtnY11->setEnabled(true);
        ui->BtnY16->setVisible(false);
        ui->BtnY17->setVisible(false);
        ui->BtnY18->setVisible(false);
        ui->BtnY19->setVisible(false);
        ui->BtnY20->setVisible(false);
        ui->BtnY21->setVisible(false);
        ui->BtnY22->setVisible(false);
        ui->BtnY23->setVisible(false);
        ui->BtnY24->setVisible(false);
        ui->BtnY25->setVisible(false);
        ui->BtnY26->setVisible(false);
        ui->BtnY27->setVisible(false);
        ui->BtnY28->setVisible(false);
        ui->BtnY29->setVisible(false);
        ui->BtnY30->setVisible(false);
        ui->BtnY31->setVisible(false);
        ui->BtnY32->setVisible(false);
        ui->BtnY33->setVisible(false);
        ui->BtnY34->setVisible(false);
        ui->BtnY35->setVisible(false);
        ui->BtnY36->setVisible(false);
        ui->BtnY37->setVisible(false);
        ui->BtnY38->setVisible(false);
        ui->BtnY39->setVisible(false);
        ui->BtnY40->setVisible(false);
        ui->BtnY41->setVisible(false);
        ui->BtnY42->setVisible(false);
        ui->BtnY43->setVisible(false);
        ui->BtnY44->setVisible(false);
        ui->BtnY45->setVisible(false);
        ui->BtnY46->setVisible(false);
        ui->BtnY47->setVisible(false);
        break;
    }
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        ui->BtnY21->setEnabled(false);
    }
    else
    {
        ui->BtnY21->setEnabled(true);
    }
}
// 设置扩展输出显示状态
void FormManual::SetInPortVisible(int idx)
{
    switch (idx)
    {
    case EXTEND_MAIN:
        ui->LedX00->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X00));
        ui->LedX01->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X01));
        ui->LedX02->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X02));
        ui->LedX03->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X03));
        ui->LedX04->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X04));
        ui->LedX05->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X05));
        ui->LedX06->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X06));
        ui->LedX07->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X07));
        ui->LedX08->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X08));
//        ui->LedX09->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X09));
//        ui->LedX10->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X10));
//        ui->LedX11->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X11));
        ui->LedX12->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X12));
        ui->LedX13->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X13));
        ui->LedX14->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X14));
        ui->LedX15->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X15));
        ui->LedX16->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X16));
        ui->LedX17->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X17));
        ui->LedX18->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X18));
        ui->LedX19->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X19));
        ui->LedX20->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X20));
        ui->LedX21->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X21));
        ui->LedX22->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X22));
        ui->LedX23->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X23));
        ui->LedX24->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X24));
        ui->LedX25->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X25));
        ui->LedX26->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X26));
        ui->LedX27->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X27));
        ui->LedX28->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X28));
        ui->LedX29->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X29));
        ui->LedX30->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X30));
        //不知道X 31,32 为啥不显示。先改回去
//		ui->LedX31->setVisible(false);
//		ui->LedX32->setVisible(false);
        ui->LedX31->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X31));
        ui->LedX32->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X32));

        ui->LedX33->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X33));
        ui->LedX34->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X34));
        ui->LedX35->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X35));
        ui->LedX36->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X36));
        ui->LedX37->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X37));
        ui->LedX38->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X38));
        ui->LedX39->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X39));
        ui->LedX40->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X40));
        ui->LedX41->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X41));
        ui->LedX42->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X42));
        ui->LedX43->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X43));
        ui->LedX44->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X44));
        ui->LedX45->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X45));
        ui->LedX46->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X46));
        ui->LedX47->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X47));
        break;
    case EXTEND_BOARD_1:
        ui->LedX00->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X00));
        ui->LedX01->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X01));
        ui->LedX02->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X02));
        ui->LedX03->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X03));
        ui->LedX04->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X04));
        ui->LedX05->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X05));
        ui->LedX06->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X06));
        ui->LedX07->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X07));
        ui->LedX08->setEnabled(xIoPort::IsVisibleExtIn(EM1_VAR_X08));
        ui->LedX09->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X09));
        ui->LedX10->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X10));
        ui->LedX11->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X11));
        ui->LedX12->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X12));
        ui->LedX13->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X13));
        ui->LedX14->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X14));
        ui->LedX15->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X15));
        ui->LedX08->setVisible(true);
        ui->LedX16->setVisible(false);
        ui->LedX17->setVisible(false);
        ui->LedX18->setVisible(false);
        ui->LedX19->setVisible(false);
        ui->LedX20->setVisible(false);
        ui->LedX21->setVisible(false);
        ui->LedX22->setVisible(false);
        ui->LedX23->setVisible(false);
        ui->LedX24->setVisible(false);
        ui->LedX25->setVisible(false);
        ui->LedX26->setVisible(false);
        ui->LedX27->setVisible(false);
        ui->LedX28->setVisible(false);
        ui->LedX29->setVisible(false);
        ui->LedX30->setVisible(false);
        ui->LedX31->setVisible(false);
        ui->LedX32->setVisible(false);
        ui->LedX33->setVisible(false);
        ui->LedX34->setVisible(false);
        ui->LedX35->setVisible(false);
        ui->LedX36->setVisible(false);
        ui->LedX37->setVisible(false);
        ui->LedX38->setVisible(false);
        ui->LedX39->setVisible(false);
        ui->LedX40->setVisible(false);
        ui->LedX41->setVisible(false);
        ui->LedX42->setVisible(false);
        ui->LedX43->setVisible(false);
        ui->LedX44->setVisible(false);
        ui->LedX45->setVisible(false);
        ui->LedX46->setVisible(false);
        ui->LedX47->setVisible(false);
        break;
    case EXTEND_BOARD_2:
        ui->LedX00->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X00));
        ui->LedX01->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X01));
        ui->LedX02->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X02));
        ui->LedX03->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X03));
        ui->LedX04->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X04));
        ui->LedX05->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X05));
        ui->LedX06->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X06));
        ui->LedX07->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X07));
        ui->LedX08->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X08));
        ui->LedX09->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X09));
        ui->LedX10->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X10));
        ui->LedX11->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X11));
        ui->LedX12->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X12));
        ui->LedX13->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X13));
        ui->LedX14->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X14));
        ui->LedX15->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X15));
        ui->LedX08->setEnabled(true);
        ui->LedX16->setVisible(false);
        ui->LedX17->setVisible(false);
        ui->LedX18->setVisible(false);
        ui->LedX19->setVisible(false);
        ui->LedX20->setVisible(false);
        ui->LedX21->setVisible(false);
        ui->LedX22->setVisible(false);
        ui->LedX23->setVisible(false);
        ui->LedX24->setVisible(false);
        ui->LedX25->setVisible(false);
        ui->LedX26->setVisible(false);
        ui->LedX27->setVisible(false);
        ui->LedX28->setVisible(false);
        ui->LedX29->setVisible(false);
        ui->LedX30->setVisible(false);
        ui->LedX31->setVisible(false);
        ui->LedX32->setVisible(false);
        ui->LedX33->setVisible(false);
        ui->LedX34->setVisible(false);
        ui->LedX35->setVisible(false);
        ui->LedX36->setVisible(false);
        ui->LedX37->setVisible(false);
        ui->LedX38->setVisible(false);
        ui->LedX39->setVisible(false);
        ui->LedX40->setVisible(false);
        ui->LedX41->setVisible(false);
        ui->LedX42->setVisible(false);
        ui->LedX43->setVisible(false);
        ui->LedX44->setVisible(false);
        ui->LedX45->setVisible(false);
        ui->LedX46->setVisible(false);
        ui->LedX47->setVisible(false);
        break;
    case EXTEND_BOARD_3:
        ui->LedX00->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X00));
        ui->LedX01->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X01));
        ui->LedX02->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X02));
        ui->LedX03->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X03));
        ui->LedX04->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X04));
        ui->LedX05->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X05));
        ui->LedX06->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X06));
        ui->LedX07->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X07));
        ui->LedX08->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X08));
        ui->LedX09->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X09));
        ui->LedX10->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X10));
        ui->LedX11->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X11));
        ui->LedX12->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X12));
        ui->LedX13->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X13));
        ui->LedX14->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X14));
        ui->LedX15->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X15));
        ui->LedX08->setEnabled(true);
        ui->LedX16->setVisible(false);
        ui->LedX17->setVisible(false);
        ui->LedX18->setVisible(false);
        ui->LedX19->setVisible(false);
        ui->LedX20->setVisible(false);
        ui->LedX21->setVisible(false);
        ui->LedX22->setVisible(false);
        ui->LedX23->setVisible(false);
        ui->LedX24->setVisible(false);
        ui->LedX25->setVisible(false);
        ui->LedX26->setVisible(false);
        ui->LedX27->setVisible(false);
        ui->LedX28->setVisible(false);
        ui->LedX29->setVisible(false);
        ui->LedX30->setVisible(false);
        ui->LedX31->setVisible(false);
        ui->LedX32->setVisible(false);
        ui->LedX33->setVisible(false);
        ui->LedX34->setVisible(false);
        ui->LedX35->setVisible(false);
        ui->LedX36->setVisible(false);
        ui->LedX37->setVisible(false);
        ui->LedX38->setVisible(false);
        ui->LedX39->setVisible(false);
        ui->LedX40->setVisible(false);
        ui->LedX41->setVisible(false);
        ui->LedX42->setVisible(false);
        ui->LedX43->setVisible(false);
        ui->LedX44->setVisible(false);
        ui->LedX45->setVisible(false);
        ui->LedX46->setVisible(false);
        ui->LedX47->setVisible(false);
        break;
    case EXTEND_BOARD_4:
        ui->LedX00->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X00));
        ui->LedX01->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X01));
        ui->LedX02->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X02));
        ui->LedX03->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X03));
        ui->LedX04->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X04));
        ui->LedX05->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X05));
        ui->LedX06->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X06));
        ui->LedX07->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X07));
        ui->LedX08->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X08));
        ui->LedX09->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X09));
        ui->LedX10->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X10));
        ui->LedX11->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X11));
        ui->LedX12->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X12));
        ui->LedX13->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X13));
        ui->LedX14->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X14));
        ui->LedX15->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X15));
        ui->LedX08->setEnabled(true);
        ui->LedX16->setVisible(false);
        ui->LedX17->setVisible(false);
        ui->LedX18->setVisible(false);
        ui->LedX19->setVisible(false);
        ui->LedX20->setVisible(false);
        ui->LedX21->setVisible(false);
        ui->LedX22->setVisible(false);
        ui->LedX23->setVisible(false);
        ui->LedX24->setVisible(false);
        ui->LedX25->setVisible(false);
        ui->LedX26->setVisible(false);
        ui->LedX27->setVisible(false);
        ui->LedX28->setVisible(false);
        ui->LedX29->setVisible(false);
        ui->LedX30->setVisible(false);
        ui->LedX31->setVisible(false);
        ui->LedX32->setVisible(false);
        ui->LedX33->setVisible(false);
        ui->LedX34->setVisible(false);
        ui->LedX35->setVisible(false);
        ui->LedX36->setVisible(false);
        ui->LedX37->setVisible(false);
        ui->LedX38->setVisible(false);
        ui->LedX39->setVisible(false);
        ui->LedX40->setVisible(false);
        ui->LedX41->setVisible(false);
        ui->LedX42->setVisible(false);
        ui->LedX43->setVisible(false);
        ui->LedX44->setVisible(false);
        ui->LedX45->setVisible(false);
        ui->LedX46->setVisible(false);
        ui->LedX47->setVisible(false);
        break;
    }
}

void FormManual::SetOutPortState(int idx, bool init)
{
    m_outidx = idx;
    switch (m_outidx)
    {
    case EXTEND_MAIN:
        if ((xIoPort::GetOut(MAIN_VAR_Y00) != ui->BtnY00->on()) || (init == true))
            ui->BtnY00->setOn(xIoPort::GetOut(MAIN_VAR_Y00));
        if ((xIoPort::GetOut(MAIN_VAR_Y01) != ui->BtnY01->on()) || (init == true))
            ui->BtnY01->setOn(xIoPort::GetOut(MAIN_VAR_Y01));
        if ((xIoPort::GetOut(MAIN_VAR_Y02) != ui->BtnY02->on()) || (init == true))
            ui->BtnY02->setOn(xIoPort::GetOut(MAIN_VAR_Y02));
        if ((xIoPort::GetOut(MAIN_VAR_Y03) != ui->BtnY03->on()) || (init == true))
            ui->BtnY03->setOn(xIoPort::GetOut(MAIN_VAR_Y03));
        if ((xIoPort::GetOut(MAIN_VAR_Y04) != ui->BtnY04->on()) || (init == true))
            ui->BtnY04->setOn(xIoPort::GetOut(MAIN_VAR_Y04));
        if ((xIoPort::GetOut(MAIN_VAR_Y05) != ui->BtnY05->on()) || (init == true))
            ui->BtnY05->setOn(xIoPort::GetOut(MAIN_VAR_Y05));
        if ((xIoPort::GetOut(MAIN_VAR_Y06) != ui->BtnY06->on()) || (init == true))
            ui->BtnY06->setOn(xIoPort::GetOut(MAIN_VAR_Y06));
        if ((xIoPort::GetOut(MAIN_VAR_Y07) != ui->BtnY07->on()) || (init == true))
            ui->BtnY07->setOn(xIoPort::GetOut(MAIN_VAR_Y07));
        if ((xIoPort::GetOut(MAIN_VAR_Y08) != ui->BtnY08->on()) || (init == true))
            ui->BtnY08->setOn(xIoPort::GetOut(MAIN_VAR_Y08));
        if ((xIoPort::GetOut(MAIN_VAR_Y09) != ui->BtnY09->on()) || (init == true))
            ui->BtnY09->setOn(xIoPort::GetOut(MAIN_VAR_Y09));
        if ((xIoPort::GetOut(MAIN_VAR_Y10) != ui->BtnY10->on()) || (init == true))
            ui->BtnY10->setOn(xIoPort::GetOut(MAIN_VAR_Y10));
        if ((xIoPort::GetOut(MAIN_VAR_Y11) != ui->BtnY11->on()) || (init == true))
            ui->BtnY11->setOn(xIoPort::GetOut(MAIN_VAR_Y11));
        if ((xIoPort::GetOut(MAIN_VAR_Y12) != ui->BtnY12->on()) || (init == true))
            ui->BtnY12->setOn(xIoPort::GetOut(MAIN_VAR_Y12));
        if ((xIoPort::GetOut(MAIN_VAR_Y13) != ui->BtnY13->on()) || (init == true))
            ui->BtnY13->setOn(xIoPort::GetOut(MAIN_VAR_Y13));
        if ((xIoPort::GetOut(MAIN_VAR_Y14) != ui->BtnY14->on()) || (init == true))
            ui->BtnY14->setOn(xIoPort::GetOut(MAIN_VAR_Y14));
        if ((xIoPort::GetOut(MAIN_VAR_Y15) != ui->BtnY15->on()) || (init == true))
            ui->BtnY15->setOn(xIoPort::GetOut(MAIN_VAR_Y15));

        if ((xIoPort::GetOut(MAIN_VAR_Y16) != ui->BtnY16->on()) || (init == true))
            ui->BtnY16->setOn(xIoPort::GetOut(MAIN_VAR_Y16));
        if ((xIoPort::GetOut(MAIN_VAR_Y17) != ui->BtnY17->on()) || (init == true))
            ui->BtnY17->setOn(xIoPort::GetOut(MAIN_VAR_Y17));
        if ((xIoPort::GetOut(MAIN_VAR_Y18) != ui->BtnY18->on()) || (init == true))
            ui->BtnY18->setOn(xIoPort::GetOut(MAIN_VAR_Y18));
        if ((xIoPort::GetOut(MAIN_VAR_Y19) != ui->BtnY19->on()) || (init == true))
            ui->BtnY19->setOn(xIoPort::GetOut(MAIN_VAR_Y19));
        if ((xIoPort::GetOut(MAIN_VAR_Y20) != ui->BtnY20->on()) || (init == true))
            ui->BtnY20->setOn(xIoPort::GetOut(MAIN_VAR_Y20));
        if ((xIoPort::GetOut(MAIN_VAR_Y21) != ui->BtnY21->on()) || (init == true))
            ui->BtnY21->setOn(xIoPort::GetOut(MAIN_VAR_Y21));
        if ((xIoPort::GetOut(MAIN_VAR_Y22) != ui->BtnY22->on()) || (init == true))
            ui->BtnY22->setOn(xIoPort::GetOut(MAIN_VAR_Y22));
        if ((xIoPort::GetOut(MAIN_VAR_Y23) != ui->BtnY23->on()) || (init == true))
            ui->BtnY23->setOn(xIoPort::GetOut(MAIN_VAR_Y23));
        if ((xIoPort::GetOut(MAIN_VAR_Y24) != ui->BtnY24->on()) || (init == true))
            ui->BtnY24->setOn(xIoPort::GetOut(MAIN_VAR_Y24));
        if ((xIoPort::GetOut(MAIN_VAR_Y25) != ui->BtnY25->on()) || (init == true))
            ui->BtnY25->setOn(xIoPort::GetOut(MAIN_VAR_Y25));
        if ((xIoPort::GetOut(MAIN_VAR_Y26) != ui->BtnY26->on()) || (init == true))
            ui->BtnY26->setOn(xIoPort::GetOut(MAIN_VAR_Y26));
        if ((xIoPort::GetOut(MAIN_VAR_Y27) != ui->BtnY27->on()) || (init == true))
            ui->BtnY27->setOn(xIoPort::GetOut(MAIN_VAR_Y27));
        if ((xIoPort::GetOut(MAIN_VAR_Y28) != ui->BtnY28->on()) || (init == true))
            ui->BtnY28->setOn(xIoPort::GetOut(MAIN_VAR_Y28));
        if ((xIoPort::GetOut(MAIN_VAR_Y29) != ui->BtnY29->on()) || (init == true))
            ui->BtnY29->setOn(xIoPort::GetOut(MAIN_VAR_Y29));
        if ((xIoPort::GetOut(MAIN_VAR_Y30) != ui->BtnY30->on()) || (init == true))
            ui->BtnY30->setOn(xIoPort::GetOut(MAIN_VAR_Y30));
        if ((xIoPort::GetOut(MAIN_VAR_Y31) != ui->BtnY31->on()) || (init == true))
            ui->BtnY31->setOn(xIoPort::GetOut(MAIN_VAR_Y31));
        if ((xIoPort::GetOut(MAIN_VAR_Y32) != ui->BtnY32->on()) || (init == true))
            ui->BtnY32->setOn(xIoPort::GetOut(MAIN_VAR_Y32));
        if ((xIoPort::GetOut(MAIN_VAR_Y33) != ui->BtnY33->on()) || (init == true))
            ui->BtnY33->setOn(xIoPort::GetOut(MAIN_VAR_Y33));
        if ((xIoPort::GetOut(MAIN_VAR_Y34) != ui->BtnY34->on()) || (init == true))
            ui->BtnY34->setOn(xIoPort::GetOut(MAIN_VAR_Y34));
        if ((xIoPort::GetOut(MAIN_VAR_Y35) != ui->BtnY35->on()) || (init == true))
            ui->BtnY35->setOn(xIoPort::GetOut(MAIN_VAR_Y35));
        if ((xIoPort::GetOut(MAIN_VAR_Y36) != ui->BtnY36->on()) || (init == true))
            ui->BtnY36->setOn(xIoPort::GetOut(MAIN_VAR_Y36));
        if ((xIoPort::GetOut(MAIN_VAR_Y37) != ui->BtnY37->on()) || (init == true))
            ui->BtnY37->setOn(xIoPort::GetOut(MAIN_VAR_Y37));
        if ((xIoPort::GetOut(MAIN_VAR_Y38) != ui->BtnY38->on()) || (init == true))
            ui->BtnY38->setOn(xIoPort::GetOut(MAIN_VAR_Y38));
        if ((xIoPort::GetOut(MAIN_VAR_Y39) != ui->BtnY39->on()) || (init == true))
            ui->BtnY39->setOn(xIoPort::GetOut(MAIN_VAR_Y39));
        if ((xIoPort::GetOut(MAIN_VAR_Y40) != ui->BtnY40->on()) || (init == true))
            ui->BtnY40->setOn(xIoPort::GetOut(MAIN_VAR_Y40));
        if ((xIoPort::GetOut(MAIN_VAR_Y41) != ui->BtnY41->on()) || (init == true))
            ui->BtnY41->setOn(xIoPort::GetOut(MAIN_VAR_Y41));
        if ((xIoPort::GetOut(MAIN_VAR_Y42) != ui->BtnY42->on()) || (init == true))
            ui->BtnY42->setOn(xIoPort::GetOut(MAIN_VAR_Y42));
        if ((xIoPort::GetOut(MAIN_VAR_Y43) != ui->BtnY43->on()) || (init == true))
            ui->BtnY43->setOn(xIoPort::GetOut(MAIN_VAR_Y43));
        if ((xIoPort::GetOut(MAIN_VAR_Y44) != ui->BtnY44->on()) || (init == true))
            ui->BtnY44->setOn(xIoPort::GetOut(MAIN_VAR_Y44));
        if ((xIoPort::GetOut(MAIN_VAR_Y45) != ui->BtnY45->on()) || (init == true))
            ui->BtnY45->setOn(xIoPort::GetOut(MAIN_VAR_Y45));
        if ((xIoPort::GetOut(MAIN_VAR_Y46) != ui->BtnY46->on()) || (init == true))
            ui->BtnY46->setOn(xIoPort::GetOut(MAIN_VAR_Y46));
        if ((xIoPort::GetOut(MAIN_VAR_Y47) != ui->BtnY47->on()) || (init == true))
            ui->BtnY47->setOn(xIoPort::GetOut(MAIN_VAR_Y47));

        break;
    case EXTEND_BOARD_1:
        if ((xIoPort::GetOut(EM1_VAR_Y00) != ui->BtnY00->on()) || (init == true))
            ui->BtnY00->setOn(xIoPort::GetOut(EM1_VAR_Y00));
        if ((xIoPort::GetOut(EM1_VAR_Y01) != ui->BtnY01->on()) || (init == true))
            ui->BtnY01->setOn(xIoPort::GetOut(EM1_VAR_Y01));
        if ((xIoPort::GetOut(EM1_VAR_Y02) != ui->BtnY02->on()) || (init == true))
            ui->BtnY02->setOn(xIoPort::GetOut(EM1_VAR_Y02));
        if ((xIoPort::GetOut(EM1_VAR_Y03) != ui->BtnY03->on()) || (init == true))
            ui->BtnY03->setOn(xIoPort::GetOut(EM1_VAR_Y03));
        if ((xIoPort::GetOut(EM1_VAR_Y04) != ui->BtnY04->on()) || (init == true))
            ui->BtnY04->setOn(xIoPort::GetOut(EM1_VAR_Y04));
        if ((xIoPort::GetOut(EM1_VAR_Y05) != ui->BtnY05->on()) || (init == true))
            ui->BtnY05->setOn(xIoPort::GetOut(EM1_VAR_Y05));
        if ((xIoPort::GetOut(EM1_VAR_Y06) != ui->BtnY06->on()) || (init == true))
            ui->BtnY06->setOn(xIoPort::GetOut(EM1_VAR_Y06));
        if ((xIoPort::GetOut(EM1_VAR_Y07) != ui->BtnY07->on()) || (init == true))
            ui->BtnY07->setOn(xIoPort::GetOut(EM1_VAR_Y07));
        if ((xIoPort::GetOut(EM1_VAR_Y08) != ui->BtnY08->on()) || (init == true))
            ui->BtnY08->setOn(xIoPort::GetOut(EM1_VAR_Y08));
//        else
        {
            if ((xIoPort::GetOut(EM1_VAR_Y09) != ui->BtnY09->on()) || (init == true))
                ui->BtnY09->setOn(xIoPort::GetOut(EM1_VAR_Y09));
            if ((xIoPort::GetOut(EM1_VAR_Y10) != ui->BtnY10->on()) || (init == true))
                ui->BtnY10->setOn(xIoPort::GetOut(EM1_VAR_Y10));
        }
        if ((xIoPort::GetOut(EM1_VAR_Y11) != ui->BtnY11->on()) || (init == true))
            ui->BtnY11->setOn(xIoPort::GetOut(EM1_VAR_Y11));
        if ((xIoPort::GetOut(EM1_VAR_Y12) != ui->BtnY12->on()) || (init == true))
            ui->BtnY12->setOn(xIoPort::GetOut(EM1_VAR_Y12));
        if ((xIoPort::GetOut(EM1_VAR_Y13) != ui->BtnY13->on()) || (init == true))
            ui->BtnY13->setOn(xIoPort::GetOut(EM1_VAR_Y13));
        if ((xIoPort::GetOut(EM1_VAR_Y14) != ui->BtnY14->on()) || (init == true))
            ui->BtnY14->setOn(xIoPort::GetOut(EM1_VAR_Y14));
        if ((xIoPort::GetOut(EM1_VAR_Y15) != ui->BtnY15->on()) || (init == true))
            ui->BtnY15->setOn(xIoPort::GetOut(EM1_VAR_Y15));
        break;
    case EXTEND_BOARD_2:
        if ((xIoPort::GetOut(EM2_VAR_Y00) != ui->BtnY00->on()) || (init == true))
            ui->BtnY00->setOn(xIoPort::GetOut(EM2_VAR_Y00));
        if ((xIoPort::GetOut(EM2_VAR_Y01) != ui->BtnY01->on()) || (init == true))
            ui->BtnY01->setOn(xIoPort::GetOut(EM2_VAR_Y01));
        if ((xIoPort::GetOut(EM2_VAR_Y02) != ui->BtnY02->on()) || (init == true))
            ui->BtnY02->setOn(xIoPort::GetOut(EM2_VAR_Y02));
        if ((xIoPort::GetOut(EM2_VAR_Y03) != ui->BtnY03->on()) || (init == true))
            ui->BtnY03->setOn(xIoPort::GetOut(EM2_VAR_Y03));
        if ((xIoPort::GetOut(EM2_VAR_Y04) != ui->BtnY04->on()) || (init == true))
            ui->BtnY04->setOn(xIoPort::GetOut(EM2_VAR_Y04));
        if ((xIoPort::GetOut(EM2_VAR_Y05) != ui->BtnY05->on()) || (init == true))
            ui->BtnY05->setOn(xIoPort::GetOut(EM2_VAR_Y05));
        if ((xIoPort::GetOut(EM2_VAR_Y06) != ui->BtnY06->on()) || (init == true))
            ui->BtnY06->setOn(xIoPort::GetOut(EM2_VAR_Y06));
        if ((xIoPort::GetOut(EM2_VAR_Y07) != ui->BtnY07->on()) || (init == true))
            ui->BtnY07->setOn(xIoPort::GetOut(EM2_VAR_Y07));
        if ((xIoPort::GetOut(EM2_VAR_Y08) != ui->BtnY08->on()) || (init == true))
            ui->BtnY08->setOn(xIoPort::GetOut(EM2_VAR_Y08));
        if ((xIoPort::GetOut(EM2_VAR_Y09) != ui->BtnY09->on()) || (init == true))
            ui->BtnY09->setOn(xIoPort::GetOut(EM2_VAR_Y09));
        if ((xIoPort::GetOut(EM2_VAR_Y10) != ui->BtnY10->on()) || (init == true))
            ui->BtnY10->setOn(xIoPort::GetOut(EM2_VAR_Y10));
        if ((xIoPort::GetOut(EM2_VAR_Y11) != ui->BtnY11->on()) || (init == true))
            ui->BtnY11->setOn(xIoPort::GetOut(EM2_VAR_Y11));
        if ((xIoPort::GetOut(EM2_VAR_Y12) != ui->BtnY12->on()) || (init == true))
            ui->BtnY12->setOn(xIoPort::GetOut(EM2_VAR_Y12));
        if ((xIoPort::GetOut(EM2_VAR_Y13) != ui->BtnY13->on()) || (init == true))
            ui->BtnY13->setOn(xIoPort::GetOut(EM2_VAR_Y13));
        if ((xIoPort::GetOut(EM2_VAR_Y14) != ui->BtnY14->on()) || (init == true))
            ui->BtnY14->setOn(xIoPort::GetOut(EM2_VAR_Y14));
        if ((xIoPort::GetOut(EM2_VAR_Y15) != ui->BtnY15->on()) || (init == true))
            ui->BtnY15->setOn(xIoPort::GetOut(EM2_VAR_Y15));

        break;
    case EXTEND_BOARD_3:
        if ((xIoPort::GetOut(EM3_VAR_Y00) != ui->BtnY00->on()) || (init == true))
            ui->BtnY00->setOn(xIoPort::GetOut(EM3_VAR_Y00));
        if ((xIoPort::GetOut(EM3_VAR_Y01) != ui->BtnY01->on()) || (init == true))
            ui->BtnY01->setOn(xIoPort::GetOut(EM3_VAR_Y01));
        if ((xIoPort::GetOut(EM3_VAR_Y02) != ui->BtnY02->on()) || (init == true))
            ui->BtnY02->setOn(xIoPort::GetOut(EM3_VAR_Y02));
        if ((xIoPort::GetOut(EM3_VAR_Y03) != ui->BtnY03->on()) || (init == true))
            ui->BtnY03->setOn(xIoPort::GetOut(EM3_VAR_Y03));
        if ((xIoPort::GetOut(EM3_VAR_Y04) != ui->BtnY04->on()) || (init == true))
            ui->BtnY04->setOn(xIoPort::GetOut(EM3_VAR_Y04));
        if ((xIoPort::GetOut(EM3_VAR_Y05) != ui->BtnY05->on()) || (init == true))
            ui->BtnY05->setOn(xIoPort::GetOut(EM3_VAR_Y05));
        if ((xIoPort::GetOut(EM3_VAR_Y06) != ui->BtnY06->on()) || (init == true))
            ui->BtnY06->setOn(xIoPort::GetOut(EM3_VAR_Y06));
        if ((xIoPort::GetOut(EM3_VAR_Y07) != ui->BtnY07->on()) || (init == true))
            ui->BtnY07->setOn(xIoPort::GetOut(EM3_VAR_Y07));
        if ((xIoPort::GetOut(EM3_VAR_Y08) != ui->BtnY08->on()) || (init == true))
            ui->BtnY08->setOn(xIoPort::GetOut(EM3_VAR_Y08));
        if ((xIoPort::GetOut(EM3_VAR_Y09) != ui->BtnY09->on()) || (init == true))
            ui->BtnY09->setOn(xIoPort::GetOut(EM3_VAR_Y09));
        if ((xIoPort::GetOut(EM3_VAR_Y10) != ui->BtnY10->on()) || (init == true))
            ui->BtnY10->setOn(xIoPort::GetOut(EM3_VAR_Y10));
        if ((xIoPort::GetOut(EM3_VAR_Y11) != ui->BtnY11->on()) || (init == true))
            ui->BtnY11->setOn(xIoPort::GetOut(EM3_VAR_Y11));
        if ((xIoPort::GetOut(EM3_VAR_Y12) != ui->BtnY12->on()) || (init == true))
            ui->BtnY12->setOn(xIoPort::GetOut(EM3_VAR_Y12));
        if ((xIoPort::GetOut(EM3_VAR_Y13) != ui->BtnY13->on()) || (init == true))
            ui->BtnY13->setOn(xIoPort::GetOut(EM3_VAR_Y13));
        if ((xIoPort::GetOut(EM3_VAR_Y14) != ui->BtnY14->on()) || (init == true))
            ui->BtnY14->setOn(xIoPort::GetOut(EM3_VAR_Y14));
        if ((xIoPort::GetOut(EM3_VAR_Y15) != ui->BtnY15->on()) || (init == true))
            ui->BtnY15->setOn(xIoPort::GetOut(EM3_VAR_Y15));

        break;
    case EXTEND_BOARD_4:
        if ((xIoPort::GetOut(EM4_VAR_Y00) != ui->BtnY00->on()) || (init == true))
            ui->BtnY00->setOn(xIoPort::GetOut(EM4_VAR_Y00));
        if ((xIoPort::GetOut(EM4_VAR_Y01) != ui->BtnY01->on()) || (init == true))
            ui->BtnY01->setOn(xIoPort::GetOut(EM4_VAR_Y01));
        if ((xIoPort::GetOut(EM4_VAR_Y02) != ui->BtnY02->on()) || (init == true))
            ui->BtnY02->setOn(xIoPort::GetOut(EM4_VAR_Y02));
        if ((xIoPort::GetOut(EM4_VAR_Y03) != ui->BtnY03->on()) || (init == true))
            ui->BtnY03->setOn(xIoPort::GetOut(EM4_VAR_Y03));
        if ((xIoPort::GetOut(EM4_VAR_Y04) != ui->BtnY04->on()) || (init == true))
            ui->BtnY04->setOn(xIoPort::GetOut(EM4_VAR_Y04));
        if ((xIoPort::GetOut(EM4_VAR_Y05) != ui->BtnY05->on()) || (init == true))
            ui->BtnY05->setOn(xIoPort::GetOut(EM4_VAR_Y05));
        if ((xIoPort::GetOut(EM4_VAR_Y06) != ui->BtnY06->on()) || (init == true))
            ui->BtnY06->setOn(xIoPort::GetOut(EM4_VAR_Y06));
        if ((xIoPort::GetOut(EM4_VAR_Y07) != ui->BtnY07->on()) || (init == true))
            ui->BtnY07->setOn(xIoPort::GetOut(EM4_VAR_Y07));
        if ((xIoPort::GetOut(EM4_VAR_Y08) != ui->BtnY08->on()) || (init == true))
            ui->BtnY08->setOn(xIoPort::GetOut(EM4_VAR_Y08));
        if ((xIoPort::GetOut(EM4_VAR_Y09) != ui->BtnY09->on()) || (init == true))
            ui->BtnY09->setOn(xIoPort::GetOut(EM4_VAR_Y09));
        if ((xIoPort::GetOut(EM4_VAR_Y10) != ui->BtnY10->on()) || (init == true))
            ui->BtnY10->setOn(xIoPort::GetOut(EM4_VAR_Y10));
        if ((xIoPort::GetOut(EM4_VAR_Y11) != ui->BtnY11->on()) || (init == true))
            ui->BtnY11->setOn(xIoPort::GetOut(EM4_VAR_Y11));
        if ((xIoPort::GetOut(EM4_VAR_Y12) != ui->BtnY12->on()) || (init == true))
            ui->BtnY12->setOn(xIoPort::GetOut(EM4_VAR_Y12));
        if ((xIoPort::GetOut(EM4_VAR_Y13) != ui->BtnY13->on()) || (init == true))
            ui->BtnY13->setOn(xIoPort::GetOut(EM4_VAR_Y13));
        if ((xIoPort::GetOut(EM4_VAR_Y14) != ui->BtnY14->on()) || (init == true))
            ui->BtnY14->setOn(xIoPort::GetOut(EM4_VAR_Y14));
        if ((xIoPort::GetOut(EM4_VAR_Y15) != ui->BtnY15->on()) || (init == true))
            ui->BtnY15->setOn(xIoPort::GetOut(EM4_VAR_Y15));

        break;
    }
}

void FormManual::SetInPortState(int idx, bool init)
{
    m_inidx = idx;
    switch (m_inidx)
    {
    case EXTEND_MAIN:
        if ((xIoPort::GetIn(MAIN_VAR_X00) != ui->LedX00->on()) || (init == true))
            ui->LedX00->setOn(xIoPort::GetIn(MAIN_VAR_X00));
        if ((xIoPort::GetIn(MAIN_VAR_X01) != ui->LedX01->on()) || (init == true))
            ui->LedX01->setOn(xIoPort::GetIn(MAIN_VAR_X01));
        if ((xIoPort::GetIn(MAIN_VAR_X02) != ui->LedX02->on()) || (init == true))
            ui->LedX02->setOn(xIoPort::GetIn(MAIN_VAR_X02));
        if ((xIoPort::GetIn(MAIN_VAR_X03) != ui->LedX03->on()) || (init == true))
            ui->LedX03->setOn(xIoPort::GetIn(MAIN_VAR_X03));
        if ((xIoPort::GetIn(MAIN_VAR_X04) != ui->LedX04->on()) || (init == true))
            ui->LedX04->setOn(xIoPort::GetIn(MAIN_VAR_X04));
        if ((xIoPort::GetIn(MAIN_VAR_X05) != ui->LedX05->on()) || (init == true))
            ui->LedX05->setOn(xIoPort::GetIn(MAIN_VAR_X05));
        if ((xIoPort::GetIn(MAIN_VAR_X06) != ui->LedX06->on()) || (init == true))
            ui->LedX06->setOn(xIoPort::GetIn(MAIN_VAR_X06));
        if ((xIoPort::GetIn(MAIN_VAR_X07) != ui->LedX07->on()) || (init == true))
            ui->LedX07->setOn(xIoPort::GetIn(MAIN_VAR_X07));
        if ((xIoPort::GetIn(MAIN_VAR_X08) != ui->LedX08->on()) || (init == true))
            ui->LedX08->setOn(xIoPort::GetIn(MAIN_VAR_X08));
        if ((xIoPort::GetIn(MAIN_VAR_X09) != ui->LedX09->on()) || (init == true))
            ui->LedX09->setOn(xIoPort::GetIn(MAIN_VAR_X09));
        if ((xIoPort::GetIn(MAIN_VAR_X10) != ui->LedX10->on()) || (init == true))
            ui->LedX10->setOn(xIoPort::GetIn(MAIN_VAR_X10));
        if ((xIoPort::GetIn(MAIN_VAR_X11) != ui->LedX11->on()) || (init == true))
            ui->LedX11->setOn(xIoPort::GetIn(MAIN_VAR_X11));
        if ((xIoPort::GetIn(MAIN_VAR_X12) != ui->LedX12->on()) || (init == true))
            ui->LedX12->setOn(xIoPort::GetIn(MAIN_VAR_X12));
        if ((xIoPort::GetIn(MAIN_VAR_X13) != ui->LedX13->on()) || (init == true))
            ui->LedX13->setOn(xIoPort::GetIn(MAIN_VAR_X13));
        if ((xIoPort::GetIn(MAIN_VAR_X14) != ui->LedX14->on()) || (init == true))
            ui->LedX14->setOn(xIoPort::GetIn(MAIN_VAR_X14));
        if ((xIoPort::GetIn(MAIN_VAR_X15) != ui->LedX15->on()) || (init == true))
            ui->LedX15->setOn(xIoPort::GetIn(MAIN_VAR_X15));
        if ((xIoPort::GetIn(MAIN_VAR_X16) != ui->LedX16->on()) || (init == true))
            ui->LedX16->setOn(xIoPort::GetIn(MAIN_VAR_X16));
        if ((xIoPort::GetIn(MAIN_VAR_X17) != ui->LedX17->on()) || (init == true))
            ui->LedX17->setOn(xIoPort::GetIn(MAIN_VAR_X17));
        if ((xIoPort::GetIn(MAIN_VAR_X18) != ui->LedX18->on()) || (init == true))
            ui->LedX18->setOn(xIoPort::GetIn(MAIN_VAR_X18));
        if ((xIoPort::GetIn(MAIN_VAR_X19) != ui->LedX19->on()) || (init == true))
            ui->LedX19->setOn(xIoPort::GetIn(MAIN_VAR_X19));
        if ((xIoPort::GetIn(MAIN_VAR_X20) != ui->LedX20->on()) || (init == true))
            ui->LedX20->setOn(xIoPort::GetIn(MAIN_VAR_X20));
        if ((xIoPort::GetIn(MAIN_VAR_X21) != ui->LedX21->on()) || (init == true))
            ui->LedX21->setOn(xIoPort::GetIn(MAIN_VAR_X21));
        if ((xIoPort::GetIn(MAIN_VAR_X22) != ui->LedX22->on()) || (init == true))
            ui->LedX22->setOn(xIoPort::GetIn(MAIN_VAR_X22));
        if ((xIoPort::GetIn(MAIN_VAR_X23) != ui->LedX23->on()) || (init == true))
            ui->LedX23->setOn(xIoPort::GetIn(MAIN_VAR_X23));
        if ((xIoPort::GetIn(MAIN_VAR_X24) != ui->LedX24->on()) || (init == true))
            ui->LedX24->setOn(xIoPort::GetIn(MAIN_VAR_X24));
        if ((xIoPort::GetIn(MAIN_VAR_X25) != ui->LedX25->on()) || (init == true))
            ui->LedX25->setOn(xIoPort::GetIn(MAIN_VAR_X25));
        if ((xIoPort::GetIn(MAIN_VAR_X26) != ui->LedX26->on()) || (init == true))
            ui->LedX26->setOn(xIoPort::GetIn(MAIN_VAR_X26));
        if ((xIoPort::GetIn(MAIN_VAR_X27) != ui->LedX27->on()) || (init == true))
            ui->LedX27->setOn(xIoPort::GetIn(MAIN_VAR_X27));
        if ((xIoPort::GetIn(MAIN_VAR_X28) != ui->LedX28->on()) || (init == true))
            ui->LedX28->setOn(xIoPort::GetIn(MAIN_VAR_X28));
        if ((xIoPort::GetIn(MAIN_VAR_X29) != ui->LedX29->on()) || (init == true))
            ui->LedX29->setOn(xIoPort::GetIn(MAIN_VAR_X29));
        if ((xIoPort::GetIn(MAIN_VAR_X30) != ui->LedX30->on()) || (init == true))
            ui->LedX30->setOn(xIoPort::GetIn(MAIN_VAR_X30));
        if ((xIoPort::GetIn(MAIN_VAR_X31) != ui->LedX31->on()) || (init == true))
            ui->LedX31->setOn(xIoPort::GetIn(MAIN_VAR_X31));
        if ((xIoPort::GetIn(MAIN_VAR_X32) != ui->LedX32->on()) || (init == true))
            ui->LedX32->setOn(xIoPort::GetIn(MAIN_VAR_X32));
        if ((xIoPort::GetIn(MAIN_VAR_X33) != ui->LedX33->on()) || (init == true))
            ui->LedX33->setOn(xIoPort::GetIn(MAIN_VAR_X33));
        if ((xIoPort::GetIn(MAIN_VAR_X34) != ui->LedX34->on()) || (init == true))
            ui->LedX34->setOn(xIoPort::GetIn(MAIN_VAR_X34));
        if ((xIoPort::GetIn(MAIN_VAR_X35) != ui->LedX35->on()) || (init == true))
            ui->LedX35->setOn(xIoPort::GetIn(MAIN_VAR_X35));
        if ((xIoPort::GetIn(MAIN_VAR_X36) != ui->LedX36->on()) || (init == true))
            ui->LedX36->setOn(xIoPort::GetIn(MAIN_VAR_X36));
        if ((xIoPort::GetIn(MAIN_VAR_X37) != ui->LedX37->on()) || (init == true))
            ui->LedX37->setOn(xIoPort::GetIn(MAIN_VAR_X37));
        if ((xIoPort::GetIn(MAIN_VAR_X38) != ui->LedX38->on()) || (init == true))
            ui->LedX38->setOn(xIoPort::GetIn(MAIN_VAR_X38));
        if ((xIoPort::GetIn(MAIN_VAR_X39) != ui->LedX39->on()) || (init == true))
            ui->LedX39->setOn(xIoPort::GetIn(MAIN_VAR_X39));
        if ((xIoPort::GetIn(MAIN_VAR_X40) != ui->LedX40->on()) || (init == true))
            ui->LedX40->setOn(xIoPort::GetIn(MAIN_VAR_X40));
        if ((xIoPort::GetIn(MAIN_VAR_X41) != ui->LedX41->on()) || (init == true))
            ui->LedX41->setOn(xIoPort::GetIn(MAIN_VAR_X41));
        if ((xIoPort::GetIn(MAIN_VAR_X42) != ui->LedX42->on()) || (init == true))
            ui->LedX42->setOn(xIoPort::GetIn(MAIN_VAR_X42));
        if ((xIoPort::GetIn(MAIN_VAR_X43) != ui->LedX43->on()) || (init == true))
            ui->LedX43->setOn(xIoPort::GetIn(MAIN_VAR_X43));
        if ((xIoPort::GetIn(MAIN_VAR_X44) != ui->LedX44->on()) || (init == true))
            ui->LedX44->setOn(xIoPort::GetIn(MAIN_VAR_X44));
        if ((xIoPort::GetIn(MAIN_VAR_X45) != ui->LedX45->on()) || (init == true))
            ui->LedX45->setOn(xIoPort::GetIn(MAIN_VAR_X45));
        if ((xIoPort::GetIn(MAIN_VAR_X46) != ui->LedX46->on()) || (init == true))
            ui->LedX46->setOn(xIoPort::GetIn(MAIN_VAR_X46));
        if ((xIoPort::GetIn(MAIN_VAR_X47) != ui->LedX47->on()) || (init == true))
            ui->LedX47->setOn(xIoPort::GetIn(MAIN_VAR_X47));
        break;
    case EXTEND_BOARD_1:
        if ((xIoPort::GetIn(EM1_VAR_X00) != ui->LedX00->on()) || (init == true))
            ui->LedX00->setOn(xIoPort::GetIn(EM1_VAR_X00));
        if ((xIoPort::GetIn(EM1_VAR_X01) != ui->LedX01->on()) || (init == true))
            ui->LedX01->setOn(xIoPort::GetIn(EM1_VAR_X01));
        if ((xIoPort::GetIn(EM1_VAR_X02) != ui->LedX02->on()) || (init == true))
            ui->LedX02->setOn(xIoPort::GetIn(EM1_VAR_X02));
        if ((xIoPort::GetIn(EM1_VAR_X03) != ui->LedX03->on()) || (init == true))
            ui->LedX03->setOn(xIoPort::GetIn(EM1_VAR_X03));
        if ((xIoPort::GetIn(EM1_VAR_X04) != ui->LedX04->on()) || (init == true))
            ui->LedX04->setOn(xIoPort::GetIn(EM1_VAR_X04));
        if ((xIoPort::GetIn(EM1_VAR_X05) != ui->LedX05->on()) || (init == true))
            ui->LedX05->setOn(xIoPort::GetIn(EM1_VAR_X05));
        if ((xIoPort::GetIn(EM1_VAR_X06) != ui->LedX06->on()) || (init == true))
            ui->LedX06->setOn(xIoPort::GetIn(EM1_VAR_X06));
        if ((xIoPort::GetIn(EM1_VAR_X07) != ui->LedX07->on()) || (init == true))
            ui->LedX07->setOn(xIoPort::GetIn(EM1_VAR_X07));
        if ((xIoPort::GetIn(EM1_VAR_X08) != ui->LedX08->on()) || (init == true))
            ui->LedX08->setOn(xIoPort::GetIn(EM1_VAR_X08));
//        if (pModbus->GetRunRotateUse())
//        {
//            if ((xIoPort::GetIn(EM1_VAR_X09) != ui->LedRaHor->on()) || (init == true))
//                ui->LedRaHor->setOn(xIoPort::GetIn(EM1_VAR_X09));
//            if ((xIoPort::GetIn(EM1_VAR_X10) != ui->LedRaVer->on()) || (init == true))
//                ui->LedRaVer->setOn(xIoPort::GetIn(EM1_VAR_X10));
//        }
//        else
//        {
            if ((xIoPort::GetIn(EM1_VAR_X09) != ui->LedX09->on()) || (init == true))
                ui->LedX09->setOn(xIoPort::GetIn(EM1_VAR_X09));
            if ((xIoPort::GetIn(EM1_VAR_X10) != ui->LedX10->on()) || (init == true))
                ui->LedX10->setOn(xIoPort::GetIn(EM1_VAR_X10));
//        }
        if ((xIoPort::GetIn(EM1_VAR_X11) != ui->LedX11->on()) || (init == true))
            ui->LedX11->setOn(xIoPort::GetIn(EM1_VAR_X11));
        if ((xIoPort::GetIn(EM1_VAR_X12) != ui->LedX12->on()) || (init == true))
            ui->LedX12->setOn(xIoPort::GetIn(EM1_VAR_X12));
        if ((xIoPort::GetIn(EM1_VAR_X13) != ui->LedX13->on()) || (init == true))
            ui->LedX13->setOn(xIoPort::GetIn(EM1_VAR_X13));
        if ((xIoPort::GetIn(EM1_VAR_X14) != ui->LedX14->on()) || (init == true))
            ui->LedX14->setOn(xIoPort::GetIn(EM1_VAR_X14));
        if ((xIoPort::GetIn(EM1_VAR_X15) != ui->LedX15->on()) || (init == true))
            ui->LedX15->setOn(xIoPort::GetIn(EM1_VAR_X15));
        break;
    case EXTEND_BOARD_2:
        if ((xIoPort::GetIn(EM2_VAR_X00) != ui->LedX00->on()) || (init == true))
            ui->LedX00->setOn(xIoPort::GetIn(EM2_VAR_X00));
        if ((xIoPort::GetIn(EM2_VAR_X01) != ui->LedX01->on()) || (init == true))
            ui->LedX01->setOn(xIoPort::GetIn(EM2_VAR_X01));
        if ((xIoPort::GetIn(EM2_VAR_X02) != ui->LedX02->on()) || (init == true))
            ui->LedX02->setOn(xIoPort::GetIn(EM2_VAR_X02));
        if ((xIoPort::GetIn(EM2_VAR_X03) != ui->LedX03->on()) || (init == true))
            ui->LedX03->setOn(xIoPort::GetIn(EM2_VAR_X03));
        if ((xIoPort::GetIn(EM2_VAR_X04) != ui->LedX04->on()) || (init == true))
            ui->LedX04->setOn(xIoPort::GetIn(EM2_VAR_X04));
        if ((xIoPort::GetIn(EM2_VAR_X05) != ui->LedX05->on()) || (init == true))
            ui->LedX05->setOn(xIoPort::GetIn(EM2_VAR_X05));
        if ((xIoPort::GetIn(EM2_VAR_X06) != ui->LedX06->on()) || (init == true))
            ui->LedX06->setOn(xIoPort::GetIn(EM2_VAR_X06));
        if ((xIoPort::GetIn(EM2_VAR_X07) != ui->LedX07->on()) || (init == true))
            ui->LedX07->setOn(xIoPort::GetIn(EM2_VAR_X07));
        if ((xIoPort::GetIn(EM2_VAR_X08) != ui->LedX08->on()) || (init == true))
            ui->LedX08->setOn(xIoPort::GetIn(EM2_VAR_X08));
        if ((xIoPort::GetIn(EM2_VAR_X09) != ui->LedX09->on()) || (init == true))
            ui->LedX09->setOn(xIoPort::GetIn(EM2_VAR_X09));
        if ((xIoPort::GetIn(EM2_VAR_X10) != ui->LedX10->on()) || (init == true))
            ui->LedX10->setOn(xIoPort::GetIn(EM2_VAR_X10));
        if ((xIoPort::GetIn(EM2_VAR_X11) != ui->LedX11->on()) || (init == true))
            ui->LedX11->setOn(xIoPort::GetIn(EM2_VAR_X11));
        if ((xIoPort::GetIn(EM2_VAR_X12) != ui->LedX12->on()) || (init == true))
            ui->LedX12->setOn(xIoPort::GetIn(EM2_VAR_X12));
        if ((xIoPort::GetIn(EM2_VAR_X13) != ui->LedX13->on()) || (init == true))
            ui->LedX13->setOn(xIoPort::GetIn(EM2_VAR_X13));
        if ((xIoPort::GetIn(EM2_VAR_X14) != ui->LedX14->on()) || (init == true))
            ui->LedX14->setOn(xIoPort::GetIn(EM2_VAR_X14));
        if ((xIoPort::GetIn(EM2_VAR_X15) != ui->LedX15->on()) || (init == true))
            ui->LedX15->setOn(xIoPort::GetIn(EM2_VAR_X15));
        break;
    case EXTEND_BOARD_3:
        if ((xIoPort::GetIn(EM3_VAR_X00) != ui->LedX00->on()) || (init == true))
            ui->LedX00->setOn(xIoPort::GetIn(EM3_VAR_X00));
        if ((xIoPort::GetIn(EM3_VAR_X01) != ui->LedX01->on()) || (init == true))
            ui->LedX01->setOn(xIoPort::GetIn(EM3_VAR_X01));
        if ((xIoPort::GetIn(EM3_VAR_X02) != ui->LedX02->on()) || (init == true))
            ui->LedX02->setOn(xIoPort::GetIn(EM3_VAR_X02));
        if ((xIoPort::GetIn(EM3_VAR_X03) != ui->LedX03->on()) || (init == true))
            ui->LedX03->setOn(xIoPort::GetIn(EM3_VAR_X03));
        if ((xIoPort::GetIn(EM3_VAR_X04) != ui->LedX04->on()) || (init == true))
            ui->LedX04->setOn(xIoPort::GetIn(EM3_VAR_X04));
        if ((xIoPort::GetIn(EM3_VAR_X05) != ui->LedX05->on()) || (init == true))
            ui->LedX05->setOn(xIoPort::GetIn(EM3_VAR_X05));
        if ((xIoPort::GetIn(EM3_VAR_X06) != ui->LedX06->on()) || (init == true))
            ui->LedX06->setOn(xIoPort::GetIn(EM3_VAR_X06));
        if ((xIoPort::GetIn(EM3_VAR_X07) != ui->LedX07->on()) || (init == true))
            ui->LedX07->setOn(xIoPort::GetIn(EM3_VAR_X07));
        if ((xIoPort::GetIn(EM3_VAR_X08) != ui->LedX08->on()) || (init == true))
            ui->LedX08->setOn(xIoPort::GetIn(EM3_VAR_X08));
        if ((xIoPort::GetIn(EM3_VAR_X09) != ui->LedX09->on()) || (init == true))
            ui->LedX09->setOn(xIoPort::GetIn(EM3_VAR_X09));
        if ((xIoPort::GetIn(EM3_VAR_X10) != ui->LedX10->on()) || (init == true))
            ui->LedX10->setOn(xIoPort::GetIn(EM3_VAR_X10));
        if ((xIoPort::GetIn(EM3_VAR_X11) != ui->LedX11->on()) || (init == true))
            ui->LedX11->setOn(xIoPort::GetIn(EM3_VAR_X11));
        if ((xIoPort::GetIn(EM3_VAR_X12) != ui->LedX12->on()) || (init == true))
            ui->LedX12->setOn(xIoPort::GetIn(EM3_VAR_X12));
        if ((xIoPort::GetIn(EM3_VAR_X13) != ui->LedX13->on()) || (init == true))
            ui->LedX13->setOn(xIoPort::GetIn(EM3_VAR_X13));
        if ((xIoPort::GetIn(EM3_VAR_X14) != ui->LedX14->on()) || (init == true))
            ui->LedX14->setOn(xIoPort::GetIn(EM3_VAR_X14));
        if ((xIoPort::GetIn(EM3_VAR_X15) != ui->LedX15->on()) || (init == true))
            ui->LedX15->setOn(xIoPort::GetIn(EM3_VAR_X15));
        break;
    case EXTEND_BOARD_4:
        if ((xIoPort::GetIn(EM4_VAR_X00) != ui->LedX00->on()) || (init == true))
            ui->LedX00->setOn(xIoPort::GetIn(EM4_VAR_X00));
        if ((xIoPort::GetIn(EM4_VAR_X01) != ui->LedX01->on()) || (init == true))
            ui->LedX01->setOn(xIoPort::GetIn(EM4_VAR_X01));
        if ((xIoPort::GetIn(EM4_VAR_X02) != ui->LedX02->on()) || (init == true))
            ui->LedX02->setOn(xIoPort::GetIn(EM4_VAR_X02));
        if ((xIoPort::GetIn(EM4_VAR_X03) != ui->LedX03->on()) || (init == true))
            ui->LedX03->setOn(xIoPort::GetIn(EM4_VAR_X03));
        if ((xIoPort::GetIn(EM4_VAR_X04) != ui->LedX04->on()) || (init == true))
            ui->LedX04->setOn(xIoPort::GetIn(EM4_VAR_X04));
        if ((xIoPort::GetIn(EM4_VAR_X05) != ui->LedX05->on()) || (init == true))
            ui->LedX05->setOn(xIoPort::GetIn(EM4_VAR_X05));
        if ((xIoPort::GetIn(EM4_VAR_X06) != ui->LedX06->on()) || (init == true))
            ui->LedX06->setOn(xIoPort::GetIn(EM4_VAR_X06));
        if ((xIoPort::GetIn(EM4_VAR_X07) != ui->LedX07->on()) || (init == true))
            ui->LedX07->setOn(xIoPort::GetIn(EM4_VAR_X07));
        if ((xIoPort::GetIn(EM4_VAR_X08) != ui->LedX08->on()) || (init == true))
            ui->LedX08->setOn(xIoPort::GetIn(EM4_VAR_X08));
        if ((xIoPort::GetIn(EM4_VAR_X09) != ui->LedX09->on()) || (init == true))
            ui->LedX09->setOn(xIoPort::GetIn(EM4_VAR_X09));
        if ((xIoPort::GetIn(EM4_VAR_X10) != ui->LedX10->on()) || (init == true))
            ui->LedX10->setOn(xIoPort::GetIn(EM4_VAR_X10));
        if ((xIoPort::GetIn(EM4_VAR_X11) != ui->LedX11->on()) || (init == true))
            ui->LedX11->setOn(xIoPort::GetIn(EM4_VAR_X11));
        if ((xIoPort::GetIn(EM4_VAR_X12) != ui->LedX12->on()) || (init == true))
            ui->LedX12->setOn(xIoPort::GetIn(EM4_VAR_X12));
        if ((xIoPort::GetIn(EM4_VAR_X13) != ui->LedX13->on()) || (init == true))
            ui->LedX13->setOn(xIoPort::GetIn(EM4_VAR_X13));
        if ((xIoPort::GetIn(EM4_VAR_X14) != ui->LedX14->on()) || (init == true))
            ui->LedX14->setOn(xIoPort::GetIn(EM4_VAR_X14));
        if ((xIoPort::GetIn(EM4_VAR_X15) != ui->LedX15->on()) || (init == true))
            ui->LedX15->setOn(xIoPort::GetIn(EM4_VAR_X15));
        break;
    }
}

//初始化IO端口状态
void FormManual::InitIoState(void)
{
    SetInIO(true);
    SetOutIO(true);
    SetOutPortState(m_outidx, true);
    SetInPortState(m_outidx, true);
}
// 进入手动操作画面
bool FormManual::EnterForm(void)
{
    // 设置端口名称
	setPortNames();
    SetPortVisible();
    OutputSelect(m_outidx);
//    InputSelect(m_inidx);
	// 根据系统状态设置界面控件显示
	SetState(pModbus->GetSysState());
	// 初始化界面显示状态
	InitIoState();
	// 连接信号槽
	connect(pModbus, SIGNAL(signal_SysStateChange(uint16_t)), this, SLOT(SetState(uint16_t)));
    connect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(InputIO()));
    connect(pModbus, SIGNAL(signal_OutputChange()), this, SLOT(OutputIO()));

#if ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_YIDAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE))
    ui->tabWidgetManual->setTabText(1, tr("压铸机信号"));
#elif FACTORY == FA_SINROBOT_JC
    ui->tabWidgetManual->setTabText(1, tr("机床信号"));
#else
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
        ui->tabWidgetManual->setTabText(1, tr("铸机信号"));
    else
        ui->tabWidgetManual->setTabText(1, tr("塑机信号"));
#endif
    // 默认是第一页
    if(pModbus->GetSysType() != ROBOTARM_TYPE_SIXSV_PAD_E0)
        ui->tabWidgetManual->setCurrentIndex(2);
    else
        ui->tabWidgetManual->setCurrentIndex(0);
    //pyq 将峰值扭矩 峰值转速初始化
        maxTrqX =0;
        maxTrqY =0;
        maxTrqZ =0;
        maxTrqA =0;
        maxTrqB =0;
        maxTrqC =0;
        maxSpeedX =0;
        maxSpeedY =0;
        maxSpeedZ =0;
        maxSpeedA =0;
        maxSpeedB =0;
        maxSpeedC =0;
        if(!(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS))
			ui->tabWidgetManual->removeTab(ui->tabWidgetManual->indexOf(ui->tabGuard));
		//pyq end
    // 扩展输出模块默认选中主板
    retranslateUi();
//    show();
	return true;
}

// 退出手动操作画面
bool FormManual::ExitForm(void)
{
	disconnect(pModbus, SIGNAL(signal_SysStateChange(uint16_t)), this, SLOT(SetState(uint16_t)));
    disconnect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(InputIO()));
    disconnect(pModbus, SIGNAL(signal_OutputChange()), this, SLOT(OutputIO()));
	// 隐藏界面
//	hide();
	return true;
}

void FormManual::SetInIO(bool init)
{
    // main板
    if ((xIoPort::GetIn(IMM_VAR_IN_STOP) != ui->LedEsm->on()) || (init == true))
        ui->LedEsm->setOn(xIoPort::GetIn(IMM_VAR_IN_STOP));
    if ((xIoPort::GetIn(IMM_VAR_IN_SAFE) != ui->LedSdm->on()) || (init == true))
        ui->LedSdm->setOn(xIoPort::GetIn(IMM_VAR_IN_SAFE));
    if ((xIoPort::GetIn(IMM_VAR_IN_REJECT) != ui->LedRej->on()) || (init == true))
        ui->LedRej->setOn(xIoPort::GetIn(IMM_VAR_IN_REJECT));
    if ((xIoPort::GetIn(IMM_VAR_IN_MCP) != ui->LedMcp->on()) || (init == true))
        ui->LedMcp->setOn(xIoPort::GetIn(IMM_VAR_IN_MCP));
    if ((xIoPort::GetIn(IMM_VAR_IN_MOP) != ui->LedMop->on()) || (init == true))
        ui->LedMop->setOn(xIoPort::GetIn(IMM_VAR_IN_MOP));
    if ((xIoPort::GetIn(IMM_VAR_IN_IMOP) != ui->LedImop->on()) || (init == true))
        ui->LedImop->setOn(xIoPort::GetIn(IMM_VAR_IN_IMOP));
    if ((xIoPort::GetIn(IMM_VAR_IN_AUTO) != ui->LedAuto->on()) || (init == true))
        ui->LedAuto->setOn(xIoPort::GetIn(IMM_VAR_IN_AUTO));
    if ((xIoPort::GetIn(IMM_VAR_IN_EBP) != ui->LedEbp->on()) || (init == true))
        ui->LedEbp->setOn(xIoPort::GetIn(IMM_VAR_IN_EBP));
    if ((xIoPort::GetIn(IMM_VAR_IN_EFP) != ui->LedEfp->on()) || (init == true))
        ui->LedEfp->setOn(xIoPort::GetIn(IMM_VAR_IN_EFP));
    if ((xIoPort::GetIn(IMM_VAR_IN_C1P1) != ui->LedC1p1->on()) || (init == true))
        ui->LedC1p1->setOn(xIoPort::GetIn(IMM_VAR_IN_C1P1));
    if ((xIoPort::GetIn(IMM_VAR_IN_C1P2) != ui->LedC1p2->on()) || (init == true))
        ui->LedC1p2->setOn(xIoPort::GetIn(IMM_VAR_IN_C1P2));
    if ((xIoPort::GetIn(IMM_VAR_IN_C2P1) != ui->LedC2p1->on()) || (init == true))
        ui->LedC2p1->setOn(xIoPort::GetIn(IMM_VAR_IN_C2P1));
    if ((xIoPort::GetIn(IMM_VAR_IN_C2P2) != ui->LedC2p2->on()) || (init == true))
        ui->LedC2p2->setOn(xIoPort::GetIn(IMM_VAR_IN_C2P2));
    if ((xIoPort::GetIn(IMM_VAR_IN_MID) != ui->LedMmop->on()) || (init == true))
        ui->LedMmop->setOn(xIoPort::GetIn(IMM_VAR_IN_MID));

    if ((xIoPort::GetIn(SV_VAR_IN_XHOME) != ui->LedHorOrigin->on()) || (init == true))
        ui->LedHorOrigin->setOn(xIoPort::GetIn(SV_VAR_IN_XHOME));
    if ((xIoPort::GetIn(SV_VAR_IN_XCCWL) != ui->LedHorCcwL->on()) || (init == true))
        ui->LedHorCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_XCCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_XCWL) != ui->LedHorCwL->on()) || (init == true))
        ui->LedHorCwL->setOn(xIoPort::GetIn(SV_VAR_IN_XCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_XALM) != ui->LedHorAlm->on()) || (init == true))
        ui->LedHorAlm->setOn(xIoPort::GetIn(SV_VAR_IN_XALM));
    if ((xIoPort::GetIn(SV_VAR_IN_YHOME) != ui->LedVerOrigin->on()) || (init == true))
        ui->LedVerOrigin->setOn(xIoPort::GetIn(SV_VAR_IN_YHOME));
    if ((xIoPort::GetIn(SV_VAR_IN_YCCWL) != ui->LedVerCcwL->on()) || (init == true))
        ui->LedVerCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_YCCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_YCWL) != ui->LedVerCwL->on()) || (init == true))
        ui->LedVerCwL->setOn(xIoPort::GetIn(SV_VAR_IN_YCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_YALM) != ui->LedVerAlm->on()) || (init == true))
        ui->LedVerAlm->setOn(xIoPort::GetIn(SV_VAR_IN_YALM));
    if ((xIoPort::GetIn(SV_VAR_IN_ZHOME) != ui->LedTravelOrigin->on()) || (init == true))
        ui->LedTravelOrigin->setOn(xIoPort::GetIn(SV_VAR_IN_ZHOME));
    if ((xIoPort::GetIn(SV_VAR_IN_ZCCWL) != ui->LedTravelCcwL->on()) || (init == true))
        ui->LedTravelCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_ZCCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_ZCWL) != ui->LedTravelCwL->on()) || (init == true))
        ui->LedTravelCwL->setOn(xIoPort::GetIn(SV_VAR_IN_ZCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_ZALM) != ui->LedTravelAlm->on()) || (init == true))
        ui->LedTravelAlm->setOn(xIoPort::GetIn(SV_VAR_IN_ZALM));
    if ((xIoPort::GetIn(SV_VAR_IN_BHOME) != ui->LedHor1Origin->on()) || (init == true))
        ui->LedHor1Origin->setOn(xIoPort::GetIn(SV_VAR_IN_BHOME));
    if ((xIoPort::GetIn(SV_VAR_IN_BCCWL) != ui->LedHor1CcwL->on()) || (init == true))
        ui->LedHor1CcwL->setOn(xIoPort::GetIn(SV_VAR_IN_BCCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_BCWL) != ui->LedHor1CwL->on()) || (init == true))
        ui->LedHor1CwL->setOn(xIoPort::GetIn(SV_VAR_IN_BCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_BALM) != ui->LedHor1Alm->on()) || (init == true))
        ui->LedHor1Alm->setOn(xIoPort::GetIn(SV_VAR_IN_BALM));
    if ((xIoPort::GetIn(SV_VAR_IN_AHOME) != ui->LedVer1Origin->on()) || (init == true))
        ui->LedVer1Origin->setOn(xIoPort::GetIn(SV_VAR_IN_AHOME));
    if ((xIoPort::GetIn(SV_VAR_IN_ACCWL) != ui->LedVer1CcwL->on()) || (init == true))
        ui->LedVer1CcwL->setOn(xIoPort::GetIn(SV_VAR_IN_ACCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_ACWL) != ui->LedVer1CwL->on()) || (init == true))
        ui->LedVer1CwL->setOn(xIoPort::GetIn(SV_VAR_IN_ACWL));
    if ((xIoPort::GetIn(SV_VAR_IN_AALM) != ui->LedVer1Alm->on()) || (init == true))
        ui->LedVer1Alm->setOn(xIoPort::GetIn(SV_VAR_IN_AALM));
    if ((xIoPort::GetIn(SV_VAR_IN_CHOME) != ui->LedExtOrigin->on()) || (init == true))
        ui->LedExtOrigin->setOn(xIoPort::GetIn(SV_VAR_IN_CHOME));
    if ((xIoPort::GetIn(SV_VAR_IN_CCCWL) != ui->LedExtCcwL->on()) || (init == true))
        ui->LedExtCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_CCCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_CCWL) != ui->LedExtCwL->on()) || (init == true))
        ui->LedExtCwL->setOn(xIoPort::GetIn(SV_VAR_IN_CCWL));
    if ((xIoPort::GetIn(SV_VAR_IN_CALM) != ui->LedExtAlm->on()) || (init == true))
        ui->LedExtAlm->setOn(xIoPort::GetIn(SV_VAR_IN_CALM));
    if (pModbus->GetHomeInmold())
    {
        if ((xIoPort::GetIn(SV_VAR_IN_OUTMOLD) != ui->LedSafeIn->on()) || (init == true))
        ui->LedSafeIn->setOn(xIoPort::GetIn(SV_VAR_IN_OUTMOLD) && (!pModbus->GetOutmoldSignalNotuse()));
    }
    else
    {
        if ((xIoPort::GetIn(SV_VAR_IN_INMOLD) != ui->LedSafeIn->on()) || (init == true))
        ui->LedSafeIn->setOn(xIoPort::GetIn(SV_VAR_IN_INMOLD) && (!pModbus->GetInmoldSignalNotuse()));
    }
    if ((xIoPort::GetIn(SV_VAR_IN_OUTMOLD) != ui->LedSafOut->on()) || (init == true))
        ui->LedSafOut->setOn(xIoPort::GetIn(SV_VAR_IN_OUTMOLD));
    if ((xIoPort::GetIn(SV_VAR_IN_YWPOS) != ui->LedSafePaUp->on()) || (init == true))
        ui->LedSafePaUp->setOn(xIoPort::GetIn(SV_VAR_IN_YWPOS));
    if ((xIoPort::GetIn(SV_VAR_IN_AWPOS) != ui->LedSafeRaUp->on()) || (init == true))
        ui->LedSafeRaUp->setOn(xIoPort::GetIn(SV_VAR_IN_AWPOS));
    if ((xIoPort::GetIn(RBT_VAR_IN_LOW_AIR) != ui->LedPressure->on()) || (init == true))
        ui->LedPressure->setOn(xIoPort::GetIn(RBT_VAR_IN_LOW_AIR));
    if ((xIoPort::GetIn(RBT_VAR_IN_DWN_SAF) != ui->LedDwnSafe->on()) || (init == true))
        ui->LedDwnSafe->setOn(xIoPort::GetIn(RBT_VAR_IN_DWN_SAF));
    if ((xIoPort::GetIn(RBT_VAR_IN_RUN_HOR) != ui->LedRaHor->on()) || (init == true))
        ui->LedRaHor->setOn(xIoPort::GetIn(RBT_VAR_IN_RUN_HOR));
    if ((xIoPort::GetIn(RBT_VAR_IN_RUN_VER) != ui->LedRaVer->on()) || (init == true))
        ui->LedRaVer->setOn(xIoPort::GetIn(RBT_VAR_IN_RUN_VER));
    if ((xIoPort::GetIn(RBT_VAR_IN_PRO_HOR) != ui->LedPaHor->on()) || (init == true))
        ui->LedPaHor->setOn(xIoPort::GetIn(RBT_VAR_IN_PRO_HOR));
    if ((xIoPort::GetIn(RBT_VAR_IN_PRO_VER) != ui->LedPaVer->on()) || (init == true))
        ui->LedPaVer->setOn(xIoPort::GetIn(RBT_VAR_IN_PRO_VER));
    if ((xIoPort::GetIn(RBT_VAR_IN_RUN_ASC) != ui->LedRaAsc->on()) || (init == true))
        ui->LedRaAsc->setOn(xIoPort::GetIn(RBT_VAR_IN_RUN_ASC));
    if ((xIoPort::GetIn(RBT_VAR_IN_RUN_DES) != ui->LedRaDes->on()) || (init == true))
        ui->LedRaDes->setOn(xIoPort::GetIn(RBT_VAR_IN_RUN_DES));
    if ((xIoPort::GetIn(RBT_VAR_IN_RUN_ADV) != ui->LedRaAdv->on()) || (init == true))
        ui->LedRaAdv->setOn(xIoPort::GetIn(RBT_VAR_IN_RUN_ADV));
    if ((xIoPort::GetIn(RBT_VAR_IN_RUN_RET) != ui->LedRaRet->on()) || (init == true))
        ui->LedRaRet->setOn(xIoPort::GetIn(RBT_VAR_IN_RUN_RET));
}
void FormManual::InputIO(void)
{
    SetInIO(false);
    SetInPortState(m_outidx, false);
}
void FormManual::OutputIO(void)
{
    SetOutIO(false);
    SetOutPortState(m_outidx, false);
}
void FormManual::SetOutIO(bool init)
{
    // main板
    if ((xIoPort::GetOut(IMM_VAR_OUT_MAF) != ui->LedMaf->on()) || (init == true))
        ui->LedMaf->setOn(xIoPort::GetOut(IMM_VAR_OUT_MAF));
    if ((xIoPort::GetOut(IMM_VAR_OUT_HMAF) != ui->LedHMaf->on()) || (init == true))
        ui->LedHMaf->setOn(xIoPort::GetOut(IMM_VAR_OUT_HMAF));
    if ((xIoPort::GetOut(IMM_VAR_OUT_EMC) != ui->swEmc->on()) || (init == true))
        ui->swEmc->setOn(xIoPort::GetOut(IMM_VAR_OUT_EMC));
    if ((xIoPort::GetOut(IMM_VAR_OUT_HEMC) != ui->LedHEmc->on()) || (init == true))
        ui->LedHEmc->setOn(xIoPort::GetOut(IMM_VAR_OUT_HEMC));
    if ((xIoPort::GetOut(IMM_VAR_OUT_EMO) != ui->swEmo->on()) || (init == true))
        ui->swEmo->setOn(xIoPort::GetOut(IMM_VAR_OUT_EMO));
    if ((xIoPort::GetOut(IMM_VAR_OUT_RBT) != ui->swIMM->on()) || (init == true))
        ui->swIMM->setOn(xIoPort::GetOut(IMM_VAR_OUT_RBT));
    if ((xIoPort::GetOut(IMM_VAR_OUT_EEB) != ui->swEeb->on()) || (init == true))
        ui->swEeb->setOn(xIoPort::GetOut(IMM_VAR_OUT_EEB));
    if ((xIoPort::GetOut(IMM_VAR_OUT_EEF) != ui->swEef->on()) || (init == true))
        ui->swEef->setOn(xIoPort::GetOut(IMM_VAR_OUT_EEF));
    if ((xIoPort::GetOut(IMM_VAR_OUT_C1P1) != ui->swC1p1->on()) || (init == true))
        ui->swC1p1->setOn(xIoPort::GetOut(IMM_VAR_OUT_C1P1));
    if ((xIoPort::GetOut(IMM_VAR_OUT_C1P2) != ui->swC1p2->on()) || (init == true))
        ui->swC1p2->setOn(xIoPort::GetOut(IMM_VAR_OUT_C1P2));
    if ((xIoPort::GetOut(IMM_VAR_OUT_C2P1) != ui->swC2p1->on()) || (init == true))
        ui->swC2p1->setOn(xIoPort::GetOut(IMM_VAR_OUT_C2P1));
    if ((xIoPort::GetOut(IMM_VAR_OUT_C2P2) != ui->swC2p2->on()) || (init == true))
        ui->swC2p2->setOn(xIoPort::GetOut(IMM_VAR_OUT_C2P2));
    if ((xIoPort::GetOut(SV_VAR_OUT_XSON) != ui->LedHorOn->on()) || (init == true))
        ui->LedHorOn->setOn(xIoPort::GetOut(SV_VAR_OUT_XSON));
    if ((xIoPort::GetOut(SV_VAR_OUT_YSON) != ui->LedVerOn->on()) || (init == true))
        ui->LedVerOn->setOn(xIoPort::GetOut(SV_VAR_OUT_YSON));
    if ((xIoPort::GetOut(SV_VAR_OUT_ZSON) != ui->LedTravelOn->on()) || (init == true))
        ui->LedTravelOn->setOn(xIoPort::GetOut(SV_VAR_OUT_ZSON));
    if ((xIoPort::GetOut(SV_VAR_OUT_BSON) != ui->LedHor1On->on()) || (init == true))
        ui->LedHor1On->setOn(xIoPort::GetOut(SV_VAR_OUT_BSON));
    if ((xIoPort::GetOut(SV_VAR_OUT_ASON) != ui->LedVer1On->on()) || (init == true))
        ui->LedVer1On->setOn(xIoPort::GetOut(SV_VAR_OUT_ASON));
    if ((xIoPort::GetOut(SV_VAR_OUT_CSON) != ui->LedExtOn->on()) || (init == true))
        ui->LedExtOn->setOn(xIoPort::GetOut(SV_VAR_OUT_CSON));    

    if ((xIoPort::GetOut(RBT_VAR_OUT_RUN_HOR) != ui->BtnRaHor->on()) || (init == true))
        ui->BtnRaHor->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_HOR));
    if ((xIoPort::GetOut(RBT_VAR_OUT_RUN_VER) != ui->BtnRaVer->on()) || (init == true))
        ui->BtnRaVer->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_VER));
    if ((xIoPort::GetOut(RBT_VAR_OUT_PRO_VER) != ui->BtnPaVer->on()) || (init == true))
        ui->BtnPaVer->setOn(xIoPort::GetOut(RBT_VAR_OUT_PRO_VER));
    if ((xIoPort::GetOut(RBT_VAR_OUT_PRO_HOR) != ui->BtnPaHor->on()) || (init == true))
        ui->BtnPaHor->setOn(xIoPort::GetOut(RBT_VAR_OUT_PRO_HOR));
    if ((xIoPort::GetOut(RBT_VAR_OUT_RUN_DES) != ui->BtnRaDes->on()) || (init == true))
        ui->BtnRaDes->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_DES));
    if ((xIoPort::GetOut(RBT_VAR_OUT_RUN_RET) != ui->BtnRaRet->on()) || (init == true))
        ui->BtnRaRet->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_RET));
    if ((xIoPort::GetOut(RBT_VAR_OUT_RUN_ADV) != ui->BtnRaAdv->on()) || (init == true))
        ui->BtnRaAdv->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_ADV));
    if ((xIoPort::GetOut(RBT_VAR_OUT_LAMP) != ui->LedActLed->on()) || (init == true))
        ui->LedActLed->setOn(xIoPort::GetOut(RBT_VAR_OUT_LAMP));
    if ((xIoPort::GetOut(RBT_VAR_OUT_ALM_BEEP) != ui->LedBeepLed->on()) || (init == true))
        ui->LedBeepLed->setOn(xIoPort::GetOut(RBT_VAR_OUT_ALM_BEEP));
    if ((xIoPort::GetOut(RBT_VAR_OUT_ALM_LAMP) != ui->LedAlmLed->on()) || (init == true))
        ui->LedAlmLed->setOn(xIoPort::GetOut(RBT_VAR_OUT_ALM_LAMP));

    if ((xIoPort::GetOut(EM4_VAR_Y04) != ui->BtnCONV->on()) || (init == true))
        ui->BtnCONV->setOn(xIoPort::GetOut(EM4_VAR_Y04));
    if ((xIoPort::GetOut(EM4_VAR_Y05) != ui->BtnCUT->on()) || (init == true))
        ui->BtnCUT->setOn(xIoPort::GetOut(EM4_VAR_Y05));
}
// 检查能否手动操作
bool FormManual::checkManual(void)
{
	// 只有手动状态才能执行		//Added by zhangjz for v1.03 2012-07-13
	if (pModbus->GetSysState() != SYS_STATE_MANUAL)
		return false;
	// 检查用户权限
	if (xPermissions::GetPermissions(PER_MANUAL_OPR) == false)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
		return false;
	}
	// 检查安全开关
    if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
	{
#if UI_SAFESW_TIP
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAFESW_TIP));
#endif
		return false;
	}
#if SELECT_SWITCH_USE
	// 检查选择开关
	if (pxKeyPad->GetSwitch() != CUSKEY_SEL_MANUAL)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SELSW_STOP));
		return false;
	}
#endif
	return true;
}
// 输出控制信号槽
void FormManual::ParmCtrl(int code)
{
	if (!checkManual())
		return;
	// 执行手动指令
    if (xIoPort::GetOut(RBT_VAR_OUT_PRO_HOR) == true)
		pModbus->ManualPro(PRO_ACT_VERTIACL);
	else
		pModbus->ManualPro(PRO_ACT_HOZIONTAL);
}
void FormManual::RarmCtrl(int code)
{
    if (!checkManual())
        return;
    // 执行手动指令
    if (xIoPort::GetOut(RBT_VAR_OUT_RUN_HOR) == true)
        pModbus->ManualRun(RUN_ACT_VERTIACL);
    else
        pModbus->ManualRun(RUN_ACT_HORIZONTAL);
}
void FormManual::RarmAscDesCtrl(void)
{
    if (!checkManual())
        return;
    // 执行手动指令
    if (xIoPort::GetOut(RBT_VAR_OUT_RUN_DES) == true)
        pModbus->ManualRun(RUN_ACT_ASCENT);
    else
        pModbus->ManualRun(RUN_ACT_DESCENT);
}
void FormManual::RarmAdvCtrl(void)
{
    if (!checkManual())
        return;
    // 执行手动指令
    if (xIoPort::GetOut(RBT_VAR_OUT_RUN_ADV) == true)
        pModbus->ManualRun(RUN_ACT_RETURN);
    else
        pModbus->ManualRun(RUN_ACT_ADVANCE);
}
void FormManual::RarmRetCtrl(void)
{
    if (!checkManual())
        return;
    // 执行手动指令
    if (xIoPort::GetOut(RBT_VAR_OUT_RUN_RET) == true)
        pModbus->ManualRun(RUN_ACT_ADVANCE);
    else
        pModbus->ManualRun(RUN_ACT_RETURN);
}

void FormManual::ConvCtrl(void)
{
    if(!checkManual())
        return;
    if(xIoPort::GetOut(EM4_VAR_Y04) == true)
        pModbus->ManualExt(false,EM4_VAR_Y04);
    else
        pModbus->ManualExt(true,EM4_VAR_Y04);
}

void FormManual::CutCtrl(void)
{
    if(!checkManual())
        return;
    if(xIoPort::GetOut(EM4_VAR_Y05) == true)
        pModbus->ManualExt(false,EM4_VAR_Y05);
    else
        pModbus->ManualExt(true,EM4_VAR_Y05);
}
void FormManual::ImmCtrl(int code)
{
	if (!checkManual())
		return;
	// 执行手动指令
#if (FACTORY == FA_SHINI)
    uint32_t tmp;
	tmp = pModbus->GetOutMain();
	if (code == IMMOUT_C1P1)
	{
        if (xIoPort::GetOut(IMM_VAR_OUT_C1P1) == true)
		{
			pModbus->ManualIMM(IMMOUT_C1P1_OFF);
			return;
		}
		else
		{
			pModbus->ManualIMM(IMMOUT_C1P1);
			return;
		}
	}
	else if (code == IMMOUT_C1P2)
	{
        if (xIoPort::GetOut(IMM_VAR_OUT_C1P2) == true)
		{
			pModbus->ManualIMM(IMMOUT_C1P2_OFF);
			return;
		}
		else
		{
			pModbus->ManualIMM(IMMOUT_C1P2);
			return;
		}
	}
	else if (code == IMMOUT_C2P1)
	{
        if (xIoPort::GetOut(IMM_VAR_OUT_C2P1) == true)
		{
			pModbus->ManualIMM(IMMOUT_C2P1_OFF);
			return;
		}
		else
		{
			pModbus->ManualIMM(IMMOUT_C2P1);
			return;
		}
	}
	else if (code == IMMOUT_C2P2)
	{
        if (xIoPort::GetOut(IMM_VAR_OUT_C2P2) == true)
		{
			pModbus->ManualIMM(IMMOUT_C2P2_OFF);
			return;
		}
		else
		{
			pModbus->ManualIMM(IMMOUT_C2P2);
			return;
		}
	}
	else if (code == IMMOUT_EEF)
	{
        if (xIoPort::GetOut(IMM_VAR_OUT_EEF) == true)
		{
			pModbus->ManualIMM(IMMOUT_EEF_OFF);
			return;
		}
		else
		{
			pModbus->ManualIMM(IMMOUT_EEF);
			return;
		}
	}
	else if (code == IMMOUT_EEB)
	{
        if (xIoPort::GetOut(IMM_VAR_OUT_EEB) == true)
		{
			pModbus->ManualIMM(IMMOUT_EEB_OFF);
			return;
		}
		else
		{
			pModbus->ManualIMM(IMMOUT_EEB);
			return;
		}
	}
    else if (code == IMMOUT_RBT_ON)
    {
        // 检查用户权限
        if (xPermissions::GetPermissions(PER_SRV_MACHINE) == false)
        {
            xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
            return;
        }
        if (xIoPort::GetOut(IMM_VAR_OUT_RBT) == true)
        {
            pModbus->ManualIMM(IMMOUT_RBT_ON);
            return;
        }
        else
        {
            pModbus->ManualIMM(IMMOUT_RBT_OFF);
            return;
        }
    }
#endif
	pModbus->ManualIMM(code);
}
void FormManual::EoCtrl(int code)
{
	if (!checkManual())
		return;
	// 执行手动指令
    switch (m_outidx)
    {
    case EXTEND_MAIN:
        if(code > 15)
            code += 64;
        code = MAIN_VAR_Y00 + code;
        break;
    case EXTEND_BOARD_1:
        code = EM1_VAR_Y00 + code;
        break;
    case EXTEND_BOARD_2:
        code = EM2_VAR_Y00 + code;
        break;
    case EXTEND_BOARD_3:
        code = EM3_VAR_Y00 + code;
        break;
    case EXTEND_BOARD_4:
        code = EM4_VAR_Y00 + code;
        break;
    }
    if (xIoPort::GetOut(code) == true)
		pModbus->ManualExt(false, code);
	else
		pModbus->ManualExt(true, code);
}

// 扩展输入和扩展输出翻页控制槽
void FormManual::OutputSelect(int idx)
{
    m_outidx = idx;
    switch (m_outidx)
    {
    case 0:
        ui->BtnOMain->setOn(true);
        ui->BtnOM1->setOn(false);
        ui->BtnOM2->setOn(false);
        ui->BtnOM3->setOn(false);
        ui->BtnOM4->setOn(false);
        setOutPortNames(EXTEND_MAIN);
        SetOutPortVisible(EXTEND_MAIN);
        SetOutPortState(EXTEND_MAIN, false);
        setInPortNames(EXTEND_MAIN);
        SetInPortVisible(EXTEND_MAIN);
        SetInPortState(EXTEND_MAIN, false);
        break;
    case 1:
        ui->BtnOMain->setOn(false);
        ui->BtnOM1->setOn(true);
        ui->BtnOM2->setOn(false);
        ui->BtnOM3->setOn(false);
        ui->BtnOM4->setOn(false);
        setOutPortNames(EXTEND_BOARD_1);
        SetOutPortVisible(EXTEND_BOARD_1);
        SetOutPortState(EXTEND_BOARD_1, false);
        setInPortNames(EXTEND_BOARD_1);
        SetInPortVisible(EXTEND_BOARD_1);
        SetInPortState(EXTEND_BOARD_1, false);
        break;
    case 2:
        ui->BtnOMain->setOn(false);
        ui->BtnOM1->setOn(false);
        ui->BtnOM2->setOn(true);
        ui->BtnOM3->setOn(false);
        ui->BtnOM4->setOn(false);
        setOutPortNames(EXTEND_BOARD_2);
        SetOutPortVisible(EXTEND_BOARD_2);
        SetOutPortState(EXTEND_BOARD_2, false);
        setInPortNames(EXTEND_BOARD_2);
        SetInPortVisible(EXTEND_BOARD_2);
        SetInPortState(EXTEND_BOARD_2, false);
        break;
    case 3:
        ui->BtnOMain->setOn(false);
        ui->BtnOM1->setOn(false);
        ui->BtnOM2->setOn(false);
        ui->BtnOM3->setOn(true);
        ui->BtnOM4->setOn(false);
        setOutPortNames(EXTEND_BOARD_3);
        SetOutPortVisible(EXTEND_BOARD_3);
        SetOutPortState(EXTEND_BOARD_3, false);
        setInPortNames(EXTEND_BOARD_3);
        SetInPortVisible(EXTEND_BOARD_3);
        SetInPortState(EXTEND_BOARD_3, false);
        break;
    case 4:
        ui->BtnOMain->setOn(false);
        ui->BtnOM1->setOn(false);
        ui->BtnOM2->setOn(false);
        ui->BtnOM3->setOn(false);
        ui->BtnOM4->setOn(true);
        setOutPortNames(EXTEND_BOARD_4);
        SetOutPortVisible(EXTEND_BOARD_4);
        SetOutPortState(EXTEND_BOARD_4, false);
        setInPortNames(EXTEND_BOARD_4);
        SetInPortVisible(EXTEND_BOARD_4);
        SetInPortState(EXTEND_BOARD_4, false);
        break;
    }
}
//void FormManual::InputSelect(int idx)
//{
//    m_inidx = idx;
//    switch (m_inidx)
//    {
//    case 0:
//        ui->BtnIMain->setOn(true);
//        ui->BtnIM1->setOn(false);
//        ui->BtnIM2->setOn(false);
//        ui->BtnIM3->setOn(false);
//        ui->BtnIM4->setOn(false);
//        break;
//    case 1:
//        ui->BtnIMain->setOn(false);
//        ui->BtnIM1->setOn(true);
//        ui->BtnIM2->setOn(false);
//        ui->BtnIM3->setOn(false);
//        ui->BtnIM4->setOn(false);
//        break;
//    case 2:
//        ui->BtnIMain->setOn(false);
//        ui->BtnIM1->setOn(false);
//        ui->BtnIM2->setOn(true);
//        ui->BtnIM3->setOn(false);
//        ui->BtnIM4->setOn(false);
//        break;
//    case 3:
//        ui->BtnIMain->setOn(false);
//        ui->BtnIM1->setOn(false);
//        ui->BtnIM2->setOn(false);
//        ui->BtnIM3->setOn(true);
//        ui->BtnIM4->setOn(false);
//        break;
//    case 4:
//        ui->BtnIMain->setOn(false);
//        ui->BtnIM1->setOn(false);
//        ui->BtnIM2->setOn(false);
//        ui->BtnIM3->setOn(false);
//        ui->BtnIM4->setOn(true);
//        break;
//    }
//}
void FormManual::UpdataActualServo(int16_t actualTrqX,int16_t actualTrqY,int16_t actualTrqZ,int16_t actualTrqA,int16_t actualTrqB,int16_t actualTrqC
                                            ,int16_t actualSpeedX,int16_t actualSpeedY,int16_t actualSpeedZ,int16_t actualSpeedA,int16_t actualSpeedB,int16_t actualSpeedC)
{
    ui->BoxActualTrqX->setValue(((double)actualTrqX)/10.00);
    ui->BoxActualTrqY->setValue(((double)actualTrqY)/10.00);
    ui->BoxActualTrqZ->setValue(((double)actualTrqZ)/10.00);
	ui->BoxActualTrqX2->setValue(((double)actualTrqB)/10.00);
	ui->BoxActualTrqY2->setValue(((double)actualTrqA)/10.00);
    ui->BoxActualTrqA->setValue(((double)actualTrqC)/10.00);
    ui->BoxActualSpeedX->setValue(actualSpeedX);
    ui->BoxActualSpeedY->setValue(actualSpeedY);
    ui->BoxActualSpeedZ->setValue(actualSpeedZ);
	ui->BoxActualSpeedX2->setValue(actualSpeedB);
	ui->BoxActualSpeedY2->setValue(actualSpeedA);
    ui->BoxActualSpeedA->setValue(actualSpeedC);
    if(abs(maxTrqX)<abs(actualTrqX))
        maxTrqX=actualTrqX;
    if(abs(maxTrqY)<abs(actualTrqY))
        maxTrqY=actualTrqY;
    if(abs(maxTrqZ)<abs(actualTrqZ))
        maxTrqZ=actualTrqZ;
    if(abs(maxTrqA)<abs(actualTrqA))
        maxTrqA=actualTrqA;
    if(abs(maxTrqB)<abs(actualTrqB))
        maxTrqB=actualTrqB;
    if(abs(maxTrqC)<abs(actualTrqC))
        maxTrqC=actualTrqC;
    if(abs(maxSpeedX)<abs(actualSpeedX))
        maxSpeedX=actualSpeedX;
    if(abs(maxSpeedY)<abs(actualSpeedY))
        maxSpeedY=actualSpeedY;
    if(abs(maxSpeedZ)<abs(actualSpeedZ))
        maxSpeedZ=actualSpeedZ;
    if(abs(maxSpeedA)<abs(actualSpeedA))
        maxSpeedA=actualSpeedA;
    if(abs(maxSpeedB)<abs(actualSpeedB))
        maxSpeedB=actualSpeedB;
    if(abs(maxSpeedC)<abs(actualSpeedC))
        maxSpeedC=actualSpeedC;
    ui->BoxMaxTrqX->setValue(((double)maxTrqX)/10.00);
    ui->BoxMaxTrqY->setValue(((double)maxTrqY)/10.00);
    ui->BoxMaxTrqZ->setValue(((double)maxTrqZ)/10.00);
	ui->BoxMaxTrqX2->setValue(((double)maxTrqB)/10.00);
	ui->BoxMaxTrqY2->setValue(((double)maxTrqA)/10.00);
    ui->BoxMaxTrqA->setValue(((double)maxTrqC)/10.00);
    ui->BoxMaxSpeedX->setValue(maxSpeedX);
    ui->BoxMaxSpeedY->setValue(maxSpeedY);
    ui->BoxMaxSpeedZ->setValue(maxSpeedZ);
	ui->BoxMaxSpeedX2->setValue(maxSpeedB);
	ui->BoxMaxSpeedY2->setValue(maxSpeedA);
    ui->BoxMaxSpeedA->setValue(maxSpeedC);
}
