#ifndef FORMALARM_H
#define FORMALARM_H

#include <QWidget>
#include <QModelIndex>
#include "cmbprotocol.h"
#include "xstringresource.h"

class QButtonGroup;

namespace Ui {
class FormAlarm;
}

class FormAlarm : public QWidget
{
	Q_OBJECT
	
public:
	explicit FormAlarm(CMBProtocol *modbus, QWidget *parent);
	~FormAlarm();
	
	bool EnterForm(void);
	bool ExitForm(void);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::FormAlarm *ui;
	QButtonGroup *pAlmPos;
	CMBProtocol *pModbus;					// Modbus协议对象
    void displayAlarm(int id, uint32_t code);
	void retranslateUi(void);				// 更新界面字符串翻译

private slots:
	void resetModel(void);
	void AlmPosClicked(int id);				// 报警位置单选框点击信号槽
    void slot_AlmChg(qint16 idx, quint32 alarm);
    void ClearAlarm(void);
    void displayAlarmInfo(QModelIndex idx);
};

#endif // FORMALARM_H
