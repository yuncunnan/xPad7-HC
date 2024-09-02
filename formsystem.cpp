#include <QButtonGroup>
#include <QDir>
#include <QFile>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "base32.h"
#include "crc16.h"
#include "xconfig.h"
#include "servoalias.h"
#include "cmbprotocol.h"
#include "dialogframe.h"
#include "xioport.h"
#include "xstringresource.h"
#include "xsystemlog.h"
#include "xmessagebox.h"
#include "xmessageboxactive.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "formsystem.h"
#include "ui_formsystem.h"
#include "dialogkeyboard.h"
#include "qrencode.h"


#define TAB_PAGE_RUN        0
#define TAB_PAGE_RESET      1
#define TAB_PAGE_HOME       2
#define TAB_PAGE_MAINTAIN   3
#define TAB_PAGE_VISION         4
#define MAX_TAB_PAGE            5

#define VISION_TYPE_NULL        0
#define VISION_TYPE_COGNEX      1

#define VISION_INSTALL_FIXED    0
#define VISION_INSTALL_FOLLOW   1

#define VISION_TRIGGER_PROTOCAL 0
#define VISION_TRIGGER_PORT     1


extern DialogFrame *pDialogMain;

Formsystem::Formsystem(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::Formsystem)
{
	ui->setupUi(this);
    retranslateUi();
#if (FACTORY == FA_VICTOR)//威特尔回原要检测开模完信号（加工完成）
	ui->checkMopLock->setText(tr"加工完成自锁");
#endif
#if TIME_BASE == 10
    ui->BoxAlmTime->setDecimals(2);
    ui->BoxAlmTime->setMaximum(9.99);
#else
    ui->BoxAlmTime->setDecimals(1);
    ui->BoxAlmTime->setMaximum(99.9);
#endif

#if UI_SRV_CFG != UI_SRV_4_5_6
//	ui->checkSvRaHor->setEnabled(false);
	ui->checkSvExt->setEnabled(false);
#endif
	pModbus = modbus;
    m_time = new QTimer(this);
    m_time->setSingleShot(true);
	ui->checkJigUse->setVisible(false);
    if (pModbus->GetFunctions(SUB_FUN_EUROMAP))
        ui->checkImop->setVisible(true);
    else
		ui->checkImop->setVisible(false);
    ui->lineEditCurProCode->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,10}"), this));
    ui->lineEditNewProCode->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,10}"), this));
    ui->lineEditNewProCode2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,10}"), this));
    connect(m_time,SIGNAL(timeout()),this,SLOT(VisionDataUpdate()));
#if MULPROC_ENABLE == 0
	ui->checkProc2->setChecked(false);
	ui->checkProc3->setChecked(false);
    ui->checkProc2->setVisible(false);
    ui->checkProc3->setVisible(false);
#endif

#if (FACTORY == FA_KEHAO || (FACTORY == FA_WOERDA))
    ui->BoxOilTime->setMinimum(10.0);
#endif

#if (FACTORY == FA_BEIYA || (FACTORY == FA_ZHENJIE))
    ui->BoxOilIntervalDay->setEnabled(false);
    ui->BoxOilIntervalHour->setEnabled(false);
    ui->BoxOilIntervalMinute->setSuffix(tr(" 模"));
    ui->checkOilCtrl->setChecked(false);
    ui->checkOilCtrl->setEnabled(false);
#endif
    // 初始化默认视觉0
    m_visionidx = 0;
    ui->stackedWidgetMaintain->setCurrentIndex(0);

	QFont font;
	int fontSizePx = 28; // 指定字号（像素）
	font.setPixelSize(fontSizePx); // 设置字号为28像素
	for(int i=0;i<HOME_ACTION_MAX;i++)
	{
		ui->tableAxis->item(i,0)->setFont(font);
		ui->tableAxis->verticalHeaderItem(i)->setFont(font);
	}
}

Formsystem::~Formsystem()
{
	delete ui;
    if (m_time)
        delete m_time;
}
void Formsystem::retranslateUi(void)
{
    ui->checkSvPaHor->setText(tr("不使用") + GetServoName(AXIS_IDX_PHOR) + tr("轴伺服"));
    ui->checkSvRaVer->setText(tr("使用") + GetServoName(AXIS_IDX_RVER) + tr("轴伺服"));
    ui->checkSvRaHor->setText(tr("使用") + GetServoName(AXIS_IDX_RHOR) + tr("轴伺服"));
    ui->checkSvExt->setText(tr("使用") + GetServoName(AXIS_IDX_EXT) + tr("轴伺服"));

}
// 查询原点复归顺序
void Formsystem::queryHome(quint16 (&home)[HOME_DEF_MAX])
{
	quint8 idx = 0;
    bool flag_x, flag_y, flag_z, flag_a, flag_b, flag_c, flag_rot, flag_ext, flag_run, flag_run_rot, flag_run_hor;
    flag_x = flag_y = flag_z = flag_a = flag_b = flag_c = flag_rot = flag_ext = flag_run = flag_run_hor = flag_run_rot = false;
	for (int i = 0; i < HOME_ACTION_MAX; i ++)
		Axis[i] = 0xFF;
	for (int i = 0; i < HOME_DEF_MAX; i ++)
	{
		switch (home[i])
		{
		case CUSTOMER_FUN_Y_HOME:
			if (flag_y)
				break;
			flag_y = true;
			Axis[idx] = home[i];
			idx ++;
			break;
		case CUSTOMER_FUN_Z_HOME:
			if (flag_z)
				break;
			flag_z = true;
			Axis[idx] = home[i];
			idx ++;
			break;
		case CUSTOMER_FUN_X_HOME:
			if (flag_x)
				break;
			flag_x = true;
			Axis[idx] = home[i];
			idx ++;
			break;
		case CUSTOMER_FUN_A_HOME:
			if (flag_a)
				break;
			flag_a = true;
			Axis[idx] = home[i];
			idx ++;
			break;
		case CUSTOMER_FUN_B_HOME:
			if (flag_b)
				break;
			flag_b = true;
			Axis[idx] = home[i];
			idx ++;
			break;
		case CUSTOMER_FUN_C_HOME:
			if (flag_c)
				break;
			flag_c = true;
			Axis[idx] = home[i];
			idx ++;
			break;
		case CUSTOMER_FUN_PRO_ROT:
			if (flag_rot)
				break;
			flag_rot = true;
			Axis[idx] = home[i];
			idx ++;
			break;
        case CUSTOMER_FUN_RUN_ROT:
            if (flag_run_rot)
                break;
            flag_run_rot = true;
            Axis[idx] = home[i];
            idx ++;
            break;
		case CUSTOMER_FUN_RUN_VER:
			if (flag_run)
				break;
			flag_run = true;
			Axis[idx] = home[i];
			idx ++;
			break;
        case CUSTOMER_FUN_RUN_HOR:
            if (flag_run_hor)
                break;
            flag_run_hor = true;
            Axis[idx] = home[i];
            idx ++;
            break;
		case CUSTOMER_FUN_CLR_EXT:
			if (flag_ext)
				break;
			flag_ext = true;
			Axis[idx] = home[i];
			idx ++;
			break;
		}
	}
}
bool Formsystem::IsVaildPCode(const ProductCode &PCode)
{
    if (isprint(PCode.m_product_id1&0xFF)&&
        isprint((PCode.m_product_id1>>8)&0xFF)&&
        isprint(PCode.m_product_id2&0xFF)&&
        isprint((PCode.m_product_id2>>8)&0xFF)&&
        isprint(PCode.m_product_id3&0xFF)&&
        isprint((PCode.m_product_id3>>8)&0xFF)&&
        isprint(PCode.m_product_id4&0xFF)&&
        isprint((PCode.m_product_id4>>8)&0xFF)&&
        isprint(PCode.m_product_id5&0xFF)&&
        isprint((PCode.m_product_id5>>8)&0xFF))
        return true;
    else
        return false;
}

// 查询系统参数设置
bool Formsystem::QueryPara(void)
{
	// 得到系统参数设置
    pModbus->ReadSystem();
    pModbus->GetSystem(SysPara);
	// 得到原点复归设置
    if (!pModbus->CheckHome())
    {
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), tr("查询到的原点复归顺序数据有误，初始化为默认值！"));
        pModbus->ResetHome();
        pModbus->GetHome(home);
        try
        {
                if (pModbus->WriteHome(home))
                    throw false;
                if (pModbus->CommandWrite(CMD_WRITE_USER))
                    throw false;
        }
        catch (bool &)
        {
            xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAVE_PARA_ERROR));
            return false;
        }
    }
    pModbus->GetHome(bakhome);
    pModbus->GetHome(home);
    queryHome(home);
    // 更新原点复归表格设置数据
    UpdateTab();
    // 读取激活码、机器码及产品密钥，备份产品密钥
    pModbus->GetRegistrationCode(RegCode);
    pModbus->GetProductCode(ProCode);
    memcpy(&ProCodeBak, &ProCode, sizeof(ProductCode));
//	if ((QChar(ProCode.m_product_id1&0xFF).isPrint()) && (QChar((ProCode.m_product_id1>>8)&0xFF).isPrint()) && (QChar(ProCode.m_product_id2&0xFF).isPrint()) && (QChar((ProCode.m_product_id2>>8)&0xFF).isPrint()&0xFF) &&
//		(QChar(ProCode.m_product_id3&0xFF).isPrint()) && (QChar((ProCode.m_product_id3>>8)&0xFF).isPrint()) && (QChar(ProCode.m_product_id4&0xFF).isPrint()) && (QChar((ProCode.m_product_id4>>8)&0xFF).isPrint()&0xFF) &&
//		(QChar(ProCode.m_product_id5&0xFF).isPrint()) && (QChar((ProCode.m_product_id5>>8)&0xFF).isPrint()))
    if (IsVaildPCode(ProCode))
        ui->lineEditCurProCode->setEnabled(true);
    else
        ui->lineEditCurProCode->setEnabled(false);
    // 显示机器码
    QString MachineCode;
    MachineCode = (char)(RegCode.m_system_uid1);
    MachineCode += (char)((RegCode.m_system_uid1>>8));
    MachineCode += (char)((RegCode.m_system_uid2));
    MachineCode += (char)((RegCode.m_system_uid2>>8));
    MachineCode += (char)((RegCode.m_system_uid3));
    MachineCode += (char)((RegCode.m_system_uid3>>8));
    MachineCode += (char)((RegCode.m_system_uid4));
    MachineCode += (char)((RegCode.m_system_uid4>>8));
    MachineCode += (char)((RegCode.m_system_uid5));
    MachineCode += (char)((RegCode.m_system_uid5>>8));
    MachineCode += (char)((RegCode.m_system_uid6));
    MachineCode += (char)((RegCode.m_system_uid6>>8));
    MachineCode += (char)((RegCode.m_system_uid7));
    MachineCode += (char)((RegCode.m_system_uid7>>8));
    MachineCode += (char)((RegCode.m_system_uid8));
    MachineCode += (char)((RegCode.m_system_uid8>>8));
    ui->labelMacCode->setText(MachineCode);
    // 显示二维码
    ui->widgetQRcode->setQRData(ui->labelMacCode->text());

    // 设置原点第一行默认选中
    ui->tableAxis->setCurrentCell(0, 0);
	ui->tableAxis->setFocus();
	// 备份系统参数设置
	memcpy(&SysParaBak, &SysPara, sizeof(SystemParameter));
	// 把参数设置到界面
	// 报警器鸣叫次数
	ui->BoxAlmCnt->setValue(SysPara.m_alarm_times);
	// 报警器鸣叫间隔
    ui->BoxAlmTime->setValue((double)SysPara.m_alarm_interval / (1000.0/TIME_BASE));
	// 机械手维护模数
	ui->BoxMaintain->setValue(SysPara.m_service_moldings);
	// 计划生产数量
	ui->BoxPlan->setValue(SysPara.m_plan_molding);
	// 生产数量提醒
	ui->BoxRemind->setValue(SysPara.m_plan_alarm);
	// 不良品数量报警
	ui->BoxReject->setValue(SysPara.m_reject_alarm);
    // 打油
    BreakOilInterval();
    ui->BoxOilTime->setValue((double)SysPara.m_oil_time / (1000.0/TIME_BASE));
    if (SysPara.m_oil_use != 0)
        ui->checkOilUse->setChecked(true);
    else
        ui->checkOilUse->setChecked(false);

