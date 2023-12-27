#include <QButtonGroup>
#include "xpermissions.h"
#include "dialogframe.h"
#include "formadjust.h"
#include "xKeyPad.h"
#include "ui_formadjust.h"
#include "xioport.h"
#include "safeswitch.h"
#include "xsystemlog.h"
#include "xstringresource.h"
#include "xmessagebox.h"
#include "dialognumberpad.h"
#include "servoalias.h"
#include "indicatorled.h"

#define SVADJ_STOP		0
#define SVADJ_CW		1
#define SVADJ_CCW		2

extern DialogFrame *pDialogMain;

FormAdjust::FormAdjust(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormAdjust)
{
	// 初始化界面
	ui->setupUi(this);
	retranslateUi();
	// 初始化协议
	pModbus = modbus;
	// 组织气动调位按钮组
//	pPneCcw = new QButtonGroup;
//	pPneCcw->addButton(ui->BtnRaUpCcw, ADJUST_MOTOR_IDX_UP);
//	pPneCcw->addButton(ui->BtnRaPosCcw, ADJUST_MOTOR_IDX_POS);
//	pPneCcw->addButton(ui->BtnRaLenCcw, ADJUST_MOTOR_IDX_LEN);
//	pPneCcw->setExclusive(false);
//	pPneCw = new QButtonGroup;
//	pPneCw->addButton(ui->BtnRaUpCw, ADJUST_MOTOR_IDX_UP);
//	pPneCw->addButton(ui->BtnRaPosCw, ADJUST_MOTOR_IDX_POS);
//	pPneCw->addButton(ui->BtnRaLenCw, ADJUST_MOTOR_IDX_LEN);
//	pPneCw->setExclusive(false);
//	ui->BtnRaPosCcw->setVisible(false);
//	ui->BtnRaLenCcw->setVisible(false);
//	ui->BtnRaPosCw->setVisible(false);
//	ui->BtnRaLenCw->setVisible(false);
//	ui->labelRarmPos->setVisible(false);
//	ui->labelRarmLen->setVisible(false);
    // 连接气动调位信号槽
//	connect(pPneCcw, SIGNAL(buttonPressed(int)), this, SLOT(PneAdjCcw(int)));
//	connect(pPneCw, SIGNAL(buttonPressed(int)), this, SLOT(PneAdjCw(int)));
//	connect(pPneCcw, SIGNAL(buttonReleased(int)), this, SLOT(PneAdjStop(int)));
//	connect(pPneCw, SIGNAL(buttonReleased(int)), this, SLOT(PneAdjStop(int)));

    connect(ui->BtnPaHorCcw, SIGNAL(pressed()), this, SLOT(SvPaHorCcw()));
    connect(ui->BtnPaHorCw, SIGNAL(pressed()), this, SLOT(SvPaHorCw()));
    connect(ui->BtnPaVerCcw, SIGNAL(pressed()), this, SLOT(SvPaVerCcw()));
    connect(ui->BtnPaVerCw, SIGNAL(pressed()), this, SLOT(SvPaVerCw()));
    connect(ui->BtnTravelCcw, SIGNAL(pressed()), this, SLOT(SvTrvCcw()));
    connect(ui->BtnTravelCw, SIGNAL(pressed()), this, SLOT(SvTrvCw()));
    connect(ui->BtnRaHorCcw, SIGNAL(pressed()), this, SLOT(SvRaHorCcw()));
    connect(ui->BtnRaHorCw, SIGNAL(pressed()), this, SLOT(SvRaHorCw()));
    connect(ui->BtnRaVerCcw, SIGNAL(pressed()), this, SLOT(SvRaVerCcw()));
    connect(ui->BtnRaVerCw, SIGNAL(pressed()), this, SLOT(SvRaVerCw()));
    connect(ui->BtnExtCcw, SIGNAL(pressed()), this, SLOT(SvExtCcw()));
    connect(ui->BtnExtCw, SIGNAL(pressed()), this, SLOT(SvExtCw()));

    connect(ui->BtnPaHorCcw, SIGNAL(released()), this, SLOT(SvPHorCcwStop()));
    connect(ui->BtnPaHorCw, SIGNAL(released()), this, SLOT(SvPHorCwStop()));
    connect(ui->BtnPaVerCcw, SIGNAL(released()), this, SLOT(SvPVerCcwStop()));
    connect(ui->BtnPaVerCw, SIGNAL(released()), this, SLOT(SvPVerCwStop()));
    connect(ui->BtnTravelCcw, SIGNAL(released()), this, SLOT(SvTrvCcwStop()));
    connect(ui->BtnTravelCw, SIGNAL(released()), this, SLOT(SvTrvCwStop()));
    connect(ui->BtnRaHorCcw, SIGNAL(released()), this, SLOT(SvRHorCcwStop()));
    connect(ui->BtnRaHorCw, SIGNAL(released()), this, SLOT(SvRHorCwStop()));
    connect(ui->BtnRaVerCcw, SIGNAL(released()), this, SLOT(SvRVerCcwStop()));
    connect(ui->BtnRaVerCw, SIGNAL(released()), this, SLOT(SvRVerCwStop()));
    connect(ui->BtnExtCcw, SIGNAL(released()), this, SLOT(SvExtCcwStop()));
    connect(ui->BtnExtCw, SIGNAL(released()), this, SLOT(SvExtCwStop()));

    m_havesendservocmd = false;
    m_ptimer = new QTimer();
    connect(m_ptimer,SIGNAL(timeout()),this,SLOT(StopTimer()));
}

