#ifndef XCONFIG_H
#define XCONFIG_H

#include <QtGlobal>
#include "xpermissions.h"

// 定义是否是Editor版本
#define IS_XEDITOR                  0
//  定义最大软件行程
#define MAX_DISTANCE                6000000
#define MAX_DEGREE					36000
// 定义操作器软件版本号宏
#define XPAD_SVER					"SV14.01-240809"
// 定义操作器类型字符串
#define XPAD_TYPE_STR				"SR6807A"

// 是否使用通讯
#if IS_XEDITOR
#define PENDANT_PROTOCOL			0
#else

#if defined(Q_WS_WIN)
#define PENDANT_PROTOCOL			1   // pc端改这个不影响linux
#else
#define PENDANT_PROTOCOL			1
#endif
#endif
// 是否是模拟器画面(模拟器界面400*640 某些界面文字大小，坐标会有调整)
#define SIMULATOR                   0           // 编译模拟器时，打开-640.pro文件，再将 SIMULATOR定义为true

// 通讯方式
#define CONNECT_BY_NET              0
// 进程隐藏/显示
#define MULPROC_ENABLE              1
// 时间刻度
#define TIME_BASE                   10        // 10ms,另有100ms,默认10,需与主板一致
// 运行刻度
#define SCALE_BASE					10.0

// 定义串口参数
#if defined(Q_WS_WIN)
#define MB_PORT						"\\\\.\\COM3"
#elif defined(Q_WS_X11)
#define MB_PORT						"/dev/ttyS1"
#elif defined(Q_WS_QWS)
#endif
#define MB_BAUD						115200
#define MB_PARITY					'N'
#define MB_DATABITS					8
#define MB_STOPBITS					1
// *************************************************
#define SUB_FUN_TMC429				0x0010          // 指数减数
#define SUB_FUN_ENCODER				0x0020          // 编码器
#define SUB_FUN_EUROMAP				0x0040          // 欧规版
#define SUB_FUN_LOCK_ALARM          0x0080          // 错误锁定

#define SUB_FUN_KEYMAP				0x0100          // 按键
#define SUB_FUN_SDIR				0x0200          // 方向设置
#define SUB_LOOP_INTERVAL			0x0400          // 循环定位间隔
#define SUB_VACUUM					0x0800          // 治具组

#define SUB_DOOR_RESET				0x2000          // 增加取物失败时，开关安全门程序结束
#define SUB_3_AXES					0x4000          // 有此功能，去读取物理上存在几个轴
#define SUB_IN_ANTI_CHECK_HOME_TAIL_LOOP_FREE			0x8000	// 检测扩展输入无信号//原点归位找前后端参数/单轴循环定位的自由点模式

#define SUB_FUN2_JERK               0x00010000      // 有此功能暴露jerk选项
#define SUB_FUN2_IO_BMP             0x00020000      // io口映射功能
#define SUB_FUN2_WAIT_VAR2          0x00040000      // 等待指令带大于小于功能
#define SUB_FUN2_EXT_POS            0x00080000      // 扩展定位指令,使用时路径就不要用了

#define SUB_FUN2_ROTATE             0x00100000      // 增加横行倒角选项
#define SUB_FUN2_X_B_TRAVE_SAFE		0x00200000  	// 增加引拔轴横行时安全区选项 for v3.26
#define SUB_FUN2_VISION             0x00400000      // 视觉功能
#define SUB_FUN2_IFTIME             0x00800000      // IF指令超时时间功能

#define SUB_FUN2_CAN_IMM            0x02000000      //Canopen IMM板功能
#define SUB_FUN2_MBVISION           0x04000000      //MB视觉功能
#define SUB_FUN2_LOOP_MATRIX		0x08000000      // loopmatrix指令输送带功能

#define SUB_FUN2_LOOP_MATRIX_EXT    0x10000000      //矩阵增加各轴速度
#define SUB_DOOR_QUERY				0x20000000      // 信易安全门询问（信易专用）
#define SUB_FUN2_MAIN64_BITS        0x40000000      // 主板IO64位

#define SUB_FUN2_LOOP_FREE_200      ((quint64)0x01<<32)      // 循环定位200个点

// ********************UI*****************************
#define FUN_UI_WAIT_VALID_TIME      (1<<0)//操作器的等待指令有，有效时间功能。
// *************************************************
// 定义界面
// *************************************************
// 是否使用模式选择开关
#if (FACTORY == FA_SHINI)
#define SELECT_SWITCH_USE			0
#else
#define SELECT_SWITCH_USE			0
#endif
// 参数保存成功提示
#define UI_SAVED_TIP				1
// 安全开关提示
#if ((FACTORY == FA_SHINI) || (FACTORY == FA_WETEC))
#define UI_SAFESW_TIP				1
#else
#define UI_SAFESW_TIP				1
#endif

// 安全开关默认不使用
#if (FACTORY == FA_SINROBOT)
#define SAFE_SWITCH_USE             false
#else
#define SAFE_SWITCH_USE             false
#endif
// 系统伺服轴设置
#define UI_SRV_4					0	// 正臂上下 - 正臂引拔 - 横行 - 副臂上下
#define UI_SRV_5					1	// 正臂上下 - 正臂引拔 - 横行 - 副臂上下 - 副臂引拔
#define UI_SRV_6					2	// 正臂上下 - 正臂引拔 - 横行 - 副臂上下 - 副臂引拔 - 扩展
#define UI_SRV_4_5_6				3	// 副臂引拔和扩展伺服可以配置
//#if FACTORY == FA_SHINI
//#define UI_SRV_CFG					UI_SRV_5
//#else
#define UI_SRV_CFG					UI_SRV_4_5_6
//#endif*
// ****************************************
// 定义机械手扩展版本号宏，一个字节的软件描述：高4位表示类别，低4位表示子类别。
// ****************************************
#define ROBOTARM_TYPE_TRISV_PAD_S	0xA1			// 触屏三轴单臂
#define ROBOTARM_TYPE_TRISV_PAD_D	0xA2			// 触屏三轴双臂
#define ROBOTARM_TYPE_SIXSV_PAD_A	0xA3			// 触屏六轴双臂	正引拔-正上下-[副引拔]-副上下-横行-[扩展]
#define ROBOTARM_TYPE_SIXSV_PAD_B	0xA4			// 触屏六轴单臂	引拔-上下-旋转-倒角-横行-[扩展]
#define ROBOTARM_TYPE_DUOSV_PAD_HS	0xA5			// 触屏两轴单臂	引拔-横行
#define ROBOTARM_TYPE_DUOSV_PAD_HD	0xA6			// 触屏两轴双臂	引拔-横行
#define ROBOTARM_TYPE_DUOSV_PAD_VS	0xA7			// 触屏两轴单臂	上下-横行
#define ROBOTARM_TYPE_DUOSV_PAD_VD	0xA8			// 触屏两轴双臂	上下-横行
#define ROBOTARM_TYPE_SIXSV_PAD_C	0xAA			// 触屏六轴双主臂	正引拔-正上下-[副引拔]-副上下-横行-[扩展] 气动双旋转 气动双倒角
#define ROBOTARM_TYPE_TRISV_PAD_T1S	0xC1			// 触屏三轴T1单臂	引拔-上下-横行
#define ROBOTARM_TYPE_TRISV_PAD_T1D	0xC2			// 触屏三轴T1双臂	引拔-上下-横行
#define ROBOTARM_TYPE_SIXSV_PAD_T1D	0xC3			// 触屏六轴T1双臂
#define ROBOTARM_TYPE_SIXSV_PAD_E0	0xE0			// 触屏三六轴高速三轴
#define ROBOTARM_TYPE_SIXSV_PAD_E3	0xE3			// 触屏三六轴双臂
#define ROBOTARM_TYPE_SIXSV_PAD_E4	0xE4			// 触屏三六轴单臂
#define ROBOTARM_TYPE_SIXSV_PAD_E5	0xE5			// 触屏三六轴双臂双塑机
#define ROBOTARM_TYPE_SIXSV_PAD_E6	0xE6			// 触屏三六轴单臂双塑机
#define ROBOTARM_TYPE_SIXSV_PAD_E7	0xE7			// 触屏三六轴--双三轴版
#define ROBOTARM_TYPE_SIXSV_PAD_E8	0xE8			// 触屏三六轴--信易ST5
#define ROBOTARM_TYPE_SIXSV_PAD_YZ	0xD1			// 触屏三六轴双臂压铸
#define ROBOTARM_TYPE_SIXSV_PAD_F3	0xF3			// 触屏三六轴高速双臂
#define ROBOTARM_TYPE_SIXSV_PAD_F4	0xF4			// 触屏三六轴高速单臂
#define ROBOTARM_TYPE_SIXSV_PAD_F5	0xF5			// 触屏三六轴双臂高速双塑机
#define ROBOTARM_TYPE_SIXSV_PAD_F6	0xF6			// 触屏三六轴单臂高速双塑机
#define ROBOTARM_TYPE_SIXSV_PAD_F7	0xF7			// 触屏三六轴-高速双三轴版
#define ROBOTARM_TYPE_SIXSV_PAD_F8	0xF8			// 触屏三六轴-高速信易ST5

//H750版本
#define BOARD_VERSION_ECAT                  0XE0
#define BOARD_VERSION_ECAT_CANOPEN          0XE1    //双总线
#define BOARD_VERSION_H750_6AXIS            0X70    //H750高速六轴版本
#define BOARD_VERSION_H750_DVS              0X71            //五轴驱控一体//六轴驱控一体？
#define BOARD_VERSION_H750_5AXIS            0X72    //H750高速五轴轴版本（0x71F3 750三六轴高速双臂,0x71F4 750三六轴高速单臂）

//手控器主芯片版本
enum BoardType
{
	BoardOther = 0,
	BoardA40i_I,
	BoardT113,
	BoardA40i_II
};

// *************************************************
// 定义系统语言
// *************************************************
#define LAN_CHINESE_S				0			// 简体中文
#define LAN_CHINESE_T				1			// 繁体中文
#define LAN_ENGLISH					2			// 英文
#define LAN_VIETNAM					3			// 越南文
#define LAN_RUSSIAN					4			// 俄文
#define LAN_TURKISH					5			// 土耳其文
#define LAN_PORTUGAL				6			// 葡萄牙文
#define LAN_POLAND                  7			// 波兰文
#define LAN_SPAIN                   8			// 西班牙文
#define LAN_THAILAND                9			// 泰国
#define LAN_INDONESIA               10			// 印尼

// *************************************************
// 定义系统文件目录
// *************************************************
// 定义文件扩展名
#define FAINF_FILE_EXT				".png"		// 厂商定制图片文件扩展名
#define IO_NAME_EXT					".cfg"		// IO端口名称定义文件扩展名
#define PAR_BAK_EXT					".bak"		// 参数设置备份文件扩展名

#define PGM_FILE_EXT				".xpgm"		// 教导程序文件扩展名
#define ALFA_FILE_EXT				".alfa"		// ALFA程序文件扩展名
#define LOG_FILE_EXT				".db"		// 系统日志文件扩展名
#define RCM_UPG_EXT					".hex"		// 主控模块升级包扩展名
#define RCM_UPG_EXT_H75             ".h75"		// H750主控模块升级包扩展名
// 当前程序工作路径
#if defined(Q_WS_QWS)

