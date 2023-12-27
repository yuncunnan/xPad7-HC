#include <QButtonGroup>
#include "xconfig.h"
#include "cmbprotocol.h"
#include "dialogframe.h"
#include "xioport.h"
#include "xstringresource.h"
#include "xsystemlog.h"
#include "xmessagebox.h"
#include "formio.h"
#include "ui_formio.h"


#define TAB_PAGE_POLARITY   0
#define TAB_PAGE_OUTPUT     1
#define TAB_PAGE_IGNORE     2
#define TAB_PAGE_NOALM      3

#define MAX_TAB_PAGE        4

extern DialogFrame *pDialogMain;

FormIO::FormIO(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormIO)
{
	ui->setupUi(this);
	pModbus = modbus;
}

FormIO::~FormIO()
{
	delete ui;
}
// 查询系统参数设置
bool FormIO::QueryPara(void)
{
	// 得到系统参数设置
	pModbus->GetSystem(SysPara);
	// 备份系统参数设置
	memcpy(&SysParaBak, &SysPara, sizeof(SystemParameter));
    // 主控模块信号极性
    // 主控模块信号极性
 //   if(pModbus->GetFunctions(SUB_FUN2_CAN_IMM))
 //   {
        ui->checkMainX00p->setChecked(GET_POLARITY(SysPara.m_polary[0], 0));
        ui->checkMainX01p->setChecked(GET_POLARITY(SysPara.m_polary[0], 1));
        ui->checkMainX02p->setChecked(GET_POLARITY(SysPara.m_polary[0], 2));
        ui->checkMainX03p->setChecked(GET_POLARITY(SysPara.m_polary[0], 3));
        ui->checkMainX04p->setChecked(GET_POLARITY(SysPara.m_polary[0], 4));
        ui->checkMainX05p->setChecked(GET_POLARITY(SysPara.m_polary[0], 5));
        ui->checkMainX06p->setChecked(GET_POLARITY(SysPara.m_polary[0], 6));
        ui->checkMainX07p->setChecked(GET_POLARITY(SysPara.m_polary[0], 7));
 //   }
    ui->checkMainX08p->setChecked(GET_POLARITY(SysPara.m_polary[0], 8));
    ui->checkMainX09p->setChecked(GET_POLARITY(SysPara.m_polary[0], 9));
    ui->checkMainX10p->setChecked(GET_POLARITY(SysPara.m_polary[0], 10));
    ui->checkMainX11p->setChecked(GET_POLARITY(SysPara.m_polary[0], 11));
    ui->checkMainX12p->setChecked(GET_POLARITY(SysPara.m_polary[0], 12));
    ui->checkMainX13p->setChecked(GET_POLARITY(SysPara.m_polary[0], 13));
    ui->checkMainX14p->setChecked(GET_POLARITY(SysPara.m_polary[0], 14));
    ui->checkMainX15p->setChecked(GET_POLARITY(SysPara.m_polary[0], 15));
    ui->checkMainX16p->setChecked(GET_POLARITY(SysPara.m_polary[0], 16));
    ui->checkMainX17p->setChecked(GET_POLARITY(SysPara.m_polary[0], 17));
    ui->checkMainX18p->setChecked(GET_POLARITY(SysPara.m_polary[0], 18));
    ui->checkMainX19p->setChecked(GET_POLARITY(SysPara.m_polary[0], 19));
    ui->checkMainX20p->setChecked(GET_POLARITY(SysPara.m_polary[0], 20));
    ui->checkMainX21p->setChecked(GET_POLARITY(SysPara.m_polary[0], 21));
    ui->checkMainX22p->setChecked(GET_POLARITY(SysPara.m_polary[0], 22));
    ui->checkMainX23p->setChecked(GET_POLARITY(SysPara.m_polary[0], 23));
    ui->checkMainX24p->setChecked(GET_POLARITY(SysPara.m_polary[0], 24));
    ui->checkMainX25p->setChecked(GET_POLARITY(SysPara.m_polary[0], 25));
    ui->checkMainX26p->setChecked(GET_POLARITY(SysPara.m_polary[0], 26));
    ui->checkMainX27p->setChecked(GET_POLARITY(SysPara.m_polary[0], 27));
    ui->checkMainX28p->setChecked(GET_POLARITY(SysPara.m_polary[0], 28));
    ui->checkMainX29p->setChecked(GET_POLARITY(SysPara.m_polary[0], 29));
    ui->checkMainX30p->setChecked(GET_POLARITY(SysPara.m_polary[0], 30));
    ui->checkMainX31p->setChecked(GET_POLARITY(SysPara.m_polary[0], 31));
    ui->checkMainX32p->setChecked(GET_POLARITY(SysPara.m_polary[0], 32));
    ui->checkMainX33p->setChecked(GET_POLARITY(SysPara.m_polary[0], 33));
    ui->checkMainX34p->setChecked(GET_POLARITY(SysPara.m_polary[0], 34));
    ui->checkMainX35p->setChecked(GET_POLARITY(SysPara.m_polary[0], 35));
    ui->checkMainX36p->setChecked(GET_POLARITY(SysPara.m_polary[0], 36));
    ui->checkMainX37p->setChecked(GET_POLARITY(SysPara.m_polary[0], 37));
    ui->checkMainX38p->setChecked(GET_POLARITY(SysPara.m_polary[0], 38));
    ui->checkMainX39p->setChecked(GET_POLARITY(SysPara.m_polary[0], 39));
    ui->checkMainX40p->setChecked(GET_POLARITY(SysPara.m_polary[0], 40));
    ui->checkMainX41p->setChecked(GET_POLARITY(SysPara.m_polary[0], 41));
    ui->checkMainX42p->setChecked(GET_POLARITY(SysPara.m_polary[0], 42));
    ui->checkMainX43p->setChecked(GET_POLARITY(SysPara.m_polary[0], 43));
    ui->checkMainX44p->setChecked(GET_POLARITY(SysPara.m_polary[0], 44));
    ui->checkMainX45p->setChecked(GET_POLARITY(SysPara.m_polary[0], 45));
    ui->checkMainX46p->setChecked(GET_POLARITY(SysPara.m_polary[0], 46));
    ui->checkMainX47p->setChecked(GET_POLARITY(SysPara.m_polary[0], 47));
    // 扩展模块1信号极性
    ui->checkEm1X01p->setChecked(GET_POLARITY(SysPara.m_polary[1], 0));
    ui->checkEm1X02p->setChecked(GET_POLARITY(SysPara.m_polary[1], 1));
	ui->checkEm1X03p->setChecked(GET_POLARITY(SysPara.m_polary[1], 2));
	ui->checkEm1X04p->setChecked(GET_POLARITY(SysPara.m_polary[1], 3));
	ui->checkEm1X05p->setChecked(GET_POLARITY(SysPara.m_polary[1], 4));
	ui->checkEm1X06p->setChecked(GET_POLARITY(SysPara.m_polary[1], 5));
	ui->checkEm1X07p->setChecked(GET_POLARITY(SysPara.m_polary[1], 6));
	ui->checkEm1X08p->setChecked(GET_POLARITY(SysPara.m_polary[1], 7));
	ui->checkEm1X09p->setChecked(GET_POLARITY(SysPara.m_polary[1], 8));
	ui->checkEm1X10p->setChecked(GET_POLARITY(SysPara.m_polary[1], 9));
	ui->checkEm1X11p->setChecked(GET_POLARITY(SysPara.m_polary[1], 10));
	ui->checkEm1X12p->setChecked(GET_POLARITY(SysPara.m_polary[1], 11));
	ui->checkEm1X13p->setChecked(GET_POLARITY(SysPara.m_polary[1], 12));
    ui->checkEm1X14p->setChecked(GET_POLARITY(SysPara.m_polary[1], 13));
    ui->checkEm1X15p->setChecked(GET_POLARITY(SysPara.m_polary[1], 14));
    ui->checkEm1X16p->setChecked(GET_POLARITY(SysPara.m_polary[1], 15));
    // 扩展模块2信号极性
	ui->checkEm2X01p->setChecked(GET_POLARITY(SysPara.m_polary[2], 0));
	ui->checkEm2X02p->setChecked(GET_POLARITY(SysPara.m_polary[2], 1));
	ui->checkEm2X03p->setChecked(GET_POLARITY(SysPara.m_polary[2], 2));
	ui->checkEm2X04p->setChecked(GET_POLARITY(SysPara.m_polary[2], 3));
	ui->checkEm2X05p->setChecked(GET_POLARITY(SysPara.m_polary[2], 4));
	ui->checkEm2X06p->setChecked(GET_POLARITY(SysPara.m_polary[2], 5));
	ui->checkEm2X07p->setChecked(GET_POLARITY(SysPara.m_polary[2], 6));
	ui->checkEm2X08p->setChecked(GET_POLARITY(SysPara.m_polary[2], 7));
	ui->checkEm2X09p->setChecked(GET_POLARITY(SysPara.m_polary[2], 8));
	ui->checkEm2X10p->setChecked(GET_POLARITY(SysPara.m_polary[2], 9));
	ui->checkEm2X11p->setChecked(GET_POLARITY(SysPara.m_polary[2], 10));
	ui->checkEm2X12p->setChecked(GET_POLARITY(SysPara.m_polary[2], 11));
	ui->checkEm2X13p->setChecked(GET_POLARITY(SysPara.m_polary[2], 12));
    ui->checkEm2X14p->setChecked(GET_POLARITY(SysPara.m_polary[2], 13));
    ui->checkEm2X15p->setChecked(GET_POLARITY(SysPara.m_polary[2], 14));
    ui->checkEm2X16p->setChecked(GET_POLARITY(SysPara.m_polary[2], 15));
    // 扩展模块3信号极性
	ui->checkEm3X01p->setChecked(GET_POLARITY(SysPara.m_polary[3], 0));
	ui->checkEm3X02p->setChecked(GET_POLARITY(SysPara.m_polary[3], 1));
	ui->checkEm3X03p->setChecked(GET_POLARITY(SysPara.m_polary[3], 2));
	ui->checkEm3X04p->setChecked(GET_POLARITY(SysPara.m_polary[3], 3));
	ui->checkEm3X05p->setChecked(GET_POLARITY(SysPara.m_polary[3], 4));
	ui->checkEm3X06p->setChecked(GET_POLARITY(SysPara.m_polary[3], 5));
	ui->checkEm3X07p->setChecked(GET_POLARITY(SysPara.m_polary[3], 6));
	ui->checkEm3X08p->setChecked(GET_POLARITY(SysPara.m_polary[3], 7));
	ui->checkEm3X09p->setChecked(GET_POLARITY(SysPara.m_polary[3], 8));
	ui->checkEm3X10p->setChecked(GET_POLARITY(SysPara.m_polary[3], 9));
	ui->checkEm3X11p->setChecked(GET_POLARITY(SysPara.m_polary[3], 10));
	ui->checkEm3X12p->setChecked(GET_POLARITY(SysPara.m_polary[3], 11));
	ui->checkEm3X13p->setChecked(GET_POLARITY(SysPara.m_polary[3], 12));
    ui->checkEm3X14p->setChecked(GET_POLARITY(SysPara.m_polary[3], 13));
    ui->checkEm3X15p->setChecked(GET_POLARITY(SysPara.m_polary[3], 14));
    ui->checkEm3X16p->setChecked(GET_POLARITY(SysPara.m_polary[3], 15));
    // 扩展模块4信号极性
	ui->checkEm4X01p->setChecked(GET_POLARITY(SysPara.m_polary[4], 0));
	ui->checkEm4X02p->setChecked(GET_POLARITY(SysPara.m_polary[4], 1));
	ui->checkEm4X03p->setChecked(GET_POLARITY(SysPara.m_polary[4], 2));
	ui->checkEm4X04p->setChecked(GET_POLARITY(SysPara.m_polary[4], 3));
	ui->checkEm4X05p->setChecked(GET_POLARITY(SysPara.m_polary[4], 4));
	ui->checkEm4X06p->setChecked(GET_POLARITY(SysPara.m_polary[4], 5));
	ui->checkEm4X07p->setChecked(GET_POLARITY(SysPara.m_polary[4], 6));
	ui->checkEm4X08p->setChecked(GET_POLARITY(SysPara.m_polary[4], 7));
	ui->checkEm4X09p->setChecked(GET_POLARITY(SysPara.m_polary[4], 8));
	ui->checkEm4X10p->setChecked(GET_POLARITY(SysPara.m_polary[4], 9));
	ui->checkEm4X11p->setChecked(GET_POLARITY(SysPara.m_polary[4], 10));
	ui->checkEm4X12p->setChecked(GET_POLARITY(SysPara.m_polary[4], 11));
	ui->checkEm4X13p->setChecked(GET_POLARITY(SysPara.m_polary[4], 12));
    ui->checkEm4X14p->setChecked(GET_POLARITY(SysPara.m_polary[4], 13));
    ui->checkEm4X15p->setChecked(GET_POLARITY(SysPara.m_polary[4], 14));
    ui->checkEm4X16p->setChecked(GET_POLARITY(SysPara.m_polary[4], 15));
    // 主控模块信号报警
        ui->checkMainX00i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 0));
        ui->checkMainX01i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 1));
        ui->checkMainX02i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 2));
        ui->checkMainX03i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 3));
        ui->checkMainX04i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 4));
        ui->checkMainX05i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 5));
        ui->checkMainX06i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 6));
        ui->checkMainX07i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 7));
    ui->checkMainX08i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 8));
    ui->checkMainX09i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 9));
    ui->checkMainX10i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 10));
    ui->checkMainX11i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 11));
    ui->checkMainX12i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 12));
    ui->checkMainX13i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 13));
    ui->checkMainX14i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 14));
    ui->checkMainX15i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 15));
    ui->checkMainX16i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 16));
    ui->checkMainX17i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 17));
    ui->checkMainX18i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 18));
    ui->checkMainX19i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 19));
    ui->checkMainX20i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 20));
    ui->checkMainX21i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 21));
    ui->checkMainX22i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 22));
    ui->checkMainX23i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 23));
    ui->checkMainX24i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 24));
    ui->checkMainX25i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 25));
    ui->checkMainX26i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 26));
    ui->checkMainX27i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 27));
    ui->checkMainX28i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 28));
    ui->checkMainX29i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 29));
    ui->checkMainX30i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 30));
    ui->checkMainX31i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 31));
    ui->checkMainX32i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 32));
    ui->checkMainX33i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 33));
    ui->checkMainX34i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 34));
    ui->checkMainX35i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 35));
    ui->checkMainX36i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 36));
    ui->checkMainX37i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 37));
    ui->checkMainX38i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 38));
    ui->checkMainX39i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 39));
    ui->checkMainX40i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 40));
    ui->checkMainX41i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 41));
    ui->checkMainX42i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 42));
    ui->checkMainX43i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 43));
    ui->checkMainX44i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 44));
    ui->checkMainX45i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 45));
    ui->checkMainX46i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 46));
    ui->checkMainX47i->setChecked(GET_IGNORE(SysPara.m_ignore[0], 47));
    // 扩展模块1信号报警
    ui->checkEm1X01i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 0));
    ui->checkEm1X02i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 1));
	ui->checkEm1X03i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 2));
	ui->checkEm1X04i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 3));
	ui->checkEm1X05i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 4));
	ui->checkEm1X06i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 5));
	ui->checkEm1X07i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 6));
	ui->checkEm1X08i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 7));
	ui->checkEm1X09i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 8));
	ui->checkEm1X10i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 9));
	ui->checkEm1X11i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 10));
	ui->checkEm1X12i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 11));
	ui->checkEm1X13i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 12));
    ui->checkEm1X14i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 13));
    ui->checkEm1X15i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 14));
    ui->checkEm1X16i->setChecked(GET_IGNORE(SysPara.m_ignore[1], 15));
    // 扩展模块2信号报警
	ui->checkEm2X01i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 0));
	ui->checkEm2X02i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 1));
	ui->checkEm2X03i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 2));
	ui->checkEm2X04i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 3));
	ui->checkEm2X05i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 4));
	ui->checkEm2X06i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 5));
	ui->checkEm2X07i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 6));
	ui->checkEm2X08i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 7));
	ui->checkEm2X09i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 8));
	ui->checkEm2X10i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 9));
	ui->checkEm2X11i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 10));
	ui->checkEm2X12i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 11));
	ui->checkEm2X13i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 12));
    ui->checkEm2X14i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 13));
    ui->checkEm2X15i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 14));
    ui->checkEm2X16i->setChecked(GET_IGNORE(SysPara.m_ignore[2], 15));
    // 扩展模块3信号报警
	ui->checkEm3X01i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 0));
	ui->checkEm3X02i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 1));
	ui->checkEm3X03i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 2));
	ui->checkEm3X04i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 3));
	ui->checkEm3X05i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 4));
	ui->checkEm3X06i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 5));
	ui->checkEm3X07i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 6));
	ui->checkEm3X08i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 7));
	ui->checkEm3X09i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 8));
	ui->checkEm3X10i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 9));
	ui->checkEm3X11i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 10));
	ui->checkEm3X12i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 11));
	ui->checkEm3X13i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 12));
    ui->checkEm3X14i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 13));
    ui->checkEm3X15i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 14));
    ui->checkEm3X16i->setChecked(GET_IGNORE(SysPara.m_ignore[3], 15));
    // 扩展模块4信号报警
	ui->checkEm4X01i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 0));
	ui->checkEm4X02i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 1));
	ui->checkEm4X03i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 2));
	ui->checkEm4X04i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 3));
	ui->checkEm4X05i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 4));
	ui->checkEm4X06i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 5));
	ui->checkEm4X07i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 6));
	ui->checkEm4X08i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 7));
	ui->checkEm4X09i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 8));
	ui->checkEm4X10i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 9));
	ui->checkEm4X11i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 10));
	ui->checkEm4X12i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 11));
	ui->checkEm4X13i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 12));
    ui->checkEm4X14i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 13));
    ui->checkEm4X15i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 14));
    ui->checkEm4X16i->setChecked(GET_IGNORE(SysPara.m_ignore[4], 15));
    // 主控模块模内不报警
        ui->checkMainX00a->setChecked(GET_NOALM(SysPara.m_noalm[0], 0));
        ui->checkMainX01a->setChecked(GET_NOALM(SysPara.m_noalm[0], 1));
        ui->checkMainX02a->setChecked(GET_NOALM(SysPara.m_noalm[0], 2));
        ui->checkMainX03a->setChecked(GET_NOALM(SysPara.m_noalm[0], 3));
        ui->checkMainX04a->setChecked(GET_NOALM(SysPara.m_noalm[0], 4));
        ui->checkMainX05a->setChecked(GET_NOALM(SysPara.m_noalm[0], 5));
        ui->checkMainX06a->setChecked(GET_NOALM(SysPara.m_noalm[0], 6));
        ui->checkMainX07a->setChecked(GET_NOALM(SysPara.m_noalm[0], 7));
    ui->checkMainX08a->setChecked(GET_NOALM(SysPara.m_noalm[0], 8));
    ui->checkMainX09a->setChecked(GET_NOALM(SysPara.m_noalm[0], 9));
    ui->checkMainX10a->setChecked(GET_NOALM(SysPara.m_noalm[0], 10));
    ui->checkMainX11a->setChecked(GET_NOALM(SysPara.m_noalm[0], 11));
    ui->checkMainX12a->setChecked(GET_NOALM(SysPara.m_noalm[0], 12));
    ui->checkMainX13a->setChecked(GET_NOALM(SysPara.m_noalm[0], 13));
    ui->checkMainX14a->setChecked(GET_NOALM(SysPara.m_noalm[0], 14));
    ui->checkMainX15a->setChecked(GET_NOALM(SysPara.m_noalm[0], 15));
    ui->checkMainX16a->setChecked(GET_NOALM(SysPara.m_noalm[0], 16));
    ui->checkMainX17a->setChecked(GET_NOALM(SysPara.m_noalm[0], 17));
    ui->checkMainX18a->setChecked(GET_NOALM(SysPara.m_noalm[0], 18));
    ui->checkMainX19a->setChecked(GET_NOALM(SysPara.m_noalm[0], 19));
    ui->checkMainX20a->setChecked(GET_NOALM(SysPara.m_noalm[0], 20));
    ui->checkMainX21a->setChecked(GET_NOALM(SysPara.m_noalm[0], 21));
    ui->checkMainX22a->setChecked(GET_NOALM(SysPara.m_noalm[0], 22));
    ui->checkMainX23a->setChecked(GET_NOALM(SysPara.m_noalm[0], 23));
    ui->checkMainX24a->setChecked(GET_NOALM(SysPara.m_noalm[0], 24));
    ui->checkMainX25a->setChecked(GET_NOALM(SysPara.m_noalm[0], 25));
    ui->checkMainX26a->setChecked(GET_NOALM(SysPara.m_noalm[0], 26));
    ui->checkMainX27a->setChecked(GET_NOALM(SysPara.m_noalm[0], 27));
    ui->checkMainX28a->setChecked(GET_NOALM(SysPara.m_noalm[0], 28));
    ui->checkMainX29a->setChecked(GET_NOALM(SysPara.m_noalm[0], 29));
    ui->checkMainX30a->setChecked(GET_NOALM(SysPara.m_noalm[0], 30));
    ui->checkMainX31a->setChecked(GET_NOALM(SysPara.m_noalm[0], 31));
    ui->checkMainX32a->setChecked(GET_NOALM(SysPara.m_noalm[0], 32));
    ui->checkMainX33a->setChecked(GET_NOALM(SysPara.m_noalm[0], 33));
    ui->checkMainX34a->setChecked(GET_NOALM(SysPara.m_noalm[0], 34));
    ui->checkMainX35a->setChecked(GET_NOALM(SysPara.m_noalm[0], 35));
    ui->checkMainX36a->setChecked(GET_NOALM(SysPara.m_noalm[0], 36));
    ui->checkMainX37a->setChecked(GET_NOALM(SysPara.m_noalm[0], 37));
    ui->checkMainX38a->setChecked(GET_NOALM(SysPara.m_noalm[0], 38));
    ui->checkMainX39a->setChecked(GET_NOALM(SysPara.m_noalm[0], 39));
    ui->checkMainX40a->setChecked(GET_NOALM(SysPara.m_noalm[0], 40));
    ui->checkMainX41a->setChecked(GET_NOALM(SysPara.m_noalm[0], 41));
    ui->checkMainX42a->setChecked(GET_NOALM(SysPara.m_noalm[0], 42));
    ui->checkMainX43a->setChecked(GET_NOALM(SysPara.m_noalm[0], 43));
    ui->checkMainX44a->setChecked(GET_NOALM(SysPara.m_noalm[0], 44));
    ui->checkMainX45a->setChecked(GET_NOALM(SysPara.m_noalm[0], 45));
    ui->checkMainX46a->setChecked(GET_NOALM(SysPara.m_noalm[0], 46));
    ui->checkMainX47a->setChecked(GET_NOALM(SysPara.m_noalm[0], 47));
    // 扩展模块1模内不报警
    ui->checkEm1X01a->setChecked(GET_NOALM(SysPara.m_noalm[1], 0));
    ui->checkEm1X02a->setChecked(GET_NOALM(SysPara.m_noalm[1], 1));
	ui->checkEm1X03a->setChecked(GET_NOALM(SysPara.m_noalm[1], 2));
	ui->checkEm1X04a->setChecked(GET_NOALM(SysPara.m_noalm[1], 3));
	ui->checkEm1X05a->setChecked(GET_NOALM(SysPara.m_noalm[1], 4));
	ui->checkEm1X06a->setChecked(GET_NOALM(SysPara.m_noalm[1], 5));
	ui->checkEm1X07a->setChecked(GET_NOALM(SysPara.m_noalm[1], 6));
	ui->checkEm1X08a->setChecked(GET_NOALM(SysPara.m_noalm[1], 7));
	ui->checkEm1X09a->setChecked(GET_NOALM(SysPara.m_noalm[1], 8));
	ui->checkEm1X10a->setChecked(GET_NOALM(SysPara.m_noalm[1], 9));
	ui->checkEm1X11a->setChecked(GET_NOALM(SysPara.m_noalm[1], 10));
	ui->checkEm1X12a->setChecked(GET_NOALM(SysPara.m_noalm[1], 11));
	ui->checkEm1X13a->setChecked(GET_NOALM(SysPara.m_noalm[1], 12));
    ui->checkEm1X14a->setChecked(GET_NOALM(SysPara.m_noalm[1], 13));
    ui->checkEm1X15a->setChecked(GET_NOALM(SysPara.m_noalm[1], 14));
    ui->checkEm1X16a->setChecked(GET_NOALM(SysPara.m_noalm[1], 15));
    // 扩展模块2模内不报警
	ui->checkEm2X01a->setChecked(GET_NOALM(SysPara.m_noalm[2], 0));
	ui->checkEm2X02a->setChecked(GET_NOALM(SysPara.m_noalm[2], 1));
	ui->checkEm2X03a->setChecked(GET_NOALM(SysPara.m_noalm[2], 2));
	ui->checkEm2X04a->setChecked(GET_NOALM(SysPara.m_noalm[2], 3));
	ui->checkEm2X05a->setChecked(GET_NOALM(SysPara.m_noalm[2], 4));
	ui->checkEm2X06a->setChecked(GET_NOALM(SysPara.m_noalm[2], 5));
	ui->checkEm2X07a->setChecked(GET_NOALM(SysPara.m_noalm[2], 6));
	ui->checkEm2X08a->setChecked(GET_NOALM(SysPara.m_noalm[2], 7));
	ui->checkEm2X09a->setChecked(GET_NOALM(SysPara.m_noalm[2], 8));
	ui->checkEm2X10a->setChecked(GET_NOALM(SysPara.m_noalm[2], 9));
	ui->checkEm2X11a->setChecked(GET_NOALM(SysPara.m_noalm[2], 10));
	ui->checkEm2X12a->setChecked(GET_NOALM(SysPara.m_noalm[2], 11));
	ui->checkEm2X13a->setChecked(GET_NOALM(SysPara.m_noalm[2], 12));
    ui->checkEm2X14a->setChecked(GET_NOALM(SysPara.m_noalm[2], 13));
    ui->checkEm2X15a->setChecked(GET_NOALM(SysPara.m_noalm[2], 14));
    ui->checkEm2X16a->setChecked(GET_NOALM(SysPara.m_noalm[2], 15));
    // 扩展模块3模内不报警
	ui->checkEm3X01a->setChecked(GET_NOALM(SysPara.m_noalm[3], 0));
	ui->checkEm3X02a->setChecked(GET_NOALM(SysPara.m_noalm[3], 1));
	ui->checkEm3X03a->setChecked(GET_NOALM(SysPara.m_noalm[3], 2));
	ui->checkEm3X04a->setChecked(GET_NOALM(SysPara.m_noalm[3], 3));
	ui->checkEm3X05a->setChecked(GET_NOALM(SysPara.m_noalm[3], 4));
	ui->checkEm3X06a->setChecked(GET_NOALM(SysPara.m_noalm[3], 5));
	ui->checkEm3X07a->setChecked(GET_NOALM(SysPara.m_noalm[3], 6));
	ui->checkEm3X08a->setChecked(GET_NOALM(SysPara.m_noalm[3], 7));
	ui->checkEm3X09a->setChecked(GET_NOALM(SysPara.m_noalm[3], 8));
	ui->checkEm3X10a->setChecked(GET_NOALM(SysPara.m_noalm[3], 9));
	ui->checkEm3X11a->setChecked(GET_NOALM(SysPara.m_noalm[3], 10));
	ui->checkEm3X12a->setChecked(GET_NOALM(SysPara.m_noalm[3], 11));
	ui->checkEm3X13a->setChecked(GET_NOALM(SysPara.m_noalm[3], 12));
    ui->checkEm3X14a->setChecked(GET_NOALM(SysPara.m_noalm[3], 13));
    ui->checkEm3X15a->setChecked(GET_NOALM(SysPara.m_noalm[3], 14));
    ui->checkEm3X16a->setChecked(GET_NOALM(SysPara.m_noalm[3], 15));
    // 扩展模块4模内不报警
	ui->checkEm4X01a->setChecked(GET_NOALM(SysPara.m_noalm[4], 0));
	ui->checkEm4X02a->setChecked(GET_NOALM(SysPara.m_noalm[4], 1));
	ui->checkEm4X03a->setChecked(GET_NOALM(SysPara.m_noalm[4], 2));
	ui->checkEm4X04a->setChecked(GET_NOALM(SysPara.m_noalm[4], 3));
	ui->checkEm4X05a->setChecked(GET_NOALM(SysPara.m_noalm[4], 4));
	ui->checkEm4X06a->setChecked(GET_NOALM(SysPara.m_noalm[4], 5));
	ui->checkEm4X07a->setChecked(GET_NOALM(SysPara.m_noalm[4], 6));
	ui->checkEm4X08a->setChecked(GET_NOALM(SysPara.m_noalm[4], 7));
	ui->checkEm4X09a->setChecked(GET_NOALM(SysPara.m_noalm[4], 8));
	ui->checkEm4X10a->setChecked(GET_NOALM(SysPara.m_noalm[4], 9));
	ui->checkEm4X11a->setChecked(GET_NOALM(SysPara.m_noalm[4], 10));
	ui->checkEm4X12a->setChecked(GET_NOALM(SysPara.m_noalm[4], 11));
	ui->checkEm4X13a->setChecked(GET_NOALM(SysPara.m_noalm[4], 12));
    ui->checkEm4X14a->setChecked(GET_NOALM(SysPara.m_noalm[4], 13));
    ui->checkEm4X15a->setChecked(GET_NOALM(SysPara.m_noalm[4], 14));
    ui->checkEm4X16a->setChecked(GET_NOALM(SysPara.m_noalm[4], 15));

    // 主控模块输出信号极性
        ui->checkMainY00p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 0));
        ui->checkMainY01p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 1));
        ui->checkMainY02p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 2));
        ui->checkMainY03p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 3));
        ui->checkMainY04p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 4));
        ui->checkMainY05p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 5));
        ui->checkMainY06p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 6));
        ui->checkMainY07p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 7));
    ui->checkMainY08p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 8));
    ui->checkMainY09p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 9));
    ui->checkMainY10p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 10));
    ui->checkMainY11p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 11));
    ui->checkMainY12p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 12));
    ui->checkMainY13p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 13));
    ui->checkMainY14p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 14));
    ui->checkMainY15p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 15));
    ui->checkMainY16p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 16));
    ui->checkMainY17p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 17));
    ui->checkMainY18p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 18));
    ui->checkMainY19p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 19));
    ui->checkMainY20p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 20));
    ui->checkMainY21p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 21));
    ui->checkMainY22p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 22));
    ui->checkMainY23p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 23));
    ui->checkMainY24p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 24));
    ui->checkMainY25p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 25));
    ui->checkMainY26p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 26));
    ui->checkMainY27p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 27));
    ui->checkMainY28p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 28));
    ui->checkMainY29p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 29));
    ui->checkMainY30p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 30));
    ui->checkMainY31p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 31));
    ui->checkMainY32p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 32));
    ui->checkMainY33p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 33));
    ui->checkMainY34p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 34));
    ui->checkMainY35p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 35));
    ui->checkMainY36p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 36));
    ui->checkMainY37p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 37));
    ui->checkMainY38p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 38));
    ui->checkMainY39p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 39));
    ui->checkMainY40p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 40));
    ui->checkMainY41p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 41));
    ui->checkMainY42p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 42));
    ui->checkMainY43p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 43));
    ui->checkMainY44p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 44));
    ui->checkMainY45p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 45));
    ui->checkMainY46p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 46));
    ui->checkMainY47p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[0], 47));
    // 扩展模块1输出信号极性
    ui->checkEm1Y01p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 0));
    ui->checkEm1Y02p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 1));
    ui->checkEm1Y03p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 2));
    ui->checkEm1Y04p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 3));
    ui->checkEm1Y05p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 4));
    ui->checkEm1Y06p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 5));
    ui->checkEm1Y07p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 6));
    ui->checkEm1Y08p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 7));
    ui->checkEm1Y09p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 8));
    ui->checkEm1Y10p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 9));
    ui->checkEm1Y11p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 10));
    ui->checkEm1Y12p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 11));
    ui->checkEm1Y13p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 12));
    ui->checkEm1Y14p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 13));
    ui->checkEm1Y15p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 14));
    ui->checkEm1Y16p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[1], 15));
    // 扩展模块2输出信号极性
    ui->checkEm2Y01p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 0));
    ui->checkEm2Y02p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 1));
    ui->checkEm2Y03p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 2));
    ui->checkEm2Y04p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 3));
    ui->checkEm2Y05p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 4));
    ui->checkEm2Y06p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 5));
    ui->checkEm2Y07p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 6));
    ui->checkEm2Y08p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 7));
    ui->checkEm2Y09p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 8));
    ui->checkEm2Y10p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 9));
    ui->checkEm2Y11p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 10));
    ui->checkEm2Y12p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 11));
    ui->checkEm2Y13p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 12));
    ui->checkEm2Y14p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 13));
    ui->checkEm2Y15p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 14));
    ui->checkEm2Y16p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[2], 15));
    // 扩展模块3输出信号极性
    ui->checkEm3Y01p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 0));
    ui->checkEm3Y02p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 1));
    ui->checkEm3Y03p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 2));
    ui->checkEm3Y04p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 3));
    ui->checkEm3Y05p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 4));
    ui->checkEm3Y06p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 5));
    ui->checkEm3Y07p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 6));
    ui->checkEm3Y08p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 7));
    ui->checkEm3Y09p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 8));
    ui->checkEm3Y10p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 9));
    ui->checkEm3Y11p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 10));
    ui->checkEm3Y12p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 11));
    ui->checkEm3Y13p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 12));
    ui->checkEm3Y14p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 13));
    ui->checkEm3Y15p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 14));
    ui->checkEm3Y16p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[3], 15));
    // 扩展模块4输出信号极性
    ui->checkEm4Y01p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 0));
    ui->checkEm4Y02p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 1));
    ui->checkEm4Y03p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 2));
    ui->checkEm4Y04p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 3));
    ui->checkEm4Y05p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 4));
    ui->checkEm4Y06p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 5));
    ui->checkEm4Y07p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 6));
    ui->checkEm4Y08p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 7));
    ui->checkEm4Y09p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 8));
    ui->checkEm4Y10p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 9));
    ui->checkEm4Y11p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 10));
    ui->checkEm4Y12p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 11));
    ui->checkEm4Y13p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 12));
    ui->checkEm4Y14p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 13));
    ui->checkEm4Y15p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 14));
    ui->checkEm4Y16p->setChecked(GET_OUTPOLARITY(SysPara.m_outputpolary[4], 15));
    return true;
}