#if (FACTORY == FA_BEIYA || (FACTORY == FA_ZHENJIE))
#else
    if (ui->checkOilUse->isChecked())
        ui->checkOilCtrl->setEnabled(true);
    else
        ui->checkOilCtrl->setEnabled(false);
    if (SysPara.m_oil_ctrl_use != 0)
        ui->checkOilCtrl->setChecked(true);
    else
        ui->checkOilCtrl->setChecked(false);
#endif
	// 横行时正臂倒角状态
#if PENDANT_PROTOCOL
    if (pModbus->GetFunctions(SUB_FUN2_ROTATE))
    {
        if (SysPara.m_rotate_out_at_origin == 0)
            ui->radioButtonNoLimit->setChecked(true);
        else if ((SysPara.m_rotate_out_at_origin == 1))
            ui->radioButtonRotHor->setChecked(true);
        else
            ui->radioButtonRotVer->setChecked(true);
    }
    else
    {
        if (SysPara.m_rotate_out_at_origin == 0)
            ui->radioButtonRotVer->setChecked(true);
        else
            ui->radioButtonRotHor->setChecked(true);
    }
#else
    if (SysPara.m_rotate_out_at_origin == 0)
        ui->radioButtonNoLimit->setChecked(true);
    else if ((SysPara.m_rotate_out_at_origin == 1))
        ui->radioButtonRotHor->setChecked(true);
    else
        ui->radioButtonRotVer->setChecked(true);
