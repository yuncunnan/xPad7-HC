#ifndef XMESSAGEBOX_H
#define XMESSAGEBOX_H

#include <QDialog>
#include "cmbprotocol.h"

#define XMSG_RET_TIMEOUT		0
#define XMSG_RET_WAITFINISH		1
#define XMSG_RET_YES			2
#define XMSG_RET_NO				3
#define XMSG_RET_SAVE			4
#define XMSG_RET_NOSAVE			5
#define XMSG_RET_CANCEL			6

#define XMSG_HAS_SHOWED			255

#define XMSG_TYP_WAIT		0
#define XMSG_TYP_INF		1
#define XMSG_TYP_WAR		2
#define XMSG_TYP_ASK		3
#define XMSG_TYP_SAVE		4
#define XMSG_TYP_HOME		5
#define XMSG_TYP_DOORRESET	6
#define XMSG_TYP_OUTIMM 	7

class QMovie;
class QTimer;
namespace Ui {
class xMessageBox;
}

class xMessageBox : public QDialog
{
	Q_OBJECT
	

public:
	explicit xMessageBox(QWidget *parent = 0);
	~xMessageBox();
	
	static qint32 RunMsg(xMessageBox *pDlg);

    static qint32 DoWaiting(const QString &title, const QString &msg); // 消息等待框
    static qint32 DoHomeWaiting(const QString &title);					// 原点复归提示框
	static qint32 DoInformation(const QString &title, const QString &msg);
	static qint32 DoWarning(const QString &title, const QString &msg);
    static qint32 DoIMM_OUT(CMBProtocol *modbus,const QString &title, const QString &msg);
	static qint32 DoQuestion(const QString &title, const QString &msg);
    static qint32 DoDoorResetQuestion(const QString &title, const QString &msg);
	static qint32 DoSaveTip(const QString &title, const QString &msg);
    static qint32 DoAdjQuestion(const QString &title, const QString &msg);
    static qint32 DoJBYSaveQuestion(const QString &title, const QString &msg);
    static bool IsShow(void){return pmsgdlg!=NULL;}
    static void ForceQuit(void);
protected:
	void resizeEvent(QResizeEvent *event);

private:
	Ui::xMessageBox *ui;

	QMovie *pMovie;
	QTimer *pTimer;
	quint32 TimeCount;
	quint8 MsgType;
    static xMessageBox* pmsgdlg;
	static QString TransHome(quint8 Type);
	static quint16 home[HOME_DEF_MAX];
    static CMBProtocol *pModbus;

//	static quint32 ShowCount;

private slots:
	void BtnF1Clicked(void);
	void BtnF2Clicked(void);
	void BtnF3Clicked(void);
	void PeriodCount(void);
};

#endif // XMESSAGEBOX_H
