#include <stdio.h>
#include "cmbprotocol.h"
#include "xsystemlog.h"
#include "xpermissions.h"
#include "dialogframe.h"
#include "xstringresource.h"
#include "xmessagebox.h"
#include "driver/xioport.h"
#include "formauto.h"
#include "alfamodel.h"
#include "ui_formauto.h"

#define PROCESS_1   0
#define PROCESS_2   1
#define PROCESS_3   2

extern DialogFrame *pDialogMain;


FormAuto::FormAuto(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormAuto), pgmModel(false)
{
	ui->setupUi(this);
	pModbus = modbus;
#if SELECT_SWITCH_USE
	ui->BtnManualStop->setVisible(false);
//	ui->BtnAutoRun->setVisible(false);
#endif
	// 设置数据源
	ui->tablePgm->setModel(&pgmModel);
    ui->tablePgm->setColumnWidth(0, 80);
	ui->tablePgm->setColumnWidth(1, 40);
//	ui->tablePgm->setColumnWidth(2, 385);
//	connect(this, SIGNAL(BtnManualClick()), parent, SLOT(BtnManualClick()));
//    ui->tablePgm->setSelectionBehavior(QAbstractItemView::SelectItems); // 选择模式？？？？？？？？？？？
	// 安装事件过滤器
	QObjectList list = ui->tablePgm->children();
	for (int i = 0; i < list.count(); i ++)
	{
		if (list.at(i)->objectName() == QString("qt_scrollarea_viewport"))
		{
			list.at(i)->installEventFilter(this);
		}
	}
    // 进程切换
    pBtnProcess = new QButtonGroup;
    pBtnProcess->addButton(ui->BtnProcess1, PROCESS_1);
    pBtnProcess->addButton(ui->BtnProcess2, PROCESS_2);
    pBtnProcess->addButton(ui->BtnProcess3, PROCESS_3);

#if (MULPROC_ENABLE == 0)
    ui->BtnProcess1->setVisible(false);
    ui->BtnProcess2->setVisible(false);
    ui->BtnProcess3->setVisible(false);
#endif

#if FACTORY == FA_SINROBOT_JC
    ui->LedEmo->setVisible(false);
    ui->LedEmc->setVisible(false);
    ui->LedMaf->setVisible(false);
#endif

}

FormAuto::~FormAuto()
{
	delete ui;
    delete pBtnProcess;
}

bool FormAuto::eventFilter(QObject *obj, QEvent *event)
{
	if (ui->checkBoxFllow->isChecked() == false)
		return QWidget::eventFilter(obj, event);
	if ((event->type() == QEvent::MouseButtonPress) || (event->type() == QEvent::MouseButtonRelease) || (event->type() == QEvent::MouseMove))
		return true;
	return QWidget::eventFilter(obj, event);
}

void FormAuto::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
        setBtnState(pModbus->GetSysState(), pModbus->GetRunState());
		break;
	default:
		break;
	}
}

