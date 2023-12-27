#include <stdio.h>
#include "cmbprotocol.h"
#include "xsystemlog.h"
#include "xpermissions.h"
#include "xstringresource.h"
#include "xmessagebox.h"
#include "dialogoption.h"
#include "driver/xioport.h"
#include "formeditoption.h"
#include "ui_formeditoption.h"

FormEditOption::FormEditOption(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormEditOption), pgmModel(true)
{
	ui->setupUi(this);
	pModbus = modbus;
	// 设置数据源
	ui->tablePgm->setModel(&pgmModel);
	ui->tablePgm->setColumnWidth(0, 50);
    ui->tablePgm->setColumnWidth(1, 30);
    ui->tablePgm->setColumnWidth(2, 285);
    ui->tablePgm->setColumnWidth(3, 20);

    ui->tableWidgetOpt->setColumnWidth(0, 30);
    ui->tableWidgetOpt->setColumnWidth(1, 165);
    ui->tableWidgetOpt->setColumnWidth(2, 165);
    // 安装事件过滤器
	QObjectList list = ui->tablePgm->children();
	for (int i = 0; i < list.count(); i ++)
	{
		if (list.at(i)->objectName() == QString("qt_scrollarea_viewport"))
		{
			list.at(i)->installEventFilter(this);
		}
	}
}

FormEditOption::~FormEditOption()
{
	delete ui;
}

bool FormEditOption::EnterForm(void)
{
    int i;
    if (pModbus->IsALFAMode())
    {
        xMessageBox::DoWarning(tr("系统警告"), tr("系统为简易模式，不能进入！"));
        return false;
    }
	// 如果没有载入程序文件则警告并退出
	if (pModbus->GetCurPgmName().isEmpty())
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("没有载入程序文件，不能进入！"));
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
	if (pgmModel.CheckProgram() == false)
	{
		xMessageBox::DoWarning(tr("检查程序"), pgmModel.GetErrString()+tr(",\n请进入教导画面修改程序！"));
		return false;
	}
	// 生成程序文件对应的机器代码并上传到主控模块
    /*quint32 codeCnt;
	quint8 codes[MAX_CODES];
	quint32 paras[MAX_CODES];
	LoopParameter loop;
	PaperParameter paper;
	// 生成程序文件机器代码
	codeCnt = pgmModel.GenerateCode(codes, paras, &loop, &paper);
	// 上传机器代码
	if (pModbus->WriteCodes(codes, 0, codeCnt) != SENDMSG_RET_ACK)
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件指令到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
		return false;
	}
	// 上传机器代码参数
	if (pModbus->WriteCodeParas(paras, 0, codeCnt) != SENDMSG_RET_ACK)
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
		return false;
	}
	// 上传机器代码循环定位区参数
	for (quint8 i = 0; i < loop.count; i ++)
	{
		if (loop.type[i] == LOOP_MODE_MATRIX)
		{
			if (pModbus->WriteLoopsMatrix(i, loop.loop[i].m_matrix) != SENDMSG_RET_ACK)
			{
				xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件正臂矩阵参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
				return false;
			}
		}
		else
		{
			if (pModbus->WriteLoopsFree(i, loop.loop[i].m_free) != SENDMSG_RET_ACK)
			{
				xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件正臂循环定位参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
				return false;
			}
		}
	}
	// 上传机器代码取纸参数
	if (pModbus->WritePaper(paper) != SENDMSG_RET_ACK)
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("上传程序文件取纸参数到主控模块出错，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
		return false;
	}
	// 更新主控模块当前程序
	if (pModbus->CommandUpdate(CMD_UPDATE_CODE | CMD_UPDATE_CODEPARA | CMD_UPDATE_PAPER | CMD_UPDATE_LOOP) != SENDMSG_RET_ACK)
	{
		xMessageBox::DoWarning(tr("系统警告"), tr("主控模块更新当前程序失败，不能进行程序运行操作！\n请检查操作器和主控模块的通讯链路。"));
		return false;
    }*/
    m_IsItemChanged = false;
    ui->tableWidgetOpt->setRowCount(0);
    for (i=0; i<pgmModel.GetItemCountOpt(); i++)
    {
        QTableWidgetItem *item;
        ui->tableWidgetOpt->insertRow(i);
        item = new QTableWidgetItem(QString::number(i+1));
        item->setFlags(item->flags()^Qt::ItemIsEditable);
        ui->tableWidgetOpt->setItem(i, 0, item);
        item = new QTableWidgetItem(pgmModel.GetItemOpt(i)->GetNameEn());
        ui->tableWidgetOpt->setItem(i, 1, item);
        item = new QTableWidgetItem(pgmModel.GetItemOpt(i)->GetNameDis());
        ui->tableWidgetOpt->setItem(i, 2, item);
    }
    ui->tableWidgetOpt->selectRow(0);
    pgmModel.SetCurrentOpt(0);
    m_IsItemChanged = true;