#	define XPAD_ARGUMENT			"-qws"
#elif defined(Q_WS_X11)
#	define XPAD_CURRENT_PATH		"/opt/xPad/linux/xPad_x86"
#	define XPAD_ARGUMENT			""
#elif defined(Q_WS_WIN)
#	define XPAD_CURRENT_PATH		"./"
#	define XPAD_ARGUMENT			""
#endif
// 定义系统目录
//#if (FACTORY == FA_JINBOYUE)
#define TEMP_PATH                   "temp"					// 教导程序文件夹(相对路径)
//#endif
#define PROGRAM_PATH				"program"					// 教导程序文件夹(相对路径)
#define ALFA_PATH                   "alfa"                      // Alfa程序文件夹(相对路径)
#define TEMPLATE_PATH				"template"					// 非教导程序文件夹(相对路径)
#define SYSLOG_PATH					"log"						// 系统日志文件夹(相对路径)
#define IMAGE_PATH					"img"						//
#define USB_PATH                    "usb"
// 系统图片文件夹(相对路径)
#if defined(Q_WS_QWS)
#define XPAD_USB_PATH			"/mnt/usb/sda1/"             // Linux USB 存储器路径(绝对路径)
#elif defined(Q_WS_WIN)
#define XPAD_USB_PATH			"/usb/"					// Windows USB 存储器路径(绝对路径)
#endif
// 触摸屏校准文件
#if defined(Q_WS_QWS)
#define XPAD_TOUCH_CAL				"/etc/pointercal"
#endif
// 系统日志文件
#define XPAD_SYSLOG_FILE			"systemlog"LOG_FILE_EXT
#define XPAD_SYSLOG_MAX				50000
// io端口名称文件
#define XPAD_PORT_FILE              "ionames.cfg"				// 端口名称文件
#define CHINESE                     "chineses"                  //中文
#define ENGLISH                     "english"                   //英文
// 系统配置文件
#define XPAD_SETTING_FILE			"xPad.ini"					// 系统配置文件
#define XPAD_SET_CURPGM				"system/currentprogram"		// 当前程序名称
#define XPAD_SET_TEMPLATE			"system/template"			// 非教导模式

#define XPAD_SET_ALFAMODE			"system/alfamode"			// 天行模式
#define XPAD_SET_ALFAPGM			"system/alfaprogram"		// 天行模式程序名称