bool FormAuto::EnterForm(void)
{
    int i;
#if FACTORY == FA_SINROBOT_JC
    ui->LedMop->setText(tr("加工完成"));
    ui->LedMcp->setText(tr("加工启动"));
    ui->LedSdm->setText(tr("防护门"));
#endif
    // 设置按钮使能
    ui->BtnProcess2->setEnabled(pModbus->GetProcUse(1));
    ui->BtnProcess3->setEnabled(pModbus->GetProcUse(2));
    ui->BtnProcess2->setVisible(pModbus->GetProcUse(1));
    ui->BtnProcess3->setVisible(pModbus->GetProcUse(2));
    ui->BtnProcess1->setVisible(pModbus->GetProcUse(1)||pModbus->GetProcUse(2));

//    if (pModbus->GetProcUse(1)||pModbus->GetProcUse(2))
//        ui->tablePgm->setGeometry(1, 75, 798, 611);
//    else
//        ui->tablePgm->setGeometry(1, 1, 798, 683);
    // 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return false;
	}
	// 检查用户权限
	if (xPermissions::GetPermissions(PER_AUTO_OPR) == false)
	{
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (pDialogMain)
            if (pDialogMain->ScreenSaverUserManager() == 0)
                return false;
	}
	// 如果没有载入程序文件则警告并退出
    if (pModbus->IsALFAMode())
    {
        if (pModbus->GetAlfaPgmName().isEmpty())
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("没有载入程序文件，不能自动运行！"));
            return false;
        }
        // 如果加载程序文件出错则警告并退出
        AlfaModel alfa;
        if (alfa.LoadProgram(pModbus->GetAlfaPgmName()) == false)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("装载程序文件出错，不能修改伺服全局速度设置！"));
            return false;
        }
        if (alfa.CreateRunPgm() < 0)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("向导生成运行程序出错！"));
            return false;
        }
        if (pgmModel.LoadProgram(alfa.GetRunPgmName()) == false)
        {
            if (pgmModel.GetLastError() == LOADERROR_VERSION)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取程序版本出错，无法装载程序文件！"));
                return false;
            }
            if (pgmModel.GetLastError() == LOADERROR_FORMAT)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取文件格式出错，无法装载程序文件！"));
                return false;
            }
            if (pgmModel.GetLastError() == LOADERROR_FILE)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取程序文件出错，无法装载程序文件！"));
                return false;
            }
        }
    }
    else
    {
        if (pModbus->GetCurPgmName().isEmpty())
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("没有载入程序文件，不能自动运行！"));
            return false;
        }
        // 如果加载程序文件出错则警告并退出
        if (pgmModel.LoadProgram(pModbus->GetCurPgmName(true)) == false)
        {
            if (pgmModel.GetLastError() == LOADERROR_VERSION)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取程序版本出错，无法装载程序文件！"));
                return false;
            }
            if (pgmModel.GetLastError() == LOADERROR_FORMAT)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取文件格式出错，无法装载程序文件！"));
                return false;
            }
            if (pgmModel.GetLastError() == LOADERROR_FILE)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("读取程序文件出错，无法装载程序文件！"));
                return false;
            }
        }
    }
	if (pgmModel.CheckProgram() == false)
	{
		xMessageBox::DoWarning(tr("检查程序"), pgmModel.GetErrString()+tr(",\n请进入教导画面修改程序！"));
		return false;
	}
    // 清除计数器
    CurPgmFile = pModbus->GetCurPgmName(true);
    if (CurPgmFile.compare(CurPgmFileBak))
    {
        quint32 paras[MAX_CODES];
        for (i=0; i<MAX_USER_VARS;)
        {
            int firstidx = i;
            int count = pgmModel.GenerateVar(firstidx, paras, true);
            if (count)
            {
                pModbus->WriteUserVar(paras, firstidx, count);
                i = count+firstidx;
            }
            else
            {
                break;
            }
        }
        CurPgmFileBak = CurPgmFile;
    }
#if ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_YIDAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE))
    ui->groupBoxImm->setTitle(tr("压铸机信号"));
#elif FACTORY == FA_SINROBOT_JC
    ui->groupBoxImm->setTitle(tr("机床信号"));
#else
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
        ui->groupBoxImm->setTitle(tr("压铸机信号"));
    else
        ui->groupBoxImm->setTitle(tr("注塑机信号"));
#endif
    SetProcBtnState(pgmModel.GetCurProcess());
