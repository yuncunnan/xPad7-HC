#include <QSettings>
#include <QButtonGroup>
#include <QDesktopWidget>
#include <QKeyEvent>
#include "cmbprotocol.h"
#include "SafeSwitch.h"
//#include "xKeypad.h"
#include "Buzzer.h"
#include "indicatorled.h"
#include "xstringresource.h"
#include "xsystemlog.h"
#include "xmessagebox.h"
#include "dialogservocontrol.h"
#include "ui_dialogservocontrol.h"
#include "driver/xioport.h"
#include "dialognumberpad.h"
#include "servoalias.h"
#include "HardwareInterface.h"
#include <QDebug>

#define SRV_CTRLPG_PAHOR		0
#define SRV_CTRLPG_PAVER		1
#define SRV_CTRLPG_TRV          2
#define SRV_CTRLPG_RAVER		3
#define SRV_CTRLPG_RAHOR		4
#define SRV_CTRLPG_EXT          5

DialogServoControl::DialogServoControl(CMBProtocol *modbus, QWidget *parent) : QDialog(parent), ui(new Ui::DialogServoControl)
{
	ui->setupUi(this);
    retranslateUi();
    pModbus = modbus;
	CurServoIdx = SRV_PAHOR;
#if defined(Q_WS_QWS)
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
	// 组织伺服轴选择按钮组
	pSrvAxies = new QButtonGroup;
	pSrvAxies->addButton(ui->radioPaHor, SRV_CTRLPG_PAHOR);
	pSrvAxies->addButton(ui->radioPaVer, SRV_CTRLPG_PAVER);
	pSrvAxies->addButton(ui->radioTrv, SRV_CTRLPG_TRV);
	pSrvAxies->addButton(ui->radioRaHor, SRV_CTRLPG_RAHOR);
	pSrvAxies->addButton(ui->radioRaVer, SRV_CTRLPG_RAVER);
	pSrvAxies->addButton(ui->radioExt, SRV_CTRLPG_EXT);
    keyVector.clear();
    keyVector << ENCODER_CW << ENCODER_CCW;
    installEventFilter(this);
    // 微调按钮隐藏
    ui->BtnShiftMoveCcw->setVisible(true);
    ui->BtnShiftMoveCw->setVisible(true);
    connect(ui->BtnMoveCcw, SIGNAL(pressed()), this, SLOT(SvMoveCcw()));
    connect(ui->BtnMoveCw, SIGNAL(pressed()), this, SLOT(SvMoveCw()));
    connect(ui->BtnMoveCcw, SIGNAL(released()), this, SLOT(SvMoveCcwStop()));
    connect(ui->BtnMoveCw, SIGNAL(released()), this, SLOT(SvMoveCwStop()));
    // 连接信号槽
    m_havesendservocmd = false;
    m_ptimer = new QTimer();
    connect(pModbus, SIGNAL(signal_InputChange()), this, SLOT(SafeInputChg()));
    connect(m_ptimer,SIGNAL(timeout()),this,SLOT(StopTimer()));
    ui->BtnRaHorBegin->setVisible(false);
    ui->BtnRaHorEnd->setVisible(false);
    ui->BtnPaHorBegin->setVisible(false);
    ui->BtnPaHorEnd->setVisible(false);
    ui->BtnPaVerWait->setVisible(false);
    ui->BtnPaVerCat->setVisible(false);
    ui->BtnRaVerWait->setVisible(false);
    ui->BtnRaVerCat->setVisible(false);
}

