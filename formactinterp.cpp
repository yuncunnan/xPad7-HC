#include <QSettings>
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "formactinterp.h"
#include "ui_formactinterp.h"
#include "servoalias.h"
#include "xstringresource.h"
#include "xmessagebox.h"

FormActInterp::FormActInterp(QWidget *parent) : QWidget(parent), ui(new Ui::FormActInterp)
{
	// 初始化界面
    ui->setupUi(this);
	retranslateUi();
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

}

FormActInterp::~FormActInterp()
{
    delete ui;
}

void FormActInterp::changeEvent(QEvent *e)
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

void FormActInterp::retranslateUi(void)
{
	ui->checkPaHor->setText(GetServoName(AXIS_IDX_PHOR));
	ui->checkPaVer->setText(GetServoName(AXIS_IDX_PVER));
	ui->checkTravel->setText(GetServoName(AXIS_IDX_TRV));
	ui->checkRaHor->setText(GetServoName(AXIS_IDX_RHOR));
	ui->checkRaVer->setText(GetServoName(AXIS_IDX_RVER));
	ui->checkOther->setText(GetServoName(AXIS_IDX_EXT));
}

quint32 FormActInterp::GetSpeed()
{
	return ui->BoxSpeed->value();
}

void FormActInterp::SetSpeed(int speed)
{
	ui->BoxSpeed->setValue(speed);
}

int FormActInterp::GetAxes()
{
    int ret = 0;
	if (ui->checkPaVer->isChecked() == true)
		ret |= SRV_PAVER;
	if (ui->checkTravel->isChecked() == true)
		ret |= SRV_TRV;
	if (ui->checkPaHor->isChecked() == true)
		ret |= SRV_PAHOR;
	if (ui->checkRaVer->isChecked() == true)
		ret |= SRV_RAVER;
	if (ui->checkRaHor->isChecked() == true)
		ret |= SRV_RAHOR;
	if (ui->checkOther->isChecked() == true)
		ret |= SRV_EXT;
    return ret;
}

void FormActInterp::SetAxes(int axes)
{
	// 正臂上下轴
	ui->checkPaVer->setChecked((axes & SRV_PAVER) != 0);
	// 横行轴
	ui->checkTravel->setChecked((axes & SRV_TRV) != 0);
	// 正臂引拔轴
	ui->checkPaHor->setChecked((axes & SRV_PAHOR) != 0);
	// 副臂上下轴
	ui->checkRaVer->setChecked((axes & SRV_RAVER) != 0);
	// 副臂引拔轴
	ui->checkRaHor->setChecked((axes & SRV_RAHOR) != 0);
	// 扩展轴
	ui->checkOther->setChecked(((axes & SRV_EXT) != 0));
	// 更新界面显示状态
	UpdateWidgetState();
}

int FormActInterp::GetX()
{
    if (m_x_type==POS_TYPE_POINT)
        return m_x_pos;
    if (m_x_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_x_pos);
    return 0;
}

void FormActInterp::SetX(int pos, int type)
{
    m_x_type = type;
    m_x_pos = pos;
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
        ui->BoxPaHor->setText(QString::number((double)m_x_pos / 100.00) + "mm");
        break;
    case POS_TYPE_VAR:
        ui->BoxPaHor->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_x_pos));
        break;
    }
}

int FormActInterp::GetY()
{
    if (m_y_type==POS_TYPE_POINT)
        return m_y_pos;
    if (m_y_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_y_pos);
    return 0;
}

void FormActInterp::SetY(int pos, int type)
{
    m_y_type = type;
    m_y_pos = pos;
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
        ui->BoxPaVer->setText(QString::number((double)m_y_pos / 100.00) + "mm");
        break;
    case POS_TYPE_VAR:
        ui->BoxPaVer->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_y_pos));
        break;
    }
}

int FormActInterp::GetZ()
{
    if (m_z_type==POS_TYPE_POINT)
        return m_z_pos;
    if (m_z_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_z_pos);
    return 0;
}