FormAdjust::~FormAdjust()
{
	delete ui;
//	delete pPneCcw;
//	delete pPneCw;
}

void FormAdjust::changeEvent(QEvent *e)
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

void FormAdjust::retranslateUi(void)
{
	ui->labelHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴"));
	ui->labelVer->setText(GetServoName(AXIS_IDX_PVER) + tr("轴"));
	ui->labelTravel->setText(GetServoName(AXIS_IDX_TRV) + tr("轴"));
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        ui->labelServoA->setText(GetServoName(AXIS_IDX_RHOR) + tr("(旋转)轴"));
        ui->labelServoB->setText(GetServoName(AXIS_IDX_RVER) + tr("(倒角)轴"));
    }
    else
    {
        ui->labelServoA->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴"));
        ui->labelServoB->setText(GetServoName(AXIS_IDX_RVER) + tr("轴"));
    }
    ui->labelServoC->setText(GetServoName(AXIS_IDX_EXT) + tr("轴"));

    ui->BtnPaHorCcw->setText("-");	ui->BtnPaHorCw->setText("+");
    ui->BtnPaVerCcw->setText("-");	ui->BtnPaVerCw->setText("+");
    ui->BtnTravelCcw->setText("-");	ui->BtnTravelCw->setText("+");
    ui->BtnRaHorCcw->setText("-");	ui->BtnRaHorCw->setText("+");
    ui->BtnRaVerCcw->setText("-");	ui->BtnRaVerCw->setText("+");
    ui->BtnExtCcw->setText("-");	ui->BtnExtCw->setText("+");

    if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        ui->checkBoxJig03->setText(xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->checkBoxJig04->setText(xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->checkBoxJig05->setText(xStringResource::GetVarName(MAIN_VAR_Y14));
    }
    else
    {
        ui->checkBoxJig03->setText(xStringResource::GetVarName(EM1_VAR_Y02));
        ui->checkBoxJig04->setText(xStringResource::GetVarName(EM1_VAR_Y03));
        ui->checkBoxJig05->setText(xStringResource::GetVarName(EM1_VAR_Y04));
        ui->checkBoxJig06->setText(xStringResource::GetVarName(EM1_VAR_Y05));
        ui->checkBoxJig07->setText(xStringResource::GetVarName(EM1_VAR_Y06));
        ui->checkBoxJig08->setText(xStringResource::GetVarName(EM1_VAR_Y07));
    }
}

// 设置界面状态
void FormAdjust::setPermissions(quint16 refState)
{
	if (xPermissions::GetPermissions(PER_ADJ_CTRL) == false)
	{
		// 登录用户没有调位权限
        ui->groupBoxServo->setEnabled(false);
        ui->groupBoxPneumatic->setEnabled(false);
    }
	else
	{
        ui->groupBoxServo->setEnabled(pModbus->GetSysState() != SYS_STATE_AUTO);
        ui->groupBoxPneumatic->setEnabled(pModbus->GetSysState() != SYS_STATE_AUTO);
    }
}

// 进入调位操作画面
bool FormAdjust::EnterForm(void)
{
    int i;
    // 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return false;
	}
    // 检查用户权限
    if (xPermissions::GetPermissions(PER_ADJ_CTRL) == false)
    {
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (pDialogMain)
            if (pDialogMain->ScreenSaverUserManager() == 0)
        return false;
    }
