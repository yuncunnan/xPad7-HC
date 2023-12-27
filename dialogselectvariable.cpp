#include <assert.h>
#include <QButtonGroup>
#include "xconfig.h"
#include "xioport.h"
#include "xstringresource.h"
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "dialogselectvariable.h"
#include "ui_dialogselectvariable.h"

// 界面主页面索引
#define PAGE_USERVAR		0
#define PAGE_EXTIN			1
#define PAGE_EXTOUT			2
#define PAGE_SYSVAR			3
#define PAGE_SYSIO			4
// 扩展输入输出页面索引
#define MAIN_MODULE			0
#define MAIN_MODULE2		1
#define MAIN_MODULE3		2
#define MAIN_MODULE4		3
#define EXT1_MODULE			4
#define EXT2_MODULE			5
#define EXT3_MODULE			6
#define EXT4_MODULE			7

// 系统 I/O 页面索引
#define SYS_IMM_IN			0
#define SYS_IMM_OUT			1
#define SYS_SRV_IN			2
#define SYS_SRV_OUT			3
#define SYS_RBT_IN			4
#define SYS_RBT_OUT			5

const quint16 DialogSelectVariable::extInputVar[8][16] =
{
    { MAIN_VAR_X00, MAIN_VAR_X01, MAIN_VAR_X02, MAIN_VAR_X03, MAIN_VAR_X04, MAIN_VAR_X05, MAIN_VAR_X06, MAIN_VAR_X07, MAIN_VAR_X08, MAIN_VAR_X09, MAIN_VAR_X10, MAIN_VAR_X11, MAIN_VAR_X12, MAIN_VAR_X13, MAIN_VAR_X14, MAIN_VAR_X15},
    { MAIN_VAR_X16, MAIN_VAR_X17, MAIN_VAR_X18, MAIN_VAR_X19, MAIN_VAR_X20, MAIN_VAR_X21, MAIN_VAR_X22, MAIN_VAR_X23, MAIN_VAR_X24, MAIN_VAR_X25, MAIN_VAR_X26, MAIN_VAR_X27, MAIN_VAR_X28, MAIN_VAR_X29, MAIN_VAR_X30, MAIN_VAR_X31},
    { MAIN_VAR_X32, MAIN_VAR_X33, MAIN_VAR_X34, MAIN_VAR_X35, MAIN_VAR_X36, MAIN_VAR_X37, MAIN_VAR_X38, MAIN_VAR_X39, MAIN_VAR_X40, MAIN_VAR_X41, MAIN_VAR_X42, MAIN_VAR_X43, MAIN_VAR_X44, MAIN_VAR_X45, MAIN_VAR_X46, MAIN_VAR_X47},
    { MAIN_VAR_X48, MAIN_VAR_X49, MAIN_VAR_X50, MAIN_VAR_X51, MAIN_VAR_X52, MAIN_VAR_X53, MAIN_VAR_X54, MAIN_VAR_X55, MAIN_VAR_X56, MAIN_VAR_X57, MAIN_VAR_X58, MAIN_VAR_X59, MAIN_VAR_X60, MAIN_VAR_X61, MAIN_VAR_X62, MAIN_VAR_X63},
    { EM1_VAR_X00, EM1_VAR_X01, EM1_VAR_X02, EM1_VAR_X03, EM1_VAR_X04, EM1_VAR_X05, EM1_VAR_X06, EM1_VAR_X07, EM1_VAR_X08, EM1_VAR_X09, EM1_VAR_X10, EM1_VAR_X11, EM1_VAR_X12, EM1_VAR_X13, EM1_VAR_X14, EM1_VAR_X15},
    { EM2_VAR_X00, EM2_VAR_X01, EM2_VAR_X02, EM2_VAR_X03, EM2_VAR_X04, EM2_VAR_X05, EM2_VAR_X06, EM2_VAR_X07, EM2_VAR_X08, EM2_VAR_X09, EM2_VAR_X10, EM2_VAR_X11, EM2_VAR_X12, EM2_VAR_X13, EM2_VAR_X14, EM2_VAR_X15},
    { EM3_VAR_X00, EM3_VAR_X01, EM3_VAR_X02, EM3_VAR_X03, EM3_VAR_X04, EM3_VAR_X05, EM3_VAR_X06, EM3_VAR_X07, EM3_VAR_X08, EM3_VAR_X09, EM3_VAR_X10, EM3_VAR_X11, EM3_VAR_X12, EM3_VAR_X13, EM3_VAR_X14, EM3_VAR_X15},
    { EM4_VAR_X00, EM4_VAR_X01, EM4_VAR_X02, EM4_VAR_X03, EM4_VAR_X04, EM4_VAR_X05, EM4_VAR_X06, EM4_VAR_X07, EM4_VAR_X08, EM4_VAR_X09, EM4_VAR_X10, EM4_VAR_X11, EM4_VAR_X12, EM4_VAR_X13, EM4_VAR_X14, EM4_VAR_X15},
};

