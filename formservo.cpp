#if defined(Q_WS_QWS)
#include <unistd.h>
#endif
#include <QSettings>
#include "formservo.h"
#include "ui_formservo.h"
#include "driver/xioport.h"
#include "xstringresource.h"
#include "xsystemlog.h"
#include "xmessagebox.h"
#include "dialogframe.h"
#include "servoalias.h"
#include "dialognumberpad.h"


#define SRVPG_SAFE				0
#define SRVPG_SAFE2 			1
#define SRVPG_SHORTCUT			2
#define SRVPG_PAHOR				3
#define SRVPG_PAVER				4
#define SRVPG_TRAVEL			5
#define SRVPG_RAHOR				6
#define SRVPG_RAVER				7
#define SRVPG_EXTEND			8
#define SRVPG_HOME				9

#define ENCODER_INCREMENTAL     0
#define ENCODER_HCFA_X3         1
#define ENCODER_HCFA_X3E        2
#define ENCODER_DELTA_A2        3
#define ENCODER_PANASONIC_A6	4
#define ENCODER_SINSERVO_SS 	5

#define AxisPA                  0x0000
#define AxisP3                  0x0100
#define AxisP4                  0x0200
#define AxisPS                  0x1000

extern DialogFrame *pDialogMain;

Formservo::Formservo(CMBProtocol *modbus, QWidget *parent) :	QWidget(parent), ui(new Ui::Formservo)
{
	ui->setupUi(this);
	pModbus = modbus;
	retranslateUi();

    m_AxisType[0] = ui->checkBoxPHor;
    m_AxisType[1] = ui->checkBoxPVer;
    m_AxisType[2] = ui->checkBoxTrv;
    m_AxisType[3] = ui->checkBoxRVer;
    m_AxisType[4] = ui->checkBoxRHor;
    m_AxisType[5] = ui->checkBoxExt;

    m_HomeType[0] = ui->cBoxPaHorHome;
    m_HomeType[1] = ui->cBoxPaVerHome;
    m_HomeType[2] = ui->cBoxTrvHome;
    m_HomeType[3] = ui->cBoxRaVerHome;
    m_HomeType[4] = ui->cBoxRaHorHome;
    m_HomeType[5] = ui->cBoxExtHome;

    m_DecType[0] = ui->checkBoxPHorDes;
    m_DecType[1] = ui->checkBoxPVerDes;
    m_DecType[2] = ui->checkBoxTrvDes;
    m_DecType[3] = ui->checkBoxRVerDes;
    m_DecType[4] = ui->checkBoxRHorDes;
    m_DecType[5] = ui->checkBoxExtDes;

    m_DirType[0] = ui->checkBoxPHorDir;
    m_DirType[1] = ui->checkBoxPVerDir;
    m_DirType[2] = ui->checkBoxTrvDir;
    m_DirType[3] = ui->checkBoxRVerDir;
    m_DirType[4] = ui->checkBoxRHorDir;
    m_DirType[5] = ui->checkBoxExtDir;

    m_HomeMod[0] = ui->checkBoxPHorHome;
    m_HomeMod[1] = ui->checkBoxPVerHome;
    m_HomeMod[2] = ui->checkBoxTrvHome;
    m_HomeMod[3] = ui->checkBoxRVerHome;
    m_HomeMod[4] = ui->checkBoxRHorHome;
    m_HomeMod[5] = ui->checkBoxExtHome;
    // 选择按钮组
    pBtnPage = new QButtonGroup;
    pBtnPage->addButton(ui->radioSafe, SRVPG_SAFE);
    pBtnPage->addButton(ui->radioSafe2, SRVPG_SAFE2);
    pBtnPage->addButton(ui->radioQuick, SRVPG_SHORTCUT);
    pBtnPage->addButton(ui->radioPaHor, SRVPG_PAHOR);
    pBtnPage->addButton(ui->radioPaVer, SRVPG_PAVER);
    pBtnPage->addButton(ui->radioTrv, SRVPG_TRAVEL);
    pBtnPage->addButton(ui->radioRaHor, SRVPG_RAHOR);
    pBtnPage->addButton(ui->radioRaVer, SRVPG_RAVER);
    pBtnPage->addButton(ui->radioExt, SRVPG_EXTEND);
    pBtnPage->addButton(ui->radioHome, SRVPG_HOME);
    connect(pBtnPage, SIGNAL(buttonClicked(int)), this, SLOT(setCurrentpage(int)));

    pRBtnSVDev = new QButtonGroup;
    pRBtnSVDev->addButton(ui->radioPHorDEV,AXES_IDX_X);
    pRBtnSVDev->addButton(ui->radioPVerDEV,AXES_IDX_Y);
    pRBtnSVDev->addButton(ui->radioTRVDEV,AXES_IDX_Z);
    pRBtnSVDev->addButton(ui->radioRVerDEV,AXES_IDX_A);
    pRBtnSVDev->addButton(ui->radioRHorDEV,AXES_IDX_B);
    connect(pRBtnSVDev, SIGNAL(buttonClicked(int)), this, SLOT(updataSvDevPara(int)));

    pRBtnSVSelect = new QButtonGroup;
    pRBtnSVSelect->addButton(ui->radioSelectAxisPA,AxisPA);
    pRBtnSVSelect->addButton(ui->radioSelectAxisP3,AxisP3);
    pRBtnSVSelect->addButton(ui->radioSelectAxisP4,AxisP4);
    pRBtnSVSelect->addButton(ui->radioSelectAxisPS,AxisPS);

    //构造轮询计时器
    time = new QTimer(this);
    ReadSVDev = true;
    ui->radioPower->setEnabled(false);
    connect(ui->tabWidgetSvDev,SIGNAL(currentChanged(int)),this,SLOT(currentChanged(int)));
}

Formservo::~Formservo()
{
	delete ui;
//	StrDirection.clear();
    delete pBtnPage;
    delete pRBtnSVDev;
    delete time;

}

void Formservo::changeEvent(QEvent *e)
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

void Formservo::retranslateUi(void)
{
#if ((FACTORY == FA_SINROBOT_SIDE) || (FACTORY == FA_JIEJIA_SIDE))
    ui->LedSafePaUp->setText(GetServoName(AXIS_IDX_PVER) + tr("轴模外安全区"));
    ui->LedSafeRaUp->setText(GetServoName(AXIS_IDX_RVER) + tr("轴上位安全区"));
#else
	ui->LedSafePaUp->setText(GetServoName(AXIS_IDX_PVER) + tr("轴上位安全区"));
	ui->LedSafeRaUp->setText(GetServoName(AXIS_IDX_RVER) + tr("轴上位安全区"));
#endif
	ui->LedSafeOut->setText(GetServoName(AXIS_IDX_TRV) + tr("轴模外安全区"));
    ui->LedSafeRot->setText(GetServoName(AXIS_IDX_RVER) + tr("(倒角)轴模內安全区"));
    ui->LedSafeTrv->setText(GetServoName(AXIS_IDX_RVER) + tr("(倒角)轴横行安全区"));
	ui->labelTrvWaitPos->setText(GetServoName(AXIS_IDX_TRV) + tr("轴原点复归后待机位置"));
    ui->LedSafeOut2->setText(GetServoName(AXIS_IDX_TRV) + tr("轴模外安全区2"));
    ui->LedSafePaHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴横行安全区"));

	ui->groupBoxPaHor->setTitle(GetServoName(AXIS_IDX_PHOR) + tr("轴"));
	ui->groupBoxPaVer->setTitle(GetServoName(AXIS_IDX_PVER) + tr("轴"));
	ui->groupBoxTrv->setTitle(GetServoName(AXIS_IDX_TRV) + tr("轴"));
	ui->groupBoxRaHor->setTitle(GetServoName(AXIS_IDX_RHOR) + tr("轴"));
	ui->groupBoxRaVer->setTitle(GetServoName(AXIS_IDX_RVER) + tr("轴"));
	ui->groupBoxExt->setTitle(GetServoName(AXIS_IDX_EXT) + tr("轴"));

    ui->cBPaHorEncoder->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴"));
    ui->cBPaVerEncoder->setText(GetServoName(AXIS_IDX_PVER) + tr("轴"));
    ui->cBTrvEncoder->setText(GetServoName(AXIS_IDX_TRV) + tr("轴"));
    ui->cBRaHorEncoder->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴"));
    ui->cBRaVerEncoder->setText(GetServoName(AXIS_IDX_RVER) + tr("轴"));
    ui->cBExtEncoder->setText(GetServoName(AXIS_IDX_EXT) + tr("轴"));

    ui->radioPaHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴"));
    ui->radioPaVer->setText(GetServoName(AXIS_IDX_PVER) + tr("轴"));
    ui->radioTrv->setText(GetServoName(AXIS_IDX_TRV) + tr("轴"));
    ui->radioRaHor->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴"));
    ui->radioRaVer->setText(GetServoName(AXIS_IDX_RVER) + tr("轴"));
    ui->radioExt->setText(GetServoName(AXIS_IDX_EXT) + tr("轴"));

    ui->radioPHorDEV->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴"));
    ui->radioPVerDEV->setText(GetServoName(AXIS_IDX_PVER) + tr("轴"));
    ui->radioTRVDEV->setText(GetServoName(AXIS_IDX_TRV) + tr("轴"));
    ui->radioRHorDEV->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴"));
    ui->radioRVerDEV->setText(GetServoName(AXIS_IDX_RVER) + tr("轴"));

    if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        ui->LedSafeOut->setText(tr("横行X模外安全区域"));
        ui->labelPaSafeHor->setText(tr("(取件臂Z1) 前后Y方向模内安全区"));
        ui->labelRaSafeHor->setText(tr("(喷雾臂Z2) 前后Y方向模内安全区"));
        ui->LedSafeIn->setText(tr("(取件臂Z1) 横行X方向模内安全区"));
        ui->LedSafeIn2->setText(tr("(喷雾臂Z2) 横行X方向模内安全区"));
        ui->LedSafeRaHor->setText(tr("(喷雾臂Z2) 横行X方向安全区"));
        ui->LedSafeExtMold->setText(GetServoName(AXIS_IDX_EXT) + tr("轴模内安全区"));
        ui->LedSafeExt->setText(GetServoName(AXIS_IDX_EXT) + tr("轴横行安全区"));
    }
    else if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E3) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F3) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0))
    {
        ui->LedSafeIn->setText(GetServoName(AXIS_IDX_TRV) + tr("轴模內安全区"));
        ui->LedSafeIn2->setText(GetServoName(AXIS_IDX_TRV) + tr("轴模內安全区"));
        ui->labelPaSafeHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴模内安全区"));
        ui->labelRaSafeHor->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴模内安全区"));
        ui->LedSafeRaHor->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴横行安全区"));
        ui->LedSafeExtMold->setText(GetServoName(AXIS_IDX_EXT) + tr("轴模内安全区"));
        ui->LedSafeExt->setText(GetServoName(AXIS_IDX_EXT) + tr("轴横行安全区"));
    }
    else
    {
        ui->LedSafeIn->setText(tr("正臂") + GetServoName(AXIS_IDX_TRV) + tr("轴模內安全区"));
        ui->LedSafeIn2->setText(tr("副臂") + GetServoName(AXIS_IDX_TRV) + tr("轴模內安全区"));
        ui->labelPaSafeHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴模内安全区域"));
        ui->labelRaSafeHor->setText(GetServoName(AXIS_IDX_RHOR) + tr("(旋转)轴模内安全角度"));
        ui->LedSafeRaHor->setText(GetServoName(AXIS_IDX_RHOR) + tr("(旋转)轴横行安全区"));
        ui->LedSafeExtMold->setText(GetServoName(AXIS_IDX_EXT) + tr("轴模内安全区"));
        ui->LedSafeExt->setText(GetServoName(AXIS_IDX_EXT) + tr("轴横行安全区"));
    }

#if ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE))
    if(!pModbus->GetRhorSrvUse())
        ui->labelPaHorLen->setText(tr("前后Y轴软件行程"));
    else
        ui->labelPaHorLen->setText(tr("取件和喷雾臂原点距离"));
