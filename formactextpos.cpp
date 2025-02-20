#include <QButtonGroup>
#include "dialognumberpad.h"
#include "formactextpos.h"
#include "cmbprotocol.h"
#include "ui_formactextpos.h"
#include "servoalias.h"
#include "xmessagebox.h"
#include "xstringresource.h"

FormActExtPos::FormActExtPos(QWidget *parent) : QWidget(parent), ui(new Ui::FormActExtPos)
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

	// 组织伺服轴选择按钮
	pAxesBtn = new QButtonGroup;
	pAxesBtn->addButton(ui->radioPaVer, SRV_PAVER);
	pAxesBtn->addButton(ui->radioTravel, SRV_TRV);
	pAxesBtn->addButton(ui->radioPaHor, SRV_PAHOR);
	pAxesBtn->addButton(ui->radioRaVer, SRV_RAVER);
	pAxesBtn->addButton(ui->radioRaHor, SRV_RAHOR);
	pAxesBtn->addButton(ui->radioOther, SRV_EXT);
	// 连接信号槽
	connect(pAxesBtn, SIGNAL(buttonClicked(int)), this, SLOT(AxesClick(int)));
#if TIME_BASE == 10
    ui->BoxDelay->setDecimals(2);
    ui->BoxDelay->setMaximum(9.99);
#else
    ui->BoxDelay->setDecimals(1);
    ui->BoxDelay->setMaximum(99.9);
#endif

#if (FACTORY != FA_XIONGCHUAN)			// 熊创（显示加速度和加加速调整框）
    ui->labelAcc->setVisible(false);
    ui->BoxAcc->setVisible(false);
    ui->labelJerk->setVisible(false);
    ui->BoxJerk->setVisible(false);
#endif
}

FormActExtPos::~FormActExtPos()
{
	delete ui;
	delete pAxesBtn;
}

void FormActExtPos::changeEvent(QEvent *e)
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

void FormActExtPos::retranslateUi(void)
{
	ui->radioPaHor->setText(GetServoName(AXIS_IDX_PHOR));
	ui->radioPaVer->setText(GetServoName(AXIS_IDX_PVER));
	ui->radioTravel->setText(GetServoName(AXIS_IDX_TRV));
	ui->radioRaHor->setText(GetServoName(AXIS_IDX_RHOR));
	ui->radioRaVer->setText(GetServoName(AXIS_IDX_RVER));
	ui->radioOther->setText(GetServoName(AXIS_IDX_EXT));
}

void FormActExtPos::SetType(quint8 type)
{
    if (type == SERVO_POS_REL)
        ui->checkOffset->setChecked(true);
    else
        ui->checkOffset->setChecked(false);
    UpdateWidgetState();
}

int FormActExtPos::GetType(void)
{
    if (ui->checkOffset->isChecked() == true)
        return SERVO_POS_REL;
    else
        return SERVO_POS_ABS;
}

quint32 FormActExtPos::GetSpeed()
{
	return ui->BoxSpeed->value();
}

void FormActExtPos::SetSpeed(int speed)
{
	ui->BoxSpeed->setValue((double)speed);
}

int FormActExtPos::GetAxes()
{
	return pAxesBtn->checkedId();
}

void FormActExtPos::SetAxes(int axes)
{
	if (pAxesBtn->button(axes) == 0)
		return;
	pAxesBtn->button(axes)->setChecked(true);
    UpdateWidgetState();
}

void FormActExtPos::AxesClick(int axes)
{
    UpdateWidgetState();
}

int FormActExtPos::GetX()
{
    if (m_x_type==POS_TYPE_POINT)
        return m_x_pos;
    if (m_x_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_x_pos);
    return 0;
}

void FormActExtPos::SetX(int pos, int type)
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

int FormActExtPos::GetY()
{
    if (m_y_type==POS_TYPE_POINT)
        return m_y_pos;
    if (m_y_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_y_pos);
    return 0;
}

void FormActExtPos::SetY(int pos, int type)
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

int FormActExtPos::GetZ()
{
    if (m_z_type==POS_TYPE_POINT)
        return m_z_pos;
    if (m_z_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_z_pos);
    return 0;
}

void FormActExtPos::SetZ(int pos, int type)
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

int FormActExtPos::GetA()
{
    if (m_a_type==POS_TYPE_POINT)
        return m_a_pos;
    if (m_a_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_a_pos);
    return 0;
}

