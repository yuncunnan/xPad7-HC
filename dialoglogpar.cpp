#include "dialoglogpar.h"
#include "ui_dialoglogpar.h"
#include "cmbprotocol.h"
#include "xsystemlog.h"

DialogLogPar::DialogLogPar(QWidget *parent) : QDialog(parent), ui(new Ui::DialogLogPar)
{
	ui->setupUi(this);
#if defined(Q_WS_QWS)
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
}

DialogLogPar::~DialogLogPar()
{
	delete ui;
}

int DialogLogPar::DoForm(const QDateTime &time, const QByteArray &par, const quint8 type)
{
	// 设置记录时间
	ui->labelTime->setText(tr("参数设置状态记录时间：") + time.toString("yyyy-MM-dd hh:mm:ss"));
	// 设置参数内容
	if (type == SYSLOG_TYPE_SYS)
	{
		// 系统参数设置状态
		if (par.count() > (int)(LOG_SYSPAR_SIZE * sizeof(quint16)))
		{
			ui->textDisplay->setPlainText(tr("当前日志记录系统参数设置状态无效！"));
		}
		else
		{
			quint16 *pBuf = (quint16*)par.data();
			quint64 modify = (quint64)pBuf[LOG_SYSPAR_MOFIGYLL] | ((quint64)pBuf[LOG_SYSPAR_MOFIGYLH] << 16) |
						((quint64)pBuf[LOG_SYSPAR_MOFIGYHL] << 32) | ((quint64)pBuf[LOG_SYSPAR_MOFIGYHH] << 48);
			QString strPar(tr("系统参数设置：\n"));
			strPar.append("--------------------------------------------------\n");
			strPar.append(tr("计划生产数量：") + QString::number((quint64)pBuf[LOG_PLAN_MOLDING_LOW] | ((quint64)pBuf[LOG_PLAN_MOLDING_HIGH] << 16)) +
						  (modify & ((quint64)1 << LOG_PLAN_MOLDING_LOW) ? "*" : "") + "\n");
			strPar.append(tr("生产数量提醒：") + QString::number((quint64)pBuf[LOG_PLAN_ALARM_LOW] | ((quint64)pBuf[LOG_PLAN_ALARM_HIGH] << 16)) +
						  (modify & ((quint64)1 << LOG_PLAN_ALARM_LOW) ? "*" : "") + "\n");
			strPar.append(tr("不良品数量报警：") + QString::number(pBuf[LOG_REJECT_ALARM]) +
						  (modify & ((quint64)1 << LOG_REJECT_ALARM) ? "*" : "") + "\n");
			strPar.append(tr("报警鸣叫次数：") + QString::number(pBuf[LOG_ALARM_TIMES]) +
						  (modify & ((quint64)1 << LOG_ALARM_TIMES) ? "*" : "") + "\n");
			strPar.append(tr("报警器鸣叫时间：") + QString::number(pBuf[LOG_ALARM_INTERVAL]) +
						  (modify & ((quint64)1 << LOG_ALARM_INTERVAL) ? "*" : "") + "\n");
            strPar.append(tr("打油间隔：") + QString::number((quint64)pBuf[LOG_OIL_INTERVAL_LOW] | ((quint64)pBuf[LOG_OIL_INTERVAL_HIGH] << 16)) +
                          (modify & ((quint64)1 << LOG_OIL_INTERVAL_LOW) ? "*" : "") + "\n");
            strPar.append(tr("打油时间：") + QString::number((quint64)pBuf[LOG_OIL_TIME_LOW] | ((quint64)pBuf[LOG_OIL_TIME_HIGH] << 16)) +
                          (modify & ((quint64)1 << LOG_OIL_TIME_LOW) ? "*" : "") + "\n");
			strPar.append(tr("横行时正臂倒角水平：") + QString::number(pBuf[LOG_ROTATE_OUT_AT_ORIGIN]) +
						  (modify & ((quint64)1 << LOG_ROTATE_OUT_AT_ORIGIN) ? "*" : "") + "\n");
			strPar.append(tr("打开安全门暂停自动运行：") + QString::number(pBuf[LOG_PAUSE_OPEN_DOOR]) +
						  (modify & ((quint64)1 << LOG_PAUSE_OPEN_DOOR) ? "*" : "") + "\n");
			strPar.append(tr("正臂模内倒角允许：") + QString::number(pBuf[LOG_ROTATE_INMOLD_USE]) +
						  (modify & ((quint64)1 << LOG_ROTATE_INMOLD_USE) ? "*" : "") + "\n");
			strPar.append(tr("待机选项：") + QString::number(pBuf[LOG_WAIT_OUTMOULD]) +
						  (modify & ((quint64)1 << LOG_WAIT_OUTMOULD) ? "*" : "") + "\n");
			strPar.append("--------------------------------------------------\n");
#if ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_YIDAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE))
            strPar.append(tr("压铸机关模完成信号使用：") + QString::number(pBuf[LOG_MOLD_CLOSED_USE]) +
                          (modify & ((quint64)1 << LOG_MOLD_CLOSED_USE) ? "*" : "") + "\n");
            strPar.append(tr("压铸机开模中间信号使用：") + QString::number(pBuf[LOG_INTERMOLD_DOWN_USE]) +
                          (modify & ((quint64)1 << LOG_INTERMOLD_DOWN_USE) ? "*" : "") + "\n");
            strPar.append(tr("压铸机开中板模确认信号使用：") + QString::number(pBuf[LOG_MID_OPEN_USE]) +
                          (modify & ((quint64)1 << LOG_MID_OPEN_USE) ? "*" : "") + "\n");
#elif (FACTORY == FA_SINROBOT_JC)
            strPar.append(tr("机床关模完成信号使用：") + QString::number(pBuf[LOG_MOLD_CLOSED_USE]) +
                          (modify & ((quint64)1 << LOG_MOLD_CLOSED_USE) ? "*" : "") + "\n");
            strPar.append(tr("机床开模中间信号使用：") + QString::number(pBuf[LOG_INTERMOLD_DOWN_USE]) +
                          (modify & ((quint64)1 << LOG_INTERMOLD_DOWN_USE) ? "*" : "") + "\n");
            strPar.append(tr("机床开中板模确认信号使用：") + QString::number(pBuf[LOG_MID_OPEN_USE]) +
                          (modify & ((quint64)1 << LOG_MID_OPEN_USE) ? "*" : "") + "\n");
#else
            if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
            {
                strPar.append(tr("压铸机关模完成信号使用：") + QString::number(pBuf[LOG_MOLD_CLOSED_USE]) +
                              (modify & ((quint64)1 << LOG_MOLD_CLOSED_USE) ? "*" : "") + "\n");
                strPar.append(tr("压铸机开模中间信号使用：") + QString::number(pBuf[LOG_INTERMOLD_DOWN_USE]) +
                              (modify & ((quint64)1 << LOG_INTERMOLD_DOWN_USE) ? "*" : "") + "\n");
                strPar.append(tr("压铸机开中板模确认信号使用：") + QString::number(pBuf[LOG_MID_OPEN_USE]) +
                              (modify & ((quint64)1 << LOG_MID_OPEN_USE) ? "*" : "") + "\n");
            }
            else
            {
            strPar.append(tr("注塑机关模完成信号使用：") + QString::number(pBuf[LOG_MOLD_CLOSED_USE]) +
                          (modify & ((quint64)1 << LOG_MOLD_CLOSED_USE) ? "*" : "") + "\n");
            strPar.append(tr("注塑机开模中间信号使用：") + QString::number(pBuf[LOG_INTERMOLD_DOWN_USE]) +
                          (modify & ((quint64)1 << LOG_INTERMOLD_DOWN_USE) ? "*" : "") + "\n");
            strPar.append(tr("注塑机开中板模确认信号使用：") + QString::number(pBuf[LOG_MID_OPEN_USE]) +
                          (modify & ((quint64)1 << LOG_MID_OPEN_USE) ? "*" : "") + "\n");
            }
#endif
			strPar.append(tr("扩展轴伺服使用：") + QString::number(pBuf[LOG_EXT_SERVO_USE]) +
						  (modify & ((quint64)1 << LOG_EXT_SERVO_USE) ? "*" : "") + "\n");
			strPar.append(tr("副臂上下轴伺服使用：") + QString::number(pBuf[LOG_RVER_SERVO_USE]) +
						  (modify & ((quint64)1 << LOG_RVER_SERVO_USE) ? "*" : "") + "\n");
			strPar.append(tr("副臂引拔轴伺服使用：") + QString::number(pBuf[LOG_RHOR_SERVO_USE]) +
						  (modify & ((quint64)1 << LOG_RHOR_SERVO_USE) ? "*" : "") + "\n");
			strPar.append(tr("气动副臂使用：") + QString::number(pBuf[LOG_RUNNER_USE]) +
						  (modify & ((quint64)1 << LOG_RUNNER_USE) ? "*" : "") + "\n");
			strPar.append(tr("气动副臂下位电眼使用：") + QString::number(pBuf[LOG_RUNNER_DOWN_USE]) +
						  (modify & ((quint64)1 << LOG_RUNNER_DOWN_USE) ? "*" : "") + "\n");
            strPar.append(tr("气动副臂前进电眼使用：") + QString::number(pBuf[LOG_RUNNER_ADVANCE_USE]) +
                          (modify & ((quint64)1 << LOG_RUNNER_ADVANCE_USE) ? "*" : "") + "\n");
            strPar.append(tr("气动副臂后退电眼使用：") + QString::number(pBuf[LOG_RUNNER_RETURN_USE]) +
                          (modify & ((quint64)1 << LOG_RUNNER_RETURN_USE) ? "*" : "") + "\n");
			strPar.append(tr("调位使用：") + QString::number(pBuf[LOG_ADJUST_USE]) +
						  (modify & ((quint64)1 << LOG_ADJUST_USE) ? "*" : "") + "\n");
			strPar.append(tr("换治具使用: ") + QString::number(pBuf[LOG_JIG_USE]) +
						  (modify & ((quint64)1 << LOG_JIG_USE) ? "*" : "") + "\n");
            strPar.append(tr("原点在模内: ") + QString::number(pBuf[LOG_HOME_INMOLD]) +
                          (modify & ((quint64)1 << LOG_HOME_INMOLD) ? "*" : "") + "\n");
            strPar.append(tr("进程二使用: ") + QString::number(pBuf[LOG_PROC2_USE]) +
                          (modify & ((quint64)1 << LOG_PROC2_USE) ? "*" : "") + "\n");
            strPar.append(tr("进程三使用: ") + QString::number(pBuf[LOG_PROC3_USE]) +
                          (modify & ((quint64)1 << LOG_PROC3_USE) ? "*" : "") + "\n");
            strPar.append(tr("气动正臂倒角使用: ") + QString::number(pBuf[LOG_ROTATE_USE]) +
                          (modify & ((quint64)1 << LOG_ROTATE_USE) ? "*" : "") + "\n");
            strPar.append(tr("气动副臂倒角使用: ") + QString::number(pBuf[LOG_RUN_ROTATE_USE]) +
                          (modify & ((quint64)1 << LOG_RUN_ROTATE_USE) ? "*" : "") + "\n");
            strPar.append(tr("取物失败开关安全门程序结束: ") + QString::number(pBuf[LOG_DOOR_RESET_USE]) +
                          (modify & ((quint64)1 << LOG_DOOR_RESET_USE) ? "*" : "") + "\n");
            strPar.append(tr("打油使用: ") + QString::number(pBuf[LOG_OIL_USE]) +
                          (modify & ((quint64)1 << LOG_OIL_USE) ? "*" : "") + "\n");
            strPar.append(tr("开机打油: ") + QString::number(pBuf[LOG_OIL_USE_CTRL]) +
                          (modify & ((quint64)1 << LOG_OIL_USE_CTRL) ? "*" : "") + "\n");
            strPar.append(tr("IP地址：") + QString::number((quint8)(pBuf[LOG_IP_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_IP_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_IP_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_IP_LOW]))
                          + (modify & ((quint64)1 << LOG_IP_LOW) ? "*" : "") + "\n");
            strPar.append(tr("子网掩码：") + QString::number((quint8)(pBuf[LOG_SUBMASK_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_SUBMASK_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_SUBMASK_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_SUBMASK_LOW]))
                          + (modify & ((quint64)1 << LOG_SUBMASK_LOW) ? "*" : "") + "\n");
            strPar.append(tr("网关：") + QString::number((quint8)(pBuf[LOG_GATEWAY_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_GATEWAY_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_GATEWAY_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_GATEWAY_LOW]))
                          + (modify & ((quint64)1 << LOG_GATEWAY_LOW) ? "*" : "") + "\n");
            strPar.append(tr("扩展控制位: ") + QString::number(pBuf[LOG_EXTEND_BIT_USE]) +
                          (modify & ((quint64)1 << LOG_EXTEND_BIT_USE) ? "*" : "") + "\n");
			strPar.append(tr("退出时清除扩展IO口使用: ") + QString::number(pBuf[LOG_SYS_IO_CLR]) +
						  (modify & ((quint64)1 << LOG_SYS_IO_CLR) ? "*" : "") + "\n");
            strPar.append("--------------------------------------------------\n");
            strPar.append(tr("相机一IP地址：") + QString::number((quint8)(pBuf[LOG_VISION1_IP_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_VISION1_IP_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_VISION1_IP_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_VISION1_IP_LOW]))
                          + (modify & ((quint64)1 << LOG_VISION1_IP_LOW) ? "*" : "") + "\n");
            strPar.append(tr("相机二IP地址：") + QString::number((quint8)(pBuf[LOG_VISION2_IP_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_VISION2_IP_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_VISION2_IP_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_VISION2_IP_LOW]))
                          + (modify & ((quint64)1 << LOG_VISION2_IP_LOW) ? "*" : "") + "\n");
            strPar.append(tr("相机三IP地址：") + QString::number((quint8)(pBuf[LOG_VISION3_IP_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_VISION3_IP_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_VISION3_IP_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_VISION3_IP_LOW]))
                          + (modify & ((quint64)1 << LOG_VISION3_IP_LOW) ? "*" : "") + "\n");
            strPar.append(tr("相机四IP地址：") + QString::number((quint8)(pBuf[LOG_VISION4_IP_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_VISION4_IP_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_VISION4_IP_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_VISION4_IP_LOW]))
                          + (modify & ((quint64)1 << LOG_VISION4_IP_LOW) ? "*" : "") + "\n");
            strPar.append(tr("相机五IP地址：") + QString::number((quint8)(pBuf[LOG_VISION5_IP_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_VISION5_IP_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_VISION5_IP_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_VISION5_IP_LOW]))
                          + (modify & ((quint64)1 << LOG_VISION5_IP_LOW) ? "*" : "") + "\n");
            strPar.append(tr("相机六IP地址：") + QString::number((quint8)(pBuf[LOG_VISION6_IP_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_VISION6_IP_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_VISION6_IP_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_VISION6_IP_LOW]))
                          + (modify & ((quint64)1 << LOG_VISION1_IP_LOW) ? "*" : "") + "\n");
            strPar.append(tr("相机七IP地址：") + QString::number((quint8)(pBuf[LOG_VISION7_IP_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_VISION7_IP_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_VISION7_IP_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_VISION7_IP_LOW]))
                          + (modify & ((quint64)1 << LOG_VISION7_IP_LOW) ? "*" : "") + "\n");
            strPar.append(tr("相机八IP地址：") + QString::number((quint8)(pBuf[LOG_VISION8_IP_HIGH]>>8)) + "." + QString::number((quint8)(pBuf[LOG_VISION8_IP_HIGH])) + "." +
                          QString::number((quint8)(pBuf[LOG_VISION8_IP_LOW]>>8)) +"." +  QString::number((quint8)(pBuf[LOG_VISION8_IP_LOW]))
                          + (modify & ((quint64)1 << LOG_VISION8_IP_LOW) ? "*" : "") + "\n");
            strPar.append(tr("相机一端口: ") + QString::number(pBuf[LOG_VISION1_PORT]) +
                          (modify & ((quint64)1 << LOG_VISION1_PORT) ? "*" : "") + "\n");
            strPar.append(tr("相机二端口: ") + QString::number(pBuf[LOG_VISION2_PORT]) +
                          (modify & ((quint64)1 << LOG_VISION2_PORT) ? "*" : "") + "\n");
            strPar.append(tr("相机三端口: ") + QString::number(pBuf[LOG_VISION3_PORT]) +
                          (modify & ((quint64)1 << LOG_VISION3_PORT) ? "*" : "") + "\n");
            strPar.append(tr("相机四端口: ") + QString::number(pBuf[LOG_VISION4_PORT]) +
                          (modify & ((quint64)1 << LOG_VISION4_PORT) ? "*" : "") + "\n");
            strPar.append(tr("相机五端口: ") + QString::number(pBuf[LOG_VISION5_PORT]) +
                          (modify & ((quint64)1 << LOG_VISION5_PORT) ? "*" : "") + "\n");
            strPar.append(tr("相机六端口: ") + QString::number(pBuf[LOG_VISION6_PORT]) +
                          (modify & ((quint64)1 << LOG_VISION6_PORT) ? "*" : "") + "\n");
            strPar.append(tr("相机七端口: ") + QString::number(pBuf[LOG_VISION7_PORT]) +
                          (modify & ((quint64)1 << LOG_VISION7_PORT) ? "*" : "") + "\n");
            strPar.append(tr("相机八端口: ") + QString::number(pBuf[LOG_VISION8_PORT]) +
                          (modify & ((quint64)1 << LOG_VISION8_PORT) ? "*" : "") + "\n");
            strPar.append("--------------------------------------------------\n");
			strPar.append(tr("主控模块输入反相：") + QString::number(pBuf[LOG_MAIN_POLARY], 2) +
						  (modify & ((quint64)1 << LOG_MAIN_POLARY) ? "*" : "") + "\n");
            strPar.append(tr("主控模块2输入反相：") + QString::number(pBuf[LOG_MAIN2_POLARY], 2) +
                          (modify & ((quint64)1 << LOG_MAIN2_POLARY) ? "*" : "") + "\n");
            strPar.append(tr("主控模块3输入反相：") + QString::number(pBuf[LOG_MAIN3_POLARY], 2) +
                          (modify & ((quint64)1 << LOG_MAIN3_POLARY) ? "*" : "") + "\n");
            strPar.append(tr("主控模块4输入反相：") + QString::number(pBuf[LOG_MAIN4_POLARY], 2) +
                          (modify & ((quint64)1 << LOG_MAIN4_POLARY) ? "*" : "") + "\n");
            strPar.append(tr("扩展模块1输入反相：") + QString::number(pBuf[LOG_EXT1_POLARY], 2) +
                          (modify & ((quint64)1 << LOG_EXT1_POLARY) ? "*" : "") + "\n");
            strPar.append(tr("扩展模块2输入反相：") + QString::number(pBuf[LOG_EXT2_POLARY], 2) +
                          (modify & ((quint64)1 << LOG_EXT2_POLARY) ? "*" : "") + "\n");
            strPar.append(tr("扩展模块3输入反相：") + QString::number(pBuf[LOG_EXT3_POLARY], 2) +
                          (modify & ((quint64)1 << LOG_EXT3_POLARY) ? "*" : "") + "\n");
            strPar.append(tr("扩展模块4输入反相：") + QString::number(pBuf[LOG_EXT4_POLARY], 2) +
                          (modify & ((quint64)1 << LOG_EXT4_POLARY) ? "*" : "") + "\n");

            strPar.append(tr("主控模块输出反相：") + QString::number(pBuf[LOG_MAIN_OUTPOLARY], 2) +
                          (modify & ((quint64)1 << LOG_MAIN_OUTPOLARY) ? "*" : "") + "\n");
            strPar.append(tr("主控模块2输出反相：") + QString::number(pBuf[LOG_MAIN2_OUTPOLARY], 2) +
                          (modify & ((quint64)1 << LOG_MAIN2_OUTPOLARY) ? "*" : "") + "\n");
            strPar.append(tr("主控模块3输出反相：") + QString::number(pBuf[LOG_MAIN3_OUTPOLARY], 2) +
                          (modify & ((quint64)1 << LOG_MAIN3_OUTPOLARY) ? "*" : "") + "\n");
            strPar.append(tr("主控模块4输出反相：") + QString::number(pBuf[LOG_MAIN4_OUTPOLARY], 2) +
                          (modify & ((quint64)1 << LOG_MAIN4_OUTPOLARY) ? "*" : "") + "\n");

            strPar.append(tr("扩展模块1输出反相：") + QString::number(pBuf[LOG_EXT1_OUTPOLARY], 2) +
                          (modify & ((quint64)1 << LOG_EXT1_OUTPOLARY) ? "*" : "") + "\n");
            strPar.append(tr("扩展模块2输出反相：") + QString::number(pBuf[LOG_EXT2_OUTPOLARY], 2) +
                          (modify & ((quint64)1 << LOG_EXT2_OUTPOLARY) ? "*" : "") + "\n");
            strPar.append(tr("扩展模块3输出反相：") + QString::number(pBuf[LOG_EXT3_OUTPOLARY], 2) +
                          (modify & ((quint64)1 << LOG_EXT3_OUTPOLARY) ? "*" : "") + "\n");
            strPar.append(tr("扩展模块4输出反相：") + QString::number(pBuf[LOG_EXT4_OUTPOLARY], 2) +
                          (modify & ((quint64)1 << LOG_EXT4_OUTPOLARY) ? "*" : "") + "\n");
            strPar.append("--------------------------------------------------\n");
			strPar.append(tr("主控模块输入报警允许忽略：") + QString::number(pBuf[LOG_MAIN_IGNORE], 2) +
						  (modify & ((quint64)1 << LOG_MAIN_IGNORE) ? "*" : "") + "\n");
            strPar.append(tr("主控模块2输入报警允许忽略：") + QString::number(pBuf[LOG_MAIN2_IGNORE], 2) +
                          (modify & ((quint64)1 << LOG_MAIN2_IGNORE) ? "*" : "") + "\n");
            strPar.append(tr("主控模块3输入报警允许忽略：") + QString::number(pBuf[LOG_MAIN3_IGNORE], 2) +
                          (modify & ((quint64)1 << LOG_MAIN3_IGNORE) ? "*" : "") + "\n");
            strPar.append(tr("主控模块4输入报警允许忽略：") + QString::number(pBuf[LOG_MAIN4_IGNORE], 2) +
                          (modify & ((quint64)1 << LOG_MAIN4_IGNORE) ? "*" : "") + "\n");
			strPar.append(tr("扩展模块1输入报警允许忽略：") + QString::number(pBuf[LOG_EXT1_IGNORE], 2) +
						  (modify & ((quint64)1 << LOG_EXT1_IGNORE) ? "*" : "") + "\n");
			strPar.append(tr("扩展模块2输入报警允许忽略：") + QString::number(pBuf[LOG_EXT2_IGNORE], 2) +
						  (modify & ((quint64)1 << LOG_EXT2_IGNORE) ? "*" : "") + "\n");
			strPar.append(tr("扩展模块3输入报警允许忽略：") + QString::number(pBuf[LOG_EXT3_IGNORE], 2) +
						  (modify & ((quint64)1 << LOG_EXT3_IGNORE) ? "*" : "") + "\n");
			strPar.append(tr("扩展模块4输入报警允许忽略：") + QString::number(pBuf[LOG_EXT4_IGNORE], 2) +
						  (modify & ((quint64)1 << LOG_EXT4_IGNORE) ? "*" : "") + "\n");
			strPar.append(tr("主控模块模内不报警：") + QString::number(pBuf[LOG_MAIN_NOALM], 2) +
						  (modify & ((quint64)1 << LOG_MAIN_NOALM) ? "*" : "") + "\n");
            strPar.append(tr("主控模块2模内不报警：") + QString::number(pBuf[LOG_MAIN2_NOALM], 2) +
                          (modify & ((quint64)1 << LOG_MAIN2_NOALM) ? "*" : "") + "\n");
            strPar.append(tr("主控模块3模内不报警：") + QString::number(pBuf[LOG_MAIN3_NOALM], 2) +
                          (modify & ((quint64)1 << LOG_MAIN3_NOALM) ? "*" : "") + "\n");
            strPar.append(tr("主控模块4模内不报警：") + QString::number(pBuf[LOG_MAIN4_NOALM], 2) +
                          (modify & ((quint64)1 << LOG_MAIN4_NOALM) ? "*" : "") + "\n");
			strPar.append(tr("扩展模块1模内不报警：") + QString::number(pBuf[LOG_EXT1_NOALM], 2) +
						  (modify & ((quint64)1 << LOG_EXT1_NOALM) ? "*" : "") + "\n");
			strPar.append(tr("扩展模块2模内不报警：") + QString::number(pBuf[LOG_EXT2_NOALM], 2) +
						  (modify & ((quint64)1 << LOG_EXT2_NOALM) ? "*" : "") + "\n");
			strPar.append(tr("扩展模块3模内不报警：") + QString::number(pBuf[LOG_EXT3_NOALM], 2) +
						  (modify & ((quint64)1 << LOG_EXT3_NOALM) ? "*" : "") + "\n");
			strPar.append(tr("扩展模块4模内不报警：") + QString::number(pBuf[LOG_EXT4_NOALM], 2) +
						  (modify & ((quint64)1 << LOG_EXT4_NOALM) ? "*" : "") + "\n");
			ui->textDisplay->setPlainText(strPar);
		}
	}
	else if (type == SYSLOG_TYPE_SRV)
	{
		// 伺服参数设置状态
		if (par.count() > (int)(LOG_SRVPAR_SIZE * sizeof(quint32)))
		{
			ui->textDisplay->setPlainText(tr("当前日志记录伺服参数设置状态无效！"));
		}
		else
		{
            qint32 *pBuf = (qint32*)par.data();
			quint64 modify = (quint64)pBuf[LOG_SRVPAR_MODIFYLL] | ((quint64)pBuf[LOG_SRVPAR_MODIFYLH] << 16) |
							 ((quint64)pBuf[LOG_SRVPAR_MODIFYHL] << 32) | ((quint64)pBuf[LOG_SRVPAR_MODIFYHH] << 48);
			QString strPar(tr("伺服参数设置：\n"));
			strPar.append("--------------------------------------------------\n");
            strPar.append(tr("正臂上行位置安全区域：0 - ") + QString::number(pBuf[LOG_MAX_WAIT_POS_INMOLD_Y] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_MAX_WAIT_POS_INMOLD_Y) ? "*" : "") + "\n");
            strPar.append(tr("副臂上行位置安全区域：0 - ") + QString::number(pBuf[LOG_MAX_WAIT_POS_INMOLD_A] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_MAX_WAIT_POS_INMOLD_A) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔模内安全区域：") + QString::number(pBuf[LOG_MIN_SAFE_POS_INMOLD_X] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_MIN_SAFE_POS_INMOLD_X) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_SAFE_POS_INMOLD_X] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_MAX_SAFE_POS_INMOLD_X) ? "*" : "") + "\n");
            strPar.append(tr("副臂引拔模内安全区域：") + QString::number(pBuf[LOG_MIN_SAFE_POS_INMOLD_B] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_MIN_SAFE_POS_INMOLD_B) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_SAFE_POS_INMOLD_B] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_MAX_SAFE_POS_INMOLD_B) ? "*" : "") + "\n");
            strPar.append(tr("副臂引拔横行安全区域：") + QString::number(pBuf[LOG_MIN_B_TRAVE] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MIN_B_TRAVE) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_B_TRAVE] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MAX_B_TRAVE) ? "*" : "") + "\n");
            strPar.append(tr("横行模外安全区域：") + QString::number(pBuf[LOG_MIN_SAFE_POS_OUTMOLD_Z] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MIN_SAFE_POS_OUTMOLD_Z) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_SAFE_POS_OUTMOLD_Z] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MAX_SAFE_POS_OUTMOLD_Z) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔轴模内安全区域：") + QString::number(pBuf[LOG_MIN_SAFE_POS_INMOLD_Z] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MIN_SAFE_POS_INMOLD_Z) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_SAFE_POS_INMOLD_Z] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MAX_SAFE_POS_INMOLD_Z) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔轴横行安全区域：") + QString::number(pBuf[LOG_MIN_X_TRAVE] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MIN_X_TRAVE) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_X_TRAVE] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MAX_X_TRAVE) ? "*" : "") + "\n");
            strPar.append(tr("副臂横行模内安全区域：") + QString::number(pBuf[LOG_MIN_SAFE_POS_INMOLD_Z_A] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MIN_SAFE_POS_INMOLD_Z_A) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_SAFE_POS_INMOLD_Z_A] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MAX_SAFE_POS_INMOLD_Z_A) ? "*" : "") + "\n");
            strPar.append(tr("横行模外安全区域2：") + QString::number(pBuf[LOG_MIN_SAFE_POS_OUTMOLD2_Z] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MIN_SAFE_POS_OUTMOLD2_Z) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_SAFE_POS_OUTMOLD2_Z] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MAX_SAFE_POS_OUTMOLD2_Z) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴(倒角)模内安全区域：") + QString::number(pBuf[LOG_MIN_SAFE_ROT] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MIN_SAFE_ROT) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_SAFE_ROT] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MAX_SAFE_ROT) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴(倒角)横行安全区域：") + QString::number(pBuf[LOG_MIN_SAFE_TRV] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MIN_SAFE_TRV) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_SAFE_TRV] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MAX_SAFE_TRV) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴模内安全区域：") + QString::number(pBuf[LOG_MIN_C_INMOLD] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MIN_C_INMOLD) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_C_INMOLD] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MAX_C_INMOLD) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴横行安全区域：") + QString::number(pBuf[LOG_MIN_C_TRAVE] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MIN_C_TRAVE) ? "*" : "") +
                          " - " + QString::number(pBuf[LOG_MAX_C_TRAVE] / 100.00, 'f', 2) +
                          (modify & ((quint64)1 << LOG_MAX_C_TRAVE) ? "*" : "") + "\n");
            strPar.append(tr("正臂原点和副臂原点距离：") + QString::number(pBuf[LOG_MACHINE_MAX_LEN_X] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_MACHINE_MAX_LEN_X) ? "*" : "") + "\n");
            strPar.append(tr("正臂和副臂最小安全间距：") + QString::number(pBuf[LOG_MIN_SAFE_DIS_X_B] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_MIN_SAFE_DIS_X_B) ? "*" : "") + "\n");
			strPar.append("--------------------------------------------------\n");
			strPar.append(tr("正臂引拔轴运行速度：") + QString::number(pBuf[LOG_XMAX_SPEED]) +
						  (modify & ((quint64)1 << LOG_XMAX_SPEED) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔轴加速度：") + QString::number(pBuf[LOG_XMAX_ACCELERATION]) +
                          (modify & ((quint64)1 << LOG_XMAX_ACCELERATION) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔轴JERK加加速：") + QString::number(pBuf[LOG_XMAX_JERK]) +
                          (modify & ((quint64)1 << LOG_XMAX_JERK) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔轴马达转动一圈距离：") + QString::number(*(float*)&pBuf[LOG_X_UNITS]) +
                          (modify & ((quint64)1 << LOG_X_UNITS) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔轴马达转动一圈需脉冲：") + QString::number(*(float*)&pBuf[LOG_X_PLUSES]) +
                          (modify & ((quint64)1 << LOG_X_PLUSES) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔轴原点偏移：") + QString::number(pBuf[LOG_ORIGIN_OFFSET_X] / 100.00) +
                          (modify & ((quint64)1 << LOG_ORIGIN_OFFSET_X) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔轴编码器：") + QString::number(pBuf[LOG_ENCODER_X]) +
                          (modify & ((quint64)1 << LOG_ENCODER_X) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔轴原点待机点：") + QString::number(pBuf[LOG_HOME_WAIT_X]) +
                          (modify & ((quint64)1 << LOG_HOME_WAIT_X) ? "*" : "") + "\n");
            strPar.append(tr("正臂引拔轴模：") + QString::number(pBuf[LOG_MOD_X]) +
                          (modify & ((quint64)1 << LOG_MOD_X) ? "*" : "") + "\n");
            strPar.append(tr("副臂引拔轴运行速度：") + QString::number(pBuf[LOG_BMAX_SPEED]) +
						  (modify & ((quint64)1 << LOG_BMAX_SPEED) ? "*" : "") + "\n");
			strPar.append(tr("副臂引拔轴加速度：") + QString::number(pBuf[LOG_BMAX_ACCELERATION]) +
						  (modify & ((quint64)1 << LOG_BMAX_ACCELERATION) ? "*" : "") + "\n");
            strPar.append(tr("副臂引拔轴JERK加加速：") + QString::number(pBuf[LOG_BMAX_JERK]) +
                          (modify & ((quint64)1 << LOG_BMAX_JERK) ? "*" : "") + "\n");
            strPar.append(tr("副臂引拔轴马达转动一圈距离：") + QString::number(*(float*)&pBuf[LOG_B_UNITS]) +
                          (modify & ((quint64)1 << LOG_B_UNITS) ? "*" : "") + "\n");
            strPar.append(tr("副臂引拔轴马达转动一圈需脉冲：") + QString::number(*(float*)&pBuf[LOG_B_PLUSES]) +
                          (modify & ((quint64)1 << LOG_B_PLUSES) ? "*" : "") + "\n");
            strPar.append(tr("副臂引拔轴原点偏移：") + QString::number(pBuf[LOG_ORIGIN_OFFSET_B] / 100.00) +
                          (modify & ((quint64)1 << LOG_ORIGIN_OFFSET_B) ? "*" : "") + "\n");
            strPar.append(tr("副臂引拔轴编码器：") + QString::number(pBuf[LOG_ENCODER_B]) +
                          (modify & ((quint64)1 << LOG_ENCODER_B) ? "*" : "") + "\n");
            strPar.append(tr("副臂引拔轴原点待机点：") + QString::number(pBuf[LOG_HOME_WAIT_B]) +
                          (modify & ((quint64)1 << LOG_HOME_WAIT_B) ? "*" : "") + "\n");
            strPar.append(tr("副臂引拔轴模：") + QString::number(pBuf[LOG_MOD_B]) +
                          (modify & ((quint64)1 << LOG_MOD_B) ? "*" : "") + "\n");
            strPar.append("--------------------------------------------------\n");
            strPar.append(tr("正臂上下轴软件行程：") + QString::number(pBuf[LOG_SOFTWARE_MAX_LEN_Y] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_SOFTWARE_MAX_LEN_Y) ? "*" : "") + "\n");
			strPar.append(tr("正臂上下轴运行速度：") + QString::number(pBuf[LOG_YMAX_SPEED]) +
						  (modify & ((quint64)1 << LOG_YMAX_SPEED) ? "*" : "") + "\n");
            strPar.append(tr("正臂上下轴加速度：") + QString::number(pBuf[LOG_YMAX_ACCELERATION]) +
                          (modify & ((quint64)1 << LOG_YMAX_ACCELERATION) ? "*" : "") + "\n");
            strPar.append(tr("正臂上下轴JERK加加速：") + QString::number(pBuf[LOG_YMAX_JERK]) +
                          (modify & ((quint64)1 << LOG_YMAX_JERK) ? "*" : "") + "\n");
            strPar.append(tr("正臂上下轴马达转动一圈距离：") + QString::number(*(float*)&pBuf[LOG_Y_UNITS]) +
                          (modify & ((quint64)1 << LOG_Y_UNITS) ? "*" : "") + "\n");
            strPar.append(tr("正臂上下轴马达转动一圈需脉冲：") + QString::number(*(float*)&pBuf[LOG_Y_PLUSES]) +
                          (modify & ((quint64)1 << LOG_Y_PLUSES) ? "*" : "") + "\n");
            strPar.append(tr("正臂上下轴原点偏移：") + QString::number(pBuf[LOG_ORIGIN_OFFSET_Y] / 100.00) +
                          (modify & ((quint64)1 << LOG_ORIGIN_OFFSET_Y) ? "*" : "") + "\n");
            strPar.append(tr("正臂上下轴编码器：") + QString::number(pBuf[LOG_ENCODER_Y]) +
                          (modify & ((quint64)1 << LOG_ENCODER_Y) ? "*" : "") + "\n");
            strPar.append(tr("正臂上下轴原点待机点：") + QString::number(pBuf[LOG_HOME_WAIT_Y]) +
                          (modify & ((quint64)1 << LOG_HOME_WAIT_Y) ? "*" : "") + "\n");
            strPar.append(tr("正臂上下轴模：") + QString::number(pBuf[LOG_MOD_Y]) +
                          (modify & ((quint64)1 << LOG_MOD_Y) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴软件行程：") + QString::number(pBuf[LOG_SOFTWARE_MAX_LEN_A] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_SOFTWARE_MAX_LEN_A) ? "*" : "") + "\n");
			strPar.append(tr("副臂上下轴运行速度：") + QString::number(pBuf[LOG_AMAX_SPEED]) +
						  (modify & ((quint64)1 << LOG_AMAX_SPEED) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴加速度：") + QString::number(pBuf[LOG_AMAX_ACCELERATION]) +
                          (modify & ((quint64)1 << LOG_AMAX_ACCELERATION) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴JERK加加速：") + QString::number(pBuf[LOG_AMAX_JERK]) +
                          (modify & ((quint64)1 << LOG_AMAX_JERK) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴马达转动一圈距离：") + QString::number(*(float*)&pBuf[LOG_A_UNITS]) +
                          (modify & ((quint64)1 << LOG_A_UNITS) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴马达转动一圈需脉冲：") + QString::number(*(float*)&pBuf[LOG_A_PLUSES]) +
                          (modify & ((quint64)1 << LOG_A_PLUSES) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴原点偏移：") + QString::number(pBuf[LOG_ORIGIN_OFFSET_A] / 100.00) +
                          (modify & ((quint64)1 << LOG_ORIGIN_OFFSET_A) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴编码器：") + QString::number(pBuf[LOG_ENCODER_A]) +
                          (modify & ((quint64)1 << LOG_ENCODER_A) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴原点待机点：") + QString::number(pBuf[LOG_HOME_WAIT_A]) +
                          (modify & ((quint64)1 << LOG_HOME_WAIT_A) ? "*" : "") + "\n");
            strPar.append(tr("副臂上下轴模：") + QString::number(pBuf[LOG_MOD_A]) +
                          (modify & ((quint64)1 << LOG_MOD_A) ? "*" : "") + "\n");
            strPar.append("--------------------------------------------------\n");
            strPar.append(tr("横行轴软件行程：") + QString::number(pBuf[LOG_SOFTWARE_MAX_LEN_Z] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_SOFTWARE_MAX_LEN_Z) ? "*" : "") + "\n");
			strPar.append(tr("横行轴运行速度：") + QString::number(pBuf[LOG_ZMAX_SPEED]) +
						  (modify & ((quint64)1 << LOG_ZMAX_SPEED) ? "*" : "") + "\n");
            strPar.append(tr("横行轴加速度：") + QString::number(pBuf[LOG_ZMAX_ACCELERATION]) +
                          (modify & ((quint64)1 << LOG_ZMAX_ACCELERATION) ? "*" : "") + "\n");
            strPar.append(tr("横行轴JERK加加速：") + QString::number(pBuf[LOG_ZMAX_JERK]) +
                          (modify & ((quint64)1 << LOG_ZMAX_JERK) ? "*" : "") + "\n");
            strPar.append(tr("横行轴马达转动一圈距离：") + QString::number(*(float*)&pBuf[LOG_Z_UNITS]) +
                          (modify & ((quint64)1 << LOG_Z_UNITS) ? "*" : "") + "\n");
            strPar.append(tr("横行轴马达转动一圈需脉冲：") + QString::number(*(float*)&pBuf[LOG_Z_PLUSES]) +
                          (modify & ((quint64)1 << LOG_Z_PLUSES) ? "*" : "") + "\n");
            strPar.append(tr("横行轴原点偏移：") + QString::number(pBuf[LOG_ORIGIN_OFFSET_Z] / 100.00) +
                          (modify & ((quint64)1 << LOG_ORIGIN_OFFSET_Z) ? "*" : "") + "\n");
            strPar.append(tr("横行轴编码器：") + QString::number(pBuf[LOG_ENCODER_Z]) +
                          (modify & ((quint64)1 << LOG_ENCODER_Z) ? "*" : "") + "\n");
            strPar.append(tr("横行轴原点待机点：") + QString::number(pBuf[LOG_HOME_WAIT_Z]) +
                          (modify & ((quint64)1 << LOG_HOME_WAIT_Z) ? "*" : "") + "\n");
            strPar.append(tr("横行轴模：") + QString::number(pBuf[LOG_MOD_Z]) +
                          (modify & ((quint64)1 << LOG_MOD_Z) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴软件行程：") + QString::number(pBuf[LOG_SOFTWARE_MAX_LEN_C] / 100.00, 'f', 2) +
						  (modify & ((quint64)1 << LOG_SOFTWARE_MAX_LEN_C) ? "*" : "") + "\n");
			strPar.append(tr("扩展轴运行速度：") + QString::number(pBuf[LOG_CMAX_SPEED]) +
						  (modify & ((quint64)1 << LOG_CMAX_SPEED) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴加速度：") + QString::number(pBuf[LOG_CMAX_ACCELERATION]) +
                          (modify & ((quint64)1 << LOG_CMAX_ACCELERATION) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴JERK加加速：") + QString::number(pBuf[LOG_CMAX_JERK]) +
                          (modify & ((quint64)1 << LOG_CMAX_JERK) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴马达转动一圈距离：") + QString::number(*(float*)&pBuf[LOG_C_UNITS]) +
                          (modify & ((quint64)1 << LOG_C_UNITS) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴马达转动一圈需脉冲：") + QString::number(*(float*)&pBuf[LOG_C_PLUSES]) +
                          (modify & ((quint64)1 << LOG_C_PLUSES) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴原点偏移：") + QString::number(pBuf[LOG_ORIGIN_OFFSET_C] / 100.00) +
                          (modify & ((quint64)1 << LOG_ORIGIN_OFFSET_C) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴编码器：") + QString::number(pBuf[LOG_ENCODER_C]) +
                          (modify & ((quint64)1 << LOG_ENCODER_C) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴原点待机点：") + QString::number(pBuf[LOG_HOME_WAIT_C]) +
                          (modify & ((quint64)1 << LOG_HOME_WAIT_C) ? "*" : "") + "\n");
            strPar.append(tr("扩展轴模：") + QString::number(pBuf[LOG_MOD_C]) +
                          (modify & ((quint64)1 << LOG_MOD_C) ? "*" : "") + "\n");
            strPar.append("--------------------------------------------------\n");
            strPar.append(tr("轴类型：") + QString::number(pBuf[LOG_ANGLE_BMP]) +
                          (modify & ((quint64)1 << LOG_ANGLE_BMP) ? "*" : "") + "\n");
            strPar.append(tr("减速类型：") + QString::number(pBuf[LOG_RAMP_BMP]) +
                          (modify & ((quint64)1 << LOG_RAMP_BMP) ? "*" : "") + "\n");
            strPar.append(tr("原点归位模式：") + QString::number(pBuf[LOG_HOME_MODE]) +
                          (modify & ((quint64)1 << LOG_HOME_MODE) ? "*" : "") + "\n");
            strPar.append(tr("原点归位快速速度：") + QString::number(pBuf[LOG_HOME_VEL]) +
                          (modify & ((quint64)1 << LOG_HOME_VEL) ? "*" : "") + "\n");
            strPar.append(tr("原点归位慢速速度：") + QString::number(pBuf[LOG_HOME_VEL_SLOW]) +
                          (modify & ((quint64)1 << LOG_HOME_VEL_SLOW) ? "*" : "") + "\n");
            ui->textDisplay->setPlainText(strPar);
		}
	}
	else if (type == SYSLOG_TYPE_UI)
	{
		if (par.count() > (int)(LOG_UIPAR_SIZE * sizeof(quint16)))
		{
			ui->textDisplay->setPlainText(tr("当前日志记录界面参数设置状态无效！"));
		}
		else
		{
			quint16 *pBuf = (quint16*)par.data();
			quint16 modify = pBuf[LOG_UIPAR_MODIFY];
			QString strPar(tr("界面参数设置：\n"));
			strPar.append("--------------------------------------------------\n");
			strPar.append(tr("界面语言："));
			if (pBuf[LOG_UI_LAN] == LAN_CHINESE_S)
				strPar.append(tr("简体中文", "不要翻译"));
			else if (pBuf[LOG_UI_LAN] == LAN_CHINESE_T)
				strPar.append(tr("繁體中文", "不要翻译"));
            else if (pBuf[LOG_UI_LAN] == LAN_ENGLISH)
                strPar.append(tr("ENGLISH", "不要翻译"));
            else if (pBuf[LOG_UI_LAN] == LAN_RUSSIAN)
                strPar.append(tr("РУССКИЕ", "不要翻译"));
            else if (pBuf[LOG_UI_LAN] == LAN_TURKISH)
                strPar.append(tr("TÜRK", "不要翻译"));
            else if (pBuf[LOG_UI_LAN] == LAN_VIETNAM)
                strPar.append(tr("Việt Nam", "不要翻译"));
            else if (pBuf[LOG_UI_LAN] == LAN_PORTUGAL)
                strPar.append(tr("Português", "不要翻译"));
			strPar.append((modify & (1 << LOG_UI_LAN) ? "*\n" : "\n"));
			strPar.append(tr("屏保时间设置：") + QString::number(pBuf[LOG_UI_SCRSAVER]) +
						  (modify & (1 << LOG_UI_SCRSAVER) ? "*" : "") + "\n");
			strPar.append(tr("背光亮度调节：") + QString::number(pBuf[LOG_UI_BKLIGHT]) +
						  (modify & (1 << LOG_UI_BKLIGHT) ? "*" : "") + "\n");
			strPar.append(tr("震动反馈：") + QString::number(pBuf[LOG_UI_SH0CK]) +
						  (modify & (1 << LOG_UI_SH0CK) ? "*" : "") + "\n");
			strPar.append(tr("按键提示音：") + QString::number(pBuf[LOG_UI_KEYBELL]) +
						  (modify & (1 << LOG_UI_KEYBELL) ? "*" : "") + "\n");
			strPar.append(tr("触屏提示音：") + QString::number(pBuf[LOG_UI_TOUCHBELL]) +
						  (modify & (1 << LOG_UI_TOUCHBELL) ? "*" : "") + "\n");
			strPar.append(tr("提示音频率设置：") + QString::number(pBuf[LOG_UI_BELLFREQ]) +
						  (modify & (1 << LOG_UI_BELLFREQ) ? "*" : "") + "\n");
			strPar.append(tr("安全开关使用：") + QString::number(pBuf[LOG_UI_SWITCHUSE]) +
						  (modify & (1 << LOG_UI_SWITCHUSE) ? "*" : "") + "\n");
			strPar.append(tr("原点归位安全开关长按：") + QString::number(pBuf[LOG_UI_ALWAYSON]) +
						  (modify & (1 << LOG_UI_ALWAYSON) ? "*" : "") + "\n");
			ui->textDisplay->setPlainText(strPar);
		}
	}
	else if (type == SYSLOG_TYPE_ALM)
	{
        if (par.count() > (int)(6 * sizeof(quint32)))
		{
			ui->textDisplay->setPlainText(tr("当前日志记录伺服位置状态无效！"));
		}
		else
		{
            quint32 *pBuf = (quint32*)par.data();
			QString strPar(tr("报警时各轴伺服位置：\n"));
			strPar.append("--------------------------------------------------\n");
            strPar.append(tr("正臂引拔轴：") + QString::number(pBuf[AXIS_IDX_PHOR] / 100.00, 'f', 2) + "\n");
            strPar.append(tr("正臂上下轴：") + QString::number(pBuf[AXIS_IDX_PVER] / 100.00, 'f', 2) + "\n");
            strPar.append(tr("横行轴：") + QString::number(pBuf[AXIS_IDX_TRV] / 100.00, 'f', 2) + "\n");
            strPar.append(tr("副臂引拔轴：") + QString::number(pBuf[AXIS_IDX_RHOR] / 100.00, 'f', 2) + "\n");
            strPar.append(tr("副臂上下轴：") + QString::number(pBuf[AXIS_IDX_RVER] / 100.00, 'f', 2) + "\n");
            strPar.append(tr("扩展轴：") + QString::number(pBuf[AXIS_IDX_EXT] / 100.00, 'f', 2) + "\n");
			ui->textDisplay->setPlainText(strPar);
		}
	}
	else if (type == SYSLOG_TYPE_STATE_CHG)
	{
        if (par.count() > (int)(6 * sizeof(quint32)))
		{
			ui->textDisplay->setPlainText(tr("当前日志记录伺服位置状态无效！"));
		}
		else
		{
            quint32 *pBuf = (quint32*)par.data();
			QString strPar(tr("系统状态改变时各轴伺服位置：\n"));
			strPar.append("--------------------------------------------------\n");
            strPar.append(tr("正臂引拔轴：") + QString::number(pBuf[AXIS_IDX_PHOR] / 100.00, 'f', 2) + "\n");
            strPar.append(tr("正臂上下轴：") + QString::number(pBuf[AXIS_IDX_PVER] / 100.00, 'f', 2) + "\n");
            strPar.append(tr("横行轴：") + QString::number(pBuf[AXIS_IDX_TRV] / 100.00, 'f', 2) + "\n");
            strPar.append(tr("副臂引拔轴：") + QString::number(pBuf[AXIS_IDX_RHOR] / 100.00, 'f', 2) + "\n");
            strPar.append(tr("副臂上下轴：") + QString::number(pBuf[AXIS_IDX_RVER] / 100.00, 'f', 2) + "\n");
            strPar.append(tr("扩展轴：") + QString::number(pBuf[AXIS_IDX_EXT] / 100.00, 'f', 2) + "\n");
            ui->textDisplay->setPlainText(strPar);
		}
	}
	else
	{
		// 记录没有参数设置状态
		ui->textDisplay->setPlainText(tr("当前日志记录没有参数设置状态。"));
	}
	// 显示对话框
	return exec();
}

void DialogLogPar::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}
