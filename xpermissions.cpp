#include "xconfig.h"
#include "xsystemlog.h"
#include "xpermissions.h"

quint8 xPermissions::currentUser;

#if FACTORY == FA_WETEC
bool xPermissions::oprPerm[PERMISSIONS_MAX] =
{
	true,	// PER_SRV_ORG			0
	false,	// PER_CHG_PGM			1
	false,	// PER_OPR_PGM			2
	false,	// PER_SET_TIME			3
	true,	// PER_SRV_CTRL			4
	true,	// PER_AUTO_OPR			5
	true,	// PER_MANUAL_OPR		6
	false,	// PER_TEACH			7
	false,	// PER_SYS_NORMAL		8
	false,	// PER_SYS_SIGNAL		9
	false,	// PER_SYS_RESET		10
	false,	// PER_SYS_MAINTAIN		11
	false,	// PER_SRV_SAFE			12
	false,	// PER_SRV_MACHINE		13
	false,	// PER_UI_SET			14
	false,	// PER_ADJ_CTRL			15
	false,	// PER_MANUFACTURER		16
	false,	// PER_SYS_LOG			17
	false,	// PER_SYS_OPTION		18
};
bool xPermissions::advOprPerm[PERMISSIONS_MAX] =
{
	true,	// PER_SRV_ORG			0
	true,	// PER_CHG_PGM			1
	true,	// PER_OPR_PGM			2
	false,	// PER_SET_TIME			3
	true,	// PER_SRV_CTRL			4
	true,	// PER_AUTO_OPR			5
	true,	// PER_MANUAL_OPR		6
	true,	// PER_TEACH			7
	true,	// PER_SYS_NORMAL		8
	false,	// PER_SYS_SIGNAL		9
	false,	// PER_SYS_RESET		10
	false,	// PER_SYS_MAINTAIN		11
	false,	// PER_SRV_SAFE			12
	false,	// PER_SRV_MACHINE		13
	true,	// PER_UI_SET			14
	true,	// PER_ADJ_CTRL			15
	false,	// PER_MANUFACTURER		16
	false,	// PER_SYS_LOG			17
	true,	// PER_SYS_OPTION		18
};
bool xPermissions::adminPerm[PERMISSIONS_MAX] =
{
	true,	// PER_SRV_ORG			0
	true,	// PER_CHG_PGM			1
	true,	// PER_OPR_PGM			2
	true,	// PER_SET_TIME			3
	true,	// PER_SRV_CTRL			4
	true,	// PER_AUTO_OPR			5
	true,	// PER_MANUAL_OPR		6
	true,	// PER_TEACH			7
	true,	// PER_SYS_NORMAL		8
	true,	// PER_SYS_SIGNAL		9
	true,	// PER_SYS_RESET		10
	false,	// PER_SYS_MAINTAIN		11
	true,	// PER_SRV_SAFE			12
	false,	// PER_SRV_MACHINE		13
	true,	// PER_UI_SET			14
	true,	// PER_ADJ_CTRL			15
	false,	// PER_MANUFACTURER		16
	true,	// PER_SYS_LOG			17
	true,	// PER_SYS_OPTION		18
};
#else
bool xPermissions::oprPerm[PERMISSIONS_MAX] =
{
	true,	// PER_SRV_ORG			0
	false,	// PER_CHG_PGM			1
	false,	// PER_OPR_PGM			2
	false,	// PER_SET_TIME			3
	false,	// PER_SRV_CTRL			4
	true,	// PER_AUTO_OPR			5
	false,	// PER_MANUAL_OPR		6
	false,	// PER_TEACH			7
	false,	// PER_SYS_NORMAL		8
	false,	// PER_SYS_SIGNAL		9
	false,	// PER_SYS_RESET		10
	false,	// PER_SYS_MAINTAIN		11
	false,	// PER_SRV_SAFE			12
	false,	// PER_SRV_MACHINE		13
	false,	// PER_UI_SET			14
	false,	// PER_ADJ_CTRL			15
	false,	// PER_MANUFACTURER		16
	false,	// PER_SYS_LOG			17
	false,	// PER_SYS_OPTION		18
};
bool xPermissions::advOprPerm[PERMISSIONS_MAX] =
{
	true,	// PER_SRV_ORG			0
	true,	// PER_CHG_PGM			1
	false,	// PER_OPR_PGM			2
	false,	// PER_SET_TIME			3
	true,	// PER_SRV_CTRL			4
	true,	// PER_AUTO_OPR			5
	true,	// PER_MANUAL_OPR		6
	false,	// PER_TEACH			7
	true,	// PER_SYS_NORMAL		8
	false,	// PER_SYS_SIGNAL		9
	false,	// PER_SYS_RESET		10
	false,	// PER_SYS_MAINTAIN		11
	false,	// PER_SRV_SAFE			12
	false,	// PER_SRV_MACHINE		13
	false,	// PER_UI_SET			14
	false,	// PER_ADJ_CTRL			15
	false,	// PER_MANUFACTURER		16
	false,	// PER_SYS_LOG			17
	true,	// PER_SYS_OPTION		18
};
bool xPermissions::adminPerm[PERMISSIONS_MAX] =
{
	true,	// PER_SRV_ORG			0
	true,	// PER_CHG_PGM			1
	true,	// PER_OPR_PGM			2
	true,	// PER_SET_TIME			3
    true,	// PER_SRV_CTRL			4
	true,	// PER_AUTO_OPR			5
    true,	// PER_MANUAL_OPR		6
	true,	// PER_TEACH			7
	true,	// PER_SYS_NORMAL		8
	true,	// PER_SYS_SIGNAL		9
    false,	// PER_SYS_RESET		10
	false,	// PER_SYS_MAINTAIN		11
	true,	// PER_SRV_SAFE			12
	false,	// PER_SRV_MACHINE		13
	true,	// PER_UI_SET			14
	true,	// PER_ADJ_CTRL			15
	false,	// PER_MANUFACTURER		16
	true,	// PER_SYS_LOG			17
	true,	// PER_SYS_OPTION		18
};
#endif

