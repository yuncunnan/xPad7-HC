#include <QModelIndex>
#include <QKeyEvent>
#include "xconfig.h"
#include "xioport.h"
#include "formteach.h"
#include "ui_formteach.h"
#include "teachtablemodel.h"
#include "dialogselectaction.h"
//#include "dialogspeed.h"
#include "xmessagebox.h"
#include "xsystemlog.h"
#include "xstringresource.h"
#include "xKeypad.h"
#include "dialogkeyboard.h"
#include "dialogparaedit.h"
#include <QDebug>
// *********************************************
#include "formactpos.h"
#include "formactextpos.h"
#include "formactextin.h"
#include "formactextout.h"
#include "formactpro.h"
#include "formactrun.h"
#include "formactimm.h"
#include "formactpaper.h"
#include "formactloopfree.h"
#include "formactloopmatrix.h"
#include "formactdelay.h"
#include "formactfor.h"
#include "formactif.h"
#include "formactnull.h"
#include "formactwait.h"
#include "formactoperate.h"
#include "formvactvacuum.h"
#include "formactvacuum.h"
#include "formactpath.h"
#include "formactspeed.h"
#include "formactsingleloop.h"
#include "formactsingleloopfree.h"
#include "formactinterp.h"
#include "formactpower.h"
#include "formactcircle.h"
#include "formactvision.h"
#include "formactmextout.h"
#include "formactassist.h"
// *********************************************
#include "xmlmodelitem.h"
#include "codedelay.h"
#include "codeparm.h"
#include "coderarm.h"
#include "codeend.h"
#include "codeendif.h"
#include "codeendfor.h"
#include "codeelse.h"
#include "codebreak.h"
#include "codeoperator.h"
#include "codeif.h"
#include "codefor.h"
#include "codewait.h"
#include "codeimm.h"
#include "codepos.h"
#include "codeextpos.h"
#include "codeextin.h"
#include "codeextout.h"
#include "codepaper.h"
#include "codeloopfree.h"
#include "codeloopmatrix.h"
#include "codespeed.h"
#include "vcodevacuum.h"
#include "codevacuum.h"
#include "codetbegin.h"
#include "codetend.h"
#include "codesingleloop.h"
#include "codesingleloopfree.h"
#include "codeinterp.h"
#include "codepower.h"
#include "codecircle.h"
#include "codevision.h"
#include "codemextout.h"
#include "codeassist.h"
// *********************************************
#include "formbtnextpos.h"
#include "formbtnpos.h"
#include "formbtnimm.h"
#include "formbtnvacuum.h"
#include "formbtnwait.h"
#include "formbtnmextout.h"
#include "formbtnassist.h"
#include "formbtnpro.h"
#include "formbtnrun.h"
#include "formbtnquick.h"
// *********************************************
#define PROCESS_1   0
#define PROCESS_2   1
#define PROCESS_3   2

FormTeach::FormTeach(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormTeach),
    m_teachmodel(new TeachTableModel(false)),
	m_actdlg(new DialogSelectAction())
{
	ui->setupUi(this);
	pModbus = modbus;
	// ********************************************
    // 进程
    pBtnProcess = new QButtonGroup;
    pBtnProcess->addButton(ui->BtnProcess1, PROCESS_1);
    pBtnProcess->addButton(ui->BtnProcess2, PROCESS_2);
    pBtnProcess->addButton(ui->BtnProcess3, PROCESS_3);
    // ********************************************

    m_dialogparaedit = new DialogParaEdit();
    // 伺服单轴指令参数
    m_actextpos = new FormActExtPos(m_dialogparaedit);
    m_actextpos->hide();
    m_actpos = new FormActPos(m_dialogparaedit);
    m_actpos->hide();
    // 伺服插补指令参数
    m_actinterp = new FormActInterp(m_dialogparaedit);
    m_actinterp->hide();
    // 伺服电源指令参数
    m_actpower = new FormActPower(m_dialogparaedit);
    m_actpower->hide();
    // 扩展输入指令参数
    m_actextin = new FormActExtIn(m_dialogparaedit);
	m_actextin->hide();
	// 扩展输出指令参数
    m_actextout = new FormActExtOut(modbus, m_dialogparaedit);
	m_actextout->hide();
    // 多扩展输出指令参数
    m_actmextout = new FormActMExtOut(m_dialogparaedit);
    m_actmextout->hide();
	// 正臂动作指令参数
    m_actpro = new FormActPro(modbus, m_dialogparaedit);
	m_actpro->hide();
	// 副臂动作指令参数
    m_actrun = new FormActRun(modbus, m_dialogparaedit);
	m_actrun->hide();
	// 塑机动作指令参数
    m_actimm = new FormActIMM(m_dialogparaedit);
	m_actimm->hide();
	// 取纸指令参数
    m_actpaper = new FormActPaper(m_dialogparaedit);
	m_actpaper->hide();
	// 正臂循环定位指令参数
    m_actloopfree = new FormActLoopFree(m_dialogparaedit);
	m_actloopfree->hide();
    // 正臂堆叠指令参数
    m_actloopmatrix = new FormActLoopMatrix(m_dialogparaedit);
    m_actloopmatrix->hide();
    // 单轴循环定位指令参数
    m_actsingleloop = new FormActSingleLoop(m_dialogparaedit);
    m_actsingleloop->hide();
    // 单轴循环自由定位指令参数
    m_actsingleloopfree = new FormActSingleLoopFree(m_dialogparaedit);
    m_actsingleloopfree->hide();
    // 延时动作指令参数
    m_actdelay = new FormActDelay(m_dialogparaedit);
	m_actdelay->hide();
	// 循环指令参数
    m_actfor = new FormActFor(m_dialogparaedit);
	m_actfor->hide();
	// 条件指令参数
    m_actif = new FormActIf(m_dialogparaedit);
	m_actif->hide();
	// 路径指令参数
    m_actpath = new FormActPath(m_dialogparaedit);
	m_actpath->hide();
	// 等待信号指令参数
    m_actwait = new FormActWait(m_dialogparaedit);
	m_actwait->hide();
    // 伺服速度指令参数
    m_actspeed = new FormActSpeed(m_dialogparaedit);
    m_actspeed->hide();
    // 用户变量加减指令参数
    m_actoperator = new FormActOperate(m_dialogparaedit);
	m_actoperator->hide();
	// 治具指令
    m_vactvacuum = new FormVActVacuum(modbus, m_dialogparaedit);
    m_vactvacuum->hide();
    m_actvacuum = new FormActVacuum(modbus, m_dialogparaedit);
	m_actvacuum->hide();
    // 无参数动作指令参数
    m_actnull = new FormActNull(m_dialogparaedit);
    m_actnull->hide();
    // 喷雾指令参数
    m_actcircle = new FormActCircle(m_dialogparaedit);
    m_actcircle->hide();
    // 视觉指令参数
    m_actvision = new FormActVision(m_dialogparaedit);
    m_actvision->hide();
    // 辅助设备参数
    m_actassist = new FormActAssist(modbus, m_dialogparaedit);
    m_actassist->hide();
    ///////////////////////////////////////////////
    // 当前选中的指令
    currentCode = 0;
    // 快速教导提示
    m_haswarning = false;

    m_btnextpos = new FormBtnExtPos(ui->widgetPara);
    m_btnextpos->hide();
    m_btnpos = new FormBtnPos(ui->widgetPara);
    m_btnpos->hide();
    m_btnimm = new FormBtnIMM(ui->widgetPara);
    m_btnimm->hide();
    m_btnvacuum = new FormBtnVacuum(ui->widgetPara);
    m_btnvacuum->hide();
    m_btnwait = new FormBtnWait(ui->widgetPara);
    m_btnwait->hide();
    m_btnextout = new FormBtnMExtOut(ui->widgetPara);
    m_btnextout->hide();
    m_btnassist = new FormBtnAssist(ui->widgetPara);
    m_btnassist->hide();
    m_btnpro =new FormBtnPro(modbus, ui->widgetPara);
    m_btnpro->hide();
    m_btnrun =new FormBtnRun(modbus, ui->widgetPara);
    m_btnrun->hide();
    m_btnquick = new FormBtnQuick(modbus ,ui->widgetPara);
    m_btnquick->hide();
    ///////////////////////////////////////////////
    ui->BtnPos->setStyleSheet("text-align:left");
    ui->BtnPro->setStyleSheet("text-align:left");
    ui->BtnRun->setStyleSheet("text-align:left");
    ui->BtnMatrix->setStyleSheet("text-align:left");
    ui->BtnMExtOut->setStyleSheet("text-align:left");
    ui->BtnIMM->setStyleSheet("text-align:left");
    ui->BtnVacuum->setStyleSheet("text-align:left");
    ui->BtnWait->setStyleSheet("text-align:left");
    ui->BtnOther->setStyleSheet("text-align:left");
//    ui->BtnAssist->setStyleSheet("text-align:left");
#if (MULPROC_ENABLE == 0)
    ui->BtnProcess1->setVisible(false);
    ui->BtnProcess2->setVisible(false);
    ui->BtnProcess3->setVisible(false);
#endif

	ui->tableView_teach->setModel(m_teachmodel);
    ui->tableView_teach->setColumnWidth(0, 80);
	ui->tableView_teach->setColumnWidth(1, 40);
    ui->tableView_teach->setEditTriggers(QTableView::NoEditTriggers);
#if IS_XEDITOR
    dialogedit = new Dialogedit(this);
    ui->tableView_teach->setItemDelegate(dialogedit);
    ui->tableView_teach->setEditTriggers(QTableView::DoubleClicked);
#endif
    connect(m_teachmodel, SIGNAL(GetWidget(int, QWidget*&)), this, SLOT(GetWidget(int, QWidget*&)));
}

FormTeach::~FormTeach()
{
	delete ui;
    delete pBtnProcess;
	delete m_actpos;
    delete m_actextpos;
	delete m_actextin;
	delete m_actextout;
	delete m_actpro;
	delete m_actrun;
	delete m_actimm;
	delete m_actpaper;
	delete m_actloopfree;
	delete m_actloopmatrix;
	delete m_actdelay;
	delete m_actfor;
	delete m_actif;
	delete m_actpath;
	delete m_actnull;
	delete m_actwait;
    delete m_actspeed;
	delete m_actoperator;
	delete m_actdlg;
    delete m_vactvacuum;
    delete m_actvacuum;
    delete m_actsingleloop;
    delete m_actsingleloopfree;
    delete m_actinterp;
    delete m_actpower;
    delete m_actcircle;
    delete m_actmextout;
    delete m_actvision;
    delete m_actassist;

    delete m_btnextpos;
    delete m_btnpos;
    delete m_btnimm;
    delete m_btnvacuum;
    delete m_btnwait;
    delete m_btnextout;
    delete m_btnassist;
    delete m_btnpro;
    delete m_btnrun;
    delete m_btnquick;
}
void FormTeach::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

bool FormTeach::EnterForm(void)
{
    int i;
    if (pModbus->IsALFAMode())
    {
        xMessageBox::DoWarning(tr("系统警告"), tr("系统为简易模式，不能进入！"));
        return false;
    }
    // 设置按钮使能

    // 当进程二三不选择的时候进程一也不显示
    ui->BtnProcess2->setVisible(pModbus->GetProcUse(1));
    ui->BtnProcess3->setVisible(pModbus->GetProcUse(2));
    ui->BtnProcess1->setVisible(pModbus->GetProcUse(1)||pModbus->GetProcUse(2));
    // 设置按钮使能
    ui->BtnProcess2->setEnabled(pModbus->GetProcUse(1));
    ui->BtnProcess3->setEnabled(pModbus->GetProcUse(2));

    if (CMBProtocol::GetCurPgmName().isEmpty())
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("没有载入当前程序文件，不能教导程序！"));
		return false;
	}
    if (m_teachmodel->LoadProgram(CMBProtocol::GetCurPgmName(true)) == false)
	{
        if (m_teachmodel->GetLastError() == LOADERROR_VERSION)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("读取程序版本出错，无法装载程序文件！"));
            return false;
        }
        if (m_teachmodel->GetLastError() == LOADERROR_FORMAT)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("读取文件格式出错，无法装载程序文件！"));
            return false;
        }
        if (m_teachmodel->GetLastError() == LOADERROR_FILE)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("读取程序文件出错，无法装载程序文件！"));
            return false;
        }
	}
    SetProcBtnState(m_teachmodel->GetCurProcess());
    for (i=0; i<MAX_PROCESS; i++)
        curpos[i] = 0;
    qDebug()<<CMBProtocol::GetSysState()<<endl;
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
	{
        if (CMBProtocol::GetTemplateUse())
		{
			ui->BtnTechDelete->setVisible(false);
			ui->BtnTechMoveU->setVisible(false);
			ui->BtnTechMoveD->setVisible(false);
            ui->BtnTechSeparate->setVisible(false);
            ui->BtnTechCombine->setVisible(false);
            ui->BtnInsert->setEnabled(false);
            ui->BtnPos->setEnabled(false);
            ui->BtnPro->setEnabled(false);
            ui->BtnRun->setEnabled(false);
            ui->BtnMatrix->setEnabled(false);
            ui->BtnMExtOut->setEnabled(false);
            ui->BtnIMM->setEnabled(false);
            ui->BtnVacuum->setEnabled(false);
            ui->BtnWait->setEnabled(false);
            ui->BtnOther->setEnabled(false);
            ui->BtnQuick->setEnabled(false);
            ui->BtnMain->setEnabled(false);
            ui->BtnDelay->setEnabled(false);
        }
		else
		{
			ui->BtnTechDelete->setVisible(true);
			ui->BtnTechMoveU->setVisible(true);
			ui->BtnTechMoveD->setVisible(true);
            ui->BtnTechSeparate->setVisible(true);
            ui->BtnTechCombine->setVisible(true);
			if (m_teachmodel->GetItemCount() > 1)
				ui->BtnTechDelete->setEnabled(true);
			else
				ui->BtnTechDelete->setEnabled(false);
			ui->BtnTechMoveD->setEnabled(true);
			ui->BtnTechMoveU->setEnabled(true);
            ui->BtnTechSeparate->setEnabled(true);
            ui->BtnTechCombine->setEnabled(true);
            ui->BtnInsert->setEnabled(true);
            ui->BtnPos->setEnabled(true);
            ui->BtnPro->setEnabled(CMBProtocol::GetRotateUse());
            ui->BtnRun->setEnabled(CMBProtocol::GetRunnerUse() || CMBProtocol::GetRunRotateUse());
            ui->BtnMatrix->setEnabled(true);
            ui->BtnMExtOut->setEnabled(true);
            ui->BtnIMM->setEnabled(true);
            ui->BtnVacuum->setEnabled(true);
            ui->BtnWait->setEnabled(true);
            ui->BtnOther->setEnabled(true);
            ui->BtnQuick->setEnabled(true);
            ui->BtnMain->setEnabled(true);
            ui->BtnDelay->setEnabled(true);
            ui->BtnTest->setEnabled(true);
        }
	}
    else if (CMBProtocol::GetSysState() == SYS_STATE_AUTO)
	{
		// 自动模式
		ui->BtnTechDelete->setEnabled(false);
		ui->BtnTechMoveU->setEnabled(false);
		ui->BtnTechMoveD->setEnabled(false);
        ui->BtnTechSeparate->setEnabled(false);
        ui->BtnTechCombine->setEnabled(false);
        ui->BtnInsert->setEnabled(false);
        ui->BtnPos->setEnabled(false);
        ui->BtnPro->setEnabled(false);
        ui->BtnRun->setEnabled(false);
        ui->BtnMatrix->setEnabled(false);
        ui->BtnMExtOut->setEnabled(false);
        ui->BtnIMM->setEnabled(false);
        ui->BtnVacuum->setEnabled(false);
        ui->BtnWait->setEnabled(false);
        ui->BtnOther->setEnabled(false);
        ui->BtnQuick->setEnabled(false);
        ui->BtnMain->setEnabled(false);
        ui->BtnDelay->setEnabled(false);
        ui->BtnTest->setEnabled(false);
    }
    // 控件隐藏