void DialogServoControl::StopTimer(void)
{
    quint8 srvMap;
    quint32 distance = 0;
	if (ui->BtnMoveCcw->isDown()||ui->BtnMoveCw->isDown())
    {
        if (!m_havesendservocmd)
        {
            switch (pSrvAxies->checkedId())
            {
            case AXIS_IDX_PHOR:
                srvMap = SRV_PAHOR;
                if (ui->BtnMoveCw->isDown())
                {
                    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
                    {
                    distance = disHomP_RLen;
                    }
                    else
                    {
                        if (pModbus->GetRhorSrvUse())
                        {
                            distance = disHomP_RLen - MinDisP_RLen;
                        }
                        else
                        {
                            distance = disHomP_RLen;
                        }
                    }
                }
                break;
            case AXIS_IDX_RHOR:
                srvMap = SRV_RAHOR;
                if (ui->BtnMoveCw->isDown())
                {
                    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
                    {
                    distance = MinDisP_RLen;
                    }
                    else
                    {
                        if (pModbus->GetRhorSrvUse())
                        {
                            distance = disHomP_RLen - MinDisP_RLen;
                        }
                        else
                        {
                    distance = MinDisP_RLen;
                        }
                    }
                }
                break;
            case AXIS_IDX_PVER:
                srvMap = SRV_PAVER;
                if (ui->BtnMoveCw->isDown())
                    distance = PverLen;
                break;
            case AXIS_IDX_RVER:
                srvMap = SRV_RAVER;
                if (ui->BtnMoveCw->isDown())
                    distance = RverLen;
                break;
            case AXIS_IDX_TRV:
                srvMap = SRV_TRV;
                if (ui->BtnMoveCw->isDown())
                    distance = TrvLen;
                break;
            case AXIS_IDX_EXT:
                srvMap = SRV_EXT;
                if (ui->BtnMoveCw->isDown())
                    distance = ExtLen;
                break;
            default:
				return ;
            }
            if (ServoSetup == false)
            {
				if (ui->BtnMoveCw->isDown())
					pModbus->ManualPos(ui->spinBoxSpeed->value(), srvMap, MAX_DISTANCE, SERVO_MODE_SAFE);
                else
					pModbus->ManualPos(ui->spinBoxSpeed->value(), srvMap, 0, SERVO_MODE_SAFE);
                posChanged = true;
            }
            else
            {
				pModbus->ManualPos(ui->spinBoxSpeed->value(), srvMap, distance, SERVO_MODE_FORCE);
                posChanged = true;
            }
            m_ptimer->start(10);
            m_havesendservocmd = true;
		}
    }
    else
    {
        m_ptimer->stop();
        if (m_havesendservocmd)
            pModbus->SetRunState(RUN_STATE_PAUSE);
	}
}

DialogServoControl::~DialogServoControl()
{
	delete ui;
	delete pSrvAxies;
    delete m_ptimer;
}

void DialogServoControl::changeEvent(QEvent *e)
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
void DialogServoControl::retranslateUi(void)
{
    ui->radioPaHor->setText(GetServoName(AXIS_IDX_PHOR));
    ui->radioPaVer->setText(GetServoName(AXIS_IDX_PVER));
    ui->radioTrv->setText(GetServoName(AXIS_IDX_TRV));
    ui->radioRaHor->setText(GetServoName(AXIS_IDX_RHOR));
    ui->radioRaVer->setText(GetServoName(AXIS_IDX_RVER));
    ui->radioExt->setText(GetServoName(AXIS_IDX_EXT));
}

bool DialogServoControl::eventFilter(QObject *obj, QEvent *event)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyVector.contains(keyEvent->key()) == false)
        return QDialog::eventFilter(obj, event);
    if (event->type() == QEvent::KeyPress)
    {
        xBuzzer->KeyBeep();
     }
    else if (event->type() == QEvent::KeyRelease)
    {
        keyRelease(keyEvent->key());
    }
    return true;
}
// 按键弹起事件处理函数
void DialogServoControl::keyRelease(quint32 key)
{

	if (!pModbus->GetFunctions(SUB_FUN_ENCODER))
        return;
    if (!checkManual())
        return;
    quint8 relSpd = pModbus->GetSrvSpeed();
    double scale = pModbus->GetSrvScale();

    switch (key)
    {
    case ENCODER_CW:
        pModbus->CommandEncoder(pModbus->GetManualSpeed()*relSpd/100, pSrvAxies->checkedId(), qRound(scale*100.00), TRUE, ServoSetup?SERVO_MODE_FORCE:SERVO_MODE_SAFE);
        posChanged = true;
        break;
    case ENCODER_CCW:
        pModbus->CommandEncoder(pModbus->GetManualSpeed()*relSpd/100, pSrvAxies->checkedId(), qRound(scale*100.00), FALSE, ServoSetup?SERVO_MODE_FORCE:SERVO_MODE_SAFE);
        posChanged = true;
        break;
    }
}