void FormActExtPos::SetA(int pos, int type)
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

int FormActExtPos::GetB()
{
    if (m_b_type==POS_TYPE_POINT)
        return m_b_pos;
    if (m_b_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_b_pos);
    return 0;
}

void FormActExtPos::SetB(int pos, int type)
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

int FormActExtPos::GetC()
{
    if (m_c_type==POS_TYPE_POINT)
        return m_c_pos;
    if (m_c_type==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_c_pos);
    return 0;
}

void FormActExtPos::SetC(int pos, int type)
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

// 输入伺服速度槽
void FormActExtPos::inputSpeed(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->BoxSpeed->minimum(), ui->BoxSpeed->maximum()) == QDialog::Accepted)
        ui->BoxSpeed->setValue(value);
}

// 输入正臂引拔位置信号槽
void FormActExtPos::inputPaHor(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
    {
        if (m_x_type!=POS_TYPE_POINT) return;
        type = m_x_type;
        if (ui->checkOffset->isChecked() == true)
        {
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
        }
        else
        {
#if PENDANT_PROTOCOL
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
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
            return;
#endif
    }
    }
    else
    {
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
			if (type!=POS_TYPE_POINT)
				ui->checkOffset->setChecked(false);
		}
    else
    {
#if PENDANT_PROTOCOL
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
#else
        if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
            return;
#endif
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
void FormActExtPos::syncPaHor(void)
{
    m_x_pos = CMBProtocol::GetPaHorPos();
    ui->BoxPaHor->setText(QString::number((double)m_x_pos / 100.00) + "mm");
}
// 输入正臂上下位置信号槽
void FormActExtPos::inputPaVer(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
	{
		if (m_y_type!=POS_TYPE_POINT) return;
		type = m_y_type;
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
		}
		else
		{
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	}
	else
	{
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
			if (type!=POS_TYPE_POINT)
				ui->checkOffset->setChecked(false);
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
void FormActExtPos::syncPaVer(void)
{
    m_y_pos = CMBProtocol::GetPaVerPos();
    ui->BoxPaVer->setText(QString::number((double)m_y_pos / 100.00) + "mm");
}
// 输入横行位置信号槽
void FormActExtPos::inputTravel(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
	{
		if (m_z_type!=POS_TYPE_POINT) return;
		type = m_z_type;
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
		}
		else
		{
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetTravLen()  / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE  / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	}
	else
	{
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
			if (type!=POS_TYPE_POINT)
				ui->checkOffset->setChecked(false);
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
void FormActExtPos::syncTravel(void)
{
    m_z_pos = CMBProtocol::GetTravelPos();
    ui->BoxTrv->setText(QString::number((double)m_z_pos / 100.00) + "mm");
}
// 输入副臂引拔位置信号槽
void FormActExtPos::inputRaHor(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
	{
		if (m_b_type!=POS_TYPE_POINT) return;
		type = m_b_type;
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
		}
		else
		{
#if PENDANT_PROTOCOL
        // 不使用的时候按键disenable, 情况可以排除，
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
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
            return;
#endif
	}
	}
	else
	{
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
			if (type!=POS_TYPE_POINT)
				ui->checkOffset->setChecked(false);
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
                if (numberPad.DoForm(type, value, 0.00, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
                    return;
            }
#else
            if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
                return;
#endif
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
// 同步副臂引拔位置信号槽
void FormActExtPos::syncRaHor(void)
{
    m_b_pos = CMBProtocol::GetRaHorPos();
    ui->BoxRaHor->setText(QString::number((double)m_b_pos / 100.00) + "mm");
}
// 输入副臂上下位置信号槽
void FormActExtPos::inputRaVer(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
	{
		if (m_a_type!=POS_TYPE_POINT) return;
		type = m_a_type;
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
		}
		else
		{
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetRaVerLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	}
	else
	{
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
			if (type!=POS_TYPE_POINT)
				ui->checkOffset->setChecked(false);
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
// 同步副臂引拔位置信号槽
void FormActExtPos::syncRaVer(void)
{
    m_a_pos = CMBProtocol::GetRaVerPos();
    ui->BoxRaVer->setText(QString::number((double)m_a_pos / 100.00) + "mm");
}
// 输入扩展位置信号槽
void FormActExtPos::inputOther(void)
{
    int type = POS_TYPE_POINT;
	DialogNumberPad numberPad;
	double value;
    if (CMBProtocol::GetTemplateUse())
	{
		if (m_c_type!=POS_TYPE_POINT) return;
		type = m_c_type;
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
		}
		else
		{
#if PENDANT_PROTOCOL
        if (numberPad.DoFormPos(value, 0.00, CMBProtocol::GetExteLen() / 100.00) != QDialog::Accepted)
#else
        if (numberPad.DoFormPos(value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
            return;
	}
	}
	else
	{
		if (ui->checkOffset->isChecked() == true)
		{
            if (numberPad.DoFormDouble(value, -3000.00, 3000.00) != QDialog::Accepted)
				return;
			if (type!=POS_TYPE_POINT)
				ui->checkOffset->setChecked(false);
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
// 同步扩展位置信号槽
void FormActExtPos::syncOther(void)
{
    m_c_pos = CMBProtocol::GetExtendPos();
    ui->BoxOther->setText(QString::number((double)m_c_pos / 100.00) + "mm");
}
void FormActExtPos::UpdateWidgetState()
{
    if (CMBProtocol::GetTemplateUse())
    {
//        if (visible)
        {
            ui->checkAdvFinish->setEnabled(false);
            ui->checkAdvDec->setEnabled(false);
            ui->checkOffset->setEnabled(false);
            ui->radioPaHor->setEnabled((false) && (!CMBProtocol::GetPaHorNotUse()));
            ui->radioPaVer->setEnabled(false);
            ui->radioRaHor->setEnabled((false) && CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
            ui->radioRaVer->setEnabled((false) && CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
            ui->radioTravel->setEnabled(false);
            ui->radioOther->setEnabled((false) && CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
            if ((m_x_type == POS_TYPE_CAT) || (m_x_type ==POS_TYPE_REL) || (m_x_type ==POS_TYPE_WAIT))
            {
                ui->BoxPaHor->setEnabled(false);
            }
            if ((m_y_type == POS_TYPE_CAT) || (m_y_type ==POS_TYPE_REL) || (m_y_type ==POS_TYPE_WAIT))
            {
                ui->BoxPaVer->setEnabled(false);
            }
            if ((m_z_type == POS_TYPE_CAT) || (m_z_type ==POS_TYPE_REL) || (m_z_type ==POS_TYPE_WAIT))
            {
                ui->BoxTrv->setEnabled(false);
            }
            if ((m_b_type == POS_TYPE_CAT) || (m_b_type ==POS_TYPE_REL) || (m_b_type ==POS_TYPE_WAIT))
            {
                ui->BoxRaHor->setEnabled(false);
            }
            if ((m_a_type == POS_TYPE_CAT) || (m_a_type ==POS_TYPE_REL) || (m_a_type ==POS_TYPE_WAIT))
            {
                ui->BoxRaVer->setEnabled(false);
            }
            if ((m_c_type == POS_TYPE_CAT) || (m_c_type ==POS_TYPE_REL) || (m_c_type ==POS_TYPE_WAIT))
            {
                ui->BoxOther->setEnabled(false);
            }
        }
    }
    else
    {
        ui->BoxPaVer->setEnabled(ui->radioPaVer->isChecked());
        ui->BoxTrv->setEnabled(ui->radioTravel->isChecked());
        if (!CMBProtocol::GetPaHorNotUse())
            ui->BoxPaHor->setEnabled(ui->radioPaHor->isChecked());
        else
            ui->BoxPaHor->setEnabled(false);
        if (CMBProtocol::GetRhorSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_B) & 1) == 0))
            ui->BoxRaHor->setEnabled(ui->radioRaHor->isChecked());
        else
            ui->BoxRaHor->setEnabled(false);
        if (CMBProtocol::GetRverSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_A) & 1) == 0))
            ui->BoxRaVer->setEnabled(ui->radioRaVer->isChecked());
        else
            ui->BoxRaVer->setEnabled(false);
        if (CMBProtocol::GetExtSrvUse() && (((CMBProtocol::GetServoNotExist() >> AXES_IDX_C) & 1) == 0))
            ui->BoxOther->setEnabled(ui->radioOther->isChecked());
        else

            ui->BoxOther->setEnabled(false);
        if(CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
        {
            // 手动模式
            ui->checkOffset->setEnabled(true);
            ui->radioPaVer->setEnabled(true);
            ui->radioTravel->setEnabled(true);
            ui->checkAdvFinish->setEnabled(true);
            ui->checkAdvDec->setEnabled(true);
            ui->BtnExtSync->setEnabled(true);
            ui->BtnPaHorSync->setEnabled(true);
            ui->BtnPaVerSync->setEnabled(true);
            ui->BtnRaHorSync->setEnabled(true);
            ui->BtnRaVerSync->setEnabled(true);
            ui->BtnTrvSync->setEnabled(true);
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
            ui->checkOffset->setEnabled(false);
            ui->radioPaHor->setEnabled(false);
            ui->radioPaVer->setEnabled(false);
            ui->radioTravel->setEnabled(false);
            ui->radioRaHor->setEnabled(false);
            ui->radioRaVer->setEnabled(false);
            ui->radioOther->setEnabled(false);
            ui->checkAdvFinish->setEnabled(false);
            ui->checkAdvDec->setEnabled(false);
            ui->BtnExtSync->setEnabled(false);
            ui->BtnPaHorSync->setEnabled(false);
            ui->BtnPaVerSync->setEnabled(false);
            ui->BtnRaHorSync->setEnabled(false);
            ui->BtnRaVerSync->setEnabled(false);
            ui->BtnTrvSync->setEnabled(false);
        }

    }
}
// 输入延时参数信号槽
void FormActExtPos::inputDelay(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxDelay->minimum(), ui->BoxDelay->maximum()) == QDialog::Accepted)
        ui->BoxDelay->setValue(value);
}
void FormActExtPos::inputDeC(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxDec->minimum(), ui->BoxDec->maximum()) == QDialog::Accepted)
        ui->BoxDec->setValue(value);
}
void FormActExtPos::inputAcc(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxAcc->minimum(), ui->BoxAcc->maximum()) == QDialog::Accepted)
        ui->BoxAcc->setValue(value);
}
void FormActExtPos::inputJerk(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxJerk->minimum(), ui->BoxJerk->maximum()) == QDialog::Accepted)
        ui->BoxJerk->setValue(value);
}
void FormActExtPos::inputAdvDis(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxAdvDis->minimum(), ui->BoxAdvDis->maximum()) == QDialog::Accepted)
        ui->BoxAdvDis->setValue(value);
}
void FormActExtPos::inputEndDis(void)
{
    DialogNumberPad numberPad;
    double value;
    if (numberPad.DoFormDouble(value, ui->BoxEndDis->minimum(), ui->BoxEndDis->maximum()) == QDialog::Accepted)
        ui->BoxEndDis->setValue(value);
}
void FormActExtPos::SetDelay(int delay)
{
    ui->BoxDelay->setValue((double)delay / (1000.0/TIME_BASE));
}

int FormActExtPos::GetDelay()
{
    return qRound(ui->BoxDelay->value() * (1000.0/TIME_BASE));
}

int FormActExtPos::GetAdvDec()//提前变速
{
    return ui->checkAdvDec->isChecked();
}

int FormActExtPos::GetAdvSpeed()//变速速度
{
    return ui->BoxDec->value();
}
int FormActExtPos::GetAccSpeed()
{
    return ui->BoxAcc->value();
}
int FormActExtPos::GetJerkSpeed()
{
    return ui->BoxJerk->value();
}

int FormActExtPos::GetAdvFinish()//提前结束
{
    return ui->checkAdvFinish->isChecked();
}

int FormActExtPos::GetAdvDis()//提前距离
{
    return qRound(ui->BoxAdvDis->value() * 100.00);
}
int FormActExtPos::GetEndDis()//提前距离
{
    return qRound(ui->BoxEndDis->value() * 100.00);
}

void FormActExtPos::SetAdvDec(int dec)//提前变速
{
    return ui->checkAdvDec->setChecked(dec);
}

void FormActExtPos::SetAdvSpeed(int speed)//变速速度
{
    ui->BoxDec->setValue((double)speed);
}
void FormActExtPos::SetAccSpeed(int speed)
{
    ui->BoxAcc->setValue((double)speed);
}
void FormActExtPos::SetJerkSpeed(int speed)
{
    ui->BoxJerk->setValue((double)speed);
}

void FormActExtPos::SetAdvFinish(int finish)//提前结束
{
    return ui->checkAdvFinish->setChecked(finish);
}
void FormActExtPos::SetAdvDis(int dist)//提前距离
{
    ui->BoxAdvDis->setValue((double)dist / 100.00);
}
void FormActExtPos::SetEndDis(int dist)//提前距离
{
    ui->BoxEndDis->setValue((double)dist / 100.00);
}