//    ui->BtnAssist->setVisible(false);

    ui->tableView_teach->selectRow(0);
//	ChangeSelect(0);
	// 连接信号槽
	connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    connect(pBtnProcess, SIGNAL(buttonClicked(int)), this, SLOT(ProcBtnStateChanged(int)));
    // 显示界面
	setPermissions();
    // 记住上一个指令，进入教导页面重新进入一次，指令刷不刷新？
    clickBtnmenu();
    //测试按钮默认状态
    QModelIndex index;
    tableViewClicked(index);
//    if((pModbus->GetSysType() != ROBOTARM_TYPE_SIXSV_PAD_F3) && (pModbus->GetSysType() != ROBOTARM_TYPE_SIXSV_PAD_F4)
//             && (pModbus->GetSysType() != ROBOTARM_TYPE_SIXSV_PAD_F5) && (pModbus->GetSysType() != ROBOTARM_TYPE_SIXSV_PAD_F6)
//             && (pModbus->GetSysType() != ROBOTARM_TYPE_SIXSV_PAD_F7) && (pModbus->GetSysType() != ROBOTARM_TYPE_SIXSV_PAD_F8))
//        ui->BtnTest->setVisible(false);

//    show();
	return true;
}

bool FormTeach::ExitForm()
{
	if (xPermissions::GetPermissions(PER_TEACH) == true)
	{
		if (m_teachmodel->CheckProgram()==false)
		{
			xMessageBox::DoInformation(tr("检查程序"), m_teachmodel->GetErrString());
            ui->tableView_teach->selectRow(m_teachmodel->GetJumpBackPos());
            ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
			return false;
		}
		if (m_teachmodel->IsModified())
				SaveProgram();
			}
	// 取消信号槽连接
	disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    disconnect(pBtnProcess, SIGNAL(buttonClicked(int)), this, SLOT(ProcBtnStateChanged(int)));
    // 隐藏界面
//	hide();
	return true;
}
void FormTeach::GetWidget(int idx, QWidget*& widget)
{
	uchar code;
	code = idx;
	switch (code)
	{
	case CODE_IMM://		0x03	//塑机指令
        widget = (m_actimm);
        break;
    case CODE_EXT_IN://		0x04	//扩展指令
        widget = (m_actextin);
        break;
    case CODE_EXT_OUT://		0x04	//扩展指令
        widget = (m_actextout);
        break;
    case CODE_MEXTOUT://		0x04	//扩展指令
        widget = (m_actmextout);
        break;
	case CODE_PROARM://		0x06	//前臂指令
		widget = (m_actpro);
		break;
    case CODE_RUNARM://		0x06	//副臂指令
		widget = (m_actrun);
		break;
	case CODE_DELAY://		0x07	//延时指令
        widget = (m_actdelay);
        break;
    case CODE_POS://		0x08	//单轴定位指令
        widget = (m_actpos);
        break;
    case CODE_EXTPOS://		0x08	//扩展单轴定位指令
        widget = (m_actextpos);
        break;
    case CODE_INTERP://		0x08	//插补指令
        widget = (m_actinterp);
        break;
    case CODE_POWER://		0x08	//伺服电源
        widget = (m_actpower);
        break;
    case CODE_OPR://		0x14	//赋值指令
        widget = (m_actoperator);
        break;
	case VCODE_VACUUM://	0x80	//治具指令
        widget = (m_vactvacuum);
        break;
    case CODE_VACUUM://	0x80	//治具指令
		widget = (m_actvacuum);
		break;
	case CODE_WAIT://		0x20	//等待指令
        widget = (m_actwait);
        break;
    case CODE_IF://			0x21	//大于条件指令
        widget = (m_actif);
        break;
    case CODE_ELSE://		0x22	//ELSE指令
    case CODE_ENDIF://		0x23	//ENDIF指令
    case CODE_ENDFOR://		0x26	//ENDFOR指令
    case CODE_BREAK://		0x27	//BREAK指令
	case CODE_TEND://		0x2D	//路径结束指令
	case CODE_END://		0x2F	//程序结束指令
        widget = (m_actnull);
        break;
	case CODE_SPEED://		0x04	//速度指令
        widget = (m_actspeed);
        break;
    case CODE_TBEGIN://		0x2C	//路径开始指令
        widget = (m_actpath);
        break;
    case CODE_FOR_CONST://	0x24	//常FOR指令
    case CODE_FOR_VAR://	0x25	//变FOR指令
        widget = (m_actfor);
        break;
    case CODE_PAPER://		0xB	//取纸指令
        widget = (m_actpaper);
        break;
    case CODE_MATRIX://		0xC	//矩阵指令
        widget = (m_actloopmatrix);
        break;
    case CODE_FREEPOS://		0xD	//循环定位指令
        widget = (m_actloopfree);
        break;
    case CODE_LOOP://		0xE	//单轴循环定位指令
        widget = (m_actsingleloop);
        break;
    case CODE_LOOPFREE://		0x12	//单轴循环自由定位指令
        widget = (m_actsingleloopfree);
        break;
    case CODE_CIRCLE://		0x0F	//喷雾指令
        widget = (m_actcircle);
        break;
    case CODE_VISION://		0x12	//单轴循环自由定位指令
        widget = (m_actvision);
        break;
    case VCODE_ASSIST://		0x82	//辅助设备
        widget = (m_actassist);
        break;
    }
}

XmlModelItem *FormTeach::GetCodeItem(int idx)
{
	XmlModelItem *pitem = 0;
	uchar code;
	uchar subcall;
	code = idx;
	subcall = idx>>8;
	switch (code)
	{
	case CODE_IMM://		0x03	//塑机指令
		pitem = new CodeImm(m_actimm);
		break;
	case CODE_EXT_IN://		0x04	//扩展指令
		pitem = new CodeExtIn(m_actextin);
		break;
	case CODE_EXT_OUT://		0x04	//扩展指令
		pitem = new CodeExtOut(m_actextout);
		break;
    case CODE_MEXTOUT://		0x14	//扩展指令
        pitem = new CodeMExtOut(m_actmextout);
        break;
	case CODE_PROARM://		0x06	//前臂指令
		pitem = new CodePArm(m_actpro);
		break;
	case CODE_RUNARM://		0x06	//前臂指令
		pitem = new CodeRArm(m_actrun);
		break;
	case CODE_DELAY://		0x07	//延时指令
		pitem = new CodeDelay(m_actdelay);
		break;
    case CODE_CIRCLE://		0x0F	//喷雾指令
        pitem = new CodeCircle(m_actcircle);
        break;
    case CODE_POS://		0x08	//单轴定位指令
        pitem = new CodePos(m_actpos);
        break;
    case CODE_EXTPOS://		0x08	//扩展单轴定位指令
        pitem = new CodeExtPos(m_actextpos);
        break;
    case CODE_INTERP://		0x08	//插补指令
        pitem = new CodeInterp(m_actinterp);
        break;
    case CODE_POWER://		0x08	//伺服电源
        pitem = new CodePower(m_actpower);
        break;
    case CODE_OPR://		0x14	//赋值指令
		pitem = new CodeOperator(m_actoperator, OPR_TYPE_ADD);
		break;
	case CODE_WAIT://		0x20	//等待指令
		pitem = new CodeWait(m_actwait);
		break;
	case CODE_IF://			0x21	//大于条件指令
        pitem = new CodeIf(m_actif, subcall);
		break;
	case CODE_ELSE://		0x22	//ELSE指令
		pitem = new CodeElse(m_actnull);
		break;
	case CODE_ENDIF://		0x23	//ENDIF指令
		pitem = new CodeEndIf(m_actnull);
		break;
	case CODE_SPEED:
        pitem = new CodeSpeed(m_actspeed);
		break;
	case CODE_FOR_CONST://	0x24	//常FOR指令
		pitem = new CodeFor(m_actfor, CODE_FOR_CONST);
		break;
	case CODE_FOR_VAR://	0x25	//变FOR指令
		pitem = new CodeFor(m_actfor, CODE_FOR_VAR);
		break;
	case CODE_ENDFOR://		0x26	//ENDFOR指令
		pitem = new CodeEndFor(m_actnull);
		break;
	case CODE_BREAK://		0x27	//BREAK指令
		pitem = new CodeBreak(m_actnull);
		break;
	case VCODE_VACUUM:
        pitem = new VCodeVacuum(m_vactvacuum);
        break;
    case CODE_VACUUM:
		pitem = new CodeVacuum(m_actvacuum);
		break;
	case CODE_TBEGIN://		0x28	//组合开始指令
		pitem = new CodeTBegin(m_actpath);
        break;
	case CODE_TEND://		0x29	//组合结束指令
        pitem = new CodeTEnd(m_actnull);
        break;
    case CODE_PAPER://
        pitem = new CodePaper(m_actpaper);
        break;
    case CODE_MATRIX://
        pitem = new CodeLoopMatrix(m_actloopmatrix);
        break;
    case CODE_FREEPOS://
        pitem = new CodeLoopFree(m_actloopfree);
        break;
    case CODE_END://		0x2F	//程序结束指令
        pitem = new CodeEnd(m_actnull);
        break;
    case CODE_LOOP://		0xE	//程序结束指令
        pitem = new CodeSingleLoop(m_actsingleloop);
        break;
    case CODE_LOOPFREE://		0xE	//程序结束指令
        pitem = new CodeSingleLoopFree(m_actsingleloopfree);
        break;
    case CODE_VISION://		0x40	// 视觉指令
        pitem = new CodeVision(m_actvision);
        break;
    case VCODE_ASSIST://		0x82	// 辅助设备
        pitem = new CodeAssist(m_actassist);
        break;
    }
	return pitem;
}

// 当前登录用户更改槽
void FormTeach::userChange(void)
{
	if (xPermissions::GetPermissions(PER_TEACH) == false)
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
	setPermissions();
}