#else
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        if(!pModbus->GetRhorSrvUse())
            ui->labelPaHorLen->setText(tr("前后Y轴软件行程"));
        else
            ui->labelPaHorLen->setText(tr("取件和喷雾臂原点距离"));
    }
    else if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4)))
    {
        ui->labelPaHorLen->setText(tr("软件行程"));
        ui->labelRaHorInt->setText(tr("软件行程"));
    }
    else
    {
        if ((!pModbus->GetRhorSrvUse() || pModbus->GetPaHorNotUse()) || (!(((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0)))
        {
            ui->labelPaHorLen->setText(tr("软件行程"));
            ui->labelRaHorInt->setText(tr("软件行程"));
        }
        else
        {
            ui->labelPaHorLen->setText(GetServoName(AXIS_IDX_PHOR) + tr("和") +  GetServoName(AXIS_IDX_RHOR) + tr("原点距离"));
            ui->labelRaHorInt->setText(GetServoName(AXIS_IDX_PHOR) + tr("和") +  GetServoName(AXIS_IDX_RHOR) + tr("最小距离"));
        }
    }
#endif
}

// 根据当前用户权限设置界面
void Formservo::setPermissions(void)
{
	if (xPermissions::GetPermissions(PER_SRV_SAFE) == true)
	{
		// 用户具有第一页安全区域和第二页快速定位设置权限
        ui->radioSafe->setEnabled(true);
        ui->radioQuick->setEnabled(true);
	}
	else
	{
		// 用户没有第一页安全区域和第二页快速定位设置权限
        ui->radioSafe->setEnabled(false);
        ui->radioQuick->setEnabled(false);
    }
	if (xPermissions::GetPermissions(PER_SRV_MACHINE) == true)
	{
		// 用户具有伺服机械参数设置权限
        ui->radioPaHor->setEnabled(true);
        ui->radioPaVer->setEnabled(true);
        ui->radioTrv->setEnabled(true);
        ui->radioRaHor->setEnabled(true);
        ui->radioRaVer->setEnabled(true);
        ui->radioExt->setEnabled(true);
        ui->radioHome->setEnabled(true);
    }
	else
	{
		// 用户没有伺服机械参数设置权限
        ui->radioPaHor->setEnabled(false);
        ui->radioPaVer->setEnabled(false);
        ui->radioTrv->setEnabled(false);
        ui->radioRaHor->setEnabled(false);
        ui->radioRaVer->setEnabled(false);
        ui->radioExt->setEnabled(false);
        ui->radioHome->setEnabled(false);
    }
    if (xPermissions::GetCurrentUser() == xPermissions::SuperUser)
    {
        ui->labelPaHorType->setVisible(true);
        ui->labelPaHorPluses->setVisible(true);
//        ui->labelPaHorHomeWait->setVisible(true);
        ui->labelPaHorMod->setVisible(true);
        ui->checkBoxPHor->setVisible(true);
        ui->BoxPaHorPluses->setVisible(true);
//        ui->BoxPaHorHomeWait->setVisible(true);
        ui->BoxPaHorMod->setVisible(true);

        ui->labelPaVerType->setVisible(true);
        ui->labelPaVerPluses->setVisible(true);
//        ui->labelPaVerHomeWait->setVisible(true);
        ui->labelPaVerMod->setVisible(true);
        ui->checkBoxPVer->setVisible(true);
        ui->BoxPaVerPluses->setVisible(true);
//        ui->BoxPaVerHomeWait->setVisible(true);
        ui->BoxPaVerMod->setVisible(true);

        ui->labelRaHorType->setVisible(true);
        ui->labelRaHorPluses->setVisible(true);
//        ui->labelRaHorHomeWait->setVisible(true);
        ui->labelRaHorMod->setVisible(true);
        ui->checkBoxRHor->setVisible(true);
        ui->BoxRaHorPluses->setVisible(true);
//        ui->BoxRaHorHomeWait->setVisible(true);
        ui->BoxRaHorMod->setVisible(true);

        ui->labelRaVerType->setVisible(true);
        ui->labelRaVerPluses->setVisible(true);
//        ui->labelRaVerHomeWait->setVisible(true);
        ui->labelRaVerMod->setVisible(true);
        ui->checkBoxRVer->setVisible(true);
        ui->BoxRaVerPluses->setVisible(true);
//        ui->BoxRaVerHomeWait->setVisible(true);
        ui->BoxRaVerMod->setVisible(true);

        ui->labelTrvType->setVisible(true);
        ui->labelTrvPluses->setVisible(true);
//        ui->labelTrvHomeWait->setVisible(true);
        ui->labelTrvMod->setVisible(true);
        ui->checkBoxTrv->setVisible(true);
        ui->BoxTrvPluses->setVisible(true);
//        ui->BoxTrvHomeWait->setVisible(true);
        ui->BoxTrvMod->setVisible(true);

        ui->labelExtType->setVisible(true);
        ui->labelExtPluses->setVisible(true);
 //       ui->labelExtHomeWait->setVisible(true);
        ui->labelExtMod->setVisible(true);
        ui->checkBoxExt->setVisible(true);
        ui->BoxExtPluses->setVisible(true);
 //       ui->BoxExtHomeWait->setVisible(true);
        ui->BoxExtMod->setVisible(true);
    }
    else
    {
        ui->labelPaHorType->setVisible(false);
        ui->labelPaHorPluses->setVisible(false);
//        ui->labelPaHorHomeWait->setVisible(false);
        ui->labelPaHorMod->setVisible(false);
        ui->checkBoxPHor->setVisible(false);
        ui->BoxPaHorPluses->setVisible(false);
 //       ui->BoxPaHorHomeWait->setVisible(false);
        ui->BoxPaHorMod->setVisible(false);

        ui->labelPaVerType->setVisible(false);
        ui->labelPaVerPluses->setVisible(false);
//        ui->labelPaVerHomeWait->setVisible(false);
        ui->labelPaVerMod->setVisible(false);
        ui->checkBoxPVer->setVisible(false);
        ui->BoxPaVerPluses->setVisible(false);
 //       ui->BoxPaVerHomeWait->setVisible(false);
        ui->BoxPaVerMod->setVisible(false);

        ui->labelRaHorType->setVisible(false);
        ui->labelRaHorPluses->setVisible(false);
 //       ui->labelRaHorHomeWait->setVisible(false);
        ui->labelRaHorMod->setVisible(false);
        ui->checkBoxRHor->setVisible(false);
        ui->BoxRaHorPluses->setVisible(false);
 //       ui->BoxRaHorHomeWait->setVisible(false);
        ui->BoxRaHorMod->setVisible(false);

        ui->labelRaVerType->setVisible(false);
        ui->labelRaVerPluses->setVisible(false);
 //       ui->labelRaVerHomeWait->setVisible(false);
        ui->labelRaVerMod->setVisible(false);
        ui->checkBoxRVer->setVisible(false);
        ui->BoxRaVerPluses->setVisible(false);
 //       ui->BoxRaVerHomeWait->setVisible(false);
        ui->BoxRaVerMod->setVisible(false);

        ui->labelTrvType->setVisible(false);
        ui->labelTrvPluses->setVisible(false);
  //      ui->labelTrvHomeWait->setVisible(false);
        ui->labelTrvMod->setVisible(false);
        ui->checkBoxTrv->setVisible(false);
        ui->BoxTrvPluses->setVisible(false);
 //       ui->BoxTrvHomeWait->setVisible(false);
        ui->BoxTrvMod->setVisible(false);

        ui->labelExtType->setVisible(false);
        ui->labelExtPluses->setVisible(false);
//        ui->labelExtHomeWait->setVisible(false);
        ui->labelExtMod->setVisible(false);
        ui->checkBoxExt->setVisible(false);
        ui->BoxExtPluses->setVisible(false);
 //       ui->BoxExtHomeWait->setVisible(false);
        ui->BoxExtMod->setVisible(false);
    }
}

// 查询伺服参数设置
bool Formservo::QueryPara(void)
{
//	// 得到伺服参数设置
    int i;
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	trvRelPosBak = trvRelPos = settings.value(XPAD_SET_TRVRELPOS, 0).toUInt();
	trvCatPosBak = trvCatPos = settings.value(XPAD_SET_TRVCATPOS, 0).toUInt();
	trvWaitPosBak = trvWaitPos = settings.value(XPAD_SET_TRVWAIT, 0).toUInt();
	paVerCatPosBak = paVerCatPos = settings.value(XPAD_SET_PAVERCAT, 0).toUInt();
	paVerRelPosBak = paVerRelPos = settings.value(XPAD_SET_PAVERREL, 0).toUInt();
	paVerWaitPosBak = paVerWaitPos = settings.value(XPAD_SET_PAVERWAIT, 0).toUInt();
	paHorCatPosBak = paHorCatPos = settings.value(XPAD_SET_PAHORCAT, 0).toUInt();
	paHorRelPosBak = paHorRelPos = settings.value(XPAD_SET_PAHORREL, 0).toUInt();
	paHorWaitPosBak = paHorWaitPos = settings.value(XPAD_SET_PAHORWAIT, 0).toUInt();
	raVerCatPosBak = raVerCatPos = settings.value(XPAD_SET_RAVERCAT, 0).toUInt();
	raVerRelPosBak = raVerRelPos = settings.value(XPAD_SET_RAVERREL, 0).toUInt();
	raVerWaitPosBak = raVerWaitPos = settings.value(XPAD_SET_RAVERWAIT, 0).toUInt();
	raHorCatPosBak = raHorCatPos = settings.value(XPAD_SET_RAHORCAT, 0).toUInt();
	raHorRelPosBak = raHorRelPos = settings.value(XPAD_SET_RAHORREL, 0).toUInt();
	raHorWaitPosBak = raHorWaitPos = settings.value(XPAD_SET_RAHORWAIT, 0).toUInt();
	extCatPosBak = extCatPos = settings.value(XPAD_SET_EXTCAT, 0).toUInt();
	extRelPosBak = extRelPos = settings.value(XPAD_SET_EXTREL, 0).toUInt();
	extWaitPosBak = extWaitPos = settings.value(XPAD_SET_EXTWAIT, 0).toUInt();
	pModbus->GetServo(ServoPara);
	// 备份伺服参数设置
	memcpy(&ServoParaBak, &ServoPara, sizeof(ServoParameter));
	// 把伺服参数设置到界面
	// 引拔轴设置
    ui->BoxHorLen->setValue((double)ServoPara.m_machine_max_len_x / 100.00);
    ui->BoxHorInt->setValue((double)ServoPara.m_min_safe_dis_x_b / 100.00);
	// 最大软件行程
    ui->BoxPaVerSoftDist->setValue((double)ServoPara.m_software_max_len_y / 100.00);
    ui->BoxTrvSoftDist->setValue((double)ServoPara.m_software_max_len_z / 100.00);
    ui->BoxRaVerSoftDist->setValue((double)ServoPara.m_software_max_len_a / 100.00);
    ui->BoxExtSoftDist->setValue((double)ServoPara.m_software_max_len_c / 100.00);
	// 安全区域参数
    ui->BoxSafePaUp->setValue((double)ServoPara.m_max_wait_pos_inmold_y / 100.00);
    ui->BoxSafeRaUp->setValue((double)ServoPara.m_max_wait_pos_inmold_a / 100.00);
    ui->BoxSafePaHorS->setValue((double)ServoPara.m_min_safe_pos_inmold_x / 100.00);
    ui->BoxSafePaHorE->setValue((double)ServoPara.m_max_safe_pos_inmold_x / 100.00);
    ui->BoxSafeRaHorS->setValue((double)ServoPara.m_min_safe_pos_inmold_b / 100.00);
    ui->BoxSafeRaHorE->setValue((double)ServoPara.m_max_safe_pos_inmold_b / 100.00);
    ui->BoxTrvOutS->setValue((double)ServoPara.m_min_safe_pos_outmold_z / 100.00);
    ui->BoxTrvOutE->setValue((double)ServoPara.m_max_safe_pos_outmold_z / 100.00);
    ui->BoxTrvInS->setValue((double)ServoPara.m_min_safe_pos_inmold_z / 100.00);
    ui->BoxTrvInE->setValue((double)ServoPara.m_max_safe_pos_inmold_z / 100.00);
    ui->BoxTrvInS2->setValue((double)ServoPara.m_min_safe_pos_inmold_z_a / 100.00);
    ui->BoxTrvInE2->setValue((double)ServoPara.m_max_safe_pos_inmold_z_a / 100.00);
    ui->BoxTrvOutS2->setValue((double)ServoPara.m_min_safe_pos_outmold2_z / 100.00);
    ui->BoxTrvOutE2->setValue((double)ServoPara.m_max_safe_pos_outmold2_z / 100.00);
    ui->BoxSafeRotS->setValue((double)ServoPara.m_min_a_inmold /100.0);
    ui->BoxSafeRotE->setValue((double)ServoPara.m_max_a_inmold /100.0);
    ui->BoxSafeTrvS->setValue((double)ServoPara.m_min_a_trv /100.0);
    ui->BoxSafeTrvE->setValue((double)ServoPara.m_max_a_trv /100.0);
    ui->BoxTrvRel->setValue((double)trvRelPos / 100.00);
    ui->BoxTrvCat->setValue((double)trvCatPos / 100.00);
    ui->BoxTrvWait->setValue((double)trvWaitPos / 100.00);
    ui->BoxTrvWait2->setValue((double)trvWaitPos / 100.00);
    ui->BoxPaVerCat->setValue((double)paVerCatPos / 100.00);
    ui->BoxPaVerRel->setValue((double)paVerRelPos / 100.00);
    ui->BoxPaVerWait->setValue((double)paVerWaitPos / 100.00);
    ui->BoxPaHorCat->setValue((double)paHorCatPos / 100.00);
    ui->BoxPaHorRel->setValue((double)paHorRelPos / 100.00);
    ui->BoxPaHorWait->setValue((double)paHorWaitPos / 100.00);
    ui->BoxRaHorCat->setValue((double)raHorCatPos / 100.00);
    ui->BoxRaHorRel->setValue((double)raHorRelPos / 100.00);
    ui->BoxRaHorWait->setValue((double)raHorWaitPos / 100.00);
    ui->BoxRaVerCat->setValue((double)raVerCatPos / 100.00);
    ui->BoxRaVerRel->setValue((double)raVerRelPos / 100.00);
    ui->BoxRaVerWait->setValue((double)raVerWaitPos / 100.00);
    ui->BoxExtCat->setValue((double)extCatPos / 100.00);
    ui->BoxExtRel->setValue((double)extRelPos / 100.00);
    ui->BoxExtWait->setValue((double)extWaitPos / 100.00);
    ui->BoxSafeRHorS->setValue((double)ServoPara.m_min_b_trave / 100.00);
    ui->BoxSafeRHorE->setValue((double)ServoPara.m_max_b_trave / 100.00);
    ui->BoxSafeExtMoldS->setValue((double)ServoPara.m_min_c_inmold / 100.00);
    ui->BoxSafeExtMoldE->setValue((double)ServoPara.m_max_c_inmold / 100.00);
    ui->BoxSafeExtS->setValue((double)ServoPara.m_min_c_trave / 100.00);
    ui->BoxSafeExtE->setValue((double)ServoPara.m_max_c_trave / 100.00);
    ui->BoxSafePHorS->setValue((double)ServoPara.m_min_x_trave / 100.00);
    ui->BoxSafePHorE->setValue((double)ServoPara.m_max_x_trave / 100.00);
    // 伺服速度和加速度
	ui->BoxPaHorSpeed->setValue(ServoPara.m_xmax_speed);
    ui->l_MaxR_PaHor->setText(QString::number(ServoPara.m_xmax_speed*3000/100));
	ui->BoxPaHorAcc->setValue(ServoPara.m_xmax_acceleration);

	ui->BoxPaVerSpeed->setValue(ServoPara.m_ymax_speed);
    ui->l_MaxR_PaVer->setText(QString::number(ServoPara.m_ymax_speed*3000/100));
	ui->BoxPaVerAcc->setValue(ServoPara.m_ymax_acceleration);

	ui->BoxTrvSpeed->setValue(ServoPara.m_zmax_speed);
    ui->l_MaxR_Trv->setText(QString::number(ServoPara.m_zmax_speed*3000/100));
	ui->BoxTrvAcc->setValue(ServoPara.m_zmax_acceleration);

	ui->BoxRaHorSpeed->setValue(ServoPara.m_bmax_speed);
    ui->l_MaxR_RaHor->setText(QString::number(ServoPara.m_bmax_speed*3000/100));
	ui->BoxRaHorAcc->setValue(ServoPara.m_bmax_acceleration);

	ui->BoxRaVerSpeed->setValue(ServoPara.m_amax_speed);
    ui->l_MaxR_RaVer->setText(QString::number(ServoPara.m_amax_speed*3000/100));
	ui->BoxRaVerAcc->setValue(ServoPara.m_amax_acceleration);

    ui->BoxExtSpeed->setValue(ServoPara.m_cmax_speed);
    ui->l_MaxR_Ext->setText(QString::number(ServoPara.m_cmax_speed*3000/100));
    ui->BoxExtAcc->setValue(ServoPara.m_cmax_acceleration);

    // 马达转动一圈距离和脉冲数
    ui->BoxPaHorUnits->setValue(ServoPara.m_x_units);
    ui->BoxPaHorPluses->setValue(ServoPara.m_x_pluses);
    ui->BoxPaVerUnits->setValue(ServoPara.m_y_units);
    ui->BoxPaVerPluses->setValue(ServoPara.m_y_pluses);
    ui->BoxTrvUnits->setValue(ServoPara.m_z_units);
    ui->BoxTrvPluses->setValue(ServoPara.m_z_pluses);
    ui->BoxRaHorUnits->setValue(ServoPara.m_b_units);
    ui->BoxRaHorPluses->setValue(ServoPara.m_b_pluses);
    ui->BoxRaVerUnits->setValue(ServoPara.m_a_units);
    ui->BoxRaVerPluses->setValue(ServoPara.m_a_pluses);
    ui->BoxExtUnits->setValue(ServoPara.m_c_units);
    ui->BoxExtPluses->setValue(ServoPara.m_c_pluses);
    // 原点偏移
    ui->BoxPaHorOffset->setValue((double)ServoPara.m_origin_offset_x / 100.00);
    ui->BoxPaVerOffset->setValue((double)ServoPara.m_origin_offset_y / 100.00);
    ui->BoxTrvOffset->setValue((double)ServoPara.m_origin_offset_z / 100.00);
    ui->BoxRaVerOffset->setValue((double)ServoPara.m_origin_offset_a / 100.00);
    ui->BoxRaHorOffset->setValue((double)ServoPara.m_origin_offset_b / 100.00);
    ui->BoxExtOffset->setValue((double)ServoPara.m_origin_offset_c / 100.00);
    // 原点待机点
    ui->BoxPaHorHomeWait->setValue((double)ServoPara.m_home_pos_x / 100.00);
    ui->BoxPaVerHomeWait->setValue((double)ServoPara.m_home_pos_y / 100.00);
    ui->BoxTrvHomeWait->setValue((double)ServoPara.m_home_pos_z / 100.00);
    ui->BoxRaHorHomeWait->setValue((double)ServoPara.m_home_pos_b / 100.00);
    ui->BoxRaVerHomeWait->setValue((double)ServoPara.m_home_pos_a / 100.00);
    ui->BoxExtHomeWait->setValue((double)ServoPara.m_home_pos_c / 100.00);
    // 模
    ui->BoxPaHorMod->setValue((double)ServoPara.m_mod_x / 100.00);
    ui->BoxPaVerMod->setValue((double)ServoPara.m_mod_y / 100.00);
    ui->BoxTrvMod->setValue((double)ServoPara.m_mod_z / 100.00);
    ui->BoxRaHorMod->setValue((double)ServoPara.m_mod_b / 100.00);
    ui->BoxRaVerMod->setValue((double)ServoPara.m_mod_a / 100.00);
    ui->BoxExtMod->setValue((double)ServoPara.m_mod_c / 100.00);
    // 编码器类型
    if(pModbus->GetSysTypeHigh() == BOARD_VERSION_ECAT)
    {
        ui->checkBoxPHorAbsolute->setChecked(ServoPara.m_encoder_x != 0);
        ui->checkBoxPVerAbsolute->setChecked(ServoPara.m_encoder_y != 0);
        ui->checkBoxTrvAbsolute->setChecked(ServoPara.m_encoder_z != 0);
        ui->checkBoxRHorAbsolute->setChecked(ServoPara.m_encoder_b != 0);
        ui->checkBoxRVerAbsolute->setChecked(ServoPara.m_encoder_a != 0);
        ui->checkBoxExtAbsolute->setChecked(ServoPara.m_encoder_c != 0);
    }
    else
    {
    ui->cBoxPaHorEncoder->setCurrentIndex((quint8)ServoPara.m_encoder_x);
    ui->cBoxPaVerEncoder->setCurrentIndex((quint8)ServoPara.m_encoder_y);
    ui->cBoxTrvEncoder->setCurrentIndex((quint8)ServoPara.m_encoder_z);
    ui->cBoxRaHorEncoder->setCurrentIndex((quint8)ServoPara.m_encoder_b);
    ui->cBoxRaVerEncoder->setCurrentIndex((quint8)ServoPara.m_encoder_a);
    ui->cBoxExtEncoder->setCurrentIndex((quint8)ServoPara.m_encoder_c);
    ui->BoxPaHorAddr->setValue(ServoPara.m_encoder_x >> 8);
    ui->BoxPaVerAddr->setValue(ServoPara.m_encoder_y >> 8);
    ui->BoxTrvAddr->setValue(ServoPara.m_encoder_z >> 8);
    ui->BoxRaHorAddr->setValue(ServoPara.m_encoder_b >> 8);
    ui->BoxRaVerAddr->setValue(ServoPara.m_encoder_a >> 8);
    ui->BoxExtAddr->setValue(ServoPara.m_encoder_c >> 8);
    }
    // JERK加加速
    ui->BoxPaHorJerk->setValue(ServoPara.m_xmax_jerk);
    ui->BoxPaVerJerk->setValue(ServoPara.m_ymax_jerk);
    ui->BoxTrvJerk->setValue(ServoPara.m_zmax_jerk);
    ui->BoxRaVerJerk->setValue(ServoPara.m_amax_jerk);
    ui->BoxRaHorJerk->setValue(ServoPara.m_bmax_jerk);
    ui->BoxExtJerk->setValue(ServoPara.m_cmax_jerk);

    ui->BoxHomeSpeed->setValue(ServoPara.m_home_vel);
    ui->BoxHomeSpeedSlow->setValue(ServoPara.m_home_vel_slow);
    // 轴类型
    for (i = 0; i < MAX_AXIS_NUM; i++)
    {
        GetAngleType(i);
        GetHomeType(i);
        GetDecType(i);
    }
    if(CMBProtocol::GetPaHorNotUse()) showSVDevPara(AXES_IDX_Y);
    else showSVDevPara(AXES_IDX_X);
    return true;
}
// 得到指定伺服轴的当前软件行程
void Formservo::GetDistance(quint32 &Pver, quint32 &Rver, quint32 &trv, quint32 &ext, quint32 &disHomP_R, quint32 &MinDisP_R)
{
    if ((ui->radioPaVer->isChecked()) && (ui->stackedWidget->currentIndex() == SRVPG_PAVER))
        Pver = MAX_DISTANCE;
    else
        Pver = qRound(ui->BoxPaVerSoftDist->value()*100.00);
    if ((ui->radioRaVer->isChecked()) && (ui->stackedWidget->currentIndex() == SRVPG_RAVER))
        Rver = MAX_DISTANCE;
    else
        Rver = qRound(ui->BoxRaVerSoftDist->value()*100.00);
    if ((ui->radioTrv->isChecked()) && (ui->stackedWidget->currentIndex() == SRVPG_TRAVEL))
        trv = MAX_DISTANCE;
    else
        trv = qRound(ui->BoxTrvSoftDist->value()*100.00);
    if ((ui->radioExt->isChecked()) && (ui->stackedWidget->currentIndex() == SRVPG_EXTEND))
        ext = MAX_DISTANCE;
    else
        ext = qRound(ui->BoxExtSoftDist->value()*100.00);

/*
    if(!pModbus->GetRhorSrvUse())
    {
        disHomP_R = MAX_DISTANCE;
        MinDisP_R = 0;
    }
    else
    {
        if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        {
            if ((ui->radioPaHor->isChecked()) && (ui->stackedWidget->currentIndex() == SRVPG_PAHOR))
                disHomP_R = MAX_DISTANCE;
            else
                disHomP_R = qRound(ui->BoxHorLen->value()*100.00);
            if ((ui->radioRaHor->isChecked()) && (ui->stackedWidget->currentIndex() == SRVPG_RAHOR))
                MinDisP_R = MAX_DISTANCE;
            else
                MinDisP_R = qRound(ui->BoxHorInt->value()*100.00);
        }
        else
        {
            disHomP_R = qRound(ui->BoxHorLen->value()*100.00);	// 正臂和副臂原点距离
            MinDisP_R = qRound(ui->BoxHorInt->value()*100.00);	// 正臂和副臂最小间距
        }
    }
*/
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if ((ui->radioPaHor->isChecked()) && (ui->stackedWidget->currentIndex() == SRVPG_PAHOR))
            disHomP_R = MAX_DISTANCE;
        else
            disHomP_R = qRound(ui->BoxHorLen->value()*100.00);
        if ((ui->radioRaHor->isChecked()) && (ui->stackedWidget->currentIndex() == SRVPG_RAHOR))
            MinDisP_R = MAX_DISTANCE;
        else
            MinDisP_R = qRound(ui->BoxHorInt->value()*100.00);
    }
    else
    {
        if(!pModbus->GetRhorSrvUse())
        {
            disHomP_R = MAX_DISTANCE;
            MinDisP_R = 0;
        }
        else
        {
            disHomP_R = qRound(ui->BoxHorLen->value()*100.00);	// 正臂和副臂原点距离
            MinDisP_R = qRound(ui->BoxHorInt->value()*100.00);	// 正臂和副臂最小间距
        }
    }
}
// 从界面得到伺服参数设置
void Formservo::LoadPara(void)
{
    int i;
	if (xPermissions::GetPermissions(PER_SRV_SAFE) == true)
	{
		// 安全区域参数
        ServoPara.m_max_wait_pos_inmold_y = qRound(ui->BoxSafePaUp->value() * 100.00);
        ServoPara.m_max_wait_pos_inmold_a = qRound(ui->BoxSafeRaUp->value() * 100.00);
        ServoPara.m_min_safe_pos_inmold_x = qRound(ui->BoxSafePaHorS->value() * 100.00);
        ServoPara.m_max_safe_pos_inmold_x = qRound(ui->BoxSafePaHorE->value() * 100.00);
        ServoPara.m_min_safe_pos_inmold_b = qRound(ui->BoxSafeRaHorS->value() * 100.00);
        ServoPara.m_max_safe_pos_inmold_b = qRound(ui->BoxSafeRaHorE->value() * 100.00);
		ServoPara.m_min_a_inmold = qRound(ui->BoxSafeRotS->value() * 100.00);
		ServoPara.m_max_a_inmold = qRound(ui->BoxSafeRotE->value() * 100.00);
		ServoPara.m_min_a_trv = qRound(ui->BoxSafeTrvS->value() * 100.00);
		ServoPara.m_max_a_trv = qRound(ui->BoxSafeTrvE->value() * 100.00);
        ServoPara.m_min_safe_pos_outmold_z = qRound(ui->BoxTrvOutS->value() * 100.00);
        ServoPara.m_max_safe_pos_outmold_z = qRound(ui->BoxTrvOutE->value() * 100.00);
        ServoPara.m_min_safe_pos_inmold_z = qRound(ui->BoxTrvInS->value() * 100.00);
        ServoPara.m_max_safe_pos_inmold_z = qRound(ui->BoxTrvInE->value() * 100.00);
        ServoPara.m_min_safe_pos_outmold2_z = qRound(ui->BoxTrvOutS2->value() * 100.00);
        ServoPara.m_max_safe_pos_outmold2_z = qRound(ui->BoxTrvOutE2->value() * 100.00);
        ServoPara.m_min_safe_pos_inmold_z_a = qRound(ui->BoxTrvInS2->value() * 100.00);
        ServoPara.m_max_safe_pos_inmold_z_a = qRound(ui->BoxTrvInE2->value() * 100.00);
        ServoPara.m_min_b_trave = qRound(ui->BoxSafeRHorS->value() * 100.00);
        ServoPara.m_max_b_trave = qRound(ui->BoxSafeRHorE->value() * 100.00);
        ServoPara.m_min_c_trave = qRound(ui->BoxSafeExtS->value() * 100.00);
        ServoPara.m_max_c_trave = qRound(ui->BoxSafeExtE->value() * 100.00);
        ServoPara.m_min_c_inmold = qRound(ui->BoxSafeExtMoldS->value() * 100.00);
        ServoPara.m_max_c_inmold = qRound(ui->BoxSafeExtMoldE->value() * 100.00);
        ServoPara.m_min_x_trave = qRound(ui->BoxSafePHorS->value() * 100.00);
        ServoPara.m_max_x_trave = qRound(ui->BoxSafePHorE->value() * 100.00);

        trvRelPos = qRound(ui->BoxTrvRel->value() * 100.00);
        trvCatPos = qRound(ui->BoxTrvCat->value() * 100.00);
        trvWaitPos = qRound(ui->BoxTrvWait->value() * 100.00);
        trvWaitPos = qRound(ui->BoxTrvWait2->value() * 100.00);
        paVerCatPos = qRound(ui->BoxPaVerCat->value() * 100.00);
        paVerRelPos = qRound(ui->BoxPaVerRel->value() * 100.00);
        paVerWaitPos = qRound(ui->BoxPaVerWait->value() * 100.00);
        paHorCatPos = qRound(ui->BoxPaHorCat->value() * 100.00);
        paHorRelPos = qRound(ui->BoxPaHorRel->value() * 100.00);
        paHorWaitPos = qRound(ui->BoxPaHorWait->value() * 100.00);
        raHorCatPos = qRound(ui->BoxRaHorCat->value() * 100.00);
        raHorRelPos = qRound(ui->BoxRaHorRel->value() * 100.00);
        raHorWaitPos = qRound(ui->BoxRaHorWait->value() * 100.00);
        raVerCatPos = qRound(ui->BoxRaVerCat->value() * 100.00);
        raVerRelPos = qRound(ui->BoxRaVerRel->value() * 100.00);
        raVerWaitPos = qRound(ui->BoxRaVerWait->value() * 100.00);
        extCatPos = qRound(ui->BoxExtCat->value() * 100.00);
        extRelPos = qRound(ui->BoxExtRel->value() * 100.00);
        extWaitPos = qRound(ui->BoxExtWait->value() * 100.00);
	}
	if (xPermissions::GetPermissions(PER_SRV_MACHINE) == true)
	{
		// 引拔轴设置
        ServoPara.m_machine_max_len_x = qRound(ui->BoxHorLen->value() * 100.00);
        ServoPara.m_min_safe_dis_x_b = qRound(ui->BoxHorInt->value() * 100.00);
		// 最大软件行程
        ServoPara.m_software_max_len_y = qRound(ui->BoxPaVerSoftDist->value() * 100.00);
        ServoPara.m_software_max_len_z = qRound(ui->BoxTrvSoftDist->value() * 100.00);
        ServoPara.m_software_max_len_a = qRound(ui->BoxRaVerSoftDist->value() * 100.00);
        ServoPara.m_software_max_len_c = qRound(ui->BoxExtSoftDist->value() * 100.00);
		// 伺服速度和加速度
		ServoPara.m_xmax_speed = ui->BoxPaHorSpeed->value();
		ServoPara.m_xmax_acceleration = ui->BoxPaHorAcc->value();
		ServoPara.m_ymax_speed = ui->BoxPaVerSpeed->value();
		ServoPara.m_ymax_acceleration = ui->BoxPaVerAcc->value();
		ServoPara.m_zmax_speed = ui->BoxTrvSpeed->value();
		ServoPara.m_zmax_acceleration = ui->BoxTrvAcc->value();
		ServoPara.m_bmax_speed = ui->BoxRaHorSpeed->value();
		ServoPara.m_bmax_acceleration = ui->BoxRaHorAcc->value();
		ServoPara.m_amax_speed = ui->BoxRaVerSpeed->value();
		ServoPara.m_amax_acceleration = ui->BoxRaVerAcc->value();
        ServoPara.m_cmax_speed = ui->BoxExtSpeed->value();
        ServoPara.m_cmax_acceleration = ui->BoxExtAcc->value();
        // 马达转动一圈距离和脉冲数
        ServoPara.m_x_units = ui->BoxPaHorUnits->value();
        ServoPara.m_x_pluses = ui->BoxPaHorPluses->value();
        ServoPara.m_y_units = ui->BoxPaVerUnits->value();
        ServoPara.m_y_pluses = ui->BoxPaVerPluses->value();
        ServoPara.m_z_units = ui->BoxTrvUnits->value();
        ServoPara.m_z_pluses = ui->BoxTrvPluses->value();
        ServoPara.m_b_units = ui->BoxRaHorUnits->value();
        ServoPara.m_b_pluses = ui->BoxRaHorPluses->value();
        ServoPara.m_a_units = ui->BoxRaVerUnits->value();
        ServoPara.m_a_pluses = ui->BoxRaVerPluses->value();
        ServoPara.m_c_units = ui->BoxExtUnits->value();
        ServoPara.m_c_pluses = ui->BoxExtPluses->value();
        // 原点偏移
        ServoPara.m_origin_offset_x = qRound(ui->BoxPaHorOffset->value() * 100.00);
        ServoPara.m_origin_offset_y = qRound(ui->BoxPaVerOffset->value() * 100.00);
        ServoPara.m_origin_offset_z = qRound(ui->BoxTrvOffset->value() * 100.00);
        ServoPara.m_origin_offset_a = qRound(ui->BoxRaVerOffset->value() * 100.00);
        ServoPara.m_origin_offset_b = qRound(ui->BoxRaHorOffset->value() * 100.00);
        ServoPara.m_origin_offset_c = qRound(ui->BoxExtOffset->value() * 100.00);
        // 原点待机点
        ServoPara.m_home_pos_x = qRound(ui->BoxPaHorHomeWait->value() * 100.00);
        ServoPara.m_home_pos_y = qRound(ui->BoxPaVerHomeWait->value() * 100.00);
        ServoPara.m_home_pos_z = qRound(ui->BoxTrvHomeWait->value() * 100.00);
        ServoPara.m_home_pos_a = qRound(ui->BoxRaVerHomeWait->value() * 100.00);
        ServoPara.m_home_pos_b = qRound(ui->BoxRaHorHomeWait->value() * 100.00);
        ServoPara.m_home_pos_c = qRound(ui->BoxExtHomeWait->value() * 100.00);
        // 模
        ServoPara.m_mod_x = qRound(ui->BoxPaHorMod->value() * 100.00);
        ServoPara.m_mod_y = qRound(ui->BoxPaVerMod->value() * 100.00);
        ServoPara.m_mod_z = qRound(ui->BoxTrvMod->value() * 100.00);
        ServoPara.m_mod_a = qRound(ui->BoxRaVerMod->value() * 100.00);
        ServoPara.m_mod_b = qRound(ui->BoxRaHorMod->value() * 100.00);
        ServoPara.m_mod_c = qRound(ui->BoxExtMod->value() * 100.00);

        // 编码器
        if(pModbus->GetSysTypeHigh() == BOARD_VERSION_ECAT)
        {
            ServoPara.m_encoder_x = ui->checkBoxPHorAbsolute->isChecked()? 1:0;
            ServoPara.m_encoder_y = ui->checkBoxPVerAbsolute->isChecked()? 1:0;
            ServoPara.m_encoder_z = ui->checkBoxTrvAbsolute->isChecked()? 1:0;
            ServoPara.m_encoder_a = ui->checkBoxRHorAbsolute->isChecked()? 1:0;
            ServoPara.m_encoder_b = ui->checkBoxRVerAbsolute->isChecked()? 1:0;
            ServoPara.m_encoder_c = ui->checkBoxExtAbsolute->isChecked()? 1:0;
        }
        else
        {
        ServoPara.m_encoder_x = ui->cBoxPaHorEncoder->currentIndex() | (quint16)ui->BoxPaHorAddr->value() << 8;
        ServoPara.m_encoder_y = ui->cBoxPaVerEncoder->currentIndex() | (quint16)ui->BoxPaVerAddr->value() << 8;
        ServoPara.m_encoder_z = ui->cBoxTrvEncoder->currentIndex() | (quint16)ui->BoxTrvAddr->value() << 8;
        ServoPara.m_encoder_a = ui->cBoxRaVerEncoder->currentIndex() | (quint16)ui->BoxRaVerAddr->value() << 8;
        ServoPara.m_encoder_b = ui->cBoxRaHorEncoder->currentIndex() | (quint16)ui->BoxRaHorAddr->value() << 8;
        ServoPara.m_encoder_c = ui->cBoxExtEncoder->currentIndex() | (quint16)ui->BoxExtAddr->value() << 8;
        }

        // JERK加加速
        ServoPara.m_xmax_jerk = ui->BoxPaHorJerk->value();
        ServoPara.m_ymax_jerk = ui->BoxPaVerJerk->value();
        ServoPara.m_zmax_jerk = ui->BoxTrvJerk->value();
        ServoPara.m_amax_jerk = ui->BoxRaVerJerk->value();
        ServoPara.m_bmax_jerk = ui->BoxRaHorJerk->value();
        ServoPara.m_cmax_jerk = ui->BoxExtJerk->value();

        // 轴类型
        for (i = 0; i < MAX_AXIS_NUM; i++)
        {
            SetAngleType(i);
            SetHomeType(i);
            SetDecType(i);
        }
        ServoPara.m_home_vel = ui->BoxHomeSpeed->value();
        ServoPara.m_home_vel_slow = ui->BoxHomeSpeedSlow->value();

        LoadSvDevPara(pRBtnSVDev->checkedId());
    }
}