xPermissions::xPermissions(QObject *parent) : QObject(parent)
{
#if defined(Q_WS_WIN)
    currentUser = AdvAdministrator;
#elif FACTORY == FA_YIDAO
    currentUser = AdvAdministrator;
#else
  currentUser = Operater;
#endif
}

xPermissions::~xPermissions(void)
{

}

#if FACTORY == FA_GH
// **********************************
// 马海菲自动化密码设置
// **********************************
// 默认密码
void xPermissions::DefaultPwd(quint8 usr, QByteArray &pwd)
{
	pwd.clear();
	if (usr == AdvOperater)
		pwd.append("11111111");
	else if (usr == Administrator)
		pwd.append("22222222");
	else if (usr == AdvAdministrator)
		pwd.append("9678");
}
#elif FACTORY == FA_CALET
// **********************************
// 凯力特密码设置
// **********************************
// 默认密码
void xPermissions::DefaultPwd(quint8 usr, QByteArray &pwd)
{
	pwd.clear();
	if (usr == AdvOperater)
		pwd.append("11111111");
	else if (usr == Administrator)
		pwd.append("22222222");
	else if (usr == AdvAdministrator)
		pwd.append("CALET299");
}
#elif FACTORY == FA_WETEC
// **********************************
// 威得客密码设置
// **********************************
// 默认密码
void xPermissions::DefaultPwd(quint8 usr, QByteArray &pwd)
{
	pwd.clear();
	if (usr == AdvOperater)
		pwd.append("12345678");
	else if (usr == Administrator)
		pwd.append("22222222");
	else if (usr == AdvAdministrator)
		pwd.append("20060306");
}
#elif FACTORY == FA_KEDA
// **********************************
// 科达密码设置
// **********************************
// 默认密码
void xPermissions::DefaultPwd(quint8 usr, QByteArray &pwd)
{
    pwd.clear();
    if (usr == AdvOperater)
        pwd.append("1111");
    else if (usr == Administrator)
        pwd.append("2222");
    else if (usr == AdvAdministrator)
        pwd.append("20090101");
}
#elif FACTORY == FA_KEHAO
// **********************************
// 科皓密码设置
// **********************************
// 默认密码
void xPermissions::DefaultPwd(quint8 usr, QByteArray &pwd)
{
    pwd.clear();
    if (usr == AdvOperater)
        pwd.append("1111");
    else if (usr == Administrator)
        pwd.append("2222");
    else if (usr == AdvAdministrator)
        pwd.append("KHROBOT8");
}
#elif (FACTORY == FA_SENCHUAN)
// **********************************
// 森川密码设置
// **********************************
// 默认密码
void xPermissions::DefaultPwd(quint8 usr, QByteArray &pwd)
{
	pwd.clear();
	if (usr == AdvOperater)
		pwd.append("11111111");
	else if (usr == Administrator)
		pwd.append("22222222");
	else if (usr == AdvAdministrator)
		pwd.append("sekawa17");
}
#elif (FACTORY == FA_ZHENJIE)
// **********************************
// 震界密码设置
// **********************************
// 默认密码
void xPermissions::DefaultPwd(quint8 usr, QByteArray &pwd)
{
    pwd.clear();
    if (usr == AdvOperater)
        pwd.append("11111111");
    else if (usr == Administrator)
        pwd.append("22222222");
    else if (usr == AdvAdministrator)
        pwd.append("57778022");
}
#elif ((FACTORY == FA_SINROBOT_HC) || (FACTORY == FA_SINROBOT_CN) || (FACTORY == FA_SINROBOT))
// **********************************
// 默认密码
void xPermissions::DefaultPwd(quint8 usr, QByteArray &pwd)
{
    pwd.clear();
    if (usr == AdvOperater)
        pwd.append("11111111");
    else if (usr == Administrator)
        pwd.append("22222222");
    else if (usr == AdvAdministrator)
        pwd.append("20090101");
}
#elif (FACTORY == FA_WEILIHE2)
// **********************************
// 伟力合２
// **********************************
// 默认密码
void xPermissions::DefaultPwd(quint8 usr, QByteArray &pwd)
{
	pwd.clear();
	if (usr == AdvOperater)
		pwd.append("11111111");
	else if (usr == Administrator)
		pwd.append("22222222");
	else if (usr == AdvAdministrator)
		pwd.append("83190039");
}
#else
// **********************************
// 新睿默认密码设置
// **********************************
// 默认密码
void xPermissions::DefaultPwd(quint8 usr, QByteArray &pwd)
{
	pwd.clear();
	if (usr == AdvOperater)
		pwd.append("11111111");
	else if (usr == Administrator)
		pwd.append("22222222");
	else if (usr == AdvAdministrator)
		pwd.append("20090101");
}
#endif

