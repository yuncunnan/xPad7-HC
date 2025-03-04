#include "formbacklight.h"
#include <QDebug>
#include "qtimer.h"
#include "ui_formbacklight.h"

uint32_t FormBacklight::lastSumMold;
uint32_t FormBacklight::lastInMold;
uint32_t FormBacklight::lastCyc;

FormBacklight::FormBacklight(CMBProtocol *modbus, QWidget *parent) :	QWidget(parent), ui(new Ui::FormBacklight)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	pModbus = modbus;
	// ����ʱ�Ӷ�ʱ��
	pClockTimer = new QTimer(this);
	// ����ʱ�Ӷ�ʱ��
	pClockTimer->start(1000);
	connect(pClockTimer,SIGNAL(timeout()),this,SLOT(clockUpdate()));//����ʱ��
	connect(pModbus, SIGNAL(signal_TotalMoldChange(uint32_t)), this, SLOT(prdSumChange(uint32_t)));//����ģ��
	connect(pModbus, SIGNAL(signal_PeriodTimeChange(uint32_t, uint16_t)), this, SLOT(periodChange(uint32_t, uint16_t)));//ѭ������
	connect(pModbus, SIGNAL(signal_InmoldTimeChange(uint32_t, uint16_t)), this, SLOT(inmoldTimeChange(uint32_t, uint16_t)));//ȡ������
	ui->label_lastSumMold->setText(QString::number(pModbus->GetPrdSum())+"pcs");
	ui->label_curCyc->setText(QString::number((double)lastCyc / (100.0), 'f', 2) +"S" );
	ui->label_curInMold->setText(QString::number((double)lastInMold / (100.0), 'f', 2) +"S" );

}

FormBacklight::~FormBacklight()
{
	delete ui;
	// ����������Դ
	delete pClockTimer;
}

bool FormBacklight::EnterForm(void)
{
	ui->label_lastSumMold->setText(QString::number(pModbus->GetPrdSum())+"pcs");
	ui->label_curCyc->setText(QString::number((double)lastCyc / (100.0), 'f', 2) +"S" );
	ui->label_curInMold->setText(QString::number((double)lastInMold / (100.0), 'f', 2) +"S" );
	show();
	return true;
}

bool FormBacklight::ExitForm(void)
{
	hide();
	return true;
}


// ���õ�ǰ�����¼�
void FormBacklight::clockUpdate(void)
{
	ui->dateEdit->setDate(QDate::currentDate());
	ui->timeEdit->setTime(QTime::currentTime());
}

void FormBacklight::prdSumChange(uint32_t input)
{
	if(input!=lastSumMold)
	{
		ui->label_lastSumMold->setText(QString::number(lastSumMold)+"pcs");
		lastSumMold=input;
	}
}

void FormBacklight::periodChange(uint32_t input, uint16_t idx)
{
	if (idx == 0)
		if(input!=lastCyc)
		{
			ui->label_curCyc->setText(QString::number((double)input / (100.0), 'f', 2) +"S" );
			lastCyc=input;
		}
}

void FormBacklight::inmoldTimeChange(uint32_t input, uint16_t idx)
{
	if (idx == 0)
		if(input!=lastInMold)
		{
			ui->label_curInMold->setText(QString::number((double)input / (100.0), 'f', 2) +"S" );
			lastInMold=input;
		}
}