int DialogServoControl::DoForm(uint8_t curServo, bool svSet, quint32 Pver, quint32 Rver, quint32 trv, quint32 ext, quint32 disHomP_R, quint32 MinDisP_R)
{
	int ret;
	strTitleSuffix.clear();
	if (svSet)
	{
		ui->frameTitle->setStyleSheet(QString("QFrame#frameTitle {"\
											  "background-color: transparent;"\
											  "border-image: url(:/img/widget/DialogTitleRed.png) 0 12 0 12;"\
											  "border-left: 12px transparent;"\
											  "border-right: 12px transparent; }"));
		strTitleSuffix.append(tr(" - 无安全区域限制"));
	}
	else
	{
		ui->frameTitle->setStyleSheet(QString("QFrame#frameTitle {"\
											  "background-color: transparent;"\
											  "border-image: url(:/img/widget/DialogTitle.png) 0 12 0 12;"\
											  "border-left: 12px transparent;"\
											  "border-right: 12px transparent; }"));
	}
//	ServoParameter par;
	// 得到伺服参数设置
	paHorSafeBegin = pModbus->GetPaHorSafeBegin();
	paHorSafeEnd = pModbus->GetPaHorSafeEnd();
	raHorSafeBegin = pModbus->GetRaHorSafeBegin();
	raHorSafeEnd = pModbus->GetRaHorSafeEnd();
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	trvRelPos = settings.value(XPAD_SET_TRVRELPOS, 0).toUInt();
	trvCatPos = settings.value(XPAD_SET_TRVCATPOS, 0).toUInt();
	paVerCatPos = settings.value(XPAD_SET_PAVERCAT, 0).toUInt();
	raVerCatPos = settings.value(XPAD_SET_RAVERCAT, 0).toUInt();
	paVerWaitPos = settings.value(XPAD_SET_PAVERWAIT, 0).toUInt();
	raVerWaitPos = settings.value(XPAD_SET_RAVERWAIT, 0).toUInt();
	PverLen = Pver;
	RverLen = Rver;
	TrvLen = trv;
	ExtLen = ext;
	disHomP_RLen = disHomP_R;
	MinDisP_RLen = MinDisP_R;
	// 设置当前控制的伺服轴
	switch (curServo)
	{
	case SRV_PAHOR:
		ui->radioPaHor->setChecked(true);
		break;
	case SRV_PAVER:
		ui->radioPaVer->setChecked(true);
		break;
	case SRV_TRV:
		ui->radioTrv->setChecked(true);
		break;
	case SRV_RAHOR:
		ui->radioRaHor->setChecked(true);
		break;
	case SRV_RAVER:
		ui->radioRaVer->setChecked(true);
		break;
	case SRV_EXT:
		ui->radioExt->setChecked(true);
		break;
	default:
		return QDialog::Rejected;
	}
	setCurServo();
	// 设置是否设置伺服参数标志
	ServoSetup = svSet;
	posChanged = false;
	// 初始化界面显示
    ui->LedSafePaUp->setOn(xIoPort::GetIn(SV_VAR_IN_YWPOS));
    ui->LedSafeRaUp->setOn(xIoPort::GetIn(SV_VAR_IN_AWPOS));
    if (pModbus->GetHomeInmold())
    {
        ui->LedSafeIn->setText(xStringResource::GetVarName(SV_VAR_IN_OUTMOLD));
        ui->LedSafeIn->setOn(xIoPort::GetIn(SV_VAR_IN_OUTMOLD) && (!pModbus->GetOutmoldSignalNotuse()));
//        ui->LedSafeOut->setOn(xIoPort::GetIn(SV_VAR_IN_ZHOME) && (!pModbus->GetInmoldSignalNotuse()));
    }
    else
    {
        ui->LedSafeIn->setText(xStringResource::GetVarName(SV_VAR_IN_INMOLD));
        ui->LedSafeIn->setOn(xIoPort::GetIn(SV_VAR_IN_INMOLD) && (!pModbus->GetInmoldSignalNotuse()));
//        ui->LedSafeOut->setOn(xIoPort::GetIn(SV_VAR_IN_ZHOME) && (!pModbus->GetOutmoldSignalNotuse()));
    }
    if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        ui->LedSafeIn->setVisible(false);
    }
    ui->LedSafeOut->setOn(xIoPort::GetIn(SV_VAR_IN_ZHOME));
    ui->LedSafePaUp->setText(GetServoName(AXIS_IDX_PVER) + tr("轴原点"));
    ui->LedSafeRaUp->setText(GetServoName(AXIS_IDX_RVER) + tr("轴原点"));
    ui->LedSafeOut->setText(GetServoName(AXIS_IDX_TRV) + tr("轴原点"));

    ui->radioPaHor->setEnabled(!pModbus->GetPaHorNotUse());
    ui->radioRaHor->setEnabled(pModbus->GetRhorSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 0));
    ui->radioRaVer->setEnabled(pModbus->GetRverSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 0));
    ui->radioExt->setEnabled(pModbus->GetExtSrvUse() && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 0));
    // 初始化界面字符串
	ui->radioPaHor->setText(GetServoName(AXIS_IDX_PHOR));
	ui->radioPaVer->setText(GetServoName(AXIS_IDX_PVER));
	ui->radioTrv->setText(GetServoName(AXIS_IDX_TRV));
	ui->radioRaHor->setText(GetServoName(AXIS_IDX_RHOR));
	ui->radioRaVer->setText(GetServoName(AXIS_IDX_RVER));
	ui->radioExt->setText(GetServoName(AXIS_IDX_EXT));
	// 显示对话框
	ret = exec();
	// 退出
	if (posChanged)
	{
		// 写入系统日志
        QString srvPos = QString("%1: %2, %3: %4, %5: %6,%7: %8, %9: %10, %11: %12").arg(GetServoName(AXIS_IDX_PHOR)).arg(pModbus->GetPaHorPos()/100.0).arg(GetServoName(AXIS_IDX_PVER)).arg(pModbus->GetPaVerPos()/100.0).arg(GetServoName(AXIS_IDX_TRV)).arg(pModbus->GetTravelPos()/100.0).arg(GetServoName(AXIS_IDX_RHOR)).arg(pModbus->GetRaHorPos()/100.0).arg(GetServoName(AXIS_IDX_RVER)).arg(pModbus->GetRaVerPos()/100.0).arg(GetServoName(AXIS_IDX_EXT)).arg(pModbus->GetExtendPos()/100.0);
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_SRVCTRL, srvPos);
		xSysLog::SaveChange();
	}
	return ret;
}

