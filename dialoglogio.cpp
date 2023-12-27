#include "xconfig.h"
#include "xioport.h"
#include "cmbprotocol.h"
#include "xstringresource.h"
#include "dialoglogio.h"
#include "ui_dialoglogio.h"
#include "servoalias.h"

DialogLogIo::DialogLogIo(QWidget *parent) : QDialog(parent),	ui(new Ui::DialogLogIo)
{
	ui->setupUi(this);
#if defined(Q_WS_QWS)
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
	setPortNames();
	ui->tabWidget->setCurrentIndex(0);
    // 设置控件状态
    ui->IoImop->setVisible(false);
    ui->IoEbp->setVisible(false);
    ui->IoEfp->setVisible(false);
    ui->IoC1p1->setVisible(false);
    ui->IoC1p2->setVisible(false);
    ui->IoC2p1->setVisible(false);
    ui->IoC2p2->setVisible(false);
    ui->IoEeb->setVisible(false);
    ui->IoEc1p1->setVisible(false);
    ui->IoEc1p2->setVisible(false);
    ui->IoEc2p1->setVisible(false);
    ui->IoEc2p2->setVisible(false);
}

DialogLogIo::~DialogLogIo()
{
	delete ui;
}

void DialogLogIo::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		setPortNames();
		break;
	default:
		break;
	}
}

// 显示对话框
int DialogLogIo::DoForm(const QDateTime &time, const quint16 (&input)[LOG_INPUT_SIZE], const quint16 (&output)[LOG_OUTPUT_SIZE])
{
	ui->labelTime->setText(tr("端口状态记录时间：") + time.toString("yyyy-MM-dd hh:mm:ss"));
	setPortStatus(input, output);
    if (CMBProtocol::GetRotateUse())
    {
        ui->IoEm1X01->setVisible(false);
        ui->IoEm1X02->setVisible(false);
        ui->IoEm1Y01->setVisible(false);
        ui->IoEm1Y02->setVisible(false);
        ui->IoPaHorIn->setVisible(true);
        ui->IoPaVerIn->setVisible(true);
        ui->IoPaHorOut->setVisible(true);
        ui->IoPaVerOut->setVisible(true);
    }
    else
    {
        ui->IoEm1X01->setVisible(true);
        ui->IoEm1X02->setVisible(true);
        ui->IoEm1Y01->setVisible(true);
        ui->IoEm1Y02->setVisible(true);
        ui->IoPaHorIn->setVisible(false);
        ui->IoPaVerIn->setVisible(false);
        ui->IoPaHorOut->setVisible(false);
        ui->IoPaVerOut->setVisible(false);
    }
#if ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_YIDAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE))
    ui->IoSdm->setText(tr("铸机安全设备"));
    ui->IoEsm->setText(tr("铸机紧急停止"));
    ui->IoAuto->setText(tr("铸机全自动"));
    ui->tabWidget->setTabText(1, tr("压铸机"));
#elif (FACTORY == FA_SINROBOT_JC)
    ui->IoSdm->setText(tr("机床安全设备"));
    ui->IoEsm->setText(tr("机床紧急停止"));
    ui->IoAuto->setText(tr("机床全自动"));
    ui->tabWidget->setTabText(1, tr("机床"));
#else
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        ui->IoSdm->setText(tr("铸机安全设备"));
        ui->IoEsm->setText(tr("铸机紧急停止"));
        ui->IoAuto->setText(tr("铸机全自动"));
        ui->tabWidget->setTabText(1, tr("压铸机"));
    }
    else
    {
        ui->IoSdm->setText(tr("塑机安全设备"));
        ui->IoEsm->setText(tr("塑机紧急停止"));
        ui->IoAuto->setText(tr("注塑机全自动"));
        ui->tabWidget->setTabText(1, tr("注塑机"));
    }
#endif
    return exec();
}

