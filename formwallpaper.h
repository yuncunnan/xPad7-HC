#ifndef FORMWALLPAPER_H
#define FORMWALLPAPER_H

#include <QWidget>
#include "cmbprotocol.h"
#include "xstringresource.h"

namespace Ui {
class FormWallpaper;
}

class FormWallpaper : public QWidget
{
	Q_OBJECT

public:
	explicit FormWallpaper(CMBProtocol *modbus, QWidget *parent = 0);
	~FormWallpaper();

	bool EnterForm(void);
	bool ExitForm(void);

private:
	Ui::FormWallpaper *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
    void setPermissions(void);				// 根据当前用户权限设置界面

private slots:
    void InputIO(void);
    void userChange(void);					// 当前登录用户更改槽
    void OutputIO(void);
    void btnclick(void);

};

#endif // FORMWALLPAPER_H
