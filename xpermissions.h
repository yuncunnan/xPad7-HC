#ifndef XPERMISSIONS_H
#define XPERMISSIONS_H

#include <QObject>
#include <QByteArray>

// 中国省份代码
#define BEIJING				11	// 北京市
#define TIANJING			12	// 天津市
#define HEBEI				13	// 河北省
#define SHANXI				14	// 山西省
#define NEIMENGGU			15	// 内蒙古自治区
#define LIAONING			21	// 辽宁省
#define JILING				22	// 吉林省
#define HEILONGJIANG		23	// 黑龙江省
#define SHANGHAI			31	// 上海市
#define JIANGSU				32	// 江苏省
#define ZHEJIANG			33	// 浙江省
#define ANHUI				34	// 安徽省
#define FUJIAN				35	// 福建省
#define JIANGXI				36	// 江西省
#define SHANDONG			37	// 山东省
#define HENAN				41	// 河南省
#define HUBEI				42	// 湖北省
#define HUNAN				43	// 湖南省
#define GUANGDONG			44	// 广东省
#define GUANGXI				45	// 广西壮族自治区
#define HAINAN				46	// 海南省
#define CHONGQING			50	// 重庆市
#define SICHUAN				51	// 四川省
#define GUIZHOU				52	// 贵州省
#define YUNNAN				53	// 云南省
#define XIZHANG				54	// 西藏自治区
#define SHAANXI				61	// 陕西省
#define GANSU				62	// 甘肃省
#define QINGHAI				63	// 青海省
#define NINGXIANG			64	// 宁夏回族自治区
#define XINJIANG			65	// 新疆维吾尔自治区
#define TAIWAN				71	// 台湾省
#define HONGKONG			81	// 香港特别行政区
#define MACAO				82	// 澳门特别行政区
// 定义厂商 ID
#define FA_SINROBOT			(0)                             // 标准版XYZ
#define FA_SINROBOT_JC		(1)                             // 机床版
#define FA_SINROBOT_CN		(2)                             // 标准版_中文軸名稱
#define FA_SINROBOT_HC		(3)                             // HC操作方式
#define FA_SINROBOT_SIDE		(4)                         // 侧取机（原横行->上下，原上下->出入模，其他轴名称暂时未动，只改了双臂报警。）
#define FA_SINROBOT_4AS_YZ	(5)                             // 标准版四轴压铸
// 安徽
#define FA_RUIXIANG			((ANHUI << 8) | 0x0001)         // 滁州瑞祥
// 浙江
#define FA_GH				((ZHEJIANG << 8) | 0x0001)		// 马海菲自动化
#define FA_HAITIAN			((ZHEJIANG << 8) | 0x0002)		// 海天驱动
#define FA_CALET			((ZHEJIANG << 8) | 0x0003)		// 凯力特
#define FA_KINGROBOT		((ZHEJIANG << 8) | 0x0004)		// 国祥机器人
#define FA_SIMANER			((ZHEJIANG << 8) | 0x0005)		// 斯曼尔
#define FA_KEWEI			((ZHEJIANG << 8) | 0x0006)		// 科伟
#define FA_BLUEARROW		((ZHEJIANG << 8) | 0x0007)		// 布鲁艾诺--8455
#define FA_KEHUI            ((ZHEJIANG << 8) | 0x0008)		// 科辉
#define FA_BOAO             ((ZHEJIANG << 8) | 0x0009)		// 搏傲
#define FA_YUANBANG         ((ZHEJIANG << 8) | 0x000A)		// 元邦
#define FA_BLUEARROW_MO		((ZHEJIANG << 8) | 0x000B)		// 布鲁艾诺(磨床)
#define FA_JUXING           ((ZHEJIANG << 8) | 0x000C)		// 聚鑫
#define FA_SAIPULUO			((ZHEJIANG << 8) | 0x000D)		// 赛普罗
#define FA_NBZWF			((ZHEJIANG << 8) | 0x000E)		// 宁波众为发
#define FA_QIHONG           ((ZHEJIANG << 8) | 0x000F)      // 奇泓（黄岩）
#define FA_KEWEI_SOUP		((ZHEJIANG << 8) | 0x0010)		// 科伟给汤机
#define FA_CALET_CN         ((ZHEJIANG << 8) | 0x0011)		// 凯力特中文
#define FA_KEHUI_LANTIAN    ((ZHEJIANG << 8) | 0x0012)		// 科辉蓝天
#define FA_FUSHITONG        ((ZHEJIANG << 8) | 0x0013)		// 温州 富士通
// 江苏
#define FA_JSKJL			((JIANGSU << 8) | 0x0004)		// 常州科捷龙
#define FA_GAOTONG			((JIANGSU << 8) | 0x0005)		// 苏州高通
#define FA_KEHAO			((JIANGSU << 8) | 0x0006)		// 昆山科皓
#define FA_KINGSTRONG       ((JIANGSU << 8) | 0x0007)		// 苏州金实创
#define FA_NEWPARTNER       ((JIANGSU << 8) | 0x0008)		// 昆山新伙伴
#define FA_CHAOQUN          ((JIANGSU << 8) | 0x0009)		// 苏州超群
#define FA_BEIYA            ((JIANGSU << 8) | 0x000A)		// 太仓北雅
#define FA_AIERFA           ((JIANGSU << 8) | 0x000B)           // 苏州艾尔发
// 广东
#define FA_WETEC			((GUANGDONG << 8) | 0x0001)		// 威得客自动化科技
#define FA_SHINI			((GUANGDONG << 8) | 0x0002)		// 信易电热机械
#define FA_BLT              ((GUANGDONG << 8) | 0x0003)		// 布鲁特五金机械
#define FA_HUNGLUNG			((GUANGDONG << 8) | 0x0004)		// 鸿隆机械制造
#define FA_XIONGCHUANG		((GUANGDONG << 8) | 0x0005)		// 雄创自动化机械
#define FA_ZAOYU			((GUANGDONG << 8) | 0x0006)		// 造誉机械
#define FA_KEDA             ((GUANGDONG << 8) | 0x0007)     // 科达自动化机械
#define FA_WENSUI			((GUANGDONG << 8) | 0x0008)     // 文穗塑机
#define FA_XINDA			((GUANGDONG << 8) | 0x0009)		// 鑫达自动化
#define FA_SIGMA			((GUANGDONG << 8) | 0x000A)		// 西格玛自动化
#define FA_GDKJL			((GUANGDONG << 8) | 0x000B)		// 中山科捷龙
#define FA_FUJING			((GUANGDONG << 8) | 0x000C)		// 富井机器人
#define FA_LIYATE			((GUANGDONG << 8) | 0x000D)		// 利雅特自动化
#define FA_FULUDA			((GUANGDONG << 8) | 0x000E)		// 富路达
#define FA_VICTOR			((GUANGDONG << 8) | 0x000F)		// 威特尔
#define FA_SURUI			((GUANGDONG << 8) | 0x0015)		// 速瑞
#define FA_YAHOO			((GUANGDONG << 8) | 0x0016)		// 亚昊
#define FA_HUASHENG			((GUANGDONG << 8) | 0x0017)		// 华盛
#define FA_WEILIHE			((GUANGDONG << 8) | 0x0018)		// 伟力合
#define FA_TUOMU			((GUANGDONG << 8) | 0x0019)		// 拓木
#define FA_BEISHITE			((GUANGDONG << 8) | 0x001A)		// 倍适特
#define FA_YIDAO			((GUANGDONG << 8) | 0x001B)		// 一道
#define FA_WOERDA			((GUANGDONG << 8) | 0x001C)		// 沃尔达
#define FA_KAIBOER          ((GUANGDONG << 8) | 0x001D)     // 凯博尔
#define FA_SONINT           ((GUANGDONG << 8) | 0x001E)     // 硕尼
#define FA_WENJIE			((GUANGDONG << 8) | 0x00A0)		// 文杰智能机械
#define FA_TIANRUI          ((GUANGDONG << 8) | 0x00A1)     // 天锐 王壮益　（只有一个客户有这种需求，其他都新睿标准）
#define FA_JIEJIA_SIDE      ((GUANGDONG << 8) | 0x00A2)		// 捷嘉标准机
#define FA_CHUANHE			((GUANGDONG << 8) | 0x00A3)		// 川河
#define FA_BEISHITE_CN      ((GUANGDONG << 8) | 0x00A4)		// 倍适特中文
#define FA_MINGRUI			((GUANGDONG << 8) | 0x00A5)		// 单臂三轴备料（ＡＢＣ轴控制另外一台小机器）
#define FA_WEILIHE2			((GUANGDONG << 8) | 0x00A6)		// 伟力合(密码83190039)
#define FA_HAMO             ((GUANGDONG << 8) | 0x00A7)		// 哈馍
#define FA_VICTOR_SPECIAL	((GUANGDONG << 8) | 0x00A8)		// 威特尔-非标
#define FA_MIDEA			((GUANGDONG << 8) | 0x00A9)		// 美的
// 上海
#define FA_RUIBEI			((SHANGHAI << 8) | 0x0001)		// 睿贝
#define FA_ZHENJIE			((SHANGHAI << 8) | 0x0002)		// 震界
#define FA_HUIZE_FEIBIAO    ((SHANGHAI << 8) | 0x0003)		// 卉喆非标
#define FA_HUIZE            ((SHANGHAI << 8) | 0x0004)		// 卉喆
// 福建省
#define FA_JINBOYUE			((FUJIAN << 8) | 0x0001)        // 金博跃-标准
#define FA_JINBOYUE_SPECIAL	((FUJIAN << 8) | 0x0002)        // 金博跃-特殊定制
// 天津
#define FA_SENCHUAN			((TIANJING << 8) | 0x0001)		// 森川-3073
// 山东
#define FA_SHUNWANG			((SHANDONG << 8) | 0x0001)		// 顺旺