void FormTeach::InsertCode()
{
	int bakpos = 0;
    int curProcess = m_teachmodel->GetCurProcess(); // 当前进程
	int pos = ui->tableView_teach->currentIndex().row();
	if (pos < 0)
	{
        qDebug()<<"fuck FormTeach::InsertCode";
        return;
	}
	m_teachmodel->SavePara(pos);
	if (m_teachmodel->IsModified())
		ChangeSelect(pos);

    if (m_actdlg->exec(curProcess) == QDialog::Accepted)
	{
		//Insert Code
		XmlModelItem *pitem = GetCodeItem(m_actdlg->GetCode());
		if (pitem)
		{
			if (m_teachmodel->GetItemCount()>(pos+1))
			{
				pos ++;
			}
			m_teachmodel->InsertCode(pitem, pos);
			bakpos = pos;
			ChangeSelect(pos);
		}
		if (m_actdlg->GetCode()==CODE_TBEGIN)
        {
			pitem = GetCodeItem(CODE_TEND);
            if (pitem)
            {
                if (m_teachmodel->GetItemCount()>(pos+1))
                {
                    pos ++;
                }
                m_teachmodel->InsertCode(pitem, pos);
                ChangeSelect(bakpos);
            }
        }
        if (m_actdlg->GetCode()==CODE_IF)
		{
			pitem = GetCodeItem(CODE_ENDIF);
			if (pitem)
			{
				if (m_teachmodel->GetItemCount()>(pos+1))
				{
					pos ++;
				}
				m_teachmodel->InsertCode(pitem, pos);
				ChangeSelect(bakpos);
			}
		}
		if ((m_actdlg->GetCode()==CODE_FOR_CONST)||
            (m_actdlg->GetCode()==CODE_FOR_VAR))
		{
			pitem = GetCodeItem(CODE_ENDFOR);
			if (pitem)
			{
				if (m_teachmodel->GetItemCount()>(pos+1))
				{
					pos ++;
				}
				m_teachmodel->InsertCode(pitem, pos);
				ChangeSelect(bakpos);
			}
		}
		if (m_teachmodel->GetItemCount()>1)
		{
			ui->BtnTechDelete->setEnabled(true);
		}
		ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
	}
}
void FormTeach::RemoveCode()
{
    int ret;
    int pos = ui->tableView_teach->currentIndex().row();
	if (m_teachmodel->GetItemCount()!=(pos+1))
	{
        ret = xMessageBox::DoQuestion(tr("系统提示"), tr("确定要删除当前指令吗？"));
        if (ret != XMSG_RET_YES)
            return;
		m_teachmodel->RemoveCode(pos);
        ui->tableView_teach->selectRow(pos);
	}
	if (m_teachmodel->GetItemCount()<=1)
	{
		ui->BtnTechDelete->setEnabled(false);
	}
}
void FormTeach::CodeCombine(void)
{
    int pos = ui->tableView_teach->currentIndex().row();
    if (pos >= 0)
    {
        m_teachmodel->CodeCombine(pos);
        ui->tableView_teach->selectRow(pos);
    }
    else
        qDebug() << "CodeCombine error currentidx: " << pos;
}
void FormTeach::CodeSeparate(void)
{
    int pos = ui->tableView_teach->currentIndex().row();
    if (pos >= 0)
    {
        m_teachmodel->CodeSeparate(pos);
        ui->tableView_teach->selectRow(pos);
    }
    else
        qDebug() << "CodeSeparate error currentidx: " << pos;
}

void FormTeach::MoveUp()
{
    int pos = ui->tableView_teach->currentIndex().row();
    if ((pos==-1)||(pos==0)) return;
    if (m_teachmodel->GetItemCount()>(pos+1))
    {
        m_teachmodel->MoveUp(pos);
        ui->tableView_teach->selectRow(pos-1);
        ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
	}
}

void FormTeach::MoveDown()
{
    int pos = ui->tableView_teach->currentIndex().row();
    if ((pos==-1)||(pos==m_teachmodel->GetItemCount()-1)) return;
    if (m_teachmodel->GetItemCount()>pos+2)
    {
        m_teachmodel->MoveDown(pos);
        ui->tableView_teach->selectRow(pos+1);
        ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
	}
}
extern quint16 globlecodes[MAX_CODES];
extern quint32 globleparas[MAX_CODES];
void FormTeach::SaveProgram(int pos, bool isReset)
{
    int curpos;
    uint16_t updateflag = CMD_UPDATE_PARA1|CMD_UPDATE_PARA2|CMD_UPDATE_PARA3;
    if (m_teachmodel->GetCurProcess() == 0)
    {
        updateflag = CMD_UPDATE_PARA1;
    }
    if (m_teachmodel->GetCurProcess() == 1)
    {
        updateflag = CMD_UPDATE_PARA2;
    }
    if (m_teachmodel->GetCurProcess() == 2)
    {
        updateflag = CMD_UPDATE_PARA3;
    }
    if (pos<0)
        curpos = ui->tableView_teach->currentIndex().row();
    else
        curpos = pos;
#if (FACTORY == FA_JINBOYUE_SPECIAL)
    // 点击保存将修改保存到temp目录下程序
    m_teachmodel->SaveProgram(pModbus->GetCurPgmName(true));
#else
    m_teachmodel->SaveProgram(pModbus->GetCurPgmName());
#endif
    if ((pModbus->GetSysState() == SYS_STATE_AUTO)&&(!m_teachmodel->IsCodeDisable(curpos)))
	{
		int idx = m_teachmodel->GetPcPointer(curpos);
        int codeCnt = m_teachmodel->GenerateCode(curpos, globlecodes, globleparas);
        if (m_teachmodel->GetCurProcess() == 0)
        {
            if (pModbus->WriteCodeParas(globleparas, (0*MAX_CODES + idx), codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传指令参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return;
            }
        }
        if ((m_teachmodel->GetCurProcess() == 1) && pModbus->GetProcUse(1))
        {
            if (pModbus->WriteCodeParas(globleparas, (1*MAX_CODES + idx), codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传指令参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return;
            }
        }
        if ((m_teachmodel->GetCurProcess() == 2) && pModbus->GetProcUse(2))
        {
            if (pModbus->WriteCodeParas(globleparas, (2*MAX_CODES + idx), codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传指令参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return;
            }
        }
        // 更新主控模块当前程序
		if (pModbus->CommandUpdate(updateflag) != SENDMSG_RET_ACK)
		{
			xMessageBox::DoWarning(tr("系统警告"), tr("更新指令参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
			return;
		}
		// 写入系统日志
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_TEACH_SAVE);
		xSysLog::SaveChange();
	}
}

// 根据当前用户权限设置界面
void FormTeach::setPermissions(void)
{
	ui->frameTeach->setEnabled(xPermissions::GetPermissions(PER_TEACH));
}

void FormTeach::ChangeSelect(int pos)
{
    SetCurPos(pos);
	ui->tableView_teach->selectRow(pos);
}

void FormTeach::ProcBtnStateChanged(int idx)
{
    if (idx<MAX_PROCESS)
    {
        int pos = ui->tableView_teach->currentIndex().row();
        curpos[m_teachmodel->GetCurProcess()] = pos;
        m_teachmodel->SetCurProcess(idx);
        SetProcBtnState(idx);
// ********************************************************************
        // 2019-02-28
        ui->tableView_teach->selectRow(curpos[m_teachmodel->GetCurProcess()]);
        ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
// ********************************************************************
        // 当前进程指令条数大于1时，删除指令按钮可用，否则灰, 还要判断系统状态
        if ((m_teachmodel->GetItemCount()>1) && (pModbus->GetSysState() != SYS_STATE_AUTO))
            ui->BtnTechDelete->setEnabled(true);
        else
            ui->BtnTechDelete->setEnabled(false);
    }
}
void FormTeach::SetCurPos(int idx)
{
    if (idx < MAX_PROCESS)
        curpos[m_teachmodel->GetCurProcess()] = idx;
}

void FormTeach::SetProcBtnState(int idx)
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
void FormTeach::EditProgramSlot()
{
    int code;
    int pos = ui->tableView_teach->currentIndex().row();
    if (pos < 0)
    {
        qDebug()<<"fuck FormTeach::EditProgramSlot";
        return;
    }
    code = m_teachmodel->GetCode(pos);
    if ((code == CODE_ELSE) || (code == CODE_ENDIF) || (code == CODE_ENDFOR) || (code == CODE_BREAK) || (code == CODE_END) || (code == CODE_TEND))
        return;
    if (!(pos < 0))
    {
        m_teachmodel->ShowUI(pos);
        int ret = m_dialogparaedit->exec();
        m_teachmodel->ShowUI(pos, false);

        if (ret == QDialog::Accepted)
        {
            if (m_teachmodel->IsModified(pos))
            {
                m_teachmodel->SavePara(pos, false);
                SaveProgram(pos);
            }
        }
    }
}

void FormTeach::clickBtnInsert(void)
{
    int i;
    int idx = ui->tableView_teach->currentIndex().row();
    int poscnt = 0;
    bool combine = false;
    switch(currentCode)
    {
    case CODE_POS:
    {
        int axesbmp = m_btnpos->GetAxes();
        int pos[6], spd[6], delay[6], type[6];
        pos[AXIS_IDX_PHOR] = m_btnpos->GetX();
        pos[AXIS_IDX_PVER] = m_btnpos->GetY();
        pos[AXIS_IDX_TRV] = m_btnpos->GetZ();
        pos[AXIS_IDX_RVER] = m_btnpos->GetA();
        pos[AXIS_IDX_RHOR] = m_btnpos->GetB();
        pos[AXIS_IDX_EXT] = m_btnpos->GetC();

        spd[AXIS_IDX_PHOR] = m_btnpos->GetPaHorSpeed();
        spd[AXIS_IDX_PVER] = m_btnpos->GetPaVerSpeed();
        spd[AXIS_IDX_TRV] = m_btnpos->GetTrvSpeed();
        spd[AXIS_IDX_RVER] = m_btnpos->GetRaVerSpeed();
        spd[AXIS_IDX_RHOR] = m_btnpos->GetRaHorSpeed();
        spd[AXIS_IDX_EXT] = m_btnpos->GetOtherSpeed();

        delay[AXIS_IDX_PHOR] = m_btnpos->GetPaHorDelay();
        delay[AXIS_IDX_PVER] = m_btnpos->GetPaVerDelay();
        delay[AXIS_IDX_TRV] = m_btnpos->GetTrvDelay();
        delay[AXIS_IDX_RVER] = m_btnpos->GetRaVerDelay();
        delay[AXIS_IDX_RHOR] = m_btnpos->GetRaHorDelay();
        delay[AXIS_IDX_EXT] = m_btnpos->GetOtherDelay();

        type[AXIS_IDX_PHOR] = m_btnpos->GetXType();
        type[AXIS_IDX_PVER] = m_btnpos->GetYType();
        type[AXIS_IDX_TRV] = m_btnpos->GetZType();
        type[AXIS_IDX_RVER] = m_btnpos->GetAType();
        type[AXIS_IDX_RHOR] = m_btnpos->GetBType();
        type[AXIS_IDX_EXT] = m_btnpos->GetCType();

        for (i=0; i<6; i++)
        {
            if (axesbmp & (1<<i))
            {
                poscnt++;
            }
        }
        for (i=0; i<6; i++)
        {
            if (axesbmp & (1<<i))
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                {
                    idx ++;
                }
                CodePos* pitem = new CodePos(m_actpos);
                pitem->SetParas(i, spd[i], pos[i], delay[i], type[i]);
                m_teachmodel->InsertCode(pitem, idx);
                if (poscnt>1)
                {
                    if (!combine)
                        combine = true;
                    else
                    {
                        m_teachmodel->CodeCombine(idx);
                    }
                }
            }
        }
        m_btnpos->init();
        break;
    }
    case CODE_EXTPOS:
    {
        int axesbmp = m_btnextpos->GetAxes();
        int pos[6], spd[6], delay[6], type[6];
        pos[AXES_IDX_X] = m_btnextpos->GetX();
        pos[AXES_IDX_Y] = m_btnextpos->GetY();
        pos[AXES_IDX_Z] = m_btnextpos->GetZ();
        pos[AXES_IDX_A] = m_btnextpos->GetA();
        pos[AXES_IDX_B] = m_btnextpos->GetB();
        pos[AXES_IDX_C] = m_btnextpos->GetC();

        spd[AXIS_IDX_PHOR] = m_btnextpos->GetPaHorSpeed();
        spd[AXIS_IDX_PVER] = m_btnextpos->GetPaVerSpeed();
        spd[AXIS_IDX_TRV] = m_btnextpos->GetTrvSpeed();
        spd[AXIS_IDX_RVER] = m_btnextpos->GetRaVerSpeed();
        spd[AXIS_IDX_RHOR] = m_btnextpos->GetRaHorSpeed();
        spd[AXIS_IDX_EXT] = m_btnextpos->GetOtherSpeed();

        delay[AXIS_IDX_PHOR] = m_btnextpos->GetPaHorDelay();
        delay[AXIS_IDX_PVER] = m_btnextpos->GetPaVerDelay();
        delay[AXIS_IDX_TRV] = m_btnextpos->GetTrvDelay();
        delay[AXIS_IDX_RVER] = m_btnextpos->GetRaVerDelay();
        delay[AXIS_IDX_RHOR] = m_btnextpos->GetRaHorDelay();
        delay[AXIS_IDX_EXT] = m_btnextpos->GetOtherDelay();

        type[AXIS_IDX_PHOR] = m_btnextpos->GetXType();
        type[AXIS_IDX_PVER] = m_btnextpos->GetYType();
        type[AXIS_IDX_TRV] = m_btnextpos->GetZType();
        type[AXIS_IDX_RVER] = m_btnextpos->GetAType();
        type[AXIS_IDX_RHOR] = m_btnextpos->GetBType();
        type[AXIS_IDX_EXT] = m_btnextpos->GetCType();

        for (i=0; i<6; i++)
        {
            if (axesbmp & (1<<i))
            {
                poscnt++;
            }
        }
        for (i=0; i<6; i++)
        {
            if (axesbmp & (1<<i))
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                {
                    idx ++;
                }
                CodeExtPos* pitem = new CodeExtPos(m_actextpos);
                pitem->SetParas(i, spd[i], pos[i], delay[i], type[i]);
                m_teachmodel->InsertCode(pitem, idx);
                if (poscnt>1)
                {
                    if (!combine)
                        combine = true;
                    else
                    {
                        m_teachmodel->CodeCombine(idx);
                    }
                }
            }
        }
        m_btnextpos->init();
        break;
    }
    case CODE_IMM:
    {
        int immbmp = m_btnimm->GetIMMBmp();
        int immtype[8], immdelay[8];
        immtype[0] = m_btnimm->GetTypeEmc();
        immtype[1] = m_btnimm->GetTypeEmo();
        immtype[2] = m_btnimm->GetTypeEef();
        immtype[3] = m_btnimm->GetTypeEeb();
        immtype[4] = m_btnimm->GetTypeC1p1();
        immtype[5] = m_btnimm->GetTypeC1p2();
        immtype[6] = m_btnimm->GetTypeC2p1();
        immtype[7] = m_btnimm->GetTypeC2p2();

        immdelay[0] = m_btnimm->GetDelayEmc();
        immdelay[1] = m_btnimm->GetDelayEmo();
        immdelay[2] = m_btnimm->GetDelayEef();
        immdelay[3] = m_btnimm->GetDelayEeb();
        immdelay[4] = m_btnimm->GetDelayC1p1();
        immdelay[5] = m_btnimm->GetDelayC1p2();
        immdelay[6] = m_btnimm->GetDelayC2p1();
        immdelay[7] = m_btnimm->GetDelayC2p2();
        for (i=0; i<8; i++)
        {
            if (immbmp & (1<<i))
            {
                poscnt++;
            }
        }
        for (i = 0; i < 8; i++)
        {
            if (immbmp & (1<<i))
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                {
                    idx ++;
                }
                CodeImm* pitem = new CodeImm(m_actimm);
                pitem->SetParas(immtype[i], immdelay[i]);
                m_teachmodel->InsertCode(pitem, idx);
            }
        }
        m_btnimm->init();
        break;
    }
    case CODE_VACUUM:
    {
        poscnt++;
        if (m_teachmodel->GetItemCount()>(idx+1))
        {
            idx ++;
        }
        CodeVacuum* pitem = new CodeVacuum(m_actvacuum);
        pitem->SetParas(m_btnvacuum->GetType(), m_btnvacuum->GetDelay(), m_btnvacuum->GetOutBmp(), m_btnvacuum->GetInBmp());
        m_teachmodel->InsertCode(pitem, idx);
        m_btnvacuum->init();
        break;
    }
    case CODE_WAIT:
    {
        poscnt++;
        if (m_teachmodel->GetItemCount()>(idx+1))
        {
            idx ++;
        }
        CodeWait* pitem = new CodeWait(m_actwait);
        bool isconst;
        pitem->SetParas(m_btnwait->GetInvalidSet(), m_btnwait->GetVar(), m_btnwait->GetTimeout(), m_btnwait->GetVar2(isconst), m_btnwait->GetTimevalid());
        m_teachmodel->InsertCode(pitem, idx);
        m_btnwait->init();
        break;
    }
//    case CODE_MEXTOUT:
//    {
//        poscnt++;
//        if (m_teachmodel->GetItemCount()>(idx+1))
//        {
//            idx ++;
//        }
//        CodeMExtOut* pitem = new CodeMExtOut(m_actmextout);
//        pitem->SetParas(m_btnmextout->GetType(), m_btnmextout->GetOutBmp(), m_btnmextout->GetDelay());
//        m_teachmodel->InsertCode(pitem, idx);
//        m_btnmextout->init();
//        break;
//    }
    case CODE_EXT_OUT:
    {
        poscnt++;
        if (m_teachmodel->GetItemCount()>(idx+1))
        {
            idx ++;
        }
        CodeExtOut* pitem = new CodeExtOut(m_actextout);
        pitem->SetParas(m_btnextout->GetVar(), m_btnextout->GetType(), m_btnextout->GetInterval(),m_btnextout->GetDelay());//int var, int type, int interval, int delay
        m_teachmodel->InsertCode(pitem, idx);
        m_btnextout->init();
        break;
    }
    case CODE_PROARM:
    {
        poscnt++;
        if (m_teachmodel->GetItemCount()>(idx+1))
        {
            idx ++;
        }
        CodePArm* pitem = new CodePArm(m_actpro);
        pitem->SetParas(m_btnpro->GetType(), m_btnpro->GetDelay());
        m_teachmodel->InsertCode(pitem, idx);
        m_btnpro->init();
        break;
    }
    case CODE_RUNARM:
    {
        poscnt++;
        if (m_teachmodel->GetItemCount()>(idx+1))
        {
            idx ++;
        }
        CodeRArm* pitem = new CodeRArm(m_actrun);
        pitem->SetParas(m_btnrun->GetType(), m_btnrun->GetDelay());
        m_teachmodel->InsertCode(pitem, idx);
        m_btnrun->init();
        break;
    }
    case VCODE_ASSIST:
    {
        int assistbmp = m_btnassist->GetAssistBmp();
        int assisttype[3], assistdelay[3], assistinterval[3], assistvar[3];
        assisttype[0] = m_btnassist->GetTypeOil();
        assisttype[1] = m_btnassist->GetTypeConveyor();
        assisttype[2] = m_btnassist->GetTypeReject();

        assistdelay[0] = m_btnassist->GetDelayOil();
        assistdelay[1] = m_btnassist->GetDelayConveyor();
        assistdelay[2] = m_btnassist->GetDelayReject();

        assistinterval[0] = m_btnassist->GetIntervalOil();
        assistinterval[1] = m_btnassist->GetIntervalConveyor();
        assistinterval[2] = m_btnassist->GetIntervalReject();

        assistvar[0] = m_btnassist->GetVarOil();
        assistvar[1] = m_btnassist->GetVarConveyor();
        assistvar[2] = m_btnassist->GetVarReject();

        for (i=0; i<3; i++)
        {
            if (assistbmp & (1<<i))
            {
                poscnt++;
            }
        }
        for (i = 0; i < 3; i++)
        {
            if (assistbmp & (1<<i))
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                {
                    idx ++;
                }
                CodeAssist* pitem = new CodeAssist(m_actassist);
                pitem->SetParas(assistvar[i], assisttype[i], assistinterval[i], assistdelay[i]);
                m_teachmodel->InsertCode(pitem, idx);
            }
        }
        m_btnassist->init();
        break;
    }

    }

    if (m_teachmodel->GetItemCount()>1)
    {
        ui->BtnTechDelete->setEnabled(true);
    }
    if (poscnt)
    {
        ui->tableView_teach->selectRow(idx);
        ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
    }
}
void FormTeach::clickBtnmenu(void)
{
 //   ui->BtnInsert->setEnabled(true);
    switch(currentCode)
    {
    case CODE_EXTPOS:
        m_btnextpos->hide();
        break;
    case CODE_POS:
        m_btnpos->hide();
        break;
    case CODE_IMM:
        m_btnimm->hide();
        break;
    case CODE_VACUUM:
        m_btnvacuum->hide();
        break;
    case CODE_WAIT:
        m_btnwait->hide();
        break;
    case CODE_EXT_OUT:
        m_btnextout->hide();
        break;
    case CODE_PROARM:
        m_btnpro->hide();
        break;
    case CODE_RUNARM:
        m_btnrun->hide();
        break;
    case VCODE_ASSIST:
        m_btnassist->hide();
        break;
    }
    m_btnquick->hide();
    // 点击主菜单将当前指令码置成0xFF，否则点击插入仍会插入上一指令
    currentCode = 0xFF;
    ui->BtnPrev->setVisible(false);
    ui->BtnNext->setVisible(false);
    ui->BtnOK->setVisible(false);
    ui->groupBoxInstruction->setVisible(true);
}