// 检查参数是否修改
bool Formservo::isModified(void)
{
	parModify = 0;
	if (xPermissions::GetPermissions(PER_SRV_SAFE) == true)
	{
		// 安全区域参数
		if (ServoPara.m_max_wait_pos_inmold_y != ServoParaBak.m_max_wait_pos_inmold_y)		parModify |= ((quint64)1 << LOG_MAX_WAIT_POS_INMOLD_Y);
		if (ServoPara.m_max_wait_pos_inmold_a != ServoParaBak.m_max_wait_pos_inmold_a)		parModify |= ((quint64)1 << LOG_MAX_WAIT_POS_INMOLD_A);
		if (ServoPara.m_min_safe_pos_inmold_x != ServoParaBak.m_min_safe_pos_inmold_x)		parModify |= ((quint64)1 << LOG_MIN_SAFE_POS_INMOLD_X);
		if (ServoPara.m_max_safe_pos_inmold_x != ServoParaBak.m_max_safe_pos_inmold_x)		parModify |= ((quint64)1 << LOG_MAX_SAFE_POS_INMOLD_X);
		if (ServoPara.m_min_safe_pos_inmold_b != ServoParaBak.m_min_safe_pos_inmold_b)		parModify |= ((quint64)1 << LOG_MIN_SAFE_POS_INMOLD_B);
		if (ServoPara.m_max_safe_pos_inmold_b != ServoParaBak.m_max_safe_pos_inmold_b)		parModify |= ((quint64)1 << LOG_MAX_SAFE_POS_INMOLD_B);
        if (ServoPara.m_min_safe_pos_outmold_z != ServoParaBak.m_min_safe_pos_outmold_z)	parModify |= ((quint64)1 << LOG_MIN_SAFE_POS_OUTMOLD_Z);
        if (ServoPara.m_max_safe_pos_outmold_z != ServoParaBak.m_max_safe_pos_outmold_z)	parModify |= ((quint64)1 << LOG_MAX_SAFE_POS_OUTMOLD_Z);
        if (ServoPara.m_min_safe_pos_inmold_z != ServoParaBak.m_min_safe_pos_inmold_z)		parModify |= ((quint64)1 << LOG_MIN_SAFE_POS_INMOLD_Z);
        if (ServoPara.m_max_safe_pos_inmold_z != ServoParaBak.m_max_safe_pos_inmold_z)		parModify |= ((quint64)1 << LOG_MAX_SAFE_POS_INMOLD_Z);
        if (ServoPara.m_min_safe_pos_outmold2_z != ServoParaBak.m_min_safe_pos_outmold2_z)	return true;
        if (ServoPara.m_max_safe_pos_outmold2_z != ServoParaBak.m_max_safe_pos_outmold2_z)	return true;
        if (ServoPara.m_min_a_inmold != ServoParaBak.m_min_a_inmold)		parModify |= ((quint64)1 << LOG_MIN_SAFE_ROT);
        if (ServoPara.m_max_a_inmold != ServoParaBak.m_max_a_inmold)		parModify |= ((quint64)1 << LOG_MAX_SAFE_ROT);
        if (ServoPara.m_min_a_trv != ServoParaBak.m_min_a_trv)              parModify |= ((quint64)1 << LOG_MIN_SAFE_TRV);
        if (ServoPara.m_max_a_trv != ServoParaBak.m_max_a_trv)              parModify |= ((quint64)1 << LOG_MAX_SAFE_TRV);
        if (ServoPara.m_min_safe_pos_inmold_z_a != ServoParaBak.m_min_safe_pos_inmold_z_a)	return true;
        if (ServoPara.m_max_safe_pos_inmold_z_a != ServoParaBak.m_max_safe_pos_inmold_z_a)	return true;

        if (ServoPara.m_min_b_trave != ServoParaBak.m_min_b_trave)                          return true;
        if (ServoPara.m_max_b_trave != ServoParaBak.m_max_b_trave)                          return true;
        if (ServoPara.m_min_c_trave != ServoParaBak.m_min_c_trave)                          return true;
        if (ServoPara.m_max_c_trave != ServoParaBak.m_max_c_trave)                          return true;
        if (ServoPara.m_min_c_inmold != ServoParaBak.m_min_c_inmold)                        return true;
        if (ServoPara.m_max_c_inmold != ServoParaBak.m_max_c_inmold)                        return true;
        if (ServoPara.m_min_x_trave != ServoParaBak.m_min_x_trave)                          return true;
        if (ServoPara.m_max_x_trave != ServoParaBak.m_max_x_trave)                          return true;

		if (trvRelPos != trvRelPosBak)														return true;
		if (trvCatPos != trvCatPosBak)														return true;
		if (trvWaitPos != trvWaitPosBak)													return true;
		if (paVerCatPos != paVerCatPosBak)													return true;
		if (paVerRelPos != paVerRelPosBak)													return true;
		if (paVerWaitPos != paVerWaitPosBak)												return true;
		if (paHorCatPos != paHorCatPosBak)													return true;
		if (paHorRelPos != paHorRelPosBak)													return true;
		if (paHorWaitPos != paHorWaitPosBak)												return true;
		if (raVerCatPos != raVerCatPosBak)													return true;
		if (raVerRelPos != raVerRelPosBak)													return true;
		if (raVerWaitPos != raVerWaitPosBak)												return true;
		if (raHorCatPos != raHorCatPosBak)													return true;
		if (raHorRelPos != raHorRelPosBak)													return true;
		if (raHorWaitPos != raHorWaitPosBak)												return true;
		if (extCatPos != extCatPosBak)														return true;
		if (extRelPos != extRelPosBak)														return true;
		if (extWaitPos != extWaitPosBak)													return true;
	}
	if (xPermissions::GetPermissions(PER_SRV_MACHINE) == true)
	{
		// 引拔轴设置
		if (ServoPara.m_machine_max_len_x != ServoParaBak.m_machine_max_len_x)				parModify |= ((quint64)1 << LOG_MACHINE_MAX_LEN_X);
		if (ServoPara.m_min_safe_dis_x_b != ServoParaBak.m_min_safe_dis_x_b)				parModify |= ((quint64)1 << LOG_MIN_SAFE_DIS_X_B);
		// 最大软件行程
		if (ServoPara.m_software_max_len_y != ServoParaBak.m_software_max_len_y)			parModify |= ((quint64)1 << LOG_SOFTWARE_MAX_LEN_Y);
		if (ServoPara.m_software_max_len_z != ServoParaBak.m_software_max_len_z)			parModify |= ((quint64)1 << LOG_SOFTWARE_MAX_LEN_Z);
		if (ServoPara.m_software_max_len_a != ServoParaBak.m_software_max_len_a)			parModify |= ((quint64)1 << LOG_SOFTWARE_MAX_LEN_A);
		if (ServoPara.m_software_max_len_c != ServoParaBak.m_software_max_len_c)			parModify |= ((quint64)1 << LOG_SOFTWARE_MAX_LEN_C);
		// 伺服速度和加速度
        if (pModbus->GetFunctions(SUB_FUN2_JERK))
        {
            if (ServoPara.m_xmax_jerk != ServoParaBak.m_xmax_jerk)                          return true;
            if (ServoPara.m_ymax_jerk != ServoParaBak.m_ymax_jerk)                          return true;
            if (ServoPara.m_zmax_jerk != ServoParaBak.m_zmax_jerk)                          return true;
            if (ServoPara.m_amax_jerk != ServoParaBak.m_amax_jerk)                          return true;
            if (ServoPara.m_bmax_jerk != ServoParaBak.m_bmax_jerk)                          return true;
            if (ServoPara.m_cmax_jerk != ServoParaBak.m_cmax_jerk)                          return true;
        }
		if (ServoPara.m_xmax_speed != ServoParaBak.m_xmax_speed)							parModify |= ((quint64)1 << LOG_XMAX_SPEED);
		if (ServoPara.m_xmax_acceleration != ServoParaBak.m_xmax_acceleration)				parModify |= ((quint64)1 << LOG_XMAX_ACCELERATION);
		if (ServoPara.m_ymax_speed != ServoParaBak.m_ymax_speed)							parModify |= ((quint64)1 << LOG_YMAX_SPEED);
		if (ServoPara.m_ymax_acceleration != ServoParaBak.m_ymax_acceleration)				parModify |= ((quint64)1 << LOG_YMAX_ACCELERATION);
		if (ServoPara.m_zmax_speed != ServoParaBak.m_zmax_speed)							parModify |= ((quint64)1 << LOG_ZMAX_SPEED);
		if (ServoPara.m_zmax_acceleration != ServoParaBak.m_zmax_acceleration)				parModify |= ((quint64)1 << LOG_ZMAX_ACCELERATION);
		if (ServoPara.m_amax_speed != ServoParaBak.m_amax_speed)							parModify |= ((quint64)1 << LOG_AMAX_SPEED);
		if (ServoPara.m_amax_acceleration != ServoParaBak.m_amax_acceleration)				parModify |= ((quint64)1 << LOG_AMAX_ACCELERATION);
		if (ServoPara.m_bmax_speed != ServoParaBak.m_bmax_speed)							parModify |= ((quint64)1 << LOG_BMAX_SPEED);
		if (ServoPara.m_bmax_acceleration != ServoParaBak.m_bmax_acceleration)				parModify |= ((quint64)1 << LOG_BMAX_ACCELERATION);
		if (ServoPara.m_cmax_speed != ServoParaBak.m_cmax_speed)							parModify |= ((quint64)1 << LOG_CMAX_SPEED);
		if (ServoPara.m_cmax_acceleration != ServoParaBak.m_cmax_acceleration)				parModify |= ((quint64)1 << LOG_CMAX_ACCELERATION);
        // 马达转动一圈距离和脉冲数
        if (ServoPara.m_x_units != ServoParaBak.m_x_units)                                  parModify |= ((quint64)1 << LOG_X_UNITS);
        if (ServoPara.m_x_pluses != ServoParaBak.m_x_pluses)                                parModify |= ((quint64)1 << LOG_X_PLUSES);
        if (ServoPara.m_y_units != ServoParaBak.m_y_units)                                  parModify |= ((quint64)1 << LOG_Y_UNITS);
        if (ServoPara.m_y_pluses != ServoParaBak.m_y_pluses)                                parModify |= ((quint64)1 << LOG_Y_PLUSES);
        if (ServoPara.m_z_units != ServoParaBak.m_z_units)                                  parModify |= ((quint64)1 << LOG_Z_UNITS);
        if (ServoPara.m_z_pluses != ServoParaBak.m_z_pluses)                                parModify |= ((quint64)1 << LOG_Z_PLUSES);
        if (ServoPara.m_b_units != ServoParaBak.m_b_units)                                  parModify |= ((quint64)1 << LOG_B_UNITS);
        if (ServoPara.m_b_pluses != ServoParaBak.m_b_pluses)                                parModify |= ((quint64)1 << LOG_B_PLUSES);
        if (ServoPara.m_a_units != ServoParaBak.m_a_units)                                  parModify |= ((quint64)1 << LOG_A_UNITS);
        if (ServoPara.m_a_pluses != ServoParaBak.m_a_pluses)                                parModify |= ((quint64)1 << LOG_A_PLUSES);
        if (ServoPara.m_c_units != ServoParaBak.m_c_units)                                  parModify |= ((quint64)1 << LOG_C_UNITS);
        if (ServoPara.m_c_pluses != ServoParaBak.m_c_pluses)                                parModify |= ((quint64)1 << LOG_C_PLUSES);
        // 轴类型
        if (ServoPara.m_angle_type != ServoParaBak.m_angle_type)                              parModify |= ((quint64)1 << LOG_ANGLE_BMP);
//        if (pModbus->GetFunctions(SUB_FUN_TMC429))
        {
        if (ServoPara.m_dec_type != ServoParaBak.m_dec_type)                                parModify |= ((quint64)1 << LOG_RAMP_BMP);
        }
        // 原点归位模式
//        if (pModbus->GetFunctions(SUB_IN_ANTI_CHECK_HOME_TAIL_LOOP_FREE))
        {
        if (ServoPara.m_home_mode != ServoParaBak.m_home_mode)                              parModify |= ((quint64)1 << LOG_HOME_MODE);
        }
        if (ServoPara.m_home_vel != ServoParaBak.m_home_vel)                                parModify |= ((quint64)1 << LOG_HOME_VEL);
        if (pModbus->GetFunctions(SUB_FUN2_EXT_POS))
            if (ServoPara.m_home_vel_slow != ServoParaBak.m_home_vel_slow)                      return true;
        // 原点偏移
        if (ServoPara.m_origin_offset_x != ServoParaBak.m_origin_offset_x)                  parModify |= ((quint64)1 << LOG_ORIGIN_OFFSET_X);
        if (ServoPara.m_origin_offset_y != ServoParaBak.m_origin_offset_y)                  parModify |= ((quint64)1 << LOG_ORIGIN_OFFSET_Y);
        if (ServoPara.m_origin_offset_z != ServoParaBak.m_origin_offset_z)                  parModify |= ((quint64)1 << LOG_ORIGIN_OFFSET_Z);
        if (ServoPara.m_origin_offset_a != ServoParaBak.m_origin_offset_a)                  parModify |= ((quint64)1 << LOG_ORIGIN_OFFSET_A);
        if (ServoPara.m_origin_offset_b != ServoParaBak.m_origin_offset_b)                  parModify |= ((quint64)1 << LOG_ORIGIN_OFFSET_B);
        if (ServoPara.m_origin_offset_c != ServoParaBak.m_origin_offset_c)                  parModify |= ((quint64)1 << LOG_ORIGIN_OFFSET_C);
        // 编码器
        if (ServoPara.m_encoder_x != ServoParaBak.m_encoder_x)                  parModify |= ((quint64)1 << LOG_ENCODER_X);
        if (ServoPara.m_encoder_y != ServoParaBak.m_encoder_y)                  parModify |= ((quint64)1 << LOG_ENCODER_Y);
        if (ServoPara.m_encoder_z != ServoParaBak.m_encoder_z)                  parModify |= ((quint64)1 << LOG_ENCODER_Z);
        if (ServoPara.m_encoder_a != ServoParaBak.m_encoder_a)                  parModify |= ((quint64)1 << LOG_ENCODER_A);
        if (ServoPara.m_encoder_b != ServoParaBak.m_encoder_b)                  parModify |= ((quint64)1 << LOG_ENCODER_B);
        if (ServoPara.m_encoder_c != ServoParaBak.m_encoder_c)                  parModify |= ((quint64)1 << LOG_ENCODER_C);
        // 原点待机点
        if (ServoPara.m_home_pos_x != ServoParaBak.m_home_pos_x)                            return true;
        if (ServoPara.m_home_pos_y != ServoParaBak.m_home_pos_y)                            return true;
        if (ServoPara.m_home_pos_z != ServoParaBak.m_home_pos_z)                            return true;
        if (ServoPara.m_home_pos_a != ServoParaBak.m_home_pos_a)                            return true;
        if (ServoPara.m_home_pos_b != ServoParaBak.m_home_pos_b)                            return true;
        if (ServoPara.m_home_pos_c != ServoParaBak.m_home_pos_c)                            return true;
        // 模
        if (ServoPara.m_mod_x != ServoParaBak.m_mod_x)                                      return true;
        if (ServoPara.m_mod_y != ServoParaBak.m_mod_y)                                      return true;
        if (ServoPara.m_mod_z != ServoParaBak.m_mod_z)                                      return true;
        if (ServoPara.m_mod_a != ServoParaBak.m_mod_a)                                      return true;
        if (ServoPara.m_mod_b != ServoParaBak.m_mod_b)                                      return true;
        if (ServoPara.m_mod_c != ServoParaBak.m_mod_c)                                      return true;

        if (ServoPara.m_pa5_x != ServoParaBak.m_pa5_x)                          return true;
        if (ServoPara.m_pa5_y != ServoParaBak.m_pa5_y)                          return true;
        if (ServoPara.m_pa5_z != ServoParaBak.m_pa5_z)                          return true;
        if (ServoPara.m_pa5_a != ServoParaBak.m_pa5_a)                          return true;
        if (ServoPara.m_pa5_b != ServoParaBak.m_pa5_b)                          return true;

        if (ServoPara.m_pa6_x != ServoParaBak.m_pa6_x)                          return true;
        if (ServoPara.m_pa6_y != ServoParaBak.m_pa6_y)                          return true;
        if (ServoPara.m_pa6_z != ServoParaBak.m_pa6_z)                          return true;
        if (ServoPara.m_pa6_a != ServoParaBak.m_pa6_a)                          return true;
        if (ServoPara.m_pa6_b != ServoParaBak.m_pa6_b)                          return true;

        if (ServoPara.m_pa7_x != ServoParaBak.m_pa7_x)                          return true;
        if (ServoPara.m_pa7_y != ServoParaBak.m_pa7_y)                          return true;
        if (ServoPara.m_pa7_z != ServoParaBak.m_pa7_z)                          return true;
        if (ServoPara.m_pa7_a != ServoParaBak.m_pa7_a)                          return true;
        if (ServoPara.m_pa7_b != ServoParaBak.m_pa7_b)                          return true;

        if (ServoPara.m_pa8_x != ServoParaBak.m_pa8_x)                          return true;
        if (ServoPara.m_pa8_y != ServoParaBak.m_pa8_y)                          return true;
        if (ServoPara.m_pa8_z != ServoParaBak.m_pa8_z)                          return true;
        if (ServoPara.m_pa8_a != ServoParaBak.m_pa8_a)                          return true;
        if (ServoPara.m_pa8_b != ServoParaBak.m_pa8_b)                          return true;

        if (ServoPara.m_pa9_x != ServoParaBak.m_pa9_x)                          return true;
        if (ServoPara.m_pa9_y != ServoParaBak.m_pa9_y)                          return true;
        if (ServoPara.m_pa9_z != ServoParaBak.m_pa9_z)                          return true;
        if (ServoPara.m_pa9_a != ServoParaBak.m_pa9_a)                          return true;
        if (ServoPara.m_pa9_b != ServoParaBak.m_pa9_b)                          return true;

        if (ServoPara.m_pa19_x != ServoParaBak.m_pa19_x)                          return true;
        if (ServoPara.m_pa19_y != ServoParaBak.m_pa19_y)                          return true;
        if (ServoPara.m_pa19_z != ServoParaBak.m_pa19_z)                          return true;
        if (ServoPara.m_pa19_a != ServoParaBak.m_pa19_a)                          return true;
        if (ServoPara.m_pa19_b != ServoParaBak.m_pa19_b)                          return true;

        if (ServoPara.m_pa63_x != ServoParaBak.m_pa63_x)                          return true;
        if (ServoPara.m_pa63_y != ServoParaBak.m_pa63_y)                          return true;
        if (ServoPara.m_pa63_z != ServoParaBak.m_pa63_z)                          return true;
        if (ServoPara.m_pa63_a != ServoParaBak.m_pa63_a)                          return true;
        if (ServoPara.m_pa63_b != ServoParaBak.m_pa63_b)                          return true;

    }
	if (parModify == 0)
		return false;
	else
		return true;
}