//    show();
	return true;
}

bool FormEditOption::ExitForm(void)
{
    if (pgmModel.IsModified())
    {
        quint8 ret = xMessageBox::DoSaveTip(tr("系统提示"), tr("当前选项已经修改，是否写入程序文件？\n点击[保存]将会写入程序文件并退出；\n点击[不保存]将会放弃当前程序修改并退出；\n点击[取消]将会放弃退出操作继续选项编辑。"));
        if (ret == XMSG_RET_SAVE)
        {
            pgmModel.SaveProgram(pModbus->GetCurPgmName(true));
        }
        else if (ret != XMSG_RET_NOSAVE)
            return false;
    }
//    hide();
	return true;
}
// 插入指令配置
void FormEditOption::InsertOption()
{
	DialogOption option;
    if (option.exec() == QDialog::Accepted)
    {
        if (option.GetNameEn().isEmpty()||option.GetNameDis().isEmpty())
        {
            xMessageBox::DoInformation(tr("系统提示"), tr("选项名不能为空！"));
            return;
        }
        XmlModelItemOption * opt = new XmlModelItemOption();
        opt->SetNameEn(option.GetNameEn());
        opt->SetNameDis(option.GetNameDis());
        pgmModel.InsertOpt(opt);

        m_IsItemChanged = false;
        QTableWidgetItem *item;
        int rows = ui->tableWidgetOpt->rowCount();
        ui->tableWidgetOpt->insertRow(rows);
        item = new QTableWidgetItem(QString::number(rows+1));
        item->setFlags(item->flags()^Qt::ItemIsEditable);
        ui->tableWidgetOpt->setItem(rows, 0, item);
        item = new QTableWidgetItem(option.GetNameEn());
        ui->tableWidgetOpt->setItem(rows, 1, item);
        item = new QTableWidgetItem(option.GetNameDis());
        ui->tableWidgetOpt->setItem(rows, 2, item);
        m_IsItemChanged = true;
        ui->tableWidgetOpt->selectRow(rows);
        ui->tableWidgetOpt->scrollTo(ui->tableWidgetOpt->currentIndex());
    }
}
// 删除指令配置
void FormEditOption::RemoveOption()
{
    quint8 ret = xMessageBox::DoQuestion(tr("系统提示"), tr("确定删除此条选项？"));
    if (ret == XMSG_RET_YES)
    {
        int pos = ui->tableWidgetOpt->currentIndex().row();
        if (pos>=0)
        {
            int i;
            pgmModel.RemoveOpt(pos);
            ui->tableWidgetOpt->setRowCount(0);
            for (i=0; i<pgmModel.GetItemCountOpt(); i++)
            {
                QTableWidgetItem *item;
                ui->tableWidgetOpt->insertRow(i);
                item = new QTableWidgetItem(QString::number(i+1));
                ui->tableWidgetOpt->setItem(i, 0, item);
                item = new QTableWidgetItem(pgmModel.GetItemOpt(i)->GetNameEn());
                ui->tableWidgetOpt->setItem(i, 1, item);
                item = new QTableWidgetItem(pgmModel.GetItemOpt(i)->GetNameEn());
                ui->tableWidgetOpt->setItem(i, 2, item);
            }
        }
    }
}

void FormEditOption::on_BtnSave_clicked()
{
    if (pgmModel.IsModified())
        pgmModel.SaveProgram(pModbus->GetCurPgmName(true));
}

void FormEditOption::selectionChanged()
{
    pgmModel.SetCurrentOpt(ui->tableWidgetOpt->currentIndex().row());
}

void FormEditOption::itemChanged(QTableWidgetItem * item)
{
    if (m_IsItemChanged)
    {
        if (item->data(Qt::DisplayRole).toString().isEmpty())
        {
            xMessageBox::DoInformation(tr("系统提示"), tr("选项名不能为空！"));
            if (item->column()==1)
                item->setData(Qt::DisplayRole, pgmModel.GetItemOpt(item->row())->GetNameEn());
            if (item->column()==2)
                item->setData(Qt::DisplayRole, pgmModel.GetItemOpt(item->row())->GetNameDis());

            return;
        }
        if (item->column()==1)
            pgmModel.SetOptNameEn(item->row(), item->data(Qt::DisplayRole).toString());
        if (item->column()==2)
            pgmModel.SetOptNameDis(item->row(), item->data(Qt::DisplayRole).toString());
        //qDebug() << item->row() <<;
    }
}