// 从界面得到系统参数设置
void FormIO::LoadPara(void)
{
	if (xPermissions::GetPermissions(PER_SYS_SIGNAL))
	{
        // 主板信号极性
//        if (ui->checkLowAir->isChecked())	SET_POLARITY(SysPara.m_polary[0], 7, 1);	else	SET_POLARITY(SysPara.m_polary[0], 7, 0);
        // 主控模块极性
        if (ui->checkMainX00p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 0, 1);	else	SET_POLARITY(SysPara.m_polary[0], 0, 0);
        if (ui->checkMainX01p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 1, 1);	else	SET_POLARITY(SysPara.m_polary[0], 1, 0);
        if (ui->checkMainX02p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 2, 1);	else	SET_POLARITY(SysPara.m_polary[0], 2, 0);
        if (ui->checkMainX03p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 3, 1);	else	SET_POLARITY(SysPara.m_polary[0], 3, 0);
        if (ui->checkMainX04p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 4, 1);	else	SET_POLARITY(SysPara.m_polary[0], 4, 0);
        if (ui->checkMainX05p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 5, 1);	else	SET_POLARITY(SysPara.m_polary[0], 5, 0);
        if (ui->checkMainX06p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 6, 1);	else	SET_POLARITY(SysPara.m_polary[0], 6, 0);
        if (ui->checkMainX07p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 7, 1);	else	SET_POLARITY(SysPara.m_polary[0], 7, 0);
        if (ui->checkMainX08p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 8, 1);	else	SET_POLARITY(SysPara.m_polary[0], 8, 0);
        if (ui->checkMainX09p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 9, 1);	else	SET_POLARITY(SysPara.m_polary[0], 9, 0);
        if (ui->checkMainX10p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 10, 1);	else	SET_POLARITY(SysPara.m_polary[0], 10, 0);
        if (ui->checkMainX11p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 11, 1);	else	SET_POLARITY(SysPara.m_polary[0], 11, 0);
        if (ui->checkMainX12p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 12, 1);	else	SET_POLARITY(SysPara.m_polary[0], 12, 0);
        if (ui->checkMainX13p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 13, 1);	else	SET_POLARITY(SysPara.m_polary[0], 13, 0);
        if (ui->checkMainX14p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 14, 1);	else	SET_POLARITY(SysPara.m_polary[0], 14, 0);
        if (ui->checkMainX15p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 15, 1);	else	SET_POLARITY(SysPara.m_polary[0], 15, 0);
        if (ui->checkMainX16p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 16, 1);	else	SET_POLARITY(SysPara.m_polary[0], 16, 0);
        if (ui->checkMainX17p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 17, 1);	else	SET_POLARITY(SysPara.m_polary[0], 17, 0);
        if (ui->checkMainX18p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 18, 1);	else	SET_POLARITY(SysPara.m_polary[0], 18, 0);
        if (ui->checkMainX19p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 19, 1);	else	SET_POLARITY(SysPara.m_polary[0], 19, 0);
        if (ui->checkMainX20p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 20, 1);	else	SET_POLARITY(SysPara.m_polary[0], 20, 0);
        if (ui->checkMainX21p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 21, 1);	else	SET_POLARITY(SysPara.m_polary[0], 21, 0);
        if (ui->checkMainX22p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 22, 1);	else	SET_POLARITY(SysPara.m_polary[0], 22, 0);
        if (ui->checkMainX23p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 23, 1);	else	SET_POLARITY(SysPara.m_polary[0], 23, 0);
        if (ui->checkMainX24p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 24, 1);	else	SET_POLARITY(SysPara.m_polary[0], 24, 0);
        if (ui->checkMainX25p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 25, 1);	else	SET_POLARITY(SysPara.m_polary[0], 25, 0);
        if (ui->checkMainX26p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 26, 1);	else	SET_POLARITY(SysPara.m_polary[0], 26, 0);
        if (ui->checkMainX27p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 27, 1);	else	SET_POLARITY(SysPara.m_polary[0], 27, 0);
        if (ui->checkMainX28p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 28, 1);	else	SET_POLARITY(SysPara.m_polary[0], 28, 0);
        if (ui->checkMainX29p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 29, 1);	else	SET_POLARITY(SysPara.m_polary[0], 29, 0);
        if (ui->checkMainX30p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 30, 1);	else	SET_POLARITY(SysPara.m_polary[0], 30, 0);
        if (ui->checkMainX31p->isChecked())	SET_POLARITY(SysPara.m_polary[0], 31, 1);	else	SET_POLARITY(SysPara.m_polary[0], 31, 0);
        if (ui->checkMainX32p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)32, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)32, (uint64_t)0);
        if (ui->checkMainX33p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)33, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)33, (uint64_t)0);
        if (ui->checkMainX34p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)34, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)34, (uint64_t)0);
        if (ui->checkMainX35p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)35, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)35, (uint64_t)0);
        if (ui->checkMainX36p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)36, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)36, (uint64_t)0);
        if (ui->checkMainX37p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)37, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)37, (uint64_t)0);
        if (ui->checkMainX38p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)38, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)38, (uint64_t)0);
        if (ui->checkMainX39p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)39, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)39, (uint64_t)0);
        if (ui->checkMainX40p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)40, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)40, (uint64_t)0);
        if (ui->checkMainX41p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)41, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)41, (uint64_t)0);
        if (ui->checkMainX42p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)42, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)42, (uint64_t)0);
        if (ui->checkMainX43p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)43, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)43, (uint64_t)0);
        if (ui->checkMainX44p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)44, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)44, (uint64_t)0);
        if (ui->checkMainX45p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)45, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)45, (uint64_t)0);
        if (ui->checkMainX46p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)46, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)46, (uint64_t)0);
        if (ui->checkMainX47p->isChecked())	SET_POLARITY(SysPara.m_polary[0], (uint64_t)47, (uint64_t)1);	else	SET_POLARITY(SysPara.m_polary[0], (uint64_t)47, (uint64_t)0);
		// 扩展模块1极性
        if (ui->checkEm1X01p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 0, 1);	else	SET_POLARITY(SysPara.m_polary[1], 0, 0);
        if (ui->checkEm1X02p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 1, 1);	else	SET_POLARITY(SysPara.m_polary[1], 1, 0);
		if (ui->checkEm1X03p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 2, 1);	else	SET_POLARITY(SysPara.m_polary[1], 2, 0);
		if (ui->checkEm1X04p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 3, 1);	else	SET_POLARITY(SysPara.m_polary[1], 3, 0);
		if (ui->checkEm1X05p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 4, 1);	else	SET_POLARITY(SysPara.m_polary[1], 4, 0);
		if (ui->checkEm1X06p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 5, 1);	else	SET_POLARITY(SysPara.m_polary[1], 5, 0);
		if (ui->checkEm1X07p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 6, 1);	else	SET_POLARITY(SysPara.m_polary[1], 6, 0);
		if (ui->checkEm1X08p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 7, 1);	else	SET_POLARITY(SysPara.m_polary[1], 7, 0);
		if (ui->checkEm1X09p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 8, 1);	else	SET_POLARITY(SysPara.m_polary[1], 8, 0);
		if (ui->checkEm1X10p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 9, 1);	else	SET_POLARITY(SysPara.m_polary[1], 9, 0);
		if (ui->checkEm1X11p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 10, 1);	else	SET_POLARITY(SysPara.m_polary[1], 10, 0);
		if (ui->checkEm1X12p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 11, 1);	else	SET_POLARITY(SysPara.m_polary[1], 11, 0);
		if (ui->checkEm1X13p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 12, 1);	else	SET_POLARITY(SysPara.m_polary[1], 12, 0);
        if (ui->checkEm1X14p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 13, 1);	else	SET_POLARITY(SysPara.m_polary[1], 13, 0);
        if (ui->checkEm1X15p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 14, 1);	else	SET_POLARITY(SysPara.m_polary[1], 14, 0);
        if (ui->checkEm1X16p->isChecked())	SET_POLARITY(SysPara.m_polary[1], 15, 1);	else	SET_POLARITY(SysPara.m_polary[1], 15, 0);
        // 扩展模块2极性
		if (ui->checkEm2X01p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 0, 1);	else	SET_POLARITY(SysPara.m_polary[2], 0, 0);
		if (ui->checkEm2X02p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 1, 1);	else	SET_POLARITY(SysPara.m_polary[2], 1, 0);
		if (ui->checkEm2X03p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 2, 1);	else	SET_POLARITY(SysPara.m_polary[2], 2, 0);
		if (ui->checkEm2X04p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 3, 1);	else	SET_POLARITY(SysPara.m_polary[2], 3, 0);
		if (ui->checkEm2X05p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 4, 1);	else	SET_POLARITY(SysPara.m_polary[2], 4, 0);
		if (ui->checkEm2X06p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 5, 1);	else	SET_POLARITY(SysPara.m_polary[2], 5, 0);
		if (ui->checkEm2X07p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 6, 1);	else	SET_POLARITY(SysPara.m_polary[2], 6, 0);
		if (ui->checkEm2X08p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 7, 1);	else	SET_POLARITY(SysPara.m_polary[2], 7, 0);
		if (ui->checkEm2X09p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 8, 1);	else	SET_POLARITY(SysPara.m_polary[2], 8, 0);
		if (ui->checkEm2X10p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 9, 1);	else	SET_POLARITY(SysPara.m_polary[2], 9, 0);
		if (ui->checkEm2X11p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 10, 1);	else	SET_POLARITY(SysPara.m_polary[2], 10, 0);
		if (ui->checkEm2X12p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 11, 1);	else	SET_POLARITY(SysPara.m_polary[2], 11, 0);
		if (ui->checkEm2X13p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 12, 1);	else	SET_POLARITY(SysPara.m_polary[2], 12, 0);
        if (ui->checkEm2X14p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 13, 1);	else	SET_POLARITY(SysPara.m_polary[2], 13, 0);
        if (ui->checkEm2X15p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 14, 1);	else	SET_POLARITY(SysPara.m_polary[2], 14, 0);
        if (ui->checkEm2X16p->isChecked())	SET_POLARITY(SysPara.m_polary[2], 15, 1);	else	SET_POLARITY(SysPara.m_polary[2], 15, 0);
        // 扩展模块3极性
		if (ui->checkEm3X01p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 0, 1);	else	SET_POLARITY(SysPara.m_polary[3], 0, 0);
		if (ui->checkEm3X02p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 1, 1);	else	SET_POLARITY(SysPara.m_polary[3], 1, 0);
		if (ui->checkEm3X03p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 2, 1);	else	SET_POLARITY(SysPara.m_polary[3], 2, 0);
		if (ui->checkEm3X04p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 3, 1);	else	SET_POLARITY(SysPara.m_polary[3], 3, 0);
		if (ui->checkEm3X05p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 4, 1);	else	SET_POLARITY(SysPara.m_polary[3], 4, 0);
		if (ui->checkEm3X06p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 5, 1);	else	SET_POLARITY(SysPara.m_polary[3], 5, 0);
		if (ui->checkEm3X07p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 6, 1);	else	SET_POLARITY(SysPara.m_polary[3], 6, 0);
		if (ui->checkEm3X08p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 7, 1);	else	SET_POLARITY(SysPara.m_polary[3], 7, 0);
		if (ui->checkEm3X09p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 8, 1);	else	SET_POLARITY(SysPara.m_polary[3], 8, 0);
		if (ui->checkEm3X10p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 9, 1);	else	SET_POLARITY(SysPara.m_polary[3], 9, 0);
		if (ui->checkEm3X11p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 10, 1);	else	SET_POLARITY(SysPara.m_polary[3], 10, 0);
		if (ui->checkEm3X12p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 11, 1);	else	SET_POLARITY(SysPara.m_polary[3], 11, 0);
		if (ui->checkEm3X13p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 12, 1);	else	SET_POLARITY(SysPara.m_polary[3], 12, 0);
        if (ui->checkEm3X14p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 13, 1);	else	SET_POLARITY(SysPara.m_polary[3], 13, 0);
        if (ui->checkEm3X15p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 14, 1);	else	SET_POLARITY(SysPara.m_polary[3], 14, 0);
        if (ui->checkEm3X16p->isChecked())	SET_POLARITY(SysPara.m_polary[3], 15, 1);	else	SET_POLARITY(SysPara.m_polary[3], 15, 0);
        // 扩展模块4极性
		if (ui->checkEm4X01p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 0, 1);	else	SET_POLARITY(SysPara.m_polary[4], 0, 0);
		if (ui->checkEm4X02p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 1, 1);	else	SET_POLARITY(SysPara.m_polary[4], 1, 0);
		if (ui->checkEm4X03p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 2, 1);	else	SET_POLARITY(SysPara.m_polary[4], 2, 0);
		if (ui->checkEm4X04p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 3, 1);	else	SET_POLARITY(SysPara.m_polary[4], 3, 0);
		if (ui->checkEm4X05p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 4, 1);	else	SET_POLARITY(SysPara.m_polary[4], 4, 0);
		if (ui->checkEm4X06p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 5, 1);	else	SET_POLARITY(SysPara.m_polary[4], 5, 0);
		if (ui->checkEm4X07p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 6, 1);	else	SET_POLARITY(SysPara.m_polary[4], 6, 0);
		if (ui->checkEm4X08p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 7, 1);	else	SET_POLARITY(SysPara.m_polary[4], 7, 0);
		if (ui->checkEm4X09p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 8, 1);	else	SET_POLARITY(SysPara.m_polary[4], 8, 0);
		if (ui->checkEm4X10p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 9, 1);	else	SET_POLARITY(SysPara.m_polary[4], 9, 0);
		if (ui->checkEm4X11p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 10, 1);	else	SET_POLARITY(SysPara.m_polary[4], 10, 0);
		if (ui->checkEm4X12p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 11, 1);	else	SET_POLARITY(SysPara.m_polary[4], 11, 0);
		if (ui->checkEm4X13p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 12, 1);	else	SET_POLARITY(SysPara.m_polary[4], 12, 0);
        if (ui->checkEm4X14p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 13, 1);	else	SET_POLARITY(SysPara.m_polary[4], 13, 0);
        if (ui->checkEm4X15p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 14, 1);	else	SET_POLARITY(SysPara.m_polary[4], 14, 0);
        if (ui->checkEm4X16p->isChecked())	SET_POLARITY(SysPara.m_polary[4], 15, 1);	else	SET_POLARITY(SysPara.m_polary[4], 15, 0);
        // 主控模块报警
        if (ui->checkMainX00i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 0, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 0, 0);
        if (ui->checkMainX01i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 1, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 1, 0);
        if (ui->checkMainX02i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 2, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 2, 0);
        if (ui->checkMainX03i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 3, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 3, 0);
        if (ui->checkMainX04i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 4, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 4, 0);
        if (ui->checkMainX05i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 5, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 5, 0);
        if (ui->checkMainX06i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 6, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 6, 0);
        if (ui->checkMainX07i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 7, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 7, 0);
        if (ui->checkMainX08i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 8, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 8, 0);
        if (ui->checkMainX09i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 9, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 9, 0);
        if (ui->checkMainX10i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 10, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 10, 0);
        if (ui->checkMainX11i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 11, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 11, 0);
        if (ui->checkMainX12i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 12, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 12, 0);
        if (ui->checkMainX13i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 13, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 13, 0);
        if (ui->checkMainX14i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 14, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 14, 0);
        if (ui->checkMainX15i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 15, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 15, 0);
        if (ui->checkMainX16i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 16, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 16, 0);
        if (ui->checkMainX17i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 17, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 17, 0);
        if (ui->checkMainX18i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 18, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 18, 0);
        if (ui->checkMainX19i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 19, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 19, 0);
        if (ui->checkMainX20i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 20, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 20, 0);
        if (ui->checkMainX21i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 21, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 21, 0);
        if (ui->checkMainX22i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 22, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 22, 0);
        if (ui->checkMainX23i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 23, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 23, 0);
        if (ui->checkMainX24i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 24, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 24, 0);
        if (ui->checkMainX25i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 25, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 25, 0);
        if (ui->checkMainX26i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 26, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 26, 0);
        if (ui->checkMainX27i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 27, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 27, 0);
        if (ui->checkMainX28i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 28, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 28, 0);
        if (ui->checkMainX29i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 29, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 29, 0);
        if (ui->checkMainX30i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 30, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 30, 0);
        if (ui->checkMainX31i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], 31, 1);		else	SET_IGNORE(SysPara.m_ignore[0], 31, 0);
        if (ui->checkMainX32i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)32, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)32, (uint64_t)0);
        if (ui->checkMainX33i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)33, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)33, (uint64_t)0);
        if (ui->checkMainX34i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)34, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)34, (uint64_t)0);
        if (ui->checkMainX35i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)35, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)35, (uint64_t)0);
        if (ui->checkMainX36i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)36, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)36, (uint64_t)0);
        if (ui->checkMainX37i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)37, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)37, (uint64_t)0);
        if (ui->checkMainX38i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)38, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)38, (uint64_t)0);
        if (ui->checkMainX39i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)39, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)39, (uint64_t)0);
        if (ui->checkMainX40i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)40, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)40, (uint64_t)0);
        if (ui->checkMainX41i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)41, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)41, (uint64_t)0);
        if (ui->checkMainX42i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)42, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)42, (uint64_t)0);
        if (ui->checkMainX43i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)43, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)43, (uint64_t)0);
        if (ui->checkMainX44i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)44, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)44, (uint64_t)0);
        if (ui->checkMainX45i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)45, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)45, (uint64_t)0);
        if (ui->checkMainX46i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)46, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)46, (uint64_t)0);
        if (ui->checkMainX47i->isChecked())	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)47, (uint64_t)1);		else	SET_IGNORE(SysPara.m_ignore[0], (uint64_t)47, (uint64_t)0);
        // 扩展模块1报警
        if (ui->checkEm1X01i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 0, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 0, 0);
        if (ui->checkEm1X02i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 1, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 1, 0);
		if (ui->checkEm1X03i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 2, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 2, 0);
		if (ui->checkEm1X04i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 3, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 3, 0);
		if (ui->checkEm1X05i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 4, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 4, 0);
		if (ui->checkEm1X06i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 5, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 5, 0);
		if (ui->checkEm1X07i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 6, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 6, 0);
		if (ui->checkEm1X08i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 7, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 7, 0);
		if (ui->checkEm1X09i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 8, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 8, 0);
		if (ui->checkEm1X10i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 9, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 9, 0);
		if (ui->checkEm1X11i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 10, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 10, 0);
		if (ui->checkEm1X12i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 11, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 11, 0);
		if (ui->checkEm1X13i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 12, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 12, 0);
        if (ui->checkEm1X14i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 13, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 13, 0);
        if (ui->checkEm1X15i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 14, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 14, 0);
        if (ui->checkEm1X16i->isChecked())	SET_IGNORE(SysPara.m_ignore[1], 15, 1);		else	SET_IGNORE(SysPara.m_ignore[1], 15, 0);
        // 扩展模块2报警
		if (ui->checkEm2X01i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 0, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 0, 0);
		if (ui->checkEm2X02i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 1, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 1, 0);
		if (ui->checkEm2X03i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 2, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 2, 0);
		if (ui->checkEm2X04i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 3, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 3, 0);
		if (ui->checkEm2X05i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 4, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 4, 0);
		if (ui->checkEm2X06i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 5, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 5, 0);
		if (ui->checkEm2X07i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 6, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 6, 0);
		if (ui->checkEm2X08i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 7, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 7, 0);
		if (ui->checkEm2X09i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 8, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 8, 0);
		if (ui->checkEm2X10i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 9, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 9, 0);
		if (ui->checkEm2X11i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 10, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 10, 0);
		if (ui->checkEm2X12i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 11, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 11, 0);
		if (ui->checkEm2X13i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 12, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 12, 0);
        if (ui->checkEm2X14i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 13, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 13, 0);
        if (ui->checkEm2X15i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 14, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 14, 0);
        if (ui->checkEm2X16i->isChecked())	SET_IGNORE(SysPara.m_ignore[2], 15, 1);		else	SET_IGNORE(SysPara.m_ignore[2], 15, 0);
        // 扩展模块3报警
		if (ui->checkEm3X01i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 0, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 0, 0);
		if (ui->checkEm3X02i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 1, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 1, 0);
		if (ui->checkEm3X03i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 2, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 2, 0);
		if (ui->checkEm3X04i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 3, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 3, 0);
		if (ui->checkEm3X05i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 4, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 4, 0);
		if (ui->checkEm3X06i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 5, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 5, 0);
		if (ui->checkEm3X07i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 6, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 6, 0);
		if (ui->checkEm3X08i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 7, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 7, 0);
		if (ui->checkEm3X09i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 8, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 8, 0);
		if (ui->checkEm3X10i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 9, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 9, 0);
		if (ui->checkEm3X11i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 10, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 10, 0);
		if (ui->checkEm3X12i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 11, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 11, 0);
		if (ui->checkEm3X13i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 12, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 12, 0);
        if (ui->checkEm3X14i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 13, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 13, 0);
        if (ui->checkEm3X15i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 14, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 14, 0);
        if (ui->checkEm3X16i->isChecked())	SET_IGNORE(SysPara.m_ignore[3], 15, 1);		else	SET_IGNORE(SysPara.m_ignore[3], 15, 0);
        // 扩展模块4报警
		if (ui->checkEm4X01i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 0, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 0, 0);
		if (ui->checkEm4X02i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 1, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 1, 0);
		if (ui->checkEm4X03i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 2, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 2, 0);
		if (ui->checkEm4X04i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 3, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 3, 0);
		if (ui->checkEm4X05i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 4, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 4, 0);
		if (ui->checkEm4X06i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 5, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 5, 0);
		if (ui->checkEm4X07i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 6, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 6, 0);
		if (ui->checkEm4X08i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 7, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 7, 0);
		if (ui->checkEm4X09i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 8, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 8, 0);
		if (ui->checkEm4X10i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 9, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 9, 0);
		if (ui->checkEm4X11i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 10, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 10, 0);
		if (ui->checkEm4X12i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 11, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 11, 0);
		if (ui->checkEm4X13i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 12, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 12, 0);
        if (ui->checkEm4X14i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 13, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 13, 0);
        if (ui->checkEm4X15i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 14, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 14, 0);
        if (ui->checkEm4X16i->isChecked())	SET_IGNORE(SysPara.m_ignore[4], 15, 1);		else	SET_IGNORE(SysPara.m_ignore[4], 15, 0);
        // 主控模块模内不报警
        if (ui->checkMainX00a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 0, 1);		else	SET_NOALM(SysPara.m_noalm[0], 0, 0);
        if (ui->checkMainX01a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 1, 1);		else	SET_NOALM(SysPara.m_noalm[0], 1, 0);
        if (ui->checkMainX02a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 2, 1);		else	SET_NOALM(SysPara.m_noalm[0], 2, 0);
        if (ui->checkMainX03a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 3, 1);		else	SET_NOALM(SysPara.m_noalm[0], 3, 0);
        if (ui->checkMainX04a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 4, 1);		else	SET_NOALM(SysPara.m_noalm[0], 4, 0);
        if (ui->checkMainX05a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 5, 1);		else	SET_NOALM(SysPara.m_noalm[0], 5, 0);
        if (ui->checkMainX06a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 6, 1);		else	SET_NOALM(SysPara.m_noalm[0], 6, 0);
        if (ui->checkMainX07a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 7, 1);		else	SET_NOALM(SysPara.m_noalm[0], 7, 0);
        if (ui->checkMainX08a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 8, 1);		else	SET_NOALM(SysPara.m_noalm[0], 8, 0);
        if (ui->checkMainX09a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 9, 1);		else	SET_NOALM(SysPara.m_noalm[0], 9, 0);
        if (ui->checkMainX10a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 10, 1);		else	SET_NOALM(SysPara.m_noalm[0], 10, 0);
        if (ui->checkMainX11a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 11, 1);		else	SET_NOALM(SysPara.m_noalm[0], 11, 0);
        if (ui->checkMainX12a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 12, 1);		else	SET_NOALM(SysPara.m_noalm[0], 12, 0);
        if (ui->checkMainX13a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 13, 1);		else	SET_NOALM(SysPara.m_noalm[0], 13, 0);
        if (ui->checkMainX14a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 14, 1);		else	SET_NOALM(SysPara.m_noalm[0], 14, 0);
        if (ui->checkMainX15a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 15, 1);		else	SET_NOALM(SysPara.m_noalm[0], 15, 0);
        if (ui->checkMainX16a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 16, 1);		else	SET_NOALM(SysPara.m_noalm[0], 16, 0);
        if (ui->checkMainX17a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 17, 1);		else	SET_NOALM(SysPara.m_noalm[0], 17, 0);
        if (ui->checkMainX18a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 18, 1);		else	SET_NOALM(SysPara.m_noalm[0], 18, 0);
        if (ui->checkMainX19a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 19, 1);		else	SET_NOALM(SysPara.m_noalm[0], 19, 0);
        if (ui->checkMainX20a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 20, 1);		else	SET_NOALM(SysPara.m_noalm[0], 20, 0);
        if (ui->checkMainX21a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 21, 1);		else	SET_NOALM(SysPara.m_noalm[0], 21, 0);
        if (ui->checkMainX22a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 22, 1);		else	SET_NOALM(SysPara.m_noalm[0], 22, 0);
        if (ui->checkMainX23a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 23, 1);		else	SET_NOALM(SysPara.m_noalm[0], 23, 0);
        if (ui->checkMainX24a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 24, 1);		else	SET_NOALM(SysPara.m_noalm[0], 24, 0);
        if (ui->checkMainX25a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 25, 1);		else	SET_NOALM(SysPara.m_noalm[0], 25, 0);
        if (ui->checkMainX26a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 26, 1);		else	SET_NOALM(SysPara.m_noalm[0], 26, 0);
        if (ui->checkMainX27a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 27, 1);		else	SET_NOALM(SysPara.m_noalm[0], 27, 0);
        if (ui->checkMainX28a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 28, 1);		else	SET_NOALM(SysPara.m_noalm[0], 28, 0);
        if (ui->checkMainX29a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 29, 1);		else	SET_NOALM(SysPara.m_noalm[0], 29, 0);
        if (ui->checkMainX30a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 30, 1);		else	SET_NOALM(SysPara.m_noalm[0], 30, 0);
        if (ui->checkMainX31a->isChecked())	SET_NOALM(SysPara.m_noalm[0], 31, 1);		else	SET_NOALM(SysPara.m_noalm[0], 31, 0);
        if (ui->checkMainX32a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)32, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)32, (uint64_t)0);
        if (ui->checkMainX33a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)33, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)33, (uint64_t)0);
        if (ui->checkMainX34a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)34, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)34, (uint64_t)0);
        if (ui->checkMainX35a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)35, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)35, (uint64_t)0);
        if (ui->checkMainX36a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)36, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)36, (uint64_t)0);
        if (ui->checkMainX37a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)37, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)37, (uint64_t)0);
        if (ui->checkMainX38a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)38, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)38, (uint64_t)0);
        if (ui->checkMainX39a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)39, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)39, (uint64_t)0);
        if (ui->checkMainX40a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)40, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)40, (uint64_t)0);
        if (ui->checkMainX41a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)41, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)41, (uint64_t)0);
        if (ui->checkMainX42a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)42, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)42, (uint64_t)0);
        if (ui->checkMainX43a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)43, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)43, (uint64_t)0);
        if (ui->checkMainX44a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)44, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)44, (uint64_t)0);
        if (ui->checkMainX45a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)45, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)45, (uint64_t)0);
        if (ui->checkMainX46a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)46, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)46, (uint64_t)0);
        if (ui->checkMainX47a->isChecked())	SET_NOALM(SysPara.m_noalm[0], (uint64_t)47, (uint64_t)1);		else	SET_NOALM(SysPara.m_noalm[0], (uint64_t)47, (uint64_t)0);
        // 扩展模块1模内不报警
        if (ui->checkEm1X01a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 0, 1);		else	SET_NOALM(SysPara.m_noalm[1], 0, 0);
        if (ui->checkEm1X02a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 1, 1);		else	SET_NOALM(SysPara.m_noalm[1], 1, 0);
		if (ui->checkEm1X03a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 2, 1);		else	SET_NOALM(SysPara.m_noalm[1], 2, 0);
		if (ui->checkEm1X04a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 3, 1);		else	SET_NOALM(SysPara.m_noalm[1], 3, 0);
		if (ui->checkEm1X05a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 4, 1);		else	SET_NOALM(SysPara.m_noalm[1], 4, 0);
		if (ui->checkEm1X06a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 5, 1);		else	SET_NOALM(SysPara.m_noalm[1], 5, 0);
		if (ui->checkEm1X07a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 6, 1);		else	SET_NOALM(SysPara.m_noalm[1], 6, 0);
		if (ui->checkEm1X08a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 7, 1);		else	SET_NOALM(SysPara.m_noalm[1], 7, 0);
		if (ui->checkEm1X09a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 8, 1);		else	SET_NOALM(SysPara.m_noalm[1], 8, 0);
		if (ui->checkEm1X10a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 9, 1);		else	SET_NOALM(SysPara.m_noalm[1], 9, 0);
		if (ui->checkEm1X11a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 10, 1);		else	SET_NOALM(SysPara.m_noalm[1], 10, 0);
		if (ui->checkEm1X12a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 11, 1);		else	SET_NOALM(SysPara.m_noalm[1], 11, 0);
		if (ui->checkEm1X13a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 12, 1);		else	SET_NOALM(SysPara.m_noalm[1], 12, 0);
        if (ui->checkEm1X14a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 13, 1);		else	SET_NOALM(SysPara.m_noalm[1], 13, 0);
        if (ui->checkEm1X15a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 14, 1);		else	SET_NOALM(SysPara.m_noalm[1], 14, 0);
        if (ui->checkEm1X16a->isChecked())	SET_NOALM(SysPara.m_noalm[1], 15, 1);		else	SET_NOALM(SysPara.m_noalm[1], 15, 0);
        // 扩展模块2模内不报警
		if (ui->checkEm2X01a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 0, 1);		else	SET_NOALM(SysPara.m_noalm[2], 0, 0);
		if (ui->checkEm2X02a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 1, 1);		else	SET_NOALM(SysPara.m_noalm[2], 1, 0);
		if (ui->checkEm2X03a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 2, 1);		else	SET_NOALM(SysPara.m_noalm[2], 2, 0);
		if (ui->checkEm2X04a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 3, 1);		else	SET_NOALM(SysPara.m_noalm[2], 3, 0);
		if (ui->checkEm2X05a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 4, 1);		else	SET_NOALM(SysPara.m_noalm[2], 4, 0);
		if (ui->checkEm2X06a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 5, 1);		else	SET_NOALM(SysPara.m_noalm[2], 5, 0);
		if (ui->checkEm2X07a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 6, 1);		else	SET_NOALM(SysPara.m_noalm[2], 6, 0);
		if (ui->checkEm2X08a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 7, 1);		else	SET_NOALM(SysPara.m_noalm[2], 7, 0);
		if (ui->checkEm2X09a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 8, 1);		else	SET_NOALM(SysPara.m_noalm[2], 8, 0);
		if (ui->checkEm2X10a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 9, 1);		else	SET_NOALM(SysPara.m_noalm[2], 9, 0);
		if (ui->checkEm2X11a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 10, 1);		else	SET_NOALM(SysPara.m_noalm[2], 10, 0);
		if (ui->checkEm2X12a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 11, 1);		else	SET_NOALM(SysPara.m_noalm[2], 11, 0);
		if (ui->checkEm2X13a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 12, 1);		else	SET_NOALM(SysPara.m_noalm[2], 12, 0);
        if (ui->checkEm2X14a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 13, 1);		else	SET_NOALM(SysPara.m_noalm[2], 13, 0);
        if (ui->checkEm2X15a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 14, 1);		else	SET_NOALM(SysPara.m_noalm[2], 14, 0);
        if (ui->checkEm2X16a->isChecked())	SET_NOALM(SysPara.m_noalm[2], 15, 1);		else	SET_NOALM(SysPara.m_noalm[2], 15, 0);
        // 扩展模块3模内不报警
		if (ui->checkEm3X01a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 0, 1);		else	SET_NOALM(SysPara.m_noalm[3], 0, 0);
		if (ui->checkEm3X02a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 1, 1);		else	SET_NOALM(SysPara.m_noalm[3], 1, 0);
		if (ui->checkEm3X03a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 2, 1);		else	SET_NOALM(SysPara.m_noalm[3], 2, 0);
		if (ui->checkEm3X04a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 3, 1);		else	SET_NOALM(SysPara.m_noalm[3], 3, 0);
		if (ui->checkEm3X05a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 4, 1);		else	SET_NOALM(SysPara.m_noalm[3], 4, 0);
		if (ui->checkEm3X06a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 5, 1);		else	SET_NOALM(SysPara.m_noalm[3], 5, 0);
		if (ui->checkEm3X07a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 6, 1);		else	SET_NOALM(SysPara.m_noalm[3], 6, 0);
		if (ui->checkEm3X08a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 7, 1);		else	SET_NOALM(SysPara.m_noalm[3], 7, 0);
		if (ui->checkEm3X09a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 8, 1);		else	SET_NOALM(SysPara.m_noalm[3], 8, 0);
		if (ui->checkEm3X10a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 9, 1);		else	SET_NOALM(SysPara.m_noalm[3], 9, 0);
		if (ui->checkEm3X11a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 10, 1);		else	SET_NOALM(SysPara.m_noalm[3], 10, 0);
		if (ui->checkEm3X12a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 11, 1);		else	SET_NOALM(SysPara.m_noalm[3], 11, 0);
		if (ui->checkEm3X13a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 12, 1);		else	SET_NOALM(SysPara.m_noalm[3], 12, 0);
        if (ui->checkEm3X14a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 13, 1);		else	SET_NOALM(SysPara.m_noalm[3], 13, 0);
        if (ui->checkEm3X15a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 14, 1);		else	SET_NOALM(SysPara.m_noalm[3], 14, 0);
        if (ui->checkEm3X16a->isChecked())	SET_NOALM(SysPara.m_noalm[3], 15, 1);		else	SET_NOALM(SysPara.m_noalm[3], 15, 0);
        // 扩展模块4模内不报警
		if (ui->checkEm4X01a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 0, 1);		else	SET_NOALM(SysPara.m_noalm[4], 0, 0);
		if (ui->checkEm4X02a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 1, 1);		else	SET_NOALM(SysPara.m_noalm[4], 1, 0);
		if (ui->checkEm4X03a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 2, 1);		else	SET_NOALM(SysPara.m_noalm[4], 2, 0);
		if (ui->checkEm4X04a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 3, 1);		else	SET_NOALM(SysPara.m_noalm[4], 3, 0);
		if (ui->checkEm4X05a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 4, 1);		else	SET_NOALM(SysPara.m_noalm[4], 4, 0);
		if (ui->checkEm4X06a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 5, 1);		else	SET_NOALM(SysPara.m_noalm[4], 5, 0);
		if (ui->checkEm4X07a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 6, 1);		else	SET_NOALM(SysPara.m_noalm[4], 6, 0);
		if (ui->checkEm4X08a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 7, 1);		else	SET_NOALM(SysPara.m_noalm[4], 7, 0);
		if (ui->checkEm4X09a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 8, 1);		else	SET_NOALM(SysPara.m_noalm[4], 8, 0);
		if (ui->checkEm4X10a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 9, 1);		else	SET_NOALM(SysPara.m_noalm[4], 9, 0);
		if (ui->checkEm4X11a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 10, 1);		else	SET_NOALM(SysPara.m_noalm[4], 10, 0);
		if (ui->checkEm4X12a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 11, 1);		else	SET_NOALM(SysPara.m_noalm[4], 11, 0);
		if (ui->checkEm4X13a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 12, 1);		else	SET_NOALM(SysPara.m_noalm[4], 12, 0);
        if (ui->checkEm4X14a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 13, 1);		else	SET_NOALM(SysPara.m_noalm[4], 13, 0);
        if (ui->checkEm4X15a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 14, 1);		else	SET_NOALM(SysPara.m_noalm[4], 14, 0);
        if (ui->checkEm4X16a->isChecked())	SET_NOALM(SysPara.m_noalm[4], 15, 1);		else	SET_NOALM(SysPara.m_noalm[4], 15, 0);

        // 主控模块输出极性
        if (ui->checkMainY00p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 0, 1);   else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 0, 0);
        if (ui->checkMainY01p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 1, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 1, 0);
        if (ui->checkMainY02p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 2, 1);   else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 2, 0);
        if (ui->checkMainY03p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 3, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 3, 0);
        if (ui->checkMainY04p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 4, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 4, 0);
        if (ui->checkMainY05p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 5, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 5, 0);
        if (ui->checkMainY06p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 6, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 6, 0);
        if (ui->checkMainY07p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 7, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 7, 0);
        if (ui->checkMainY08p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 8, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 8, 0);
        if (ui->checkMainY09p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 9, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 9, 0);
        if (ui->checkMainY10p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 10, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 10, 0);
        if (ui->checkMainY11p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 11, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 11, 0);
        if (ui->checkMainY12p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 12, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 12, 0);
        if (ui->checkMainY13p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 13, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 13, 0);
        if (ui->checkMainY14p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 14, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 14, 0);
        if (ui->checkMainY15p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 15, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 15, 0);
        if (ui->checkMainY16p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 16, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 16, 0);
        if (ui->checkMainY17p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 17, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 17, 0);
        if (ui->checkMainY18p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 18, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 18, 0);
        if (ui->checkMainY19p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 19, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 19, 0);
        if (ui->checkMainY20p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 20, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 20, 0);
        if (ui->checkMainY21p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 21, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 21, 0);
        if (ui->checkMainY22p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 22, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 22, 0);
        if (ui->checkMainY23p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 23, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 23, 0);
        if (ui->checkMainY24p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 24, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 24, 0);
        if (ui->checkMainY25p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 25, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 25, 0);
        if (ui->checkMainY26p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 26, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 26, 0);
        if (ui->checkMainY27p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 27, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 27, 0);
        if (ui->checkMainY28p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 28, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 28, 0);
        if (ui->checkMainY29p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 29, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 29, 0);
        if (ui->checkMainY30p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 30, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 30, 0);
        if (ui->checkMainY31p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 31, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], 31, 0);
        if (ui->checkMainY32p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)32, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)32, (uint64_t)0);
        if (ui->checkMainY33p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)33, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)33, (uint64_t)0);
        if (ui->checkMainY34p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)34, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)34, (uint64_t)0);
        if (ui->checkMainY35p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)35, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)35, (uint64_t)0);
        if (ui->checkMainY36p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)36, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)36, (uint64_t)0);
        if (ui->checkMainY37p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)37, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)37, (uint64_t)0);
        if (ui->checkMainY38p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)38, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)38, (uint64_t)0);
        if (ui->checkMainY39p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)39, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)39, (uint64_t)0);
        if (ui->checkMainY40p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)40, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)40, (uint64_t)0);
        if (ui->checkMainY41p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)41, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)41, (uint64_t)0);
        if (ui->checkMainY42p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)42, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)42, (uint64_t)0);
        if (ui->checkMainY43p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)43, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)43, (uint64_t)0);
        if (ui->checkMainY44p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)44, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)44, (uint64_t)0);
        if (ui->checkMainY45p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)45, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)45, (uint64_t)0);
        if (ui->checkMainY46p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)46, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)46, (uint64_t)0);
        if (ui->checkMainY47p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)47, (uint64_t)1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[0], (uint64_t)47, (uint64_t)0);
        // 扩展模块1输出极性
        if (ui->checkEm1Y01p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 0, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 0, 0);
        if (ui->checkEm1Y02p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 1, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 1, 0);
        if (ui->checkEm1Y03p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 2, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 2, 0);
        if (ui->checkEm1Y04p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 3, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 3, 0);
        if (ui->checkEm1Y05p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 4, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 4, 0);
        if (ui->checkEm1Y06p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 5, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 5, 0);
        if (ui->checkEm1Y07p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 6, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 6, 0);
        if (ui->checkEm1Y08p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 7, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 7, 0);
        if (ui->checkEm1Y09p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 8, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 8, 0);
        if (ui->checkEm1Y10p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 9, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 9, 0);
        if (ui->checkEm1Y11p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 10, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 10, 0);
        if (ui->checkEm1Y12p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 11, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 11, 0);
        if (ui->checkEm1Y13p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 12, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 12, 0);
        if (ui->checkEm1Y14p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 13, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 13, 0);
        if (ui->checkEm1Y15p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 14, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 14, 0);
        if (ui->checkEm1Y16p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 15, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[1], 15, 0);
        // 扩展模块2输出极性
        if (ui->checkEm2Y01p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 0, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 0, 0);
        if (ui->checkEm2Y02p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 1, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 1, 0);
        if (ui->checkEm2Y03p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 2, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 2, 0);
        if (ui->checkEm2Y04p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 3, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 3, 0);
        if (ui->checkEm2Y05p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 4, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 4, 0);
        if (ui->checkEm2Y06p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 5, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 5, 0);
        if (ui->checkEm2Y07p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 6, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 6, 0);
        if (ui->checkEm2Y08p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 7, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 7, 0);
        if (ui->checkEm2Y09p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 8, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 8, 0);
        if (ui->checkEm2Y10p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 9, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 9, 0);
        if (ui->checkEm2Y11p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 10, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 10, 0);
        if (ui->checkEm2Y12p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 11, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 11, 0);
        if (ui->checkEm2Y13p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 12, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 12, 0);
        if (ui->checkEm2Y14p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 13, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 13, 0);
        if (ui->checkEm2Y15p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 14, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 14, 0);
        if (ui->checkEm2Y16p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 15, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[2], 15, 0);
        // 扩展模块3输出极性
        if (ui->checkEm3Y01p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 0, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 0, 0);
        if (ui->checkEm3Y02p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 1, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 1, 0);
        if (ui->checkEm3Y03p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 2, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 2, 0);
        if (ui->checkEm3Y04p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 3, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 3, 0);
        if (ui->checkEm3Y05p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 4, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 4, 0);
        if (ui->checkEm3Y06p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 5, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 5, 0);
        if (ui->checkEm3Y07p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 6, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 6, 0);
        if (ui->checkEm3Y08p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 7, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 7, 0);
        if (ui->checkEm3Y09p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 8, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 8, 0);
        if (ui->checkEm3Y10p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 9, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 9, 0);
        if (ui->checkEm3Y11p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 10, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 10, 0);
        if (ui->checkEm3Y12p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 11, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 11, 0);
        if (ui->checkEm3Y13p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 12, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 12, 0);
        if (ui->checkEm3Y14p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 13, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 13, 0);
        if (ui->checkEm3Y15p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 14, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 14, 0);
        if (ui->checkEm3Y16p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 15, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[3], 15, 0);
        // 扩展模块4输出极性
        if (ui->checkEm4Y01p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 0, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 0, 0);
        if (ui->checkEm4Y02p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 1, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 1, 0);
        if (ui->checkEm4Y03p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 2, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 2, 0);
        if (ui->checkEm4Y04p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 3, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 3, 0);
        if (ui->checkEm4Y05p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 4, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 4, 0);
        if (ui->checkEm4Y06p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 5, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 5, 0);
        if (ui->checkEm4Y07p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 6, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 6, 0);
        if (ui->checkEm4Y08p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 7, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 7, 0);
        if (ui->checkEm4Y09p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 8, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 8, 0);
        if (ui->checkEm4Y10p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 9, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 9, 0);
        if (ui->checkEm4Y11p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 10, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 10, 0);
        if (ui->checkEm4Y12p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 11, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 11, 0);
        if (ui->checkEm4Y13p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 12, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 12, 0);
        if (ui->checkEm4Y14p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 13, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 13, 0);
        if (ui->checkEm4Y15p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 14, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 14, 0);
        if (ui->checkEm4Y16p->isChecked())	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 15, 1);	else	SET_OUTPOLARITY(SysPara.m_outputpolary[4], 15, 0);
    }
}