#define XPAD_SET_IP                 "system/ip"
#define XPAD_SET_SUBMASK            "system/submask"
#define XPAD_SET_GATEWAY            "system/gateway"
#define XPAD_SET_SRVSPD				"servo/rel_speed"			// 伺服相对速度
#define XPAD_SET_PAVERCAT			"servo/paver_cat_pos"		// 正臂下行取物点位置
#define XPAD_SET_PAVERREL			"servo/paver_rel_pos"
#define XPAD_SET_PAVERWAIT			"servo/paver_wait_pos"
#define XPAD_SET_PAHORCAT			"servo/pahor_cat_pos"
#define XPAD_SET_PAHORREL			"servo/pahor_rel_pos"
#define XPAD_SET_PAHORWAIT			"servo/pahor_wait_pos"
#define XPAD_SET_TRVWAIT			"servo/trv_wait_pos"		// 横行轴原点复归后待机位置
#define XPAD_SET_RAVERCAT			"servo/raver_cat_pos"		// 副臂下行取物点位置
#define XPAD_SET_RAVERREL			"servo/raver_rel_pos"
#define XPAD_SET_RAVERWAIT			"servo/raver_wait_pos"
#define XPAD_SET_RAHORCAT			"servo/rahor_cat_pos"
#define XPAD_SET_RAHORREL			"servo/rahor_rel_pos"
#define XPAD_SET_RAHORWAIT			"servo/rahor_wait_pos"
#define XPAD_SET_EXTCAT				"servo/ext_cat_pos"
#define XPAD_SET_EXTREL				"servo/ext_rel_pos"
#define XPAD_SET_EXTWAIT			"servo/ext_wait_pos"
#define XPAD_SET_TRVRELPOS			"servo/trv_rel_pos"			// 横行置物点位置
#define XPAD_SET_TRVCATPOS			"servo/trv_cat_pos"			// 横行取物点位置
#define XPAD_SET_LANGUAGE			"ui/language"				// 界面语言
#define XPAD_SET_SCRSVER			"ui/screensaver_sec"		// 屏保时间设置
#define XPAD_SET_BAKLIGHT			"ui/backlight"				// 背光设置
#define XPAD_SET_USESHAKE			"ui/useshake"				// 使用震动反馈
#define XPAD_SET_KEYBELL			"ui/keybell"				// 使用按键音
#define XPAD_SET_TOUCHBELL			"ui/touchbell"				// 使用触屏音
#define XPAD_SET_BELLFREQ			"ui/bellfreq"				// 按键音频率
#define XPAD_SET_SWITCHUSE			"ui/switchon"				// 安全開關使用
#define XPAD_SET_ALWAYSON			"ui/alwayson"				// 原點歸位安全開關長按
// 开机图片文件
#define XPAD_SPLASH_NAME			IMAGE_PATH"/Splash"FAINF_FILE_EXT
// 主画面壁纸文件
#define XPAD_WALLPAPER_NAME			IMAGE_PATH"/Wallpaper"FAINF_FILE_EXT
// 系统信息图片文件
#define XPAD_INFORMATION_NAME		IMAGE_PATH"/Information"FAINF_FILE_EXT
// XPAD 主程序文件
#if defined(Q_WS_QWS)
#	define XPAD_PGM_NAME			"xPad"
#	define XPAD_PGM_PATHNAME		XPAD_USB_PATH"xPad"
#elif defined(Q_WS_X11)
#	define XPAD_PGM_NAME			"xPad"
#	define XPAD_PGM_PATHNAME		XPAD_USB_PATH"xPad"
#elif defined(Q_WS_WIN)
#	define XPAD_PGM_NAME			"xPad.exe"
#	define XPAD_PGM_PATHNAME		XPAD_USB_PATH"xPad.exe"
#endif
// IO端口名称文件
#define XPAD_IO_NAME				"ionames"IO_NAME_EXT
// 参数设置备份文件结构
#define PARBAK_ALM_TIMES			"system/alarm_times"		// 报警器鸣叫次数
#define PARBAK_ALM_INTERVAL			"system/alarm_interval"		// 报警器鸣叫间隔
#define PARBAK_LANGUAGE				"system/language"			// 语言设置
#define PARBAK_ROTATE				"system/rotate_travel"		// 横行时正臂倒角状态
#define PARBAK_DOOR					"system/door_pause"			// 自动运行时开安全门
#define PARBAK_RVERSRV_USE			"system/rversrv_use"		// 副臂上下轴伺服使用
#define PARBAK_RHORSRV_USE			"system/rhorsrv_use"		// 副臂引拔轴伺服使用
#define PARBAK_RUNNER_USE			"system/runner_use"			// 气动副臂使用
#define PARBAK_RUNNER_DOWN_USE		"system/runner_down_use"	// 气动副臂下位电眼使用
#define PARBAK_RUNNER_ADVANCE_USE	"system/runner_advance_use"	// 气动副臂前进电眼使用
#define PARBAK_RUNNER_RETURN_USE	"system/runner_return_use"	// 气动副臂后退电眼使用
#define PARBAK_ADJUST_USE			"system/adjust_use"			// 调位使用
#define PARBAK_HOME_INMOLD			"system/home_inmold"		// 原点在模内
#define PARBAK_EXTSRV_USE			"system/extsrv_use"			// 扩展轴伺服使用
#define PARBAK_MCP					"system/mcp_usage"			// 关模完成信号配置
#define PARBAK_IMOP					"system/imop_usage"			// 开模中间信号配置
#define PARBAK_MMOP					"system/mmop_usage"			// 开中板模确认信号配置
#define PARBAK_ROTATE_IN			"system/rotate_inmold"		// 模内倒角使用
#define PARBAK_WAIT_OUTMOULD		"system/wait_outmould"		// 待机选项
#define PARBAK_PLAN					"system/plan"				// 计划生产数量
#define PARBAK_REMIND				"system/remind"				// 生产数量提醒
#define PARBAK_REJECT				"system/reject"				// 不良品数量报警
#define PARBAK_RCM_POLARITY			"system/rcm_polarity"		// 主控模块信号极性
#define PARBAK_EM1_POLARITY			"system/em1_polarity"		// 扩展模块1信号极性
#define PARBAK_EM2_POLARITY			"system/em2_polarity"		// 扩展模块2信号极性
#define PARBAK_EM3_POLARITY			"system/em3_polarity"		// 扩展模块3信号极性
#define PARBAK_EM4_POLARITY			"system/em4_polarity"		// 扩展模块4信号极性
#define PARBAK_MAIN_OUTPOLARITY		"system/main_outpolarity"	// 主控模块输出信号极性
#define PARBAK_EM1_OUTPOLARITY		"system/em1_outpolarity"	// 扩展模块1输出信号极性
#define PARBAK_EM2_OUTPOLARITY		"system/em2_outpolarity"	// 扩展模块2输出信号极性
#define PARBAK_EM3_OUTPOLARITY		"system/em3_outpolarity"	// 扩展模块3输出信号极性
#define PARBAK_EM4_OUTPOLARITY		"system/em4_outpolarity"	// 扩展模块4输出信号极性
#define PARBAK_RCM_IGNORE			"system/rcm_ignore"			// 主控模块信号报警设置
#define PARBAK_EM1_IGNORE			"system/em1_ignore"			// 扩展模块1信号报警设置
#define PARBAK_EM2_IGNORE			"system/em2_ignore"			// 扩展模块2信号报警设置
#define PARBAK_EM3_IGNORE			"system/em3_ignore"			// 扩展模块3信号报警设置
#define PARBAK_EM4_IGNORE			"system/em4_ignore"			// 扩展模块4信号报警设置
#define	PARBAK_RCM_NOALM			"system/rcm_noalm"			// 主控模块模内不报警
#define	PARBAK_EM1_NOALM			"system/em1_noalm"			// 扩展模块1模内不报警
#define	PARBAK_EM2_NOALM			"system/em2_noalm"			// 扩展模块2模内不报警
#define	PARBAK_EM3_NOALM			"system/em3_noalm"			// 扩展模块3模内不报警
#define	PARBAK_EM4_NOALM			"system/em4_noalm"			// 扩展模块4模内不报警
#define PARBAK_JIG_USE				"system/jig_use"			// 换治具使用
#define PARBAK_PROC2_USE            "system/proc2_use"          // 进程2使用
#define PARBAK_PROC3_USE            "system/proc3_use"          // 进程3使用
#define PARBAK_IP                   "system/ip_low"             // ip地址
#define PARBAK_SUBMASK              "system/submask_low"
#define PARBAK_GATEWAY              "system/gateway_low"
#define PARBAK_OIL_INTERVAL         "system/oil_interval"
#define PARBAK_OIL_TIME             "system/oil_time"
#define PARBAK_OIL_USE              "system/oil_use"
#define PARBAK_ROTATE_USE           "system/rotate_use"         // 气动倒角
#define PARBAK_RUN_RATOTE_USE       "system/run_rotate_arm"
#define PARBAK_DOOR_RESET_USE       "system/door_reset"
#define PARBAK_EXTEND_BIT_USE       "system/extend_bit"
#define PARBAK_OIL_USE_CTRL         "system/oil_use_ctrl"
#define PARBAK_VISION1_IP           "system/vision1_ip"
#define PARBAK_VISION2_IP           "system/vision2_ip"
#define PARBAK_VISION3_IP           "system/vision3_ip"
#define PARBAK_VISION4_IP           "system/vision4_ip"
#define PARBAK_VISION5_IP           "system/vision5_ip"
#define PARBAK_VISION6_IP           "system/vision6_ip"
#define PARBAK_VISION7_IP           "system/vision7_ip"
#define PARBAK_VISION8_IP           "system/vision8_ip"
#define PARBAK_VISION1_PORT         "system/vision1_port"
#define PARBAK_VISION2_PORT         "system/vision2_port"
#define PARBAK_VISION3_PORT         "system/vision3_port"
#define PARBAK_VISION4_PORT         "system/vision4_port"
#define PARBAK_VISION5_PORT         "system/vision5_port"
#define PARBAK_VISION6_PORT         "system/vision6_port"
#define PARBAK_VISION7_PORT         "system/vision7_port"
#define PARBAK_VISION8_PORT         "system/vision8_port"
#define PARBAK_VISION1_TRIGGER      "system/vision1_trigger"
#define PARBAK_VISION2_TRIGGER      "system/vision2_trigger"
#define PARBAK_VISION3_TRIGGER      "system/vision3_trigger"
#define PARBAK_VISION4_TRIGGER      "system/vision4_trigger"
#define PARBAK_VISION5_TRIGGER      "system/vision5_trigger"
#define PARBAK_VISION6_TRIGGER      "system/vision6_trigger"
#define PARBAK_VISION7_TRIGGER      "system/vision7_trigger"
#define PARBAK_VISION8_TRIGGER      "system/vision8_trigger"
#define PARBAK_VISION1_OUTVAR       "system/vision1_outvar"
#define PARBAK_VISION2_OUTVAR       "system/vision2_outvar"
#define PARBAK_VISION3_OUTVAR       "system/vision3_outvar"
#define PARBAK_VISION4_OUTVAR       "system/vision4_outvar"
#define PARBAK_VISION5_OUTVAR       "system/vision5_outvar"
#define PARBAK_VISION6_OUTVAR       "system/vision6_outvar"
#define PARBAK_VISION7_OUTVAR       "system/vision7_outvar"
#define PARBAK_VISION8_OUTVAR       "system/vision8_outvar"
// 伺服参数-机械最大行程
#define PARBAK_HOR_MAXLEN			"servo/hor_maxlen"			// 正/副臂原点位置机械距离
#define PARBAK_HOR_MINLEN			"servo/hor_minlen"			// 正/副臂最小安全距离
// 伺服参数-软件最大行程
#define PARBAK_PVER_SOFTLEN			"servo/pver_softlen"		// 正臂上下轴最大软件行程
#define PARBAK_TRAV_SOFTLEN			"servo/trav_softlen"		// 横行轴最大软件行程
#define PARBAK_RVER_SOFTLEN			"servo/rver_softlen"		// 副臂上下轴最大软件行程
#define PARBAK_EXTE_SOFTLEN			"servo/exte_softlen"		// 扩展轴最大软件行程
// 伺服参数-安全区
#define PARBAK_PVER_WAIT			"servo/pver_wait"			// 正臂上下轴上位安全区
#define PARBAK_RVER_WAIT			"servo/rver_wait"			// 副臂上行模内待机位置
#define PARBAK_TRAV_OMIN			"servo/trav_omin"			// 横行轴模外安全区起点
#define PARBAK_TRAV_OMAX			"servo/trav_omax"			// 横行轴模外安全区终点
#define PARBAK_TRAV_OMIN2			"servo/trav_omin2"			// 横行轴模外安全区2起点
#define PARBAK_TRAV_OMAX2			"servo/trav_omax2"			// 横行轴模外安全区2终点
#define PARBAK_TRAV_IMIN			"servo/trv_imin"			// 横行轴模内安全区起点
#define PARBAK_TRAV_IMAX			"servo/trv_imax"			// 横行轴模内安全区终点
#define PARBAK_PHOR_IMIN			"servo/phor_imin"			// 正臂引拔轴模内安全区起点
#define PARBAK_PHOR_IMAX			"servo/phor_imax"			// 正臂引拔轴模内安全区终点
#define PARBAK_RHOR_IMIN			"servo/rhor_imin"			// 副臂引拔轴模内安全区起点
#define PARBAK_RHOR_IMAX			"servo/rhor_imax"			// 副臂引拔轴模内安全区终点
#define PARBAK_MIN_ROT              "servo/min_rot"
#define PARBAK_MAX_ROT              "servo/min_rot"
#define PARBAK_MIN_TRV              "servo/min_trv"
#define PARBAK_MAX_TRV              "servo/min_trv"
#define PARBAK_RHOR_ZAMIN           "servo/rhor_zamin"
#define PARBAK_RHOR_ZAMAX           "servo/rhor_zamax"
#define PARBAK_RHOR_TRVMIN            "servo/rhor_trvmin"
#define PARBAK_RHOR_TRVMAX            "servo/rhor_trvmax"
#define PARBAK_EXT_TRVMIN             "servo/ext_trvmin"
#define PARBAK_EXT_TRVMAX             "servo/ext_trvmax"
#define PARBAK_EXT_INMOLDMIN             "servo/ext_inmoldmin"
#define PARBAK_EXT_INMOLDMAX             "servo/ext_inmoldmax"
#define PARBAK_PHOR_TRVMIN          "servo/phor_trvmin"
#define PARBAK_PHOR_TRVMAX          "servo/phor_trvmax"
// 快速定位
#define PARBAK_TRAV_WAIT_POS			"servo/trav_wait_pos"			// 横行轴待机位置
#define PARBAK_TRAV_REL_POS				"servo/trav_rel_pos"			// 横行轴置物位置
#define PARBAK_TRAV_CAT_POS             "servo/trav_cat_pos"			// 横行轴取物位置
#define PARBAK_PVER_CAT_POS				"servo/pver_cat_pos"			// 正臂上下轴取物位置
#define PARBAK_PVER_REL_POS				"servo/pver_rel_pos"
#define PARBAK_PVER_WAIT_POS			"servo/pver_wait_pos"
#define PARBAK_PHOR_CAT_POS				"servo/phor_cat_pos"
#define PARBAK_PHOR_REL_POS				"servo/phor_rel_pos"
#define PARBAK_PHOR_WAIT_POS			"servo/phor_wait_pos"
#define PARBAK_RVER_CAT_POS				"servo/rver_cat_pos"			// 副臂上下轴取物位置
#define PARBAK_RVER_REL_POS				"servo/rver_rel_pos"
#define PARBAK_RVER_WAIT_POS			"servo/rver_wait_pos"
#define PARBAK_RHOR_CAT_POS				"servo/rhor_cat_pos"
#define PARBAK_RHOR_REL_POS				"servo/rhor_rel_pos"
#define PARBAK_RHOR_WAIT_POS			"servo/rhor_wait_pos"
#define PARBAK_EXT_CAT_POS				"servo/ext_cat_pos"
#define PARBAK_EXT_REL_POS				"servo/ext_rel_pos"
#define PARBAK_EXT_WAIT_POS				"servo/ext_wait_pos"
// 原点偏移
#define PARBAK_X_OFFSET             "servo/x_offset"
#define PARBAK_Y_OFFSET             "servo/y_offset"
#define PARBAK_Z_OFFSET             "servo/z_offset"
#define PARBAK_A_OFFSET             "servo/a_offset"
#define PARBAK_B_OFFSET             "servo/b_offset"
#define PARBAK_C_OFFSET             "servo/c_offset"
// 原点待机点
#define PARBAK_X_HOME_POS           "servo/x_home_pos"
#define PARBAK_Y_HOME_POS           "servo/y_home_pos"
#define PARBAK_Z_HOME_POS           "servo/z_home_pos"
#define PARBAK_A_HOME_POS           "servo/a_home_pos"
#define PARBAK_B_HOME_POS           "servo/b_home_pos"
#define PARBAK_C_HOME_POS           "servo/c_home_pos"
// 模
#define PARBAK_X_MOD                "servo/x_mod"
#define PARBAK_Y_MOD                "servo/y_mod"
#define PARBAK_Z_MOD                "servo/z_mod"
#define PARBAK_A_MOD                "servo/a_mod"
#define PARBAK_B_MOD                "servo/b_mod"
#define PARBAK_C_MOD                "servo/c_mod"
// 编码器
#define PARBAK_ENCODER_X             "servo/x_encoder"
#define PARBAK_ENCODER_Y             "servo/y_encoder"
#define PARBAK_ENCODER_Z             "servo/z_encoder"
#define PARBAK_ENCODER_A             "servo/a_encoder"
#define PARBAK_ENCODER_B             "servo/b_encoder"
#define PARBAK_ENCODER_C             "servo/c_encoder"
// 伺服参数-正臂引拔轴速度/加速度
#define PARBAK_PHOR_SPD				"servo/phor_spd"			// 正臂引拔轴速度
#define PARBAK_PHOR_ACC				"servo/phor_acc"			// 正臂引拔轴加速度
#define PARBAK_PHOR_JERK			"servo/phor_jerk"			// 正臂引拔轴加速度
// 伺服参数-正臂上下轴速度/加速度
#define PARBAK_PVER_SPD				"servo/pver_spd"			// 正臂上下轴速度
#define PARBAK_PVER_ACC				"servo/pver_acc"			// 正臂上下轴加速度
#define PARBAK_PVER_JERK			"servo/pver_jerk"			// 正臂上下轴加速度
// 伺服参数-横行轴速度/加速度
#define PARBAK_TRAV_SPD				"servo/trav_spd"			// 横行轴速度
#define PARBAK_TRAV_ACC				"servo/trav_acc"			// 横行轴加速度
#define PARBAK_TRAV_JERK			"servo/trav_jerk"			// 横行轴加速度
// 伺服参数-副臂引拔轴速度/加速度
#define PARBAK_RHOR_SPD				"servo/rhor_spd"			// 副臂引拔轴速度
#define PARBAK_RHOR_ACC				"servo/rhor_acc"			// 副臂引拔轴加速度
#define PARBAK_RHOR_JERK			"servo/rhor_jerk"			// 副臂引拔轴加速度
// 伺服参数-副臂上下轴速度/加速度
#define PARBAK_RVER_SPD				"servo/rver_spd"			// 副臂上下轴速度
#define PARBAK_RVER_ACC				"servo/rver_acc"			// 副臂上下轴加速度
#define PARBAK_RVER_JERK			"servo/rver_jerk"			// 副臂上下轴加速度
// 伺服参数-扩展轴速度/加速度
#define PARBAK_EXTE_SPD				"servo/exte_spd"			// 扩展轴速度
#define PARBAK_EXTE_ACC				"servo/exte_acc"			// 扩展轴加速度
#define PARBAK_EXTE_JERK			"servo/exte_jerk"			// 扩展轴加速度
// 马达转动一圈距离和脉冲
#define PARBAK_PHOR_UNITS           "servo/phor_units"
#define PARBAK_PHOR_PLUSES          "servo/phor_pluses"
#define PARBAK_PVER_UNITS           "servo/pver_units"
#define PARBAK_PVER_PLUSES          "servo/pver_pluses"
#define PARBAK_RHOR_UNITS           "servo/rhor_units"
#define PARBAK_RHOR_PLUSES          "servo/rhor_pluses"
#define PARBAK_RVER_UNITS           "servo/rver_units"
#define PARBAK_RVER_PLUSES          "servo/rver_pluses"
#define PARBAK_TRV_UNITS           "servo/trv_units"
#define PARBAK_TRV_PLUSES          "servo/trv_pluses"
#define PARBAK_EXT_UNITS           "servo/ext_units"
#define PARBAK_EXT_PLUSES          "servo/ext_pluses"
// 轴类型
#define PARBAK_ANGLE_BMP            "servo/angle_bmp"
#define PARBAK_RAMP_BMP             "servo/ramp_bmp"
// 原点归位模式
#define PARBAK_HOME_MODE            "servo/home_mode"
#define PARBAK_HOME_VEL             "servo/home_vel"
#define PARBAK_HOME_VEL_SLOW        "servo/home_vel_slow"
// *************************************************
// 定义用户密码长度
// *************************************************
#define MAX_PWD_LEN					8

