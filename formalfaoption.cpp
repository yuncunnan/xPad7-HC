#include <QButtonGroup>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "xconfig.h"
#include "cmbprotocol.h"
#include "dialogframe.h"
#include "alfamodel.h"
#include "xstringresource.h"
#include "xsystemlog.h"
#include "xmessagebox.h"
#include "dialognumberpad.h"
#include "formalfaoption.h"
#include "ui_formalfaoption.h"
#include "servoalias.h"
#include "dialogselectvariable.h"
#include <QDebug>

#define TAB_PAGE_PRO        0
#define TAB_PAGE_RUN        1
#define TAB_PAGE_SPD        2
#define TAB_PAGE_JIG        3
#define TAB_PAGE_MATRIX     4
#define TAB_PAGE_IMM        5
#define TAB_PAGE_CONVEYOR   6

extern DialogFrame *pDialogMain;

Formalfaoption::Formalfaoption(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::Formalfaoption), pgmModel(false)
{
	ui->setupUi(this);
    retranslateUi();
    pModbus = modbus;
	m_alfamodel = new AlfaModel(this);
	Axis[0] = AXIS_IDX_PHOR;
    Axis[1] = AXIS_IDX_PVER;
    Axis[2] = AXIS_IDX_TRV;
	// 设置原点第一行默认选中
	ui->tableWidgetAxis->setCurrentCell(0, 0);
	ui->tableWidgetAxis->setFocus();

    pTrvInBtn = new QButtonGroup;
    pTrvInBtn->addButton(ui->checkBoxTrvInHor, 1);
    pTrvInBtn->addButton(ui->checkBoxTrvInVer, 0);

    pTrvOutBtn = new QButtonGroup;
    pTrvOutBtn->addButton(ui->checkBoxTrvOutHor, 1);
    pTrvOutBtn->addButton(ui->checkBoxTrvOutVer, 0);

    pFetchBtn = new QButtonGroup;
    pFetchBtn->addButton(ui->checkBoxFetchHor, 1);
    pFetchBtn->addButton(ui->checkBoxFetchVer, 0);

    pReleaseBtn = new QButtonGroup;
    pReleaseBtn->addButton(ui->checkBoxReleaseHor, 1);
    pReleaseBtn->addButton(ui->checkBoxReleaseVer, 0);

	QFont font;
	font.setPixelSize(28); // 设置字号为28像素
	for(int i=0;i<ui->tableWidgetAxis->rowCount();i++)
	{
		ui->tableWidgetAxis->item(i,0)->setFont(font);
		ui->tableWidgetAxis->verticalHeaderItem(i)->setFont(font);
	}
}

Formalfaoption::~Formalfaoption()
{
	delete ui;
}

// 检查参数是否修改
bool Formalfaoption::isModified(void)
{
    if (ui->ProJig1->isChecked() != ((m_alfamodel->GetProVacBmp()>>0) & 1)) return true;
    if (ui->ProJig2->isChecked() != ((m_alfamodel->GetProVacBmp()>>1) & 1)) return true;
    if (ui->ProJig3->isChecked() != ((m_alfamodel->GetProVacBmp()>>2) & 1)) return true;
    if (ui->ProJig4->isChecked() != ((m_alfamodel->GetProVacBmp()>>3) & 1)) return true;
    if (ui->ProJig5->isChecked() != ((m_alfamodel->GetProVacBmp()>>4) & 1)) return true;
    if (ui->ProJig6->isChecked() != ((m_alfamodel->GetProVacBmp()>>5) & 1)) return true;
    if (ui->RunJig1->isChecked() != ((m_alfamodel->GetRunVacBmp()>>0) & 1)) return true;
    if (ui->RunJig2->isChecked() != ((m_alfamodel->GetRunVacBmp()>>1) & 1)) return true;
    if (ui->RunJig3->isChecked() != ((m_alfamodel->GetRunVacBmp()>>2) & 1)) return true;
    if (ui->RunJig4->isChecked() != ((m_alfamodel->GetRunVacBmp()>>3) & 1)) return true;
    if (ui->RunJig5->isChecked() != ((m_alfamodel->GetRunVacBmp()>>4) & 1)) return true;
    if (ui->RunJig6->isChecked() != ((m_alfamodel->GetRunVacBmp()>>5) & 1)) return true;
    if (ui->ProCheck1->isChecked() != ((m_alfamodel->GetProVacChk()>>0) & 1)) return true;
    if (ui->ProCheck2->isChecked() != ((m_alfamodel->GetProVacChk()>>1) & 1)) return true;
    if (ui->ProCheck3->isChecked() != ((m_alfamodel->GetProVacChk()>>2) & 1)) return true;
    if (ui->ProCheck4->isChecked() != ((m_alfamodel->GetProVacChk()>>3) & 1)) return true;
    if (ui->ProCheck5->isChecked() != ((m_alfamodel->GetProVacChk()>>4) & 1)) return true;
    if (ui->ProCheck6->isChecked() != ((m_alfamodel->GetProVacChk()>>5) & 1)) return true;
    if (ui->RunCheck1->isChecked() != ((m_alfamodel->GetRunVacChk()>>0) & 1)) return true;
    if (ui->RunCheck2->isChecked() != ((m_alfamodel->GetRunVacChk()>>1) & 1)) return true;
    if (ui->RunCheck3->isChecked() != ((m_alfamodel->GetRunVacChk()>>2) & 1)) return true;
    if (ui->RunCheck4->isChecked() != ((m_alfamodel->GetRunVacChk()>>3) & 1)) return true;
    if (ui->RunCheck5->isChecked() != ((m_alfamodel->GetRunVacChk()>>4) & 1)) return true;
    if (ui->RunCheck6->isChecked() != ((m_alfamodel->GetRunVacChk()>>5) & 1)) return true;

    if (ui->cBoxProMode->currentIndex() != m_alfamodel->GetProMode()) return true;
    if (ui->cBoxRunMode->currentIndex() != m_alfamodel->GetRunMode()) return true;

//    if (ui->cBoxProReleaseMode->currentIndex() != m_alfamodel->GetProReleaseMode()) return true;
    if (qRound(ui->BoxProDelay->value()*(1000.0/TIME_BASE)) != m_alfamodel->GetProVacDelay()) return true;
    if (qRound(ui->BoxRunDelay->value()*(1000.0/TIME_BASE)) != m_alfamodel->GetRunVacDelay()) return true;
    if (qRound(ui->BoxRotateDelay->value()*(1000.0/TIME_BASE)) != m_alfamodel->GetRotateDelay()) return true;
    if (ui->checkBoxEjectorFront->isChecked() != m_alfamodel->UseEjectorFront()) return true;
    if (ui->checkBoxEjectorBack->isChecked() != m_alfamodel->UseEjectorBack()) return true;
    if (ui->checkBoxC1Front->isChecked() != m_alfamodel->UseC1Front()) return true;
    if (ui->checkBoxC1Back->isChecked() != m_alfamodel->UseC1Back()) return true;
    if (ui->checkBoxC2Front->isChecked() != m_alfamodel->UseC2Front()) return true;
    if (ui->checkBoxC2Back->isChecked() != m_alfamodel->UseC2Back()) return true;

    if (qRound(ui->BoxEjectorFrontDelay->value()*(1000.0/TIME_BASE)) != m_alfamodel->GetEjectorFrontDelay()) return true;
    if (qRound(ui->BoxMOPTimeout->value()*(1000.0/TIME_BASE)) != m_alfamodel->GetMOPTimeout()) return true;
    if (qRound(ui->BoxEMCDelay->value()*(1000.0/TIME_BASE)) != m_alfamodel->GetEMCDelay()) return true;

    if (qRound(ui->BoxProRelPos->value()*100.0) != m_alfamodel->GetZProReleasePos()) return true;
    if (qRound(ui->BoxRunRelPos->value()*100.0) != m_alfamodel->GetZRunReleasePos()) return true;
    if (qRound(ui->BoxCatchPos->value()*100.0) != m_alfamodel->GetZCatchPos()) return true;
    if (qRound(ui->BoxXProDown->value()*100.0) != m_alfamodel->GetXProDownPos()) return true;
    if (qRound(ui->BoxXProCatch->value()*100.0) != m_alfamodel->GetXProCatchPos()) return true;
    if (qRound(ui->BoxBRunCatch->value()*100.0) != m_alfamodel->GetBRunCatchPos()) return true;
    if (qRound(ui->BoxBRunDown->value()*100.0) != m_alfamodel->GetBRunDownPos()) return true;
    if (qRound(ui->BoxYProCatch->value()*100.0) != m_alfamodel->GetYProCatchPos()) return true;
    if (qRound(ui->BoxARunCatch->value()*100.0) != m_alfamodel->GetARunCatchPos()) return true;
    if (qRound(ui->BoxYProRel->value()*100.0) != m_alfamodel->GetYProReleasePos()) return true;
    if (qRound(ui->BoxARunRel->value()*100.0) != m_alfamodel->GetARunReleasePos()) return true;
    if (qRound(ui->BoxXProRel->value()*100.0) != m_alfamodel->GetXProReleasePos()) return true;
    if (qRound(ui->BoxBRunRel->value()*100.0) != m_alfamodel->GetBRunReleasePos()) return true;
    if (qRound(ui->BoxYProWait->value()*100.0) != m_alfamodel->GetYProWaitPos()) return true;
    if (qRound(ui->BoxARunWait->value()*100.0) != m_alfamodel->GetARunWaitPos()) return true;
    if (qRound(ui->BoxXProUP->value()*100.0) != m_alfamodel->GetXProUpPos()) return true;
    if (qRound(ui->BoxBRunUP->value()*100.0) != m_alfamodel->GetBRunUpPos()) return true;

    if (ui->checkBoxConveyor->isChecked() != m_alfamodel->UseConveyor()) return true;
    if (qRound(ui->BoxConveyorDelay->value()*(1000.0/TIME_BASE)) != m_alfamodel->GetConveyorDelay()) return true;
//    if (qRound(ui->BoxConveyorInterval->value()*(1000.0/TIME_BASE)) != m_alfamodel->GetConveyorInterval()) return true;
    if (ui->BoxConveyorInterval->value() != m_alfamodel->GetConveyorInterval()) return true;
    if (outport != m_alfamodel->GetConveyorOut()) return true;

    if (ui->BoxXSpeed->value() != m_alfamodel->GetXSpeed()) return true;
    if (ui->BoxYSpeed->value() != m_alfamodel->GetYSpeed()) return true;
    if (ui->BoxZSpeed->value() != m_alfamodel->GetZSpeed()) return true;
    if (ui->BoxASpeed->value() != m_alfamodel->GetASpeed()) return true;
    if (ui->BoxBSpeed->value() != m_alfamodel->GetBSpeed()) return true;
    if (ui->BoxCSpeed->value() != m_alfamodel->GetCSpeed()) return true;
    if (ui->BoxYSpeedOut->value() != m_alfamodel->GetYSpeedOut()) return true;
    if (ui->BoxASpeedOut->value() != m_alfamodel->GetASpeedOut()) return true;

    if (ui->checkBox_rotate->isChecked() != m_alfamodel->GetMatrixHor()) return true;
    if (ui->checkBoxIsRunner->isChecked() != m_alfamodel->GetMatrixIsRunner()) return true;
    if (ui->checkBoxTrvRot->isChecked() != m_alfamodel->GetMatrixTrvrot()) return true;
    if (ui->checkBox_xdec->isChecked() != m_alfamodel->GetMatrixDecAxis()) return true;
    if (ui->checkBoxHorRel->isChecked() != m_alfamodel->GetMatrixRelx()) return true;
    if (ui->checkBoxVerRel->isChecked() != m_alfamodel->GetMatrixRely()) return true;
    if (ui->checkBoxTrvRel->isChecked() != m_alfamodel->GetMatrixRelz()) return true;
    if (ui->BoxHspd->value() != m_alfamodel->GetMatrixSpeed()) return true;
    if (ui->BoxLspd->value() != m_alfamodel->GetMatrixdSpeed()) return true;
    if (ui->BoxLowDis->value() != m_alfamodel->GetMatrixdlen()) return true;
    if (ui->BoxHorCnt->value() != m_alfamodel->GetMatrixXS()) return true;
    if (ui->BoxVerCnt->value() != m_alfamodel->GetMatrixYS()) return true;
    if (ui->BoxTrvCnt->value() != m_alfamodel->GetMatrixZS()) return true;

    if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
    {
        if (qRound(ui->BoxHorInt->value()* 10.0) != m_alfamodel->GetMatrixXInterval()) return true;
        if (qRound(ui->BoxVerInt->value()* 10.0) != m_alfamodel->GetMatrixYInterval()) return true;
        if (qRound(ui->BoxTrvInt->value()* 10.0) != m_alfamodel->GetMatrixZInterval()) return true;
    }
    else
    {
        if (qRound(ui->BoxHorInt->value()* 100.0) != m_alfamodel->GetMatrixXInterval()) return true;
        if (qRound(ui->BoxVerInt->value()* 100.0) != m_alfamodel->GetMatrixYInterval()) return true;
        if (qRound(ui->BoxTrvInt->value()* 100.0) != m_alfamodel->GetMatrixZInterval()) return true;
    }
    if (qRound(ui->BoxHorPos->value()* 100.0) != m_alfamodel->GetMatrixPosx()) return true;
    if (qRound(ui->BoxVerPos->value()* 100.0) != m_alfamodel->GetMatrixPosy()) return true;
    if (qRound(ui->BoxTrvPos->value()* 100.0) != m_alfamodel->GetMatrixPosz()) return true;
    if (GetFirstDec() != m_alfamodel->GetMatrixDecPrior()) return true;

    if (pTrvInBtn->checkedId() != m_alfamodel->GetTrvInRotate()) return true;
    if (pTrvOutBtn->checkedId() != m_alfamodel->GetTrvOutRotate()) return true;
    if (pFetchBtn->checkedId() != m_alfamodel->GetFetchRotate()) return true;
    if (pReleaseBtn->checkedId() != m_alfamodel->GetReleaseRotate()) return true;
    if (ui->CheckBoxProReleaseUse->isChecked() != m_alfamodel->GetProReleaseUse()) return true;

    return false;
}

