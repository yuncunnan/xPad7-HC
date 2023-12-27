#include "dialoglogdetail.h"
#include "ui_dialoglogdetail.h"

DialogLogDetail::DialogLogDetail(QWidget *parent) : QDialog(parent), ui(new Ui::DialogLogDetail)
{
	ui->setupUi(this);
#if defined(Q_WS_QWS)
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
}

DialogLogDetail::~DialogLogDetail()
{
	delete ui;
}

int DialogLogDetail::DoForm(const QString &time, const QIcon &type, const QString &user, const QString &detail)
{
	// 设置图标
	ui->labelIcon->setPixmap(type.pixmap(ui->labelIcon->size()));
	// 设置记录时间
	ui->labelTime->setText(time);
	// 设置用户
	ui->labelUser->setText(user);
	// 设置详细内容
	ui->labelDetail->setText(detail);
	// 显示对话框
	return exec();
}

void DialogLogDetail::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}