void FormActInterp::SetZ(int pos, int type)
{
    m_z_type = type;
    m_z_pos = pos;
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
        ui->BoxTrv->setText(QString::number((double)m_z_pos / 100.00) + "mm");
        break;
    case POS_TYPE_VAR:
        ui->BoxTrv->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_z_pos));
        break;
    }
}

int FormActInterp::GetA()
{
    if (m_a_type==POS_TYPE_POINT)
        return m_a_pos;
    if (m_a_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_a_pos);
    return 0;
}

void FormActInterp::SetA(int pos, int type)
{
	m_a_type = type;
    m_a_pos = pos;
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
        ui->BoxRaVer->setText(QString::number((double)m_a_pos / 100.00) + "mm");
        break;
    case POS_TYPE_VAR:
        ui->BoxRaVer->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_a_pos));
		break;
	}
}

int FormActInterp::GetB()
{
    if (m_b_type==POS_TYPE_POINT)
        return m_b_pos;
    if (m_b_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_b_pos);
    return 0;
}

void FormActInterp::SetB(int pos, int type)
{
	m_b_type = type;
    m_b_pos = pos;
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
        ui->BoxRaHor->setText(QString::number((double)m_b_pos / 100.00) + "mm");
        break;
    case POS_TYPE_VAR:
        ui->BoxRaHor->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_b_pos));
		break;
	}
}

int FormActInterp::GetC()
{
    if (m_c_type==POS_TYPE_POINT)
        return m_c_pos;
    if (m_c_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_c_pos);
    return 0;
}

void FormActInterp::SetC(int pos, int type)
{
	m_c_type = type;
    m_c_pos = pos;
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
        ui->BoxOther->setText(QString::number((double)m_c_pos / 100.00) + "mm");
        break;
    case POS_TYPE_VAR:
        ui->BoxOther->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_c_pos));
		break;
	}
}

void FormActInterp::UpdateWidgetState(void)
{
	ui->BoxPaVer->setEnabled(ui->checkPaVer->isChecked());
	ui->BoxTrv->setEnabled(ui->checkTravel->isChecked());
    if (!CMBProtocol::GetPaHorNotUse())
        ui->BoxPaHor->setEnabled(ui->checkPaHor->isChecked());
    else
        ui->BoxPaHor->setEnabled(false);
    if (CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0))
		ui->BoxRaHor->setEnabled(ui->checkRaHor->isChecked());
	else
		ui->BoxRaHor->setEnabled(false);
    if (CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0))
        ui->BoxRaVer->setEnabled(ui->checkRaVer->isChecked());
    else
        ui->BoxRaVer->setEnabled(false);
    if (CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0))
		ui->BoxOther->setEnabled(ui->checkOther->isChecked());
	else
		ui->BoxOther->setEnabled(false);
	if(CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
	{
		// 手动模式
		ui->checkPaVer->setEnabled(true);
		ui->checkTravel->setEnabled(true);
        if (!CMBProtocol::GetPaHorNotUse())
        {
            ui->checkPaHor->setEnabled(true);
        }
        else
        {
            ui->checkPaHor->setEnabled(false);
            ui->checkPaHor->setChecked(false);
        }
        if (CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0))
		{
			ui->checkRaHor->setEnabled(true);
		}
		else
		{
			ui->checkRaHor->setEnabled(false);
			ui->checkRaHor->setChecked(false);
		}
        if (CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0))
        {
            ui->checkRaVer->setEnabled(true);
        }
        else
        {
            ui->checkRaVer->setEnabled(false);
            ui->checkRaVer->setChecked(false);
        }
        if (CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0))
		{
			ui->checkOther->setEnabled(true);
		}
		else
		{
			ui->checkOther->setEnabled(false);
			ui->checkOther->setChecked(false);
		}
	}
	else
	{
		// 自动模式
		ui->checkPaHor->setEnabled(false);
		ui->checkPaVer->setEnabled(false);
		ui->checkTravel->setEnabled(false);
		ui->checkRaHor->setEnabled(false);
		ui->checkRaVer->setEnabled(false);
		ui->checkOther->setEnabled(false);
	}
}

void FormActInterp::checkClick(void)
{
	UpdateWidgetState();
}

