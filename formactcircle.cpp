#include <QPixmap>
#include "formactcircle.h"
#include "ui_formactcircle.h"
#include "dialognumberpad.h"
#include "cmbprotocol.h"
#include "servoalias.h"

FormActCircle::FormActCircle(QWidget *parent) : QWidget(parent), ui(new Ui::FormActCircle)
{
    ui->setupUi(this);
    retranslateUi();
}

FormActCircle::~FormActCircle()
{
    delete ui;
}

void FormActCircle::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
        retranslateUi();
		break;
	default:
		break;
	}
}

void FormActCircle::retranslateUi(void)
{
    ui->labelZ->setText(GetServoName(AXIS_IDX_TRV));
    ui->labelY2->setText(GetServoName(AXIS_IDX_RVER));
}

quint8 FormActCircle::GetDir()
{
    if (ui->checkBoxDir->isChecked())
        return CIRCLE_ANTI_CLOCKWIDE;
    else
        return CIRCLE_CLOCKWIDE;


}
void FormActCircle::SetDir(quint8 dir)
{
    if (dir == CIRCLE_CLOCKWIDE)
        ui->checkBoxDir->setChecked(false);
    else
        ui->checkBoxDir->setChecked(true);
}

quint16 FormActCircle::GetRadius()
{
    return qRound(ui->dSpinBoxRadius->value()*100.0);
}
void FormActCircle::SetRadius(quint16 radius)
{
    ui->dSpinBoxRadius->setValue((double)radius / 100.0);
}

quint8 FormActCircle::GetSpeed()
{
    return ui->BoxSpeed->value();
}
void FormActCircle::SetSpeed(quint8 speed)
{
    ui->BoxSpeed->setValue((double)speed);
}

quint8 FormActCircle::GetBegin()
{
    return ui->comboBoxStart->currentIndex();
}
void FormActCircle::SetBegin(quint8 begin)
{
    if (begin > 11) return;
    ui->comboBoxStart->setCurrentIndex(begin);
}

quint8 FormActCircle::GetEnd()
{
    return ui->comboBoxEnd->currentIndex();
}
void FormActCircle::SetEnd(quint8 end)
{
    if (end > 11) return;
    ui->comboBoxEnd->setCurrentIndex(end);
}

quint32 FormActCircle::GetZ()
{
    return qRound(ui->doubleSpinBoxZ->value() * 100.0);
}
void FormActCircle::SetZ(quint32 zpoint)
{
    ui->doubleSpinBoxZ->setValue((double)zpoint / 100.0);
}

quint32 FormActCircle::GetY2()
{
    return qRound(ui->doubleSpinBoxY2->value() * 100.0);
}
void FormActCircle::SetY2(quint32 y2point)
{
    ui->doubleSpinBoxY2->setValue((double)y2point / 100.0);
}

void FormActCircle::UpdateWidgetState()
{
    if(CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        ui->BoxSpeed->setEnabled(true);
        ui->checkBoxDir->setEnabled(true);
        ui->comboBoxEnd->setEnabled(true);
        ui->comboBoxStart->setEnabled(true);
        ui->dSpinBoxRadius->setEnabled(true);
    }
    else
    {
        ui->BoxSpeed->setEnabled(false);
        ui->checkBoxDir->setEnabled(false);
        ui->comboBoxEnd->setEnabled(false);
        ui->comboBoxStart->setEnabled(false);
        ui->dSpinBoxRadius->setEnabled(false);
    }
    if (ui->checkBoxDir->isChecked())
        ui->labelCirclePic->setPixmap(QPixmap("://img/action/anti_clockwise.png"));
    else
        ui->labelCirclePic->setPixmap(QPixmap("://img/action/Clockwise.png"));
}
void FormActCircle::inputRadius(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->dSpinBoxRadius->minimum(), ui->dSpinBoxRadius->maximum()) == QDialog::Accepted)
        ui->dSpinBoxRadius->setValue(value);
}
void FormActCircle::inputSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxSpeed->minimum(), ui->BoxSpeed->maximum()) == QDialog::Accepted)
        ui->BoxSpeed->setValue(value);
}
void FormActCircle::setCirclePic(void)
{
    if (ui->checkBoxDir->isChecked())
        ui->labelCirclePic->setPixmap(QPixmap("://img/action/anti_clockwise.png"));
    else
        ui->labelCirclePic->setPixmap(QPixmap("://img/action/Clockwise.png"));
}
void FormActCircle::inputZ(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->doubleSpinBoxZ->minimum(), ui->doubleSpinBoxZ->maximum()) == QDialog::Accepted)
        ui->doubleSpinBoxZ->setValue(value);
}
void FormActCircle::inputY2(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormPos(value, ui->doubleSpinBoxY2->minimum(), ui->doubleSpinBoxY2->maximum()) == QDialog::Accepted)
        ui->doubleSpinBoxY2->setValue(value);
}
void FormActCircle::SetZPoint(void)
{
    ui->doubleSpinBoxZ->setValue((double)CMBProtocol::GetTravelPos() / 100.0);
}
void FormActCircle::SetY2Point(void)
{
    ui->doubleSpinBoxY2->setValue((double)CMBProtocol::GetRaVerPos() / 100.0);
}