#if SELECT_SWITCH_USE
    // 检查选择开关
	if (pxKeyPad->GetSwitch() != CUSKEY_SEL_MANUAL)
    {
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), tr("选择开关不在手动状态不能进行调位操作！"));
        return false;
    }
#endif
    // 如果系统不在手动状态则不能进入调位操作画面
    if (pModbus->GetSysState() == SYS_STATE_AUTO)
	{
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), tr("机械手在自动状态时，不能进行调位操作！"));
		return false;
	}
#if ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_YIDAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE) || (FACTORY == FA_SINROBOT_4AS_YZ))
    if (xMessageBox::DoAdjQuestion(tr("系统提示"), tr("调位操作时，\n压铸机顶针、开模、关模等操作将禁止, \n机械手不进行任何安全检测，操作由用户掌控， \n一切后果将由用户负责， \n确定进入吗？")) != XMSG_RET_YES)
        return false;
#elif FACTORY == FA_SINROBOT_JC
    if (xMessageBox::DoAdjQuestion(tr("系统提示"), tr("调位操作时，\n机床顶针、开模、关模等操作将禁止, \n机械手不进行任何安全检测，操作由用户掌控， \n一切后果将由用户负责， \n确定进入吗？")) != XMSG_RET_YES)
        return false;
#else
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        if (xMessageBox::DoAdjQuestion(tr("系统提示"), tr("调位操作时，\n压铸机顶针、开模、关模等操作将禁止, \n机械手不进行任何安全检测，操作由用户掌控， \n一切后果将由用户负责， \n确定进入吗？")) != XMSG_RET_YES)
            return false;
    }
    else
    {
        if (xMessageBox::DoAdjQuestion(tr("系统提示"), tr("调位操作时，\n注塑机顶针、开模、关模等操作将禁止, \n机械手不进行任何安全检测，操作由用户掌控， \n一切后果将由用户负责， \n确定进入吗？")) != XMSG_RET_YES)
            return false;
    }
#endif
    // 进入JOG模式
    if (pModbus->SetSysState(SYS_STATE_JOG) != SENDMSG_RET_ACK)
    {
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), tr("机械手无法切到JOG模式！"));
		return false;
	}