// 输入伺服速度信号槽
void FormActInterp::inputSpeed(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxSpeed->minimum(), ui->BoxSpeed->maximum()) == QDialog::Accepted)
		ui->BoxSpeed->setValue(value);
}

// 输入正臂引拔位置信号槽
void FormActInterp::inputPaHor(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
    {
        if (m_x_type!=POS_TYPE_POINT) return;
        type = m_x_type;
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4) || (!CMBProtocol::GetRhorSrvUse()))
        {
            if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
                return;
        }
        else
        {
            if (numberPad.DoFormPos(value, 0.00, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
                return;
        }
    }
    else
    {
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4) || (!CMBProtocol::GetRhorSrvUse()))
        {
            if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
                return;

        }
        else
        {
            if (numberPad.DoForm(type, value, 0.00, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
                return;
        }
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
            ui->BoxPaHor->setText(QString::number((double)m_x_pos / 100.00) + "mm");
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
            ui->BoxPaHor->setText(QString::number((double)m_x_pos / 100.00) + "mm");
		}
	}
}
// 同步正臂引拔位置信号槽
void FormActInterp::syncPaHor(void)
{
    m_x_pos = CMBProtocol::GetPaHorPos();
    ui->BoxPaHor->setText(QString::number((double)m_x_pos / 100.00) + "mm");
}
// 输入正臂上下位置信号槽
void FormActInterp::inputPaVer(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
    {
        if (m_y_type!=POS_TYPE_POINT) return;
        type = m_y_type;
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
            return;
	}
    else
    {
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
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
            ui->BoxPaVer->setText(QString::number((double)m_y_pos / 100.00) + "mm");
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
            ui->BoxPaVer->setText(QString::number((double)m_y_pos / 100.00) + "mm");
		}
	}
}
// 同步正臂上下位置信号槽
void FormActInterp::syncPaVer(void)
{
    m_y_pos = CMBProtocol::GetPaVerPos();
    ui->BoxPaVer->setText(QString::number((double)m_y_pos / 100.00) + "mm");
}
// 输入横行位置信号槽
void FormActInterp::inputTravel(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
	if (CMBProtocol::GetTemplateUse())
	{
        if (m_z_type!=POS_TYPE_POINT) return;
        type = m_z_type;
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetTravLen() / 100.00) != QDialog::Accepted)
            return;
	}
	else
	{
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetTravLen() / 100.00) != QDialog::Accepted)
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
            ui->BoxTrv->setText(QString::number((double)m_z_pos / 100.00) + "mm");
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
            ui->BoxTrv->setText(QString::number((double)m_z_pos / 100.00) + "mm");
        }
    }
}
// 同步横行位置信号槽
void FormActInterp::syncTravel(void)
{
    m_z_pos = CMBProtocol::GetTravelPos();
    ui->BoxTrv->setText(QString::number((double)m_z_pos / 100.00) + "mm");
}
// 输入副臂引拔轴位置信号槽
void FormActInterp::inputRaHor(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
	if (CMBProtocol::GetTemplateUse())
	{
		if (m_b_type!=POS_TYPE_POINT) return;
		type = m_b_type;
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        {
            if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetHorInt() / 100.00) != QDialog::Accepted)
                return;
        }
        else
        {
            if (numberPad.DoFormPos(value, 0.00, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
                return;
        }
	}
	else
	{
        if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
        {
            if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorInt() / 100.00) != QDialog::Accepted)
                return;
        }
        else
        {
            if (numberPad.DoForm(type, value, 0.00, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
                return;
        }
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
            ui->BoxRaHor->setText(QString::number((double)m_b_pos / 100.00) + "mm");
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
            ui->BoxRaHor->setText(QString::number((double)m_b_pos / 100.00) + "mm");
        }
    }
}
// 同步副臂引拔轴位置信号槽
void FormActInterp::syncRaHor(void)
{
    m_b_pos = CMBProtocol::GetRaHorPos();
    ui->BoxRaHor->setText(QString::number((double)m_b_pos / 100.00) + "mm");
}
// 输入副臂上下轴位置信号槽
void FormActInterp::inputRaVer(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
	if (CMBProtocol::GetTemplateUse())
	{
		if (m_a_type!=POS_TYPE_POINT) return;
		type = m_a_type;
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetRaVerLen() / 100.00) != QDialog::Accepted)
            return;
	}
	else
	{
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetRaVerLen() / 100.00) != QDialog::Accepted)
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
            ui->BoxRaVer->setText(QString::number((double)m_a_pos / 100.00) + "mm");
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
            ui->BoxRaVer->setText(QString::number((double)m_a_pos / 100.00) + "mm");
        }
    }
}
// 同步副臂上下轴位置信号槽
void FormActInterp::syncRaVer(void)
{
    m_a_pos = CMBProtocol::GetRaVerPos();
    ui->BoxRaVer->setText(QString::number((double)m_a_pos / 100.00) + "mm");
}
// 输入扩展轴位置信号槽
void FormActInterp::inputOther(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
	if (CMBProtocol::GetTemplateUse())
	{
		if (m_c_type!=POS_TYPE_POINT) return;
		type = m_c_type;
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetExteLen() / 100.00) != QDialog::Accepted)
            return;
	}
	else
	{
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetExteLen() / 100.00) != QDialog::Accepted)
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
            ui->BoxOther->setText(QString::number((double)m_c_pos / 100.00) + "mm");
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
            ui->BoxOther->setText(QString::number((double)m_c_pos / 100.00) + "mm");
	}
	}
}
// 同步扩展轴位置信号槽
void FormActInterp::syncOther(void)
{
    m_c_pos = CMBProtocol::GetExtendPos();
    ui->BoxOther->setText(QString::number((double)m_c_pos / 100.00) + "mm");
}
void FormActInterp::setVisible(bool visible)
{
	if (visible)
	{
        ui->checkPaHor->setEnabled(!CMBProtocol::GetTemplateUse()  && (!CMBProtocol::GetPaHorNotUse()));
		ui->checkPaVer->setEnabled(!CMBProtocol::GetTemplateUse());
		ui->checkTravel->setEnabled(!CMBProtocol::GetTemplateUse());
        ui->checkRaHor->setEnabled((!CMBProtocol::GetTemplateUse()) && CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
        ui->checkRaVer->setEnabled((!CMBProtocol::GetTemplateUse()) && CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
        ui->checkOther->setEnabled((!CMBProtocol::GetTemplateUse()) && CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
		if ((m_x_type == POS_TYPE_CAT) || (m_x_type ==POS_TYPE_REL) || (m_x_type ==POS_TYPE_WAIT))
		{
			ui->BoxPaHor->setEnabled(!CMBProtocol::GetTemplateUse());
		}
		if ((m_y_type == POS_TYPE_CAT) || (m_y_type ==POS_TYPE_REL) || (m_y_type ==POS_TYPE_WAIT))
		{
			ui->BoxPaVer->setEnabled(!CMBProtocol::GetTemplateUse());
		}
		if ((m_z_type == POS_TYPE_CAT) || (m_z_type ==POS_TYPE_REL) || (m_z_type ==POS_TYPE_WAIT))
		{
			ui->BoxTrv->setEnabled(!CMBProtocol::GetTemplateUse());
		}
		if ((m_b_type == POS_TYPE_CAT) || (m_b_type ==POS_TYPE_REL) || (m_b_type ==POS_TYPE_WAIT))
		{
			ui->BoxRaHor->setEnabled(!CMBProtocol::GetTemplateUse());
		}
		if ((m_a_type == POS_TYPE_CAT) || (m_a_type ==POS_TYPE_REL) || (m_a_type ==POS_TYPE_WAIT))
		{
			ui->BoxRaVer->setEnabled(!CMBProtocol::GetTemplateUse());
		}
		if ((m_c_type == POS_TYPE_CAT) || (m_c_type ==POS_TYPE_REL) || (m_c_type ==POS_TYPE_WAIT))
		{
			ui->BoxOther->setEnabled(!CMBProtocol::GetTemplateUse());
		}
	}
	QWidget::setVisible(visible);
}
