#include "xconfig.h"
#include "dialognumberpad.h"
#include "xioport.h"
#include "cmbprotocol.h"
#include "xstringresource.h"
#include "formbtnimm.h"
#include "ui_formbtnimm.h"

FormBtnIMM::FormBtnIMM(QWidget *parent) : QWidget(parent), ui(new Ui::FormBtnIMM)
{
    ui->setupUi(this);
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);
#if TIME_BASE == 10
    ui->BoxDelayEmo->setDecimals(2);
    ui->BoxDelayEmo->setMaximum(600.00);
    ui->BoxDelayEmc->setDecimals(2);
    ui->BoxDelayEmc->setMaximum(600.00);
    ui->BoxDelayEef->setDecimals(2);
    ui->BoxDelayEef->setMaximum(600.00);
    ui->BoxDelayEeb->setDecimals(2);
    ui->BoxDelayEeb->setMaximum(600.00);
    ui->BoxDelayC1p1->setDecimals(2);
    ui->BoxDelayC1p1->setMaximum(600.00);
    ui->BoxDelayC1p2->setDecimals(2);
    ui->BoxDelayC1p2->setMaximum(600.00);
    ui->BoxDelayC2p1->setDecimals(2);
    ui->BoxDelayC2p1->setMaximum(600.00);
    ui->BoxDelayC2p2->setDecimals(2);
    ui->BoxDelayC2p2->setMaximum(600.00);
