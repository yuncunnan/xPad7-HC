#include "dialognumberpad.h"
#include "elccalc.h"
#include "ui_elccalc.h"

quint64 MDivisor(quint64 x, quint64  y)
{

	quint64 MD = x;
	if(y < x) MD = y;
	for(; MD >= 1; MD--)
	{
		if((x % MD == 0) && (y % MD == 0))
			break;
	}
	return MD;
}

ElcCalc::ElcCalc(QWidget *parent) : QDialog(parent), ui(new Ui::ElcCalc)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
}

ElcCalc::~ElcCalc()
{
	delete ui;
}

void ElcCalc::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

// 输入编码器分辨率
void ElcCalc::inputResolution(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->boxResolution->minimum(), ui->boxResolution->maximum()) == QDialog::Accepted)
		ui->boxResolution->setValue(value);
}
// 输入同步轮周长
void ElcCalc::inputPerimeter(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->boxPulleyPerimeter->minimum(), ui->boxPulleyPerimeter->maximum()) == QDialog::Accepted)
		ui->boxPulleyPerimeter->setValue(value);
}
// 输入减速比分子
void ElcCalc::inputNumerator(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->boxNumerator->minimum(), ui->boxNumerator->maximum()) == QDialog::Accepted)
		ui->boxNumerator->setValue(value);
}
// 输入减速比分母
void ElcCalc::inputDenomintor(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->boxDenominator->minimum(), ui->boxDenominator->maximum()) == QDialog::Accepted)
		ui->boxDenominator->setValue(value);
}

void ElcCalc::press(void)
{
	quint64 Pluse_L =100, T1, T2, Numerator, Nominator, T3, Circle, Slow_M, Slow_S, Pluse_Motor;
	Pluse_Motor= ui->boxResolution->value();
	Circle = ui->boxPulleyPerimeter->value();
	Slow_S = ui->boxNumerator->value();
	Slow_M = ui->boxDenominator->value();
	T1 = Pluse_L * Pluse_Motor * Slow_M;
	T2 = Circle * Slow_S * 1000;
	T3 = MDivisor(T1, T2);
	if (T3 == 0)
	{
		ui->resultNumerator->setText("Invalid");
		ui->resultDenominator->setText("Invalid");
	}
	else
	{
		Numerator = T1 / T3;
		Nominator = T2 / T3;
		ui->resultNumerator->setText(QString::number(Numerator));
		ui->resultDenominator->setText(QString::number(Nominator));
	}
}
