#include <QButtonGroup>
#include "dialognumberpad.h"
#include "formbtnextpos.h"
#include "cmbprotocol.h"
#include "ui_formbtnextpos.h"
#include "servoalias.h"
#include "xmessagebox.h"
#include "xstringresource.h"

FormBtnExtPos::FormBtnExtPos(QWidget *parent) : QWidget(parent), ui(new Ui::FormBtnExtPos)
{
    ui->setupUi(this);
    retranslateUi();
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);

    m_x_type = POS_TYPE_POINT;
    m_y_type = POS_TYPE_POINT;
    m_z_type = POS_TYPE_POINT;
    m_a_type = POS_TYPE_POINT;
    m_b_type = POS_TYPE_POINT;
    m_c_type = POS_TYPE_POINT;

    m_x_pos = 0;
    m_y_pos = 0;
    m_z_pos = 0;
    m_a_pos = 0;
    m_b_pos = 0;
    m_c_pos = 0;

	// 初始化界面
#if TIME_BASE == 10
    ui->BoxPaHorDelay->setDecimals(2);
    ui->BoxPaHorDelay->setMaximum(9.99);
    ui->BoxPaVerDelay->setDecimals(2);
    ui->BoxPaVerDelay->setMaximum(9.99);
    ui->BoxTrvDelay->setDecimals(2);
    ui->BoxTrvDelay->setMaximum(9.99);
    ui->BoxRaHorDelay->setDecimals(2);
    ui->BoxRaHorDelay->setMaximum(9.99);
    ui->BoxRaVerDelay->setDecimals(2);
    ui->BoxRaVerDelay->setMaximum(9.99);
    ui->BoxOtherDelay->setDecimals(2);
    ui->BoxOtherDelay->setMaximum(9.99);
#else
    ui->BoxPaHorDelay->setDecimals(1);
    ui->BoxPaHorDelay->setMaximum(99.9);
    ui->BoxPaVerDelay->setDecimals(1);
    ui->BoxPaVerDelay->setMaximum(99.9);
    ui->BoxTrvDelay->setDecimals(1);
    ui->BoxTrvDelay->setMaximum(99.9);
    ui->BoxRaHorDelay->setDecimals(1);
    ui->BoxRaHorDelay->setMaximum(99.9);
    ui->BoxRaVerDelay->setDecimals(1);
    ui->BoxRaVerDelay->setMaximum(99.9);
    ui->BoxOtherDelay->setDecimals(1);
    ui->BoxOtherDelay->setMaximum(99.9);
#endif
}

FormBtnExtPos::~FormBtnExtPos()
{
	delete ui;
}

void FormBtnExtPos::changeEvent(QEvent *e)
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

void FormBtnExtPos::retranslateUi(void)
{
	ui->radioPaHor->setText(GetServoName(AXIS_IDX_PHOR));
	ui->radioPaVer->setText(GetServoName(AXIS_IDX_PVER));
	ui->radioTravel->setText(GetServoName(AXIS_IDX_TRV));
	ui->radioRaHor->setText(GetServoName(AXIS_IDX_RHOR));
	ui->radioRaVer->setText(GetServoName(AXIS_IDX_RVER));
	ui->radioOther->setText(GetServoName(AXIS_IDX_EXT));
    UpdateWidgetState();
}

bool FormBtnExtPos::EnterForm(void)
{
    init();
    UpdateWidgetState();
    show();
    return true;
}
void FormBtnExtPos::init(void)
{
    ui->radioPaHor->setChecked(false);
    ui->radioPaVer->setChecked(false);
    ui->radioTravel->setChecked(false);
    ui->radioRaHor->setChecked(false);
    ui->radioRaVer->setChecked(false);
    ui->radioOther->setChecked(false);
    ui->BoxPaHorSpeed->setValue(50);
    ui->BoxPaVerSpeed->setValue(50);
    ui->BoxTrvSpeed->setValue(50);
    ui->BoxRaHorSpeed->setValue(50);
    ui->BoxRaVerSpeed->setValue(50);
    ui->BoxOtherSpeed->setValue(50);
    ui->BoxPaHorDelay->setValue(0.00);
    ui->BoxPaVerDelay->setValue(0.00);
    ui->BoxTrvDelay->setValue(0.00);
    ui->BoxRaHorDelay->setValue(0.00);
    ui->BoxRaVerDelay->setValue(0.00);
    ui->BoxOtherDelay->setValue(0.00);
    ui->BoxPaHor->setText(QString::number(0 / 100.00));
    ui->BoxPaVer->setText(QString::number(0 / 100.00));
    ui->BoxTrv->setText(QString::number(0 / 100.00));
    ui->BoxRaHor->setText(QString::number(0 / 100.00));
    ui->BoxRaVer->setText(QString::number(0 / 100.00));
    ui->BoxOther->setText(QString::number(0 / 100.00));
    m_x_pos = 0;
    m_y_pos = 0;
    m_z_pos = 0;
    m_a_pos = 0;
    m_b_pos = 0;
    m_c_pos = 0;

    m_x_type = POS_TYPE_POINT;
    m_y_type = POS_TYPE_POINT;
    m_z_type = POS_TYPE_POINT;
    m_a_type = POS_TYPE_POINT;
    m_b_type = POS_TYPE_POINT;
    m_c_type = POS_TYPE_POINT;
}