// 检查参数合法性
bool Formservo::CheckValid(void)
{
#if ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE))
    // 正副臂最小间距必须小于正副臂原点距离
    if (ServoPara.m_min_safe_dis_x_b > ServoPara.m_machine_max_len_x)
    {
        xMessageBox::DoWarning(tr("系统警告"), tr("取件臂和喷雾臂的最小间距必须要小于取件臂原点和喷雾臂原点的距离！"));
        return false;
    }
    // 正臂引拔轴模内安全区域起点必须小于其安全区域终点
    if (ServoPara.m_min_safe_pos_inmold_x > ServoPara.m_max_safe_pos_inmold_x)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER)+  GetServoName(AXIS_IDX_PHOR) + tr("方向模内安全区开始位置必须要小于结束位置！"));
        return false;
    }
    if (ServoPara.m_max_safe_pos_inmold_x > ServoPara.m_machine_max_len_x)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER)+  GetServoName(AXIS_IDX_PHOR) + tr("方向模内安全区结束位置必须要小于软件行程！"));
        return false;
    }
    if (ServoPara.m_max_safe_pos_inmold_b > ServoPara.m_machine_max_len_x)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER)+  GetServoName(AXIS_IDX_PHOR) + tr("方向模内安全区结束位置必须要小于软件行程！"));
        return false;
    }
    if (ServoPara.m_min_safe_pos_inmold_b > ServoPara.m_max_safe_pos_inmold_b)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER)+  GetServoName(AXIS_IDX_PHOR) + tr("方向模内安全区开始位置必须要小于结束位置！"));
        return false;
    }
    // 横行轴模外安全区域起点必须小于其终点
    if (ServoPara.m_min_safe_pos_outmold_z > ServoPara.m_max_safe_pos_outmold_z)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_TRV) + tr("轴模外安全区开始位置必须要小于模外安全区结束位置！"));
        return false;
    }
    // 横行轴模内安全区域起点必须小于其终点
    if (ServoPara.m_min_safe_pos_inmold_z > ServoPara.m_max_safe_pos_inmold_z)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER) +  GetServoName(AXIS_IDX_TRV) + tr("方向模内安全区开始位置必须要小于结束位置！"));
        return false;
    }
	if (ServoPara.m_min_safe_pos_inmold_z_a > ServoPara.m_max_safe_pos_inmold_z_a)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER) +  GetServoName(AXIS_IDX_TRV) + tr("方向模内安全区开始位置必须要小于结束位置！"));
        return false;
    }
    // 各轴伺服安全位置设置必须要小于对应轴的最大软件行程
    if (ServoPara.m_max_wait_pos_inmold_y > ServoPara.m_software_max_len_y)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER) + tr("上行位置安全区必须要小于软件行程！"));
        return false;
    }
    if (ServoPara.m_max_wait_pos_inmold_a > ServoPara.m_software_max_len_a)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER) + tr("上行位置安全区必须要小于软件行程！"));
        return false;
    }
    if (ServoPara.m_max_safe_pos_outmold_z > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_TRV) + tr("模外安全区终点必须要小于软件行程！"));
        return false;
    }
    if (ServoPara.m_max_safe_pos_inmold_z > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER) +  GetServoName(AXIS_IDX_TRV) + tr("方向模内安全区终点必须要小于软件行程！"));
        return false;
    }
	if (ServoPara.m_max_safe_pos_inmold_z_a > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER) +  GetServoName(AXIS_IDX_TRV) + tr("方向模内安全区终点必须要小于软件行程！"));
        return false;
    }
    if (trvRelPos > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_TRV) + tr("轴置物点位置必须要小于软件行程！"));
        return false;
    }
    if (trvWaitPos > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_TRV) + tr("轴原点复归后待机位置必须要小于软件行程！"));
        return false;
    }
    if (trvCatPos > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_TRV) + tr("轴取物点位置必须要小于软件行程！"));
        return false;
    }
    if (paVerCatPos > ServoPara.m_software_max_len_y)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER) + tr("轴取物点位置必须要小于软件行程！"));
        return false;
    }
    if (raVerCatPos > ServoPara.m_software_max_len_a)
    {
        xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER) + tr("轴取物点位置必须要小于软件行程！"));
        return false;
    }
#else
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        // 正副臂最小间距必须小于正副臂原点距离
        if (ServoPara.m_min_safe_dis_x_b > ServoPara.m_machine_max_len_x)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("取件臂和喷雾臂的最小间距必须要小于取件臂原点和喷雾臂原点的距离！"));
            return false;
        }
        // 正臂引拔轴模内安全区域起点必须小于其安全区域终点
        if (ServoPara.m_min_safe_pos_inmold_x > ServoPara.m_max_safe_pos_inmold_x)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER)+  GetServoName(AXIS_IDX_PHOR) + tr("方向模内安全区开始位置必须要小于结束位置！"));
            return false;
        }
        if (ServoPara.m_max_safe_pos_inmold_x > ServoPara.m_machine_max_len_x)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER)+  GetServoName(AXIS_IDX_PHOR) + tr("方向模内安全区结束位置必须要小于软件行程！"));
            return false;
        }
        if (ServoPara.m_max_safe_pos_inmold_b > ServoPara.m_machine_max_len_x)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER)+  GetServoName(AXIS_IDX_PHOR) + tr("方向模内安全区结束位置必须要小于软件行程！"));
            return false;
        }
        if (ServoPara.m_min_safe_pos_inmold_b > ServoPara.m_max_safe_pos_inmold_b)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER)+  GetServoName(AXIS_IDX_PHOR) + tr("方向模内安全区开始位置必须要小于结束位置！"));
            return false;
        }
        // 横行轴模外安全区域起点必须小于其终点
        if (ServoPara.m_min_safe_pos_outmold_z > ServoPara.m_max_safe_pos_outmold_z)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_TRV) + tr("轴模外安全区开始位置必须要小于模外安全区结束位置！"));
            return false;
        }
        // 横行轴模内安全区域起点必须小于其终点
        if (ServoPara.m_min_safe_pos_inmold_z > ServoPara.m_max_safe_pos_inmold_z)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER) +  GetServoName(AXIS_IDX_TRV) + tr("方向模内安全区开始位置必须要小于结束位置！"));
            return false;
        }
        if (ServoPara.m_min_safe_pos_inmold_z_a > ServoPara.m_max_safe_pos_inmold_z_a)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER) +  GetServoName(AXIS_IDX_TRV) + tr("方向模内安全区开始位置必须要小于结束位置！"));
            return false;
        }
        // 各轴伺服安全位置设置必须要小于对应轴的最大软件行程
        if (ServoPara.m_max_wait_pos_inmold_y > ServoPara.m_software_max_len_y)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER) + tr("上行位置安全区必须要小于软件行程！"));
            return false;
        }
        if (ServoPara.m_max_wait_pos_inmold_a > ServoPara.m_software_max_len_a)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER) + tr("上行位置安全区必须要小于软件行程！"));
            return false;
        }
        if (ServoPara.m_max_safe_pos_outmold_z > ServoPara.m_software_max_len_z)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_TRV) + tr("模外安全区终点必须要小于软件行程！"));
            return false;
        }
        if (ServoPara.m_max_safe_pos_inmold_z > ServoPara.m_software_max_len_z)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER) +  GetServoName(AXIS_IDX_TRV) + tr("方向模内安全区终点必须要小于软件行程！"));
            return false;
        }
        if (ServoPara.m_max_safe_pos_inmold_z_a > ServoPara.m_software_max_len_z)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_RVER) +  GetServoName(AXIS_IDX_TRV) + tr("方向模内安全区终点必须要小于软件行程！"));
            return false;
        }
        if (trvRelPos > ServoPara.m_software_max_len_z)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_TRV) + tr("轴置物点位置必须要小于软件行程！"));
            return false;
        }
        if (trvWaitPos > ServoPara.m_software_max_len_z)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_TRV) + tr("轴原点复归后待机位置必须要小于软件行程！"));
            return false;
        }
        if (trvCatPos > ServoPara.m_software_max_len_z)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_TRV) + tr("轴取物点位置必须要小于软件行程！"));
            return false;
        }
        if (paVerCatPos > ServoPara.m_software_max_len_y)
        {
            xMessageBox::DoWarning(tr("系统警告"),  GetServoName(AXIS_IDX_PVER) + tr("轴取物点位置必须要小于软件行程！"));
            return false;
        }
        if (raVerCatPos > ServoPara.m_software_max_len_a)
        {
            xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_RVER) + tr("轴取物点位置必须要小于软件行程！"));
            return false;
        }
    }
    else
    {
    // 正臂引拔轴模内安全区域起点必须小于其安全区域终点
    if (!pModbus->GetPaHorNotUse())
    {
    if (ServoPara.m_min_safe_pos_inmold_x > ServoPara.m_max_safe_pos_inmold_x)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_PHOR) + tr("轴模内安全区开始位置必须要小于模内安全区结束位置！"));
        return false;
    }
    }
    // 副臂引拔轴模内安全区域起点必须要小于其安全区域终点
    if (ServoPara.m_min_safe_pos_inmold_b > ServoPara.m_max_safe_pos_inmold_b)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_RHOR) + tr("轴模内安全区开始位置必须要小于模内安全区结束位置！"));
        return false;
    }
    // 横行轴模外安全区域起点必须小于其终点
    if (ServoPara.m_min_safe_pos_outmold_z > ServoPara.m_max_safe_pos_outmold_z)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴模外安全区开始位置必须要小于模外安全区结束位置！"));
        return false;
    }
    // 横行轴模内安全区域起点必须小于其终点
    if (ServoPara.m_min_safe_pos_inmold_z > ServoPara.m_max_safe_pos_inmold_z)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴模内安全区开始位置必须要小于模内安全区结束位置！"));
        return false;
    }
    // 各轴伺服安全位置设置必须要小于对应轴的最大软件行程
    if (ServoPara.m_max_wait_pos_inmold_y > ServoPara.m_software_max_len_y)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_PVER) + tr("轴上位安全位置必须要小于软件行程！"));
        return false;
    }
        if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (pModbus->GetRverSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0))
    {
        if (ServoPara.m_min_a_inmold > ServoPara.m_max_a_inmold)
        {
            xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_RVER) + tr("轴模内安全区开始位置必须小于结束位置！"));
            return false;
        }
        if (ServoPara.m_min_a_trv > ServoPara.m_max_a_trv)
        {
            xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_RVER) + tr("轴横行安全区开始位置必须小于结束位置！"));
            return false;
        }
        if (ServoPara.m_max_a_inmold > ServoPara.m_software_max_len_a)
        {
            xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_RVER) + tr("轴模内安全区结束位置必须要小于软件行程！"));
            return false;
        }
        if (ServoPara.m_max_a_trv > ServoPara.m_software_max_len_a)
        {
            xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_RVER) + tr("轴横行安全区结束位置必须要小于软件行程！"));
            return false;
        }
    }
    }
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E3)
    {
        if (pModbus->GetRhorSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0))
        {
        // 正副臂最小间距必须小于正副臂原点距离
        if (ServoPara.m_min_safe_dis_x_b > ServoPara.m_machine_max_len_x)
        {
            xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_PHOR) + tr("和")+ GetServoName(AXIS_IDX_RHOR) + tr("的最小间距必须要小于原点的距离！"));
            return false;
        }
    }
    }
    if (ServoPara.m_min_safe_pos_inmold_z > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴模内安全区起点必须要小于软件行程！"));
        return false;
    }
    if (ServoPara.m_max_safe_pos_inmold_z > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴模内安全区终点必须要小于软件行程！"));
        return false;
    }
    if (ServoPara.m_min_safe_pos_outmold_z > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴模外安全区起点必须要小于软件行程！"));
        return false;
    }
    if (ServoPara.m_max_safe_pos_outmold_z > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴模外安全区终点必须要小于软件行程！"));
        return false;
    }
    if (pModbus->GetOutmold2use())
    {
        // 横行轴模外安全区域2起点必须小于其终点
        if (ServoPara.m_min_safe_pos_outmold2_z > ServoPara.m_software_max_len_z)
        {
            xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴模外安全区2起点必须要小于软件行程！"));
            return false;
        }
        if (ServoPara.m_min_safe_pos_outmold2_z > ServoPara.m_max_safe_pos_outmold2_z)
        {
            xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴模外安全区2起点必须要小于模外安全区2终点！"));
            return false;
        }
        if (ServoPara.m_max_safe_pos_outmold2_z > ServoPara.m_software_max_len_z)
        {
            xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴模外安全区2终点必须要小于软件行程！"));
            return false;
        }
    }
    if (trvRelPos > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴置物点位置必须要小于软件行程！"));
        return false;
    }
    if (trvWaitPos > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴原点复归后待机位置必须要小于软件行程！"));
        return false;
    }
    if (trvCatPos > ServoPara.m_software_max_len_z)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_TRV) + tr("轴取物点位置必须要小于软件行程！"));
        return false;
    }
    if (paVerCatPos > ServoPara.m_software_max_len_y)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_PVER) + tr("上下轴取物点位置必须要小于软件行程！"));
        return false;
    }
    if (pModbus->GetRverSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0))
    {
        if (ServoPara.m_max_wait_pos_inmold_a > ServoPara.m_software_max_len_a)
        {
            xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_RVER) + tr("轴上位安全位置必须要小于软件行程！"));
            return false;
        }
    if (raVerCatPos > ServoPara.m_software_max_len_a)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_RVER) + tr("轴取物点位置必须要小于软件行程！"));
        return false;
    }
    }
    if (pModbus->GetRhorSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0))
    {
    if (ServoPara.m_min_safe_pos_inmold_b > ServoPara.m_max_safe_pos_inmold_b)
    {
        xMessageBox::DoWarning(tr("系统警告"), GetServoName(AXIS_IDX_RHOR) + tr("轴模内安全区起点位置必须要小于终点位置！"));
        return false;
    }
     }
    }