extern quint16 globlecodes[MAX_CODES];
extern quint32 globleparas[MAX_CODES];

// 保存参数设置
bool Formalfaoption::SaveAlfaPara(void)
{
	try
	{
        // 治具和气动参数
        quint16 probmp, runbmp, prochk, runchk;
		probmp  = ((quint16)ui->ProJig1->isChecked()?1:0) << 0;
        probmp |= ((quint16)ui->ProJig2->isChecked()?1:0) << 1;
        probmp |= ((quint16)ui->ProJig3->isChecked()?1:0) << 2;
        probmp |= ((quint16)ui->ProJig4->isChecked()?1:0) << 3;
        probmp |= ((quint16)ui->ProJig5->isChecked()?1:0) << 4;
        probmp |= ((quint16)ui->ProJig6->isChecked()?1:0) << 5;

        runbmp  = ((quint16)ui->RunJig1->isChecked()?1:0) << 0;
        runbmp |= ((quint16)ui->RunJig2->isChecked()?1:0) << 1;
        runbmp |= ((quint16)ui->RunJig3->isChecked()?1:0) << 2;
        runbmp |= ((quint16)ui->RunJig4->isChecked()?1:0) << 3;
        runbmp |= ((quint16)ui->RunJig5->isChecked()?1:0) << 4;
        runbmp |= ((quint16)ui->RunJig6->isChecked()?1:0) << 5;

        prochk  = ((quint16)(ui->ProCheck1->isChecked()?1:0 && ui->ProCheck1->isEnabled()) << 0);
        prochk |= ((quint16)(ui->ProCheck2->isChecked()?1:0 && ui->ProCheck2->isEnabled()) << 1);
        prochk |= ((quint16)(ui->ProCheck3->isChecked()?1:0 && ui->ProCheck3->isEnabled()) << 2);
        prochk |= ((quint16)(ui->ProCheck4->isChecked()?1:0 && ui->ProCheck4->isEnabled()) << 3);
        prochk |= ((quint16)(ui->ProCheck5->isChecked()?1:0 && ui->ProCheck5->isEnabled()) << 4);
        prochk |= ((quint16)(ui->ProCheck6->isChecked()?1:0 && ui->ProCheck6->isEnabled()) << 5);

        runchk  = ((quint16)(ui->RunCheck1->isChecked()?1:0 && ui->RunCheck1->isEnabled()) << 0);
        runchk |= ((quint16)(ui->RunCheck2->isChecked()?1:0 && ui->RunCheck2->isEnabled()) << 1);
        runchk |= ((quint16)(ui->RunCheck3->isChecked()?1:0 && ui->RunCheck3->isEnabled()) << 2);
        runchk |= ((quint16)(ui->RunCheck4->isChecked()?1:0 && ui->RunCheck4->isEnabled()) << 3);
        runchk |= ((quint16)(ui->RunCheck5->isChecked()?1:0 && ui->RunCheck5->isEnabled()) << 4);
        runchk |= ((quint16)(ui->RunCheck6->isChecked()?1:0 && ui->RunCheck6->isEnabled()) << 5);

        m_alfamodel->SetProVacBmp(probmp);
        m_alfamodel->SetRunVacBmp(runbmp);
        m_alfamodel->SetProVacChk(prochk);
        m_alfamodel->SetRunVacChk(runchk);
        m_alfamodel->SetProVacDelay(qRound(ui->BoxProDelay->value()* (1000.0/TIME_BASE)));
        m_alfamodel->SetRunVacDelay(qRound(ui->BoxRunDelay->value()* (1000.0/TIME_BASE)));
        m_alfamodel->SetRotateDelay(qRound(ui->BoxRotateDelay->value()* (1000.0/TIME_BASE)));
        // 模式和位置
        m_alfamodel->SetProMode(ui->cBoxProMode->currentIndex());
        m_alfamodel->SetRunMode(ui->cBoxRunMode->currentIndex());
        m_alfamodel->SetZProReleasePos(qRound(ui->BoxProRelPos->value() * 100.0));
        m_alfamodel->SetZRunReleasePos(qRound(ui->BoxRunRelPos->value() * 100.0));
        m_alfamodel->SetZCatchPos(qRound(ui->BoxCatchPos->value() * 100.0));
        m_alfamodel->SetXProDownPos(qRound(ui->BoxXProDown->value() * 100.0));
        m_alfamodel->SetXProCatchPos(qRound(ui->BoxXProCatch->value() * 100.0));
        m_alfamodel->SetBRunDownPos(qRound(ui->BoxBRunDown->value() * 100.0));
        m_alfamodel->SetBRunCatchPos(qRound(ui->BoxBRunCatch->value() * 100.0));
        m_alfamodel->SetYProCatchPos(qRound(ui->BoxYProCatch->value() * 100.0));
        m_alfamodel->SetYProReleasePos(qRound(ui->BoxYProRel->value() * 100.0));
        m_alfamodel->SetARunCatchPos(qRound(ui->BoxARunCatch->value() * 100.0));
        m_alfamodel->SetARunReleasePos(qRound(ui->BoxARunRel->value() * 100.0));
        m_alfamodel->SetXProReleasePos(qRound(ui->BoxXProRel->value() * 100.0));
        m_alfamodel->SetBRunReleasePos(qRound(ui->BoxBRunRel->value() * 100.0));
        m_alfamodel->SetYProWaitPos(qRound(ui->BoxYProWait->value() * 100.0));
        m_alfamodel->SetARunWaitPos(qRound(ui->BoxARunWait->value() * 100.0));
        m_alfamodel->SetXProUpPos(qRound(ui->BoxXProUP->value() * 100.0));
        m_alfamodel->SetBRunUpPos(qRound(ui->BoxBRunUP->value() * 100.0));

        m_alfamodel->SetXSpeed(ui->BoxXSpeed->value());
        m_alfamodel->SetYSpeed(ui->BoxYSpeed->value());
        m_alfamodel->SetZSpeed(ui->BoxZSpeed->value());
        m_alfamodel->SetASpeed(ui->BoxASpeed->value());
        m_alfamodel->SetBSpeed(ui->BoxBSpeed->value());
        m_alfamodel->SetCSpeed(ui->BoxCSpeed->value());
        m_alfamodel->SetYSpeedOut(ui->BoxYSpeedOut->value());
        m_alfamodel->SetASpeedOut(ui->BoxASpeedOut->value());
        // 塑机参数
        m_alfamodel->SetEjectorFront(ui->checkBoxEjectorFront->isChecked()?1:0);
        m_alfamodel->setEjectorFrontDelay(qRound(ui->BoxEjectorFrontDelay->value() * (1000.0/TIME_BASE)));
        m_alfamodel->SetEjectorBack(ui->checkBoxEjectorBack->isChecked()?1:0);
        m_alfamodel->setEjectorBackDelay(qRound(ui->BoxEjectorBackDelay->value() * (1000.0/TIME_BASE)));
        m_alfamodel->SetC1Front(ui->checkBoxC1Front->isChecked()?1:0);
        m_alfamodel->setC1FrontDelay(qRound(ui->BoxC1FrontDelay->value() * (1000.0/TIME_BASE)));
        m_alfamodel->SetC1Back(ui->checkBoxC1Back->isChecked()?1:0);
        m_alfamodel->setC1BackDelay(qRound(ui->BoxC1BackDelay->value() * (1000.0/TIME_BASE)));
        m_alfamodel->SetC2Front(ui->checkBoxC2Front->isChecked()?1:0);
        m_alfamodel->setC2FrontDelay(qRound(ui->BoxC2FrontDelay->value() * (1000.0/TIME_BASE)));
        m_alfamodel->SetC2Back(ui->checkBoxC2Back->isChecked()?1:0);
        m_alfamodel->setC2BackDelay(qRound(ui->BoxC2BackDelay->value() * (1000.0/TIME_BASE)));

        m_alfamodel->SetMOPTimeout(qRound(ui->BoxMOPTimeout->value() * (1000.0/TIME_BASE)));
        m_alfamodel->SetEMCDelay(qRound(ui->BoxEMCDelay->value() * (1000.0/TIME_BASE)));

        m_alfamodel->SetConveyor(ui->checkBoxConveyor->isChecked()?1:0);
        m_alfamodel->SetConveyorDelay(qRound(ui->BoxConveyorDelay->value() * (1000.0/TIME_BASE)));
        m_alfamodel->SetConveyorInterval(ui->BoxConveyorInterval->value());
        m_alfamodel->SetConveyorOut(outport);

        // 矩阵
        m_alfamodel->SetMatrixHor(ui->checkBox_rotate->isChecked()?1:0);
        m_alfamodel->SetMatrixIsRunner(ui->checkBoxIsRunner->isChecked()?1:0);
        m_alfamodel->SetMatrixTrvrot(ui->checkBoxTrvRot->isChecked()?1:0);
        m_alfamodel->SetMatrixDecAxis(ui->checkBox_xdec->isChecked()?1:0);
        m_alfamodel->SetMatrixRelx(ui->checkBoxHorRel->isChecked()?1:0);
        m_alfamodel->SetMatrixRely(ui->checkBoxVerRel->isChecked()?1:0);
        m_alfamodel->SetMatrixRelz(ui->checkBoxTrvRel->isChecked()?1:0);
        m_alfamodel->SetMatrixSpeed(ui->BoxHspd->value());
        m_alfamodel->SetMatrixdSpeed(ui->BoxLspd->value());
        m_alfamodel->SetMatrixdlen(ui->BoxLowDis->value());
        m_alfamodel->SetMatrixXS(ui->BoxHorCnt->value());
        m_alfamodel->SetMatrixYS(ui->BoxVerCnt->value());
        m_alfamodel->SetMatrixZS(ui->BoxTrvCnt->value());
        m_alfamodel->SetMatrixPosx(qRound(ui->BoxHorPos->value()* 100.0));
        m_alfamodel->SetMatrixPosy(qRound(ui->BoxVerPos->value()* 100.0));
        m_alfamodel->SetMatrixPosz(qRound(ui->BoxTrvPos->value()* 100.0));
        if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
        {
            m_alfamodel->SetMatrixXInterval(qRound(ui->BoxHorInt->value()* 10.0));
            m_alfamodel->SetMatrixYInterval(qRound(ui->BoxVerInt->value()* 10.0));
            m_alfamodel->SetMatrixZInterval(qRound(ui->BoxTrvInt->value()* 10.0));
        }
        else
        {
            m_alfamodel->SetMatrixXInterval(qRound(ui->BoxHorInt->value()* 100.0));
            m_alfamodel->SetMatrixYInterval(qRound(ui->BoxVerInt->value()* 100.0));
            m_alfamodel->SetMatrixZInterval(qRound(ui->BoxTrvInt->value()* 100.0));
        }
        m_alfamodel->SetMatrixDecPrior(GetFirstDec());

        m_alfamodel->SetTrvInRotate(pTrvInBtn->checkedId());
        m_alfamodel->SetTrvOutRotate(pTrvOutBtn->checkedId());
        m_alfamodel->SetFetchRotate(pFetchBtn->checkedId());
        m_alfamodel->SetReleaseRotate(pReleaseBtn->checkedId());
        m_alfamodel->SetProReleaseUse(ui->CheckBoxProReleaseUse->isChecked()?1:0);

        // 保存程序
        m_alfamodel->SaveProgram();
        m_alfamodel->CreateRunPgm();
    }
	catch (bool &)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAVE_PARA_ERROR));
		return false;
	}
    // ////////////////////////////////////////////////////////////////////////
    // //////////////////////////////////////////////////////////////////////////////////////
    if (CMBProtocol::GetSysState() == SYS_STATE_AUTO)
    {
        int procid;
        // 生成程序文件对应的机器代码并上传到主控模块
        quint32 codeCnt;
//        quint16 codes[MAX_CODES];
//        quint32 paras[MAX_CODES];
        if (pgmModel.LoadProgram(m_alfamodel->GetRunPgmName()) == false)
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

        // 生成程序文件机器代码
        for (procid=0; procid<MAX_PROCESS; procid++)
        {
            if (CMBProtocol::GetProcUse(procid))
            {
                codeCnt = pgmModel.GenerateCodes(procid, globlecodes, globleparas);
                // 上传机器代码
    /*            if (CMBProtocol::WriteCodes(codes, procid*MAX_CODES, codeCnt) != SENDMSG_RET_ACK)
                {
                    xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件指令到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
                    return false;
                }*/
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
    }

    // //////////////////////////////////////////////////////////////////////////////////////
	return true;
}
// 翻译界面
void Formalfaoption::changeEvent(QEvent *e)
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
void Formalfaoption::retranslateUi(void)
{
	ui->ProJig1->setText(xStringResource::GetVarName(EM1_VAR_Y02));
    ui->ProJig2->setText(xStringResource::GetVarName(EM1_VAR_Y03));
    ui->ProJig3->setText(xStringResource::GetVarName(EM1_VAR_Y04));
    ui->ProJig4->setText(xStringResource::GetVarName(EM1_VAR_Y05));
    ui->ProJig5->setText(xStringResource::GetVarName(EM1_VAR_Y06));
    ui->ProJig6->setText(xStringResource::GetVarName(EM1_VAR_Y07));
    ui->RunJig1->setText(xStringResource::GetVarName(EM1_VAR_Y02));
    ui->RunJig2->setText(xStringResource::GetVarName(EM1_VAR_Y03));
    ui->RunJig3->setText(xStringResource::GetVarName(EM1_VAR_Y04));
    ui->RunJig4->setText(xStringResource::GetVarName(EM1_VAR_Y05));
    ui->RunJig5->setText(xStringResource::GetVarName(EM1_VAR_Y06));
    ui->RunJig6->setText(xStringResource::GetVarName(EM1_VAR_Y07));
    ui->labelHorCnt->setText(GetServoName(AXIS_IDX_PHOR) + tr("点数："));
    ui->labelVerCnt->setText(GetServoName(AXIS_IDX_PVER) + tr("点数："));
    ui->labelTrvCnt->setText(GetServoName(AXIS_IDX_TRV) + tr("点数："));

    ui->labelHorInt->setText(GetServoName(AXIS_IDX_PHOR) + tr("间距："));
    ui->labelVerInt->setText(GetServoName(AXIS_IDX_PVER) + tr("间距："));
    ui->labelTrvInt->setText(GetServoName(AXIS_IDX_TRV) + tr("间距："));

    ui->labelHorPos->setText(GetServoName(AXIS_IDX_PHOR) + ("："));
    ui->labelVerPos->setText(GetServoName(AXIS_IDX_PVER) + ("："));
    ui->labelTrvPos->setText(GetServoName(AXIS_IDX_TRV) + ("："));

    ui->labelXSpeed->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴速度："));
    ui->labelYSpeed->setText(GetServoName(AXIS_IDX_PVER) + tr("轴速度："));
    ui->labelZSpeed->setText(GetServoName(AXIS_IDX_TRV) + tr("轴速度："));
    ui->labelASpeed->setText(GetServoName(AXIS_IDX_RVER) + tr("轴速度："));
    ui->labelBSpeed->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴速度："));
    ui->labelCSpeed->setText(GetServoName(AXIS_IDX_EXT) + tr("轴速度："));
    ui->labelYSpeedOut->setText(GetServoName(AXIS_IDX_PVER) + tr("轴模外速度："));
    ui->labelASpeedOut->setText(GetServoName(AXIS_IDX_RVER) + tr("轴模外速度："));
}

bool Formalfaoption::EnterForm(void)
{
    // 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return false;
	}
    // 检查用户权限
    if (xPermissions::GetPermissions(PER_TEACH) == false)
    {
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (pDialogMain)
            if (pDialogMain->ScreenSaverUserManager() == 0)
        return false;
    }
	// 如果系统不在手动状态则不能进入系统参数设置画面
//	if (pModbus->GetSysState() != SYS_STATE_MANUAL)
//	{
//		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SYSTEM_NO_MANUAL));
//		return false;
//	}
    if (pModbus->GetAlfaPgmName().isEmpty())
    {
        xMessageBox::DoWarning(tr("系统警告"), tr("没有载入当前程序文件，不能进入向导！"));
        return false;
    }
    if (m_alfamodel->LoadProgram(CMBProtocol::GetAlfaPgmName()) == false)
    {
        xMessageBox::DoWarning(tr("系统警告"), tr("装载当前程序文件出错，不能进入向导！"));
        return false;
    }
    if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
    {
        ui->BoxHorInt->setDecimals(1);
        ui->BoxHorInt->setMinimum(-3200.0);
        ui->BoxHorInt->setMaximum(3200.0);
        ui->BoxVerInt->setDecimals(1);
        ui->BoxVerInt->setMinimum(-3200.0);
        ui->BoxVerInt->setMaximum(3200.0);
        ui->BoxTrvInt->setDecimals(1);
        ui->BoxTrvInt->setMinimum(-3200.0);
        ui->BoxTrvInt->setMaximum(3200.0);
    }
    else
    {
        ui->BoxHorInt->setDecimals(2);
        ui->BoxHorInt->setMinimum(-320.00);
        ui->BoxHorInt->setMaximum(320.00);
        ui->BoxVerInt->setDecimals(2);
        ui->BoxVerInt->setMinimum(-320.00);
        ui->BoxVerInt->setMaximum(320.00);
        ui->BoxTrvInt->setDecimals(2);
        ui->BoxTrvInt->setMinimum(-320.00);
        ui->BoxTrvInt->setMaximum(320.00);
    }
    // 矩阵副臂隐藏
    ui->checkBoxIsRunner->setVisible(false);
    ui->labelCounter->setVisible(false);
    ui->lineEditCount->setVisible(false);
    // 得到模式和位置
    ui->cBoxProMode->setCurrentIndex(m_alfamodel->GetProMode());
    ui->cBoxRunMode->setCurrentIndex(m_alfamodel->GetRunMode());
    ui->BoxProRelPos->setValue((double)m_alfamodel->GetZProReleasePos() /100.0);
    ui->BoxRunRelPos->setValue((double)m_alfamodel->GetZRunReleasePos() /100.0);
    ui->BoxCatchPos->setValue((double)m_alfamodel->GetZCatchPos() /100.0);
    ui->BoxXProDown->setValue((double)m_alfamodel->GetXProDownPos() /100.0);
    ui->BoxXProCatch->setValue((double)m_alfamodel->GetXProCatchPos() /100.0);
    ui->BoxBRunCatch->setValue((double)m_alfamodel->GetBRunCatchPos() /100.0);
    ui->BoxBRunDown->setValue((double)m_alfamodel->GetBRunDownPos() /100.0);
    ui->BoxYProCatch->setValue((double)m_alfamodel->GetYProCatchPos() /100.0);
    ui->BoxYProRel->setValue((double)m_alfamodel->GetYProReleasePos() /100.0);
    ui->BoxARunCatch->setValue((double)m_alfamodel->GetARunCatchPos() /100.0);
    ui->BoxARunRel->setValue((double)m_alfamodel->GetARunReleasePos() /100.0);
    ui->BoxXProRel->setValue((double)m_alfamodel->GetXProReleasePos() /100.0);
    ui->BoxBRunRel->setValue((double)m_alfamodel->GetBRunReleasePos() /100.0);
    ui->BoxYProWait->setValue((double)m_alfamodel->GetYProWaitPos() /100.0);
    ui->BoxARunWait->setValue((double)m_alfamodel->GetARunWaitPos() /100.0);
    ui->BoxXProUP->setValue((double)m_alfamodel->GetXProUpPos() /100.0);
    ui->BoxBRunUP->setValue((double)m_alfamodel->GetBRunUpPos() /100.0);
    // 得到治具和气动设置
    ui->ProJig1->setChecked((m_alfamodel->GetProVacBmp() >> 0) & 1);
    ui->ProJig2->setChecked((m_alfamodel->GetProVacBmp() >> 1) & 1);
    ui->ProJig3->setChecked((m_alfamodel->GetProVacBmp() >> 2) & 1);
    ui->ProJig4->setChecked((m_alfamodel->GetProVacBmp() >> 3) & 1);
    ui->ProJig5->setChecked((m_alfamodel->GetProVacBmp() >> 4) & 1);
    ui->ProJig6->setChecked((m_alfamodel->GetProVacBmp() >> 5) & 1);
    ui->ProCheck1->setChecked((m_alfamodel->GetProVacChk() >> 0) & 1);
    ui->ProCheck2->setChecked((m_alfamodel->GetProVacChk() >> 1) & 1);
    ui->ProCheck3->setChecked((m_alfamodel->GetProVacChk() >> 2) & 1);
    ui->ProCheck4->setChecked((m_alfamodel->GetProVacChk() >> 3) & 1);
    ui->ProCheck5->setChecked((m_alfamodel->GetProVacChk() >> 4) & 1);
    ui->ProCheck6->setChecked((m_alfamodel->GetProVacChk() >> 5) & 1);
    ui->BoxProDelay->setValue((double)m_alfamodel->GetProVacDelay() /(1000.0/TIME_BASE));

    ui->RunJig1->setChecked((m_alfamodel->GetRunVacBmp() >> 0) & 1);
    ui->RunJig2->setChecked((m_alfamodel->GetRunVacBmp() >> 1) & 1);
    ui->RunJig3->setChecked((m_alfamodel->GetRunVacBmp() >> 2) & 1);
    ui->RunJig4->setChecked((m_alfamodel->GetRunVacBmp() >> 3) & 1);
    ui->RunJig5->setChecked((m_alfamodel->GetRunVacBmp() >> 4) & 1);
    ui->RunJig6->setChecked((m_alfamodel->GetRunVacBmp() >> 5) & 1);
    ui->RunCheck1->setChecked((m_alfamodel->GetRunVacChk() >> 0) & 1);
    ui->RunCheck2->setChecked((m_alfamodel->GetRunVacChk() >> 1) & 1);
    ui->RunCheck3->setChecked((m_alfamodel->GetRunVacChk() >> 2) & 1);
    ui->RunCheck4->setChecked((m_alfamodel->GetRunVacChk() >> 3) & 1);
    ui->RunCheck5->setChecked((m_alfamodel->GetRunVacChk() >> 4) & 1);
    ui->RunCheck6->setChecked((m_alfamodel->GetRunVacChk() >> 5) & 1);
    ui->BoxRunDelay->setValue((double)m_alfamodel->GetRunVacDelay() / (1000.0/TIME_BASE));
    ui->BoxRotateDelay->setValue((double)m_alfamodel->GetRotateDelay() / (1000.0/TIME_BASE));

    ui->BoxXSpeed->setValue(m_alfamodel->GetXSpeed());
    ui->BoxYSpeed->setValue(m_alfamodel->GetYSpeed());
    ui->BoxZSpeed->setValue(m_alfamodel->GetZSpeed());
    ui->BoxASpeed->setValue(m_alfamodel->GetASpeed());
    ui->BoxBSpeed->setValue(m_alfamodel->GetBSpeed());
    ui->BoxCSpeed->setValue(m_alfamodel->GetCSpeed());
    ui->BoxYSpeedOut->setValue(m_alfamodel->GetYSpeedOut());
    ui->BoxASpeedOut->setValue(m_alfamodel->GetASpeedOut());

    // 得到塑机设置
    ui->checkBoxEjectorFront->setChecked((m_alfamodel->UseEjectorFront()?1:0));
    ui->BoxEjectorFrontDelay->setValue((double)m_alfamodel->GetEjectorFrontDelay() / (1000.0/TIME_BASE));
    ui->checkBoxEjectorBack->setChecked((m_alfamodel->UseEjectorBack()?1:0));
    ui->BoxEjectorBackDelay->setValue((double)m_alfamodel->GetEjectorBackDelay() / (1000.0/TIME_BASE));
    ui->checkBoxC1Back->setChecked((m_alfamodel->UseC1Back()?1:0));
    ui->BoxC1BackDelay->setValue((double)m_alfamodel->GetC1BackDelay() / (1000.0/TIME_BASE));
    ui->checkBoxC1Front->setChecked((m_alfamodel->UseC1Front()?1:0));
    ui->BoxC1FrontDelay->setValue((double)m_alfamodel->GetC1FrontDelay() / (1000.0/TIME_BASE));
    ui->checkBoxC2Front->setChecked((m_alfamodel->UseC2Front()?1:0));
    ui->BoxC2FrontDelay->setValue((double)m_alfamodel->GetC2FrontDelay() / (1000.0/TIME_BASE));
    ui->checkBoxC2Back->setChecked((m_alfamodel->UseC2Back()?1:0));
    ui->BoxC2BackDelay->setValue((double)m_alfamodel->GetC2BackDelay() / (1000.0/TIME_BASE));
    ui->BoxMOPTimeout->setValue((double)m_alfamodel->GetMOPTimeout() / (1000.0/TIME_BASE));
    ui->BoxEMCDelay->setValue((double)m_alfamodel->GetEMCDelay() / (1000.0/TIME_BASE));

    // 矩阵
    ui->checkBox_rotate->setChecked(m_alfamodel->GetMatrixHor()?1:0);
    ui->checkBoxIsRunner->setChecked(m_alfamodel->GetMatrixIsRunner()?1:0);
    ui->checkBoxTrvRot->setChecked(m_alfamodel->GetMatrixTrvrot()?1:0);
    ui->checkBox_xdec->setChecked(m_alfamodel->GetMatrixDecAxis()?1:0);
    ui->checkBoxHorRel->setChecked(m_alfamodel->GetMatrixRelx()?1:0);
    ui->checkBoxVerRel->setChecked(m_alfamodel->GetMatrixRely()?1:0);
    ui->checkBoxTrvRel->setChecked(m_alfamodel->GetMatrixRelz()?1:0);
    ui->BoxHspd->setValue(m_alfamodel->GetMatrixSpeed());
    ui->BoxLspd->setValue(m_alfamodel->GetMatrixdSpeed());
    ui->BoxLowDis->setValue(m_alfamodel->GetMatrixdlen());
    ui->BoxHorCnt->setValue(m_alfamodel->GetMatrixXS());
    ui->BoxVerCnt->setValue(m_alfamodel->GetMatrixYS());
    ui->BoxTrvCnt->setValue(m_alfamodel->GetMatrixZS());

    // 传送带
    ui->checkBoxConveyor->setChecked((m_alfamodel->UseConveyor()?1:0));
    ui->BoxConveyorDelay->setValue((double)m_alfamodel->GetConveyorDelay() / (1000.0/TIME_BASE));
    ui->BoxConveyorInterval->setValue(m_alfamodel->GetConveyorInterval());
    outport = m_alfamodel->GetConveyorOut();
    ui->lineEditPort->setText(xStringResource::GetVarName(outport));

    if (CMBProtocol::GetFunctions(SUB_LOOP_INTERVAL))
    {
        ui->BoxHorInt->setValue((double)m_alfamodel->GetMatrixXInterval() /10.0);
        ui->BoxVerInt->setValue((double)m_alfamodel->GetMatrixYInterval() /10.0);
        ui->BoxTrvInt->setValue((double)m_alfamodel->GetMatrixZInterval() /10.0);
    }
    else
    {
        ui->BoxHorInt->setValue((double)m_alfamodel->GetMatrixXInterval() /100.0);
        ui->BoxVerInt->setValue((double)m_alfamodel->GetMatrixYInterval() /100.0);
        ui->BoxTrvInt->setValue((double)m_alfamodel->GetMatrixZInterval() /100.0);
    }
    ui->BoxHorPos->setValue((double)m_alfamodel->GetMatrixPosx() /100.0);
    ui->BoxVerPos->setValue((double)m_alfamodel->GetMatrixPosy() /100.0);
    ui->BoxTrvPos->setValue((double)m_alfamodel->GetMatrixPosz() /100.0);
    SetFirstDec(m_alfamodel->GetMatrixDecPrior());

    if (m_alfamodel->GetTrvInRotate())
        ui->checkBoxTrvInHor->setChecked(true);
    else
        ui->checkBoxTrvInVer->setChecked(true);
    if (m_alfamodel->GetTrvOutRotate())
        ui->checkBoxTrvOutHor->setChecked(true);
    else
        ui->checkBoxTrvOutVer->setChecked(true);
    if (m_alfamodel->GetReleaseRotate())
        ui->checkBoxReleaseHor->setChecked(true);
    else
        ui->checkBoxReleaseVer->setChecked(true);
    if (m_alfamodel->GetFetchRotate())
        ui->checkBoxFetchHor->setChecked(true);
    else
        ui->checkBoxFetchVer->setChecked(true);

    ui->CheckBoxProReleaseUse->setChecked(m_alfamodel->GetProReleaseUse()?1:0);

    // 控件状态
    setPortState();
//    UpdateTab();
    // 连接信号槽
	connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
//    show();
	return true;
}