//	pModbus->MBPeriodPoll();
	// 设置界面状态
    setPermissions(pModbus->GetHomeState());
    // 初始化界面IO端口显示状态
	uint64_t input;
	input = pModbus->GetInMain();
	SetMain(true);
    retranslateUi();
    // 进入界面设置位置改变为false
    for (i = 0; i < 6; i++)
        posChanged[i] = false;
    ui->BtnPaHorCcw->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BtnPaHorCw->setEnabled(!pModbus->GetPaHorNotUse());
    ui->BtnRaHorCcw->setEnabled(pModbus->GetRhorSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BtnRaHorCw->setEnabled(pModbus->GetRhorSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->BtnExtCcw->setEnabled(pModbus->GetExtSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BtnExtCw->setEnabled(pModbus->GetExtSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    ui->BtnRaVerCcw->setEnabled(pModbus->GetRverSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->BtnRaVerCw->setEnabled(pModbus->GetRverSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
//	ui->labelRarmUp->setEnabled(pModbus->GetRunnerUse());
//	ui->BtnRaUpCcw->setEnabled(pModbus->GetRunnerUse());
//	ui->BtnRaUpCw->setEnabled(pModbus->GetRunnerUse());

	ui->BtnRaHor->setVisible(CMBProtocol::GetRunRotateUse());
	ui->BtnRaVer->setVisible(CMBProtocol::GetRunRotateUse());
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        ui->checkBoxJig03->setVisible(true);
        ui->checkBoxJig04->setVisible(true);
        ui->checkBoxJig05->setVisible(true);
        ui->checkBoxJig06->setVisible(false);
        ui->checkBoxJig07->setVisible(false);
        ui->checkBoxJig08->setVisible(false);

        ui->checkBoxJig03->setChecked(true);
        ui->checkBoxJig04->setChecked(true);
        ui->checkBoxJig05->setChecked(true);
    }
    else
    {
        ui->checkBoxJig03->setVisible(true);
        ui->checkBoxJig04->setVisible(true);
        ui->checkBoxJig05->setVisible(true);
        ui->checkBoxJig06->setVisible(true);
        ui->checkBoxJig07->setVisible(true);
        ui->checkBoxJig08->setVisible(true);

        ui->checkBoxJig03->setChecked(true);
        ui->checkBoxJig04->setChecked(true);
        ui->checkBoxJig05->setChecked(true);
        ui->checkBoxJig06->setChecked(true);
        ui->checkBoxJig07->setChecked(true);
        ui->checkBoxJig08->setChecked(true);
    }
	// 手臂输出
	ui->BtnPaHor->setText(xStringResource::GetVarName(RBT_VAR_OUT_PRO_HOR));
	ui->BtnPaVer->setText(xStringResource::GetVarName(RBT_VAR_OUT_PRO_VER));
	ui->BtnRaHor->setText(xStringResource::GetVarName(RBT_VAR_OUT_RUN_HOR));
	ui->BtnRaVer->setText(xStringResource::GetVarName(RBT_VAR_OUT_RUN_VER));
	ui->BtnRaDes->setText(xStringResource::GetVarName(RBT_VAR_OUT_RUN_DES));
	ui->BtnRaRet->setText(xStringResource::GetVarName(RBT_VAR_OUT_RUN_RET));

	// 连接信号槽
	connect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(InputMain()));
	connect(pModbus, SIGNAL(signal_OutputChange()), this, SLOT(SetOutIO()));
	connect(pModbus, SIGNAL(signal_HomeStateChange(uint16_t)), this, SLOT(SvReferState(uint16_t)));
	connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 显示界面
	SetOutIO();
//	show();
//    qDebug() << "FormAdjust::EnterForm";
	return true;
}

// 退出调位操作画面
bool FormAdjust::ExitForm(void)
{
    if (posChanged[AXIS_IDX_PHOR] == true)
    {
        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_ADJ_PHORCHG);
        xSysLog::SaveChange();
    }
    if (posChanged[AXIS_IDX_PVER] == true)
    {
        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_ADJ_PVERCHG);
        xSysLog::SaveChange();
    }
    if (posChanged[AXIS_IDX_TRV] == true)
    {
        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_ADJ_TRVCHG);
        xSysLog::SaveChange();
    }
    if (posChanged[AXIS_IDX_RHOR] == true)
    {
        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_ADJ_RHORCHG);
        xSysLog::SaveChange();
    }
    if (posChanged[AXIS_IDX_RVER] == true)
    {
        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_ADJ_RVERCHG);
        xSysLog::SaveChange();
    }
    if (posChanged[AXIS_IDX_EXT] == true)
    {
        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_ADJ_EXTCHG);
        xSysLog::SaveChange();
    }
    // 取消信号槽连接
	disconnect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(InputMain()));
	disconnect(pModbus, SIGNAL(signal_OutputChange()), this, SLOT(SetOutIO()));
	disconnect(pModbus, SIGNAL(signal_HomeStateChange(uint16_t)), this, SLOT(SvReferState(uint16_t)));
	disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    if (pModbus->SetSysState(SYS_STATE_MANUAL) != SENDMSG_RET_ACK)
    {
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), tr("机械手没有切回手动状态！"));
        return false;
    }
    // 隐藏界面
//	hide();
	return true;
}