#else
    ui->BoxDelayEmo->setDecimals(1);
    ui->BoxDelayEmo->setMaximum(6000.0);
    ui->BoxDelayEmc->setDecimals(1);
    ui->BoxDelayEmc->setMaximum(6000.0);
    ui->BoxDelayEef->setDecimals(1);
    ui->BoxDelayEef->setMaximum(6000.0);
    ui->BoxDelayEeb->setDecimals(1);
    ui->BoxDelayEeb->setMaximum(6000.0);
    ui->BoxDelayC1p1->setDecimals(1);
    ui->BoxDelayC1p1->setMaximum(6000.0);
    ui->BoxDelayC1p2->setDecimals(1);
    ui->BoxDelayC1p2->setMaximum(6000.0);
    ui->BoxDelayC2p1->setDecimals(1);
    ui->BoxDelayC2p1->setMaximum(6000.0);
    ui->BoxDelayC2p2->setDecimals(1);
    ui->BoxDelayC2p2->setMaximum(6000.0);
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
#if (FACTORY == FA_SHINI)
	{
        ui->radioButton_c1p1->setText(tr("允中子1进", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC1P1"));
        ui->radioButton_c1p2->setText(tr("允中子1退", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC1P2"));
        ui->radioButton_c2p1->setText(tr("允中子2进", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC2P1"));
        ui->radioButton_c2p2->setText(tr("允中子2退", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC2P2"));
//        ui->radioButton_c1p1_off->setText(tr("禁中子1进", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC1P1_OFF"));
//        ui->radioButton_c1p2_off->setText(tr("禁中子1退", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC1P2_OFF"));
//        ui->radioButton_c2p1_off->setText(tr("禁中子2进", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC2P1_OFF"));
//        ui->radioButton_c2p2_off->setText(tr("禁中子2退", "由于长度受限, 翻译时无论什么语言一律使用(中文除外): IMM-EC2P2_OFF"));
	}
#endif
}
FormBtnIMM::~FormBtnIMM()
{
    delete ui;
}

void FormBtnIMM::changeEvent(QEvent *e)
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
bool FormBtnIMM::EnterForm(void)
{
    init();
    UpdateWidgetState();
    show();
    return true;
}
void FormBtnIMM::init(void)
{
    ui->checkBoxEmo->setChecked(false);
    ui->checkBoxEmc->setChecked(false);
    ui->checkBoxEef->setChecked(false);
    ui->checkBoxEeb->setChecked(false);
    ui->checkBoxC1p1->setChecked(false);
    ui->checkBoxC1p2->setChecked(false);
    ui->checkBoxC2p1->setChecked(false);
    ui->checkBoxC2p2->setChecked(false);
    ui->BoxDelayEmo->setValue(0.0);
    ui->BoxDelayEmc->setValue(0.0);
    ui->BoxDelayEef->setValue(0.0);
    ui->BoxDelayEeb->setValue(0.0);
    ui->BoxDelayC1p1->setValue(0.0);
    ui->BoxDelayC1p2->setValue(0.0);
    ui->BoxDelayC2p1->setValue(0.0);
    ui->BoxDelayC2p2->setValue(0.0);

    ui->radioButton_eef->setChecked(false);
    ui->radioButton_eef->setOn(false);
    ui->radioButton_eef->setFlat(false);
    ui->radioButton_eef->setText(tr("允许顶进"));
    ui->radioButton_eeb->setChecked(false);
    ui->radioButton_eeb->setOn(false);
    ui->radioButton_eeb->setFlat(false);
    ui->radioButton_eeb->setText(tr("允许顶退"));
    ui->radioButton_c1p1->setChecked(false);
    ui->radioButton_c1p1->setOn(false);
    ui->radioButton_c1p1->setFlat(false);
    ui->radioButton_c1p1->setText(tr("允许抽1进"));
    ui->radioButton_c1p2->setChecked(false);
    ui->radioButton_c1p2->setOn(false);
    ui->radioButton_c1p2->setFlat(false);
    ui->radioButton_c1p2->setText(tr("允许抽1退"));
    ui->radioButton_c2p1->setChecked(false);
    ui->radioButton_c2p1->setOn(false);
    ui->radioButton_c2p1->setFlat(false);
    ui->radioButton_c2p1->setText(tr("允许抽2进"));
    ui->radioButton_c2p2->setChecked(false);
    ui->radioButton_c2p2->setOn(false);
    ui->radioButton_c2p2->setFlat(false);
    ui->radioButton_c2p2->setText(tr("允许抽2退"));
}

int FormBtnIMM::GetTypeEmo()
{
    if (ui->checkBoxEmo->isChecked())
        return IMMOUT_EMO;
}
int FormBtnIMM::GetTypeEmc()
{
    if (ui->checkBoxEmc->isChecked())
        return IMMOUT_EMC;
}

int FormBtnIMM::GetTypeEef()
{
    if (ui->checkBoxEef->isChecked())
    {
        if (ui->radioButton_eef->isFlat())
            return IMMOUT_EEF_OFF;
        return IMMOUT_EEF;
    }
}
int FormBtnIMM::GetTypeEeb()
{
    if (ui->checkBoxEeb->isChecked())
    {
        if (ui->radioButton_eeb->isFlat())
            return IMMOUT_EEB_OFF;
        return IMMOUT_EEB;
    }
}
int FormBtnIMM::GetTypeC1p1()
{
    if (ui->checkBoxC1p1->isChecked())
    {
        if (ui->radioButton_c1p1->isFlat())
            return IMMOUT_C1P1_OFF;
        return IMMOUT_C1P1;
    }
}
int FormBtnIMM::GetTypeC1p2()
{
    if (ui->checkBoxC1p2->isChecked())
    {
        if (ui->radioButton_c1p2->isFlat())
            return IMMOUT_C1P2_OFF;
        return IMMOUT_C1P2;
    }
}
int FormBtnIMM::GetTypeC2p1()
{
    if (ui->checkBoxC2p1->isChecked())
    {
        if (ui->radioButton_c2p1->isFlat())
            return IMMOUT_C2P1_OFF;
        return IMMOUT_C2P1;
    }
}
int FormBtnIMM::GetTypeC2p2()
{
    if (ui->checkBoxC2p2->isChecked())
    {
        if (ui->radioButton_c2p2->isFlat())
            return IMMOUT_C2P2_OFF;
        return IMMOUT_C2P2;
    }
}

int FormBtnIMM::GetIMMBmp()
{
    int ret = 0;
    if (ui->checkBoxEmc->isChecked()) ret |= (1<< 0);
    if (ui->checkBoxEmo->isChecked()) ret |= (1<< 1);
    if (ui->checkBoxEef->isChecked()) ret |= (1<< 2);
    if (ui->checkBoxEeb->isChecked()) ret |= (1<< 3);
    if (ui->checkBoxC1p1->isChecked()) ret |= (1<< 4);
    if (ui->checkBoxC1p2->isChecked()) ret |= (1<< 5);
    if (ui->checkBoxC2p1->isChecked()) ret |= (1<< 6);
    if (ui->checkBoxC2p2->isChecked()) ret |= (1<< 7);

    return ret;
}

int FormBtnIMM::GetDelayEmo()
{
    return qRound(ui->BoxDelayEmo->value() * (1000.0/TIME_BASE));
}
int FormBtnIMM::GetDelayEmc()
{
    return qRound(ui->BoxDelayEmc->value() * (1000.0/TIME_BASE));
}
int FormBtnIMM::GetDelayEef()
{
    return qRound(ui->BoxDelayEef->value() * (1000.0/TIME_BASE));
}
int FormBtnIMM::GetDelayEeb()
{
    return qRound(ui->BoxDelayEeb->value() * (1000.0/TIME_BASE));
}
int FormBtnIMM::GetDelayC1p1()
{
    return qRound(ui->BoxDelayC1p1->value() * (1000.0/TIME_BASE));
}
int FormBtnIMM::GetDelayC1p2()
{
    return qRound(ui->BoxDelayC1p2->value() * (1000.0/TIME_BASE));
}
int FormBtnIMM::GetDelayC2p1()
{
    return qRound(ui->BoxDelayC2p1->value() * (1000.0/TIME_BASE));
}
int FormBtnIMM::GetDelayC2p2()
{
    return qRound(ui->BoxDelayC2p2->value() * (1000.0/TIME_BASE));
}

void FormBtnIMM::inputDelayEmo(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayEmo->minimum(), ui->BoxDelayEmo->maximum()) == QDialog::Accepted)
        ui->BoxDelayEmo->setValue(value);
}
void FormBtnIMM::inputDelayEmc(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayEmc->minimum(), ui->BoxDelayEmc->maximum()) == QDialog::Accepted)
        ui->BoxDelayEmc->setValue(value);
}
void FormBtnIMM::inputDelayEef(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayEef->minimum(), ui->BoxDelayEef->maximum()) == QDialog::Accepted)
        ui->BoxDelayEef->setValue(value);
}
void FormBtnIMM::inputDelayEeb(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayEeb->minimum(), ui->BoxDelayEeb->maximum()) == QDialog::Accepted)
        ui->BoxDelayEeb->setValue(value);
}
void FormBtnIMM::inputDelayC1p1(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayC1p1->minimum(), ui->BoxDelayC1p1->maximum()) == QDialog::Accepted)
        ui->BoxDelayC1p1->setValue(value);
}
void FormBtnIMM::inputDelayC1p2(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayC1p2->minimum(), ui->BoxDelayC1p2->maximum()) == QDialog::Accepted)
        ui->BoxDelayC1p2->setValue(value);
}
void FormBtnIMM::inputDelayC2p1(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayC2p1->minimum(), ui->BoxDelayC2p1->maximum()) == QDialog::Accepted)
        ui->BoxDelayC2p1->setValue(value);
}
void FormBtnIMM::inputDelayC2p2(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelayC2p2->minimum(), ui->BoxDelayC2p2->maximum()) == QDialog::Accepted)
        ui->BoxDelayC2p2->setValue(value);
}