const quint16 DialogSelectVariable::extOutputVar[8][16] =
{
    { MAIN_VAR_Y00, MAIN_VAR_Y01, MAIN_VAR_Y02, MAIN_VAR_Y03, MAIN_VAR_Y04, MAIN_VAR_Y05, MAIN_VAR_Y06, MAIN_VAR_Y07, MAIN_VAR_Y08, MAIN_VAR_Y09, MAIN_VAR_Y10, MAIN_VAR_Y11, MAIN_VAR_Y12, MAIN_VAR_Y13, MAIN_VAR_Y14, MAIN_VAR_Y15},
    { MAIN_VAR_Y16, MAIN_VAR_Y17, MAIN_VAR_Y18, MAIN_VAR_Y19, MAIN_VAR_Y20, MAIN_VAR_Y21, MAIN_VAR_Y22, MAIN_VAR_Y23, MAIN_VAR_Y24, MAIN_VAR_Y25, MAIN_VAR_Y26, MAIN_VAR_Y27, MAIN_VAR_Y28, MAIN_VAR_Y29, MAIN_VAR_Y30, MAIN_VAR_Y31},
    { MAIN_VAR_Y32, MAIN_VAR_Y33, MAIN_VAR_Y34, MAIN_VAR_Y35, MAIN_VAR_Y36, MAIN_VAR_Y37, MAIN_VAR_Y38, MAIN_VAR_Y39, MAIN_VAR_Y40, MAIN_VAR_Y41, MAIN_VAR_Y42, MAIN_VAR_Y43, MAIN_VAR_Y44, MAIN_VAR_Y45, MAIN_VAR_Y46, MAIN_VAR_Y47},
    { MAIN_VAR_Y48, MAIN_VAR_Y49, MAIN_VAR_Y50, MAIN_VAR_Y51, MAIN_VAR_Y52, MAIN_VAR_Y53, MAIN_VAR_Y54, MAIN_VAR_Y55, MAIN_VAR_Y56, MAIN_VAR_Y57, MAIN_VAR_Y58, MAIN_VAR_Y59, MAIN_VAR_Y60, MAIN_VAR_Y61, MAIN_VAR_Y62, MAIN_VAR_Y63},
    { EM1_VAR_Y00, EM1_VAR_Y01, EM1_VAR_Y02, EM1_VAR_Y03, EM1_VAR_Y04, EM1_VAR_Y05, EM1_VAR_Y06, EM1_VAR_Y07, EM1_VAR_Y08, EM1_VAR_Y09, EM1_VAR_Y10, EM1_VAR_Y11, EM1_VAR_Y12, EM1_VAR_Y13, EM1_VAR_Y14, EM1_VAR_Y15},
    { EM2_VAR_Y00, EM2_VAR_Y01, EM2_VAR_Y02, EM2_VAR_Y03, EM2_VAR_Y04, EM2_VAR_Y05, EM2_VAR_Y06, EM2_VAR_Y07, EM2_VAR_Y08, EM2_VAR_Y09, EM2_VAR_Y10, EM2_VAR_Y11, EM2_VAR_Y12, EM2_VAR_Y13, EM2_VAR_Y14, EM2_VAR_Y15},
    { EM3_VAR_Y00, EM3_VAR_Y01, EM3_VAR_Y02, EM3_VAR_Y03, EM3_VAR_Y04, EM3_VAR_Y05, EM3_VAR_Y06, EM3_VAR_Y07, EM3_VAR_Y08, EM3_VAR_Y09, EM3_VAR_Y10, EM3_VAR_Y11, EM3_VAR_Y12, EM3_VAR_Y13, EM3_VAR_Y14, EM3_VAR_Y15},
    { EM4_VAR_Y00, EM4_VAR_Y01, EM4_VAR_Y02, EM4_VAR_Y03, EM4_VAR_Y04, EM4_VAR_Y05, EM4_VAR_Y06, EM4_VAR_Y07, EM4_VAR_Y08, EM4_VAR_Y09, EM4_VAR_Y10, EM4_VAR_Y11, EM4_VAR_Y12, EM4_VAR_Y13, EM4_VAR_Y14, EM4_VAR_Y15},
};