// *************************************************
// 伺服控制模式
// *************************************************
#define SERVO_MODE_SAFE				0
#define SERVO_MODE_FORCE			1
#define SERVO_MODE_ADJUST			2
// *************************************************
// 伺服定位模式
// *************************************************
#define SERVO_POS_ABS				0
#define SERVO_POS_REL				1
// *************************************************
// 喷雾方向
// *************************************************
#define CIRCLE_CLOCKWIDE			1
#define CIRCLE_ANTI_CLOCKWIDE		0
// *************************************************
// 伺服轴索引(自定义原点复归伺服轴定义)
// *************************************************
#define CUSTOMER_FUN_X_HOME			0	// 伺服 正臂引拔轴原点 *
#define CUSTOMER_FUN_Y_HOME			1	// 伺服 正臂上下轴原点 *
#define CUSTOMER_FUN_Z_HOME			2	// 伺服 横行轴原点 *
#define CUSTOMER_FUN_A_HOME			3	// 伺服 副臂上下轴原点 *
#define CUSTOMER_FUN_B_HOME			4	// 伺服 副臂引拔轴原点 *
#define CUSTOMER_FUN_C_HOME			5	// 伺服 扩展轴原点 *
#define CUSTOMER_FUN_PRO_VER		6	// 气动 主臂上下
#define CUSTOMER_FUN_PRO_HOR    	7	// 气动 主臂引拔
#define CUSTOMER_FUN_PRO_ROT		8	// 气动 主臂倒角 *
#define CUSTOMER_FUN_PRO_REV    	9	// 气动 主臂旋转
#define CUSTOMER_FUN_RUN_VER		10	// 气动 副臂上下 *
#define CUSTOMER_FUN_RUN_HOR    	11	// 气动 副臂引拔  *
#define CUSTOMER_FUN_RUN_ROT		12	// 气动 副臂倒角  *
#define CUSTOMER_FUN_RUN_REV    	13	// 气动 副臂旋转
#define CUSTOMER_FUN_CLR_EXT    	14	// 其他 扩展动作 *

#define CUSTOMER_FUN_END            0xFFFF
// *************************************************
// 伺服轴索引(供界面逻辑使用)
// *************************************************
#define AXES_IDX_X              	0
#define AXES_IDX_Y              	1
#define AXES_IDX_Z              	2
#define AXES_IDX_A              	3
#define AXES_IDX_B              	4
#define AXES_IDX_C              	5
#define AXIS_IDX_PHOR           	AXES_IDX_X
#define AXIS_IDX_PVER           	AXES_IDX_Y
#define AXIS_IDX_TRV            	AXES_IDX_Z
#define AXIS_IDX_RVER           	AXES_IDX_A
#define AXIS_IDX_RHOR           	AXES_IDX_B
#define AXIS_IDX_EXT            	AXES_IDX_C
// *************************************************
// 伺服轴映像(手动自动时伺服轴定义)
// *************************************************
#define SRV_PAHOR					(1<<AXIS_IDX_PHOR)
#define SRV_PAVER					(1<<AXIS_IDX_PVER)
#define SRV_TRV						(1<<AXIS_IDX_TRV)
#define SRV_RAVER					(1<<AXIS_IDX_RVER)
#define SRV_RAHOR					(1<<AXIS_IDX_RHOR)
#define SRV_EXT						(1<<AXIS_IDX_EXT)

// *************************************************
// 定义报警编码结构
// *************************************************
// 得到报警类型
#define GET_ALM_TYPE(e)				(e & 0x2000)
// 得到普通报警码
#define GET_ALM_NCODE(e)			(e & 0x1FFF)
// 得到变量报警码
#define GET_ALM_VCODE(e)			(e & 0x1FFF)

// *************************************************
// 定义变量结构
// *************************************************
// 变量结构
#define MASK_VAR_TYPE				0x0C00
#define MASK_VAR_VAL				0x03FF

#define GET_VAR_TYPE(x)				((x) & MASK_VAR_TYPE)
#define GET_VAR_VALUE(x)			((x) & MASK_VAR_VAL)
#define CREATE_VAR(t, x)			((t) | (x))
// 变量类型
#define VAR_TYPE_SYS				0x0000		// 系统变量
#define VAR_TYPE_IN					0x0400		// 输入变量
#define VAR_TYPE_OUT				0x0800		// 输出变量
#define VAR_TYPE_USR				0x0C00		// 用户变量
// IO变量地址
// 基址
#define VAR_RBT_BASE				0x0000		// 机械手气动IO
#define VAR_IMM_BASE				0x0100		// 注塑机IO
#define VAR_SEV_BASE				0x0200		// 伺服系统IO
#define VAR_EXT_BASE				0x0300		// 扩展IO
// *************************************************
// 定义系统变量
// *************************************************
#define SYS_VAR_MOLDS				0x0000		// 系统自动生产累计总模数
#define SYS_VAR_X_POS				0x0001		// 正臂引拔轴当前位置
#define SYS_VAR_Y_POS				0x0002		// 正臂上下轴当前位置
#define SYS_VAR_Z_POS				0x0003		// 横行轴当前位置
#define SYS_VAR_A_POS				0x0004		// 副臂上下轴当前位置
#define SYS_VAR_B_POS				0x0005		// 副臂引拔轴当前位置
#define SYS_VAR_C_POS				0x0006		// 扩展轴当前位置
#define SYS_VAR_Y_WAITPOS_INMOLD	0x0007		// 正臂上位安全位置
#define SYS_VAR_A_WAITPOS_INMOLD	0x0008		// 副臂上位安全位置
#define SYS_VAR_Z_MINPOS_OUTMOLD	0x0009		// 横行轴模外安全区起点
#define SYS_VAR_Z_MAXPOS_OUTMOLD	0x000A		// 横行轴模外安全区终点
#define SYS_VAR_Z_MINPOS_INMOLD		0x000B		// 横行轴模内安全区起点
#define SYS_VAR_Z_MAXPOS_INMOLD		0x000C		// 横行轴模内安全区终点
#define SYS_VAR_X_MINPOS_INMOLD		0x000D		// 正臂引拔轴模内安全区起点
#define SYS_VAR_X_MAXPOS_INMOLD		0x000E		// 正臂引拔轴模内安全区终点
#define SYS_VAR_B_MINPOS_INMOLD		0x000F		// 副臂引拔轴模内安全区起点
#define SYS_VAR_B_MAXPOS_INMOLD		0x0010		// 副臂引拔轴模内安全区终点
#define SYS_VAR_HOME_ROTATE			0x0011		// 横行时正臂倒角状态
#define SYS_VAR_PLAN				0x0012		// 计划生产数量
#define SYS_VAR_REJECT_ALARM		0x0013		// 累计不良品报警数量
#define SYS_VAR_PGM_MOLDS			0x0014		// 当前程序自动生产累计模数
#define SYS_VAR_REJECT				0x0015		// 当前产品是次品，这个是被锁存的注塑机次品信号，在开模时注塑机次品信号被锁存，每个周期结束清除锁存
#define SYS_VAR_Z_MINPOS_OUTMOLD2	0x0016		// 横行轴模外安全区2起点
#define SYS_VAR_Z_MAXPOS_OUTMOLD2	0x0017		// 横行轴模外安全区2终点