// 检查参数是否修改
bool FormIO::isModified(void)
{
	parModify = 0;
	if (xPermissions::GetPermissions(PER_SYS_SIGNAL) == true)
	{
		// 主控模块信号极性
		if (SysPara.m_polary[0] != SysParaBak.m_polary[0])							parModify |= ((quint64)1 << LOG_MAIN_POLARY);
		// 扩展模块1信号极性
		if (SysPara.m_polary[1] != SysParaBak.m_polary[1])							parModify |= ((quint64)1 << LOG_EXT1_POLARY);
		// 扩展模块2信号极性
		if (SysPara.m_polary[2] != SysParaBak.m_polary[2])							parModify |= ((quint64)1 << LOG_EXT2_POLARY);
		// 扩展模块3信号极性
		if (SysPara.m_polary[3] != SysParaBak.m_polary[3])							parModify |= ((quint64)1 << LOG_EXT3_POLARY);
        // 扩展模块4信号极性
		if (SysPara.m_polary[4] != SysParaBak.m_polary[4])							parModify |= ((quint64)1 << LOG_EXT4_POLARY);
		// 主控模块信号报警
		if (SysPara.m_ignore[0] != SysParaBak.m_ignore[0])							parModify |= ((quint64)1 << LOG_MAIN_IGNORE);
		// 扩展模块1信号报警
		if (SysPara.m_ignore[1] != SysParaBak.m_ignore[1])							parModify |= ((quint64)1 << LOG_EXT1_IGNORE);
		// 扩展模块2信号报警
		if (SysPara.m_ignore[2] != SysParaBak.m_ignore[2])							parModify |= ((quint64)1 << LOG_EXT2_IGNORE);
		// 扩展模块3信号报警
		if (SysPara.m_ignore[3] != SysParaBak.m_ignore[3])							parModify |= ((quint64)1 << LOG_EXT3_IGNORE);
		// 扩展模块4信号报警
		if (SysPara.m_ignore[4] != SysParaBak.m_ignore[4])							parModify |= ((quint64)1 << LOG_EXT4_IGNORE);
		// 主控模块模内不报警
		if (SysPara.m_noalm[0] != SysParaBak.m_noalm[0])							parModify |= ((quint64)1 << LOG_MAIN_NOALM);
		// 扩展模块1模内不报警
		if (SysPara.m_noalm[1] != SysParaBak.m_noalm[1])							parModify |= ((quint64)1 << LOG_EXT1_NOALM);
		// 扩展模块2模内不报警
		if (SysPara.m_noalm[2] != SysParaBak.m_noalm[2])							parModify |= ((quint64)1 << LOG_EXT2_NOALM);
		// 扩展模块3模内不报警
		if (SysPara.m_noalm[3] != SysParaBak.m_noalm[3])							parModify |= ((quint64)1 << LOG_EXT3_NOALM);
		// 扩展模块4模内不报警
		if (SysPara.m_noalm[4] != SysParaBak.m_noalm[4])							parModify |= ((quint64)1 << LOG_EXT4_NOALM);
         // 主控模块输出信号极性
        if (SysPara.m_outputpolary[0] != SysParaBak.m_outputpolary[0])				parModify |= ((quint64)1 << LOG_MAIN_OUTPOLARY);
        // 扩展模块1信号极性
        if (SysPara.m_outputpolary[1] != SysParaBak.m_outputpolary[1])				parModify |= ((quint64)1 << LOG_EXT1_OUTPOLARY);
        // 扩展模块2信号极性
        if (SysPara.m_outputpolary[2] != SysParaBak.m_outputpolary[2])				parModify |= ((quint64)1 << LOG_EXT2_OUTPOLARY);
        // 扩展模块3信号极性
        if (SysPara.m_outputpolary[3] != SysParaBak.m_outputpolary[3])				parModify |= ((quint64)1 << LOG_EXT3_OUTPOLARY);
        // 扩展模块4信号极性
        if (SysPara.m_outputpolary[4] != SysParaBak.m_outputpolary[4])				parModify |= ((quint64)1 << LOG_EXT4_OUTPOLARY);
    }
	if (parModify == 0)
		return false;
	else
		return true;
}
// 检查参数合法性
bool FormIO::CheckValid(void)
{
	return true;
}
// 保存系统参数设置
bool FormIO::SavePara(void)
{
	try
	{
		if (pModbus->WriteSystem(SysPara, parModify))
			throw false;
		if (pModbus->CommandWrite(CMD_WRITE_SYSTEM))
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
void FormIO::changeEvent(QEvent *e)
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
// 设置当前模块端口标题
void FormIO::setPortLabel(void)
{
    switch (ui->stackedWidgetPolary->currentIndex())
    {
    case 0:
        ui->labelPolarity->setText(tr("[1/5] 主控模块输入信号反相"));;
        break;
    case 1:
        ui->labelPolarity->setText(tr("[2/5] 扩展模块1输入信号反相"));;
        break;
    case 2:
        ui->labelPolarity->setText(tr("[3/5] 扩展模块2输入信号反相"));;
        break;
    case 3:
        ui->labelPolarity->setText(tr("[4/5] 扩展模块3输入信号反相"));;
        break;
    case 4:
        ui->labelPolarity->setText(tr("[5/5] 扩展模块4输入信号反相"));;
        break;
    }
        switch (ui->stackedWidgetOutput->currentIndex())
        {
        case 0:
            ui->labelOutput->setText(tr("[1/5] 主控模块输出信号反相"));;
            break;
        case 1:
            ui->labelOutput->setText(tr("[2/5] 扩展模块1输出信号反相"));;
            break;
        case 2:
            ui->labelOutput->setText(tr("[3/5] 扩展模块2输出信号反相"));;
            break;
        case 3:
            ui->labelOutput->setText(tr("[4/5] 扩展模块3输出信号反相"));;
            break;
        case 4:
            ui->labelOutput->setText(tr("[5/5] 扩展模块4输出信号反相"));;
            break;
        }
        switch (ui->stackedWidgetIgnore->currentIndex())
        {
        case 0:
            ui->labelIgnore->setText(tr("[1/5] 主控模块输入报警允许忽略"));;
            break;
        case 1:
            ui->labelIgnore->setText(tr("[2/5] 扩展模块1输入报警允许忽略"));;
            break;
        case 2:
            ui->labelIgnore->setText(tr("[3/5] 扩展模块2输入报警允许忽略"));;
            break;
        case 3:
            ui->labelIgnore->setText(tr("[4/5] 扩展模块3输入报警允许忽略"));;
            break;
        case 4:
            ui->labelIgnore->setText(tr("[5/5] 扩展模块4输入报警允许忽略"));;
            break;
        }
        switch (ui->stackedWidgetNoalm->currentIndex())
        {
        case 0:
            ui->labelNoalm->setText(tr("[1/5] 主控模块模内不报警"));;
            break;
        case 1:
            ui->labelNoalm->setText(tr("[2/5] 扩展模块1模内不报警"));;
            break;
        case 2:
            ui->labelNoalm->setText(tr("[3/5] 扩展模块2模内不报警"));;
            break;
        case 3:
            ui->labelNoalm->setText(tr("[4/5] 扩展模块3模内不报警"));;
            break;
        case 4:
            ui->labelNoalm->setText(tr("[5/5] 扩展模块4模内不报警"));;
            break;
        }
}
void FormIO::setPortvisible(void)
{
    ui->checkMainY00p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y00));  ui->checkMainX00p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X00));  ui->checkMainX00i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X00));  ui->checkMainX00a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X00));
    ui->checkMainY01p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y01));  ui->checkMainX01p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X01));  ui->checkMainX01i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X01));  ui->checkMainX01a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X01));
    ui->checkMainY02p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y02));  ui->checkMainX02p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X02));  ui->checkMainX02i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X02));  ui->checkMainX02a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X02));
    ui->checkMainY03p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y03));  ui->checkMainX03p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X03));  ui->checkMainX03i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X03));  ui->checkMainX03a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X03));
    ui->checkMainY04p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y04));  ui->checkMainX04p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X04));  ui->checkMainX04i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X04));  ui->checkMainX04a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X04));
    ui->checkMainY05p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y05));  ui->checkMainX05p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X05));  ui->checkMainX05i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X05));  ui->checkMainX05a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X05));
    ui->checkMainY06p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y06));  ui->checkMainX06p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X06));  ui->checkMainX06i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X06));  ui->checkMainX06a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X06));
    ui->checkMainY07p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y07));  ui->checkMainX07p->setVisible(true);/*xIoPort::IsVisibleExtIn(MAIN_VAR_X07)*/ui->checkMainX07i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X07));  ui->checkMainX07a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X07));
    ui->checkMainY08p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y08));  ui->checkMainX08p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X08));  ui->checkMainX08i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X08));  ui->checkMainX08a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X08));
    ui->checkMainY09p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y09));  ui->checkMainX09p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X09));  ui->checkMainX09i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X09));  ui->checkMainX09a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X09));
    ui->checkMainY10p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y10));  ui->checkMainX10p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X10));  ui->checkMainX10i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X10));  ui->checkMainX10a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X10));
    ui->checkMainY11p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y11));  ui->checkMainX11p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X11));  ui->checkMainX11i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X11));  ui->checkMainX11a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X11));
    ui->checkMainY12p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y12));  ui->checkMainX12p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X12));  ui->checkMainX12i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X12));  ui->checkMainX12a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X12));
    ui->checkMainY13p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y13));  ui->checkMainX13p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X13));  ui->checkMainX13i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X13));  ui->checkMainX13a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X13));
    ui->checkMainY14p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y14));  ui->checkMainX14p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X14));  ui->checkMainX14i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X14));  ui->checkMainX14a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X14));
    ui->checkMainY15p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y15));  ui->checkMainX15p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X15));  ui->checkMainX15i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X15));  ui->checkMainX15a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X15));
    if(pModbus->GetFunctions(SUB_FUN2_MAIN64_BITS))
    {
        ui->checkMainY16p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y16));  ui->checkMainX16p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X16));  ui->checkMainX16i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X16));  ui->checkMainX16a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X16));
        ui->checkMainY17p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y17));  ui->checkMainX17p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X17));  ui->checkMainX17i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X17));  ui->checkMainX17a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X17));
        ui->checkMainY18p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y18));  ui->checkMainX18p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X18));  ui->checkMainX18i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X18));  ui->checkMainX18a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X18));
        ui->checkMainY19p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y19));  ui->checkMainX19p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X19));  ui->checkMainX19i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X19));  ui->checkMainX19a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X19));
        ui->checkMainY20p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y20));  ui->checkMainX20p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X20));  ui->checkMainX20i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X20));  ui->checkMainX20a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X20));
        ui->checkMainY21p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y21));  ui->checkMainX21p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X21));  ui->checkMainX21i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X21));  ui->checkMainX21a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X21));
        ui->checkMainY22p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y22));  ui->checkMainX22p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X22));  ui->checkMainX22i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X22));  ui->checkMainX22a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X22));
        ui->checkMainY23p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y23));  ui->checkMainX23p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X23));  ui->checkMainX23i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X23));  ui->checkMainX23a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X23));
        ui->checkMainY24p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y24));  ui->checkMainX24p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X24));  ui->checkMainX24i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X24));  ui->checkMainX24a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X24));
        ui->checkMainY25p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y25));  ui->checkMainX25p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X25));  ui->checkMainX25i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X25));  ui->checkMainX25a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X25));
        ui->checkMainY26p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y26));  ui->checkMainX26p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X26));  ui->checkMainX26i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X26));  ui->checkMainX26a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X26));
        ui->checkMainY27p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y27));  ui->checkMainX27p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X27));  ui->checkMainX27i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X27));  ui->checkMainX27a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X27));
        ui->checkMainY28p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y28));  ui->checkMainX28p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X28));  ui->checkMainX28i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X28));  ui->checkMainX28a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X28));
        ui->checkMainY29p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y29));  ui->checkMainX29p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X29));  ui->checkMainX29i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X29));  ui->checkMainX29a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X29));
        ui->checkMainY30p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y30));  ui->checkMainX30p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X30));  ui->checkMainX30i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X30));  ui->checkMainX30a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X30));
        ui->checkMainY31p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y31));  ui->checkMainX31p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X31));  ui->checkMainX31i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X31));  ui->checkMainX31a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X31));
        ui->checkMainY32p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y32));  ui->checkMainX32p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X32));  ui->checkMainX32i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X32));  ui->checkMainX32a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X32));
        ui->checkMainY33p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y33));  ui->checkMainX33p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X33));  ui->checkMainX33i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X33));  ui->checkMainX33a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X33));
        ui->checkMainY34p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y34));  ui->checkMainX34p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X34));  ui->checkMainX34i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X34));  ui->checkMainX34a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X34));
        ui->checkMainY35p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y35));  ui->checkMainX35p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X35));  ui->checkMainX35i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X35));  ui->checkMainX35a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X35));
        ui->checkMainY36p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y36));  ui->checkMainX36p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X36));  ui->checkMainX36i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X36));  ui->checkMainX36a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X36));
        ui->checkMainY37p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y37));  ui->checkMainX37p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X37));  ui->checkMainX37i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X37));  ui->checkMainX37a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X37));
        ui->checkMainY38p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y38));  ui->checkMainX38p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X38));  ui->checkMainX38i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X38));  ui->checkMainX38a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X38));
        ui->checkMainY39p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y39));  ui->checkMainX39p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X39));  ui->checkMainX39i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X39));  ui->checkMainX39a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X39));
        ui->checkMainY40p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y40));  ui->checkMainX40p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X40));  ui->checkMainX40i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X40));  ui->checkMainX40a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X40));
        ui->checkMainY41p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y41));  ui->checkMainX41p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X41));  ui->checkMainX41i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X41));  ui->checkMainX41a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X41));
        ui->checkMainY42p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y42));  ui->checkMainX42p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X42));  ui->checkMainX42i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X42));  ui->checkMainX42a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X42));
        ui->checkMainY43p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y43));  ui->checkMainX43p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X43));  ui->checkMainX43i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X43));  ui->checkMainX43a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X43));
        ui->checkMainY44p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y44));  ui->checkMainX44p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X44));  ui->checkMainX44i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X44));  ui->checkMainX44a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X44));
        ui->checkMainY45p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y45));  ui->checkMainX45p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X45));  ui->checkMainX45i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X45));  ui->checkMainX45a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X45));
        ui->checkMainY46p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y46));  ui->checkMainX46p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X46));  ui->checkMainX46i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X46));  ui->checkMainX46a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X46));
        ui->checkMainY47p->setVisible(xIoPort::IsVisibleExtOut(MAIN_VAR_Y47));  ui->checkMainX47p->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X47));  ui->checkMainX47i->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X47));  ui->checkMainX47a->setVisible(xIoPort::IsVisibleExtIn(MAIN_VAR_X47));
    }
    else
    {
        ui->checkMainY16p->setVisible(false);  ui->checkMainX16p->setVisible(false);  ui->checkMainX16i->setVisible(false);  ui->checkMainX16a->setVisible(false);
        ui->checkMainY17p->setVisible(false);  ui->checkMainX17p->setVisible(false);  ui->checkMainX17i->setVisible(false);  ui->checkMainX17a->setVisible(false);
        ui->checkMainY18p->setVisible(false);  ui->checkMainX18p->setVisible(false);  ui->checkMainX18i->setVisible(false);  ui->checkMainX18a->setVisible(false);
        ui->checkMainY19p->setVisible(false);  ui->checkMainX19p->setVisible(false);  ui->checkMainX19i->setVisible(false);  ui->checkMainX19a->setVisible(false);
        ui->checkMainY20p->setVisible(false);  ui->checkMainX20p->setVisible(false);  ui->checkMainX20i->setVisible(false);  ui->checkMainX20a->setVisible(false);
        ui->checkMainY21p->setVisible(false);  ui->checkMainX21p->setVisible(false);  ui->checkMainX21i->setVisible(false);  ui->checkMainX21a->setVisible(false);
        ui->checkMainY22p->setVisible(false);  ui->checkMainX22p->setVisible(false);  ui->checkMainX22i->setVisible(false);  ui->checkMainX22a->setVisible(false);
        ui->checkMainY23p->setVisible(false);  ui->checkMainX23p->setVisible(false);  ui->checkMainX23i->setVisible(false);  ui->checkMainX23a->setVisible(false);
        ui->checkMainY24p->setVisible(false);  ui->checkMainX24p->setVisible(false);  ui->checkMainX24i->setVisible(false);  ui->checkMainX24a->setVisible(false);
        ui->checkMainY25p->setVisible(false);  ui->checkMainX25p->setVisible(false);  ui->checkMainX25i->setVisible(false);  ui->checkMainX25a->setVisible(false);
        ui->checkMainY26p->setVisible(false);  ui->checkMainX26p->setVisible(false);  ui->checkMainX26i->setVisible(false);  ui->checkMainX26a->setVisible(false);
        ui->checkMainY27p->setVisible(false);  ui->checkMainX27p->setVisible(false);  ui->checkMainX27i->setVisible(false);  ui->checkMainX27a->setVisible(false);
        ui->checkMainY28p->setVisible(false);  ui->checkMainX28p->setVisible(false);  ui->checkMainX28i->setVisible(false);  ui->checkMainX28a->setVisible(false);
        ui->checkMainY29p->setVisible(false);  ui->checkMainX29p->setVisible(false);  ui->checkMainX29i->setVisible(false);  ui->checkMainX29a->setVisible(false);
        ui->checkMainY30p->setVisible(false);  ui->checkMainX30p->setVisible(false);  ui->checkMainX30i->setVisible(false);  ui->checkMainX30a->setVisible(false);
        ui->checkMainY31p->setVisible(false);  ui->checkMainX31p->setVisible(false);  ui->checkMainX31i->setVisible(false);  ui->checkMainX31a->setVisible(false);
        ui->checkMainY32p->setVisible(false);  ui->checkMainX32p->setVisible(false);  ui->checkMainX32i->setVisible(false);  ui->checkMainX32a->setVisible(false);
        ui->checkMainY33p->setVisible(false);  ui->checkMainX33p->setVisible(false);  ui->checkMainX33i->setVisible(false);  ui->checkMainX33a->setVisible(false);
        ui->checkMainY34p->setVisible(false);  ui->checkMainX34p->setVisible(false);  ui->checkMainX34i->setVisible(false);  ui->checkMainX34a->setVisible(false);
        ui->checkMainY35p->setVisible(false);  ui->checkMainX35p->setVisible(false);  ui->checkMainX35i->setVisible(false);  ui->checkMainX35a->setVisible(false);
        ui->checkMainY36p->setVisible(false);  ui->checkMainX36p->setVisible(false);  ui->checkMainX36i->setVisible(false);  ui->checkMainX36a->setVisible(false);
        ui->checkMainY37p->setVisible(false);  ui->checkMainX37p->setVisible(false);  ui->checkMainX37i->setVisible(false);  ui->checkMainX37a->setVisible(false);
        ui->checkMainY38p->setVisible(false);  ui->checkMainX38p->setVisible(false);  ui->checkMainX38i->setVisible(false);  ui->checkMainX38a->setVisible(false);
        ui->checkMainY39p->setVisible(false);  ui->checkMainX39p->setVisible(false);  ui->checkMainX39i->setVisible(false);  ui->checkMainX39a->setVisible(false);
        ui->checkMainY40p->setVisible(false);  ui->checkMainX40p->setVisible(false);  ui->checkMainX40i->setVisible(false);  ui->checkMainX40a->setVisible(false);
        ui->checkMainY41p->setVisible(false);  ui->checkMainX41p->setVisible(false);  ui->checkMainX41i->setVisible(false);  ui->checkMainX41a->setVisible(false);
        ui->checkMainY42p->setVisible(false);  ui->checkMainX42p->setVisible(false);  ui->checkMainX42i->setVisible(false);  ui->checkMainX42a->setVisible(false);
        ui->checkMainY43p->setVisible(false);  ui->checkMainX43p->setVisible(false);  ui->checkMainX43i->setVisible(false);  ui->checkMainX43a->setVisible(false);
        ui->checkMainY44p->setVisible(false);  ui->checkMainX44p->setVisible(false);  ui->checkMainX44i->setVisible(false);  ui->checkMainX44a->setVisible(false);
        ui->checkMainY45p->setVisible(false);  ui->checkMainX45p->setVisible(false);  ui->checkMainX45i->setVisible(false);  ui->checkMainX45a->setVisible(false);
        ui->checkMainY46p->setVisible(false);  ui->checkMainX46p->setVisible(false);  ui->checkMainX46i->setVisible(false);  ui->checkMainX46a->setVisible(false);
        ui->checkMainY47p->setVisible(false);  ui->checkMainX47p->setVisible(false);  ui->checkMainX47i->setVisible(false);  ui->checkMainX47a->setVisible(false);

    }

    ui->checkEm1Y01p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y00));	ui->checkEm1X01p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X00));	ui->checkEm1X01i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X00));  ui->checkEm1X01a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X00));
    ui->checkEm1Y02p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y01));	ui->checkEm1X02p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X01));	ui->checkEm1X02i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X01));  ui->checkEm1X02a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X01));
    ui->checkEm1Y03p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y02));	ui->checkEm1X03p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X02));	ui->checkEm1X03i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X02));  ui->checkEm1X03a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X02));
    ui->checkEm1Y04p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y03));	ui->checkEm1X04p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X03));	ui->checkEm1X04i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X03));  ui->checkEm1X04a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X03));
    ui->checkEm1Y05p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y04));	ui->checkEm1X05p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X04));	ui->checkEm1X05i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X04));  ui->checkEm1X05a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X04));
    ui->checkEm1Y06p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y05));	ui->checkEm1X06p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X05));	ui->checkEm1X06i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X05));  ui->checkEm1X06a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X05));
    ui->checkEm1Y07p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y06));	ui->checkEm1X07p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X06));	ui->checkEm1X07i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X06));  ui->checkEm1X07a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X06));
    ui->checkEm1Y08p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y07));	ui->checkEm1X08p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X07));	ui->checkEm1X08i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X07));  ui->checkEm1X08a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X07));
    ui->checkEm1Y09p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y08));	ui->checkEm1X09p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X08));	ui->checkEm1X09i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X08));  ui->checkEm1X09a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X08));
    ui->checkEm1Y10p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y09));	ui->checkEm1X10p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X09));	ui->checkEm1X10i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X09));  ui->checkEm1X10a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X09));
    ui->checkEm1Y11p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y10));	ui->checkEm1X11p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X10));	ui->checkEm1X11i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X10));  ui->checkEm1X11a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X10));
    ui->checkEm1Y12p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y11));	ui->checkEm1X12p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X11));	ui->checkEm1X12i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X11));  ui->checkEm1X12a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X11));
    ui->checkEm1Y13p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y12));	ui->checkEm1X13p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X12));	ui->checkEm1X13i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X12));  ui->checkEm1X13a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X12));
    ui->checkEm1Y14p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y13));	ui->checkEm1X14p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X13));	ui->checkEm1X14i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X13));  ui->checkEm1X14a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X13));
    ui->checkEm1Y15p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y14));	ui->checkEm1X15p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X14));	ui->checkEm1X15i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X14));  ui->checkEm1X15a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X14));
    ui->checkEm1Y16p->setVisible(xIoPort::IsVisibleExtOut(EM1_VAR_Y15));	ui->checkEm1X16p->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X15));	ui->checkEm1X16i->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X15));  ui->checkEm1X16a->setVisible(xIoPort::IsVisibleExtIn(EM1_VAR_X15));

    ui->checkEm2Y01p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y00));	ui->checkEm2X01p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X00));	ui->checkEm2X01i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X00));  ui->checkEm2X01a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X00));
    ui->checkEm2Y02p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y01));	ui->checkEm2X02p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X01));	ui->checkEm2X02i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X01));  ui->checkEm2X02a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X01));
    ui->checkEm2Y03p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y02));	ui->checkEm2X03p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X02));	ui->checkEm2X03i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X02));  ui->checkEm2X03a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X02));
    ui->checkEm2Y04p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y03));	ui->checkEm2X04p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X03));	ui->checkEm2X04i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X03));  ui->checkEm2X04a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X03));
    ui->checkEm2Y05p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y04));	ui->checkEm2X05p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X04));	ui->checkEm2X05i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X04));  ui->checkEm2X05a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X04));
    ui->checkEm2Y06p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y05));	ui->checkEm2X06p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X05));	ui->checkEm2X06i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X05));  ui->checkEm2X06a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X05));
    ui->checkEm2Y07p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y06));	ui->checkEm2X07p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X06));	ui->checkEm2X07i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X06));  ui->checkEm2X07a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X06));
    ui->checkEm2Y08p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y07));	ui->checkEm2X08p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X07));	ui->checkEm2X08i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X07));  ui->checkEm2X08a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X07));
    ui->checkEm2Y09p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y08));	ui->checkEm2X09p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X08));	ui->checkEm2X09i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X08));  ui->checkEm2X09a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X08));
    ui->checkEm2Y10p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y09));	ui->checkEm2X10p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X09));	ui->checkEm2X10i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X09));  ui->checkEm2X10a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X09));
    ui->checkEm2Y11p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y10));	ui->checkEm2X11p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X10));	ui->checkEm2X11i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X10));  ui->checkEm2X11a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X10));
    ui->checkEm2Y12p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y11));	ui->checkEm2X12p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X11));	ui->checkEm2X12i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X11));  ui->checkEm2X12a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X11));
    ui->checkEm2Y13p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y12));	ui->checkEm2X13p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X12));	ui->checkEm2X13i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X12));  ui->checkEm2X13a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X12));
    ui->checkEm2Y14p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y13));	ui->checkEm2X14p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X13));	ui->checkEm2X14i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X13));  ui->checkEm2X14a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X13));
    ui->checkEm2Y15p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y14));	ui->checkEm2X15p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X14));	ui->checkEm2X15i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X14));  ui->checkEm2X15a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X14));
    ui->checkEm2Y16p->setVisible(xIoPort::IsVisibleExtOut(EM2_VAR_Y15));	ui->checkEm2X16p->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X15));	ui->checkEm2X16i->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X15));  ui->checkEm2X16a->setVisible(xIoPort::IsVisibleExtIn(EM2_VAR_X15));

    ui->checkEm3Y01p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y00));	ui->checkEm3X01p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X00));	ui->checkEm3X01i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X00));  ui->checkEm3X01a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X00));
    ui->checkEm3Y02p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y01));	ui->checkEm3X02p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X01));	ui->checkEm3X02i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X01));  ui->checkEm3X02a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X01));
    ui->checkEm3Y03p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y02));	ui->checkEm3X03p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X02));	ui->checkEm3X03i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X02));  ui->checkEm3X03a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X02));
    ui->checkEm3Y04p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y03));	ui->checkEm3X04p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X03));	ui->checkEm3X04i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X03));  ui->checkEm3X04a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X03));
    ui->checkEm3Y05p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y04));	ui->checkEm3X05p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X04));	ui->checkEm3X05i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X04));  ui->checkEm3X05a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X04));
    ui->checkEm3Y06p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y05));	ui->checkEm3X06p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X05));	ui->checkEm3X06i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X05));  ui->checkEm3X06a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X05));
    ui->checkEm3Y07p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y06));	ui->checkEm3X07p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X06));	ui->checkEm3X07i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X06));  ui->checkEm3X07a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X06));
    ui->checkEm3Y08p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y07));	ui->checkEm3X08p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X07));	ui->checkEm3X08i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X07));  ui->checkEm3X08a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X07));
    ui->checkEm3Y09p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y08));	ui->checkEm3X09p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X08));	ui->checkEm3X09i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X08));  ui->checkEm3X09a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X08));
    ui->checkEm3Y10p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y09));	ui->checkEm3X10p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X09));	ui->checkEm3X10i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X09));  ui->checkEm3X10a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X09));
    ui->checkEm3Y11p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y10));	ui->checkEm3X11p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X10));	ui->checkEm3X11i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X10));  ui->checkEm3X11a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X10));
    ui->checkEm3Y12p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y11));	ui->checkEm3X12p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X11));	ui->checkEm3X12i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X11));  ui->checkEm3X12a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X11));
    ui->checkEm3Y13p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y12));	ui->checkEm3X13p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X12));	ui->checkEm3X13i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X12));  ui->checkEm3X13a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X12));
    ui->checkEm3Y14p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y13));	ui->checkEm3X14p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X13));	ui->checkEm3X14i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X13));  ui->checkEm3X14a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X13));
    ui->checkEm3Y15p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y14));	ui->checkEm3X15p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X14));	ui->checkEm3X15i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X14));  ui->checkEm3X15a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X14));
    ui->checkEm3Y16p->setVisible(xIoPort::IsVisibleExtOut(EM3_VAR_Y15));	ui->checkEm3X16p->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X15));	ui->checkEm3X16i->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X15));  ui->checkEm3X16a->setVisible(xIoPort::IsVisibleExtIn(EM3_VAR_X15));

    ui->checkEm4Y01p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y00));	ui->checkEm4X01p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X00));	ui->checkEm4X01i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X00));  ui->checkEm4X01a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X00));
    ui->checkEm4Y02p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y01));	ui->checkEm4X02p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X01));	ui->checkEm4X02i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X01));  ui->checkEm4X02a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X01));
    ui->checkEm4Y03p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y02));	ui->checkEm4X03p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X02));	ui->checkEm4X03i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X02));  ui->checkEm4X03a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X02));
    ui->checkEm4Y04p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y03));	ui->checkEm4X04p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X03));	ui->checkEm4X04i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X03));  ui->checkEm4X04a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X03));
    ui->checkEm4Y05p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y04));	ui->checkEm4X05p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X04));	ui->checkEm4X05i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X04));  ui->checkEm4X05a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X04));
    ui->checkEm4Y06p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y05));	ui->checkEm4X06p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X05));	ui->checkEm4X06i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X05));  ui->checkEm4X06a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X05));
    ui->checkEm4Y07p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y06));	ui->checkEm4X07p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X06));	ui->checkEm4X07i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X06));  ui->checkEm4X07a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X06));
    ui->checkEm4Y08p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y07));	ui->checkEm4X08p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X07));	ui->checkEm4X08i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X07));  ui->checkEm4X08a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X07));
    ui->checkEm4Y09p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y08));	ui->checkEm4X09p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X08));	ui->checkEm4X09i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X08));  ui->checkEm4X09a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X08));
    ui->checkEm4Y10p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y09));	ui->checkEm4X10p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X09));	ui->checkEm4X10i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X09));  ui->checkEm4X10a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X09));
    ui->checkEm4Y11p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y10));	ui->checkEm4X11p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X10));	ui->checkEm4X11i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X10));  ui->checkEm4X11a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X10));
    ui->checkEm4Y12p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y11));	ui->checkEm4X12p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X11));	ui->checkEm4X12i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X11));  ui->checkEm4X12a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X11));
    ui->checkEm4Y13p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y12));	ui->checkEm4X13p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X12));	ui->checkEm4X13i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X12));  ui->checkEm4X13a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X12));
    ui->checkEm4Y14p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y13));	ui->checkEm4X14p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X13));	ui->checkEm4X14i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X13));  ui->checkEm4X14a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X13));
    ui->checkEm4Y15p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y14));	ui->checkEm4X15p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X14));	ui->checkEm4X15i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X14));  ui->checkEm4X15a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X14));
    ui->checkEm4Y16p->setVisible(xIoPort::IsVisibleExtOut(EM4_VAR_Y15));	ui->checkEm4X16p->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X15));	ui->checkEm4X16i->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X15));  ui->checkEm4X16a->setVisible(xIoPort::IsVisibleExtIn(EM4_VAR_X15));
}