// 设置当前伺服轴
bool DialogServoControl::setCurServo(void)
{
	int axis = pSrvAxies->checkedId();
	QString axisAlias;
	QString title;
	switch (axis)
	{
	case SRV_CTRLPG_PAHOR:
		axisAlias = GetServoName(AXIS_IDX_PHOR);
		title.append(tr(" 轴伺服"));
		break;
	case SRV_CTRLPG_PAVER:
		axisAlias = GetServoName(AXIS_IDX_PVER);
		title.append(tr(" 轴伺服"));
		break;
	case SRV_CTRLPG_TRV:
		axisAlias = GetServoName(AXIS_IDX_TRV);
		title.append(tr(" 轴伺服"));
		break;
	case SRV_CTRLPG_RAHOR:
		axisAlias = GetServoName(AXIS_IDX_RHOR);
		title.append(tr(" 轴伺服"));
		break;
	case SRV_CTRLPG_RAVER:
		axisAlias = GetServoName(AXIS_IDX_RVER);
		title.append(tr(" 轴伺服"));
		break;
	case SRV_CTRLPG_EXT:
		axisAlias = GetServoName(AXIS_IDX_EXT);
		title.append(tr(" 轴伺服"));
		break;
	default:
		return false;
	}
	ui->stackedWidget->setCurrentIndex(axis);
    ui->groupDec->setTitle(axisAlias + QString::fromAscii("-"));
    ui->groupAdd->setTitle(axisAlias + QString::fromAscii("+"));
	title.append(strTitleSuffix);
	ui->labelTitle->setText(axisAlias + title);
	return true;
}
// 输出控制信号槽
bool DialogServoControl::checkManual(void)
{
	// 只有手动状态才能执行		//Added by zhangjz for v1.11 2012-07-13
	if (pModbus->GetSysState() != SYS_STATE_MANUAL)
		return false;
	// 检查安全开关
	if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
	{
#if UI_SAFESW_TIP
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAFESW_TIP));
#endif
		return false;
	}
#if SELECT_SWITCH_USE
	// 检查选择开关
	if (pxKeyPad->GetSwitch() != CUSKEY_SEL_MANUAL)
	{
		xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SELSW_STOP));
		return false;
	}