// 当前登录用户更改槽
void FormAdjust::userChange(void)
{
	if (xPermissions::GetPermissions(PER_ADJ_CTRL) == false)
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
    setPermissions(pModbus->GetHomeState());
}
// 系统原点复归状态信号槽
void FormAdjust::SvReferState(uint16_t state)
{
	setPermissions(state);
}
// 伺服输入信号槽
void FormAdjust::SetMain(bool init)
{
	if ((xIoPort::GetIn(SV_VAR_IN_XHOME) != ui->LedPaHorHome->on()) || (init == true))
		ui->LedPaHorHome->setOn(xIoPort::GetIn(SV_VAR_IN_XHOME));
	if ((xIoPort::GetIn(SV_VAR_IN_XCCWL) != ui->LedPaHorCcwL->on()) || (init == true))
		ui->LedPaHorCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_XCCWL));
	if ((xIoPort::GetIn(SV_VAR_IN_XCWL) != ui->LedPaHorCwL->on()) || (init == true))
		ui->LedPaHorCwL->setOn(xIoPort::GetIn(SV_VAR_IN_XCWL));
	if ((xIoPort::GetIn(SV_VAR_IN_YHOME) != ui->LedPaVerHome->on()) || (init == true))
		ui->LedPaVerHome->setOn(xIoPort::GetIn(SV_VAR_IN_YHOME));
	if ((xIoPort::GetIn(SV_VAR_IN_YCCWL) != ui->LedPaVerCcwL->on()) || (init == true))
		ui->LedPaVerCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_YCCWL));
	if ((xIoPort::GetIn(SV_VAR_IN_YCWL) != ui->LedPaVerCwL->on()) || (init == true))
		ui->LedPaVerCwL->setOn(xIoPort::GetIn(SV_VAR_IN_YCWL));
	if ((xIoPort::GetIn(SV_VAR_IN_ZHOME) != ui->LedTrvHome->on()) || (init == true))
		ui->LedTrvHome->setOn(xIoPort::GetIn(SV_VAR_IN_ZHOME));
	if ((xIoPort::GetIn(SV_VAR_IN_ZCCWL) != ui->LedTrvCcwL->on()) || (init == true))
		ui->LedTrvCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_ZCCWL));
	if ((xIoPort::GetIn(SV_VAR_IN_ZCWL) != ui->LedTrvCwL->on()) || (init == true))
		ui->LedTrvCwL->setOn(xIoPort::GetIn(SV_VAR_IN_ZCWL));
	if ((xIoPort::GetIn(SV_VAR_IN_BHOME) != ui->LedRaHorHome->on()) || (init == true))
		ui->LedRaHorHome->setOn(xIoPort::GetIn(SV_VAR_IN_BHOME));
	if ((xIoPort::GetIn(SV_VAR_IN_BCCWL) != ui->LedRaHorCcwL->on()) || (init == true))
		ui->LedRaHorCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_BCCWL));
	if ((xIoPort::GetIn(SV_VAR_IN_BCWL) != ui->LedRaHorCwL->on()) || (init == true))
		ui->LedRaHorCwL->setOn(xIoPort::GetIn(SV_VAR_IN_BCWL));
	if ((xIoPort::GetIn(SV_VAR_IN_AHOME) != ui->LedRaVerHome->on()) || (init == true))
		ui->LedRaVerHome->setOn(xIoPort::GetIn(SV_VAR_IN_AHOME));
	if ((xIoPort::GetIn(SV_VAR_IN_ACCWL) != ui->LedRaVerCcwL->on()) || (init == true))
		ui->LedRaVerCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_ACCWL));
	if ((xIoPort::GetIn(SV_VAR_IN_ACWL) != ui->LedRaVerCwL->on()) || (init == true))
		ui->LedRaVerCwL->setOn(xIoPort::GetIn(SV_VAR_IN_ACWL));
	if ((xIoPort::GetIn(SV_VAR_IN_CHOME) != ui->LedExtHome->on()) || (init == true))
		ui->LedExtHome->setOn(xIoPort::GetIn(SV_VAR_IN_CHOME));
	if ((xIoPort::GetIn(SV_VAR_IN_CCCWL) != ui->LedExtCcwL->on()) || (init == true))
		ui->LedExtCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_CCCWL));
	if ((xIoPort::GetIn(SV_VAR_IN_CCWL) != ui->LedExtCwL->on()) || (init == true))
		ui->LedExtCwL->setOn(xIoPort::GetIn(SV_VAR_IN_CCWL));
}
void FormAdjust::InputMain()
{
	SetMain(false);
}

bool FormAdjust::checkManual(void)
{
#if SELECT_SWITCH_USE
    if (pModbus->GetSelectUse())
    {
    // 检查选择开关
	if (pxKeyPad->GetSwitch() != CUSKEY_SEL_MANUAL)
    {
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), tr("选择开关不在手动状态不能进行调位操作！"));
            return false;
        }
    }
#endif
    // 检查安全开关
    if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
    {
#if UI_SAFESW_TIP
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAFESW_TIP));
#endif
        return false;
    }
    return true;
}