const quint16 DialogSelectVariable::systemVar[24] =
{
	SYS_VAR_MOLDS,
	SYS_VAR_X_POS,
	SYS_VAR_Y_POS,
	SYS_VAR_Z_POS,
	SYS_VAR_A_POS,
	SYS_VAR_B_POS,
	SYS_VAR_C_POS,
	SYS_VAR_Y_WAITPOS_INMOLD,
	SYS_VAR_A_WAITPOS_INMOLD,
	SYS_VAR_Z_MINPOS_OUTMOLD,
	SYS_VAR_Z_MAXPOS_OUTMOLD,
	SYS_VAR_Z_MINPOS_INMOLD,
	SYS_VAR_Z_MAXPOS_INMOLD,
	SYS_VAR_X_MINPOS_INMOLD,
	SYS_VAR_X_MAXPOS_INMOLD,
	SYS_VAR_B_MINPOS_INMOLD,
	SYS_VAR_B_MAXPOS_INMOLD,
	SYS_VAR_HOME_ROTATE,
	SYS_VAR_PLAN,
	SYS_VAR_REJECT_ALARM,
    SYS_VAR_PGM_MOLDS,
    SYS_VAR_REJECT,
    SYS_VAR_Z_MINPOS_OUTMOLD2,
    SYS_VAR_Z_MAXPOS_OUTMOLD2
};

#define SYS_IO_NULL			0xFFFF
const quint16 DialogSelectVariable::systemIo[6][12] =
{
	{	// 注塑机信号输入
		IMM_VAR_IN_SAFE,
		IMM_VAR_IN_REJECT,
		IMM_VAR_IN_MCP,
		IMM_VAR_IN_MOP,
        IMM_VAR_IN_IMOP,        // euro
        IMM_VAR_IN_EBP,         // euro
        IMM_VAR_IN_EFP,         // euro
        IMM_VAR_IN_C1P1,        // euro
        IMM_VAR_IN_C1P2,        // euro
        IMM_VAR_IN_C2P1,        // euro
        IMM_VAR_IN_C2P2,        // euro
        IMM_VAR_IN_MID,
    },
	{	// 注塑机信号输出
		IMM_VAR_OUT_MAF,
		IMM_VAR_OUT_EMC,
		IMM_VAR_OUT_EMO,
        IMM_VAR_OUT_RBT,        // euro
		IMM_VAR_OUT_EEB,
		IMM_VAR_OUT_EEF,
        IMM_VAR_OUT_C1P1,       // euro
        IMM_VAR_OUT_C1P2,       // euro
        IMM_VAR_OUT_C2P1,       // euro
        IMM_VAR_OUT_C2P2,       // euro
        SYS_IO_NULL,
        SYS_IO_NULL,
    },
	{	// 伺服信号输入
		SV_VAR_IN_XHOME,
		SV_VAR_IN_YHOME,
		SV_VAR_IN_ZHOME,
		SV_VAR_IN_BHOME,
		SV_VAR_IN_AHOME,
		SV_VAR_IN_CHOME,
		SV_VAR_IN_YWPOS,
		SV_VAR_IN_AWPOS,
		SV_VAR_IN_INMOLD,
		SV_VAR_IN_OUTMOLD,
		SYS_IO_NULL,
		SYS_IO_NULL
	},
	{	// 伺服信号输出
        SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL
    },
	{	// 其它信号输入
		RBT_VAR_IN_DWN_SAF,
		RBT_VAR_IN_PRO_HOR,
		RBT_VAR_IN_PRO_VER,
		RBT_VAR_IN_RUN_ASC,
		RBT_VAR_IN_RUN_DES,
        RBT_VAR_IN_RUN_ADV,
        RBT_VAR_IN_RUN_RET,
		SYS_IO_NULL,
		SYS_IO_NULL,
        SYS_IO_NULL,
        SYS_IO_NULL,
		SYS_IO_NULL
	},
	{	// 其它信号输出
		RBT_VAR_OUT_PRO_HOR,
		RBT_VAR_OUT_PRO_VER,
        RBT_VAR_OUT_RUN_DES,
        RBT_VAR_OUT_RUN_RET,
		SYS_IO_NULL,
		SYS_IO_NULL,
		SYS_IO_NULL,
		SYS_IO_NULL,
		SYS_IO_NULL,
		SYS_IO_NULL,
		SYS_IO_NULL,
		SYS_IO_NULL
	}
};

