#include <QDesktopWidget>
#include <QEvent>
#include <QMovie>
#include <QtCore/QTimer>
#include <QDebug>
#include "ui_xmessagebox.h"
#include "servoalias.h"
#include "cmbprotocol.h"
#include "modbusaddr.h"
#include "xmessagebox.h"

#define XMSG_TIMEOUT		30



xMessageBox* xMessageBox::pmsgdlg = NULL;
quint16 xMessageBox::home[HOME_DEF_MAX];
CMBProtocol *xMessageBox::pModbus;

xMessageBox::xMessageBox(QWidget *parent) :	QDialog(parent), ui(new Ui::xMessageBox)
{
	ui->setupUi(this);
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
	// 构造影片对象
	pMovie = new QMovie(":/img/animation/Loading.gif");
	// 构造定时器
	pTimer = new QTimer(this);
	connect(pTimer, SIGNAL(timeout()), this, SLOT(PeriodCount()));
	TimeCount = 0;
	// 初始化 Modbus 对象
    pmsgdlg = this;
}

xMessageBox::~xMessageBox()
{
    pmsgdlg = NULL;
	delete ui;
	delete pMovie;
	delete pTimer;
}

void xMessageBox::resizeEvent(QResizeEvent *event)
{
	QDialog::resizeEvent(event);
	QRect screenRect = QApplication::desktop()->geometry();
	move((screenRect.width() - width()) / 2, (screenRect.height() - height()) / 2);
}

qint32 xMessageBox::RunMsg(xMessageBox *pDlg)
{
	quint32 ret;
//	ShowCount ++;
	ret = pDlg->exec();
//	ShowCount --;
	return ret;
}