#endif
	// 自动运行时开安全门
	if (SysPara.m_pause_open_door != 0)
		ui->radioButtonPause->setChecked(true);
	else
		ui->radioButtonContinue->setChecked(true);
	// 模内倒角动作
    if (SysPara.m_rotate_inmold_use == 0)
        ui->radioRotVer->setChecked(true);   //垂直
    else if (SysPara.m_rotate_inmold_use == 1)
        ui->radioRotNoLimit->setChecked(true);  //不限制
	else
        ui->radioRotHor->setChecked(true);  //==2 水平
	// 待机选项
	if (SysPara.m_wait_outmould != 0)
		ui->radioWaitOutM->setChecked(true);
	else
		ui->radioWaitInM->setChecked(true);
	// 关模完成信号配置
	ui->checkMcp->setChecked(SysPara.m_mold_closed_use != 0);
	// 开模中间信号配置
	ui->checkImop->setChecked(SysPara.m_imop_dwn_use != 0);
	// 开中板模确认信号配置
	ui->checkMid->setChecked(SysPara.m_mid_open_use != 0);
	// 副臂上下伺服使用配置
	ui->checkSvRaVer->setChecked(SysPara.m_rver_servo_use != 0);
	// 副臂引拔伺服使用配置
	ui->checkSvRaHor->setChecked(SysPara.m_rhor_servo_use != 0);
	// 气动副臂使用配置
	ui->checkRunner->setChecked(SysPara.m_runner_use != 0);
	// 气动副臂下位电眼使用配置
	ui->checkRunnerDown->setChecked(SysPara.m_runner_down_use != 0);
    // 气动副臂前进电眼使用配置
    ui->checkRunnerAdvance->setChecked(SysPara.m_runner_advance_use != 0);
    // 气动副臂后退电眼使用配置
    ui->checkRunnerReturn->setChecked(SysPara.m_runner_return_use != 0);
	// 调位使用配置
	ui->checkAdjust->setChecked(SysPara.m_adjust_use != 0);
    // 原点在模内
    ui->checkHomeInmold->setChecked(SysPara.m_home_inmold != 0);
	// 扩展伺服使用配置
	ui->checkSvExt->setChecked(SysPara.m_ext_servo_use != 0);
	// 換治具使用
	ui->checkJigUse->setChecked(SysPara.m_jig_use != 0);
    // 进程2使用
    ui->checkProc2->setChecked(SysPara.m_proc2_use != 0);
    // 进程3使用
    ui->checkProc3->setChecked(SysPara.m_proc3_use != 0);
    // 气动正臂倒角使用
    ui->checkRotateUse->setChecked(SysPara.m_rotate_use != 0);
    // 气动副臂倒角使用
    ui->checkRunRotateUse->setChecked(SysPara.m_run_rotate_use != 0);
    // 取物失败，开关安全门程序结束
    ui->checkDoorReset->setChecked(SysPara.m_door_reset_use != 0);
    // 模外安全区2使用
    ui->checkOutSafe2->setChecked(((SysPara.m_extend_bit_use >> 0)& 1) != 0);
    // 模外安全区信号不使用
    ui->checkOutSignal->setChecked(((SysPara.m_extend_bit_use >> 1) & 1) != 0);
    // 正臂引拔不使用
    ui->checkSvPaHor->setChecked(((SysPara.m_extend_bit_use >> 2)& 1) != 0);
    // 外部控制功能使用
    ui->checkExtraCtrl->setChecked(((SysPara.m_extend_bit_use >> 4)& 1) != 0);
    // 模内安全区信号不使用
    ui->checkInSignal->setChecked(((SysPara.m_extend_bit_use >> 5) & 1) != 0);
    // 安全门报警信号不输出
    ui->checkIgnoreDoor->setChecked(((SysPara.m_extend_bit_use >> 6) & 1) != 0);
    // 开模完信号自锁
    ui->checkMopLock->setChecked(((SysPara.m_extend_bit_use >> 7) & 1) != 0);
    //退出自动时清除IO口
	ui->checkClearIO->setChecked(SysPara.m_sys_io_clr != 0);


    // IP
    ui->sBoxIP1->setValue((quint8)(SysPara.m_ip>>24));
    ui->sBoxIP2->setValue((quint8)(SysPara.m_ip>>16));
    ui->sBoxIP3->setValue((quint8)(SysPara.m_ip>>8));
    ui->sBoxIP4->setValue((quint8)(SysPara.m_ip));
    ui->sBoxSubMask1->setValue((quint8)(SysPara.m_submask>>24));
    ui->sBoxSubMask2->setValue((quint8)(SysPara.m_submask>>16));
    ui->sBoxSubMask3->setValue((quint8)(SysPara.m_submask>>8));
    ui->sBoxSubMask4->setValue((quint8)(SysPara.m_submask));
    ui->sBoxGateWay1->setValue((quint8)(SysPara.m_gateway>>24));
    ui->sBoxGateWay2->setValue((quint8)(SysPara.m_gateway>>16));
    ui->sBoxGateWay3->setValue((quint8)(SysPara.m_gateway>>8));
    ui->sBoxGateWay4->setValue((quint8)(SysPara.m_gateway));

    // Vision,将参数设置到界面
    m_visiondata[0][0] = SysPara.m_visionip1;
    m_visiondata[0][1] = SysPara.m_vision1port;
    m_visiondata[0][2] = SysPara.m_vision1_trigger;
    m_visiondata[0][3] = SysPara.m_vision1_outvar;
    m_visiondata[1][0] = SysPara.m_visionip2;
    m_visiondata[1][1] = SysPara.m_vision2port;
    m_visiondata[1][2] = SysPara.m_vision2_trigger;
    m_visiondata[1][3] = SysPara.m_vision2_outvar;
    m_visiondata[2][0] = SysPara.m_visionip3;
    m_visiondata[2][1] = SysPara.m_vision3port;
    m_visiondata[2][2] = SysPara.m_vision3_trigger;
    m_visiondata[2][3] = SysPara.m_vision3_outvar;
    m_visiondata[3][0] = SysPara.m_visionip4;
    m_visiondata[3][1] = SysPara.m_vision4port;
    m_visiondata[3][2] = SysPara.m_vision4_trigger;
    m_visiondata[3][3] = SysPara.m_vision4_outvar;
    m_visiondata[4][0] = SysPara.m_visionip5;
    m_visiondata[4][1] = SysPara.m_vision5port;
    m_visiondata[4][2] = SysPara.m_vision5_trigger;
    m_visiondata[4][3] = SysPara.m_vision5_outvar;
    m_visiondata[5][0] = SysPara.m_visionip6;
    m_visiondata[5][1] = SysPara.m_vision6port;
    m_visiondata[5][2] = SysPara.m_vision6_trigger;
    m_visiondata[5][3] = SysPara.m_vision6_outvar;
    m_visiondata[6][0] = SysPara.m_visionip7;
    m_visiondata[6][1] = SysPara.m_vision7port;
    m_visiondata[6][2] = SysPara.m_vision7_trigger;
    m_visiondata[6][3] = SysPara.m_vision7_outvar;
    m_visiondata[7][0] = SysPara.m_visionip8;
    m_visiondata[7][1] = SysPara.m_vision8port;
    m_visiondata[7][2] = SysPara.m_vision8_trigger;
    m_visiondata[7][3] = SysPara.m_vision8_outvar;
    ui->sBoxVisionIP1->setValue((quint8)(m_visiondata[m_visionidx][0]>>24)&0xFF);
    ui->sBoxVisionIP2->setValue((quint8)(m_visiondata[m_visionidx][0]>>16)&0xFF);
    ui->sBoxVisionIP3->setValue((quint8)(m_visiondata[m_visionidx][0]>>8)&0xFF);
    ui->sBoxVisionIP4->setValue((quint8)(m_visiondata[m_visionidx][0])&0xFF);
    ui->lineEditVisionPort->setValue((quint16)m_visiondata[m_visionidx][1]);
    ui->cBoxVision->setCurrentIndex((((quint16)m_visiondata[m_visionidx][2]>>8)&0xFF) ? VISION_TYPE_COGNEX : VISION_TYPE_NULL);
    ui->cBoxVisionInstall->setCurrentIndex((((quint16)m_visiondata[m_visionidx][2]>>1)&1) ? VISION_INSTALL_FOLLOW : VISION_INSTALL_FIXED);
    ui->cBoxVisionProtocol->setCurrentIndex(((quint16)m_visiondata[m_visionidx][2]&1) ? VISION_TRIGGER_PORT : VISION_TRIGGER_PROTOCAL);
    ui->lineEditVisionOutput->setText(xStringResource::GetVarName((quint16)m_visiondata[m_visionidx][3]));

    // 读取轴物理存在，设置轴使用不使用
    if (pModbus->GetFunctions(SUB_3_AXES))
    {
		ui->checkSvRaVer->setChecked(pModbus->GetRverSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
		ui->checkSvRaHor->setChecked(pModbus->GetRhorSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
		ui->checkSvExt->setChecked(pModbus->GetExtSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
        ui->checkSvRaVer->setEnabled(((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0);
        ui->checkSvRaHor->setEnabled(((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0);
        ui->checkSvExt->setEnabled(((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0);
    }
    // 非教导模式
    TemplateChecked = pModbus->GetTemplateUse();
    ui->checkTemplate->setChecked(TemplateChecked);
    AlfaChecked = pModbus->IsALFAMode();
    ui->checkAlfaMode->setChecked(AlfaChecked);
   return true;
}

// 从界面得到系统参数设置
void Formsystem::LoadPara(void)
{
	if (xPermissions::GetPermissions(PER_SYS_NORMAL))
	{
		// 报警器鸣叫次数
		SysPara.m_alarm_times = ui->BoxAlmCnt->value();
		// 报警器鸣叫间隔
        SysPara.m_alarm_interval = qRound(ui->BoxAlmTime->value() * (1000.0/TIME_BASE));
		// 计划生产数量
		SysPara.m_plan_molding = ui->BoxPlan->value();
		// 生产数量提醒
		SysPara.m_plan_alarm = ui->BoxRemind->value();
		// 不良品数量报警
		SysPara.m_reject_alarm = ui->BoxReject->value();
		// 横行时正臂倒角状态
        if (pModbus->GetFunctions(SUB_FUN2_ROTATE))
        {
            if (ui->radioButtonRotHor->isChecked())
                SysPara.m_rotate_out_at_origin = 1;
            else if (ui->radioButtonNoLimit->isChecked())
                SysPara.m_rotate_out_at_origin = 0;
            else
                SysPara.m_rotate_out_at_origin = 3;
        }
        else
        {
            if (ui->radioButtonRotHor->isChecked())
                SysPara.m_rotate_out_at_origin = 1;
            else
                SysPara.m_rotate_out_at_origin = 0;
        }
		// 自动运行时开安全门
		if (ui->radioButtonPause->isChecked())
			SysPara.m_pause_open_door = 1;
		else
			SysPara.m_pause_open_door = 0;
		// 模内倒角动作
        if (ui->radioRotVer->isChecked())
            SysPara.m_rotate_inmold_use = 0;            //垂直
        else if(ui->radioRotNoLimit->isChecked())
            SysPara.m_rotate_inmold_use = 1;            //不限制
		else
            SysPara.m_rotate_inmold_use = 2;            //水平
		// 待机选项
		if (ui->radioWaitOutM->isChecked())
			SysPara.m_wait_outmould = 1;
		else
			SysPara.m_wait_outmould = 0;
        // 打油
        CombineOilInterval();
        SysPara.m_oil_time = ui->BoxOilTime->value() * (1000.0/TIME_BASE);
        if (ui->checkOilUse->isChecked())
            SysPara.m_oil_use = 1;
        else
            SysPara.m_oil_use = 0;
        if (ui->checkOilCtrl->isChecked() && ui->checkOilCtrl->isEnabled())
            SysPara.m_oil_ctrl_use = 1;
        else
            SysPara.m_oil_ctrl_use = 0;
	}
	if (xPermissions::GetPermissions(PER_SYS_SIGNAL))
	{
		// 映射原点复归顺序
		TransHome(home);
		// 关模完成信号配置
		if (ui->checkMcp->isChecked())
			SysPara.m_mold_closed_use = 1;
		else
			SysPara.m_mold_closed_use = 0;
		// 开模中间信号配置
		if (ui->checkImop->isChecked())
			SysPara.m_imop_dwn_use = 1;
		else
			SysPara.m_imop_dwn_use = 0;
		// 开中板模确认信号配置
		if (ui->checkMid->isChecked())
			SysPara.m_mid_open_use = 1;
		else
			SysPara.m_mid_open_use = 0;
		// 副臂引拔伺服使用设置
		if (ui->checkSvRaHor->isChecked())
			SysPara.m_rhor_servo_use = 1;
		else
			SysPara.m_rhor_servo_use = 0;
		// 副臂上下伺服使用设置
		if (ui->checkSvRaVer->isChecked())
			SysPara.m_rver_servo_use = 1;
		else
			SysPara.m_rver_servo_use = 0;
		// 气动副臂使用设置
		if (ui->checkRunner->isChecked())
			SysPara.m_runner_use = 1;
		else
			SysPara.m_runner_use = 0;
		// 气动副臂下位电眼使用设置
		if (ui->checkRunnerDown->isChecked())
			SysPara.m_runner_down_use = 1;
		else
			SysPara.m_runner_down_use = 0;
        // 气动副臂前进电眼使用设置
        SysPara.m_runner_advance_use = ui->checkRunnerAdvance->isChecked() ? 1 : 0;
        // 气动副臂后退电眼使用设置
        SysPara.m_runner_return_use = ui->checkRunnerReturn->isChecked() ? 1 : 0;
        // 调位使用设置
		if (ui->checkAdjust->isChecked())
			SysPara.m_adjust_use = 1;
		else
			SysPara.m_adjust_use = 0;
        // 原点在模内设置
        if (ui->checkHomeInmold->isChecked())
        {
            SysPara.m_home_inmold = 1;
        }
        else
        {
            SysPara.m_home_inmold = 0;
        }
        // 扩展伺服使用设置
		if (ui->checkSvExt->isChecked())
			SysPara.m_ext_servo_use = 1;
		else
			SysPara.m_ext_servo_use = 0;
         // 取物失败，开关安全门程序结束
        SysPara.m_door_reset_use = (ui->checkDoorReset->isChecked() ? 1 : 0) << 0;
        // 扩展安全区2使用
        SysPara.m_extend_bit_use = (ui->checkOutSafe2->isChecked() ? 1 : 0) << 0;
        // 模外安全区信号不使用
        SysPara.m_extend_bit_use |= (ui->checkOutSignal->isChecked() ? 1 : 0) << 1;
        // 正臂引拔轴使用
        SysPara.m_extend_bit_use |= (ui->checkSvPaHor->isChecked() ? 1 : 0) << 2;
        // 外部控制功能使用
        SysPara.m_extend_bit_use |= (ui->checkExtraCtrl->isChecked() ? 1 : 0) << 4;
        // 模内安全区信号不使用
        SysPara.m_extend_bit_use |= (ui->checkInSignal->isChecked() ? 1 : 0) << 5;
        // 安全门报警信号不输出
        SysPara.m_extend_bit_use |= (ui->checkIgnoreDoor->isChecked() ? 1 : 0) << 6;
        // 开模完信号自锁
        SysPara.m_extend_bit_use |= (ui->checkMopLock->isChecked() ? 1 : 0) << 7;

        // 換治具信號配置
		SysPara.m_jig_use = ui->checkJigUse->isChecked() ? 1 : 0;
        // 进程2使用
        SysPara.m_proc2_use = ui->checkProc2->isChecked() ? 1 : 0;
        // 进程3使用
        SysPara.m_proc3_use = ui->checkProc3->isChecked() ? 1 : 0;
        // 气动倒角使用
        SysPara.m_rotate_use = ui->checkRotateUse->isChecked() ? 1 : 0;
        SysPara.m_run_rotate_use = ui->checkRunRotateUse->isChecked() ? 1 : 0;

		//退出自动时清除IO口
		SysPara.m_sys_io_clr = ui->checkClearIO->isChecked() ? 1 : 0;

        // IP地址
        SysPara.m_ip = (quint32)(ui->sBoxIP1->value() << 24) | (quint32)(ui->sBoxIP2->value() << 16) | (quint32)(ui->sBoxIP3->value() << 8) | ui->sBoxIP4->value();
        SysPara.m_submask = (quint32)(ui->sBoxSubMask1->value() << 24) | (quint32)(ui->sBoxSubMask2->value() << 16) | (quint32)(ui->sBoxSubMask3->value() << 8) | ui->sBoxSubMask4->value();
        SysPara.m_gateway = (quint32)(ui->sBoxGateWay1->value() << 24) | (quint32)(ui->sBoxGateWay2->value() << 16) | (quint32)(ui->sBoxGateWay3->value() << 8) | ui->sBoxGateWay4->value();
        // Vision
        SysPara.m_visionip1 = m_visiondata[0][0];
        SysPara.m_visionip2 = m_visiondata[1][0];
        SysPara.m_visionip3 = m_visiondata[2][0];
        SysPara.m_visionip4 = m_visiondata[3][0];
        SysPara.m_visionip5 = m_visiondata[4][0];
        SysPara.m_visionip6 = m_visiondata[5][0];
        SysPara.m_visionip7 = m_visiondata[6][0];
        SysPara.m_visionip8 = m_visiondata[7][0];
        SysPara.m_vision1port = (quint16)m_visiondata[0][1];
        SysPara.m_vision2port = (quint16)m_visiondata[1][1];
        SysPara.m_vision3port = (quint16)m_visiondata[2][1];
        SysPara.m_vision4port = (quint16)m_visiondata[3][1];
        SysPara.m_vision5port = (quint16)m_visiondata[4][1];
        SysPara.m_vision6port = (quint16)m_visiondata[5][1];
        SysPara.m_vision7port = (quint16)m_visiondata[6][1];
        SysPara.m_vision8port = (quint16)m_visiondata[7][1];
        SysPara.m_vision1_trigger = (quint16)m_visiondata[0][2];
        SysPara.m_vision2_trigger = (quint16)m_visiondata[1][2];
        SysPara.m_vision3_trigger = (quint16)m_visiondata[2][2];
        SysPara.m_vision4_trigger = (quint16)m_visiondata[3][2];
        SysPara.m_vision5_trigger = (quint16)m_visiondata[4][2];
        SysPara.m_vision6_trigger = (quint16)m_visiondata[5][2];
        SysPara.m_vision7_trigger = (quint16)m_visiondata[6][2];
        SysPara.m_vision8_trigger = (quint16)m_visiondata[7][2];
        SysPara.m_vision1_outvar = (quint16)m_visiondata[0][3];
        SysPara.m_vision2_outvar = (quint16)m_visiondata[1][3];
        SysPara.m_vision3_outvar = (quint16)m_visiondata[2][3];
        SysPara.m_vision4_outvar = (quint16)m_visiondata[3][3];
        SysPara.m_vision5_outvar = (quint16)m_visiondata[4][3];
        SysPara.m_vision6_outvar = (quint16)m_visiondata[5][3];
        SysPara.m_vision7_outvar = (quint16)m_visiondata[6][3];
        SysPara.m_vision8_outvar = (quint16)m_visiondata[7][3];
  }
	if (xPermissions::GetPermissions(PER_SYS_MAINTAIN) == true)
	{
		// 机械手维护模数
		SysPara.m_service_moldings = ui->BoxMaintain->value();
	}
}

// 检查参数是否修改
bool Formsystem::isModified(void)
{
	parModify = 0;
	if (xPermissions::GetPermissions(PER_SYS_NORMAL) == true)
	{
		// 报警器鸣叫次数
		if (SysPara.m_alarm_times != SysParaBak.m_alarm_times)						parModify |= ((quint64)1 << LOG_ALARM_TIMES);
		// 报警器鸣叫时间
		if (SysPara.m_alarm_interval != SysParaBak.m_alarm_interval)				parModify |= ((quint64)1 << LOG_ALARM_INTERVAL);
		// 计划生产数量
		if (SysPara.m_plan_molding != SysParaBak.m_plan_molding)					parModify |= ((quint64)1 << LOG_PLAN_MOLDING_LOW);
		// 生产数量提醒
		if (SysPara.m_plan_alarm != SysParaBak.m_plan_alarm)						parModify |= ((quint64)1 << LOG_PLAN_ALARM_LOW);
		// 不良品数量报警
		if (SysPara.m_reject_alarm != SysParaBak.m_reject_alarm)					parModify |= ((quint64)1 << LOG_REJECT_ALARM);
		// 横行时正臂倒角状态
		if (SysPara.m_rotate_out_at_origin != SysParaBak.m_rotate_out_at_origin)	parModify |= ((quint64)1 << LOG_ROTATE_OUT_AT_ORIGIN);
		// 自动运行时开安全门
		if (SysPara.m_pause_open_door != SysParaBak.m_pause_open_door)				parModify |= ((quint64)1 << LOG_PAUSE_OPEN_DOOR);
		// 模内倒角动作
		if (SysPara.m_rotate_inmold_use != SysParaBak.m_rotate_inmold_use)			parModify |= ((quint64)1 << LOG_ROTATE_INMOLD_USE);
		// 待机选项
		if (SysPara.m_wait_outmould != SysParaBak.m_wait_outmould)					parModify |= ((quint64)1 << LOG_WAIT_OUTMOULD);
        // 打油
        if (SysPara.m_oil_interval != SysParaBak.m_oil_interval)                    parModify |= ((quint64)1 << LOG_OIL_INTERVAL_LOW);
        if (SysPara.m_oil_time != SysParaBak.m_oil_time)                            parModify |= ((quint64)1 << LOG_OIL_TIME_LOW);
	}
	if (xPermissions::GetPermissions(PER_SYS_SIGNAL) == true)
	{
        if (SysPara.m_oil_use != SysParaBak.m_oil_use)                              parModify |= ((quint64)1 << LOG_OIL_USE);
        if (SysPara.m_oil_ctrl_use != SysParaBak.m_oil_ctrl_use)                    parModify |= ((quint64)1 << LOG_OIL_USE_CTRL);
        // 关模完成信号配置
		if (SysPara.m_mold_closed_use != SysParaBak.m_mold_closed_use)				parModify |= ((quint64)1 << LOG_MOLD_CLOSED_USE);
		// 开模中间信号配置
		if (SysPara.m_imop_dwn_use != SysParaBak.m_imop_dwn_use)					parModify |= ((quint64)1 << LOG_INTERMOLD_DOWN_USE);
		// 开中板模确认信号配置
		if (SysPara.m_mid_open_use != SysParaBak.m_mid_open_use)					parModify |= ((quint64)1 << LOG_MID_OPEN_USE);
        // 副臂上下伺服使用配置 // 副臂引拔伺服使用配置

        if (pModbus->GetFunctions(SUB_3_AXES))
        {
            if (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0)
                if (SysPara.m_rver_servo_use != SysParaBak.m_rver_servo_use)				parModify |= ((quint64)1 << LOG_RVER_SERVO_USE);
            if (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0)
                if (SysPara.m_rhor_servo_use != SysParaBak.m_rhor_servo_use)				parModify |= ((quint64)1 << LOG_RHOR_SERVO_USE);
        }
		// 气动副臂使用配置
		if (SysPara.m_runner_use != SysParaBak.m_runner_use)						parModify |= ((quint64)1 << LOG_RUNNER_USE);
        // 气动副臂下位电眼使用配置
        if (SysPara.m_runner_down_use != SysParaBak.m_runner_down_use)				parModify |= ((quint64)1 << LOG_RUNNER_DOWN_USE);
        // 气动副臂前进电眼使用配置
        if (SysPara.m_runner_advance_use != SysParaBak.m_runner_advance_use)		parModify |= ((quint64)1 << LOG_RUNNER_ADVANCE_USE);
        // 气动副臂后退电眼使用配置
        if (SysPara.m_runner_return_use != SysParaBak.m_runner_return_use)			parModify |= ((quint64)1 << LOG_RUNNER_RETURN_USE);
        // 调位使用配置
		if (SysPara.m_adjust_use != SysParaBak.m_adjust_use)						parModify |= ((quint64)1 << LOG_ADJUST_USE);
        // 原点在模内配置
        if (SysPara.m_home_inmold != SysParaBak.m_home_inmold)
        {
            parModify |= ((quint64)1 << LOG_HOME_INMOLD);
            pModbus->ChangeSafePos_Inmold_Outmold(SysPara.m_home_inmold);
        }
        // 扩展伺服使用配置
		if (SysPara.m_ext_servo_use != SysParaBak.m_ext_servo_use)					parModify |= ((quint64)1 << LOG_EXT_SERVO_USE);
		// 换治具信号配置
		if (SysPara.m_jig_use != SysParaBak.m_jig_use)								parModify |= ((quint64)1 << LOG_JIG_USE);
        // Proc2使用
        if (SysPara.m_proc2_use != SysParaBak.m_proc2_use)                          parModify |= ((quint64)1 << LOG_PROC2_USE);
        // Proc3使用
        if (SysPara.m_proc3_use != SysParaBak.m_proc3_use)                          parModify |= ((quint64)1 << LOG_PROC3_USE);
        // 气动倒角使用
        if (SysPara.m_rotate_use != SysParaBak.m_rotate_use)                        parModify |= ((quint64)1 << LOG_ROTATE_USE);
        //
        if (SysPara.m_run_rotate_use != SysParaBak.m_run_rotate_use)                parModify |= ((quint64)1 << LOG_RUN_ROTATE_USE);
        // IP地址
        if (SysPara.m_ip != SysParaBak.m_ip)                                        parModify |= ((quint64)1 << LOG_IP_LOW);
        if (SysPara.m_submask != SysParaBak.m_submask)                              parModify |= ((quint64)1 << LOG_SUBMASK_LOW);
        if (SysPara.m_gateway != SysParaBak.m_gateway)                              parModify |= ((quint64)1 << LOG_GATEWAY_LOW);
        // Vision
        if (SysPara.m_visionip1 != SysParaBak.m_visionip1)                          return true;
        if (SysPara.m_visionip2 != SysParaBak.m_visionip2)                          return true;
        if (SysPara.m_visionip3 != SysParaBak.m_visionip3)                          return true;
        if (SysPara.m_visionip4 != SysParaBak.m_visionip4)                          return true;
        if (SysPara.m_visionip5 != SysParaBak.m_visionip5)                          return true;
        if (SysPara.m_visionip6 != SysParaBak.m_visionip6)                          return true;
        if (SysPara.m_visionip7 != SysParaBak.m_visionip7)                          return true;
        if (SysPara.m_visionip8 != SysParaBak.m_visionip8)                          return true;
        if (SysPara.m_vision1port != SysParaBak.m_vision1port)                      return true;
        if (SysPara.m_vision2port != SysParaBak.m_vision2port)                      return true;
        if (SysPara.m_vision3port != SysParaBak.m_vision3port)                      return true;
        if (SysPara.m_vision4port != SysParaBak.m_vision4port)                      return true;
        if (SysPara.m_vision5port != SysParaBak.m_vision5port)                      return true;
        if (SysPara.m_vision6port != SysParaBak.m_vision6port)                      return true;
        if (SysPara.m_vision7port != SysParaBak.m_vision7port)                      return true;
        if (SysPara.m_vision8port != SysParaBak.m_vision8port)                      return true;
        if (SysPara.m_vision1_outvar != SysParaBak.m_vision1_outvar)                return true;
        if (SysPara.m_vision2_outvar != SysParaBak.m_vision2_outvar)                return true;
        if (SysPara.m_vision3_outvar != SysParaBak.m_vision3_outvar)                return true;
        if (SysPara.m_vision4_outvar != SysParaBak.m_vision4_outvar)                return true;
        if (SysPara.m_vision5_outvar != SysParaBak.m_vision5_outvar)                return true;
        if (SysPara.m_vision6_outvar != SysParaBak.m_vision6_outvar)                return true;
        if (SysPara.m_vision7_outvar != SysParaBak.m_vision7_outvar)                return true;
        if (SysPara.m_vision8_outvar != SysParaBak.m_vision8_outvar)                return true;
        if (SysPara.m_vision1_trigger != SysParaBak.m_vision1_trigger)              return true;
        if (SysPara.m_vision2_trigger != SysParaBak.m_vision2_trigger)              return true;
        if (SysPara.m_vision3_trigger != SysParaBak.m_vision3_trigger)              return true;
        if (SysPara.m_vision4_trigger != SysParaBak.m_vision4_trigger)              return true;
        if (SysPara.m_vision5_trigger != SysParaBak.m_vision5_trigger)              return true;
        if (SysPara.m_vision6_trigger != SysParaBak.m_vision6_trigger)              return true;
        if (SysPara.m_vision7_trigger != SysParaBak.m_vision7_trigger)              return true;
        if (SysPara.m_vision8_trigger != SysParaBak.m_vision8_trigger)              return true;
        // 取物失败，开关安全门程序结束
        if (SysPara.m_door_reset_use != SysParaBak.m_door_reset_use)                parModify |= ((quint64)1 << LOG_DOOR_RESET_USE);
        // 扩展控制位
        if (SysPara.m_extend_bit_use != SysParaBak.m_extend_bit_use)                return true;
		// 非教导模式
		if (TemplateChecked != ui->checkTemplate->isChecked())	return true;
        if (AlfaChecked != ui->checkAlfaMode->isChecked())	return true;

		//退出自动时清除IO口
		if(SysPara.m_sys_io_clr != SysParaBak.m_sys_io_clr)							return true;

        for(int i = 0;i < HOME_DEF_MAX; i ++ )
        {
            if (home[i] != bakhome[i] )
            {
                parModify = 1 ;
                break;
            }
        }

	}
	if (xPermissions::GetPermissions(PER_SYS_MAINTAIN) == true)
	{
		// 机械手维护模数
		if (SysPara.m_service_moldings != SysParaBak.m_service_moldings)			return true;
	}

	if (parModify == 0)
		return false;
	else
		return true;
}
// 检查参数合法性
bool Formsystem::CheckValid(void)
{
	return true;
}
// 保存系统参数设置
bool Formsystem::SavePara(void)
{
	try
	{
		if (pModbus->WriteSystem(SysPara, parModify))
			throw false;
		if (pModbus->CommandWrite(CMD_WRITE_SYSTEM))
			throw false;
		QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
		settings.setValue(XPAD_SET_TEMPLATE, ui->checkTemplate->isChecked());
        pModbus->SetTemplateUse(ui->checkTemplate->isChecked());
        settings.setValue(XPAD_SET_ALFAMODE, ui->checkAlfaMode->isChecked());
        pModbus->SetALFAMode(ui->checkAlfaMode->isChecked());
        settings.setValue(XPAD_SET_IP, SysPara.m_ip);
        settings.setValue(XPAD_SET_SUBMASK, SysPara.m_submask);
        settings.setValue(XPAD_SET_GATEWAY, SysPara.m_gateway);
        settings.sync();
        if (pModbus->WriteHome(home))
            throw false;
        if (pModbus->CommandWrite(CMD_WRITE_USER))
            throw false;
	}
	catch (bool &)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAVE_PARA_ERROR));
		return false;
	}
	return true;
}
// 翻译界面
void Formsystem::changeEvent(QEvent *e)
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

bool Formsystem::EnterForm(void)
{
    // 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return false;
	}
    // 检查用户权限
    if ((xPermissions::GetPermissions(PER_SYS_NORMAL) == false) && (xPermissions::GetPermissions(PER_SYS_SIGNAL) == false) &&
            (xPermissions::GetPermissions(PER_SYS_RESET) == false) && (xPermissions::GetPermissions(PER_SYS_MAINTAIN) == false))
    {
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (pDialogMain)
            if (pDialogMain->ScreenSaverUserManager() == 0)
        return false;
    }
	// 如果系统不在手动状态则不能进入系统参数设置画面
	if (pModbus->GetSysState() != SYS_STATE_MANUAL)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SYSTEM_NO_MANUAL));
		return false;
	}
	// 查询系统参数设置
	if (QueryPara() != true)
		return false;
//    if(pModbus->GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
//        ui->checkSvExt->setVisible(false);
    // 设置激活码框为空
    ui->lineEditCurProCode->setText("");
    ui->lineEditNewProCode->setText("");
    ui->lineEditNewProCode2->setText("");
    ui->lineEditUpdateReg->setText("");
	// 根据当前用户权限设置界面
	setPermissions();
#if ((FACTORY == FA_SINROBOT_SIDE) || (FACTORY == FA_JIEJIA_SIDE))
    ui->groupBoxRotate->setTitle(tr("上下时倒角状态"));
#endif
//    if (!pModbus->GetFunctions(SUB_FUN2_VISION))
        ui->tabWidgetSystem->removeTab(TAB_PAGE_VISION);
    ui->labelVisionInfo->setText(tr("当前视觉编号：") + QString::number(m_visionidx+1) + tr(" ，总可设置视觉数：8"));
    ui->spinBoxVisionIdx->setValue(m_visionidx+1);
	ui->tabWidgetSystem->setCurrentIndex(0);
    if (ui->lineEditCurProCode->isEnabled())
    {
        ui->labelRemainTime->setVisible(true);
        if (pModbus->GetRemainTime() == 0xFFFFFFFF)
            ui->labelRemainTime->setText(tr("系统剩余使用时间：") + tr("无限期"));
        else
        {
            quint32 remainTime, day, hour, minute, second;
            remainTime = pModbus->GetRemainTime();
            day = remainTime / (24*60*60);
            hour = (remainTime - day*24*60*60) / (60*60);
            minute = (remainTime - day*24*60*60 - hour*60*60) / 60;
            second = remainTime - day*24*60*60 - hour*60*60 - minute*60;
            ui->labelRemainTime->setText(tr("系统剩余使用时间：") + QString::number(day) + tr("天") + QString::number(hour) + tr("小时") + QString::number(minute) + tr("分钟") + QString::number(second) + tr("秒"));
        }
    }
    else
        ui->labelRemainTime->setVisible(false);
    // 连接信号槽
    connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    connect(pModbus, SIGNAL(signal_active_remainTime(uint32_t)), this, SLOT(activeRemainTime(uint32_t)));
    // 显示界面
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        ui->checkSvRaVer->setText(tr("使用") + GetServoName(AXIS_IDX_RVER) + tr("(倒角)伺服"));
        ui->checkSvRaHor->setText(tr("使用") + GetServoName(AXIS_IDX_RHOR) + tr("(旋转)伺服"));
    }
    else if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E3)
    {
        ui->checkSvRaVer->setText(tr("使用") + GetServoName(AXIS_IDX_RVER) + tr("伺服"));
        ui->checkSvRaHor->setText(tr("使用") + GetServoName(AXIS_IDX_RHOR) + tr("伺服"));
    }
    ui->checkSvExt->setText(tr("使用") + GetServoName(AXIS_IDX_EXT) + tr("伺服"));