bool Formalfaoption::ExitForm(void)
{
	if (isModified() == true)
	{
        // 参数设置已经更改
		int ret = xMessageBox::DoSaveTip(tr("系统提示"), xStringResource::GetString(STRRES_SAVETIP));
		if (ret == XMSG_RET_SAVE)
		{
			// 保存参数
            if (SaveAlfaPara() == false)
				return false;
		}
		else if (ret != XMSG_RET_NOSAVE)
			return false;
	}
	// 取消信号槽连接
	disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 隐藏界面
//	hide();
	return true;
}
// 根据当前用户权限设置界面
void Formalfaoption::setPermissions(void)
{
    ui->tabWidgetGuide->setTabEnabled(TAB_PAGE_PRO, xPermissions::GetPermissions(PER_SYS_NORMAL));
    ui->tabWidgetGuide->setTabEnabled(TAB_PAGE_RUN, xPermissions::GetPermissions(PER_SYS_NORMAL));
    ui->tabWidgetGuide->setTabEnabled(TAB_PAGE_SPD, xPermissions::GetPermissions(PER_SYS_NORMAL));
    ui->tabWidgetGuide->setTabEnabled(TAB_PAGE_JIG, xPermissions::GetPermissions(PER_SYS_NORMAL));
    ui->tabWidgetGuide->setTabEnabled(TAB_PAGE_MATRIX, xPermissions::GetPermissions(PER_SYS_NORMAL));
    ui->tabWidgetGuide->setTabEnabled(TAB_PAGE_IMM, xPermissions::GetPermissions(PER_SYS_NORMAL));
    ui->tabWidgetGuide->setTabEnabled(TAB_PAGE_CONVEYOR, xPermissions::GetPermissions(PER_SYS_NORMAL));
}
// 当前登录用户更改槽
void Formalfaoption::userChange(void)
{
    if (xPermissions::GetPermissions(PER_TEACH) == false)
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
    setPermissions();
}
// ************************************************
// 保存参数信号槽
// ************************************************
void Formalfaoption::AcceptSetup(void)
{

    if (xPermissions::GetPermissions(PER_TEACH) == false)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
		return;
	}
    //if (isModified())
	{
        if (SaveAlfaPara() == false)
			return;
	}
	// 显示保存成功信息