quint32 FormBtnExtPos::GetPaHorSpeed()
{
    return ui->BoxPaHorSpeed->value();
}
quint32 FormBtnExtPos::GetPaVerSpeed()
{
    return ui->BoxPaVerSpeed->value();
}
quint32 FormBtnExtPos::GetTrvSpeed()
{
    return ui->BoxTrvSpeed->value();
}
quint32 FormBtnExtPos::GetRaHorSpeed()
{
    return ui->BoxRaHorSpeed->value();
}
quint32 FormBtnExtPos::GetRaVerSpeed()
{
    return ui->BoxRaVerSpeed->value();
}
quint32 FormBtnExtPos::GetOtherSpeed()
{
    return ui->BoxOtherSpeed->value();
}

int FormBtnExtPos::GetAxes()
{
    int ret = 0;
    if (ui->radioPaHor->isChecked())  ret |= (1<<AXIS_IDX_PHOR);
    if (ui->radioPaVer->isChecked())  ret |= (1<<AXIS_IDX_PVER);
    if (ui->radioTravel->isChecked())  ret |= (1<<AXIS_IDX_TRV);
    if (ui->radioRaHor->isChecked())  ret |= (1<<AXIS_IDX_RHOR);
    if (ui->radioRaVer->isChecked())  ret |= (1<<AXIS_IDX_RVER);
    if (ui->radioOther->isChecked())  ret |= (1<<AXIS_IDX_EXT);
    return ret;
}

int FormBtnExtPos::GetX()
{
    if (m_x_type==POS_TYPE_POINT)
        return m_x_pos;
    if (m_x_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_x_pos);
    return 0;
}

int FormBtnExtPos::GetY()
{
    if (m_y_type==POS_TYPE_POINT)
        return m_y_pos;
    if (m_y_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_y_pos);
    return 0;
}

int FormBtnExtPos::GetZ()
{
    if (m_z_type==POS_TYPE_POINT)
        return m_z_pos;
    if (m_z_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_z_pos);
    return 0;
}

int FormBtnExtPos::GetA()
{
    if (m_a_type==POS_TYPE_POINT)
        return m_a_pos;
    if (m_a_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_a_pos);
    return 0;
}

int FormBtnExtPos::GetB()
{
    if (m_b_type==POS_TYPE_POINT)
        return m_b_pos;
    if (m_b_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_b_pos);
    return 0;
}

int FormBtnExtPos::GetC()
{
    if (m_c_type==POS_TYPE_POINT)
        return m_c_pos;
    if (m_c_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_c_pos);
    return 0;
}

