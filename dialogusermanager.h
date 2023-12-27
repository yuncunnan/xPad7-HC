#ifndef DIALOGUSERMANAGER_H
#define DIALOGUSERMANAGER_H

#include <QDialog>
#include "cmbprotocol.h"
#include "xstringresource.h"

class xPermissions;

namespace Ui {
class DialogUserManager;
}

class DialogUserManager : public QDialog
{
	Q_OBJECT
	
public:
	explicit DialogUserManager(CMBProtocol *modbus, xPermissions *perm, QWidget *parent = 0);
	~DialogUserManager();
	
	int DoForm(void);
protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::DialogUserManager *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
	xPermissions *pUsrPerm;				// 用户权限对象

private slots:
	void inputPwd(void);					// 输入密码
	void clearPwd(void);					// 清除密码输入
	void inputOldPwd(void);					// 输入旧密码
	void inputNewPwd(void);					// 输入新密码
	void confirmPwd(void);					// 确认新密码
	void clearModify(void);					// 清除密码修改输入
	void btnOkClick(void);					// 确定按键信号槽
	void btnLogoutClick(void);				// 注销按键信号槽
};

#endif // DIALOGUSERMANAGER_H