#if ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE))
        ui->checkProc2->setText(tr("使用喷雾臂进程"));
        ui->checkMcp->setText(tr("使用压铸机关模完成信号"));
        ui->checkImop->setText(tr("使用压铸机开模中间信号"));
        ui->checkMid->setText(tr("使用压铸机中板模确认信号"));
        ui->BoxOilIntervalDay->setEnabled(false);
#elif (FACTORY == FA_YIDAO)
        ui->checkProc2->setText(tr("使用进程二"));
        ui->checkMcp->setText(tr("使用压铸机关模完成信号"));
        ui->checkImop->setText(tr("使用压铸机开模中间信号"));
        ui->checkMid->setText(tr("使用压铸机中板模确认信号"));
        ui->BoxOilIntervalDay->setEnabled(true);
#elif (FACTORY == FA_SINROBOT_JC)
    ui->checkMcp->setText(tr("使用机床关模完成信号"));
    ui->checkImop->setText(tr("使用机床开模中间信号"));
    ui->checkMid->setText(tr("使用机床中板模确认信号"));
    ui->groupBoxSafeDoor->setTitle(tr("自动运行时开防护门"));
#else
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        ui->checkProc2->setText(tr("使用喷雾臂进程"));
        ui->checkMcp->setText(tr("使用压铸机关模完成信号"));
        ui->checkImop->setText(tr("使用压铸机开模中间信号"));
        ui->checkMid->setText(tr("使用压铸机中板模确认信号"));
        ui->BoxOilIntervalDay->setEnabled(false);
    }
    else
    {
        ui->checkProc2->setText(tr("使用进程二"));
        ui->checkMcp->setText(tr("使用注塑机关模完成信号"));
        ui->checkImop->setText(tr("使用注塑机开模中间信号"));
        ui->checkMid->setText(tr("使用注塑机中板模确认信号"));
        ui->groupBoxSafeDoor->setTitle(tr("自动运行时开安全门"));
        ui->BoxOilIntervalDay->setEnabled(true);
    }
