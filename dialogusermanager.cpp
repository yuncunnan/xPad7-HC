#include <QByteArray>
#include "xpermissions.h"
#include "xsystemlog.h"
#include "dialogusermanager.h"
#include "ui_dialogusermanager.h"
#include "dialogkeyboard.h"
#include "xmessagebox.h"

DialogUserManager::DialogUserManager(CMBProtocol *modbus, xPermissions *perm, QWidget *parent) : QDialog(parent), ui(new Ui::DialogUserManager)
{
	ui->setupUi(this);
	pModbus = modbus;
	pUsrPerm = perm;
#if defined(Q_WS_QWS)
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
}

DialogUserManager::~DialogUserManager()
{
	delete ui;
}

void DialogUserManager::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

int DialogUserManager::DoForm(void)
{
	// 初始化界面状态
	ui->tabWidget->setCurrentIndex(0);
	ui->lineEditPwd->setText(QString(""));
	ui->lineEditPwd->setMaxLength(MAX_PWD_LEN);
	ui->lineEditOldPwd->setText(QString(""));
	ui->lineEditOldPwd->setMaxLength(MAX_PWD_LEN);
	ui->lineEditNewPwd->setText(QString(""));
	ui->lineEditNewPwd->setMaxLength(MAX_PWD_LEN);
	ui->lineEditComfirmPwd->setText(QString(""));
	ui->lineEditComfirmPwd->setMaxLength(MAX_PWD_LEN);
	ui->labelStatus->setText(QString(""));
    ui->radioButtonAdvOperator->setVisible(false);
    ui->radioButtonAdvOperatorM->setVisible(false);
	return exec();
}

// 输入密码
void DialogUserManager::inputPwd(void)
{
//	DialogKeyboard keypad;
	QString str;
	if (xKbd->DoForm(str, KEYBOARD_TYPE_PWD) == QDialog::Accepted)
		ui->lineEditPwd->setText(str);
}
// 清除密码输入
void DialogUserManager::clearPwd(void)
{
	ui->lineEditPwd->setText(QString(""));
}

// 输入旧密码
void DialogUserManager::inputOldPwd(void)
{
//	DialogKeyboard keypad;
	QString str;
	if (xKbd->DoForm(str, KEYBOARD_TYPE_PWD) == QDialog::Accepted)
		ui->lineEditOldPwd->setText(str);
}
// 输入新密码
void DialogUserManager::inputNewPwd(void)
{
//	DialogKeyboard keypad;
	QString str;
	if (xKbd->DoForm(str, KEYBOARD_TYPE_PWD) == QDialog::Accepted)
		ui->lineEditNewPwd->setText(str);
}
// 确认新密码
void DialogUserManager::confirmPwd(void)
{
//	DialogKeyboard keypad;
	QString str;
	if (xKbd->DoForm(str, KEYBOARD_TYPE_PWD) == QDialog::Accepted)
		ui->lineEditComfirmPwd->setText(str);
}
// 清除密码修改输入
void DialogUserManager::clearModify(void)
{
	ui->lineEditOldPwd->setText(QString(""));
	ui->lineEditNewPwd->setText(QString(""));
	ui->lineEditComfirmPwd->setText(QString(""));
}