// 运行等待消息框
qint32 xMessageBox::DoWaiting(const QString &title, const QString &msg)
{
    if (pmsgdlg != 0)
		return XMSG_HAS_SHOWED;
	xMessageBox dlg;
	dlg.MsgType = XMSG_TYP_WAIT;
	// 显示等待信息不需要显示功能按钮
	dlg.ui->BtnF1->setVisible(false);
	dlg.ui->BtnF2->setVisible(false);
	dlg.ui->BtnF3->setVisible(false);
	dlg.ui->frameMainArea->layout()->removeItem(dlg.ui->horizontalLayoutBtns);
	// 设置标题栏
	dlg.ui->labelTitle->setText(title);
	// 设置等待动画
	dlg.ui->labelImage->setMovie(dlg.pMovie);
	dlg.pMovie->start();
	// 设置要显示的信息
	dlg.ui->labelMessage->setText(msg);
	// 启动延时定时器
	dlg.pTimer->start(1000);
	// 运行对话框
	return  RunMsg(&dlg);
}
// 运行原点等待消息框
qint32 xMessageBox::DoHomeWaiting(const QString &title)
{
    if (pmsgdlg != 0)
		return XMSG_HAS_SHOWED;
	xMessageBox dlg;
	dlg.MsgType = XMSG_TYP_HOME;
	// 显示等待信息不需要显示功能按钮
	dlg.ui->BtnF1->setVisible(false);
	dlg.ui->BtnF2->setVisible(false);
	dlg.ui->BtnF3->setVisible(false);
	dlg.ui->frameMainArea->layout()->removeItem(dlg.ui->horizontalLayoutBtns);
	// 设置标题栏
	dlg.ui->labelTitle->setText(title);
	// 设置等待动画
	dlg.ui->labelImage->setMovie(dlg.pMovie);
	dlg.pMovie->start();
	// 设置 Modbus 对象
    CMBProtocol::GetHome(home);  //得到原点复归序列
	dlg.ui->labelMessage->setText(TransHome(home[0]));
	// 启动延时定时器
	dlg.pTimer->start(500);
	// 运行对话框
	return  RunMsg(&dlg);
}
// 运行通知消息框
qint32 xMessageBox::DoInformation(const QString &title, const QString &msg)
{
    if (pmsgdlg != 0)
		return XMSG_HAS_SHOWED;
	xMessageBox dlg;
	dlg.MsgType = XMSG_TYP_INF;
	// 显示提示信息不需要显示F1和F2功能按钮,F3功能键为"确定"键
	dlg.ui->BtnF1->setVisible(false);
	dlg.ui->BtnF2->setVisible(false);
    dlg.ui->BtnF3->setIcon(QIcon(":/img/32X32/OK.png"));
    dlg.ui->BtnF3->setText(tr("确定"));
	// 设置标题栏
	dlg.ui->labelTitle->setText(title);
	// 设置图标
	dlg.ui->labelImage->setPixmap(QPixmap(":/img/48X48/Information.png"));
	// 设置要显示的信息
	dlg.ui->labelMessage->setText(msg);
	// 启动延时定时器
	dlg.pTimer->start(1000);
	// 运行对话框
	return  RunMsg(&dlg);
}
// 运行一般询问消息框
qint32 xMessageBox::DoAdjQuestion(const QString &title, const QString &msg)
{
    if (pmsgdlg != 0)
        return XMSG_HAS_SHOWED;
    xMessageBox dlg;
    dlg.MsgType = XMSG_TYP_ASK;
    dlg.ui->frameTitle->setStyleSheet(QString("QFrame#frameTitle {"\
                                              "background-color: transparent;"\
                                              "border-image: url(:/img/widget/DialogTitleRed.png) 0 12 0 12;"\
                                              "border-left: 12px transparent;"\
                                              "border-right: 12px transparent; }"));
    // 显示等待信息不需要显示F1功能按钮,F2为"否"键,F3为"是"键
    dlg.ui->BtnF1->setVisible(false);
    dlg.ui->BtnF2->setIcon(QIcon(":/img/32X32/Cancel.png"));
    dlg.ui->BtnF3->setIcon(QIcon(":/img/32X32/OK.png"));
    dlg.ui->BtnF2->setText(tr("取消"));
    dlg.ui->BtnF3->setText(tr("确定"));
    // 设置标题栏
    dlg.ui->labelTitle->setText(title);
    // 设置图标
    dlg.ui->labelImage->setPixmap(QPixmap(":/img/48X48/Warning.png"));
    // 设置要显示的信息
    dlg.ui->labelMessage->setText(msg);
    // 启动延时定时器
    dlg.pTimer->start(1000);
    // 运行对话框
    return  RunMsg(&dlg);
}
// 运行警告消息框
qint32 xMessageBox::DoWarning(const QString &title, const QString &msg)
{
    if (pmsgdlg != 0)
		return XMSG_HAS_SHOWED;
	xMessageBox dlg;
	dlg.MsgType = XMSG_TYP_WAR;
	// 显示警告信息不需要显示F1和F2功能按钮,F3功能键为"确定"键
	dlg.ui->BtnF1->setVisible(false);
	dlg.ui->BtnF2->setVisible(false);
    dlg.ui->BtnF3->setIcon(QIcon(":/img/32X32/OK.png"));
    dlg.ui->BtnF3->setText(tr("确定"));
    // 设置标题栏
	dlg.ui->labelTitle->setText(title);
	// 设置图标
	dlg.ui->labelImage->setPixmap(QPixmap(":/img/48X48/Warning.png"));
	// 设置要显示的信息
	dlg.ui->labelMessage->setText(msg);
	// 启动延时定时器
	dlg.pTimer->start(1000);
	// 运行对话框
	return  RunMsg(&dlg);
}
qint32 xMessageBox::DoIMM_OUT(CMBProtocol *modbus,const QString &title, const QString &msg)
{
    if (pmsgdlg != 0)
        return XMSG_HAS_SHOWED;
    xMessageBox dlg;
    // 设置 Modbus 对象
    pModbus = modbus;
    dlg.MsgType = XMSG_TYP_OUTIMM;
    // 显示警告信息不需要显示F1和F2功能按钮,F3功能键为"确定"键
    dlg.ui->BtnF1->setVisible(false);
    dlg.ui->BtnF2->setIcon(QIcon(":/img/32X32/Cancel.png"));
    dlg.ui->BtnF2->setText(tr("关闭"));
    dlg.ui->BtnF3->setIcon(QIcon(":/img/32X32/OK.png"));
    dlg.ui->BtnF3->setText(tr("打开"));
    // 设置标题栏
    dlg.ui->labelTitle->setText(title);
    // 设置图标
    dlg.ui->labelImage->setPixmap(QPixmap(":/img/48X48/Warning.png"));
    // 设置要显示的信息
    dlg.ui->labelMessage->setText(msg);
    // 运行对话框
    return  RunMsg(&dlg);
}
// 运行一般询问消息框
qint32 xMessageBox::DoQuestion(const QString &title, const QString &msg)
{
    if (pmsgdlg != 0)
		return XMSG_HAS_SHOWED;
	xMessageBox dlg;
	dlg.MsgType = XMSG_TYP_ASK;
	// 显示等待信息不需要显示F1功能按钮,F2为"否"键,F3为"是"键
	dlg.ui->BtnF1->setVisible(false);
    dlg.ui->BtnF2->setIcon(QIcon(":/img/32X32/Cancel.png"));
    dlg.ui->BtnF3->setIcon(QIcon(":/img/32X32/OK.png"));
    dlg.ui->BtnF2->setText(tr("取消"));
    dlg.ui->BtnF3->setText(tr("确定"));
    // 设置标题栏
	dlg.ui->labelTitle->setText(title);
	// 设置图标
	dlg.ui->labelImage->setPixmap(QPixmap(":/img/48X48/Question.png"));
	// 设置要显示的信息
	dlg.ui->labelMessage->setText(msg);
	// 启动延时定时器
	dlg.pTimer->start(1000);
	// 运行对话框
	return  RunMsg(&dlg);
}
// 运行一般询问消息框
qint32 xMessageBox::DoDoorResetQuestion(const QString &title, const QString &msg)
{
    if (pmsgdlg != 0)
    {
        pmsgdlg->pTimer->stop();
        pmsgdlg->done(XMSG_RET_TIMEOUT);
    }
    xMessageBox dlg;
    dlg.MsgType = XMSG_TYP_DOORRESET;
    // 显示等待信息不需要显示F1功能按钮,F2为"否"键,F3为"是"键
    dlg.ui->BtnF1->setVisible(false);
    dlg.ui->BtnF2->setText(tr("继续"));
    dlg.ui->BtnF3->setText(tr("复位"));
    // 设置标题栏
    dlg.ui->labelTitle->setText(title);
    // 设置图标
    dlg.ui->labelImage->setPixmap(QPixmap(":/img/48X48/Question.png"));
    // 设置要显示的信息
    dlg.ui->labelMessage->setText(msg);
    // 启动延时定时器
    dlg.pTimer->start(1000);
    // 运行对话框
    return  RunMsg(&dlg);
}
// 运行保存询问消息框
qint32 xMessageBox::DoSaveTip(const QString &title, const QString &msg)
{
    if (pmsgdlg != 0)
        return XMSG_HAS_SHOWED;
    xMessageBox dlg;
    dlg.MsgType = XMSG_TYP_SAVE;
    // 显示保存提示信息,F1为"取消"键,F2为"不保存退出"键,F3为"保存退出"键
    dlg.ui->BtnF1->setIcon(QIcon(":/img/32X32/Cancel.png"));
    dlg.ui->BtnF2->setIcon(QIcon(":/img/32X32/NoSave.png"));
    dlg.ui->BtnF3->setIcon(QIcon(":/img/32X32/Save.png"));
    dlg.ui->BtnF1->setText(tr("取消"));
    dlg.ui->BtnF2->setText(tr("不保存"));
    dlg.ui->BtnF3->setText(tr("保存"));
    // 设置标题栏
    dlg.ui->labelTitle->setText(title);
    // 设置图标
    dlg.ui->labelImage->setPixmap(QPixmap(":/img/48X48/Question.png"));
    // 设置要显示的信息
    dlg.ui->labelMessage->setText(msg);
    // 启动延时定时器
    dlg.pTimer->start(1000);
    // 运行对话框
    return  RunMsg(&dlg);
}
// 金博跃保存按钮询问
qint32 xMessageBox::DoJBYSaveQuestion(const QString &title, const QString &msg)
{
    if (pmsgdlg != 0)
        return XMSG_HAS_SHOWED;
    xMessageBox dlg;
    dlg.MsgType = XMSG_TYP_SAVE;
    // 显示保存提示信息,F2为"保存不覆盖"键,F3为"保存覆盖"键
    dlg.ui->BtnF1->setIcon(QIcon(":/img/32X32/Cancel.png"));
    dlg.ui->BtnF2->setIcon(QIcon(":/img/32X32/NoSave.png"));
    dlg.ui->BtnF3->setIcon(QIcon(":/img/32X32/Save.png"));
    dlg.ui->BtnF1->setVisible(false);
    dlg.ui->BtnF2->setText(tr("不覆盖"));
    dlg.ui->BtnF3->setText(tr("覆盖"));
    // 设置标题栏
    dlg.ui->labelTitle->setText(title);
    // 设置图标
    dlg.ui->labelImage->setPixmap(QPixmap(":/img/48X48/Question.png"));
    // 设置要显示的信息
    dlg.ui->labelMessage->setText(msg);
    // 启动延时定时器
    dlg.pTimer->start(1000);
    // 运行对话框
    return  RunMsg(&dlg);
}