#endif

#if (FACTORY == FA_MIDEA)	// 20240827 美的隐藏自动开安全门暂停接口
	ui->groupBoxSafeDoor->setVisible(false);
#endif

    if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        ui->checkRunRotateUse->setChecked(false);
        ui->checkRunRotateUse->setEnabled(false);
        ui->checkRunner->setEnabled(false);
        ui->checkRunnerAdvance->setEnabled(false);
        ui->checkRunnerDown->setEnabled(false);
        ui->checkRunnerReturn->setEnabled(false);
        ui->checkSvExt->setEnabled(false);
        ui->checkSvPaHor->setEnabled(false);
        ui->checkHomeInmold->setEnabled(false);
        ui->checkDoorReset->setEnabled(false);
        ui->checkOutSafe2->setEnabled(false);
        ui->checkSvRaHor->setEnabled(false);
    }
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0))
    {
        ui->checkProc2->setChecked(false);
        ui->checkProc2->setEnabled(false);
        ui->checkProc3->setChecked(false);
        ui->checkProc3->setEnabled(false);
        ui->checkOilUse->setChecked(false);
        ui->checkOilUse->setEnabled(false);
        ui->checkRunRotateUse->setChecked(false);
        ui->checkRunRotateUse->setEnabled(false);
    }
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        ui->checkRunnerDown->setEnabled(false);
        ui->checkRunnerAdvance->setEnabled(false);
    }
    else
    {
        ui->checkRunnerDown->setEnabled(true);
        ui->checkRunnerAdvance->setEnabled(true);
    }
    // 设置输出端口状态
    ui->lineEditVisionOutput->setEnabled(m_visiondata[m_visionidx][2]&1);
#if PENDANT_PROTOCOL
    if (pModbus->GetFunctions(SUB_FUN2_ROTATE))
        ui->radioButtonNoLimit->setVisible(true);
    else
        ui->radioButtonNoLimit->setVisible(false);
#else
    ui->radioButtonNoLimit->setVisible(true);
#endif
#if (FACTORY == FA_KEHUI)
        ui->radioButtonContinue->setText(tr("安全门不使用"));
#endif
//	show();
	return true;
}

bool Formsystem::ExitForm(void)
{
	LoadPara();
	if (isModified() == true)
	{
		// 参数设置已经更改
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
	disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    disconnect(pModbus, SIGNAL(signal_active_remainTime(uint32_t)), this, SLOT(activeRemainTime(uint32_t)));
    // 隐藏界面
//	hide();
	return true;
}
// 根据当前用户权限设置界面
void Formsystem::setPermissions(void)
{

    // 系统运行参数设置权限
    // 参数初始化权限
    ui->tabWidgetSystem->setTabEnabled(TAB_PAGE_RUN, xPermissions::GetPermissions(PER_SYS_NORMAL));
    ui->tabWidgetSystem->setTabEnabled(TAB_PAGE_RESET, xPermissions::GetPermissions(PER_SYS_RESET));
	ui->tabWidgetSystem->setTabEnabled(TAB_PAGE_HOME, xPermissions::GetPermissions(PER_SYS_RESET));
    // 系统维护权限
	if (xPermissions::GetPermissions(PER_SYS_MAINTAIN))
	{
		quint16 id = pModbus->GetFactoryId();
        if (ui->tabWidgetSystem->count() < MAX_TAB_PAGE)
        {
            ui->tabWidgetSystem->insertTab(TAB_PAGE_MAINTAIN, ui->tabMaintain, QIcon(":/img/widget/TabHeader.png"), tr("系统维护"));
            ui->tabWidgetSystem->setTabEnabled(TAB_PAGE_MAINTAIN, xPermissions::GetPermissions(PER_SYS_MAINTAIN));
        }
		if ((id != 0) && (FACTORY != id))
		{
			if (xPermissions::GetCurrentUser() == xPermissions::SuperUser)
			{
				ui->labelMaintainTip->setText(tr("操作器与主控模块厂商代码不一致！"));
				ui->groupMaintainMold->setEnabled(true);
			}
			else
			{
				ui->labelMaintainTip->setText(tr("操作器与主控模块厂商代码不一致，不能设置系统维护参数！"));
				ui->groupMaintainMold->setEnabled(false);
			}
		}
		else
		{
			ui->labelMaintainTip->clear();
			ui->groupMaintainMold->setEnabled(true);
		}
	}
	else
	{
        if (ui->tabWidgetSystem->count() >= MAX_TAB_PAGE)
            ui->tabWidgetSystem->removeTab(TAB_PAGE_MAINTAIN);
	}
    ui->tabWidgetSystem->setTabEnabled(TAB_PAGE_VISION, xPermissions::GetPermissions(PER_SYS_RESET));
	if (xPermissions::GetPermissions(PER_MANUFACTURER))
    {
//        ui->checkAlfaMode->setVisible(true);
		ui->checkTemplate->setVisible(true);
    }
	else
    {
//        ui->checkAlfaMode->setVisible(false);
		ui->checkTemplate->setVisible(false);
    }
    if (xPermissions::GetCurrentUser() == xPermissions::SuperUser)
    {
        ui->checkAlfaMode->setVisible(true);
        ui->checkRunnerDown->setVisible(true);
        ui->checkRunnerAdvance->setVisible(true);
        ui->checkRunnerReturn->setVisible(true);
    }
    else
    {
        ui->checkAlfaMode->setVisible(false);
        ui->checkRunnerDown->setVisible(false);
        ui->checkRunnerAdvance->setVisible(false);
        ui->checkRunnerReturn->setVisible(false);
    }

    // 产品激活框显示
    if (xPermissions::GetPermissions(PER_SYS_MAINTAIN))
        ui->groupBoxProCode->setVisible(true);
    else
        ui->groupBoxProCode->setVisible(false);
}
// 当前登录用户更改槽
void Formsystem::userChange(void)
{
	if ((xPermissions::GetPermissions(PER_SYS_NORMAL) == false) || (xPermissions::GetPermissions(PER_SYS_SIGNAL) == false) ||
			(xPermissions::GetPermissions(PER_SYS_RESET) == false) || (xPermissions::GetPermissions(PER_SYS_MAINTAIN) == false))
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
	setPermissions();
}
void Formsystem::activeRemainTime(uint32_t time)
{
    // 精确到分钟，*天*小时*分钟
    if (time == 0xFFFFFFFF)
        ui->labelRemainTime->setText(tr("系统剩余使用时间：") + tr("无限期"));
    else
    {
        quint32 remainTime, day, hour, minute, second;
        remainTime = time;
        day = remainTime / (24*60*60);
        hour = (remainTime - day*24*60*60) / (60*60);
        minute = (remainTime - day*24*60*60 - hour*60*60) / 60;
        second = remainTime - day*24*60*60 - hour*60*60 - minute*60;
        ui->labelRemainTime->setText(tr("系统剩余使用时间：") + QString::number(day) + tr("天") + QString::number(hour) + tr("小时") + QString::number(minute) + tr("分钟") + QString::number(second) + tr("秒"));
    }
}
// 输入计划生产数量信号槽
void Formsystem::slotPrdCnt(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxPlan->minimum(), ui->BoxPlan->maximum()) == QDialog::Accepted)
		ui->BoxPlan->setValue(value);
}
// 输入生产数量提醒信号槽
void Formsystem::slotRmdCnt(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxRemind->minimum(), ui->BoxRemind->maximum()) == QDialog::Accepted)
		ui->BoxRemind->setValue(value);
}
// 输入累计不良品报警数量信号槽
void Formsystem::slotRjtCnt(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxReject->minimum(), ui->BoxReject->maximum()) == QDialog::Accepted)
		ui->BoxReject->setValue(value);
}
// 输入报警器鸣叫次数信号槽
void Formsystem::slotAlmCnt(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxAlmCnt->minimum(), ui->BoxAlmCnt->maximum()) == QDialog::Accepted)
		ui->BoxAlmCnt->setValue(value);
}
// 输入报警器鸣叫时间信号槽
void Formsystem::slotAlmTime(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxAlmTime->minimum(), ui->BoxAlmTime->maximum()) == QDialog::Accepted)
		ui->BoxAlmTime->setValue(value);
}
// 输入维护模数信号槽
void Formsystem::slotMaintain(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxMaintain->minimum(), ui->BoxMaintain->maximum()) == QDialog::Accepted)
		ui->BoxMaintain->setValue(value);
}
// ************************************************
// 复位操作信号槽
// ************************************************
// 清除生产总模数
void Formsystem::clrMouldSum(void)
{
	if (xMessageBox::DoQuestion(tr("系统提示"), tr("本操作将会清除生产总模数并且无法恢复！\n确定要清除生产总模数吗？")) == XMSG_RET_YES)
	{
		if (pModbus->CommandReset(CMD_RESET_MOLDS) == SENDMSG_RET_ACK)
		{
			xMessageBox::DoInformation(tr("系统提示"), tr("生产总模数已经成功清除！"));
			// 写入系统日志
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_CLEAR_SUM);
			xSysLog::SaveChange();
		}
	}
}
// 复位系统参数设置
void Formsystem::resetSysPara(void)
{
	if (xMessageBox::DoQuestion(tr("系统提示"), tr("本操作将会把系统参数重置为出厂默认值并且无法恢复！\n确定要重置系统参数设置吗？")) == XMSG_RET_YES)
	{
		if (pModbus->CommandReset(CMD_RESET_SYSTEM) == SENDMSG_RET_ACK)
		{
			// 重新读取系统参数
			pModbus->ReadSystem();
			QueryPara();
			// 复位系统参数不应修改界面语言,恢复原有的语言设置
			QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
			quint8 lan = settings.value(XPAD_SET_LANGUAGE, LAN_CHINESE_S).toUInt();
			pModbus->WriteLanguage(lan);
			xMessageBox::DoInformation(tr("系统提示"), tr("系统参数设置已经重置为出厂默认值！"));
			// 写入系统日志
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_RESET_SYSPAR);
			xSysLog::SaveChange();
		}
	}
}
// 复位伺服参数设置
void Formsystem::resetSrvPara(void)
{
	if (xMessageBox::DoQuestion(tr("系统提示"), tr("本操作将会把伺服参数重置为出厂默认值并且无法恢复！\n确定要重置伺服参数设置吗？")) == XMSG_RET_YES)
	{
		if (pModbus->CommandReset(CMD_RESET_SERVO) == SENDMSG_RET_ACK)
		{
			pModbus->ReadServo();
			xMessageBox::DoInformation(tr("系统提示"), tr("伺服参数设置已经重置为出厂默认值！"));
			// 写入系统日志
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_RESET_SRVPAR);
			xSysLog::SaveChange();
		}
	}
}
//复位驱动器参数
void Formsystem::resetSvdevPara(void)
{
	if (xMessageBox::DoQuestion(tr("系统提示"), tr("本操作将会把驱动器参数重置为出厂默认值并且无法恢复！\n确定要重置驱动器参数设置吗？")) == XMSG_RET_YES)
		{
			if (pModbus->CommandReset(CMD_RESET_SVDEV) == SENDMSG_RET_ACK)
			{
				pModbus->ReadServo();
				xMessageBox::DoInformation(tr("系统提示"), tr("伺服参数设置已经重置为出厂默认值！"));
				// 写入系统日志
				xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_RESET_SRVPAR);
				xSysLog::SaveChange();
			}
		}
}
// 复位系统密码设置
void Formsystem::resetPwd(void)
{
	if (xMessageBox::DoQuestion(tr("系统提示"), tr("本操作将会把系统密码重置为出厂默认值并且无法恢复！\n确定要重置系统密码设置吗？")) == XMSG_RET_YES)
	{
		QByteArray pwd;
		xPermissions::DefaultPwd(xPermissions::AdvOperater, pwd);
		if (pModbus->WritePwd(xPermissions::AdvOperater, pwd) != SENDMSG_RET_ACK)
		{
			xMessageBox::DoWarning(tr("系统提示"), tr("重置高级操作员密码失败！\n请检查系统通讯链路是否正常。"));
			return;
		}
		xPermissions::DefaultPwd(xPermissions::Administrator, pwd);
		if (pModbus->WritePwd(xPermissions::Administrator, pwd) != SENDMSG_RET_ACK)
		{
			xMessageBox::DoWarning(tr("系统提示"), tr("重置管理员密码失败！\n请检查系统通讯链路是否正常。"));
			return;
		}
		xMessageBox::DoInformation(tr("系统提示"), tr("高级操作员和管理员密码已经成功重置为出厂默认值！"));
		// 写入系统日志
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_RESET_PWD);
		xSysLog::SaveChange();
	}
}
// ************************************************
// 选择输入端口
// ************************************************
// ************************************************
// 保存参数信号槽
// ************************************************
void Formsystem::AcceptSetup(void)
{

	if ((xPermissions::GetPermissions(PER_SYS_NORMAL) == false) && (xPermissions::GetPermissions(PER_SYS_SIGNAL) == false) &&
			(xPermissions::GetPermissions(PER_SYS_RESET) == false) && (xPermissions::GetPermissions(PER_SYS_MAINTAIN) == false))
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
		return;
	}
	LoadPara();