DialogSelectVariable *xSelVar = 0;

quint32 DialogSelectVariable::returnValue = 0;
bool DialogSelectVariable::m_isconst = false;

DialogSelectVariable::DialogSelectVariable(QWidget *parent) : QDialog(parent), ui(new Ui::DialogSelectVariable)
{
	// 初始化界面
	ui->setupUi(this);
	xSelVar = this;

	ui->tabWidget->setCurrentIndex(0);
	ui->tableExtIn->verticalHeader()->setVisible(true);
	ui->tableExtIn->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	ui->tableExtIn->setCurrentCell(0, 0);

	ui->tableExtOut->verticalHeader()->setVisible(true);
	ui->tableExtOut->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	ui->tableExtOut->setCurrentCell(0, 0);

	ui->tableSysVar->verticalHeader()->setVisible(true);
	ui->tableSysVar->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	ui->tableSysVar->setCurrentCell(0, 0);

	ui->tableSysIo->verticalHeader()->setVisible(true);
	ui->tableSysIo->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	ui->tableSysIo->setCurrentCell(0, 0);

	QFont font;
	int fontSizePx = 28; // 指定字号（像素）
	font.setPixelSize(fontSizePx); // 设置字号为28像素
	for(int i=0;i<16;i++)
	{
		ui->tableExtIn->item(i,0)->setFont(font);
		ui->tableExtIn->verticalHeaderItem(i)->setFont(font);
		ui->tableExtOut->item(i,0)->setFont(font);
		ui->tableExtOut->verticalHeaderItem(i)->setFont(font);
	}
	for(int i=0;i<ui->tableSysVar->rowCount();i++)
	{
		ui->tableSysVar->item(i,0)->setFont(font);
		ui->tableSysVar->verticalHeaderItem(i)->setFont(font);
	}
	for(int i=0;i<ui->tableSysIo->rowCount();i++)
	{
		ui->tableSysIo->item(i,0)->setFont(font);
		ui->tableSysIo->verticalHeaderItem(i)->setFont(font);
	}

#if defined(Q_WS_QWS)
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
	// 组织输入模块选择按钮
	pInModule = new QButtonGroup;
    pInModule->addButton(ui->radioIMain, MAIN_MODULE);
    pInModule->addButton(ui->radioIMain_2, MAIN_MODULE2);
    pInModule->addButton(ui->radioIMain_3, MAIN_MODULE3);
    pInModule->addButton(ui->radioIMain_4, MAIN_MODULE4);
	pInModule->addButton(ui->radioIM1, EXT1_MODULE);
	pInModule->addButton(ui->radioIM2, EXT2_MODULE);
	pInModule->addButton(ui->radioIM3, EXT3_MODULE);
	pInModule->addButton(ui->radioIM4, EXT4_MODULE);
	// 组织输出模块选择按钮
	pOutModule = new QButtonGroup;
    pOutModule->addButton(ui->radioOMain, MAIN_MODULE);
    pOutModule->addButton(ui->radioOMain_2, MAIN_MODULE2);
    pOutModule->addButton(ui->radioOMain_3, MAIN_MODULE3);
    pOutModule->addButton(ui->radioOMain_4, MAIN_MODULE4);
	pOutModule->addButton(ui->radioOM1, EXT1_MODULE);
	pOutModule->addButton(ui->radioOM2, EXT2_MODULE);
	pOutModule->addButton(ui->radioOM3, EXT3_MODULE);
	pOutModule->addButton(ui->radioOM4, EXT4_MODULE);
	// 组织系统IO按钮
	pSysIo = new QButtonGroup;
	pSysIo->addButton(ui->radioImmIn, SYS_IMM_IN);
	pSysIo->addButton(ui->radioImmOut, SYS_IMM_OUT);
	pSysIo->addButton(ui->radioServoIn, SYS_SRV_IN);
	pSysIo->addButton(ui->radioServoOut, SYS_SRV_OUT);
	pSysIo->addButton(ui->radioOtherIn, SYS_RBT_IN);
	pSysIo->addButton(ui->radioOtherOut, SYS_RBT_OUT);
    // 翻译
    ui->radioServoIn->setText(tr("伺服信号输入"));
    ui->radioServoOut->setText(tr("伺服信号输出"));
    ui->radioOtherIn->setText(tr("其他信号输入"));
    ui->radioOtherOut->setText(tr("其他信号输出"));
    // 连接信号槽
	connect(pInModule, SIGNAL(buttonClicked(int)), this, SLOT(inputModuleChanged(int)));
	connect(pOutModule, SIGNAL(buttonClicked(int)), this, SLOT(outputModuleChanged(int)));
	connect(pSysIo, SIGNAL(buttonClicked(int)), this, SLOT(systemIoChanged(int)));
	// 默认第一页
	ui->tabWidget->setCurrentIndex(0);
}