//    for (i=0; i<MAX_PROCESS; i++)
//        curpc[i] = 0;
	// 初始化界面显示状态
    setBtnState(pModbus->GetSysState(), pModbus->GetRunState());
    SetInputImm(true);
    SetOutputImm(true);
	ui->disSum->setText(QString::number(pModbus->GetPrdSum()));
	ui->disPlan->setText(QString::number(pModbus->GetPrdPlan()));
	ui->disPeriod->setText(QString::number(pModbus->GetPeriod(), 'f', 1) + "s");
    ui->disInmoldTime->setText(QString::number(pModbus->GetInmoldTime(), 'f', 1) + "s");
    setFollow(ui->checkBoxFllow->isChecked());
    pgmPcChange(pModbus->GetPgmPc(), pgmModel.GetCurProcess(), true);
    // 连接信号槽
	connect(pModbus, SIGNAL(signal_SysStateChange(uint16_t)), this, SLOT(sysStateChanged(uint16_t)));
	connect(pModbus, SIGNAL(signal_RunStateChange(uint16_t)), this, SLOT(runStateChanged(uint16_t)));
    connect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(inputImm()));
    connect(pModbus, SIGNAL(signal_OutputChange()), this, SLOT(outputImm()));
	connect(pModbus, SIGNAL(signal_TotalMoldChange(uint32_t)), this, SLOT(prdSumChange(uint32_t)));
	connect(pModbus, SIGNAL(signal_TotalPlanChange(uint32_t)), this, SLOT(prdPlanChange(uint32_t)));
    connect(pModbus, SIGNAL(signal_PeriodTimeChange(uint32_t, uint16_t)), this, SLOT(periodChange(uint32_t, uint16_t)));
    connect(pModbus, SIGNAL(signal_PC_Pointer(uint16_t, uint16_t)), this, SLOT(pgmPcChange(uint16_t, uint16_t)));
    connect(pModbus, SIGNAL(signal_InmoldTimeChange(uint32_t, uint16_t)), this, SLOT(inmoldTimeChange(uint32_t, uint16_t)));


    connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    connect(pBtnProcess, SIGNAL(buttonClicked(int)), this, SLOT(ProcBtnStateChanged(int)));
    // 显示界面
	setPermissions();
//    show();
    return true;
}

bool FormAuto::ExitForm(void)
{
	// 断开信号槽
	disconnect(pModbus, SIGNAL(signal_SysStateChange(uint16_t)), this, SLOT(sysStateChanged(uint16_t)));
	disconnect(pModbus, SIGNAL(signal_RunStateChange(uint16_t)), this, SLOT(runStateChanged(uint16_t)));
    disconnect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(inputImm()));
    disconnect(pModbus, SIGNAL(signal_OutputChange()), this, SLOT(outputImm()));
	disconnect(pModbus, SIGNAL(signal_TotalMoldChange(uint32_t)), this, SLOT(prdSumChange(uint32_t)));
	disconnect(pModbus, SIGNAL(signal_TotalPlanChange(uint32_t)), this, SLOT(prdPlanChange(uint32_t)));
    disconnect(pModbus, SIGNAL(signal_PeriodTimeChange(uint32_t, uint16_t)), this, SLOT(periodChange(uint32_t, uint16_t)));
    disconnect(pModbus, SIGNAL(signal_PC_Pointer(uint16_t, uint16_t)), this, SLOT(pgmPcChange(uint16_t, uint16_t)));
    disconnect(pModbus, SIGNAL(signal_InmoldTimeChange(uint32_t, uint16_t)), this, SLOT(inmoldTimeChange(uint32_t, uint16_t)));
    disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    disconnect(pBtnProcess, SIGNAL(buttonClicked(int)), this, SLOT(ProcBtnStateChanged(int)));
    // 隐藏界面
//	hide();
	return true;
}

// 根据当前用户权限设置界面
void FormAuto::setPermissions(void)
{
	ui->frameMainArea->setEnabled(xPermissions::GetPermissions(PER_AUTO_OPR));
}