// 要求新建程序进入界面时要显示初始值
// 点击快速按钮时，判断程序的条数，如果不多于1条，可看成是新建的程序
bool FormTeach::checkNewProgram(void)
{
    if (m_teachmodel->GetItemCount() > 1)
        return false;
    return true;
}

// 扩展输出端口打开信号槽
//void FormTeach::extOutOn(void)
//{
//    // 打开输出端口
//    quint16 outselect;     // 治具选择
//    outselect  = ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 0;
//    outselect |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 1;
//    outselect |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 2;
//    outselect |= ((quint16)(ui->checkBoxJig06->isChecked()?1:0)) << 3;
//    outselect |= ((quint16)(ui->checkBoxJig07->isChecked()?1:0)) << 4;
//    outselect |= ((quint16)(ui->checkBoxJig08->isChecked()?1:0)) << 5;
//    outselect |= ((quint16)(ui->checkBoxJig09->isChecked()?1:0)) << 6;
//    outselect |= ((quint16)(ui->checkBoxJig10->isChecked()?1:0)) << 7;
//    outselect |= ((quint16)(ui->checkBoxJig11->isChecked()?1:0)) << 8;
//    outselect |= ((quint16)(ui->checkBoxJig12->isChecked()?1:0)) << 9;
//    outselect |= ((quint16)(ui->checkBoxJig13->isChecked()?1:0)) << 10;
//    outselect |= ((quint16)(ui->checkBoxJig14->isChecked()?1:0)) << 11;
//    outselect |= ((quint16)(ui->checkBoxJig15->isChecked()?1:0)) << 12;
//    outselect |= ((quint16)(ui->checkBoxJig16->isChecked()?1:0)) << 13;
//    pModbus->ManualVacuum(true, 16383);
//}
// 扩展输出端口关闭信号槽
//void FormTeach::extOutOff(void)
//{
//    quint16 outselect;     // 治具选择
//    outselect  = ((quint16)(ui->checkBoxJig03->isChecked()?1:0)) << 0;
//    outselect |= ((quint16)(ui->checkBoxJig04->isChecked()?1:0)) << 1;
//    outselect |= ((quint16)(ui->checkBoxJig05->isChecked()?1:0)) << 2;
//    outselect |= ((quint16)(ui->checkBoxJig06->isChecked()?1:0)) << 3;
//    outselect |= ((quint16)(ui->checkBoxJig07->isChecked()?1:0)) << 4;
//    outselect |= ((quint16)(ui->checkBoxJig08->isChecked()?1:0)) << 5;
//    outselect |= ((quint16)(ui->checkBoxJig09->isChecked()?1:0)) << 6;
//    outselect |= ((quint16)(ui->checkBoxJig10->isChecked()?1:0)) << 7;
//    outselect |= ((quint16)(ui->checkBoxJig11->isChecked()?1:0)) << 8;
//    outselect |= ((quint16)(ui->checkBoxJig12->isChecked()?1:0)) << 9;
//    outselect |= ((quint16)(ui->checkBoxJig13->isChecked()?1:0)) << 10;
//    outselect |= ((quint16)(ui->checkBoxJig14->isChecked()?1:0)) << 11;
//    outselect |= ((quint16)(ui->checkBoxJig15->isChecked()?1:0)) << 12;
//    outselect |= ((quint16)(ui->checkBoxJig16->isChecked()?1:0)) << 13;
//    // 关闭输出端口
//    pModbus->ManualVacuum(false, 16383);
//}