DialogSelectVariable::~DialogSelectVariable()
{
	delete ui;
	delete pInModule;
	delete pOutModule;
	delete pSysIo;
}

void DialogSelectVariable::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
    {
        ui->radioServoIn->setText(tr("伺服信号输入"));
        ui->radioServoOut->setText(tr("伺服信号输出"));
        ui->radioOtherIn->setText(tr("其他信号输入"));
        ui->radioOtherOut->setText(tr("其他信号输出"));
        ui->retranslateUi(this);
        break;
    }
	default:
		break;
	}
}
#if  FA_BEISHITE_CN
// 设置扩展输入端口名称
void DialogSelectVariable::setExtIn(void)
{
    quint16 inVar;
    for (quint8 i = 0; i < 16; i ++)
    {
        inVar = extInputVar[pInModule->checkedId()][i];
        ui->tableExtIn->item(i, 0)->setText(xStringResource::GetVarName(inVar));
#if PENDANT_PROTOCOL
        ui->tableExtIn->item(i, 0)->setFlags(!xIoPort::IsVisibleExtIn(inVar) ? Qt::NoItemFlags : (Qt::ItemIsEnabled | Qt::ItemIsSelectable));
#endif
    }
    ui->radioIM1->setVisible(CMBProtocol::GetExtBoard(0));
    ui->radioIM2->setVisible(CMBProtocol::GetExtBoard(1));
    ui->radioIM3->setVisible(CMBProtocol::GetExtBoard(2));
    ui->radioIM4->setVisible(CMBProtocol::GetExtBoard(3));
    ui->radioIMain_3->setVisible(false);
    ui->radioIMain_4->setVisible(false);
}
// 设置扩展输出端口名称
void DialogSelectVariable::setExtOut(void)
{
    quint16 outVar;
    for (quint8 i = 0; i < 16; i ++)
    {
        outVar = extOutputVar[pOutModule->checkedId()][i];
        ui->tableExtOut->item(i, 0)->setText(xStringResource::GetVarName(outVar));
#if PENDANT_PROTOCOL
        ui->tableExtOut->item(i, 0)->setFlags(!xIoPort::IsVisibleExtOut(outVar) ? Qt::NoItemFlags : (Qt::ItemIsEnabled | Qt::ItemIsSelectable));
#endif
    }
    ui->radioOM1->setVisible(CMBProtocol::GetExtBoard(0));
    ui->radioOM2->setVisible(CMBProtocol::GetExtBoard(1));
    ui->radioOM3->setVisible(CMBProtocol::GetExtBoard(2));
    ui->radioOM4->setVisible(CMBProtocol::GetExtBoard(3));
    ui->radioOMain_3->setVisible(false);
    ui->radioOMain_4->setVisible(false);
}
#else
// 设置扩展输入端口名称
void DialogSelectVariable::setExtIn(void)
{
    quint16 inVar;
    for (quint8 i = 0; i < 16; i ++)
	{
        inVar = extInputVar[pInModule->checkedId()][i];
        ui->tableExtIn->item(i, 0)->setText(xStringResource::GetVarName(inVar));
#if PENDANT_PROTOCOL
        ui->tableExtIn->item(i, 0)->setFlags(!xIoPort::IsVisibleExtIn(inVar) ? Qt::NoItemFlags : (Qt::ItemIsEnabled | Qt::ItemIsSelectable));
#endif
    }
}
// 设置扩展输出端口名称
void DialogSelectVariable::setExtOut(void)
{
	quint16 outVar;
	for (quint8 i = 0; i < 16; i ++)
	{
		outVar = extOutputVar[pOutModule->checkedId()][i];
		ui->tableExtOut->item(i, 0)->setText(xStringResource::GetVarName(outVar));
#if PENDANT_PROTOCOL
        ui->tableExtOut->item(i, 0)->setFlags(!xIoPort::IsVisibleExtOut(outVar) ? Qt::NoItemFlags : (Qt::ItemIsEnabled | Qt::ItemIsSelectable));
#endif
    }
}
#endif
// 设置系统IO端口名称
void DialogSelectVariable::setSysIo(void)
{
    quint16 ioVar;
    for (quint8 i = 0; i < 12; i ++)
    {
        ioVar = systemIo[pSysIo->checkedId()][i];
        ui->tableSysIo->item(i, 0)->setText(xStringResource::GetVarName(ioVar));
#if PENDANT_PROTOCOL
        if (pSysIo->checkedId() == SYS_RBT_IN)
        {
            ui->tableSysIo->item(i, 0)->setFlags(xIoPort::IsVisibleInSignal(ioVar) ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable) : Qt::NoItemFlags);
        }
        if (pSysIo->checkedId() == SYS_RBT_OUT)
        {
            ui->tableSysIo->item(i, 0)->setFlags(xIoPort::IsVisibleOutSignal(ioVar) ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable) : Qt::NoItemFlags);
        }
        if (pSysIo->checkedId() == SYS_IMM_IN)
        {
            ui->tableSysIo->item(i, 0)->setFlags(xIoPort::IsVisibleInSignal(ioVar) ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable) : Qt::NoItemFlags);
        }
        if (pSysIo->checkedId() == SYS_IMM_OUT)
        {
            ui->tableSysIo->item(i, 0)->setFlags(xIoPort::IsVisibleOutSignal(ioVar) ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable) : Qt::NoItemFlags);
        }
        if (pSysIo->checkedId() == SYS_SRV_IN)
        {
            ui->tableSysIo->item(i, 0)->setFlags(xIoPort::IsVisibleInSignal(ioVar) ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable) : Qt::NoItemFlags);
        }