// 设置界面控制按钮状态
void FormAuto::setBtnState(uint16_t sysState, uint16_t runState)
{
	if (sysState == SYS_STATE_MANUAL)
	{
		// 手动状态
		ui->BtnManualStop->setText(xStringResource::GetString(STRRES_MANUAL));
		ui->BtnManualStop->setEnabled(false);
        ui->BtnManualStop->setFlat(false);
#if SELECT_SWITCH_USE
		ui->BtnAutoRun->setText(xStringResource::GetString(STRRES_RUN));
		ui->BtnAutoRun->setEnabled(false);
#else
		ui->BtnAutoRun->setText(xStringResource::GetString(STRRES_AUTO));
		ui->BtnAutoRun->setEnabled(true);
#endif
		ui->BtnPeriod->setEnabled(false);
		ui->BtnStep->setEnabled(false);
	}
	else if (sysState == SYS_STATE_AUTO)
	{
		if (runState == RUN_STATE_RUN)
		{
			// 自动运行状态(全自动/单周期/单步)
			ui->BtnManualStop->setText(xStringResource::GetString(STRRES_STOP));
			ui->BtnManualStop->setEnabled(true);
            ui->BtnManualStop->setFlat(true);
            ui->BtnAutoRun->setText(xStringResource::GetString(STRRES_RUN));
			ui->BtnAutoRun->setEnabled(false);
			ui->BtnPeriod->setEnabled(false);
			ui->BtnStep->setEnabled(false);
		}
		else
		{
			// 自动待机状态
			ui->BtnManualStop->setText(xStringResource::GetString(STRRES_MANUAL));
			ui->BtnManualStop->setEnabled(true);
            ui->BtnManualStop->setFlat(true);
            ui->BtnAutoRun->setText(xStringResource::GetString(STRRES_RUN));
			ui->BtnAutoRun->setEnabled(true);
			ui->BtnPeriod->setEnabled(true);
			ui->BtnStep->setEnabled(true);
		}
	}
}
// 设置界面注塑机输入信号状态
void FormAuto::SetInputImm(bool init)
{
	// 安全设备
	if ((xIoPort::GetIn(IMM_VAR_IN_SAFE) != ui->LedSdm->on()) || (init == true))
		ui->LedSdm->setOn(xIoPort::GetIn(IMM_VAR_IN_SAFE));
	// 关模完成
	if ((xIoPort::GetIn(IMM_VAR_IN_MCP) != ui->LedMcp->on()) || (init == true))
		ui->LedMcp->setOn(xIoPort::GetIn(IMM_VAR_IN_MCP));
	// 开模完成
	if ((xIoPort::GetIn(IMM_VAR_IN_MOP) != ui->LedMop->on()) || (init == true))
		ui->LedMop->setOn(xIoPort::GetIn(IMM_VAR_IN_MOP));
}
// 设置界面注塑机输出信号状态
void FormAuto::SetOutputImm(bool init)
{
	// 模区安全
	if ((xIoPort::GetOut(IMM_VAR_OUT_MAF) != ui->LedMaf->on()) || (init == true))
		ui->LedMaf->setOn(xIoPort::GetOut(IMM_VAR_OUT_MAF));
	// 允许关模
	if ((xIoPort::GetOut(IMM_VAR_OUT_EMC) != ui->LedEmc->on()) || (init == true))
		ui->LedEmc->setOn(xIoPort::GetOut(IMM_VAR_OUT_EMC));
	// 允许开模
	if ((xIoPort::GetOut(IMM_VAR_OUT_EMO) != ui->LedEmo->on()) || (init == true))
		ui->LedEmo->setOn(xIoPort::GetOut(IMM_VAR_OUT_EMO));
}

// 当前登录用户更改槽
void FormAuto::userChange(void)
{
	if (xPermissions::GetPermissions(PER_AUTO_OPR) == false)
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
	setPermissions();
}

// 系统状态改变信号槽
void FormAuto::sysStateChanged(uint16_t state)
{
    setBtnState(state, pModbus->GetRunState());
}

// 运行状态改变信号槽
void FormAuto::runStateChanged(uint16_t state)
{
    setBtnState(pModbus->GetSysState(), state);
}

// 设置跟随状态
void FormAuto::setFollow(bool follow)
{
	if (follow)
	{
		// 跟随
		ui->tablePgm->setSelectionMode(QAbstractItemView::MultiSelection);
	}
	else
	{
		// 不跟随
		ui->tablePgm->setSelectionMode(QAbstractItemView::SingleSelection);
		ui->tablePgm->selectionModel()->clearSelection();
	}
}