#if UI_SAVED_TIP
	xMessageBox::DoInformation(tr("保存参数"), xStringResource::GetString(STRRES_HAS_SAVED));
#endif
}
void Formalfaoption::inputConveyorDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxConveyorDelay->minimum(), ui->BoxConveyorDelay->maximum()) == QDialog::Accepted)
        ui->BoxConveyorDelay->setValue(value);
}

void Formalfaoption::inputConveyorInterval(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxConveyorInterval->minimum(), ui->BoxConveyorInterval->maximum()) == QDialog::Accepted)
        ui->BoxConveyorInterval->setValue(value);
}
// 选择扩展输出端口
void Formalfaoption::selectPort(void)
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_EOUT, ret) != QDialog::Accepted)
        return;
    outport = ret;
    ui->lineEditPort->setText(xStringResource::GetVarName(outport));
}
// 输入主臂延时信号槽
void Formalfaoption::inputProDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxProDelay->minimum(), ui->BoxProDelay->maximum()) == QDialog::Accepted)
        ui->BoxProDelay->setValue(value);
}
// 输入副臂延时信号槽
void Formalfaoption::inputRunDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRunDelay->minimum(), ui->BoxRunDelay->maximum()) == QDialog::Accepted)
        ui->BoxRunDelay->setValue(value);
}
// 输入主臂倒角延时信号槽
void Formalfaoption::inputRotateDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRotateDelay->minimum(), ui->BoxRotateDelay->maximum()) == QDialog::Accepted)
        ui->BoxRotateDelay->setValue(value);
}
// 输入注塑机延时
void Formalfaoption::inputEjectorFrontDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxEjectorFrontDelay->minimum(), ui->BoxEjectorFrontDelay->maximum()) == QDialog::Accepted)
        ui->BoxEjectorFrontDelay->setValue(value);
}
void Formalfaoption::inputEjectorBackDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxEjectorBackDelay->minimum(), ui->BoxEjectorBackDelay->maximum()) == QDialog::Accepted)
        ui->BoxEjectorBackDelay->setValue(value);
}
void Formalfaoption::inputC1FrontDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxC1FrontDelay->minimum(), ui->BoxC1FrontDelay->maximum()) == QDialog::Accepted)
        ui->BoxC1FrontDelay->setValue(value);
}
void Formalfaoption::inputC1BackDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxC1BackDelay->minimum(), ui->BoxC1BackDelay->maximum()) == QDialog::Accepted)
        ui->BoxC1BackDelay->setValue(value);
}
void Formalfaoption::inputC2FrontDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxC2FrontDelay->minimum(), ui->BoxC2FrontDelay->maximum()) == QDialog::Accepted)
        ui->BoxC2FrontDelay->setValue(value);
}
void Formalfaoption::inputC2BackDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxC2BackDelay->minimum(), ui->BoxC2BackDelay->maximum()) == QDialog::Accepted)
        ui->BoxC2BackDelay->setValue(value);
}