#endif
	return true;
}
// 得到轴类型是否是旋转 方向
void Formservo::GetAngleType(uint8_t idx)
{
    if (idx > MAX_AXIS_NUM) return;
    m_AxisType[idx]->setChecked((ServoPara.m_angle_type >> idx) & 1);
    m_DirType[idx]->setChecked((ServoPara.m_angle_type >> (idx+8)) & 1);
}
void Formservo::SetAngleType(uint8_t idx)
{
    if (idx > MAX_AXIS_NUM) return;
    if (m_AxisType[idx]->isChecked())
        ServoPara.m_angle_type |= (1 << idx);
    else
        ServoPara.m_angle_type &= ~(1 << idx);

    if (m_DirType[idx]->isChecked())
        ServoPara.m_angle_type |= ((uint16_t)(1 << (idx+8)))&0xFFFF;
    else
        ServoPara.m_angle_type &= ((uint16_t)(~(1 << (idx+8))))&0xFFFF;
}
// 减速模式
void Formservo::GetDecType(uint8_t idx)
{
    if (idx > MAX_AXIS_NUM) return;
    m_DecType[idx]->setChecked((ServoPara.m_dec_type >> idx) & 1);
    m_HomeMod[idx]->setChecked(((ServoPara.m_dec_type >> 8)>>idx) & 1);
}
void Formservo::SetDecType(uint8_t idx)
{
    if (idx > MAX_AXIS_NUM) return;
    if (m_DecType[idx]->isChecked())
        ServoPara.m_dec_type |= (1 << idx);
    else
        ServoPara.m_dec_type &= ~(1 << idx);

    if (m_HomeMod[idx]->isChecked())
        ServoPara.m_dec_type |= ((1 << idx)<<8);
    else
        ServoPara.m_dec_type &= ~((1 << idx)<<8);
}
void Formservo::showSVDevPara(uint8_t idx)
{
    switch (idx)
    {
    case AXES_IDX_X:
        ui->BoxPA5_DEV->setValue(ServoPara.m_pa5_x);
        ui->BoxPA6_DEV->setValue(ServoPara.m_pa6_x);
        ui->BoxPA7_DEV->setValue(ServoPara.m_pa7_x);
        ui->BoxPA8_DEV->setValue(ServoPara.m_pa8_x);
        ui->BoxPA9_DEV->setValue(ServoPara.m_pa9_x);
        ui->BoxPA19_DEV->setValue(ServoPara.m_pa19_x);
		ui->BoxPA63_DEV->setValue(ServoPara.m_pa63_x);
    break;
    case AXES_IDX_Y:
        ui->BoxPA5_DEV->setValue(ServoPara.m_pa5_y);
        ui->BoxPA6_DEV->setValue(ServoPara.m_pa6_y);
        ui->BoxPA7_DEV->setValue(ServoPara.m_pa7_y);
        ui->BoxPA8_DEV->setValue(ServoPara.m_pa8_y);
        ui->BoxPA9_DEV->setValue(ServoPara.m_pa9_y);
        ui->BoxPA19_DEV->setValue(ServoPara.m_pa19_y);
		ui->BoxPA63_DEV->setValue(ServoPara.m_pa63_y);
    break;
    case AXES_IDX_Z:
        ui->BoxPA5_DEV->setValue(ServoPara.m_pa5_z);
        ui->BoxPA6_DEV->setValue(ServoPara.m_pa6_z);
        ui->BoxPA7_DEV->setValue(ServoPara.m_pa7_z);
        ui->BoxPA8_DEV->setValue(ServoPara.m_pa8_z);
        ui->BoxPA9_DEV->setValue(ServoPara.m_pa9_z);
        ui->BoxPA19_DEV->setValue(ServoPara.m_pa19_z);
		ui->BoxPA63_DEV->setValue(ServoPara.m_pa63_z);
    break;
    case AXES_IDX_A:
        ui->BoxPA5_DEV->setValue(ServoPara.m_pa5_a);
        ui->BoxPA6_DEV->setValue(ServoPara.m_pa6_a);
        ui->BoxPA7_DEV->setValue(ServoPara.m_pa7_a);
        ui->BoxPA8_DEV->setValue(ServoPara.m_pa8_a);
        ui->BoxPA9_DEV->setValue(ServoPara.m_pa9_a);
        ui->BoxPA19_DEV->setValue(ServoPara.m_pa19_a);
		ui->BoxPA63_DEV->setValue(ServoPara.m_pa63_a);
    break;
    case AXES_IDX_B:
		ui->BoxPA5_DEV->setValue(ServoPara.m_pa5_b);
        ui->BoxPA6_DEV->setValue(ServoPara.m_pa6_b);
        ui->BoxPA7_DEV->setValue(ServoPara.m_pa7_b);
        ui->BoxPA8_DEV->setValue(ServoPara.m_pa8_b);
        ui->BoxPA9_DEV->setValue(ServoPara.m_pa9_b);
        ui->BoxPA19_DEV->setValue(ServoPara.m_pa19_b);
		ui->BoxPA63_DEV->setValue(ServoPara.m_pa63_b);
    break;
    }
}
// 读取旋转选框是否勾上，显示马达转动一圈距离后单位
void Formservo::CheckBoxStatus(void)
{
    if (ui->checkBoxPHor->isChecked())
	{
        ui->BoxPaHorUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxPaHorOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxPaHorUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxPaHorOffset->setSuffix(QString::fromUtf8("mm"));
	}

    if (ui->checkBoxRHor->isChecked())
	{
        ui->BoxRaHorUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxRaHorOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxRaHorUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxRaHorOffset->setSuffix(QString::fromUtf8("mm"));
	}

    if (ui->checkBoxPVer->isChecked())
	{
        ui->BoxPaVerUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxPaVerOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxPaVerUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxPaVerOffset->setSuffix(QString::fromUtf8("mm"));
	}

    if (ui->checkBoxRVer->isChecked())
	{
        ui->BoxRaVerUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxRaVerOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxRaVerUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxRaVerOffset->setSuffix(QString::fromUtf8("mm"));
	}

    if (ui->checkBoxTrv->isChecked())
	{
        ui->BoxTrvUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxTrvOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxTrvUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxTrvOffset->setSuffix(QString::fromUtf8("mm"));
	}

    if (ui->checkBoxExt->isChecked())
	{
        ui->BoxExtUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxExtOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxExtUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxExtOffset->setSuffix(QString::fromUtf8("mm"));
	}
}
// 原点归位模式设置
void Formservo::GetHomeType(uint8_t idx)
{
    if (idx > MAX_AXIS_NUM) return;
    if(pModbus->GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
//        if(((ServoPara.m_home_mode >> (idx*2)) &3) == 2)              // 20240228 放开限制
//            m_HomeType[idx]->setCurrentIndex(1); // 每个轴占2位
//        else
            m_HomeType[idx]->setCurrentIndex((ServoPara.m_home_mode >> (idx*2)) &3); // 每个轴占2位
    }
    else
    m_HomeType[idx]->setCurrentIndex((ServoPara.m_home_mode >> (idx*2)) &3); // 每个轴占2位
}

void Formservo::SetHomeType(uint8_t idx)
{
    if (idx > MAX_AXIS_NUM) return;
    ServoPara.m_home_mode &= ~(3 <<(idx*2));
    if(pModbus->GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
//        if(m_HomeType[idx]->currentIndex() == 1)//0：不归原点。1：原点加Z。2：原点 。五轴主板特殊处理    // 20240228 放开限制
//            ServoPara.m_home_mode |= 2<< (idx*2) ;
//        else
            ServoPara.m_home_mode |= m_HomeType[idx]->currentIndex()<< (idx*2) ;
    }
    else
    ServoPara.m_home_mode |= m_HomeType[idx]->currentIndex()<< (idx*2) ;
}
// 保存伺服参数设置
bool Formservo::SavePara(void)
{
	try
	{
		if (pModbus->WriteServo(ServoPara, parModify))
			throw false;
		if (pModbus->CommandWrite(CMD_WRITE_SERVO))
			throw false;
		QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
		settings.setValue(XPAD_SET_TRVRELPOS, trvRelPos);
		settings.setValue(XPAD_SET_TRVCATPOS, trvCatPos);
		settings.setValue(XPAD_SET_TRVWAIT, trvWaitPos);
		settings.setValue(XPAD_SET_PAVERCAT, paVerCatPos);
		settings.setValue(XPAD_SET_PAVERREL, paVerRelPos);
		settings.setValue(XPAD_SET_PAVERWAIT, paVerWaitPos);
		settings.setValue(XPAD_SET_PAHORCAT, paHorCatPos);
		settings.setValue(XPAD_SET_PAHORREL, paHorRelPos);
		settings.setValue(XPAD_SET_PAHORWAIT, paHorWaitPos);
		settings.setValue(XPAD_SET_RAVERCAT, raVerCatPos);
		settings.setValue(XPAD_SET_RAVERREL, raVerRelPos);
		settings.setValue(XPAD_SET_RAVERWAIT, raVerWaitPos);
		settings.setValue(XPAD_SET_RAHORCAT, raHorCatPos);
		settings.setValue(XPAD_SET_RAHORREL, raHorRelPos);
		settings.setValue(XPAD_SET_RAHORWAIT, raHorWaitPos);
		settings.setValue(XPAD_SET_EXTCAT, extCatPos);
		settings.setValue(XPAD_SET_EXTREL, extRelPos);
		settings.setValue(XPAD_SET_EXTWAIT, extWaitPos);
		settings.sync();
	}
	catch (bool &)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAVE_PARA_ERROR));
		return false;
	}
#if defined(Q_OS_LINUX)
	sync();
#endif
	return true;
}

// 进入伺服参数设置画面
bool Formservo::EnterForm(void)
{
    if(CMBProtocol::GetPaHorNotUse()) SvDevParaPage = AXES_IDX_Y;
    else SvDevParaPage = AXES_IDX_X;
	// 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return false;
	}
    // 检查用户权限
    if ((xPermissions::GetPermissions(PER_SRV_SAFE) == false) && (xPermissions::GetPermissions(PER_SRV_MACHINE) == false))
    {
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (pDialogMain)
            if (pDialogMain->ScreenSaverUserManager() == 0)
        return false;
    }
    // 如果系统不在手动状态则不能进入伺服参数设置画面
	if (pModbus->GetSysState() != SYS_STATE_MANUAL)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SERVO_NO_MANUAL));
		return false;
	}
	// 查询伺服参数设置
	if (QueryPara() != true)
		return false;
    CheckBoxStatus();
//    retranslateUi();
    // 根据当前用户权限设置界面
    ui->radioPaHor->setChecked(true);
    ui->stackedWidget->setCurrentIndex(SRVPG_SAFE);
	setPermissions();
    retranslateUi();
    // 原点待机点隐藏
    ui->labelTrvWaitPos->setVisible(false);
    ui->BoxTrvWait->setVisible(false);

	// 初始化界面显示状态
    if (pModbus->GetOutmold2use())
    {
        ui->BoxTrvOutS2->setVisible(true);
        ui->BoxTrvOutE2->setVisible(true);
        ui->LedSafeOut2->setVisible(true);
    }
    else
    {
        ui->BoxTrvOutS2->setVisible(false);
        ui->BoxTrvOutE2->setVisible(false);
        ui->LedSafeOut2->setVisible(false);
    }
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        ui->LedSafeRot->setVisible(true);
        ui->LedSafeTrv->setVisible(true);
        ui->BoxSafeRotS->setVisible(true);
        ui->BoxSafeRotE->setVisible(true);
        ui->BoxSafeTrvS->setVisible(true);
        ui->BoxSafeTrvE->setVisible(true);
        ui->LedSafeRaUp->setVisible(false);
        ui->BoxSafeRaUpDumb->setVisible(false);
        ui->BoxSafeRaUp->setVisible(false);
    }
    else
    {
        ui->LedSafeRot->setVisible(false);
        ui->LedSafeTrv->setVisible(false);
        ui->BoxSafeRotS->setVisible(false);
        ui->BoxSafeRotE->setVisible(false);
        ui->BoxSafeTrvS->setVisible(false);
        ui->BoxSafeTrvE->setVisible(false);
        ui->LedSafeRaUp->setVisible(true);
        ui->BoxSafeRaUpDumb->setVisible(true);
        ui->BoxSafeRaUp->setVisible(true);
    }
#if PENDANT_PROTOCOL
    if (pModbus->GetFunctions(SUB_FUN_SDIR))
    {
        ui->labelPaHorDir->setVisible(true);
        ui->checkBoxPHorDir->setVisible(true);
        ui->labelRaHorDir->setVisible(true);
        ui->checkBoxRHorDir->setVisible(true);
        ui->labelPaVerDir->setVisible(true);
        ui->checkBoxPVerDir->setVisible(true);
        ui->labelRaVerDir->setVisible(true);
        ui->checkBoxRVerDir->setVisible(true);
        ui->labelExtDir->setVisible(true);
        ui->checkBoxExtDir->setVisible(true);
        ui->labelTrvDir->setVisible(true);
        ui->checkBoxTrvDir->setVisible(true);
    }
    else
    {
        ui->labelPaHorDir->setVisible(false);
        ui->checkBoxPHorDir->setVisible(false);
        ui->labelRaHorDir->setVisible(false);
        ui->checkBoxRHorDir->setVisible(false);
        ui->labelPaVerDir->setVisible(false);
        ui->checkBoxPVerDir->setVisible(false);
        ui->labelRaVerDir->setVisible(false);
        ui->checkBoxRVerDir->setVisible(false);
        ui->labelExtDir->setVisible(false);
        ui->checkBoxExtDir->setVisible(false);
        ui->labelTrvDir->setVisible(false);
        ui->checkBoxTrvDir->setVisible(false);
    }
    if (pModbus->GetFunctions(SUB_FUN2_JERK))
    {
        ui->labelPaHorJerk->setVisible(true);
        ui->BoxPaHorJerk->setVisible(true);
        ui->labelPaVerJerk->setVisible(true);
        ui->BoxPaVerJerk->setVisible(true);
        ui->labelRaHorJerk->setVisible(true);
        ui->BoxRaHorJerk->setVisible(true);
        ui->labelRaVerJerk->setVisible(true);
        ui->BoxRaVerJerk->setVisible(true);
        ui->labelTrvJerk->setVisible(true);
        ui->BoxTrvJerk->setVisible(true);
        ui->labelExtJerk->setVisible(true);
        ui->BoxExtJerk->setVisible(true);
    }
    else
    {
        ui->labelPaHorJerk->setVisible(false);
        ui->BoxPaHorJerk->setVisible(false);
        ui->labelPaVerJerk->setVisible(false);
        ui->BoxPaVerJerk->setVisible(false);
        ui->labelRaHorJerk->setVisible(false);
        ui->BoxRaHorJerk->setVisible(false);
        ui->labelRaVerJerk->setVisible(false);
        ui->BoxRaVerJerk->setVisible(false);
        ui->labelTrvJerk->setVisible(false);
        ui->BoxTrvJerk->setVisible(false);
        ui->labelExtJerk->setVisible(false);
        ui->BoxExtJerk->setVisible(false);
    }
    // 找原点方式显示
    if (pModbus->GetFunctions(SUB_IN_ANTI_CHECK_HOME_TAIL_LOOP_FREE))
    {
        ui->labelPaHorHomeMod->setVisible(true);
        ui->labelPaVerHomeMod->setVisible(true);
        ui->labelRaHorHomeMod->setVisible(true);
        ui->labelRaVerHomeMod->setVisible(true);
        ui->labelTrvHomeMod->setVisible(true);
        ui->labelExtHomeMod->setVisible(true);
        ui->checkBoxPHorHome->setVisible(true);
        ui->checkBoxPVerHome->setVisible(true);
        ui->checkBoxRHorHome->setVisible(true);
        ui->checkBoxRVerHome->setVisible(true);
        ui->checkBoxTrvHome->setVisible(true);
        ui->checkBoxExtHome->setVisible(true);
    }
    else
    {
        ui->labelPaHorHomeMod->setVisible(false);
        ui->labelPaVerHomeMod->setVisible(false);
        ui->labelRaHorHomeMod->setVisible(false);
        ui->labelRaVerHomeMod->setVisible(false);
        ui->labelTrvHomeMod->setVisible(false);
        ui->labelExtHomeMod->setVisible(false);
        ui->checkBoxPHorHome->setVisible(false);
        ui->checkBoxPVerHome->setVisible(false);
        ui->checkBoxRHorHome->setVisible(false);
        ui->checkBoxRVerHome->setVisible(false);
        ui->checkBoxTrvHome->setVisible(false);
        ui->checkBoxExtHome->setVisible(false);
    }
    if (pModbus->GetFunctions(SUB_FUN_TMC429))
    {
        ui->labelPaHorDecType->setVisible(true);
        ui->checkBoxPHorDes->setVisible(true);
        ui->labelPaVerDecType->setVisible(true);
        ui->checkBoxPVerDes->setVisible(true);
        ui->labelRaHorDecType->setVisible(true);
        ui->checkBoxRHorDes->setVisible(true);
        ui->labelRaVerDecType->setVisible(true);
        ui->checkBoxRVerDes->setVisible(true);
        ui->labelTrvDecType->setVisible(true);
        ui->checkBoxTrvDes->setVisible(true);
        ui->labelExtDecType->setVisible(true);
        ui->checkBoxExtDes->setVisible(true);
    }
    else
    {
        ui->labelPaHorDecType->setVisible(false);
        ui->checkBoxPHorDes->setVisible(false);
        ui->labelPaVerDecType->setVisible(false);
        ui->checkBoxPVerDes->setVisible(false);
        ui->labelRaHorDecType->setVisible(false);
        ui->checkBoxRHorDes->setVisible(false);
        ui->labelRaVerDecType->setVisible(false);
        ui->checkBoxRVerDes->setVisible(false);
        ui->labelTrvDecType->setVisible(false);
        ui->checkBoxTrvDes->setVisible(false);
        ui->labelExtDecType->setVisible(false);
        ui->checkBoxExtDes->setVisible(false);
    }
    if (pModbus->GetFunctions(SUB_FUN2_EXT_POS))
    {
        ui->groupBoxHome->setTitle(tr("原点快速速度"));
        ui->groupBoxHome2->setVisible(true);
    }
    else
    {
        ui->groupBoxHome->setTitle(tr("原点速度"));
        ui->groupBoxHome2->setVisible(false);
    }
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        ui->LedSafeRaHor->setVisible(true);
        ui->BoxSafeRHorS->setVisible(true);
        ui->BoxSafeRHorE->setVisible(true);
    }
    else
    {
        if (pModbus->GetFunctions(SUB_FUN2_X_B_TRAVE_SAFE))
        {
            ui->LedSafeRaHor->setVisible(true);
            ui->BoxSafeRHorS->setVisible(true);
            ui->BoxSafeRHorE->setVisible(true);
        }
        else
        {
            ui->LedSafeRaHor->setVisible(false);
            ui->BoxSafeRHorS->setVisible(false);
            ui->BoxSafeRHorE->setVisible(false);
        }
    }
    if (pModbus->GetFunctions(SUB_FUN2_X_B_TRAVE_SAFE)) // 无论单双臂均读功能码
    {
        ui->LedSafePaHor->setVisible(true);
        ui->BoxSafePHorS->setVisible(true);
        ui->BoxSafePHorE->setVisible(true);
    }
    else
    {
        ui->LedSafePaHor->setVisible(false);
        ui->BoxSafePHorS->setVisible(false);
        ui->BoxSafePHorE->setVisible(false);
    }
#else
	ui->labelPaHorDecType->setVisible(false);
	ui->checkBoxPHorDes->setVisible(false);
	ui->labelPaVerDecType->setVisible(false);
	ui->checkBoxPVerDes->setVisible(false);
	ui->labelRaHorDecType->setVisible(false);
	ui->checkBoxRHorDes->setVisible(false);
	ui->labelRaVerDecType->setVisible(false);
	ui->checkBoxRVerDes->setVisible(false);
	ui->labelTrvDecType->setVisible(false);
	ui->checkBoxTrvDes->setVisible(false);
	ui->labelExtDecType->setVisible(false);
	ui->checkBoxExtDes->setVisible(false);

#endif
    if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        ui->LedSafeIn2->setVisible(true);
        ui->BoxTrvInS2->setVisible(true);
        ui->BoxTrvInE2->setVisible(true);
    }
    else
    {
        ui->LedSafeIn2->setVisible(false);
        ui->BoxTrvInS2->setVisible(false);
        ui->BoxTrvInE2->setVisible(false);
    }
    // IO端口
    SetMain(false);
    // 正臂引拔伺服设置
    ui->labelPaSafeHor->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxSafePaHorS->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxSafePaHorE->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxPaHorSpeed->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxPaHorAcc->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxPaHorJerk->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxPaHorCat->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxPaHorRel->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxPaHorWait->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxPaHorUnits->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxPaHorPluses->setEnabled(!pModbus->GetPaHorNotUse());
    ui->checkBoxPHor->setEnabled(!pModbus->GetPaHorNotUse());
    ui->cBoxPaHorHome->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxPaHorOffset->setEnabled(!pModbus->GetPaHorNotUse());
    ui->checkBoxPHorDes->setEnabled(!pModbus->GetPaHorNotUse());
    ui->checkBoxPHorHome->setEnabled(!pModbus->GetPaHorNotUse());
    ui->cBoxPaHorEncoder->setEnabled(!pModbus->GetPaHorNotUse());
    ui->cBPaHorEncoder->setEnabled(!pModbus->GetPaHorNotUse());
     ui->BoxPaHorMod->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxPaHorHomeWait->setEnabled(!pModbus->GetPaHorNotUse());
    ui->checkBoxPHorDir->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxHorLen->setEnabled(!pModbus->GetPaHorNotUse());
    ui->LedSafePaHor->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxSafePHorS->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BoxSafePHorE->setEnabled(!pModbus->GetPaHorNotUse());

    ui->checkBoxPHorAbsolute->setEnabled(!pModbus->GetPaHorNotUse());
    ui->labelPaHorEncoder_ECat->setEnabled(!pModbus->GetPaHorNotUse());
    // 副臂引拔伺服设置
    if (pModbus->GetSysType()!=ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        ui->labelRaSafeHor->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
        ui->BoxSafeRaHorS->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
        ui->BoxSafeRaHorE->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    }
	ui->BoxRaHorSpeed->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
	ui->BoxRaHorAcc->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BoxRaHorJerk->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
