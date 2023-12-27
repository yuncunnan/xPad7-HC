#include "xconfig.h"
#include "dialognumberpad.h"
#include "xioport.h"
#include "cmbprotocol.h"
#include "xstringresource.h"
#include "formactimm.h"
#include "ui_formactimm.h"

FormActIMM::FormActIMM(QWidget *parent) : QWidget(parent), ui(new Ui::FormActIMM)
{
    ui->setupUi(this);
#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(600.00);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(6000.0);
#endif
    pIMMBtn = new QButtonGroup;
    pIMMBtn->addButton(ui->radioButton_emo, IMMOUT_EMO);
    pIMMBtn->addButton(ui->radioButton_emc, IMMOUT_EMC);
    pIMMBtn->addButton(ui->radioButton_eef, IMMOUT_EEF);
    pIMMBtn->addButton(ui->radioButton_eeb, IMMOUT_EEB);
    pIMMBtn->addButton(ui->radioButton_c1p1, IMMOUT_C1P1);
    pIMMBtn->addButton(ui->radioButton_c1p2, IMMOUT_C1P2);
    pIMMBtn->addButton(ui->radioButton_c2p1, IMMOUT_C2P1);
    pIMMBtn->addButton(ui->radioButton_c2p2, IMMOUT_C2P2);
    pIMMBtn->addButton(ui->radioButton_eef_off, IMMOUT_EEF_OFF);
    pIMMBtn->addButton(ui->radioButton_eeb_off, IMMOUT_EEB_OFF);
    pIMMBtn->addButton(ui->radioButton_c1p1_off, IMMOUT_C1P1_OFF);
    pIMMBtn->addButton(ui->radioButton_c1p2_off, IMMOUT_C1P2_OFF);
    pIMMBtn->addButton(ui->radioButton_c2p1_off, IMMOUT_C2P1_OFF);
    pIMMBtn->addButton(ui->radioButton_c2p2_off, IMMOUT_C2P2_OFF);
    // 连接信号槽
    connect(pIMMBtn, SIGNAL(buttonClicked(int)), this, SLOT(IMMBtnClick(int)));
#if (FACTORY == FA_SHINI)
    {
        ui->radioButton_c1p1->setText(tr("允中子1进", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC1P1"));
        ui->radioButton_c1p2->setText(tr("允中子1退", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC1P2"));
        ui->radioButton_c2p1->setText(tr("允中子2进", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC2P1"));
        ui->radioButton_c2p2->setText(tr("允中子2退", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC2P2"));
        ui->radioButton_c1p1_off->setText(tr("禁中子1进", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC1P1_OFF"));
        ui->radioButton_c1p2_off->setText(tr("禁中子1退", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC1P2_OFF"));
        ui->radioButton_c2p1_off->setText(tr("禁中子2进", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC2P1_OFF"));
        ui->radioButton_c2p2_off->setText(tr("禁中子2退", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC2P2_OFF"));
    }
#endif
}
FormActIMM::~FormActIMM()
{
    delete ui;
}

void FormActIMM::changeEvent(QEvent *e)
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
void FormActIMM::IMMBtnClick(int btn)
{
    GetType();
}

int FormActIMM::GetType()
{
	if (ui->radioButton_emo->isChecked())
        return IMMOUT_EMO;
    if (ui->radioButton_emc->isChecked())
        return IMMOUT_EMC;
    if (ui->radioButton_eef->isChecked())
        return IMMOUT_EEF;
    if (ui->radioButton_eeb->isChecked())
		return IMMOUT_EEB;
    if (ui->radioButton_c1p1->isChecked())
        return IMMOUT_C1P1;
    if (ui->radioButton_c1p2->isChecked())
        return IMMOUT_C1P2;
    if (ui->radioButton_c2p1->isChecked())
        return IMMOUT_C2P1;
	if (ui->radioButton_c2p2->isChecked())
        return IMMOUT_C2P2;
	if (ui->radioButton_eef_off->isChecked())
		return IMMOUT_EEF_OFF;
	if (ui->radioButton_eeb_off->isChecked())
		return IMMOUT_EEB_OFF;
	if (ui->radioButton_c1p1_off->isChecked())
		return IMMOUT_C1P1_OFF;
	if (ui->radioButton_c1p2_off->isChecked())
		return IMMOUT_C1P2_OFF;
	if (ui->radioButton_c2p1_off->isChecked())
		return IMMOUT_C2P1_OFF;
	if (ui->radioButton_c2p2_off->isChecked())
		return IMMOUT_C2P2_OFF;

	return IMMOUT_EMO;
}

void FormActIMM::SetType(int type)
{
    switch(type)
    {
    case IMMOUT_EMO:
        ui->radioButton_emo->setChecked(true);
        break;
    case IMMOUT_EMC:
        ui->radioButton_emc->setChecked(true);
        break;
    case IMMOUT_EEF:
        ui->radioButton_eef->setChecked(true);
        break;
    case IMMOUT_EEB:
        ui->radioButton_eeb->setChecked(true);
        break;
    case IMMOUT_C1P1:
        ui->radioButton_c1p1->setChecked(true);
        break;
    case IMMOUT_C1P2:
        ui->radioButton_c1p2->setChecked(true);
        break;
    case IMMOUT_C2P1:
        ui->radioButton_c2p1->setChecked(true);
        break;
    case IMMOUT_C2P2:
        ui->radioButton_c2p2->setChecked(true);
        break;
	case IMMOUT_EEF_OFF:
		ui->radioButton_eef_off->setChecked(true);
		break;
	case IMMOUT_EEB_OFF:
		ui->radioButton_eeb_off->setChecked(true);
		break;
	case IMMOUT_C1P1_OFF:
		ui->radioButton_c1p1_off->setChecked(true);
		break;
	case IMMOUT_C1P2_OFF:
		ui->radioButton_c1p2_off->setChecked(true);
		break;
	case IMMOUT_C2P1_OFF:
		ui->radioButton_c2p1_off->setChecked(true);
		break;
	case IMMOUT_C2P2_OFF:
		ui->radioButton_c2p2_off->setChecked(true);
		break;
    }
}

int FormActIMM::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

void FormActIMM::SetDelay(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

void FormActIMM::inputDelay(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
		ui->BoxDelay->setValue(value);
}

void FormActIMM::UpdateWidgetState()
{
    ui->radioButton_eeb->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EEB));
    ui->radioButton_c1p1->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P1));
    ui->radioButton_c1p2->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P2));
    ui->radioButton_c2p1->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P1));
    ui->radioButton_c2p2->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P2));
    ui->radioButton_eeb_off->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EEB));
    ui->radioButton_c1p1_off->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P1));
    ui->radioButton_c1p2_off->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P2));
    ui->radioButton_c2p1_off->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P1));
    ui->radioButton_c2p2_off->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P2));
#if FACTORY == FA_SINROBOT_JC
	ui->radioButton_emo->setText(tr("加工完成"));
	ui->radioButton_emc->setText(tr("加工启动"));
    ui->radioButton_eef_off->setVisible(false);
    ui->radioButton_eeb_off->setVisible(false);
    ui->radioButton_eeb->setVisible(false);
    ui->radioButton_eef->setVisible(false);
    ui->radioButton_c1p1_off->setVisible(false);
    ui->radioButton_c1p2_off->setVisible(false);
    ui->radioButton_c2p1_off->setVisible(false);
    ui->radioButton_c2p2_off->setVisible(false);
    ui->radioButton_c1p1->setVisible(false);
    ui->radioButton_c1p2->setVisible(false);
    ui->radioButton_c2p1->setVisible(false);
    ui->radioButton_c2p2->setVisible(false);
#endif
#if (FACTORY == FA_VICTOR_SPECIAL)              //2023-12-06
    ui->radioButton_emo->setText(tr("等待加工"));
    ui->radioButton_emc->setText(tr("允许加工"));
    ui->radioButton_eef->setVisible(false);
#endif
}