void FormBtnIMM::UpdateWidgetState()
{
    ui->radioButton_eeb->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EEB));
    ui->checkBoxEeb->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EEB));
    ui->BoxDelayEeb->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_EEB));
    ui->radioButton_c1p1->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P1));
    ui->checkBoxC1p1->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P1));
    ui->BoxDelayC1p1->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P1));
    ui->radioButton_c1p2->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P2));
    ui->checkBoxC1p2->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P2));
    ui->BoxDelayC1p2->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C1P2));
    ui->radioButton_c2p1->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P1));
    ui->checkBoxC2p1->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P1));
    ui->BoxDelayC2p1->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P1));
    ui->radioButton_c2p2->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P2));
    ui->checkBoxC2p2->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P2));
    ui->BoxDelayC2p2->setVisible(xIoPort::IsVisibleOutSignal(IMM_VAR_OUT_C2P2));


#if FACTORY == FA_SINROBOT_JC
	ui->radioButton_emo->setText(tr("加工完成"));
	ui->radioButton_emc->setText(tr("加工启动"));
    ui->radioButton_eeb->setVisible(false);
    ui->radioButton_eef->setVisible(false);
    ui->radioButton_c1p1->setVisible(false);
    ui->radioButton_c1p2->setVisible(false);
    ui->radioButton_c2p1->setVisible(false);
    ui->radioButton_c2p2->setVisible(false);