// 定义当前厂商 ID
#define FACTORY				FA_SINROBOT//FA_TIANRUI//FA_TIANRUI//FA_MIDEA//FA_TIANRUI//FA_XIONGCHUANG//FA_BEISHITE_CN//FA_SINROBOT//FA_VICTOR_SPECIAL//FA_SINROBOT_CN//FA_BEISHITE_CN//FA_VICTOR_SPECIAL

// 定义用户权限
#define PER_SRV_ORG			0
#define PER_CHG_PGM			1
#define PER_OPR_PGM			2
#define PER_SET_TIME		3
#define PER_SRV_CTRL		4
#define PER_AUTO_OPR		5
#define PER_MANUAL_OPR		6
#define PER_TEACH			7
#define PER_SYS_NORMAL		8
#define PER_SYS_SIGNAL		9
#define PER_SYS_RESET		10
#define PER_SYS_MAINTAIN	11
#define PER_SRV_SAFE		12
#define PER_SRV_MACHINE		13
#define PER_UI_SET			14
#define PER_ADJ_CTRL		15
#define PER_MANUFACTURER	16
#define PER_SYS_LOG			17
#define PER_SYS_OPTION		18

#define PERMISSIONS_MAX		19

class xPermissions : public QObject
{
	Q_OBJECT
public:
	explicit xPermissions(QObject *parent = 0);
	~xPermissions(void);

	enum User
	{
		Operater = 0x00,
		AdvOperater = 0x01,
		Administrator = 0x02,
		AdvAdministrator = 0x03,
		SuperUser = 0x04
	};

	static quint8 GetCurrentUser(void) { return currentUser; }
	static void DefaultPwd(quint8 usr, QByteArray &pwd);
	static void SupperUsrPwd(QByteArray &pwd);
	static bool GetPermissions(quint8 perm);
	bool ChangeUser(quint8 usr);
	void UserLogout(void);
	
signals:
	void UserChanged(void);

private:
	static quint8 currentUser;
	static bool oprPerm[PERMISSIONS_MAX];
	static bool advOprPerm[PERMISSIONS_MAX];
	static bool adminPerm[PERMISSIONS_MAX];
	
};

#endif // XPERMISSIONS_H