//    if ((SysPara.m_ip & SysPara.m_submask) != (SysPara.m_gateway & SysPara.m_submask))
//    {
//        xMessageBox::DoWarning(tr("系统提示"), tr("IP地址和网关不在同一网段，请返回修改"));
//        return;
//    }
	if (isModified())
	{
		if (CheckValid() == false)
			return;
		if (SavePara() == false)
			return;
		// 备份系统参数设置
		memcpy(&bakhome, &home, sizeof(quint16)*HOME_DEF_MAX);
		memcpy(&SysParaBak, &SysPara, sizeof(SystemParameter));
		TemplateChecked = ui->checkTemplate->isChecked();
        AlfaChecked = ui->checkAlfaMode->isChecked();
	}
	// 显示保存成功信息
#if UI_SAVED_TIP
	xMessageBox::DoInformation(tr("保存参数"), xStringResource::GetString(STRRES_HAS_SAVED));
#endif
}
// 根据数组内容，刷新Table参数
void Formsystem::UpdateTab()
{
	for(int i = 0;i < HOME_ACTION_MAX; i++)
		ui->tableAxis->item(i, 0)->setText(TranslateAxis(Axis[i]));
}
// 解析轴名称
QString Formsystem::TranslateAxis(quint8 Step)
{
	switch (Step)
	{
        case CUSTOMER_FUN_Y_HOME:		return QString(tr("伺服 ") + GetServoName(AXIS_IDX_PVER)+ tr("轴原点"));		//*
        case CUSTOMER_FUN_Z_HOME:		return QString(tr("伺服 ") + GetServoName(AXIS_IDX_TRV)+ tr("轴原点"));			//*
        case CUSTOMER_FUN_X_HOME:		return QString(tr("伺服 ") + GetServoName(AXIS_IDX_PHOR)+ tr("轴原点"));		//*
        case CUSTOMER_FUN_A_HOME:
        if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
            return QString(tr("伺服 ") + GetServoName(AXIS_IDX_RVER)+ tr("(倒角)轴原点"));		//*
        else
            return QString(tr("伺服 ") + GetServoName(AXIS_IDX_RVER)+ tr("轴原点"));		//*
        case CUSTOMER_FUN_B_HOME:
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E3)
            return QString(tr("伺服 ") + GetServoName(AXIS_IDX_RHOR)+ tr("(旋转)轴原点"));		//*
        else
            return QString(tr("伺服 ") + GetServoName(AXIS_IDX_RHOR)+ tr("轴原点"));		//*
        case CUSTOMER_FUN_C_HOME:		return QString(tr("伺服 ") + GetServoName(AXIS_IDX_EXT)+ tr("轴原点"));			//*
		case CUSTOMER_FUN_PRO_VER:		return QString(tr("气动 主臂上行"));
		case CUSTOMER_FUN_PRO_HOR:    	return QString(tr("气动 主臂引拔"));
		case CUSTOMER_FUN_PRO_ROT:		return QString(tr("气动 主臂倒角"));			//*
		case CUSTOMER_FUN_PRO_REV:    	return QString(tr("气动 主臂旋转"));
		case CUSTOMER_FUN_RUN_VER:		return QString(tr("气动 副臂上行"));			//*
        case CUSTOMER_FUN_RUN_HOR:    	return QString(tr("气动 副臂引拔"));          //*
        case CUSTOMER_FUN_RUN_ROT:		return QString(tr("气动 副臂倒角"));          //*
		case CUSTOMER_FUN_RUN_REV:    	return QString(tr("气动 副臂旋转"));
		default:						return QString(tr("其他 扩展动作"));			//*
	}
}
// 判断轴原点复归顺序
bool Formsystem::MoveTab(quint8 currentselect, quint8 last_range)
{
	int i;
	bool ret = FALSE;
    if (last_range > 10) return ret;

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
// 向下一项
void Formsystem::AxisGoDown(void)
{
	quint8 current_Select = ui->tableAxis->currentRow();
	if (MoveTab(current_Select, current_Select + 1))
	{
		UpdateTab();
		ui->tableAxis->setCurrentCell(current_Select + 1, 0);
	}
}
// 向上一项
void Formsystem::AxisGoUp(void)
{
	quint8 current_Select = ui->tableAxis->currentRow();
	if (MoveTab(current_Select, current_Select-1))
	{
		UpdateTab();
		ui->tableAxis->setCurrentCell(current_Select - 1, 0);
	}
}
// 移动至顶部
void Formsystem::AxisGoTop(void)
{
	if (MoveTab(ui->tableAxis->currentRow(), 0))
	{
		UpdateTab();
		ui->tableAxis->setCurrentCell(0, 0);
	}
}
// 移动至底部
void Formsystem::AxisGoBottom(void)
{
    if (MoveTab(ui->tableAxis->currentRow(), 10))
	{
		UpdateTab();
        ui->tableAxis->setCurrentCell(10, 0);
	}
}
// 8个原点复归顺序到20个地址的映射
void Formsystem::TransHome(quint16 (&home)[HOME_DEF_MAX])
{
	for(int i = 0; i < HOME_DEF_MAX; ++i)
	{
		if (i < HOME_ACTION_MAX)
			home[i] = Axis[i];
		else
			home[i] = 0xFF;
	}
}
// 更新激活码
bool Formsystem::UpdateRegCode(void)
{
    if (!ui->lineEditCurProCode->isEnabled())
    {
        xMessageBox::DoInformation(tr("提示"), tr("请先设置产品密钥，再更新激活码！"));
        return false;
    }
    QString tmpRegCode;
    tmpRegCode = ui->lineEditUpdateReg->text();
    if (tmpRegCode.length() < 16)
    {
        xMessageBox::DoInformation(tr("更新激活码"), tr("激活码必须为16位，请检查后重新输入！"));
        return false;
    }
    if (!checkRegCodeValid(tmpRegCode))
    {
        xMessageBox::DoInformation(tr("警告"), tr("无效激活码！"));
        return false;
    }
    RegCode.m_activation_1 = tmpRegCode.at(0).toAscii() | tmpRegCode.at(1).toAscii()<< 8;
    RegCode.m_activation_2 = tmpRegCode.at(2).toAscii() | tmpRegCode.at(3).toAscii()<< 8;
    RegCode.m_activation_3 = tmpRegCode.at(4).toAscii() | tmpRegCode.at(5).toAscii()<< 8;
    RegCode.m_activation_4 = tmpRegCode.at(6).toAscii() | tmpRegCode.at(7).toAscii()<< 8;
    RegCode.m_activation_5 = tmpRegCode.at(8).toAscii() | tmpRegCode.at(9).toAscii()<< 8;
    RegCode.m_activation_6 = tmpRegCode.at(10).toAscii() | tmpRegCode.at(11).toAscii()<< 8;
    RegCode.m_activation_7 = tmpRegCode.at(12).toAscii() | tmpRegCode.at(13).toAscii()<< 8;
    RegCode.m_activation_8 = tmpRegCode.at(14).toAscii() | tmpRegCode.at(15).toAscii()<< 8;
    try
    {
        if (pModbus->WriteRegistrationCode(RegCode))
            throw false;
        if (pModbus->CommandWrite(CMD_WRITE_REGISTRATION))
            throw false;
    }
    catch (bool &)
    {
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAVE_PARA_ERROR));
        return false;
    }
    ui->lineEditUpdateReg->setText("");
    ui->labelRemainTime->setVisible(true);
    if (pModbus->GetRemainTime() == 0xFFFFFFFF)
        ui->labelRemainTime->setText(tr("系统剩余使用时间：") + tr("无限期"));
    else
    {
        quint32 remainTime, day, hour, minute, second;
        remainTime = pModbus->GetRemainTime();
        day = remainTime / (24*60*60);
        hour = (remainTime - day*24*60*60) / (60*60);
        minute = (remainTime - day*24*60*60 - hour*60*60) / 60;
        second = remainTime - day*24*60*60 - hour*60*60 - minute*60;
        ui->labelRemainTime->setText(tr("系统剩余使用时间：") + QString::number(day) + tr("天") + QString::number(hour) + tr("小时") + QString::number(minute) + tr("分钟") + QString::number(second) + tr("秒"));
    }
    // 写入系统日志
    xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_ACTIVATION);
    xSysLog::SaveChange();
    return true;
}
// 更新产品密钥
bool Formsystem::UpdateProductCode(void)
{
    QString tmpCurProCode, tmpNewProCode, strActive;
    if (ui->lineEditCurProCode->isEnabled())
    {
        if (ui->lineEditCurProCode->text().length() < 10)
        {
            xMessageBox::DoInformation(tr("更新产品密钥"), tr("产品密钥必须为10位，请检查后重新输入！"));
            return false;
        }
    }
    if ((ui->lineEditNewProCode->text().length() <10)||(ui->lineEditNewProCode2->text().length() <10))
    {
        xMessageBox::DoInformation(tr("更新产品密钥"), tr("产品密钥必须为10位，请检查后重新输入！"));
        return false;
    }
    if (ui->lineEditNewProCode->text() != ui->lineEditNewProCode2->text())
    {
        xMessageBox::DoInformation(tr("更新产品密钥"), tr("两次输入的新产品密钥不匹配，请检查后重新输入！"));
        return false;
    }

    tmpCurProCode = ui->lineEditCurProCode->text();
    tmpNewProCode = ui->lineEditNewProCode->text();
    if (ui->lineEditCurProCode->isEnabled())
    {
        if (((tmpCurProCode.at(0).toAscii() | tmpCurProCode.at(1).toAscii() <<8)!= ProCodeBak.m_product_id1) ||
            ((tmpCurProCode.at(2).toAscii() | tmpCurProCode.at(3).toAscii() <<8)!= ProCodeBak.m_product_id2) ||
            ((tmpCurProCode.at(4).toAscii() | tmpCurProCode.at(5).toAscii() <<8)!= ProCodeBak.m_product_id3) ||
            ((tmpCurProCode.at(6).toAscii() | tmpCurProCode.at(7).toAscii() <<8)!= ProCodeBak.m_product_id4) ||
            ((tmpCurProCode.at(8).toAscii() | tmpCurProCode.at(9).toAscii() <<8)!= ProCodeBak.m_product_id5))
        {
            xMessageBox::DoInformation(tr("更新产品密钥"), tr("旧产品密钥不匹配，请检查后重新输入！"));
            return false;
        }
    }
    else
    {
        xMessageBoxActive BoxActive;
        if (BoxActive.DoForm(strActive) == QDialog::Accepted)
        {
            if (strActive.length() < 16)
            {
                xMessageBox::DoInformation(tr("更新产品密钥"), tr("首次设置产品密钥必须同时设置激活码! 激活码必须为16位，请检查后重新输入！"));
                return false;
            }
            if (!checkRegCodeValid(strActive, tmpNewProCode))
            {
                xMessageBox::DoInformation(tr("警告"), tr("无效激活码，产品密钥未更新，请检查后重新设置！"));
                return false;
            }
        }
        else
        {
            xMessageBox::DoInformation(tr("更新产品密钥"), tr("首次设置产品密钥必须同时设置激活码！产品密钥未更新！"));
            ui->lineEditUpdateReg->setText("");
            return false;
        }
    }

    RegCode.m_activation_1 = strActive.at(0).toAscii() | strActive.at(1).toAscii()<< 8;
    RegCode.m_activation_2 = strActive.at(2).toAscii() | strActive.at(3).toAscii()<< 8;
    RegCode.m_activation_3 = strActive.at(4).toAscii() | strActive.at(5).toAscii()<< 8;
    RegCode.m_activation_4 = strActive.at(6).toAscii() | strActive.at(7).toAscii()<< 8;
    RegCode.m_activation_5 = strActive.at(8).toAscii() | strActive.at(9).toAscii()<< 8;
    RegCode.m_activation_6 = strActive.at(10).toAscii() | strActive.at(11).toAscii()<< 8;
    RegCode.m_activation_7 = strActive.at(12).toAscii() | strActive.at(13).toAscii()<< 8;
    RegCode.m_activation_8 = strActive.at(14).toAscii() | strActive.at(15).toAscii()<< 8;

    ProCode.m_product_id1 = tmpNewProCode.at(0).toAscii() | tmpNewProCode.at(1).toAscii() <<8;
    ProCode.m_product_id2 = tmpNewProCode.at(2).toAscii() | tmpNewProCode.at(3).toAscii() <<8;
    ProCode.m_product_id3 = tmpNewProCode.at(4).toAscii() | tmpNewProCode.at(5).toAscii() <<8;
    ProCode.m_product_id4 = tmpNewProCode.at(6).toAscii() | tmpNewProCode.at(7).toAscii() <<8;
    ProCode.m_product_id5 = tmpNewProCode.at(8).toAscii() | tmpNewProCode.at(9).toAscii() <<8;

    try
    {
        if (pModbus->WriteProductCode(ProCode))
            throw false;
        if (pModbus->CommandWrite(CMD_WRITE_PRODUCTCODE))
            throw false;
        if (!ui->lineEditCurProCode->isEnabled())
        {
            if (pModbus->WriteRegistrationCode(RegCode))
                throw false;
            if (pModbus->CommandWrite(CMD_WRITE_REGISTRATION))
                throw false;
        }
    }
    catch (bool &)
    {
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAVE_PARA_ERROR));
        return false;
    }
    xMessageBox::DoInformation(tr("更新产品密钥"), tr("产品密钥更新成功！"));
    // 写入系统日志
    xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_PRODUCT_ID);
    xSysLog::SaveChange();
    memcpy(&ProCodeBak, &ProCode, sizeof(ProductCode));

