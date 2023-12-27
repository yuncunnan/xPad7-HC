#include <QKeyEvent>
#include "xconfig.h"
#include "cmbprotocol.h"
#include "dialognumberpad.h"
#include "ui_dialognumberpad.h"
#include "servoalias.h"

DialogNumberPad::DialogNumberPad(QWidget *parent) :	QDialog(parent), ui(new Ui::DialogNumberPad)
{
	ui->setupUi(this);
    retranslateUi();
#if defined(Q_WS_QWS)
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
	// 设置数值输入格式
    ui->lineEdit->setValidator(new QDoubleValidator(-99999999.00, 99999999.00, 2, ui->lineEdit));
	if (!CMBProtocol::GetFunctions(SUB_FUN2_VISION))
	{
		ui->KeyVar->setEnabled(false);
		ui->KeyVar->setText(tr("预留"));
	}
}

DialogNumberPad::~DialogNumberPad()
{
	delete ui;
}

void DialogNumberPad::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
        retranslateUi();
        break;
	default:
		break;
	}
}
void DialogNumberPad::retranslateUi(void)
{
    ui->KeyPHor->setText(GetServoName(AXIS_IDX_PHOR));
    ui->KeyPVer->setText(GetServoName(AXIS_IDX_PVER));
	ui->KeyTrv->setText(GetServoName(AXIS_IDX_TRV));
    ui->KeyRHor->setText(GetServoName(AXIS_IDX_RHOR));
    ui->KeyRVer->setText(GetServoName(AXIS_IDX_RVER));
    ui->KeyExt->setText(GetServoName(AXIS_IDX_EXT));
}

/*int DialogNumberPad::DoForm(double &value)
{
    m_type = POS_TYPE_POINT;
	ui->KeyCat->setVisible(false);
	ui->KeyRel->setVisible(false);
	ui->KeyWait->setVisible(false);
    ui->KeyPHor->setVisible(false);
    ui->KeyPVer->setVisible(false);
    ui->KeyRHor->setVisible(false);
    ui->KeyRVer->setVisible(false);
    ui->KeyTrv->setVisible(false);
    ui->KeyExt->setVisible(false);
    ui->KeyVar->setVisible(false);
    setMinimumHeight(480);
    setMaximumHeight(480);
    resize(0, 0);
	int ret;
	// 显示对话框
	ui->labelMessage->clear();
	ret = exec();
	// 返回输入的数值
	if (ret == QDialog::Accepted)
		value = ui->lineEdit->text().toDouble();
	else
		value = 0.0;
	return ret;
}*/

int DialogNumberPad::DoFormPos(double &value, double min, double max)
{
    m_type = POS_TYPE_POINT;
    ui->KeyCat->setEnabled(false);
    ui->KeyRel->setEnabled(false);
    ui->KeyWait->setEnabled(false);
    ui->KeyVar->setEnabled(false);
    setMinimumHeight(666);
    setMaximumHeight(666);
    resize(0, 0);
    int ret;
    double tmp;
    if (min > max)
    {
        tmp = max;
        max = min;
        min = tmp;
    }
    // 显示对话框
    ui->labelMessage->setText(tr("范围：") + QString::number(min, 'F', 2) + QString(" ~ ") + QString::number(max, 'F', 2));
    ret = exec();
    // 返回输入的数值
    if (ret == QDialog::Accepted)
        value = ui->lineEdit->text().toDouble();
    else
        value = 0.0;
    if (value < min)
        value = min;
    else if (value > max)
        value = max;
    return ret;
}


