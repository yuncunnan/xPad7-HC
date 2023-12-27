#include <QSettings>
#include "xconfig.h"
#include "ui_xmessageboxactive.h"
#include "xmessageboxactive.h"
#include "dialogkeyboard.h"
#include "xmessagebox.h"
xMessageBoxActive::xMessageBoxActive(QWidget *parent) :	QDialog(parent), ui(new Ui::xMessageBoxActive)
{
	ui->setupUi(this);
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
}

xMessageBoxActive::~xMessageBoxActive()
{
	delete ui;
}

// 运行警告消息框
qint32 xMessageBoxActive::DoForm(QString &stractive)
{
    int ret;
    ui->lineEditUpdateReg->clear();
    ret = exec();
    // 返回输入的数值
    if (ret == QDialog::Accepted)
        stractive = ui->lineEditUpdateReg->text();
    else
        stractive = "";
    return ret;
}
void xMessageBoxActive::inputActive(void)
{
#if defined(Q_WS_WIN)
    ui->lineEditUpdateReg->setValidator(new QRegExpValidator(QRegExp("[A-Z2-7]{0,16}"), this));
#else
    QString str;
    ui->lineEditUpdateReg->setValidator(new QRegExpValidator(QRegExp("[A-Za-z2-7]{0,16}"), this));
    if (xKbd->DoForm(str, KEYBOARD_TYPE_STR) == QDialog::Accepted)
        ui->lineEditUpdateReg->setText(str.toUpper());
#endif
    if (!ui->lineEditUpdateReg->hasAcceptableInput())
    {
        xMessageBox::DoInformation(tr("系统提示"), tr("含有不符合要求的字符，\n请重新输入！"));
        ui->lineEditUpdateReg->setText("");
    }
}