// 设置端口名称
void FormIO::loadPortNames(void)
{
    // 主控模块扩展输入
    ui->checkMainX00p->setText(xStringResource::GetVarName(MAIN_VAR_X00));	ui->checkMainX00i->setText(xStringResource::GetVarName(MAIN_VAR_X00));	  ui->checkMainX00a->setText(xStringResource::GetVarName(MAIN_VAR_X00));
    ui->checkMainX01p->setText(xStringResource::GetVarName(MAIN_VAR_X01));	ui->checkMainX01i->setText(xStringResource::GetVarName(MAIN_VAR_X01));    ui->checkMainX01a->setText(xStringResource::GetVarName(MAIN_VAR_X01));
    ui->checkMainX02p->setText(xStringResource::GetVarName(MAIN_VAR_X02));	ui->checkMainX02i->setText(xStringResource::GetVarName(MAIN_VAR_X02));    ui->checkMainX02a->setText(xStringResource::GetVarName(MAIN_VAR_X02));
    ui->checkMainX03p->setText(xStringResource::GetVarName(MAIN_VAR_X03));	ui->checkMainX03i->setText(xStringResource::GetVarName(MAIN_VAR_X03));    ui->checkMainX03a->setText(xStringResource::GetVarName(MAIN_VAR_X03));
    ui->checkMainX04p->setText(xStringResource::GetVarName(MAIN_VAR_X04));	ui->checkMainX04i->setText(xStringResource::GetVarName(MAIN_VAR_X04));    ui->checkMainX04a->setText(xStringResource::GetVarName(MAIN_VAR_X04));
    ui->checkMainX05p->setText(xStringResource::GetVarName(MAIN_VAR_X05));	ui->checkMainX05i->setText(xStringResource::GetVarName(MAIN_VAR_X05));    ui->checkMainX05a->setText(xStringResource::GetVarName(MAIN_VAR_X05));
    ui->checkMainX06p->setText(xStringResource::GetVarName(MAIN_VAR_X06));	ui->checkMainX06i->setText(xStringResource::GetVarName(MAIN_VAR_X06));    ui->checkMainX06a->setText(xStringResource::GetVarName(MAIN_VAR_X06));
    ui->checkMainX07p->setText(xStringResource::GetVarName(MAIN_VAR_X07));	ui->checkMainX07i->setText(xStringResource::GetVarName(MAIN_VAR_X07));    ui->checkMainX07a->setText(xStringResource::GetVarName(MAIN_VAR_X07));
    ui->checkMainX08p->setText(xStringResource::GetVarName(MAIN_VAR_X08));	ui->checkMainX08i->setText(xStringResource::GetVarName(MAIN_VAR_X08));    ui->checkMainX08a->setText(xStringResource::GetVarName(MAIN_VAR_X08));
    ui->checkMainX09p->setText(xStringResource::GetVarName(MAIN_VAR_X09));	ui->checkMainX09i->setText(xStringResource::GetVarName(MAIN_VAR_X09));    ui->checkMainX09a->setText(xStringResource::GetVarName(MAIN_VAR_X09));
    ui->checkMainX10p->setText(xStringResource::GetVarName(MAIN_VAR_X10));	ui->checkMainX10i->setText(xStringResource::GetVarName(MAIN_VAR_X10));    ui->checkMainX10a->setText(xStringResource::GetVarName(MAIN_VAR_X10));
    ui->checkMainX11p->setText(xStringResource::GetVarName(MAIN_VAR_X11));	ui->checkMainX11i->setText(xStringResource::GetVarName(MAIN_VAR_X11));    ui->checkMainX11a->setText(xStringResource::GetVarName(MAIN_VAR_X11));
    ui->checkMainX12p->setText(xStringResource::GetVarName(MAIN_VAR_X12));	ui->checkMainX12i->setText(xStringResource::GetVarName(MAIN_VAR_X12));    ui->checkMainX12a->setText(xStringResource::GetVarName(MAIN_VAR_X12));
    ui->checkMainX13p->setText(xStringResource::GetVarName(MAIN_VAR_X13));	ui->checkMainX13i->setText(xStringResource::GetVarName(MAIN_VAR_X13));    ui->checkMainX13a->setText(xStringResource::GetVarName(MAIN_VAR_X13));
    ui->checkMainX14p->setText(xStringResource::GetVarName(MAIN_VAR_X14));	ui->checkMainX14i->setText(xStringResource::GetVarName(MAIN_VAR_X14));    ui->checkMainX14a->setText(xStringResource::GetVarName(MAIN_VAR_X14));
    ui->checkMainX15p->setText(xStringResource::GetVarName(MAIN_VAR_X15));	ui->checkMainX15i->setText(xStringResource::GetVarName(MAIN_VAR_X15));    ui->checkMainX15a->setText(xStringResource::GetVarName(MAIN_VAR_X15));

    ui->checkMainX16p->setText(xStringResource::GetVarName(MAIN_VAR_X16));	ui->checkMainX16i->setText(xStringResource::GetVarName(MAIN_VAR_X16));    ui->checkMainX16a->setText(xStringResource::GetVarName(MAIN_VAR_X16));
    ui->checkMainX17p->setText(xStringResource::GetVarName(MAIN_VAR_X17));	ui->checkMainX17i->setText(xStringResource::GetVarName(MAIN_VAR_X17));    ui->checkMainX17a->setText(xStringResource::GetVarName(MAIN_VAR_X17));
    ui->checkMainX18p->setText(xStringResource::GetVarName(MAIN_VAR_X18));	ui->checkMainX18i->setText(xStringResource::GetVarName(MAIN_VAR_X18));    ui->checkMainX18a->setText(xStringResource::GetVarName(MAIN_VAR_X18));
    ui->checkMainX19p->setText(xStringResource::GetVarName(MAIN_VAR_X19));	ui->checkMainX19i->setText(xStringResource::GetVarName(MAIN_VAR_X19));    ui->checkMainX19a->setText(xStringResource::GetVarName(MAIN_VAR_X19));
    ui->checkMainX20p->setText(xStringResource::GetVarName(MAIN_VAR_X20));	ui->checkMainX20i->setText(xStringResource::GetVarName(MAIN_VAR_X20));    ui->checkMainX20a->setText(xStringResource::GetVarName(MAIN_VAR_X20));
    ui->checkMainX21p->setText(xStringResource::GetVarName(MAIN_VAR_X21));	ui->checkMainX21i->setText(xStringResource::GetVarName(MAIN_VAR_X21));    ui->checkMainX21a->setText(xStringResource::GetVarName(MAIN_VAR_X21));
    ui->checkMainX22p->setText(xStringResource::GetVarName(MAIN_VAR_X22));	ui->checkMainX22i->setText(xStringResource::GetVarName(MAIN_VAR_X22));    ui->checkMainX22a->setText(xStringResource::GetVarName(MAIN_VAR_X22));
    ui->checkMainX23p->setText(xStringResource::GetVarName(MAIN_VAR_X23));	ui->checkMainX23i->setText(xStringResource::GetVarName(MAIN_VAR_X23));    ui->checkMainX23a->setText(xStringResource::GetVarName(MAIN_VAR_X23));
    ui->checkMainX24p->setText(xStringResource::GetVarName(MAIN_VAR_X24));	ui->checkMainX24i->setText(xStringResource::GetVarName(MAIN_VAR_X24));    ui->checkMainX24a->setText(xStringResource::GetVarName(MAIN_VAR_X24));
    ui->checkMainX25p->setText(xStringResource::GetVarName(MAIN_VAR_X25));	ui->checkMainX25i->setText(xStringResource::GetVarName(MAIN_VAR_X25));    ui->checkMainX25a->setText(xStringResource::GetVarName(MAIN_VAR_X25));
    ui->checkMainX26p->setText(xStringResource::GetVarName(MAIN_VAR_X26));	ui->checkMainX26i->setText(xStringResource::GetVarName(MAIN_VAR_X26));    ui->checkMainX26a->setText(xStringResource::GetVarName(MAIN_VAR_X26));
    ui->checkMainX27p->setText(xStringResource::GetVarName(MAIN_VAR_X27));	ui->checkMainX27i->setText(xStringResource::GetVarName(MAIN_VAR_X27));    ui->checkMainX27a->setText(xStringResource::GetVarName(MAIN_VAR_X27));
    ui->checkMainX28p->setText(xStringResource::GetVarName(MAIN_VAR_X28));	ui->checkMainX28i->setText(xStringResource::GetVarName(MAIN_VAR_X28));    ui->checkMainX28a->setText(xStringResource::GetVarName(MAIN_VAR_X28));
    ui->checkMainX29p->setText(xStringResource::GetVarName(MAIN_VAR_X29));	ui->checkMainX29i->setText(xStringResource::GetVarName(MAIN_VAR_X29));    ui->checkMainX29a->setText(xStringResource::GetVarName(MAIN_VAR_X29));
    ui->checkMainX30p->setText(xStringResource::GetVarName(MAIN_VAR_X30));	ui->checkMainX30i->setText(xStringResource::GetVarName(MAIN_VAR_X30));    ui->checkMainX30a->setText(xStringResource::GetVarName(MAIN_VAR_X30));
    ui->checkMainX31p->setText(xStringResource::GetVarName(MAIN_VAR_X31));	ui->checkMainX31i->setText(xStringResource::GetVarName(MAIN_VAR_X31));    ui->checkMainX31a->setText(xStringResource::GetVarName(MAIN_VAR_X31));
    ui->checkMainX32p->setText(xStringResource::GetVarName(MAIN_VAR_X32));	ui->checkMainX32i->setText(xStringResource::GetVarName(MAIN_VAR_X32));    ui->checkMainX32a->setText(xStringResource::GetVarName(MAIN_VAR_X32));
    ui->checkMainX33p->setText(xStringResource::GetVarName(MAIN_VAR_X33));	ui->checkMainX33i->setText(xStringResource::GetVarName(MAIN_VAR_X33));    ui->checkMainX33a->setText(xStringResource::GetVarName(MAIN_VAR_X33));
    ui->checkMainX34p->setText(xStringResource::GetVarName(MAIN_VAR_X34));	ui->checkMainX34i->setText(xStringResource::GetVarName(MAIN_VAR_X34));    ui->checkMainX34a->setText(xStringResource::GetVarName(MAIN_VAR_X34));
    ui->checkMainX35p->setText(xStringResource::GetVarName(MAIN_VAR_X35));	ui->checkMainX35i->setText(xStringResource::GetVarName(MAIN_VAR_X35));    ui->checkMainX35a->setText(xStringResource::GetVarName(MAIN_VAR_X35));
    ui->checkMainX36p->setText(xStringResource::GetVarName(MAIN_VAR_X36));	ui->checkMainX36i->setText(xStringResource::GetVarName(MAIN_VAR_X36));    ui->checkMainX36a->setText(xStringResource::GetVarName(MAIN_VAR_X36));
    ui->checkMainX37p->setText(xStringResource::GetVarName(MAIN_VAR_X37));	ui->checkMainX37i->setText(xStringResource::GetVarName(MAIN_VAR_X37));    ui->checkMainX37a->setText(xStringResource::GetVarName(MAIN_VAR_X37));
    ui->checkMainX38p->setText(xStringResource::GetVarName(MAIN_VAR_X38));	ui->checkMainX38i->setText(xStringResource::GetVarName(MAIN_VAR_X38));    ui->checkMainX38a->setText(xStringResource::GetVarName(MAIN_VAR_X38));
    ui->checkMainX39p->setText(xStringResource::GetVarName(MAIN_VAR_X39));	ui->checkMainX39i->setText(xStringResource::GetVarName(MAIN_VAR_X39));    ui->checkMainX39a->setText(xStringResource::GetVarName(MAIN_VAR_X39));
    ui->checkMainX40p->setText(xStringResource::GetVarName(MAIN_VAR_X40));	ui->checkMainX40i->setText(xStringResource::GetVarName(MAIN_VAR_X40));    ui->checkMainX40a->setText(xStringResource::GetVarName(MAIN_VAR_X40));
    ui->checkMainX41p->setText(xStringResource::GetVarName(MAIN_VAR_X41));	ui->checkMainX41i->setText(xStringResource::GetVarName(MAIN_VAR_X41));    ui->checkMainX41a->setText(xStringResource::GetVarName(MAIN_VAR_X41));
    ui->checkMainX42p->setText(xStringResource::GetVarName(MAIN_VAR_X42));	ui->checkMainX42i->setText(xStringResource::GetVarName(MAIN_VAR_X42));    ui->checkMainX42a->setText(xStringResource::GetVarName(MAIN_VAR_X42));
    ui->checkMainX43p->setText(xStringResource::GetVarName(MAIN_VAR_X43));	ui->checkMainX43i->setText(xStringResource::GetVarName(MAIN_VAR_X43));    ui->checkMainX43a->setText(xStringResource::GetVarName(MAIN_VAR_X43));
    ui->checkMainX44p->setText(xStringResource::GetVarName(MAIN_VAR_X44));	ui->checkMainX44i->setText(xStringResource::GetVarName(MAIN_VAR_X44));    ui->checkMainX44a->setText(xStringResource::GetVarName(MAIN_VAR_X44));
    ui->checkMainX45p->setText(xStringResource::GetVarName(MAIN_VAR_X45));	ui->checkMainX45i->setText(xStringResource::GetVarName(MAIN_VAR_X45));    ui->checkMainX45a->setText(xStringResource::GetVarName(MAIN_VAR_X45));
    ui->checkMainX46p->setText(xStringResource::GetVarName(MAIN_VAR_X46));	ui->checkMainX46i->setText(xStringResource::GetVarName(MAIN_VAR_X46));    ui->checkMainX46a->setText(xStringResource::GetVarName(MAIN_VAR_X46));
    ui->checkMainX47p->setText(xStringResource::GetVarName(MAIN_VAR_X47));	ui->checkMainX47i->setText(xStringResource::GetVarName(MAIN_VAR_X47));    ui->checkMainX47a->setText(xStringResource::GetVarName(MAIN_VAR_X47));
	// 模块1扩展输入
    ui->checkEm1X01p->setText(xStringResource::GetVarName(EM1_VAR_X00));	ui->checkEm1X01i->setText(xStringResource::GetVarName(EM1_VAR_X00));	ui->checkEm1X01a->setText(xStringResource::GetVarName(EM1_VAR_X00));
    ui->checkEm1X02p->setText(xStringResource::GetVarName(EM1_VAR_X01));	ui->checkEm1X02i->setText(xStringResource::GetVarName(EM1_VAR_X01));	ui->checkEm1X02a->setText(xStringResource::GetVarName(EM1_VAR_X01));
    ui->checkEm1X03p->setText(xStringResource::GetVarName(EM1_VAR_X02));	ui->checkEm1X03i->setText(xStringResource::GetVarName(EM1_VAR_X02));	ui->checkEm1X03a->setText(xStringResource::GetVarName(EM1_VAR_X02));
	ui->checkEm1X04p->setText(xStringResource::GetVarName(EM1_VAR_X03));	ui->checkEm1X04i->setText(xStringResource::GetVarName(EM1_VAR_X03));	ui->checkEm1X04a->setText(xStringResource::GetVarName(EM1_VAR_X03));
	ui->checkEm1X05p->setText(xStringResource::GetVarName(EM1_VAR_X04));	ui->checkEm1X05i->setText(xStringResource::GetVarName(EM1_VAR_X04));	ui->checkEm1X05a->setText(xStringResource::GetVarName(EM1_VAR_X04));
	ui->checkEm1X06p->setText(xStringResource::GetVarName(EM1_VAR_X05));	ui->checkEm1X06i->setText(xStringResource::GetVarName(EM1_VAR_X05));	ui->checkEm1X06a->setText(xStringResource::GetVarName(EM1_VAR_X05));
	ui->checkEm1X07p->setText(xStringResource::GetVarName(EM1_VAR_X06));	ui->checkEm1X07i->setText(xStringResource::GetVarName(EM1_VAR_X06));	ui->checkEm1X07a->setText(xStringResource::GetVarName(EM1_VAR_X06));
	ui->checkEm1X08p->setText(xStringResource::GetVarName(EM1_VAR_X07));	ui->checkEm1X08i->setText(xStringResource::GetVarName(EM1_VAR_X07));	ui->checkEm1X08a->setText(xStringResource::GetVarName(EM1_VAR_X07));
    if (pModbus->GetOilUse())
    {
        ui->checkEm1X09p->setText(tr("打油反馈-X09"));	ui->checkEm1X09i->setText(tr("打油反馈-X09"));	ui->checkEm1X09a->setText(tr("打油反馈-X09"));
    }
    else
    {
	ui->checkEm1X09p->setText(xStringResource::GetVarName(EM1_VAR_X08));	ui->checkEm1X09i->setText(xStringResource::GetVarName(EM1_VAR_X08));	ui->checkEm1X09a->setText(xStringResource::GetVarName(EM1_VAR_X08));
    }
	ui->checkEm1X10p->setText(xStringResource::GetVarName(EM1_VAR_X09));	ui->checkEm1X10i->setText(xStringResource::GetVarName(EM1_VAR_X09));	ui->checkEm1X10a->setText(xStringResource::GetVarName(EM1_VAR_X09));
	ui->checkEm1X11p->setText(xStringResource::GetVarName(EM1_VAR_X10));	ui->checkEm1X11i->setText(xStringResource::GetVarName(EM1_VAR_X10));	ui->checkEm1X11a->setText(xStringResource::GetVarName(EM1_VAR_X10));
	ui->checkEm1X12p->setText(xStringResource::GetVarName(EM1_VAR_X11));	ui->checkEm1X12i->setText(xStringResource::GetVarName(EM1_VAR_X11));	ui->checkEm1X12a->setText(xStringResource::GetVarName(EM1_VAR_X11));
	ui->checkEm1X13p->setText(xStringResource::GetVarName(EM1_VAR_X12));	ui->checkEm1X13i->setText(xStringResource::GetVarName(EM1_VAR_X12));	ui->checkEm1X13a->setText(xStringResource::GetVarName(EM1_VAR_X12));
    ui->checkEm1X14p->setText(xStringResource::GetVarName(EM1_VAR_X13));	ui->checkEm1X14i->setText(xStringResource::GetVarName(EM1_VAR_X13));	ui->checkEm1X14a->setText(xStringResource::GetVarName(EM1_VAR_X13));
    ui->checkEm1X15p->setText(xStringResource::GetVarName(EM1_VAR_X14));	ui->checkEm1X15i->setText(xStringResource::GetVarName(EM1_VAR_X14));	ui->checkEm1X15a->setText(xStringResource::GetVarName(EM1_VAR_X14));
    ui->checkEm1X16p->setText(xStringResource::GetVarName(EM1_VAR_X15));	ui->checkEm1X16i->setText(xStringResource::GetVarName(EM1_VAR_X15));	ui->checkEm1X16a->setText(xStringResource::GetVarName(EM1_VAR_X15));
    // 模块2扩展输入
	ui->checkEm2X01p->setText(xStringResource::GetVarName(EM2_VAR_X00));	ui->checkEm2X01i->setText(xStringResource::GetVarName(EM2_VAR_X00));	ui->checkEm2X01a->setText(xStringResource::GetVarName(EM2_VAR_X00));
	ui->checkEm2X02p->setText(xStringResource::GetVarName(EM2_VAR_X01));	ui->checkEm2X02i->setText(xStringResource::GetVarName(EM2_VAR_X01));    ui->checkEm2X02a->setText(xStringResource::GetVarName(EM2_VAR_X01));
	ui->checkEm2X03p->setText(xStringResource::GetVarName(EM2_VAR_X02));	ui->checkEm2X03i->setText(xStringResource::GetVarName(EM2_VAR_X02));    ui->checkEm2X03a->setText(xStringResource::GetVarName(EM2_VAR_X02));
	ui->checkEm2X04p->setText(xStringResource::GetVarName(EM2_VAR_X03));	ui->checkEm2X04i->setText(xStringResource::GetVarName(EM2_VAR_X03));    ui->checkEm2X04a->setText(xStringResource::GetVarName(EM2_VAR_X03));
	ui->checkEm2X05p->setText(xStringResource::GetVarName(EM2_VAR_X04));	ui->checkEm2X05i->setText(xStringResource::GetVarName(EM2_VAR_X04));    ui->checkEm2X05a->setText(xStringResource::GetVarName(EM2_VAR_X04));
	ui->checkEm2X06p->setText(xStringResource::GetVarName(EM2_VAR_X05));	ui->checkEm2X06i->setText(xStringResource::GetVarName(EM2_VAR_X05));    ui->checkEm2X06a->setText(xStringResource::GetVarName(EM2_VAR_X05));
	ui->checkEm2X07p->setText(xStringResource::GetVarName(EM2_VAR_X06));	ui->checkEm2X07i->setText(xStringResource::GetVarName(EM2_VAR_X06));    ui->checkEm2X07a->setText(xStringResource::GetVarName(EM2_VAR_X06));
	ui->checkEm2X08p->setText(xStringResource::GetVarName(EM2_VAR_X07));	ui->checkEm2X08i->setText(xStringResource::GetVarName(EM2_VAR_X07));    ui->checkEm2X08a->setText(xStringResource::GetVarName(EM2_VAR_X07));
	ui->checkEm2X09p->setText(xStringResource::GetVarName(EM2_VAR_X08));	ui->checkEm2X09i->setText(xStringResource::GetVarName(EM2_VAR_X08));    ui->checkEm2X09a->setText(xStringResource::GetVarName(EM2_VAR_X08));
	ui->checkEm2X10p->setText(xStringResource::GetVarName(EM2_VAR_X09));	ui->checkEm2X10i->setText(xStringResource::GetVarName(EM2_VAR_X09));    ui->checkEm2X10a->setText(xStringResource::GetVarName(EM2_VAR_X09));
	ui->checkEm2X11p->setText(xStringResource::GetVarName(EM2_VAR_X10));	ui->checkEm2X11i->setText(xStringResource::GetVarName(EM2_VAR_X10));    ui->checkEm2X11a->setText(xStringResource::GetVarName(EM2_VAR_X10));
	ui->checkEm2X12p->setText(xStringResource::GetVarName(EM2_VAR_X11));	ui->checkEm2X12i->setText(xStringResource::GetVarName(EM2_VAR_X11));    ui->checkEm2X12a->setText(xStringResource::GetVarName(EM2_VAR_X11));
	ui->checkEm2X13p->setText(xStringResource::GetVarName(EM2_VAR_X12));	ui->checkEm2X13i->setText(xStringResource::GetVarName(EM2_VAR_X12));    ui->checkEm2X13a->setText(xStringResource::GetVarName(EM2_VAR_X12));
    ui->checkEm2X14p->setText(xStringResource::GetVarName(EM2_VAR_X13));	ui->checkEm2X14i->setText(xStringResource::GetVarName(EM2_VAR_X13));    ui->checkEm2X14a->setText(xStringResource::GetVarName(EM2_VAR_X13));
    ui->checkEm2X15p->setText(xStringResource::GetVarName(EM2_VAR_X14));	ui->checkEm2X15i->setText(xStringResource::GetVarName(EM2_VAR_X14));    ui->checkEm2X15a->setText(xStringResource::GetVarName(EM2_VAR_X14));
    ui->checkEm2X16p->setText(xStringResource::GetVarName(EM2_VAR_X15));	ui->checkEm2X16i->setText(xStringResource::GetVarName(EM2_VAR_X15));    ui->checkEm2X16a->setText(xStringResource::GetVarName(EM2_VAR_X15));
    // 模块3扩展输入
	ui->checkEm3X01p->setText(xStringResource::GetVarName(EM3_VAR_X00));	ui->checkEm3X01i->setText(xStringResource::GetVarName(EM3_VAR_X00));	ui->checkEm3X01a->setText(xStringResource::GetVarName(EM3_VAR_X00));
	ui->checkEm3X02p->setText(xStringResource::GetVarName(EM3_VAR_X01));	ui->checkEm3X02i->setText(xStringResource::GetVarName(EM3_VAR_X01));    ui->checkEm3X02a->setText(xStringResource::GetVarName(EM3_VAR_X01));
	ui->checkEm3X03p->setText(xStringResource::GetVarName(EM3_VAR_X02));	ui->checkEm3X03i->setText(xStringResource::GetVarName(EM3_VAR_X02));    ui->checkEm3X03a->setText(xStringResource::GetVarName(EM3_VAR_X02));
	ui->checkEm3X04p->setText(xStringResource::GetVarName(EM3_VAR_X03));	ui->checkEm3X04i->setText(xStringResource::GetVarName(EM3_VAR_X03));    ui->checkEm3X04a->setText(xStringResource::GetVarName(EM3_VAR_X03));
	ui->checkEm3X05p->setText(xStringResource::GetVarName(EM3_VAR_X04));	ui->checkEm3X05i->setText(xStringResource::GetVarName(EM3_VAR_X04));    ui->checkEm3X05a->setText(xStringResource::GetVarName(EM3_VAR_X04));
	ui->checkEm3X06p->setText(xStringResource::GetVarName(EM3_VAR_X05));	ui->checkEm3X06i->setText(xStringResource::GetVarName(EM3_VAR_X05));    ui->checkEm3X06a->setText(xStringResource::GetVarName(EM3_VAR_X05));
	ui->checkEm3X07p->setText(xStringResource::GetVarName(EM3_VAR_X06));	ui->checkEm3X07i->setText(xStringResource::GetVarName(EM3_VAR_X06));    ui->checkEm3X07a->setText(xStringResource::GetVarName(EM3_VAR_X06));
	ui->checkEm3X08p->setText(xStringResource::GetVarName(EM3_VAR_X07));	ui->checkEm3X08i->setText(xStringResource::GetVarName(EM3_VAR_X07));    ui->checkEm3X08a->setText(xStringResource::GetVarName(EM3_VAR_X07));
	ui->checkEm3X09p->setText(xStringResource::GetVarName(EM3_VAR_X08));	ui->checkEm3X09i->setText(xStringResource::GetVarName(EM3_VAR_X08));    ui->checkEm3X09a->setText(xStringResource::GetVarName(EM3_VAR_X08));
	ui->checkEm3X10p->setText(xStringResource::GetVarName(EM3_VAR_X09));	ui->checkEm3X10i->setText(xStringResource::GetVarName(EM3_VAR_X09));    ui->checkEm3X10a->setText(xStringResource::GetVarName(EM3_VAR_X09));
	ui->checkEm3X11p->setText(xStringResource::GetVarName(EM3_VAR_X10));	ui->checkEm3X11i->setText(xStringResource::GetVarName(EM3_VAR_X10));    ui->checkEm3X11a->setText(xStringResource::GetVarName(EM3_VAR_X10));
	ui->checkEm3X12p->setText(xStringResource::GetVarName(EM3_VAR_X11));	ui->checkEm3X12i->setText(xStringResource::GetVarName(EM3_VAR_X11));    ui->checkEm3X12a->setText(xStringResource::GetVarName(EM3_VAR_X11));
	ui->checkEm3X13p->setText(xStringResource::GetVarName(EM3_VAR_X12));	ui->checkEm3X13i->setText(xStringResource::GetVarName(EM3_VAR_X12));    ui->checkEm3X13a->setText(xStringResource::GetVarName(EM3_VAR_X12));
    ui->checkEm3X14p->setText(xStringResource::GetVarName(EM3_VAR_X13));	ui->checkEm3X14i->setText(xStringResource::GetVarName(EM3_VAR_X13));    ui->checkEm3X14a->setText(xStringResource::GetVarName(EM3_VAR_X13));
    ui->checkEm3X15p->setText(xStringResource::GetVarName(EM3_VAR_X14));	ui->checkEm3X15i->setText(xStringResource::GetVarName(EM3_VAR_X14));    ui->checkEm3X15a->setText(xStringResource::GetVarName(EM3_VAR_X14));
    ui->checkEm3X16p->setText(xStringResource::GetVarName(EM3_VAR_X15));	ui->checkEm3X16i->setText(xStringResource::GetVarName(EM3_VAR_X15));    ui->checkEm3X16a->setText(xStringResource::GetVarName(EM3_VAR_X15));
    // 模块4扩展输入
	ui->checkEm4X01p->setText(xStringResource::GetVarName(EM4_VAR_X00));	ui->checkEm4X01i->setText(xStringResource::GetVarName(EM4_VAR_X00));	ui->checkEm4X01a->setText(xStringResource::GetVarName(EM4_VAR_X00));
	ui->checkEm4X02p->setText(xStringResource::GetVarName(EM4_VAR_X01));	ui->checkEm4X02i->setText(xStringResource::GetVarName(EM4_VAR_X01));    ui->checkEm4X02a->setText(xStringResource::GetVarName(EM4_VAR_X01));
	ui->checkEm4X03p->setText(xStringResource::GetVarName(EM4_VAR_X02));	ui->checkEm4X03i->setText(xStringResource::GetVarName(EM4_VAR_X02));    ui->checkEm4X03a->setText(xStringResource::GetVarName(EM4_VAR_X02));
	ui->checkEm4X04p->setText(xStringResource::GetVarName(EM4_VAR_X03));	ui->checkEm4X04i->setText(xStringResource::GetVarName(EM4_VAR_X03));    ui->checkEm4X04a->setText(xStringResource::GetVarName(EM4_VAR_X03));
	ui->checkEm4X05p->setText(xStringResource::GetVarName(EM4_VAR_X04));	ui->checkEm4X05i->setText(xStringResource::GetVarName(EM4_VAR_X04));    ui->checkEm4X05a->setText(xStringResource::GetVarName(EM4_VAR_X04));
	ui->checkEm4X06p->setText(xStringResource::GetVarName(EM4_VAR_X05));	ui->checkEm4X06i->setText(xStringResource::GetVarName(EM4_VAR_X05));    ui->checkEm4X06a->setText(xStringResource::GetVarName(EM4_VAR_X05));
	ui->checkEm4X07p->setText(xStringResource::GetVarName(EM4_VAR_X06));	ui->checkEm4X07i->setText(xStringResource::GetVarName(EM4_VAR_X06));    ui->checkEm4X07a->setText(xStringResource::GetVarName(EM4_VAR_X06));
	ui->checkEm4X08p->setText(xStringResource::GetVarName(EM4_VAR_X07));	ui->checkEm4X08i->setText(xStringResource::GetVarName(EM4_VAR_X07));    ui->checkEm4X08a->setText(xStringResource::GetVarName(EM4_VAR_X07));
	ui->checkEm4X09p->setText(xStringResource::GetVarName(EM4_VAR_X08));	ui->checkEm4X09i->setText(xStringResource::GetVarName(EM4_VAR_X08));    ui->checkEm4X09a->setText(xStringResource::GetVarName(EM4_VAR_X08));
	ui->checkEm4X10p->setText(xStringResource::GetVarName(EM4_VAR_X09));	ui->checkEm4X10i->setText(xStringResource::GetVarName(EM4_VAR_X09));    ui->checkEm4X10a->setText(xStringResource::GetVarName(EM4_VAR_X09));
	ui->checkEm4X11p->setText(xStringResource::GetVarName(EM4_VAR_X10));	ui->checkEm4X11i->setText(xStringResource::GetVarName(EM4_VAR_X10));    ui->checkEm4X11a->setText(xStringResource::GetVarName(EM4_VAR_X10));
	ui->checkEm4X12p->setText(xStringResource::GetVarName(EM4_VAR_X11));	ui->checkEm4X12i->setText(xStringResource::GetVarName(EM4_VAR_X11));    ui->checkEm4X12a->setText(xStringResource::GetVarName(EM4_VAR_X11));
	ui->checkEm4X13p->setText(xStringResource::GetVarName(EM4_VAR_X12));	ui->checkEm4X13i->setText(xStringResource::GetVarName(EM4_VAR_X12));    ui->checkEm4X13a->setText(xStringResource::GetVarName(EM4_VAR_X12));
    ui->checkEm4X14p->setText(xStringResource::GetVarName(EM4_VAR_X13));	ui->checkEm4X14i->setText(xStringResource::GetVarName(EM4_VAR_X13));    ui->checkEm4X14a->setText(xStringResource::GetVarName(EM4_VAR_X13));
    ui->checkEm4X15p->setText(xStringResource::GetVarName(EM4_VAR_X14));	ui->checkEm4X15i->setText(xStringResource::GetVarName(EM4_VAR_X14));    ui->checkEm4X15a->setText(xStringResource::GetVarName(EM4_VAR_X14));
    ui->checkEm4X16p->setText(xStringResource::GetVarName(EM4_VAR_X15));	ui->checkEm4X16i->setText(xStringResource::GetVarName(EM4_VAR_X15));    ui->checkEm4X16a->setText(xStringResource::GetVarName(EM4_VAR_X15));
    // 主控模块扩展输出
    ui->checkMainY00p->setText(xStringResource::GetVarName(MAIN_VAR_Y00));
    ui->checkMainY01p->setText(xStringResource::GetVarName(MAIN_VAR_Y01));
    ui->checkMainY02p->setText(xStringResource::GetVarName(MAIN_VAR_Y02));
    ui->checkMainY03p->setText(xStringResource::GetVarName(MAIN_VAR_Y03));
    ui->checkMainY04p->setText(xStringResource::GetVarName(MAIN_VAR_Y04));
    ui->checkMainY05p->setText(xStringResource::GetVarName(MAIN_VAR_Y05));
    ui->checkMainY06p->setText(xStringResource::GetVarName(MAIN_VAR_Y06));
    ui->checkMainY07p->setText(xStringResource::GetVarName(MAIN_VAR_Y07));
    ui->checkMainY08p->setText(xStringResource::GetVarName(MAIN_VAR_Y08));
    ui->checkMainY09p->setText(xStringResource::GetVarName(MAIN_VAR_Y09));
    ui->checkMainY10p->setText(xStringResource::GetVarName(MAIN_VAR_Y10));
    ui->checkMainY11p->setText(xStringResource::GetVarName(MAIN_VAR_Y11));
    ui->checkMainY12p->setText(xStringResource::GetVarName(MAIN_VAR_Y12));
    ui->checkMainY13p->setText(xStringResource::GetVarName(MAIN_VAR_Y13));
    ui->checkMainY14p->setText(xStringResource::GetVarName(MAIN_VAR_Y14));
    ui->checkMainY15p->setText(xStringResource::GetVarName(MAIN_VAR_Y15));
    ui->checkMainY16p->setText(xStringResource::GetVarName(MAIN_VAR_Y16));
    ui->checkMainY17p->setText(xStringResource::GetVarName(MAIN_VAR_Y17));
    ui->checkMainY18p->setText(xStringResource::GetVarName(MAIN_VAR_Y18));
    ui->checkMainY19p->setText(xStringResource::GetVarName(MAIN_VAR_Y19));
    ui->checkMainY20p->setText(xStringResource::GetVarName(MAIN_VAR_Y20));
    ui->checkMainY21p->setText(xStringResource::GetVarName(MAIN_VAR_Y21));
    ui->checkMainY22p->setText(xStringResource::GetVarName(MAIN_VAR_Y22));
    ui->checkMainY23p->setText(xStringResource::GetVarName(MAIN_VAR_Y23));
    ui->checkMainY24p->setText(xStringResource::GetVarName(MAIN_VAR_Y24));
    ui->checkMainY25p->setText(xStringResource::GetVarName(MAIN_VAR_Y25));
    ui->checkMainY26p->setText(xStringResource::GetVarName(MAIN_VAR_Y26));
    ui->checkMainY27p->setText(xStringResource::GetVarName(MAIN_VAR_Y27));
    ui->checkMainY28p->setText(xStringResource::GetVarName(MAIN_VAR_Y28));
    ui->checkMainY29p->setText(xStringResource::GetVarName(MAIN_VAR_Y29));
    ui->checkMainY30p->setText(xStringResource::GetVarName(MAIN_VAR_Y30));
    ui->checkMainY31p->setText(xStringResource::GetVarName(MAIN_VAR_Y31));
    ui->checkMainY32p->setText(xStringResource::GetVarName(MAIN_VAR_Y32));
    ui->checkMainY33p->setText(xStringResource::GetVarName(MAIN_VAR_Y33));
    ui->checkMainY34p->setText(xStringResource::GetVarName(MAIN_VAR_Y34));
    ui->checkMainY35p->setText(xStringResource::GetVarName(MAIN_VAR_Y35));
    ui->checkMainY36p->setText(xStringResource::GetVarName(MAIN_VAR_Y36));
    ui->checkMainY37p->setText(xStringResource::GetVarName(MAIN_VAR_Y37));
    ui->checkMainY38p->setText(xStringResource::GetVarName(MAIN_VAR_Y38));
    ui->checkMainY39p->setText(xStringResource::GetVarName(MAIN_VAR_Y39));
    ui->checkMainY40p->setText(xStringResource::GetVarName(MAIN_VAR_Y40));
    ui->checkMainY41p->setText(xStringResource::GetVarName(MAIN_VAR_Y41));
    ui->checkMainY42p->setText(xStringResource::GetVarName(MAIN_VAR_Y42));
    ui->checkMainY43p->setText(xStringResource::GetVarName(MAIN_VAR_Y43));
    ui->checkMainY44p->setText(xStringResource::GetVarName(MAIN_VAR_Y44));
    ui->checkMainY45p->setText(xStringResource::GetVarName(MAIN_VAR_Y45));
    ui->checkMainY46p->setText(xStringResource::GetVarName(MAIN_VAR_Y46));
    ui->checkMainY47p->setText(xStringResource::GetVarName(MAIN_VAR_Y47));
    // 模块1扩展输出
    ui->checkEm1Y01p->setText(xStringResource::GetVarName(EM1_VAR_Y00));
    ui->checkEm1Y02p->setText(xStringResource::GetVarName(EM1_VAR_Y01));
    ui->checkEm1Y03p->setText(xStringResource::GetVarName(EM1_VAR_Y02));
    ui->checkEm1Y04p->setText(xStringResource::GetVarName(EM1_VAR_Y03));
    ui->checkEm1Y05p->setText(xStringResource::GetVarName(EM1_VAR_Y04));
    ui->checkEm1Y06p->setText(xStringResource::GetVarName(EM1_VAR_Y05));
    ui->checkEm1Y07p->setText(xStringResource::GetVarName(EM1_VAR_Y06));
    ui->checkEm1Y08p->setText(xStringResource::GetVarName(EM1_VAR_Y07));
    ui->checkEm1Y09p->setText(xStringResource::GetVarName(EM1_VAR_Y08));
    ui->checkEm1Y10p->setText(xStringResource::GetVarName(EM1_VAR_Y09));
    ui->checkEm1Y11p->setText(xStringResource::GetVarName(EM1_VAR_Y10));
    ui->checkEm1Y13p->setText(xStringResource::GetVarName(EM1_VAR_Y12));
    ui->checkEm1Y14p->setText(xStringResource::GetVarName(EM1_VAR_Y13));
    ui->checkEm1Y15p->setText(xStringResource::GetVarName(EM1_VAR_Y14));
    ui->checkEm1Y16p->setText(xStringResource::GetVarName(EM1_VAR_Y15));
    if (pModbus->GetRotateUse())    // 正臂倒角使用
    {
        ui->checkEm1Y01p->setEnabled(false);
        ui->checkEm1Y02p->setEnabled(false);
    }
    else
    {
        ui->checkEm1Y01p->setEnabled(true);
        ui->checkEm1Y02p->setEnabled(true);
    }
    if (pModbus->GetRunnerUse())    // 副臂使用
    {
        ui->checkEm1Y13p->setEnabled(false);
        ui->checkEm1Y14p->setEnabled(false);
    }
    else
    {
        ui->checkEm1Y13p->setEnabled(true);
        ui->checkEm1Y14p->setEnabled(true);
    }
    if (pModbus->GetAdjustUse())    // 气动调位使用
    {
        ui->checkEm1Y15p->setEnabled(false);
        ui->checkEm1Y16p->setEnabled(false);
    }
    else
    {
        ui->checkEm1Y15p->setEnabled(true);
        ui->checkEm1Y16p->setEnabled(true);
    }
    if (pModbus->GetRunRotateUse()) // 气动副臂倒角使用
    {
        ui->checkEm1Y10p->setEnabled(false);
        ui->checkEm1Y11p->setEnabled(false);
    }
    else
    {
        ui->checkEm1Y10p->setEnabled(true);
        ui->checkEm1Y11p->setEnabled(true);
    }
    if (pModbus->GetOilUse())
    {
        ui->checkEm1Y12p->setText(tr("打油-Y12"));
    }
    else
    {
        ui->checkEm1Y12p->setText(xStringResource::GetVarName(EM1_VAR_Y11));
    }
    // 模块2扩展输出
    ui->checkEm2Y01p->setText(xStringResource::GetVarName(EM2_VAR_Y00));
    ui->checkEm2Y02p->setText(xStringResource::GetVarName(EM2_VAR_Y01));
    ui->checkEm2Y03p->setText(xStringResource::GetVarName(EM2_VAR_Y02));
    ui->checkEm2Y04p->setText(xStringResource::GetVarName(EM2_VAR_Y03));
    ui->checkEm2Y05p->setText(xStringResource::GetVarName(EM2_VAR_Y04));
    ui->checkEm2Y06p->setText(xStringResource::GetVarName(EM2_VAR_Y05));
    ui->checkEm2Y07p->setText(xStringResource::GetVarName(EM2_VAR_Y06));
    ui->checkEm2Y08p->setText(xStringResource::GetVarName(EM2_VAR_Y07));
    ui->checkEm2Y09p->setText(xStringResource::GetVarName(EM2_VAR_Y08));
    ui->checkEm2Y10p->setText(xStringResource::GetVarName(EM2_VAR_Y09));
    ui->checkEm2Y11p->setText(xStringResource::GetVarName(EM2_VAR_Y10));
    ui->checkEm2Y12p->setText(xStringResource::GetVarName(EM2_VAR_Y11));
    ui->checkEm2Y13p->setText(xStringResource::GetVarName(EM2_VAR_Y12));
    ui->checkEm2Y14p->setText(xStringResource::GetVarName(EM2_VAR_Y13));
    ui->checkEm2Y15p->setText(xStringResource::GetVarName(EM2_VAR_Y14));
    ui->checkEm2Y16p->setText(xStringResource::GetVarName(EM2_VAR_Y15));
    // 模块3扩展输出
    ui->checkEm3Y01p->setText(xStringResource::GetVarName(EM3_VAR_Y00));
    ui->checkEm3Y02p->setText(xStringResource::GetVarName(EM3_VAR_Y01));
    ui->checkEm3Y03p->setText(xStringResource::GetVarName(EM3_VAR_Y02));
    ui->checkEm3Y04p->setText(xStringResource::GetVarName(EM3_VAR_Y03));
    ui->checkEm3Y05p->setText(xStringResource::GetVarName(EM3_VAR_Y04));
    ui->checkEm3Y06p->setText(xStringResource::GetVarName(EM3_VAR_Y05));
    ui->checkEm3Y07p->setText(xStringResource::GetVarName(EM3_VAR_Y06));
    ui->checkEm3Y08p->setText(xStringResource::GetVarName(EM3_VAR_Y07));
    ui->checkEm3Y09p->setText(xStringResource::GetVarName(EM3_VAR_Y08));
    ui->checkEm3Y10p->setText(xStringResource::GetVarName(EM3_VAR_Y09));
    ui->checkEm3Y11p->setText(xStringResource::GetVarName(EM3_VAR_Y10));
    ui->checkEm3Y12p->setText(xStringResource::GetVarName(EM3_VAR_Y11));
    ui->checkEm3Y13p->setText(xStringResource::GetVarName(EM3_VAR_Y12));
    ui->checkEm3Y14p->setText(xStringResource::GetVarName(EM3_VAR_Y13));
    ui->checkEm3Y15p->setText(xStringResource::GetVarName(EM3_VAR_Y14));
    ui->checkEm3Y16p->setText(xStringResource::GetVarName(EM3_VAR_Y15));
    // 模块4扩展输出
    ui->checkEm4Y01p->setText(xStringResource::GetVarName(EM4_VAR_Y00));
    ui->checkEm4Y02p->setText(xStringResource::GetVarName(EM4_VAR_Y01));
    ui->checkEm4Y03p->setText(xStringResource::GetVarName(EM4_VAR_Y02));
    ui->checkEm4Y04p->setText(xStringResource::GetVarName(EM4_VAR_Y03));
    ui->checkEm4Y05p->setText(xStringResource::GetVarName(EM4_VAR_Y04));
    ui->checkEm4Y06p->setText(xStringResource::GetVarName(EM4_VAR_Y05));
    ui->checkEm4Y07p->setText(xStringResource::GetVarName(EM4_VAR_Y06));
    ui->checkEm4Y08p->setText(xStringResource::GetVarName(EM4_VAR_Y07));
    ui->checkEm4Y09p->setText(xStringResource::GetVarName(EM4_VAR_Y08));
    ui->checkEm4Y10p->setText(xStringResource::GetVarName(EM4_VAR_Y09));
    ui->checkEm4Y11p->setText(xStringResource::GetVarName(EM4_VAR_Y10));
    ui->checkEm4Y12p->setText(xStringResource::GetVarName(EM4_VAR_Y11));
    ui->checkEm4Y13p->setText(xStringResource::GetVarName(EM4_VAR_Y12));
    ui->checkEm4Y14p->setText(xStringResource::GetVarName(EM4_VAR_Y13));
    ui->checkEm4Y15p->setText(xStringResource::GetVarName(EM4_VAR_Y14));
    ui->checkEm4Y16p->setText(xStringResource::GetVarName(EM4_VAR_Y15));
}