// *************************************************
// 定义输入变量
// *************************************************
#define NUL_VAR_XXX					(0xFFFF)
// 主板扩展输入
#define MAIN_VAR_X00                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x00)
#define MAIN_VAR_X01                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x01)
#define MAIN_VAR_X02                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x02)
#define MAIN_VAR_X03                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x03)
#define MAIN_VAR_X04                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x04)
#define MAIN_VAR_X05                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x05)
#define MAIN_VAR_X06                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x06)
#define MAIN_VAR_X07                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x07)
#define MAIN_VAR_X08                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x08)
#define MAIN_VAR_X09                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x09)
#define MAIN_VAR_X10                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x0A)
#define MAIN_VAR_X11                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x0B)
#define MAIN_VAR_X12                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x0C)
#define MAIN_VAR_X13                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x0D)
#define MAIN_VAR_X14                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x0E)
#define MAIN_VAR_X15                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x0F)
// 扩展模块1扩展输入
#define EM1_VAR_X00					(VAR_TYPE_IN | VAR_EXT_BASE | 0x10)
#define EM1_VAR_X01					(VAR_TYPE_IN | VAR_EXT_BASE | 0x11)
#define EM1_VAR_X02					(VAR_TYPE_IN | VAR_EXT_BASE | 0x12)
#define EM1_VAR_X03					(VAR_TYPE_IN | VAR_EXT_BASE | 0x13)
#define EM1_VAR_X04					(VAR_TYPE_IN | VAR_EXT_BASE | 0x14)
#define EM1_VAR_X05					(VAR_TYPE_IN | VAR_EXT_BASE | 0x15)
#define EM1_VAR_X06					(VAR_TYPE_IN | VAR_EXT_BASE | 0x16)
#define EM1_VAR_X07					(VAR_TYPE_IN | VAR_EXT_BASE | 0x17)
#define EM1_VAR_X08					(VAR_TYPE_IN | VAR_EXT_BASE | 0x18)
#define EM1_VAR_X09					(VAR_TYPE_IN | VAR_EXT_BASE | 0x19)
#define EM1_VAR_X10					(VAR_TYPE_IN | VAR_EXT_BASE | 0x1A)
#define EM1_VAR_X11					(VAR_TYPE_IN | VAR_EXT_BASE | 0x1B)
#define EM1_VAR_X12					(VAR_TYPE_IN | VAR_EXT_BASE | 0x1C)
#define EM1_VAR_X13					(VAR_TYPE_IN | VAR_EXT_BASE | 0x1D)
#define EM1_VAR_X14					(VAR_TYPE_IN | VAR_EXT_BASE | 0x1E)
#define EM1_VAR_X15					(VAR_TYPE_IN | VAR_EXT_BASE | 0x1F)
// 扩展模块2扩展输入
#define EM2_VAR_X00					(VAR_TYPE_IN | VAR_EXT_BASE | 0x20)
#define EM2_VAR_X01					(VAR_TYPE_IN | VAR_EXT_BASE | 0x21)
#define EM2_VAR_X02					(VAR_TYPE_IN | VAR_EXT_BASE | 0x22)
#define EM2_VAR_X03					(VAR_TYPE_IN | VAR_EXT_BASE | 0x23)
#define EM2_VAR_X04					(VAR_TYPE_IN | VAR_EXT_BASE | 0x24)
#define EM2_VAR_X05					(VAR_TYPE_IN | VAR_EXT_BASE | 0x25)
#define EM2_VAR_X06					(VAR_TYPE_IN | VAR_EXT_BASE | 0x26)
#define EM2_VAR_X07					(VAR_TYPE_IN | VAR_EXT_BASE | 0x27)
#define EM2_VAR_X08					(VAR_TYPE_IN | VAR_EXT_BASE | 0x28)
#define EM2_VAR_X09					(VAR_TYPE_IN | VAR_EXT_BASE | 0x29)
#define EM2_VAR_X10					(VAR_TYPE_IN | VAR_EXT_BASE | 0x2A)
#define EM2_VAR_X11					(VAR_TYPE_IN | VAR_EXT_BASE | 0x2B)
#define EM2_VAR_X12					(VAR_TYPE_IN | VAR_EXT_BASE | 0x2C)
#define EM2_VAR_X13					(VAR_TYPE_IN | VAR_EXT_BASE | 0x2D)
#define EM2_VAR_X14					(VAR_TYPE_IN | VAR_EXT_BASE | 0x2E)
#define EM2_VAR_X15					(VAR_TYPE_IN | VAR_EXT_BASE | 0x2F)
// 扩展模块3扩展输入
#define EM3_VAR_X00					(VAR_TYPE_IN | VAR_EXT_BASE | 0x30)
#define EM3_VAR_X01					(VAR_TYPE_IN | VAR_EXT_BASE | 0x31)
#define EM3_VAR_X02					(VAR_TYPE_IN | VAR_EXT_BASE | 0x32)
#define EM3_VAR_X03					(VAR_TYPE_IN | VAR_EXT_BASE | 0x33)
#define EM3_VAR_X04					(VAR_TYPE_IN | VAR_EXT_BASE | 0x34)
#define EM3_VAR_X05					(VAR_TYPE_IN | VAR_EXT_BASE | 0x35)
#define EM3_VAR_X06					(VAR_TYPE_IN | VAR_EXT_BASE | 0x36)
#define EM3_VAR_X07					(VAR_TYPE_IN | VAR_EXT_BASE | 0x37)
#define EM3_VAR_X08					(VAR_TYPE_IN | VAR_EXT_BASE | 0x38)
#define EM3_VAR_X09					(VAR_TYPE_IN | VAR_EXT_BASE | 0x39)
#define EM3_VAR_X10					(VAR_TYPE_IN | VAR_EXT_BASE | 0x3A)
#define EM3_VAR_X11					(VAR_TYPE_IN | VAR_EXT_BASE | 0x3B)
#define EM3_VAR_X12					(VAR_TYPE_IN | VAR_EXT_BASE | 0x3C)
#define EM3_VAR_X13					(VAR_TYPE_IN | VAR_EXT_BASE | 0x3D)
#define EM3_VAR_X14					(VAR_TYPE_IN | VAR_EXT_BASE | 0x3E)
#define EM3_VAR_X15					(VAR_TYPE_IN | VAR_EXT_BASE | 0x3F)
// 扩展模块4扩展输入
#define EM4_VAR_X00					(VAR_TYPE_IN | VAR_EXT_BASE | 0x40)
#define EM4_VAR_X01					(VAR_TYPE_IN | VAR_EXT_BASE | 0x41)
#define EM4_VAR_X02					(VAR_TYPE_IN | VAR_EXT_BASE | 0x42)
#define EM4_VAR_X03					(VAR_TYPE_IN | VAR_EXT_BASE | 0x43)
#define EM4_VAR_X04					(VAR_TYPE_IN | VAR_EXT_BASE | 0x44)
#define EM4_VAR_X05					(VAR_TYPE_IN | VAR_EXT_BASE | 0x45)
#define EM4_VAR_X06					(VAR_TYPE_IN | VAR_EXT_BASE | 0x46)
#define EM4_VAR_X07					(VAR_TYPE_IN | VAR_EXT_BASE | 0x47)
#define EM4_VAR_X08					(VAR_TYPE_IN | VAR_EXT_BASE | 0x48)
#define EM4_VAR_X09					(VAR_TYPE_IN | VAR_EXT_BASE | 0x49)
#define EM4_VAR_X10					(VAR_TYPE_IN | VAR_EXT_BASE | 0x4A)
#define EM4_VAR_X11					(VAR_TYPE_IN | VAR_EXT_BASE | 0x4B)
#define EM4_VAR_X12					(VAR_TYPE_IN | VAR_EXT_BASE | 0x4C)
#define EM4_VAR_X13					(VAR_TYPE_IN | VAR_EXT_BASE | 0x4D)
#define EM4_VAR_X14					(VAR_TYPE_IN | VAR_EXT_BASE | 0x4E)
#define EM4_VAR_X15					(VAR_TYPE_IN | VAR_EXT_BASE | 0x4F)
// 主板2扩展输入
#define MAIN_VAR_X16                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x50)
#define MAIN_VAR_X17                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x51)
#define MAIN_VAR_X18                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x52)
#define MAIN_VAR_X19                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x53)
#define MAIN_VAR_X20                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x54)
#define MAIN_VAR_X21                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x55)
#define MAIN_VAR_X22                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x56)
#define MAIN_VAR_X23                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x57)
#define MAIN_VAR_X24                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x58)
#define MAIN_VAR_X25                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x59)
#define MAIN_VAR_X26                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x5A)
#define MAIN_VAR_X27                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x5B)
#define MAIN_VAR_X28                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x5C)
#define MAIN_VAR_X29                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x5D)
#define MAIN_VAR_X30                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x5E)
#define MAIN_VAR_X31                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x5F)
// 主板3扩展输入
#define MAIN_VAR_X32                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x60)
#define MAIN_VAR_X33                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x61)
#define MAIN_VAR_X34                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x62)
#define MAIN_VAR_X35                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x63)
#define MAIN_VAR_X36                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x64)
#define MAIN_VAR_X37                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x65)
#define MAIN_VAR_X38                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x66)
#define MAIN_VAR_X39                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x67)
#define MAIN_VAR_X40                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x68)
#define MAIN_VAR_X41                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x69)
#define MAIN_VAR_X42                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x6A)
#define MAIN_VAR_X43                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x6B)
#define MAIN_VAR_X44                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x6C)
#define MAIN_VAR_X45                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x6D)
#define MAIN_VAR_X46                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x6E)
#define MAIN_VAR_X47                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x6F)
// 主板4扩展输入
#define MAIN_VAR_X48                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x70)
#define MAIN_VAR_X49                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x71)
#define MAIN_VAR_X50                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x72)
#define MAIN_VAR_X51                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x73)
#define MAIN_VAR_X52                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x74)
#define MAIN_VAR_X53                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x75)
#define MAIN_VAR_X54                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x76)
#define MAIN_VAR_X55                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x77)
#define MAIN_VAR_X56                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x78)
#define MAIN_VAR_X57                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x79)
#define MAIN_VAR_X58                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x7A)
#define MAIN_VAR_X59                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x7B)
#define MAIN_VAR_X60                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x7C)
#define MAIN_VAR_X61                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x7D)
#define MAIN_VAR_X62                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x7E)
#define MAIN_VAR_X63                 (VAR_TYPE_IN | VAR_EXT_BASE | 0x7F)