//	ui->BoxHorInt->setEnabled(pModbus->GetRhorSrvUse());
//	ui->labelHorInt->setEnabled(pModbus->GetRhorSrvUse());
	ui->BoxRaHorCat->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
	ui->BoxRaHorRel->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
	ui->BoxRaHorWait->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BoxRaHorUnits->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BoxRaHorPluses->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->checkBoxRHor->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->cBoxRaHorHome->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BoxRaHorOffset->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->checkBoxRHorDes->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->checkBoxRHorHome->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->cBoxRaHorEncoder->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->cBRaHorEncoder->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BoxRaHorMod->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BoxRaHorHomeWait->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->checkBoxRHorDir->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BoxHorInt->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->LedSafeRaHor->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BoxSafeRHorS->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BoxSafeRHorE->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));

    ui->checkBoxRHorAbsolute->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->labelRaHorEncoder_ECat->setEnabled((pModbus->GetRhorSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
   // 副臂上下设置
    ui->LedSafeRaUp->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxSafeRaUp->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerCat->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerRel->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerWait->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerUnits->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerPluses->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->checkBoxRVer->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerSoftDist->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerSpeed->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerAcc->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerJerk->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->cBoxRaVerHome->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerOffset->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->checkBoxRVerDes->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->checkBoxRVerHome->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->cBoxRaVerEncoder->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->cBRaVerEncoder->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerHomeWait->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BoxRaVerMod->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->checkBoxRVerDir->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));

    ui->checkBoxRVerAbsolute->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->labelRaVerEncoder_ECat->setEnabled((pModbus->GetRverSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
   // 扩展伺服设置
    ui->BoxExtSoftDist->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtSpeed->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtAcc->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtJerk->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtCat->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtRel->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtWait->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtPluses->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtUnits->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->checkBoxExt->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->cBoxExtHome->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtOffset->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->checkBoxExtDes->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->checkBoxExtHome->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtHomeWait->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxExtMod->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->checkBoxExtDir->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->cBoxExtEncoder->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->cBExtEncoder->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxSafeExtMoldS->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxSafeExtMoldE->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxSafeExtS->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BoxSafeExtE->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->LedSafeExtMold->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->LedSafeExt->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));

    ui->checkBoxExtAbsolute->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->labelExtEncoder_ECat->setEnabled((pModbus->GetExtSrvUse()) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    // 马达脉冲不可编辑
    ui->BoxPaHorPluses->setEnabled(false);
    ui->BoxPaVerPluses->setEnabled(false);
    ui->BoxRaHorPluses->setEnabled(false);
    ui->BoxRaVerPluses->setEnabled(false);
    ui->BoxTrvPluses->setEnabled(false);
    ui->BoxExtPluses->setEnabled(false);
    // 编码器
    if(pModbus->GetSysTypeHigh() == BOARD_VERSION_ECAT)
    {
        if(ui->checkBoxPHorAbsolute->isChecked()&& (!pModbus->GetPaHorNotUse()))
            ui->cBPaHorEncoder->setEnabled(true);
        else
            ui->cBPaHorEncoder->setEnabled(false);

        if(ui->checkBoxPVerAbsolute->isChecked())
            ui->cBPaVerEncoder->setEnabled(true);
        else
            ui->cBPaVerEncoder->setEnabled(false);

        if(ui->checkBoxTrvAbsolute->isChecked())
            ui->cBTrvEncoder->setEnabled(true);
        else
            ui->cBTrvEncoder->setEnabled(false);

        if(ui->checkBoxRHorAbsolute->isChecked()&&pModbus->GetRhorSrvUse())
            ui->cBRaHorEncoder->setEnabled(true);
        else
            ui->cBRaHorEncoder->setEnabled(false);

        if(ui->checkBoxRVerAbsolute->isChecked()&&pModbus->GetRverSrvUse())
            ui->cBRaVerEncoder->setEnabled(true);
        else
            ui->cBRaVerEncoder->setEnabled(false);

        if(ui->checkBoxExtAbsolute->isChecked()&&pModbus->GetExtSrvUse())
            ui->cBExtEncoder->setEnabled(true);
        else
            ui->cBExtEncoder->setEnabled(false);
    }
    else
    {
    if (ui->cBoxPaHorEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxPaHorAddr->setEnabled(false);
        ui->cBPaHorEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxPaHorAddr->setEnabled(true);
        ui->cBPaHorEncoder->setEnabled(true);
    }
    if (ui->cBoxPaVerEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxPaVerAddr->setEnabled(false);
        ui->cBPaVerEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxPaVerAddr->setEnabled(true);
		ui->cBPaVerEncoder->setEnabled(true);
    }
    if (ui->cBoxTrvEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxTrvAddr->setEnabled(false);
        ui->cBTrvEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxTrvAddr->setEnabled(true);
		ui->cBTrvEncoder->setEnabled(true);
    }
    if (ui->cBoxRaHorEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxRaHorAddr->setEnabled(false);
        ui->cBRaHorEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxRaHorAddr->setEnabled(true);
		ui->cBRaHorEncoder->setEnabled(true);
    }
    if (ui->cBoxRaVerEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxRaVerAddr->setEnabled(false);
        ui->cBRaVerEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxRaVerAddr->setEnabled(true);
		ui->cBRaVerEncoder->setEnabled(true);
    }
    if (ui->cBoxExtEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxExtAddr->setEnabled(false);
        ui->cBExtEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxExtAddr->setEnabled(true);
		ui->cBExtEncoder->setEnabled(true);
    }
    }
    setEncoderHomeState();
    ui->radioSafe->setChecked(true);
    setCurrentpage(pBtnPage->checkedId());
    if(pModbus->GetSysTypeHigh() == BOARD_VERSION_ECAT)//ECat主板
    {
        ui->ClrHomeEncoder->setVisible(false);
        ui->labelPaHorEncoder->setVisible(false);
        ui->labelPaHorAddr->setVisible(false);
        ui->cBoxPaHorEncoder->setVisible(false);
        ui->BoxPaHorAddr->setVisible(false);
        ui->labelPaHorEncoder_ECat->setVisible(true);
        ui->checkBoxPHorAbsolute->setVisible(true);

        ui->labelPaVerEncoder->setVisible(false);
        ui->labelPaVerAddr->setVisible(false);
        ui->cBoxPaVerEncoder->setVisible(false);
        ui->BoxPaVerAddr->setVisible(false);
        ui->labelPaVerEncoder_ECat->setVisible(true);
        ui->checkBoxPVerAbsolute->setVisible(true);

        ui->labelTrvEncoder->setVisible(false);
        ui->labelTrvAddr->setVisible(false);
        ui->cBoxTrvEncoder->setVisible(false);
        ui->BoxTrvAddr->setVisible(false);
        ui->labelTrvEncoder_ECat->setVisible(true);
        ui->checkBoxTrvAbsolute->setVisible(true);

        ui->labelRaHorEncoder->setVisible(false);
        ui->labelRaHorAddr->setVisible(false);
        ui->cBoxRaHorEncoder->setVisible(false);
        ui->BoxRaHorAddr->setVisible(false);
        ui->labelRaHorEncoder_ECat->setVisible(true);
        ui->checkBoxRHorAbsolute->setVisible(true);

        ui->labelRaVerEncoder->setVisible(false);
        ui->labelRaVerAddr->setVisible(false);
        ui->cBoxRaVerEncoder->setVisible(false);
        ui->BoxRaVerAddr->setVisible(false);
        ui->labelRaVerEncoder_ECat->setVisible(true);
        ui->checkBoxRVerAbsolute->setVisible(true);

        ui->labelExtEncoder->setVisible(false);
        ui->labelExtAddr->setVisible(false);
        ui->cBoxExtEncoder->setVisible(false);
        ui->BoxExtAddr->setVisible(false);
        ui->labelExtEncoder_ECat->setVisible(true);
        ui->checkBoxExtAbsolute->setVisible(true);

    }
    else
    {
        ui->ClrHomeEncoder->setVisible(true);
        ui->labelPaHorEncoder->setVisible(true);
        ui->labelPaHorAddr->setVisible(true);
        ui->cBoxPaHorEncoder->setVisible(true);
        ui->BoxPaHorAddr->setVisible(true);
        ui->labelPaHorEncoder_ECat->setVisible(false);
        ui->checkBoxPHorAbsolute->setVisible(false);

        ui->labelPaVerEncoder->setVisible(true);
        ui->labelPaVerAddr->setVisible(true);
        ui->cBoxPaVerEncoder->setVisible(true);
        ui->BoxPaVerAddr->setVisible(true);
        ui->labelPaVerEncoder_ECat->setVisible(false);
        ui->checkBoxPVerAbsolute->setVisible(false);

        ui->labelTrvEncoder->setVisible(true);
        ui->labelTrvAddr->setVisible(true);
        ui->cBoxTrvEncoder->setVisible(true);
        ui->BoxTrvAddr->setVisible(true);
        ui->labelTrvEncoder_ECat->setVisible(false);
        ui->checkBoxTrvAbsolute->setVisible(false);

        ui->labelRaHorEncoder->setVisible(true);
        ui->labelRaHorAddr->setVisible(true);
        ui->cBoxRaHorEncoder->setVisible(true);
        ui->BoxRaHorAddr->setVisible(true);
        ui->labelRaHorEncoder_ECat->setVisible(false);
        ui->checkBoxRHorAbsolute->setVisible(false);

        ui->labelRaVerEncoder->setVisible(true);
        ui->labelRaVerAddr->setVisible(true);
        ui->cBoxRaVerEncoder->setVisible(true);
        ui->BoxRaVerAddr->setVisible(true);
        ui->labelRaVerEncoder_ECat->setVisible(false);
        ui->checkBoxRVerAbsolute->setVisible(false);

        ui->labelExtEncoder->setVisible(true);
        ui->labelExtAddr->setVisible(true);
        ui->cBoxExtEncoder->setVisible(true);
        ui->BoxExtAddr->setVisible(true);
        ui->labelExtEncoder_ECat->setVisible(false);
        ui->checkBoxExtAbsolute->setVisible(false);

    }
//    if(pModbus->GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
//    {
//        if(ui->cBoxRaHorHome->count() > 2)
//        {
//            m_HomeType[0]->removeItem(1);
//            m_HomeType[1]->removeItem(1);
//            m_HomeType[2]->removeItem(1);
//            m_HomeType[3]->removeItem(1);
//            m_HomeType[4]->removeItem(1);
//            m_HomeType[5]->removeItem(1);
//        }
//    }
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        ui->tabWidgetSvDev->setVisible(true);
        ui->radioPower->setVisible(true);
        ui->radioPHorDEV->setVisible(true);
        ui->radioPVerDEV->setVisible(true);
        ui->radioTRVDEV->setVisible(true);
        ui->radioRHorDEV->setVisible(true);
        ui->radioRVerDEV->setVisible(true);
    }
    else
    {
        ui->radioPower->setVisible(false);
        ui->radioPHorDEV->setVisible(false);
        ui->radioPVerDEV->setVisible(false);
        ui->radioTRVDEV->setVisible(false);
        ui->radioRHorDEV->setVisible(false);
        ui->radioRVerDEV->setVisible(false);
        ui->tabWidgetSvDev->setVisible(false);
    }
    if(CMBProtocol::GetPaHorNotUse())
    {
        ui->radioPHorDEV->setEnabled(false);
        ui->radioPVerDEV->setChecked(true);
    }
    else
    {
        ui->radioPHorDEV->setEnabled(true);
        ui->radioPHorDEV->setChecked(true);
    }
    if(CMBProtocol::GetRhorSrvUse()) ui->radioRHorDEV->setEnabled(true);
    else ui->radioRHorDEV->setEnabled(false);
    if(CMBProtocol::GetRverSrvUse()) ui->radioRVerDEV->setEnabled(true);
    else ui->radioRVerDEV->setEnabled(false);
    // 连接信号槽
    connect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(InputMain()));
    connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    connect(time,SIGNAL(timeout()),this,SLOT(QuerySVDev()));
    time->start(1000);
	// 显示界面
//    show();
	return true;
}
// 退出伺服参数设置画面
bool Formservo::ExitForm(void)
{
	LoadPara();
	if (isModified() == true)
	{
		// 参数已经修改
		int ret = xMessageBox::DoSaveTip(tr("系统提示"), xStringResource::GetString(STRRES_SAVETIP));
		if (ret == XMSG_RET_SAVE)
		{
			// 检查参数合法性
			if (CheckValid() == false)
				return false;
			// 保存参数
			if (SavePara() == false)
				return false;
		}
		else if (ret != XMSG_RET_NOSAVE)
			return false;
	}

	// 取消信号槽连接
	disconnect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(InputMain()));
	disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    disconnect(time,SIGNAL(timeout()),this,SLOT(QuerySVDev()));

	// 隐藏界面
//	hide();
	return true;
}

// 当前登录用户更改槽
void Formservo::userChange(void)
{
	// 检查用户权限
	if ((xPermissions::GetPermissions(PER_SRV_SAFE) == false) || (xPermissions::GetPermissions(PER_SRV_MACHINE) == false))
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
	setPermissions();
}
// 系统输入信号槽
void Formservo::SetMain(bool init)
{
        if ((xIoPort::GetIn(SV_VAR_IN_OUTMOLD) != ui->LedSafeOut->on()) || (init == true))
        ui->LedSafeOut->setOn(xIoPort::GetIn(SV_VAR_IN_OUTMOLD) && (!pModbus->GetOutmoldSignalNotuse()));
            if ((xIoPort::GetIn(SV_VAR_IN_OUTMOLD) != ui->LedSafeOut2->on()) || (init == true))
        ui->LedSafeOut2->setOn(xIoPort::GetIn(SV_VAR_IN_OUTMOLD) && (!pModbus->GetOutmoldSignalNotuse()) && (pModbus->GetOutmold2use()));

        if ((xIoPort::GetIn(SV_VAR_IN_INMOLD) != ui->LedSafeIn->on()) || (init == true))
        ui->LedSafeIn->setOn(xIoPort::GetIn(SV_VAR_IN_INMOLD) && (!pModbus->GetInmoldSignalNotuse()));
        if ((xIoPort::GetIn(SV_VAR_IN_INMOLD) != ui->LedSafeIn2->on()) || (init == true))
        ui->LedSafeIn2->setOn(xIoPort::GetIn(SV_VAR_IN_INMOLD) && (!pModbus->GetInmoldSignalNotuse()));

    if ((xIoPort::GetIn(SV_VAR_IN_YWPOS) != ui->LedSafePaUp->on()) || (init == true))
        ui->LedSafePaUp->setOn(xIoPort::GetIn(SV_VAR_IN_YWPOS));
    if ((xIoPort::GetIn(SV_VAR_IN_AWPOS) != ui->LedSafeRaUp->on()) || (init == true))
        ui->LedSafeRaUp->setOn(xIoPort::GetIn(SV_VAR_IN_AWPOS));
}
void Formservo::InputMain(void)
{
	SetMain(false);
}
void Formservo::InputSafePaTrvS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
        ui->BoxSafePHorS->setValue(value);
}
void Formservo::InputSafePaTrvE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
        ui->BoxSafePHorE->setValue(value);
}
void Formservo::InputSafeRaTrvS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
        ui->BoxSafeRHorS->setValue(value);
}
void Formservo::InputSafeRaTrvE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
        ui->BoxSafeRHorE->setValue(value);
}
void Formservo::InputSafeExtS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
        ui->BoxSafeExtS->setValue(value);
}
void Formservo::InputSafeExtE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
        ui->BoxSafeExtE->setValue(value);
}
void Formservo::InputSafeExtInmoldS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
        ui->BoxSafeExtMoldS->setValue(value);
}
void Formservo::InputSafeExtInmoldE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
        ui->BoxSafeExtMoldE->setValue(value);
}

// *************************************************
// 编辑伺服行程
// *************************************************
// 输入正副臂引拔轴原点距离
void Formservo::InputHorLen(void)
{
	DialogNumberPad numberPad;
	double distance;
    if (numberPad.DoFormDouble(distance, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
	{
		ui->BoxHorLen->setValue(distance);
        try
		{
            if (pModbus->WritePaHorMacDistance(qRound(ui->BoxHorLen->value() * 100.00)))
				throw false;
			if (pModbus->CommandWrite(CMD_WRITE_SERVO))
				throw false;
		}
		catch (bool &)
		{
			xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAVE_PARA_ERROR));
			return;
		}
        ServoPara.m_machine_max_len_x = qRound(ui->BoxHorLen->value() * 100.00);
	}
}
// 输入正副臂引拔轴最小间距
void Formservo::InputHorInt(void)
{
	DialogNumberPad numberPad;
	double distance;
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (numberPad.DoFormDouble(distance, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
            ui->BoxHorInt->setValue(distance);
    }
    else
    {
        if (numberPad.DoFormDouble(distance, 0.00, ui->BoxHorLen->value()) == QDialog::Accepted)
            ui->BoxHorInt->setValue(distance);
    }
}
// 输入正臂上下软件行程
void Formservo::InputPaVerDistance(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
		ui->BoxPaVerSoftDist->setValue(value);
}
// 输入横行软件行程
void Formservo::InputTravelDistance(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
		ui->BoxTrvSoftDist->setValue(value);
}
// 输入副臂上下软件行程
void Formservo::InputRaVerDistance(void)
{
	DialogNumberPad numberPad;
	double value;
        if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
        ui->BoxRaVerSoftDist->setValue(value);
}
// 输入扩展软件行程
void Formservo::InputExtendDistance(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, 0.00, MAX_DISTANCE / 100.00) == QDialog::Accepted)
        ui->BoxExtSoftDist->setValue(value);
}
// *************************************************
// 输入伺服速度和加减速信号槽
// *************************************************
// 输入伺服速度和加减速信号槽
void Formservo::InputPaHorSpd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxPaHorSpeed->minimum(), ui->BoxPaHorSpeed->maximum()) == QDialog::Accepted)
		ui->BoxPaHorSpeed->setValue(value);
    ui->l_MaxR_PaHor->setText(QString::number(value*3000/100));
}
void Formservo::InputPaHorAcc(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxPaHorAcc->minimum(), ui->BoxPaHorAcc->maximum()) == QDialog::Accepted)
		ui->BoxPaHorAcc->setValue(value);
}
void Formservo::InputPaVerSpd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxPaVerSpeed->minimum(), ui->BoxPaVerSpeed->maximum()) == QDialog::Accepted)
		ui->BoxPaVerSpeed->setValue(value);
    ui->l_MaxR_PaVer->setText(QString::number(value*3000/100));
}
void Formservo::InputPaVerAcc(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxPaVerAcc->minimum(), ui->BoxPaVerAcc->maximum()) == QDialog::Accepted)
		ui->BoxPaVerAcc->setValue(value);
}
void Formservo::InputTrvSpd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxTrvSpeed->minimum(), ui->BoxTrvSpeed->maximum()) == QDialog::Accepted)
		ui->BoxTrvSpeed->setValue(value);
    ui->l_MaxR_Trv->setText(QString::number(value*3000/100));
}

void Formservo::InputHomeSpd(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxHomeSpeed->minimum(), ui->BoxHomeSpeed->maximum()) == QDialog::Accepted)
        ui->BoxHomeSpeed->setValue(value);
}
void Formservo::InputHomeSpdSlow(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxHomeSpeedSlow->minimum(), ui->BoxHomeSpeedSlow->maximum()) == QDialog::Accepted)
        ui->BoxHomeSpeedSlow->setValue(value);
}

void Formservo::InputParaID()
{
    DialogNumberPad numberPad;
    int value;
    if(ui->radioSelectAxisPS->isChecked())
    {
        if (numberPad.DoForm(value, 0, 20) == QDialog::Accepted)
        {
            ui->BoxParaID->setValue(value);
        }
    }
    else
    {
        if (numberPad.DoForm(value, 0, 255) == QDialog::Accepted)
        {
            ui->BoxParaID->setValue(value);
        }
    }
}

void Formservo::InputSetValue()
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxSetValue->minimum(), ui->BoxSetValue->maximum()) == QDialog::Accepted)
        ui->BoxSetValue->setValue(value);
}

void Formservo::BtnReadClick()
{
    uint16_t adr, data, cmd = 0x0100, servoID;
    adr = pRBtnSVSelect->checkedId() | ui->BoxParaID->value();
    data = ui->BoxSetValue->value();
    servoID = pRBtnSVDev->checkedId();
    if(pModbus->CommandDVS_CanRtu(adr, data, cmd, servoID) == SENDMSG_RET_ACK)
        ReadSVDev = false;
}

void Formservo::BtnWriteClick()
{
    uint16_t adr, data, cmd = 0x1000, servoID;
    adr = pRBtnSVSelect->checkedId() | ui->BoxParaID->value();
    data = ui->BoxSetValue->value();
    servoID = pRBtnSVDev->checkedId();
    if(ui->radioSelectAxisPA->isChecked())
    {
        if((adr == (AxisPA|5))||(adr == (AxisPA|6))||(adr == (AxisPA|7))||(adr == (AxisPA|8))||(adr == (AxisPA|9))||(adr == (AxisPA|19))||(adr == (AxisPA|63)))
        {
            xMessageBox::DoWarning(tr("系统提示"),tr("常用参数请到常用参数栏设置！"));
            return;
        }
    }
    pModbus->CommandDVS_CanRtu(adr, data, cmd, servoID);
}

void Formservo::QuerySVDev()
{
    if(!ReadSVDev)
    {
        if(pModbus->ReadSDOPara())
        {
            ui->BoxCurrentValue->setValue(pModbus->ReadReg16(COMMAND_SDO_RDDATA));
            ReadSVDev = true;
        }
    }
}

