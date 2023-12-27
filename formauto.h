#ifndef FORMAUTO_H
#define FORMAUTO_H

#include <QWidget>
#include "cmbprotocol.h"
#include "teachtablemodel.h"

class xStringResource;
class QButtonGroup;

namespace Ui {
class FormAuto;
}

class FormAuto : public QWidget
{
	Q_OBJECT
	
public:
	explicit FormAuto(CMBProtocol *modbus, QWidget *parent = 0);
	~FormAuto();
	
	bool EnterForm(void);
	bool ExitForm(void);
	bool TransAutoCode();					// 发送全自动代码

public slots:
	void BtnManualStop(void);				// 手动/停止按钮信号槽
	void BtnAutoRunClick(void);				// 自动/运行按钮信号槽
	void BtnPeriodClick(void);				// 单周期运行按钮信号槽
	void BtnStepClick(void);				// 单步运行按钮信号槽

protected:
	bool eventFilter(QObject *obj, QEvent *event);
	void changeEvent(QEvent *e);

signals:
	void BtnManualClick(void);

private:
    int curpc[MAX_PROCESS];
	Ui::FormAuto *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
	TeachTableModel pgmModel;
    QButtonGroup *pBtnProcess;
    QString CurPgmFileBak;
    QString CurPgmFile;

	void setPermissions(void);				// 根据当前用户权限设置界面
	void setBtnState(uint16_t sysState, uint16_t runState);
    void SetInputImm(bool init);
    void SetOutputImm(bool init);
    void SetProcBtnState(int idx);

private slots:
	void userChange(void);					// 当前登录用户更改槽
	void sysStateChanged(uint16_t state);	// 系统状态改变信号槽
	void runStateChanged(uint16_t state);	// 运行状态改变信号槽
	void setFollow(bool follow);				// 设置跟随状态

	// IO信号槽
    void inputImm(void);
    void outputImm(void);
	// 生产统计信息改变信号槽
	void prdSumChange(uint32_t input);
	void prdPlanChange(uint32_t input);
    void periodChange(uint32_t input, uint16_t idx);
    void pgmPcChange(uint16_t pc, uint16_t idx, bool init = false);
    void inmoldTimeChange(uint32_t input, uint16_t idx);
    void ProcBtnStateChanged(int idx);


};

#endif // FORMAUTO_H