// 设置端口名称
void DialogLogIo::setPortNames(void)
{

    ui->groupBoxPaHor->setTitle(GetServoName(AXIS_IDX_PHOR));//正臂引拔轴
    ui->groupBoxPaVer->setTitle(GetServoName(AXIS_IDX_PVER));//正臂上下轴
    ui->groupBoxRaHor->setTitle(GetServoName(AXIS_IDX_RHOR));//副臂引拔轴
    ui->groupBoxRaVer->setTitle(GetServoName(AXIS_IDX_RVER));//副臂上下轴
    ui->groupBoxTrv->setTitle(GetServoName(AXIS_IDX_TRV));//横行轴
    ui->groupBox_2->setTitle(GetServoName(AXIS_IDX_EXT));//扩展轴
	// 伺服输入
    if (CMBProtocol::GetHomeInmold())
        ui->IoInSafe->setText(xStringResource::GetVarName(SV_VAR_IN_OUTMOLD));
    else
	ui->IoInSafe->setText(xStringResource::GetVarName(SV_VAR_IN_INMOLD));

	ui->IoPaUpSafe->setText(xStringResource::GetVarName(SV_VAR_IN_YWPOS));
	ui->IoRaUpSafe->setText(xStringResource::GetVarName(SV_VAR_IN_AWPOS));
	// 注塑机输入
	ui->IoEsm->setText(xStringResource::GetVarName(IMM_VAR_IN_STOP));
	ui->IoSdm->setText(xStringResource::GetVarName(IMM_VAR_IN_SAFE));
	ui->IoRej->setText(xStringResource::GetVarName(IMM_VAR_IN_REJECT));
	ui->IoMcp->setText(xStringResource::GetVarName(IMM_VAR_IN_MCP));
	ui->IoMop->setText(xStringResource::GetVarName(IMM_VAR_IN_MOP));
	ui->IoImop->setText(xStringResource::GetVarName(IMM_VAR_IN_IMOP));
	ui->IoAuto->setText(xStringResource::GetVarName(IMM_VAR_IN_AUTO));
	ui->IoEbp->setText(xStringResource::GetVarName(IMM_VAR_IN_EBP));
	ui->IoEfp->setText(xStringResource::GetVarName(IMM_VAR_IN_EFP));
	ui->IoC1p1->setText(xStringResource::GetVarName(IMM_VAR_IN_C1P1));
	ui->IoC1p2->setText(xStringResource::GetVarName(IMM_VAR_IN_C1P2));
	ui->IoC2p1->setText(xStringResource::GetVarName(IMM_VAR_IN_C2P1));
	ui->IoC2p2->setText(xStringResource::GetVarName(IMM_VAR_IN_C2P2));
	ui->IoMmop->setText(xStringResource::GetVarName(IMM_VAR_IN_MID));
	// 注塑机输出
	ui->IoHmaf->setText(xStringResource::GetVarName(IMM_VAR_OUT_HMAF));
	ui->IoMaf->setText(xStringResource::GetVarName(IMM_VAR_OUT_MAF));
	ui->IoHemc->setText(xStringResource::GetVarName(IMM_VAR_OUT_HEMC));
	ui->IoEmo->setText(xStringResource::GetVarName(IMM_VAR_OUT_EMO));
	ui->IoEmc->setText(xStringResource::GetVarName(IMM_VAR_OUT_EMC));
	ui->IoEef->setText(xStringResource::GetVarName(IMM_VAR_OUT_EEF));
	ui->IoEeb->setText(xStringResource::GetVarName(IMM_VAR_OUT_EEB));
	ui->IoEc1p1->setText(xStringResource::GetVarName(IMM_VAR_OUT_C1P1));
	ui->IoEc1p2->setText(xStringResource::GetVarName(IMM_VAR_OUT_C1P2));
	ui->IoEc2p1->setText(xStringResource::GetVarName(IMM_VAR_OUT_C2P1));
	ui->IoEc2p2->setText(xStringResource::GetVarName(IMM_VAR_OUT_C2P2));
	// 手臂输入
	ui->IoPaHorIn->setText(xStringResource::GetVarName(RBT_VAR_IN_PRO_HOR));
	ui->IoPaVerIn->setText(xStringResource::GetVarName(RBT_VAR_IN_PRO_VER));
	// 手臂输出
	ui->IoPaHorOut->setText(xStringResource::GetVarName(RBT_VAR_OUT_PRO_HOR));
	ui->IoPaVerOut->setText(xStringResource::GetVarName(RBT_VAR_OUT_PRO_VER));
	// 其他输入
	ui->IoPressure->setText(xStringResource::GetVarName(RBT_VAR_IN_LOW_AIR));
	ui->IoDwnSafe->setText(xStringResource::GetVarName(RBT_VAR_IN_DWN_SAF));
}