void Formalfaoption::inputMOPTimeout(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxMOPTimeout->minimum(), ui->BoxMOPTimeout->maximum()) == QDialog::Accepted)
        ui->BoxMOPTimeout->setValue(value);
}
void Formalfaoption::inputEMCDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxEMCDelay->minimum(), ui->BoxEMCDelay->maximum()) == QDialog::Accepted)
        ui->BoxEMCDelay->setValue(value);
}
// 点置物模式
void Formalfaoption::inputProRelPos(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxProRelPos->minimum(), ui->BoxProRelPos->maximum()) == QDialog::Accepted)
        ui->BoxProRelPos->setValue(value);
}
void Formalfaoption::inputRunRelPos(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxRunRelPos->minimum(), ui->BoxRunRelPos->maximum()) == QDialog::Accepted)
        ui->BoxRunRelPos->setValue(value);
}
void Formalfaoption::inputCatchPos(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxCatchPos->minimum(), ui->BoxCatchPos->maximum()) == QDialog::Accepted)
        ui->BoxCatchPos->setValue(value);
}
void Formalfaoption::inputXProDown(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxXProDown->minimum(), ui->BoxXProDown->maximum()) == QDialog::Accepted)
        ui->BoxXProDown->setValue(value);
}
void Formalfaoption::inputXProCatch(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxXProCatch->minimum(), ui->BoxXProCatch->maximum()) == QDialog::Accepted)
        ui->BoxXProCatch->setValue(value);
}
void Formalfaoption::inputBRunDown(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxBRunDown->minimum(), ui->BoxBRunDown->maximum()) == QDialog::Accepted)
        ui->BoxBRunDown->setValue(value);
}
void Formalfaoption::inputBRunCatch(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxBRunCatch->minimum(), ui->BoxBRunCatch->maximum()) == QDialog::Accepted)
        ui->BoxBRunCatch->setValue(value);
}
void Formalfaoption::inputYProCatch(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxYProCatch->minimum(), ui->BoxYProCatch->maximum()) == QDialog::Accepted)
        ui->BoxYProCatch->setValue(value);
}
void Formalfaoption::inputARunCatch(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxARunCatch->minimum(), ui->BoxARunCatch->maximum()) == QDialog::Accepted)
        ui->BoxARunCatch->setValue(value);
}
void Formalfaoption::inputYProRel(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxYProRel->minimum(), ui->BoxYProRel->maximum()) == QDialog::Accepted)
        ui->BoxYProRel->setValue(value);
}
void Formalfaoption::inputARunRel(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxARunRel->minimum(), ui->BoxARunRel->maximum()) == QDialog::Accepted)
        ui->BoxARunRel->setValue(value);
}
void Formalfaoption::inputXProRel(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxXProRel->minimum(), ui->BoxXProRel->maximum()) == QDialog::Accepted)
        ui->BoxXProRel->setValue(value);
}
void Formalfaoption::inputBRunRel(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxBRunRel->minimum(), ui->BoxBRunRel->maximum()) == QDialog::Accepted)
        ui->BoxBRunRel->setValue(value);
}
void Formalfaoption::inputYProWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxYProWait->minimum(), ui->BoxYProWait->maximum()) == QDialog::Accepted)
        ui->BoxYProWait->setValue(value);
}
void Formalfaoption::inputARunWait(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxARunWait->minimum(), ui->BoxARunWait->maximum()) == QDialog::Accepted)
        ui->BoxARunWait->setValue(value);
}
void Formalfaoption::inputXProUP(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxXProUP->minimum(), ui->BoxXProUP->maximum()) == QDialog::Accepted)
        ui->BoxXProUP->setValue(value);
}
void Formalfaoption::inputBRunUP(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->BoxBRunUP->minimum(), ui->BoxBRunUP->maximum()) == QDialog::Accepted)
        ui->BoxBRunUP->setValue(value);
}
// 速度
void Formalfaoption::inputXSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxXSpeed->minimum(), ui->BoxXSpeed->maximum()) == QDialog::Accepted)
        ui->BoxXSpeed->setValue(value);
}
void Formalfaoption::inputYSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxYSpeed->minimum(), ui->BoxYSpeed->maximum()) == QDialog::Accepted)
        ui->BoxYSpeed->setValue(value);
}
void Formalfaoption::inputZSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxZSpeed->minimum(), ui->BoxZSpeed->maximum()) == QDialog::Accepted)
        ui->BoxZSpeed->setValue(value);
}
void Formalfaoption::inputASpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxASpeed->minimum(), ui->BoxASpeed->maximum()) == QDialog::Accepted)
        ui->BoxASpeed->setValue(value);
}
void Formalfaoption::inputBSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxBSpeed->minimum(), ui->BoxBSpeed->maximum()) == QDialog::Accepted)
        ui->BoxBSpeed->setValue(value);
}
void Formalfaoption::inputCSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxCSpeed->minimum(), ui->BoxCSpeed->maximum()) == QDialog::Accepted)
        ui->BoxCSpeed->setValue(value);
}
void Formalfaoption::inputYSpeedout(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxYSpeedOut->minimum(), ui->BoxYSpeedOut->maximum()) == QDialog::Accepted)
        ui->BoxYSpeedOut->setValue(value);
}
void Formalfaoption::inputASpeedout(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxASpeedOut->minimum(), ui->BoxASpeedOut->maximum()) == QDialog::Accepted)
        ui->BoxASpeedOut->setValue(value);
}

