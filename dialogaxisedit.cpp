#include "dialogaxisedit.h"
#include "ui_dialogaxisedit.h"
#include "xconfig.h"
#include <QSettings>
#include "qdebug.h"
#include "cmbprotocol.h"
#include "xioport.h"
#include "xtranslator.h"
#include "servoalias.h"

DialogAxisEdit::DialogAxisEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAxisEdit)
{
    ui->setupUi(this);
    // 设置对话框显示效果
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint);//setWindowFlags(Qt::FramelessWindowHint);

    retranslateUI();
    ui->tableWidget ->setRowCount(MAX_AXIS_NUM);
    ui->tableWidget ->setColumnCount(2);
    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        for(int col = 0; col < ui->tableWidget->columnCount(); col++)
        {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(""));
        }
        ui->tableWidget->setRowHeight(row,50);
        ui->tableWidget->item(row,0)->setFlags(Qt::ItemIsSelectable);
    }
    ui->tableWidget->setColumnWidth(0,250);
    ui->tableWidget->setColumnWidth(1,250);

    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(tableWidgeCellClicked(int,int)));

}

DialogAxisEdit::~DialogAxisEdit()
{
    delete ui;
}

int DialogAxisEdit::DoForm()
{
    quint8 i;
    InitInAxisName();
    ui->label->setText("");
    //设置默认名称不能修改
    for(i = 0; i < MAX_AXIS_NUM; i++)
    {
        ui->tableWidget->item(i,0)->setFlags(Qt::ItemIsEnabled);
    }
    return exec();
}

void DialogAxisEdit::InitInAxisName()
{
    //初始化轴默认名称
    ui->tableWidget->item(AXIS_NAME_X,0)->setText(GetServoName(AXIS_NAME_X,true));
    ui->tableWidget->item(AXIS_NAME_Y,0)->setText(GetServoName(AXIS_NAME_Y,true));
    ui->tableWidget->item(AXIS_NAME_Z,0)->setText(GetServoName(AXIS_NAME_Z,true));
    ui->tableWidget->item(AXIS_NAME_A,0)->setText(GetServoName(AXIS_NAME_A,true));
    ui->tableWidget->item(AXIS_NAME_B,0)->setText(GetServoName(AXIS_NAME_B,true));
    ui->tableWidget->item(AXIS_NAME_C,0)->setText(GetServoName(AXIS_NAME_C,true));

    QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
    settings.beginGroup("chineses");
    ui->tableWidget->item(AXIS_NAME_X,1)->setText((settings.value("AXIS_NAME_X").toString()));
    ui->tableWidget->item(AXIS_NAME_Y,1)->setText((settings.value("AXIS_NAME_Y").toString()));
    ui->tableWidget->item(AXIS_NAME_Z,1)->setText((settings.value("AXIS_NAME_Z").toString()));
    ui->tableWidget->item(AXIS_NAME_A,1)->setText((settings.value("AXIS_NAME_A").toString()));
    ui->tableWidget->item(AXIS_NAME_B,1)->setText((settings.value("AXIS_NAME_B").toString()));
    ui->tableWidget->item(AXIS_NAME_C,1)->setText((settings.value("AXIS_NAME_C").toString()));
    settings.endGroup();
}

void DialogAxisEdit::tableWidgeCellClicked(int row, int column)
{
    QString name;
    if((column == 1 ) && (row < MAX_AXIS_NUM))
    {
        // 输入单臂名称
        if (xKbd->DoForm(name, KEYBOARD_TYPE_STR) != QDialog::Accepted)
            return;
        ui->tableWidget->item(row,column)->setText(name);
    }
}


void DialogAxisEdit::NewPortFile(void)
{
    QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
    ui->BtnCancel->setEnabled(false);
    quint8 i;
    quint8 lan = CMBProtocol::GetLanguage();
    QString curLan;
    curLan.append("chineses/");
    for(i = 0; i < MAX_AXIS_NUM; i++)
    {
        if(ui->tableWidget->item(i,1)->text() != tr(""))
        {
            switch(i)
            {
            case AXIS_NAME_X:
                settings.setValue(curLan + QString("AXIS_NAME_X"),QString(ui->tableWidget->item(i,1)->text()));
                break;
            case AXIS_NAME_Y:
                settings.setValue(curLan + QString("AXIS_NAME_Y"),QString(ui->tableWidget->item(i,1)->text()));
                break;
            case AXIS_NAME_Z:
                settings.setValue(curLan + QString("AXIS_NAME_Z"),QString(ui->tableWidget->item(i,1)->text()));
                break;
            case AXIS_NAME_A:
                settings.setValue(curLan + QString("AXIS_NAME_A"),QString(ui->tableWidget->item(i,1)->text()));
                break;
            case AXIS_NAME_B:
                settings.setValue(curLan + QString("AXIS_NAME_B"),QString(ui->tableWidget->item(i,1)->text()));
                break;
            case AXIS_NAME_C:
                settings.setValue(curLan + QString("AXIS_NAME_C"),QString(ui->tableWidget->item(i,1)->text()));
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
    // 更新界面轴名称
    ui->label->setText(tr("轴名称修改成功!"));
    xLan->SetLanguage(lan);
    ui->BtnCancel->setEnabled(true);
}

void DialogAxisEdit::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        retranslateUI();
        break;
    default:
        break;
    }
}

void DialogAxisEdit::retranslateUI()
{
    setWindowTitle(tr("编辑轴名称"));
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("默认名称") << tr("修改名称"));
}