#endif
    }
#if PENDANT_PROTOCOL
    if (CMBProtocol::GetOutmold2use())
    {
        ui->tableSysVar->item(22, 0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->tableSysVar->item(23, 0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    }
    else
    {
        ui->tableSysVar->item(22, 0)->setFlags(Qt::NoItemFlags);
        ui->tableSysVar->item(23, 0)->setFlags(Qt::NoItemFlags);
    }
#endif
}
// 设置端口名称资源
void DialogSelectVariable::setPort(void)
{
    // 扩展输入端口名称
    setExtIn();
    // 扩展输出端口名称
    setExtOut();
    // 系统IO端口名称
    setSysIo();
}

int DialogSelectVariable::DoForm(quint16 mask, quint32 &var, bool *isconst)
{
	int ret;
    m_isconst = false;
    m_mask = mask;
	// 设置端口名称资源
    setPort();
	// 根据掩码设置各个页面状态
	ui->radioConst->setEnabled((mask & VARSEL_MASK_CONST) != 0);
    ui->BoxConst->setEnabled(((mask & VARSEL_MASK_CONST) != 0) && (ui->radioConst->isChecked()));
#if PENDANT_PROTOCOL
	ui->radioIM1->setEnabled(CMBProtocol::GetExtBoard(0));
	ui->radioIM2->setEnabled(CMBProtocol::GetExtBoard(1));
	ui->radioIM3->setEnabled(CMBProtocol::GetExtBoard(2));
	ui->radioIM4->setEnabled(CMBProtocol::GetExtBoard(3));
	ui->radioOM1->setEnabled(CMBProtocol::GetExtBoard(0));
	ui->radioOM2->setEnabled(CMBProtocol::GetExtBoard(1));
	ui->radioOM3->setEnabled(CMBProtocol::GetExtBoard(2));
	ui->radioOM4->setEnabled(CMBProtocol::GetExtBoard(3));
    if(!CMBProtocol::GetFunctions(SUB_FUN2_MAIN64_BITS))
    {
        ui->radioIMain_2->setVisible(false);
        ui->radioIMain_3->setVisible(false);
        ui->radioIMain_4->setVisible(false);
        ui->radioOMain_2->setVisible(false);
        ui->radioOMain_3->setVisible(false);
        ui->radioOMain_4->setVisible(false);
    }
#endif
    ui->tabWidget->setTabEnabled(0, ((mask & VARSEL_MASK_USER) != 0) || ((mask & VARSEL_MASK_COUNTER) != 0));
	ui->tabWidget->setTabEnabled(1, (mask & VARSEL_MASK_EIN) != 0);
	ui->tabWidget->setTabEnabled(2, (mask & VARSEL_MASK_EOUT) != 0);
	ui->tabWidget->setTabEnabled(3, (mask & VARSEL_MASK_SYS) != 0);
	if (((mask & VARSEL_MASK_SYSIN) == 0) && ((mask & VARSEL_MASK_SYSOUT) == 0))
		ui->tabWidget->setTabEnabled(4, false);
	else
	{
		ui->tabWidget->setTabEnabled(4, true);
		ui->radioImmIn->setEnabled((mask & VARSEL_MASK_SYSIN) != 0);
		ui->radioServoIn->setEnabled((mask & VARSEL_MASK_SYSIN) != 0);
		ui->radioOtherIn->setEnabled((mask & VARSEL_MASK_SYSIN) != 0);
		if (ui->radioOtherIn->isChecked())
		{
			ui->tableSysIo->item(1, 0)->setFlags(CMBProtocol::GetExtBoard(0) ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable) : Qt::NoItemFlags);
			ui->tableSysIo->item(2, 0)->setFlags(CMBProtocol::GetExtBoard(0) ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable) : Qt::NoItemFlags);
		}
		ui->radioImmOut->setEnabled((mask & VARSEL_MASK_SYSOUT) != 0);
		ui->radioServoOut->setEnabled((mask & VARSEL_MASK_SYSOUT) != 0);
        ui->radioOtherOut->setEnabled(((mask & VARSEL_MASK_SYSOUT) != 0) ? CMBProtocol::GetExtBoard(0) : false);
	}
	if (!ui->tabWidget->currentWidget()->isEnabled())
	{
		if (ui->tabWidget->widget(PAGE_USERVAR)->isEnabled())
			ui->tabWidget->setCurrentIndex(PAGE_USERVAR);
		else if (ui->tabWidget->widget(PAGE_EXTIN)->isEnabled())
			ui->tabWidget->setCurrentIndex(PAGE_EXTIN);
		else if (ui->tabWidget->widget(PAGE_EXTOUT)->isEnabled())
			ui->tabWidget->setCurrentIndex(PAGE_EXTOUT);
		else if (ui->tabWidget->widget(PAGE_SYSVAR)->isEnabled())
			ui->tabWidget->setCurrentIndex(PAGE_SYSVAR);
		else if (ui->tabWidget->widget(PAGE_SYSIO)->isEnabled())
			ui->tabWidget->setCurrentIndex(PAGE_SYSIO);
	}
    if (((m_mask &VARSEL_MASK_USER) != 0) && ((m_mask &VARSEL_MASK_COUNTER) == 0))
    {
        ui->radioUserVar->setText(tr("选择用户变量 (User-00 - User-399)"));
        ui->BoxVar->setMinimum(0);
        ui->BoxVar->setMaximum(MAX_USER_VAR);
    }
    else
    if (((m_mask &VARSEL_MASK_COUNTER) != 0) && ((m_mask &VARSEL_MASK_USER) == 0))
    {
        ui->radioUserVar->setText(tr("选择用户变量 (Counter-500 - Counter-999)"));
        ui->BoxVar->setMinimum(MAX_USER_VAR+1);
        ui->BoxVar->setMaximum(MAX_COUNTER_VAR);
    }
    else
    if (((m_mask &VARSEL_MASK_USER) != 0) && ((m_mask &VARSEL_MASK_COUNTER) != 0))
    {
        ui->radioUserVar->setText(tr("选择用户变量 (User-00 - Counter-999)"));
        ui->BoxVar->setMinimum(0);
        ui->BoxVar->setMaximum(MAX_COUNTER_VAR);
    }
    if (ui->BoxVar->value() > MAX_USER_VAR)
        ui->BoxVar->setPrefix("Counter-");
    else
        ui->BoxVar->setPrefix("User-");