// 手动/停止按钮信号槽
void FormAuto::BtnManualStop(void)
{
	if (pModbus->GetSysState() == SYS_STATE_MANUAL)
	{
		// 回到手动画面
//		emit BtnManualClick();
	}
	else if (pModbus->GetSysState() == SYS_STATE_AUTO)
	{
		if (pModbus->GetRunState() == RUN_STATE_PAUSE)
		{
#if SELECT_SWITCH_USE == 0
			// 自动待机 -> 手动
			if (pModbus->SetSysState(SYS_STATE_MANUAL) == SENDMSG_RET_ACK)
			{
				// 写入系统日志
				xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_WAIT2MANUL);
				xSysLog::SaveChange();
			}
#endif
		}
		else
		{
			// 自动运行/单周期运行/单步运行 -> 自动待机
//			if (pModbus->SetRunType(RUN_TYPE_SINGLE) == SENDMSG_RET_ACK)
            if (pModbus->SetRunState(RUN_STATE_PAUSE) == SENDMSG_RET_ACK)
			{
				if (pModbus->GetRunType() == RUN_TYPE_LOOP)
				{
                    xMessageBox::DoWaiting(tr("系统提示"), tr("正在停止系统全自动运行，请稍候..."));
					xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_RUN2WAIT);
				}
				else if (pModbus->GetRunType() == RUN_TYPE_SINGLE)
				{
                    xMessageBox::DoWaiting(tr("系统提示"), tr("正在停止系统单周期运行，请稍候..."));
					xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_PERIOD2WAIT);
				}
				else if (pModbus->GetRunType() == RUN_TYPE_STEP)
				{
                    xMessageBox::DoWaiting(tr("系统提示"), tr("正在停止系统单步运行，请稍候..."));
					xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_STEP2WAIT);
				}
				// 写入系统日志
				xSysLog::SaveChange();
			}
		}
	}
}
// 自动/运行按钮信号槽
void FormAuto::BtnAutoRunClick(void)
{
/*
    int i;
    // 生成程序文件对应的机器代码并上传到主控模块
    quint32 paras[MAX_CODES];

    qDebug() << "-----------------------------------------";
    for (i=0; i<MAX_USER_VARS;)
    {
        int firstidx = i;
        int count = pgmModel.GenerateVar(firstidx, paras, false);
        if (count)
        {
            qDebug() << "firstidx: " <<firstidx  << " count:" << count << " paras:" << paras[0];
            i = count+firstidx;
        }
        else
        {
            break;
        }
    }
    qDebug() << "-----------------------------------------";
    for (i=0; i<MAX_USER_VARS;)
    {
        int firstidx = i;
        int count = pgmModel.GenerateVar(firstidx, paras, true);
        if (count)
        {
            qDebug() << "firstidx: " <<firstidx  << " count:" << count << " paras:" << paras[0];
            i = count+firstidx;
        }
        else
        {
            break;
        }
    }
    qDebug() << "-----------------------------------------";
*/
    if (pModbus->GetSysState() == SYS_STATE_MANUAL)
	{
#if SELECT_SWITCH_USE == 0
		// 手动 -> 自动待机
		if(!TransAutoCode())
		{
			return;
		}
		if (pModbus->SetSysState(SYS_STATE_AUTO) != SENDMSG_RET_ACK)
			return;
		// 写入系统日志
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL2AUTO);
		xSysLog::SaveChange();
#endif
	}
	else if (pModbus->GetSysState() == SYS_STATE_AUTO)
	{
		if (pModbus->GetRunState() == RUN_STATE_PAUSE)
		{
			// 自动待机 -> 自动运行
			if (pModbus->SetRunType(RUN_TYPE_LOOP) != SENDMSG_RET_ACK)
				return;
			if (pModbus->SetRunState() != SENDMSG_RET_ACK)
				return;
			// 写入系统日志
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_WAIT2RUN);
			xSysLog::SaveChange();
		}
	}
}
// 单周期运行按钮信号槽
void FormAuto::BtnPeriodClick(void)
{
	if (pModbus->GetSysState() != SYS_STATE_AUTO)
		return;
	if (pModbus->GetRunState() != RUN_STATE_PAUSE)
		return;
	// 自动待机 -> 单周期运行
	if (pModbus->SetRunType(RUN_TYPE_SINGLE) != SENDMSG_RET_ACK)
		return;
	if (pModbus->SetRunState() != SENDMSG_RET_ACK)
		return;
	// 写入系统日志
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_WAIT2PERIOD);
	xSysLog::SaveChange();
}
// 单步运行按钮信号槽
void FormAuto::BtnStepClick(void)
{
	if (pModbus->GetSysState() != SYS_STATE_AUTO)
		return;
	if (pModbus->GetRunState() != RUN_STATE_PAUSE)
		return;
	// 自动待机 -> 单步运行
	if (pModbus->SetRunType(RUN_TYPE_STEP) != SENDMSG_RET_ACK)
		return;
	if (pModbus->SetRunState() != SENDMSG_RET_ACK)
		return;
	// 写入系统日志
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_WAIT2STEP);
	xSysLog::SaveChange();
}
// IO信号槽
void FormAuto::inputImm(void)
{
    SetInputImm(false);
}
void FormAuto::outputImm(void)
{
    SetOutputImm(false);
}

