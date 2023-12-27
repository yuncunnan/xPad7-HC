#include <QSettings>
#include "xconfig.h"
#include "ui_xmessageboxIP.h"
#include "xmessageboxIP.h"
#include "dialognumberpad.h"
xMessageBoxIP::xMessageBoxIP(QWidget *parent) :	QDialog(parent), ui(new Ui::xMessageBoxIP)
{
	ui->setupUi(this);
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
}

xMessageBoxIP::~xMessageBoxIP()
{
	delete ui;
}

// 运行警告消息框
qint32 xMessageBoxIP::DoForm()
{
    quint32 ip, submask, gateway;
    QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
    ip = settings.value(XPAD_SET_IP, 0).toUInt();
    submask = settings.value(XPAD_SET_SUBMASK, 0).toUInt();
    gateway = settings.value(XPAD_SET_GATEWAY, 0).toUInt();
    ui->labelCurrentIP->setText(QString::number((quint8)(ip >> 24)) + "." + QString::number((quint8)(ip >> 16)) + "." + QString::number((quint8)(ip >> 8)) + "." + QString::number((quint8)ip));
    ui->BoxIP1->setValue((quint8)(ip >> 24));
    ui->BoxIP2->setValue((quint8)(ip >> 16));
    ui->BoxIP3->setValue((quint8)(ip >> 8));
    ui->BoxIP4->setValue((quint8)ip);
    ui->BoxSubMask1->setValue((quint8)(submask >> 24));
    ui->BoxSubMask2->setValue((quint8)(submask >> 16));
    ui->BoxSubMask3->setValue((quint8)(submask >> 8));
    ui->BoxSubMask4->setValue((quint8)submask);
    ui->BoxGateWay1->setValue((quint8)(gateway >> 24));
    ui->BoxGateWay2->setValue((quint8)(gateway >> 16));
    ui->BoxGateWay3->setValue((quint8)(gateway >> 8));
    ui->BoxGateWay4->setValue((quint8)gateway);
    ui->labelWarning->setText("");
    return exec();
}
void xMessageBoxIP::BtnClicked(void)
{
    quint32 m_ip, m_submask, m_gateway;
    ui->labelWarning->setText("");
    m_ip = (quint32)(ui->BoxIP1->value()<<24) | (quint32)(ui->BoxIP2->value()<<16) | (quint32)(ui->BoxIP3->value()<<8) | (quint32)(ui->BoxIP4->value());
    m_submask = (quint32)(ui->BoxSubMask1->value()<<24) | (quint32)(ui->BoxSubMask2->value()<<16) | (quint32)(ui->BoxSubMask3->value()<<8) | (quint32)(ui->BoxSubMask4->value());
    m_gateway = (quint32)(ui->BoxGateWay1->value()<<24) | (quint32)(ui->BoxGateWay2->value()<<16) | (quint32)(ui->BoxGateWay3->value()<<8) | (quint32)(ui->BoxGateWay4->value());
    if ((m_ip & m_submask) != (m_gateway & m_submask))
    {
        ui->labelWarning->setText(tr("IP地址和网关不在同一网段，请修改......"));
        return;
    }
    QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
    settings.setValue(XPAD_SET_IP, m_ip);
    settings.setValue(XPAD_SET_SUBMASK, m_submask);
    settings.setValue(XPAD_SET_GATEWAY, m_gateway);
    settings.sync();
    reject();
}
void xMessageBoxIP::inputIP1(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxIP1->minimum(), ui->BoxIP1->maximum()) == QDialog::Accepted)
        ui->BoxIP1->setValue(value);
}
void xMessageBoxIP::inputIP2(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxIP2->minimum(), ui->BoxIP2->maximum()) == QDialog::Accepted)
        ui->BoxIP2->setValue(value);
}
void xMessageBoxIP::inputIP3(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxIP3->minimum(), ui->BoxIP3->maximum()) == QDialog::Accepted)
        ui->BoxIP3->setValue(value);
}
void xMessageBoxIP::inputIP4(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxIP4->minimum(), ui->BoxIP4->maximum()) == QDialog::Accepted)
        ui->BoxIP4->setValue(value);
}
void xMessageBoxIP::inputSubMask1(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxSubMask1->minimum(), ui->BoxSubMask1->maximum()) == QDialog::Accepted)
        ui->BoxSubMask1->setValue(value);
}
void xMessageBoxIP::inputSubMask2(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxSubMask2->minimum(), ui->BoxSubMask2->maximum()) == QDialog::Accepted)
        ui->BoxSubMask2->setValue(value);
}
void xMessageBoxIP::inputSubMask3(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxSubMask3->minimum(), ui->BoxSubMask3->maximum()) == QDialog::Accepted)
        ui->BoxSubMask3->setValue(value);
}
void xMessageBoxIP::inputSubMask4(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxSubMask4->minimum(), ui->BoxSubMask4->maximum()) == QDialog::Accepted)
        ui->BoxSubMask4->setValue(value);
}
void xMessageBoxIP::inputGateWay1(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxGateWay1->minimum(), ui->BoxGateWay1->maximum()) == QDialog::Accepted)
        ui->BoxGateWay1->setValue(value);
}
void xMessageBoxIP::inputGateWay2(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxGateWay2->minimum(), ui->BoxGateWay2->maximum()) == QDialog::Accepted)
        ui->BoxGateWay2->setValue(value);
}
void xMessageBoxIP::inputGateWay3(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxGateWay3->minimum(), ui->BoxGateWay3->maximum()) == QDialog::Accepted)
        ui->BoxGateWay3->setValue(value);
}
void xMessageBoxIP::inputGateWay4(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, ui->BoxGateWay4->minimum(), ui->BoxGateWay4->maximum()) == QDialog::Accepted)
        ui->BoxGateWay4->setValue(value);
}