#endif
	return true;
}
// 当前伺服开始反向运行
void DialogServoControl::SvMoveCcw(void)
{
	if (!checkManual())
		return;
    m_havesendservocmd = false;
    m_ptimer->start(200);
}
// 当前伺服开始正向运行
void DialogServoControl::SvMoveCw(void)
{
	if (!checkManual())
		return;
    m_havesendservocmd = false;
    m_ptimer->start(200);
}
void DialogServoControl::SvMoveCwStop(void)
{
	if (!m_havesendservocmd)
    {
		SvShiftCw();
    }
    else
    {
    }
}
void DialogServoControl::SvMoveCcwStop(void)
{
	if (!m_havesendservocmd)
    {
        SvShiftCcw();
    }
    else
    {
    }
}
// 当前伺服反向微调
void DialogServoControl::SvShiftCcw(void)
{
    if (!checkManual())
		return;
	quint8 srvMap;
	double shiftPos = ui->doubleSpinBoxShift->value();
	switch (pSrvAxies->checkedId())
	{
	case SRV_CTRLPG_PAHOR:
		srvMap = SRV_PAHOR;
		break;
	case SRV_CTRLPG_PAVER:
		srvMap = SRV_PAVER;
		break;
	case SRV_CTRLPG_TRV:
		srvMap = SRV_TRV;
		break;
	case SRV_CTRLPG_RAHOR:
		srvMap = SRV_RAHOR;
		break;
	case SRV_CTRLPG_RAVER:
		srvMap = SRV_RAVER;
		break;
	case SRV_CTRLPG_EXT:
		srvMap = SRV_EXT;
		break;
	default:
		return ;
	}
	if (ServoSetup == false)
	{
        pModbus->ManualPos(ui->spinBoxSpeed->value(), srvMap, qRound(shiftPos * -100.00), SERVO_MODE_SAFE, true);
		posChanged = true;
	}
	else
	{
        pModbus->ManualPos(ui->spinBoxSpeed->value(), srvMap, qRound(shiftPos * -100.00), SERVO_MODE_FORCE, true);
		posChanged = true;
	}
}
// 当前伺服正向微调
void DialogServoControl::SvShiftCw(void)
{
    if (!checkManual())
		return;
	quint8 srvMap;
	double shiftPos = ui->doubleSpinBoxShift->value();
	switch (pSrvAxies->checkedId())
	{
	case SRV_CTRLPG_PAHOR:
		srvMap = SRV_PAHOR;
		break;
	case SRV_CTRLPG_PAVER:
		srvMap = SRV_PAVER;
		break;
	case SRV_CTRLPG_TRV:
		srvMap = SRV_TRV;
		break;
	case SRV_CTRLPG_RAHOR:
		srvMap = SRV_RAHOR;
		break;
	case SRV_CTRLPG_RAVER:
		srvMap = SRV_RAVER;
		break;
	case SRV_CTRLPG_EXT:
		srvMap = SRV_EXT;
		break;
	default:
		return ;
	}
	if (ServoSetup == false)
	{
        pModbus->ManualPos(ui->spinBoxSpeed->value(), srvMap, qRound(shiftPos * 100.00), SERVO_MODE_SAFE, true);
		posChanged = true;
	}
	else
	{
        pModbus->ManualPos(ui->spinBoxSpeed->value(), srvMap, qRound(shiftPos * 100.00), SERVO_MODE_FORCE, true);
		posChanged = true;
    }
}
// 伺服安全区域检测信号槽
void DialogServoControl::SafeInputChg(void)
{
	if (isVisible() == false)
		return;
	// 更新模内安全区显示
    if (pModbus->GetHomeInmold())
    {
            if (xIoPort::GetIn(SV_VAR_IN_OUTMOLD) != ui->LedSafeIn->on())
            ui->LedSafeIn->setOn(xIoPort::GetIn(SV_VAR_IN_OUTMOLD) && (!pModbus->GetOutmoldSignalNotuse()));
        // 更新原点安全区显示
            if (xIoPort::GetIn(SV_VAR_IN_ZHOME) != ui->LedSafeOut->on())
            ui->LedSafeOut->setOn(xIoPort::GetIn(SV_VAR_IN_ZHOME) && (!pModbus->GetInmoldSignalNotuse()));
    }
    else
    {
            if (xIoPort::GetIn(SV_VAR_IN_INMOLD) != ui->LedSafeIn->on())
            ui->LedSafeIn->setOn(xIoPort::GetIn(SV_VAR_IN_INMOLD) && (!pModbus->GetInmoldSignalNotuse()));
            if (xIoPort::GetIn(SV_VAR_IN_ZHOME) != ui->LedSafeOut->on())
            ui->LedSafeOut->setOn(xIoPort::GetIn(SV_VAR_IN_ZHOME) && (!pModbus->GetOutmoldSignalNotuse()));
    }
	// 更新正臂上位安全区显示
	if (xIoPort::GetIn(SV_VAR_IN_YWPOS) != ui->LedSafePaUp->on())
		ui->LedSafePaUp->setOn(xIoPort::GetIn(SV_VAR_IN_YWPOS));
	// 更新副臂上位安全区显示
	if (xIoPort::GetIn(SV_VAR_IN_AWPOS) != ui->LedSafeRaUp->on())
		ui->LedSafeRaUp->setOn(xIoPort::GetIn(SV_VAR_IN_AWPOS));
}