// 伺服调位信号槽
void FormAdjust::SvPaHorCcw(void)
{
    if (!checkManual())
        return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvPaHorCw(void)
{
    if (!checkManual())
        return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvPaVerCcw(void)
{
    if (!checkManual())
            return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvPaVerCw(void)
{
    if (!checkManual())
            return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvTrvCcw(void)
{
    if (!checkManual())
        return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvTrvCw(void)
{
    if (!checkManual())
        return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvRaHorCcw(void)
{
    if (!checkManual())
        return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvRaHorCw(void)
{
    if (!checkManual())
        return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvRaVerCcw(void)
{
    if (!checkManual())
            return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvRaVerCw(void)
{
    if (!checkManual())
            return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvExtCcw(void)
{
    if (!checkManual())
        return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::SvExtCw(void)
{
    if (!checkManual())
            return;
    m_havesendservocmd = false;
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
        m_ptimer->start(200);
    else
        m_ptimer->start(100);
}
void FormAdjust::StopTimer(void)
{
    if (ui->BtnPaHorCcw->isDown()||ui->BtnPaHorCw->isDown()||ui->BtnPaVerCcw->isDown()||ui->BtnPaVerCw->isDown()||ui->BtnRaHorCcw->isDown()||ui->BtnRaHorCw->isDown()||
        ui->BtnRaVerCcw->isDown()||ui->BtnRaVerCw->isDown()||ui->BtnTravelCcw->isDown()||ui->BtnTravelCw->isDown()||ui->BtnExtCcw->isDown()||ui->BtnExtCw->isDown())
    {
        if (!m_havesendservocmd)
        {
            quint16 spd = ui->spinBox->value();
            if (pModbus->IsHasRefer(pModbus->GetHomeState()))
            {
                if (ui->BtnPaHorCw->isDown())
                {
                    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4) || (!CMBProtocol::GetRhorSrvUse()))
                    {
                    if (pModbus->ManualPos(spd, SRV_PAHOR, pModbus->GetHorLen(), SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_PHOR] = true;
                }
                    else
                    {
                        if (pModbus->ManualPos(spd, SRV_PAHOR, (pModbus->GetHorLen()-pModbus->GetHorInt()), SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                            posChanged[AXIS_IDX_PHOR] = true;
                    }
                }
                if (ui->BtnPaHorCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_PAHOR, 0, SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_PHOR] = true;
                }
                if (ui->BtnPaVerCw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_PAVER, pModbus->GetPaVerLen(), SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_PVER] = true;
                }
                if (ui->BtnPaVerCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_PAVER, 0, SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_PVER] = true;
                }
                if (ui->BtnRaVerCw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_RAVER, pModbus->GetRaVerLen(), SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_RVER] = true;
                }
                if (ui->BtnRaVerCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_RAVER, 0, SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_RVER] = true;
                }
                if (ui->BtnRaHorCw->isDown())
                {
                    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
                    {
                        if (pModbus->ManualPos(spd, SRV_RAHOR, pModbus->GetHorInt(), SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                            posChanged[AXIS_IDX_RHOR] = true;
                    }
                    else
                    {
                        if (pModbus->ManualPos(spd, SRV_RAHOR, pModbus->GetHorLen()-pModbus->GetHorInt(), SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_RHOR] = true;
                }
                }
                if (ui->BtnRaHorCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_RAHOR, 0, SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_RHOR] = true;
                }
                if (ui->BtnTravelCw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_TRV, pModbus->GetTravLen(), SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_TRV] = true;
                }
                if (ui->BtnTravelCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_TRV, 0, SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_TRV] = true;
                }
                if (ui->BtnExtCw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_EXT, pModbus->GetExteLen(), SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_EXT] = true;
                }
                if (ui->BtnExtCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_EXT, 0, SERVO_MODE_FORCE) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_EXT] = true;
                }
            }
            else
            {
                if (ui->BtnPaHorCw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_PAHOR, SVADJ_CW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_PHOR] = true;
                }
                if (ui->BtnPaHorCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_PAHOR, SVADJ_CCW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_PHOR] = true;
                }
                if (ui->BtnPaVerCw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_PAVER, SVADJ_CW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_PVER] = true;
                }
                if (ui->BtnPaVerCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_PAVER, SVADJ_CCW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_PVER] = true;
                }
                if (ui->BtnRaVerCw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_RAVER, SVADJ_CW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_RVER] = true;
                }
                if (ui->BtnRaVerCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_RAVER, SVADJ_CCW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_RVER] = true;
                }
                if (ui->BtnRaHorCw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_RAHOR, SVADJ_CW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_RHOR] = true;
                }
                if (ui->BtnRaHorCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_RAHOR, SVADJ_CCW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_RHOR] = true;
                }
                if (ui->BtnTravelCw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_TRV, SVADJ_CW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_TRV] = true;
                }
                if (ui->BtnTravelCcw->isDown())
                {
                    if (pModbus->ManualPos(spd, SRV_TRV, SVADJ_CCW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_TRV] = true;
                }
                if (ui->BtnExtCw->isDown())
    {
                    if (pModbus->ManualPos(spd, SRV_EXT, SVADJ_CW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_EXT] = true;
                }
                if (ui->BtnExtCcw->isDown())
        {
                    if (pModbus->ManualPos(spd, SRV_EXT, SVADJ_CCW, SERVO_MODE_ADJUST) == SENDMSG_RET_ACK)
                        posChanged[AXIS_IDX_EXT] = true;
                }
            }
            m_ptimer->start(10);
            m_havesendservocmd = true;
        }
    }
    else
    {
        m_ptimer->stop();
        if (m_havesendservocmd)
            pModbus->SetRunState(RUN_STATE_PAUSE);
    }
}
// 气动调位信号槽
void FormAdjust::PneAdjCcw(int code)
{
    if (!checkManual())
        return;
    pModbus->CommandAdjustMotor(code, false);
}
void FormAdjust::PneAdjCw(int code)
{
    if (!checkManual())
        return;
    pModbus->CommandAdjustMotor(code, true);
}
void FormAdjust::PneAdjStop(int code)
{
	code = 0xFF;
	pModbus->CommandAdjustMotor(code, true);
}

