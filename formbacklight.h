#ifndef FORMBACKLIGHT_H
#define FORMBACKLIGHT_H

#include <QWidget>
#include "cmbprotocol.h"

namespace Ui {
class FormBacklight;
}

class FormBacklight : public QWidget
{
	Q_OBJECT

public:
	explicit FormBacklight(CMBProtocol *modbus,QWidget *parent = 0);
    ~FormBacklight();

	bool EnterForm(void);
	bool ExitForm(void);

private:
    Ui::FormBacklight *ui;
	QTimer *pClockTimer;					// 时钟定时器
	static uint32_t lastSumMold,lastInMold,lastCyc;
	CMBProtocol *pModbus;					// Modbus 协议对象

private slots:
	// 时钟信号槽
	void clockUpdate(void);
	void prdSumChange(uint32_t input);//生产总数
	void periodChange(uint32_t input, uint16_t idx);//循环周期
	void inmoldTimeChange(uint32_t input, uint16_t idx);//取件时间
};

#endif // FORMBACKLIGHT_H
