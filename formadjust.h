#ifndef FORMADJUST_H
#define FORMADJUST_H

#include <QWidget>
#include "cmbprotocol.h"

class QButtonGroup;
class xStringResource;

namespace Ui {
class FormAdjust;
}

class FormAdjust : public QWidget
{
	Q_OBJECT
	
public:
	explicit FormAdjust(CMBProtocol *modbus, QWidget *parent);
	~FormAdjust();
	
	bool EnterForm(void);
	bool ExitForm(void);

protected:
	void changeEvent(QEvent *e);
	
private:
    QTimer * m_ptimer;
    bool m_havesendservocmd;

    Ui::FormAdjust *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
//	QButtonGroup *pPneCcw;
//	QButtonGroup *pPneCw;
    bool posChanged[6];						// 设置参数修改标志

    bool checkManual(void);
    void retranslateUi(void);				// 设置界面字符串资源
    void setPermissions(quint16 refState);	// 设置界面状态

private slots:
	void userChange(void);					// 当前登录用户更改槽
	void SvReferState(uint16_t state);		// 系统原点复归状态更改槽
	void SetMain(bool init);
	void InputMain(void);
	void SvPaHorCcw(void);
	void SvPaHorCw(void);
	void SvPaVerCcw(void);
	void SvPaVerCw(void);
	void SvTrvCcw(void);
	void SvTrvCw(void);
	void SvRaHorCcw(void);
	void SvRaHorCw(void);
	void SvRaVerCcw(void);
	void SvRaVerCw(void);
	void SvExtCcw(void);
	void SvExtCw(void);
    void SvStop(void);
	void PneAdjCcw(int code);
	void PneAdjCw(int code);
	void PneAdjStop(int code);
    void safeSwOff(void);
	void InputAdjSpd(void);
    void InputAdjScale(void);

    void StopTimer(void);
    void SvPHorShiftCcw(void);
    void SvPHorShiftCw(void);
    void SvPVerShiftCcw(void);
    void SvPVerShiftCw(void);
    void SvRHorShiftCcw(void);
    void SvRHorShiftCw(void);
    void SvRVerShiftCcw(void);
    void SvRVerShiftCw(void);
    void SvTrvShiftCcw(void);
    void SvTrvShiftCw(void);
    void SvExtShiftCcw(void);
    void SvExtShiftCw(void);

    void SvPHorCwStop(void);
    void SvPHorCcwStop(void);
    void SvPVerCwStop(void);
    void SvPVerCcwStop(void);
    void SvRHorCwStop(void);
    void SvRHorCcwStop(void);
    void SvRVerCwStop(void);
    void SvRVerCcwStop(void);
    void SvTrvCwStop(void);
    void SvTrvCcwStop(void);
    void SvExtCwStop(void);
    void SvExtCcwStop(void);

	void RaHorClick(void);
	void PaHorClick(void);
	void RaAdvClick(void);
	void RaDesClick(void);
	void SetOutIO(void);
    void extOutOn(void);
    void extOutOff(void);

};

#endif // FORMADJUST_H