void Formservo::currentChanged(int page)
{
    if(ui->tabWidgetSvDev->currentIndex() == 1)
    {
        ui->radioPower->setEnabled(true);
    }
    else
    {
        ui->radioPower->setEnabled(false);
    }
}

void Formservo::InputTrvAcc(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxTrvAcc->minimum(), ui->BoxTrvAcc->maximum()) == QDialog::Accepted)
		ui->BoxTrvAcc->setValue(value);
}
void Formservo::InputRaHorSpd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxRaHorSpeed->minimum(), ui->BoxRaHorSpeed->maximum()) == QDialog::Accepted)
		ui->BoxRaHorSpeed->setValue(value);
    ui->l_MaxR_RaHor->setText(QString::number(value*3000/100));
}
void Formservo::InputRaHorAcc(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxRaHorAcc->minimum(), ui->BoxRaHorAcc->maximum()) == QDialog::Accepted)
		ui->BoxRaHorAcc->setValue(value);
}
void Formservo::InputRaVerSpd(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxRaVerSpeed->minimum(), ui->BoxRaVerSpeed->maximum()) == QDialog::Accepted)
		ui->BoxRaVerSpeed->setValue(value);
    ui->l_MaxR_RaVer->setText(QString::number(value*3000/100));
}
void Formservo::InputRaVerAcc(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxRaVerAcc->minimum(), ui->BoxRaVerAcc->maximum()) == QDialog::Accepted)
		ui->BoxRaVerAcc->setValue(value);
}
void Formservo::InputExtSpd(void)
{
	DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxExtSpeed->minimum(), ui->BoxExtSpeed->maximum()) == QDialog::Accepted)
        ui->BoxExtSpeed->setValue(value);
    ui->l_MaxR_Ext->setText(QString::number(value*3000/100));
}
void Formservo::InputExtAcc(void)
{
	DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxExtAcc->minimum(), ui->BoxExtAcc->maximum()) == QDialog::Accepted)
        ui->BoxExtAcc->setValue(value);
}
// *************************************************
// 输入Jerk位置
// *************************************************
void Formservo::InputPaHorJERK(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxPaHorJerk->minimum(), ui->BoxPaHorJerk->maximum()) == QDialog::Accepted)
        ui->BoxPaHorJerk->setValue(value);
}
void Formservo::InputPaVerJERK(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxPaVerJerk->minimum(), ui->BoxPaVerJerk->maximum()) == QDialog::Accepted)
        ui->BoxPaVerJerk->setValue(value);
}
void Formservo::InputTrvJERK(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxTrvJerk->minimum(), ui->BoxTrvJerk->maximum()) == QDialog::Accepted)
        ui->BoxTrvJerk->setValue(value);
}
void Formservo::InputRaHorJERK(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxRaHorJerk->minimum(), ui->BoxRaHorJerk->maximum()) == QDialog::Accepted)
        ui->BoxRaHorJerk->setValue(value);
}
void Formservo::InputRaVerJERK(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxRaVerJerk->minimum(), ui->BoxRaVerJerk->maximum()) == QDialog::Accepted)
        ui->BoxRaVerJerk->setValue(value);
}
void Formservo::InputExtJERK(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxExtJerk->minimum(), ui->BoxExtJerk->maximum()) == QDialog::Accepted)
        ui->BoxExtJerk->setValue(value);
}
void Formservo::InputSvDevPara()
{
    DialogNumberPad numberPad;
    int value;
    QObject *boxsender = QObject::sender();
    if(boxsender == ui->BoxPA5_DEV)
    {
        if (numberPad.DoForm(value, ui->BoxPA5_DEV->minimum(), ui->BoxPA5_DEV->maximum()) == QDialog::Accepted)
            ui->BoxPA5_DEV->setValue(value);
    }
    else if(boxsender == ui->BoxPA6_DEV)
    {
        if (numberPad.DoForm(value, ui->BoxPA6_DEV->minimum(), ui->BoxPA6_DEV->maximum()) == QDialog::Accepted)
            ui->BoxPA6_DEV->setValue(value);
    }
    else if(boxsender == ui->BoxPA7_DEV)
    {
        if (numberPad.DoForm(value, ui->BoxPA7_DEV->minimum(), ui->BoxPA7_DEV->maximum()) == QDialog::Accepted)
            ui->BoxPA7_DEV->setValue(value);
    }
    else if(boxsender == ui->BoxPA8_DEV)
    {
        if (numberPad.DoForm(value, ui->BoxPA8_DEV->minimum(), ui->BoxPA8_DEV->maximum()) == QDialog::Accepted)
            ui->BoxPA8_DEV->setValue(value);
    }
    else if(boxsender == ui->BoxPA9_DEV)
    {
        if (numberPad.DoForm(value, ui->BoxPA9_DEV->minimum(), ui->BoxPA9_DEV->maximum()) == QDialog::Accepted)
            ui->BoxPA9_DEV->setValue(value);
    }
    else if(boxsender == ui->BoxPA19_DEV)
    {
        if (numberPad.DoForm(value, ui->BoxPA19_DEV->minimum(), ui->BoxPA19_DEV->maximum()) == QDialog::Accepted)
            ui->BoxPA19_DEV->setValue(value);
    }
    else if(boxsender == ui->BoxPA63_DEV)
    {
        if (numberPad.DoForm(value, ui->BoxPA63_DEV->minimum(), ui->BoxPA63_DEV->maximum()) == QDialog::Accepted)
            ui->BoxPA63_DEV->setValue(value);
    }
}
// *************************************************
// 输入安全区位置
// *************************************************
void Formservo::InputTrvInS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvInS->minimum(), ui->BoxTrvInS->maximum()) == QDialog::Accepted)
        ui->BoxTrvInS->setValue(value);
}
void Formservo::InputTrvInE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvInE->minimum(), ui->BoxTrvInE->maximum()) == QDialog::Accepted)
        ui->BoxTrvInE->setValue(value);
}
void Formservo::InputTrvInS2(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvInS2->minimum(), ui->BoxTrvInS2->maximum()) == QDialog::Accepted)
        ui->BoxTrvInS2->setValue(value);
}
void Formservo::InputTrvInE2(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvInE2->minimum(), ui->BoxTrvInE2->maximum()) == QDialog::Accepted)
        ui->BoxTrvInE2->setValue(value);
}
void Formservo::InputTrvOutS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvOutS->minimum(), ui->BoxTrvOutS->maximum()) == QDialog::Accepted)
        ui->BoxTrvOutS->setValue(value);
}
void Formservo::InputTrvOutE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvOutE->minimum(), ui->BoxTrvOutE->maximum()) == QDialog::Accepted)
        ui->BoxTrvOutE->setValue(value);
}
void Formservo::InputSafePaUp(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxSafePaUp->minimum(), ui->BoxSafePaUp->maximum()) == QDialog::Accepted)
        ui->BoxSafePaUp->setValue(value);
}
void Formservo::InputSafeRaUp(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxSafeRaUp->minimum(), ui->BoxSafeRaUp->maximum()) == QDialog::Accepted)
        ui->BoxSafeRaUp->setValue(value);
}
void Formservo::InputSafePaHorS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxSafePaHorS->minimum(), ui->BoxSafePaHorS->maximum()) == QDialog::Accepted)
        ui->BoxSafePaHorS->setValue(value);
}
void Formservo::InputSafePaHorE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxSafePaHorE->minimum(), ui->BoxSafePaHorE->maximum()) == QDialog::Accepted)
        ui->BoxSafePaHorE->setValue(value);
}
void Formservo::InputSafeRaHorS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxSafeRaHorS->minimum(), ui->BoxSafeRaHorS->maximum()) == QDialog::Accepted)
        ui->BoxSafeRaHorS->setValue(value);
}
void Formservo::InputSafeRaHorE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxSafeRaHorE->minimum(), ui->BoxSafeRaHorE->maximum()) == QDialog::Accepted)
        ui->BoxSafeRaHorE->setValue(value);
}
void Formservo::InputTrvBackWardS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvOutS2->minimum(), ui->BoxTrvOutS2->maximum()) == QDialog::Accepted)
        ui->BoxTrvOutS2->setValue(value);
}
void Formservo::InputTrvBackWardE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvOutE2->minimum(), ui->BoxTrvOutE2->maximum()) == QDialog::Accepted)
        ui->BoxTrvOutE2->setValue(value);
}
void Formservo::InputTrvWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvWait->minimum(), ui->BoxTrvWait->maximum()) == QDialog::Accepted)
        ui->BoxTrvWait->setValue(value);
}
void Formservo::InputSafeRotS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxSafeRotS->minimum(), ui->BoxSafeRotS->maximum()) == QDialog::Accepted)
        ui->BoxSafeRotS->setValue(value);
}
void Formservo::InputSafeRotE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxSafeRotE->minimum(), ui->BoxSafeRotE->maximum()) == QDialog::Accepted)
        ui->BoxSafeRotE->setValue(value);
}
void Formservo::InputSafeTrvS(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxSafeTrvS->minimum(), ui->BoxSafeTrvS->maximum()) == QDialog::Accepted)
        ui->BoxSafeTrvS->setValue(value);
}
void Formservo::InputSafeTrvE(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxSafeTrvE->minimum(), ui->BoxSafeTrvE->maximum()) == QDialog::Accepted)
        ui->BoxSafeTrvE->setValue(value);
}
// *************************************************
// 快速定位
// *************************************************
void Formservo::InputPaHorCat(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaHorCat->minimum(), ui->BoxPaHorCat->maximum()) == QDialog::Accepted)
        ui->BoxPaHorCat->setValue(value);
}
void Formservo::InputPaHorRel(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaHorRel->minimum(), ui->BoxPaHorRel->maximum()) == QDialog::Accepted)
        ui->BoxPaHorRel->setValue(value);
}
void Formservo::InputPaHorWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaHorWait->minimum(), ui->BoxPaHorWait->maximum()) == QDialog::Accepted)
        ui->BoxPaHorWait->setValue(value);
}
void Formservo::InputPaVerCat(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaVerCat->minimum(), ui->BoxPaVerCat->maximum()) == QDialog::Accepted)
        ui->BoxPaVerCat->setValue(value);
}
void Formservo::InputPaVerRel(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaVerRel->minimum(), ui->BoxPaVerRel->maximum()) == QDialog::Accepted)
        ui->BoxPaVerRel->setValue(value);
}
void Formservo::InputPaVerWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaVerWait->minimum(), ui->BoxPaVerWait->maximum()) == QDialog::Accepted)
        ui->BoxPaVerWait->setValue(value);
}
void Formservo::InputRaHorCat(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaHorCat->minimum(), ui->BoxRaHorCat->maximum()) == QDialog::Accepted)
        ui->BoxRaHorCat->setValue(value);
}
void Formservo::InputRaHorRel(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaHorRel->minimum(), ui->BoxRaHorRel->maximum()) == QDialog::Accepted)
        ui->BoxRaHorRel->setValue(value);
}
void Formservo::InputRaHorWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaHorWait->minimum(), ui->BoxRaHorWait->maximum()) == QDialog::Accepted)
        ui->BoxRaHorWait->setValue(value);
}
void Formservo::InputRaVerCat(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaVerCat->minimum(), ui->BoxRaVerCat->maximum()) == QDialog::Accepted)
        ui->BoxRaVerCat->setValue(value);
}
void Formservo::InputRaVerRel(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaVerRel->minimum(), ui->BoxRaVerRel->maximum()) == QDialog::Accepted)
        ui->BoxRaVerRel->setValue(value);
}
void Formservo::InputRaVerWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaVerWait->minimum(), ui->BoxRaVerWait->maximum()) == QDialog::Accepted)
        ui->BoxRaVerWait->setValue(value);
}
void Formservo::InputTrvCat(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvCat->minimum(), ui->BoxTrvCat->maximum()) == QDialog::Accepted)
        ui->BoxTrvCat->setValue(value);
}
void Formservo::InputTrvRel(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvRel->minimum(), ui->BoxTrvRel->maximum()) == QDialog::Accepted)
        ui->BoxTrvRel->setValue(value);
}
void Formservo::InputTrvWait2(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvWait2->minimum(), ui->BoxTrvWait2->maximum()) == QDialog::Accepted)
        ui->BoxTrvWait2->setValue(value);
}
void Formservo::InputExtCat(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxExtCat->minimum(), ui->BoxExtCat->maximum()) == QDialog::Accepted)
        ui->BoxExtCat->setValue(value);
}
void Formservo::InputExtRel(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxExtRel->minimum(), ui->BoxExtRel->maximum()) == QDialog::Accepted)
        ui->BoxExtRel->setValue(value);
}
void Formservo::InputExtWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxExtWait->minimum(), ui->BoxExtWait->maximum()) == QDialog::Accepted)
        ui->BoxExtWait->setValue(value);
}
// *************************************************
// 原点偏移
// *************************************************
void Formservo::InputPaHorOffset(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaHorOffset->minimum(), ui->BoxPaHorOffset->maximum()) == QDialog::Accepted)
        ui->BoxPaHorOffset->setValue(value);
}
void Formservo::InputPaVerOffset(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaVerOffset->minimum(), ui->BoxPaVerOffset->maximum()) == QDialog::Accepted)
        ui->BoxPaVerOffset->setValue(value);
}
void Formservo::InputRaHorOffset(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaHorOffset->minimum(), ui->BoxRaHorOffset->maximum()) == QDialog::Accepted)
        ui->BoxRaHorOffset->setValue(value);
}
void Formservo::InputRaVerOffset(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaVerOffset->minimum(), ui->BoxRaVerOffset->maximum()) == QDialog::Accepted)
        ui->BoxRaVerOffset->setValue(value);
}
void Formservo::InputTrvOffset(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvOffset->minimum(), ui->BoxTrvOffset->maximum()) == QDialog::Accepted)
        ui->BoxTrvOffset->setValue(value);
}
void Formservo::InputExtOffset(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxExtOffset->minimum(), ui->BoxExtOffset->maximum()) == QDialog::Accepted)
        ui->BoxExtOffset->setValue(value);
}
// 输入原点待机点
void Formservo::InputPaHorHomeWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaHorHomeWait->minimum(), ui->BoxPaHorHomeWait->maximum()) == QDialog::Accepted)
        ui->BoxPaHorHomeWait->setValue(value);
}
void Formservo::InputPaVerHomeWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaVerHomeWait->minimum(), ui->BoxPaVerHomeWait->maximum()) == QDialog::Accepted)
        ui->BoxPaVerHomeWait->setValue(value);
}
void Formservo::InputTrvHomeWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvHomeWait->minimum(), ui->BoxTrvHomeWait->maximum()) == QDialog::Accepted)
        ui->BoxTrvHomeWait->setValue(value);
}
void Formservo::InputRaHorHomeWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaHorHomeWait->minimum(), ui->BoxRaHorHomeWait->maximum()) == QDialog::Accepted)
        ui->BoxRaHorHomeWait->setValue(value);
}
void Formservo::InputRaVerHomeWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaVerHomeWait->minimum(), ui->BoxRaVerHomeWait->maximum()) == QDialog::Accepted)
        ui->BoxRaVerHomeWait->setValue(value);
}
void Formservo::InputExtHomeWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxExtHomeWait->minimum(), ui->BoxExtHomeWait->maximum()) == QDialog::Accepted)
        ui->BoxExtHomeWait->setValue(value);
}
// 输入模
void Formservo::InputPaHorMod(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaHorMod->minimum(), ui->BoxPaHorMod->maximum()) == QDialog::Accepted)
        ui->BoxPaHorMod->setValue(value);
}
void Formservo::InputPaVerMod(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaVerMod->minimum(), ui->BoxPaVerMod->maximum()) == QDialog::Accepted)
        ui->BoxPaVerMod->setValue(value);
}
void Formservo::InputTrvMod(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvMod->minimum(), ui->BoxTrvMod->maximum()) == QDialog::Accepted)
        ui->BoxTrvMod->setValue(value);
}
void Formservo::InputRaHorMod(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaHorMod->minimum(), ui->BoxRaHorMod->maximum()) == QDialog::Accepted)
        ui->BoxRaHorMod->setValue(value);
}
void Formservo::InputRaVerMod(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaVerMod->minimum(), ui->BoxRaVerMod->maximum()) == QDialog::Accepted)
        ui->BoxRaVerMod->setValue(value);
}
void Formservo::InputExtMod(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxExtMod->minimum(), ui->BoxExtMod->maximum()) == QDialog::Accepted)
        ui->BoxExtMod->setValue(value);
}

// *************************************************
// 马达
// *************************************************
void Formservo::InputPaHorUnits(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaHorUnits->minimum(), ui->BoxPaHorUnits->maximum()) == QDialog::Accepted)
        ui->BoxPaHorUnits->setValue(value);
}
void Formservo::InputPaHorPluses(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaHorPluses->minimum(), ui->BoxPaHorPluses->maximum()) == QDialog::Accepted)
        ui->BoxPaHorPluses->setValue(value);
}
void Formservo::InputRaHorUnits(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaHorUnits->minimum(), ui->BoxRaHorUnits->maximum()) == QDialog::Accepted)
        ui->BoxRaHorUnits->setValue(value);
}
void Formservo::InputRaHorPluses(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaHorPluses->minimum(), ui->BoxRaHorPluses->maximum()) == QDialog::Accepted)
        ui->BoxRaHorPluses->setValue(value);
}
void Formservo::InputPaVerUnits(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaVerUnits->minimum(), ui->BoxPaVerUnits->maximum()) == QDialog::Accepted)
        ui->BoxPaVerUnits->setValue(value);
}
void Formservo::InputPaVerPluses(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaVerPluses->minimum(), ui->BoxPaVerPluses->maximum()) == QDialog::Accepted)
        ui->BoxPaVerPluses->setValue(value);
}
void Formservo::InputRaVerUnits(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaVerUnits->minimum(), ui->BoxRaVerUnits->maximum()) == QDialog::Accepted)
        ui->BoxRaVerUnits->setValue(value);
}
void Formservo::InputRaVerPluses(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaVerPluses->minimum(), ui->BoxRaVerPluses->maximum()) == QDialog::Accepted)
        ui->BoxRaVerPluses->setValue(value);
}
void Formservo::InputTrvUnits(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvUnits->minimum(), ui->BoxTrvUnits->maximum()) == QDialog::Accepted)
        ui->BoxTrvUnits->setValue(value);
}
void Formservo::InputTrvPluses(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvPluses->minimum(), ui->BoxTrvPluses->maximum()) == QDialog::Accepted)
        ui->BoxTrvPluses->setValue(value);
}
void Formservo::InputExtUnits(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxExtUnits->minimum(), ui->BoxExtUnits->maximum()) == QDialog::Accepted)
        ui->BoxExtUnits->setValue(value);
}
void Formservo::InputExtPluses(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxExtPluses->minimum(), ui->BoxExtPluses->maximum()) == QDialog::Accepted)
        ui->BoxExtPluses->setValue(value);
}
// *************************************************
// 轴类型选择框状态改变，mm与°切换
// *************************************************
void Formservo::CheckBoxPaHorChanged(void)
{
    if (ui->checkBoxPHor->isChecked())
	{
        ui->BoxPaHorUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxPaHorOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxPaHorUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxPaHorOffset->setSuffix(QString::fromUtf8("mm"));
	}
}
void Formservo::CheckBoxRaHorChanged(void)
{
    if (ui->checkBoxRHor->isChecked())
	{
        ui->BoxRaHorUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxRaHorOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxRaHorUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxRaHorOffset->setSuffix(QString::fromUtf8("mm"));
	}
}
void Formservo::CheckBoxPaVerChanged(void)
{
    if (ui->checkBoxPVer->isChecked())
	{
        ui->BoxPaVerUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxPaVerOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxPaVerUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxPaVerOffset->setSuffix(QString::fromUtf8("mm"));
	}
}
void Formservo::CheckBoxRaVerChanged(void)
{
    if (ui->checkBoxRVer->isChecked())
	{
        ui->BoxRaVerUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxRaVerOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxRaVerUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxRaVerOffset->setSuffix(QString::fromUtf8("mm"));
	}
}
void Formservo::CheckBoxTrvChanged(void)
{
    if (ui->checkBoxTrv->isChecked())
	{
        ui->BoxTrvUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxTrvOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxTrvUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxTrvOffset->setSuffix(QString::fromUtf8("mm"));
	}
}
void Formservo::CheckBoxExtChanged(void)
{
    if (ui->checkBoxExt->isChecked())
	{
        ui->BoxExtUnits->setSuffix(QString::fromUtf8("°"));
        ui->BoxExtOffset->setSuffix(QString::fromUtf8("°"));
	}
    else
	{
        ui->BoxExtUnits->setSuffix(QString::fromUtf8("mm"));
        ui->BoxExtOffset->setSuffix(QString::fromUtf8("mm"));
	}
}
// *************************************************
// 保存参数信号槽
// *************************************************
void Formservo::AcceptSetup(void)
{
	// 检查用户权限
	if ((xPermissions::GetPermissions(PER_SRV_SAFE) == false) && (xPermissions::GetPermissions(PER_SRV_MACHINE) == false))
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
		return;
	}
	LoadPara();
	if (isModified())
	{
		if (CheckValid() == false)
			return;
		if (SavePara() == false)
			return;
		// 重新备份伺服参数设置
		memcpy(&ServoParaBak, &ServoPara, sizeof(ServoParameter));
		trvRelPosBak = trvRelPos;
		trvCatPosBak = trvCatPos;
		trvWaitPosBak = trvWaitPos;
		paVerCatPosBak = paVerCatPos;
		paVerRelPosBak = paVerRelPos;
		paVerWaitPosBak = paVerWaitPos;
		paHorCatPosBak = paHorCatPos;
		paHorRelPosBak = paHorRelPos;
		paHorWaitPosBak = paHorWaitPos;
		raVerCatPosBak = raVerCatPos;
		raVerRelPosBak = raVerRelPos;
		raVerWaitPosBak = raVerWaitPos;
		raHorCatPosBak = raHorCatPos;
		raHorRelPosBak = raHorRelPos;
		raHorWaitPosBak = raHorWaitPos;
		extCatPosBak = extCatPos;
		extRelPosBak = extRelPos;
		extWaitPosBak = extWaitPos;
	}
	// 显示保存成功信息