bool FormIO::EnterForm(void)
{
    // 检查操作器与主控模块类型匹配
	if (!pModbus->GetTypeMatch())
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_MATE_ERROR));
		return false;
	}
    // 检查用户权限
    if (xPermissions::GetPermissions(PER_SYS_SIGNAL) == false || xPermissions::GetCurrentUser() == xPermissions::Administrator)
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
	// 根据当前用户权限设置界面
	setPermissions();
    ui->tabWidgetIO->setCurrentIndex(0);
    ui->stackedWidgetPolary->setCurrentIndex(0);
       ui->stackedWidgetOutput->setCurrentIndex(0);
       ui->stackedWidgetIgnore->setCurrentIndex(0);
    ui->stackedWidgetNoalm->setCurrentIndex(0);
    // 设置端口名称
    loadPortNames();
    setPortvisible();
    setPortLabel();
    // 连接信号槽
	connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
	// 显示界面
//	show();
	return true;
}
bool FormIO::ExitForm(void)
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
	// 隐藏界面
//	hide();
	return true;
}
// 根据当前用户权限设置界面
void FormIO::setPermissions(void)
{
    // 信号配配置设置权限
    ui->tabWidgetIO->setTabEnabled(TAB_PAGE_POLARITY, xPermissions::GetPermissions(PER_SYS_SIGNAL));
    ui->tabWidgetIO->setTabEnabled(TAB_PAGE_OUTPUT, xPermissions::GetPermissions(PER_SYS_SIGNAL));
    ui->tabWidgetIO->setTabEnabled(TAB_PAGE_IGNORE, xPermissions::GetPermissions(PER_SYS_SIGNAL));
    ui->tabWidgetIO->setTabEnabled(TAB_PAGE_NOALM, xPermissions::GetPermissions(PER_SYS_SIGNAL));
    if (xPermissions::GetCurrentUser() == xPermissions::Administrator)
    {
        ui->tabWidgetIO->setVisible(false);
        ui->BtnOK->setVisible(false);
    }
    else if(xPermissions::GetCurrentUser() == xPermissions::AdvAdministrator || xPermissions::GetCurrentUser() == xPermissions::SuperUser)
    {
        ui->tabWidgetIO->setVisible(true);
        ui->BtnOK->setVisible(true);
    }
}
// 当前登录用户更改槽
void FormIO::userChange(void)
{
	if ((xPermissions::GetPermissions(PER_SYS_NORMAL) == false) || (xPermissions::GetPermissions(PER_SYS_SIGNAL) == false) ||
			(xPermissions::GetPermissions(PER_SYS_RESET) == false) || (xPermissions::GetPermissions(PER_SYS_MAINTAIN) == false))
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
	setPermissions();
}
// 保存参数信号槽
// ************************************************
void FormIO::AcceptSetup(void)
{

    if ((xPermissions::GetPermissions(PER_SYS_NORMAL) == false) && (xPermissions::GetPermissions(PER_SYS_SIGNAL) == false))
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
		return;
	}
	LoadPara();
	if (isModified())
	{
		if (CheckValid() == false)
			return;
		if (SavePara() == false)
			return;
		// 备份系统参数设置
		memcpy(&SysParaBak, &SysPara, sizeof(SystemParameter));
	}
	// 显示保存成功信息