// 输入手动速度
void DialogServoControl::inputSpeed(void)
{
	DialogNumberPad numberPad;
    int value;
	if (numberPad.DoForm(value, ui->spinBoxSpeed->minimum(), ui->spinBoxSpeed->maximum()) == QDialog::Accepted)
    {
        pModbus->SetManualSpeed(value);
		ui->spinBoxSpeed->setValue(value);
    }
}
// 输入微调距离
void DialogServoControl::inputShift(void)
{
	DialogNumberPad numberPad;
	double value;
    if (numberPad.DoFormDouble(value, ui->doubleSpinBoxShift->minimum(), ui->doubleSpinBoxShift->maximum()) == QDialog::Accepted)
    {
        pModbus->SetSrvScale(value);
		ui->doubleSpinBoxShift->setValue(value);
    }
}
// 快速定位到正臂模内安全区起点
void DialogServoControl::toPaHorSafeBegin(void)
{
	if (!checkManual())
		return;
	pModbus->ManualPos(ui->spinBoxSpeed->value(), SRV_PAHOR, paHorSafeBegin, SERVO_MODE_SAFE);
	posChanged = true;
}
// 快速定位到正臂模内安全区终点
void DialogServoControl::toPaHorSafeEnd(void)
{
	if (!checkManual())
		return;
	pModbus->ManualPos(ui->spinBoxSpeed->value(), SRV_PAHOR, paHorSafeEnd, SERVO_MODE_SAFE);
	posChanged = true;
}
// 快速定位到正臂模内上位待机点
void DialogServoControl::toPaVerWaitPos(void)
{
	if (!checkManual())
		return;
	pModbus->ManualPos(ui->spinBoxSpeed->value(), SRV_PAVER, paVerWaitPos, SERVO_MODE_SAFE);
	posChanged = true;
}
// 快速定位到正臂模内下行取物点
void DialogServoControl::toPaVetCatPos(void)
{
	if (!checkManual())
		return;
	pModbus->ManualPos(ui->spinBoxSpeed->value(), SRV_PAVER, paVerCatPos, SERVO_MODE_SAFE);
	posChanged = true;
}
// 快速定位到副臂模内安全区起点
void DialogServoControl::toRaHorSafeBegin(void)
{
	if (!checkManual())
		return;
	pModbus->ManualPos(ui->spinBoxSpeed->value(), SRV_RAHOR, raHorSafeBegin, SERVO_MODE_SAFE);
	posChanged = true;
}
// 快速定位到副臂模内安全区终点
void DialogServoControl::toRaHorSafeEnd(void)
{
	if (!checkManual())
		return;
	pModbus->ManualPos(ui->spinBoxSpeed->value(), SRV_RAHOR, raHorSafeEnd, SERVO_MODE_SAFE);
	posChanged = true;
}
// 快速定位到副臂模内上位待机点
void DialogServoControl::toRaVerWaitPos(void)
{
	if (!checkManual())
		return;
	pModbus->ManualPos(ui->spinBoxSpeed->value(), SRV_RAVER, raVerWaitPos, SERVO_MODE_SAFE);
	posChanged = true;
}
// 快速定位到副臂模内下行取物点
void DialogServoControl::toRaVerCatPos(void)
{
	if (!checkManual())
		return;
	pModbus->ManualPos(ui->spinBoxSpeed->value(), SRV_RAVER, raVerCatPos, SERVO_MODE_SAFE);
	posChanged = true;
}
// 快速定位到横行模内取物点
void DialogServoControl::toTrvCatPos(void)
{
	if (!checkManual())
		return;
	pModbus->ManualPos(ui->spinBoxSpeed->value(), SRV_TRV, trvCatPos, SERVO_MODE_SAFE);
	posChanged = true;
}
// 快速定位到横行模外置物点
void DialogServoControl::toTrvRelPos(void)
{
	if (!checkManual())
		return;
	pModbus->ManualPos(ui->spinBoxSpeed->value(), SRV_TRV, trvRelPos, SERVO_MODE_SAFE);
	posChanged = true;
}
