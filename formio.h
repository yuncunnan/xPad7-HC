#ifndef FORMIO_H
#define FORMIO_H

#include <QWidget>
#include "cmbprotocol.h"
#include "xstringresource.h"

namespace Ui {
class FormIO;
}

class FormIO : public QWidget
{
	Q_OBJECT
	
public:
    explicit FormIO(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormIO();
	
	bool EnterForm(void);
	bool ExitForm(void);

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormIO *ui;
	CMBProtocol *pModbus;					// Modbus协议对象

	SystemParameter SysPara;				// 系统参数设置
	SystemParameter SysParaBak;
    quint64 parModify;						// 参数修改标志

	void loadPortNames(void);				// 设置端口名称
    void setPermissions(void);				// 根据当前用户权限设置界面
	void setPortLabel(void);				// 设置当前模块端口标题
    void setPortvisible(void);              // 设置端口显示状态
	bool QueryPara(void);					// 查询系统参数设置
	void LoadPara(void);					// 从界面得到系统参数设置
	bool isModified(void);					// 检查参数是否修改
	bool CheckValid(void);					// 检查参数合法性
	bool SavePara(void);					// 保存系统参数设置

private slots:
	void userChange(void);					// 当前登录用户更改槽
	void AcceptSetup(void);					// 保存参数并且退出信号槽

    void IgnorePagePrev(void);
    void PolaryPagePrev(void);
    void NoalmPagePrev(void);
    void OutputPagePrev(void);
    void IgnorePageNext(void);
    void PolaryPageNext(void);
    void NoalmPageNext(void);
    void OutputPageNext(void);
};

#endif // FORMIO_H