// 生产统计信息改变信号槽
void FormAuto::prdSumChange(uint32_t input)
{
	ui->disSum->setText(QString::number(input));
}
void FormAuto::prdPlanChange(uint32_t input)
{
	ui->disPlan->setText(QString::number(input));
}
void FormAuto::periodChange(uint32_t input, uint16_t idx)
{
    if (idx == pgmModel.GetCurProcess())
#if TIME_BASE == 10
    ui->disPeriod->setText(QString::number((double)input / (1000.0/TIME_BASE), 'f', 2) + "s");
#else
    ui->disPeriod->setText(QString::number((double)input / (1000.0/TIME_BASE), 'f', 1) + "s");
#endif
}
void FormAuto::inmoldTimeChange(uint32_t input, uint16_t idx)
{
    if (idx == pgmModel.GetCurProcess())
#if TIME_BASE == 10
    ui->disInmoldTime->setText(QString::number((double)input / (1000.0/TIME_BASE), 'f', 2) + "s");
#else
    ui->disInmoldTime->setText(QString::number((double)input / (1000.0/TIME_BASE), 'f', 1) + "s");
#endif
}
void FormAuto::pgmPcChange(uint16_t pc, uint16_t idx, bool init)
{
    if (idx<MAX_PROCESS) curpc[idx] = pc;
    if (idx == pgmModel.GetCurProcess())
    {
        if (init == false)
        {
            if (ui->checkBoxFllow->isChecked() == false)
                return;
            if (pModbus->GetSysState() != SYS_STATE_AUTO)
                return;
        }
        ui->tablePgm->selectionModel()->clearSelection();
        quint16 i;
        quint16 endpos;
        quint16 beginpos = endpos = pgmModel.GetPosByPcPointer(pc);
        quint8 code = pgmModel.GetCode(beginpos);
//	if (pos == 0)
//	{
//		ui->tablePgm->selectRow(pos);
//	}
//    else
        if ((code == CODE_WAIT) || (code == CODE_POS) || (code == CODE_EXTPOS) || (code == CODE_DELAY) ||(code == CODE_LOOP) ||(code == CODE_PAPER) || (code == VCODE_VACUUM) || (code == CODE_VACUUM) || (code == CODE_INTERP) ||
                (code == CODE_SPEED) || (code == CODE_PROARM) || (code == CODE_RUNARM) || (code == CODE_IMM) || (code == CODE_EXT_IN) || (code == CODE_EXT_OUT) || (code == CODE_POWER) || (code == CODE_LOOPFREE) ||
            (code == CODE_MATRIX) || (code == CODE_TEND) || (code == CODE_TBEGIN) || (code == CODE_FREEPOS) || (code == CODE_CUSTOMER) || (pModbus->GetRunType()==RUN_TYPE_STEP) || (code == CODE_CIRCLE) || (code == CODE_MEXTOUT) ||
			 (code == CODE_VISION) || (pModbus->GetRunType()==RUN_TYPE_SINGLE) || (code == CODE_IF))
        {
            quint8 flag = pgmModel.GetFlag(beginpos);
            //if (code == CODE_CBEGIN)
            if (flag & FLAG_COMBINE)
                endpos = pgmModel.GetCombineEndPos(beginpos);
//        for (i = beginpos; i <= pos; i++)
//			ui->tablePgm->selectRow(i);
            for (i = beginpos;i <= endpos; i++)
                ui->tablePgm->selectRow(i);
        }
        ui->tablePgm->scrollTo(ui->tablePgm->currentIndex());
    }
}
extern quint16 globlecodes[MAX_CODES];
extern quint32 globleparas[MAX_CODES];