#if UI_SAVED_TIP
	xMessageBox::DoInformation(tr("保存参数"), xStringResource::GetString(STRRES_HAS_SAVED));
#endif
}

void Formservo::ECatEncodeStateChanged(int state)
{
    QObject* encodechange = (QObject*)sender();
    if(encodechange == ui->checkBoxPHorAbsolute)
        ui->cBPaHorEncoder->setEnabled(state);
    if(encodechange == ui->checkBoxPVerAbsolute)
        ui->cBPaVerEncoder->setEnabled(state);
    if(encodechange == ui->checkBoxTrvAbsolute)
        ui->cBTrvEncoder->setEnabled(state);
    if(encodechange == ui->checkBoxRHorAbsolute)
        ui->cBRaHorEncoder->setEnabled(state);
    if(encodechange == ui->checkBoxRVerAbsolute)
        ui->cBRaVerEncoder->setEnabled(state);
    if(encodechange == ui->checkBoxExtAbsolute)
        ui->cBExtEncoder->setEnabled(state);
}
// 编码器
void Formservo::PaHorEncoderChanged(int idx)
{
    if (ui->cBoxPaHorEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxPaHorAddr->setEnabled(false);
        ui->cBPaHorEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxPaHorAddr->setEnabled(true);
        ui->cBPaHorEncoder->setEnabled(true);
    }
}
void Formservo::PaVerEncoderChanged(int idx)
{
    if (ui->cBoxPaVerEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxPaVerAddr->setEnabled(false);
        ui->cBPaVerEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxPaVerAddr->setEnabled(true);
        ui->cBPaVerEncoder->setEnabled(true);
    }
}
void Formservo::RaHorEncoderChanged(int idx)
{
    if (ui->cBoxRaHorEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxRaHorAddr->setEnabled(false);
        ui->cBRaHorEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxRaHorAddr->setEnabled(true);
        ui->cBRaHorEncoder->setEnabled(true);
    }
}
void Formservo::RaVerEncoderChanged(int idx)
{
    if (ui->cBoxRaVerEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxRaVerAddr->setEnabled(false);
        ui->cBRaVerEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxRaVerAddr->setEnabled(true);
        ui->cBRaVerEncoder->setEnabled(true);
    }
}
void Formservo::TrvEncoderChanged(int idx)
{
    if (ui->cBoxTrvEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxTrvAddr->setEnabled(false);
        ui->cBTrvEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxTrvAddr->setEnabled(true);
        ui->cBTrvEncoder->setEnabled(true);
    }
}
void Formservo::ExtEncoderChanged(int idx)
{
    if (ui->cBoxExtEncoder->currentIndex() == ENCODER_INCREMENTAL)
    {
        ui->BoxExtAddr->setEnabled(false);
        ui->cBExtEncoder->setEnabled(false);
    }
    else
    {
        ui->BoxExtAddr->setEnabled(true);
        ui->cBExtEncoder->setEnabled(true);
    }
}
void Formservo::InputPaHorAddr(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxPaHorAddr->minimum(), ui->BoxPaHorAddr->maximum()) == QDialog::Accepted)
        ui->BoxPaHorAddr->setValue(value);
}
void Formservo::InputPaVerAddr(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxPaVerAddr->minimum(), ui->BoxPaVerAddr->maximum()) == QDialog::Accepted)
        ui->BoxPaVerAddr->setValue(value);
}
void Formservo::InputRaHorAddr(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxRaHorAddr->minimum(), ui->BoxRaHorAddr->maximum()) == QDialog::Accepted)
        ui->BoxRaHorAddr->setValue(value);
}
void Formservo::InputRaVerAddr(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxRaVerAddr->minimum(), ui->BoxRaVerAddr->maximum()) == QDialog::Accepted)
        ui->BoxRaVerAddr->setValue(value);
}
void Formservo::InputTrvAddr(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxTrvAddr->minimum(), ui->BoxTrvAddr->maximum()) == QDialog::Accepted)
        ui->BoxTrvAddr->setValue(value);
}
void Formservo::InputExtAddr(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxExtAddr->minimum(), ui->BoxExtAddr->maximum()) == QDialog::Accepted)
        ui->BoxExtAddr->setValue(value);
}
void Formservo::setEncoderHomeState(void)
{
    if ((!ui->cBPaHorEncoder->isChecked()) && (!ui->cBPaVerEncoder->isChecked()) && (!ui->cBTrvEncoder->isChecked()) &&
            (!ui->cBRaHorEncoder->isChecked())  && (!ui->cBRaVerEncoder->isChecked())  && (!ui->cBExtEncoder->isChecked()))
    {
        ui->SetHomeEncoder->setEnabled(false);
        ui->ClrHomeEncoder->setEnabled(false);
    }
    else
    {
        ui->SetHomeEncoder->setEnabled(true);
        ui->ClrHomeEncoder->setEnabled(true);
    }
}
void Formservo::SetHomeEncoderClick(void)
{
    if (xMessageBox::DoAdjQuestion(tr("系统提示"), tr("此操作将设置绝对值编码器的机械原点位置，\n请确保此时绝对值编码器轴处于原点位置。\n请确保参数设置完全正确。\n设置完成后系统需要重启，可能会出现通讯错误，复位即可。\n确定设置吗？")) != XMSG_RET_YES)
        return;
    quint8 encoder;
    encoder  = ((ui->cBPaHorEncoder->isEnabled()&& ui->cBPaHorEncoder->isChecked()) ? 1: 0) << AXIS_IDX_PHOR;
    encoder |= ((ui->cBPaVerEncoder->isEnabled()&& ui->cBPaVerEncoder->isChecked()) ? 1: 0) << AXIS_IDX_PVER;
    encoder |= ((ui->cBTrvEncoder->isEnabled()&& ui->cBTrvEncoder->isChecked()) ? 1: 0) << AXIS_IDX_TRV;
    encoder |= ((ui->cBRaVerEncoder->isEnabled()&& ui->cBRaVerEncoder->isChecked()) ? 1: 0) << AXIS_IDX_RVER;
    encoder |= ((ui->cBRaHorEncoder->isEnabled()&& ui->cBRaHorEncoder->isChecked()) ? 1: 0) << AXIS_IDX_RHOR;
    encoder |= ((ui->cBExtEncoder->isEnabled()&& ui->cBExtEncoder->isChecked()) ? 1: 0) << AXIS_IDX_EXT;
    if (pModbus->CommandEncoderHome(encoder, SET_ABS_HOME) == SENDMSG_RET_ACK)
    {
        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_SET_ABS_HOME);
        xSysLog::SaveChange();
        xMessageBox::DoInformation(tr("系统提示"), tr("请重启系统。"));
    }
}
void Formservo::ClrHomeEncoderClick(void)
{
    if (xMessageBox::DoAdjQuestion(tr("系统提示"), tr("此操作将清除绝对值编码器的机械原点位置。\n设置完成后系统需要重启，可能会出现通讯错误，复位即可。\n确定设置吗？")) != XMSG_RET_YES)
        return;
    quint8 encoder;
    encoder  = ((ui->cBPaHorEncoder->isEnabled()&& ui->cBPaHorEncoder->isChecked()) ? 1: 0) << AXIS_IDX_PHOR;
    encoder |= ((ui->cBPaVerEncoder->isEnabled()&& ui->cBPaVerEncoder->isChecked()) ? 1: 0) << AXIS_IDX_PVER;
    encoder |= ((ui->cBTrvEncoder->isEnabled()&& ui->cBTrvEncoder->isChecked()) ? 1: 0) << AXIS_IDX_TRV;
    encoder |= ((ui->cBRaVerEncoder->isEnabled()&& ui->cBRaVerEncoder->isChecked()) ? 1: 0) << AXIS_IDX_RVER;
    encoder |= ((ui->cBRaHorEncoder->isEnabled()&& ui->cBRaHorEncoder->isChecked()) ? 1: 0) << AXIS_IDX_RHOR;
    encoder |= ((ui->cBExtEncoder->isEnabled()&& ui->cBExtEncoder->isChecked()) ? 1: 0) << AXIS_IDX_EXT;
    if (pModbus->CommandEncoderHome(encoder, CLR_ABS_HOME) == SENDMSG_RET_ACK)
    {
        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_CLR_ABS_HOME);
        xSysLog::SaveChange();
        xMessageBox::DoInformation(tr("系统提示"), tr("请重启系统。"));
    }
}
void Formservo::updataSvDevPara(int idx)
{
    LoadSvDevPara(SvDevParaPage);
    SvDevParaPage = idx;
    showSVDevPara(idx);
}

void Formservo::LoadSvDevPara(int idx)
{
    switch (idx)//pRBtnSVDev->checkedId()
    {
    case AXES_IDX_X:
        (ServoPara.m_pa5_x = ui->BoxPA5_DEV->value());
        (ServoPara.m_pa6_x = ui->BoxPA6_DEV->value());
        (ServoPara.m_pa7_x = ui->BoxPA7_DEV->value());
        (ServoPara.m_pa8_x = ui->BoxPA8_DEV->value());
        (ServoPara.m_pa9_x = ui->BoxPA9_DEV->value());
        (ServoPara.m_pa19_x = ui->BoxPA19_DEV->value());
		(ServoPara.m_pa63_x = ui->BoxPA63_DEV->value());
    break;
    case AXES_IDX_Y:
        (ServoPara.m_pa5_y = ui->BoxPA5_DEV->value());
        (ServoPara.m_pa6_y = ui->BoxPA6_DEV->value());
        (ServoPara.m_pa7_y = ui->BoxPA7_DEV->value());
        (ServoPara.m_pa8_y = ui->BoxPA8_DEV->value());
        (ServoPara.m_pa9_y = ui->BoxPA9_DEV->value());
        (ServoPara.m_pa19_y = ui->BoxPA19_DEV->value());
		(ServoPara.m_pa63_y = ui->BoxPA63_DEV->value());
    break;
    case AXES_IDX_Z:
        (ServoPara.m_pa5_z = ui->BoxPA5_DEV->value());
        (ServoPara.m_pa6_z = ui->BoxPA6_DEV->value());
        (ServoPara.m_pa7_z = ui->BoxPA7_DEV->value());
        (ServoPara.m_pa8_z = ui->BoxPA8_DEV->value());
        (ServoPara.m_pa9_z = ui->BoxPA9_DEV->value());
        (ServoPara.m_pa19_z = ui->BoxPA19_DEV->value());
		(ServoPara.m_pa63_z = ui->BoxPA63_DEV->value());
    break;
    case AXES_IDX_A:
        (ServoPara.m_pa5_a = ui->BoxPA5_DEV->value());
        (ServoPara.m_pa6_a = ui->BoxPA6_DEV->value());
        (ServoPara.m_pa7_a = ui->BoxPA7_DEV->value());
        (ServoPara.m_pa8_a = ui->BoxPA8_DEV->value());
        (ServoPara.m_pa9_a = ui->BoxPA9_DEV->value());
        (ServoPara.m_pa19_a = ui->BoxPA19_DEV->value());
		(ServoPara.m_pa63_a = ui->BoxPA63_DEV->value());
    break;
    case AXES_IDX_B:
        (ServoPara.m_pa5_b = ui->BoxPA5_DEV->value());
        (ServoPara.m_pa6_b = ui->BoxPA6_DEV->value());
        (ServoPara.m_pa7_b = ui->BoxPA7_DEV->value());
        (ServoPara.m_pa8_b = ui->BoxPA8_DEV->value());
        (ServoPara.m_pa9_b = ui->BoxPA9_DEV->value());
        (ServoPara.m_pa19_b = ui->BoxPA19_DEV->value());
		(ServoPara.m_pa63_b = ui->BoxPA63_DEV->value());
    break;
    }

}
void Formservo::setCurrentpage(int idx)
{
    idx = pBtnPage->checkedId();
    switch (idx)
    {
    case SRVPG_SAFE:
        ui->stackedWidget->setCurrentIndex(SRVPG_SAFE);
        ui->radioSafe->setEnabled(false);
        ui->radioSafe2->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioQuick->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioPaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioPaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioTrv->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioHome->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioExt->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioSafe->setStyleSheet("border-image: url(:/img/widget/green.png);");
        ui->radioSafe2->setStyleSheet("");
        ui->radioQuick->setStyleSheet("");
        ui->radioPaHor->setStyleSheet("");
        ui->radioPaVer->setStyleSheet("");
        ui->radioTrv->setStyleSheet("");
        ui->radioRaHor->setStyleSheet("");
        ui->radioRaVer->setStyleSheet("");
        ui->radioHome->setStyleSheet("");
        ui->radioExt->setStyleSheet("");
        break;
    case SRVPG_SHORTCUT:
        ui->stackedWidget->setCurrentIndex(SRVPG_SHORTCUT);
        ui->radioSafe->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioSafe2->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioQuick->setEnabled(false);
        ui->radioPaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioPaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioTrv->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioHome->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioExt->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioQuick->setStyleSheet("border-image: url(:/img/widget/green.png);");
        ui->radioSafe->setStyleSheet("");
        ui->radioSafe2->setStyleSheet("");
        ui->radioPaHor->setStyleSheet("");
        ui->radioPaVer->setStyleSheet("");
        ui->radioTrv->setStyleSheet("");
        ui->radioRaHor->setStyleSheet("");
        ui->radioRaVer->setStyleSheet("");
        ui->radioHome->setStyleSheet("");
        ui->radioExt->setStyleSheet("");
        break;
    case SRVPG_PAHOR:
        ui->stackedWidget->setCurrentIndex(SRVPG_PAHOR);
        ui->radioSafe->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioSafe2->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioQuick->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioPaHor->setEnabled(false);
        ui->radioPaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioTrv->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioHome->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioExt->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioQuick->setStyleSheet("");
        ui->radioSafe->setStyleSheet("");
        ui->radioSafe2->setStyleSheet("");
        ui->radioPaHor->setStyleSheet("border-image: url(:/img/widget/green.png);");
        ui->radioPaVer->setStyleSheet("");
        ui->radioTrv->setStyleSheet("");
        ui->radioRaHor->setStyleSheet("");
        ui->radioRaVer->setStyleSheet("");
        ui->radioHome->setStyleSheet("");
        ui->radioExt->setStyleSheet("");
        break;
    case SRVPG_PAVER:
        ui->stackedWidget->setCurrentIndex(SRVPG_PAVER);
        ui->radioSafe->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioSafe2->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioQuick->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioPaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioPaVer->setEnabled(false);
        ui->radioTrv->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioHome->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioExt->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioSafe2->setStyleSheet("");
        ui->radioQuick->setStyleSheet("");
        ui->radioSafe->setStyleSheet("");
        ui->radioPaHor->setStyleSheet("");
        ui->radioPaVer->setStyleSheet("border-image: url(:/img/widget/green.png);");
        ui->radioTrv->setStyleSheet("");
        ui->radioRaHor->setStyleSheet("");
        ui->radioRaVer->setStyleSheet("");
        ui->radioHome->setStyleSheet("");
        ui->radioExt->setStyleSheet("");
        break;
    case SRVPG_TRAVEL:
        ui->stackedWidget->setCurrentIndex(SRVPG_TRAVEL);
        ui->radioSafe->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioSafe2->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioQuick->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioPaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioPaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioTrv->setEnabled(false);
        ui->radioRaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioHome->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioExt->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioQuick->setStyleSheet("");
        ui->radioSafe->setStyleSheet("");
        ui->radioPaHor->setStyleSheet("");
        ui->radioPaVer->setStyleSheet("");
        ui->radioTrv->setStyleSheet("border-image: url(:/img/widget/green.png);");
        ui->radioRaHor->setStyleSheet("");
        ui->radioRaVer->setStyleSheet("");
        ui->radioHome->setStyleSheet("");
        ui->radioExt->setStyleSheet("");
        ui->radioSafe2->setStyleSheet("");
        break;
    case SRVPG_RAHOR:
        ui->stackedWidget->setCurrentIndex(SRVPG_RAHOR);
        ui->radioSafe->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioSafe2->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioQuick->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioPaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioPaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioTrv->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaHor->setEnabled(false);
        ui->radioRaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioHome->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioExt->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioQuick->setStyleSheet("");
        ui->radioSafe->setStyleSheet("");
        ui->radioPaHor->setStyleSheet("");
        ui->radioPaVer->setStyleSheet("");
        ui->radioTrv->setStyleSheet("");
        ui->radioRaHor->setStyleSheet("border-image: url(:/img/widget/green.png);");
        ui->radioRaVer->setStyleSheet("");
        ui->radioHome->setStyleSheet("");
        ui->radioExt->setStyleSheet("");
        ui->radioSafe2->setStyleSheet("");
        break;
    case SRVPG_RAVER:
        ui->stackedWidget->setCurrentIndex(SRVPG_RAVER);
        ui->radioSafe->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioSafe2->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioQuick->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioPaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioPaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioTrv->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaVer->setEnabled(false);
        ui->radioHome->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioExt->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioQuick->setStyleSheet("");
        ui->radioSafe->setStyleSheet("");
        ui->radioPaHor->setStyleSheet("");
        ui->radioPaVer->setStyleSheet("");
        ui->radioTrv->setStyleSheet("");
        ui->radioRaHor->setStyleSheet("");
        ui->radioRaVer->setStyleSheet("border-image: url(:/img/widget/green.png);");
        ui->radioHome->setStyleSheet("");
        ui->radioExt->setStyleSheet("");
        ui->radioSafe2->setStyleSheet("");
        break;
    case SRVPG_EXTEND:
        ui->stackedWidget->setCurrentIndex(SRVPG_EXTEND);
        ui->radioSafe->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioSafe2->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioQuick->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioPaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioPaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioTrv->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioHome->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioExt->setEnabled(false);
        ui->radioQuick->setStyleSheet("");
        ui->radioSafe->setStyleSheet("");
        ui->radioPaHor->setStyleSheet("");
        ui->radioPaVer->setStyleSheet("");
        ui->radioTrv->setStyleSheet("");
        ui->radioRaHor->setStyleSheet("");
        ui->radioRaVer->setStyleSheet("");
        ui->radioHome->setStyleSheet("");
        ui->radioExt->setStyleSheet("border-image: url(:/img/widget/green.png);");
        ui->radioSafe2->setStyleSheet("");
        break;
    case SRVPG_HOME:
        ui->stackedWidget->setCurrentIndex(SRVPG_HOME);
        ui->radioSafe->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioSafe2->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioQuick->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioPaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioPaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioTrv->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioHome->setEnabled(false);
        ui->radioExt->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioQuick->setStyleSheet("");
        ui->radioSafe->setStyleSheet("");
        ui->radioPaHor->setStyleSheet("");
        ui->radioPaVer->setStyleSheet("");
        ui->radioTrv->setStyleSheet("");
        ui->radioRaHor->setStyleSheet("");
        ui->radioRaVer->setStyleSheet("");
        ui->radioHome->setStyleSheet("border-image: url(:/img/widget/green.png);");
        ui->radioExt->setStyleSheet("");
        ui->radioSafe2->setStyleSheet("");
        break;
    case SRVPG_SAFE2:
        ui->stackedWidget->setCurrentIndex(SRVPG_SAFE2);
        ui->radioSafe->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioSafe2->setEnabled(false);
        ui->radioQuick->setEnabled(xPermissions::GetPermissions(PER_SRV_SAFE));
        ui->radioPaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioPaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioTrv->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaHor->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioRaVer->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioHome->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioExt->setEnabled(xPermissions::GetPermissions(PER_SRV_MACHINE));
        ui->radioQuick->setStyleSheet("");
        ui->radioSafe->setStyleSheet("");
        ui->radioPaHor->setStyleSheet("");
        ui->radioPaVer->setStyleSheet("");
        ui->radioTrv->setStyleSheet("");
        ui->radioRaHor->setStyleSheet("");
        ui->radioRaVer->setStyleSheet("");
        ui->radioHome->setStyleSheet("");
        ui->radioExt->setStyleSheet("");
        ui->radioSafe2->setStyleSheet("border-image: url(:/img/widget/green.png);");
        break;
    }
}