#if ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_YIDAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE))
    ui->radioImmIn->setText(tr("压铸机信号输入"));
    ui->radioImmOut->setText(tr("压铸机信号输出"));
#elif (FACTORY == FA_SINROBOT_JC)
    ui->radioImmIn->setText(tr("机床信号输入"));
    ui->radioImmOut->setText(tr("机床信号输出"));
#else
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        ui->radioImmIn->setText(tr("压铸机信号输入"));
        ui->radioImmOut->setText(tr("压铸机信号输出"));
    }
    else
    {
        ui->radioImmIn->setText(tr("注塑机信号输入"));
        ui->radioImmOut->setText(tr("注塑机信号输出"));
    }
#endif
    // 显示对话框
	ret = exec();
	// 设置返回的变量
	if (ret == QDialog::Accepted)
    {
        if (isconst) *isconst = m_isconst;
		var = returnValue;
    }

	return ret;
}

// 输入模块选择改变信号槽
void DialogSelectVariable::inputModuleChanged(int)
{
    setExtIn();
	ui->tableExtIn->setCurrentCell(0, 0);
}
// 输出模块选择改变信号槽
void DialogSelectVariable::outputModuleChanged(int)
{
    setExtOut();
	ui->tableExtOut->setCurrentCell(0, 0);
}
// 系统IO选择改变信号槽
void DialogSelectVariable::systemIoChanged(int)
{
    setSysIo();
	ui->tableSysIo->setCurrentCell(0, 0);
}