// 得到超级用户密码
void xPermissions::SupperUsrPwd(QByteArray &pwd)
{
	pwd.clear();
	pwd.append("SinRobot");
}
// 得到当前用户的权限
bool xPermissions::GetPermissions(quint8 perm)
{
#if IS_XEDITOR
    return true;
#else
	if (perm >= PERMISSIONS_MAX)
		return false;
	if (currentUser == Operater)
		return oprPerm[perm];
	else if (currentUser == AdvOperater)
		return advOprPerm[perm];
	else if (currentUser == Administrator)
		return adminPerm[perm];
	else if (currentUser == AdvAdministrator)
		return true;
	else if (currentUser == SuperUser)
		return true;
	else
	{
		currentUser = Operater;
		return oprPerm[perm];
	}
#endif
}

// 更改当前用户
bool xPermissions::ChangeUser(quint8 usr)
{
	bool ret = false;
	switch (usr)
	{
	case Operater:
	case AdvOperater:
	case Administrator:
	case AdvAdministrator:
	case SuperUser:
		currentUser = usr;
		emit UserChanged();
		ret = true;
		break;
	}
	return ret;
}

// 注销当前用户
void xPermissions::UserLogout(void)
{
	currentUser = Operater;
	// 写入系统日志
	xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_LOGOUT);
	xSysLog::SaveChange();
	emit UserChanged();
}