#if UI_SAVED_TIP
	xMessageBox::DoInformation(tr("保存参数"), xStringResource::GetString(STRRES_HAS_SAVED));
#endif
}
void FormIO::IgnorePagePrev(void)
{
    quint8 curPage;
    curPage = ui->stackedWidgetIgnore->currentIndex();
        if (curPage == 0)
            curPage = ui->stackedWidgetIgnore->count() - 1;
        else
            curPage --;
    ui->stackedWidgetIgnore->setCurrentIndex(curPage);
    setPortLabel();
}
void FormIO::PolaryPagePrev(void)
{
    quint8 curPage;
    curPage = ui->stackedWidgetPolary->currentIndex();
        if (curPage == 0)
            curPage = ui->stackedWidgetPolary->count() - 1;
        else
            curPage --;
    ui->stackedWidgetPolary->setCurrentIndex(curPage);
    setPortLabel();
}
void FormIO::NoalmPagePrev(void)
{
    quint8 curPage;
    curPage = ui->stackedWidgetNoalm->currentIndex();
        if (curPage == 0)
            curPage = ui->stackedWidgetNoalm->count() - 1;
        else
            curPage --;
    ui->stackedWidgetNoalm->setCurrentIndex(curPage);
    setPortLabel();
}
void FormIO::OutputPagePrev(void)
{
    quint8 curPage;
    curPage = ui->stackedWidgetOutput->currentIndex();
        if (curPage == 0)
            curPage = ui->stackedWidgetOutput->count() - 1;
        else
            curPage --;
    ui->stackedWidgetOutput->setCurrentIndex(curPage);
    setPortLabel();
}
void FormIO::IgnorePageNext(void)
{
    quint8 curPage;
    curPage = ui->stackedWidgetIgnore->currentIndex();
        if (curPage >= ui->stackedWidgetIgnore->count() - 1)
            curPage = 0;
        else
            curPage ++;
    ui->stackedWidgetIgnore->setCurrentIndex(curPage);
    setPortLabel();
}
void FormIO::PolaryPageNext(void)
{
    quint8 curPage;
    curPage = ui->stackedWidgetPolary->currentIndex();
        if (curPage >= ui->stackedWidgetPolary->count() - 1)
            curPage = 0;
        else
            curPage ++;
    ui->stackedWidgetPolary->setCurrentIndex(curPage);
    setPortLabel();
}
void FormIO::NoalmPageNext(void)
{
    quint8 curPage;
    curPage = ui->stackedWidgetNoalm->currentIndex();
        if (curPage >= ui->stackedWidgetNoalm->count() - 1)
            curPage = 0;
        else
            curPage ++;
    ui->stackedWidgetNoalm->setCurrentIndex(curPage);
    setPortLabel();
}
void FormIO::OutputPageNext(void)
{
    quint8 curPage;
    curPage = ui->stackedWidgetOutput->currentIndex();
        if (curPage >= ui->stackedWidgetOutput->count() - 1)
            curPage = 0;
        else
            curPage ++;
    ui->stackedWidgetOutput->setCurrentIndex(curPage);
    setPortLabel();
}