// 输入正臂引拔位置信号槽
void FormBtnExtPos::inputPaHor(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
    {
        if (m_x_type!=POS_TYPE_POINT) return;
        type = m_x_type;
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
    }
    else
    {
#if PENDANT_PROTOCOL
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
    }
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_x_type = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxPaHor->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxPaHor->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxPaHor->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_x_pos = value * 100;
            ui->BoxPaHor->setText(QString::number((double)m_x_pos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_x_pos = value;
            ui->BoxPaHor->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_x_pos));
            break;
        }
    }
	else
	{
        if ((m_x_type==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
			int diff = pos - m_x_pos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_x_pos += diff;
            ui->BoxPaHor->setText(QString::number((double)m_x_pos / 100.00));
        }
	}
}
// 输入正臂上下位置信号槽
void FormBtnExtPos::inputPaVer(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
	{
		if (m_y_type!=POS_TYPE_POINT) return;
		type = m_y_type;
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	else
	{
#if PENDANT_PROTOCOL
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
	{
		m_y_type = type;
		switch(type)
		{
		case POS_TYPE_CAT:
			ui->BoxPaVer->setText(tr("取物点"));
			break;
		case POS_TYPE_REL:
			ui->BoxPaVer->setText(tr("置物点"));
			break;
		case POS_TYPE_WAIT:
			ui->BoxPaVer->setText(tr("待机点"));
			break;
        case POS_TYPE_POINT:
            m_y_pos = value * 100;
            ui->BoxPaVer->setText(QString::number((double)m_y_pos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_y_pos = value;
            ui->BoxPaVer->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_y_pos));
			break;
		}
	}
	else
	{
		if ((m_y_type==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
		{
            int pos = value * 100;
			int diff = pos - m_y_pos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_y_pos += diff;
            ui->BoxPaVer->setText(QString::number((double)m_y_pos / 100.00));
        }
	}
}
// 输入横行位置信号槽
void FormBtnExtPos::inputTravel(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
	{
		if (m_z_type!=POS_TYPE_POINT) return;
		type = m_z_type;
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetTravLen()  / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE  / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	else
	{
#if PENDANT_PROTOCOL
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetTravLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
	{
		m_z_type = type;
		switch(type)
		{
		case POS_TYPE_CAT:
			ui->BoxTrv->setText(tr("取物点"));
			break;
		case POS_TYPE_REL:
			ui->BoxTrv->setText(tr("置物点"));
			break;
		case POS_TYPE_WAIT:
			ui->BoxTrv->setText(tr("待机点"));
			break;
        case POS_TYPE_POINT:
            m_z_pos = value * 100;
            ui->BoxTrv->setText(QString::number((double)m_z_pos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_z_pos = value;
            ui->BoxTrv->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_z_pos));
			break;
		}
	}
	else
	{
		if ((m_z_type==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
		{
            int pos = value * 100;
			int diff = pos - m_z_pos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_z_pos += diff;
            ui->BoxTrv->setText(QString::number((double)m_z_pos / 100.00));
	}
	}
}
// 输入副臂引拔位置信号槽
void FormBtnExtPos::inputRaHor(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
	{
		if (m_b_type!=POS_TYPE_POINT) return;
		type = m_b_type;
#if PENDANT_PROTOCOL
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        {
            if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetHorInt() / 100.00) != QDialog::Accepted)
                return;
        }
        else
        {
            if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
                return;
        }
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
            return;
#endif
	}
	else
	{
#if PENDANT_PROTOCOL
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        {
            if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorInt() / 100.00) != QDialog::Accepted)
                return;
        }
        else
        {
            if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
                return;
        }
#else
        if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
            return;
#endif
	}
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
	{
		m_b_type = type;
		switch(type)
		{
		case POS_TYPE_CAT:
			ui->BoxRaHor->setText(tr("取物点"));
			break;
		case POS_TYPE_REL:
			ui->BoxRaHor->setText(tr("置物点"));
			break;
		case POS_TYPE_WAIT:
			ui->BoxRaHor->setText(tr("待机点"));
			break;
        case POS_TYPE_POINT:
            m_b_pos = value * 100;
            ui->BoxRaHor->setText(QString::number((double)m_b_pos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_b_pos = value;
            ui->BoxRaHor->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_b_pos));
			break;
		}
	}
	else
	{
		if ((m_b_type==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
		{
            int pos = value * 100;
			int diff = pos - m_b_pos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_b_pos += diff;
            ui->BoxRaHor->setText(QString::number((double)m_b_pos / 100.00));
	}
	}
}
// 输入副臂上下位置信号槽
void FormBtnExtPos::inputRaVer(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
	{
		if (m_a_type!=POS_TYPE_POINT) return;
		type = m_a_type;
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetRaVerLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	else
	{
#if PENDANT_PROTOCOL
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetRaVerLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
	{
		m_a_type = type;
		switch(type)
		{
		case POS_TYPE_CAT:
			ui->BoxRaVer->setText(tr("取物点"));
			break;
		case POS_TYPE_REL:
			ui->BoxRaVer->setText(tr("置物点"));
			break;
		case POS_TYPE_WAIT:
			ui->BoxRaVer->setText(tr("待机点"));
			break;
        case POS_TYPE_POINT:
            m_a_pos = value * 100;
            ui->BoxRaVer->setText(QString::number((double)m_a_pos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_a_pos = value;
            ui->BoxRaVer->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_a_pos));
			break;
		}
	}
	else
	{
		if ((m_a_type==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
		{
            int pos = value * 100;
			int diff = pos - m_a_pos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_a_pos += diff;
            ui->BoxRaVer->setText(QString::number((double)m_a_pos / 100.00));
	}
	}
}
// 输入扩展位置信号槽
void FormBtnExtPos::inputOther(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
	{
		if (m_c_type!=POS_TYPE_POINT) return;
		type = m_c_type;
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetExteLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	else
	{
#if PENDANT_PROTOCOL
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetExteLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
	{
		m_c_type = type;
		switch(type)
		{
		case POS_TYPE_CAT:
			ui->BoxOther->setText(tr("取物点"));
			break;
		case POS_TYPE_REL:
			ui->BoxOther->setText(tr("置物点"));
			break;
		case POS_TYPE_WAIT:
			ui->BoxOther->setText(tr("待机点"));
			break;
        case POS_TYPE_POINT:
            m_c_pos = value * 100;
            ui->BoxOther->setText(QString::number((double)m_c_pos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_c_pos = value;
            ui->BoxOther->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_c_pos));
			break;
		}
	}
	else
	{
		if ((m_c_type==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
		{
            int pos = value * 100;
			int diff = pos - m_c_pos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_c_pos += diff;
            ui->BoxOther->setText(QString::number((double)m_c_pos / 100.00));
	}
        }
}
void FormBtnExtPos::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
        ui->radioPaHor->setEnabled((false) && (!CMBProtocol::GetPaHorNotUse()));
        ui->radioPaVer->setEnabled(false);
        ui->radioRaHor->setEnabled((false) && CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
        ui->radioRaVer->setEnabled((false) && CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
        ui->radioTravel->setEnabled(false);
        ui->radioOther->setEnabled((false) && CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
        if ((m_x_type == POS_TYPE_CAT) || (m_x_type ==POS_TYPE_REL) || (m_x_type ==POS_TYPE_WAIT))
        {
            ui->BoxPaHor->setEnabled(false);
            ui->BoxPaHorSpeed->setEnabled(false);
            ui->BoxPaHorDelay->setEnabled(false);
        }
        if ((m_y_type == POS_TYPE_CAT) || (m_y_type ==POS_TYPE_REL) || (m_y_type ==POS_TYPE_WAIT))
        {
            ui->BoxPaVer->setEnabled(false);
            ui->BoxPaVerSpeed->setEnabled(false);
            ui->BoxPaVerDelay->setEnabled(false);
        }
        if ((m_z_type == POS_TYPE_CAT) || (m_z_type ==POS_TYPE_REL) || (m_z_type ==POS_TYPE_WAIT))
        {
            ui->BoxTrv->setEnabled(false);
            ui->BoxTrvSpeed->setEnabled(false);
            ui->BoxTrvDelay->setEnabled(false);
        }
        if ((m_b_type == POS_TYPE_CAT) || (m_b_type ==POS_TYPE_REL) || (m_b_type ==POS_TYPE_WAIT))
        {
            ui->BoxRaHor->setEnabled(false);
            ui->BoxRaHorSpeed->setEnabled(false);
            ui->BoxRaHorDelay->setEnabled(false);
        }
        if ((m_a_type == POS_TYPE_CAT) || (m_a_type ==POS_TYPE_REL) || (m_a_type ==POS_TYPE_WAIT))
        {
            ui->BoxRaVer->setEnabled(false);
            ui->BoxRaVerSpeed->setEnabled(false);
            ui->BoxRaVerDelay->setEnabled(false);
        }
        if ((m_c_type == POS_TYPE_CAT) || (m_c_type ==POS_TYPE_REL) || (m_c_type ==POS_TYPE_WAIT))
        {
            ui->BoxOther->setEnabled(false);
            ui->BoxOtherSpeed->setEnabled(false);
            ui->BoxOtherDelay->setEnabled(false);
        }
    }
    else
    {
        ui->BoxPaVer->setEnabled(ui->radioPaVer->isChecked());
        ui->BoxPaVerSpeed->setEnabled(ui->radioPaVer->isChecked());
        ui->BoxPaVerDelay->setEnabled(ui->radioPaVer->isChecked());
        ui->BoxTrv->setEnabled(ui->radioTravel->isChecked());
        ui->BoxTrvSpeed->setEnabled(ui->radioTravel->isChecked());
        ui->BoxTrvDelay->setEnabled(ui->radioTravel->isChecked());
        if (!CMBProtocol::GetPaHorNotUse())
        {
            ui->BoxPaHor->setEnabled(ui->radioPaHor->isChecked());
            ui->BoxPaHorSpeed->setEnabled(ui->radioPaHor->isChecked());
            ui->BoxPaHorDelay->setEnabled(ui->radioPaHor->isChecked());
        }
        else
        {
            ui->BoxPaHor->setEnabled(false);
            ui->BoxPaHorSpeed->setEnabled(false);
            ui->BoxPaHorDelay->setEnabled(false);
        }
        if (CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0))
        {
            ui->BoxRaHor->setEnabled(ui->radioRaHor->isChecked());
            ui->BoxRaHorSpeed->setEnabled(ui->radioRaHor->isChecked());
            ui->BoxRaHorDelay->setEnabled(ui->radioRaHor->isChecked());
        }
        else
        {
            ui->BoxRaHor->setEnabled(false);
            ui->BoxRaHorSpeed->setEnabled(false);
            ui->BoxRaHorDelay->setEnabled(false);
        }
        if (CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0))
        {
            ui->BoxRaVer->setEnabled(ui->radioRaVer->isChecked());
            ui->BoxRaVerSpeed->setEnabled(ui->radioRaVer->isChecked());
            ui->BoxRaVerDelay->setEnabled(ui->radioRaVer->isChecked());
        }
        else
        {
            ui->BoxRaVer->setEnabled(false);
            ui->BoxRaVerSpeed->setEnabled(false);
            ui->BoxRaVerDelay->setEnabled(false);
        }
        if (CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0))
        {
            ui->BoxOther->setEnabled(ui->radioOther->isChecked());
            ui->BoxOtherSpeed->setEnabled(ui->radioOther->isChecked());
            ui->BoxOtherDelay->setEnabled(ui->radioOther->isChecked());
        }
        else
        {
            ui->BoxOther->setEnabled(false);
            ui->BoxOtherSpeed->setEnabled(false);
            ui->BoxOtherDelay->setEnabled(false);
        }
        if(CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            // 手动模式
            ui->radioPaVer->setEnabled(true);
            ui->radioTravel->setEnabled(true);
            if (!CMBProtocol::GetPaHorNotUse())
            {
                ui->radioPaHor->setEnabled(true);
            }
            else
            {
                ui->radioPaHor->setEnabled(false);
                ui->radioPaHor->setChecked(false);
            }
            if (CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0))
            {
                ui->radioRaHor->setEnabled(true);
            }
            else
            {
                ui->radioRaHor->setEnabled(false);
                ui->radioRaHor->setChecked(false);
            }
            if (CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0))
            {
                ui->radioRaVer->setEnabled(true);
            }
            else
            {
                ui->radioRaVer->setEnabled(false);
                ui->radioRaVer->setChecked(false);
            }
            if (CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0))
            {
                ui->radioOther->setEnabled(true);
            }
            else
            {
                ui->radioOther->setEnabled(false);
                ui->radioOther->setChecked(false);
            }
        }
        else
        {
            // 自动模式
            ui->radioPaHor->setEnabled(false);
            ui->radioPaVer->setEnabled(false);
            ui->radioTravel->setEnabled(false);
            ui->radioRaHor->setEnabled(false);
            ui->radioRaVer->setEnabled(false);
            ui->radioOther->setEnabled(false);
            ui->BtnPaHorSync->setEnabled(false);
            ui->BtnPaVerSync->setEnabled(false);
            ui->BtnTrvSync->setEnabled(false);
            ui->BtnRaHorSync->setEnabled(false);
            ui->BtnRaVerSync->setEnabled(false);
            ui->BtnExtSync->setEnabled(false);
        }

    }
}
int FormBtnExtPos::GetPaHorDelay()
{
    return qRound(ui->BoxPaHorDelay->value() * (1000.0/TIME_BASE));
}
int FormBtnExtPos::GetPaVerDelay()
{
    return qRound(ui->BoxPaVerDelay->value() * (1000.0/TIME_BASE));
}
int FormBtnExtPos::GetTrvDelay()
{
    return qRound(ui->BoxTrvDelay->value() * (1000.0/TIME_BASE));
}
int FormBtnExtPos::GetRaHorDelay()
{
    return qRound(ui->BoxRaHorDelay->value() * (1000.0/TIME_BASE));
}
int FormBtnExtPos::GetRaVerDelay()
{
    return qRound(ui->BoxRaVerDelay->value() * (1000.0/TIME_BASE));
}
int FormBtnExtPos::GetOtherDelay()
{
    return qRound(ui->BoxOtherDelay->value() * (1000.0/TIME_BASE));
}
void FormBtnExtPos::inputPaHorSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxPaHorSpeed->minimum(), ui->BoxPaHorSpeed->maximum()) == QDialog::Accepted)
        ui->BoxPaHorSpeed->setValue(value);
}
void FormBtnExtPos::inputPaVerSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxPaVerSpeed->minimum(), ui->BoxPaVerSpeed->maximum()) == QDialog::Accepted)
        ui->BoxPaVerSpeed->setValue(value);
}
void FormBtnExtPos::inputTrvSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxTrvSpeed->minimum(), ui->BoxTrvSpeed->maximum()) == QDialog::Accepted)
        ui->BoxTrvSpeed->setValue(value);
}
void FormBtnExtPos::inputRaHorSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxRaHorSpeed->minimum(), ui->BoxRaHorSpeed->maximum()) == QDialog::Accepted)
        ui->BoxRaHorSpeed->setValue(value);
}
void FormBtnExtPos::inputRaVerSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxRaVerSpeed->minimum(), ui->BoxRaVerSpeed->maximum()) == QDialog::Accepted)
        ui->BoxRaVerSpeed->setValue(value);
}
void FormBtnExtPos::inputOtherSpeed(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxOtherSpeed->minimum(), ui->BoxOtherSpeed->maximum()) == QDialog::Accepted)
        ui->BoxOtherSpeed->setValue(value);
}
void FormBtnExtPos::inputPaHorDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaHorDelay->minimum(), ui->BoxPaHorDelay->maximum()) == QDialog::Accepted)
        ui->BoxPaHorDelay->setValue(value);
}
void FormBtnExtPos::inputPaVerDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxPaVerDelay->minimum(), ui->BoxPaVerDelay->maximum()) == QDialog::Accepted)
        ui->BoxPaVerDelay->setValue(value);
}
void FormBtnExtPos::inputTrvDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxTrvDelay->minimum(), ui->BoxTrvDelay->maximum()) == QDialog::Accepted)
        ui->BoxTrvDelay->setValue(value);
}
void FormBtnExtPos::inputRaHorDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaHorDelay->minimum(), ui->BoxRaHorDelay->maximum()) == QDialog::Accepted)
        ui->BoxRaHorDelay->setValue(value);
}
void FormBtnExtPos::inputRaVerDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxRaVerDelay->minimum(), ui->BoxRaVerDelay->maximum()) == QDialog::Accepted)
        ui->BoxRaVerDelay->setValue(value);
}
void FormBtnExtPos::inputOtherDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxOtherDelay->minimum(), ui->BoxOtherDelay->maximum()) == QDialog::Accepted)
        ui->BoxOtherDelay->setValue(value);
}
void FormBtnExtPos::syncPaHorPos(void)
{
    m_x_pos = CMBProtocol::GetPaHorPos();
    ui->BoxPaHor->setText(QString::number((double)m_x_pos / 100.00));
}
void FormBtnExtPos::syncPaVerPos(void)
{
    m_y_pos = CMBProtocol::GetPaVerPos();
    ui->BoxPaVer->setText(QString::number((double)m_y_pos / 100.00));
}
void FormBtnExtPos::syncTrvPos(void)
{
    m_z_pos = CMBProtocol::GetTravelPos();
    ui->BoxTrv->setText(QString::number((double)m_z_pos / 100.00));
}
void FormBtnExtPos::syncRaHorPos(void)
{
    m_b_pos = CMBProtocol::GetRaHorPos();
    ui->BoxRaHor->setText(QString::number((double)m_b_pos / 100.00));
}
void FormBtnExtPos::syncRaVerPos(void)
{
    m_a_pos = CMBProtocol::GetRaVerPos();
    ui->BoxRaVer->setText(QString::number((double)m_a_pos / 100.00));
}
void FormBtnExtPos::syncExtPos(void)
{
    m_c_pos = CMBProtocol::GetExtendPos();
    ui->BoxOther->setText(QString::number((double)m_c_pos / 100.00));
}