void FormAdjust::SvStop(void)
{
    pModbus->SetRunState(RUN_STATE_PAUSE);
}

// 安全开关关闭信号槽
void FormAdjust::safeSwOff(void)
{
    pModbus->SetRunState(RUN_STATE_PAUSE);
}

// 输入调位速度信号槽
void FormAdjust::InputAdjSpd(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->spinBox->minimum(), ui->spinBox->maximum()) == QDialog::Accepted)
    {
        pModbus->SetAdjustSpeed(value);
        ui->spinBox->setValue(value);
    }
}
// 输入调位尺度信号槽
void FormAdjust::InputAdjScale(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->SpinBoxScale->minimum(), ui->SpinBoxScale->maximum()) == QDialog::Accepted)
        ui->SpinBoxScale->setValue(value);
}
void FormAdjust::SvPHorShiftCcw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_PAHOR, qRound(shiftPos * -100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_PHOR] = true;
    }
    else
    {
    }
}
void FormAdjust::SvPHorShiftCw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_PAHOR, qRound(shiftPos * 100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_PHOR] = true;
    }
    else
    {
    }
}
void FormAdjust::SvPVerShiftCcw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_PAVER, qRound(shiftPos * -100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_PVER] = true;
    }
    else
    {
    }
}
void FormAdjust::SvPVerShiftCw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_PAVER, qRound(shiftPos * 100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_PVER] = true;
    }
    else
    {
    }
}
void FormAdjust::SvRHorShiftCcw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_RAHOR, qRound(shiftPos * -100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_RHOR] = true;
    }
    else
    {
    }
}
void FormAdjust::SvRHorShiftCw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_RAHOR, qRound(shiftPos * 100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_RHOR] = true;
    }
    else
    {
    }
}
void FormAdjust::SvRVerShiftCcw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_RAVER, qRound(shiftPos * -100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_RVER] = true;
    }
    else
    {
    }
}
void FormAdjust::SvRVerShiftCw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_RAVER, qRound(shiftPos * 100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_RVER] = true;
    }
    else
    {
    }
}
void FormAdjust::SvTrvShiftCcw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_TRV, qRound(shiftPos * -100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_TRV] = true;
    }
    else
    {
    }
}
void FormAdjust::SvTrvShiftCw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_TRV, qRound(shiftPos * 100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_TRV] = true;
    }
    else
    {
    }
}
void FormAdjust::SvExtShiftCcw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_EXT, qRound(shiftPos * -100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_EXT] = true;
    }
    else
    {
    }
}
void FormAdjust::SvExtShiftCw(void)
{
    if (!checkManual())
        return;
    double shiftPos = ui->SpinBoxScale->value();
    if (pModbus->IsHasRefer(pModbus->GetHomeState()))
    {
        pModbus->ManualPos(ui->spinBox->value(), SRV_EXT, qRound(shiftPos * 100.00), SERVO_MODE_FORCE, true);
        posChanged[AXIS_IDX_EXT] = true;
    }
    else
    {
    }
}