// 进入窗口控件状态
void Formalfaoption::setPortState(void)
{
    ui->ProCheck1->setEnabled(ui->ProJig1->isChecked()?1:0);
    ui->RunJig1->setEnabled(ui->ProJig1->isChecked()?0:1);
    ui->ProCheck2->setEnabled(ui->ProJig2->isChecked()?1:0);
    ui->RunJig2->setEnabled(ui->ProJig2->isChecked()?0:1);
    ui->ProCheck3->setEnabled(ui->ProJig3->isChecked()?1:0);
    ui->RunJig3->setEnabled(ui->ProJig3->isChecked()?0:1);
    ui->ProCheck4->setEnabled(ui->ProJig4->isChecked()?1:0);
    ui->RunJig4->setEnabled(ui->ProJig4->isChecked()?0:1);
    ui->ProCheck5->setEnabled(ui->ProJig5->isChecked()?1:0);
    ui->RunJig5->setEnabled(ui->ProJig5->isChecked()?0:1);
    ui->ProCheck6->setEnabled(ui->ProJig6->isChecked()?1:0);
    ui->RunJig6->setEnabled(ui->ProJig6->isChecked()?0:1);

    ui->RunCheck1->setEnabled(ui->RunJig1->isChecked()?1:0);
    ui->ProJig1->setEnabled(ui->RunJig1->isChecked()?0:1);
    ui->RunCheck2->setEnabled(ui->RunJig2->isChecked()?1:0);
    ui->ProJig2->setEnabled(ui->RunJig2->isChecked()?0:1);
    ui->RunCheck3->setEnabled(ui->RunJig3->isChecked()?1:0);
    ui->ProJig3->setEnabled(ui->RunJig3->isChecked()?0:1);
    ui->RunCheck4->setEnabled(ui->RunJig4->isChecked()?1:0);
    ui->ProJig4->setEnabled(ui->RunJig4->isChecked()?0:1);
    ui->RunCheck5->setEnabled(ui->RunJig5->isChecked()?1:0);
    ui->ProJig5->setEnabled(ui->RunJig5->isChecked()?0:1);
    ui->RunCheck6->setEnabled(ui->RunJig6->isChecked()?1:0);
    ui->ProJig6->setEnabled(ui->RunJig6->isChecked()?0:1);
    if (pModbus->GetSysState() == SYS_STATE_AUTO)
    {
        ui->cBoxProMode->setEnabled(false);
        ui->BoxProRelPos->setEnabled(false);
        ui->BoxRunRelPos->setEnabled(false);
        ui->BoxCatchPos->setEnabled(false);
        ui->BoxXProDown->setEnabled(false);
        ui->BoxYProWait->setEnabled(false);
        ui->BoxXProCatch->setEnabled(false);
        ui->BoxXProRel->setEnabled(false);
        ui->BoxYProCatch->setEnabled(false);
        ui->BoxYProRel->setEnabled(false);
        ui->BoxXProUP->setEnabled(false);

        ui->cBoxRunMode->setEnabled(false);
        ui->BoxBRunDown->setEnabled(false);
        ui->BoxARunWait->setEnabled(false);
        ui->BoxBRunCatch->setEnabled(false);
        ui->BoxBRunRel->setEnabled(false);
        ui->BoxARunCatch->setEnabled(false);
        ui->BoxARunRel->setEnabled(false);
        ui->BoxBRunUP->setEnabled(false);

        ui->ProJig1->setEnabled(false);
        ui->ProJig2->setEnabled(false);
        ui->ProJig3->setEnabled(false);
        ui->ProJig4->setEnabled(false);
        ui->ProJig5->setEnabled(false);
        ui->ProJig6->setEnabled(false);
        ui->ProCheck1->setEnabled(false);
        ui->ProCheck2->setEnabled(false);
        ui->ProCheck3->setEnabled(false);
        ui->ProCheck4->setEnabled(false);
        ui->ProCheck5->setEnabled(false);
        ui->ProCheck6->setEnabled(false);
        ui->RunJig1->setEnabled(false);
        ui->RunJig2->setEnabled(false);
        ui->RunJig3->setEnabled(false);
        ui->RunJig4->setEnabled(false);
        ui->RunJig5->setEnabled(false);
        ui->RunJig6->setEnabled(false);
        ui->RunCheck1->setEnabled(false);
        ui->RunCheck2->setEnabled(false);
        ui->RunCheck3->setEnabled(false);
        ui->RunCheck4->setEnabled(false);
        ui->RunCheck5->setEnabled(false);
        ui->RunCheck6->setEnabled(false);
        ui->BtnGoUp->setEnabled(false);
        ui->BtnGoDown->setEnabled(false);

        ui->checkBox_rotate->setEnabled(false);
        ui->checkBoxIsRunner->setEnabled(false);
        ui->checkBox_xdec->setEnabled(false);
        ui->checkBoxTrvRot->setEnabled(false);
        ui->lineEditCount->setEnabled(false);
        ui->BoxHorCnt->setEnabled(false);
        ui->BoxVerCnt->setEnabled(false);
        ui->BoxTrvCnt->setEnabled(false);
        ui->BoxLowDis->setEnabled(false);
        ui->BoxHorInt->setEnabled(false);
        ui->BoxVerInt->setEnabled(false);
        ui->BoxTrvInt->setEnabled(false);
        ui->BoxHorPos->setEnabled(false);
        ui->BoxVerPos->setEnabled(false);
        ui->BoxTrvPos->setEnabled(false);
        ui->checkBoxHorRel->setEnabled(false);
        ui->checkBoxVerRel->setEnabled(false);
        ui->checkBoxTrvRel->setEnabled(false);

        ui->checkBoxEjectorFront->setEnabled(false);
        ui->checkBoxEjectorBack->setEnabled(false);
        ui->checkBoxC1Front->setEnabled(false);
        ui->checkBoxC1Back->setEnabled(false);
        ui->checkBoxC2Front->setEnabled(false);
        ui->checkBoxC2Back->setEnabled(false);

        ui->checkBoxConveyor->setEnabled(false);
        ui->lineEditPort->setEnabled(false);
        ui->BoxConveyorInterval->setEnabled(false);

        ui->checkBoxTrvInHor->setEnabled(false);
        ui->checkBoxTrvInVer->setEnabled(false);
        ui->checkBoxTrvOutHor->setEnabled(false);
        ui->checkBoxTrvOutVer->setEnabled(false);
        ui->checkBoxFetchHor->setEnabled(false);
        ui->checkBoxFetchVer->setEnabled(false);
        ui->checkBoxReleaseHor->setEnabled(false);
        ui->checkBoxReleaseVer->setEnabled(false);
    }
    else
    {
        ui->cBoxProMode->setEnabled(true);
        ui->BoxProRelPos->setEnabled(true);
        ui->BoxRunRelPos->setEnabled(true);
        ui->BoxCatchPos->setEnabled(true);
        ui->BoxXProDown->setEnabled(true);
        ui->BoxYProWait->setEnabled(true);
        ui->BoxXProCatch->setEnabled(true);
        ui->BoxXProRel->setEnabled(true);
        ui->BoxYProCatch->setEnabled(true);
        ui->BoxYProRel->setEnabled(true);
        ui->BoxXProUP->setEnabled(true);

        ui->cBoxRunMode->setEnabled(true);
        ui->BoxBRunDown->setEnabled(true);
        ui->BoxARunWait->setEnabled(true);
        ui->BoxBRunCatch->setEnabled(true);
        ui->BoxBRunRel->setEnabled(true);
        ui->BoxARunCatch->setEnabled(true);
        ui->BoxARunRel->setEnabled(true);
        ui->BoxBRunUP->setEnabled(true);

        ui->ProJig1->setEnabled(true);
        ui->ProJig2->setEnabled(true);
        ui->ProJig3->setEnabled(true);
        ui->ProJig4->setEnabled(true);
        ui->ProJig5->setEnabled(true);
        ui->ProJig6->setEnabled(true);
        ui->ProCheck1->setEnabled(true);
        ui->ProCheck2->setEnabled(true);
        ui->ProCheck3->setEnabled(true);
        ui->ProCheck4->setEnabled(true);
        ui->ProCheck5->setEnabled(true);
        ui->ProCheck6->setEnabled(true);
        ui->RunJig1->setEnabled(true);
        ui->RunJig2->setEnabled(true);
        ui->RunJig3->setEnabled(true);
        ui->RunJig4->setEnabled(true);
        ui->RunJig5->setEnabled(true);
        ui->RunJig6->setEnabled(true);
        ui->RunCheck1->setEnabled(true);
        ui->RunCheck2->setEnabled(true);
        ui->RunCheck3->setEnabled(true);
        ui->RunCheck4->setEnabled(true);
        ui->RunCheck5->setEnabled(true);
        ui->RunCheck6->setEnabled(true);
        ui->BtnGoUp->setEnabled(true);
        ui->BtnGoDown->setEnabled(true);

        ui->checkBox_rotate->setEnabled(true);
        ui->checkBoxIsRunner->setEnabled(true);
        ui->checkBox_xdec->setEnabled(true);
        ui->checkBoxTrvRot->setEnabled(true);
        ui->lineEditCount->setEnabled(true);
        ui->BoxHorCnt->setEnabled(true);
        ui->BoxVerCnt->setEnabled(true);
        ui->BoxTrvCnt->setEnabled(true);
        ui->BoxLowDis->setEnabled(true);
        ui->BoxHorInt->setEnabled(true);
        ui->BoxVerInt->setEnabled(true);
        ui->BoxTrvInt->setEnabled(true);
        ui->BoxHorPos->setEnabled(true);
        ui->BoxVerPos->setEnabled(true);
        ui->BoxTrvPos->setEnabled(true);
        ui->checkBoxHorRel->setEnabled(true);
        ui->checkBoxVerRel->setEnabled(true);
        ui->checkBoxTrvRel->setEnabled(true);

        ui->checkBoxEjectorFront->setEnabled(true);
        ui->checkBoxEjectorBack->setEnabled(true);
        ui->checkBoxC1Front->setEnabled(true);
        ui->checkBoxC1Back->setEnabled(true);
        ui->checkBoxC2Front->setEnabled(true);
        ui->checkBoxC2Back->setEnabled(true);

        ui->checkBoxConveyor->setEnabled(true);
        ui->lineEditPort->setEnabled(true);
        ui->BoxConveyorInterval->setEnabled(true);

        ui->checkBoxTrvInHor->setEnabled(true);
        ui->checkBoxTrvInVer->setEnabled(true);
        ui->checkBoxTrvOutHor->setEnabled(true);
        ui->checkBoxTrvOutVer->setEnabled(true);
        ui->checkBoxFetchHor->setEnabled(true);
        ui->checkBoxFetchVer->setEnabled(true);
        ui->checkBoxReleaseHor->setEnabled(true);
        ui->checkBoxReleaseVer->setEnabled(true);
    }
    // 设置界面显示状态
    if (ui->cBoxProMode->currentIndex() == 0)
    {
        ui->groupBoxProJig->setEnabled(false);
        ui->ProJig1->setChecked(false);
        ui->ProJig2->setChecked(false);
        ui->ProJig3->setChecked(false);
        ui->ProJig4->setChecked(false);
        ui->ProJig5->setChecked(false);
        ui->ProJig6->setChecked(false);
        ui->ProCheck1->setChecked(false);
        ui->ProCheck2->setChecked(false);
        ui->ProCheck3->setChecked(false);
        ui->ProCheck4->setChecked(false);
        ui->ProCheck5->setChecked(false);
        ui->ProCheck6->setChecked(false);
        ui->BoxXProCatch->setEnabled(false);
        ui->BoxXProDown->setEnabled(false);
        ui->BoxYProCatch->setEnabled(false);
        ui->BoxYProRel->setEnabled(false);
        ui->BoxXProRel->setEnabled(false);
        ui->BoxYProWait->setEnabled(false);
        ui->BoxXProUP->setEnabled(false);
    }
    else
    {
        ui->groupBoxProJig->setEnabled(true);
        ui->BoxXProCatch->setEnabled(true);
        ui->BoxXProDown->setEnabled(true);
        ui->BoxYProCatch->setEnabled(true);
        ui->BoxYProRel->setEnabled(true);
        ui->BoxXProRel->setEnabled(true);
        ui->BoxYProWait->setEnabled(true);
        ui->BoxXProUP->setEnabled(true);
    }
    if (ui->cBoxRunMode->currentIndex() == 0)
    {
        ui->RunJig1->setChecked(false);
        ui->RunJig2->setChecked(false);
        ui->RunJig3->setChecked(false);
        ui->RunJig4->setChecked(false);
        ui->RunJig5->setChecked(false);
        ui->RunJig6->setChecked(false);
        ui->RunCheck1->setChecked(false);
        ui->RunCheck2->setChecked(false);
        ui->RunCheck3->setChecked(false);
        ui->RunCheck4->setChecked(false);
        ui->RunCheck5->setChecked(false);
        ui->RunCheck6->setChecked(false);
        ui->BoxBRunCatch->setEnabled(false);
        ui->BoxBRunDown->setEnabled(false);
        ui->BoxARunCatch->setEnabled(false);
        ui->BoxARunRel->setEnabled(false);
        ui->BoxBRunRel->setEnabled(false);
        ui->BoxARunWait->setEnabled(false);
        ui->BoxBRunUP->setEnabled(false);
        ui->CheckBoxProReleaseUse->setEnabled(true);

    }
    else
    {
        ui->BoxBRunCatch->setEnabled(true);
        ui->BoxBRunDown->setEnabled(true);
        ui->BoxARunCatch->setEnabled(true);
        ui->BoxARunRel->setEnabled(true);
        ui->BoxBRunRel->setEnabled(true);
        ui->BoxARunWait->setEnabled(true);
        ui->BoxBRunUP->setEnabled(true);
        ui->CheckBoxProReleaseUse->setEnabled(false);
    }
    if (ui->CheckBoxProReleaseUse->isChecked())
        ui->cBoxRunMode->setEnabled(false);
    else
        ui->cBoxRunMode->setEnabled(true);
    ui->groupBoxRunJig->setEnabled(ui->CheckBoxProReleaseUse->isChecked()|| (ui->cBoxRunMode->currentIndex() != 0));
}
// 治具框状态改变
void Formalfaoption::stateChanged_ProJig1(int state)
{
    if (ui->ProJig1->isChecked())
    {
        ui->ProCheck1->setEnabled(true);
        ui->RunJig1->setEnabled(false);
    }
    else
    {
        ui->ProCheck1->setEnabled(false);
        ui->RunJig1->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_ProJig2(int state)
{
    if (ui->ProJig2->isChecked())
    {
        ui->ProCheck2->setEnabled(true);
        ui->RunJig2->setEnabled(false);
    }
    else
    {
        ui->ProCheck2->setEnabled(false);
        ui->RunJig2->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_ProJig3(int state)
{
    if (ui->ProJig3->isChecked())
    {
        ui->ProCheck3->setEnabled(true);
        ui->RunJig3->setEnabled(false);
    }
    else
    {
        ui->ProCheck3->setEnabled(false);
        ui->RunJig3->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_ProJig4(int state)
{
    if (ui->ProJig4->isChecked())
    {
        ui->ProCheck4->setEnabled(true);
        ui->RunJig4->setEnabled(false);
    }
    else
    {
        ui->ProCheck4->setEnabled(false);
        ui->RunJig4->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_ProJig5(int state)
{
    if (ui->ProJig5->isChecked())
    {
        ui->ProCheck5->setEnabled(true);
        ui->RunJig5->setEnabled(false);
    }
    else
    {
        ui->ProCheck5->setEnabled(false);
        ui->RunJig5->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_ProJig6(int state)
{
    if (ui->ProJig6->isChecked())
    {
        ui->ProCheck6->setEnabled(true);
        ui->RunJig6->setEnabled(false);
    }
    else
    {
        ui->ProCheck6->setEnabled(false);
        ui->RunJig6->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_RunJig1(int state)
{
    if (ui->RunJig1->isChecked())
    {
        ui->RunCheck1->setEnabled(true);
        ui->ProJig1->setEnabled(false);
    }
    else
    {
        ui->RunCheck1->setEnabled(false);
        ui->ProJig1->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_RunJig2(int state)
{
    if (ui->RunJig2->isChecked())
    {
        ui->RunCheck2->setEnabled(true);
        ui->ProJig2->setEnabled(false);
    }
    else
    {
        ui->RunCheck2->setEnabled(false);
        ui->ProJig2->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_RunJig3(int state)
{
    if (ui->RunJig3->isChecked())
    {
        ui->RunCheck3->setEnabled(true);
        ui->ProJig3->setEnabled(false);
    }
    else
    {
        ui->RunCheck3->setEnabled(false);
        ui->ProJig3->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_RunJig4(int state)
{
    if (ui->RunJig4->isChecked())
    {
        ui->RunCheck4->setEnabled(true);
        ui->ProJig4->setEnabled(false);
    }
    else
    {
        ui->RunCheck4->setEnabled(false);
        ui->ProJig4->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_RunJig5(int state)
{
    if (ui->RunJig5->isChecked())
    {
        ui->RunCheck5->setEnabled(true);
        ui->ProJig5->setEnabled(false);
    }
    else
    {
        ui->RunCheck5->setEnabled(false);
        ui->ProJig5->setEnabled(true);
    }
}
void Formalfaoption::stateChanged_RunJig6(int state)
{
    if (ui->RunJig6->isChecked())
    {
        ui->RunCheck6->setEnabled(true);
        ui->ProJig6->setEnabled(false);
    }
    else
    {
        ui->RunCheck6->setEnabled(false);
        ui->ProJig6->setEnabled(true);
    }
}
// 模式设置改变
void Formalfaoption::indexChanged_proMode(int index)
{
    if (ui->cBoxProMode->currentIndex() == 0)
    {
        ui->groupBoxProJig->setEnabled(false);
        ui->ProJig1->setChecked(false);
        ui->ProJig2->setChecked(false);
        ui->ProJig3->setChecked(false);
        ui->ProJig4->setChecked(false);
        ui->ProJig5->setChecked(false);
        ui->ProJig6->setChecked(false);
        ui->ProCheck1->setChecked(false);
        ui->ProCheck2->setChecked(false);
        ui->ProCheck3->setChecked(false);
        ui->ProCheck4->setChecked(false);
        ui->ProCheck5->setChecked(false);
        ui->ProCheck6->setChecked(false);
//        ui->BoxProRelPos->setEnabled(false);
        ui->BoxXProCatch->setEnabled(false);
        ui->BoxXProDown->setEnabled(false);
        ui->BoxYProCatch->setEnabled(false);
        ui->BoxYProRel->setEnabled(false);
        ui->BoxXProRel->setEnabled(false);
        ui->BoxYProWait->setEnabled(false);
        ui->BoxXProUP->setEnabled(false);
    }
    else
    {
        ui->groupBoxProJig->setEnabled(true);
//        ui->BoxProRelPos->setEnabled(true);
        ui->BoxXProCatch->setEnabled(true);
        ui->BoxXProDown->setEnabled(true);
        ui->BoxYProCatch->setEnabled(true);
        ui->BoxYProRel->setEnabled(true);
        ui->BoxXProRel->setEnabled(true);
        ui->BoxYProWait->setEnabled(true);
        ui->BoxXProUP->setEnabled(true);
    }
}
void Formalfaoption::indexChanged_runMode(int index)
{
    if (ui->cBoxRunMode->currentIndex() == 0)
    {
        ui->groupBoxRunJig->setEnabled(false);
        ui->RunJig1->setChecked(false);
        ui->RunJig2->setChecked(false);
        ui->RunJig3->setChecked(false);
        ui->RunJig4->setChecked(false);
        ui->RunJig5->setChecked(false);
        ui->RunJig6->setChecked(false);
        ui->RunCheck1->setChecked(false);
        ui->RunCheck2->setChecked(false);
        ui->RunCheck3->setChecked(false);
        ui->RunCheck4->setChecked(false);
        ui->RunCheck5->setChecked(false);
        ui->RunCheck6->setChecked(false);
//        ui->BoxRunRelPos->setEnabled(false);
        ui->BoxBRunCatch->setEnabled(false);
        ui->BoxBRunDown->setEnabled(false);
        ui->BoxARunCatch->setEnabled(false);
        ui->BoxARunRel->setEnabled(false);
        ui->BoxBRunRel->setEnabled(false);
        ui->BoxARunWait->setEnabled(false);
        ui->BoxBRunUP->setEnabled(false);
        ui->CheckBoxProReleaseUse->setEnabled(true);
    }
    else
    {
        ui->groupBoxRunJig->setEnabled(true);
//        ui->BoxRunRelPos->setEnabled(true);
        ui->BoxBRunCatch->setEnabled(true);
        ui->BoxBRunDown->setEnabled(true);
        ui->BoxARunCatch->setEnabled(true);
        ui->BoxARunRel->setEnabled(true);
        ui->BoxBRunRel->setEnabled(true);
        ui->BoxARunWait->setEnabled(true);
        ui->BoxBRunUP->setEnabled(true);
        ui->CheckBoxProReleaseUse->setEnabled(false);
    }
}
// 主臂置料使用
void Formalfaoption::proReleaseState(int state)
{
    // 主臂置料使用时副臂无法使用，副臂治具组可以使用
    // 副臂使用时，主臂置料无法使用
    if (ui->CheckBoxProReleaseUse->isChecked())
    {
        ui->cBoxRunMode->setCurrentIndex(0);
        ui->cBoxRunMode->setEnabled(false);
        ui->groupBoxRunJig->setEnabled(true);
    }
    else
    {
        ui->cBoxRunMode->setEnabled(true);
        ui->groupBoxRunJig->setEnabled(ui->cBoxRunMode->currentIndex());
    }
}
// 输入引拔轴点数信号槽
void Formalfaoption::inputHorCnt(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxHorCnt->minimum(), ui->BoxHorCnt->maximum()) == QDialog::Accepted)
        ui->BoxHorCnt->setValue(value);
}
// 输入上下轴点数信号槽
void Formalfaoption::inputVerCnt(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxVerCnt->minimum(), ui->BoxVerCnt->maximum()) == QDialog::Accepted)
        ui->BoxVerCnt->setValue(value);
}
// 输入横行轴点数信号槽
void Formalfaoption::inputTrvCnt(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxTrvCnt->minimum(), ui->BoxTrvCnt->maximum()) == QDialog::Accepted)
        ui->BoxTrvCnt->setValue(value);
}

// 输入引拔轴点距信号槽
void Formalfaoption::inputHorInt(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxHorInt->minimum(), ui->BoxHorInt->maximum()) != QDialog::Accepted)
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        ui->BoxHorInt->setValue(value);
    else
    {
        double diff = ui->BoxHorInt->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
        ui->BoxHorInt->setValue(ui->BoxHorInt->value() - diff);
    }
}
// 输入上下轴点距信号槽
void Formalfaoption::inputVerInt(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxVerInt->minimum(), ui->BoxVerInt->maximum()) != QDialog::Accepted)
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        ui->BoxVerInt->setValue(value);
    else
    {
        double diff = ui->BoxVerInt->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
        ui->BoxVerInt->setValue(ui->BoxVerInt->value() - diff);
    }
}
// 输入横行轴点距信号槽
void Formalfaoption::inputTrvInt(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvInt->minimum(), ui->BoxTrvInt->maximum()) != QDialog::Accepted)
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        ui->BoxTrvInt->setValue(value);
    else
    {
        double diff = ui->BoxTrvInt->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
        ui->BoxTrvInt->setValue(ui->BoxTrvInt->value() - diff);
    }
}

// 输入引拔轴第一点位置信号槽
void Formalfaoption::inputHorPos(void)
{
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4) || (!CMBProtocol::GetRhorSrvUse()))
    {
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
            return;
    }
    else
    {
    if (numberPad.DoFormPos(value, 0.00, (CMBProtocol::GetHorLen() - CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
            return;
    }
#else
    if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
        return;
#endif
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        ui->BoxHorPos->setValue(value);
    else
    {
        double diff = ui->BoxHorPos->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
        ui->BoxHorPos->setValue(ui->BoxHorPos->value() - diff);
    }
}
// 输入上下轴第一点位置信号槽
void Formalfaoption::inputVerPos(void)
{
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        ui->BoxVerPos->setValue(value);
    else
    {
        double diff = ui->BoxVerPos->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
        ui->BoxVerPos->setValue(ui->BoxVerPos->value() - diff);
    }
}
// 输入横行轴第一点位置信号槽
void Formalfaoption::inputTrvPos(void)
{
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetTravLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        ui->BoxTrvPos->setValue(value);
    else
    {
        double diff = ui->BoxTrvPos->value() - value;
        if (diff < -5.00)
            diff = -5.00;
        else if (diff > 5.00)
            diff = 5.00;
        ui->BoxTrvPos->setValue(ui->BoxTrvPos->value() - diff);
    }
}
// 输入运行速度信号槽
void Formalfaoption::inputHspd(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxHspd->minimum(), ui->BoxHspd->maximum()) == QDialog::Accepted)
        ui->BoxHspd->setValue(value);
}
// 输入低速速度信号槽
void Formalfaoption::inputLspd(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxLspd->minimum(), ui->BoxLspd->maximum()) == QDialog::Accepted)
        ui->BoxLspd->setValue(value);
}
// 输入减速距离信号槽
void Formalfaoption::inputLdis(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxLowDis->minimum(), ui->BoxLowDis->maximum()) == QDialog::Accepted)
        ui->BoxLowDis->setValue(value);
}
// 选择变量
void Formalfaoption::selectUser(void)
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_COUNTER, ret) != QDialog::Accepted)
        return;
    userVar = ret;
    ui->lineEditCount->setText(xStringResource::GetVarName(userVar));
}
// 向下一项
void Formalfaoption::AxisGoDown(void)
{
    quint8 current_Select = ui->tableWidgetAxis->currentRow();
    if (MoveTab(current_Select, current_Select + 1))
    {
        UpdateTab();
        ui->tableWidgetAxis->setCurrentCell(current_Select + 1, 0);
    }
    GetFirstDec();
}
// 向上一项
void Formalfaoption::AxisGoUp(void)
{
    quint8 current_Select = ui->tableWidgetAxis->currentRow();
    if (MoveTab(current_Select, current_Select-1))
    {
        UpdateTab();
        ui->tableWidgetAxis->setCurrentCell(current_Select - 1, 0);
    }
    GetFirstDec();
}
// 根据数组内容，刷新Table参数
void Formalfaoption::UpdateTab()
{
    for(int i = 0;i < 3; i++)
        ui->tableWidgetAxis->item(i, 0)->setText(TranslateAxis(Axis[i]));
}
// 解析轴名称
QString Formalfaoption::TranslateAxis(quint8 Step)
{
    switch (Step)
    {
        case AXIS_IDX_PHOR:		return GetServoName(AXIS_IDX_PHOR);		//*
        case AXIS_IDX_PVER:		return GetServoName(AXIS_IDX_PVER);			//*
        case AXIS_IDX_TRV:		return GetServoName(AXIS_IDX_TRV);			//*
    }
    return "";
}
// 判断轴原点复归顺序
bool Formalfaoption::MoveTab(quint8 currentselect, quint8 last_range)
{
    int i;
    bool ret = FALSE;
    if (last_range > 2) return ret;

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
// 得到减速轴优先等位设置
int Formalfaoption::GetFirstDec()
{
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_PHOR) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_PVER) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_TRV))
        return ORDER_MODE_XYZ;
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_PHOR) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_TRV) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_PVER))
        return ORDER_MODE_XZY;
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_PVER) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_PHOR) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_TRV))
        return ORDER_MODE_YXZ;
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_PVER) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_TRV) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_PHOR))
        return ORDER_MODE_YZX;
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_TRV) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_PHOR) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_PVER))
        return ORDER_MODE_ZXY;
    if (ui->tableWidgetAxis->item(0, 0)->text() == GetServoName(AXIS_IDX_TRV) && ui->tableWidgetAxis->item(1, 0)->text() == GetServoName(AXIS_IDX_PVER) && ui->tableWidgetAxis->item(2, 0)->text() == GetServoName(AXIS_IDX_PHOR))
        return ORDER_MODE_ZYX;
    return 0;
}
// 设置减速轴优先定位设置
void Formalfaoption::SetFirstDec(int fdec)
{
    switch (fdec)
    {
    case ORDER_MODE_XYZ:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_PVER));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_TRV));
        break;
    case ORDER_MODE_XZY:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_TRV));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_PVER));
        break;
    case ORDER_MODE_YXZ:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_PVER));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_TRV));
        break;
    case ORDER_MODE_YZX:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_PVER));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_TRV));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        break;
    case ORDER_MODE_ZXY:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_TRV));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_PVER));
        break;
    case ORDER_MODE_ZYX:
        ui->tableWidgetAxis->item(0, 0)->setText(GetServoName(AXIS_IDX_TRV));
        ui->tableWidgetAxis->item(1, 0)->setText(GetServoName(AXIS_IDX_PVER));
        ui->tableWidgetAxis->item(2, 0)->setText(GetServoName(AXIS_IDX_PHOR));
        break;
    }
}
