#include "dialognumberpad.h"
#include "cmbprotocol.h"
#include "formactvision.h"
#include "ui_formactvision.h"
#include "xconfig.h"
#include "xstringresource.h"

FormActVision::FormActVision(QWidget *parent) : QWidget(parent), ui(new Ui::FormActVision)
{
    ui->setupUi(this);
#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(9.99);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(99.9);
#endif

}

FormActVision::~FormActVision()
{
    delete ui;
}

void FormActVision::changeEvent(QEvent *e)
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

// 输入延时参数信号槽
void FormActVision::inputDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
        ui->BoxDelay->setValue(value);
}

int FormActVision::GetTimeout()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}
void FormActVision::SetTimeOut(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}
int FormActVision::GetVision()
{
    return ui->comboBoxVision->currentIndex();
}
void FormActVision::SetVision(int vision)
{
    ui->comboBoxVision->setCurrentIndex(vision);
}
int FormActVision::GetMatch()
{
    return m_matchbmp;
}
void FormActVision::SetMatch(int match)
{
    m_matchbmp = match;
}
int FormActVision::GetData(int idxmatch, int idxdata)
{
    return m_uservar[idxmatch][idxdata];
}
void FormActVision::SetData(int idxmatch, int idxdata, int uservar)
{
/*
    m_uservar[idxmatch][idxdata] = uservar;
    switch (idxdata)
    {
    case 0:
        ui->BoxVisionVar1->setText(xStringResource::GetUserVarName(m_uservar[0][0]));
        break;
    case 1:
        ui->BoxVisionVar2->setText(xStringResource::GetUserVarName(m_uservar[0][1]));
        break;
    case 2:
        ui->BoxVisionVar3->setText(xStringResource::GetUserVarName(m_uservar[0][2]));
        break;
    case 3:
        ui->BoxVisionVar4->setText(xStringResource::GetUserVarName(m_uservar[0][3]));
        break;
    }
*/
    m_uservar[idxmatch][idxdata] = uservar;
    switch (idxmatch)
    {
        case 0:
        {
            switch (idxdata)
            {
            case 0:
                ui->BoxVisionVar1->setText(xStringResource::GetUserVarName(m_uservar[0][0]));
                break;
            case 1:
                ui->BoxVisionVar2->setText(xStringResource::GetUserVarName(m_uservar[0][1]));
                break;
            case 2:
                ui->BoxVisionVar3->setText(xStringResource::GetUserVarName(m_uservar[0][2]));
                break;
            case 3:
                ui->BoxVisionVar4->setText(xStringResource::GetUserVarName(m_uservar[0][3]));
                break;
            }
            break;
        }
        case 1:
        {
            switch (idxdata)
            {
            case 0:
                ui->BoxVisionVar5->setText(xStringResource::GetUserVarName(m_uservar[1][0]));
                break;
            case 1:
                ui->BoxVisionVar6->setText(xStringResource::GetUserVarName(m_uservar[1][1]));
                break;
            case 2:
                ui->BoxVisionVar7->setText(xStringResource::GetUserVarName(m_uservar[1][2]));
                break;
            case 3:
                ui->BoxVisionVar8->setText(xStringResource::GetUserVarName(m_uservar[1][3]));
                break;
            }
            break;
        }
        case 2:
        {
            switch (idxdata)
            {
            case 0:
                ui->BoxVisionVar9->setText(xStringResource::GetUserVarName(m_uservar[2][0]));
                break;
            case 1:
                ui->BoxVisionVar10->setText(xStringResource::GetUserVarName(m_uservar[2][1]));
                break;
            case 2:
                ui->BoxVisionVar11->setText(xStringResource::GetUserVarName(m_uservar[2][2]));
                break;
            case 3:
                ui->BoxVisionVar12->setText(xStringResource::GetUserVarName(m_uservar[2][3]));
                break;
            }
            break;
        }
    }
}
void FormActVision::inputUserVar1(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[0][0] = VAR_TYPE_USR | value;
        ui->BoxVisionVar1->setText(xStringResource::GetUserVarName(m_uservar[0][0]));
    }
}
void FormActVision::inputUserVar2(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[0][1] = VAR_TYPE_USR | value;
        ui->BoxVisionVar2->setText(xStringResource::GetUserVarName(m_uservar[0][1]));
    }
}
void FormActVision::inputUserVar3(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[0][2] = VAR_TYPE_USR | value;
        ui->BoxVisionVar3->setText(xStringResource::GetUserVarName(m_uservar[0][2]));
    }
}
void FormActVision::inputUserVar4(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[0][3] = VAR_TYPE_USR | value;
        ui->BoxVisionVar4->setText(xStringResource::GetUserVarName(m_uservar[0][3]));
    }
}
void FormActVision::inputUserVar5(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[1][0] = VAR_TYPE_USR | value;
        ui->BoxVisionVar5->setText(xStringResource::GetUserVarName(m_uservar[1][0]));
    }
}
void FormActVision::inputUserVar6(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[1][1] = VAR_TYPE_USR | value;
        ui->BoxVisionVar6->setText(xStringResource::GetUserVarName(m_uservar[1][1]));
    }
}
void FormActVision::inputUserVar7(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[1][2] = VAR_TYPE_USR | value;
        ui->BoxVisionVar7->setText(xStringResource::GetUserVarName(m_uservar[1][2]));
    }
}
void FormActVision::inputUserVar8(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[1][3] = VAR_TYPE_USR | value;
        ui->BoxVisionVar8->setText(xStringResource::GetUserVarName(m_uservar[1][3]));
    }
}
void FormActVision::inputUserVar9(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[2][0] = VAR_TYPE_USR | value;
        ui->BoxVisionVar9->setText(xStringResource::GetUserVarName(m_uservar[2][0]));
    }
}
void FormActVision::inputUserVar10(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[2][1] = VAR_TYPE_USR | value;
        ui->BoxVisionVar10->setText(xStringResource::GetUserVarName(m_uservar[2][1]));
    }
}
void FormActVision::inputUserVar11(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[2][2] = VAR_TYPE_USR | value;
        ui->BoxVisionVar11->setText(xStringResource::GetUserVarName(m_uservar[2][2]));
    }
}
void FormActVision::inputUserVar12(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 400, 499) == QDialog::Accepted)
    {
        m_uservar[2][3] = VAR_TYPE_USR | value;
        ui->BoxVisionVar12->setText(xStringResource::GetUserVarName(m_uservar[2][3]));
    }
}

