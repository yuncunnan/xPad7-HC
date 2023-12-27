#include <QButtonGroup>
#include "xsystemlog.h"
#include "formalarm.h"
#include "servoalias.h"
#include "xmessagebox.h"
#include "ui_formalarm.h"

FormAlarm::FormAlarm(CMBProtocol *modbus, QWidget *parent) :	QWidget(parent), ui(new Ui::FormAlarm)
{
	ui->setupUi(this);
	retranslateUi();
	ui->tabWidget->setCurrentIndex(0);
	pModbus = modbus;
	// 组织报警位置单选框
	pAlmPos = new QButtonGroup;
	pAlmPos->addButton(ui->radioSysImm, ALARM_IMM_SYS);
	pAlmPos->addButton(ui->radioPaRotate, ALARM_PRO_ARM);
	pAlmPos->addButton(ui->radioRunPneu, ALARM_RUN_ARM);
	pAlmPos->addButton(ui->radioEm1, ALARM_IOEXT_1);
	pAlmPos->addButton(ui->radioEm2, ALARM_IOEXT_2);
	pAlmPos->addButton(ui->radioEm3, ALARM_IOEXT_3);
	pAlmPos->addButton(ui->radioEm4, ALARM_IOEXT_4);
	pAlmPos->addButton(ui->radioPaHor, ALARM_SV_PHOR);
	pAlmPos->addButton(ui->radioPaVer, ALARM_SV_PVER);
	pAlmPos->addButton(ui->radioTravel, ALARM_SV_TRAV);
	pAlmPos->addButton(ui->radioRaHor, ALARM_SV_RHOR);
	pAlmPos->addButton(ui->radioRaVer, ALARM_SV_RVER);
	pAlmPos->addButton(ui->radioExtend, ALARM_SV_EXTE);
	// 连接信号槽
	connect(pAlmPos, SIGNAL(buttonClicked(int)), this, SLOT(AlmPosClicked(int)));
	connect(parent, SIGNAL(LogModelUpdate()), this, SLOT(resetModel()));
	// 挂载数据源
	ui->viewRecords->setModel(xSysLog::GetModel());
	ui->viewRecords->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// 设置表头字体
#if SIMULATOR
    ui->viewRecords->horizontalHeader()->setFont(QFont("Microsoft YaHei", 10));
    ui->viewRecords->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 10pt;}");
    ui->viewRecords->verticalHeader()->setFont(QFont("Microsoft YaHei", 10));
    ui->viewRecords->verticalHeader()->setStyleSheet("QHeaderView {font-size: 10pt;}");
#else
	ui->viewRecords->horizontalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->viewRecords->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
	ui->viewRecords->verticalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->viewRecords->verticalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
#endif
    // 设置表头尺寸模式
	ui->viewRecords->horizontalHeader()->setResizeMode(xSysLog::logTime, QHeaderView::Fixed);
	ui->viewRecords->horizontalHeader()->setResizeMode(xSysLog::logValue, QHeaderView::Stretch);
	ui->viewRecords->verticalHeader()->setVisible(true);
	ui->viewRecords->verticalHeader()->setMaximumWidth(100);
	ui->viewRecords->verticalHeader()->setMinimumWidth(25);
	// 隐藏列
	ui->viewRecords->setColumnHidden(xSysLog::logType, true);
	ui->viewRecords->setColumnHidden(xSysLog::logUser, true);
	ui->viewRecords->setColumnHidden(xSysLog::logExt, true);
	ui->viewRecords->setColumnHidden(xSysLog::logID, true);
	ui->viewRecords->setColumnHidden(xSysLog::input, true);
	ui->viewRecords->setColumnHidden(xSysLog::output, true);
	ui->viewRecords->setColumnHidden(xSysLog::parameter, true);
	// 设置列宽度
    ui->viewRecords->setColumnWidth(xSysLog::logTime, 300);
    // 设置数据源过滤
    xSysLog::GetModel()->setFilter(QString("logType = '%1'").arg(SYSLOG_TYPE_ALM));
    xSysLog::GetModel()->select();
}

FormAlarm::~FormAlarm()
{
	delete ui;
	delete pAlmPos;
}