void xMessageBox::ForceQuit()
{
    if (pmsgdlg)
    {
        pmsgdlg->done(XMSG_RET_CANCEL);
        pmsgdlg = NULL;
    }
}
// *** 定义信号槽 ***
// F1 键槽
void xMessageBox::BtnF1Clicked(void)
{
	if (MsgType == XMSG_TYP_SAVE)
	{
		done(XMSG_RET_CANCEL);
	}
}
// F2 键槽
void xMessageBox::BtnF2Clicked(void)
{
	if (MsgType == XMSG_TYP_ASK)
	{
		done(XMSG_RET_NO);
	}
	else if (MsgType == XMSG_TYP_SAVE)
	{
		done(XMSG_RET_NOSAVE);
	}
    else if (MsgType == XMSG_TYP_DOORRESET)
    {
        done(XMSG_RET_NO);
    }
    else if(MsgType == XMSG_TYP_OUTIMM)
    {
        if(pModbus)
            pModbus->CommandIMMOut(false);
        done(XMSG_RET_CANCEL);
    }
}
// F3 键槽
void xMessageBox::BtnF3Clicked(void)
{
	if (MsgType == XMSG_TYP_INF)
	{
		done(XMSG_RET_YES);
	}
	else if (MsgType == XMSG_TYP_WAR)
	{
		done(XMSG_RET_YES);
	}
	else if (MsgType == XMSG_TYP_ASK)
	{
		done(XMSG_RET_YES);
	}
	else if (MsgType == XMSG_TYP_SAVE)
	{
		done(XMSG_RET_SAVE);
	}
    else if (MsgType == XMSG_TYP_DOORRESET)
    {
        done(XMSG_RET_YES);
    }
    else if(MsgType == XMSG_TYP_OUTIMM)
    {
        if(pModbus)
            pModbus->CommandIMMOut(true);
    }
}
// 定时器槽
void xMessageBox::PeriodCount(void)
{
	if (MsgType == XMSG_TYP_WAIT)
	{
#if SELECT_SWITCH_USE
        CMBProtocol::ReadRunState();
#endif
        if (CMBProtocol::GetRunState() == RUN_STATE_PAUSE)
		{
			pMovie->stop();
			pTimer->stop();
			done(XMSG_RET_WAITFINISH);
		}
	}
	// 原点复归
	else if (MsgType == XMSG_TYP_HOME)
	{
		int pc;
        pc = CMBProtocol::GetPgmPc(); // 得到当前运行指令标号
		if (pc<8)
		{
			//qDebug() << TransHome(home[pc]);
			ui->labelMessage->setText(TransHome(home[pc]));
		}
        if (CMBProtocol::GetRunState() == RUN_STATE_PAUSE)
		{
			pMovie->stop();
			pTimer->stop();
			done(XMSG_RET_WAITFINISH);
		}
	}
    else if (MsgType == XMSG_TYP_DOORRESET)
    {

        if ((CMBProtocol::GetSysState() != SYS_STATE_AUTO)||(CMBProtocol::GetRunState() != RUN_STATE_PAUSE))
        {
            pTimer->stop();
            done(XMSG_RET_WAITFINISH);
        }
    }
	else
	{
		TimeCount ++;
		if (TimeCount >= XMSG_TIMEOUT)
		{
			pTimer->stop();
			done(XMSG_RET_TIMEOUT);
		}
	}
}
// 原点复归指令映射
QString xMessageBox::TransHome(quint8 Type)
{
	switch (Type)
	{

        case CUSTOMER_FUN_Y_HOME:		return QString(tr("伺服 ") + GetServoName(AXIS_IDX_PVER)+ tr("轴原点"));		//*
        case CUSTOMER_FUN_Z_HOME:		return QString(tr("伺服 ") + GetServoName(AXIS_IDX_TRV)+ tr("轴原点"));			//*
        case CUSTOMER_FUN_X_HOME:		return QString(tr("伺服 ") + GetServoName(AXIS_IDX_PHOR)+ tr("轴原点"));		//*
    case CUSTOMER_FUN_A_HOME:
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        return QString(tr("伺服 ") + GetServoName(AXIS_IDX_RVER)+ tr("(倒角)轴原点"));		//*
    else
        return QString(tr("伺服 ") + GetServoName(AXIS_IDX_RVER)+ tr("轴原点"));		//*
    case CUSTOMER_FUN_B_HOME:
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        return QString(tr("伺服 ") + GetServoName(AXIS_IDX_RHOR)+ tr("(旋转)轴原点"));		//*
    else
        return QString(tr("伺服 ") + GetServoName(AXIS_IDX_RHOR)+ tr("轴原点"));		//*
//        case CUSTOMER_FUN_A_HOME:		return QString(tr("伺服 ") + GetServoName(AXIS_IDX_RVER)+ tr("轴原点"));		//*
//        case CUSTOMER_FUN_B_HOME:		return QString(tr("伺服 ") + GetServoName(AXIS_IDX_RHOR)+ tr("轴原点"));		//*
        case CUSTOMER_FUN_C_HOME:		return QString(tr("伺服 ") + GetServoName(AXIS_IDX_EXT)+ tr("轴原点"));			//*
		case CUSTOMER_FUN_PRO_VER:		return QString(tr("气动 主臂上行"));
		case CUSTOMER_FUN_PRO_HOR:    	return QString(tr("气动 主臂引拔"));
		case CUSTOMER_FUN_PRO_ROT:		return QString(tr("气动 主臂倒角"));			//*
		case CUSTOMER_FUN_PRO_REV:    	return QString(tr("气动 主臂旋转"));
		case CUSTOMER_FUN_RUN_VER:		return QString(tr("气动 副臂上行"));
        case CUSTOMER_FUN_RUN_HOR:    	return QString(tr("气动 副臂引拔"));          //*
        case CUSTOMER_FUN_RUN_ROT:		return QString(tr("气动 副臂倒角"));          //*
		case CUSTOMER_FUN_RUN_REV:    	return QString(tr("气动 副臂旋转"));
		default:						return QString(tr("其他 扩展动作"));			//*
	}
}