void FormTeach::test_order()
{
    int curpos;
//    quint16 codes[20];
//    quint32 paras[20];
    uint16_t updateflag = CMD_UPDATE_PARA1|CMD_UPDATE_PARA2|CMD_UPDATE_PARA3;
    if (m_teachmodel->GetCurProcess() == 0)
    {
        updateflag = CMD_UPDATE_PARA1;
    }
    if (m_teachmodel->GetCurProcess() == 1)
    {
        updateflag = CMD_UPDATE_PARA2;
    }
    if (m_teachmodel->GetCurProcess() == 2)
    {
        updateflag = CMD_UPDATE_PARA3;
    }
    curpos = ui->tableView_teach->currentIndex().row();
    int codeCnt = m_teachmodel->GenerateCode(curpos, globlecodes, globleparas);

    int code;
    int pos = ui->tableView_teach->currentIndex().row();
    if (pos < 0)
        return;
    code = m_teachmodel->GetCode(pos);
    if((code == CODE_EXTPOS) || (code == CODE_POS))
    {
        globleparas[0] = globleparas[0] & 0xFFFF;
        quint8 axesbmp;
        quint32 pos;
        axesbmp = ((globleparas[0] >> 8) & 0x3F);
        pos = globleparas[1];
        pModbus->ManualPos(pModbus->GetManualSpeed(), axesbmp, pos, SERVO_MODE_SAFE);
    }
    else if((code == CODE_INTERP) || (code == CODE_MEXTOUT) || (code == CODE_PROARM) || (code == CODE_RUNARM) || (code == CODE_VACUUM))
    {
        globlecodes[codeCnt] = CODE_END;
        codeCnt++;
        if(code == CODE_VACUUM)
        {
            globleparas[0] &= ~(0xffff0000);//清除检测
            globleparas[1] &= ~(0x0000ffff);//清除延时
        }
        else if ((code == CODE_PROARM) || (code == CODE_RUNARM))
        {
            globleparas[0] &= ~(0xffff0000);   //清除延时
        }
        else if((code == CODE_INTERP) || (code == CODE_MEXTOUT))
        {
            globleparas[0] &= ~(0x7f);//清除速度参数
            quint32 spd;
            spd = (pModbus->GetManualSpeed() & 0x7f);
            globleparas[0] = (globleparas[0] | spd);
        }
        if (m_teachmodel->GetCurProcess() == 0)
        {
            if (pModbus->WriteCodes(globlecodes, 0, codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件指令到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return;
            }
            if (pModbus->WriteCodeParas(globleparas, 0, codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传指令参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return;
            }
        }
        if ((m_teachmodel->GetCurProcess() == 1) && pModbus->GetProcUse(1))
        {
            if (pModbus->WriteCodes(globlecodes, 1*MAX_CODES, codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件指令到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return;
            }
            if (pModbus->WriteCodeParas(globleparas, (1*MAX_CODES), codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传指令参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return;
            }
        }
        if ((m_teachmodel->GetCurProcess() == 2) && pModbus->GetProcUse(2))
        {
            if (pModbus->WriteCodes(globlecodes, 2*MAX_CODES, codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件指令到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return;
            }
            if (pModbus->WriteCodeParas(globleparas, (2*MAX_CODES), codeCnt) != SENDMSG_RET_ACK)
            {
                xMessageBox::DoWarning(tr("系统警告"), tr("上传指令参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                return;
            }
        }
        // 更新主控模块当前程序
        if (pModbus->CommandUpdate(updateflag) != SENDMSG_RET_ACK)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("更新指令参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
            return;
        }
        pModbus->SetRun();
    }
    else
    {
//        if(code == CODE_MATRIX)
//        {}
//        else if(code == CODE_FREEPOS)
//        {}
//        else if(code == CODE_LOOP)
//        {}
//        else if(code == CODE_LOOPFREE)
//        {}
//        else if(code == CODE_PAPER)//最大位置
//        {}
//        else
            return;
    }
}

void FormTeach::stop_test()
{
    if(pModbus->SetRunState(RUN_STATE_PAUSE) == SENDMSG_RET_ACK)
    {
        pModbus->SetSysState(SYS_STATE_MANUAL);
    }

}

void FormTeach::tableViewClicked(QModelIndex index)
{
    if(pModbus->GetSysState() == SYS_STATE_MANUAL)
    {
    int code;
    int pos = ui->tableView_teach->currentIndex().row();
    if (pos < 0)
        return;
    code = m_teachmodel->GetCode(pos);
    if((code != CODE_EXTPOS) && (code != CODE_POS) && (code != CODE_INTERP) && (code != CODE_MEXTOUT) && (code != CODE_PROARM) && (code != CODE_RUNARM) && (code != CODE_VACUUM))
        ui->BtnTest->setEnabled(false);
    else
        ui->BtnTest->setEnabled(true);
    }
}
#if (FACTORY == FA_BEISHITE || FACTORY == FA_BEISHITE_CN)
    static bool isfirstIn = true;//开机第一次进入快速教导
#endif
void FormTeach::clickBtnQuick(void)
{
    switch(currentCode)
    {
    case CODE_EXTPOS:
        m_btnextpos->hide();
        break;
    case CODE_POS:
        m_btnpos->hide();
        break;
    case CODE_IMM:
        m_btnimm->hide();
        break;
    case CODE_VACUUM:
        m_btnvacuum->hide();
        break;
    case CODE_WAIT:
        m_btnwait->hide();
        break;
    case CODE_EXT_OUT:
        m_btnextout->hide();
        break;
    case CODE_PROARM:
        m_btnpro->hide();
        break;
    case CODE_RUNARM:
        m_btnrun->hide();
        break;
    case VCODE_ASSIST:
        m_btnassist->hide();
        break;
    }
    ui->BtnPrev->setVisible(true);
    ui->BtnNext->setVisible(true);
    ui->BtnOK->setVisible(true);
    ui->BtnPrev->setEnabled(false);
    ui->BtnNext->setEnabled(true);
#if (FACTORY == FA_BEISHITE || FACTORY == FA_BEISHITE_CN)
    if(isfirstIn)
    {
        m_btnquick->EnterForm(true);
        isfirstIn = false;
    }
    else
        m_btnquick->EnterForm(false);
#else
    m_btnquick->EnterForm(true);//checkNewProgram()
#endif
    ui->groupBoxInstruction->setVisible(false);
    ui->BtnInsert->setEnabled(false);
}
void FormTeach::clickPagePrev(void)
{
    if (m_btnquick->clickPagePrev() == 0)
        ui->BtnPrev->setEnabled(false);
    else
    {
        ui->BtnPrev->setEnabled(true);
        ui->BtnNext->setEnabled(true);
    }

}
void FormTeach::clickPageNext(void)
{
    if(m_btnquick->CheckBoxWasteRotateFirstState() == false)
    {
        if (m_btnquick->clickPageNext() == 5)
        {
            ui->BtnNext->setEnabled(false);
        }
        else
        {
            ui->BtnPrev->setEnabled(true);
            ui->BtnNext->setEnabled(true);
        }
    }
    else
    {
        if (m_btnquick->clickPageNext() == 4)
        {
            ui->BtnNext->setEnabled(false);
        }
        else
        {
            ui->BtnPrev->setEnabled(true);
            ui->BtnNext->setEnabled(true);
        }

    }
}
// 完成生成教导程序
void FormTeach::clickQuickOK(void)
{
    int ret, itemcount, checkbmp = 0; // checkbmp 检测表
    bool combine = false;
    if (!m_haswarning)
    {
        ret = xMessageBox::DoQuestion(tr("系统提示"), tr("此操作将依照上述步骤设定生成一个全新的程序并且会覆盖当前程序，确定要继续吗？"));
        if (ret != XMSG_RET_YES)
            return;
    }
    m_haswarning = true;
    itemcount = m_teachmodel->GetItemCount();
    // 清除原程序
    for (int i = 0; i < (itemcount-1); i++)
    {
        m_teachmodel->RemoveCode(0);
    }
    // 插入新程序
    int idx = ui->tableView_teach->currentIndex().row();
        if ((((m_btnquick->GetCheckBoxState() >> 0)&1) == 0) && (((m_btnquick->GetCheckBoxState() >> 1)&1) == 0))            // 正臂和副臂都不选 仅横行运行到待机点-倒角-等待开模

        {
            // 运行到待机点Z
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaitzitem = new CodeExtPos(m_actextpos);
            pwaitzitem->SetParas(AXES_IDX_Z, 50, m_btnquick->GetWaitZ(), 0, m_btnquick->GetWaitZType());
            m_teachmodel->InsertCode(pwaitzitem, idx);
            // 待机点倒角
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodePArm* pwaitparm = new CodePArm(m_actpro);
            pwaitparm->SetParas((m_btnquick->GetCheckBoxState()>>4&1) , 5);
            m_teachmodel->InsertCode(pwaitparm, idx);
            // 等待开模
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeImm* pwaitmop = new CodeImm(m_actimm);
            pwaitmop->SetParas(IMMOUT_EMO, 0);
            m_teachmodel->InsertCode(pwaitmop, idx);
        }
        else
        if ((((m_btnquick->GetCheckBoxState() >> 0)&1) == 1) && (((m_btnquick->GetCheckBoxState() >> 1)&1) == 0))            // 选择正臂且副臂不选
        {
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaitYitem = new CodeExtPos(m_actextpos);
            pwaitYitem->SetParas(AXES_IDX_Y, 50, m_btnquick->GetWaitY(), 0, m_btnquick->GetWaitYType());
            m_teachmodel->InsertCode(pwaitYitem, idx);

            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaitxitem = new CodeExtPos(m_actextpos);
            pwaitxitem->SetParas(AXES_IDX_X, 50, m_btnquick->GetWaitX(), 0, m_btnquick->GetWaitXType());
            m_teachmodel->InsertCode(pwaitxitem, idx);
            if (!combine)
                combine = true;
            else
                m_teachmodel->CodeCombine(idx);

            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaitzitem = new CodeExtPos(m_actextpos);
            pwaitzitem->SetParas(AXES_IDX_Z, 50, m_btnquick->GetWaitZ(), 0, m_btnquick->GetWaitZType());
            m_teachmodel->InsertCode(pwaitzitem, idx);
            if (!combine)
                combine = true;
            else
                m_teachmodel->CodeCombine(idx);
            // 待机点倒角
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodePArm* pwaitparm = new CodePArm(m_actpro);
            pwaitparm->SetParas((m_btnquick->GetCheckBoxState()>>4&1) , 50);
            m_teachmodel->InsertCode(pwaitparm, idx);
            // 等待开模
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeImm* pwaitmop = new CodeImm(m_actimm);
            pwaitmop->SetParas(IMMOUT_EMO , 0);
            m_teachmodel->InsertCode(pwaitmop, idx);
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pfetchyitem = new CodeExtPos(m_actextpos);
            pfetchyitem->SetParas(AXES_IDX_Y, 50, m_btnquick->GetFetchY(), 0, m_btnquick->GetFetchYType());
            m_teachmodel->InsertCode(pfetchyitem, idx);

            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pfetchxitem = new CodeExtPos(m_actextpos);
            pfetchxitem->SetParas(AXES_IDX_X, 50, m_btnquick->GetFetchX(), 0, m_btnquick->GetFetchXType());
            m_teachmodel->InsertCode(pfetchxitem, idx);
            // 取成品治具打开
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeVacuum* pfetchvacopenitem = new CodeVacuum(m_actvacuum);
            // 获取治具检测对应表
            if ((m_btnquick->GetVacuumBmp()>>0)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 0;
            if ((m_btnquick->GetVacuumBmp()>>1)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 1;
            if ((m_btnquick->GetVacuumBmp()>>2)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 2;
            if ((m_btnquick->GetVacuumBmp()>>3)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 3;
            if ((m_btnquick->GetVacuumBmp()>>4)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 4;
            if ((m_btnquick->GetVacuumBmp()>>5)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 5;
            if ((m_btnquick->GetVacuumBmp()>>6)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 6;
            if ((m_btnquick->GetVacuumBmp()>>7)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 7;
            if ((m_btnquick->GetVacuumBmp()>>8)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 8;
            if ((m_btnquick->GetVacuumBmp()>>9)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 9;
            if ((m_btnquick->GetVacuumBmp()>>10)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 10;
            if ((m_btnquick->GetVacuumBmp()>>11)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 11;
            if ((m_btnquick->GetVacuumBmp()>>12)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 12;
            if ((m_btnquick->GetVacuumBmp()>>13)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 13;
            if ((m_btnquick->GetVacuumBmp()>>14)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 14;
            if ((m_btnquick->GetVacuumBmp()>>15)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 15;
            pfetchvacopenitem->SetParas(1, 50, (quint16)m_btnquick->GetVacuumBmp(), checkbmp, 0);
            m_teachmodel->InsertCode(pfetchvacopenitem, idx);
            // 运行到待机点X-Y
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaitxitemret = new CodeExtPos(m_actextpos);
            pwaitxitemret->SetParas(AXES_IDX_X, 50, m_btnquick->GetWaitX(), 0, m_btnquick->GetWaitXType());
            m_teachmodel->InsertCode(pwaitxitemret, idx);

            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaityitemret = new CodeExtPos(m_actextpos);
            pwaityitemret->SetParas(AXES_IDX_Y, 50, m_btnquick->GetWaitY(), 0, m_btnquick->GetWaitYType());
            m_teachmodel->InsertCode(pwaityitemret, idx);
            // 允许关模
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeImm* pwaitemc = new CodeImm(m_actimm);
            pwaitemc->SetParas(IMMOUT_EMC , 0);
            m_teachmodel->InsertCode(pwaitemc, idx);
            // 放成品
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pproductxitem = new CodeExtPos(m_actextpos);
            pproductxitem->SetParas(AXES_IDX_X, 50, m_btnquick->GetProductX(), 0, m_btnquick->GetProductXType());
            m_teachmodel->InsertCode(pproductxitem, idx);
            // 提前倒角为放成品状态
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodePArm* ptrvoutparm = new CodePArm(m_actpro);
            ptrvoutparm->SetParas((m_btnquick->GetCheckBoxState()>>6&1) , 50);//(m_btnquick->GetCheckBoxState()>>8&1)
            m_teachmodel->InsertCode(ptrvoutparm, idx);

            // 堆叠 -可选
            if ((m_btnquick->GetCheckBoxState() >> 10)&1)
            {
                bool rel[3]; quint16 num[3]; qint16 interval[3]; qint32 pos[3];
                rel[0] = false; rel[1] = false; rel[2] = false;
                pos[0] = 0; pos[1] = 0; pos[2] = 0;
                interval[0] = 0; interval[1] = 0; interval[2] = 0;
                num[0] = 1; num[1] = 1; num[2] = 1;

                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeLoopMatrix* pmatrixitem = new CodeLoopMatrix(m_actloopmatrix);
                pmatrixitem->SetParas(50, 10, 50, ORDER_MODE_XYZ, false, true, false, ((m_btnquick->GetCheckBoxState()>>6&1) ? true : false), rel, num, interval, pos, 0, 0, 0);
                m_teachmodel->InsertCode(pmatrixitem, idx);
            }
            else
            {
                // 放成品Z
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pproductzitem = new CodeExtPos(m_actextpos);
                pproductzitem->SetParas(AXES_IDX_Z, 50, m_btnquick->GetProductZ(), 0, m_btnquick->GetProductZType());
                m_teachmodel->InsertCode(pproductzitem, idx);

                //组合
//                if (!combine)
//                    combine = true;
//                else
//                    m_teachmodel->CodeCombine(idx);
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pproductyitem = new CodeExtPos(m_actextpos);
                pproductyitem->SetParas(AXES_IDX_Y, 50, m_btnquick->GetProductY(), 0, m_btnquick->GetProductYType());
                m_teachmodel->InsertCode(pproductyitem, idx);
            }
            // 关闭治具
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeVacuum* pfetchvaccloseitem = new CodeVacuum(m_actvacuum);
            pfetchvaccloseitem->SetParas(0, 50, (quint16)m_btnquick->GetVacuumBmp(), checkbmp, 0);
            m_teachmodel->InsertCode(pfetchvaccloseitem, idx);
            // 待机点
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaityitemback = new CodeExtPos(m_actextpos);
            pwaityitemback->SetParas(AXES_IDX_Y, 50, m_btnquick->GetWaitY(), 0, m_btnquick->GetWaitYType());
            m_teachmodel->InsertCode(pwaityitemback, idx);
        }
        else
        if ((((m_btnquick->GetCheckBoxState() >> 0)&1) == 0) && (((m_btnquick->GetCheckBoxState() >> 1)&1) == 1))            // 选择副臂且正臂不选

        {
            // Y2-X2-Z待机点
            if(pModbus->GetRunnerUse())//气动副臂使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* prarmretwaititem = new CodeRArm(m_actrun);
                if(m_btnquick->GetRarmWaitState_ADV())
                    prarmretwaititem->SetParas(RUN_ACT_ADVANCE,50);
                else
                    prarmretwaititem->SetParas(RUN_ACT_RETURN,50);
                m_teachmodel->InsertCode(prarmretwaititem,idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }
            else
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwaitbitem = new CodeExtPos(m_actextpos);
                pwaitbitem->SetParas(AXES_IDX_B, 50, m_btnquick->GetWaitB(), 0, m_btnquick->GetWaitBType());
                m_teachmodel->InsertCode(pwaitbitem, idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }

            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaitzitem = new CodeExtPos(m_actextpos);
            pwaitzitem->SetParas(AXES_IDX_Z, 50, m_btnquick->GetWaitZ(), 0, m_btnquick->GetWaitZType());
            m_teachmodel->InsertCode(pwaitzitem, idx);
            if (!combine)
                combine = true;
            else
                m_teachmodel->CodeCombine(idx);

            // 待机点倒角
            if(pModbus->GetRunRotateUse())//初始设置中副臂倒角使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* pwaitrarm = new CodeRArm(m_actrun);
                pwaitrarm->SetParas(((m_btnquick->GetCheckBoxState()>>4&1)?5:4), 50);
                m_teachmodel->InsertCode(pwaitrarm, idx);
            }
            // 等待开模
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeImm* pwaitmop = new CodeImm(m_actimm);
            pwaitmop->SetParas(IMMOUT_EMO , 0);
            m_teachmodel->InsertCode(pwaitmop, idx);

            if(pModbus->GetRunnerUse())//气动副臂使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* prarmascchaitem = new CodeRArm(m_actrun);
                prarmascchaitem->SetParas(RUN_ACT_DESCENT,50);
                m_teachmodel->InsertCode(prarmascchaitem,idx);

                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* prarmretchaitem = new CodeRArm(m_actrun);
                if(m_btnquick->GetRarmWaitState_ADV())
                    prarmretchaitem->SetParas(RUN_ACT_RETURN,50);
                else
                    prarmretchaitem->SetParas(RUN_ACT_ADVANCE,50);
                m_teachmodel->InsertCode(prarmretchaitem,idx);
            }
            else
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pfetchaitem = new CodeExtPos(m_actextpos);
                pfetchaitem->SetParas(AXES_IDX_A, 50, m_btnquick->GetFetchA(), 0, m_btnquick->GetFetchAType());
                m_teachmodel->InsertCode(pfetchaitem, idx);

                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pfetchbitem = new CodeExtPos(m_actextpos);
                pfetchbitem->SetParas(AXES_IDX_B, 50, m_btnquick->GetFetchB(), 0, m_btnquick->GetFetchBType());
                m_teachmodel->InsertCode(pfetchbitem, idx);
            }
            // 取成品治具打开
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeVacuum* pfetchrunitem = new CodeVacuum(m_actvacuum);
            if ((m_btnquick->GetVacuumBmp()>>16)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 0;
            if ((m_btnquick->GetVacuumBmp()>>17)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 1;
            if ((m_btnquick->GetVacuumBmp()>>18)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 2;
            if ((m_btnquick->GetVacuumBmp()>>19)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 3;
            if ((m_btnquick->GetVacuumBmp()>>20)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 4;
            if ((m_btnquick->GetVacuumBmp()>>21)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 5;
            if ((m_btnquick->GetVacuumBmp()>>22)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 6;
            if ((m_btnquick->GetVacuumBmp()>>23)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 7;
            if ((m_btnquick->GetVacuumBmp()>>24)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 8;
            if ((m_btnquick->GetVacuumBmp()>>25)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 9;
            if ((m_btnquick->GetVacuumBmp()>>26)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 10;
            if ((m_btnquick->GetVacuumBmp()>>27)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 11;
            if ((m_btnquick->GetVacuumBmp()>>28)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 12;
            if ((m_btnquick->GetVacuumBmp()>>29)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 13;
            pfetchrunitem->SetParas(1, 50, (quint16)(m_btnquick->GetVacuumBmp()>>16), checkbmp, 0);
            m_teachmodel->InsertCode(pfetchrunitem, idx);
            // 运行到待机点X2-Y2
            if(pModbus->GetRunnerUse())//气动副臂使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* prarmretwaititem = new CodeRArm(m_actrun);
                if(m_btnquick->GetRarmWaitState_ADV())
                    prarmretwaititem->SetParas(RUN_ACT_ADVANCE,50);
                else
                    prarmretwaititem->SetParas(RUN_ACT_RETURN,50);
                m_teachmodel->InsertCode(prarmretwaititem,idx);

                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* prarmascwaititem = new CodeRArm(m_actrun);
                prarmascwaititem->SetParas(RUN_ACT_ASCENT,50);
                m_teachmodel->InsertCode(prarmascwaititem,idx);
            }
            else
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwaitbitemret = new CodeExtPos(m_actextpos);
                pwaitbitemret->SetParas(AXES_IDX_B, 50, m_btnquick->GetWaitB(), 0, m_btnquick->GetWaitBType());
                m_teachmodel->InsertCode(pwaitbitemret, idx);

                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwaitaitemret = new CodeExtPos(m_actextpos);
                pwaitaitemret->SetParas(AXES_IDX_A, 50, m_btnquick->GetWaitA(), 0, m_btnquick->GetWaitAType());
                m_teachmodel->InsertCode(pwaitaitemret, idx);
            }
            // 允许关模
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeImm* pwaitemc = new CodeImm(m_actimm);
            pwaitemc->SetParas(IMMOUT_EMC , 0);
            m_teachmodel->InsertCode(pwaitemc, idx);
            // 横出倒角
            if(pModbus->GetRunRotateUse())//初始设置中副臂倒角使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* ptrvoutrarm = new CodeRArm(m_actpro);
                ptrvoutrarm->SetParas(((m_btnquick->GetCheckBoxState()>>8&1)?5:4) , 50);
                m_teachmodel->InsertCode(ptrvoutrarm, idx);
            }
            // 放水口z
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pproductzitem = new CodeExtPos(m_actextpos);
            pproductzitem->SetParas(AXES_IDX_Z, 50, m_btnquick->GetWasteZ(), 0, m_btnquick->GetWasteZType());
            m_teachmodel->InsertCode(pproductzitem, idx);
            // 倒角-放水口
            if(pModbus->GetRunRotateUse())//初始设置中副臂倒角使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* pproductrarm = new CodeRArm(m_actpro);
                pproductrarm->SetParas(((m_btnquick->GetCheckBoxState()>>7&1)?5:4) , 50);
                m_teachmodel->InsertCode(pproductrarm, idx);
            }
            // 放水口
            if(pModbus->GetRunnerUse())//气动副臂使用
            {
				if(m_btnquick->GetRunnerWasterState())
                {
                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeRArm* prarmputwateritem = new CodeRArm(m_actrun);
                    prarmputwateritem->SetParas(RUN_ACT_DESCENT,50);
                    m_teachmodel->InsertCode(prarmputwateritem,idx);
                }
            }
            else
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pproductbitem = new CodeExtPos(m_actextpos);
                pproductbitem->SetParas(AXES_IDX_B, 50, m_btnquick->GetWasteB(), 0, m_btnquick->GetWasteBType());
                m_teachmodel->InsertCode(pproductbitem, idx);

                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pproductaitem = new CodeExtPos(m_actextpos);
                pproductaitem->SetParas(AXES_IDX_A, 50, m_btnquick->GetWasteA(), 0, m_btnquick->GetWasteAType());
                m_teachmodel->InsertCode(pproductaitem, idx);
            }
            // 关闭治具
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeVacuum* pfetchvaccloseitem = new CodeVacuum(m_actvacuum);
            pfetchvaccloseitem->SetParas(0, 50, (quint16)(m_btnquick->GetVacuumBmp()>>16), checkbmp, 0);
            m_teachmodel->InsertCode(pfetchvaccloseitem, idx);
            // 待机点
            if(pModbus->GetRunnerUse())//气动副臂使用
            {
				if(m_btnquick->GetRunnerWasterState())
                {
                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeRArm* prarmputwateritem = new CodeRArm(m_actrun);
                    prarmputwateritem->SetParas(RUN_ACT_ASCENT,50);
                    m_teachmodel->InsertCode(prarmputwateritem,idx);
                }
            }
            else
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwaitaitemback = new CodeExtPos(m_actextpos);
                pwaitaitemback->SetParas(AXES_IDX_A, 50, m_btnquick->GetWaitA(), 0, m_btnquick->GetWaitAType());
                m_teachmodel->InsertCode(pwaitaitemback, idx);
            }
        }
        else            // 选择副臂和正臂

        {
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaitxitem = new CodeExtPos(m_actextpos);
            pwaitxitem->SetParas(AXES_IDX_X, 50, m_btnquick->GetWaitX(), 0, m_btnquick->GetWaitXType());
            m_teachmodel->InsertCode(pwaitxitem, idx);
            if (!combine)
                combine = true;
            else
                m_teachmodel->CodeCombine(idx);

            if(pModbus->GetRunnerUse())//气动副臂使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* prarmretwaititem = new CodeRArm(m_actrun);
                if(m_btnquick->GetRarmWaitState_ADV())
                    prarmretwaititem->SetParas(RUN_ACT_ADVANCE,50);
                else
                    prarmretwaititem->SetParas(RUN_ACT_RETURN,50);
                m_teachmodel->InsertCode(prarmretwaititem,idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }
            else
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwaitbitem = new CodeExtPos(m_actextpos);
                pwaitbitem->SetParas(AXES_IDX_B, 50, m_btnquick->GetWaitB(), 0, m_btnquick->GetWaitBType());
                m_teachmodel->InsertCode(pwaitbitem, idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }

            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaitzitem = new CodeExtPos(m_actextpos);
            pwaitzitem->SetParas(AXES_IDX_Z, 50, m_btnquick->GetWaitZ(), 0, m_btnquick->GetWaitZType());
            m_teachmodel->InsertCode(pwaitzitem, idx);
            if (!combine)
                combine = true;
            else
                m_teachmodel->CodeCombine(idx);
            // 待机点倒角
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodePArm* pwaitparm = new CodePArm(m_actpro);
            pwaitparm->SetParas((m_btnquick->GetCheckBoxState()>>4&1) , 50);
            m_teachmodel->InsertCode(pwaitparm, idx);
            // 等待开模
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeImm* pwaitmop = new CodeImm(m_actimm);
            pwaitmop->SetParas(IMMOUT_EMO , 0);
            m_teachmodel->InsertCode(pwaitmop, idx);
            // 取物,Y-Y2组合 X-X2组合
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pfetchyitem = new CodeExtPos(m_actextpos);
            pfetchyitem->SetParas(AXES_IDX_Y, 50, m_btnquick->GetFetchY(), 0, m_btnquick->GetFetchYType());
            m_teachmodel->InsertCode(pfetchyitem, idx);

            if(pModbus->GetRunnerUse())//气动副臂使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* prarmascchaitem = new CodeRArm(m_actrun);
                prarmascchaitem->SetParas(RUN_ACT_DESCENT,50);
                m_teachmodel->InsertCode(prarmascchaitem,idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }
            else
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pfetchy2item = new CodeExtPos(m_actextpos);
                pfetchy2item->SetParas(AXES_IDX_A, 50, m_btnquick->GetFetchA(), 0, m_btnquick->GetFetchAType());
                m_teachmodel->InsertCode(pfetchy2item, idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }

            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pfetchxitem = new CodeExtPos(m_actextpos);
            pfetchxitem->SetParas(AXES_IDX_X, 50, m_btnquick->GetFetchX(), 0, m_btnquick->GetFetchXType());
            m_teachmodel->InsertCode(pfetchxitem, idx);

            if(pModbus->GetRunnerUse())//气动副臂使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* prarmretchaitem = new CodeRArm(m_actrun);
                if(m_btnquick->GetRarmFetch_adv())
                    prarmretchaitem->SetParas(RUN_ACT_ADVANCE,50);
                else
                    prarmretchaitem->SetParas(RUN_ACT_RETURN,50);
                m_teachmodel->InsertCode(prarmretchaitem,idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }
            else
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pfetchx2item = new CodeExtPos(m_actextpos);
                pfetchx2item->SetParas(AXES_IDX_B, 50, m_btnquick->GetFetchB(), 0, m_btnquick->GetFetchBType());
                m_teachmodel->InsertCode(pfetchx2item, idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }
            // 治具打开，组合
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeVacuum* pfetchproitem = new CodeVacuum(m_actvacuum);
            // 获取治具检测对应表
            if ((m_btnquick->GetVacuumBmp()>>0)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 0;
            if ((m_btnquick->GetVacuumBmp()>>1)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 1;
            if ((m_btnquick->GetVacuumBmp()>>2)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 2;
            if ((m_btnquick->GetVacuumBmp()>>3)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 3;
            if ((m_btnquick->GetVacuumBmp()>>4)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 4;
            if ((m_btnquick->GetVacuumBmp()>>5)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 5;
            if ((m_btnquick->GetVacuumBmp()>>6)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 6;
            if ((m_btnquick->GetVacuumBmp()>>7)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 7;
            if ((m_btnquick->GetVacuumBmp()>>8)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 8;
            if ((m_btnquick->GetVacuumBmp()>>9)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 9;
            if ((m_btnquick->GetVacuumBmp()>>10)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 10;
            if ((m_btnquick->GetVacuumBmp()>>11)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 11;
            if ((m_btnquick->GetVacuumBmp()>>12)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 12;
            if ((m_btnquick->GetVacuumBmp()>>13)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 13;
            pfetchproitem->SetParas(1, 50, ((quint16)m_btnquick->GetVacuumBmp()), checkbmp, 0);
            m_teachmodel->InsertCode(pfetchproitem, idx);

            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeVacuum* pfetchrunitem = new CodeVacuum(m_actvacuum);
            if ((m_btnquick->GetVacuumBmp()>>16)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 0;
            if ((m_btnquick->GetVacuumBmp()>>17)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 1;
            if ((m_btnquick->GetVacuumBmp()>>18)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 2;
            if ((m_btnquick->GetVacuumBmp()>>19)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 3;
            if ((m_btnquick->GetVacuumBmp()>>20)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 4;
            if ((m_btnquick->GetVacuumBmp()>>21)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 5;
            if ((m_btnquick->GetVacuumBmp()>>22)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 6;
            if ((m_btnquick->GetVacuumBmp()>>23)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 7;
            if ((m_btnquick->GetVacuumBmp()>>24)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 8;
            if ((m_btnquick->GetVacuumBmp()>>25)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 9;
            if ((m_btnquick->GetVacuumBmp()>>26)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 10;
            if ((m_btnquick->GetVacuumBmp()>>27)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 11;
            if ((m_btnquick->GetVacuumBmp()>>28)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 12;
            if ((m_btnquick->GetVacuumBmp()>>29)&1)
                checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 13;
            pfetchrunitem->SetParas(1, 50, (quint16)(m_btnquick->GetVacuumBmp()>>16), checkbmp, 0);
            m_teachmodel->InsertCode(pfetchrunitem, idx);
            if (!combine)
                combine = true;
            else
                m_teachmodel->CodeCombine(idx);
            // 运行到待机点X-X2 Y-Y2
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaitxitemret = new CodeExtPos(m_actextpos);
            pwaitxitemret->SetParas(AXES_IDX_X, 50, m_btnquick->GetWaitX(), 0, m_btnquick->GetWaitXType());
            m_teachmodel->InsertCode(pwaitxitemret, idx);

            if(pModbus->GetRunnerUse())//气动副臂使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* prarmretwaititem = new CodeRArm(m_actrun);
                if(m_btnquick->GetRarmFetch_adv())
                    prarmretwaititem->SetParas(RUN_ACT_RETURN,50);
                else
                    prarmretwaititem->SetParas(RUN_ACT_ADVANCE,50);
                m_teachmodel->InsertCode(prarmretwaititem,idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }
            else
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwaitbitemret = new CodeExtPos(m_actextpos);
                pwaitbitemret->SetParas(AXES_IDX_B, 50, m_btnquick->GetWaitB(), 0, m_btnquick->GetWaitBType());
                m_teachmodel->InsertCode(pwaitbitemret, idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }

            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pwaityitemret = new CodeExtPos(m_actextpos);
            pwaityitemret->SetParas(AXES_IDX_Y, 50, m_btnquick->GetWaitY(), 0, m_btnquick->GetWaitYType());
            m_teachmodel->InsertCode(pwaityitemret, idx);

            if(pModbus->GetRunnerUse())//气动副臂使用
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeRArm* prarmascwaititem = new CodeRArm(m_actrun);
                prarmascwaititem->SetParas(RUN_ACT_ASCENT,50);
                m_teachmodel->InsertCode(prarmascwaititem,idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }
            else
            {
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwaitaitemret = new CodeExtPos(m_actextpos);
                pwaitaitemret->SetParas(AXES_IDX_A, 50, m_btnquick->GetWaitA(), 0, m_btnquick->GetWaitAType());
                m_teachmodel->InsertCode(pwaitaitemret, idx);
                if (!combine)
                    combine = true;
                else
                    m_teachmodel->CodeCombine(idx);
            }
            // 允许关模
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeImm* pwaitemc = new CodeImm(m_actimm);
            pwaitemc->SetParas(IMMOUT_EMC , 0);
            m_teachmodel->InsertCode(pwaitemc, idx);
            //正引拔
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodeExtPos* pproductxitem = new CodeExtPos(m_actextpos);
            pproductxitem->SetParas(AXES_IDX_X, 50, m_btnquick->GetProductX(), 0, m_btnquick->GetProductXType());
            m_teachmodel->InsertCode(pproductxitem, idx);
            // 横出倒角
            if (m_teachmodel->GetItemCount()>(idx+1))
                idx ++;
            CodePArm* ptrvoutparm = new CodePArm(m_actpro);
            ptrvoutparm->SetParas((m_btnquick->GetCheckBoxState()>>6&1) , 50);//(m_btnquick->GetCheckBoxState()>>8&1)
            m_teachmodel->InsertCode(ptrvoutparm, idx);

            // -------------------------------------------------------------
            if(((m_btnquick->GetCheckBoxState()>>11)&1) == 0)//先放成品
            {
                // 使用矩阵
                if ((m_btnquick->GetCheckBoxState() >> 10)&1)
                {
                    bool rel[3]; quint16 num[3]; qint16 interval[3]; qint32 pos[3];
                    rel[0] = false; rel[1] = false; rel[2] = false;
                    pos[0] = 0; pos[1] = 0; pos[2] = 0;
                    interval[0] = 0; interval[1] = 0; interval[2] = 0;
                    num[0] = 1; num[1] = 1; num[2] = 1;

                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeLoopMatrix* pmatrixitem = new CodeLoopMatrix(m_actloopmatrix);
                    pmatrixitem->SetParas(50, 10, 50, ORDER_MODE_XYZ, false, true, false, ((m_btnquick->GetCheckBoxState()>>6&1) ? true : false), rel, num, interval, pos ,0, 0, 0);
                    m_teachmodel->InsertCode(pmatrixitem, idx);
                }
                else
                {
                    // 放成品
                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeExtPos* pproductzitem = new CodeExtPos(m_actextpos);
                    pproductzitem->SetParas(AXES_IDX_Z, 50, m_btnquick->GetProductZ(), 0, m_btnquick->GetProductZType());
                    m_teachmodel->InsertCode(pproductzitem, idx);


                    //组合
//                    if (!combine)
//                        combine = true;
//                    else
//                        m_teachmodel->CodeCombine(idx);
                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeExtPos* pproductyitem = new CodeExtPos(m_actextpos);
                    pproductyitem->SetParas(AXES_IDX_Y, 50, m_btnquick->GetProductY(), 0, m_btnquick->GetProductYType());
                    m_teachmodel->InsertCode(pproductyitem, idx);
                }
                // 关闭治具
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeVacuum* pfetchvaccloseitem = new CodeVacuum(m_actvacuum);
                if ((m_btnquick->GetVacuumBmp()>>0)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 0;
                if ((m_btnquick->GetVacuumBmp()>>1)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 1;
                if ((m_btnquick->GetVacuumBmp()>>2)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 2;
                if ((m_btnquick->GetVacuumBmp()>>3)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 3;
                if ((m_btnquick->GetVacuumBmp()>>4)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 4;
                if ((m_btnquick->GetVacuumBmp()>>5)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 5;
                if ((m_btnquick->GetVacuumBmp()>>6)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 6;
                if ((m_btnquick->GetVacuumBmp()>>7)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 7;
                if ((m_btnquick->GetVacuumBmp()>>8)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 8;
                if ((m_btnquick->GetVacuumBmp()>>9)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 9;
                if ((m_btnquick->GetVacuumBmp()>>10)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 10;
                if ((m_btnquick->GetVacuumBmp()>>11)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 11;
                if ((m_btnquick->GetVacuumBmp()>>12)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 12;
                if ((m_btnquick->GetVacuumBmp()>>13)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 13;
                pfetchvaccloseitem->SetParas(0, 50, (quint16)m_btnquick->GetVacuumBmp(), checkbmp, 0);
                m_teachmodel->InsertCode(pfetchvaccloseitem, idx);

                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwaityitemback = new CodeExtPos(m_actextpos);
                pwaityitemback->SetParas(AXES_IDX_Y, 50, m_btnquick->GetWaitY(), 0, m_btnquick->GetWaitYType());
                m_teachmodel->InsertCode(pwaityitemback, idx);
                // 放水口
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwastezitem = new CodeExtPos(m_actextpos);
                pwastezitem->SetParas(AXES_IDX_Z, 50, m_btnquick->GetWasteZ(), 0, m_btnquick->GetWasteZType());
                m_teachmodel->InsertCode(pwastezitem, idx);

                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                if(pModbus->GetRunnerUse())//气动副臂使用
                {
					if(m_btnquick->GetRunnerWasterState())
                    {
                        if (m_teachmodel->GetItemCount()>(idx+1))
                            idx ++;
                        CodeRArm* prarmputwateritem = new CodeRArm(m_actrun);
                        prarmputwateritem->SetParas(RUN_ACT_DESCENT,50);
                        m_teachmodel->InsertCode(prarmputwateritem,idx);
                    }

                }
                else
                {
                    CodeExtPos* pwastebitem = new CodeExtPos(m_actextpos);
                    pwastebitem->SetParas(AXES_IDX_B, 50, m_btnquick->GetWasteB(), 0, m_btnquick->GetWasteBType());
                    m_teachmodel->InsertCode(pwastebitem, idx);

                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeExtPos* pwasteaitem = new CodeExtPos(m_actextpos);
                    pwasteaitem->SetParas(AXES_IDX_A, 50, m_btnquick->GetWasteA(), 0, m_btnquick->GetWasteAType());
                    m_teachmodel->InsertCode(pwasteaitem, idx);
                }

                // 关闭治具
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeVacuum* pwastevaccloseitem = new CodeVacuum(m_actvacuum);
                if ((m_btnquick->GetVacuumBmp()>>16)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 0;
                if ((m_btnquick->GetVacuumBmp()>>17)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 1;
                if ((m_btnquick->GetVacuumBmp()>>18)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 2;
                if ((m_btnquick->GetVacuumBmp()>>19)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 3;
                if ((m_btnquick->GetVacuumBmp()>>20)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 4;
                if ((m_btnquick->GetVacuumBmp()>>21)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 5;
                if ((m_btnquick->GetVacuumBmp()>>22)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 6;
                if ((m_btnquick->GetVacuumBmp()>>23)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 7;
                if ((m_btnquick->GetVacuumBmp()>>24)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 8;
                if ((m_btnquick->GetVacuumBmp()>>25)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 9;
                if ((m_btnquick->GetVacuumBmp()>>26)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 10;
                if ((m_btnquick->GetVacuumBmp()>>27)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 11;
                if ((m_btnquick->GetVacuumBmp()>>28)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 12;
                if ((m_btnquick->GetVacuumBmp()>>29)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 13;
                pwastevaccloseitem->SetParas(0, 50, (quint16)(m_btnquick->GetVacuumBmp()>>16), checkbmp, 0);
                m_teachmodel->InsertCode(pwastevaccloseitem, idx);


                if(pModbus->GetRunnerUse())//气动副臂使用
                {
					if(m_btnquick->GetRunnerWasterState())
                    {
                        if (m_teachmodel->GetItemCount()>(idx+1))
                            idx ++;
                        CodeRArm* prarmputwateritem = new CodeRArm(m_actrun);
                        prarmputwateritem->SetParas(RUN_ACT_ASCENT,50);
                        m_teachmodel->InsertCode(prarmputwateritem,idx);
                    }

                }
                else
                {
                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeExtPos* pwaitaitemback = new CodeExtPos(m_actextpos);
                    pwaitaitemback->SetParas(AXES_IDX_A, 50, m_btnquick->GetWaitA(), 0, m_btnquick->GetWaitAType());
                    m_teachmodel->InsertCode(pwaitaitemback, idx);
                }
            }
            else//先放水口
            {
                // 放水口
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwastezitem = new CodeExtPos(m_actextpos);
                pwastezitem->SetParas(AXES_IDX_Z, 50, m_btnquick->GetWasteZ(), 0, m_btnquick->GetWasteZType());
                m_teachmodel->InsertCode(pwastezitem, idx);

                if(pModbus->GetRunnerUse())//气动副臂使用
                {
					if(m_btnquick->GetRunnerWasterState())
                    {
                        if (m_teachmodel->GetItemCount()>(idx+1))
                            idx ++;
                        CodeRArm* prarmputwateritem = new CodeRArm(m_actrun);
                        prarmputwateritem->SetParas(RUN_ACT_DESCENT,50);
                        m_teachmodel->InsertCode(prarmputwateritem,idx);
                    }
                }
                else
                {
                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeExtPos* pwastebitem = new CodeExtPos(m_actextpos);
                    pwastebitem->SetParas(AXES_IDX_B, 50, m_btnquick->GetWasteB(), 0, m_btnquick->GetWasteBType());
                    m_teachmodel->InsertCode(pwastebitem, idx);

                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeExtPos* pwasteaitem = new CodeExtPos(m_actextpos);
                    pwasteaitem->SetParas(AXES_IDX_A, 50, m_btnquick->GetWasteA(), 0, m_btnquick->GetWasteAType());
                    m_teachmodel->InsertCode(pwasteaitem, idx);
                }

                // 关闭治具
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeVacuum* pwastevaccloseitem = new CodeVacuum(m_actvacuum);
                if ((m_btnquick->GetVacuumBmp()>>16)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 0;
                if ((m_btnquick->GetVacuumBmp()>>17)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 1;
                if ((m_btnquick->GetVacuumBmp()>>18)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 2;
                if ((m_btnquick->GetVacuumBmp()>>19)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 3;
                if ((m_btnquick->GetVacuumBmp()>>20)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 4;
                if ((m_btnquick->GetVacuumBmp()>>21)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 5;
                if ((m_btnquick->GetVacuumBmp()>>22)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 6;
                if ((m_btnquick->GetVacuumBmp()>>23)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 7;
                if ((m_btnquick->GetVacuumBmp()>>24)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 8;
                if ((m_btnquick->GetVacuumBmp()>>25)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 9;
                if ((m_btnquick->GetVacuumBmp()>>26)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 10;
                if ((m_btnquick->GetVacuumBmp()>>27)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 11;
                if ((m_btnquick->GetVacuumBmp()>>28)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 12;
                if ((m_btnquick->GetVacuumBmp()>>29)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>3)&1) << 13;
                pwastevaccloseitem->SetParas(0, 50, (quint16)(m_btnquick->GetVacuumBmp()>>16), checkbmp, 0);
                m_teachmodel->InsertCode(pwastevaccloseitem, idx);

                if(pModbus->GetRunnerUse())//气动副臂使用
                {
					if(m_btnquick->GetRunnerWasterState())
                    {
                        if (m_teachmodel->GetItemCount()>(idx+1))
                            idx ++;
                        CodeRArm* prarmputwateritem = new CodeRArm(m_actrun);
                        prarmputwateritem->SetParas(RUN_ACT_ASCENT,50);
                        m_teachmodel->InsertCode(prarmputwateritem,idx);
                    }
                }
                else
                {
                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeExtPos* pwaitaitemback = new CodeExtPos(m_actextpos);
                    pwaitaitemback->SetParas(AXES_IDX_A, 50, m_btnquick->GetWaitA(), 0, m_btnquick->GetWaitAType());
                    m_teachmodel->InsertCode(pwaitaitemback, idx);

                }
                if ((m_btnquick->GetCheckBoxState() >> 10)&1) // 矩阵使用
                {
                    bool rel[3]; quint16 num[3]; qint16 interval[3]; qint32 pos[3];
                    rel[0] = false; rel[1] = false; rel[2] = false;
                    pos[0] = 0; pos[1] = 0; pos[2] = 0;
                    interval[0] = 0; interval[1] = 0; interval[2] = 0;
                    num[0] = 1; num[1] = 1; num[2] = 1;

                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeLoopMatrix* pmatrixitem = new CodeLoopMatrix(m_actloopmatrix);
                    pmatrixitem->SetParas(50, 10, 50, ORDER_MODE_XYZ, false, true, false, ((m_btnquick->GetCheckBoxState()>>6&1) ? true : false), rel, num, interval, pos, 0, 0, 0);
                    m_teachmodel->InsertCode(pmatrixitem, idx);
                }
                else
                {
                    // 放成品
                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeExtPos* pproductzitem = new CodeExtPos(m_actextpos);
                    pproductzitem->SetParas(AXES_IDX_Z, 50, m_btnquick->GetProductZ(), 0, m_btnquick->GetProductZType());
                    m_teachmodel->InsertCode(pproductzitem, idx);

                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeExtPos* pproductxitem = new CodeExtPos(m_actextpos);
                    pproductxitem->SetParas(AXES_IDX_X, 50, m_btnquick->GetProductX(), 0, m_btnquick->GetProductXType());
                    m_teachmodel->InsertCode(pproductxitem, idx);

                    if (m_teachmodel->GetItemCount()>(idx+1))
                        idx ++;
                    CodeExtPos* pproductyitem = new CodeExtPos(m_actextpos);
                    pproductyitem->SetParas(AXES_IDX_Y, 50, m_btnquick->GetProductY(), 0, m_btnquick->GetProductYType());
                    m_teachmodel->InsertCode(pproductyitem, idx);
                }
                // 关闭治具
                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeVacuum* pfetchvaccloseitem = new CodeVacuum(m_actvacuum);
                // 获取治具检测对应表
                if ((m_btnquick->GetVacuumBmp()>>0)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 0;
                if ((m_btnquick->GetVacuumBmp()>>1)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 1;
                if ((m_btnquick->GetVacuumBmp()>>2)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 2;
                if ((m_btnquick->GetVacuumBmp()>>3)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 3;
                if ((m_btnquick->GetVacuumBmp()>>4)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 4;
                if ((m_btnquick->GetVacuumBmp()>>5)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 5;
                if ((m_btnquick->GetVacuumBmp()>>6)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 6;
                if ((m_btnquick->GetVacuumBmp()>>7)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 7;
                if ((m_btnquick->GetVacuumBmp()>>8)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 8;
                if ((m_btnquick->GetVacuumBmp()>>9)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 9;
                if ((m_btnquick->GetVacuumBmp()>>10)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 10;
                if ((m_btnquick->GetVacuumBmp()>>11)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 11;
                if ((m_btnquick->GetVacuumBmp()>>12)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 12;
                if ((m_btnquick->GetVacuumBmp()>>13)&1)
                    checkbmp = ((m_btnquick->GetCheckBoxState()>>2)&1) << 13;
                pfetchvaccloseitem->SetParas(0, 50, (quint16)m_btnquick->GetVacuumBmp(), checkbmp, 0);
                m_teachmodel->InsertCode(pfetchvaccloseitem, idx);

                if (m_teachmodel->GetItemCount()>(idx+1))
                    idx ++;
                CodeExtPos* pwaityitemback = new CodeExtPos(m_actextpos);
                pwaityitemback->SetParas(AXES_IDX_Y, 50, m_btnquick->GetWaitY(), 0, m_btnquick->GetWaitYType());
                m_teachmodel->InsertCode(pwaityitemback, idx);
            }
        }
//    }
    if (m_teachmodel->GetItemCount()>1)
        ui->BtnTechDelete->setEnabled(true);
    ui->tableView_teach->selectRow(idx);
    ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
    ui->BtnInsert->setEnabled(true);
}

void FormTeach::clickBtnPos(void)
{
    // 初始currentCode = 0；每次点击指令按钮，currentCode改变，显示指令界面，点击主菜单currentCode设为0，当currentCode=0时，点插入无效
    if (CMBProtocol::GetFunctions(SUB_FUN2_EXT_POS))
    {
        m_btnextpos->EnterForm();
        ui->groupBoxInstruction->setVisible(false);
        currentCode = CODE_EXTPOS;
    }
    else
    {
        m_btnpos->EnterForm();
        ui->groupBoxInstruction->setVisible(false);
        currentCode = CODE_POS;
    }
}
void FormTeach::clickBtnIMM(void)
{
    m_btnimm->EnterForm();
    ui->groupBoxInstruction->setVisible(false);
    currentCode = CODE_IMM;
}
void FormTeach::clickBtnVacuum(void)
{
    m_btnvacuum->EnterForm();
    ui->groupBoxInstruction->setVisible(false);
    currentCode = CODE_VACUUM;
}

void FormTeach::clickBtnAssist(void)
{
    m_btnassist->EnterForm();
    ui->groupBoxInstruction->setVisible(false);
    currentCode = VCODE_ASSIST;
}

void FormTeach::clickBtnPro(void)
{
    m_btnpro->EnterForm();
    ui->groupBoxInstruction->setVisible(false);
    currentCode = CODE_PROARM;
}
void FormTeach::clickBtnRun(void)
{
    m_btnrun->EnterForm();
    ui->groupBoxInstruction->setVisible(false);
    currentCode = CODE_RUNARM;
}

void FormTeach::clickBtnMatrix(void)
{
    bool rel[3], isrunner, trvrot, horizontal, decaxes, ConveyorUse;
    int pos[3];
    quint8 spd, dspd, decaxesprior;
    quint8 Horspd, Trvspd;
    quint16 num[3], dlen, converyorDelay, converyorOut;
    qint16 interval[3];
    m_actloopmatrix->EnterForm(true);
    int ret = m_dialogparaedit->exec();
    currentCode = CODE_MATRIX;
    int idx = ui->tableView_teach->currentIndex().row();

    spd = m_actloopmatrix->GetSpeed();
    Horspd = m_actloopmatrix->GetHorSpeed();
    Trvspd = m_actloopmatrix->GetTrvSpeed();
    dspd = m_actloopmatrix->GetDSpeed();
    dlen = m_actloopmatrix->GetDLen();
    decaxesprior = m_actloopmatrix->GetFirstDec();
    isrunner = m_actloopmatrix->GetIsRunner();
    trvrot = m_actloopmatrix->GetTrvRot();
    decaxes = m_actloopmatrix->GetXDec();
    horizontal = m_actloopmatrix->GetRotate();
    rel[0] = false; //m_actloopmatrix->GetHorRel();
    rel[1] = false; //m_actloopmatrix->GetVerRel();
    rel[2] = false; //m_actloopmatrix->GetTrvRel();
    pos[0] = m_actloopmatrix->GetX(0);
    pos[1] = m_actloopmatrix->GetY(0);
    pos[2] = m_actloopmatrix->GetZ(0);
    interval[0] = m_actloopmatrix->GetX(1);
    interval[1] = m_actloopmatrix->GetY(1);
    interval[2] = m_actloopmatrix->GetZ(1);
    num[0] = m_actloopmatrix->GetX(2);
    num[1] = m_actloopmatrix->GetY(2);
    num[2] = m_actloopmatrix->GetZ(2);
    converyorDelay = m_actloopmatrix->GetConveyor_delay();
    converyorOut = m_actloopmatrix->GetConveyor_out();
    ConveyorUse = m_actloopmatrix->GetConveyor_use();
	if (ret == QDialog::Accepted)
    {
        if (m_teachmodel->GetItemCount()>(idx+1))
            idx ++;
        CodeLoopMatrix* pitem = new CodeLoopMatrix(m_actloopmatrix);
        pitem->SetParas(spd, dspd, dlen, decaxesprior, isrunner, trvrot, decaxes, horizontal, rel, num, interval, pos, converyorDelay, converyorOut, ConveyorUse, Horspd, Trvspd);
        m_teachmodel->InsertCode(pitem, idx);
    }
    if (m_teachmodel->GetItemCount()>1)
        ui->BtnTechDelete->setEnabled(true);
    ui->tableView_teach->selectRow(idx);
    ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
    currentCode = 0xFF;
    m_actloopmatrix->hide();
}
void FormTeach::clickBtnDelay(void)
{
    int delay = m_actdelay->GetDelay();
    int idx = ui->tableView_teach->currentIndex().row();
    if (m_teachmodel->GetItemCount()>(idx+1))
        idx ++;
    CodeDelay* pitem = new CodeDelay(m_actdelay);
    pitem->SetParas(delay);
    m_teachmodel->InsertCode(pitem, idx);
    m_teachmodel->SavePara(idx, false);
    SaveProgram(idx);
    ui->BtnTechDelete->setEnabled(true);
    currentCode = CODE_DELAY;
    ui->tableView_teach->selectRow(idx);
    ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());//idx

}

void FormTeach::clickBtnWait(void)
{
    m_btnwait->EnterForm();
    ui->groupBoxInstruction->setVisible(false);
    currentCode = CODE_WAIT;
}
void FormTeach::clickBtnMExtout(void)
{
    m_btnextout->EnterForm();
    ui->groupBoxInstruction->setVisible(false);
    currentCode = CODE_EXT_OUT;
}
void FormTeach::clickBtnOther(void)
{
    int bakpos = 0;
    int curProcess = m_teachmodel->GetCurProcess(); // 当前进程
    int pos = ui->tableView_teach->currentIndex().row();
    if (pos < 0)
    {
        qDebug()<<"fuck FormTeach::clickBtnOther";
        return;
    }
    // 这里不需要保存了
//    m_teachmodel->SavePara(pos);
    if (m_teachmodel->IsModified())
        ChangeSelect(pos);

    if (m_actdlg->exec(curProcess) == QDialog::Accepted)
    {
        //Insert Code
        XmlModelItem *pitem = GetCodeItem(m_actdlg->GetCode());
        if (pitem)
        {
            if (m_teachmodel->GetItemCount()>(pos+1))
            {
                pos ++;
            }
            m_teachmodel->InsertCode(pitem, pos);
            bakpos = pos;
            ChangeSelect(pos);
        }
        if (m_actdlg->GetCode()==CODE_TBEGIN)
        {
            pitem = GetCodeItem(CODE_TEND);
            if (pitem)
            {
                if (m_teachmodel->GetItemCount()>(pos+1))
                {
                    pos ++;
                }
                m_teachmodel->InsertCode(pitem, pos);
                ChangeSelect(bakpos);
            }
        }
        if (m_actdlg->GetCode()==CODE_IF)
        {
            pitem = GetCodeItem(CODE_ENDIF);
            if (pitem)
            {
                if (m_teachmodel->GetItemCount()>(pos+1))
                {
                    pos ++;
                }
                m_teachmodel->InsertCode(pitem, pos);
                ChangeSelect(bakpos);
            }
        }
        if ((m_actdlg->GetCode()==CODE_FOR_CONST)||
            (m_actdlg->GetCode()==CODE_FOR_VAR))
        {
            pitem = GetCodeItem(CODE_ENDFOR);
            if (pitem)
            {
                if (m_teachmodel->GetItemCount()>(pos+1))
                {
                    pos ++;
                }
                m_teachmodel->InsertCode(pitem, pos);
                ChangeSelect(bakpos);
            }
        }
        if (m_teachmodel->GetItemCount()>1)
        {
            ui->BtnTechDelete->setEnabled(true);
        }
        ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
    }
}void FormTeach::keyRelease(quint32 key)
{
    int currentRow = 0;
    currentRow = ui->tableView_teach->currentIndex().row();

    switch (key)
    {
    case ENCODER_CW:
        if ((currentRow+1) > ui->tableView_teach->model()->rowCount())
            return;
        ui->tableView_teach->selectRow(currentRow+1);
        ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
        break;
    case ENCODER_CCW:
        if ((currentRow-1) < 0)
            return;
        ui->tableView_teach->selectRow(currentRow-1);
        ui->tableView_teach->scrollTo(ui->tableView_teach->currentIndex());
        break;
    }
    QModelIndex index;
    tableViewClicked(index);
}