// 注塑机输入
#define IMM_VAR_IN_STOP				(VAR_TYPE_IN | VAR_IMM_BASE | 0x00)
#define IMM_VAR_IN_SAFE				(VAR_TYPE_IN | VAR_IMM_BASE | 0x01)
#define IMM_VAR_IN_REJECT			(VAR_TYPE_IN | VAR_IMM_BASE | 0x02)
#define IMM_VAR_IN_MCP				(VAR_TYPE_IN | VAR_IMM_BASE | 0x03)
#define IMM_VAR_IN_MOP				(VAR_TYPE_IN | VAR_IMM_BASE | 0x04)
#define IMM_VAR_IN_IMOP				(VAR_TYPE_IN | VAR_IMM_BASE | 0x05)
#define IMM_VAR_IN_AUTO				(VAR_TYPE_IN | VAR_IMM_BASE | 0x06)
#define IMM_VAR_IN_EBP				(VAR_TYPE_IN | VAR_IMM_BASE | 0x07)
#define IMM_VAR_IN_EFP				(VAR_TYPE_IN | VAR_IMM_BASE | 0x08)
#define IMM_VAR_IN_C1P1				(VAR_TYPE_IN | VAR_IMM_BASE | 0x09)
#define IMM_VAR_IN_C1P2				(VAR_TYPE_IN | VAR_IMM_BASE | 0x0A)
#define IMM_VAR_IN_C2P1				(VAR_TYPE_IN | VAR_IMM_BASE | 0x0B)
#define IMM_VAR_IN_C2P2				(VAR_TYPE_IN | VAR_IMM_BASE | 0x0C)
#define IMM_VAR_IN_MID				(VAR_TYPE_IN | VAR_IMM_BASE | 0x0D)
// 伺服系统输入
// 正臂上下轴
#define SV_VAR_IN_YHOME				(VAR_TYPE_IN | VAR_SEV_BASE | 0x00)
#define SV_VAR_IN_YCCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x01)
#define SV_VAR_IN_YCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x02)
#define SV_VAR_IN_YALM				(VAR_TYPE_IN | VAR_SEV_BASE | 0x03)
#define SV_VAR_IN_YRDY				(VAR_TYPE_IN | VAR_SEV_BASE | 0x04)
#define SV_VAR_IN_YINP				(VAR_TYPE_IN | VAR_SEV_BASE | 0x05)
#define SV_VAR_IN_YWPOS				(VAR_TYPE_IN | VAR_SEV_BASE | 0x06)
// 副臂上下轴
#define SV_VAR_IN_AHOME				(VAR_TYPE_IN | VAR_SEV_BASE | 0x07)
#define SV_VAR_IN_ACCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x08)
#define SV_VAR_IN_ACWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x09)
#define SV_VAR_IN_AALM				(VAR_TYPE_IN | VAR_SEV_BASE | 0x0A)
#define SV_VAR_IN_ARDY				(VAR_TYPE_IN | VAR_SEV_BASE | 0x0B)
#define SV_VAR_IN_AINP				(VAR_TYPE_IN | VAR_SEV_BASE | 0x0C)
#define SV_VAR_IN_AWPOS				(VAR_TYPE_IN | VAR_SEV_BASE | 0x0D)
// 正臂引拔轴
#define SV_VAR_IN_XHOME				(VAR_TYPE_IN | VAR_SEV_BASE | 0x0E)
#define SV_VAR_IN_XCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x0F)
#define SV_VAR_IN_XCCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x10)
#define SV_VAR_IN_XALM				(VAR_TYPE_IN | VAR_SEV_BASE | 0x11)
#define SV_VAR_IN_XRDY				(VAR_TYPE_IN | VAR_SEV_BASE | 0x12)
#define SV_VAR_IN_XINP				(VAR_TYPE_IN | VAR_SEV_BASE | 0x13)
// 副臂引拔轴
#define SV_VAR_IN_BHOME				(VAR_TYPE_IN | VAR_SEV_BASE | 0x14)
#define SV_VAR_IN_BCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x15)
#define SV_VAR_IN_BCCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x16)
#define SV_VAR_IN_BALM				(VAR_TYPE_IN | VAR_SEV_BASE | 0x17)
#define SV_VAR_IN_BRDY				(VAR_TYPE_IN | VAR_SEV_BASE | 0x18)
#define SV_VAR_IN_BINP				(VAR_TYPE_IN | VAR_SEV_BASE | 0x19)
// 横行轴
#define SV_VAR_IN_ZHOME				(VAR_TYPE_IN | VAR_SEV_BASE | 0x1A)
#define SV_VAR_IN_ZCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x1B)
#define SV_VAR_IN_ZCCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x1C)
#define SV_VAR_IN_ZALM				(VAR_TYPE_IN | VAR_SEV_BASE | 0x1D)
#define SV_VAR_IN_ZRDY				(VAR_TYPE_IN | VAR_SEV_BASE | 0x1E)
#define SV_VAR_IN_ZINP				(VAR_TYPE_IN | VAR_SEV_BASE | 0x1F)
#define SV_VAR_IN_INMOLD			(VAR_TYPE_IN | VAR_SEV_BASE | 0x20)
#define SV_VAR_IN_OUTMOLD			(VAR_TYPE_IN | VAR_SEV_BASE | 0x21)
// 扩展轴
#define SV_VAR_IN_CHOME				(VAR_TYPE_IN | VAR_SEV_BASE | 0x22)
#define SV_VAR_IN_CCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x23)
#define SV_VAR_IN_CCCWL				(VAR_TYPE_IN | VAR_SEV_BASE | 0x24)
#define SV_VAR_IN_CALM				(VAR_TYPE_IN | VAR_SEV_BASE | 0x25)
#define SV_VAR_IN_CRDY				(VAR_TYPE_IN | VAR_SEV_BASE | 0x26)
#define SV_VAR_IN_CINP				(VAR_TYPE_IN | VAR_SEV_BASE | 0x27)
// 机械手输入
#define RBT_VAR_IN_LOW_AIR			(VAR_TYPE_IN | VAR_RBT_BASE | 0x00)
#define RBT_VAR_IN_DWN_SAF			(VAR_TYPE_IN | VAR_RBT_BASE | 0x01)
#define RBT_VAR_IN_PRO_HOR			(VAR_TYPE_IN | VAR_RBT_BASE | 0x02)
#define RBT_VAR_IN_PRO_VER			(VAR_TYPE_IN | VAR_RBT_BASE | 0x03)
#define RBT_VAR_IN_ARM_SAF			(VAR_TYPE_IN | VAR_RBT_BASE | 0x04)
#define RBT_VAR_IN_RUN_ASC			(VAR_TYPE_IN | VAR_RBT_BASE | 0x05)
#define RBT_VAR_IN_RUN_DES			(VAR_TYPE_IN | VAR_RBT_BASE | 0x06)
#define RBT_VAR_IN_PRO_ADV			(VAR_TYPE_IN | VAR_RBT_BASE | 0x07)
#define RBT_VAR_IN_PRO_RET			(VAR_TYPE_IN | VAR_RBT_BASE | 0x08)
#define RBT_VAR_IN_RUN_ADV			(VAR_TYPE_IN | VAR_RBT_BASE | 0x09)
#define RBT_VAR_IN_RUN_RET			(VAR_TYPE_IN | VAR_RBT_BASE | 0x0A)
#define RBT_VAR_IN_RUN_HOR			(VAR_TYPE_IN | VAR_RBT_BASE | 0x0B)
#define RBT_VAR_IN_RUN_VER			(VAR_TYPE_IN | VAR_RBT_BASE | 0x0C)
// 治具
#define IN_VAR_VACUUM1				(VAR_TYPE_IN | VAR_RBT_BASE | 0x10)
#define IN_VAR_VACUUM2				(VAR_TYPE_IN | VAR_RBT_BASE | 0x11)
#define IN_VAR_GRIP1				(VAR_TYPE_IN | VAR_RBT_BASE | 0x12)
#define IN_VAR_GRIP2				(VAR_TYPE_IN | VAR_RBT_BASE | 0x13)
#define IN_VAR_GRIP3				(VAR_TYPE_IN | VAR_RBT_BASE | 0x14)
#define IN_VAR_GRIP4				(VAR_TYPE_IN | VAR_RBT_BASE | 0x15)

// *************************************************
// 定义输出变量
// *************************************************
#define NUL_VAR_YXX					(0xFFFF)
// 主板扩展输出
#define MAIN_VAR_Y00                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x00)
#define MAIN_VAR_Y01                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x01)
#define MAIN_VAR_Y02                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x02)
#define MAIN_VAR_Y03                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x03)
#define MAIN_VAR_Y04                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x04)
#define MAIN_VAR_Y05                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x05)
#define MAIN_VAR_Y06                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x06)
#define MAIN_VAR_Y07                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x07)
#define MAIN_VAR_Y08                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x08)
#define MAIN_VAR_Y09                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x09)
#define MAIN_VAR_Y10                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x0A)
#define MAIN_VAR_Y11                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x0B)
#define MAIN_VAR_Y12                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x0C)
#define MAIN_VAR_Y13                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x0D)
#define MAIN_VAR_Y14                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x0E)
#define MAIN_VAR_Y15                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x0F)
// 扩展模块1扩展输出
#define EM1_VAR_Y00					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x10)
#define EM1_VAR_Y01					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x11)
#define EM1_VAR_Y02					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x12)
#define EM1_VAR_Y03					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x13)
#define EM1_VAR_Y04					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x14)
#define EM1_VAR_Y05					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x15)
#define EM1_VAR_Y06					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x16)
#define EM1_VAR_Y07					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x17)
#define EM1_VAR_Y08					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x18)
#define EM1_VAR_Y09					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x19)
#define EM1_VAR_Y10					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x1A)
#define EM1_VAR_Y11					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x1B)
#define EM1_VAR_Y12					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x1C)
#define EM1_VAR_Y13					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x1D)
#define EM1_VAR_Y14					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x1E)
#define EM1_VAR_Y15					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x1F)
// 扩展模块2扩展输出
#define EM2_VAR_Y00					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x20)
#define EM2_VAR_Y01					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x21)
#define EM2_VAR_Y02					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x22)
#define EM2_VAR_Y03					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x23)
#define EM2_VAR_Y04					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x24)
#define EM2_VAR_Y05					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x25)
#define EM2_VAR_Y06					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x26)
#define EM2_VAR_Y07					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x27)
#define EM2_VAR_Y08					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x28)
#define EM2_VAR_Y09					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x29)
#define EM2_VAR_Y10					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x2A)
#define EM2_VAR_Y11					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x2B)
#define EM2_VAR_Y12					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x2C)
#define EM2_VAR_Y13					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x2D)
#define EM2_VAR_Y14					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x2E)
#define EM2_VAR_Y15					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x2F)
// 扩展模块3扩展输出
#define EM3_VAR_Y00					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x30)
#define EM3_VAR_Y01					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x31)
#define EM3_VAR_Y02					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x32)
#define EM3_VAR_Y03					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x33)
#define EM3_VAR_Y04					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x34)
#define EM3_VAR_Y05					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x35)
#define EM3_VAR_Y06					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x36)
#define EM3_VAR_Y07					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x37)
#define EM3_VAR_Y08					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x38)
#define EM3_VAR_Y09					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x39)
#define EM3_VAR_Y10					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x3A)
#define EM3_VAR_Y11					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x3B)
#define EM3_VAR_Y12					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x3C)
#define EM3_VAR_Y13					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x3D)
#define EM3_VAR_Y14					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x3E)
#define EM3_VAR_Y15					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x3F)
// 扩展模块4扩展输出
#define EM4_VAR_Y00					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x40)
#define EM4_VAR_Y01					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x41)
#define EM4_VAR_Y02					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x42)
#define EM4_VAR_Y03					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x43)
#define EM4_VAR_Y04					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x44)
#define EM4_VAR_Y05					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x45)
#define EM4_VAR_Y06					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x46)
#define EM4_VAR_Y07					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x47)
#define EM4_VAR_Y08					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x48)
#define EM4_VAR_Y09					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x49)
#define EM4_VAR_Y10					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x4A)
#define EM4_VAR_Y11					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x4B)
#define EM4_VAR_Y12					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x4C)
#define EM4_VAR_Y13					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x4D)
#define EM4_VAR_Y14					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x4E)
#define EM4_VAR_Y15					(VAR_TYPE_OUT | VAR_EXT_BASE | 0x4F)
// 主板扩展输出
#define MAIN_VAR_Y16                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x50)
#define MAIN_VAR_Y17                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x51)
#define MAIN_VAR_Y18                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x52)
#define MAIN_VAR_Y19                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x53)
#define MAIN_VAR_Y20                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x54)
#define MAIN_VAR_Y21                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x55)
#define MAIN_VAR_Y22                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x56)
#define MAIN_VAR_Y23                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x57)
#define MAIN_VAR_Y24                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x58)
#define MAIN_VAR_Y25                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x59)
#define MAIN_VAR_Y26                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x5A)
#define MAIN_VAR_Y27                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x5B)
#define MAIN_VAR_Y28                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x5C)
#define MAIN_VAR_Y29                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x5D)
#define MAIN_VAR_Y30                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x5E)
#define MAIN_VAR_Y31                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x5F)
// 主板扩展输出
#define MAIN_VAR_Y32                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x60)
#define MAIN_VAR_Y33                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x61)
#define MAIN_VAR_Y34                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x62)
#define MAIN_VAR_Y35                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x63)
#define MAIN_VAR_Y36                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x64)
#define MAIN_VAR_Y37                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x65)
#define MAIN_VAR_Y38                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x66)
#define MAIN_VAR_Y39                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x67)
#define MAIN_VAR_Y40                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x68)
#define MAIN_VAR_Y41                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x69)
#define MAIN_VAR_Y42                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x6A)
#define MAIN_VAR_Y43                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x6B)
#define MAIN_VAR_Y44                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x6C)
#define MAIN_VAR_Y45                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x6D)
#define MAIN_VAR_Y46                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x6E)
#define MAIN_VAR_Y47                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x6F)
// 主板扩展输出
#define MAIN_VAR_Y48                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x70)
#define MAIN_VAR_Y49                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x71)
#define MAIN_VAR_Y50                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x72)
#define MAIN_VAR_Y51                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x73)
#define MAIN_VAR_Y52                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x74)
#define MAIN_VAR_Y53                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x75)
#define MAIN_VAR_Y54                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x76)
#define MAIN_VAR_Y55                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x77)
#define MAIN_VAR_Y56                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x78)
#define MAIN_VAR_Y57                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x79)
#define MAIN_VAR_Y58                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x7A)
#define MAIN_VAR_Y59                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x7B)
#define MAIN_VAR_Y60                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x7C)
#define MAIN_VAR_Y61                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x7D)
#define MAIN_VAR_Y62                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x7E)
#define MAIN_VAR_Y63                (VAR_TYPE_OUT | VAR_EXT_BASE | 0x7F)
// 注塑机输出
#define IMM_VAR_OUT_MAF				(VAR_TYPE_OUT | VAR_IMM_BASE | 0x00)
#define IMM_VAR_OUT_EMC				(VAR_TYPE_OUT | VAR_IMM_BASE | 0x01)
#define IMM_VAR_OUT_EMO				(VAR_TYPE_OUT | VAR_IMM_BASE | 0x02)
#define IMM_VAR_OUT_RBT				(VAR_TYPE_OUT | VAR_IMM_BASE | 0x03)
#define IMM_VAR_OUT_EEB				(VAR_TYPE_OUT | VAR_IMM_BASE | 0x04)
#define IMM_VAR_OUT_EEF				(VAR_TYPE_OUT | VAR_IMM_BASE | 0x05)
#define IMM_VAR_OUT_C1P1			(VAR_TYPE_OUT | VAR_IMM_BASE | 0x06)
#define IMM_VAR_OUT_C1P2			(VAR_TYPE_OUT | VAR_IMM_BASE | 0x07)
#define IMM_VAR_OUT_C2P1			(VAR_TYPE_OUT | VAR_IMM_BASE | 0x08)
#define IMM_VAR_OUT_C2P2			(VAR_TYPE_OUT | VAR_IMM_BASE | 0x09)
#define IMM_VAR_OUT_HMAF			(VAR_TYPE_OUT | VAR_IMM_BASE | 0x0A)
#define IMM_VAR_OUT_HEMC			(VAR_TYPE_OUT | VAR_IMM_BASE | 0x0B)
// 伺服系统输出
#define SV_VAR_OUT_YSON				(VAR_TYPE_OUT | VAR_SEV_BASE | 0x00)
#define SV_VAR_OUT_XSON				(VAR_TYPE_OUT | VAR_SEV_BASE | 0x01)
#define SV_VAR_OUT_ZSON				(VAR_TYPE_OUT | VAR_SEV_BASE | 0x02)
#define SV_VAR_OUT_ASON				(VAR_TYPE_OUT | VAR_SEV_BASE | 0x03)
#define SV_VAR_OUT_BSON				(VAR_TYPE_OUT | VAR_SEV_BASE | 0x04)
#define SV_VAR_OUT_CSON				(VAR_TYPE_OUT | VAR_SEV_BASE | 0x05)
// 机械手输出
#define RBT_VAR_OUT_PRO_HOR			(VAR_TYPE_OUT | VAR_RBT_BASE | 0x00)
#define RBT_VAR_OUT_PRO_VER			(VAR_TYPE_OUT | VAR_RBT_BASE | 0x01)
#define RBT_VAR_OUT_ALM_BEEP		(VAR_TYPE_OUT | VAR_RBT_BASE | 0x02)
#define RBT_VAR_OUT_ALM_LAMP		(VAR_TYPE_OUT | VAR_RBT_BASE | 0x03)
#define RBT_VAR_OUT_LAMP			(VAR_TYPE_OUT | VAR_RBT_BASE | 0x04)
#define RBT_VAR_OUT_RUN_DES			(VAR_TYPE_OUT | VAR_RBT_BASE | 0x05)
#define RBT_VAR_OUT_RUN_SPEED		(VAR_TYPE_OUT | VAR_RBT_BASE | 0x06)
#define RBT_VAR_OUT_PRO_ADV			(VAR_TYPE_OUT | VAR_RBT_BASE | 0x07)
#define RBT_VAR_OUT_PRO_RET			(VAR_TYPE_OUT | VAR_RBT_BASE | 0x08)
#define RBT_VAR_OUT_RUN_ADV			(VAR_TYPE_OUT | VAR_RBT_BASE | 0x09)
#define RBT_VAR_OUT_RUN_RET			(VAR_TYPE_OUT | VAR_RBT_BASE | 0x0A)
#define RBT_VAR_OUT_OIL				(VAR_TYPE_OUT | VAR_RBT_BASE | 0x0B)
#define RBT_VAR_OUT_RUN_HOR			(VAR_TYPE_OUT | VAR_RBT_BASE | 0x0C)
#define RBT_VAR_OUT_RUN_VER			(VAR_TYPE_OUT | VAR_RBT_BASE | 0x0D)
// 治具
#define OUT_VAR_VACUUM1             (VAR_TYPE_OUT | VAR_RBT_BASE | 0x10)
#define OUT_VAR_VACUUM2             (VAR_TYPE_OUT | VAR_RBT_BASE | 0x11)
#define OUT_VAR_GRIP1				(VAR_TYPE_OUT | VAR_RBT_BASE | 0x12)
#define OUT_VAR_GRIP2				(VAR_TYPE_OUT | VAR_RBT_BASE | 0x13)
#define OUT_VAR_GRIP3				(VAR_TYPE_OUT | VAR_RBT_BASE | 0x14)
#define OUT_VAR_GRIP4				(VAR_TYPE_OUT | VAR_RBT_BASE | 0x15)
#define OUT_VAR_CONV                (VAR_TYPE_OUT | VAR_RBT_BASE | 0x16)
#define OUT_VAR_CUT                 (VAR_TYPE_OUT | VAR_RBT_BASE | 0x17)