void FormAlarm::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		retranslateUi();
		break;
	default:
		break;
	}
}
void FormAlarm::retranslateUi(void)
{
#if ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_YIDAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE))
    ui->radioSysImm->setText(tr("压铸机/系统"));
#elif FACTORY == FA_SINROBOT_JC
    ui->radioSysImm->setText(tr("机床/系统"));
#else
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
        ui->radioSysImm->setText(tr("压铸机/系统"));
    else
    {
        ui->radioSysImm->setText(tr("注塑机/系统"));
    }
#endif
    ui->radioPaHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴伺服"));
	ui->radioPaVer->setText(GetServoName(AXIS_IDX_PVER) + tr("轴伺服"));
	ui->radioTravel->setText(GetServoName(AXIS_IDX_TRV) + tr("轴伺服"));
	ui->radioRaHor->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴伺服"));
	ui->radioRaVer->setText(GetServoName(AXIS_IDX_RVER) + tr("轴伺服"));
	ui->radioExtend->setText(GetServoName(AXIS_IDX_EXT) + tr("轴伺服"));
}

void FormAlarm::resetModel(void)
{
	ui->viewRecords->setModel(xSysLog::GetModel());
}

bool FormAlarm::EnterForm(void)
{
    // 设置数据源过滤
    xSysLog::GetModel()->setFilter(QString("logType = '%1'").arg(SYSLOG_TYPE_ALM));
    xSysLog::GetModel()->select();
    // 初始化界面报警状态显示
    for (int id=0; id<ALARM_MAX; id++)
        slot_AlmChg(id, pModbus->GetAlmByPos(id));
    // 连接报警状态改变信号槽
    connect(pModbus, SIGNAL(signal_AlarmChange(qint16, quint32)), this, SLOT(slot_AlmChg(qint16, quint32)));
    // 显示界面
    retranslateUi();
//	show();
	return true;
}

bool FormAlarm::ExitForm(void)
{
    // 取消连接报警状态改变信号槽
    disconnect(pModbus, SIGNAL(signal_AlarmChange(qint16, quint32)), this, SLOT(slot_AlmChg(qint16, quint32)));
    // 隐藏界面
//	hide();
	return true;
}

// 显示报警信息
void FormAlarm::displayAlarm(int id, uint32_t code)
{
    if ((code & 0xffff) != ALMRES_NO_ALARM)
		pAlmPos->button(id)->setIcon(QIcon(":/img/32X32/LampActive.png"));
	else
		pAlmPos->button(id)->setIcon(QIcon(":/img/32X32/LampInactive.png"));
	if (pAlmPos->button(id)->isChecked())
    {
        ui->labelAlarmInf->setText(xStringResource::GetAlarm(code));
        if(code & 0xffff0000)
            ui->labelAlarmSolution->setText(xStringResource::GetAlarm(code));
        else
        ui->labelAlarmSolution->setText(xStringResource::GetAlarmSolution(code));
    }
}

// 报警位置单选框点击信号槽
void FormAlarm::AlmPosClicked(int id)
{
    slot_AlmChg(id, pModbus->GetAlmByPos(id));
}
// 报警状态改变信号槽
void FormAlarm::slot_AlmChg(qint16 idx, quint32 alarm)
{
    displayAlarm(idx, alarm);
}

void FormAlarm::ClearAlarm(void)
{
    if (pModbus->CommandClearAlarm() == SENDMSG_RET_ACK)
    {
        pModbus->CommandClearAlarm();
        // 写入系统日志
        xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_CLEAR_ALARM);
        xSysLog::SaveChange();
    }
}
void FormAlarm::displayAlarmInfo(QModelIndex idx)
{
    QModelIndex curIdx = ui->viewRecords->currentIndex();
    QModelIndex curValue = curIdx.sibling(curIdx.row(), xSysLog::logValue);
    QString strAlarm = xSysLog::GetModel()->data(curValue, Qt::DisplayRole).toString();
    ui->labelDetail->setText(strAlarm);
    ui->labelSolve->setText(xStringResource::GetAlarmSolution(strAlarm.mid(1, 3).toInt()));
}