//	if ((QChar(ProCode.m_product_id1&0xFF).isPrint()) && (QChar((ProCode.m_product_id1>>8)&0xFF).isPrint()) && (QChar(ProCode.m_product_id2&0xFF).isPrint()) && (QChar((ProCode.m_product_id2>>8)&0xFF).isPrint()&0xFF) &&
//		(QChar(ProCode.m_product_id3&0xFF).isPrint()) && (QChar((ProCode.m_product_id3>>8)&0xFF).isPrint()) && (QChar(ProCode.m_product_id4&0xFF).isPrint()) && (QChar((ProCode.m_product_id4>>8)&0xFF).isPrint()&0xFF) &&
//		(QChar(ProCode.m_product_id5&0xFF).isPrint()) && (QChar((ProCode.m_product_id5>>8)&0xFF).isPrint()))
    if (IsVaildPCode(ProCode))
        ui->lineEditCurProCode->setEnabled(true);
    else
        ui->lineEditCurProCode->setEnabled(false);

    ui->lineEditCurProCode->setText("");
    ui->lineEditNewProCode->setText("");
    ui->lineEditNewProCode2->setText("");
    ui->labelRemainTime->setVisible(ui->lineEditCurProCode->isEnabled());
    return true;
}
// 点击输入框弹出字符键盘
void Formsystem::inputRegCode(void)
{
#if defined(Q_WS_WIN)
    ui->lineEditUpdateReg->setValidator(new QRegExpValidator(QRegExp("[A-Z2-7]{0,16}"), this));
#else
    QString str;
    ui->lineEditUpdateReg->setValidator(new QRegExpValidator(QRegExp("[A-Za-z2-7]{0,16}"), this));
    if (xKbd->DoForm(str, KEYBOARD_TYPE_STR) == QDialog::Accepted)
        ui->lineEditUpdateReg->setText(str.toUpper());
#endif
    if (!ui->lineEditUpdateReg->hasAcceptableInput())
    {
        xMessageBox::DoInformation(tr("系统提示"), tr("含有不符合要求的字符，\n请重新输入！"));
        ui->lineEditUpdateReg->setText("");
    }
}
void Formsystem::inputCurProCode(void)
{
#if defined(Q_WS_WIN)
#else
    QString str;
    if (xKbd->DoForm(str, KEYBOARD_TYPE_STR) == QDialog::Accepted)
        ui->lineEditCurProCode->setText(str.left(10));
#endif
}
void Formsystem::inputNewProCode(void)
{
#if defined(Q_WS_WIN)
#else
    QString str;
    if (xKbd->DoForm(str, KEYBOARD_TYPE_STR) == QDialog::Accepted)
        ui->lineEditNewProCode->setText(str.left(10));
#endif
}
void Formsystem::inputNewProCode2(void)
{
#if defined(Q_WS_WIN)
#else
    QString str;
    if (xKbd->DoForm(str, KEYBOARD_TYPE_STR) == QDialog::Accepted)
        ui->lineEditNewProCode2->setText(str.left(10));
#endif
}
void Formsystem::inputIP1(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxIP1->minimum(), ui->sBoxIP1->maximum()) == QDialog::Accepted)
        ui->sBoxIP1->setValue(value);
}
void Formsystem::inputIP2(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxIP2->minimum(), ui->sBoxIP2->maximum()) == QDialog::Accepted)
        ui->sBoxIP2->setValue(value);
}
void Formsystem::inputIP3(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxIP3->minimum(), ui->sBoxIP3->maximum()) == QDialog::Accepted)
        ui->sBoxIP3->setValue(value);
}
void Formsystem::inputIP4(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxIP4->minimum(), ui->sBoxIP4->maximum()) == QDialog::Accepted)
        ui->sBoxIP4->setValue(value);
}
void Formsystem::inputSubMask1(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxSubMask1->minimum(), ui->sBoxSubMask1->maximum()) == QDialog::Accepted)
        ui->sBoxSubMask1->setValue(value);
}
void Formsystem::inputSubMask2(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxSubMask2->minimum(), ui->sBoxSubMask2->maximum()) == QDialog::Accepted)
        ui->sBoxSubMask2->setValue(value);
}
void Formsystem::inputSubMask3(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxSubMask3->minimum(), ui->sBoxSubMask3->maximum()) == QDialog::Accepted)
        ui->sBoxSubMask3->setValue(value);
}
void Formsystem::inputSubMask4(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxSubMask4->minimum(), ui->sBoxSubMask4->maximum()) == QDialog::Accepted)
        ui->sBoxSubMask4->setValue(value);
}
void Formsystem::inputGateWay1(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxGateWay1->minimum(), ui->sBoxGateWay1->maximum()) == QDialog::Accepted)
        ui->sBoxGateWay1->setValue(value);
}
void Formsystem::inputGateWay2(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxGateWay2->minimum(), ui->sBoxGateWay2->maximum()) == QDialog::Accepted)
        ui->sBoxGateWay2->setValue(value);
}
void Formsystem::inputGateWay3(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxGateWay3->minimum(), ui->sBoxGateWay3->maximum()) == QDialog::Accepted)
        ui->sBoxGateWay3->setValue(value);
}
void Formsystem::inputGateWay4(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxGateWay4->minimum(), ui->sBoxGateWay4->maximum()) == QDialog::Accepted)
        ui->sBoxGateWay4->setValue(value);
}
void Formsystem::inputOilIntervalDay(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxOilIntervalDay->minimum(), ui->BoxOilIntervalDay->maximum()) == QDialog::Accepted)
        ui->BoxOilIntervalDay->setValue(value);
}
void Formsystem::inputOilIntervalHour(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxOilIntervalHour->minimum(), ui->BoxOilIntervalHour->maximum()) == QDialog::Accepted)
        ui->BoxOilIntervalHour->setValue(value);
}
void Formsystem::inputOilIntervalMinute(void)
{
#if (FACTORY == FA_BEIYA || (FACTORY == FA_ZHENJIE))
    ui->BoxOilIntervalMinute->setMaximum(600000);
#else
    ui->BoxOilIntervalMinute->setMaximum(60);
#endif
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxOilIntervalMinute->minimum(), ui->BoxOilIntervalMinute->maximum()) == QDialog::Accepted)
        ui->BoxOilIntervalMinute->setValue(value);
}
void Formsystem::inputOilTime(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxOilTime->minimum(), ui->BoxOilTime->maximum()) == QDialog::Accepted)
        ui->BoxOilTime->setValue(value);
}
void Formsystem::CombineOilInterval(void)
{
#if (FACTORY == FA_BEIYA || (FACTORY == FA_ZHENJIE))
    SysPara.m_oil_interval = ui->BoxOilIntervalMinute->value();
#else
    SysPara.m_oil_interval = ui->BoxOilIntervalDay->value()*24*60*60 + ui->BoxOilIntervalHour->value()*60*60 + ui->BoxOilIntervalMinute->value()*60;
#endif
}
void Formsystem::BreakOilInterval(void)
{
#if (FACTORY == FA_BEIYA || (FACTORY == FA_ZHENJIE))
    ui->BoxOilIntervalDay->setValue(0);
    ui->BoxOilIntervalHour->setValue(0);
    ui->BoxOilIntervalMinute->setValue((SysPara.m_oil_interval));
#else
    ui->BoxOilIntervalDay->setValue(SysPara.m_oil_interval/(24*60*60));
    ui->BoxOilIntervalHour->setValue((SysPara.m_oil_interval - ui->BoxOilIntervalDay->value()*24*60*60)/(60*60));
    ui->BoxOilIntervalMinute->setValue((SysPara.m_oil_interval-ui->BoxOilIntervalDay->value()*24*60*60-ui->BoxOilIntervalHour->value()*60*60)/60);
#endif
}
void Formsystem::BtnPageChanged(void)
{
    if (ui->stackedWidgetMaintain->currentIndex() == 0)
    {
        ui->stackedWidgetMaintain->setCurrentIndex(1);
        ui->labelMaintain->setText(tr("[2/2] 参数重置"));
    }
    else
    {
        ui->stackedWidgetMaintain->setCurrentIndex(0);
        ui->labelMaintain->setText(tr("[1/2] 激活信息"));
    }
}
void Formsystem::checkOilStateChanged(int state)
{
    if (ui->checkOilUse->isChecked())
        ui->checkOilCtrl->setEnabled(true);
    else
        ui->checkOilCtrl->setEnabled(false);
}
// 设置保存按钮显示
void Formsystem::IsBtnOKVisible(int idx)
{
    if (ui->tabWidgetSystem->currentIndex() == TAB_PAGE_MAINTAIN)
        ui->BtnOK->setVisible(false);
    else
        ui->BtnOK->setVisible(true);

}
////////////////////////////////////////////////////////////////////////////
//Vision
////////////////////////////////////////////////////////////////////////////