// 总线错误内容字符串资源
#define HARDWARE_OVER_CURRENT           0x2214
#define IPM_SHORT_CIRCUIT               0x2250
#define MOTOR_FOLDBACK                  0x2310
#define DRIVE_FOLDBACK                  0x2311
#define UVW_SHORT_CIRCUIT               0x2330
#define CURRENT_SENSORS_OFFSET_INVALID  0x2380
#define OUTPUT_OVER_CURRENT             0x2382
#define OVER_VOLTAGE                    0x3110
#define UNDER_VOLTAGE                   0x3120
#define BUS_AC_LINE_DISCONNECT          0x3183
#define REGENERATION_FAULT              0x3199
#define INTEGRATED_POWER_MODULE         0x4080
#define OVER_TEMPERATURE                0x4310
#define POWER_EEPROM_FAULT              0x5530
#define CONTROL_EEPROM_FAULT            0x5581
#define EEPROM_VERSION_ERROR            0x5585
#define FAILURE_WRITING_FLASH           0x5586
#define HOMING_ERROR                    0x6100
#define POWER_ON_TIME_OUT               0x6320
#define NOT_CONFIGURED                  0x6381
#define FPGA_CONFIG_FAILED              0x6581
#define FPGA_VERSION_MISMATCH           0x7090
#define EMERGENCY_STOP                  0x7091
#define STALL_FAULT                     0x7121
#define ENCODER_COUNTER_OVERFLOW        0x7305
#define FEEDBACK_COMMUNICATION_ERROR    0x7380
#define TAMAGAWA_INIT_FAILED            0x7382
#define ABSOLUTE_ENCODER_BATTERY        0x7385
#define TAMAGAWA_ABS_OPERATIONAL_FAULT  0x7388
#define ENCODER_FAULT                   0x738D
#define FIELDBUS_CABLE_DISCONNECTED     0x7580
#define ETHERCAT_PACKET_LOSS            0x818D
#define VELOCITY_OVER_SPEED_EXCEEDED    0x8481
#define EXCEEDED_MAXIMUM_VELOCITY_ERROR 0x8482
#define EXCESSIVE_PE_VALUE              0x8689
#define ETHERCAT_STATE_NOT_OPERATIONAL  0xF080
#define MOTOR_PLATE_READ_FAILED         0xFF02
#define REALTIME_OVERLOAD_FAULT         0xFF04
#define MOTOR_MTP_DATA_NOT_COMPATIBLE   0xFF14

// *************************************************
// 指令机器码
// *************************************************
#define CODE_CONST					0x00	// 常参数指令
#define CODE_VAR					0x01	// 变参数指令
#define CODE_INTERP					0x02	// 插补参数指令
#define CODE_POS					0x03	// 单轴定位指令
#define CODE_SPEED					0x04	// 单轴速度指令
#define CODE_DELAY					0x05	// 延时指令
#define CODE_EXT_IN					0x06	// 扩展输入指令
#define CODE_EXT_OUT				0x07	// 扩展输出指令
#define CODE_IMM					0x08	// 塑机指令
#define CODE_PROARM					0x09	// 主臂指令
#define CODE_RUNARM					0x0A	// 副臂指令
#define CODE_PAPER                  0x0B	// 取纸指令
#define CODE_MATRIX                 0x0C	// 矩阵指令
#define CODE_FREEPOS                0x0D	// 循环定位指令
#define CODE_LOOP                   0x0E	// 单轴循环指令
#define CODE_OPR                    0x10	// 变量操作指令
#define CODE_CIRCLE                 0x11	// 喷雾指令
#define CODE_LOOPFREE               0x12	// 单轴循环指令(自由定位)
#define CODE_EXTPOS                 0x13	// 扩展单轴定位指令
#define CODE_MEXTOUT        	 	0x14    // 多扩展指令

#define CODE_POWER                  0x0F	// 轴电源指令
#define CODE_WAIT					0x20	// 等待指令
#define CODE_IF						0x21	// 条件指令
#define CODE_ELSE					0x22	// ELSE指令
#define CODE_ENDIF					0x23	// ENDIF指令
#define CODE_FOR_CONST				0x24	// 常FOR指令
#define CODE_FOR_VAR				0x25	// 变FOR指令
#define CODE_ENDFOR					0x26	// ENDFOR指令
#define CODE_BREAK					0x27	// BREAK指令
#define CODE_CUSTOMER				0x2B	// 定制原点指令
#define CODE_TBEGIN					0x2C	// 连续路径开始指令
#define CODE_TEND					0x2D	// 连续路径结束指令
#define CODE_END					0x2F	// 程序结束指令
#define CODE_VACUUM					0x31	// 主板治具指令
#define CODE_VISION                 0x40	// 视觉指令
#define CODE_MBSLAVESTART           0x41    //modbus从设备启动
#define CODE_MBSLAVECTRL            0x42    //modbus从设备控制
#define VCODE_VACUUM				0x80	// 虚拟治具
#define VCODE_ASSIST				0x82	// 虚拟辅助设备

// *************************************************
#define FLAG_COMBINE                0x80    //组合控制位

