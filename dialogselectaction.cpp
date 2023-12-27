#include "xconfig.h"
#include "cmbprotocol.h"
#include "dialogselectaction.h"
#include "ui_dialogselectaction.h"

DialogSelectAction::DialogSelectAction(QWidget *parent) : QDialog(parent), ui(new Ui::DialogSelectAction), m_code(-1)
{
	ui->setupUi(this);
#if defined(Q_WS_QWS)
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
	ui->tabWidget->setCurrentIndex(0);
    pCodeBtn = new QButtonGroup;
    pCodeBtn->addButton(ui->radioLoop2, CODE_FREEPOS);
    pCodeBtn->addButton(ui->radioSingleLoop, CODE_LOOP);
    pCodeBtn->addButton(ui->radioPaper, CODE_PAPER);
    if (!CMBProtocol::GetFunctions(SUB_FUN2_EXT_POS))
    {
        pCodeBtn->addButton(ui->radioPathBegin, CODE_TBEGIN);
        pCodeBtn->addButton(ui->radioPathEnd, CODE_TEND);
    }
    pCodeBtn->addButton(ui->radioExtInput, CODE_EXT_IN);
    pCodeBtn->addButton(ui->radioExtOutput, CODE_MEXTOUT);
    pCodeBtn->addButton(ui->radioDelay, CODE_DELAY);
    pCodeBtn->addButton(ui->radioIf, CODE_IF);
    pCodeBtn->addButton(ui->radioElse, CODE_ELSE);
    pCodeBtn->addButton(ui->radioEndif, CODE_ENDIF);
    pCodeBtn->addButton(ui->radioFor, CODE_FOR_CONST);
    pCodeBtn->addButton(ui->radioEndfor, CODE_ENDFOR);
    pCodeBtn->addButton(ui->radioBreak, CODE_BREAK);
    pCodeBtn->addButton(ui->radioValueVar, CODE_OPR);
    pCodeBtn->addButton(ui->radioSrvStop, CODE_SPEED);
    pCodeBtn->addButton(ui->radioEnd, CODE_END);
    pCodeBtn->addButton(ui->radioInterp, CODE_INTERP);
    pCodeBtn->addButton(ui->radioPower, CODE_POWER);
    pCodeBtn->addButton(ui->radioCircle, CODE_CIRCLE);
    pCodeBtn->addButton(ui->radioSingleLoopFree, CODE_LOOPFREE);
    pCodeBtn->addButton(ui->radioVision, CODE_VISION);

    if (CMBProtocol::GetFunctions(SUB_FUN2_EXT_POS))
    {
        ui->radioPathBegin->setVisible(false);
        ui->radioPathEnd->setVisible(false);
    }
    else
    {
        ui->radioPathBegin->setVisible(true);
        ui->radioPathEnd->setVisible(true);
    }
    pCodeBtn->button(CODE_FREEPOS)->setChecked(true);
    m_code = CODE_FREEPOS;
    connect(pCodeBtn, SIGNAL(buttonClicked(int)), this, SLOT(SelectCode(int)));
}

DialogSelectAction::~DialogSelectAction()
{
	delete ui;
}

void DialogSelectAction::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}
void DialogSelectAction::SelectCode(int code)
{
    m_code = code;
}

int DialogSelectAction::exec(int curProc)
{
#if PENDANT_PROTOCOL
    if (CMBProtocol::GetFunctions(SUB_IN_ANTI_CHECK_HOME_TAIL_LOOP_FREE))
        ui->radioSingleLoopFree->setVisible(true);
    else
        ui->radioSingleLoopFree->setVisible(false);
#else
    ui->radioSingleLoopFree->setVisible(true);
#endif
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
        ui->radioCircle->setEnabled(true);
    else
        ui->radioCircle->setEnabled(false);
    if (CMBProtocol::GetFunctions(SUB_FUN2_VISION))
        ui->radioVision->setVisible(true);
    else
        ui->radioVision->setVisible(false);
    return QDialog::exec();
}
