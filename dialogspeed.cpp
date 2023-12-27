#include "dialognumberpad.h"
#include "dialogspeed.h"
#include "ui_dialogspeed.h"

DialogSpeed::DialogSpeed(QWidget *parent) : QDialog(parent), ui(new Ui::DialogSpeed)
{
	ui->setupUi(this);
#if defined(Q_WS_QWS)
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
}

DialogSpeed::~DialogSpeed()
{
	delete ui;
}

void DialogSpeed::changeEvent(QEvent *e)
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

int DialogSpeed::DoForm(quint8 &speed, quint8 initSpd)
{
	int ret;
	ui->BoxRunSpd->setValue(initSpd);
	// 显示对话框
	ret = exec();
	// 返回输入的数值
	if (ret == QDialog::Accepted)
		speed = ui->BoxRunSpd->value();
//	else
//		speed = 0;
	return ret;
}

void DialogSpeed::inputSpeed(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxRunSpd->minimum(), ui->BoxRunSpd->maximum()) == QDialog::Accepted)
		ui->BoxRunSpd->setValue(value);
}