// *************************************************
#define OPR_TYPE_ASSIGN         0
#define OPR_TYPE_ADD			1
#define OPR_TYPE_SUB			2
#define OPR_TYPE_MUL			3
#define OPR_TYPE_DIV			4
#define OPR_TYPE_MOD			5
// *************************************************
// 条件类型
// *************************************************
#define IF_TYPE_DIR					0		// 直接
#define IF_TYPE_GT					1		// >
#define IF_TYPE_LT					2		// <
#define IF_TYPE_GE					3		// >=
#define IF_TYPE_LE					4		// <=
#define IF_TYPE_EQ					5		// ==
#define IF_TYPE_NE					6		// !=
// *************************************************
// 注塑机动作
// *************************************************
#define IMMOUT_EMC					0
#define IMMOUT_EMO					1
#define IMMOUT_EEF					2
#define IMMOUT_EEB					3
#define IMMOUT_C1P1					4
#define IMMOUT_C1P2					5
#define IMMOUT_C2P1					6
#define IMMOUT_C2P2					7
#define IMMOUT_EEF_OFF				8
#define IMMOUT_EEB_OFF				9
#define IMMOUT_C1P1_OFF				10
#define IMMOUT_C1P2_OFF				11
#define IMMOUT_C2P1_OFF				12
#define IMMOUT_C2P2_OFF				13
#define IMMOUT_RBT_ON               14
#define IMMOUT_RBT_OFF              15
// *************************************************
// 主臂气动动作
// *************************************************
#define PRO_ACT_VERTIACL			0
#define PRO_ACT_HOZIONTAL			1
#define PRO_ACT_JIG_RELEASE			2
#define PRO_ACT_JIG_BIND			3
// *************************************************
// 副臂气动动作
// *************************************************
#define RUN_ACT_ASCENT				0
#define RUN_ACT_DESCENT				1
#define RUN_ACT_ADVANCE				2
#define RUN_ACT_RETURN				3
#define RUN_ACT_VERTIACL            4
#define RUN_ACT_HORIZONTAL          5
// *************************************************
// 机器代码程序最大尺寸
// *************************************************
#define MAX_CODES					4096
#define MAX_PROCESS                 3
#define MAX_COMBINE                 30
#define MAX_TRAJ                    100
#define MAX_USER_VARS               0x400
#define MAX_USER_VAR                499
#define MAX_COUNTER_VAR             (MAX_USER_VARS-25)

// *************************************************
// XML 元素
// *************************************************
#define XML_ELEMENT_SINROBOT        "sinrobot"
#define XML_VERSION100  			"1.00"

#define XML_ELEMENT_OPTION          "option"
#define XML_ELEMENT_OPTION1         "option1"
#define XML_ELEMENT_OPTION2         "option2"
#define XML_ELEMENT_OPTION3         "option3"
#define XML_ELEMENT_OPTION4         "option4"
#define XML_ELEMENT_VAR_INIT        "varinit"
#define XML_ELEMENT_ITEM            "item"
#define XML_ELEMENT_LINE            "line"
#define XML_ATTR_ENABLE             "enable"
#define XML_ATTR_NAMEEN             "nameen"
#define XML_ATTR_NAMEDIS            "namedis"
#define XML_ATTR_NUM                "num"

#define XML_ELEMENT_PROGRAM			"program"
#define XML_ELEMENT_PROGRAM1		"program1"
#define XML_ELEMENT_PROGRAM2		"program2"
#define XML_ELEMENT_PROGRAM3		"program3"
#define XML_ELEMENT_PROGRAM4		"program4"
#define XML_ELEMENT_CODE			"code"
#define XML_ELEMENT_PARA			"para"
#define XML_ELEMENT_VALUE			"value"
#define XML_ELEMENT_VAR             "var"
#define XML_ATTR_NOTE               "note"
#define XML_ATTR_FLAG               "flag"
#define XML_ATTR_VERSION			"version"
#define XML_ATTR_NAME				"name"
#define XML_ATTR_TYPE				"type"

#define XML_ATTR_DIR				"dir"
#define XML_ATTR_RADIUS				"radius"
#define XML_ATTR_SPEED				"speed"
#define XML_ATTR_BEGIN				"begin"
#define XML_ATTR_END				"end"
#define XML_ATTR_ZPOINT				"zpoint"
#define XML_ATTR_Y2POINT			"y2point"


#define XML_ATTR_AXES				"axes"
#define XML_ATTR_INDEX				"index"
#define XML_ATTR_X					"x"
#define XML_ATTR_Y					"y"
#define XML_ATTR_Z					"z"
#define XML_ATTR_POS				"pos"
#define XML_ATTR_LEN				"len"
#define XML_ATTR_COUNT				"count"
#define XML_ATTR_VAL				"val"
#define XML_ATTR_INQ				"inq"
#define XML_CNAME_BREAK				"break"
#define XML_CNAME_CBEGIN			"cbegin"
#define XML_CNAME_CEND				"cend"
#define XML_CNAME_TBEGIN            "tbegin"
#define XML_CNAME_TEND              "tend"
#define XML_CNAME_DELAY				"delay"
#define XML_CNAME_SPEED				"speed"
#define XML_CNAME_ELSE				"else"
#define XML_CNAME_END				"end"
#define XML_CNAME_ENDFOR			"endfor"
#define XML_CNAME_ENDIF				"endif"
#define XML_CNAME_IF				"if"
#define XML_CNAME_ASSIGN			"assign"
#define XML_CNAME_PARM				"parm"
#define XML_CNAME_RARM				"rarm"
#define XML_CNAME_OPR				"operator"
#define XML_CNAME_WAIT				"wait"
#define XML_CNAME_IMM				"imm"
#define XML_CNAME_POS				"pos"
#define XML_CNAME_EXTPOS			"extpos"
#define XML_CNAME_EXTIN				"extin"
#define XML_CNAME_EXTOUT			"extout"
#define XML_CNAME_MEXTOUT			"mextout"
#define XML_CNAME_VACUUM	        "vacuum"
#define XML_CNAME_INVACUUM	        "invacuum"
#define XML_CNAME_PAPER				"paper"
#define XML_CNAME_LOOP				"loop"
#define XML_CNAME_MATRIX			"matrix"
#define XML_CNAME_FOR				"for"
#define XML_CNAME_SINGLE_LOOP       "singleloop"
#define XML_CNAME_SINGLE_LOOP_FREE  "singleloopfree"
#define XML_CNAME_INTERP            "interp"
#define XML_CNAME_POWER            "power"
#define XML_CNAME_CIRCLE            "circle"
#define XML_CNAME_VISION            "vision"
#define XML_CNAME_ASSIST            "assist"

#define XML_TYPE_VAR				"var"
#define XML_TYPE_CONST				"const"
#define XML_TYPE_TIMEOUT			"timeout"
#define XML_TYPE_INFINITE			"infinite"
#define XML_TYPE_EMO				"emo"
#define XML_TYPE_EMC				"emc"
#define XML_TYPE_EEF				"eef"
#define XML_TYPE_EEB				"eeb"
#define XML_TYPE_C1P1				"c1p1"
#define XML_TYPE_C1P2				"c1p2"
#define XML_TYPE_C2P1				"c2p1"
#define XML_TYPE_C2P2				"c2p2"
#define XML_TYPE_EEF_OFF			"eef_off"
#define XML_TYPE_EEB_OFF			"eeb_off"
#define XML_TYPE_C1P1_OFF			"c1p1_off"
#define XML_TYPE_C1P2_OFF			"c1p2_off"
#define XML_TYPE_C2P1_OFF			"c2p1_off"
#define XML_TYPE_C2P2_OFF			"c2p2_off"
#define XML_TYPE_VER				"ver"
#define XML_TYPE_HOR				"hor"
#define XML_TYPE_ADV				"adv"
#define XML_TYPE_JIGR				"jigr"
#define XML_TYPE_JIGB				"jigb"
#define XML_TYPE_RET				"ret"
#define XML_TYPE_ASC				"asc"
#define XML_TYPE_DES				"des"
#define XML_TYPE_ON					"on"
#define XML_TYPE_USELESS			"useless"
#define XML_TYPE_OFF				"off"
#define XML_TYPE_PULSE				"pulse"
#define XML_TYPE_NOT				"not"

#define XML_PNAME_PARA1				"para1"
#define XML_PNAME_PARA2				"para2"
#define XML_PNAME_PARA3				"para3"
#define XML_PNAME_PARA4				"para4"
#define XML_PNAME_PARA5				"para5"
#define XML_PNAME_PARA6				"para6"
#define XML_PNAME_PARA7				"para7"
#define XML_PNAME_PARA8				"para8"
#define XML_PNAME_PARA9				"para9"
#define XML_PNAME_PARA10			"para10"
#define XML_PNAME_PARA11			"para11"
#define XML_PNAME_PARA12			"para12"
#define XML_PNAME_PARA13			"para13"
#define XML_PNAME_PARA14			"para14"
#define XML_PNAME_PARA15			"para15"
#define XML_PNAME_PARA16			"para16"
#define XML_PNAME_PARA17			"para17"
#define XML_PNAME_PARA18			"para18"
#define XML_PNAME_PARA19			"para19"
#define XML_PNAME_PARA20			"para20"
#define XML_PNAME_PARA21			"para21"
#define XML_PNAME_PARA22			"para22"
#define XML_PNAME_PARA23			"para23"
#define XML_PNAME_PARA24			"para24"
#define XML_PNAME_PARA25            "para25"
#define XML_PNAME_PARA26            "para26"

#define POS_TYPE_POINT  0           // 数值
#define POS_TYPE_CAT	1           // 取物点
#define POS_TYPE_REL	2           // 置物点
#define POS_TYPE_WAIT	3           // 待机点
//#define POS_TYPE_SYNC   4           // 同步位置
#define POS_TYPE_VAR    4           // 变量

// ------------------------------------------
// 系统外设配置
// ------------------------------------------
// LCD
#define DEV_LCD_BKLIGHT			"/sys/devices/virtual/disp/disp/attr/lcd_bl"

// 状态选择开关
#define DEV_SWITCH_CFG0			"/sys/class/gpio_xr/gpio52/cfg"
#define DEV_SWITCH_CFG1			"/sys/class/gpio_xr/gpio53/cfg"
#define DEV_SWITCH_DATA0		"/sys/class/gpio_xr/gpio52/data"
#define DEV_SWITCH_DATA1		"/sys/class/gpio_xr/gpio53/data"



// 蜂鸣器时间设定: 单位 100ms, 0 表示常开, 1 表示常闭
#define BUZZER_TIME				"2"

// 指示灯
#define DEV_LAMP_CFG0			"/sys/class/gpio_xr/gpio22/cfg"
#define DEV_LAMP_CFG1			"/sys/class/gpio_xr/gpio23/cfg"
#define DEV_LAMP_DATA0			"/sys/class/gpio_xr/gpio22/data"
#define DEV_LAMP_DATA1			"/sys/class/gpio_xr/gpio23/data"

// Motor
#define DEV_LAMP_CFG4			"/sys/class/gpio_xr/gpio03/cfg"
#define DEV_LAMP_DATA4			"/sys/class/gpio_xr/gpio03/data"

// 三态安全开关
#define DEV_SAFESWITCH_CFG		"/sys/class/gpio_xr/gpio54/cfg"
#define DEV_SAFESWITCH_DATA		"/sys/class/gpio_xr/gpio54/data"
#endif // XCONFIG_H