void Formsystem::inputVisionIP1(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxVisionIP1->minimum(), ui->sBoxVisionIP1->maximum()) == QDialog::Accepted)
    {
        m_visiondata[m_visionidx][0] &= 0x00FFFFFF;
        m_visiondata[m_visionidx][0] |= ((quint32)value << 24);
        ui->sBoxVisionIP1->setValue((quint8)(m_visiondata[m_visionidx][0] >> 24));
    }
}
void Formsystem::inputVisionIP2(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxVisionIP2->minimum(), ui->sBoxVisionIP2->maximum()) == QDialog::Accepted)
    {
        m_visiondata[m_visionidx][0] &= 0xFF00FFFF;
        m_visiondata[m_visionidx][0] |= ((quint32)value << 16);
        ui->sBoxVisionIP2->setValue((quint8)(m_visiondata[m_visionidx][0] >> 16));
    }
}
void Formsystem::inputVisionIP3(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxVisionIP3->minimum(), ui->sBoxVisionIP3->maximum()) == QDialog::Accepted)
    {
        m_visiondata[m_visionidx][0] &= 0xFFFF00FF;
        m_visiondata[m_visionidx][0] |= ((quint32)value << 8);
        ui->sBoxVisionIP3->setValue((quint8)(m_visiondata[m_visionidx][0] >> 8));
    }
}
void Formsystem::inputVisionIP4(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->sBoxVisionIP4->minimum(), ui->sBoxVisionIP4->maximum()) == QDialog::Accepted)
    {
        m_visiondata[m_visionidx][0] &= 0xFFFFFF00;
        m_visiondata[m_visionidx][0] |= (quint32)value;
        ui->sBoxVisionIP4->setValue((quint8)m_visiondata[m_visionidx][0]);
    }
}
void Formsystem::inputVisionPort(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->lineEditVisionPort->minimum(), ui->lineEditVisionPort->maximum()) == QDialog::Accepted)
    {
        m_visiondata[m_visionidx][1] = (quint16)value;
        ui->lineEditVisionPort->setValue((quint16)m_visiondata[m_visionidx][1]);
    }
}
// 选择第一个参数信号槽
void Formsystem::selectVariable(void)
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_EOUT, ret) != QDialog::Accepted)
        return;
    m_visiondata[m_visionidx][3] = ret;
    ui->lineEditVisionOutput->setText(xStringResource::GetVarName((quint16)m_visiondata[m_visionidx][3]));
    qDebug() << "Variable: " << (quint16)m_visiondata[m_visionidx][3];
}

void Formsystem::BtnVisionPrevClick(void)
{
    m_visionidx--;
    if (m_visionidx < 0)
        m_visionidx = 7;
    ui->labelVisionInfo->setText(tr("当前视觉编号：") + QString::number(m_visionidx+1) + tr(" ，总可设置视觉数：8"));
    ui->spinBoxVisionIdx->setValue(m_visionidx+1);
    ui->sBoxVisionIP1->setValue((m_visiondata[m_visionidx][0] >> 24)&0xFF);
    ui->sBoxVisionIP2->setValue((m_visiondata[m_visionidx][0] >> 16)&0xFF);
    ui->sBoxVisionIP3->setValue((m_visiondata[m_visionidx][0] >> 8)&0xFF);
    ui->sBoxVisionIP4->setValue((m_visiondata[m_visionidx][0] >> 0)&0xFF);
    ui->lineEditVisionPort->setValue((quint16)m_visiondata[m_visionidx][1]);
    ui->cBoxVision->setCurrentIndex(((m_visiondata[m_visionidx][2]>>8)&1) ? VISION_TYPE_COGNEX : VISION_TYPE_NULL);
    ui->cBoxVisionInstall->setCurrentIndex(((m_visiondata[m_visionidx][2]>>1)&1) ? VISION_INSTALL_FOLLOW : VISION_INSTALL_FIXED);
    ui->cBoxVisionProtocol->setCurrentIndex((m_visiondata[m_visionidx][2]&1) ? VISION_TRIGGER_PORT : VISION_TRIGGER_PROTOCAL);
    ui->lineEditVisionOutput->setText(xStringResource::GetVarName(m_visiondata[m_visionidx][3]));
}
void Formsystem::BtnVisionNextClick(void)
{
    m_visionidx++;
    if (m_visionidx > 7)
        m_visionidx = 0;
    ui->labelVisionInfo->setText(tr("当前视觉编号：") + QString::number(m_visionidx+1) + tr(" ，总可设置视觉数：8"));
    ui->spinBoxVisionIdx->setValue(m_visionidx+1);
    ui->sBoxVisionIP1->setValue((m_visiondata[m_visionidx][0] >> 24)&0xFF);
    ui->sBoxVisionIP2->setValue((m_visiondata[m_visionidx][0] >> 16)&0xFF);
    ui->sBoxVisionIP3->setValue((m_visiondata[m_visionidx][0] >> 8)&0xFF);
    ui->sBoxVisionIP4->setValue((m_visiondata[m_visionidx][0] >> 0)&0xFF);
    ui->lineEditVisionPort->setValue(m_visiondata[m_visionidx][1]);
    ui->cBoxVision->setCurrentIndex(((m_visiondata[m_visionidx][2]>>8)&1) ? VISION_TYPE_COGNEX : VISION_TYPE_NULL);
    ui->cBoxVisionInstall->setCurrentIndex(((m_visiondata[m_visionidx][2]>>1)&1) ? VISION_INSTALL_FOLLOW : VISION_INSTALL_FIXED);
    ui->cBoxVisionProtocol->setCurrentIndex((m_visiondata[m_visionidx][2]&1) ? VISION_TRIGGER_PORT : VISION_TRIGGER_PROTOCAL);
    ui->lineEditVisionOutput->setText(xStringResource::GetVarName(m_visiondata[m_visionidx][3]));
}

void Formsystem::VisionDataUpdate()
{
    if ((m_visionidx < 0) || (m_visionidx > 7))
        return;
    pModbus->ReadVisionTestData(m_visionidx);
    quint32 tmp, data14, data24, data34;
    float data11, data12, data13, data21, data22, data23, data31, data32, data33;

    tmp = pModbus->ReadReg16_MB2(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1));
    tmp <<= 16;
    tmp |= pModbus->ReadReg16(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1));
    data11 = *((float*)&tmp);

    tmp = pModbus->ReadReg16_MB2(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+1);
    tmp <<= 16;
    tmp |= pModbus->ReadReg16(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+1);
    data12 = *((float*)&tmp);

    tmp = pModbus->ReadReg16_MB2(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+2);
    tmp <<= 16;
    tmp |= pModbus->ReadReg16(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+2);
    data13 = *((float*)&tmp);
    data14 = pModbus->ReadReg32(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+3);
    // /////////////////////////////////////////////////////////////////////////////////////
    tmp = pModbus->ReadReg16_MB2(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+4);
    tmp <<= 16;
    tmp |= pModbus->ReadReg16(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+4);
    data21 = *((float*)&tmp);

    tmp = pModbus->ReadReg16_MB2(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+1+4);
    tmp <<= 16;
    tmp |= pModbus->ReadReg16(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+1+4);
    data22 = *((float*)&tmp);

    tmp = pModbus->ReadReg16_MB2(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+2+4);
    tmp <<= 16;
    tmp |= pModbus->ReadReg16(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+2+4);
    data23 = *((float*)&tmp);
    data24 = pModbus->ReadReg32(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+3+4);
    // //////////////////////////////////////////////////////////////////////////////////////
    tmp = pModbus->ReadReg16_MB2(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+8);
    tmp <<= 16;
    tmp |= pModbus->ReadReg16(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+8);
    data31 = *((float*)&tmp);

    tmp = pModbus->ReadReg16_MB2(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+1+8);
    tmp <<= 16;
    tmp |= pModbus->ReadReg16(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+1+8);
    data32 = *((float*)&tmp);

    tmp = pModbus->ReadReg16_MB2(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+2+8);
    tmp <<= 16;
    tmp |= pModbus->ReadReg16(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+2+8);
    data33 = *((float*)&tmp);
    data34 = pModbus->ReadReg32(VISION1_MATCH1_DATA1+m_visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1)+3+8);

    ui->labelVisionData11->setText(QString::number(data11));
    ui->labelVisionData12->setText(QString::number(data12));
    ui->labelVisionData13->setText(QString::number(data13));
    ui->labelVisionData14->setText(QString::number(data14));
    ui->labelVisionData21->setText(QString::number(data21));
    ui->labelVisionData22->setText(QString::number(data22));
    ui->labelVisionData23->setText(QString::number(data23));
    ui->labelVisionData24->setText(QString::number(data24));
    ui->labelVisionData31->setText(QString::number(data31));
    ui->labelVisionData32->setText(QString::number(data32));
    ui->labelVisionData33->setText(QString::number(data33));
    ui->labelVisionData34->setText(QString::number(data34));

//    m_visionidx = -1;
}

void Formsystem::BtnVisonTestClick(void)
{
    if ((m_visionidx > 8) || (m_visionidx < 0))
        return;
    m_time->start(200);
    pModbus->CommandVisionTest(m_visionidx);
}
void Formsystem::VisionProtocolChanged(int idx)
{
    if (idx == VISION_TRIGGER_PROTOCAL)
        ui->lineEditVisionOutput->setEnabled(false);
    else
        ui->lineEditVisionOutput->setEnabled(true);
    m_visiondata[m_visionidx][2] &= 0xFFFE;
    m_visiondata[m_visionidx][2] |= ui->cBoxVisionProtocol->currentIndex();
}
void Formsystem::VisionInstallChanged(int idx)
{
    m_visiondata[m_visionidx][2] &= 0xFFFD;
    m_visiondata[m_visionidx][2] |= ((quint16)ui->cBoxVisionInstall->currentIndex() << 1);
}
void Formsystem::VisionTypeChanged(int idx)
{
    m_visiondata[m_visionidx][2] &= 0x00FF;
    m_visiondata[m_visionidx][2] |= ((quint16)ui->cBoxVision->currentIndex() << 8);
}
bool Formsystem::checkRegCodeValid(QString strregcode, QString strprocode)
{
    // 激活码判断有效流程
    // 1、16位激活码经过base32解码得到10位激活码
    // 2、激活码与产品密钥异或
    // 3、激活码与机器码异或
    // 4、激活码经过CRC16得到crc，判断crc与激活码后2位
    uint8_t tmp[10], pro[10], mac[16], demac[10];
    uint16_t crc;
    char* transRegCode;

    mac[0] = RegCode.m_system_uid1; mac[1] = RegCode.m_system_uid1>>8;
    mac[2] = RegCode.m_system_uid2; mac[3] = RegCode.m_system_uid2>>8;
    mac[4] = RegCode.m_system_uid3; mac[5] = RegCode.m_system_uid3>>8;
    mac[6] = RegCode.m_system_uid4; mac[7] = RegCode.m_system_uid4>>8;
    mac[8] = RegCode.m_system_uid5; mac[9] = RegCode.m_system_uid5>>8;
    mac[10] = RegCode.m_system_uid6; mac[11] = RegCode.m_system_uid6>>8;
    mac[12] = RegCode.m_system_uid7; mac[13] = RegCode.m_system_uid7>>8;
    mac[14] = RegCode.m_system_uid8; mac[15] = RegCode.m_system_uid8>>8;
    if (strprocode == "")
    {
        pro[0] = ProCode.m_product_id1; pro[1] = ProCode.m_product_id1>>8;
        pro[2] = ProCode.m_product_id2; pro[3] = ProCode.m_product_id2>>8;
        pro[4] = ProCode.m_product_id3; pro[5] = ProCode.m_product_id3>>8;
        pro[6] = ProCode.m_product_id4; pro[7] = ProCode.m_product_id4>>8;
        pro[8] = ProCode.m_product_id5; pro[9] = ProCode.m_product_id5>>8;
    }
    else
    {
        pro[0] = strprocode.at(0).toAscii(); pro[1] = strprocode.at(1).toAscii();
        pro[2] = strprocode.at(2).toAscii(); pro[3] = strprocode.at(3).toAscii();
        pro[4] = strprocode.at(4).toAscii(); pro[5] = strprocode.at(5).toAscii();
        pro[6] = strprocode.at(6).toAscii(); pro[7] = strprocode.at(7).toAscii();
        pro[8] = strprocode.at(8).toAscii(); pro[9] = strprocode.at(9).toAscii();
    }
    QByteArray tmptransRegCode = strregcode.toLatin1();
    transRegCode = tmptransRegCode.data();
    base32_decode(transRegCode, 16, (char*)tmp, 10);
    base32_decode((char*)mac, 16, (char*)demac, 10);
    for (int i=0; i<10; i++)
        tmp[i] ^= pro[i];

    for (int i=0; i<10; i++)
        tmp[i] ^= ((uint8_t*)demac)[i];

    crc = CCRC16::GetCRC16(tmp, 8);
    if (crc != *(uint16_t*)(&tmp[8]))
        return false;
    return true;
}