int DialogNumberPad::DoFormDouble(double &value, double min, double max)
{
    m_type = POS_TYPE_POINT;
	ui->KeyCat->setVisible(false);
	ui->KeyRel->setVisible(false);
	ui->KeyWait->setVisible(false);
    ui->KeyPHor->setVisible(false);
    ui->KeyPVer->setVisible(false);
    ui->KeyRHor->setVisible(false);
    ui->KeyRVer->setVisible(false);
    ui->KeyTrv->setVisible(false);
    ui->KeyExt->setVisible(false);
    ui->KeyVar->setVisible(false);
    setMinimumHeight(480);
    setMaximumHeight(480);
    resize(0, 0);
	int ret;
	double tmp;
	if (min > max)
	{
		tmp = max;
		max = min;
		min = tmp;
	}
	// 显示对话框
    ui->labelMessage->setText(tr("范围：") + QString::number(min, 'F', 2) + QString(" ~ ") + QString::number(max, 'F', 2));
	ret = exec();
	// 返回输入的数值
	if (ret == QDialog::Accepted)
		value = ui->lineEdit->text().toDouble();
	else
		value = 0.0;
	if (value < min)
		value = min;
	else if (value > max)
		value = max;
	return ret;
}

int DialogNumberPad::DoForm(int &value, int min, int max)
{
    m_type = POS_TYPE_POINT;
	ui->KeyCat->setVisible(false);
	ui->KeyRel->setVisible(false);
	ui->KeyWait->setVisible(false);
    ui->KeyPHor->setVisible(false);
    ui->KeyPVer->setVisible(false);
    ui->KeyRHor->setVisible(false);
    ui->KeyRVer->setVisible(false);
    ui->KeyTrv->setVisible(false);
    ui->KeyExt->setVisible(false);
    ui->KeyVar->setVisible(false);
    ui->KeyDOT->setEnabled(false);
    setMinimumHeight(480);
    setMaximumHeight(480);
    resize(0, 0);
	int ret;
    int tmp;
	if (min > max)
	{
		tmp = max;
		max = min;
		min = tmp;
	}
	// 显示对话框
	ui->labelMessage->setText(tr("范围：") + QString::number(min) + QString(" ~ ") + QString::number(max));
	ret = exec();
	// 返回输入的数值
	if (ret == QDialog::Accepted)
        value = ui->lineEdit->text().toInt();
	else
        value = 0;
	if (value < min)
		value = min;
	else if (value > max)
		value = max;
	return ret;
}

int DialogNumberPad::DoForm(int &type, double &value, double min, double max)
{
	int ret;
	double tmp;
    m_type = type;
    if (min > max)
	{
		tmp = max;
		max = min;
		min = tmp;
	}
    m_min = min;
    m_max = max;
    if (m_type==POS_TYPE_VAR)
    {
        ui->KeyVar->setChecked(true);
        max = 499;
        min = 400;
        ui->lineEdit->setValidator(new QDoubleValidator(400, 499, 0, ui->lineEdit));
        ui->labelMessage->setText(tr("变量范围：400~499"));
    }
    else
    {
        ui->KeyVar->setChecked(false);
        ui->lineEdit->setValidator(new QDoubleValidator(-3000.00, 6000000.00, 2, ui->lineEdit));
        ui->labelMessage->setText(tr("范围：") + QString::number(m_min, 'F', 2) + QString(" ~ ") + QString::number(m_max, 'F', 2));
    }
	ret = exec();
	// 返回输入的数值
	if (ret == QDialog::Accepted)
        value = ui->lineEdit->text().toDouble();

    if (ui->KeyVar->isChecked())
    {
        m_type = POS_TYPE_VAR;
    }
	if (value < min)
		value = min;
	else if (value > max)
		value = max;
	type = m_type;
	return ret;
}