void FormAdjust::SvPHorCwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvPHorShiftCw();
    }
    else
    {
    }
}
void FormAdjust::SvPHorCcwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvPHorShiftCcw();
    }
    else
    {
    }
}
void FormAdjust::SvPVerCwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvPVerShiftCw();
    }
    else
    {
    }
}
void FormAdjust::SvPVerCcwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvPVerShiftCcw();
    }
    else
    {
    }
}
void FormAdjust::SvRHorCwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvRHorShiftCw();
    }
    else
    {
    }
}
void FormAdjust::SvRHorCcwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvRHorShiftCcw();
    }
    else
    {
    }
}
void FormAdjust::SvRVerCwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvRVerShiftCw();
    }
    else
    {
    }
}
void FormAdjust::SvRVerCcwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvRVerShiftCcw();
    }
    else
    {
    }
}
void FormAdjust::SvTrvCwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvTrvShiftCw();
    }
    else
    {
    }
}
void FormAdjust::SvTrvCcwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvTrvShiftCcw();
    }
    else
    {
    }
}
void FormAdjust::SvExtCwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvExtShiftCw();
    }
    else
    {
    }
}
void FormAdjust::SvExtCcwStop(void)
{
    if (!m_havesendservocmd)
    {
        SvExtShiftCcw();
    }
    else
    {
    }
}
void FormAdjust::RaHorClick(void)
{
	if (xIoPort::GetOut(EM1_VAR_Y10) == true)
		pModbus->ManualRun(RUN_ACT_HORIZONTAL);
	else
		pModbus->ManualRun(RUN_ACT_VERTIACL);
}
void FormAdjust::PaHorClick(void)
{
	if (xIoPort::GetOut(RBT_VAR_OUT_PRO_HOR) == true)
		pModbus->ManualPro(PRO_ACT_VERTIACL);
	else
		pModbus->ManualPro(PRO_ACT_HOZIONTAL);
}
void FormAdjust::RaAdvClick(void)
{
	if (xIoPort::GetOut(RBT_VAR_OUT_RUN_RET) == true)
		pModbus->ManualRun(RUN_ACT_ADVANCE);
	else
		pModbus->ManualRun(RUN_ACT_RETURN);
}
void FormAdjust::RaDesClick(void)
{
	if (xIoPort::GetOut(RBT_VAR_OUT_RUN_DES) == true)
		pModbus->ManualRun(RUN_ACT_ASCENT);
	else
		pModbus->ManualRun(RUN_ACT_DESCENT);
}
void FormAdjust::SetOutIO(void)
{
		ui->BtnPaVer->setOn(xIoPort::GetOut(RBT_VAR_OUT_PRO_VER));
		ui->BtnPaHor->setOn(xIoPort::GetOut(RBT_VAR_OUT_PRO_HOR));
	if (CMBProtocol::GetRunRotateUse())
	{
			ui->BtnRaHor->setOn(xIoPort::GetOut(EM1_VAR_Y09));
			ui->BtnRaVer->setOn(xIoPort::GetOut(EM1_VAR_Y10));
	}
		ui->BtnRaDes->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_DES));
		ui->BtnRaRet->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_RET));
}

void FormAdjust::extOutOn()
{
    // 打开输出端口
    quint16 outselect;     // 治具选择
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        outselect  = ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 12;
        outselect |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 13;
        outselect |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 14;
    }
    else
    {
        outselect  = ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 0;
        outselect |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 1;
        outselect |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 2;
        outselect |= ((quint16)(ui->checkBoxJig06->isChecked()?1:0)) << 3;
        outselect |= ((quint16)(ui->checkBoxJig07->isChecked()?1:0)) << 4;
        outselect |= ((quint16)(ui->checkBoxJig08->isChecked()?1:0)) << 5;
    }
    if (outselect==0)return;
    pModbus->ManualVacuum(true, outselect);

}

void FormAdjust::extOutOff()
{
    quint16 outselect;     // 治具选择
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        outselect  = ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 12;
        outselect |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 13;
        outselect |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 14;
    }
    else
    {
        outselect  = ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 0;
        outselect |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 1;
        outselect |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 2;
        outselect |= ((quint16)(ui->checkBoxJig06->isChecked()?1:0)) << 3;
        outselect |= ((quint16)(ui->checkBoxJig07->isChecked()?1:0)) << 4;
        outselect |= ((quint16)(ui->checkBoxJig08->isChecked()?1:0)) << 5;
    }
    // 关闭输出端口
    if (outselect==0)return;
    pModbus->ManualVacuum(false, outselect);
}