#endif

#if (FACTORY == FA_VICTOR_SPECIAL)              //2023-12-06
    ui->radioButton_emo->setText(tr("等待加工"));
    ui->radioButton_emc->setText(tr("允许加工"));
    ui->checkBoxEef->setVisible(false);
    ui->radioButton_eef->setVisible(false);
    ui->BoxDelayEef->setVisible(false);
#endif
}

void FormBtnIMM::btnEefclicked(void)
{
    if (ui->radioButton_eef->isFlat())
    {
        ui->radioButton_eef->setOn(false);
        ui->radioButton_eef->setFlat(false);
        ui->radioButton_eef->setText(tr("允许顶进"));
    }
    else
    {
        ui->radioButton_eef->setOn(true);
        ui->radioButton_eef->setFlat(true);
        ui->radioButton_eef->setText(tr("禁止顶进"));
    }
}
void FormBtnIMM::btnEebclicked(void)
{
    if (ui->radioButton_eeb->isFlat())
    {
        ui->radioButton_eeb->setOn(false);
        ui->radioButton_eeb->setFlat(false);
        ui->radioButton_eeb->setText(tr("允许顶退"));
    }
    else
    {
        ui->radioButton_eeb->setOn(true);
        ui->radioButton_eeb->setFlat(true);
        ui->radioButton_eeb->setText(tr("禁止顶退"));
    }
}
void FormBtnIMM::btnC1p1clicked(void)
{
    if (ui->radioButton_c1p1->isFlat())
    {
        ui->radioButton_c1p1->setOn(false);
        ui->radioButton_c1p1->setFlat(false);
        ui->radioButton_c1p1->setText(tr("允许抽1进"));
    }
    else
    {
        ui->radioButton_c1p1->setOn(true);
        ui->radioButton_c1p1->setFlat(true);
        ui->radioButton_c1p1->setText(tr("禁止抽1进"));
    }
}
void FormBtnIMM::btnC1p2clicked(void)
{
    if (ui->radioButton_c1p2->isFlat())
    {
        ui->radioButton_c1p2->setOn(false);
        ui->radioButton_c1p2->setFlat(false);
        ui->radioButton_c1p2->setText(tr("允许抽1退"));
    }
    else
    {
        ui->radioButton_c1p2->setOn(true);
        ui->radioButton_c1p2->setFlat(true);
        ui->radioButton_c1p2->setText(tr("禁止抽1退"));
    }
}
void FormBtnIMM::btnC2p1clicked(void)
{
    if (ui->radioButton_c2p1->isFlat())
    {
        ui->radioButton_c2p1->setOn(false);
        ui->radioButton_c2p1->setFlat(false);
        ui->radioButton_c2p1->setText(tr("允许抽2进"));
    }
    else
    {
        ui->radioButton_c2p1->setOn(true);
        ui->radioButton_c2p1->setFlat(true);
        ui->radioButton_c2p1->setText(tr("禁止抽2进"));
    }
}
void FormBtnIMM::btnC2p2clicked(void)
{
    if (ui->radioButton_c2p2->isFlat())
    {
        ui->radioButton_c2p2->setOn(false);
        ui->radioButton_c2p2->setFlat(false);
        ui->radioButton_c2p2->setText(tr("允许抽2退"));
    }
    else
    {
        ui->radioButton_c2p2->setOn(true);
        ui->radioButton_c2p2->setFlat(true);
        ui->radioButton_c2p2->setText(tr("禁止抽2退"));
    }
}
