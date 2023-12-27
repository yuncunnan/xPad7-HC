#ifndef FORMSYSLOG_H
#define FORMSYSLOG_H

#include <QWidget>
#include <QtSql/QtSql>
#include <QDateTime>
#include "cmbprotocol.h"

class DialogLogQuery;

namespace Ui {
class FormSysLog;
}

class FormSysLog : public QWidget
{
	Q_OBJECT
	
public:
	explicit FormSysLog(CMBProtocol *modbus, QWidget *parent = 0);
	~FormSysLog();

	bool EnterForm(void);
	bool ExitForm(void);

protected:
	void changeEvent(QEvent *e);

private:
	Ui::FormSysLog *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
	static DialogLogQuery *pQuery;

private slots:
	void resetModel(void);
	void userChange(void);					// 当前登录用户更改槽
	void showPortStatus(void);
	void showParameter(void);
	void showDetail(void);
	void query(void);
};

#endif // FORMSYSLOG_H