void FormActVision::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->comboBoxVision->setEnabled(false);
    }
    else
    {
        if(CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            // 手动模式
            ui->BoxVisionVar1->setEnabled(true);
            ui->BoxVisionVar2->setEnabled(true);
            ui->BoxVisionVar3->setEnabled(true);
            ui->BoxVisionVar4->setEnabled(true);
            ui->BoxVisionVar5->setEnabled(true);
            ui->BoxVisionVar6->setEnabled(true);
            ui->BoxVisionVar7->setEnabled(true);
            ui->BoxVisionVar8->setEnabled(true);
            ui->BoxVisionVar9->setEnabled(true);
            ui->BoxVisionVar10->setEnabled(true);
            ui->BoxVisionVar11->setEnabled(true);
            ui->BoxVisionVar12->setEnabled(true);
            ui->comboBoxVision->setEnabled(true);
        }
        else
        {
            // 自动模式
            ui->BoxVisionVar1->setEnabled(false);
            ui->BoxVisionVar2->setEnabled(false);
            ui->BoxVisionVar3->setEnabled(false);
            ui->BoxVisionVar4->setEnabled(false);
            ui->BoxVisionVar5->setEnabled(true);
            ui->BoxVisionVar6->setEnabled(true);
            ui->BoxVisionVar7->setEnabled(true);
            ui->BoxVisionVar8->setEnabled(true);
            ui->BoxVisionVar9->setEnabled(true);
            ui->BoxVisionVar10->setEnabled(true);
            ui->BoxVisionVar11->setEnabled(true);
            ui->BoxVisionVar12->setEnabled(true);
            ui->comboBoxVision->setEnabled(false);
        }

    }
}