// 输入用户变量信号槽
void DialogSelectVariable::inputUserVariable(void)
{
	DialogNumberPad numberPad;
    int value;
    if (((m_mask &VARSEL_MASK_USER) != 0 && ((m_mask &VARSEL_MASK_COUNTER) == 0)))
    {
        if (numberPad.DoForm(value, 0, MAX_USER_VAR) == QDialog::Accepted)
        {
            ui->BoxVar->setPrefix("User-");
            ui->BoxVar->setValue(value);
        }
    }
    else
    if (((m_mask &VARSEL_MASK_COUNTER) != 0 && (m_mask &VARSEL_MASK_USER) == 0))
    {
        if (numberPad.DoForm(value, MAX_USER_VAR, MAX_COUNTER_VAR) == QDialog::Accepted)
        {
            ui->BoxVar->setPrefix("Counter-");
            ui->BoxVar->setValue(value);
        }
    }
    else
    if (((m_mask &VARSEL_MASK_USER) != 0) && ((m_mask &VARSEL_MASK_COUNTER) != 0))
    {
        if (numberPad.DoForm(value, 0, MAX_COUNTER_VAR) == QDialog::Accepted)
        {
            if (value > MAX_USER_VAR)
                ui->BoxVar->setPrefix("Counter-");
            else
                ui->BoxVar->setPrefix("User-");
            ui->BoxVar->setValue(value);
        }
    }
}
// 输入常量信号槽
void DialogSelectVariable::inputConst(void)
{
	DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 0, 6000000) == QDialog::Accepted)
		ui->BoxConst->setValue(value);
}

// 确定按钮点击信号槽
void DialogSelectVariable::btnOkClick(void)
{
	int typeId = ui->tabWidget->currentIndex();
	if (typeId == PAGE_USERVAR)
	{
		if (ui->radioUserVar->isChecked() == true)
			// 返回用户变量
			returnValue = CREATE_VAR(VAR_TYPE_USR, ui->BoxVar->value());
		else
        {
			// 返回常量
            m_isconst = true;
            returnValue = ui->BoxConst->value();
        }
	}
	else if (typeId == PAGE_EXTIN)
	{
		// 返回扩展输入变量
		returnValue = extInputVar[pInModule->checkedId()][ui->tableExtIn->currentRow()];
	}
	else if (typeId == PAGE_EXTOUT)
	{
		// 返回扩展输出变量
		returnValue = extOutputVar[pOutModule->checkedId()][ui->tableExtOut->currentRow()];
	}
	else if (typeId == PAGE_SYSVAR)
	{
		// 返回系统变量
		returnValue = systemVar[ui->tableSysVar->currentRow()];
	}
	else if (typeId == PAGE_SYSIO)
	{
		// 返回系统IO变量
		returnValue = systemIo[pSysIo->checkedId()][ui->tableSysIo->currentRow()];
	}
	done(QDialog::Accepted);
	return;
}
