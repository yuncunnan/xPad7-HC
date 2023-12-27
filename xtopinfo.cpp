#include "xtopinfo.h"
#include "ui_xtopinfo.h"

xTopInfo *pTopInfo = 0;

xTopInfo::xTopInfo(QWidget *parent) : QDialog(parent), ui(new Ui::xTopInfo)
{
	ui->setupUi(this);
	pTopInfo = this;
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
}

xTopInfo::~xTopInfo()
{
	delete ui;
}

bool xTopInfo::ShowInformation(const QPixmap &pixmap, const QString &title, const QString &info, bool canClose)
{
	// 如果窗口已经显示则返回
	if (isVisible())
		return false;
	// 设置标题
	ui->labelTitle->setText(title);
	// 设置消息
	ui->labelMessage->setText(info);
	// 设置图标
	ui->labelImage->setPixmap(pixmap);
	// 设置窗口关闭按钮状态
	ui->pushButtonClose->setEnabled(canClose);
	// 显示窗口
	show();
	return true;
}