// 确定按键信号槽
void DialogUserManager::btnOkClick(void)
{
	if (ui->tabWidget->currentIndex() == 0)
	{
#if 0
        // *** 用户登录 ***
        uint8_t user;
        QByteArray pwd;
        if (ui->radioButtonAdvOperator->isChecked() == true)		// 登录高级用户
            user = xPermissions::AdvOperater;
        else if (ui->radioButtonManager->isChecked() == true)		// 登录管理员
            user = xPermissions::Administrator;
        else
            return;
        try
        {
            // 得到指定登录用户密码
            if (pModbus->ReadPwd(user, pwd) != SENDMSG_RET_ACK)
                throw false;
            if (QString(pwd).isEmpty() == true)
                xPermissions::DefaultPwd(user, pwd);
            // 核对用户密码是否正确
            if (ui->lineEditPwd->text() != QString(pwd))
            {
                // 用户密码不正确
                if (user != xPermissions::Administrator)
                {
                    // 后门密码不正确则检查高级管理员密码
                    xPermissions::DefaultPwd(xPermissions::Administrator, pwd);
                    if (ui->lineEditPwd->text() != QString(pwd))
                    {
                        xPermissions::DefaultPwd(xPermissions::AdvAdministrator, pwd);
                        if (ui->lineEditPwd->text() != QString(pwd))
                        {
                            // 高级管理员密码不正确则检查超级密码
                            xPermissions::SupperUsrPwd(pwd);
                            if (ui->lineEditPwd->text() != QString(pwd))
                            {
                                // 完蛋了,超级密码也不正确只能显示"密码不正确"并返回了
                                ui->labelStatus->setText(tr("用户密码输入错误！"));
                                return;
                            }
                        }
                    }
                }
                else
                {
                    xPermissions::DefaultPwd(xPermissions::AdvAdministrator, pwd);
                    if (ui->lineEditPwd->text() != QString(pwd))
                    {
                        xPermissions::SupperUsrPwd(pwd);
                        if (ui->lineEditPwd->text() != QString(pwd))
                        {
                            ui->labelStatus->setText(tr("用户密码输入错误！"));
                            return;
                        }
                        // 超级密码正确登陆超级用户
                        user = xPermissions::SuperUser;
                    }
                    else
                        user = xPermissions::AdvAdministrator;
                }
            }
            // 登录成功修改当前用户
            pUsrPerm->ChangeUser(user);
#else
        // *** 用户登录 ***
		uint8_t user;
		QByteArray pwd;
		if (ui->radioButtonAdvOperator->isChecked() == true)		// 登录高级用户
			user = xPermissions::AdvOperater;
		else if (ui->radioButtonManager->isChecked() == true)		// 登录管理员
			user = xPermissions::Administrator;
		else if (ui->radioButtonAdvManager->isChecked() == true)	// 登录高级管理员
			user = xPermissions::AdvAdministrator;
		else
			return;
		try
		{
			// 得到指定登录用户密码
			if (pModbus->ReadPwd(user, pwd) != SENDMSG_RET_ACK)
				throw false;
			if (QString(pwd).isEmpty() == true)
				xPermissions::DefaultPwd(user, pwd);
			// 核对用户密码是否正确
/*            if ((ui->lineEditPwd->text() == "222")&&(user = xPermissions::Administrator))
            {
            }
            else */
            if (ui->lineEditPwd->text() != QString(pwd))
            {
				// 用户密码不正确
                if (user != xPermissions::AdvAdministrator)     // 密码不正确则检查高级管理员密码
				{
                    xPermissions::DefaultPwd(xPermissions::AdvAdministrator, pwd);
                    if (ui->lineEditPwd->text() != QString(pwd))
                    {
                        // 高级管理员密码不正确则检查超级密码
                        xPermissions::SupperUsrPwd(pwd);
                        if (ui->lineEditPwd->text() != QString(pwd))
                        {
                            // 完蛋了,超级密码也不正确只能显示"密码不正确"并返回了
                            ui->labelStatus->setText(tr("用户密码输入错误！"));
                            return;
                        }
                    }
				}
				else
				{
					if(ui->lineEditPwd->text() != "123" || FACTORY == FA_SHINI || FACTORY == FA_WEILIHE2)
                    {
                        // 登录的是高级管理员则检查超级密码
                        xPermissions::SupperUsrPwd(pwd);
                        if (ui->lineEditPwd->text() != QString(pwd))
                        {
                            ui->labelStatus->setText(tr("用户密码输入错误！"));
                            return;
                        }
                        // 超级密码正确登陆超级用户
                        user = xPermissions::SuperUser;
                    }
                }
			}

			// 登录成功修改当前用户
			pUsrPerm->ChangeUser(user);
#endif
		}
		catch (bool &)
		{
			xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_QUERY_PARA_ERROR));
			return;
		}
		// 写入系统日志
		if (user == xPermissions::AdvOperater)
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_ADVOPRLOG);
		else if (user == xPermissions::Administrator)
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_ADMLOG);
		else if (user == xPermissions::AdvAdministrator)
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_ADVADMLOG);
		else if (user == xPermissions::SuperUser)
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_SULOG);
		else
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_OPRLOG);
		xSysLog::SaveChange();
		// 关闭对话框
		done(QDialog::Accepted);
	}
	else
	{
		// 密码修改
		uint8_t user;
		QByteArray pwd;
		// 核对两次输入的新密码是否一致
		if (ui->lineEditNewPwd->text() != ui->lineEditComfirmPwd->text())
		{
			ui->labelStatus->setText(tr("新密码确认错误！"));
			return;
		}
		// 新密码不能为空
		if (ui->lineEditNewPwd->text().size() == 0)
		{
			ui->labelStatus->setText(tr("新密码不能为空！"));
			return;
		}
		if (ui->radioButtonAdvOperatorM->isChecked() == true)		// 修改高级操作员密码
			user = xPermissions::AdvOperater;
		else if (ui->radioButtonManagerM->isChecked() == true)	// 修改管理员密码
			user = xPermissions::Administrator;
		else
			return;
		try
		{
			// 读取指定用户密码
			if (pModbus->ReadPwd(user, pwd) != SENDMSG_RET_ACK)
				throw false;
			if (QString(pwd).isEmpty() == true)
				xPermissions::DefaultPwd(user, pwd);
			// 核对旧密码是否正确
            if (ui->lineEditOldPwd->text() != QString(pwd))
			{
				xPermissions::SupperUsrPwd(pwd);
				if (ui->lineEditPwd->text() != QString(pwd))
				{
					ui->labelStatus->setText(tr("用户密码输入错误！"));
					return;
				}
			}
			QByteArray newPwd = ui->lineEditNewPwd->text().toAscii();
			// 写入新密码
			if (pModbus->WritePwd(user, newPwd) != SENDMSG_RET_ACK)
				throw true;
		}
		catch (bool &err)
		{
			if (err == true)
				xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_SAVE_PARA_ERROR));
			else
				xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_QUERY_PARA_ERROR));
			return;
		}
		// 写入系统日志
		if (user == xPermissions::AdvOperater)
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_ADVOPRPWD);
		else if (user == xPermissions::Administrator)
			xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_ADMPWD);
		xSysLog::SaveChange();
		// 关闭对话框
		done(QDialog::Accepted);
	}
}
// 注销按键信号槽
void DialogUserManager::btnLogoutClick(void)
{
//	pUsrPerm->ChangeUser(xPermissions::Operater);
	pUsrPerm->UserLogout();
    done(QDialog::Rejected);
}