// 发送全自动代码
bool FormAuto::TransAutoCode()
{
    bool ClearInq = false;
    int i;
    int procid;
	// 生成程序文件对应的机器代码并上传到主控模块
	quint32 codeCnt;
//    quint16 codes[MAX_CODES];
//	quint32 paras[MAX_CODES];

    // 清除循环定位计数
    if (pgmModel.Inquire())
    {
        if (xMessageBox::DoQuestion(tr("系统提示"), tr("是否要初始化矩阵、循环定位、扩展输入或扩展输出计数？")) == XMSG_RET_YES)
        {
            ClearInq = true;
        }
    }

    for (i=0; i<MAX_USER_VARS;)
    {
        int firstidx = i;
        int count = pgmModel.GenerateVar(firstidx, globleparas, ClearInq);
        if (count)
        {
//            int j;
//            qDebug() << "firstidx: " <<firstidx  << " count:" << count << " para:";
//            for (j=0; j<count; j++)
//            {
//                qDebug() << paras[j];
//            }
            if (pModbus->WriteUserVar(globleparas, firstidx, count) != SENDMSG_RET_ACK)
            {
//                xMessageBox::DoWarning(tr("系统警告"), tr("是否要清除循环、矩阵和扩展输入、输出的计数？"));
                return false;
            }
            i = count+firstidx;
        }
        else
        {
            break;
        }
    }
    // 生成程序文件机器代码
    for (procid=0; procid<MAX_PROCESS; procid++)
    {
        if (pModbus->GetProcUse(procid))
        {
            codeCnt = pgmModel.GenerateCodes(procid, globlecodes, globleparas);
            // 上传机器代码
            if (pModbus->WriteCodes(globlecodes, procid*MAX_CODES, codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件指令到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return false;
            }
            // 上传机器代码参数
            if (pModbus->WriteCodeParas(globleparas, procid*MAX_CODES, codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return false;
            }
        }
    }

	// 更新主控模块当前程序
    if (pModbus->CommandUpdate(CMD_UPDATE_PARA1|CMD_UPDATE_PARA2|CMD_UPDATE_PARA3) != SENDMSG_RET_ACK)
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("主控模块更新当前程序失败，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
		return false;
	}
	return true;
}

void FormAuto::ProcBtnStateChanged(int idx)
{
    if (idx<MAX_PROCESS)
    {
        pgmModel.SetCurProcess(idx);
        SetProcBtnState(idx);
        if (ui->checkBoxFllow->isChecked())
        {
            pgmPcChange(curpc[idx], idx);
        }
    }
}
void FormAuto::SetProcBtnState(int idx)
{
    if (idx < MAX_PROCESS)
    {
        if (idx == PROCESS_1)
        {
            ui->BtnProcess1->setOn(true);
            ui->BtnProcess2->setOn(false);
            ui->BtnProcess3->setOn(false);
        }
        if (idx == PROCESS_2)
        {
            ui->BtnProcess1->setOn(false);
            ui->BtnProcess2->setOn(true);
            ui->BtnProcess3->setOn(false);
        }
        if (idx == PROCESS_3)
        {
            ui->BtnProcess1->setOn(false);
            ui->BtnProcess2->setOn(false);
            ui->BtnProcess3->setOn(true);
        }
    }
}
