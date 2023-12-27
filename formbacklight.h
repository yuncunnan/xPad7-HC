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
	QTimer *pClockTimer;					// ʱ�Ӷ�ʱ��
	static uint32_t lastSumMold,lastInMold,lastCyc;
	CMBProtocol *pModbus;					// Modbus Э�����

private slots:
	// ʱ���źŲ�
	void clockUpdate(void);
	void prdSumChange(uint32_t input);//��������
	void periodChange(uint32_t input, uint16_t idx);//ѭ������
	void inmoldTimeChange(uint32_t input, uint16_t idx);//ȡ��ʱ��
};

#endif // FORMBACKLIGHT_H
