#include <QApplication>
#include <QSettings>
#include "xconfig.h"
#include "cmbprotocol.h"
#include "xstringresource.h"
#include "xtranslator.h"

xTranslator *xLan = 0;

xTranslator::xTranslator(QObject *parent) :	QObject(parent), appTranslator()
{
	quint8 lan;
	xLan = this;
	// 读取系统语言设置
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	lan = settings.value(XPAD_SET_LANGUAGE, LAN_CHINESE_S).toUInt();
	// 设置系统翻译对象
	qApp->installTranslator(&appTranslator);
	// 加载系统当前语言翻译文件
	SetLanguage(lan);
}

xTranslator::~xTranslator(void)
{

}

void xTranslator::SetLanguage(quint8 lan)
{
	switch (lan)
	{
	case LAN_CHINESE_T:			// 繁体中文
		appTranslator.load("xPad_cht", ":/translation");
		break;
	case LAN_ENGLISH:			// 英文
#if FACTORY == FA_CHUANHE
        appTranslator.load("xPad_en_MYS", ":/translation");
#else
		appTranslator.load("xPad_en", ":/translation");
#endif
		break;
    case LAN_RUSSIAN:			// 俄文
        appTranslator.load("xPad_rus", ":/translation");
        break;
    case LAN_TURKISH:			// 土耳其文
        appTranslator.load("xPad_tur", ":/translation");
        break;
    case LAN_VIETNAM:			// 越南文
        appTranslator.load("xPad_viet", ":/translation");
        break;
    case LAN_PORTUGAL:			// 葡萄牙文
        appTranslator.load("xPad_pt", ":/translation");
        break;
	default:					// 简体中文
		appTranslator.load("xPad_chs", ":/translation");
		break;
	}
	xStringResource::retranslateRes(lan);
}
