#include "dialogportedit.h"
#include "ui_dialogportedit.h"
#include "xconfig.h"
#include <QSettings>
#include "qdebug.h"
#include "cmbprotocol.h"
#include "xioport.h"
#include "xtranslator.h"

DialogPortEdit::DialogPortEdit(QWidget *parent) : QDialog(parent), ui(new Ui::DialogPortEdit)
{
    ui->setupUi(this);
#if defined(Q_WS_QWS)
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
    //    setAttribute(Qt::WA_TranslucentBackground, true);
#endif
    quint8 i;

    retranslateUi();
    //pyq
    //    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        for(i = 0;i <MAX_INPORT_NUM2;i++)
        {
            ui->tableWidget_In->setRowHeight(i,50);
        }
        ui->tableWidget_In->setColumnWidth(0,184);
        ui->tableWidget_In->setColumnWidth(1,230);
        ui->tableWidget_In->setColumnWidth(2,267);

        for(i = 0;i <MAX_OUTPORT_NUM2;i++)
        {
            ui->tableWidget_Out->setRowHeight(i,50);
        }
        ui->tableWidget_Out->setColumnWidth(0,197);
        ui->tableWidget_Out->setColumnWidth(1,208);
        ui->tableWidget_Out->setColumnWidth(2,276);

        ui->tabWidget->setCurrentIndex(0);//默认显示第一页
    }
    //    else
    //    {
    //        for(i = 0;i <MAX_INPORT_NUM;i++)
    //        {
    //            ui->tableWidget_In->setRowHeight(i,50);
    //        }
    //        ui->tableWidget_In->setColumnWidth(0,184);
    //        ui->tableWidget_In->setColumnWidth(1,230);
    //        ui->tableWidget_In->setColumnWidth(2,267);

    //        for(i = 0;i <MAX_OUTPORT_NUM;i++)
    //        {
    //            ui->tableWidget_Out->setRowHeight(i,50);
    //        }
    //        ui->tableWidget_Out->setColumnWidth(0,197);
    //        ui->tableWidget_Out->setColumnWidth(1,208);
    //        ui->tableWidget_Out->setColumnWidth(2,276);

    //        ui->tabWidget->setCurrentIndex(0);//默认显示第一页
    //    }

    QFont font;
    font.setPixelSize(28); // 设置字号为28像素
    for(int i=0;i<ui->tableWidget_Out->rowCount();i++)
    {
        ui->tableWidget_Out->verticalHeaderItem(i)->setFont(font);
    }
    for(int i=0;i<ui->tableWidget_Out->columnCount();i++)
    {
        ui->tableWidget_Out->horizontalHeaderItem(i)->setFont(font);
    }
    for(int i=0;i<ui->tableWidget_In->rowCount();i++)
    {
        ui->tableWidget_In->verticalHeaderItem(i)->setFont(font);
    }
    for(int i=0;i<ui->tableWidget_In->columnCount();i++)
    {
        ui->tableWidget_In->horizontalHeaderItem(i)->setFont(font);
    }
}

DialogPortEdit::~DialogPortEdit()
{
    delete ui;
}

int DialogPortEdit::DoForm()
{
    int i;
    InitInPortName();
    InitOutPortName();
    setIOVisible();
    ui->label->setText("");
    //    for(i = 0; i < MAX_INPORT_NUM; i++)
    //    {
    //        ui->tableWidget_In->item(i,0)->setFlags(Qt::ItemIsEnabled);
    //        ui->tableWidget_In->item(i,1)->setFlags(Qt::ItemIsEnabled);
    //    }
    //    for(i = 0; i < MAX_OUTPORT_NUM; i++)
    //    {
    //        ui->tableWidget_Out->item(i,0)->setFlags(Qt::ItemIsEnabled);
    //        ui->tableWidget_Out->item(i,1)->setFlags(Qt::ItemIsEnabled);
    //    }

    return exec();
}
void DialogPortEdit::retranslateUi(void)
{

}
void DialogPortEdit::InitInPortName()
{
    ui->tabWidget->setTabText(0,tr("扩展输入"));
    ui->tabWidget->setTabText(1,tr("扩展输出"));
    QStringList name;
    name << tr("端口") <<tr("默认名称") <<tr("修改名称");
    ui->tableWidget_In->setHorizontalHeaderLabels(name);
    ui->tableWidget_Out->setHorizontalHeaderLabels(name);
    ui->BtnCancel->setText(tr("关闭"));
    ui->BtnSafe->setText(tr("保存"));
    ui->tableWidget_In->setItem(MAIN_X00,0,new QTableWidgetItem(tr("主板X00")));
    ui->tableWidget_In->setItem(MAIN_X01,0,new QTableWidgetItem(tr("主板X01")));
    ui->tableWidget_In->setItem(MAIN_X02,0,new QTableWidgetItem(tr("主板X02")));
    ui->tableWidget_In->setItem(MAIN_X03,0,new QTableWidgetItem(tr("主板X03")));
    ui->tableWidget_In->setItem(MAIN_X04,0,new QTableWidgetItem(tr("主板X04")));
    ui->tableWidget_In->setItem(MAIN_X05,0,new QTableWidgetItem(tr("主板X05")));
    ui->tableWidget_In->setItem(MAIN_X06,0,new QTableWidgetItem(tr("主板X06")));
    ui->tableWidget_In->setItem(MAIN_X07,0,new QTableWidgetItem(tr("主板X07")));
    ui->tableWidget_In->setItem(MAIN_X08,0,new QTableWidgetItem(tr("主板X08")));
    ui->tableWidget_In->setItem(MAIN_X09,0,new QTableWidgetItem(tr("主板X09")));
    ui->tableWidget_In->setItem(MAIN_X10,0,new QTableWidgetItem(tr("主板X10")));
    ui->tableWidget_In->setItem(MAIN_X11,0,new QTableWidgetItem(tr("主板X11")));
    ui->tableWidget_In->setItem(MAIN_X12,0,new QTableWidgetItem(tr("主板X12")));
    ui->tableWidget_In->setItem(MAIN_X13,0,new QTableWidgetItem(tr("主板X13")));
    ui->tableWidget_In->setItem(MAIN_X14,0,new QTableWidgetItem(tr("主板X14")));
    ui->tableWidget_In->setItem(MAIN_X15,0,new QTableWidgetItem(tr("主板X15")));

    if(CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {        //主板 输入端口号
        //扩展输入
        ui->tableWidget_In->setItem(EM1_X00,0,new QTableWidgetItem(tr("扩展模块1X00")));
        ui->tableWidget_In->setItem(EM1_X01,0,new QTableWidgetItem(tr("扩展模块1X01")));
        ui->tableWidget_In->setItem(EM1_X02,0,new QTableWidgetItem(tr("扩展模块1X02")));
        ui->tableWidget_In->setItem(EM1_X03,0,new QTableWidgetItem(tr("扩展模块1X03")));
        ui->tableWidget_In->setItem(EM1_X04,0,new QTableWidgetItem(tr("扩展模块1X04")));
        ui->tableWidget_In->setItem(EM1_X05,0,new QTableWidgetItem(tr("扩展模块1X05")));
        ui->tableWidget_In->setItem(EM1_X06,0,new QTableWidgetItem(tr("扩展模块1X06")));
        ui->tableWidget_In->setItem(EM1_X07,0,new QTableWidgetItem(tr("扩展模块1X07")));
        ui->tableWidget_In->setItem(EM1_X08,0,new QTableWidgetItem(tr("扩展模块1X08")));
        ui->tableWidget_In->setItem(EM1_X09,0,new QTableWidgetItem(tr("扩展模块1X09")));
        ui->tableWidget_In->setItem(EM1_X10,0,new QTableWidgetItem(tr("扩展模块1X10")));
        ui->tableWidget_In->setItem(EM1_X11,0,new QTableWidgetItem(tr("扩展模块1X11")));
        ui->tableWidget_In->setItem(EM1_X12,0,new QTableWidgetItem(tr("扩展模块1X12")));
        ui->tableWidget_In->setItem(EM1_X13,0,new QTableWidgetItem(tr("扩展模块1X13")));
        ui->tableWidget_In->setItem(EM1_X14,0,new QTableWidgetItem(tr("扩展模块1X14")));
        ui->tableWidget_In->setItem(EM1_X15,0,new QTableWidgetItem(tr("扩展模块1X15")));

        ui->tableWidget_In->setItem(EM2_X00,0,new QTableWidgetItem(tr("扩展模块2X00")));
        ui->tableWidget_In->setItem(EM2_X01,0,new QTableWidgetItem(tr("扩展模块2X01")));
        ui->tableWidget_In->setItem(EM2_X02,0,new QTableWidgetItem(tr("扩展模块2X02")));
        ui->tableWidget_In->setItem(EM2_X03,0,new QTableWidgetItem(tr("扩展模块2X03")));
        ui->tableWidget_In->setItem(EM2_X04,0,new QTableWidgetItem(tr("扩展模块2X04")));
        ui->tableWidget_In->setItem(EM2_X05,0,new QTableWidgetItem(tr("扩展模块2X05")));
        ui->tableWidget_In->setItem(EM2_X06,0,new QTableWidgetItem(tr("扩展模块2X06")));
        ui->tableWidget_In->setItem(EM2_X07,0,new QTableWidgetItem(tr("扩展模块2X07")));
        ui->tableWidget_In->setItem(EM2_X08,0,new QTableWidgetItem(tr("扩展模块2X08")));
        ui->tableWidget_In->setItem(EM2_X09,0,new QTableWidgetItem(tr("扩展模块2X09")));
        ui->tableWidget_In->setItem(EM2_X10,0,new QTableWidgetItem(tr("扩展模块2X10")));
        ui->tableWidget_In->setItem(EM2_X11,0,new QTableWidgetItem(tr("扩展模块2X11")));
        ui->tableWidget_In->setItem(EM2_X12,0,new QTableWidgetItem(tr("扩展模块2X12")));
        ui->tableWidget_In->setItem(EM2_X13,0,new QTableWidgetItem(tr("扩展模块2X13")));
        ui->tableWidget_In->setItem(EM2_X14,0,new QTableWidgetItem(tr("扩展模块2X14")));
        ui->tableWidget_In->setItem(EM2_X15,0,new QTableWidgetItem(tr("扩展模块2X15")));

        ui->tableWidget_In->setItem(EM3_X00,0,new QTableWidgetItem(tr("扩展模块3X00")));
        ui->tableWidget_In->setItem(EM3_X01,0,new QTableWidgetItem(tr("扩展模块3X01")));
        ui->tableWidget_In->setItem(EM3_X02,0,new QTableWidgetItem(tr("扩展模块3X02")));
        ui->tableWidget_In->setItem(EM3_X03,0,new QTableWidgetItem(tr("扩展模块3X03")));
        ui->tableWidget_In->setItem(EM3_X04,0,new QTableWidgetItem(tr("扩展模块3X04")));
        ui->tableWidget_In->setItem(EM3_X05,0,new QTableWidgetItem(tr("扩展模块3X05")));
        ui->tableWidget_In->setItem(EM3_X06,0,new QTableWidgetItem(tr("扩展模块3X06")));
        ui->tableWidget_In->setItem(EM3_X07,0,new QTableWidgetItem(tr("扩展模块3X07")));
        ui->tableWidget_In->setItem(EM3_X08,0,new QTableWidgetItem(tr("扩展模块3X08")));
        ui->tableWidget_In->setItem(EM3_X09,0,new QTableWidgetItem(tr("扩展模块3X09")));
        ui->tableWidget_In->setItem(EM3_X10,0,new QTableWidgetItem(tr("扩展模块3X10")));
        ui->tableWidget_In->setItem(EM3_X11,0,new QTableWidgetItem(tr("扩展模块3X11")));
        ui->tableWidget_In->setItem(EM3_X12,0,new QTableWidgetItem(tr("扩展模块3X12")));
        ui->tableWidget_In->setItem(EM3_X13,0,new QTableWidgetItem(tr("扩展模块3X13")));
        ui->tableWidget_In->setItem(EM3_X14,0,new QTableWidgetItem(tr("扩展模块3X14")));
        ui->tableWidget_In->setItem(EM3_X15,0,new QTableWidgetItem(tr("扩展模块3X15")));

        ui->tableWidget_In->setItem(EM4_X00,0,new QTableWidgetItem(tr("扩展模块4X00")));
        ui->tableWidget_In->setItem(EM4_X01,0,new QTableWidgetItem(tr("扩展模块4X01")));
        ui->tableWidget_In->setItem(EM4_X02,0,new QTableWidgetItem(tr("扩展模块4X02")));
        ui->tableWidget_In->setItem(EM4_X03,0,new QTableWidgetItem(tr("扩展模块4X03")));
        ui->tableWidget_In->setItem(EM4_X04,0,new QTableWidgetItem(tr("扩展模块4X04")));
        ui->tableWidget_In->setItem(EM4_X05,0,new QTableWidgetItem(tr("扩展模块4X05")));
        ui->tableWidget_In->setItem(EM4_X06,0,new QTableWidgetItem(tr("扩展模块4X06")));
        ui->tableWidget_In->setItem(EM4_X07,0,new QTableWidgetItem(tr("扩展模块4X07")));
        ui->tableWidget_In->setItem(EM4_X08,0,new QTableWidgetItem(tr("扩展模块4X08")));
        ui->tableWidget_In->setItem(EM4_X09,0,new QTableWidgetItem(tr("扩展模块4X09")));
        ui->tableWidget_In->setItem(EM4_X10,0,new QTableWidgetItem(tr("扩展模块4X10")));
        ui->tableWidget_In->setItem(EM4_X11,0,new QTableWidgetItem(tr("扩展模块4X11")));
        ui->tableWidget_In->setItem(EM4_X12,0,new QTableWidgetItem(tr("扩展模块4X12")));
        ui->tableWidget_In->setItem(EM4_X13,0,new QTableWidgetItem(tr("扩展模块4X13")));
        ui->tableWidget_In->setItem(EM4_X14,0,new QTableWidgetItem(tr("扩展模块4X14")));
        ui->tableWidget_In->setItem(EM4_X15,0,new QTableWidgetItem(tr("扩展模块4X15")));
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        //pyq 端口号
        //主板 输入端口号
        //扩展输入
        ui->tableWidget_In->setItem(EM1_X00,0,new QTableWidgetItem(QString::fromUtf8("主板X16")));
        ui->tableWidget_In->setItem(EM1_X01,0,new QTableWidgetItem(QString::fromUtf8("主板X17")));
        ui->tableWidget_In->setItem(EM1_X02,0,new QTableWidgetItem(QString::fromUtf8("主板X18")));
        ui->tableWidget_In->setItem(EM1_X03,0,new QTableWidgetItem(QString::fromUtf8("主板X19")));
        ui->tableWidget_In->setItem(EM1_X04,0,new QTableWidgetItem(QString::fromUtf8("主板X20")));
        ui->tableWidget_In->setItem(EM1_X05,0,new QTableWidgetItem(QString::fromUtf8("主板X21")));
        ui->tableWidget_In->setItem(EM1_X06,0,new QTableWidgetItem(QString::fromUtf8("主板X22")));
        ui->tableWidget_In->setItem(EM1_X07,0,new QTableWidgetItem(QString::fromUtf8("主板X23")));
        ui->tableWidget_In->setItem(EM1_X08,0,new QTableWidgetItem(QString::fromUtf8("主板X24")));
        ui->tableWidget_In->setItem(EM1_X09,0,new QTableWidgetItem(QString::fromUtf8("主板X25")));
        ui->tableWidget_In->setItem(EM1_X10,0,new QTableWidgetItem(QString::fromUtf8("主板X26")));
        ui->tableWidget_In->setItem(EM1_X11,0,new QTableWidgetItem(QString::fromUtf8("主板X27")));

        ui->tableWidget_In->setItem(EM1_X12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X00")));
        ui->tableWidget_In->setItem(EM1_X13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X01")));
        ui->tableWidget_In->setItem(EM1_X14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X02")));
        ui->tableWidget_In->setItem(EM1_X15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X03")));
        ui->tableWidget_In->setItem(EM2_X00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X04")));
        ui->tableWidget_In->setItem(EM2_X01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X05")));
        ui->tableWidget_In->setItem(EM2_X02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X06")));
        ui->tableWidget_In->setItem(EM2_X03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X07")));
        ui->tableWidget_In->setItem(EM2_X04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X08")));
        ui->tableWidget_In->setItem(EM2_X05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X09")));
        ui->tableWidget_In->setItem(EM2_X06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X10")));
        ui->tableWidget_In->setItem(EM2_X07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X11")));
        ui->tableWidget_In->setItem(EM2_X08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X12")));
        ui->tableWidget_In->setItem(EM2_X09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X13")));
        ui->tableWidget_In->setItem(EM2_X10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X14")));
        ui->tableWidget_In->setItem(EM2_X11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X15")));

        ui->tableWidget_In->setItem(EM2_X12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X00")));
        ui->tableWidget_In->setItem(EM2_X13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X01")));
        ui->tableWidget_In->setItem(EM2_X14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X02")));
        ui->tableWidget_In->setItem(EM2_X15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X03")));
        ui->tableWidget_In->setItem(EM3_X00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X04")));
        ui->tableWidget_In->setItem(EM3_X01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X05")));
        ui->tableWidget_In->setItem(EM3_X02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X06")));
        ui->tableWidget_In->setItem(EM3_X03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X07")));
        ui->tableWidget_In->setItem(EM3_X04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X08")));
        ui->tableWidget_In->setItem(EM3_X05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X09")));
        ui->tableWidget_In->setItem(EM3_X06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X10")));
        ui->tableWidget_In->setItem(EM3_X07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X11")));
        ui->tableWidget_In->setItem(EM3_X08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X12")));
        ui->tableWidget_In->setItem(EM3_X09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X13")));
        ui->tableWidget_In->setItem(EM3_X10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X14")));
        ui->tableWidget_In->setItem(EM3_X11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X15")));

        ui->tableWidget_In->setItem(EM3_X12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X00")));
        ui->tableWidget_In->setItem(EM3_X13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X01")));
        ui->tableWidget_In->setItem(EM3_X14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X02")));
        ui->tableWidget_In->setItem(EM3_X15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X03")));
        ui->tableWidget_In->setItem(EM4_X00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X04")));
        ui->tableWidget_In->setItem(EM4_X01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X05")));
        ui->tableWidget_In->setItem(EM4_X02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X06")));
        ui->tableWidget_In->setItem(EM4_X03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X07")));
        ui->tableWidget_In->setItem(EM4_X04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X08")));
        ui->tableWidget_In->setItem(EM4_X05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X09")));
        ui->tableWidget_In->setItem(EM4_X06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X10")));
        ui->tableWidget_In->setItem(EM4_X07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X11")));
        ui->tableWidget_In->setItem(EM4_X08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X12")));
        ui->tableWidget_In->setItem(EM4_X09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X13")));
        ui->tableWidget_In->setItem(EM4_X10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X14")));
        ui->tableWidget_In->setItem(EM4_X11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X15")));

        ui->tableWidget_In->setItem(EM4_X12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X00")));
        ui->tableWidget_In->setItem(EM4_X13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X01")));
        ui->tableWidget_In->setItem(EM4_X14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X02")));
        ui->tableWidget_In->setItem(EM4_X15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X03")));
        ui->tableWidget_In->setItem(MAIN_X16,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X04")));
        ui->tableWidget_In->setItem(MAIN_X17,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X05")));
        ui->tableWidget_In->setItem(MAIN_X18,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X06")));
        ui->tableWidget_In->setItem(MAIN_X19,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X07")));
        ui->tableWidget_In->setItem(MAIN_X20,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X08")));
        ui->tableWidget_In->setItem(MAIN_X21,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X09")));
        ui->tableWidget_In->setItem(MAIN_X22,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X10")));
        ui->tableWidget_In->setItem(MAIN_X23,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X11")));
        ui->tableWidget_In->setItem(MAIN_X24,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X12")));
        ui->tableWidget_In->setItem(MAIN_X25,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X13")));
        ui->tableWidget_In->setItem(MAIN_X26,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X14")));
        ui->tableWidget_In->setItem(MAIN_X27,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X15")));
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        //pyq 端口号
        //主板 输入端口号
        //扩展输入
        ui->tableWidget_In->setItem(EM1_X00,0,new QTableWidgetItem(QString::fromUtf8("主板X16")));
        ui->tableWidget_In->setItem(EM1_X01,0,new QTableWidgetItem(QString::fromUtf8("主板X17")));
        ui->tableWidget_In->setItem(EM1_X02,0,new QTableWidgetItem(QString::fromUtf8("主板X18")));
        ui->tableWidget_In->setItem(EM1_X03,0,new QTableWidgetItem(QString::fromUtf8("主板X19")));
        ui->tableWidget_In->setItem(EM1_X04,0,new QTableWidgetItem(QString::fromUtf8("主板X20")));
        ui->tableWidget_In->setItem(EM1_X05,0,new QTableWidgetItem(QString::fromUtf8("主板X21")));
        ui->tableWidget_In->setItem(EM1_X06,0,new QTableWidgetItem(QString::fromUtf8("主板X22")));
        ui->tableWidget_In->setItem(EM1_X07,0,new QTableWidgetItem(QString::fromUtf8("主板X23")));
        ui->tableWidget_In->setItem(EM1_X08,0,new QTableWidgetItem(QString::fromUtf8("主板X24")));
        ui->tableWidget_In->setItem(EM1_X09,0,new QTableWidgetItem(QString::fromUtf8("主板X25")));
        ui->tableWidget_In->setItem(EM1_X10,0,new QTableWidgetItem(QString::fromUtf8("主板X26")));
        ui->tableWidget_In->setItem(EM1_X11,0,new QTableWidgetItem(QString::fromUtf8("主板X27")));

        ui->tableWidget_In->setItem(EM1_X12,0,new QTableWidgetItem(QString::fromUtf8("主板X28")));
        ui->tableWidget_In->setItem(EM1_X13,0,new QTableWidgetItem(QString::fromUtf8("主板X29")));
        ui->tableWidget_In->setItem(EM1_X14,0,new QTableWidgetItem(QString::fromUtf8("主板X30")));
        ui->tableWidget_In->setItem(EM1_X15,0,new QTableWidgetItem(QString::fromUtf8("主板X31")));
        ui->tableWidget_In->setItem(EM2_X00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X00")));
        ui->tableWidget_In->setItem(EM2_X01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X01")));
        ui->tableWidget_In->setItem(EM2_X02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X02")));
        ui->tableWidget_In->setItem(EM2_X03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X03")));
        ui->tableWidget_In->setItem(EM2_X04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X04")));
        ui->tableWidget_In->setItem(EM2_X05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X05")));
        ui->tableWidget_In->setItem(EM2_X06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X06")));
        ui->tableWidget_In->setItem(EM2_X07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X07")));
        ui->tableWidget_In->setItem(EM2_X08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X08")));
        ui->tableWidget_In->setItem(EM2_X09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X09")));
        ui->tableWidget_In->setItem(EM2_X10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X10")));
        ui->tableWidget_In->setItem(EM2_X11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X11")));

        ui->tableWidget_In->setItem(EM2_X12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X12")));
        ui->tableWidget_In->setItem(EM2_X13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X13")));
        ui->tableWidget_In->setItem(EM2_X14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X14")));
        ui->tableWidget_In->setItem(EM2_X15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1X15")));
        ui->tableWidget_In->setItem(EM3_X00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X00")));
        ui->tableWidget_In->setItem(EM3_X01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X01")));
        ui->tableWidget_In->setItem(EM3_X02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X02")));
        ui->tableWidget_In->setItem(EM3_X03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X03")));
        ui->tableWidget_In->setItem(EM3_X04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X04")));
        ui->tableWidget_In->setItem(EM3_X05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X05")));
        ui->tableWidget_In->setItem(EM3_X06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X06")));
        ui->tableWidget_In->setItem(EM3_X07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X07")));
        ui->tableWidget_In->setItem(EM3_X08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X08")));
        ui->tableWidget_In->setItem(EM3_X09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X09")));
        ui->tableWidget_In->setItem(EM3_X10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X10")));
        ui->tableWidget_In->setItem(EM3_X11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X11")));

        ui->tableWidget_In->setItem(EM3_X12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X12")));
        ui->tableWidget_In->setItem(EM3_X13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X13")));
        ui->tableWidget_In->setItem(EM3_X14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X14")));
        ui->tableWidget_In->setItem(EM3_X15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2X15")));
        ui->tableWidget_In->setItem(EM4_X00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X00")));
        ui->tableWidget_In->setItem(EM4_X01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X01")));
        ui->tableWidget_In->setItem(EM4_X02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X02")));
        ui->tableWidget_In->setItem(EM4_X03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X03")));
        ui->tableWidget_In->setItem(EM4_X04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X04")));
        ui->tableWidget_In->setItem(EM4_X05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X05")));
        ui->tableWidget_In->setItem(EM4_X06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X06")));
        ui->tableWidget_In->setItem(EM4_X07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X07")));
        ui->tableWidget_In->setItem(EM4_X08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X08")));
        ui->tableWidget_In->setItem(EM4_X09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X09")));
        ui->tableWidget_In->setItem(EM4_X10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X10")));
        ui->tableWidget_In->setItem(EM4_X11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X11")));

        ui->tableWidget_In->setItem(EM4_X12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X12")));
        ui->tableWidget_In->setItem(EM4_X13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X13")));
        ui->tableWidget_In->setItem(EM4_X14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X14")));
        ui->tableWidget_In->setItem(EM4_X15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3X15")));
        ui->tableWidget_In->setItem(MAIN_X16,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X00")));
        ui->tableWidget_In->setItem(MAIN_X17,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X01")));
        ui->tableWidget_In->setItem(MAIN_X18,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X02")));
        ui->tableWidget_In->setItem(MAIN_X19,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X03")));
        ui->tableWidget_In->setItem(MAIN_X20,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X04")));
        ui->tableWidget_In->setItem(MAIN_X21,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X05")));
        ui->tableWidget_In->setItem(MAIN_X22,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X06")));
        ui->tableWidget_In->setItem(MAIN_X23,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X07")));
        ui->tableWidget_In->setItem(MAIN_X24,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X08")));
        ui->tableWidget_In->setItem(MAIN_X25,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X09")));
        ui->tableWidget_In->setItem(MAIN_X26,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X10")));
        ui->tableWidget_In->setItem(MAIN_X27,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X11")));
        ui->tableWidget_In->setItem(MAIN_X28,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X12")));
        ui->tableWidget_In->setItem(MAIN_X29,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X13")));
        ui->tableWidget_In->setItem(MAIN_X30,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X14")));
        ui->tableWidget_In->setItem(MAIN_X31,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4X15")));
    }
    else
    {
        //扩展输入
        ui->tableWidget_In->setItem(EM1_X00,0,new QTableWidgetItem(tr("扩展模块1X01")));
        ui->tableWidget_In->setItem(EM1_X01,0,new QTableWidgetItem(tr("扩展模块1X02")));
        ui->tableWidget_In->setItem(EM1_X02,0,new QTableWidgetItem(tr("扩展模块1X03")));
        ui->tableWidget_In->setItem(EM1_X03,0,new QTableWidgetItem(tr("扩展模块1X04")));
        ui->tableWidget_In->setItem(EM1_X04,0,new QTableWidgetItem(tr("扩展模块1X05")));
        ui->tableWidget_In->setItem(EM1_X05,0,new QTableWidgetItem(tr("扩展模块1X06")));
        ui->tableWidget_In->setItem(EM1_X06,0,new QTableWidgetItem(tr("扩展模块1X07")));
        ui->tableWidget_In->setItem(EM1_X07,0,new QTableWidgetItem(tr("扩展模块1X08")));
        ui->tableWidget_In->setItem(EM1_X08,0,new QTableWidgetItem(tr("扩展模块1X09")));
        ui->tableWidget_In->setItem(EM1_X09,0,new QTableWidgetItem(tr("扩展模块1X10")));
        ui->tableWidget_In->setItem(EM1_X10,0,new QTableWidgetItem(tr("扩展模块1X11")));
        ui->tableWidget_In->setItem(EM1_X11,0,new QTableWidgetItem(tr("扩展模块1X12")));
        ui->tableWidget_In->setItem(EM1_X12,0,new QTableWidgetItem(tr("扩展模块1X13")));
        ui->tableWidget_In->setItem(EM1_X13,0,new QTableWidgetItem(tr("扩展模块1X14")));
        ui->tableWidget_In->setItem(EM1_X14,0,new QTableWidgetItem(tr("扩展模块1X15")));
        ui->tableWidget_In->setItem(EM1_X15,0,new QTableWidgetItem(tr("扩展模块1X16")));

        ui->tableWidget_In->setItem(EM2_X00,0,new QTableWidgetItem(tr("扩展模块2X01")));
        ui->tableWidget_In->setItem(EM2_X01,0,new QTableWidgetItem(tr("扩展模块2X02")));
        ui->tableWidget_In->setItem(EM2_X02,0,new QTableWidgetItem(tr("扩展模块2X03")));
        ui->tableWidget_In->setItem(EM2_X03,0,new QTableWidgetItem(tr("扩展模块2X04")));
        ui->tableWidget_In->setItem(EM2_X04,0,new QTableWidgetItem(tr("扩展模块2X05")));
        ui->tableWidget_In->setItem(EM2_X05,0,new QTableWidgetItem(tr("扩展模块2X06")));
        ui->tableWidget_In->setItem(EM2_X06,0,new QTableWidgetItem(tr("扩展模块2X07")));
        ui->tableWidget_In->setItem(EM2_X07,0,new QTableWidgetItem(tr("扩展模块2X08")));
        ui->tableWidget_In->setItem(EM2_X08,0,new QTableWidgetItem(tr("扩展模块2X09")));
        ui->tableWidget_In->setItem(EM2_X09,0,new QTableWidgetItem(tr("扩展模块2X10")));
        ui->tableWidget_In->setItem(EM2_X10,0,new QTableWidgetItem(tr("扩展模块2X11")));
        ui->tableWidget_In->setItem(EM2_X11,0,new QTableWidgetItem(tr("扩展模块2X12")));
        ui->tableWidget_In->setItem(EM2_X12,0,new QTableWidgetItem(tr("扩展模块2X13")));
        ui->tableWidget_In->setItem(EM2_X13,0,new QTableWidgetItem(tr("扩展模块2X14")));
        ui->tableWidget_In->setItem(EM2_X14,0,new QTableWidgetItem(tr("扩展模块2X15")));
        ui->tableWidget_In->setItem(EM2_X15,0,new QTableWidgetItem(tr("扩展模块2X16")));

        ui->tableWidget_In->setItem(EM3_X00,0,new QTableWidgetItem(tr("扩展模块3X01")));
        ui->tableWidget_In->setItem(EM3_X01,0,new QTableWidgetItem(tr("扩展模块3X02")));
        ui->tableWidget_In->setItem(EM3_X02,0,new QTableWidgetItem(tr("扩展模块3X03")));
        ui->tableWidget_In->setItem(EM3_X03,0,new QTableWidgetItem(tr("扩展模块3X04")));
        ui->tableWidget_In->setItem(EM3_X04,0,new QTableWidgetItem(tr("扩展模块3X05")));
        ui->tableWidget_In->setItem(EM3_X05,0,new QTableWidgetItem(tr("扩展模块3X06")));
        ui->tableWidget_In->setItem(EM3_X06,0,new QTableWidgetItem(tr("扩展模块3X07")));
        ui->tableWidget_In->setItem(EM3_X07,0,new QTableWidgetItem(tr("扩展模块3X08")));
        ui->tableWidget_In->setItem(EM3_X08,0,new QTableWidgetItem(tr("扩展模块3X09")));
        ui->tableWidget_In->setItem(EM3_X09,0,new QTableWidgetItem(tr("扩展模块3X10")));
        ui->tableWidget_In->setItem(EM3_X10,0,new QTableWidgetItem(tr("扩展模块3X11")));
        ui->tableWidget_In->setItem(EM3_X11,0,new QTableWidgetItem(tr("扩展模块3X12")));
        ui->tableWidget_In->setItem(EM3_X12,0,new QTableWidgetItem(tr("扩展模块3X13")));
        ui->tableWidget_In->setItem(EM3_X13,0,new QTableWidgetItem(tr("扩展模块3X14")));
        ui->tableWidget_In->setItem(EM3_X14,0,new QTableWidgetItem(tr("扩展模块3X15")));
        ui->tableWidget_In->setItem(EM3_X15,0,new QTableWidgetItem(tr("扩展模块3X16")));

        ui->tableWidget_In->setItem(EM4_X00,0,new QTableWidgetItem(tr("扩展模块4X01")));
        ui->tableWidget_In->setItem(EM4_X01,0,new QTableWidgetItem(tr("扩展模块4X02")));
        ui->tableWidget_In->setItem(EM4_X02,0,new QTableWidgetItem(tr("扩展模块4X03")));
        ui->tableWidget_In->setItem(EM4_X03,0,new QTableWidgetItem(tr("扩展模块4X04")));
        ui->tableWidget_In->setItem(EM4_X04,0,new QTableWidgetItem(tr("扩展模块4X05")));
        ui->tableWidget_In->setItem(EM4_X05,0,new QTableWidgetItem(tr("扩展模块4X06")));
        ui->tableWidget_In->setItem(EM4_X06,0,new QTableWidgetItem(tr("扩展模块4X07")));
        ui->tableWidget_In->setItem(EM4_X07,0,new QTableWidgetItem(tr("扩展模块4X08")));
        ui->tableWidget_In->setItem(EM4_X08,0,new QTableWidgetItem(tr("扩展模块4X09")));
        ui->tableWidget_In->setItem(EM4_X09,0,new QTableWidgetItem(tr("扩展模块4X10")));
        ui->tableWidget_In->setItem(EM4_X10,0,new QTableWidgetItem(tr("扩展模块4X11")));
        ui->tableWidget_In->setItem(EM4_X11,0,new QTableWidgetItem(tr("扩展模块4X12")));
        ui->tableWidget_In->setItem(EM4_X12,0,new QTableWidgetItem(tr("扩展模块4X13")));
        ui->tableWidget_In->setItem(EM4_X13,0,new QTableWidgetItem(tr("扩展模块4X14")));
        ui->tableWidget_In->setItem(EM4_X14,0,new QTableWidgetItem(tr("扩展模块4X15")));
        ui->tableWidget_In->setItem(EM4_X15,0,new QTableWidgetItem(tr("扩展模块4X16")));
        /*    // 注塑机输入
        ui->tableWidget_In->setItem(IMM_IN_STOP,0,new QTableWidgetItem(tr("注塑机STOP")));
        ui->tableWidget_In->setItem(IMM_IN_SAFE,0,new QTableWidgetItem(tr("注塑机SAFE")));
        ui->tableWidget_In->setItem(IMM_IN_REJECT,0,new QTableWidgetItem(tr("注塑机REJECT")));
        ui->tableWidget_In->setItem(IMM_IN_MCP,0,new QTableWidgetItem(tr("注塑机MCP")));
        ui->tableWidget_In->setItem(IMM_IN_MOP,0,new QTableWidgetItem(tr("注塑机MOP")));
        ui->tableWidget_In->setItem(IMM_IN_IMOP,0,new QTableWidgetItem(tr("注塑机IMOP")));
        ui->tableWidget_In->setItem(IMM_IN_AUTO,0,new QTableWidgetItem(tr("注塑机AUTO")));
        ui->tableWidget_In->setItem(IMM_IN_EBP,0,new QTableWidgetItem(tr("注塑机EBP")));
        ui->tableWidget_In->setItem(IMM_IN_EFP,0,new QTableWidgetItem(tr("注塑机EFP")));
        ui->tableWidget_In->setItem(IMM_IN_MID,0,new QTableWidgetItem(tr("注塑机MID")));
        ui->tableWidget_In->setItem(IMM_IN_C1P1,0,new QTableWidgetItem(tr("注塑机C1P1")));
        ui->tableWidget_In->setItem(IMM_IN_C1P2,0,new QTableWidgetItem(tr("注塑机C1P2")));
        ui->tableWidget_In->setItem(IMM_IN_C2P1,0,new QTableWidgetItem(tr("注塑机C2P1")));
        ui->tableWidget_In->setItem(IMM_IN_C2P2,0,new QTableWidgetItem(tr("注塑机C2P2")));

        // 机械手输入
        ui->tableWidget_In->setItem(RBT_IN_LOW_AIR,0,new QTableWidgetItem(tr("机械手LOW_AIR")));
        ui->tableWidget_In->setItem(RBT_IN_DWN_SAF,0,new QTableWidgetItem(tr("机械手DWN_SAF")));
        ui->tableWidget_In->setItem(RBT_IN_PRO_HOR,0,new QTableWidgetItem(tr("机械手PRO_HOR")));
        ui->tableWidget_In->setItem(RBT_IN_PRO_VER,0,new QTableWidgetItem(tr("机械手PRO_VER")));
        ui->tableWidget_In->setItem(RBT_IN_ARM_SAF,0,new QTableWidgetItem(tr("机械手ARM_SAF")));
        ui->tableWidget_In->setItem(RBT_IN_RUN_ASC,0,new QTableWidgetItem(tr("机械手RUN_ASC")));
        ui->tableWidget_In->setItem(RBT_IN_RUN_DES,0,new QTableWidgetItem(tr("机械手RUN_DES")));
        ui->tableWidget_In->setItem(RBT_IN_PRO_ADV,0,new QTableWidgetItem(tr("机械手PRO_ADV")));
        ui->tableWidget_In->setItem(RBT_IN_PRO_RET,0,new QTableWidgetItem(tr("机械手PRO_RET")));
        ui->tableWidget_In->setItem(RBT_IN_RUN_ADV,0,new QTableWidgetItem(tr("机械手RUN_ADV")));
        ui->tableWidget_In->setItem(RBT_IN_RUN_RET,0,new QTableWidgetItem(tr("机械手RUN_RET")));
        ui->tableWidget_In->setItem(RBT_IN_RUN_HOR,0,new QTableWidgetItem(tr("机械手RUN_HOR")));
        ui->tableWidget_In->setItem(RBT_IN_RUN_VER,0,new QTableWidgetItem(tr("机械手RUN_VER")));*/
    }
    //-------------------------------------------------------------------------------------------

    //主板默认名称
    //pyq
    if(CMBProtocol::GetSysTypeHigh()==BOARD_VERSION_H750_5AXIS)
    {
        ui->tableWidget_In->setItem(MAIN_X00,1,new QTableWidgetItem(QString::fromUtf8("Main-X00")));
        ui->tableWidget_In->setItem(MAIN_X01,1,new QTableWidgetItem(QString::fromUtf8("Main-X01")));
        ui->tableWidget_In->setItem(MAIN_X02,1,new QTableWidgetItem(QString::fromUtf8("Main-X02")));
        ui->tableWidget_In->setItem(MAIN_X03,1,new QTableWidgetItem(QString::fromUtf8("Main-X03")));
        ui->tableWidget_In->setItem(MAIN_X04,1,new QTableWidgetItem(QString::fromUtf8("Main-X04")));
        ui->tableWidget_In->setItem(MAIN_X05,1,new QTableWidgetItem(QString::fromUtf8("Main-X05")));
        ui->tableWidget_In->setItem(MAIN_X06,1,new QTableWidgetItem(QString::fromUtf8("Main-X06")));
        ui->tableWidget_In->setItem(MAIN_X07,1,new QTableWidgetItem(QString::fromUtf8("Main-X07")));
        ui->tableWidget_In->setItem(MAIN_X08,1,new QTableWidgetItem(QString::fromUtf8("Main-X08")));
        ui->tableWidget_In->setItem(MAIN_X09,1,new QTableWidgetItem(QString::fromUtf8("Main-X09")));
        ui->tableWidget_In->setItem(MAIN_X10,1,new QTableWidgetItem(QString::fromUtf8("Main-X10")));
        ui->tableWidget_In->setItem(MAIN_X11,1,new QTableWidgetItem(QString::fromUtf8("Main-X11")));
        ui->tableWidget_In->setItem(MAIN_X12,1,new QTableWidgetItem(tr("吸具1-X12")));
        ui->tableWidget_In->setItem(MAIN_X13,1,new QTableWidgetItem(tr("夹具1-X13")));
        ui->tableWidget_In->setItem(MAIN_X14,1,new QTableWidgetItem(QString::fromUtf8("吸具1-X14")));
        ui->tableWidget_In->setItem(MAIN_X15,1,new QTableWidgetItem(QString::fromUtf8("吸具2-X15")));
    }
    if(CMBProtocol::GetSysTypeHigh()==BOARD_VERSION_H750_DVS)
    {
        ui->tableWidget_In->setItem(MAIN_X00,1,new QTableWidgetItem(QString::fromUtf8("Main-X00")));
        ui->tableWidget_In->setItem(MAIN_X01,1,new QTableWidgetItem(QString::fromUtf8("Main-X01")));
        ui->tableWidget_In->setItem(MAIN_X02,1,new QTableWidgetItem(QString::fromUtf8("Main-X02")));
        ui->tableWidget_In->setItem(MAIN_X03,1,new QTableWidgetItem(QString::fromUtf8("Main-X03")));
        ui->tableWidget_In->setItem(MAIN_X04,1,new QTableWidgetItem(QString::fromUtf8("Main-X04")));
        ui->tableWidget_In->setItem(MAIN_X05,1,new QTableWidgetItem(QString::fromUtf8("Main-X05")));
        ui->tableWidget_In->setItem(MAIN_X06,1,new QTableWidgetItem(QString::fromUtf8("Main-X06")));
        ui->tableWidget_In->setItem(MAIN_X07,1,new QTableWidgetItem(QString::fromUtf8("Main-X07")));
        ui->tableWidget_In->setItem(MAIN_X08,1,new QTableWidgetItem(QString::fromUtf8("吸具1-X08")));
        ui->tableWidget_In->setItem(MAIN_X09,1,new QTableWidgetItem(QString::fromUtf8("吸具2-X09")));
        ui->tableWidget_In->setItem(MAIN_X10,1,new QTableWidgetItem(QString::fromUtf8("抱具1-X10")));
        ui->tableWidget_In->setItem(MAIN_X11,1,new QTableWidgetItem(QString::fromUtf8("抱具2-X11")));
        ui->tableWidget_In->setItem(MAIN_X12,1,new QTableWidgetItem(QString::fromUtf8("抱具3-X12")));
        ui->tableWidget_In->setItem(MAIN_X13,1,new QTableWidgetItem(QString::fromUtf8("抱具4-X13")));
        ui->tableWidget_In->setItem(MAIN_X14,1,new QTableWidgetItem(QString::fromUtf8("Main-X14")));
        ui->tableWidget_In->setItem(MAIN_X15,1,new QTableWidgetItem(QString::fromUtf8("Main-X15")));
    }
    else
    {
        ui->tableWidget_In->setItem(MAIN_X00,1,new QTableWidgetItem(QString::fromUtf8("Main-X00")));
        ui->tableWidget_In->setItem(MAIN_X01,1,new QTableWidgetItem(QString::fromUtf8("Main-X01")));
        ui->tableWidget_In->setItem(MAIN_X02,1,new QTableWidgetItem(QString::fromUtf8("Main-X02")));
        ui->tableWidget_In->setItem(MAIN_X03,1,new QTableWidgetItem(QString::fromUtf8("Main-X03")));
        ui->tableWidget_In->setItem(MAIN_X04,1,new QTableWidgetItem(QString::fromUtf8("Main-X04")));
        ui->tableWidget_In->setItem(MAIN_X05,1,new QTableWidgetItem(QString::fromUtf8("Main-X05")));
        ui->tableWidget_In->setItem(MAIN_X06,1,new QTableWidgetItem(QString::fromUtf8("Main-X06")));
        ui->tableWidget_In->setItem(MAIN_X07,1,new QTableWidgetItem(QString::fromUtf8("Main-X07")));
        ui->tableWidget_In->setItem(MAIN_X08,1,new QTableWidgetItem(QString::fromUtf8("Main-X08")));
        ui->tableWidget_In->setItem(MAIN_X09,1,new QTableWidgetItem(QString::fromUtf8("Main-X09")));
        ui->tableWidget_In->setItem(MAIN_X10,1,new QTableWidgetItem(QString::fromUtf8("Main-X10")));
        ui->tableWidget_In->setItem(MAIN_X11,1,new QTableWidgetItem(QString::fromUtf8("Main-X11")));
        ui->tableWidget_In->setItem(MAIN_X12,1,new QTableWidgetItem(tr("吸具1-X12")));
        ui->tableWidget_In->setItem(MAIN_X13,1,new QTableWidgetItem(tr("夹具1-X13")));
        ui->tableWidget_In->setItem(MAIN_X14,1,new QTableWidgetItem(tr("抱具1-X14")));
        ui->tableWidget_In->setItem(MAIN_X15,1,new QTableWidgetItem(QString::fromUtf8("Main-X15")));
    }

    //扩展1
    //        if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    //        {
    //            ui->tableWidget_In->setItem(EM1_X00,1,new QTableWidgetItem(QString::fromUtf8("EM1-X01")));
    //            ui->tableWidget_In->setItem(EM1_X01,1,new QTableWidgetItem(QString::fromUtf8("EM1-X02")));
    //            ui->tableWidget_In->setItem(EM1_X02,1,new QTableWidgetItem(QString::fromUtf8("EM1-X03")));
    //            ui->tableWidget_In->setItem(EM1_X03,1,new QTableWidgetItem(QString::fromUtf8("爪手产品检知1-X04")));
    //            ui->tableWidget_In->setItem(EM1_X04,1,new QTableWidgetItem(QString::fromUtf8("爪手产品检知2-X05")));
    //            ui->tableWidget_In->setItem(EM1_X05,1,new QTableWidgetItem(QString::fromUtf8("备用-X06")));
    //            ui->tableWidget_In->setItem(EM1_X06,1,new QTableWidgetItem(QString::fromUtf8("备用-X07")));
    //            ui->tableWidget_In->setItem(EM1_X07,1,new QTableWidgetItem(QString::fromUtf8("EM1-X08")));
    //            ui->tableWidget_In->setItem(EM1_X08,1,new QTableWidgetItem(QString::fromUtf8("EM1-X09")));
    //            ui->tableWidget_In->setItem(EM1_X09,1,new QTableWidgetItem(QString::fromUtf8("压铸完成-X10")));
    //            ui->tableWidget_In->setItem(EM1_X10,1,new QTableWidgetItem(QString::fromUtf8("EM1-X11")));
    //            ui->tableWidget_In->setItem(EM1_X11,1,new QTableWidgetItem(QString::fromUtf8("EM1-X12")));
    //            ui->tableWidget_In->setItem(EM1_X12,1,new QTableWidgetItem(QString::fromUtf8("EM1-X13")));
    //            ui->tableWidget_In->setItem(EM1_X13,1,new QTableWidgetItem(QString::fromUtf8("EM1-X14")));
    //            ui->tableWidget_In->setItem(EM1_X14,1,new QTableWidgetItem(QString::fromUtf8("EM1-X15")));
    //            ui->tableWidget_In->setItem(EM1_X15,1,new QTableWidgetItem(QString::fromUtf8("EM1-X16")));
    //        }
    //        else if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    //        {

    //            ui->tableWidget_In->setItem(EM1_X00,1,new QTableWidgetItem(QString::fromUtf8("EM1-X00")));
    //            ui->tableWidget_In->setItem(EM1_X01,1,new QTableWidgetItem(QString::fromUtf8("EM1-X01")));
    //            ui->tableWidget_In->setItem(EM1_X02,1,new QTableWidgetItem(QString::fromUtf8("EM1-X02")));
    //            ui->tableWidget_In->setItem(EM1_X03,1,new QTableWidgetItem(QString::fromUtf8("EM1-X03")));
    //            ui->tableWidget_In->setItem(EM1_X04,1,new QTableWidgetItem(QString::fromUtf8("EM1-X04")));
    //            ui->tableWidget_In->setItem(EM1_X05,1,new QTableWidgetItem(QString::fromUtf8("EM1-X05")));
    //            ui->tableWidget_In->setItem(EM1_X06,1,new QTableWidgetItem(QString::fromUtf8("EM1-X06")));
    //            ui->tableWidget_In->setItem(EM1_X07,1,new QTableWidgetItem(QString::fromUtf8("EM1-X07")));
    //            ui->tableWidget_In->setItem(EM1_X08,1,new QTableWidgetItem(QString::fromUtf8("EM1-X08")));
    //            ui->tableWidget_In->setItem(EM1_X09,1,new QTableWidgetItem(QString::fromUtf8("EM1-X09")));
    //            ui->tableWidget_In->setItem(EM1_X10,1,new QTableWidgetItem(QString::fromUtf8("EM1-X10")));
    //            ui->tableWidget_In->setItem(EM1_X11,1,new QTableWidgetItem(QString::fromUtf8("EM1-X11")));
    //            ui->tableWidget_In->setItem(EM1_X12,1,new QTableWidgetItem(QString::fromUtf8("EM1-X12")));
    //            ui->tableWidget_In->setItem(EM1_X13,1,new QTableWidgetItem(QString::fromUtf8("EM1-X13")));
    //            ui->tableWidget_In->setItem(EM1_X14,1,new QTableWidgetItem(QString::fromUtf8("EM1-X14")));
    //            ui->tableWidget_In->setItem(EM1_X15,1,new QTableWidgetItem(QString::fromUtf8("EM1-X15")));
    //            //扩展2
    //            ui->tableWidget_In->setItem(EM2_X00,1,new QTableWidgetItem(QString::fromUtf8("EM2-X00")));
    //            ui->tableWidget_In->setItem(EM2_X01,1,new QTableWidgetItem(QString::fromUtf8("EM2-X01")));
    //            ui->tableWidget_In->setItem(EM2_X02,1,new QTableWidgetItem(QString::fromUtf8("EM2-X02")));
    //            ui->tableWidget_In->setItem(EM2_X03,1,new QTableWidgetItem(QString::fromUtf8("EM2-X03")));
    //            ui->tableWidget_In->setItem(EM2_X04,1,new QTableWidgetItem(QString::fromUtf8("EM2-X04")));
    //            ui->tableWidget_In->setItem(EM2_X05,1,new QTableWidgetItem(QString::fromUtf8("EM2-X05")));
    //            ui->tableWidget_In->setItem(EM2_X06,1,new QTableWidgetItem(QString::fromUtf8("EM2-X06")));
    //            ui->tableWidget_In->setItem(EM2_X07,1,new QTableWidgetItem(QString::fromUtf8("EM2-X07")));
    //            ui->tableWidget_In->setItem(EM2_X08,1,new QTableWidgetItem(QString::fromUtf8("EM2-X08")));
    //            ui->tableWidget_In->setItem(EM2_X09,1,new QTableWidgetItem(QString::fromUtf8("EM2-X09")));
    //            ui->tableWidget_In->setItem(EM2_X10,1,new QTableWidgetItem(QString::fromUtf8("EM2-X10")));
    //            ui->tableWidget_In->setItem(EM2_X11,1,new QTableWidgetItem(QString::fromUtf8("EM2-X11")));
    //            ui->tableWidget_In->setItem(EM2_X12,1,new QTableWidgetItem(QString::fromUtf8("EM2-X12")));
    //            ui->tableWidget_In->setItem(EM2_X13,1,new QTableWidgetItem(QString::fromUtf8("EM2-X13")));
    //            ui->tableWidget_In->setItem(EM2_X14,1,new QTableWidgetItem(QString::fromUtf8("EM2-X14")));
    //            ui->tableWidget_In->setItem(EM2_X15,1,new QTableWidgetItem(QString::fromUtf8("EM2-X15")));
    //            //扩展3
    //            ui->tableWidget_In->setItem(EM3_X00,1,new QTableWidgetItem(QString::fromUtf8("EM3-X00")));
    //            ui->tableWidget_In->setItem(EM3_X01,1,new QTableWidgetItem(QString::fromUtf8("EM3-X01")));
    //            ui->tableWidget_In->setItem(EM3_X02,1,new QTableWidgetItem(QString::fromUtf8("EM3-X02")));
    //            ui->tableWidget_In->setItem(EM3_X03,1,new QTableWidgetItem(QString::fromUtf8("EM3-X03")));
    //            ui->tableWidget_In->setItem(EM3_X04,1,new QTableWidgetItem(QString::fromUtf8("EM3-X04")));
    //            ui->tableWidget_In->setItem(EM3_X05,1,new QTableWidgetItem(QString::fromUtf8("EM3-X05")));
    //            ui->tableWidget_In->setItem(EM3_X06,1,new QTableWidgetItem(QString::fromUtf8("EM3-X06")));
    //            ui->tableWidget_In->setItem(EM3_X07,1,new QTableWidgetItem(QString::fromUtf8("EM3-X07")));
    //            ui->tableWidget_In->setItem(EM3_X08,1,new QTableWidgetItem(QString::fromUtf8("EM3-X08")));
    //            ui->tableWidget_In->setItem(EM3_X09,1,new QTableWidgetItem(QString::fromUtf8("EM3-X09")));
    //            ui->tableWidget_In->setItem(EM3_X10,1,new QTableWidgetItem(QString::fromUtf8("EM3-X10")));
    //            ui->tableWidget_In->setItem(EM3_X11,1,new QTableWidgetItem(QString::fromUtf8("EM3-X11")));
    //            ui->tableWidget_In->setItem(EM3_X12,1,new QTableWidgetItem(QString::fromUtf8("EM3-X12")));
    //            ui->tableWidget_In->setItem(EM3_X13,1,new QTableWidgetItem(QString::fromUtf8("EM3-X13")));
    //            ui->tableWidget_In->setItem(EM3_X14,1,new QTableWidgetItem(QString::fromUtf8("EM3-X14")));
    //            ui->tableWidget_In->setItem(EM3_X15,1,new QTableWidgetItem(QString::fromUtf8("EM3-X15")));
    //            //扩展4
    //            ui->tableWidget_In->setItem(EM4_X00,1,new QTableWidgetItem(QString::fromUtf8("EM4-X00")));
    //            ui->tableWidget_In->setItem(EM4_X01,1,new QTableWidgetItem(QString::fromUtf8("EM4-X01")));
    //            ui->tableWidget_In->setItem(EM4_X02,1,new QTableWidgetItem(QString::fromUtf8("EM4-X02")));
    //            ui->tableWidget_In->setItem(EM4_X03,1,new QTableWidgetItem(QString::fromUtf8("EM4-X03")));
    //            ui->tableWidget_In->setItem(EM4_X04,1,new QTableWidgetItem(QString::fromUtf8("EM4-X04")));
    //            ui->tableWidget_In->setItem(EM4_X05,1,new QTableWidgetItem(QString::fromUtf8("EM4-X05")));
    //            ui->tableWidget_In->setItem(EM4_X06,1,new QTableWidgetItem(QString::fromUtf8("EM4-X06")));
    //            ui->tableWidget_In->setItem(EM4_X07,1,new QTableWidgetItem(QString::fromUtf8("EM4-X07")));
    //            ui->tableWidget_In->setItem(EM4_X08,1,new QTableWidgetItem(QString::fromUtf8("EM4-X08")));
    //            ui->tableWidget_In->setItem(EM4_X09,1,new QTableWidgetItem(QString::fromUtf8("EM4-X09")));
    //            ui->tableWidget_In->setItem(EM4_X10,1,new QTableWidgetItem(QString::fromUtf8("EM4-X10")));
    //            ui->tableWidget_In->setItem(EM4_X11,1,new QTableWidgetItem(QString::fromUtf8("EM4-X11")));
    //            ui->tableWidget_In->setItem(EM4_X12,1,new QTableWidgetItem(QString::fromUtf8("EM4-X12")));
    //            ui->tableWidget_In->setItem(EM4_X13,1,new QTableWidgetItem(QString::fromUtf8("EM4-X13")));
    //            ui->tableWidget_In->setItem(EM4_X14,1,new QTableWidgetItem(QString::fromUtf8("EM4-X14")));
    //            ui->tableWidget_In->setItem(EM4_X15,1,new QTableWidgetItem(QString::fromUtf8("EM4-X15")));
    //        }
    //pyq 默认名称
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        ui->tableWidget_In->setItem(EM1_X00,1,new QTableWidgetItem(QString::fromUtf8("抱具1-X16")));
        ui->tableWidget_In->setItem(EM1_X01,1,new QTableWidgetItem(QString::fromUtf8("抱具2-X17")));
        ui->tableWidget_In->setItem(EM1_X02,1,new QTableWidgetItem(QString::fromUtf8("抱具3-X18")));
        ui->tableWidget_In->setItem(EM1_X03,1,new QTableWidgetItem(QString::fromUtf8("抱具4-X19")));
        ui->tableWidget_In->setItem(EM1_X04,1,new QTableWidgetItem(QString::fromUtf8("Main-X20")));
#if (FACTORY == FA_BEISHITE_CN)
        ui->tableWidget_In->setItem(EM1_X05,1,new QTableWidgetItem(QString::fromUtf8("副臂夹-X21")));
#else
        ui->tableWidget_In->setItem(EM1_X05,1,new QTableWidgetItem(QString::fromUtf8("Main-X21")));
#endif
        ui->tableWidget_In->setItem(EM1_X06,1,new QTableWidgetItem(QString::fromUtf8("Main-X22")));
        ui->tableWidget_In->setItem(EM1_X07,1,new QTableWidgetItem(QString::fromUtf8("Main-X23")));
        ui->tableWidget_In->setItem(EM1_X08,1,new QTableWidgetItem(QString::fromUtf8("Main-X24")));
        ui->tableWidget_In->setItem(EM1_X09,1,new QTableWidgetItem(QString::fromUtf8("Main-X25")));
#if (FACTORY == FA_BEISHITE_CN)
        ui->tableWidget_In->setItem(EM1_X10,1,new QTableWidgetItem(QString::fromUtf8("吸3-X26")));
        ui->tableWidget_In->setItem(EM1_X11,1,new QTableWidgetItem(QString::fromUtf8("吸4-X27")));
#else
        ui->tableWidget_In->setItem(EM1_X10,1,new QTableWidgetItem(QString::fromUtf8("Main-X26")));
        ui->tableWidget_In->setItem(EM1_X11,1,new QTableWidgetItem(QString::fromUtf8("Main-X27")));
#endif

        ui->tableWidget_In->setItem(EM1_X12,1,new QTableWidgetItem(QString::fromUtf8("EM1-X01")));
        ui->tableWidget_In->setItem(EM1_X13,1,new QTableWidgetItem(QString::fromUtf8("EM1-X02")));
        ui->tableWidget_In->setItem(EM1_X14,1,new QTableWidgetItem(QString::fromUtf8("吸具1-X03")));
        ui->tableWidget_In->setItem(EM1_X15,1,new QTableWidgetItem(QString::fromUtf8("吸具2-X04")));
        ui->tableWidget_In->setItem(EM2_X00,1,new QTableWidgetItem(QString::fromUtf8("抱具1-X05")));
        ui->tableWidget_In->setItem(EM2_X01,1,new QTableWidgetItem(QString::fromUtf8("抱具2-X06")));
        ui->tableWidget_In->setItem(EM2_X02,1,new QTableWidgetItem(QString::fromUtf8("抱具3-X07")));
        ui->tableWidget_In->setItem(EM2_X03,1,new QTableWidgetItem(QString::fromUtf8("抱具4-X08")));
        ui->tableWidget_In->setItem(EM2_X04,1,new QTableWidgetItem(QString::fromUtf8("EM1-X09")));
        ui->tableWidget_In->setItem(EM2_X05,1,new QTableWidgetItem(QString::fromUtf8("EM1-X10")));
        ui->tableWidget_In->setItem(EM2_X06,1,new QTableWidgetItem(QString::fromUtf8("EM1-X11")));
        ui->tableWidget_In->setItem(EM2_X07,1,new QTableWidgetItem(QString::fromUtf8("EM1-X12")));
        ui->tableWidget_In->setItem(EM2_X08,1,new QTableWidgetItem(QString::fromUtf8("EM1-X13")));
        ui->tableWidget_In->setItem(EM2_X09,1,new QTableWidgetItem(QString::fromUtf8("EM1-X14")));
        ui->tableWidget_In->setItem(EM2_X10,1,new QTableWidgetItem(QString::fromUtf8("EM1-X15")));
        ui->tableWidget_In->setItem(EM2_X11,1,new QTableWidgetItem(QString::fromUtf8("EM1-X16")));
        //扩展2
        ui->tableWidget_In->setItem(EM2_X12,1,new QTableWidgetItem(QString::fromUtf8("EM2-X01")));
        ui->tableWidget_In->setItem(EM2_X13,1,new QTableWidgetItem(QString::fromUtf8("EM2-X02")));
        ui->tableWidget_In->setItem(EM2_X14,1,new QTableWidgetItem(QString::fromUtf8("EM2-X03")));
        ui->tableWidget_In->setItem(EM2_X15,1,new QTableWidgetItem(QString::fromUtf8("EM2-X04")));
        ui->tableWidget_In->setItem(EM3_X00,1,new QTableWidgetItem(QString::fromUtf8("EM2-X05")));
        ui->tableWidget_In->setItem(EM3_X01,1,new QTableWidgetItem(QString::fromUtf8("EM2-X06")));
        ui->tableWidget_In->setItem(EM3_X02,1,new QTableWidgetItem(QString::fromUtf8("EM2-X07")));
        ui->tableWidget_In->setItem(EM3_X03,1,new QTableWidgetItem(QString::fromUtf8("EM2-X08")));
        ui->tableWidget_In->setItem(EM3_X04,1,new QTableWidgetItem(QString::fromUtf8("EM2-X09")));
        ui->tableWidget_In->setItem(EM3_X05,1,new QTableWidgetItem(QString::fromUtf8("EM2-X10")));
        ui->tableWidget_In->setItem(EM3_X06,1,new QTableWidgetItem(QString::fromUtf8("EM2-X11")));
        ui->tableWidget_In->setItem(EM3_X07,1,new QTableWidgetItem(QString::fromUtf8("EM2-X12")));
        ui->tableWidget_In->setItem(EM3_X08,1,new QTableWidgetItem(QString::fromUtf8("EM2-X13")));
        ui->tableWidget_In->setItem(EM3_X09,1,new QTableWidgetItem(QString::fromUtf8("EM2-X14")));
        ui->tableWidget_In->setItem(EM3_X10,1,new QTableWidgetItem(QString::fromUtf8("EM2-X15")));
        ui->tableWidget_In->setItem(EM3_X11,1,new QTableWidgetItem(QString::fromUtf8("EM2-X16")));
        //扩展3
        ui->tableWidget_In->setItem(EM3_X12,1,new QTableWidgetItem(QString::fromUtf8("EM3-X01")));
        ui->tableWidget_In->setItem(EM3_X13,1,new QTableWidgetItem(QString::fromUtf8("EM3-X02")));
        ui->tableWidget_In->setItem(EM3_X14,1,new QTableWidgetItem(QString::fromUtf8("EM3-X03")));
        ui->tableWidget_In->setItem(EM3_X15,1,new QTableWidgetItem(QString::fromUtf8("EM3-X04")));
        ui->tableWidget_In->setItem(EM4_X00,1,new QTableWidgetItem(QString::fromUtf8("EM3-X05")));
        ui->tableWidget_In->setItem(EM4_X01,1,new QTableWidgetItem(QString::fromUtf8("EM3-X06")));
        ui->tableWidget_In->setItem(EM4_X02,1,new QTableWidgetItem(QString::fromUtf8("EM3-X07")));
        ui->tableWidget_In->setItem(EM4_X03,1,new QTableWidgetItem(QString::fromUtf8("EM3-X08")));
        ui->tableWidget_In->setItem(EM4_X04,1,new QTableWidgetItem(QString::fromUtf8("EM3-X09")));
        ui->tableWidget_In->setItem(EM4_X05,1,new QTableWidgetItem(QString::fromUtf8("EM3-X10")));
        ui->tableWidget_In->setItem(EM4_X06,1,new QTableWidgetItem(QString::fromUtf8("EM3-X11")));
        ui->tableWidget_In->setItem(EM4_X07,1,new QTableWidgetItem(QString::fromUtf8("EM3-X12")));
        ui->tableWidget_In->setItem(EM4_X08,1,new QTableWidgetItem(QString::fromUtf8("EM3-X13")));
        ui->tableWidget_In->setItem(EM4_X09,1,new QTableWidgetItem(QString::fromUtf8("EM3-X14")));
        ui->tableWidget_In->setItem(EM4_X10,1,new QTableWidgetItem(QString::fromUtf8("EM3-X15")));
        ui->tableWidget_In->setItem(EM4_X11,1,new QTableWidgetItem(QString::fromUtf8("EM3-X16")));
        //扩展4
        ui->tableWidget_In->setItem(EM4_X12,1,new QTableWidgetItem(QString::fromUtf8("EM4-X01")));
        ui->tableWidget_In->setItem(EM4_X13,1,new QTableWidgetItem(QString::fromUtf8("EM4-X02")));
        ui->tableWidget_In->setItem(EM4_X14,1,new QTableWidgetItem(QString::fromUtf8("EM4-X03")));
        ui->tableWidget_In->setItem(EM4_X15,1,new QTableWidgetItem(QString::fromUtf8("EM4-X04")));
        ui->tableWidget_In->setItem(MAIN_X16,1,new QTableWidgetItem(QString::fromUtf8("EM4-X05")));
        ui->tableWidget_In->setItem(MAIN_X17,1,new QTableWidgetItem(QString::fromUtf8("EM4-X06")));
        ui->tableWidget_In->setItem(MAIN_X18,1,new QTableWidgetItem(QString::fromUtf8("EM4-X07")));
        ui->tableWidget_In->setItem(MAIN_X19,1,new QTableWidgetItem(QString::fromUtf8("EM4-X08")));
        ui->tableWidget_In->setItem(MAIN_X20,1,new QTableWidgetItem(QString::fromUtf8("EM4-X09")));
        ui->tableWidget_In->setItem(MAIN_X21,1,new QTableWidgetItem(QString::fromUtf8("EM4-X10")));
        ui->tableWidget_In->setItem(MAIN_X22,1,new QTableWidgetItem(QString::fromUtf8("EM4-X11")));
        ui->tableWidget_In->setItem(MAIN_X23,1,new QTableWidgetItem(QString::fromUtf8("EM4-X12")));
        ui->tableWidget_In->setItem(MAIN_X24,1,new QTableWidgetItem(QString::fromUtf8("EM4-X13")));
        ui->tableWidget_In->setItem(MAIN_X25,1,new QTableWidgetItem(QString::fromUtf8("EM4-X14")));
        ui->tableWidget_In->setItem(MAIN_X26,1,new QTableWidgetItem(QString::fromUtf8("EM4-X15")));
        ui->tableWidget_In->setItem(MAIN_X27,1,new QTableWidgetItem(QString::fromUtf8("EM4-X16")));
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        ui->tableWidget_In->setItem(EM1_X00,1,new QTableWidgetItem(QString::fromUtf8("Main-X16")));
        ui->tableWidget_In->setItem(EM1_X01,1,new QTableWidgetItem(QString::fromUtf8("Main-X17")));
        ui->tableWidget_In->setItem(EM1_X02,1,new QTableWidgetItem(QString::fromUtf8("Main-X18")));
        ui->tableWidget_In->setItem(EM1_X03,1,new QTableWidgetItem(QString::fromUtf8("Main-X19")));
        ui->tableWidget_In->setItem(EM1_X04,1,new QTableWidgetItem(QString::fromUtf8("Main-X20")));
        ui->tableWidget_In->setItem(EM1_X05,1,new QTableWidgetItem(QString::fromUtf8("打油-X21")));
        ui->tableWidget_In->setItem(EM1_X06,1,new QTableWidgetItem(QString::fromUtf8("低气压-X22")));
        ui->tableWidget_In->setItem(EM1_X07,1,new QTableWidgetItem(QString::fromUtf8("横行模内安全-X23")));
        ui->tableWidget_In->setItem(EM1_X08,1,new QTableWidgetItem(QString::fromUtf8("前进安全-X24")));
        ui->tableWidget_In->setItem(EM1_X09,1,new QTableWidgetItem(QString::fromUtf8("模外下行安全检测-X25")));
        ui->tableWidget_In->setItem(EM1_X10,1,new QTableWidgetItem(QString::fromUtf8("引拔原点-X26")));
        ui->tableWidget_In->setItem(EM1_X11,1,new QTableWidgetItem(QString::fromUtf8("上下原点-X27")));
        ui->tableWidget_In->setItem(EM1_X12,1,new QTableWidgetItem(QString::fromUtf8("横行原点-X28")));
        ui->tableWidget_In->setItem(EM1_X13,1,new QTableWidgetItem(QString::fromUtf8("副上下(倒角)-X29")));
        ui->tableWidget_In->setItem(EM1_X14,1,new QTableWidgetItem(QString::fromUtf8("副引拔(旋转)-X30")));
        ui->tableWidget_In->setItem(EM1_X15,1,new QTableWidgetItem(QString::fromUtf8("Main-X31")));

        ui->tableWidget_In->setItem(EM2_X00,1,new QTableWidgetItem(QString::fromUtf8("EM1-X01")));
        ui->tableWidget_In->setItem(EM2_X01,1,new QTableWidgetItem(QString::fromUtf8("EM1-X02")));
        ui->tableWidget_In->setItem(EM2_X02,1,new QTableWidgetItem(QString::fromUtf8("吸具1-X03")));
        ui->tableWidget_In->setItem(EM2_X03,1,new QTableWidgetItem(QString::fromUtf8("吸具2-X04")));
        ui->tableWidget_In->setItem(EM2_X04,1,new QTableWidgetItem(QString::fromUtf8("抱具1-X05")));
        ui->tableWidget_In->setItem(EM2_X05,1,new QTableWidgetItem(QString::fromUtf8("抱具2-X06")));
        ui->tableWidget_In->setItem(EM2_X06,1,new QTableWidgetItem(QString::fromUtf8("抱具3-X07")));
        ui->tableWidget_In->setItem(EM2_X07,1,new QTableWidgetItem(QString::fromUtf8("抱具4-X08")));
        ui->tableWidget_In->setItem(EM2_X08,1,new QTableWidgetItem(QString::fromUtf8("EM1-X09")));
        ui->tableWidget_In->setItem(EM2_X09,1,new QTableWidgetItem(QString::fromUtf8("EM1-X10")));
        ui->tableWidget_In->setItem(EM2_X10,1,new QTableWidgetItem(QString::fromUtf8("EM1-X11")));
        ui->tableWidget_In->setItem(EM2_X11,1,new QTableWidgetItem(QString::fromUtf8("EM1-X12")));
        ui->tableWidget_In->setItem(EM2_X12,1,new QTableWidgetItem(QString::fromUtf8("EM1-X13")));
        ui->tableWidget_In->setItem(EM2_X13,1,new QTableWidgetItem(QString::fromUtf8("EM1-X14")));
        ui->tableWidget_In->setItem(EM2_X14,1,new QTableWidgetItem(QString::fromUtf8("EM1-X15")));
        ui->tableWidget_In->setItem(EM2_X15,1,new QTableWidgetItem(QString::fromUtf8("EM1-X16")));
        //扩展2
        ui->tableWidget_In->setItem(EM3_X00,1,new QTableWidgetItem(QString::fromUtf8("EM2-X01")));
        ui->tableWidget_In->setItem(EM3_X01,1,new QTableWidgetItem(QString::fromUtf8("EM2-X02")));
        ui->tableWidget_In->setItem(EM3_X02,1,new QTableWidgetItem(QString::fromUtf8("EM2-X03")));
        ui->tableWidget_In->setItem(EM3_X03,1,new QTableWidgetItem(QString::fromUtf8("EM2-X04")));
        ui->tableWidget_In->setItem(EM3_X04,1,new QTableWidgetItem(QString::fromUtf8("EM2-X05")));
        ui->tableWidget_In->setItem(EM3_X05,1,new QTableWidgetItem(QString::fromUtf8("EM2-X06")));
        ui->tableWidget_In->setItem(EM3_X06,1,new QTableWidgetItem(QString::fromUtf8("EM2-X07")));
        ui->tableWidget_In->setItem(EM3_X07,1,new QTableWidgetItem(QString::fromUtf8("EM2-X08")));
        ui->tableWidget_In->setItem(EM3_X08,1,new QTableWidgetItem(QString::fromUtf8("EM2-X09")));
        ui->tableWidget_In->setItem(EM3_X09,1,new QTableWidgetItem(QString::fromUtf8("EM2-X10")));
        ui->tableWidget_In->setItem(EM3_X10,1,new QTableWidgetItem(QString::fromUtf8("EM2-X11")));
        ui->tableWidget_In->setItem(EM3_X11,1,new QTableWidgetItem(QString::fromUtf8("EM2-X12")));
        ui->tableWidget_In->setItem(EM3_X12,1,new QTableWidgetItem(QString::fromUtf8("EM2-X13")));
        ui->tableWidget_In->setItem(EM3_X13,1,new QTableWidgetItem(QString::fromUtf8("EM2-X14")));
        ui->tableWidget_In->setItem(EM3_X14,1,new QTableWidgetItem(QString::fromUtf8("EM2-X15")));
        ui->tableWidget_In->setItem(EM3_X15,1,new QTableWidgetItem(QString::fromUtf8("EM2-X16")));
        //扩展3
        ui->tableWidget_In->setItem(EM4_X00,1,new QTableWidgetItem(QString::fromUtf8("EM3-X01")));
        ui->tableWidget_In->setItem(EM4_X01,1,new QTableWidgetItem(QString::fromUtf8("EM3-X02")));
        ui->tableWidget_In->setItem(EM4_X02,1,new QTableWidgetItem(QString::fromUtf8("EM3-X03")));
        ui->tableWidget_In->setItem(EM4_X03,1,new QTableWidgetItem(QString::fromUtf8("EM3-X04")));
        ui->tableWidget_In->setItem(EM4_X04,1,new QTableWidgetItem(QString::fromUtf8("EM3-X05")));
        ui->tableWidget_In->setItem(EM4_X05,1,new QTableWidgetItem(QString::fromUtf8("EM3-X06")));
        ui->tableWidget_In->setItem(EM4_X06,1,new QTableWidgetItem(QString::fromUtf8("EM3-X07")));
        ui->tableWidget_In->setItem(EM4_X07,1,new QTableWidgetItem(QString::fromUtf8("EM3-X08")));
        ui->tableWidget_In->setItem(EM4_X08,1,new QTableWidgetItem(QString::fromUtf8("EM3-X09")));
        ui->tableWidget_In->setItem(EM4_X09,1,new QTableWidgetItem(QString::fromUtf8("EM3-X10")));
        ui->tableWidget_In->setItem(EM4_X10,1,new QTableWidgetItem(QString::fromUtf8("EM3-X11")));
        ui->tableWidget_In->setItem(EM4_X11,1,new QTableWidgetItem(QString::fromUtf8("EM3-X12")));
        ui->tableWidget_In->setItem(EM4_X12,1,new QTableWidgetItem(QString::fromUtf8("EM3-X13")));
        ui->tableWidget_In->setItem(EM4_X13,1,new QTableWidgetItem(QString::fromUtf8("EM3-X14")));
        ui->tableWidget_In->setItem(EM4_X14,1,new QTableWidgetItem(QString::fromUtf8("EM3-X15")));
        ui->tableWidget_In->setItem(EM4_X15,1,new QTableWidgetItem(QString::fromUtf8("EM3-X16")));
        //扩展4
        ui->tableWidget_In->setItem(MAIN_X16,1,new QTableWidgetItem(QString::fromUtf8("EM4-X01")));
        ui->tableWidget_In->setItem(MAIN_X17,1,new QTableWidgetItem(QString::fromUtf8("EM4-X02")));
        ui->tableWidget_In->setItem(MAIN_X18,1,new QTableWidgetItem(QString::fromUtf8("EM4-X03")));
        ui->tableWidget_In->setItem(MAIN_X19,1,new QTableWidgetItem(QString::fromUtf8("EM4-X04")));
        ui->tableWidget_In->setItem(MAIN_X20,1,new QTableWidgetItem(QString::fromUtf8("EM4-X05")));
        ui->tableWidget_In->setItem(MAIN_X21,1,new QTableWidgetItem(QString::fromUtf8("EM4-X06")));
        ui->tableWidget_In->setItem(MAIN_X22,1,new QTableWidgetItem(QString::fromUtf8("EM4-X07")));
        ui->tableWidget_In->setItem(MAIN_X23,1,new QTableWidgetItem(QString::fromUtf8("EM4-X08")));
        ui->tableWidget_In->setItem(MAIN_X24,1,new QTableWidgetItem(QString::fromUtf8("EM4-X09")));
        ui->tableWidget_In->setItem(MAIN_X25,1,new QTableWidgetItem(QString::fromUtf8("EM4-X10")));
        ui->tableWidget_In->setItem(MAIN_X26,1,new QTableWidgetItem(QString::fromUtf8("EM4-X11")));
        ui->tableWidget_In->setItem(MAIN_X27,1,new QTableWidgetItem(QString::fromUtf8("EM4-X12")));
        ui->tableWidget_In->setItem(MAIN_X28,1,new QTableWidgetItem(QString::fromUtf8("EM4-X13")));
        ui->tableWidget_In->setItem(MAIN_X29,1,new QTableWidgetItem(QString::fromUtf8("EM4-X14")));
        ui->tableWidget_In->setItem(MAIN_X30,1,new QTableWidgetItem(QString::fromUtf8("EM4-X15")));
        ui->tableWidget_In->setItem(MAIN_X31,1,new QTableWidgetItem(QString::fromUtf8("EM4-X16")));
    }
    else
    {
        ui->tableWidget_In->setItem(EM1_X00,1,new QTableWidgetItem(QString::fromUtf8("EM1-X01")));
        ui->tableWidget_In->setItem(EM1_X01,1,new QTableWidgetItem(QString::fromUtf8("EM1-X02")));
        ui->tableWidget_In->setItem(EM1_X02,1,new QTableWidgetItem(tr("吸具1-X03")));
        ui->tableWidget_In->setItem(EM1_X03,1,new QTableWidgetItem(tr("吸具2-X04")));
        ui->tableWidget_In->setItem(EM1_X04,1,new QTableWidgetItem(tr("抱具1-X05")));
        ui->tableWidget_In->setItem(EM1_X05,1,new QTableWidgetItem(tr("抱具2-X06")));
        ui->tableWidget_In->setItem(EM1_X06,1,new QTableWidgetItem(tr("抱具3-X07")));
        ui->tableWidget_In->setItem(EM1_X07,1,new QTableWidgetItem(tr("抱具4-X08")));
        ui->tableWidget_In->setItem(EM1_X09,1,new QTableWidgetItem(QString::fromUtf8("EM1-X10")));
        ui->tableWidget_In->setItem(EM1_X08,1,new QTableWidgetItem(QString::fromUtf8("EM1-X09")));
        ui->tableWidget_In->setItem(EM1_X10,1,new QTableWidgetItem(QString::fromUtf8("EM1-X11")));
        ui->tableWidget_In->setItem(EM1_X11,1,new QTableWidgetItem(QString::fromUtf8("EM1-X12")));
        ui->tableWidget_In->setItem(EM1_X12,1,new QTableWidgetItem(QString::fromUtf8("EM1-X13")));
        ui->tableWidget_In->setItem(EM1_X13,1,new QTableWidgetItem(QString::fromUtf8("EM1-X14")));
        ui->tableWidget_In->setItem(EM1_X14,1,new QTableWidgetItem(QString::fromUtf8("EM1-X15")));
        ui->tableWidget_In->setItem(EM1_X15,1,new QTableWidgetItem(QString::fromUtf8("EM1-X16")));
        //扩展2
        ui->tableWidget_In->setItem(EM2_X00,1,new QTableWidgetItem(QString::fromUtf8("EM2-X01")));
        ui->tableWidget_In->setItem(EM2_X01,1,new QTableWidgetItem(QString::fromUtf8("EM2-X02")));
        ui->tableWidget_In->setItem(EM2_X02,1,new QTableWidgetItem(QString::fromUtf8("EM2-X03")));
        ui->tableWidget_In->setItem(EM2_X03,1,new QTableWidgetItem(QString::fromUtf8("EM2-X04")));
        ui->tableWidget_In->setItem(EM2_X04,1,new QTableWidgetItem(QString::fromUtf8("EM2-X05")));
        ui->tableWidget_In->setItem(EM2_X05,1,new QTableWidgetItem(QString::fromUtf8("EM2-X06")));
        ui->tableWidget_In->setItem(EM2_X06,1,new QTableWidgetItem(QString::fromUtf8("EM2-X07")));
        ui->tableWidget_In->setItem(EM2_X07,1,new QTableWidgetItem(QString::fromUtf8("EM2-X08")));
        ui->tableWidget_In->setItem(EM2_X08,1,new QTableWidgetItem(QString::fromUtf8("EM2-X09")));
        ui->tableWidget_In->setItem(EM2_X09,1,new QTableWidgetItem(QString::fromUtf8("EM2-X10")));
        ui->tableWidget_In->setItem(EM2_X10,1,new QTableWidgetItem(QString::fromUtf8("EM2-X11")));
        ui->tableWidget_In->setItem(EM2_X11,1,new QTableWidgetItem(QString::fromUtf8("EM2-X12")));
        ui->tableWidget_In->setItem(EM2_X12,1,new QTableWidgetItem(QString::fromUtf8("EM2-X13")));
        ui->tableWidget_In->setItem(EM2_X13,1,new QTableWidgetItem(QString::fromUtf8("EM2-X14")));
        ui->tableWidget_In->setItem(EM2_X14,1,new QTableWidgetItem(QString::fromUtf8("EM2-X15")));
        ui->tableWidget_In->setItem(EM2_X15,1,new QTableWidgetItem(QString::fromUtf8("EM2-X16")));
        //扩展3
        ui->tableWidget_In->setItem(EM3_X00,1,new QTableWidgetItem(QString::fromUtf8("EM3-X01")));
        ui->tableWidget_In->setItem(EM3_X01,1,new QTableWidgetItem(QString::fromUtf8("EM3-X02")));
        ui->tableWidget_In->setItem(EM3_X02,1,new QTableWidgetItem(QString::fromUtf8("EM3-X03")));
        ui->tableWidget_In->setItem(EM3_X03,1,new QTableWidgetItem(QString::fromUtf8("EM3-X04")));
        ui->tableWidget_In->setItem(EM3_X04,1,new QTableWidgetItem(QString::fromUtf8("EM3-X05")));
        ui->tableWidget_In->setItem(EM3_X05,1,new QTableWidgetItem(QString::fromUtf8("EM3-X06")));
        ui->tableWidget_In->setItem(EM3_X06,1,new QTableWidgetItem(QString::fromUtf8("EM3-X07")));
        ui->tableWidget_In->setItem(EM3_X07,1,new QTableWidgetItem(QString::fromUtf8("EM3-X08")));
        ui->tableWidget_In->setItem(EM3_X08,1,new QTableWidgetItem(QString::fromUtf8("EM3-X09")));
        ui->tableWidget_In->setItem(EM3_X09,1,new QTableWidgetItem(QString::fromUtf8("EM3-X10")));
        ui->tableWidget_In->setItem(EM3_X10,1,new QTableWidgetItem(QString::fromUtf8("EM3-X11")));
        ui->tableWidget_In->setItem(EM3_X11,1,new QTableWidgetItem(QString::fromUtf8("EM3-X12")));
        ui->tableWidget_In->setItem(EM3_X12,1,new QTableWidgetItem(QString::fromUtf8("EM3-X13")));
        ui->tableWidget_In->setItem(EM3_X13,1,new QTableWidgetItem(QString::fromUtf8("EM3-X14")));
        ui->tableWidget_In->setItem(EM3_X14,1,new QTableWidgetItem(QString::fromUtf8("EM3-X15")));
        ui->tableWidget_In->setItem(EM3_X15,1,new QTableWidgetItem(QString::fromUtf8("EM3-X16")));
        //扩展4
        ui->tableWidget_In->setItem(EM4_X00,1,new QTableWidgetItem(QString::fromUtf8("EM4-X01")));
        ui->tableWidget_In->setItem(EM4_X01,1,new QTableWidgetItem(QString::fromUtf8("EM4-X02")));
        ui->tableWidget_In->setItem(EM4_X02,1,new QTableWidgetItem(QString::fromUtf8("EM4-X03")));
        ui->tableWidget_In->setItem(EM4_X03,1,new QTableWidgetItem(QString::fromUtf8("EM4-X04")));
        ui->tableWidget_In->setItem(EM4_X04,1,new QTableWidgetItem(QString::fromUtf8("EM4-X05")));
        ui->tableWidget_In->setItem(EM4_X05,1,new QTableWidgetItem(QString::fromUtf8("EM4-X06")));
        ui->tableWidget_In->setItem(EM4_X06,1,new QTableWidgetItem(QString::fromUtf8("EM4-X07")));
        ui->tableWidget_In->setItem(EM4_X07,1,new QTableWidgetItem(QString::fromUtf8("EM4-X08")));
        ui->tableWidget_In->setItem(EM4_X08,1,new QTableWidgetItem(QString::fromUtf8("EM4-X09")));
        ui->tableWidget_In->setItem(EM4_X09,1,new QTableWidgetItem(QString::fromUtf8("EM4-X10")));
        ui->tableWidget_In->setItem(EM4_X10,1,new QTableWidgetItem(QString::fromUtf8("EM4-X11")));
        ui->tableWidget_In->setItem(EM4_X11,1,new QTableWidgetItem(QString::fromUtf8("EM4-X12")));
        ui->tableWidget_In->setItem(EM4_X12,1,new QTableWidgetItem(QString::fromUtf8("EM4-X13")));
        ui->tableWidget_In->setItem(EM4_X13,1,new QTableWidgetItem(QString::fromUtf8("EM4-X14")));
        ui->tableWidget_In->setItem(EM4_X14,1,new QTableWidgetItem(QString::fromUtf8("EM4-X15")));
        ui->tableWidget_In->setItem(EM4_X15,1,new QTableWidgetItem(QString::fromUtf8("EM4-X16")));
    }
    //主板输入显示修改名称
    ui->tableWidget_In->setItem(MAIN_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X00)));
    ui->tableWidget_In->setItem(MAIN_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X01)));
    ui->tableWidget_In->setItem(MAIN_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X02)));
    ui->tableWidget_In->setItem(MAIN_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X03)));
    ui->tableWidget_In->setItem(MAIN_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X04)));
    ui->tableWidget_In->setItem(MAIN_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X05)));
    ui->tableWidget_In->setItem(MAIN_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X06)));
    ui->tableWidget_In->setItem(MAIN_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X07)));
    ui->tableWidget_In->setItem(MAIN_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X08)));
    ui->tableWidget_In->setItem(MAIN_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X09)));
    ui->tableWidget_In->setItem(MAIN_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X10)));
    ui->tableWidget_In->setItem(MAIN_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X11)));
    ui->tableWidget_In->setItem(MAIN_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X12)));
    ui->tableWidget_In->setItem(MAIN_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X13)));
    ui->tableWidget_In->setItem(MAIN_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X14)));
    ui->tableWidget_In->setItem(MAIN_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X15)));

    //pyq得到保存在编辑端口名字页面更改后的数据
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        //扩展输入
        ui->tableWidget_In->setItem(EM1_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X16)));
        ui->tableWidget_In->setItem(EM1_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X17)));
        ui->tableWidget_In->setItem(EM1_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X18)));
        ui->tableWidget_In->setItem(EM1_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X19)));
        ui->tableWidget_In->setItem(EM1_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X20)));
        ui->tableWidget_In->setItem(EM1_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X21)));
        ui->tableWidget_In->setItem(EM1_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X22)));
        ui->tableWidget_In->setItem(EM1_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X23)));
        ui->tableWidget_In->setItem(EM1_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X24)));
        ui->tableWidget_In->setItem(EM1_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X25)));
        ui->tableWidget_In->setItem(EM1_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X26)));
        ui->tableWidget_In->setItem(EM1_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X27)));

        ui->tableWidget_In->setItem(EM1_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X00)));
        ui->tableWidget_In->setItem(EM1_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X01)));
        ui->tableWidget_In->setItem(EM1_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X02)));
        ui->tableWidget_In->setItem(EM1_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X03)));
        ui->tableWidget_In->setItem(EM2_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X04)));
        ui->tableWidget_In->setItem(EM2_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X05)));
        ui->tableWidget_In->setItem(EM2_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X06)));
        ui->tableWidget_In->setItem(EM2_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X07)));
        ui->tableWidget_In->setItem(EM2_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X08)));
        ui->tableWidget_In->setItem(EM2_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X09)));
        ui->tableWidget_In->setItem(EM2_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X10)));
        ui->tableWidget_In->setItem(EM2_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X11)));
        ui->tableWidget_In->setItem(EM2_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X12)));
        ui->tableWidget_In->setItem(EM2_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X13)));
        ui->tableWidget_In->setItem(EM2_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X14)));
        ui->tableWidget_In->setItem(EM2_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X15)));

        ui->tableWidget_In->setItem(EM2_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X00)));
        ui->tableWidget_In->setItem(EM2_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X01)));
        ui->tableWidget_In->setItem(EM2_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X02)));
        ui->tableWidget_In->setItem(EM2_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X03)));
        ui->tableWidget_In->setItem(EM3_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X04)));
        ui->tableWidget_In->setItem(EM3_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X05)));
        ui->tableWidget_In->setItem(EM3_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X06)));
        ui->tableWidget_In->setItem(EM3_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X07)));
        ui->tableWidget_In->setItem(EM3_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X08)));
        ui->tableWidget_In->setItem(EM3_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X09)));
        ui->tableWidget_In->setItem(EM3_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X10)));
        ui->tableWidget_In->setItem(EM3_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X11)));
        ui->tableWidget_In->setItem(EM3_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X12)));
        ui->tableWidget_In->setItem(EM3_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X13)));
        ui->tableWidget_In->setItem(EM3_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X14)));
        ui->tableWidget_In->setItem(EM3_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X15)));

        ui->tableWidget_In->setItem(EM3_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X00)));
        ui->tableWidget_In->setItem(EM3_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X01)));
        ui->tableWidget_In->setItem(EM3_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X02)));
        ui->tableWidget_In->setItem(EM3_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X03)));
        ui->tableWidget_In->setItem(EM4_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X04)));
        ui->tableWidget_In->setItem(EM4_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X05)));
        ui->tableWidget_In->setItem(EM4_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X06)));
        ui->tableWidget_In->setItem(EM4_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X07)));
        ui->tableWidget_In->setItem(EM4_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X08)));
        ui->tableWidget_In->setItem(EM4_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X09)));
        ui->tableWidget_In->setItem(EM4_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X10)));
        ui->tableWidget_In->setItem(EM4_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X11)));
        ui->tableWidget_In->setItem(EM4_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X12)));
        ui->tableWidget_In->setItem(EM4_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X13)));
        ui->tableWidget_In->setItem(EM4_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X14)));
        ui->tableWidget_In->setItem(EM4_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X15)));

        ui->tableWidget_In->setItem(EM4_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X00)));
        ui->tableWidget_In->setItem(EM4_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X01)));
        ui->tableWidget_In->setItem(EM4_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X02)));
        ui->tableWidget_In->setItem(EM4_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X03)));
        ui->tableWidget_In->setItem(MAIN_X16,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X04)));
        ui->tableWidget_In->setItem(MAIN_X17,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X05)));
        ui->tableWidget_In->setItem(MAIN_X18,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X06)));
        ui->tableWidget_In->setItem(MAIN_X19,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X07)));
        ui->tableWidget_In->setItem(MAIN_X20,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X08)));
        ui->tableWidget_In->setItem(MAIN_X21,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X09)));
        ui->tableWidget_In->setItem(MAIN_X22,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X10)));
        ui->tableWidget_In->setItem(MAIN_X23,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X11)));
        ui->tableWidget_In->setItem(MAIN_X24,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X12)));
        ui->tableWidget_In->setItem(MAIN_X25,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X13)));
        ui->tableWidget_In->setItem(MAIN_X26,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X14)));
        ui->tableWidget_In->setItem(MAIN_X27,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X15)));

    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        //扩展输入
        ui->tableWidget_In->setItem(EM1_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X16)));
        ui->tableWidget_In->setItem(EM1_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X17)));
        ui->tableWidget_In->setItem(EM1_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X18)));
        ui->tableWidget_In->setItem(EM1_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X19)));
        ui->tableWidget_In->setItem(EM1_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X20)));
        ui->tableWidget_In->setItem(EM1_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X21)));
        ui->tableWidget_In->setItem(EM1_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X22)));
        ui->tableWidget_In->setItem(EM1_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X23)));
        ui->tableWidget_In->setItem(EM1_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X24)));
        ui->tableWidget_In->setItem(EM1_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X25)));
        ui->tableWidget_In->setItem(EM1_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X26)));
        ui->tableWidget_In->setItem(EM1_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X27)));
        ui->tableWidget_In->setItem(EM1_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X28)));
        ui->tableWidget_In->setItem(EM1_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X29)));
        ui->tableWidget_In->setItem(EM1_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X30)));
        ui->tableWidget_In->setItem(EM1_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_X31)));

        ui->tableWidget_In->setItem(EM2_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X00)));
        ui->tableWidget_In->setItem(EM2_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X01)));
        ui->tableWidget_In->setItem(EM2_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X02)));
        ui->tableWidget_In->setItem(EM2_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X03)));
        ui->tableWidget_In->setItem(EM2_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X04)));
        ui->tableWidget_In->setItem(EM2_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X05)));
        ui->tableWidget_In->setItem(EM2_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X06)));
        ui->tableWidget_In->setItem(EM2_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X07)));
        ui->tableWidget_In->setItem(EM2_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X08)));
        ui->tableWidget_In->setItem(EM2_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X09)));
        ui->tableWidget_In->setItem(EM2_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X10)));
        ui->tableWidget_In->setItem(EM2_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X11)));
        ui->tableWidget_In->setItem(EM2_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X12)));
        ui->tableWidget_In->setItem(EM2_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X13)));
        ui->tableWidget_In->setItem(EM2_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X14)));
        ui->tableWidget_In->setItem(EM2_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X15)));

        ui->tableWidget_In->setItem(EM3_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X00)));
        ui->tableWidget_In->setItem(EM3_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X01)));
        ui->tableWidget_In->setItem(EM3_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X02)));
        ui->tableWidget_In->setItem(EM3_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X03)));
        ui->tableWidget_In->setItem(EM3_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X04)));
        ui->tableWidget_In->setItem(EM3_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X05)));
        ui->tableWidget_In->setItem(EM3_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X06)));
        ui->tableWidget_In->setItem(EM3_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X07)));
        ui->tableWidget_In->setItem(EM3_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X08)));
        ui->tableWidget_In->setItem(EM3_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X09)));
        ui->tableWidget_In->setItem(EM3_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X10)));
        ui->tableWidget_In->setItem(EM3_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X11)));
        ui->tableWidget_In->setItem(EM3_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X12)));
        ui->tableWidget_In->setItem(EM3_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X13)));
        ui->tableWidget_In->setItem(EM3_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X14)));
        ui->tableWidget_In->setItem(EM3_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X15)));

        ui->tableWidget_In->setItem(EM4_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X00)));
        ui->tableWidget_In->setItem(EM4_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X01)));
        ui->tableWidget_In->setItem(EM4_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X02)));
        ui->tableWidget_In->setItem(EM4_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X03)));
        ui->tableWidget_In->setItem(EM4_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X04)));
        ui->tableWidget_In->setItem(EM4_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X05)));
        ui->tableWidget_In->setItem(EM4_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X06)));
        ui->tableWidget_In->setItem(EM4_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X07)));
        ui->tableWidget_In->setItem(EM4_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X08)));
        ui->tableWidget_In->setItem(EM4_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X09)));
        ui->tableWidget_In->setItem(EM4_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X10)));
        ui->tableWidget_In->setItem(EM4_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X11)));
        ui->tableWidget_In->setItem(EM4_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X12)));
        ui->tableWidget_In->setItem(EM4_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X13)));
        ui->tableWidget_In->setItem(EM4_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X14)));
        ui->tableWidget_In->setItem(EM4_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X15)));

        ui->tableWidget_In->setItem(MAIN_X16,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X00)));
        ui->tableWidget_In->setItem(MAIN_X17,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X01)));
        ui->tableWidget_In->setItem(MAIN_X18,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X02)));
        ui->tableWidget_In->setItem(MAIN_X19,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X03)));
        ui->tableWidget_In->setItem(MAIN_X20,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X04)));
        ui->tableWidget_In->setItem(MAIN_X21,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X05)));
        ui->tableWidget_In->setItem(MAIN_X22,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X06)));
        ui->tableWidget_In->setItem(MAIN_X23,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X07)));
        ui->tableWidget_In->setItem(MAIN_X24,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X08)));
        ui->tableWidget_In->setItem(MAIN_X25,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X09)));
        ui->tableWidget_In->setItem(MAIN_X26,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X10)));
        ui->tableWidget_In->setItem(MAIN_X27,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X11)));
        ui->tableWidget_In->setItem(MAIN_X28,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X12)));
        ui->tableWidget_In->setItem(MAIN_X29,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X13)));
        ui->tableWidget_In->setItem(MAIN_X30,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X14)));
        ui->tableWidget_In->setItem(MAIN_X31,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X15)));

    }
    else
    {
        //扩展输入
        ui->tableWidget_In->setItem(EM1_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X00)));
        ui->tableWidget_In->setItem(EM1_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X01)));
        ui->tableWidget_In->setItem(EM1_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X02)));
        ui->tableWidget_In->setItem(EM1_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X03)));
        ui->tableWidget_In->setItem(EM1_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X04)));
        ui->tableWidget_In->setItem(EM1_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X05)));
        ui->tableWidget_In->setItem(EM1_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X06)));
        ui->tableWidget_In->setItem(EM1_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X07)));
        ui->tableWidget_In->setItem(EM1_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X08)));
        ui->tableWidget_In->setItem(EM1_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X09)));
        ui->tableWidget_In->setItem(EM1_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X10)));
        ui->tableWidget_In->setItem(EM1_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X11)));
        ui->tableWidget_In->setItem(EM1_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X12)));
        ui->tableWidget_In->setItem(EM1_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X13)));
        ui->tableWidget_In->setItem(EM1_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X14)));
        ui->tableWidget_In->setItem(EM1_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_X15)));

        ui->tableWidget_In->setItem(EM2_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X00)));
        ui->tableWidget_In->setItem(EM2_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X01)));
        ui->tableWidget_In->setItem(EM2_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X02)));
        ui->tableWidget_In->setItem(EM2_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X03)));
        ui->tableWidget_In->setItem(EM2_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X04)));
        ui->tableWidget_In->setItem(EM2_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X05)));
        ui->tableWidget_In->setItem(EM2_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X06)));
        ui->tableWidget_In->setItem(EM2_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X07)));
        ui->tableWidget_In->setItem(EM2_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X08)));
        ui->tableWidget_In->setItem(EM2_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X09)));
        ui->tableWidget_In->setItem(EM2_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X10)));
        ui->tableWidget_In->setItem(EM2_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X11)));
        ui->tableWidget_In->setItem(EM2_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X12)));
        ui->tableWidget_In->setItem(EM2_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X13)));
        ui->tableWidget_In->setItem(EM2_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X14)));
        ui->tableWidget_In->setItem(EM2_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_X15)));

        ui->tableWidget_In->setItem(EM3_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X00)));
        ui->tableWidget_In->setItem(EM3_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X01)));
        ui->tableWidget_In->setItem(EM3_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X02)));
        ui->tableWidget_In->setItem(EM3_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X03)));
        ui->tableWidget_In->setItem(EM3_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X04)));
        ui->tableWidget_In->setItem(EM3_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X05)));
        ui->tableWidget_In->setItem(EM3_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X06)));
        ui->tableWidget_In->setItem(EM3_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X07)));
        ui->tableWidget_In->setItem(EM3_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X08)));
        ui->tableWidget_In->setItem(EM3_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X09)));
        ui->tableWidget_In->setItem(EM3_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X10)));
        ui->tableWidget_In->setItem(EM3_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X11)));
        ui->tableWidget_In->setItem(EM3_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X12)));
        ui->tableWidget_In->setItem(EM3_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X13)));
        ui->tableWidget_In->setItem(EM3_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X14)));
        ui->tableWidget_In->setItem(EM3_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_X15)));

        ui->tableWidget_In->setItem(EM4_X00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X00)));
        ui->tableWidget_In->setItem(EM4_X01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X01)));
        ui->tableWidget_In->setItem(EM4_X02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X02)));
        ui->tableWidget_In->setItem(EM4_X03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X03)));
        ui->tableWidget_In->setItem(EM4_X04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X04)));
        ui->tableWidget_In->setItem(EM4_X05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X05)));
        ui->tableWidget_In->setItem(EM4_X06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X06)));
        ui->tableWidget_In->setItem(EM4_X07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X07)));
        ui->tableWidget_In->setItem(EM4_X08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X08)));
        ui->tableWidget_In->setItem(EM4_X09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X09)));
        ui->tableWidget_In->setItem(EM4_X10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X10)));
        ui->tableWidget_In->setItem(EM4_X11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X11)));
        ui->tableWidget_In->setItem(EM4_X12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X12)));
        ui->tableWidget_In->setItem(EM4_X13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X13)));
        ui->tableWidget_In->setItem(EM4_X14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X14)));
        ui->tableWidget_In->setItem(EM4_X15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_X15)));
    }
}
void DialogPortEdit::InitOutPortName()
{
    //主板 输出端口号
    ui->tableWidget_Out->setItem(MAIN_Y00,0,new QTableWidgetItem(tr("主板Y00")));
    ui->tableWidget_Out->setItem(MAIN_Y01,0,new QTableWidgetItem(tr("主板Y01")));
    ui->tableWidget_Out->setItem(MAIN_Y02,0,new QTableWidgetItem(tr("主板Y02")));
    ui->tableWidget_Out->setItem(MAIN_Y03,0,new QTableWidgetItem(tr("主板Y03")));
    ui->tableWidget_Out->setItem(MAIN_Y04,0,new QTableWidgetItem(tr("主板Y04")));
    ui->tableWidget_Out->setItem(MAIN_Y05,0,new QTableWidgetItem(tr("主板Y05")));
    ui->tableWidget_Out->setItem(MAIN_Y06,0,new QTableWidgetItem(tr("主板Y06")));
    ui->tableWidget_Out->setItem(MAIN_Y07,0,new QTableWidgetItem(tr("主板Y07")));
    ui->tableWidget_Out->setItem(MAIN_Y08,0,new QTableWidgetItem(tr("主板Y08")));
    ui->tableWidget_Out->setItem(MAIN_Y09,0,new QTableWidgetItem(tr("主板Y09")));
    ui->tableWidget_Out->setItem(MAIN_Y10,0,new QTableWidgetItem(tr("主板Y10")));
    ui->tableWidget_Out->setItem(MAIN_Y11,0,new QTableWidgetItem(tr("主板Y11")));
    ui->tableWidget_Out->setItem(MAIN_Y12,0,new QTableWidgetItem(tr("主板Y12")));
    ui->tableWidget_Out->setItem(MAIN_Y13,0,new QTableWidgetItem(tr("主板Y13")));
    ui->tableWidget_Out->setItem(MAIN_Y14,0,new QTableWidgetItem(tr("主板Y14")));
    ui->tableWidget_Out->setItem(MAIN_Y15,0,new QTableWidgetItem(tr("主板Y15")));
    //   if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    //   {
    //       //扩展输出
    //        ui->tableWidget_Out->setItem(EM1_Y00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y00")));
    //        ui->tableWidget_Out->setItem(EM1_Y01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y01")));
    //        ui->tableWidget_Out->setItem(EM1_Y02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y02")));
    //        ui->tableWidget_Out->setItem(EM1_Y03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y03")));
    //        ui->tableWidget_Out->setItem(EM1_Y04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y04")));
    //        ui->tableWidget_Out->setItem(EM1_Y05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y05")));
    //        ui->tableWidget_Out->setItem(EM1_Y06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y06")));
    //        ui->tableWidget_Out->setItem(EM1_Y07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y07")));
    //        ui->tableWidget_Out->setItem(EM1_Y08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y08")));
    //        ui->tableWidget_Out->setItem(EM1_Y09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y09")));
    //        ui->tableWidget_Out->setItem(EM1_Y10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y10")));
    //        ui->tableWidget_Out->setItem(EM1_Y11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y11")));
    //        ui->tableWidget_Out->setItem(EM1_Y12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y12")));
    //        ui->tableWidget_Out->setItem(EM1_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y13")));
    //        ui->tableWidget_Out->setItem(EM1_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y14")));
    //        ui->tableWidget_Out->setItem(EM1_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y15")));

    //        ui->tableWidget_Out->setItem(EM2_Y00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y00")));
    //        ui->tableWidget_Out->setItem(EM2_Y01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y01")));
    //        ui->tableWidget_Out->setItem(EM2_Y02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y02")));
    //        ui->tableWidget_Out->setItem(EM2_Y03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y03")));
    //        ui->tableWidget_Out->setItem(EM2_Y04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y04")));
    //        ui->tableWidget_Out->setItem(EM2_Y05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y05")));
    //        ui->tableWidget_Out->setItem(EM2_Y06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y06")));
    //        ui->tableWidget_Out->setItem(EM2_Y07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y07")));
    //        ui->tableWidget_Out->setItem(EM2_Y08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y08")));
    //        ui->tableWidget_Out->setItem(EM2_Y09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y09")));
    //        ui->tableWidget_Out->setItem(EM2_Y10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y10")));
    //        ui->tableWidget_Out->setItem(EM2_Y11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y11")));
    //        ui->tableWidget_Out->setItem(EM2_Y12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y12")));
    //        ui->tableWidget_Out->setItem(EM2_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y13")));
    //        ui->tableWidget_Out->setItem(EM2_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y14")));
    //        ui->tableWidget_Out->setItem(EM2_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y15")));

    //        ui->tableWidget_Out->setItem(EM3_Y00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y00")));
    //        ui->tableWidget_Out->setItem(EM3_Y01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y01")));
    //        ui->tableWidget_Out->setItem(EM3_Y02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y02")));
    //        ui->tableWidget_Out->setItem(EM3_Y03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y03")));
    //        ui->tableWidget_Out->setItem(EM3_Y04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y04")));
    //        ui->tableWidget_Out->setItem(EM3_Y05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y05")));
    //        ui->tableWidget_Out->setItem(EM3_Y06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y06")));
    //        ui->tableWidget_Out->setItem(EM3_Y07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y07")));
    //        ui->tableWidget_Out->setItem(EM3_Y08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y08")));
    //        ui->tableWidget_Out->setItem(EM3_Y09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y09")));
    //        ui->tableWidget_Out->setItem(EM3_Y10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y10")));
    //        ui->tableWidget_Out->setItem(EM3_Y11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y11")));
    //        ui->tableWidget_Out->setItem(EM3_Y12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y12")));
    //        ui->tableWidget_Out->setItem(EM3_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y13")));
    //        ui->tableWidget_Out->setItem(EM3_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y14")));
    //        ui->tableWidget_Out->setItem(EM3_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y15")));

    //        ui->tableWidget_Out->setItem(EM4_Y00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y00")));
    //        ui->tableWidget_Out->setItem(EM4_Y01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y01")));
    //        ui->tableWidget_Out->setItem(EM4_Y02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y02")));
    //        ui->tableWidget_Out->setItem(EM4_Y03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y03")));
    //        ui->tableWidget_Out->setItem(EM4_Y04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y04")));
    //        ui->tableWidget_Out->setItem(EM4_Y05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y05")));
    //        ui->tableWidget_Out->setItem(EM4_Y06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y06")));
    //        ui->tableWidget_Out->setItem(EM4_Y07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y07")));
    //        ui->tableWidget_Out->setItem(EM4_Y08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y08")));
    //        ui->tableWidget_Out->setItem(EM4_Y09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y09")));
    //        ui->tableWidget_Out->setItem(EM4_Y10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y10")));
    //        ui->tableWidget_Out->setItem(EM4_Y11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y11")));
    //        ui->tableWidget_Out->setItem(EM4_Y12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y12")));
    //        ui->tableWidget_Out->setItem(EM4_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y13")));
    //        ui->tableWidget_Out->setItem(EM4_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y14")));
    //        ui->tableWidget_Out->setItem(EM4_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y15")));
    //   }
    //pyq 输出端口号
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        ui->tableWidget_Out->setItem(EM1_Y00,0,new QTableWidgetItem(QString::fromUtf8("主板Y16")));
        ui->tableWidget_Out->setItem(EM1_Y01,0,new QTableWidgetItem(QString::fromUtf8("主板Y17")));
        ui->tableWidget_Out->setItem(EM1_Y02,0,new QTableWidgetItem(QString::fromUtf8("主板Y18")));
        ui->tableWidget_Out->setItem(EM1_Y03,0,new QTableWidgetItem(QString::fromUtf8("主板Y19")));
        ui->tableWidget_Out->setItem(EM1_Y04,0,new QTableWidgetItem(QString::fromUtf8("主板Y20")));
        ui->tableWidget_Out->setItem(EM1_Y05,0,new QTableWidgetItem(QString::fromUtf8("主板Y21")));
        ui->tableWidget_Out->setItem(EM1_Y06,0,new QTableWidgetItem(QString::fromUtf8("主板Y22")));
        ui->tableWidget_Out->setItem(EM1_Y07,0,new QTableWidgetItem(QString::fromUtf8("主板Y23")));
        ui->tableWidget_Out->setItem(EM1_Y08,0,new QTableWidgetItem(QString::fromUtf8("主板Y24")));
        ui->tableWidget_Out->setItem(EM1_Y09,0,new QTableWidgetItem(QString::fromUtf8("主板Y25")));
        ui->tableWidget_Out->setItem(EM1_Y10,0,new QTableWidgetItem(QString::fromUtf8("主板Y26")));
        ui->tableWidget_Out->setItem(EM1_Y11,0,new QTableWidgetItem(QString::fromUtf8("主板Y27")));
        ui->tableWidget_Out->setItem(EM1_Y12,0,new QTableWidgetItem(QString::fromUtf8("主板Y28")));

        ui->tableWidget_Out->setItem(EM1_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y00")));
        ui->tableWidget_Out->setItem(EM1_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y01")));
        ui->tableWidget_Out->setItem(EM1_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y02")));
        ui->tableWidget_Out->setItem(EM2_Y00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y03")));
        ui->tableWidget_Out->setItem(EM2_Y01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y04")));
        ui->tableWidget_Out->setItem(EM2_Y02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y05")));
        ui->tableWidget_Out->setItem(EM2_Y03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y06")));
        ui->tableWidget_Out->setItem(EM2_Y04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y07")));
        ui->tableWidget_Out->setItem(EM2_Y05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y08")));
        ui->tableWidget_Out->setItem(EM2_Y06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y09")));
        ui->tableWidget_Out->setItem(EM2_Y07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y10")));
        ui->tableWidget_Out->setItem(EM2_Y08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y11")));
        ui->tableWidget_Out->setItem(EM2_Y09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y12")));
        ui->tableWidget_Out->setItem(EM2_Y10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y13")));
        ui->tableWidget_Out->setItem(EM2_Y11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y14")));
        ui->tableWidget_Out->setItem(EM2_Y12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y15")));

        ui->tableWidget_Out->setItem(EM2_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y00")));
        ui->tableWidget_Out->setItem(EM2_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y01")));
        ui->tableWidget_Out->setItem(EM2_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y02")));
        ui->tableWidget_Out->setItem(EM3_Y00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y03")));
        ui->tableWidget_Out->setItem(EM3_Y01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y04")));
        ui->tableWidget_Out->setItem(EM3_Y02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y05")));
        ui->tableWidget_Out->setItem(EM3_Y03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y06")));
        ui->tableWidget_Out->setItem(EM3_Y04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y07")));
        ui->tableWidget_Out->setItem(EM3_Y05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y08")));
        ui->tableWidget_Out->setItem(EM3_Y06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y09")));
        ui->tableWidget_Out->setItem(EM3_Y07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y10")));
        ui->tableWidget_Out->setItem(EM3_Y08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y11")));
        ui->tableWidget_Out->setItem(EM3_Y09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y12")));
        ui->tableWidget_Out->setItem(EM3_Y10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y13")));
        ui->tableWidget_Out->setItem(EM3_Y11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y14")));
        ui->tableWidget_Out->setItem(EM3_Y12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y15")));

        ui->tableWidget_Out->setItem(EM3_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y00")));
        ui->tableWidget_Out->setItem(EM3_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y01")));
        ui->tableWidget_Out->setItem(EM3_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y02")));
        ui->tableWidget_Out->setItem(EM4_Y00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y03")));
        ui->tableWidget_Out->setItem(EM4_Y01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y04")));
        ui->tableWidget_Out->setItem(EM4_Y02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y05")));
        ui->tableWidget_Out->setItem(EM4_Y03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y06")));
        ui->tableWidget_Out->setItem(EM4_Y04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y07")));
        ui->tableWidget_Out->setItem(EM4_Y05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y08")));
        ui->tableWidget_Out->setItem(EM4_Y06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y09")));
        ui->tableWidget_Out->setItem(EM4_Y07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y10")));
        ui->tableWidget_Out->setItem(EM4_Y08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y11")));
        ui->tableWidget_Out->setItem(EM4_Y09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y12")));
        ui->tableWidget_Out->setItem(EM4_Y10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y13")));
        ui->tableWidget_Out->setItem(EM4_Y11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y14")));
        ui->tableWidget_Out->setItem(EM4_Y12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y15")));

        ui->tableWidget_Out->setItem(EM4_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y00")));
        ui->tableWidget_Out->setItem(EM4_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y01")));
        ui->tableWidget_Out->setItem(EM4_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y02")));
        ui->tableWidget_Out->setItem(MAIN_Y16,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y03")));
        ui->tableWidget_Out->setItem(MAIN_Y17,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y04")));
        ui->tableWidget_Out->setItem(MAIN_Y18,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y05")));
        ui->tableWidget_Out->setItem(MAIN_Y19,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y06")));
        ui->tableWidget_Out->setItem(MAIN_Y20,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y07")));
        ui->tableWidget_Out->setItem(MAIN_Y21,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y08")));
        ui->tableWidget_Out->setItem(MAIN_Y22,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y09")));
        ui->tableWidget_Out->setItem(MAIN_Y23,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y10")));
        ui->tableWidget_Out->setItem(MAIN_Y24,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y11")));
        ui->tableWidget_Out->setItem(MAIN_Y25,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y12")));
        ui->tableWidget_Out->setItem(MAIN_Y26,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y13")));
        ui->tableWidget_Out->setItem(MAIN_Y27,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y14")));
        ui->tableWidget_Out->setItem(MAIN_Y28,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y15")));
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        ui->tableWidget_Out->setItem(EM1_Y00,0,new QTableWidgetItem(QString::fromUtf8("主板Y16")));
        ui->tableWidget_Out->setItem(EM1_Y01,0,new QTableWidgetItem(QString::fromUtf8("主板Y17")));
        ui->tableWidget_Out->setItem(EM1_Y02,0,new QTableWidgetItem(QString::fromUtf8("主板Y18")));
        ui->tableWidget_Out->setItem(EM1_Y03,0,new QTableWidgetItem(QString::fromUtf8("主板Y19")));
        ui->tableWidget_Out->setItem(EM1_Y04,0,new QTableWidgetItem(QString::fromUtf8("主板Y20")));
        ui->tableWidget_Out->setItem(EM1_Y05,0,new QTableWidgetItem(QString::fromUtf8("主板Y21")));
        ui->tableWidget_Out->setItem(EM1_Y06,0,new QTableWidgetItem(QString::fromUtf8("主板Y22")));
        ui->tableWidget_Out->setItem(EM1_Y07,0,new QTableWidgetItem(QString::fromUtf8("主板Y23")));
        ui->tableWidget_Out->setItem(EM1_Y08,0,new QTableWidgetItem(QString::fromUtf8("主板Y24")));
        ui->tableWidget_Out->setItem(EM1_Y09,0,new QTableWidgetItem(QString::fromUtf8("主板Y25")));
        ui->tableWidget_Out->setItem(EM1_Y10,0,new QTableWidgetItem(QString::fromUtf8("主板Y26")));
        ui->tableWidget_Out->setItem(EM1_Y11,0,new QTableWidgetItem(QString::fromUtf8("主板Y27")));
        ui->tableWidget_Out->setItem(EM1_Y12,0,new QTableWidgetItem(QString::fromUtf8("主板Y28")));
        ui->tableWidget_Out->setItem(EM1_Y13,0,new QTableWidgetItem(QString::fromUtf8("主板Y29")));
        ui->tableWidget_Out->setItem(EM1_Y14,0,new QTableWidgetItem(QString::fromUtf8("主板Y30")));
        ui->tableWidget_Out->setItem(EM1_Y15,0,new QTableWidgetItem(QString::fromUtf8("主板Y31")));

        ui->tableWidget_Out->setItem(EM2_Y00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y00")));
        ui->tableWidget_Out->setItem(EM2_Y01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y01")));
        ui->tableWidget_Out->setItem(EM2_Y02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y02")));
        ui->tableWidget_Out->setItem(EM2_Y03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y03")));
        ui->tableWidget_Out->setItem(EM2_Y04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y04")));
        ui->tableWidget_Out->setItem(EM2_Y05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y05")));
        ui->tableWidget_Out->setItem(EM2_Y06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y06")));
        ui->tableWidget_Out->setItem(EM2_Y07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y07")));
        ui->tableWidget_Out->setItem(EM2_Y08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y08")));
        ui->tableWidget_Out->setItem(EM2_Y09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y09")));
        ui->tableWidget_Out->setItem(EM2_Y10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y10")));
        ui->tableWidget_Out->setItem(EM2_Y11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y11")));
        ui->tableWidget_Out->setItem(EM2_Y12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y12")));
        ui->tableWidget_Out->setItem(EM2_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y13")));
        ui->tableWidget_Out->setItem(EM2_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y14")));
        ui->tableWidget_Out->setItem(EM2_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块1Y15")));

        ui->tableWidget_Out->setItem(EM3_Y00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y00")));
        ui->tableWidget_Out->setItem(EM3_Y01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y01")));
        ui->tableWidget_Out->setItem(EM3_Y02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y02")));
        ui->tableWidget_Out->setItem(EM3_Y03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y03")));
        ui->tableWidget_Out->setItem(EM3_Y04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y04")));
        ui->tableWidget_Out->setItem(EM3_Y05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y05")));
        ui->tableWidget_Out->setItem(EM3_Y06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y06")));
        ui->tableWidget_Out->setItem(EM3_Y07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y07")));
        ui->tableWidget_Out->setItem(EM3_Y08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y08")));
        ui->tableWidget_Out->setItem(EM3_Y09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y09")));
        ui->tableWidget_Out->setItem(EM3_Y10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y10")));
        ui->tableWidget_Out->setItem(EM3_Y11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y11")));
        ui->tableWidget_Out->setItem(EM3_Y12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y12")));
        ui->tableWidget_Out->setItem(EM3_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y13")));
        ui->tableWidget_Out->setItem(EM3_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y14")));
        ui->tableWidget_Out->setItem(EM3_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块2Y15")));

        ui->tableWidget_Out->setItem(EM4_Y00,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y00")));
        ui->tableWidget_Out->setItem(EM4_Y01,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y01")));
        ui->tableWidget_Out->setItem(EM4_Y02,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y02")));
        ui->tableWidget_Out->setItem(EM4_Y03,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y03")));
        ui->tableWidget_Out->setItem(EM4_Y04,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y04")));
        ui->tableWidget_Out->setItem(EM4_Y05,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y05")));
        ui->tableWidget_Out->setItem(EM4_Y06,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y06")));
        ui->tableWidget_Out->setItem(EM4_Y07,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y07")));
        ui->tableWidget_Out->setItem(EM4_Y08,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y08")));
        ui->tableWidget_Out->setItem(EM4_Y09,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y09")));
        ui->tableWidget_Out->setItem(EM4_Y10,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y10")));
        ui->tableWidget_Out->setItem(EM4_Y11,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y11")));
        ui->tableWidget_Out->setItem(EM4_Y12,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y12")));
        ui->tableWidget_Out->setItem(EM4_Y13,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y13")));
        ui->tableWidget_Out->setItem(EM4_Y14,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y14")));
        ui->tableWidget_Out->setItem(EM4_Y15,0,new QTableWidgetItem(QString::fromUtf8("扩展模块3Y15")));

        ui->tableWidget_Out->setItem(MAIN_Y16,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y00")));
        ui->tableWidget_Out->setItem(MAIN_Y17,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y01")));
        ui->tableWidget_Out->setItem(MAIN_Y18,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y02")));
        ui->tableWidget_Out->setItem(MAIN_Y19,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y03")));
        ui->tableWidget_Out->setItem(MAIN_Y20,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y04")));
        ui->tableWidget_Out->setItem(MAIN_Y21,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y05")));
        ui->tableWidget_Out->setItem(MAIN_Y22,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y06")));
        ui->tableWidget_Out->setItem(MAIN_Y23,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y07")));
        ui->tableWidget_Out->setItem(MAIN_Y24,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y08")));
        ui->tableWidget_Out->setItem(MAIN_Y25,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y09")));
        ui->tableWidget_Out->setItem(MAIN_Y26,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y10")));
        ui->tableWidget_Out->setItem(MAIN_Y27,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y11")));
        ui->tableWidget_Out->setItem(MAIN_Y28,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y12")));
        ui->tableWidget_Out->setItem(MAIN_Y29,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y13")));
        ui->tableWidget_Out->setItem(MAIN_Y30,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y14")));
        ui->tableWidget_Out->setItem(MAIN_Y31,0,new QTableWidgetItem(QString::fromUtf8("扩展模块4Y15")));
    }
    else
    {
        //扩展输出
        ui->tableWidget_Out->setItem(EM1_Y00,0,new QTableWidgetItem(tr("扩展模块1Y01")));
        ui->tableWidget_Out->setItem(EM1_Y01,0,new QTableWidgetItem(tr("扩展模块1Y02")));
        ui->tableWidget_Out->setItem(EM1_Y02,0,new QTableWidgetItem(tr("扩展模块1Y03")));
        ui->tableWidget_Out->setItem(EM1_Y03,0,new QTableWidgetItem(tr("扩展模块1Y04")));
        ui->tableWidget_Out->setItem(EM1_Y04,0,new QTableWidgetItem(tr("扩展模块1Y05")));
        ui->tableWidget_Out->setItem(EM1_Y05,0,new QTableWidgetItem(tr("扩展模块1Y06")));
        ui->tableWidget_Out->setItem(EM1_Y06,0,new QTableWidgetItem(tr("扩展模块1Y07")));
        ui->tableWidget_Out->setItem(EM1_Y07,0,new QTableWidgetItem(tr("扩展模块1Y08")));
        ui->tableWidget_Out->setItem(EM1_Y08,0,new QTableWidgetItem(tr("扩展模块1Y09")));
        ui->tableWidget_Out->setItem(EM1_Y09,0,new QTableWidgetItem(tr("扩展模块1Y10")));
        ui->tableWidget_Out->setItem(EM1_Y10,0,new QTableWidgetItem(tr("扩展模块1Y11")));
        ui->tableWidget_Out->setItem(EM1_Y11,0,new QTableWidgetItem(tr("扩展模块1Y12")));
        ui->tableWidget_Out->setItem(EM1_Y12,0,new QTableWidgetItem(tr("扩展模块1Y13")));
        ui->tableWidget_Out->setItem(EM1_Y13,0,new QTableWidgetItem(tr("扩展模块1Y14")));
        ui->tableWidget_Out->setItem(EM1_Y14,0,new QTableWidgetItem(tr("扩展模块1Y15")));
        ui->tableWidget_Out->setItem(EM1_Y15,0,new QTableWidgetItem(tr("扩展模块1Y16")));

        ui->tableWidget_Out->setItem(EM2_Y00,0,new QTableWidgetItem(tr("扩展模块2Y01")));
        ui->tableWidget_Out->setItem(EM2_Y01,0,new QTableWidgetItem(tr("扩展模块2Y02")));
        ui->tableWidget_Out->setItem(EM2_Y02,0,new QTableWidgetItem(tr("扩展模块2Y03")));
        ui->tableWidget_Out->setItem(EM2_Y03,0,new QTableWidgetItem(tr("扩展模块2Y04")));
        ui->tableWidget_Out->setItem(EM2_Y04,0,new QTableWidgetItem(tr("扩展模块2Y05")));
        ui->tableWidget_Out->setItem(EM2_Y05,0,new QTableWidgetItem(tr("扩展模块2Y06")));
        ui->tableWidget_Out->setItem(EM2_Y06,0,new QTableWidgetItem(tr("扩展模块2Y07")));
        ui->tableWidget_Out->setItem(EM2_Y07,0,new QTableWidgetItem(tr("扩展模块2Y08")));
        ui->tableWidget_Out->setItem(EM2_Y08,0,new QTableWidgetItem(tr("扩展模块2Y09")));
        ui->tableWidget_Out->setItem(EM2_Y09,0,new QTableWidgetItem(tr("扩展模块2Y10")));
        ui->tableWidget_Out->setItem(EM2_Y10,0,new QTableWidgetItem(tr("扩展模块2Y11")));
        ui->tableWidget_Out->setItem(EM2_Y11,0,new QTableWidgetItem(tr("扩展模块2Y12")));
        ui->tableWidget_Out->setItem(EM2_Y12,0,new QTableWidgetItem(tr("扩展模块2Y13")));
        ui->tableWidget_Out->setItem(EM2_Y13,0,new QTableWidgetItem(tr("扩展模块2Y14")));
        ui->tableWidget_Out->setItem(EM2_Y14,0,new QTableWidgetItem(tr("扩展模块2Y15")));
        ui->tableWidget_Out->setItem(EM2_Y15,0,new QTableWidgetItem(tr("扩展模块2Y16")));

        ui->tableWidget_Out->setItem(EM3_Y00,0,new QTableWidgetItem(tr("扩展模块3Y01")));
        ui->tableWidget_Out->setItem(EM3_Y01,0,new QTableWidgetItem(tr("扩展模块3Y02")));
        ui->tableWidget_Out->setItem(EM3_Y02,0,new QTableWidgetItem(tr("扩展模块3Y03")));
        ui->tableWidget_Out->setItem(EM3_Y03,0,new QTableWidgetItem(tr("扩展模块3Y04")));
        ui->tableWidget_Out->setItem(EM3_Y04,0,new QTableWidgetItem(tr("扩展模块3Y05")));
        ui->tableWidget_Out->setItem(EM3_Y05,0,new QTableWidgetItem(tr("扩展模块3Y06")));
        ui->tableWidget_Out->setItem(EM3_Y06,0,new QTableWidgetItem(tr("扩展模块3Y07")));
        ui->tableWidget_Out->setItem(EM3_Y07,0,new QTableWidgetItem(tr("扩展模块3Y08")));
        ui->tableWidget_Out->setItem(EM3_Y08,0,new QTableWidgetItem(tr("扩展模块3Y09")));
        ui->tableWidget_Out->setItem(EM3_Y09,0,new QTableWidgetItem(tr("扩展模块3Y10")));
        ui->tableWidget_Out->setItem(EM3_Y10,0,new QTableWidgetItem(tr("扩展模块3Y11")));
        ui->tableWidget_Out->setItem(EM3_Y11,0,new QTableWidgetItem(tr("扩展模块3Y12")));
        ui->tableWidget_Out->setItem(EM3_Y12,0,new QTableWidgetItem(tr("扩展模块3Y13")));
        ui->tableWidget_Out->setItem(EM3_Y13,0,new QTableWidgetItem(tr("扩展模块3Y14")));
        ui->tableWidget_Out->setItem(EM3_Y14,0,new QTableWidgetItem(tr("扩展模块3Y15")));
        ui->tableWidget_Out->setItem(EM3_Y15,0,new QTableWidgetItem(tr("扩展模块3Y16")));

        ui->tableWidget_Out->setItem(EM4_Y00,0,new QTableWidgetItem(tr("扩展模块4Y01")));
        ui->tableWidget_Out->setItem(EM4_Y01,0,new QTableWidgetItem(tr("扩展模块4Y02")));
        ui->tableWidget_Out->setItem(EM4_Y02,0,new QTableWidgetItem(tr("扩展模块4Y03")));
        ui->tableWidget_Out->setItem(EM4_Y03,0,new QTableWidgetItem(tr("扩展模块4Y04")));
        ui->tableWidget_Out->setItem(EM4_Y04,0,new QTableWidgetItem(tr("扩展模块4Y05")));
        ui->tableWidget_Out->setItem(EM4_Y05,0,new QTableWidgetItem(tr("扩展模块4Y06")));
        ui->tableWidget_Out->setItem(EM4_Y06,0,new QTableWidgetItem(tr("扩展模块4Y07")));
        ui->tableWidget_Out->setItem(EM4_Y07,0,new QTableWidgetItem(tr("扩展模块4Y08")));
        ui->tableWidget_Out->setItem(EM4_Y08,0,new QTableWidgetItem(tr("扩展模块4Y09")));
        ui->tableWidget_Out->setItem(EM4_Y09,0,new QTableWidgetItem(tr("扩展模块4Y10")));
        ui->tableWidget_Out->setItem(EM4_Y10,0,new QTableWidgetItem(tr("扩展模块4Y11")));
        ui->tableWidget_Out->setItem(EM4_Y11,0,new QTableWidgetItem(tr("扩展模块4Y12")));
        ui->tableWidget_Out->setItem(EM4_Y12,0,new QTableWidgetItem(tr("扩展模块4Y13")));
        ui->tableWidget_Out->setItem(EM4_Y13,0,new QTableWidgetItem(tr("扩展模块4Y14")));
        ui->tableWidget_Out->setItem(EM4_Y14,0,new QTableWidgetItem(tr("扩展模块4Y15")));
        ui->tableWidget_Out->setItem(EM4_Y15,0,new QTableWidgetItem(tr("扩展模块4Y16")));
    }

    /*    // 注塑机输出
    ui->tableWidget_Out->setItem(IMM_OUT_MAF,0,new QTableWidgetItem(tr("注塑机MAF")));
    ui->tableWidget_Out->setItem(IMM_OUT_EMC,0,new QTableWidgetItem(tr("注塑机EMC")));
    ui->tableWidget_Out->setItem(IMM_OUT_EMO,0,new QTableWidgetItem(tr("注塑机EMO")));
    ui->tableWidget_Out->setItem(IMM_OUT_RBT,0,new QTableWidgetItem(tr("注塑机RBT")));
    ui->tableWidget_Out->setItem(IMM_OUT_EEB,0,new QTableWidgetItem(tr("注塑机EEB")));
    ui->tableWidget_Out->setItem(IMM_OUT_EEF,0,new QTableWidgetItem(tr("注塑机EEF")));
    ui->tableWidget_Out->setItem(IMM_OUT_C1P1,0,new QTableWidgetItem(tr("注塑机C1P1")));
    ui->tableWidget_Out->setItem(IMM_OUT_C1P2,0,new QTableWidgetItem(tr("注塑机C1P2")));
    ui->tableWidget_Out->setItem(IMM_OUT_C2P1,0,new QTableWidgetItem(tr("注塑机C2P1")));
    ui->tableWidget_Out->setItem(IMM_OUT_C2P2,0,new QTableWidgetItem(tr("注塑机C2P2")));
    ui->tableWidget_Out->setItem(IMM_OUT_HMAF,0,new QTableWidgetItem(tr("注塑机HMAF")));
    ui->tableWidget_Out->setItem(IMM_OUT_HEMC,0,new QTableWidgetItem(tr("注塑机HEMC")));
    // 机械手输出
    ui->tableWidget_Out->setItem(RBT_OUT_PRO_HOR,   0,new QTableWidgetItem(tr("机械手PRO_HOR")));
    ui->tableWidget_Out->setItem(RBT_OUT_PRO_VER,   0,new QTableWidgetItem(tr("机械手PRO_VER")));
    ui->tableWidget_Out->setItem(RBT_OUT_ALM_BEEP,  0,new QTableWidgetItem(tr("机械手ALM_BEEP")));
    ui->tableWidget_Out->setItem(RBT_OUT_ALM_LAMP,  0,new QTableWidgetItem(tr("机械手ALM_LAMP")));
    ui->tableWidget_Out->setItem(RBT_OUT_LAMP,      0,new QTableWidgetItem(tr("机械手LAMP")));
    ui->tableWidget_Out->setItem(RBT_OUT_RUN_DES,   0,new QTableWidgetItem(tr("机械手RUN_DES")));
    ui->tableWidget_Out->setItem(RBT_OUT_RUN_SPEED, 0,new QTableWidgetItem(tr("机械手RUN_SPEED")));
    ui->tableWidget_Out->setItem(RBT_OUT_PRO_ADV,   0,new QTableWidgetItem(tr("机械手PRO_ADV")));
    ui->tableWidget_Out->setItem(RBT_OUT_PRO_RET,   0,new QTableWidgetItem(tr("机械手PRO_RET")));
    ui->tableWidget_Out->setItem(RBT_OUT_RUN_ADV,   0,new QTableWidgetItem(tr("机械手RUN_ADV")));
    ui->tableWidget_Out->setItem(RBT_OUT_RUN_RET,   0,new QTableWidgetItem(tr("机械手RUN_RET")));
    ui->tableWidget_Out->setItem(RBT_OUT_OIL,       0,new QTableWidgetItem(tr("机械手OIL")));
    ui->tableWidget_Out->setItem(RBT_OUT_RUN_HOR,   0,new QTableWidgetItem(tr("机械手RUN_HOR")));
    ui->tableWidget_Out->setItem(RBT_OUT_RUN_VER,   0,new QTableWidgetItem(tr("机械手RUN_VER")));*/
    //--------------------------------------------------------------------------------------------
    //pyq输出默认名称
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        //主板 输出默认名称
        ui->tableWidget_Out->setItem(MAIN_Y00,1,new QTableWidgetItem(QString::fromUtf8("Main-Y00")));
        ui->tableWidget_Out->setItem(MAIN_Y01,1,new QTableWidgetItem(QString::fromUtf8("Main-Y01")));
        ui->tableWidget_Out->setItem(MAIN_Y02,1,new QTableWidgetItem(QString::fromUtf8("Main-Y02")));
        ui->tableWidget_Out->setItem(MAIN_Y03,1,new QTableWidgetItem(QString::fromUtf8("Main-Y03")));
        ui->tableWidget_Out->setItem(MAIN_Y04,1,new QTableWidgetItem(QString::fromUtf8("Main-Y04")));
        ui->tableWidget_Out->setItem(MAIN_Y05,1,new QTableWidgetItem(QString::fromUtf8("Main-Y05")));
        ui->tableWidget_Out->setItem(MAIN_Y06,1,new QTableWidgetItem(QString::fromUtf8("Main-Y06")));
        ui->tableWidget_Out->setItem(MAIN_Y07,1,new QTableWidgetItem(QString::fromUtf8("Main-Y07")));
        ui->tableWidget_Out->setItem(MAIN_Y08,1,new QTableWidgetItem(QString::fromUtf8("打油-Y08")));
        ui->tableWidget_Out->setItem(MAIN_Y09,1,new QTableWidgetItem(QString::fromUtf8("Main-Y09")));
        ui->tableWidget_Out->setItem(MAIN_Y10,1,new QTableWidgetItem(QString::fromUtf8("Main-Y10")));
        ui->tableWidget_Out->setItem(MAIN_Y11,1,new QTableWidgetItem(QString::fromUtf8("吸具1-Y11")));
        ui->tableWidget_Out->setItem(MAIN_Y12,1,new QTableWidgetItem(QString::fromUtf8("吸具2-Y12")));
        ui->tableWidget_Out->setItem(MAIN_Y13,1,new QTableWidgetItem(QString::fromUtf8("抱具1-Y13")));
        ui->tableWidget_Out->setItem(MAIN_Y14,1,new QTableWidgetItem(QString::fromUtf8("抱具2-Y14")));
        ui->tableWidget_Out->setItem(MAIN_Y15,1,new QTableWidgetItem(QString::fromUtf8("抱具3-Y15")));

        ui->tableWidget_Out->setItem(EM1_Y00,1,new QTableWidgetItem(QString::fromUtf8("抱具4-Y16")));
        ui->tableWidget_Out->setItem(EM1_Y01,1,new QTableWidgetItem(QString::fromUtf8("Main-Y17")));
#if (FACTORY == FA_BEISHITE_CN)
        ui->tableWidget_Out->setItem(EM1_Y02,1,new QTableWidgetItem(QString::fromUtf8("副臂夹Y18")));
        ui->tableWidget_Out->setItem(EM1_Y03,1,new QTableWidgetItem(QString::fromUtf8("刀1Y19")));
        ui->tableWidget_Out->setItem(EM1_Y04,1,new QTableWidgetItem(QString::fromUtf8("刀2Y20")));

#else
        ui->tableWidget_Out->setItem(EM1_Y02,1,new QTableWidgetItem(QString::fromUtf8("Main-Y18")));
        ui->tableWidget_Out->setItem(EM1_Y03,1,new QTableWidgetItem(QString::fromUtf8("Main-Y19")));
        ui->tableWidget_Out->setItem(EM1_Y04,1,new QTableWidgetItem(QString::fromUtf8("Main-Y20")));
#endif
        ui->tableWidget_Out->setItem(EM1_Y05,1,new QTableWidgetItem(QString::fromUtf8("Main-Y21")));
        ui->tableWidget_Out->setItem(EM1_Y06,1,new QTableWidgetItem(QString::fromUtf8("Main-Y22")));
#if (FACTORY == FA_BEISHITE_CN)
        ui->tableWidget_Out->setItem(EM1_Y07,1,new QTableWidgetItem(QString::fromUtf8("吸3Y23")));
        ui->tableWidget_Out->setItem(EM1_Y08,1,new QTableWidgetItem(QString::fromUtf8("吸4Y24")));
#else
        ui->tableWidget_Out->setItem(EM1_Y07,1,new QTableWidgetItem(QString::fromUtf8("Main-Y23")));
        ui->tableWidget_Out->setItem(EM1_Y08,1,new QTableWidgetItem(QString::fromUtf8("Main-Y24")));
#endif
        ui->tableWidget_Out->setItem(EM1_Y09,1,new QTableWidgetItem(QString::fromUtf8("Main-Y25")));
        ui->tableWidget_Out->setItem(EM1_Y10,1,new QTableWidgetItem(QString::fromUtf8("Main-Y26")));
        ui->tableWidget_Out->setItem(EM1_Y11,1,new QTableWidgetItem(QString::fromUtf8("Main-Y27")));
        ui->tableWidget_Out->setItem(EM1_Y12,1,new QTableWidgetItem(QString::fromUtf8("Main-Y28")));
        ui->tableWidget_Out->setItem(EM1_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y01")));
        ui->tableWidget_Out->setItem(EM1_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y02")));
        ui->tableWidget_Out->setItem(EM1_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y03")));

        ui->tableWidget_Out->setItem(EM2_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y04")));
        ui->tableWidget_Out->setItem(EM2_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y05")));
        ui->tableWidget_Out->setItem(EM2_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y06")));
        ui->tableWidget_Out->setItem(EM2_Y03,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y07")));
        ui->tableWidget_Out->setItem(EM2_Y04,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y08")));
        ui->tableWidget_Out->setItem(EM2_Y05,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y09")));
        ui->tableWidget_Out->setItem(EM2_Y06,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y10")));
        ui->tableWidget_Out->setItem(EM2_Y07,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y11")));
        ui->tableWidget_Out->setItem(EM2_Y08,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y12")));
        ui->tableWidget_Out->setItem(EM2_Y09,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y13")));
        ui->tableWidget_Out->setItem(EM2_Y10,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y14")));
        ui->tableWidget_Out->setItem(EM2_Y11,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y15")));
        ui->tableWidget_Out->setItem(EM2_Y12,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y16")));
        ui->tableWidget_Out->setItem(EM2_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y01")));
        ui->tableWidget_Out->setItem(EM2_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y02")));
        ui->tableWidget_Out->setItem(EM2_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y03")));
        //扩展2
        ui->tableWidget_Out->setItem(EM3_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y04")));
        ui->tableWidget_Out->setItem(EM3_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y05")));
        ui->tableWidget_Out->setItem(EM3_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y06")));
        ui->tableWidget_Out->setItem(EM3_Y03,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y07")));
        ui->tableWidget_Out->setItem(EM3_Y04,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y08")));
        ui->tableWidget_Out->setItem(EM3_Y05,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y09")));
        ui->tableWidget_Out->setItem(EM3_Y06,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y10")));
        ui->tableWidget_Out->setItem(EM3_Y07,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y11")));
        ui->tableWidget_Out->setItem(EM3_Y08,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y12")));
        ui->tableWidget_Out->setItem(EM3_Y09,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y13")));
        ui->tableWidget_Out->setItem(EM3_Y10,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y14")));
        ui->tableWidget_Out->setItem(EM3_Y11,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y15")));
        ui->tableWidget_Out->setItem(EM3_Y12,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y16")));
        ui->tableWidget_Out->setItem(EM3_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y01")));
        ui->tableWidget_Out->setItem(EM3_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y02")));
        ui->tableWidget_Out->setItem(EM3_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y03")));
        //扩展3
        ui->tableWidget_Out->setItem(EM4_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y04")));
        ui->tableWidget_Out->setItem(EM4_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y05")));
        ui->tableWidget_Out->setItem(EM4_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y06")));
        ui->tableWidget_Out->setItem(EM4_Y03,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y07")));
        ui->tableWidget_Out->setItem(EM4_Y04,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y08")));
        ui->tableWidget_Out->setItem(EM4_Y05,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y09")));
        ui->tableWidget_Out->setItem(EM4_Y06,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y10")));
        ui->tableWidget_Out->setItem(EM4_Y07,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y11")));
        ui->tableWidget_Out->setItem(EM4_Y08,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y12")));
        ui->tableWidget_Out->setItem(EM4_Y09,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y13")));
        ui->tableWidget_Out->setItem(EM4_Y10,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y14")));
        ui->tableWidget_Out->setItem(EM4_Y11,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y15")));
        ui->tableWidget_Out->setItem(EM4_Y12,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y16")));
        ui->tableWidget_Out->setItem(EM4_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y01")));
        ui->tableWidget_Out->setItem(EM4_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y02")));
        ui->tableWidget_Out->setItem(EM4_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y03")));
        //扩展4
        ui->tableWidget_Out->setItem(MAIN_Y16,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y04")));
        ui->tableWidget_Out->setItem(MAIN_Y17,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y05")));
        ui->tableWidget_Out->setItem(MAIN_Y18,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y06")));
        ui->tableWidget_Out->setItem(MAIN_Y19,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y07")));
        ui->tableWidget_Out->setItem(MAIN_Y20,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y08")));
        ui->tableWidget_Out->setItem(MAIN_Y21,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y09")));
        ui->tableWidget_Out->setItem(MAIN_Y22,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y10")));
        ui->tableWidget_Out->setItem(MAIN_Y23,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y11")));
        ui->tableWidget_Out->setItem(MAIN_Y24,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y12")));
        ui->tableWidget_Out->setItem(MAIN_Y25,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y13")));
        ui->tableWidget_Out->setItem(MAIN_Y26,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y14")));
        ui->tableWidget_Out->setItem(MAIN_Y27,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y15")));
        ui->tableWidget_Out->setItem(MAIN_Y28,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y16")));
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        //主板 输出默认名称
        ui->tableWidget_Out->setItem(MAIN_Y00,1,new QTableWidgetItem(QString::fromUtf8("Main-Y00")));
        ui->tableWidget_Out->setItem(MAIN_Y01,1,new QTableWidgetItem(QString::fromUtf8("Main-Y01")));
        ui->tableWidget_Out->setItem(MAIN_Y02,1,new QTableWidgetItem(QString::fromUtf8("Main-Y02")));
        ui->tableWidget_Out->setItem(MAIN_Y03,1,new QTableWidgetItem(QString::fromUtf8("Main-Y03")));
        ui->tableWidget_Out->setItem(MAIN_Y04,1,new QTableWidgetItem(QString::fromUtf8("Main-Y04")));
        ui->tableWidget_Out->setItem(MAIN_Y05,1,new QTableWidgetItem(QString::fromUtf8("Main-Y05")));
        ui->tableWidget_Out->setItem(MAIN_Y06,1,new QTableWidgetItem(QString::fromUtf8("Main-Y06")));
        ui->tableWidget_Out->setItem(MAIN_Y07,1,new QTableWidgetItem(QString::fromUtf8("Main-Y07")));
        ui->tableWidget_Out->setItem(MAIN_Y08,1,new QTableWidgetItem(QString::fromUtf8("吸具1-Y08")));
        ui->tableWidget_Out->setItem(MAIN_Y09,1,new QTableWidgetItem(QString::fromUtf8("吸具2-Y09")));
        ui->tableWidget_Out->setItem(MAIN_Y10,1,new QTableWidgetItem(QString::fromUtf8("抱具1-Y10")));
        ui->tableWidget_Out->setItem(MAIN_Y11,1,new QTableWidgetItem(QString::fromUtf8("抱具2-Y11")));
        ui->tableWidget_Out->setItem(MAIN_Y12,1,new QTableWidgetItem(QString::fromUtf8("抱具3-Y12")));
        ui->tableWidget_Out->setItem(MAIN_Y13,1,new QTableWidgetItem(QString::fromUtf8("抱具4-Y13")));
        ui->tableWidget_Out->setItem(MAIN_Y14,1,new QTableWidgetItem(QString::fromUtf8("Main-Y14")));
        ui->tableWidget_Out->setItem(MAIN_Y15,1,new QTableWidgetItem(QString::fromUtf8("Main-Y15")));

        ui->tableWidget_Out->setItem(EM1_Y00,1,new QTableWidgetItem(QString::fromUtf8("Main-Y16")));
        ui->tableWidget_Out->setItem(EM1_Y01,1,new QTableWidgetItem(QString::fromUtf8("Main-Y17")));
        ui->tableWidget_Out->setItem(EM1_Y02,1,new QTableWidgetItem(QString::fromUtf8("Main-Y18")));
        ui->tableWidget_Out->setItem(EM1_Y03,1,new QTableWidgetItem(QString::fromUtf8("Main-Y19")));
        ui->tableWidget_Out->setItem(EM1_Y04,1,new QTableWidgetItem(QString::fromUtf8("Main-Y20")));
        ui->tableWidget_Out->setItem(EM1_Y05,1,new QTableWidgetItem(QString::fromUtf8("运行灯-Y21")));
        ui->tableWidget_Out->setItem(EM1_Y06,1,new QTableWidgetItem(QString::fromUtf8("Main-Y22")));
        ui->tableWidget_Out->setItem(EM1_Y07,1,new QTableWidgetItem(QString::fromUtf8("打油-Y23")));
        ui->tableWidget_Out->setItem(EM1_Y08,1,new QTableWidgetItem(QString::fromUtf8("")));
        ui->tableWidget_Out->setItem(EM1_Y09,1,new QTableWidgetItem(QString::fromUtf8("")));
        ui->tableWidget_Out->setItem(EM1_Y10,1,new QTableWidgetItem(QString::fromUtf8("")));
        ui->tableWidget_Out->setItem(EM1_Y11,1,new QTableWidgetItem(QString::fromUtf8("")));
        ui->tableWidget_Out->setItem(EM1_Y12,1,new QTableWidgetItem(QString::fromUtf8("")));
        ui->tableWidget_Out->setItem(EM1_Y13,1,new QTableWidgetItem(QString::fromUtf8("")));
        ui->tableWidget_Out->setItem(EM1_Y14,1,new QTableWidgetItem(QString::fromUtf8("")));
        ui->tableWidget_Out->setItem(EM1_Y15,1,new QTableWidgetItem(QString::fromUtf8("")));

        ui->tableWidget_Out->setItem(EM2_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y01")));
        ui->tableWidget_Out->setItem(EM2_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y02")));
        ui->tableWidget_Out->setItem(EM2_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y03")));
        ui->tableWidget_Out->setItem(EM2_Y03,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y04")));
        ui->tableWidget_Out->setItem(EM2_Y04,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y05")));
        ui->tableWidget_Out->setItem(EM2_Y05,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y06")));
        ui->tableWidget_Out->setItem(EM2_Y06,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y07")));
        ui->tableWidget_Out->setItem(EM2_Y07,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y08")));
        ui->tableWidget_Out->setItem(EM2_Y08,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y09")));
        ui->tableWidget_Out->setItem(EM2_Y09,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y10")));
        ui->tableWidget_Out->setItem(EM2_Y10,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y11")));
        ui->tableWidget_Out->setItem(EM2_Y11,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y12")));
        ui->tableWidget_Out->setItem(EM2_Y12,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y13")));
        ui->tableWidget_Out->setItem(EM2_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y14")));
        ui->tableWidget_Out->setItem(EM2_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y15")));
        ui->tableWidget_Out->setItem(EM2_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y16")));
        //扩展2
        ui->tableWidget_Out->setItem(EM3_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y01")));
        ui->tableWidget_Out->setItem(EM3_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y02")));
        ui->tableWidget_Out->setItem(EM3_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y03")));
        ui->tableWidget_Out->setItem(EM3_Y03,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y04")));
        ui->tableWidget_Out->setItem(EM3_Y04,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y05")));
        ui->tableWidget_Out->setItem(EM3_Y05,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y06")));
        ui->tableWidget_Out->setItem(EM3_Y06,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y07")));
        ui->tableWidget_Out->setItem(EM3_Y07,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y08")));
        ui->tableWidget_Out->setItem(EM3_Y08,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y09")));
        ui->tableWidget_Out->setItem(EM3_Y09,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y10")));
        ui->tableWidget_Out->setItem(EM3_Y10,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y11")));
        ui->tableWidget_Out->setItem(EM3_Y11,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y12")));
        ui->tableWidget_Out->setItem(EM3_Y12,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y13")));
        ui->tableWidget_Out->setItem(EM3_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y14")));
        ui->tableWidget_Out->setItem(EM3_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y15")));
        ui->tableWidget_Out->setItem(EM3_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y16")));
        //扩展3
        ui->tableWidget_Out->setItem(EM4_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y01")));
        ui->tableWidget_Out->setItem(EM4_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y02")));
        ui->tableWidget_Out->setItem(EM4_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y03")));
        ui->tableWidget_Out->setItem(EM4_Y03,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y04")));
        ui->tableWidget_Out->setItem(EM4_Y04,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y05")));
        ui->tableWidget_Out->setItem(EM4_Y05,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y06")));
        ui->tableWidget_Out->setItem(EM4_Y06,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y07")));
        ui->tableWidget_Out->setItem(EM4_Y07,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y08")));
        ui->tableWidget_Out->setItem(EM4_Y08,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y09")));
        ui->tableWidget_Out->setItem(EM4_Y09,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y10")));
        ui->tableWidget_Out->setItem(EM4_Y10,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y11")));
        ui->tableWidget_Out->setItem(EM4_Y11,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y12")));
        ui->tableWidget_Out->setItem(EM4_Y12,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y13")));
        ui->tableWidget_Out->setItem(EM4_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y14")));
        ui->tableWidget_Out->setItem(EM4_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y15")));
        ui->tableWidget_Out->setItem(EM4_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y16")));
        //扩展4
        ui->tableWidget_Out->setItem(MAIN_Y16,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y01")));
        ui->tableWidget_Out->setItem(MAIN_Y17,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y02")));
        ui->tableWidget_Out->setItem(MAIN_Y18,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y03")));
        ui->tableWidget_Out->setItem(MAIN_Y19,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y04")));
        ui->tableWidget_Out->setItem(MAIN_Y20,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y05")));
        ui->tableWidget_Out->setItem(MAIN_Y21,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y06")));
        ui->tableWidget_Out->setItem(MAIN_Y22,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y07")));
        ui->tableWidget_Out->setItem(MAIN_Y23,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y08")));
        ui->tableWidget_Out->setItem(MAIN_Y24,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y09")));
        ui->tableWidget_Out->setItem(MAIN_Y25,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y10")));
        ui->tableWidget_Out->setItem(MAIN_Y26,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y11")));
        ui->tableWidget_Out->setItem(MAIN_Y27,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y12")));
        ui->tableWidget_Out->setItem(MAIN_Y28,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y13")));
        ui->tableWidget_Out->setItem(MAIN_Y29,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y14")));
        ui->tableWidget_Out->setItem(MAIN_Y30,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y15")));
        ui->tableWidget_Out->setItem(MAIN_Y31,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y16")));
    }
    else
    {
        ui->tableWidget_Out->setItem(MAIN_Y00,1,new QTableWidgetItem(QString::fromUtf8("Main-Y00")));
        ui->tableWidget_Out->setItem(MAIN_Y01,1,new QTableWidgetItem(QString::fromUtf8("Main-Y01")));
        ui->tableWidget_Out->setItem(MAIN_Y02,1,new QTableWidgetItem(QString::fromUtf8("Main-Y02")));
        ui->tableWidget_Out->setItem(MAIN_Y03,1,new QTableWidgetItem(QString::fromUtf8("Main-Y03")));
        ui->tableWidget_Out->setItem(MAIN_Y04,1,new QTableWidgetItem(QString::fromUtf8("Main-Y04")));
        ui->tableWidget_Out->setItem(MAIN_Y05,1,new QTableWidgetItem(QString::fromUtf8("Main-Y05")));
        ui->tableWidget_Out->setItem(MAIN_Y06,1,new QTableWidgetItem(QString::fromUtf8("Main-Y06")));
        ui->tableWidget_Out->setItem(MAIN_Y07,1,new QTableWidgetItem(QString::fromUtf8("Main-Y07")));
        ui->tableWidget_Out->setItem(MAIN_Y08,1,new QTableWidgetItem(QString::fromUtf8("Main-Y08")));
        ui->tableWidget_Out->setItem(MAIN_Y09,1,new QTableWidgetItem(QString::fromUtf8("Main-Y09")));
        ui->tableWidget_Out->setItem(MAIN_Y10,1,new QTableWidgetItem(QString::fromUtf8("Main-Y10")));
        ui->tableWidget_Out->setItem(MAIN_Y11,1,new QTableWidgetItem(QString::fromUtf8("Main-Y11")));
        ui->tableWidget_Out->setItem(MAIN_Y12,1,new QTableWidgetItem(tr("吸具1-Y12")));
        ui->tableWidget_Out->setItem(MAIN_Y13,1,new QTableWidgetItem(tr("吸具2-Y13")));
        ui->tableWidget_Out->setItem(MAIN_Y14,1,new QTableWidgetItem(tr("抱具1-Y14")));
        ui->tableWidget_Out->setItem(MAIN_Y15,1,new QTableWidgetItem(QString::fromUtf8("Main-Y15")));
        //扩展输出
        if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
        {
            ui->tableWidget_Out->setItem(EM1_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y00")));
            ui->tableWidget_Out->setItem(EM1_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y01")));
            ui->tableWidget_Out->setItem(EM1_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y02")));
            ui->tableWidget_Out->setItem(EM1_Y03,1,new QTableWidgetItem(QString::fromUtf8("爪手阀-Y03")));
            ui->tableWidget_Out->setItem(EM1_Y04,1,new QTableWidgetItem(QString::fromUtf8("动模吹气1-Y04")));
            ui->tableWidget_Out->setItem(EM1_Y05,1,new QTableWidgetItem(QString::fromUtf8("动模吹气2-Y05")));
            ui->tableWidget_Out->setItem(EM1_Y06,1,new QTableWidgetItem(QString::fromUtf8("动模吹气3-Y06")));
            ui->tableWidget_Out->setItem(EM1_Y07,1,new QTableWidgetItem(QString::fromUtf8("动模吹气4-Y07")));
            ui->tableWidget_Out->setItem(EM1_Y08,1,new QTableWidgetItem(QString::fromUtf8("定模吹气1-Y08")));
            ui->tableWidget_Out->setItem(EM1_Y09,1,new QTableWidgetItem(QString::fromUtf8("定模吹气2-Y09")));
            ui->tableWidget_Out->setItem(EM1_Y10,1,new QTableWidgetItem(QString::fromUtf8("定模吹气3-Y10")));
            ui->tableWidget_Out->setItem(EM1_Y11,1,new QTableWidgetItem(QString::fromUtf8("定模吹气4-Y11")));
            ui->tableWidget_Out->setItem(EM1_Y12,1,new QTableWidgetItem(QString::fromUtf8("动模水阀1-Y12")));
            ui->tableWidget_Out->setItem(EM1_Y13,1,new QTableWidgetItem(QString::fromUtf8("动模水阀2-Y13")));
            ui->tableWidget_Out->setItem(EM1_Y14,1,new QTableWidgetItem(QString::fromUtf8("动模水阀3-Y14")));
            ui->tableWidget_Out->setItem(EM1_Y15,1,new QTableWidgetItem(QString::fromUtf8("动模水阀4-Y15")));

            ui->tableWidget_Out->setItem(EM2_Y00,1,new QTableWidgetItem(QString::fromUtf8("定模水阀1-Y00")));
            ui->tableWidget_Out->setItem(EM2_Y01,1,new QTableWidgetItem(QString::fromUtf8("定模水阀2-Y01")));
            ui->tableWidget_Out->setItem(EM2_Y02,1,new QTableWidgetItem(QString::fromUtf8("定模水阀3-Y02")));
            ui->tableWidget_Out->setItem(EM2_Y03,1,new QTableWidgetItem(QString::fromUtf8("定模水阀4-Y03")));
            ui->tableWidget_Out->setItem(EM2_Y04,1,new QTableWidgetItem(QString::fromUtf8("输送带-Y04")));
            ui->tableWidget_Out->setItem(EM2_Y05,1,new QTableWidgetItem(QString::fromUtf8("备用-Y05")));
            ui->tableWidget_Out->setItem(EM2_Y06,1,new QTableWidgetItem(QString::fromUtf8("再循环启动-Y06")));
            ui->tableWidget_Out->setItem(EM2_Y07,1,new QTableWidgetItem(QString::fromUtf8("备用-Y07")));
            ui->tableWidget_Out->setItem(EM2_Y08,1,new QTableWidgetItem(QString::fromUtf8("备用-Y08")));
            ui->tableWidget_Out->setItem(EM2_Y09,1,new QTableWidgetItem(QString::fromUtf8("备用-Y09")));
            ui->tableWidget_Out->setItem(EM2_Y10,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y10")));
            ui->tableWidget_Out->setItem(EM2_Y11,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y11")));
            ui->tableWidget_Out->setItem(EM2_Y12,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y12")));
            ui->tableWidget_Out->setItem(EM2_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y13")));
            ui->tableWidget_Out->setItem(EM2_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y14")));
            ui->tableWidget_Out->setItem(EM2_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y15")));
        }
        else
        {
            if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            {
                ui->tableWidget_Out->setItem(EM1_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y00")));
                ui->tableWidget_Out->setItem(EM1_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y01")));
                ui->tableWidget_Out->setItem(EM1_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y02")));
                ui->tableWidget_Out->setItem(EM1_Y03,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y03")));
                ui->tableWidget_Out->setItem(EM1_Y04,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y04")));
                ui->tableWidget_Out->setItem(EM1_Y05,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y05")));
                ui->tableWidget_Out->setItem(EM1_Y06,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y06")));
                ui->tableWidget_Out->setItem(EM1_Y07,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y07")));
                ui->tableWidget_Out->setItem(EM1_Y08,1,new QTableWidgetItem(QString::fromUtf8("定模吹气1-Y08")));
                ui->tableWidget_Out->setItem(EM1_Y09,1,new QTableWidgetItem(QString::fromUtf8("定模吹气2-Y09")));
                ui->tableWidget_Out->setItem(EM1_Y10,1,new QTableWidgetItem(QString::fromUtf8("定模吹气3-Y10")));
                ui->tableWidget_Out->setItem(EM1_Y11,1,new QTableWidgetItem(QString::fromUtf8("定模吹气4-Y11")));
                ui->tableWidget_Out->setItem(EM1_Y12,1,new QTableWidgetItem(QString::fromUtf8("动模水阀1-Y12")));
                ui->tableWidget_Out->setItem(EM1_Y13,1,new QTableWidgetItem(QString::fromUtf8("动模水阀2-Y13")));
                ui->tableWidget_Out->setItem(EM1_Y14,1,new QTableWidgetItem(QString::fromUtf8("动模水阀3-Y14")));
                ui->tableWidget_Out->setItem(EM1_Y15,1,new QTableWidgetItem(QString::fromUtf8("动模水阀4-Y15")));
            }
            else
            {
                ui->tableWidget_Out->setItem(EM1_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y01")));
                ui->tableWidget_Out->setItem(EM1_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM1-Y02")));
                ui->tableWidget_Out->setItem(EM1_Y02,1,new QTableWidgetItem(tr("吸具1-Y03")));
                ui->tableWidget_Out->setItem(EM1_Y03,1,new QTableWidgetItem(tr("吸具2-Y04")));
                ui->tableWidget_Out->setItem(EM1_Y04,1,new QTableWidgetItem(tr("抱具1-Y05")));
                ui->tableWidget_Out->setItem(EM1_Y05,1,new QTableWidgetItem(tr("抱具2-Y06")));
                ui->tableWidget_Out->setItem(EM1_Y06,1,new QTableWidgetItem(tr("抱具3-Y07")));
                ui->tableWidget_Out->setItem(EM1_Y07,1,new QTableWidgetItem(tr("抱具4-Y08")));
                ui->tableWidget_Out->setItem(EM1_Y08,1,new QTableWidgetItem(tr("定模吹气1-Y09")));
                ui->tableWidget_Out->setItem(EM1_Y09,1,new QTableWidgetItem(tr("定模吹气2-Y10")));
                ui->tableWidget_Out->setItem(EM1_Y10,1,new QTableWidgetItem(tr("定模吹气3-Y11")));
                ui->tableWidget_Out->setItem(EM1_Y11,1,new QTableWidgetItem(tr("定模吹气4-Y12")));
                ui->tableWidget_Out->setItem(EM1_Y12,1,new QTableWidgetItem(tr("动模水阀1-Y13")));
                ui->tableWidget_Out->setItem(EM1_Y13,1,new QTableWidgetItem(tr("动模水阀2-Y14")));
                ui->tableWidget_Out->setItem(EM1_Y14,1,new QTableWidgetItem(tr("动模水阀3-Y15")));
                ui->tableWidget_Out->setItem(EM1_Y15,1,new QTableWidgetItem(tr("动模水阀4-Y16")));
            }

            ui->tableWidget_Out->setItem(EM2_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y00")));
            ui->tableWidget_Out->setItem(EM2_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y01")));
            ui->tableWidget_Out->setItem(EM2_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y02")));
            ui->tableWidget_Out->setItem(EM2_Y03,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y03")));
            ui->tableWidget_Out->setItem(EM2_Y04,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y04")));
            ui->tableWidget_Out->setItem(EM2_Y05,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y05")));
            ui->tableWidget_Out->setItem(EM2_Y06,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y06")));
            ui->tableWidget_Out->setItem(EM2_Y07,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y07")));
            ui->tableWidget_Out->setItem(EM2_Y08,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y08")));
            ui->tableWidget_Out->setItem(EM2_Y09,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y09")));
            ui->tableWidget_Out->setItem(EM2_Y10,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y10")));
            ui->tableWidget_Out->setItem(EM2_Y11,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y11")));
            ui->tableWidget_Out->setItem(EM2_Y12,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y12")));
            ui->tableWidget_Out->setItem(EM2_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y13")));
            ui->tableWidget_Out->setItem(EM2_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y14")));
            ui->tableWidget_Out->setItem(EM2_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM2-Y15")));
        }
        ui->tableWidget_Out->setItem(EM3_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y00")));
        ui->tableWidget_Out->setItem(EM3_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y01")));
        ui->tableWidget_Out->setItem(EM3_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y02")));
        ui->tableWidget_Out->setItem(EM3_Y03,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y03")));
        ui->tableWidget_Out->setItem(EM3_Y04,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y04")));
        ui->tableWidget_Out->setItem(EM3_Y05,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y05")));
        ui->tableWidget_Out->setItem(EM3_Y06,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y06")));
        ui->tableWidget_Out->setItem(EM3_Y07,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y07")));
        ui->tableWidget_Out->setItem(EM3_Y08,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y08")));
        ui->tableWidget_Out->setItem(EM3_Y09,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y09")));
        ui->tableWidget_Out->setItem(EM3_Y10,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y10")));
        ui->tableWidget_Out->setItem(EM3_Y11,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y11")));
        ui->tableWidget_Out->setItem(EM3_Y12,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y12")));
        ui->tableWidget_Out->setItem(EM3_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y13")));
        ui->tableWidget_Out->setItem(EM3_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y14")));
        ui->tableWidget_Out->setItem(EM3_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM3-Y15")));

        ui->tableWidget_Out->setItem(EM4_Y00,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y00")));
        ui->tableWidget_Out->setItem(EM4_Y01,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y01")));
        ui->tableWidget_Out->setItem(EM4_Y02,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y02")));
        ui->tableWidget_Out->setItem(EM4_Y03,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y03")));
        ui->tableWidget_Out->setItem(EM4_Y04,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y04")));
        ui->tableWidget_Out->setItem(EM4_Y05,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y05")));
        ui->tableWidget_Out->setItem(EM4_Y06,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y06")));
        ui->tableWidget_Out->setItem(EM4_Y07,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y07")));
        ui->tableWidget_Out->setItem(EM4_Y08,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y08")));
        ui->tableWidget_Out->setItem(EM4_Y09,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y09")));
        ui->tableWidget_Out->setItem(EM4_Y10,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y10")));
        ui->tableWidget_Out->setItem(EM4_Y11,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y11")));
        ui->tableWidget_Out->setItem(EM4_Y12,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y12")));
        ui->tableWidget_Out->setItem(EM4_Y13,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y13")));
        ui->tableWidget_Out->setItem(EM4_Y14,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y14")));
        ui->tableWidget_Out->setItem(EM4_Y15,1,new QTableWidgetItem(QString::fromUtf8("EM4-Y15")));
    }

    //---------------------------------------------------------------------------------------
    //主板 输出修改的名称
    ui->tableWidget_Out->setItem(MAIN_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y00)));
    ui->tableWidget_Out->setItem(MAIN_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y01)));
    ui->tableWidget_Out->setItem(MAIN_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y02)));
    ui->tableWidget_Out->setItem(MAIN_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y03)));
    ui->tableWidget_Out->setItem(MAIN_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y04)));
    ui->tableWidget_Out->setItem(MAIN_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y05)));
    ui->tableWidget_Out->setItem(MAIN_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y06)));
    ui->tableWidget_Out->setItem(MAIN_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y07)));
    ui->tableWidget_Out->setItem(MAIN_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y08)));
    ui->tableWidget_Out->setItem(MAIN_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y09)));
    ui->tableWidget_Out->setItem(MAIN_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y10)));
    ui->tableWidget_Out->setItem(MAIN_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y11)));
    ui->tableWidget_Out->setItem(MAIN_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y12)));
    ui->tableWidget_Out->setItem(MAIN_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y13)));
    ui->tableWidget_Out->setItem(MAIN_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y14)));
    ui->tableWidget_Out->setItem(MAIN_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y15)));
    //PYQ
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        //扩展输入
        ui->tableWidget_Out->setItem(EM1_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y16)));
        ui->tableWidget_Out->setItem(EM1_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y17)));
        ui->tableWidget_Out->setItem(EM1_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y18)));
        ui->tableWidget_Out->setItem(EM1_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y19)));
        ui->tableWidget_Out->setItem(EM1_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y20)));
        ui->tableWidget_Out->setItem(EM1_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y21)));
        ui->tableWidget_Out->setItem(EM1_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y22)));
        ui->tableWidget_Out->setItem(EM1_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y23)));
        ui->tableWidget_Out->setItem(EM1_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y24)));
        ui->tableWidget_Out->setItem(EM1_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y25)));
        ui->tableWidget_Out->setItem(EM1_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y26)));
        ui->tableWidget_Out->setItem(EM1_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y27)));
        ui->tableWidget_Out->setItem(EM1_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y28)));

        ui->tableWidget_Out->setItem(EM1_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM1_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM1_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y02)));
        ui->tableWidget_Out->setItem(EM2_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y03)));
        ui->tableWidget_Out->setItem(EM2_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y04)));
        ui->tableWidget_Out->setItem(EM2_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y05)));
        ui->tableWidget_Out->setItem(EM2_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y06)));
        ui->tableWidget_Out->setItem(EM2_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y07)));
        ui->tableWidget_Out->setItem(EM2_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y08)));
        ui->tableWidget_Out->setItem(EM2_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y09)));
        ui->tableWidget_Out->setItem(EM2_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y10)));
        ui->tableWidget_Out->setItem(EM2_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y11)));
        ui->tableWidget_Out->setItem(EM2_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y12)));
        ui->tableWidget_Out->setItem(EM2_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y13)));
        ui->tableWidget_Out->setItem(EM2_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y14)));
        ui->tableWidget_Out->setItem(EM2_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y15)));

        ui->tableWidget_Out->setItem(EM2_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM2_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM2_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y02)));
        ui->tableWidget_Out->setItem(EM3_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y03)));
        ui->tableWidget_Out->setItem(EM3_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y04)));
        ui->tableWidget_Out->setItem(EM3_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y05)));
        ui->tableWidget_Out->setItem(EM3_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y06)));
        ui->tableWidget_Out->setItem(EM3_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y07)));
        ui->tableWidget_Out->setItem(EM3_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y08)));
        ui->tableWidget_Out->setItem(EM3_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y09)));
        ui->tableWidget_Out->setItem(EM3_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y10)));
        ui->tableWidget_Out->setItem(EM3_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y11)));
        ui->tableWidget_Out->setItem(EM3_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y12)));
        ui->tableWidget_Out->setItem(EM3_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y13)));
        ui->tableWidget_Out->setItem(EM3_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y14)));
        ui->tableWidget_Out->setItem(EM3_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y15)));

        ui->tableWidget_Out->setItem(EM3_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM3_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM3_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y02)));
        ui->tableWidget_Out->setItem(EM4_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y03)));
        ui->tableWidget_Out->setItem(EM4_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y04)));
        ui->tableWidget_Out->setItem(EM4_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y05)));
        ui->tableWidget_Out->setItem(EM4_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y06)));
        ui->tableWidget_Out->setItem(EM4_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y07)));
        ui->tableWidget_Out->setItem(EM4_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y08)));
        ui->tableWidget_Out->setItem(EM4_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y09)));
        ui->tableWidget_Out->setItem(EM4_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y10)));
        ui->tableWidget_Out->setItem(EM4_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y11)));
        ui->tableWidget_Out->setItem(EM4_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y12)));
        ui->tableWidget_Out->setItem(EM4_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y13)));
        ui->tableWidget_Out->setItem(EM4_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y14)));
        ui->tableWidget_Out->setItem(EM4_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y15)));

        ui->tableWidget_Out->setItem(EM4_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM4_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM4_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y02)));
        ui->tableWidget_Out->setItem(MAIN_Y16,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y03)));
        ui->tableWidget_Out->setItem(MAIN_Y17,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y04)));
        ui->tableWidget_Out->setItem(MAIN_Y18,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y05)));
        ui->tableWidget_Out->setItem(MAIN_Y19,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y06)));
        ui->tableWidget_Out->setItem(MAIN_Y20,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y07)));
        ui->tableWidget_Out->setItem(MAIN_Y21,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y08)));
        ui->tableWidget_Out->setItem(MAIN_Y22,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y09)));
        ui->tableWidget_Out->setItem(MAIN_Y23,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y10)));
        ui->tableWidget_Out->setItem(MAIN_Y24,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y11)));
        ui->tableWidget_Out->setItem(MAIN_Y25,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y12)));
        ui->tableWidget_Out->setItem(MAIN_Y26,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y13)));
        ui->tableWidget_Out->setItem(MAIN_Y27,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y14)));
        ui->tableWidget_Out->setItem(MAIN_Y28,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y15)));
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        //扩展输入
        ui->tableWidget_Out->setItem(EM1_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y16)));
        ui->tableWidget_Out->setItem(EM1_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y17)));
        ui->tableWidget_Out->setItem(EM1_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y18)));
        ui->tableWidget_Out->setItem(EM1_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y19)));
        ui->tableWidget_Out->setItem(EM1_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y20)));
        ui->tableWidget_Out->setItem(EM1_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y21)));
        ui->tableWidget_Out->setItem(EM1_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y22)));
        ui->tableWidget_Out->setItem(EM1_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y23)));
        ui->tableWidget_Out->setItem(EM1_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y24)));
        ui->tableWidget_Out->setItem(EM1_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y25)));
        ui->tableWidget_Out->setItem(EM1_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y26)));
        ui->tableWidget_Out->setItem(EM1_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y27)));
        ui->tableWidget_Out->setItem(EM1_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y28)));
        ui->tableWidget_Out->setItem(EM1_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y29)));
        ui->tableWidget_Out->setItem(EM1_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y30)));
        ui->tableWidget_Out->setItem(EM1_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(MAIN_VAR_Y31)));

        ui->tableWidget_Out->setItem(EM2_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM2_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM2_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y02)));
        ui->tableWidget_Out->setItem(EM2_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y03)));
        ui->tableWidget_Out->setItem(EM2_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y04)));
        ui->tableWidget_Out->setItem(EM2_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y05)));
        ui->tableWidget_Out->setItem(EM2_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y06)));
        ui->tableWidget_Out->setItem(EM2_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y07)));
        ui->tableWidget_Out->setItem(EM2_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y08)));
        ui->tableWidget_Out->setItem(EM2_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y09)));
        ui->tableWidget_Out->setItem(EM2_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y10)));
        ui->tableWidget_Out->setItem(EM2_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y11)));
        ui->tableWidget_Out->setItem(EM2_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y12)));
        ui->tableWidget_Out->setItem(EM2_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y13)));
        ui->tableWidget_Out->setItem(EM2_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y14)));
        ui->tableWidget_Out->setItem(EM2_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y15)));

        ui->tableWidget_Out->setItem(EM3_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM3_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM3_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y02)));
        ui->tableWidget_Out->setItem(EM3_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y03)));
        ui->tableWidget_Out->setItem(EM3_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y04)));
        ui->tableWidget_Out->setItem(EM3_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y05)));
        ui->tableWidget_Out->setItem(EM3_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y06)));
        ui->tableWidget_Out->setItem(EM3_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y07)));
        ui->tableWidget_Out->setItem(EM3_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y08)));
        ui->tableWidget_Out->setItem(EM3_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y09)));
        ui->tableWidget_Out->setItem(EM3_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y10)));
        ui->tableWidget_Out->setItem(EM3_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y11)));
        ui->tableWidget_Out->setItem(EM3_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y12)));
        ui->tableWidget_Out->setItem(EM3_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y13)));
        ui->tableWidget_Out->setItem(EM3_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y14)));
        ui->tableWidget_Out->setItem(EM3_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y15)));

        ui->tableWidget_Out->setItem(EM4_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM4_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM4_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y02)));
        ui->tableWidget_Out->setItem(EM4_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y03)));
        ui->tableWidget_Out->setItem(EM4_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y04)));
        ui->tableWidget_Out->setItem(EM4_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y05)));
        ui->tableWidget_Out->setItem(EM4_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y06)));
        ui->tableWidget_Out->setItem(EM4_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y07)));
        ui->tableWidget_Out->setItem(EM4_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y08)));
        ui->tableWidget_Out->setItem(EM4_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y09)));
        ui->tableWidget_Out->setItem(EM4_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y10)));
        ui->tableWidget_Out->setItem(EM4_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y11)));
        ui->tableWidget_Out->setItem(EM4_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y12)));
        ui->tableWidget_Out->setItem(EM4_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y13)));
        ui->tableWidget_Out->setItem(EM4_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y14)));
        ui->tableWidget_Out->setItem(EM4_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y15)));

        ui->tableWidget_Out->setItem(MAIN_Y16,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y00)));
        ui->tableWidget_Out->setItem(MAIN_Y17,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y01)));
        ui->tableWidget_Out->setItem(MAIN_Y18,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y02)));
        ui->tableWidget_Out->setItem(MAIN_Y19,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y03)));
        ui->tableWidget_Out->setItem(MAIN_Y20,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y04)));
        ui->tableWidget_Out->setItem(MAIN_Y21,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y05)));
        ui->tableWidget_Out->setItem(MAIN_Y22,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y06)));
        ui->tableWidget_Out->setItem(MAIN_Y23,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y07)));
        ui->tableWidget_Out->setItem(MAIN_Y24,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y08)));
        ui->tableWidget_Out->setItem(MAIN_Y25,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y09)));
        ui->tableWidget_Out->setItem(MAIN_Y26,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y10)));
        ui->tableWidget_Out->setItem(MAIN_Y27,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y11)));
        ui->tableWidget_Out->setItem(MAIN_Y28,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y12)));
        ui->tableWidget_Out->setItem(MAIN_Y29,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y13)));
        ui->tableWidget_Out->setItem(MAIN_Y30,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y14)));
        ui->tableWidget_Out->setItem(MAIN_Y31,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y15)));
    }
    else
    {
        //扩展输出
        ui->tableWidget_Out->setItem(EM1_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM1_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM1_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y02)));
        ui->tableWidget_Out->setItem(EM1_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y03)));
        ui->tableWidget_Out->setItem(EM1_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y04)));
        ui->tableWidget_Out->setItem(EM1_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y05)));
        ui->tableWidget_Out->setItem(EM1_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y06)));
        ui->tableWidget_Out->setItem(EM1_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y07)));
        ui->tableWidget_Out->setItem(EM1_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y08)));
        ui->tableWidget_Out->setItem(EM1_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y09)));
        ui->tableWidget_Out->setItem(EM1_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y10)));
        ui->tableWidget_Out->setItem(EM1_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y11)));
        ui->tableWidget_Out->setItem(EM1_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y12)));
        ui->tableWidget_Out->setItem(EM1_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y13)));
        ui->tableWidget_Out->setItem(EM1_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y14)));
        ui->tableWidget_Out->setItem(EM1_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM1_VAR_Y15)));

        ui->tableWidget_Out->setItem(EM2_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM2_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM2_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y02)));
        ui->tableWidget_Out->setItem(EM2_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y03)));
        ui->tableWidget_Out->setItem(EM2_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y04)));
        ui->tableWidget_Out->setItem(EM2_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y05)));
        ui->tableWidget_Out->setItem(EM2_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y06)));
        ui->tableWidget_Out->setItem(EM2_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y07)));
        ui->tableWidget_Out->setItem(EM2_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y08)));
        ui->tableWidget_Out->setItem(EM2_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y09)));
        ui->tableWidget_Out->setItem(EM2_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y10)));
        ui->tableWidget_Out->setItem(EM2_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y11)));
        ui->tableWidget_Out->setItem(EM2_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y12)));
        ui->tableWidget_Out->setItem(EM2_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y13)));
        ui->tableWidget_Out->setItem(EM2_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y14)));
        ui->tableWidget_Out->setItem(EM2_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM2_VAR_Y15)));

        ui->tableWidget_Out->setItem(EM3_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM3_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM3_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y02)));
        ui->tableWidget_Out->setItem(EM3_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y03)));
        ui->tableWidget_Out->setItem(EM3_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y04)));
        ui->tableWidget_Out->setItem(EM3_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y05)));
        ui->tableWidget_Out->setItem(EM3_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y06)));
        ui->tableWidget_Out->setItem(EM3_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y07)));
        ui->tableWidget_Out->setItem(EM3_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y08)));
        ui->tableWidget_Out->setItem(EM3_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y09)));
        ui->tableWidget_Out->setItem(EM3_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y10)));
        ui->tableWidget_Out->setItem(EM3_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y11)));
        ui->tableWidget_Out->setItem(EM3_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y12)));
        ui->tableWidget_Out->setItem(EM3_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y13)));
        ui->tableWidget_Out->setItem(EM3_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y14)));
        ui->tableWidget_Out->setItem(EM3_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM3_VAR_Y15)));

        ui->tableWidget_Out->setItem(EM4_Y00,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y00)));
        ui->tableWidget_Out->setItem(EM4_Y01,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y01)));
        ui->tableWidget_Out->setItem(EM4_Y02,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y02)));
        ui->tableWidget_Out->setItem(EM4_Y03,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y03)));
        ui->tableWidget_Out->setItem(EM4_Y04,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y04)));
        ui->tableWidget_Out->setItem(EM4_Y05,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y05)));
        ui->tableWidget_Out->setItem(EM4_Y06,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y06)));
        ui->tableWidget_Out->setItem(EM4_Y07,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y07)));
        ui->tableWidget_Out->setItem(EM4_Y08,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y08)));
        ui->tableWidget_Out->setItem(EM4_Y09,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y09)));
        ui->tableWidget_Out->setItem(EM4_Y10,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y10)));
        ui->tableWidget_Out->setItem(EM4_Y11,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y11)));
        ui->tableWidget_Out->setItem(EM4_Y12,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y12)));
        ui->tableWidget_Out->setItem(EM4_Y13,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y13)));
        ui->tableWidget_Out->setItem(EM4_Y14,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y14)));
        ui->tableWidget_Out->setItem(EM4_Y15,2,new QTableWidgetItem(xStringResource::GetModifyPortName(EM4_VAR_Y15)));
    }
}

void DialogPortEdit::setIOVisible()
{
    quint8 i;


    //pyq
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        for(i = 0; i < MAX_INPORT_NUM3; i++)
        {
            //输入表
            switch(i)
            {
            case MAIN_X00:
                ui->tableWidget_In->setRowHidden(MAIN_X00,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X00)));
                break;
            case MAIN_X01:
                ui->tableWidget_In->setRowHidden(MAIN_X01,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X01)));
                break;
            case MAIN_X02:
                ui->tableWidget_In->setRowHidden(MAIN_X02,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X02)));
                break;
            case MAIN_X03:
                ui->tableWidget_In->setRowHidden(MAIN_X03,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X03)));
                break;
            case MAIN_X04:
                ui->tableWidget_In->setRowHidden(MAIN_X04,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X04)));
                break;
            case MAIN_X05:
                ui->tableWidget_In->setRowHidden(MAIN_X05,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X05)));
                break;
            case MAIN_X06:
                ui->tableWidget_In->setRowHidden(MAIN_X06,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X06)));
                break;
            case MAIN_X07:
                ui->tableWidget_In->setRowHidden(MAIN_X07,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X07)));
                break;
            case MAIN_X08:
                ui->tableWidget_In->setRowHidden(MAIN_X08,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X08)));
                break;
            case MAIN_X09:
                ui->tableWidget_In->setRowHidden(MAIN_X09,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X09)));
                break;
            case MAIN_X10:
                ui->tableWidget_In->setRowHidden(MAIN_X10,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X10)));
                break;
            case MAIN_X11:
                ui->tableWidget_In->setRowHidden(MAIN_X11,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X11)));
                break;
            case MAIN_X12:
                ui->tableWidget_In->setRowHidden(MAIN_X12,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X12)));
                break;
            case MAIN_X13:
                ui->tableWidget_In->setRowHidden(MAIN_X13,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X13)));
                break;
            case MAIN_X14:
                ui->tableWidget_In->setRowHidden(MAIN_X14,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X14)));
                break;
            case MAIN_X15:
                ui->tableWidget_In->setRowHidden(MAIN_X15,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X15)));
                break;

            case EM1_X00:
                ui->tableWidget_In->setRowHidden(EM1_X00,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X16)));
                break;
            case EM1_X01:
                ui->tableWidget_In->setRowHidden(EM1_X01,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X17)));
                break;
            case EM1_X02:
                ui->tableWidget_In->setRowHidden(EM1_X02,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X18)));
                break;
            case EM1_X03:
                ui->tableWidget_In->setRowHidden(EM1_X03,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X19)));
                break;
            case EM1_X04:
                ui->tableWidget_In->setRowHidden(EM1_X04,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X20)));
                break;
            case EM1_X05:
                ui->tableWidget_In->setRowHidden(EM1_X05,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X21)));
                break;
            case EM1_X06:
                ui->tableWidget_In->setRowHidden(EM1_X06,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X22)));
                break;
            case EM1_X07:
                ui->tableWidget_In->setRowHidden(EM1_X07,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X23)));
                break;
            case EM1_X08:
                ui->tableWidget_In->setRowHidden(EM1_X08,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X24)));
                break;
            case EM1_X09:
                ui->tableWidget_In->setRowHidden(EM1_X09,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X25)));
                break;
            case EM1_X10:
                ui->tableWidget_In->setRowHidden(EM1_X10,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X26)));
                break;
            case EM1_X11:
                ui->tableWidget_In->setRowHidden(EM1_X11,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X27)));
                break;

            case EM1_X12:
                ui->tableWidget_In->setRowHidden(EM1_X12,!(xIoPort::IsVisibleExtIn(EM1_VAR_X00)));
                break;
            case EM1_X13:
                ui->tableWidget_In->setRowHidden(EM1_X13,!(xIoPort::IsVisibleExtIn(EM1_VAR_X01)));
                break;
            case EM1_X14:
                ui->tableWidget_In->setRowHidden(EM1_X14,!(xIoPort::IsVisibleExtIn(EM1_VAR_X02)));
                break;
            case EM1_X15:
                ui->tableWidget_In->setRowHidden(EM1_X15,!(xIoPort::IsVisibleExtIn(EM1_VAR_X03)));
                break;
            case EM2_X00:
                ui->tableWidget_In->setRowHidden(EM2_X00,!(xIoPort::IsVisibleExtIn(EM1_VAR_X04)));
                break;
            case EM2_X01:
                ui->tableWidget_In->setRowHidden(EM2_X01,!(xIoPort::IsVisibleExtIn(EM1_VAR_X05)));
                break;
            case EM2_X02:
                ui->tableWidget_In->setRowHidden(EM2_X02,!(xIoPort::IsVisibleExtIn(EM1_VAR_X06)));
                break;
            case EM2_X03:
                ui->tableWidget_In->setRowHidden(EM2_X03,!(xIoPort::IsVisibleExtIn(EM1_VAR_X07)));
                break;
            case EM2_X04:
                ui->tableWidget_In->setRowHidden(EM2_X04,!(xIoPort::IsVisibleExtIn(EM1_VAR_X08)));
                break;
            case EM2_X05:
                ui->tableWidget_In->setRowHidden(EM2_X05,!(xIoPort::IsVisibleExtIn(EM1_VAR_X09)));
                break;
            case EM2_X06:
                ui->tableWidget_In->setRowHidden(EM2_X06,!(xIoPort::IsVisibleExtIn(EM1_VAR_X10)));
                break;
            case EM2_X07:
                ui->tableWidget_In->setRowHidden(EM2_X07,!(xIoPort::IsVisibleExtIn(EM1_VAR_X11)));
                break;
            case EM2_X08:
                ui->tableWidget_In->setRowHidden(EM2_X08,!(xIoPort::IsVisibleExtIn(EM1_VAR_X12)));
                break;
            case EM2_X09:
                ui->tableWidget_In->setRowHidden(EM2_X09,!(xIoPort::IsVisibleExtIn(EM1_VAR_X13)));
                break;
            case EM2_X10:
                ui->tableWidget_In->setRowHidden(EM2_X10,!(xIoPort::IsVisibleExtIn(EM1_VAR_X14)));
                break;
            case EM2_X11:
                ui->tableWidget_In->setRowHidden(EM2_X11,!(xIoPort::IsVisibleExtIn(EM1_VAR_X15)));
                break;

            case EM2_X12:
                ui->tableWidget_In->setRowHidden(EM2_X12,!(xIoPort::IsVisibleExtIn(EM2_VAR_X00)));
                break;
            case EM2_X13:
                ui->tableWidget_In->setRowHidden(EM2_X13,!(xIoPort::IsVisibleExtIn(EM2_VAR_X01)));
                break;
            case EM2_X14:
                ui->tableWidget_In->setRowHidden(EM2_X14,!(xIoPort::IsVisibleExtIn(EM2_VAR_X02)));
                break;
            case EM2_X15:
                ui->tableWidget_In->setRowHidden(EM2_X15,!(xIoPort::IsVisibleExtIn(EM2_VAR_X03)));
                break;
            case EM3_X00:
                ui->tableWidget_In->setRowHidden(EM3_X00,!(xIoPort::IsVisibleExtIn(EM2_VAR_X04)));
                break;
            case EM3_X01:
                ui->tableWidget_In->setRowHidden(EM3_X01,!(xIoPort::IsVisibleExtIn(EM2_VAR_X05)));
                break;
            case EM3_X02:
                ui->tableWidget_In->setRowHidden(EM3_X02,!(xIoPort::IsVisibleExtIn(EM2_VAR_X06)));
                break;
            case EM3_X03:
                ui->tableWidget_In->setRowHidden(EM3_X03,!(xIoPort::IsVisibleExtIn(EM2_VAR_X07)));
                break;
            case EM3_X04:
                ui->tableWidget_In->setRowHidden(EM3_X04,!(xIoPort::IsVisibleExtIn(EM2_VAR_X08)));
                break;
            case EM3_X05:
                ui->tableWidget_In->setRowHidden(EM3_X05,!(xIoPort::IsVisibleExtIn(EM2_VAR_X09)));
                break;
            case EM3_X06:
                ui->tableWidget_In->setRowHidden(EM3_X06,!(xIoPort::IsVisibleExtIn(EM2_VAR_X10)));
                break;
            case EM3_X07:
                ui->tableWidget_In->setRowHidden(EM3_X07,!(xIoPort::IsVisibleExtIn(EM2_VAR_X11)));
                break;
            case EM3_X08:
                ui->tableWidget_In->setRowHidden(EM3_X08,!(xIoPort::IsVisibleExtIn(EM2_VAR_X12)));
                break;
            case EM3_X09:
                ui->tableWidget_In->setRowHidden(EM3_X09,!(xIoPort::IsVisibleExtIn(EM2_VAR_X13)));
                break;
            case EM3_X10:
                ui->tableWidget_In->setRowHidden(EM3_X10,!(xIoPort::IsVisibleExtIn(EM2_VAR_X14)));
                break;
            case EM3_X11:
                ui->tableWidget_In->setRowHidden(EM3_X11,!(xIoPort::IsVisibleExtIn(EM2_VAR_X15)));
                break;

            case EM3_X12:
                ui->tableWidget_In->setRowHidden(EM3_X12,!(xIoPort::IsVisibleExtIn(EM3_VAR_X00)));
                break;
            case EM3_X13:
                ui->tableWidget_In->setRowHidden(EM3_X13,!(xIoPort::IsVisibleExtIn(EM3_VAR_X01)));
                break;
            case EM3_X14:
                ui->tableWidget_In->setRowHidden(EM3_X14,!(xIoPort::IsVisibleExtIn(EM3_VAR_X02)));
                break;
            case EM3_X15:
                ui->tableWidget_In->setRowHidden(EM3_X15,!(xIoPort::IsVisibleExtIn(EM3_VAR_X03)));
                break;
            case EM4_X00:
                ui->tableWidget_In->setRowHidden(EM4_X00,!(xIoPort::IsVisibleExtIn(EM3_VAR_X04)));
                break;
            case EM4_X01:
                ui->tableWidget_In->setRowHidden(EM4_X01,!(xIoPort::IsVisibleExtIn(EM3_VAR_X05)));
                break;
            case EM4_X02:
                ui->tableWidget_In->setRowHidden(EM4_X02,!(xIoPort::IsVisibleExtIn(EM3_VAR_X06)));
                break;
            case EM4_X03:
                ui->tableWidget_In->setRowHidden(EM4_X03,!(xIoPort::IsVisibleExtIn(EM3_VAR_X07)));
                break;
            case EM4_X04:
                ui->tableWidget_In->setRowHidden(EM4_X04,!(xIoPort::IsVisibleExtIn(EM3_VAR_X08)));
                break;
            case EM4_X05:
                ui->tableWidget_In->setRowHidden(EM4_X05,!(xIoPort::IsVisibleExtIn(EM3_VAR_X09)));
                break;
            case EM4_X06:
                ui->tableWidget_In->setRowHidden(EM4_X06,!(xIoPort::IsVisibleExtIn(EM3_VAR_X10)));
                break;
            case EM4_X07:
                ui->tableWidget_In->setRowHidden(EM4_X07,!(xIoPort::IsVisibleExtIn(EM3_VAR_X11)));
                break;
            case EM4_X08:
                ui->tableWidget_In->setRowHidden(EM4_X08,!(xIoPort::IsVisibleExtIn(EM3_VAR_X12)));
                break;
            case EM4_X09:
                ui->tableWidget_In->setRowHidden(EM4_X09,!(xIoPort::IsVisibleExtIn(EM3_VAR_X13)));
                break;
            case EM4_X10:
                ui->tableWidget_In->setRowHidden(EM4_X10,!(xIoPort::IsVisibleExtIn(EM3_VAR_X14)));
                break;
            case EM4_X11:
                ui->tableWidget_In->setRowHidden(EM4_X11,!(xIoPort::IsVisibleExtIn(EM3_VAR_X15)));
                break;

            case EM4_X12:
                ui->tableWidget_In->setRowHidden(EM4_X12,!(xIoPort::IsVisibleExtIn(EM4_VAR_X00)));
                break;
            case EM4_X13:
                ui->tableWidget_In->setRowHidden(EM4_X13,!(xIoPort::IsVisibleExtIn(EM4_VAR_X01)));
                break;
            case EM4_X14:
                ui->tableWidget_In->setRowHidden(EM4_X14,!(xIoPort::IsVisibleExtIn(EM4_VAR_X02)));
                break;
            case EM4_X15:
                ui->tableWidget_In->setRowHidden(EM4_X15,!(xIoPort::IsVisibleExtIn(EM4_VAR_X03)));
                break;
            case MAIN_X16:
                ui->tableWidget_In->setRowHidden(MAIN_X16,!(xIoPort::IsVisibleExtIn(EM4_VAR_X04)));
                break;
            case MAIN_X17:
                ui->tableWidget_In->setRowHidden(MAIN_X17,!(xIoPort::IsVisibleExtIn(EM4_VAR_X05)));
                break;
            case MAIN_X18:
                ui->tableWidget_In->setRowHidden(MAIN_X18,!(xIoPort::IsVisibleExtIn(EM4_VAR_X06)));
                break;
            case MAIN_X19:
                ui->tableWidget_In->setRowHidden(MAIN_X19,!(xIoPort::IsVisibleExtIn(EM4_VAR_X07)));
                break;
            case MAIN_X20:
                ui->tableWidget_In->setRowHidden(MAIN_X20,!(xIoPort::IsVisibleExtIn(EM4_VAR_X08)));
                break;
            case MAIN_X21:
                ui->tableWidget_In->setRowHidden(MAIN_X21,!(xIoPort::IsVisibleExtIn(EM4_VAR_X09)));
                break;
            case MAIN_X22:
                ui->tableWidget_In->setRowHidden(MAIN_X22,!(xIoPort::IsVisibleExtIn(EM4_VAR_X10)));
                break;
            case MAIN_X23:
                ui->tableWidget_In->setRowHidden(MAIN_X23,!(xIoPort::IsVisibleExtIn(EM4_VAR_X11)));
                break;
            case MAIN_X24:
                ui->tableWidget_In->setRowHidden(MAIN_X24,!(xIoPort::IsVisibleExtIn(EM4_VAR_X12)));
                break;
            case MAIN_X25:
                ui->tableWidget_In->setRowHidden(MAIN_X25,!(xIoPort::IsVisibleExtIn(EM4_VAR_X13)));
                break;
            case MAIN_X26:
                ui->tableWidget_In->setRowHidden(MAIN_X26,!(xIoPort::IsVisibleExtIn(EM4_VAR_X14)));
                break;
            case MAIN_X27:
                ui->tableWidget_In->setRowHidden(MAIN_X27,!(xIoPort::IsVisibleExtIn(EM4_VAR_X15)));
                break;

            }
        }
    }
    else
    {
        for(i = 0; i < MAX_INPORT_NUM; i++)
        {
            //输入表
            switch(i)
            {
            case MAIN_X00:
                ui->tableWidget_In->setRowHidden(MAIN_X00,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X00)));
                break;
            case MAIN_X01:
                ui->tableWidget_In->setRowHidden(MAIN_X01,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X01)));
                break;
            case MAIN_X02:
                ui->tableWidget_In->setRowHidden(MAIN_X02,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X02)));
                break;
            case MAIN_X03:
                ui->tableWidget_In->setRowHidden(MAIN_X03,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X03)));
                break;
            case MAIN_X04:
                ui->tableWidget_In->setRowHidden(MAIN_X04,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X04)));
                break;
            case MAIN_X05:
                ui->tableWidget_In->setRowHidden(MAIN_X05,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X05)));
                break;
            case MAIN_X06:
                ui->tableWidget_In->setRowHidden(MAIN_X06,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X06)));
                break;
            case MAIN_X07:
                ui->tableWidget_In->setRowHidden(MAIN_X07,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X07)));
                break;
            case MAIN_X08:
                ui->tableWidget_In->setRowHidden(MAIN_X08,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X08)));
                break;
            case MAIN_X09:
                ui->tableWidget_In->setRowHidden(MAIN_X09,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X09)));
                break;
            case MAIN_X10:
                ui->tableWidget_In->setRowHidden(MAIN_X10,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X10)));
                break;
            case MAIN_X11:
                ui->tableWidget_In->setRowHidden(MAIN_X11,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X11)));
                break;
            case MAIN_X12:
                ui->tableWidget_In->setRowHidden(MAIN_X12,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X12)));
                break;
            case MAIN_X13:
                ui->tableWidget_In->setRowHidden(MAIN_X13,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X13)));
                break;
            case MAIN_X14:
                ui->tableWidget_In->setRowHidden(MAIN_X14,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X14)));
                break;
            case MAIN_X15:
                ui->tableWidget_In->setRowHidden(MAIN_X15,!(xIoPort::IsVisibleExtIn(MAIN_VAR_X15)));
                break;

            case EM1_X00:
                ui->tableWidget_In->setRowHidden(EM1_X00,!(xIoPort::IsVisibleExtIn(EM1_VAR_X00)));
                break;
            case EM1_X01:
                ui->tableWidget_In->setRowHidden(EM1_X01,!(xIoPort::IsVisibleExtIn(EM1_VAR_X01)));
                break;
            case EM1_X02:
                ui->tableWidget_In->setRowHidden(EM1_X02,!(xIoPort::IsVisibleExtIn(EM1_VAR_X02)));
                break;
            case EM1_X03:
                ui->tableWidget_In->setRowHidden(EM1_X03,!(xIoPort::IsVisibleExtIn(EM1_VAR_X03)));
                break;
            case EM1_X04:
                ui->tableWidget_In->setRowHidden(EM1_X04,!(xIoPort::IsVisibleExtIn(EM1_VAR_X04)));
                break;
            case EM1_X05:
                ui->tableWidget_In->setRowHidden(EM1_X05,!(xIoPort::IsVisibleExtIn(EM1_VAR_X05)));
                break;
            case EM1_X06:
                ui->tableWidget_In->setRowHidden(EM1_X06,!(xIoPort::IsVisibleExtIn(EM1_VAR_X06)));
                break;
            case EM1_X07:
                ui->tableWidget_In->setRowHidden(EM1_X07,!(xIoPort::IsVisibleExtIn(EM1_VAR_X07)));
                break;
            case EM1_X08:
                ui->tableWidget_In->setRowHidden(EM1_X08,!(xIoPort::IsVisibleExtIn(EM1_VAR_X08)));
                break;
            case EM1_X09:
                ui->tableWidget_In->setRowHidden(EM1_X09,!(xIoPort::IsVisibleExtIn(EM1_VAR_X09)));
                break;
            case EM1_X10:
                ui->tableWidget_In->setRowHidden(EM1_X10,!(xIoPort::IsVisibleExtIn(EM1_VAR_X10)));
                break;
            case EM1_X11:
                ui->tableWidget_In->setRowHidden(EM1_X11,!(xIoPort::IsVisibleExtIn(EM1_VAR_X11)));
                break;
            case EM1_X12:
                ui->tableWidget_In->setRowHidden(EM1_X12,!(xIoPort::IsVisibleExtIn(EM1_VAR_X12)));
                break;
            case EM1_X13:
                ui->tableWidget_In->setRowHidden(EM1_X13,!(xIoPort::IsVisibleExtIn(EM1_VAR_X13)));
                break;
            case EM1_X14:
                ui->tableWidget_In->setRowHidden(EM1_X14,!(xIoPort::IsVisibleExtIn(EM1_VAR_X14)));
                break;
            case EM1_X15:
                ui->tableWidget_In->setRowHidden(EM1_X15,!(xIoPort::IsVisibleExtIn(EM1_VAR_X15)));
                break;

            case EM2_X00:
                ui->tableWidget_In->setRowHidden(EM2_X00,!(xIoPort::IsVisibleExtIn(EM2_VAR_X00)));
                break;
            case EM2_X01:
                ui->tableWidget_In->setRowHidden(EM2_X01,!(xIoPort::IsVisibleExtIn(EM2_VAR_X01)));
                break;
            case EM2_X02:
                ui->tableWidget_In->setRowHidden(EM2_X02,!(xIoPort::IsVisibleExtIn(EM2_VAR_X02)));
                break;
            case EM2_X03:
                ui->tableWidget_In->setRowHidden(EM2_X03,!(xIoPort::IsVisibleExtIn(EM2_VAR_X03)));
                break;
            case EM2_X04:
                ui->tableWidget_In->setRowHidden(EM2_X04,!(xIoPort::IsVisibleExtIn(EM2_VAR_X04)));
                break;
            case EM2_X05:
                ui->tableWidget_In->setRowHidden(EM2_X05,!(xIoPort::IsVisibleExtIn(EM2_VAR_X05)));
                break;
            case EM2_X06:
                ui->tableWidget_In->setRowHidden(EM2_X06,!(xIoPort::IsVisibleExtIn(EM2_VAR_X06)));
                break;
            case EM2_X07:
                ui->tableWidget_In->setRowHidden(EM2_X07,!(xIoPort::IsVisibleExtIn(EM2_VAR_X07)));
                break;
            case EM2_X08:
                ui->tableWidget_In->setRowHidden(EM2_X08,!(xIoPort::IsVisibleExtIn(EM2_VAR_X08)));
                break;
            case EM2_X09:
                ui->tableWidget_In->setRowHidden(EM2_X09,!(xIoPort::IsVisibleExtIn(EM2_VAR_X09)));
                break;
            case EM2_X10:
                ui->tableWidget_In->setRowHidden(EM2_X10,!(xIoPort::IsVisibleExtIn(EM2_VAR_X10)));
                break;
            case EM2_X11:
                ui->tableWidget_In->setRowHidden(EM2_X11,!(xIoPort::IsVisibleExtIn(EM2_VAR_X11)));
                break;
            case EM2_X12:
                ui->tableWidget_In->setRowHidden(EM2_X12,!(xIoPort::IsVisibleExtIn(EM2_VAR_X12)));
                break;
            case EM2_X13:
                ui->tableWidget_In->setRowHidden(EM2_X13,!(xIoPort::IsVisibleExtIn(EM2_VAR_X13)));
                break;
            case EM2_X14:
                ui->tableWidget_In->setRowHidden(EM2_X14,!(xIoPort::IsVisibleExtIn(EM2_VAR_X14)));
                break;
            case EM2_X15:
                ui->tableWidget_In->setRowHidden(EM2_X15,!(xIoPort::IsVisibleExtIn(EM2_VAR_X15)));
                break;

            case EM3_X00:
                ui->tableWidget_In->setRowHidden(EM3_X00,!(xIoPort::IsVisibleExtIn(EM3_VAR_X00)));
                break;
            case EM3_X01:
                ui->tableWidget_In->setRowHidden(EM3_X01,!(xIoPort::IsVisibleExtIn(EM3_VAR_X01)));
                break;
            case EM3_X02:
                ui->tableWidget_In->setRowHidden(EM3_X02,!(xIoPort::IsVisibleExtIn(EM3_VAR_X02)));
                break;
            case EM3_X03:
                ui->tableWidget_In->setRowHidden(EM3_X03,!(xIoPort::IsVisibleExtIn(EM3_VAR_X03)));
                break;
            case EM3_X04:
                ui->tableWidget_In->setRowHidden(EM3_X04,!(xIoPort::IsVisibleExtIn(EM3_VAR_X04)));
                break;
            case EM3_X05:
                ui->tableWidget_In->setRowHidden(EM3_X05,!(xIoPort::IsVisibleExtIn(EM3_VAR_X05)));
                break;
            case EM3_X06:
                ui->tableWidget_In->setRowHidden(EM3_X06,!(xIoPort::IsVisibleExtIn(EM3_VAR_X06)));
                break;
            case EM3_X07:
                ui->tableWidget_In->setRowHidden(EM3_X07,!(xIoPort::IsVisibleExtIn(EM3_VAR_X07)));
                break;
            case EM3_X08:
                ui->tableWidget_In->setRowHidden(EM3_X08,!(xIoPort::IsVisibleExtIn(EM3_VAR_X08)));
                break;
            case EM3_X09:
                ui->tableWidget_In->setRowHidden(EM3_X09,!(xIoPort::IsVisibleExtIn(EM3_VAR_X09)));
                break;
            case EM3_X10:
                ui->tableWidget_In->setRowHidden(EM3_X10,!(xIoPort::IsVisibleExtIn(EM3_VAR_X10)));
                break;
            case EM3_X11:
                ui->tableWidget_In->setRowHidden(EM3_X11,!(xIoPort::IsVisibleExtIn(EM3_VAR_X11)));
                break;
            case EM3_X12:
                ui->tableWidget_In->setRowHidden(EM3_X12,!(xIoPort::IsVisibleExtIn(EM3_VAR_X12)));
                break;
            case EM3_X13:
                ui->tableWidget_In->setRowHidden(EM3_X13,!(xIoPort::IsVisibleExtIn(EM3_VAR_X13)));
                break;
            case EM3_X14:
                ui->tableWidget_In->setRowHidden(EM3_X14,!(xIoPort::IsVisibleExtIn(EM3_VAR_X14)));
                break;
            case EM3_X15:
                ui->tableWidget_In->setRowHidden(EM3_X15,!(xIoPort::IsVisibleExtIn(EM3_VAR_X15)));
                break;

            case EM4_X00:
                ui->tableWidget_In->setRowHidden(EM4_X00,!(xIoPort::IsVisibleExtIn(EM4_VAR_X00)));
                break;
            case EM4_X01:
                ui->tableWidget_In->setRowHidden(EM4_X01,!(xIoPort::IsVisibleExtIn(EM4_VAR_X01)));
                break;
            case EM4_X02:
                ui->tableWidget_In->setRowHidden(EM4_X02,!(xIoPort::IsVisibleExtIn(EM4_VAR_X02)));
                break;
            case EM4_X03:
                ui->tableWidget_In->setRowHidden(EM4_X03,!(xIoPort::IsVisibleExtIn(EM4_VAR_X03)));
                break;
            case EM4_X04:
                ui->tableWidget_In->setRowHidden(EM4_X04,!(xIoPort::IsVisibleExtIn(EM4_VAR_X04)));
                break;
            case EM4_X05:
                ui->tableWidget_In->setRowHidden(EM4_X05,!(xIoPort::IsVisibleExtIn(EM4_VAR_X05)));
                break;
            case EM4_X06:
                ui->tableWidget_In->setRowHidden(EM4_X06,!(xIoPort::IsVisibleExtIn(EM4_VAR_X06)));
                break;
            case EM4_X07:
                ui->tableWidget_In->setRowHidden(EM4_X07,!(xIoPort::IsVisibleExtIn(EM4_VAR_X07)));
                break;
            case EM4_X08:
                ui->tableWidget_In->setRowHidden(EM4_X08,!(xIoPort::IsVisibleExtIn(EM4_VAR_X08)));
                break;
            case EM4_X09:
                ui->tableWidget_In->setRowHidden(EM4_X09,!(xIoPort::IsVisibleExtIn(EM4_VAR_X09)));
                break;
            case EM4_X10:
                ui->tableWidget_In->setRowHidden(EM4_X10,!(xIoPort::IsVisibleExtIn(EM4_VAR_X10)));
                break;
            case EM4_X11:
                ui->tableWidget_In->setRowHidden(EM4_X11,!(xIoPort::IsVisibleExtIn(EM4_VAR_X11)));
                break;
            case EM4_X12:
                ui->tableWidget_In->setRowHidden(EM4_X12,!(xIoPort::IsVisibleExtIn(EM4_VAR_X12)));
                break;
            case EM4_X13:
                ui->tableWidget_In->setRowHidden(EM4_X13,!(xIoPort::IsVisibleExtIn(EM4_VAR_X13)));
                break;
            case EM4_X14:
                ui->tableWidget_In->setRowHidden(EM4_X14,!(xIoPort::IsVisibleExtIn(EM4_VAR_X14)));
                break;
            case EM4_X15:
                ui->tableWidget_In->setRowHidden(EM4_X15,!(xIoPort::IsVisibleExtIn(EM4_VAR_X15)));
                break;
            }
        }
    }
    //输出表 PYQ
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        for(i = 0; i < MAX_OUTPORT_NUM3; i++)
        {
            switch(i)
            {
            case MAIN_Y00:
                ui->tableWidget_Out->setRowHidden(MAIN_Y00,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y00)));
                break;
            case MAIN_Y01:
                ui->tableWidget_Out->setRowHidden(MAIN_Y01,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y01)));
                break;
            case MAIN_Y02:
                ui->tableWidget_Out->setRowHidden(MAIN_Y02,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y02)));
                break;
            case MAIN_Y03:
                ui->tableWidget_Out->setRowHidden(MAIN_Y03,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y03)));
                break;
            case MAIN_Y04:
                ui->tableWidget_Out->setRowHidden(MAIN_Y04,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y04)));
                break;
            case MAIN_Y05:
                ui->tableWidget_Out->setRowHidden(MAIN_Y05,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y05)));
                break;
            case MAIN_X06:
                ui->tableWidget_Out->setRowHidden(MAIN_Y06,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y06)));
                break;
            case MAIN_Y07:
                ui->tableWidget_Out->setRowHidden(MAIN_Y07,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y07)));
                break;
            case MAIN_Y08:
                ui->tableWidget_Out->setRowHidden(MAIN_Y08,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y08)));
                break;
            case MAIN_Y09:
                ui->tableWidget_Out->setRowHidden(MAIN_Y09,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y09)));
                break;
            case MAIN_Y10:
                ui->tableWidget_Out->setRowHidden(MAIN_Y10,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y10)));
                break;
            case MAIN_Y11:
                ui->tableWidget_Out->setRowHidden(MAIN_Y11,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y11)));
                break;
            case MAIN_Y12:
                ui->tableWidget_Out->setRowHidden(MAIN_Y12,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y12)));
                break;
            case MAIN_Y13:
                ui->tableWidget_Out->setRowHidden(MAIN_Y13,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y13)));
                break;
            case MAIN_Y14:
                ui->tableWidget_Out->setRowHidden(MAIN_Y14,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y14)));
                break;
            case MAIN_Y15:
                ui->tableWidget_Out->setRowHidden(MAIN_Y15,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y15)));
                break;

            case EM1_Y00:
                ui->tableWidget_Out->setRowHidden(EM1_Y00,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y16)));
                break;
            case EM1_Y01:
                ui->tableWidget_Out->setRowHidden(EM1_Y01,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y17)));
                break;
            case EM1_Y02:
                ui->tableWidget_Out->setRowHidden(EM1_Y02,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y18)));
                break;
            case EM1_Y03:
                ui->tableWidget_Out->setRowHidden(EM1_Y03,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y19)));
                break;
            case EM1_Y04:
                ui->tableWidget_Out->setRowHidden(EM1_Y04,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y20)));
                break;
            case EM1_Y05:
                ui->tableWidget_Out->setRowHidden(EM1_Y05,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y21)));
                break;
            case EM1_Y06:
                ui->tableWidget_Out->setRowHidden(EM1_Y06,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y22)));
                break;
            case EM1_Y07:
                ui->tableWidget_Out->setRowHidden(EM1_Y07,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y23)));
                break;
            case EM1_Y08:
                ui->tableWidget_Out->setRowHidden(EM1_Y08,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y24)));
                break;
            case EM1_Y09:
                ui->tableWidget_Out->setRowHidden(EM1_Y09,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y25)));
                break;
            case EM1_Y10:
                ui->tableWidget_Out->setRowHidden(EM1_Y10,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y26)));
                break;
            case EM1_Y11:
                ui->tableWidget_Out->setRowHidden(EM1_Y11,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y27)));
                break;
            case EM1_Y12:
                ui->tableWidget_Out->setRowHidden(EM1_Y12,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y28)));
                break;

            case EM1_Y13:
                ui->tableWidget_Out->setRowHidden(EM1_Y13,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y00)));
                break;
            case EM1_Y14:
                ui->tableWidget_Out->setRowHidden(EM1_Y14,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y01)));
                break;
            case EM1_Y15:
                ui->tableWidget_Out->setRowHidden(EM1_Y15,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y02)));
                break;
            case EM2_Y00:
                ui->tableWidget_Out->setRowHidden(EM2_Y00,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y03)));
                break;
            case EM2_Y01:
                ui->tableWidget_Out->setRowHidden(EM2_Y01,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y04)));
                break;
            case EM2_Y02:
                ui->tableWidget_Out->setRowHidden(EM2_Y02,!(xIoPort::IsVisibleExtOut(EM1_VAR_X05)));
                break;
            case EM2_Y03:
                ui->tableWidget_Out->setRowHidden(EM2_Y03,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y06)));
                break;
            case EM2_Y04:
                ui->tableWidget_Out->setRowHidden(EM2_Y04,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y07)));
                break;
            case EM2_Y05:
                ui->tableWidget_Out->setRowHidden(EM2_Y05,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y08)));
                break;
            case EM2_Y06:
                ui->tableWidget_Out->setRowHidden(EM2_Y06,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y09)));
                break;
            case EM2_Y07:
                ui->tableWidget_Out->setRowHidden(EM2_Y07,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y10)));
                break;
            case EM2_Y08:
                ui->tableWidget_Out->setRowHidden(EM2_Y08,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y11)));
                break;
            case EM2_Y09:
                ui->tableWidget_Out->setRowHidden(EM2_Y09,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y12)));
                break;
            case EM2_Y10:
                ui->tableWidget_Out->setRowHidden(EM2_Y10,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y13)));
                break;
            case EM2_Y11:
                ui->tableWidget_Out->setRowHidden(EM2_Y11,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y14)));
                break;
            case EM2_Y12:
                ui->tableWidget_Out->setRowHidden(EM2_Y12,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y15)));
                break;

            case EM2_Y13:
                ui->tableWidget_Out->setRowHidden(EM2_Y13,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y00)));
                break;
            case EM2_Y14:
                ui->tableWidget_Out->setRowHidden(EM2_Y14,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y01)));
                break;
            case EM2_Y15:
                ui->tableWidget_Out->setRowHidden(EM2_Y15,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y02)));
                break;
            case EM3_Y00:
                ui->tableWidget_Out->setRowHidden(EM3_Y00,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y03)));
                break;
            case EM3_Y01:
                ui->tableWidget_Out->setRowHidden(EM3_Y01,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y04)));
                break;
            case EM3_Y02:
                ui->tableWidget_Out->setRowHidden(EM3_Y02,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y05)));
                break;
            case EM3_Y03:
                ui->tableWidget_Out->setRowHidden(EM3_Y03,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y06)));
                break;
            case EM3_Y04:
                ui->tableWidget_Out->setRowHidden(EM3_Y04,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y07)));
                break;
            case EM3_Y05:
                ui->tableWidget_Out->setRowHidden(EM3_Y05,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y08)));
                break;
            case EM3_Y06:
                ui->tableWidget_Out->setRowHidden(EM3_Y06,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y09)));
                break;
            case EM3_Y07:
                ui->tableWidget_Out->setRowHidden(EM3_Y07,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y10)));
                break;
            case EM3_Y08:
                ui->tableWidget_Out->setRowHidden(EM3_Y08,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y11)));
                break;
            case EM3_Y09:
                ui->tableWidget_Out->setRowHidden(EM3_Y09,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y12)));
                break;
            case EM3_Y10:
                ui->tableWidget_Out->setRowHidden(EM3_Y10,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y13)));
                break;
            case EM3_Y11:
                ui->tableWidget_Out->setRowHidden(EM3_Y11,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y14)));
                break;
            case EM3_Y12:
                ui->tableWidget_Out->setRowHidden(EM3_Y12,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y15)));
                break;

            case EM3_Y13:
                ui->tableWidget_Out->setRowHidden(EM3_Y13,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y00)));
                break;
            case EM3_Y14:
                ui->tableWidget_Out->setRowHidden(EM3_Y14,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y01)));
                break;
            case EM3_Y15:
                ui->tableWidget_Out->setRowHidden(EM3_Y15,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y02)));
                break;
            case EM4_Y00:
                ui->tableWidget_Out->setRowHidden(EM4_Y00,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y03)));
                break;
            case EM4_Y01:
                ui->tableWidget_Out->setRowHidden(EM4_Y01,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y04)));
                break;
            case EM4_Y02:
                ui->tableWidget_Out->setRowHidden(EM4_Y02,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y05)));
                break;
            case EM4_Y03:
                ui->tableWidget_Out->setRowHidden(EM4_Y03,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y06)));
                break;
            case EM4_Y04:
                ui->tableWidget_Out->setRowHidden(EM4_Y04,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y07)));
                break;
            case EM4_Y05:
                ui->tableWidget_Out->setRowHidden(EM4_Y05,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y08)));
                break;
            case EM4_Y06:
                ui->tableWidget_Out->setRowHidden(EM4_Y06,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y09)));
                break;
            case EM4_Y07:
                ui->tableWidget_Out->setRowHidden(EM4_Y07,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y10)));
                break;
            case EM4_Y08:
                ui->tableWidget_Out->setRowHidden(EM4_Y08,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y11)));
                break;
            case EM4_Y09:
                ui->tableWidget_Out->setRowHidden(EM4_Y09,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y12)));
                break;
            case EM4_Y10:
                ui->tableWidget_Out->setRowHidden(EM4_Y10,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y13)));
                break;
            case EM4_Y11:
                ui->tableWidget_Out->setRowHidden(EM4_Y11,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y14)));
                break;
            case EM4_Y12:
                ui->tableWidget_Out->setRowHidden(EM4_Y12,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y15)));
                break;

            case EM4_Y13:
                ui->tableWidget_Out->setRowHidden(EM4_Y13,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y00)));
                break;
            case EM4_Y14:
                ui->tableWidget_Out->setRowHidden(EM4_Y14,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y01)));
                break;
            case EM4_Y15:
                ui->tableWidget_Out->setRowHidden(EM4_Y15,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y02)));
                break;
            case MAIN_Y16:
                ui->tableWidget_Out->setRowHidden(MAIN_Y16,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y03)));
                break;
            case MAIN_Y17:
                ui->tableWidget_Out->setRowHidden(MAIN_Y17,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y04)));
                break;
            case MAIN_Y18:
                ui->tableWidget_Out->setRowHidden(MAIN_Y18,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y05)));
                break;
            case MAIN_Y19:
                ui->tableWidget_Out->setRowHidden(MAIN_Y19,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y06)));
                break;
            case MAIN_Y20:
                ui->tableWidget_Out->setRowHidden(MAIN_Y20,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y07)));
                break;
            case MAIN_Y21:
                ui->tableWidget_Out->setRowHidden(MAIN_Y21,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y08)));
                break;
            case MAIN_Y22:
                ui->tableWidget_Out->setRowHidden(MAIN_Y22,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y09)));
                break;
            case MAIN_Y23:
                ui->tableWidget_Out->setRowHidden(MAIN_Y23,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y10)));
                break;
            case MAIN_Y24:
                ui->tableWidget_Out->setRowHidden(MAIN_Y24,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y11)));
                break;
            case MAIN_Y25:
                ui->tableWidget_Out->setRowHidden(MAIN_Y25,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y12)));
                break;
            case MAIN_Y26:
                ui->tableWidget_Out->setRowHidden(MAIN_Y26,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y13)));
                break;
            case MAIN_Y27:
                ui->tableWidget_Out->setRowHidden(MAIN_Y27,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y14)));
                break;
            case MAIN_Y28:
                ui->tableWidget_Out->setRowHidden(MAIN_Y28,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y15)));
                break;
            }
        }
    }
    else
    {
        for(i = 0; i < MAX_OUTPORT_NUM; i++)
        {
            switch(i)
            {
            case MAIN_Y00:
                ui->tableWidget_Out->setRowHidden(MAIN_Y00,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y00)));
                break;
            case MAIN_Y01:
                ui->tableWidget_Out->setRowHidden(MAIN_Y01,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y01)));
                break;
            case MAIN_Y02:
                ui->tableWidget_Out->setRowHidden(MAIN_Y02,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y02)));
                break;
            case MAIN_Y03:
                ui->tableWidget_Out->setRowHidden(MAIN_Y03,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y03)));
                break;
            case MAIN_Y04:
                ui->tableWidget_Out->setRowHidden(MAIN_Y04,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y04)));
                break;
            case MAIN_Y05:
                ui->tableWidget_Out->setRowHidden(MAIN_Y05,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y05)));
                break;
            case MAIN_Y06:
                ui->tableWidget_Out->setRowHidden(MAIN_Y06,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y06)));
                break;
            case MAIN_Y07:
                ui->tableWidget_Out->setRowHidden(MAIN_Y07,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y07)));
                break;
            case MAIN_Y08:
                ui->tableWidget_Out->setRowHidden(MAIN_Y08,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y08)));
                break;
            case MAIN_Y09:
                ui->tableWidget_Out->setRowHidden(MAIN_Y09,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y09)));
                break;
            case MAIN_Y10:
                ui->tableWidget_Out->setRowHidden(MAIN_Y10,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y10)));
                break;
            case MAIN_Y11:
                ui->tableWidget_Out->setRowHidden(MAIN_Y11,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y11)));
                break;
            case MAIN_Y12:
                ui->tableWidget_Out->setRowHidden(MAIN_Y12,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y12)));
                break;
            case MAIN_Y13:
                ui->tableWidget_Out->setRowHidden(MAIN_Y13,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y13)));
                break;
            case MAIN_Y14:
                ui->tableWidget_Out->setRowHidden(MAIN_Y14,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y14)));
                break;
            case MAIN_Y15:
                ui->tableWidget_Out->setRowHidden(MAIN_Y15,!(xIoPort::IsVisibleExtOut(MAIN_VAR_Y15)));
                break;
            case EM1_Y00:
                ui->tableWidget_Out->setRowHidden(EM1_Y00,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y00)));
                break;
            case EM1_Y01:
                ui->tableWidget_Out->setRowHidden(EM1_Y01,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y01)));
                break;
            case EM1_Y02:
                ui->tableWidget_Out->setRowHidden(EM1_Y02,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y02)));
                break;
            case EM1_Y03:
                ui->tableWidget_Out->setRowHidden(EM1_Y03,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y03)));
                break;
            case EM1_Y04:
                ui->tableWidget_Out->setRowHidden(EM1_Y04,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y04)));
                break;
            case EM1_Y05:
                ui->tableWidget_Out->setRowHidden(EM1_Y05,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y05)));
                break;
            case EM1_Y06:
                ui->tableWidget_Out->setRowHidden(EM1_Y06,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y06)));
                break;
            case EM1_Y07:
                ui->tableWidget_Out->setRowHidden(EM1_Y07,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y07)));
                break;
            case EM1_Y08:
                ui->tableWidget_Out->setRowHidden(EM1_Y08,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y08)));
                break;
            case EM1_Y09:
                ui->tableWidget_Out->setRowHidden(EM1_Y09,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y09)));
                break;
            case EM1_Y10:
                ui->tableWidget_Out->setRowHidden(EM1_Y10,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y10)));
                break;
            case EM1_Y11:
                ui->tableWidget_Out->setRowHidden(EM1_Y11,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y11)));
                break;
            case EM1_Y12:
                ui->tableWidget_Out->setRowHidden(EM1_Y12,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y12)));
                break;
            case EM1_Y13:
                ui->tableWidget_Out->setRowHidden(EM1_Y13,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y13)));
                break;
            case EM1_Y14:
                ui->tableWidget_Out->setRowHidden(EM1_Y14,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y14)));
                break;
            case EM1_Y15:
                ui->tableWidget_Out->setRowHidden(EM1_Y15,!(xIoPort::IsVisibleExtOut(EM1_VAR_Y15)));
                break;

            case EM2_Y00:
                ui->tableWidget_Out->setRowHidden(EM2_Y00,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y00)));
                break;
            case EM2_Y01:
                ui->tableWidget_Out->setRowHidden(EM2_Y01,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y01)));
                break;
            case EM2_Y02:
                ui->tableWidget_Out->setRowHidden(EM2_Y02,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y02)));
                break;
            case EM2_Y03:
                ui->tableWidget_Out->setRowHidden(EM2_Y03,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y03)));
                break;
            case EM2_Y04:
                ui->tableWidget_Out->setRowHidden(EM2_Y04,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y04)));
                break;
            case EM2_Y05:
                ui->tableWidget_Out->setRowHidden(EM2_Y05,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y05)));
                break;
            case EM2_Y06:
                ui->tableWidget_Out->setRowHidden(EM2_Y06,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y06)));
                break;
            case EM2_Y07:
                ui->tableWidget_Out->setRowHidden(EM2_Y07,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y07)));
                break;
            case EM2_Y08:
                ui->tableWidget_Out->setRowHidden(EM2_Y08,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y08)));
                break;
            case EM2_Y09:
                ui->tableWidget_Out->setRowHidden(EM2_Y09,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y09)));
                break;
            case EM2_Y10:
                ui->tableWidget_Out->setRowHidden(EM2_Y10,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y10)));
                break;
            case EM2_Y11:
                ui->tableWidget_Out->setRowHidden(EM2_Y11,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y11)));
                break;
            case EM2_Y12:
                ui->tableWidget_Out->setRowHidden(EM2_Y12,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y12)));
                break;
            case EM2_Y13:
                ui->tableWidget_Out->setRowHidden(EM2_Y13,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y13)));
                break;
            case EM2_Y14:
                ui->tableWidget_Out->setRowHidden(EM2_Y14,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y14)));
                break;
            case EM2_Y15:
                ui->tableWidget_Out->setRowHidden(EM2_Y15,!(xIoPort::IsVisibleExtOut(EM2_VAR_Y15)));
                break;

            case EM3_Y00:
                ui->tableWidget_Out->setRowHidden(EM3_Y00,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y00)));
                break;
            case EM3_Y01:
                ui->tableWidget_Out->setRowHidden(EM3_Y01,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y01)));
                break;
            case EM3_Y02:
                ui->tableWidget_Out->setRowHidden(EM3_Y02,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y02)));
                break;
            case EM3_Y03:
                ui->tableWidget_Out->setRowHidden(EM3_Y03,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y03)));
                break;
            case EM3_Y04:
                ui->tableWidget_Out->setRowHidden(EM3_Y04,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y04)));
                break;
            case EM3_Y05:
                ui->tableWidget_Out->setRowHidden(EM3_Y05,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y05)));
                break;
            case EM3_Y06:
                ui->tableWidget_Out->setRowHidden(EM3_Y06,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y06)));
                break;
            case EM3_Y07:
                ui->tableWidget_Out->setRowHidden(EM3_Y07,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y07)));
                break;
            case EM3_Y08:
                ui->tableWidget_Out->setRowHidden(EM3_Y08,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y08)));
                break;
            case EM3_Y09:
                ui->tableWidget_Out->setRowHidden(EM3_Y09,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y09)));
                break;
            case EM3_Y10:
                ui->tableWidget_Out->setRowHidden(EM3_Y10,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y10)));
                break;
            case EM3_Y11:
                ui->tableWidget_Out->setRowHidden(EM3_Y11,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y11)));
                break;
            case EM3_Y12:
                ui->tableWidget_Out->setRowHidden(EM3_Y12,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y12)));
                break;
            case EM3_Y13:
                ui->tableWidget_Out->setRowHidden(EM3_Y13,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y13)));
                break;
            case EM3_Y14:
                ui->tableWidget_Out->setRowHidden(EM3_Y14,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y14)));
                break;
            case EM3_Y15:
                ui->tableWidget_Out->setRowHidden(EM3_Y15,!(xIoPort::IsVisibleExtOut(EM3_VAR_Y15)));
                break;

            case EM4_Y00:
                ui->tableWidget_Out->setRowHidden(EM4_Y00,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y00)));
                break;
            case EM4_Y01:
                ui->tableWidget_Out->setRowHidden(EM4_Y01,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y01)));
                break;
            case EM4_Y02:
                ui->tableWidget_Out->setRowHidden(EM4_Y02,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y02)));
                break;
            case EM4_Y03:
                ui->tableWidget_Out->setRowHidden(EM4_Y03,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y03)));
                break;
            case EM4_Y04:
                ui->tableWidget_Out->setRowHidden(EM4_Y04,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y04)));
                break;
            case EM4_Y05:
                ui->tableWidget_Out->setRowHidden(EM4_Y05,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y05)));
                break;
            case EM4_Y06:
                ui->tableWidget_Out->setRowHidden(EM4_Y06,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y06)));
                break;
            case EM4_Y07:
                ui->tableWidget_Out->setRowHidden(EM4_Y07,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y07)));
                break;
            case EM4_Y08:
                ui->tableWidget_Out->setRowHidden(EM4_Y08,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y08)));
                break;
            case EM4_Y09:
                ui->tableWidget_Out->setRowHidden(EM4_Y09,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y09)));
                break;
            case EM4_Y10:
                ui->tableWidget_Out->setRowHidden(EM4_Y10,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y10)));
                break;
            case EM4_Y11:
                ui->tableWidget_Out->setRowHidden(EM4_Y11,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y11)));
                break;
            case EM4_Y12:
                ui->tableWidget_Out->setRowHidden(EM4_Y12,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y12)));
                break;
            case EM4_Y13:
                ui->tableWidget_Out->setRowHidden(EM4_Y13,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y13)));
                break;
            case EM4_Y14:
                ui->tableWidget_Out->setRowHidden(EM4_Y14,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y14)));
                break;
            case EM4_Y15:
                ui->tableWidget_Out->setRowHidden(EM4_Y15,!(xIoPort::IsVisibleExtOut(EM4_VAR_Y15)));
                break;

                /*        case IMM_OUT_MAF:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_MAF,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_MAF)));
            break;
        case IMM_OUT_EMC:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_EMC,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EMC)));
            break;
        case IMM_OUT_EMO:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_EMO,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EMO)));
            break;
        case IMM_OUT_RBT:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_RBT,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_RBT)));
            break;
        case IMM_OUT_EEB:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_EEB,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EEB)));
            break;
        case IMM_OUT_EEF:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_EEF,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EEF)));
            break;
        case IMM_OUT_C1P1:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_C1P1,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P1)));
            break;
        case IMM_OUT_C1P2:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_C1P2,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P2)));
           break;
        case IMM_OUT_C2P1:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_C2P1,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P1)));
            break;
        case IMM_OUT_C2P2:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_C2P2,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P2)));
            break;
        case IMM_OUT_HMAF:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_HMAF,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_HMAF)));
            break;
        case IMM_OUT_HEMC:
            ui->tableWidget_Out->setRowHidden(IMM_OUT_HEMC,!(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_HEMC)));
            break;

        case RBT_OUT_PRO_HOR:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_PRO_HOR,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_PRO_HOR)));
            break;
        case RBT_OUT_PRO_VER:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_PRO_VER,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_PRO_VER)));
            break;
        case RBT_OUT_ALM_BEEP:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_ALM_BEEP,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_ALM_BEEP)));
            break;
        case RBT_OUT_ALM_LAMP:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_ALM_LAMP,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_ALM_LAMP)));
            break;
        case RBT_OUT_LAMP:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_LAMP,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_LAMP)));
            break;
        case RBT_OUT_RUN_DES:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_RUN_DES,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_RUN_DES)));
            break;
        case RBT_OUT_RUN_SPEED:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_RUN_SPEED,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_RUN_SPEED)));
            break;
        case RBT_OUT_PRO_ADV:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_PRO_ADV,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_PRO_ADV)));
            break;
        case RBT_OUT_PRO_RET:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_PRO_RET,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_PRO_RET)));
            break;
        case RBT_OUT_RUN_ADV:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_RUN_ADV,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_RUN_ADV)));
            break;
        case RBT_OUT_RUN_RET:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_RUN_RET,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_RUN_RET)));
            break;
        case RBT_OUT_OIL:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_OIL,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_OIL)));
            break;
        case RBT_OUT_RUN_HOR:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_RUN_HOR,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_RUN_HOR)));
            break;
        case RBT_OUT_RUN_VER:
            ui->tableWidget_Out->setRowHidden(RBT_OUT_RUN_VER,!(xIoPort::IsVisibleOutSignal(RBT_VAR_OUT_RUN_VER)));
            break;*/
            }
        }
    }


}

void DialogPortEdit::tableWidgeCellClicked(int row, int column)
{
    QString name;
    //pyq
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        if((column == 2 ) && (row < MAX_INPORT_NUM3))
        {
            // 输入端口名称
            if (xKbd->DoForm(name, KEYBOARD_TYPE_STR) != QDialog::Accepted)
                return;
            ui->tableWidget_In->setItem(row,column,new QTableWidgetItem(name));
        }
    }
    else
    {
        if((column == 2 ) && (row < MAX_INPORT_NUM))
        {
            // 输入端口名称
            if (xKbd->DoForm(name, KEYBOARD_TYPE_STR) != QDialog::Accepted)
                return;
            ui->tableWidget_In->setItem(row,column,new QTableWidgetItem(name));
        }
    }
}

void DialogPortEdit::tableWidgeOutCellClicked(int row, int column)
{
    QString name;
    //pyq
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        if((column == 2 ) && (row < MAX_OUTPORT_NUM3))
        {
            // 输出端口名称
            if (xKbd->DoForm(name, KEYBOARD_TYPE_STR) != QDialog::Accepted)
                return;
            ui->tableWidget_Out->setItem(row,column,new QTableWidgetItem(name));
        }
    }
    else
    {
        if((column == 2 ) && (row < MAX_OUTPORT_NUM))
        {
            // 输出端口名称
            if (xKbd->DoForm(name, KEYBOARD_TYPE_STR) != QDialog::Accepted)
                return;
            ui->tableWidget_Out->setItem(row,column,new QTableWidgetItem(name));
        }
    }

}

void DialogPortEdit::NewPortFile()
{
    QSettings settings(XPAD_PORT_FILE, QSettings::IniFormat);
    ui->BtnCancel->setEnabled(false);
    quint8 i;
    quint8 lan = CMBProtocol::GetLanguage();
    QString curLan;
    curLan.clear();
    switch (lan)
    {
    case LAN_ENGLISH:
        curLan.append("english/");
        break;
    default:
        curLan.append("chineses/");
        break;
    }
    //输入修改名称
    //pyq改变端口名字
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        for(i = 0; i < MAX_INPORT_NUM3; i++)
        {
            if(ui->tableWidget_In->item(i,2)->text() != "")
            {
                switch(i)
                {
                case MAIN_X00:
                    settings.setValue(curLan + QString("MAIN_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X01:
                    settings.setValue(curLan + QString("MAIN_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X02:
                    settings.setValue(curLan + QString("MAIN_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X03:
                    settings.setValue(curLan + QString("MAIN_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X04:
                    settings.setValue(curLan + QString("MAIN_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X05:
                    settings.setValue(curLan + QString("MAIN_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X06:
                    settings.setValue(curLan + QString("MAIN_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X07:
                    settings.setValue(curLan + QString("MAIN_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X08:
                    settings.setValue(curLan + QString("MAIN_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X09:
                    settings.setValue(curLan + QString("MAIN_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X10:
                    settings.setValue(curLan + QString("MAIN_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X11:
                    settings.setValue(curLan + QString("MAIN_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X12:
                    settings.setValue(curLan + QString("MAIN_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X13:
                    settings.setValue(curLan + QString("MAIN_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X14:
                    settings.setValue(curLan + QString("MAIN_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X15:
                    settings.setValue(curLan + QString("MAIN_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM1_X00:
                    settings.setValue(curLan + QString("MAIN_VAR_X16"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X01:
                    settings.setValue(curLan + QString("MAIN_VAR_X17"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X02:
                    settings.setValue(curLan + QString("MAIN_VAR_X18"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X03:
                    settings.setValue(curLan + QString("MAIN_VAR_X19"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X04:
                    settings.setValue(curLan + QString("MAIN_VAR_X20"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X05:
                    settings.setValue(curLan + QString("MAIN_VAR_X21"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X06:
                    settings.setValue(curLan + QString("MAIN_VAR_X22"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X07:
                    settings.setValue(curLan + QString("MAIN_VAR_X23"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X08:
                    settings.setValue(curLan + QString("MAIN_VAR_X24"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X09:
                    settings.setValue(curLan + QString("MAIN_VAR_X25"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X10:
                    settings.setValue(curLan + QString("MAIN_VAR_X26"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X11:
                    settings.setValue(curLan + QString("MAIN_VAR_X27"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM1_X12:
                    settings.setValue(curLan + QString("EM1_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X13:
                    settings.setValue(curLan + QString("EM1_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X14:
                    settings.setValue(curLan + QString("EM1_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X15:
                    settings.setValue(curLan + QString("EM1_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X00:
                    settings.setValue(curLan + QString("EM1_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X01:
                    settings.setValue(curLan + QString("EM1_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X02:
                    settings.setValue(curLan + QString("EM1_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X03:
                    settings.setValue(curLan + QString("EM1_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X04:
                    settings.setValue(curLan + QString("EM1_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X05:
                    settings.setValue(curLan + QString("EM1_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X06:
                    settings.setValue(curLan + QString("EM1_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X07:
                    settings.setValue(curLan + QString("EM1_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X08:
                    settings.setValue(curLan + QString("EM1_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X09:
                    settings.setValue(curLan + QString("EM1_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X10:
                    settings.setValue(curLan + QString("EM1_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X11:
                    settings.setValue(curLan + QString("EM1_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM2_X12:
                    settings.setValue(curLan + QString("EM2_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X13:
                    settings.setValue(curLan + QString("EM2_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X14:
                    settings.setValue(curLan + QString("EM2_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X15:
                    settings.setValue(curLan + QString("EM2_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X00:
                    settings.setValue(curLan + QString("EM2_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X01:
                    settings.setValue(curLan + QString("EM2_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X02:
                    settings.setValue(curLan + QString("EM2_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X03:
                    settings.setValue(curLan + QString("EM2_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X04:
                    settings.setValue(curLan + QString("EM2_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X05:
                    settings.setValue(curLan + QString("EM2_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X06:
                    settings.setValue(curLan + QString("EM2_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X07:
                    settings.setValue(curLan + QString("EM2_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X08:
                    settings.setValue(curLan + QString("EM2_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X09:
                    settings.setValue(curLan + QString("EM2_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X10:
                    settings.setValue(curLan + QString("EM2_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X11:
                    settings.setValue(curLan + QString("EM2_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM3_X12:
                    settings.setValue(curLan + QString("EM3_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X13:
                    settings.setValue(curLan + QString("EM3_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X14:
                    settings.setValue(curLan + QString("EM3_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X15:
                    settings.setValue(curLan + QString("EM3_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X00:
                    settings.setValue(curLan + QString("EM3_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X01:
                    settings.setValue(curLan + QString("EM3_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X02:
                    settings.setValue(curLan + QString("EM3_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X03:
                    settings.setValue(curLan + QString("EM3_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X04:
                    settings.setValue(curLan + QString("EM3_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X05:
                    settings.setValue(curLan + QString("EM3_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X06:
                    settings.setValue(curLan + QString("EM3_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X07:
                    settings.setValue(curLan + QString("EM3_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X08:
                    settings.setValue(curLan + QString("EM3_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X09:
                    settings.setValue(curLan + QString("EM3_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X10:
                    settings.setValue(curLan + QString("EM3_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X11:
                    settings.setValue(curLan + QString("EM3_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM4_X12:
                    settings.setValue(curLan + QString("EM4_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X13:
                    settings.setValue(curLan + QString("EM4_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X14:
                    settings.setValue(curLan + QString("EM4_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X15:
                    settings.setValue(curLan + QString("EM4_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case MAIN_X16:
                    settings.setValue(curLan + QString("EM4_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X17:
                    settings.setValue(curLan + QString("EM4_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X18:
                    settings.setValue(curLan + QString("EM4_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X19:
                    settings.setValue(curLan + QString("EM4_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X20:
                    settings.setValue(curLan + QString("EM4_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X21:
                    settings.setValue(curLan + QString("EM4_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X22:
                    settings.setValue(curLan + QString("EM4_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X23:
                    settings.setValue(curLan + QString("EM4_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X24:
                    settings.setValue(curLan + QString("EM4_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X25:
                    settings.setValue(curLan + QString("EM4_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X26:
                    settings.setValue(curLan + QString("EM4_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X27:
                    settings.setValue(curLan + QString("EM4_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                    /*            case IMM_IN_STOP:
                settings.setValue(curLan + QString("IMM_VAR_IN_STOP"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_SAFE:
                settings.setValue(curLan + QString("IMM_VAR_IN_SAFE"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_REJECT:
                settings.setValue(curLan + QString("IMM_VAR_IN_REJECT"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_MCP:
                settings.setValue(curLan + QString("IMM_VAR_IN_MCP"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_MOP:
                settings.setValue(curLan + QString("IMM_VAR_IN_MOP"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_IMOP:
                settings.setValue(curLan + QString("IMM_VAR_IN_IMOP"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_AUTO:
                settings.setValue(curLan + QString("IMM_VAR_IN_AUTO"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_EBP:
                settings.setValue(curLan + QString("IMM_VAR_IN_EBP"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_EFP:
                settings.setValue(curLan + QString("IMM_VAR_IN_EFP"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_MID:
                settings.setValue(curLan + QString("IMM_VAR_IN_MID"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_C1P1:
                settings.setValue(curLan + QString("IMM_VAR_IN_C1P1"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_C1P2:
                settings.setValue(curLan + QString("IMM_VAR_IN_C1P2"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_C2P1:
                settings.setValue(curLan + QString("IMM_VAR_IN_C2P1"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case IMM_IN_C2P2:
                settings.setValue(curLan + QString("IMM_VAR_IN_C2P2"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;

            case RBT_IN_LOW_AIR:
                settings.setValue(curLan + QString("RBT_VAR_IN_LOW_AIR"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_DWN_SAF:
                settings.setValue(curLan + QString("RBT_VAR_IN_DWN_SAF"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_PRO_HOR:
                settings.setValue(curLan + QString("RBT_VAR_IN_PRO_HOR"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_PRO_VER:
                settings.setValue(curLan + QString("RBT_VAR_IN_PRO_VER"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_ARM_SAF:
                settings.setValue(curLan + QString("RBT_VAR_IN_ARM_SAF"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_RUN_ASC:
                settings.setValue(curLan + QString("RBT_VAR_IN_RUN_ASC"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_RUN_DES:
                settings.setValue(curLan + QString("RBT_VAR_IN_RUN_DES"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_PRO_ADV:
                settings.setValue(curLan + QString("RBT_VAR_IN_PRO_ADV"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_PRO_RET:
                settings.setValue(curLan + QString("RBT_VAR_IN_PRO_RET"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_RUN_ADV:
                settings.setValue(curLan + QString("RBT_VAR_IN_RUN_ADV"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_RUN_RET:
                settings.setValue(curLan + QString("RBT_VAR_IN_RUN_RET"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_RUN_HOR:
                settings.setValue(curLan + QString("RBT_VAR_IN_RUN_HOR"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;
            case RBT_IN_RUN_VER:
                settings.setValue(curLan + QString("RBT_VAR_IN_RUN_VER"),QString(ui->tableWidget_In->item(i,2)->text()));
                break;*/
                }
            }
            else
            {
                switch(i)
                {
                case MAIN_X00:
                    settings.remove(curLan + QString("MAIN_VAR_X00"));
                    break;
                case MAIN_X01:
                    settings.remove(curLan + QString("MAIN_VAR_X01"));
                    break;
                case MAIN_X02:
                    settings.remove(curLan + QString("MAIN_VAR_X02"));
                    break;
                case MAIN_X03:
                    settings.remove(curLan + QString("MAIN_VAR_X03"));
                    break;
                case MAIN_X04:
                    settings.remove(curLan + QString("MAIN_VAR_X04"));
                    break;
                case MAIN_X05:
                    settings.remove(curLan + QString("MAIN_VAR_X05"));
                    break;
                case MAIN_X06:
                    settings.remove(curLan + QString("MAIN_VAR_X06"));
                    break;
                case MAIN_X07:
                    settings.remove(curLan + QString("MAIN_VAR_X07"));
                    break;
                case MAIN_X08:
                    settings.remove(curLan + QString("MAIN_VAR_X08"));
                    break;
                case MAIN_X09:
                    settings.remove(curLan + QString("MAIN_VAR_X09"));
                    break;
                case MAIN_X10:
                    settings.remove(curLan + QString("MAIN_VAR_X10"));
                    break;
                case MAIN_X11:
                    settings.remove(curLan + QString("MAIN_VAR_X11"));
                    break;
                case MAIN_X12:
                    settings.remove(curLan + QString("MAIN_VAR_X12"));
                    break;
                case MAIN_X13:
                    settings.remove(curLan + QString("MAIN_VAR_X13"));
                    break;
                case MAIN_X14:
                    settings.remove(curLan + QString("MAIN_VAR_X14"));
                    break;
                case MAIN_X15:
                    settings.remove(curLan + QString("MAIN_VAR_X15"));
                    break;
                case EM1_X00:
                    settings.remove(curLan + QString("MAIN_VAR_X16"));
                    break;
                case EM1_X01:
                    settings.remove(curLan + QString("MAIN_VAR_X17"));
                    break;
                case EM1_X02:
                    settings.remove(curLan + QString("MAIN_VAR_X18"));
                    break;
                case EM1_X03:
                    settings.remove(curLan + QString("MAIN_VAR_X19"));
                    break;
                case EM1_X04:
                    settings.remove(curLan + QString("MAIN_VAR_X20"));
                    break;
                case EM1_X05:
                    settings.remove(curLan + QString("MAIN_VAR_X21"));
                    break;
                case EM1_X06:
                    settings.remove(curLan + QString("MAIN_VAR_X22"));
                    break;
                case EM1_X07:
                    settings.remove(curLan + QString("MAIN_VAR_X23"));
                    break;
                case EM1_X08:
                    settings.remove(curLan + QString("MAIN_VAR_X24"));
                    break;
                case EM1_X09:
                    settings.remove(curLan + QString("MAIN_VAR_X25"));
                    break;
                case EM1_X10:
                    settings.remove(curLan + QString("MAIN_VAR_X26"));
                    break;
                case EM1_X11:
                    settings.remove(curLan + QString("MAIN_VAR_X27"));
                    break;

                case EM1_X12:
                    settings.remove(curLan + QString("EM1_VAR_X00"));
                    break;
                case EM1_X13:
                    settings.remove(curLan + QString("EM1_VAR_X01"));
                    break;
                case EM1_X14:
                    settings.remove(curLan + QString("EM1_VAR_X02"));
                    break;
                case EM1_X15:
                    settings.remove(curLan + QString("EM1_VAR_X03"));
                    break;
                case EM2_X00:
                    settings.remove(curLan + QString("EM1_VAR_X04"));
                    break;
                case EM2_X01:
                    settings.remove(curLan + QString("EM1_VAR_X05"));
                    break;
                case EM2_X02:
                    settings.remove(curLan + QString("EM1_VAR_X06"));
                    break;
                case EM2_X03:
                    settings.remove(curLan + QString("EM1_VAR_X07"));
                    break;
                case EM2_X04:
                    settings.remove(curLan + QString("EM1_VAR_X08"));
                    break;
                case EM2_X05:
                    settings.remove(curLan + QString("EM1_VAR_X09"));
                    break;
                case EM2_X06:
                    settings.remove(curLan + QString("EM1_VAR_X10"));
                    break;
                case EM2_X07:
                    settings.remove(curLan + QString("EM1_VAR_X11"));
                    break;
                case EM2_X08:
                    settings.remove(curLan + QString("EM1_VAR_X12"));
                    break;
                case EM2_X09:
                    settings.remove(curLan + QString("EM1_VAR_X13"));
                    break;
                case EM2_X10:
                    settings.remove(curLan + QString("EM1_VAR_X14"));
                    break;
                case EM2_X11:
                    settings.remove(curLan + QString("EM1_VAR_X15"));
                    break;


                case EM2_X12:
                    settings.remove(curLan + QString("EM2_VAR_X00"));
                    break;
                case EM2_X13:
                    settings.remove(curLan + QString("EM2_VAR_X01"));
                    break;
                case EM2_X14:
                    settings.remove(curLan + QString("EM2_VAR_X02"));
                    break;
                case EM2_X15:
                    settings.remove(curLan + QString("EM2_VAR_X03"));
                    break;
                case EM3_X00:
                    settings.remove(curLan + QString("EM2_VAR_X04"));
                    break;
                case EM3_X01:
                    settings.remove(curLan + QString("EM2_VAR_X05"));
                    break;
                case EM3_X02:
                    settings.remove(curLan + QString("EM2_VAR_X06"));
                    break;
                case EM3_X03:
                    settings.remove(curLan + QString("EM2_VAR_X07"));
                    break;
                case EM3_X04:
                    settings.remove(curLan + QString("EM2_VAR_X08"));
                    break;
                case EM3_X05:
                    settings.remove(curLan + QString("EM2_VAR_X09"));
                    break;
                case EM3_X06:
                    settings.remove(curLan + QString("EM2_VAR_X10"));
                    break;
                case EM3_X07:
                    settings.remove(curLan + QString("EM2_VAR_X11"));
                    break;
                case EM3_X08:
                    settings.remove(curLan + QString("EM2_VAR_X12"));
                    break;
                case EM3_X09:
                    settings.remove(curLan + QString("EM2_VAR_X13"));
                    break;
                case EM3_X10:
                    settings.remove(curLan + QString("EM2_VAR_X14"));
                    break;
                case EM3_X11:
                    settings.remove(curLan + QString("EM2_VAR_X15"));
                    break;


                case EM3_X12:
                    settings.remove(curLan + QString("EM3_VAR_X00"));
                    break;
                case EM3_X13:
                    settings.remove(curLan + QString("EM3_VAR_X01"));
                    break;
                case EM3_X14:
                    settings.remove(curLan + QString("EM3_VAR_X02"));
                    break;
                case EM3_X15:
                    settings.remove(curLan + QString("EM3_VAR_X03"));
                    break;
                case EM4_X00:
                    settings.remove(curLan + QString("EM3_VAR_X04"));
                    break;
                case EM4_X01:
                    settings.remove(curLan + QString("EM3_VAR_X05"));
                    break;
                case EM4_X02:
                    settings.remove(curLan + QString("EM3_VAR_X06"));
                    break;
                case EM4_X03:
                    settings.remove(curLan + QString("EM3_VAR_X07"));
                    break;
                case EM4_X04:
                    settings.remove(curLan + QString("EM3_VAR_X08"));
                    break;
                case EM4_X05:
                    settings.remove(curLan + QString("EM3_VAR_X09"));
                    break;
                case EM4_X06:
                    settings.remove(curLan + QString("EM3_VAR_X10"));
                    break;
                case EM4_X07:
                    settings.remove(curLan + QString("EM3_VAR_X11"));
                    break;
                case EM4_X08:
                    settings.remove(curLan + QString("EM3_VAR_X12"));
                    break;
                case EM4_X09:
                    settings.remove(curLan + QString("EM3_VAR_X13"));
                    break;
                case EM4_X10:
                    settings.remove(curLan + QString("EM3_VAR_X14"));
                    break;
                case EM4_X11:
                    settings.remove(curLan + QString("EM3_VAR_X15"));
                    break;


                case EM4_X12:
                    settings.remove(curLan + QString("EM4_VAR_X00"));
                    break;
                case EM4_X13:
                    settings.remove(curLan + QString("EM4_VAR_X01"));
                    break;
                case EM4_X14:
                    settings.remove(curLan + QString("EM4_VAR_X02"));
                    break;
                case EM4_X15:
                    settings.remove(curLan + QString("EM4_VAR_X03"));
                    break;
                case MAIN_X16:
                    settings.remove(curLan + QString("EM4_VAR_X04"));
                    break;
                case MAIN_X17:
                    settings.remove(curLan + QString("EM4_VAR_X05"));
                    break;
                case MAIN_X18:
                    settings.remove(curLan + QString("EM4_VAR_X06"));
                    break;
                case MAIN_X19:
                    settings.remove(curLan + QString("EM4_VAR_X07"));
                    break;
                case MAIN_X20:
                    settings.remove(curLan + QString("EM4_VAR_X08"));
                    break;
                case MAIN_X21:
                    settings.remove(curLan + QString("EM4_VAR_X09"));
                    break;
                case MAIN_X22:
                    settings.remove(curLan + QString("EM4_VAR_X10"));
                    break;
                case MAIN_X23:
                    settings.remove(curLan + QString("EM4_VAR_X11"));
                    break;
                case MAIN_X24:
                    settings.remove(curLan + QString("EM4_VAR_X12"));
                    break;
                case MAIN_X25:
                    settings.remove(curLan + QString("EM4_VAR_X13"));
                    break;
                case MAIN_X26:
                    settings.remove(curLan + QString("EM4_VAR_X14"));
                    break;
                case MAIN_X27:
                    settings.remove(curLan + QString("EM4_VAR_X15"));
                    break;

                    /*            case IMM_IN_STOP:
                settings.remove(curLan + QString("IMM_VAR_IN_STOP"));
                break;
            case IMM_IN_SAFE:
                settings.remove(curLan + QString("IMM_VAR_IN_SAFE"));
                break;
            case IMM_IN_REJECT:
                settings.remove(curLan + QString("IMM_VAR_IN_REJECT"));
                break;
            case IMM_IN_MCP:
                settings.remove(curLan + QString("IMM_VAR_IN_MCP"));
                break;
            case IMM_IN_MOP:
                settings.remove(curLan + QString("IMM_VAR_IN_MOP"));
                break;
            case IMM_IN_IMOP:
                settings.remove(curLan + QString("IMM_VAR_IN_IMOP"));
                break;
            case IMM_IN_AUTO:
                settings.remove(curLan + QString("IMM_VAR_IN_AUTO"));
                break;
            case IMM_IN_EBP:
                settings.remove(curLan + QString("IMM_VAR_IN_EBP"));
                break;
            case IMM_IN_EFP:
                settings.remove(curLan + QString("IMM_VAR_IN_EFP"));
                break;
            case IMM_IN_MID:
                settings.remove(curLan + QString("IMM_VAR_IN_MID"));
                break;
            case IMM_IN_C1P1:
                settings.remove(curLan + QString("IMM_VAR_IN_C1P1"));
                break;
            case IMM_IN_C1P2:
                settings.remove(curLan + QString("IMM_VAR_IN_C1P2"));
                break;
            case IMM_IN_C2P1:
                settings.remove(curLan + QString("IMM_VAR_IN_C2P1"));
                break;
            case IMM_IN_C2P2:
                settings.remove(curLan + QString("IMM_VAR_IN_C2P2"));
                break;

            case RBT_IN_LOW_AIR:
                settings.remove(curLan + QString("RBT_VAR_IN_LOW_AIR"));
                break;
            case RBT_IN_DWN_SAF:
                settings.remove(curLan + QString("RBT_VAR_IN_DWN_SAF"));
                break;
            case RBT_IN_PRO_HOR:
                settings.remove(curLan + QString("RBT_VAR_IN_PRO_HOR"));
                break;
            case RBT_IN_PRO_VER:
                settings.remove(curLan + QString("RBT_VAR_IN_PRO_VER"));
                break;
            case RBT_IN_ARM_SAF:
                settings.remove(curLan + QString("RBT_VAR_IN_ARM_SAF"));
                break;
            case RBT_IN_RUN_ASC:
                settings.remove(curLan + QString("RBT_VAR_IN_RUN_ASC"));
                break;
            case RBT_IN_RUN_DES:
                settings.remove(curLan + QString("RBT_VAR_IN_RUN_DES"));
                break;
            case RBT_IN_PRO_ADV:
                settings.remove(curLan + QString("RBT_VAR_IN_PRO_ADV"));
                break;
            case RBT_IN_PRO_RET:
                settings.remove(curLan + QString("RBT_VAR_IN_PRO_RET"));
                break;
            case RBT_IN_RUN_ADV:
                settings.remove(curLan + QString("RBT_VAR_IN_RUN_ADV"));
                break;
            case RBT_IN_RUN_RET:
                settings.remove(curLan + QString("RBT_VAR_IN_RUN_RET"));
                break;
            case RBT_IN_RUN_HOR:
                settings.remove(curLan + QString("RBT_VAR_IN_RUN_HOR"));
                break;
            case RBT_IN_RUN_VER:
                settings.remove(curLan + QString("RBT_VAR_IN_RUN_VER"));
                break;*/
                }
            }
        }
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        for(i = 0; i < MAX_INPORT_NUM2; i++)
        {
            if(ui->tableWidget_In->item(i,2)->text() != (""))
            {
                switch(i)
                {
                case MAIN_X00:
                    settings.setValue(curLan + QString("MAIN_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X01:
                    settings.setValue(curLan + QString("MAIN_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X02:
                    settings.setValue(curLan + QString("MAIN_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X03:
                    settings.setValue(curLan + QString("MAIN_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X04:
                    settings.setValue(curLan + QString("MAIN_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X05:
                    settings.setValue(curLan + QString("MAIN_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X06:
                    settings.setValue(curLan + QString("MAIN_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X07:
                    settings.setValue(curLan + QString("MAIN_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X08:
                    settings.setValue(curLan + QString("MAIN_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X09:
                    settings.setValue(curLan + QString("MAIN_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X10:
                    settings.setValue(curLan + QString("MAIN_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X11:
                    settings.setValue(curLan + QString("MAIN_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X12:
                    settings.setValue(curLan + QString("MAIN_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X13:
                    settings.setValue(curLan + QString("MAIN_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X14:
                    settings.setValue(curLan + QString("MAIN_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X15:
                    settings.setValue(curLan + QString("MAIN_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM1_X00:
                    settings.setValue(curLan + QString("MAIN_VAR_X16"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X01:
                    settings.setValue(curLan + QString("MAIN_VAR_X17"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X02:
                    settings.setValue(curLan + QString("MAIN_VAR_X18"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X03:
                    settings.setValue(curLan + QString("MAIN_VAR_X19"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X04:
                    settings.setValue(curLan + QString("MAIN_VAR_X20"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X05:
                    settings.setValue(curLan + QString("MAIN_VAR_X21"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X06:
                    settings.setValue(curLan + QString("MAIN_VAR_X22"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X07:
                    settings.setValue(curLan + QString("MAIN_VAR_X23"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X08:
                    settings.setValue(curLan + QString("MAIN_VAR_X24"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X09:
                    settings.setValue(curLan + QString("MAIN_VAR_X25"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X10:
                    settings.setValue(curLan + QString("MAIN_VAR_X26"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X11:
                    settings.setValue(curLan + QString("MAIN_VAR_X27"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X12:
                    settings.setValue(curLan + QString("MAIN_VAR_X28"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X13:
                    settings.setValue(curLan + QString("MAIN_VAR_X29"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X14:
                    settings.setValue(curLan + QString("MAIN_VAR_X30"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X15:
                    settings.setValue(curLan + QString("MAIN_VAR_X31"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM2_X00:
                    settings.setValue(curLan + QString("EM1_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X01:
                    settings.setValue(curLan + QString("EM1_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X02:
                    settings.setValue(curLan + QString("EM1_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X03:
                    settings.setValue(curLan + QString("EM1_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X04:
                    settings.setValue(curLan + QString("EM1_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X05:
                    settings.setValue(curLan + QString("EM1_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X06:
                    settings.setValue(curLan + QString("EM1_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X07:
                    settings.setValue(curLan + QString("EM1_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X08:
                    settings.setValue(curLan + QString("EM1_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X09:
                    settings.setValue(curLan + QString("EM1_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X10:
                    settings.setValue(curLan + QString("EM1_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X11:
                    settings.setValue(curLan + QString("EM1_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X12:
                    settings.setValue(curLan + QString("EM1_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X13:
                    settings.setValue(curLan + QString("EM1_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X14:
                    settings.setValue(curLan + QString("EM1_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X15:
                    settings.setValue(curLan + QString("EM1_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM3_X00:
                    settings.setValue(curLan + QString("EM2_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X01:
                    settings.setValue(curLan + QString("EM2_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X02:
                    settings.setValue(curLan + QString("EM2_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X03:
                    settings.setValue(curLan + QString("EM2_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X04:
                    settings.setValue(curLan + QString("EM2_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X05:
                    settings.setValue(curLan + QString("EM2_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X06:
                    settings.setValue(curLan + QString("EM2_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X07:
                    settings.setValue(curLan + QString("EM2_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X08:
                    settings.setValue(curLan + QString("EM2_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X09:
                    settings.setValue(curLan + QString("EM2_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X10:
                    settings.setValue(curLan + QString("EM2_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X11:
                    settings.setValue(curLan + QString("EM2_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X12:
                    settings.setValue(curLan + QString("EM2_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X13:
                    settings.setValue(curLan + QString("EM2_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X14:
                    settings.setValue(curLan + QString("EM2_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X15:
                    settings.setValue(curLan + QString("EM2_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM4_X00:
                    settings.setValue(curLan + QString("EM3_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X01:
                    settings.setValue(curLan + QString("EM3_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X02:
                    settings.setValue(curLan + QString("EM3_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X03:
                    settings.setValue(curLan + QString("EM3_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X04:
                    settings.setValue(curLan + QString("EM3_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X05:
                    settings.setValue(curLan + QString("EM3_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X06:
                    settings.setValue(curLan + QString("EM3_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X07:
                    settings.setValue(curLan + QString("EM3_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X08:
                    settings.setValue(curLan + QString("EM3_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X09:
                    settings.setValue(curLan + QString("EM3_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X10:
                    settings.setValue(curLan + QString("EM3_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X11:
                    settings.setValue(curLan + QString("EM3_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X12:
                    settings.setValue(curLan + QString("EM3_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X13:
                    settings.setValue(curLan + QString("EM3_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X14:
                    settings.setValue(curLan + QString("EM3_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X15:
                    settings.setValue(curLan + QString("EM3_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case MAIN_X16:
                    settings.setValue(curLan + QString("EM4_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X17:
                    settings.setValue(curLan + QString("EM4_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X18:
                    settings.setValue(curLan + QString("EM4_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X19:
                    settings.setValue(curLan + QString("EM4_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X20:
                    settings.setValue(curLan + QString("EM4_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X21:
                    settings.setValue(curLan + QString("EM4_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X22:
                    settings.setValue(curLan + QString("EM4_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X23:
                    settings.setValue(curLan + QString("EM4_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X24:
                    settings.setValue(curLan + QString("EM4_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X25:
                    settings.setValue(curLan + QString("EM4_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X26:
                    settings.setValue(curLan + QString("EM4_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X27:
                    settings.setValue(curLan + QString("EM4_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X28:
                    settings.setValue(curLan + QString("EM4_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X29:
                    settings.setValue(curLan + QString("EM4_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X30:
                    settings.setValue(curLan + QString("EM4_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X31:
                    settings.setValue(curLan + QString("EM4_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                }
            }
            else
            {
                switch(i)
                {
                case MAIN_X00:
                    settings.remove(curLan + QString("MAIN_VAR_X00"));
                    break;
                case MAIN_X01:
                    settings.remove(curLan + QString("MAIN_VAR_X01"));
                    break;
                case MAIN_X02:
                    settings.remove(curLan + QString("MAIN_VAR_X02"));
                    break;
                case MAIN_X03:
                    settings.remove(curLan + QString("MAIN_VAR_X03"));
                    break;
                case MAIN_X04:
                    settings.remove(curLan + QString("MAIN_VAR_X04"));
                    break;
                case MAIN_X05:
                    settings.remove(curLan + QString("MAIN_VAR_X05"));
                    break;
                case MAIN_X06:
                    settings.remove(curLan + QString("MAIN_VAR_X06"));
                    break;
                case MAIN_X07:
                    settings.remove(curLan + QString("MAIN_VAR_X07"));
                    break;
                case MAIN_X08:
                    settings.remove(curLan + QString("MAIN_VAR_X08"));
                    break;
                case MAIN_X09:
                    settings.remove(curLan + QString("MAIN_VAR_X09"));
                    break;
                case MAIN_X10:
                    settings.remove(curLan + QString("MAIN_VAR_X10"));
                    break;
                case MAIN_X11:
                    settings.remove(curLan + QString("MAIN_VAR_X11"));
                    break;
                case MAIN_X12:
                    settings.remove(curLan + QString("MAIN_VAR_X12"));
                    break;
                case MAIN_X13:
                    settings.remove(curLan + QString("MAIN_VAR_X13"));
                    break;
                case MAIN_X14:
                    settings.remove(curLan + QString("MAIN_VAR_X14"));
                    break;
                case MAIN_X15:
                    settings.remove(curLan + QString("MAIN_VAR_X15"));
                    break;
                case EM1_X00:
                    settings.remove(curLan + QString("MAIN_VAR_X16"));
                    break;
                case EM1_X01:
                    settings.remove(curLan + QString("MAIN_VAR_X17"));
                    break;
                case EM1_X02:
                    settings.remove(curLan + QString("MAIN_VAR_X18"));
                    break;
                case EM1_X03:
                    settings.remove(curLan + QString("MAIN_VAR_X19"));
                    break;
                case EM1_X04:
                    settings.remove(curLan + QString("MAIN_VAR_X20"));
                    break;
                case EM1_X05:
                    settings.remove(curLan + QString("MAIN_VAR_X21"));
                    break;
                case EM1_X06:
                    settings.remove(curLan + QString("MAIN_VAR_X22"));
                    break;
                case EM1_X07:
                    settings.remove(curLan + QString("MAIN_VAR_X23"));
                    break;
                case EM1_X08:
                    settings.remove(curLan + QString("MAIN_VAR_X24"));
                    break;
                case EM1_X09:
                    settings.remove(curLan + QString("MAIN_VAR_X25"));
                    break;
                case EM1_X10:
                    settings.remove(curLan + QString("MAIN_VAR_X26"));
                    break;
                case EM1_X11:
                    settings.remove(curLan + QString("MAIN_VAR_X27"));
                    break;
                case EM1_X12:
                    settings.remove(curLan + QString("EM1_VAR_X00"));
                    break;
                case EM1_X13:
                    settings.remove(curLan + QString("EM1_VAR_X01"));
                    break;
                case EM1_X14:
                    settings.remove(curLan + QString("EM1_VAR_X02"));
                    break;
                case EM1_X15:
                    settings.remove(curLan + QString("EM1_VAR_X03"));
                    break;
                case EM2_X00:
                    settings.remove(curLan + QString("EM1_VAR_X04"));
                    break;
                case EM2_X01:
                    settings.remove(curLan + QString("EM1_VAR_X05"));
                    break;
                case EM2_X02:
                    settings.remove(curLan + QString("EM1_VAR_X06"));
                    break;
                case EM2_X03:
                    settings.remove(curLan + QString("EM1_VAR_X07"));
                    break;
                case EM2_X04:
                    settings.remove(curLan + QString("EM1_VAR_X08"));
                    break;
                case EM2_X05:
                    settings.remove(curLan + QString("EM1_VAR_X09"));
                    break;
                case EM2_X06:
                    settings.remove(curLan + QString("EM1_VAR_X10"));
                    break;
                case EM2_X07:
                    settings.remove(curLan + QString("EM1_VAR_X11"));
                    break;
                case EM2_X08:
                    settings.remove(curLan + QString("EM1_VAR_X12"));
                    break;
                case EM2_X09:
                    settings.remove(curLan + QString("EM1_VAR_X13"));
                    break;
                case EM2_X10:
                    settings.remove(curLan + QString("EM1_VAR_X14"));
                    break;
                case EM2_X11:
                    settings.remove(curLan + QString("EM1_VAR_X15"));
                    break;
                case EM2_X12:
                    settings.remove(curLan + QString("EM2_VAR_X00"));
                    break;
                case EM2_X13:
                    settings.remove(curLan + QString("EM2_VAR_X01"));
                    break;
                case EM2_X14:
                    settings.remove(curLan + QString("EM2_VAR_X02"));
                    break;
                case EM2_X15:
                    settings.remove(curLan + QString("EM2_VAR_X03"));
                    break;
                case EM3_X00:
                    settings.remove(curLan + QString("EM2_VAR_X04"));
                    break;
                case EM3_X01:
                    settings.remove(curLan + QString("EM2_VAR_X05"));
                    break;
                case EM3_X02:
                    settings.remove(curLan + QString("EM2_VAR_X06"));
                    break;
                case EM3_X03:
                    settings.remove(curLan + QString("EM2_VAR_X07"));
                    break;
                case EM3_X04:
                    settings.remove(curLan + QString("EM2_VAR_X08"));
                    break;
                case EM3_X05:
                    settings.remove(curLan + QString("EM2_VAR_X09"));
                    break;
                case EM3_X06:
                    settings.remove(curLan + QString("EM2_VAR_X10"));
                    break;
                case EM3_X07:
                    settings.remove(curLan + QString("EM2_VAR_X11"));
                    break;
                case EM3_X08:
                    settings.remove(curLan + QString("EM2_VAR_X12"));
                    break;
                case EM3_X09:
                    settings.remove(curLan + QString("EM2_VAR_X13"));
                    break;
                case EM3_X10:
                    settings.remove(curLan + QString("EM2_VAR_X14"));
                    break;
                case EM3_X11:
                    settings.remove(curLan + QString("EM2_VAR_X15"));
                    break;
                case EM3_X12:
                    settings.remove(curLan + QString("EM3_VAR_X00"));
                    break;
                case EM3_X13:
                    settings.remove(curLan + QString("EM3_VAR_X01"));
                    break;
                case EM3_X14:
                    settings.remove(curLan + QString("EM3_VAR_X02"));
                    break;
                case EM3_X15:
                    settings.remove(curLan + QString("EM3_VAR_X03"));
                    break;
                case EM4_X00:
                    settings.remove(curLan + QString("EM3_VAR_X04"));
                    break;
                case EM4_X01:
                    settings.remove(curLan + QString("EM3_VAR_X05"));
                    break;
                case EM4_X02:
                    settings.remove(curLan + QString("EM3_VAR_X06"));
                    break;
                case EM4_X03:
                    settings.remove(curLan + QString("EM3_VAR_X07"));
                    break;
                case EM4_X04:
                    settings.remove(curLan + QString("EM3_VAR_X08"));
                    break;
                case EM4_X05:
                    settings.remove(curLan + QString("EM3_VAR_X09"));
                    break;
                case EM4_X06:
                    settings.remove(curLan + QString("EM3_VAR_X10"));
                    break;
                case EM4_X07:
                    settings.remove(curLan + QString("EM3_VAR_X11"));
                    break;
                case EM4_X08:
                    settings.remove(curLan + QString("EM3_VAR_X12"));
                    break;
                case EM4_X09:
                    settings.remove(curLan + QString("EM3_VAR_X13"));
                    break;
                case EM4_X10:
                    settings.remove(curLan + QString("EM3_VAR_X14"));
                    break;
                case EM4_X11:
                    settings.remove(curLan + QString("EM3_VAR_X15"));
                    break;
                case EM4_X12:
                    settings.remove(curLan + QString("EM4_VAR_X00"));
                    break;
                case EM4_X13:
                    settings.remove(curLan + QString("EM4_VAR_X01"));
                    break;
                case EM4_X14:
                    settings.remove(curLan + QString("EM4_VAR_X02"));
                    break;
                case EM4_X15:
                    settings.remove(curLan + QString("EM4_VAR_X03"));
                    break;
                case MAIN_X16:
                    settings.remove(curLan + QString("EM4_VAR_X04"));
                    break;
                case MAIN_X17:
                    settings.remove(curLan + QString("EM4_VAR_X05"));
                    break;
                case MAIN_X18:
                    settings.remove(curLan + QString("EM4_VAR_X06"));
                    break;
                case MAIN_X19:
                    settings.remove(curLan + QString("EM4_VAR_X07"));
                    break;
                case MAIN_X20:
                    settings.remove(curLan + QString("EM4_VAR_X08"));
                    break;
                case MAIN_X21:
                    settings.remove(curLan + QString("EM4_VAR_X09"));
                    break;
                case MAIN_X22:
                    settings.remove(curLan + QString("EM4_VAR_X10"));
                    break;
                case MAIN_X23:
                    settings.remove(curLan + QString("EM4_VAR_X11"));
                    break;
                case MAIN_X24:
                    settings.remove(curLan + QString("EM4_VAR_X12"));
                    break;
                case MAIN_X25:
                    settings.remove(curLan + QString("EM4_VAR_X13"));
                    break;
                case MAIN_X26:
                    settings.remove(curLan + QString("EM4_VAR_X14"));
                    break;
                case MAIN_X27:
                    settings.remove(curLan + QString("EM4_VAR_X15"));
                    break;
                }
            }
        }
    }
    else
    {
        for(i = 0; i < MAX_INPORT_NUM; i++)
        {
            if(ui->tableWidget_In->item(i,2)->text() != (""))
            {
                switch(i)
                {
                case MAIN_X00:
                    settings.setValue(curLan + QString("MAIN_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X01:
                    settings.setValue(curLan + QString("MAIN_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X02:
                    settings.setValue(curLan + QString("MAIN_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X03:
                    settings.setValue(curLan + QString("MAIN_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X04:
                    settings.setValue(curLan + QString("MAIN_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X05:
                    settings.setValue(curLan + QString("MAIN_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X06:
                    settings.setValue(curLan + QString("MAIN_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X07:
                    settings.setValue(curLan + QString("MAIN_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X08:
                    settings.setValue(curLan + QString("MAIN_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X09:
                    settings.setValue(curLan + QString("MAIN_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X10:
                    settings.setValue(curLan + QString("MAIN_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X11:
                    settings.setValue(curLan + QString("MAIN_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X12:
                    settings.setValue(curLan + QString("MAIN_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X13:
                    settings.setValue(curLan + QString("MAIN_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X14:
                    settings.setValue(curLan + QString("MAIN_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case MAIN_X15:
                    settings.setValue(curLan + QString("MAIN_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM1_X00:
                    settings.setValue(curLan + QString("EM1_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM1_X01:
                    settings.setValue(curLan + QString("EM1_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X02:
                    settings.setValue(curLan + QString("EM1_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X03:
                    settings.setValue(curLan + QString("EM1_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X04:
                    settings.setValue(curLan + QString("EM1_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X05:
                    settings.setValue(curLan + QString("EM1_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X06:
                    settings.setValue(curLan + QString("EM1_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X07:
                    settings.setValue(curLan + QString("EM1_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X08:
                    settings.setValue(curLan + QString("EM1_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X09:
                    settings.setValue(curLan + QString("EM1_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X10:
                    settings.setValue(curLan + QString("EM1_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X11:
                    settings.setValue(curLan + QString("EM1_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X12:
                    settings.setValue(curLan + QString("EM1_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X13:
                    settings.setValue(curLan + QString("EM1_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X14:
                    settings.setValue(curLan + QString("EM1_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM1_X15:
                    settings.setValue(curLan + QString("EM1_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM2_X00:
                    settings.setValue(curLan + QString("EM2_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X01:
                    settings.setValue(curLan + QString("EM2_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X02:
                    settings.setValue(curLan + QString("EM2_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X03:
                    settings.setValue(curLan + QString("EM2_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X04:
                    settings.setValue(curLan + QString("EM2_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X05:
                    settings.setValue(curLan + QString("EM2_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X06:
                    settings.setValue(curLan + QString("EM2_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X07:
                    settings.setValue(curLan + QString("EM2_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X08:
                    settings.setValue(curLan + QString("EM2_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X09:
                    settings.setValue(curLan + QString("EM2_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X10:
                    settings.setValue(curLan + QString("EM2_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X11:
                    settings.setValue(curLan + QString("EM2_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X12:
                    settings.setValue(curLan + QString("EM2_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X13:
                    settings.setValue(curLan + QString("EM2_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X14:
                    settings.setValue(curLan + QString("EM2_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM2_X15:
                    settings.setValue(curLan + QString("EM2_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM3_X00:
                    settings.setValue(curLan + QString("EM3_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X01:
                    settings.setValue(curLan + QString("EM3_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X02:
                    settings.setValue(curLan + QString("EM3_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X03:
                    settings.setValue(curLan + QString("EM3_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X04:
                    settings.setValue(curLan + QString("EM3_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X05:
                    settings.setValue(curLan + QString("EM3_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X06:
                    settings.setValue(curLan + QString("EM3_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X07:
                    settings.setValue(curLan + QString("EM3_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X08:
                    settings.setValue(curLan + QString("EM3_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X09:
                    settings.setValue(curLan + QString("EM3_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X10:
                    settings.setValue(curLan + QString("EM3_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X11:
                    settings.setValue(curLan + QString("EM3_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X12:
                    settings.setValue(curLan + QString("EM3_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X13:
                    settings.setValue(curLan + QString("EM3_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X14:
                    settings.setValue(curLan + QString("EM3_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM3_X15:
                    settings.setValue(curLan + QString("EM3_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;

                case EM4_X00:
                    settings.setValue(curLan + QString("EM4_VAR_X00"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X01:
                    settings.setValue(curLan + QString("EM4_VAR_X01"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X02:
                    settings.setValue(curLan + QString("EM4_VAR_X02"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X03:
                    settings.setValue(curLan + QString("EM4_VAR_X03"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X04:
                    settings.setValue(curLan + QString("EM4_VAR_X04"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X05:
                    settings.setValue(curLan + QString("EM4_VAR_X05"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X06:
                    settings.setValue(curLan + QString("EM4_VAR_X06"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X07:
                    settings.setValue(curLan + QString("EM4_VAR_X07"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X08:
                    settings.setValue(curLan + QString("EM4_VAR_X08"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X09:
                    settings.setValue(curLan + QString("EM4_VAR_X09"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X10:
                    settings.setValue(curLan + QString("EM4_VAR_X10"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X11:
                    settings.setValue(curLan + QString("EM4_VAR_X11"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X12:
                    settings.setValue(curLan + QString("EM4_VAR_X12"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X13:
                    settings.setValue(curLan + QString("EM4_VAR_X13"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X14:
                    settings.setValue(curLan + QString("EM4_VAR_X14"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                case EM4_X15:
                    settings.setValue(curLan + QString("EM4_VAR_X15"),QString(ui->tableWidget_In->item(i,2)->text()));
                    break;
                }
            }
            else
            {
                switch(i)
                {
                case MAIN_X00:
                    settings.remove(curLan + QString("MAIN_VAR_X00"));
                    break;
                case MAIN_X01:
                    settings.remove(curLan + QString("MAIN_VAR_X01"));
                    break;
                case MAIN_X02:
                    settings.remove(curLan + QString("MAIN_VAR_X02"));
                    break;
                case MAIN_X03:
                    settings.remove(curLan + QString("MAIN_VAR_X03"));
                    break;
                case MAIN_X04:
                    settings.remove(curLan + QString("MAIN_VAR_X04"));
                    break;
                case MAIN_X05:
                    settings.remove(curLan + QString("MAIN_VAR_X05"));
                    break;
                case MAIN_X06:
                    settings.remove(curLan + QString("MAIN_VAR_X06"));
                    break;
                case MAIN_X07:
                    settings.remove(curLan + QString("MAIN_VAR_X07"));
                    break;
                case MAIN_X08:
                    settings.remove(curLan + QString("MAIN_VAR_X08"));
                    break;
                case MAIN_X09:
                    settings.remove(curLan + QString("MAIN_VAR_X09"));
                    break;
                case MAIN_X10:
                    settings.remove(curLan + QString("MAIN_VAR_X10"));
                    break;
                case MAIN_X11:
                    settings.remove(curLan + QString("MAIN_VAR_X11"));
                    break;
                case MAIN_X12:
                    settings.remove(curLan + QString("MAIN_VAR_X12"));
                    break;
                case MAIN_X13:
                    settings.remove(curLan + QString("MAIN_VAR_X13"));
                    break;
                case MAIN_X14:
                    settings.remove(curLan + QString("MAIN_VAR_X14"));
                    break;
                case MAIN_X15:
                    settings.remove(curLan + QString("MAIN_VAR_X15"));
                    break;
                case EM1_X00:
                    settings.remove(curLan + QString("EM1_VAR_X00"));
                    break;
                case EM1_X01:
                    settings.remove(curLan + QString("EM1_VAR_X01"));
                    break;
                case EM1_X02:
                    settings.remove(curLan + QString("EM1_VAR_X02"));
                    break;
                case EM1_X03:
                    settings.remove(curLan + QString("EM1_VAR_X03"));
                    break;
                case EM1_X04:
                    settings.remove(curLan + QString("EM1_VAR_X04"));
                    break;
                case EM1_X05:
                    settings.remove(curLan + QString("EM1_VAR_X05"));
                    break;
                case EM1_X06:
                    settings.remove(curLan + QString("EM1_VAR_X06"));
                    break;
                case EM1_X07:
                    settings.remove(curLan + QString("EM1_VAR_X07"));
                    break;
                case EM1_X08:
                    settings.remove(curLan + QString("EM1_VAR_X08"));
                    break;
                case EM1_X09:
                    settings.remove(curLan + QString("EM1_VAR_X09"));
                    break;
                case EM1_X10:
                    settings.remove(curLan + QString("EM1_VAR_X10"));
                    break;
                case EM1_X11:
                    settings.remove(curLan + QString("EM1_VAR_X11"));
                    break;
                case EM1_X12:
                    settings.remove(curLan + QString("EM1_VAR_X12"));
                    break;
                case EM1_X13:
                    settings.remove(curLan + QString("EM1_VAR_X13"));
                    break;
                case EM1_X14:
                    settings.remove(curLan + QString("EM1_VAR_X14"));
                    break;
                case EM1_X15:
                    settings.remove(curLan + QString("EM1_VAR_X15"));
                    break;

                case EM2_X00:
                    settings.remove(curLan + QString("EM2_VAR_X00"));
                    break;
                case EM2_X01:
                    settings.remove(curLan + QString("EM2_VAR_X01"));
                    break;
                case EM2_X02:
                    settings.remove(curLan + QString("EM2_VAR_X02"));
                    break;
                case EM2_X03:
                    settings.remove(curLan + QString("EM2_VAR_X03"));
                    break;
                case EM2_X04:
                    settings.remove(curLan + QString("EM2_VAR_X04"));
                    break;
                case EM2_X05:
                    settings.remove(curLan + QString("EM2_VAR_X05"));
                    break;
                case EM2_X06:
                    settings.remove(curLan + QString("EM2_VAR_X06"));
                    break;
                case EM2_X07:
                    settings.remove(curLan + QString("EM2_VAR_X07"));
                    break;
                case EM2_X08:
                    settings.remove(curLan + QString("EM2_VAR_X08"));
                    break;
                case EM2_X09:
                    settings.remove(curLan + QString("EM2_VAR_X09"));
                    break;
                case EM2_X10:
                    settings.remove(curLan + QString("EM2_VAR_X10"));
                    break;
                case EM2_X11:
                    settings.remove(curLan + QString("EM2_VAR_X11"));
                    break;
                case EM2_X12:
                    settings.remove(curLan + QString("EM2_VAR_X12"));
                    break;
                case EM2_X13:
                    settings.remove(curLan + QString("EM2_VAR_X13"));
                    break;
                case EM2_X14:
                    settings.remove(curLan + QString("EM2_VAR_X14"));
                    break;
                case EM2_X15:
                    settings.remove(curLan + QString("EM2_VAR_X15"));
                    break;

                case EM3_X00:
                    settings.remove(curLan + QString("EM3_VAR_X00"));
                    break;
                case EM3_X01:
                    settings.remove(curLan + QString("EM3_VAR_X01"));
                    break;
                case EM3_X02:
                    settings.remove(curLan + QString("EM3_VAR_X02"));
                    break;
                case EM3_X03:
                    settings.remove(curLan + QString("EM3_VAR_X03"));
                    break;
                case EM3_X04:
                    settings.remove(curLan + QString("EM3_VAR_X04"));
                    break;
                case EM3_X05:
                    settings.remove(curLan + QString("EM3_VAR_X05"));
                    break;
                case EM3_X06:
                    settings.remove(curLan + QString("EM3_VAR_X06"));
                    break;
                case EM3_X07:
                    settings.remove(curLan + QString("EM3_VAR_X07"));
                    break;
                case EM3_X08:
                    settings.remove(curLan + QString("EM3_VAR_X08"));
                    break;
                case EM3_X09:
                    settings.remove(curLan + QString("EM3_VAR_X09"));
                    break;
                case EM3_X10:
                    settings.remove(curLan + QString("EM3_VAR_X10"));
                    break;
                case EM3_X11:
                    settings.remove(curLan + QString("EM3_VAR_X11"));
                    break;
                case EM3_X12:
                    settings.remove(curLan + QString("EM3_VAR_X12"));
                    break;
                case EM3_X13:
                    settings.remove(curLan + QString("EM3_VAR_X13"));
                    break;
                case EM3_X14:
                    settings.remove(curLan + QString("EM3_VAR_X14"));
                    break;
                case EM3_X15:
                    settings.remove(curLan + QString("EM3_VAR_X15"));
                    break;

                case EM4_X00:
                    settings.remove(curLan + QString("EM4_VAR_X00"));
                    break;
                case EM4_X01:
                    settings.remove(curLan + QString("EM4_VAR_X01"));
                    break;
                case EM4_X02:
                    settings.remove(curLan + QString("EM4_VAR_X02"));
                    break;
                case EM4_X03:
                    settings.remove(curLan + QString("EM4_VAR_X03"));
                    break;
                case EM4_X04:
                    settings.remove(curLan + QString("EM4_VAR_X04"));
                    break;
                case EM4_X05:
                    settings.remove(curLan + QString("EM4_VAR_X05"));
                    break;
                case EM4_X06:
                    settings.remove(curLan + QString("EM4_VAR_X06"));
                    break;
                case EM4_X07:
                    settings.remove(curLan + QString("EM4_VAR_X07"));
                    break;
                case EM4_X08:
                    settings.remove(curLan + QString("EM4_VAR_X08"));
                    break;
                case EM4_X09:
                    settings.remove(curLan + QString("EM4_VAR_X09"));
                    break;
                case EM4_X10:
                    settings.remove(curLan + QString("EM4_VAR_X10"));
                    break;
                case EM4_X11:
                    settings.remove(curLan + QString("EM4_VAR_X11"));
                    break;
                case EM4_X12:
                    settings.remove(curLan + QString("EM4_VAR_X12"));
                    break;
                case EM4_X13:
                    settings.remove(curLan + QString("EM4_VAR_X13"));
                    break;
                case EM4_X14:
                    settings.remove(curLan + QString("EM4_VAR_X14"));
                    break;
                case EM4_X15:
                    settings.remove(curLan + QString("EM4_VAR_X15"));
                    break;
                }
            }
        }
    }

    //输出修改名称
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS){
        for(i = 0; i < MAX_OUTPORT_NUM3; i++)
        {
            if(ui->tableWidget_Out->item(i,2)->text() != ("")){
                switch(i)
                {
                case MAIN_Y00:
                    settings.setValue(curLan + QString("MAIN_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y01:
                    settings.setValue(curLan + QString("MAIN_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y02:
                    settings.setValue(curLan + QString("MAIN_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y03:
                    settings.setValue(curLan + QString("MAIN_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y04:
                    settings.setValue(curLan + QString("MAIN_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y05:
                    settings.setValue(curLan + QString("MAIN_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y06:
                    settings.setValue(curLan + QString("MAIN_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y07:
                    settings.setValue(curLan + QString("MAIN_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y08:
                    settings.setValue(curLan + QString("MAIN_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y09:
                    settings.setValue(curLan + QString("MAIN_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y10:
                    settings.setValue(curLan + QString("MAIN_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y11:
                    settings.setValue(curLan + QString("MAIN_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y12:
                    settings.setValue(curLan + QString("MAIN_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y13:
                    settings.setValue(curLan + QString("MAIN_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y14:
                    settings.setValue(curLan + QString("MAIN_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y15:
                    settings.setValue(curLan + QString("MAIN_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;

                case EM1_Y00:
                    settings.setValue(curLan + QString("MAIN_VAR_Y16"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y01:
                    settings.setValue(curLan + QString("MAIN_VAR_Y17"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y02:
                    settings.setValue(curLan + QString("MAIN_VAR_Y18"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y03:
                    settings.setValue(curLan + QString("MAIN_VAR_Y19"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y04:
                    settings.setValue(curLan + QString("MAIN_VAR_Y20"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y05:
                    settings.setValue(curLan + QString("MAIN_VAR_Y21"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y06:
                    settings.setValue(curLan + QString("MAIN_VAR_Y22"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y07:
                    settings.setValue(curLan + QString("MAIN_VAR_Y23"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y08:
                    settings.setValue(curLan + QString("MAIN_VAR_Y24"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y09:
                    settings.setValue(curLan + QString("MAIN_VAR_Y25"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y10:
                    settings.setValue(curLan + QString("MAIN_VAR_Y26"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y11:
                    settings.setValue(curLan + QString("MAIN_VAR_Y27"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y12:
                    settings.setValue(curLan + QString("MAIN_VAR_Y28"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;

                case EM1_Y13:
                    settings.setValue(curLan + QString("EM1_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y14:
                    settings.setValue(curLan + QString("EM1_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y15:
                    settings.setValue(curLan + QString("EM1_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y00:
                    settings.setValue(curLan + QString("EM1_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y01:
                    settings.setValue(curLan + QString("EM1_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y02:
                    settings.setValue(curLan + QString("EM1_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y03:
                    settings.setValue(curLan + QString("EM1_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y04:
                    settings.setValue(curLan + QString("EM1_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y05:
                    settings.setValue(curLan + QString("EM1_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y06:
                    settings.setValue(curLan + QString("EM1_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y07:
                    settings.setValue(curLan + QString("EM1_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y08:
                    settings.setValue(curLan + QString("EM1_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y09:
                    settings.setValue(curLan + QString("EM1_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y10:
                    settings.setValue(curLan + QString("EM1_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y11:
                    settings.setValue(curLan + QString("EM1_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y12:
                    settings.setValue(curLan + QString("EM1_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;

                case EM2_Y13:
                    settings.setValue(curLan + QString("EM2_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y14:
                    settings.setValue(curLan + QString("EM2_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y15:
                    settings.setValue(curLan + QString("EM2_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y00:
                    settings.setValue(curLan + QString("EM2_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y01:
                    settings.setValue(curLan + QString("EM2_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y02:
                    settings.setValue(curLan + QString("EM2_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y03:
                    settings.setValue(curLan + QString("EM2_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y04:
                    settings.setValue(curLan + QString("EM2_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y05:
                    settings.setValue(curLan + QString("EM2_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y06:
                    settings.setValue(curLan + QString("EM2_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y07:
                    settings.setValue(curLan + QString("EM2_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y08:
                    settings.setValue(curLan + QString("EM2_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y09:
                    settings.setValue(curLan + QString("EM2_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y10:
                    settings.setValue(curLan + QString("EM2_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y11:
                    settings.setValue(curLan + QString("EM2_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y12:
                    settings.setValue(curLan + QString("EM2_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;

                case EM3_Y13:
                    settings.setValue(curLan + QString("EM3_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y14:
                    settings.setValue(curLan + QString("EM3_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y15:
                    settings.setValue(curLan + QString("EM3_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y00:
                    settings.setValue(curLan + QString("EM3_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y01:
                    settings.setValue(curLan + QString("EM3_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y02:
                    settings.setValue(curLan + QString("EM3_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y03:
                    settings.setValue(curLan + QString("EM3_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y04:
                    settings.setValue(curLan + QString("EM3_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y05:
                    settings.setValue(curLan + QString("EM3_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y06:
                    settings.setValue(curLan + QString("EM3_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y07:
                    settings.setValue(curLan + QString("EM3_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y08:
                    settings.setValue(curLan + QString("EM3_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y09:
                    settings.setValue(curLan + QString("EM3_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y10:
                    settings.setValue(curLan + QString("EM3_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y11:
                    settings.setValue(curLan + QString("EM3_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y12:
                    settings.setValue(curLan + QString("EM3_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;

                case EM4_Y13:
                    settings.setValue(curLan + QString("EM4_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y14:
                    settings.setValue(curLan + QString("EM4_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y15:
                    settings.setValue(curLan + QString("EM4_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y16:
                    settings.setValue(curLan + QString("EM4_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y17:
                    settings.setValue(curLan + QString("EM4_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y18:
                    settings.setValue(curLan + QString("EM4_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y19:
                    settings.setValue(curLan + QString("EM4_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y20:
                    settings.setValue(curLan + QString("EM4_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y21:
                    settings.setValue(curLan + QString("EM4_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y22:
                    settings.setValue(curLan + QString("EM4_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y23:
                    settings.setValue(curLan + QString("EM4_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y24:
                    settings.setValue(curLan + QString("EM4_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y25:
                    settings.setValue(curLan + QString("EM4_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y26:
                    settings.setValue(curLan + QString("EM4_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y27:
                    settings.setValue(curLan + QString("EM4_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y28:
                    settings.setValue(curLan + QString("EM4_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                }
            }
            else
            {
                switch(i)
                {
                case MAIN_Y00:
                    settings.remove(curLan + QString("MAIN_VAR_Y00"));
                    break;
                case MAIN_Y01:
                    settings.remove(curLan + QString("MAIN_VAR_Y01"));
                    break;
                case MAIN_Y02:
                    settings.remove(curLan + QString("MAIN_VAR_Y02"));
                    break;
                case MAIN_Y03:
                    settings.remove(curLan + QString("MAIN_VAR_Y03"));
                    break;
                case MAIN_Y04:
                    settings.remove(curLan + QString("MAIN_VAR_Y04"));
                    break;
                case MAIN_Y05:
                    settings.remove(curLan + QString("MAIN_VAR_Y05"));
                    break;
                case MAIN_Y06:
                    settings.remove(curLan + QString("MAIN_VAR_Y06"));
                    break;
                case MAIN_Y07:
                    settings.remove(curLan + QString("MAIN_VAR_Y07"));
                    break;
                case MAIN_Y08:
                    settings.remove(curLan + QString("MAIN_VAR_Y08"));
                    break;
                case MAIN_Y09:
                    settings.remove(curLan + QString("MAIN_VAR_Y09"));
                    break;
                case MAIN_Y10:
                    settings.remove(curLan + QString("MAIN_VAR_Y10"));
                    break;
                case MAIN_Y11:
                    settings.remove(curLan + QString("MAIN_VAR_Y11"));
                    break;
                case MAIN_Y12:
                    settings.remove(curLan + QString("MAIN_VAR_Y12"));
                    break;
                case MAIN_Y13:
                    settings.remove(curLan + QString("MAIN_VAR_Y13"));
                    break;
                case MAIN_Y14:
                    settings.remove(curLan + QString("MAIN_VAR_Y14"));
                    break;
                case MAIN_Y15:
                    settings.remove(curLan + QString("MAIN_VAR_Y15"));
                    break;
                case EM1_Y00:
                    settings.remove(curLan + QString("MAIN_VAR_Y16"));
                    break;
                case EM1_Y01:
                    settings.remove(curLan + QString("MAIN_VAR_Y17"));
                    break;
                case EM1_Y02:
                    settings.remove(curLan + QString("MAIN_VAR_Y18"));
                    break;
                case EM1_Y03:
                    settings.remove(curLan + QString("MAIN_VAR_Y19"));
                    break;
                case EM1_Y04:
                    settings.remove(curLan + QString("MAIN_VAR_Y20"));
                    break;
                case EM1_Y05:
                    settings.remove(curLan + QString("MAIN_VAR_Y21"));
                    break;
                case EM1_Y06:
                    settings.remove(curLan + QString("MAIN_VAR_Y22"));
                    break;
                case EM1_Y07:
                    settings.remove(curLan + QString("MAIN_VAR_Y23"));
                    break;
                case EM1_Y08:
                    settings.remove(curLan + QString("MAIN_VAR_Y24"));
                    break;
                case EM1_Y09:
                    settings.remove(curLan + QString("MAIN_VAR_Y25"));
                    break;
                case EM1_Y10:
                    settings.remove(curLan + QString("MAIN_VAR_Y26"));
                    break;
                case EM1_Y11:
                    settings.remove(curLan + QString("MAIN_VAR_Y27"));
                    break;
                case EM1_Y12:
                    settings.remove(curLan + QString("MAIN_VAR_Y28"));
                    break;

                case EM1_Y13:
                    settings.remove(curLan + QString("EM1_VAR_Y00"));
                    break;
                case EM1_Y14:
                    settings.remove(curLan + QString("EM1_VAR_Y01"));
                    break;
                case EM1_Y15:
                    settings.remove(curLan + QString("EM1_VAR_Y02"));
                    break;
                case EM2_Y00:
                    settings.remove(curLan + QString("EM1_VAR_Y03"));
                    break;
                case EM2_Y01:
                    settings.remove(curLan + QString("EM1_VAR_Y04"));
                    break;
                case EM2_Y02:
                    settings.remove(curLan + QString("EM1_VAR_Y05"));
                    break;
                case EM2_Y03:
                    settings.remove(curLan + QString("EM1_VAR_Y06"));
                    break;
                case EM2_Y04:
                    settings.remove(curLan + QString("EM1_VAR_Y07"));
                    break;
                case EM2_Y05:
                    settings.remove(curLan + QString("EM1_VAR_Y08"));
                    break;
                case EM2_Y06:
                    settings.remove(curLan + QString("EM1_VAR_Y09"));
                    break;
                case EM2_Y07:
                    settings.remove(curLan + QString("EM1_VAR_Y10"));
                    break;
                case EM2_Y08:
                    settings.remove(curLan + QString("EM1_VAR_Y11"));
                    break;
                case EM2_Y09:
                    settings.remove(curLan + QString("EM1_VAR_Y12"));
                    break;
                case EM2_Y10:
                    settings.remove(curLan + QString("EM1_VAR_Y13"));
                    break;
                case EM2_Y11:
                    settings.remove(curLan + QString("EM1_VAR_Y14"));
                    break;
                case EM2_Y12:
                    settings.remove(curLan + QString("EM1_VAR_Y15"));
                    break;


                case EM2_Y13:
                    settings.remove(curLan + QString("EM2_VAR_Y00"));
                    break;
                case EM2_Y14:
                    settings.remove(curLan + QString("EM2_VAR_Y01"));
                    break;
                case EM2_Y15:
                    settings.remove(curLan + QString("EM2_VAR_Y02"));
                    break;
                case EM3_Y00:
                    settings.remove(curLan + QString("EM2_VAR_Y03"));
                    break;
                case EM3_Y01:
                    settings.remove(curLan + QString("EM2_VAR_Y04"));
                    break;
                case EM3_Y02:
                    settings.remove(curLan + QString("EM2_VAR_Y05"));
                    break;
                case EM3_Y03:
                    settings.remove(curLan + QString("EM2_VAR_Y06"));
                    break;
                case EM3_Y04:
                    settings.remove(curLan + QString("EM2_VAR_Y07"));
                    break;
                case EM3_Y05:
                    settings.remove(curLan + QString("EM2_VAR_Y08"));
                    break;
                case EM3_Y06:
                    settings.remove(curLan + QString("EM2_VAR_Y09"));
                    break;
                case EM3_Y07:
                    settings.remove(curLan + QString("EM2_VAR_Y10"));
                    break;
                case EM3_Y08:
                    settings.remove(curLan + QString("EM2_VAR_Y11"));
                    break;
                case EM3_Y09:
                    settings.remove(curLan + QString("EM2_VAR_Y12"));
                    break;
                case EM3_Y10:
                    settings.remove(curLan + QString("EM2_VAR_Y13"));
                    break;
                case EM3_Y11:
                    settings.remove(curLan + QString("EM2_VAR_Y14"));
                    break;
                case EM3_Y12:
                    settings.remove(curLan + QString("EM2_VAR_Y15"));
                    break;


                case EM3_Y13:
                    settings.remove(curLan + QString("EM3_VAR_Y00"));
                    break;
                case EM3_Y14:
                    settings.remove(curLan + QString("EM3_VAR_Y01"));
                    break;
                case EM3_Y15:
                    settings.remove(curLan + QString("EM3_VAR_Y02"));
                    break;
                case EM4_Y00:
                    settings.remove(curLan + QString("EM3_VAR_Y03"));
                    break;
                case EM4_Y01:
                    settings.remove(curLan + QString("EM3_VAR_Y04"));
                    break;
                case EM4_Y02:
                    settings.remove(curLan + QString("EM3_VAR_Y05"));
                    break;
                case EM4_Y03:
                    settings.remove(curLan + QString("EM3_VAR_Y06"));
                    break;
                case EM4_Y04:
                    settings.remove(curLan + QString("EM3_VAR_Y07"));
                    break;
                case EM4_Y05:
                    settings.remove(curLan + QString("EM3_VAR_Y08"));
                    break;
                case EM4_Y06:
                    settings.remove(curLan + QString("EM3_VAR_Y09"));
                    break;
                case EM4_Y07:
                    settings.remove(curLan + QString("EM3_VAR_Y10"));
                    break;
                case EM4_Y08:
                    settings.remove(curLan + QString("EM3_VAR_Y11"));
                    break;
                case EM4_Y09:
                    settings.remove(curLan + QString("EM3_VAR_Y12"));
                    break;
                case EM4_Y10:
                    settings.remove(curLan + QString("EM3_VAR_Y13"));
                    break;
                case EM4_Y11:
                    settings.remove(curLan + QString("EM3_VAR_Y14"));
                    break;
                case EM4_Y12:
                    settings.remove(curLan + QString("EM3_VAR_Y15"));
                    break;


                case EM4_Y13:
                    settings.remove(curLan + QString("EM4_VAR_Y00"));
                    break;
                case EM4_Y14:
                    settings.remove(curLan + QString("EM4_VAR_Y01"));
                    break;
                case EM4_Y15:
                    settings.remove(curLan + QString("EM4_VAR_Y02"));
                    break;
                case MAIN_Y16:
                    settings.remove(curLan + QString("EM4_VAR_Y03"));
                    break;
                case MAIN_Y17:
                    settings.remove(curLan + QString("EM4_VAR_Y04"));
                    break;
                case MAIN_Y18:
                    settings.remove(curLan + QString("EM4_VAR_Y05"));
                    break;
                case MAIN_Y19:
                    settings.remove(curLan + QString("EM4_VAR_Y06"));
                    break;
                case MAIN_Y20:
                    settings.remove(curLan + QString("EM4_VAR_Y07"));
                    break;
                case MAIN_Y21:
                    settings.remove(curLan + QString("EM4_VAR_Y08"));
                    break;
                case MAIN_Y22:
                    settings.remove(curLan + QString("EM4_VAR_Y09"));
                    break;
                case MAIN_Y23:
                    settings.remove(curLan + QString("EM4_VAR_Y10"));
                    break;
                case MAIN_Y24:
                    settings.remove(curLan + QString("EM4_VAR_Y11"));
                    break;
                case MAIN_Y25:
                    settings.remove(curLan + QString("EM4_VAR_Y12"));
                    break;
                case MAIN_Y26:
                    settings.remove(curLan + QString("EM4_VAR_Y13"));
                    break;
                case MAIN_Y27:
                    settings.remove(curLan + QString("EM4_VAR_Y14"));
                    break;
                case MAIN_Y28:
                    settings.remove(curLan + QString("EM4_VAR_Y15"));
                    break;
                }
            }
        }
    }
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS){
        for(i = 0; i < MAX_OUTPORT_NUM2; i++)
        {
            if(ui->tableWidget_Out->item(i,2)->text() != (""))
            {
                switch(i)
                {
                case MAIN_Y00:
                    settings.setValue(curLan + QString("MAIN_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y01:
                    settings.setValue(curLan + QString("MAIN_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y02:
                    settings.setValue(curLan + QString("MAIN_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y03:
                    settings.setValue(curLan + QString("MAIN_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y04:
                    settings.setValue(curLan + QString("MAIN_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y05:
                    settings.setValue(curLan + QString("MAIN_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y06:
                    settings.setValue(curLan + QString("MAIN_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y07:
                    settings.setValue(curLan + QString("MAIN_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y08:
                    settings.setValue(curLan + QString("MAIN_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y09:
                    settings.setValue(curLan + QString("MAIN_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y10:
                    settings.setValue(curLan + QString("MAIN_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y11:
                    settings.setValue(curLan + QString("MAIN_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y12:
                    settings.setValue(curLan + QString("MAIN_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y13:
                    settings.setValue(curLan + QString("MAIN_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y14:
                    settings.setValue(curLan + QString("MAIN_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y15:
                    settings.setValue(curLan + QString("MAIN_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y00:
                    settings.setValue(curLan + QString("MAIN_VAR_Y16"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y01:
                    settings.setValue(curLan + QString("MAIN_VAR_Y17"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y02:
                    settings.setValue(curLan + QString("MAIN_VAR_Y18"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y03:
                    settings.setValue(curLan + QString("MAIN_VAR_Y19"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y04:
                    settings.setValue(curLan + QString("MAIN_VAR_Y20"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y05:
                    settings.setValue(curLan + QString("MAIN_VAR_Y21"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y06:
                    settings.setValue(curLan + QString("MAIN_VAR_Y22"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y07:
                    settings.setValue(curLan + QString("MAIN_VAR_Y23"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y08:
                    settings.setValue(curLan + QString("MAIN_VAR_Y24"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y09:
                    settings.setValue(curLan + QString("MAIN_VAR_Y25"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y10:
                    settings.setValue(curLan + QString("MAIN_VAR_Y26"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y11:
                    settings.setValue(curLan + QString("MAIN_VAR_Y27"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y12:
                    settings.setValue(curLan + QString("MAIN_VAR_Y28"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y13:
                    settings.setValue(curLan + QString("MAIN_VAR_Y29"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y14:
                    settings.setValue(curLan + QString("MAIN_VAR_Y30"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y15:
                    settings.setValue(curLan + QString("MAIN_VAR_Y31"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y00:
                    settings.setValue(curLan + QString("EM1_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y01:
                    settings.setValue(curLan + QString("EM1_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y02:
                    settings.setValue(curLan + QString("EM1_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y03:
                    settings.setValue(curLan + QString("EM1_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y04:
                    settings.setValue(curLan + QString("EM1_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y05:
                    settings.setValue(curLan + QString("EM1_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y06:
                    settings.setValue(curLan + QString("EM1_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y07:
                    settings.setValue(curLan + QString("EM1_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y08:
                    settings.setValue(curLan + QString("EM1_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y09:
                    settings.setValue(curLan + QString("EM1_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y10:
                    settings.setValue(curLan + QString("EM1_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y11:
                    settings.setValue(curLan + QString("EM1_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y12:
                    settings.setValue(curLan + QString("EM1_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y13:
                    settings.setValue(curLan + QString("EM1_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y14:
                    settings.setValue(curLan + QString("EM1_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y15:
                    settings.setValue(curLan + QString("EM1_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y00:
                    settings.setValue(curLan + QString("EM2_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y01:
                    settings.setValue(curLan + QString("EM2_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y02:
                    settings.setValue(curLan + QString("EM2_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y03:
                    settings.setValue(curLan + QString("EM2_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y04:
                    settings.setValue(curLan + QString("EM2_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y05:
                    settings.setValue(curLan + QString("EM2_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y06:
                    settings.setValue(curLan + QString("EM2_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y07:
                    settings.setValue(curLan + QString("EM2_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y08:
                    settings.setValue(curLan + QString("EM2_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y09:
                    settings.setValue(curLan + QString("EM2_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y10:
                    settings.setValue(curLan + QString("EM2_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y11:
                    settings.setValue(curLan + QString("EM2_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y12:
                    settings.setValue(curLan + QString("EM2_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y13:
                    settings.setValue(curLan + QString("EM2_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y14:
                    settings.setValue(curLan + QString("EM2_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y15:
                    settings.setValue(curLan + QString("EM2_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y00:
                    settings.setValue(curLan + QString("EM3_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y01:
                    settings.setValue(curLan + QString("EM3_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y02:
                    settings.setValue(curLan + QString("EM3_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y03:
                    settings.setValue(curLan + QString("EM3_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y04:
                    settings.setValue(curLan + QString("EM3_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y05:
                    settings.setValue(curLan + QString("EM3_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y06:
                    settings.setValue(curLan + QString("EM3_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y07:
                    settings.setValue(curLan + QString("EM3_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y08:
                    settings.setValue(curLan + QString("EM3_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y09:
                    settings.setValue(curLan + QString("EM3_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y10:
                    settings.setValue(curLan + QString("EM3_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y11:
                    settings.setValue(curLan + QString("EM3_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y12:
                    settings.setValue(curLan + QString("EM3_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y13:
                    settings.setValue(curLan + QString("EM3_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y14:
                    settings.setValue(curLan + QString("EM3_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y15:
                    settings.setValue(curLan + QString("EM3_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y16:
                    settings.setValue(curLan + QString("EM4_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y17:
                    settings.setValue(curLan + QString("EM4_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y18:
                    settings.setValue(curLan + QString("EM4_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y19:
                    settings.setValue(curLan + QString("EM4_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y20:
                    settings.setValue(curLan + QString("EM4_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y21:
                    settings.setValue(curLan + QString("EM4_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y22:
                    settings.setValue(curLan + QString("EM4_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y23:
                    settings.setValue(curLan + QString("EM4_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y24:
                    settings.setValue(curLan + QString("EM4_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y25:
                    settings.setValue(curLan + QString("EM4_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y26:
                    settings.setValue(curLan + QString("EM4_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y27:
                    settings.setValue(curLan + QString("EM4_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y28:
                    settings.setValue(curLan + QString("EM4_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y29:
                    settings.setValue(curLan + QString("EM4_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y30:
                    settings.setValue(curLan + QString("EM4_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y31:
                    settings.setValue(curLan + QString("EM4_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                }
            }
            else
            {
                switch(i)
                {
                case MAIN_Y00:
                    settings.remove(curLan + QString("MAIN_VAR_Y00"));
                    break;
                case MAIN_Y01:
                    settings.remove(curLan + QString("MAIN_VAR_Y01"));
                    break;
                case MAIN_Y02:
                    settings.remove(curLan + QString("MAIN_VAR_Y02"));
                    break;
                case MAIN_Y03:
                    settings.remove(curLan + QString("MAIN_VAR_Y03"));
                    break;
                case MAIN_Y04:
                    settings.remove(curLan + QString("MAIN_VAR_Y04"));
                    break;
                case MAIN_Y05:
                    settings.remove(curLan + QString("MAIN_VAR_Y05"));
                    break;
                case MAIN_Y06:
                    settings.remove(curLan + QString("MAIN_VAR_Y06"));
                    break;
                case MAIN_Y07:
                    settings.remove(curLan + QString("MAIN_VAR_Y07"));
                    break;
                case MAIN_Y08:
                    settings.remove(curLan + QString("MAIN_VAR_Y08"));
                    break;
                case MAIN_Y09:
                    settings.remove(curLan + QString("MAIN_VAR_Y09"));
                    break;
                case MAIN_Y10:
                    settings.remove(curLan + QString("MAIN_VAR_Y10"));
                    break;
                case MAIN_Y11:
                    settings.remove(curLan + QString("MAIN_VAR_Y11"));
                    break;
                case MAIN_Y12:
                    settings.remove(curLan + QString("MAIN_VAR_Y12"));
                    break;
                case MAIN_Y13:
                    settings.remove(curLan + QString("MAIN_VAR_Y13"));
                    break;
                case MAIN_Y14:
                    settings.remove(curLan + QString("MAIN_VAR_Y14"));
                    break;
                case MAIN_Y15:
                    settings.remove(curLan + QString("MAIN_VAR_Y15"));
                    break;
                case EM1_Y00:
                    settings.remove(curLan + QString("MAIN_VAR_Y16"));
                    break;
                case EM1_Y01:
                    settings.remove(curLan + QString("MAIN_VAR_Y17"));
                    break;
                case EM1_Y02:
                    settings.remove(curLan + QString("MAIN_VAR_Y18"));
                    break;
                case EM1_Y03:
                    settings.remove(curLan + QString("MAIN_VAR_Y19"));
                    break;
                case EM1_Y04:
                    settings.remove(curLan + QString("MAIN_VAR_Y20"));
                    break;
                case EM1_Y05:
                    settings.remove(curLan + QString("MAIN_VAR_Y21"));
                    break;
                case EM1_Y06:
                    settings.remove(curLan + QString("MAIN_VAR_Y22"));
                    break;
                case EM1_Y07:
                    settings.remove(curLan + QString("MAIN_VAR_Y23"));
                    break;
                case EM1_Y08:
                    settings.remove(curLan + QString("MAIN_VAR_Y24"));
                    break;
                case EM1_Y09:
                    settings.remove(curLan + QString("MAIN_VAR_Y25"));
                    break;
                case EM1_Y10:
                    settings.remove(curLan + QString("MAIN_VAR_Y26"));
                    break;
                case EM1_Y11:
                    settings.remove(curLan + QString("MAIN_VAR_Y27"));
                    break;
                case EM1_Y12:
                    settings.remove(curLan + QString("MAIN_VAR_Y28"));
                    break;

                case EM1_Y13:
                    settings.remove(curLan + QString("EM1_VAR_Y00"));
                    break;
                case EM1_Y14:
                    settings.remove(curLan + QString("EM1_VAR_Y01"));
                    break;
                case EM1_Y15:
                    settings.remove(curLan + QString("EM1_VAR_Y02"));
                    break;
                case EM2_Y00:
                    settings.remove(curLan + QString("EM1_VAR_Y03"));
                    break;
                case EM2_Y01:
                    settings.remove(curLan + QString("EM1_VAR_Y04"));
                    break;
                case EM2_Y02:
                    settings.remove(curLan + QString("EM1_VAR_Y05"));
                    break;
                case EM2_Y03:
                    settings.remove(curLan + QString("EM1_VAR_Y06"));
                    break;
                case EM2_Y04:
                    settings.remove(curLan + QString("EM1_VAR_Y07"));
                    break;
                case EM2_Y05:
                    settings.remove(curLan + QString("EM1_VAR_Y08"));
                    break;
                case EM2_Y06:
                    settings.remove(curLan + QString("EM1_VAR_Y09"));
                    break;
                case EM2_Y07:
                    settings.remove(curLan + QString("EM1_VAR_Y10"));
                    break;
                case EM2_Y08:
                    settings.remove(curLan + QString("EM1_VAR_Y11"));
                    break;
                case EM2_Y09:
                    settings.remove(curLan + QString("EM1_VAR_Y12"));
                    break;
                case EM2_Y10:
                    settings.remove(curLan + QString("EM1_VAR_Y13"));
                    break;
                case EM2_Y11:
                    settings.remove(curLan + QString("EM1_VAR_Y14"));
                    break;
                case EM2_Y12:
                    settings.remove(curLan + QString("EM1_VAR_Y15"));
                    break;


                case EM2_Y13:
                    settings.remove(curLan + QString("EM2_VAR_Y00"));
                    break;
                case EM2_Y14:
                    settings.remove(curLan + QString("EM2_VAR_Y01"));
                    break;
                case EM2_Y15:
                    settings.remove(curLan + QString("EM2_VAR_Y02"));
                    break;
                case EM3_Y00:
                    settings.remove(curLan + QString("EM2_VAR_Y03"));
                    break;
                case EM3_Y01:
                    settings.remove(curLan + QString("EM2_VAR_Y04"));
                    break;
                case EM3_Y02:
                    settings.remove(curLan + QString("EM2_VAR_Y05"));
                    break;
                case EM3_Y03:
                    settings.remove(curLan + QString("EM2_VAR_Y06"));
                    break;
                case EM3_Y04:
                    settings.remove(curLan + QString("EM2_VAR_Y07"));
                    break;
                case EM3_Y05:
                    settings.remove(curLan + QString("EM2_VAR_Y08"));
                    break;
                case EM3_Y06:
                    settings.remove(curLan + QString("EM2_VAR_Y09"));
                    break;
                case EM3_Y07:
                    settings.remove(curLan + QString("EM2_VAR_Y10"));
                    break;
                case EM3_Y08:
                    settings.remove(curLan + QString("EM2_VAR_Y11"));
                    break;
                case EM3_Y09:
                    settings.remove(curLan + QString("EM2_VAR_Y12"));
                    break;
                case EM3_Y10:
                    settings.remove(curLan + QString("EM2_VAR_Y13"));
                    break;
                case EM3_Y11:
                    settings.remove(curLan + QString("EM2_VAR_Y14"));
                    break;
                case EM3_Y12:
                    settings.remove(curLan + QString("EM2_VAR_Y15"));
                    break;


                case EM3_Y13:
                    settings.remove(curLan + QString("EM3_VAR_Y00"));
                    break;
                case EM3_Y14:
                    settings.remove(curLan + QString("EM3_VAR_Y01"));
                    break;
                case EM3_Y15:
                    settings.remove(curLan + QString("EM3_VAR_Y02"));
                    break;
                case EM4_Y00:
                    settings.remove(curLan + QString("EM3_VAR_Y03"));
                    break;
                case EM4_Y01:
                    settings.remove(curLan + QString("EM3_VAR_Y04"));
                    break;
                case EM4_Y02:
                    settings.remove(curLan + QString("EM3_VAR_Y05"));
                    break;
                case EM4_Y03:
                    settings.remove(curLan + QString("EM3_VAR_Y06"));
                    break;
                case EM4_Y04:
                    settings.remove(curLan + QString("EM3_VAR_Y07"));
                    break;
                case EM4_Y05:
                    settings.remove(curLan + QString("EM3_VAR_Y08"));
                    break;
                case EM4_Y06:
                    settings.remove(curLan + QString("EM3_VAR_Y09"));
                    break;
                case EM4_Y07:
                    settings.remove(curLan + QString("EM3_VAR_Y10"));
                    break;
                case EM4_Y08:
                    settings.remove(curLan + QString("EM3_VAR_Y11"));
                    break;
                case EM4_Y09:
                    settings.remove(curLan + QString("EM3_VAR_Y12"));
                    break;
                case EM4_Y10:
                    settings.remove(curLan + QString("EM3_VAR_Y13"));
                    break;
                case EM4_Y11:
                    settings.remove(curLan + QString("EM3_VAR_Y14"));
                    break;
                case EM4_Y12:
                    settings.remove(curLan + QString("EM3_VAR_Y15"));
                    break;


                case EM4_Y13:
                    settings.remove(curLan + QString("EM4_VAR_Y00"));
                    break;
                case EM4_Y14:
                    settings.remove(curLan + QString("EM4_VAR_Y01"));
                    break;
                case EM4_Y15:
                    settings.remove(curLan + QString("EM4_VAR_Y02"));
                    break;
                case MAIN_Y16:
                    settings.remove(curLan + QString("EM4_VAR_Y03"));
                    break;
                case MAIN_Y17:
                    settings.remove(curLan + QString("EM4_VAR_Y04"));
                    break;
                case MAIN_Y18:
                    settings.remove(curLan + QString("EM4_VAR_Y05"));
                    break;
                case MAIN_Y19:
                    settings.remove(curLan + QString("EM4_VAR_Y06"));
                    break;
                case MAIN_Y20:
                    settings.remove(curLan + QString("EM4_VAR_Y07"));
                    break;
                case MAIN_Y21:
                    settings.remove(curLan + QString("EM4_VAR_Y08"));
                    break;
                case MAIN_Y22:
                    settings.remove(curLan + QString("EM4_VAR_Y09"));
                    break;
                case MAIN_Y23:
                    settings.remove(curLan + QString("EM4_VAR_Y10"));
                    break;
                case MAIN_Y24:
                    settings.remove(curLan + QString("EM4_VAR_Y11"));
                    break;
                case MAIN_Y25:
                    settings.remove(curLan + QString("EM4_VAR_Y12"));
                    break;
                case MAIN_Y26:
                    settings.remove(curLan + QString("EM4_VAR_Y13"));
                    break;
                case MAIN_Y27:
                    settings.remove(curLan + QString("EM4_VAR_Y14"));
                    break;
                case MAIN_Y28:
                    settings.remove(curLan + QString("EM4_VAR_Y15"));
                    break;
                }
            }
        }
    }
    else
    {
        for(i = 0; i < MAX_OUTPORT_NUM; i++)
        {
            if(ui->tableWidget_Out->item(i,2)->text() != (""))
            {
                switch(i)
                {
                case MAIN_Y00:
                    settings.setValue(curLan + QString("MAIN_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y01:
                    settings.setValue(curLan + QString("MAIN_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y02:
                    settings.setValue(curLan + QString("MAIN_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y03:
                    settings.setValue(curLan + QString("MAIN_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y04:
                    settings.setValue(curLan + QString("MAIN_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y05:
                    settings.setValue(curLan + QString("MAIN_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y06:
                    settings.setValue(curLan + QString("MAIN_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y07:
                    settings.setValue(curLan + QString("MAIN_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y08:
                    settings.setValue(curLan + QString("MAIN_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y09:
                    settings.setValue(curLan + QString("MAIN_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y10:
                    settings.setValue(curLan + QString("MAIN_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y11:
                    settings.setValue(curLan + QString("MAIN_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y12:
                    settings.setValue(curLan + QString("MAIN_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y13:
                    settings.setValue(curLan + QString("MAIN_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y14:
                    settings.setValue(curLan + QString("MAIN_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case MAIN_Y15:
                    settings.setValue(curLan + QString("MAIN_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y00:
                    settings.setValue(curLan + QString("EM1_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y01:
                    settings.setValue(curLan + QString("EM1_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y02:
                    settings.setValue(curLan + QString("EM1_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y03:
                    settings.setValue(curLan + QString("EM1_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y04:
                    settings.setValue(curLan + QString("EM1_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y05:
                    settings.setValue(curLan + QString("EM1_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y06:
                    settings.setValue(curLan + QString("EM1_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y07:
                    settings.setValue(curLan + QString("EM1_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y08:
                    settings.setValue(curLan + QString("EM1_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y09:
                    settings.setValue(curLan + QString("EM1_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y10:
                    settings.setValue(curLan + QString("EM1_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y11:
                    settings.setValue(curLan + QString("EM1_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y12:
                    settings.setValue(curLan + QString("EM1_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y13:
                    settings.setValue(curLan + QString("EM1_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y14:
                    settings.setValue(curLan + QString("EM1_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM1_Y15:
                    settings.setValue(curLan + QString("EM1_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;

                case EM2_Y00:
                    settings.setValue(curLan + QString("EM2_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y01:
                    settings.setValue(curLan + QString("EM2_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y02:
                    settings.setValue(curLan + QString("EM2_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y03:
                    settings.setValue(curLan + QString("EM2_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y04:
                    settings.setValue(curLan + QString("EM2_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y05:
                    settings.setValue(curLan + QString("EM2_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y06:
                    settings.setValue(curLan + QString("EM2_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y07:
                    settings.setValue(curLan + QString("EM2_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y08:
                    settings.setValue(curLan + QString("EM2_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y09:
                    settings.setValue(curLan + QString("EM2_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y10:
                    settings.setValue(curLan + QString("EM2_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y11:
                    settings.setValue(curLan + QString("EM2_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y12:
                    settings.setValue(curLan + QString("EM2_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y13:
                    settings.setValue(curLan + QString("EM2_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y14:
                    settings.setValue(curLan + QString("EM2_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM2_Y15:
                    settings.setValue(curLan + QString("EM2_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;

                case EM3_Y00:
                    settings.setValue(curLan + QString("EM3_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y01:
                    settings.setValue(curLan + QString("EM3_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y02:
                    settings.setValue(curLan + QString("EM3_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y03:
                    settings.setValue(curLan + QString("EM3_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y04:
                    settings.setValue(curLan + QString("EM3_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y05:
                    settings.setValue(curLan + QString("EM3_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y06:
                    settings.setValue(curLan + QString("EM3_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y07:
                    settings.setValue(curLan + QString("EM3_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y08:
                    settings.setValue(curLan + QString("EM3_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y09:
                    settings.setValue(curLan + QString("EM3_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y10:
                    settings.setValue(curLan + QString("EM3_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y11:
                    settings.setValue(curLan + QString("EM3_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y12:
                    settings.setValue(curLan + QString("EM3_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y13:
                    settings.setValue(curLan + QString("EM3_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y14:
                    settings.setValue(curLan + QString("EM3_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM3_Y15:
                    settings.setValue(curLan + QString("EM3_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;

                case EM4_Y00:
                    settings.setValue(curLan + QString("EM4_VAR_Y00"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y01:
                    settings.setValue(curLan + QString("EM4_VAR_Y01"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y02:
                    settings.setValue(curLan + QString("EM4_VAR_Y02"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y03:
                    settings.setValue(curLan + QString("EM4_VAR_Y03"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y04:
                    settings.setValue(curLan + QString("EM4_VAR_Y04"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y05:
                    settings.setValue(curLan + QString("EM4_VAR_Y05"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y06:
                    settings.setValue(curLan + QString("EM4_VAR_Y06"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y07:
                    settings.setValue(curLan + QString("EM4_VAR_Y07"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y08:
                    settings.setValue(curLan + QString("EM4_VAR_Y08"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y09:
                    settings.setValue(curLan + QString("EM4_VAR_Y09"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y10:
                    settings.setValue(curLan + QString("EM4_VAR_Y10"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y11:
                    settings.setValue(curLan + QString("EM4_VAR_Y11"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y12:
                    settings.setValue(curLan + QString("EM4_VAR_Y12"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y13:
                    settings.setValue(curLan + QString("EM4_VAR_Y13"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y14:
                    settings.setValue(curLan + QString("EM4_VAR_Y14"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;
                case EM4_Y15:
                    settings.setValue(curLan + QString("EM4_VAR_Y15"),QString(ui->tableWidget_Out->item(i,2)->text()));
                    break;

                    /*            case IMM_OUT_MAF:
                settings.setValue(curLan + QString("IMM_VAR_OUT_MAF"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_EMC:
                settings.setValue(curLan + QString("IMM_VAR_OUT_EMC"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_EMO:
                settings.setValue(curLan + QString("IMM_VAR_OUT_EMO"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_RBT:
                settings.setValue(curLan + QString("IMM_VAR_OUT_RBT"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_EEB:
                settings.setValue(curLan + QString("IMM_VAR_OUT_EEB"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_EEF:
                settings.setValue(curLan + QString("IMM_VAR_OUT_EEF"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_C1P1:
                settings.setValue(curLan + QString("IMM_VAR_OUT_C1P1"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_C1P2:
                settings.setValue(curLan + QString("IMM_VAR_OUT_C1P2"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_C2P1:
                settings.setValue(curLan + QString("IMM_VAR_OUT_C2P1"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_C2P2:
                settings.setValue(curLan + QString("IMM_VAR_OUT_C2P2"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_HMAF:
                settings.setValue(curLan + QString("IMM_VAR_OUT_HMAF"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case IMM_OUT_HEMC:
                settings.setValue(curLan + QString("IMM_VAR_OUT_HEMC"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;

            case RBT_OUT_PRO_HOR:
                settings.setValue(curLan + QString("RBT_VAR_OUT_PRO_HOR"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_PRO_VER:
                settings.setValue(curLan + QString("RBT_VAR_OUT_PRO_VER"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_ALM_BEEP:
                settings.setValue(curLan + QString("RBT_VAR_OUT_ALM_BEEP"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_ALM_LAMP:
                settings.setValue(curLan + QString("RBT_VAR_OUT_ALM_LAMP"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_LAMP:
                settings.setValue(curLan + QString("RBT_VAR_OUT_LAMP"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_RUN_DES:
                settings.setValue(curLan + QString("RBT_VAR_OUT_RUN_DES"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_RUN_SPEED:
                settings.setValue(curLan + QString("RBT_VAR_OUT_RUN_SPEED"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_PRO_ADV:
                settings.setValue(curLan + QString("RBT_VAR_OUT_PRO_ADV"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_PRO_RET:
                settings.setValue(curLan + QString("RBT_VAR_OUT_PRO_RET"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_RUN_ADV:
                settings.setValue(curLan + QString("RBT_VAR_OUT_RUN_ADV"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_RUN_RET:
                settings.setValue(curLan + QString("RBT_VAR_OUT_RUN_RET"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_OIL:
                settings.setValue(curLan + QString("RBT_VAR_OUT_OIL"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_RUN_HOR:
                settings.setValue(curLan + QString("RBT_VAR_OUT_RUN_HOR"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;
            case RBT_OUT_RUN_VER:
                settings.setValue(curLan + QString("RBT_VAR_OUT_RUN_VER"),QString(ui->tableWidget_Out->item(i,2)->text()));
                break;*/
                }
            }
            else
            {
                switch(i)
                {
                case MAIN_Y00:
                    settings.remove(curLan + QString("MAIN_VAR_Y00"));
                    break;
                case MAIN_Y01:
                    settings.remove(curLan + QString("MAIN_VAR_Y01"));
                    break;
                case MAIN_Y02:
                    settings.remove(curLan + QString("MAIN_VAR_Y02"));
                    break;
                case MAIN_Y03:
                    settings.remove(curLan + QString("MAIN_VAR_Y03"));
                    break;
                case MAIN_Y04:
                    settings.remove(curLan + QString("MAIN_VAR_Y04"));
                    break;
                case MAIN_Y05:
                    settings.remove(curLan + QString("MAIN_VAR_Y05"));
                    break;
                case MAIN_Y06:
                    settings.remove(curLan + QString("MAIN_VAR_Y06"));
                    break;
                case MAIN_Y07:
                    settings.remove(curLan + QString("MAIN_VAR_Y07"));
                    break;
                case MAIN_Y08:
                    settings.remove(curLan + QString("MAIN_VAR_Y08"));
                    break;
                case MAIN_Y09:
                    settings.remove(curLan + QString("MAIN_VAR_Y09"));
                    break;
                case MAIN_Y10:
                    settings.remove(curLan + QString("MAIN_VAR_Y10"));
                    break;
                case MAIN_Y11:
                    settings.remove(curLan + QString("MAIN_VAR_Y11"));
                    break;
                case MAIN_Y12:
                    settings.remove(curLan + QString("MAIN_VAR_Y12"));
                    break;
                case MAIN_Y13:
                    settings.remove(curLan + QString("MAIN_VAR_Y13"));
                    break;
                case MAIN_Y14:
                    settings.remove(curLan + QString("MAIN_VAR_Y14"));
                    break;
                case MAIN_Y15:
                    settings.remove(curLan + QString("MAIN_VAR_Y15"));
                    break;

                case EM1_Y00:
                    settings.remove(curLan + QString("EM1_VAR_Y00"));
                    break;
                case EM1_Y01:
                    settings.remove(curLan + QString("EM1_VAR_Y01"));
                    break;
                case EM1_Y02:
                    settings.remove(curLan + QString("EM1_VAR_Y02"));
                    break;
                case EM1_Y03:
                    settings.remove(curLan + QString("EM1_VAR_Y03"));
                    break;
                case EM1_Y04:
                    settings.remove(curLan + QString("EM1_VAR_Y04"));
                    break;
                case EM1_Y05:
                    settings.remove(curLan + QString("EM1_VAR_Y05"));
                    break;
                case EM1_Y06:
                    settings.remove(curLan + QString("EM1_VAR_Y06"));
                    break;
                case EM1_Y07:
                    settings.remove(curLan + QString("EM1_VAR_Y07"));
                    break;
                case EM1_Y08:
                    settings.remove(curLan + QString("EM1_VAR_Y08"));
                    break;
                case EM1_Y09:
                    settings.remove(curLan + QString("EM1_VAR_Y09"));
                    break;
                case EM1_Y10:
                    settings.remove(curLan + QString("EM1_VAR_Y10"));
                    break;
                case EM1_Y11:
                    settings.remove(curLan + QString("EM1_VAR_Y11"));
                    break;
                case EM1_Y12:
                    settings.remove(curLan + QString("EM1_VAR_Y12"));
                    break;
                case EM1_Y13:
                    settings.remove(curLan + QString("EM1_VAR_Y13"));
                    break;
                case EM1_Y14:
                    settings.remove(curLan + QString("EM1_VAR_Y14"));
                    break;
                case EM1_Y15:
                    settings.remove(curLan + QString("EM1_VAR_Y15"));
                    break;

                case EM2_Y00:
                    settings.remove(curLan + QString("EM2_VAR_Y00"));
                    break;
                case EM2_Y01:
                    settings.remove(curLan + QString("EM2_VAR_Y01"));
                    break;
                case EM2_Y02:
                    settings.remove(curLan + QString("EM2_VAR_Y02"));
                    break;
                case EM2_Y03:
                    settings.remove(curLan + QString("EM2_VAR_Y03"));
                    break;
                case EM2_Y04:
                    settings.remove(curLan + QString("EM2_VAR_Y04"));
                    break;
                case EM2_Y05:
                    settings.remove(curLan + QString("EM2_VAR_Y05"));
                    break;
                case EM2_Y06:
                    settings.remove(curLan + QString("EM2_VAR_Y06"));
                    break;
                case EM2_Y07:
                    settings.remove(curLan + QString("EM2_VAR_Y07"));
                    break;
                case EM2_Y08:
                    settings.remove(curLan + QString("EM2_VAR_Y08"));
                    break;
                case EM2_Y09:
                    settings.remove(curLan + QString("EM2_VAR_Y09"));
                    break;
                case EM2_Y10:
                    settings.remove(curLan + QString("EM2_VAR_Y10"));
                    break;
                case EM2_Y11:
                    settings.remove(curLan + QString("EM2_VAR_Y11"));
                    break;
                case EM2_Y12:
                    settings.remove(curLan + QString("EM2_VAR_Y12"));
                    break;
                case EM2_Y13:
                    settings.remove(curLan + QString("EM2_VAR_Y13"));
                    break;
                case EM2_Y14:
                    settings.remove(curLan + QString("EM2_VAR_Y14"));
                    break;
                case EM2_Y15:
                    settings.remove(curLan + QString("EM2_VAR_Y15"));
                    break;

                case EM3_Y00:
                    settings.remove(curLan + QString("EM3_VAR_Y00"));
                    break;
                case EM3_Y01:
                    settings.remove(curLan + QString("EM3_VAR_Y01"));
                    break;
                case EM3_Y02:
                    settings.remove(curLan + QString("EM3_VAR_Y02"));
                    break;
                case EM3_Y03:
                    settings.remove(curLan + QString("EM3_VAR_Y03"));
                    break;
                case EM3_Y04:
                    settings.remove(curLan + QString("EM3_VAR_Y04"));
                    break;
                case EM3_Y05:
                    settings.remove(curLan + QString("EM3_VAR_Y05"));
                    break;
                case EM3_Y06:
                    settings.remove(curLan + QString("EM3_VAR_Y06"));
                    break;
                case EM3_Y07:
                    settings.remove(curLan + QString("EM3_VAR_Y07"));
                    break;
                case EM3_Y08:
                    settings.remove(curLan + QString("EM3_VAR_Y08"));
                    break;
                case EM3_Y09:
                    settings.remove(curLan + QString("EM3_VAR_Y09"));
                    break;
                case EM3_Y10:
                    settings.remove(curLan + QString("EM3_VAR_Y10"));
                    break;
                case EM3_Y11:
                    settings.remove(curLan + QString("EM3_VAR_Y11"));
                    break;
                case EM3_Y12:
                    settings.remove(curLan + QString("EM3_VAR_Y12"));
                    break;
                case EM3_Y13:
                    settings.remove(curLan + QString("EM3_VAR_Y13"));
                    break;
                case EM3_Y14:
                    settings.remove(curLan + QString("EM3_VAR_Y14"));
                    break;
                case EM3_Y15:
                    settings.remove(curLan + QString("EM3_VAR_Y15"));
                    break;

                case EM4_Y00:
                    settings.remove(curLan + QString("EM4_VAR_Y00"));
                    break;
                case EM4_Y01:
                    settings.remove(curLan + QString("EM4_VAR_Y01"));
                    break;
                case EM4_Y02:
                    settings.remove(curLan + QString("EM4_VAR_Y02"));
                    break;
                case EM4_Y03:
                    settings.remove(curLan + QString("EM4_VAR_Y03"));
                    break;
                case EM4_Y04:
                    settings.remove(curLan + QString("EM4_VAR_Y04"));
                    break;
                case EM4_Y05:
                    settings.remove(curLan + QString("EM4_VAR_Y05"));
                    break;
                case EM4_Y06:
                    settings.remove(curLan + QString("EM4_VAR_Y06"));
                    break;
                case EM4_Y07:
                    settings.remove(curLan + QString("EM4_VAR_Y07"));
                    break;
                case EM4_Y08:
                    settings.remove(curLan + QString("EM4_VAR_Y08"));
                    break;
                case EM4_Y09:
                    settings.remove(curLan + QString("EM4_VAR_Y09"));
                    break;
                case EM4_Y10:
                    settings.remove(curLan + QString("EM4_VAR_Y10"));
                    break;
                case EM4_Y11:
                    settings.remove(curLan + QString("EM4_VAR_Y11"));
                    break;
                case EM4_Y12:
                    settings.remove(curLan + QString("EM4_VAR_Y12"));
                    break;
                case EM4_Y13:
                    settings.remove(curLan + QString("EM4_VAR_Y13"));
                    break;
                case EM4_Y14:
                    settings.remove(curLan + QString("EM4_VAR_Y14"));
                    break;
                case EM4_Y15:
                    settings.remove(curLan + QString("EM4_VAR_Y15"));
                    break;

                    /*            case IMM_OUT_MAF:
                settings.remove(curLan + QString("IMM_VAR_OUT_MAF"));
                break;
            case IMM_OUT_EMC:
                settings.remove(curLan + QString("IMM_VAR_OUT_EMC"));
                break;
            case IMM_OUT_EMO:
                settings.remove(curLan + QString("IMM_VAR_OUT_EMO"));
                break;
            case IMM_OUT_RBT:
                settings.remove(curLan + QString("IMM_VAR_OUT_RBT"));
                break;
            case IMM_OUT_EEB:
                settings.remove(curLan + QString("IMM_VAR_OUT_EEB"));
                break;
            case IMM_OUT_EEF:
                settings.remove(curLan + QString("IMM_VAR_OUT_EEF"));
                break;
            case IMM_OUT_C1P1:
                settings.remove(curLan + QString("IMM_VAR_OUT_C1P1"));
                break;
            case IMM_OUT_C1P2:
                settings.remove(curLan + QString("IMM_VAR_OUT_C1P2"));
                break;
            case IMM_OUT_C2P1:
                settings.remove(curLan + QString("IMM_VAR_OUT_C2P1"));
                break;
            case IMM_OUT_C2P2:
                settings.remove(curLan + QString("IMM_VAR_OUT_C2P2"));
                break;
            case IMM_OUT_HMAF:
                settings.remove(curLan + QString("IMM_VAR_OUT_HMAF"));
                break;
            case IMM_OUT_HEMC:
                settings.remove(curLan + QString("IMM_VAR_OUT_HEMC"));
                break;

            case RBT_OUT_PRO_HOR:
                settings.remove(curLan + QString("RBT_VAR_OUT_PRO_HOR"));
                break;
            case RBT_OUT_PRO_VER:
                settings.remove(curLan + QString("RBT_VAR_OUT_PRO_VER"));
                break;
            case RBT_OUT_ALM_BEEP:
                settings.remove(curLan + QString("RBT_VAR_OUT_ALM_BEEP"));
                break;
            case RBT_OUT_ALM_LAMP:
                settings.remove(curLan + QString("RBT_VAR_OUT_ALM_LAMP"));
                break;
            case RBT_OUT_LAMP:
                settings.remove(curLan + QString("RBT_VAR_OUT_LAMP"));
                break;
            case RBT_OUT_RUN_DES:
                settings.remove(curLan + QString("RBT_VAR_OUT_RUN_DES"));
                break;
            case RBT_OUT_RUN_SPEED:
                settings.remove(curLan + QString("RBT_VAR_OUT_RUN_SPEED"));
                break;
            case RBT_OUT_PRO_ADV:
                settings.remove(curLan + QString("RBT_VAR_OUT_PRO_ADV"));
                break;
            case RBT_OUT_PRO_RET:
                settings.remove(curLan + QString("RBT_VAR_OUT_PRO_RET"));
                break;
            case RBT_OUT_RUN_ADV:
                settings.remove(curLan + QString("RBT_VAR_OUT_RUN_ADV"));
                break;
            case RBT_OUT_RUN_RET:
                settings.remove(curLan + QString("RBT_VAR_OUT_RUN_RET"));
                break;
            case RBT_OUT_OIL:
                settings.remove(curLan + QString("RBT_VAR_OUT_OIL"));
                break;
            case RBT_OUT_RUN_HOR:
                settings.remove(curLan + QString("RBT_VAR_OUT_RUN_HOR"));
                break;
            case RBT_OUT_RUN_VER:
                settings.remove(curLan + QString("RBT_VAR_OUT_RUN_VER"));
                break;*/
                }
            }
        }
    }


    settings.sync();
#if defined(Q_OS_LINUX)
    sync();
#endif
    QFile fileDes(QDir::currentPath() + QString("/"XPAD_IO_NAME));
    if (fileDes.exists() == false)
    {
        ui->BtnCancel->setEnabled(true);
    }
    else
    {
        // 更新界面端口名称
        ui->label->setText(tr("端口名称修改成功!"));
        xLan->SetLanguage(lan);
        ui->BtnCancel->setEnabled(true);
    }

}

