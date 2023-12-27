#include "form.h"
#include "ui_form.h"
#include "dialogkeyboard.h"
#include "dialogportedit.h"
#include "ui_dialogportedit.h"
#include "xconfig.h"
#include <QSettings>
#include "qdebug.h"
#include "cmbprotocol.h"
#include "xioport.h"
#include "xtranslator.h"
#include "servoalias.h"
#include<iostream>
Form::Form(QWidget *parent) : QWidget(parent), ui(  new Ui::Form)
{
    ui->setupUi(this);

#if defined(Q_WS_QWS)
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground, true);
#endif
//    //设置行宽行高
//    quint8 i;
//    for(i = 0;i <6;i++)
//    {
//        ui->tableWidget_in->setRowHeight(i,50);
//    }
//    ui->tableWidget_in->setColumnWidth(0,210);
//    ui->tableWidget_in->setColumnWidth(1,260);

}
Form::~Form()
{
    delete ui;
}



//显示键盘
void Form::on_tableWidget_in_cellClicked(int row, int column)
{

    QString name;
    if((column == 1 ) && (row < MAX_INPORT_NUM))
    {
        // 输入端口名称
        if (xKbd->DoForm(name, KEYBOARD_TYPE_STR) != QDialog::Accepted)
            return;
        ui->tableWidget_in->setItem(row,column,new QTableWidgetItem(name));
    }
}

//默认轴初始化
void Form::InitInShaftName()
{
    //初始化轴默认名称
    ui->tableWidget_in->setItem(AXIS_NAME_X,0,new QTableWidgetItem(GetServoName(AXIS_IDX_PHOR,true)));
    ui->tableWidget_in->setItem(AXIS_NAME_Y,0,new QTableWidgetItem(GetServoName(AXIS_IDX_PVER,true)));
    ui->tableWidget_in->setItem(AXIS_NAME_Z,0,new QTableWidgetItem(GetServoName(AXIS_IDX_TRV,true)));
    ui->tableWidget_in->setItem(AXIS_NAME_A,0,new QTableWidgetItem(GetServoName(AXIS_IDX_RVER,true)));
    ui->tableWidget_in->setItem(AXIS_NAME_B,0,new QTableWidgetItem(GetServoName(AXIS_IDX_RHOR,true)));
    ui->tableWidget_in->setItem(AXIS_NAME_C,0,new QTableWidgetItem(GetServoName(AXIS_IDX_EXT,true)));

//    //读取配置文件获取轴已修改名称
//    quint8 lan = CMBProtocol::GetLanguage();
//    QString curLan;
//    curLan.clear();
//    switch (lan)
//    {
//    case LAN_ENGLISH:
//        curLan.append("english");
//        break;
//    default:
//        curLan.append("chineses");
//        break;
//    }
    QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
    settings.beginGroup("chineses");
    ui->tableWidget_in->setItem(AXIS_NAME_X,1,new QTableWidgetItem((settings.value("AXIS_NAME_X").toString())));
    ui->tableWidget_in->setItem(AXIS_NAME_Y,1,new QTableWidgetItem((settings.value("AXIS_NAME_Y").toString())));
    ui->tableWidget_in->setItem(AXIS_NAME_Z,1,new QTableWidgetItem((settings.value("AXIS_NAME_Z").toString())));
    ui->tableWidget_in->setItem(AXIS_NAME_A,1,new QTableWidgetItem((settings.value("AXIS_NAME_A").toString())));
    ui->tableWidget_in->setItem(AXIS_NAME_B,1,new QTableWidgetItem((settings.value("AXIS_NAME_B").toString())));
    ui->tableWidget_in->setItem(AXIS_NAME_C,1,new QTableWidgetItem((settings.value("AXIS_NAME_C").toString())));
}
void Form::NewPortFileq(){
        //输入修改名称

        QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
        ui->BtnCancel->setEnabled(false);
        quint8 i;
        quint8 lan = CMBProtocol::GetLanguage();
        QString curLan;
        curLan.append("chineses/");
//        curLan.clear();
//        switch (lan)
//        {
//        case LAN_ENGLISH:
//            curLan.append("english/");
//            break;
//        default:
//            curLan.append("chineses/");
//            break;
//        }
        //输入修改名称
        for(i = 0; i < MAX_AXIS_NUM; i++)
        {

            if(ui->tableWidget_in->item(i,1)->text() != tr(""))
            {

                switch(i)
                {
                case AXIS_NAME_X:
                    settings.setValue(curLan + QString("AXIS_NAME_X"),QString(ui->tableWidget_in->item(i,1)->text()));
                    break;
                case AXIS_NAME_Y:
                    settings.setValue(curLan + QString("AXIS_NAME_Y"),QString(ui->tableWidget_in->item(i,1)->text()));
                    break;
                case AXIS_NAME_Z:
                    settings.setValue(curLan + QString("AXIS_NAME_Z"),QString(ui->tableWidget_in->item(i,1)->text()));
                    break;
                case AXIS_NAME_A:
                    settings.setValue(curLan + QString("AXIS_NAME_A"),QString(ui->tableWidget_in->item(i,1)->text()));
                    break;
                case AXIS_NAME_B:
                    settings.setValue(curLan + QString("AXIS_NAME_B"),QString(ui->tableWidget_in->item(i,1)->text()));
                    break;
                case AXIS_NAME_C:
                    settings.setValue(curLan + QString("AXIS_NAME_C"),QString(ui->tableWidget_in->item(i,1)->text()));
                    break;

               }
            }
            else
            {

                switch(i)
                {
                case AXIS_NAME_X:
                    settings.remove(curLan + QString("AXIS_NAME_X"));
                    break;
                case AXIS_NAME_Y:
                    settings.remove(curLan + QString("AXIS_NAME_Y"));
                    break;
                case AXIS_NAME_Z:
                    settings.remove(curLan + QString("AXIS_NAME_Z"));
                    break;
                case AXIS_NAME_A:
                    settings.remove(curLan + QString("AXIS_NAME_A"));
                    break;
                case AXIS_NAME_B:
                    settings.remove(curLan + QString("AXIS_NAME_B"));
                    break;
                case AXIS_NAME_C:
                    settings.remove(curLan + QString("AXIS_NAME_C"));
                    break;
                }
            }      
        }
        settings.sync();
        ui->label->setText(tr("端口名称修改成功!"));
        xLan->SetLanguage(lan);
        ui->BtnCancel->setEnabled(true);
}