// 设置端口状态
void DialogLogIo::setPortStatus(const quint16 (&input)[LOG_INPUT_SIZE], const quint16 (&output)[LOG_OUTPUT_SIZE])
{
/*
	// 提取端口数据
	quint64 inMain;
	quint32 outMain;
	quint16 inEm1, inEm2, inEm3, inEm4, outEm1, outEm2, outEm3, outEm4;
	inMain = input[3];	inMain <<= 16;
	inMain |= input[2];	inMain <<= 16;
	inMain |= input[1];	inMain <<= 16;
	inMain |= input[0];
	inEm1 = input[4];
	inEm2 = input[5];
	inEm3 = input[6];
	inEm4 = input[7];
	outMain = output[1];	outMain <<= 16;
	outMain |= output[0];
	outEm1 = output[2];
	outEm2 = output[3];
	outEm3 = output[4];
	outEm4 = output[5];
*/
    quint16 tmpInput[8], tmpOutput[6];
    memcpy(tmpInput, input, sizeof(input));
    memcpy(tmpOutput, output, sizeof(output));
	// 设置端口显示状态
	// 伺服输入
    ui->IoPaHorOrg->setOn(xIoPort::GetIn(SV_VAR_IN_XHOME, tmpInput));		// 正臂引拔轴原点
    ui->IoPaVerOrg->setOn(xIoPort::GetIn(SV_VAR_IN_YHOME, tmpInput));		// 正臂上下轴原点
    ui->IoTrvOrg->setOn(xIoPort::GetIn(SV_VAR_IN_ZHOME, tmpInput));		// 横行轴原点
    ui->IoRaVerOrg->setOn(xIoPort::GetIn(SV_VAR_IN_AHOME, tmpInput));		// 副臂上下轴原点
    ui->IoRaHorOrg->setOn(xIoPort::GetIn(SV_VAR_IN_BHOME, tmpInput));		// 副臂引拔轴原点
    ui->IoExtOrg->setOn(xIoPort::GetIn(SV_VAR_IN_CHOME, tmpInput));		// 扩展轴原点
    ui->IoPaHorCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_XCCWL, tmpInput));     // 正臂引拔轴负极限
    ui->IoPaVerCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_YCCWL, tmpInput));     // 正臂上下轴负极限
    ui->IoTrvCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_ZCCWL, tmpInput));		// 横行轴负极限
    ui->IoRaVerCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_ACCWL, tmpInput));     // 副臂上下轴负极限
    ui->IoRaHorCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_BCCWL, tmpInput));     // 副臂引拔轴负极限
    ui->IoExtCcwL->setOn(xIoPort::GetIn(SV_VAR_IN_CCCWL, tmpInput));		// 扩展轴负极限
    ui->IoPaHorCwL->setOn(xIoPort::GetIn(SV_VAR_IN_XCWL, tmpInput));		// 正臂引拔轴正极限
    ui->IoPaVerCwL->setOn(xIoPort::GetIn(SV_VAR_IN_YCWL, tmpInput));		// 正臂上下轴正极限
    ui->IoTrvCwL->setOn(xIoPort::GetIn(SV_VAR_IN_ZCWL, tmpInput));         // 横行轴正极限
    ui->IoRaVerCwL->setOn(xIoPort::GetIn(SV_VAR_IN_ACWL, tmpInput));		// 副臂上下轴正极限
    ui->IoRaHorCwL->setOn(xIoPort::GetIn(SV_VAR_IN_BCWL, tmpInput));		// 副臂引拔轴正极限
    ui->IoExtCwL->setOn(xIoPort::GetIn(SV_VAR_IN_CCWL, tmpInput));         // 扩展轴正极限
    ui->IoPaHorAlm->setOn(xIoPort::GetIn(SV_VAR_IN_XALM, tmpInput));		// 正臂引拔轴报警
    ui->IoPaVerAlm->setOn(xIoPort::GetIn(SV_VAR_IN_YALM, tmpInput));		// 正臂上下轴报警
    ui->IoTrvAlm->setOn(xIoPort::GetIn(SV_VAR_IN_ZALM, tmpInput));         // 横行轴报警
    ui->IoRaVerAlm->setOn(xIoPort::GetIn(SV_VAR_IN_AALM, tmpInput));		// 副臂上下轴报警
    ui->IoRaHorAlm->setOn(xIoPort::GetIn(SV_VAR_IN_BALM, tmpInput));		// 副臂引拔轴报警
    ui->IoExtAlm->setOn(xIoPort::GetIn(SV_VAR_IN_CALM, tmpInput));         // 扩展轴报警
    ui->IoInSafe->setOn(xIoPort::GetIn(SV_VAR_IN_INMOLD, tmpInput));		// 横行轴模内安全区
    ui->IoPaUpSafe->setOn(xIoPort::GetIn(SV_VAR_IN_YWPOS, tmpInput));		// 正臂上位安全区
    ui->IoRaUpSafe->setOn(xIoPort::GetIn(SV_VAR_IN_AWPOS, tmpInput));		// 副臂上位安全区
	// 伺服输出
    ui->IoPaHorOn->setOn(xIoPort::GetOut(SV_VAR_OUT_XSON, tmpOutput));     // 正臂引拔轴使能
    ui->IoPaVerOn->setOn(xIoPort::GetOut(SV_VAR_OUT_YSON, tmpOutput));     // 正臂上下轴使能
    ui->IoTrvOn->setOn(xIoPort::GetOut(SV_VAR_OUT_ZSON, tmpOutput));		// 横行轴使能
    ui->IoRaVerOn->setOn(xIoPort::GetOut(SV_VAR_OUT_ASON, tmpOutput));     // 副臂上下轴使能
    ui->IoRaHorOn->setOn(xIoPort::GetOut(SV_VAR_OUT_BSON, tmpOutput));     // 副臂引拔轴使能
    ui->IoExtOn->setOn(xIoPort::GetOut(SV_VAR_OUT_CSON, tmpOutput));		// 扩展轴使能
	// 注塑机输入
    ui->IoEsm->setOn(xIoPort::GetIn(IMM_VAR_IN_STOP, tmpInput));			// 注塑机紧急停止
    ui->IoSdm->setOn(xIoPort::GetIn(IMM_VAR_IN_SAFE, tmpInput));			// 注塑机安全设备
    ui->IoRej->setOn(xIoPort::GetIn(IMM_VAR_IN_REJECT, tmpInput));         // 注塑机成型不良
    ui->IoMcp->setOn(xIoPort::GetIn(IMM_VAR_IN_MCP, tmpInput));			// 注塑机关模完成
    ui->IoMop->setOn(xIoPort::GetIn(IMM_VAR_IN_MOP, tmpInput));			// 注塑机开模完成
    ui->IoImop->setOn(xIoPort::GetIn(IMM_VAR_IN_IMOP, tmpInput));          // 注塑机开模中间
    ui->IoAuto->setOn(xIoPort::GetIn(IMM_VAR_IN_AUTO, tmpInput));			// 注塑机全自动
    ui->IoEbp->setOn(xIoPort::GetIn(IMM_VAR_IN_EBP, tmpInput));			// 注塑机顶针后退到位
    ui->IoEfp->setOn(xIoPort::GetIn(IMM_VAR_IN_EFP, tmpInput));			// 注塑机顶针前进到位
    ui->IoC1p1->setOn(xIoPort::GetIn(IMM_VAR_IN_C1P1, tmpInput));          // 注塑机抽芯1位置1
    ui->IoC1p2->setOn(xIoPort::GetIn(IMM_VAR_IN_C1P2, tmpInput));          // 注塑机抽芯1位置2
    ui->IoC2p1->setOn(xIoPort::GetIn(IMM_VAR_IN_C2P1, tmpInput));          // 注塑机抽芯2位置1
    ui->IoC2p2->setOn(xIoPort::GetIn(IMM_VAR_IN_C2P2, tmpInput));          // 注塑机抽芯2位置2
    ui->IoMmop->setOn(xIoPort::GetIn(IMM_VAR_IN_MID, tmpInput));			// 注塑机开中板模确认
	// 注塑机输出
    ui->IoMaf->setOn(xIoPort::GetOut(IMM_VAR_OUT_MAF, tmpOutput));         // 注塑机模区安全
    ui->IoHmaf->setOn(xIoPort::GetOut(IMM_VAR_OUT_HMAF, tmpOutput));       // 注塑机模区安全确认
    ui->IoEmc->setOn(xIoPort::GetOut(IMM_VAR_OUT_EMC, tmpOutput));         // 注塑机允许关模
    ui->IoHemc->setOn(xIoPort::GetOut(IMM_VAR_OUT_HEMC, tmpOutput));       // 注塑机允许关模确认
    ui->IoEmo->setOn(xIoPort::GetOut(IMM_VAR_OUT_EMO, tmpOutput));         // 注塑机允许开模
    ui->IoEeb->setOn(xIoPort::GetOut(IMM_VAR_OUT_EEB, tmpOutput));         // 注塑机允许顶针后退
    ui->IoEef->setOn(xIoPort::GetOut(IMM_VAR_OUT_EEF, tmpOutput));         // 注塑机允许顶针前进
    ui->IoEc1p1->setOn(xIoPort::GetOut(IMM_VAR_OUT_C1P1, tmpOutput));      // 注塑机允许抽芯1位置1
    ui->IoEc1p2->setOn(xIoPort::GetOut(IMM_VAR_OUT_C1P2, tmpOutput));		// 注塑机允许抽芯1位置2
    ui->IoEc2p1->setOn(xIoPort::GetOut(IMM_VAR_OUT_C2P1, tmpOutput));		// 注塑机允许抽芯2位置1
    ui->IoEc2p2->setOn(xIoPort::GetOut(IMM_VAR_OUT_C2P2, tmpOutput));		// 注塑机允许抽芯2位置2
	// 其他输入
    ui->IoPressure->setEnabled(xIoPort::GetIn(RBT_VAR_IN_LOW_AIR, tmpInput));	  // 气源低气压检测
    ui->IoDwnSafe->setEnabled(xIoPort::GetIn(RBT_VAR_IN_DWN_SAF, tmpInput));	  // 手臂模外下行安全检测信号
    // 主控模块1输入
    ui->IoMainX00->setOn(xIoPort::GetIn(MAIN_VAR_X00, tmpInput));
    ui->IoMainX01->setOn(xIoPort::GetIn(MAIN_VAR_X01, tmpInput));
    ui->IoMainX02->setOn(xIoPort::GetIn(MAIN_VAR_X02, tmpInput));
    ui->IoMainX03->setOn(xIoPort::GetIn(MAIN_VAR_X03, tmpInput));
    ui->IoMainX04->setOn(xIoPort::GetIn(MAIN_VAR_X04, tmpInput));
    ui->IoMainX05->setOn(xIoPort::GetIn(MAIN_VAR_X05, tmpInput));
    ui->IoMainX06->setOn(xIoPort::GetIn(MAIN_VAR_X06, tmpInput));
    ui->IoMainX07->setOn(xIoPort::GetIn(MAIN_VAR_X07, tmpInput));
    ui->IoMainX08->setOn(xIoPort::GetIn(MAIN_VAR_X08, tmpInput));
    ui->IoMainX09->setOn(xIoPort::GetIn(MAIN_VAR_X09, tmpInput));
    ui->IoMainX10->setOn(xIoPort::GetIn(MAIN_VAR_X10, tmpInput));
    ui->IoMainX11->setOn(xIoPort::GetIn(MAIN_VAR_X11, tmpInput));
    ui->IoMainX12->setOn(xIoPort::GetIn(MAIN_VAR_X12, tmpInput));
    ui->IoMainX13->setOn(xIoPort::GetIn(MAIN_VAR_X13, tmpInput));
    ui->IoMainX14->setOn(xIoPort::GetIn(MAIN_VAR_X14, tmpInput));
    ui->IoMainX15->setOn(xIoPort::GetIn(MAIN_VAR_X15, tmpInput));
    // 主控模块1输出
    ui->IoMainY00->setOn(xIoPort::GetOut(MAIN_VAR_Y00, tmpOutput));
    ui->IoMainY01->setOn(xIoPort::GetOut(MAIN_VAR_Y01, tmpOutput));
    ui->IoMainY02->setOn(xIoPort::GetOut(MAIN_VAR_Y02, tmpOutput));
    ui->IoMainY03->setOn(xIoPort::GetOut(MAIN_VAR_Y03, tmpOutput));
    ui->IoMainY04->setOn(xIoPort::GetOut(MAIN_VAR_Y04, tmpOutput));
    ui->IoMainY05->setOn(xIoPort::GetOut(MAIN_VAR_Y05, tmpOutput));
    ui->IoMainY06->setOn(xIoPort::GetOut(MAIN_VAR_Y06, tmpOutput));
    ui->IoMainY07->setOn(xIoPort::GetOut(MAIN_VAR_Y07, tmpOutput));
    ui->IoMainY08->setOn(xIoPort::GetOut(MAIN_VAR_Y08, tmpOutput));
    ui->IoMainY09->setOn(xIoPort::GetOut(MAIN_VAR_Y09, tmpOutput));
    ui->IoMainY10->setOn(xIoPort::GetOut(MAIN_VAR_Y10, tmpOutput));
    ui->IoMainY11->setOn(xIoPort::GetOut(MAIN_VAR_Y11, tmpOutput));
    ui->IoMainY12->setOn(xIoPort::GetOut(MAIN_VAR_Y12, tmpOutput));
    ui->IoMainY13->setOn(xIoPort::GetOut(MAIN_VAR_Y13, tmpOutput));
    ui->IoMainY14->setOn(xIoPort::GetOut(MAIN_VAR_Y14, tmpOutput));
    ui->IoMainY15->setOn(xIoPort::GetOut(MAIN_VAR_Y15, tmpOutput));
	// 扩展模块1输入
    ui->IoPaHorIn->setOn(xIoPort::GetIn(RBT_VAR_IN_PRO_HOR, tmpInput));
    ui->IoPaVerIn->setOn(xIoPort::GetIn(RBT_VAR_IN_PRO_VER, tmpInput));
    ui->IoEm1X01->setOn(xIoPort::GetIn(EM1_VAR_X00, tmpInput));
    ui->IoEm1X02->setOn(xIoPort::GetIn(EM1_VAR_X01, tmpInput));
    ui->IoEm1X03->setOn(xIoPort::GetIn(EM1_VAR_X02, tmpInput));
    ui->IoEm1X04->setOn(xIoPort::GetIn(EM1_VAR_X03, tmpInput));
    ui->IoEm1X05->setOn(xIoPort::GetIn(EM1_VAR_X04, tmpInput));
    ui->IoEm1X06->setOn(xIoPort::GetIn(EM1_VAR_X05, tmpInput));
    ui->IoEm1X07->setOn(xIoPort::GetIn(EM1_VAR_X06, tmpInput));
    ui->IoEm1X08->setOn(xIoPort::GetIn(EM1_VAR_X07, tmpInput));
    ui->IoEm1X09->setOn(xIoPort::GetIn(EM1_VAR_X08, tmpInput));
    ui->IoEm1X10->setOn(xIoPort::GetIn(EM1_VAR_X09, tmpInput));
    ui->IoEm1X11->setOn(xIoPort::GetIn(EM1_VAR_X10, tmpInput));
    ui->IoEm1X12->setOn(xIoPort::GetIn(EM1_VAR_X11, tmpInput));
    ui->IoEm1X13->setOn(xIoPort::GetIn(EM1_VAR_X12, tmpInput));
    ui->IoEm1X14->setOn(xIoPort::GetIn(EM1_VAR_X13, tmpInput));
    ui->IoEm1X15->setOn(xIoPort::GetIn(EM1_VAR_X14, tmpInput));
    ui->IoEm1X16->setOn(xIoPort::GetIn(EM1_VAR_X15, tmpInput));
    // 扩展模块1输出
    ui->IoPaVerOut->setOn(xIoPort::GetOut(RBT_VAR_OUT_PRO_VER, tmpOutput));
    ui->IoPaHorOut->setOn(xIoPort::GetOut(RBT_VAR_OUT_PRO_HOR, tmpOutput));
    ui->IoEm1Y01->setOn(xIoPort::GetOut(EM1_VAR_Y00, tmpOutput));
    ui->IoEm1Y02->setOn(xIoPort::GetOut(EM1_VAR_Y01, tmpOutput));
    ui->IoEm1Y03->setOn(xIoPort::GetOut(EM1_VAR_Y02, tmpOutput));
    ui->IoEm1Y04->setOn(xIoPort::GetOut(EM1_VAR_Y03, tmpOutput));
    ui->IoEm1Y05->setOn(xIoPort::GetOut(EM1_VAR_Y04, tmpOutput));
    ui->IoEm1Y06->setOn(xIoPort::GetOut(EM1_VAR_Y05, tmpOutput));
    ui->IoEm1Y07->setOn(xIoPort::GetOut(EM1_VAR_Y06, tmpOutput));
    ui->IoEm1Y08->setOn(xIoPort::GetOut(EM1_VAR_Y07, tmpOutput));
    ui->IoEm1Y09->setOn(xIoPort::GetOut(EM1_VAR_Y08, tmpOutput));
    ui->IoEm1Y10->setOn(xIoPort::GetOut(EM1_VAR_Y09, tmpOutput));
    ui->IoEm1Y11->setOn(xIoPort::GetOut(EM1_VAR_Y10, tmpOutput));
    ui->IoEm1Y12->setOn(xIoPort::GetOut(EM1_VAR_Y11, tmpOutput));
    ui->IoEm1Y13->setOn(xIoPort::GetOut(EM1_VAR_Y12, tmpOutput));
    ui->IoEm1Y14->setOn(xIoPort::GetOut(EM1_VAR_Y13, tmpOutput));
    ui->IoEm1Y15->setOn(xIoPort::GetOut(EM1_VAR_Y14, tmpOutput));
    ui->IoEm1Y16->setOn(xIoPort::GetOut(EM1_VAR_Y15, tmpOutput));
	// 扩展模块2输入
    ui->IoEm2X01->setOn(xIoPort::GetIn(EM2_VAR_X00, tmpInput));
    ui->IoEm2X02->setOn(xIoPort::GetIn(EM2_VAR_X01, tmpInput));
    ui->IoEm2X03->setOn(xIoPort::GetIn(EM2_VAR_X02, tmpInput));
    ui->IoEm2X04->setOn(xIoPort::GetIn(EM2_VAR_X03, tmpInput));
    ui->IoEm2X05->setOn(xIoPort::GetIn(EM2_VAR_X04, tmpInput));
    ui->IoEm2X06->setOn(xIoPort::GetIn(EM2_VAR_X05, tmpInput));
    ui->IoEm2X07->setOn(xIoPort::GetIn(EM2_VAR_X06, tmpInput));
    ui->IoEm2X08->setOn(xIoPort::GetIn(EM2_VAR_X07, tmpInput));
    ui->IoEm2X09->setOn(xIoPort::GetIn(EM2_VAR_X08, tmpInput));
    ui->IoEm2X10->setOn(xIoPort::GetIn(EM2_VAR_X09, tmpInput));
    ui->IoEm2X11->setOn(xIoPort::GetIn(EM2_VAR_X10, tmpInput));
    ui->IoEm2X12->setOn(xIoPort::GetIn(EM2_VAR_X11, tmpInput));
    ui->IoEm2X13->setOn(xIoPort::GetIn(EM2_VAR_X12, tmpInput));
    ui->IoEm2X14->setOn(xIoPort::GetIn(EM2_VAR_X13, tmpInput));
    ui->IoEm2X15->setOn(xIoPort::GetIn(EM2_VAR_X14, tmpInput));
    ui->IoEm2X16->setOn(xIoPort::GetIn(EM2_VAR_X15, tmpInput));
    // 扩展模块2输出
    ui->IoEm2Y01->setOn(xIoPort::GetOut(EM2_VAR_Y00, tmpOutput));
    ui->IoEm2Y02->setOn(xIoPort::GetOut(EM2_VAR_Y01, tmpOutput));
    ui->IoEm2Y03->setOn(xIoPort::GetOut(EM2_VAR_Y02, tmpOutput));
    ui->IoEm2Y04->setOn(xIoPort::GetOut(EM2_VAR_Y03, tmpOutput));
    ui->IoEm2Y05->setOn(xIoPort::GetOut(EM2_VAR_Y04, tmpOutput));
    ui->IoEm2Y06->setOn(xIoPort::GetOut(EM2_VAR_Y05, tmpOutput));
    ui->IoEm2Y07->setOn(xIoPort::GetOut(EM2_VAR_Y06, tmpOutput));
    ui->IoEm2Y08->setOn(xIoPort::GetOut(EM2_VAR_Y07, tmpOutput));
    ui->IoEm2Y09->setOn(xIoPort::GetOut(EM2_VAR_Y08, tmpOutput));
    ui->IoEm2Y10->setOn(xIoPort::GetOut(EM2_VAR_Y09, tmpOutput));
    ui->IoEm2Y11->setOn(xIoPort::GetOut(EM2_VAR_Y10, tmpOutput));
    ui->IoEm2Y12->setOn(xIoPort::GetOut(EM2_VAR_Y11, tmpOutput));
    ui->IoEm2Y13->setOn(xIoPort::GetOut(EM2_VAR_Y12, tmpOutput));
    ui->IoEm2Y14->setOn(xIoPort::GetOut(EM2_VAR_Y13, tmpOutput));
    ui->IoEm2Y15->setOn(xIoPort::GetOut(EM2_VAR_Y14, tmpOutput));
    ui->IoEm2Y16->setOn(xIoPort::GetOut(EM2_VAR_Y15, tmpOutput));
	// 扩展模块3输入
    ui->IoEm3X01->setOn(xIoPort::GetIn(EM3_VAR_X00, tmpInput));
    ui->IoEm3X02->setOn(xIoPort::GetIn(EM3_VAR_X01, tmpInput));
    ui->IoEm3X03->setOn(xIoPort::GetIn(EM3_VAR_X02, tmpInput));
    ui->IoEm3X04->setOn(xIoPort::GetIn(EM3_VAR_X03, tmpInput));
    ui->IoEm3X05->setOn(xIoPort::GetIn(EM3_VAR_X04, tmpInput));
    ui->IoEm3X06->setOn(xIoPort::GetIn(EM3_VAR_X05, tmpInput));
    ui->IoEm3X07->setOn(xIoPort::GetIn(EM3_VAR_X06, tmpInput));
    ui->IoEm3X08->setOn(xIoPort::GetIn(EM3_VAR_X07, tmpInput));
    ui->IoEm3X09->setOn(xIoPort::GetIn(EM3_VAR_X08, tmpInput));
    ui->IoEm3X10->setOn(xIoPort::GetIn(EM3_VAR_X09, tmpInput));
    ui->IoEm3X11->setOn(xIoPort::GetIn(EM3_VAR_X10, tmpInput));
    ui->IoEm3X12->setOn(xIoPort::GetIn(EM3_VAR_X11, tmpInput));
    ui->IoEm3X13->setOn(xIoPort::GetIn(EM3_VAR_X12, tmpInput));
    ui->IoEm3X14->setOn(xIoPort::GetIn(EM3_VAR_X13, tmpInput));
    ui->IoEm3X15->setOn(xIoPort::GetIn(EM3_VAR_X14, tmpInput));
    ui->IoEm3X16->setOn(xIoPort::GetIn(EM3_VAR_X15, tmpInput));
    // 扩展模块3输出
    ui->IoEm3Y01->setOn(xIoPort::GetOut(EM3_VAR_Y00, tmpOutput));
    ui->IoEm3Y02->setOn(xIoPort::GetOut(EM3_VAR_Y01, tmpOutput));
    ui->IoEm3Y03->setOn(xIoPort::GetOut(EM3_VAR_Y02, tmpOutput));
    ui->IoEm3Y04->setOn(xIoPort::GetOut(EM3_VAR_Y03, tmpOutput));
    ui->IoEm3Y05->setOn(xIoPort::GetOut(EM3_VAR_Y04, tmpOutput));
    ui->IoEm3Y06->setOn(xIoPort::GetOut(EM3_VAR_Y05, tmpOutput));
    ui->IoEm3Y07->setOn(xIoPort::GetOut(EM3_VAR_Y06, tmpOutput));
    ui->IoEm3Y08->setOn(xIoPort::GetOut(EM3_VAR_Y07, tmpOutput));
    ui->IoEm3Y09->setOn(xIoPort::GetOut(EM3_VAR_Y08, tmpOutput));
    ui->IoEm3Y10->setOn(xIoPort::GetOut(EM3_VAR_Y09, tmpOutput));
    ui->IoEm3Y11->setOn(xIoPort::GetOut(EM3_VAR_Y10, tmpOutput));
    ui->IoEm3Y12->setOn(xIoPort::GetOut(EM3_VAR_Y11, tmpOutput));
    ui->IoEm3Y13->setOn(xIoPort::GetOut(EM3_VAR_Y12, tmpOutput));
    ui->IoEm3Y14->setOn(xIoPort::GetOut(EM3_VAR_Y13, tmpOutput));
    ui->IoEm3Y15->setOn(xIoPort::GetOut(EM3_VAR_Y14, tmpOutput));
    ui->IoEm3Y16->setOn(xIoPort::GetOut(EM3_VAR_Y15, tmpOutput));
	// 扩展模块4输入
    ui->IoEm4X01->setOn(xIoPort::GetIn(EM4_VAR_X00, tmpInput));
    ui->IoEm4X02->setOn(xIoPort::GetIn(EM4_VAR_X01, tmpInput));
    ui->IoEm4X03->setOn(xIoPort::GetIn(EM4_VAR_X02, tmpInput));
    ui->IoEm4X04->setOn(xIoPort::GetIn(EM4_VAR_X03, tmpInput));
    ui->IoEm4X05->setOn(xIoPort::GetIn(EM4_VAR_X04, tmpInput));
    ui->IoEm4X06->setOn(xIoPort::GetIn(EM4_VAR_X05, tmpInput));
    ui->IoEm4X07->setOn(xIoPort::GetIn(EM4_VAR_X06, tmpInput));
    ui->IoEm4X08->setOn(xIoPort::GetIn(EM4_VAR_X07, tmpInput));
    ui->IoEm4X09->setOn(xIoPort::GetIn(EM4_VAR_X08, tmpInput));
    ui->IoEm4X10->setOn(xIoPort::GetIn(EM4_VAR_X09, tmpInput));
    ui->IoEm4X11->setOn(xIoPort::GetIn(EM4_VAR_X10, tmpInput));
    ui->IoEm4X12->setOn(xIoPort::GetIn(EM4_VAR_X11, tmpInput));
    ui->IoEm4X13->setOn(xIoPort::GetIn(EM4_VAR_X12, tmpInput));
    ui->IoEm4X14->setOn(xIoPort::GetIn(EM4_VAR_X13, tmpInput));
    ui->IoEm4X15->setOn(xIoPort::GetIn(EM4_VAR_X14, tmpInput));
    ui->IoEm4X16->setOn(xIoPort::GetIn(EM4_VAR_X15, tmpInput));
    // 扩展模块4输出
    ui->IoEm4Y01->setOn(xIoPort::GetOut(EM4_VAR_Y00, tmpOutput));
    ui->IoEm4Y02->setOn(xIoPort::GetOut(EM4_VAR_Y01, tmpOutput));
    ui->IoEm4Y03->setOn(xIoPort::GetOut(EM4_VAR_Y02, tmpOutput));
    ui->IoEm4Y04->setOn(xIoPort::GetOut(EM4_VAR_Y03, tmpOutput));
    ui->IoEm4Y05->setOn(xIoPort::GetOut(EM4_VAR_Y04, tmpOutput));
    ui->IoEm4Y06->setOn(xIoPort::GetOut(EM4_VAR_Y05, tmpOutput));
    ui->IoEm4Y07->setOn(xIoPort::GetOut(EM4_VAR_Y06, tmpOutput));
    ui->IoEm4Y08->setOn(xIoPort::GetOut(EM4_VAR_Y07, tmpOutput));
    ui->IoEm4Y09->setOn(xIoPort::GetOut(EM4_VAR_Y08, tmpOutput));
    ui->IoEm4Y10->setOn(xIoPort::GetOut(EM4_VAR_Y09, tmpOutput));
    ui->IoEm4Y11->setOn(xIoPort::GetOut(EM4_VAR_Y10, tmpOutput));
    ui->IoEm4Y12->setOn(xIoPort::GetOut(EM4_VAR_Y11, tmpOutput));
    ui->IoEm4Y13->setOn(xIoPort::GetOut(EM4_VAR_Y12, tmpOutput));
    ui->IoEm4Y14->setOn(xIoPort::GetOut(EM4_VAR_Y13, tmpOutput));
    ui->IoEm4Y15->setOn(xIoPort::GetOut(EM4_VAR_Y14, tmpOutput));
    ui->IoEm4Y16->setOn(xIoPort::GetOut(EM4_VAR_Y15, tmpOutput));
}