// 按钮点击信号槽
// 数字0
void DialogNumberPad::Key0Click(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_0, Qt::NoModifier, "0");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 数字1
void DialogNumberPad::Key1Click(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_1, Qt::NoModifier, "1");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 数字2
void DialogNumberPad::Key2Click(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_2, Qt::NoModifier, "2");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 数字3
void DialogNumberPad::Key3Click(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_3, Qt::NoModifier, "3");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 数字4
void DialogNumberPad::Key4Click(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_4, Qt::NoModifier, "4");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 数字5
void DialogNumberPad::Key5Click(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_5, Qt::NoModifier, "5");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 数字6
void DialogNumberPad::Key6Click(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_6, Qt::NoModifier, "6");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 数字7
void DialogNumberPad::Key7Click(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_7, Qt::NoModifier, "7");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 数字8
void DialogNumberPad::Key8Click(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_8, Qt::NoModifier, "8");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 数字9
void DialogNumberPad::Key9Click(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_9, Qt::NoModifier, "9");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 小数点
void DialogNumberPad::KeyDotClick(void)
{
	QKeyEvent event(QEvent::KeyPress,Qt::Key_Period, Qt::NoModifier, ".");
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 符号
void DialogNumberPad::KeySignClick(void)
{
	double value = ui->lineEdit->text().toDouble();
	value = -value;
	ui->lineEdit->setText(QString("%1").arg(value));
}
// 清除
void DialogNumberPad::KeyClrClick(void)
{
	ui->lineEdit->setText("");
}
// 退格
void DialogNumberPad::KeyDelClick(void)
{
	QKeyEvent event(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
	QApplication::sendEvent(ui->lineEdit, &event);
}
// 取物点
void DialogNumberPad::KeyCatClick(void)
{
	m_type = POS_TYPE_CAT;
}
// 置物点
void DialogNumberPad::KeyRelClick(void)
{
	m_type = POS_TYPE_REL;
}
// 待机点
void DialogNumberPad::KeyWaitClick(void)
{
	m_type = POS_TYPE_WAIT;
}
void DialogNumberPad::KeyVarToggled(bool ischecked)
{
    if (ischecked)
    {
        ui->KeyWait->setEnabled(false);
        ui->KeyRel->setEnabled(false);
        ui->KeyCat->setEnabled(false);
        ui->KeyPHor->setEnabled(false);
        ui->KeyPVer->setEnabled(false);
        ui->KeyRHor->setEnabled(false);
        ui->KeyRVer->setEnabled(false);
        ui->KeyTrv->setEnabled(false);
        ui->KeyExt->setEnabled(false);
        ui->KeySign->setEnabled(false);
        ui->KeyDOT->setEnabled(false);
        ui->KeyVar->setEnabled(false);
        ui->lineEdit->setText("");
        ui->lineEdit->setValidator(new QDoubleValidator(400, 499, 0, ui->lineEdit));
        ui->labelMessage->setText(tr("变量范围：400~499"));
        m_type = POS_TYPE_VAR;
    }
    else
    {
        ui->KeyWait->setEnabled(true);
        ui->KeyRel->setEnabled(true);
        ui->KeyCat->setEnabled(true);
        ui->KeyPHor->setEnabled(true);
        ui->KeyPVer->setEnabled(true);
        ui->KeyRHor->setEnabled(true);
        ui->KeyRVer->setEnabled(true);
        ui->KeyTrv->setEnabled(true);
        ui->KeyExt->setEnabled(true);
        ui->KeySign->setEnabled(true);
        ui->KeyDOT->setEnabled(true);
        ui->KeyVar->setEnabled(true);
        ui->lineEdit->setValidator(new QDoubleValidator(-3000.00, 6000000.00, 2, ui->lineEdit));
        ui->labelMessage->setText(tr("范围：") + QString::number(m_min, 'F', 2) + QString(" ~ ") + QString::number(m_max, 'F', 2));
        m_type = POS_TYPE_POINT;
     }
}

// 同步位置
void DialogNumberPad::KeyPHorClick(void)
{
    ui->lineEdit->setText(QString::number(CMBProtocol::GetPaHorPos()/100.0));
}
void DialogNumberPad::KeyPVerClick(void)
{
    ui->lineEdit->setText(QString::number(CMBProtocol::GetPaVerPos()/100.0));
}
void DialogNumberPad::KeyTrvClick(void)
{
    ui->lineEdit->setText(QString::number(CMBProtocol::GetTravelPos()/100.0));
}
void DialogNumberPad::KeyRHorClick(void)
{
    ui->lineEdit->setText(QString::number(CMBProtocol::GetRaHorPos()/100.0));
}
void DialogNumberPad::KeyRVerClick(void)
{
    ui->lineEdit->setText(QString::number(CMBProtocol::GetRaVerPos()/100.0));
}
void DialogNumberPad::KeyExtClick(void)
{
    ui->lineEdit->setText(QString::number(CMBProtocol::GetExtendPos()/100.0));
}
