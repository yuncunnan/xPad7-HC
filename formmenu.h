#ifndef FORMMENU_H
#define FORMMENU_H

#include <QWidget>
#include "cmbprotocol.h"
//#include "elccalc.h"
#include "xstringresource.h"

namespace Ui {
class Formmenu;
}

class Formmenu : public QWidget
{
	Q_OBJECT
	
public:
	explicit Formmenu(CMBProtocol *modbus, QWidget *parent);
	~Formmenu();
	
	bool EnterForm(void);
	bool ExitForm(void);

signals:
	void EnterSystemSetup(void);
	void EnterServoSetup(void);
	void EnterUiSetup(void);
	void EnterAdjust(void);
	void EnterInformation(void);
	void EnterManufacturer(void);
	void EnterSystemLog(void);
	void EnterOption(void);
    void EnterVarInit(void);
    void EnterIOSetup(void);
protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::Formmenu *ui;
	CMBProtocol *pModbus;					// Modbus协议对象

private slots:
	void BtnSystemClick(void);				// 系统参数
	void BtnServoClick(void);				// 伺服参数
	void BtnUiSetup(void);					// 用户界面
	void BtnAdjustClick(void);				// 调位操作
	void BtnInformation(void);				// 系统信息
	void BtnManufacturer(void);				// 厂商操作
	void BtnSystemLog(void);				// 系统日志
	void BtnOption(void);					// 命令配置
    void BtnVarInit(void);                  // 变量初始化
    void BtnIOSetup(void);                  // 变量初始化
};

#endif // FORMMENU_H
