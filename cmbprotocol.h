#ifndef CMBPROTOCOL_H
#define CMBPROTOCOL_H

#include <QFileInfo>
#include <QObject>
#include <QVector>
#include <QKeyEvent>
#include <QByteArray>
#include <QDir>
#include "xconfig.h"
#include "modbus.h"
#include "modbusaddr.h"

class QTimer;

// ********************************************
// 复位命令标志
// ********************************************
#define CMD_RESET_MOLDS				(1 << 0)
#define CMD_RESET_USER				(1 << 2)
#define CMD_RESET_SERVO				(1 << 3)
#define CMD_RESET_SYSTEM			(1 << 4)


#define CMD_RESET_SVDEV             (1 << 6)//复位驱动器参数
// ********************************************
// 写命令标志
// ********************************************
#define CMD_WRITE_USER				(1<<0)
#define CMD_WRITE_SERVO				(1<<1)
#define CMD_WRITE_SYSTEM			(1<<2)
#define CMD_WRITE_CODE				(1<<3)
#define CMD_WRITE_CODEPARA			(1<<4)
#define CMD_WRITE_PAPER				(1<<5)
#define CMD_WRITE_LOOP				(1<<6)
#define CMD_WRITE_REGISTRATION      (1<<7)
#define CMD_WRITE_PRODUCTCODE       (1<<8)
// ********************************************
// 更新命令标志
// ********************************************
#define CMD_UPDATE_PARA1			(1<<4)
#define CMD_UPDATE_PARA2			(1<<5)
#define CMD_UPDATE_PARA3            (1<<6)
// ********************************************
// 命令字
// ********************************************
#define COMMAND_RESET_PARA			0
#define COMMAND_DELETE_PRG          1
#define COMMAND_RENAME_PRG          2
#define COMMAND_COPY_PRG            3
#define COMMAND_WRITE_PARA			4
//#define COMMAND_STOP_SERVO		5
#define COMMAND_UPDATE_PRG			6
#define COMMAND_TECH_SAVE			7
#define COMMAND_ADJUST_MOTOR        8
#define COMMAND_SET_NAME_OFFSET     9	// 设置文件名偏移,开机是为0，通过以前文件名接口就是读前14个文件名,偏移设为10，就是读10-23程序的文件名
#define COMMAND_ENTRY_ISP			11
#define COMMAND_CLEAR_CYC			12
#define COMMAND_ENCODER             13	// 编码器
#define COMMAND_CLEAR_ALARM         14	// 清除报警
#define COMMAND_ABS_HOME			15	// 重新设置绝对值
#define COMMAND_ENTRY_HALF_ISP		16	// 按键版占用
#define COMMAND_DOOR_RESET          17	// 安全门复位命令
#define COMMAND_VISION				18	//视觉测试命令 带1个参数，0开始索引，相机编号
#define COMMAND_DOOR_QUERY          19	// 信易安全门询问
#define COMMAND_ALLIMMOUT		21	//塑机信号全输出
#define COMMAND_FUN_UI              22 //版本指令。告知主板操作器有的功能
// ********************************************
#define SET_ABS_HOME                1   // 设置绝对值编码器原点
#define CLR_ABS_HOME                0   // 清除绝对值编码器原点
// ********************************************
// 调位电机索引
// 其他索引值将停止电机运转
// ********************************************
#define ADJUST_MOTOR_IDX_POS		0
#define ADJUST_MOTOR_IDX_LEN		1
#define ADJUST_MOTOR_IDX_UP			2
// ********************************************
// 通讯返回命令字
// ********************************************
#define SENDMSG_RET_ACK				0
#define SENDMSG_RET_NACK			1
#define SENDMSG_RET_TIMEOUT			2
#define SENDMSG_RET_ALLOC_ERR		3
#define SENDMSG_RET_REGADDR_ERR		4
// ********************************************
#define MAX_PROGRAMS				200
// ********************************************
// 系统报警位置
// ********************************************
#define ALARM_IMM_SYS				0
#define ALARM_PRO_ARM				1
#define ALARM_IOEXT_1				2
#define ALARM_IOEXT_2				3
#define ALARM_IOEXT_3				4
#define ALARM_IOEXT_4				5
#define ALARM_SV_PHOR				6
#define ALARM_SV_PVER				7
#define ALARM_SV_TRAV				8
#define ALARM_SV_RVER				9
#define ALARM_SV_RHOR				10
#define ALARM_SV_EXTE				11
#define ALARM_RUN_ARM				12
#define ALARM_MAX					13
// ********************************************
// ECAT伺服报警标志位
// ********************************************
#define ECAT_BUS_DRIVER_ALARM_FLAG      0x80000000 //表示高创伺服报警,需要用高创伺服报警代码解析
// ********************************************
// 六轴驱控一体伺服报警标志位
// ********************************************
#define DVS_BUS_DRIVER_ALARM_FLAG       0x40000000
// ********************************************
//表示禾川一体机伺服报警
// ********************************************
#define ALARM_HIGH16_FLAG               0x80010000 //需要用禾川伺服报警代码解析ECAT或CANOPEN
// ********************************************
// 数据结构定义
// ********************************************
typedef struct tagPoint
{
	uint32_t _x;
	uint32_t _y;
	uint32_t _z;
} Point, *PPoint;

//历史报警
#define	MAX_HISTORYS	30
typedef struct
{
	uint16_t m_alarm[MAX_HISTORYS];
} HistoryParameter, *PHistoryParameter;

// 版本信息
typedef struct
{
	uint8_t m_hard_major;
	uint8_t m_hard_minor;
	uint8_t m_soft_major;
	uint8_t m_soft_minor;
	uint8_t m_soft_extra;
    uint8_t m_soft_extra_new;
    uint8_t m_soft_Ecat;
    uint16_t m_m0_major;
    uint16_t m_m0_minor;
    uint8_t m_servo_not_exist;
} VersionParameter, *PVersionParameter;

// 激活码及机器码
typedef struct
{
    uint16_t m_system_uid1;
    uint16_t m_system_uid2;
    uint16_t m_system_uid3;
    uint16_t m_system_uid4;
    uint16_t m_system_uid5;
    uint16_t m_system_uid6;
    uint16_t m_system_uid7;
    uint16_t m_system_uid8;
    uint16_t m_activation_1;
    uint16_t m_activation_2;
    uint16_t m_activation_3;
    uint16_t m_activation_4;
    uint16_t m_activation_5;
    uint16_t m_activation_6;
    uint16_t m_activation_7;
    uint16_t m_activation_8;
}RegistrationCode, *PRegistrationCode;
// 产品密钥
typedef struct
{
    uint16_t m_product_id1;
    uint16_t m_product_id2;
    uint16_t m_product_id3;
    uint16_t m_product_id4;
    uint16_t m_product_id5;
}ProductCode, *PProductCode;
// 系统参数
typedef struct
{
	uint16_t m_alarm_times;					// 报警器鸣叫次数
	uint16_t m_alarm_interval;				// 报警器鸣叫间隔
	uint32_t m_service_moldings;			// 维护模数
	uint32_t m_plan_molding;				// 计划成型数
	uint32_t m_plan_alarm;					// 生产提醒数量
	uint16_t m_reject_alarm;				// 累计不良品报警数
	uint16_t m_language;					// 系统语言设置
    uint32_t m_oil_interval;                // 打油间隔
    uint32_t m_oil_time;                    // 打油时间
    uint16_t m_oil_use;
    uint16_t m_oil_ctrl_use;
	// tick 最后写入时间
	uint16_t m_rotate_out_at_origin;		// 横行时倒角状态
	uint16_t m_pause_open_door;				// 开安全门暂停
	uint16_t m_ext_servo_use;				// 扩展伺服使用（0：不使用；1：使用）
	uint16_t m_rhor_servo_use;				// 副臂引拔伺服使用（0：不使用；1：使用）
	uint16_t m_rver_servo_use;				// 副臂上下伺服使用（0：不使用；1：使用）
	uint16_t m_mold_closed_use;				// 关模信号使用
	uint16_t m_imop_dwn_use;				// 开模中间信号使用
	uint16_t m_mid_open_use;				// 开中板模确认信号使用
	uint16_t m_rotate_inmold_use;			// 模内倒角使能
	uint16_t m_wait_outmould;				// 待机选项
    uint64_t m_polary[5];					// 0 表示正常，1 表示反相
    uint64_t m_outputpolary[5];					// 0 表示正常，1 表示反相
    uint64_t m_ignore[5];					// 0 表示正常，1 报警时可以忽略
    uint64_t m_noalm[5];					// 0 表示正常， 1 表示反相
	uint16_t m_jig_use;						// 治具使用（1Bit，0：不使用；1：使用）
	uint16_t m_runner_use;					// 气动副臂使用
	uint16_t m_runner_down_use;				// 气动副臂下位电眼使用
    uint16_t m_runner_advance_use;          // 气动副臂前进电眼使用
    uint16_t m_runner_return_use;           // 气动副臂后退电眼使用
	uint16_t m_adjust_use;					// 调位使用
    uint16_t m_home_inmold;                 // 原点在模内
    uint16_t m_proc2_use;                   // 进程2使用
    uint16_t m_proc3_use;                   // 进程3使用
    uint16_t m_proc_use;                   // 进程使用
    uint32_t m_ip;                          // IP地址
    uint32_t m_submask;                     // 子网掩码
    uint32_t m_gateway;                     // 默认网关
    uint16_t m_rotate_use;                  // 气动正臂倒角使用
    uint16_t m_run_rotate_use;               // 气动副臂倒角使用
    uint16_t m_door_reset_use;              // 取物失败，开关安全门程序结束
    uint16_t m_extend_bit_use;              // 扩展控制位
	uint16_t m_sys_io_clr;					//退出自动时清除IO口
    uint32_t m_visionip1;                   // 视觉IP地址
    uint32_t m_visionip2;                   // 视觉IP地址
    uint32_t m_visionip3;                   // 视觉IP地址
    uint32_t m_visionip4;                   // 视觉IP地址
    uint32_t m_visionip5;                   // 视觉IP地址
    uint32_t m_visionip6;                   // 视觉IP地址
    uint32_t m_visionip7;                   // 视觉IP地址
    uint32_t m_visionip8;                   // 视觉IP地址
    uint16_t m_vision1port;
    uint16_t m_vision2port;
    uint16_t m_vision3port;
    uint16_t m_vision4port;
    uint16_t m_vision5port;
    uint16_t m_vision6port;
    uint16_t m_vision7port;
    uint16_t m_vision8port;    
    uint16_t m_vision1_trigger;             // 高8位表示类型(相机类型 0表示没有选择 1表示cognex)
    uint16_t m_vision2_trigger;             // 第0位表示触发方式(触发方式:0表示协议触发;1表示端口触发(教导时指定输出端口))
    uint16_t m_vision3_trigger;             // 第1位表示跟随方式(跟随方式:0表示固定安装;1表示跟随安装)
    uint16_t m_vision4_trigger;
    uint16_t m_vision5_trigger;
    uint16_t m_vision6_trigger;
    uint16_t m_vision7_trigger;
    uint16_t m_vision8_trigger;
    uint16_t m_vision1_outvar;
    uint16_t m_vision2_outvar;
    uint16_t m_vision3_outvar;
    uint16_t m_vision4_outvar;
    uint16_t m_vision5_outvar;
    uint16_t m_vision6_outvar;
    uint16_t m_vision7_outvar;
    uint16_t m_vision8_outvar;



} SystemParameter, *PSystemParameter;

// 伺服参数
typedef struct
{
    // 引拔轴间距
	uint32_t m_machine_max_len_x;
    uint32_t m_min_safe_dis_x_b;
    // 软件最大行程
	uint32_t m_software_max_len_y;
	uint32_t m_software_max_len_z;
	uint32_t m_software_max_len_a;
	uint32_t m_software_max_len_c;
	// 原点偏移
    qint32 m_origin_offset_x;
    qint32 m_origin_offset_y;
    qint32 m_origin_offset_z;
    qint32 m_origin_offset_a;
    qint32 m_origin_offset_b;
    qint32 m_origin_offset_c;
	// 安全区
    uint32_t m_min_safe_pos_outmold2_z; // 模外最小安全区2
    uint32_t m_max_safe_pos_outmold2_z; // 模外最大安全区2
    uint32_t m_max_wait_pos_inmold_y;	// 正臂上行模内待机位置
	uint32_t m_max_wait_pos_inmold_a;	// 副臂上行模内待机位置
	uint32_t m_min_safe_pos_outmold_z;	// 模外下行最小Z轴位置(必须在模外电眼范围之内)
	uint32_t m_max_safe_pos_outmold_z;	// 模外下行最大Z轴位置(必须在模外电眼范围之内)
	uint32_t m_min_safe_pos_inmold_z;	// 模内下行最小Z轴位置(必须在模内电眼范围之内)
	uint32_t m_max_safe_pos_inmold_z;	// 模内下行最大Z轴位置(必须在模内电眼范围之内)
    uint32_t m_min_safe_pos_inmold_x;	// 模内下行最小X轴位置
    uint32_t m_max_safe_pos_inmold_x;	// 模内下行最大X轴位置
    uint32_t m_min_safe_pos_inmold_z_a;	// 副臂模内下行最小Z轴位置(必须在模内电眼范围之内)
    uint32_t m_max_safe_pos_inmold_z_a;	// 副臂模内下行最大Z轴位置(必须在模内电眼范围之内)
	uint32_t m_min_safe_pos_inmold_b;	// 模内下行最小B轴位置
	uint32_t m_max_safe_pos_inmold_b;	// 模内下行最大B轴位置
    uint32_t m_min_b_trave;             // 副臂引拔轴横行最小位置
    uint32_t m_max_b_trave;             // 副臂引拔轴横行最大位置
    uint32_t m_min_c_trave;             // 扩展轴横行最小位置
    uint32_t m_max_c_trave;             // 扩展轴横行最大位置
    uint32_t m_min_c_inmold;            // 扩展轴模内最小位置
    uint32_t m_max_c_inmold;            // 扩展轴模内最大位置
    uint32_t m_min_x_trave;             // 正引拔横行安全最小位置
    uint32_t m_max_x_trave;             // 正引拔横行安全最大位置
    // 正臂引拔轴速度/加速度/运行参数
	uint16_t m_xmax_speed;
	uint16_t m_xmax_acceleration;
    float m_x_units;
    float m_x_pluses;
    uint16_t m_xmax_jerk;
    // 正臂上下轴速度/加速度/运行参数
	uint16_t m_ymax_speed;
	uint16_t m_ymax_acceleration;
    float m_y_units;
    float m_y_pluses;
    uint16_t m_ymax_jerk;
    // 横行轴速度/加速度/运行参数
	uint16_t m_zmax_speed;
	uint16_t m_zmax_acceleration;
    float m_z_units;
    float m_z_pluses;
    uint16_t m_zmax_jerk;
    // 副臂上下轴速度/加速度/运行参数
	uint16_t m_amax_speed;
	uint16_t m_amax_acceleration;
    float m_a_units;
    float m_a_pluses;
    uint16_t m_amax_jerk;
    // 副臂引拔轴速度/加速度/运行参数
	uint16_t m_bmax_speed;
	uint16_t m_bmax_acceleration;
    float m_b_units;
    float m_b_pluses;
    uint16_t m_bmax_jerk;
    // 扩展轴速度/加速度/运行参数
	uint16_t m_cmax_speed;
	uint16_t m_cmax_acceleration;
    float m_c_units;
    float m_c_pluses;
    uint16_t m_cmax_jerk;
    // 轴类型 方向
    uint16_t m_angle_type;
    // 减速类型和找原点方式
    uint16_t m_dec_type;
    // 原点归位模式
    uint16_t m_home_mode;
    uint8_t m_home_vel;					//原点归位速度-快速	//(1-100)%
    uint8_t m_home_vel_slow;			//原点归位速度-慢速	//(1-100)%
    // 倒角
    uint32_t m_min_a_trv;               // 横行倒角
    uint32_t m_max_a_trv;
    uint32_t m_min_a_inmold;            // 模内倒角
    uint32_t m_max_a_inmold;
    // 编码器
    uint16_t m_encoder_x;
    uint16_t m_encoder_y;
    uint16_t m_encoder_z;
    uint16_t m_encoder_a;
    uint16_t m_encoder_b;
    uint16_t m_encoder_c;
    // 原点待机点
    uint32_t m_home_pos_x;
    uint32_t m_home_pos_y;
    uint32_t m_home_pos_z;
    uint32_t m_home_pos_a;
    uint32_t m_home_pos_b;
    uint32_t m_home_pos_c;
    // 模
    uint32_t m_mod_x;
    uint32_t m_mod_y;
    uint32_t m_mod_z;
    uint32_t m_mod_a;
    uint32_t m_mod_b;
    uint32_t m_mod_c;
    //伺服一体机参数PA5
    //速度环比例增益 5-2000
    uint16_t m_pa5_x;
    uint16_t m_pa5_y;
    uint16_t m_pa5_z;
    uint16_t m_pa5_a;
    uint16_t m_pa5_b;
    //uint16_t m_pa5_c;

    //伺服一体机参数PA6
    // 速度积分常数 1-1000
    uint16_t m_pa6_x;
    uint16_t m_pa6_y;
    uint16_t m_pa6_z;
    uint16_t m_pa6_a;
    uint16_t m_pa6_b;
    //uint16_t m_pa6_c;

    //伺服一体机参数PA7
    // 转矩滤波器 20-500
    uint16_t m_pa7_x;
    uint16_t m_pa7_y;
    uint16_t m_pa7_z;
    uint16_t m_pa7_a;
    uint16_t m_pa7_b;
    //uint16_t m_pa7_c;

    //伺服一体机参数PA8
    // 速度检测滤波器 20-500
    uint16_t m_pa8_x;
    uint16_t m_pa8_y;
    uint16_t m_pa8_z;
    uint16_t m_pa8_a;
    uint16_t m_pa8_b;
    //uint16_t m_pa8_c;

    //伺服一体机参数PA9
    // 位置比例增益 0-1000
    uint16_t m_pa9_x;
    uint16_t m_pa9_y;
    uint16_t m_pa9_z;
    uint16_t m_pa9_a;
    uint16_t m_pa9_b;
    //uint16_t m_pa9_c;

    //伺服一体机参数PA19
    // 位置平滑滤波 0-1000
    uint16_t m_pa19_x;
    uint16_t m_pa19_y;
    uint16_t m_pa19_z;
    uint16_t m_pa19_a;
    uint16_t m_pa19_b;
    //uint16_t m_pa19_c;


    //伺服一体机参数PA63
    // 负载惯量比 1-500
    uint16_t m_pa63_x;
    uint16_t m_pa63_y;
    uint16_t m_pa63_z;
    uint16_t m_pa63_a;
    uint16_t m_pa63_b;
    //uint16_t m_pa63_c;

} ServoParameter, *PServoParameter;

//循环模式1参数(任意10点)
#define MAX_LOOP_POINTS					100
#define MAX_LOOPS						10
#define LOOP_MODE_POINT					0
#define LOOP_MODE_MATRIX				1
#define DEC_AXES_X						1
#define DEC_AXES_Y						0
#define MAX_LOOP_AXIS                   3
// 单轴自由定位
#define MAX_SINGLELOOPFREE_POINTS       100

//程序参数
typedef struct
{
	uint8_t m_name[10];
} ProgramParameter, *PProgramParameter;

#define MAX_MANUAL_CODES		10

// *** 系统工作状态 ***
#define SYS_STATE_MANUAL		0
#define SYS_STATE_AUTO			1
#define SYS_STATE_JOG			2		//自由运行模式
#define SYS_STATE_ERROR         3
// *** 运行状态 ***
#define RUN_STATE_PAUSE			0
#define RUN_STATE_RUN			1
// *** 运行方式 ***
#define RUN_TYPE_LOOP			0
#define RUN_TYPE_STEP			1
#define RUN_TYPE_SINGLE			2
// *** 指令状态 ***
#define VMRUN_STATE_GET         0		//取指
#define VMRUN_STATE_EXEC        1		//指令执行
#define VMRUN_STATE_END         2		//指令完成
// *** 系统通讯初始化返回码 ***
#define COM_INIT_OK				0		// 通讯初始化成功
#define COM_INIT_COM_ERR		1		// 通讯链路出错
#define COM_INIT_MATE_ERR		2		// 操作器和主控模块类型不匹配
#define COM_INIT_SVER_ERR		3		// 操作器和主控模块软件版本不匹配
// *** 系统授权码 ***
#define LICENSE_PREVER			0x00	// 没有加密的以前版本
#define LICENSE_LEGAL			0x01	// 正版
#define LICENSE_PIRATE			0x02	// 盗版

#define PROTOCOL_KEY_HOME      (1<<0)
#define PROTOCOL_KEY_RUN       (1<<1)
#define PROTOCOL_KEY_STOP      (1<<2)
#define PROTOCOL_KEY_DOOR_QUERY     (1<<14)

#define PROTOCOL_KEY_DOOR_RESET     (1<<15)

class CMBProtocol : public QObject
{
	Q_OBJECT
public:
	explicit CMBProtocol(QObject *parent = 0);
	~CMBProtocol();
	// 初始化系统通讯状态数据
	uint8_t InitSystemStatus(void);
	// 当前程序管理
    static QString GetCurPgmName(bool iscachefile = false)
    {
#if (FACTORY == FA_JINBOYUE_SPECIAL)
        if (iscachefile)
        {
            // change path to temp
            QFileInfo fileInfo(curPgmName);
            return QDir::currentPath().append("/"TEMP_PATH"/") + fileInfo.baseName() + ".xpgm";
        }
        else
            return curPgmName;
#else
        return curPgmName;
#endif
    }
    void SetCurPgmName(const QString &name);
    static QString GetAlfaPgmName(void) { return alfaPgmName; }
    void SetAlfaPgmName(const QString &name);
	// 厂商管理
	uint16_t GetFactoryId(void) { return factoryId; }
	// 系统状态接口
	static uint8_t GetPirate(void) { return pirateFlag; }
	static uint8_t GetHverMajor(void) { return sysVersion.m_hard_major; }
	static uint8_t GetHverMinor(void) { return sysVersion.m_hard_minor; }
	static uint8_t GetSverMajor(void) { return sysVersion.m_soft_major; }
	static uint8_t GetSverMinor(void) { return sysVersion.m_soft_minor; }
    static uint16_t GetM0Major(void) { return sysVersion.m_m0_major; }
    static uint16_t GetM0Minor(void) { return sysVersion.m_m0_minor; }
    static uint8_t GetSverExtra(void) { return sysVersion.m_soft_extra_new; }
    static uint8_t GetServoNotExist(void) { return sysVersion.m_servo_not_exist; }
	static void SetSrvSpeed(quint8 spd) { srvSpeed = spd; }
	static quint8 GetSrvSpeed(void) { return srvSpeed; }

    static void SetManualSpeed(quint8 spd) { manualSpeed = spd; }
    static quint8 GetManualSpeed(void) { return manualSpeed; }
    static void SetSrvScale(double spd) { servoScale = spd; }
    static double GetSrvScale(void) { return servoScale; }
    static bool GetSwitchUse(void) { return switchUse; }
    static void SetSwitchUse(bool use) { switchUse = use; }
    static bool GetAlwaysOn(void) { return alwaysOn; }
	static void SetAlwaysOn(bool use) { alwaysOn = use; }
    static bool GetTemplateUse(void) { return templateUse; }
    static bool SetTemplateUse(bool use) { return templateUse = use; }
    static quint8 GetAdjustSpeed(void) {return adjustSpeed;}
    static void SetAdjustSpeed(quint8 spd) { adjustSpeed = spd; }

    static bool IsALFAMode(void) { return alfamode; }
    bool SetALFAMode(bool use);

    int8_t SetSysState(uint8_t state);
    int8_t SetRunState(uint8_t runstate = RUN_STATE_RUN);
	int8_t SetRunType(uint8_t type);
	// 周期轮循接口
	void StartPeriodTimer(void);
	void StopPeriodTimer(void);
	void CloseSerialPort(void);
	bool GetTypeMatch(void) { return typeMate; }
    static int GetSysType(void);
    static int GetSysTypeHigh(void);
    bool GetComState(void) { return ComState; }
	static uint64_t GetInMain(void) { return InputMain; }
	static uint16_t GetInEm1(void) { return InputEm1; }
	static uint16_t GetInEm2(void) { return InputEm2; }
	static uint16_t GetInEm3(void) { return InputEm3; }
	static uint16_t GetInEm4(void) { return InputEm4; }
	static uint32_t GetOutMain(void) { return OutputMain; }
	static uint16_t GetOutEm1(void) { return OutputEm1; }
	static uint16_t GetOutEm2(void) { return OutputEm2; }
	static uint16_t GetOutEm3(void) { return OutputEm3; }
	static uint16_t GetOutEm4(void) { return OutputEm4; }
	static void GetServoPos(uint32_t &pHor, uint32_t &pVer, uint32_t &trv, uint32_t &rHor, uint32_t &rVer, uint32_t &ext);
	static quint32 GetPaHorPos(void) { return svPhorPos; }
	static quint32 GetPaVerPos(void) { return svPverPos; }
	static quint32 GetTravelPos(void) { return svTrvPos; }
	static quint32 GetRaHorPos(void) { return svRhorPos; }
	static quint32 GetRaVerPos(void) { return svRverPos; }
	static quint32 GetExtendPos(void) { return svExtPos; }
	static uint32_t GetHorLen(void);
	static uint32_t GetHorInt(void);
	static uint32_t GetPaVerLen(void);
	static uint32_t GetTravLen(void);
	static uint32_t GetRaVerLen(void);
	static uint32_t GetExteLen(void);
	static uint32_t GetPaHorSafeBegin(void);
	static uint32_t GetPaHorSafeEnd(void);
	static uint32_t GetRaHorSafeBegin(void);
	static uint32_t GetRaHorSafeEnd(void);

	static bool GetExtBoard(quint8 idx) { return ((ExtBoardState >> idx) & 0x0001) != 0; }
	static uint16_t GetSysState(void) { return SystemState; }
	int8_t ReadRunState(void);
    static uint16_t GetRunState(void) { return RunningState; }
	uint16_t GetRunType(void) { return RunningType; }
	uint16_t GetHomeState(void) { return HomeState; }						// 得到机械手原点状态(是否经过原点复归,是否在原点位置)
	uint32_t GetPrdSum(void) { return productSum; }							// 得到生产总模数
	uint32_t GetPrdPlan(void) { return productPlan; }						// 得到生产计划数
    double GetPeriod(void) { return (double)productPeriod / (1000.0/TIME_BASE); }			// 得到产品成型周期
    double GetInmoldTime(void) { return (double)inmoldTime / (1000.0/TIME_BASE); }          // 得到产品模内周期
    static uint16_t GetPgmPc(void) { return programPc; }                                           // 得到程序执行指令指针
    double GetPeriod2(void) { return (double)productPeriod2 / (1000.0/TIME_BASE); }			// 得到产品成型周期2
    double GetInmoldTime2(void) { return (double)inmoldTime2 / (1000.0/TIME_BASE); }		// 得到产品模内周期2
    uint16_t GetPgmPc2(void) { return programPc2; }                                         // 得到程序执行指令指针2
    double GetPeriod3(void) { return (double)productPeriod3 / (1000.0/TIME_BASE); }			// 得到产品成型周期3
    double GetInmoldTime3(void) { return (double)inmoldTime3 / (1000.0/TIME_BASE); }		// 得到产品模内周期3
    uint16_t GetPgmPc3(void) { return programPc3; }							// 得到程序执行指令指针3
    double GetPeriod4(void) { return (double)productPeriod4 / (1000.0/TIME_BASE); }			// 得到产品成型周期4
    double GetInmoldTime4(void) { return (double)inmoldTime4 / (1000.0/TIME_BASE); }		// 得到产品模内周期4
    uint16_t GetPgmPc4(void) { return programPc4; }                                         // 得到程序执行指令指针4
    int8_t GetFirstAlarm(uint32_t &alm);									// 得到第一个报警位置
    uint32_t GetAlmByPos(uint8_t pos);										// 得到指定位置报警
	quint32 GetSysMsg(void) { return sysMessage; }							// 得到系统消息
#if PENDANT_PROTOCOL
	bool IsHasRefer(uint16_t state) { return (state & 0x01) != 0; }			// 机械手是否经过原点复归操作
#else
	bool IsHasRefer(uint16_t state) { return true;}							// 机械手是否经过原点复归操作
#endif
	bool IsHomePos(uint16_t state) { return (state >> 1) != 0; }			// 机械手是否在原点位置
	int8_t PeriodRead(void);
	int8_t ClrMessage(void);
    quint32 GetRemainTime(void) { return activeRemainTime; }
    // ********************************************
    // 手动接口
    // ********************************************
    int8_t ManualHome(quint8 spd);
	int8_t ManualPro(uint8_t act);
	int8_t ManualRun(uint8_t act);
	int8_t ManualIMM(uint8_t act);
	int8_t ManualExt(uint8_t on_off, uint16_t out);
    int8_t ManualVacuum(uint8_t on_off, uint16_t outbmp);
    int8_t ManualPos(uint8_t speed, uint8_t axesbmp, uint32_t pos, uint8_t mode, bool rel = false);
    int8_t SetRun(void);
    // ********************************************
	// 命令接口
	// ********************************************
    int8_t CommandReset(uint16_t resetflag);
	int8_t CommandWrite(uint16_t writeflag);
	int8_t CommandUpdate(uint16_t writeflag);
	int8_t CommandStop(void);
	int8_t CommandEnterIsp(void);
	int8_t CommandAdjustMotor(uint8_t motoridx, uint8_t ccw);
    int8_t CommandClearAlarm(void);
    int8_t CommandEncoder(uint8_t speed, uint8_t axesbmp, qint16 scale, bool cw, uint8_t mode);
    int8_t CommandEncoderHome(uint16_t encoder, uint8_t mode);
    int8_t CommandDoorReset(bool reset);
    int8_t CommandDoorQuery();
    int8_t CommandVisionTest(quint16 idx);
    int8_t CommandIMMOut(uint8_t on);
    int8_t CommandFUNUI(quint32 idx);
    // ********************************************
	// 参数读接口
	// ********************************************
	int8_t ReadPwd(const uint8_t user, QByteArray &pwd);					// 读取指定用户的密码
	int8_t ReadVersion(void);												// 读取版本信息
	int8_t ReadPirate(void);												// 读取系统授权信息
	int8_t ReadFunctions(void);												// 读取系统功能列表
	int8_t ReadFactory(void);												// 读取厂商ID
	int8_t ReadHome(void);													// 读取原点复归设置
    static void GetHome(quint16 (&home)[HOME_DEF_MAX]);
	void ResetHome();														// 复位原点复归
	bool CheckHome();														// 检查原点复归
    void GetProductCode(ProductCode &proc);                                 // 读产品密钥
    void GetRegistrationCode(RegistrationCode &regc);                       // 读激活码
    int ReadVisionTestData(quint8 visionidx);
    // *** 读取系统参数设置 ***
	int8_t ReadSystem(void);
	void GetSystem(SystemParameter &par);									// 得到系统参数设置
	// 得到系统语言设置
	static uint16_t GetLanguage(void) { return m_mbaddrspace[SYS_LANGUAGE]; }
#if UI_SRV_CFG == UI_SRV_4
	static bool GetRhorSrvUse(void) { return false; }						// 副臂引拔伺服使用设置
	static bool GetExtSrvUse(void) { return false; }						// 扩展轴伺服使用设置
#elif UI_SRV_CFG == UI_SRV_5
	static bool GetRhorSrvUse(void) { return true; }						// 副臂引拔伺服使用设置
	static bool GetExtSrvUse(void) { return false; }						// 扩展轴伺服使用设置
#elif UI_SRV_CFG == UI_SRV_6
	static bool GetRhorSrvUse(void) { return true; }						// 副臂引拔伺服使用设置
	static bool GetExtSrvUse(void) { return true; }							// 扩展轴伺服使用设置
#else
	// 副臂引拔伺服使用设置
    static bool GetRhorSrvUse(void)
    {
        if (GetFunctions(SUB_3_AXES))
        {
            if (((GetServoNotExist() >> AXES_IDX_B) & 1) == 1)
                return 0;
        }
        return m_mbaddrspace[SYS_RHOR_SERVO_USE] != 0;
    }
	// 扩展轴伺服使用设置
	static bool GetExtSrvUse(void) { return m_mbaddrspace[SYS_EXT_SERVO_USE] != 0; }
#endif
    // 横行时倒角状态
    static bool GetRotateAtOrigin(void) { return m_mbaddrspace[SYS_ROTATE_OUT_AT_ORIGIN] != 0; }
    static int8_t ReadRotateAtOrigin(void) { return m_mbaddrspace[SYS_ROTATE_OUT_AT_ORIGIN]; }
	// 副臂上下伺服使用设置
    static bool GetRverSrvUse(void)
    {
        if (GetFunctions(SUB_3_AXES))
        {
            if (((GetServoNotExist() >> AXES_IDX_A) & 1) == 1)// not exist
                return 0;
        }
        return m_mbaddrspace[SYS_RVER_SERVO_USE] != 0;
    }
	// 气动副臂使用设置
	static bool GetRunnerUse(void) { return m_mbaddrspace[SYS_RUNNER_USE] != 0; }
	// 气动副臂下位电眼使用设置
	static bool GetRunnerDownUse(void) { return m_mbaddrspace[SYS_RUN_DOWN_USE] != 0; }
    // 气动副臂前进电眼使用设置
    static bool GetRunnerAdvUse(void) { return m_mbaddrspace[SYS_RUN_ADVANCE_USE] != 0; }
    // 气动副臂后退电眼使用设置
    static bool GetRunnerRetUse(void) { return m_mbaddrspace[SYS_RUN_RETURN_USE] != 0; }
    // 气动调位使用设置
	static bool GetAdjustUse(void) { return m_mbaddrspace[SYS_ADJUST_USE] != 0; }
    // 原点在模内设置
    static bool GetHomeInmold(void) { return m_mbaddrspace[SYS_HOME_INMOLD] != 0; }
	// 开中板模确认信号使用
	static bool GetMidOpenUse(void) { return m_mbaddrspace[SYS_MID_OPEN_USE] != 0; }
    // 换治具使用
    static bool  GetJigUse(void) { return m_mbaddrspace[SYS_JIG_USE] != 0; }
    // 气动倒角使用
    static bool  GetRotateUse(void) { return m_mbaddrspace[SYS_ROTATE_USE] != 0; }
    // Proc使用
    static bool  GetProcUse(int procid);
    // 打油使用
    static bool GetOilUse(void) { return m_mbaddrspace[SYS_OIL_USE] != 0; }
    // 模外安全区2使用
    static bool GetOutmold2use(void) { return ((m_mbaddrspace[SYS_EXTRA_CTRL_BIT_USE] >> 0)& 1) != 0; }
    // 模外安全区信号不使用
    static bool GetOutmoldSignalNotuse(void) { return ((m_mbaddrspace[SYS_EXTRA_CTRL_BIT_USE] >> 1)& 1) != 0; }
    // 模内安全区信号不使用
    static bool GetInmoldSignalNotuse(void) { return ((m_mbaddrspace[SYS_EXTRA_CTRL_BIT_USE] >> 5)& 1) != 0; }
    // 正臂引拔不使用
    static bool GetPaHorNotUse(void) { return ((m_mbaddrspace[SYS_EXTRA_CTRL_BIT_USE] >> 2) & 1) != 0; }
    // 外部控制位使用
    static bool GetExtraControl(void) { return ((m_mbaddrspace[SYS_EXTRA_CTRL_BIT_USE] >> 4) & 1) != 0; }
    // 副臂倒角使用
    static bool GetRunRotateUse(void) { return m_mbaddrspace[SYS_RUN_ROTATE_USE] != 0; }
    // *** 读取伺服参数设置 ***

    //pyq
    // X轴是否选择编码器SERVO_ENCODER
    static bool GetServoEncoderX(void) { return m_mbaddrspace[SERVO_ENCODER_X] != 0X100; }
    // Y轴是否选择编码器
    static bool GetServoEncoderY(void) { return m_mbaddrspace[SERVO_ENCODER_Y] != 0X100; }
    // Z轴是否选择编码器
    static bool GetServoEncoderZ(void) { return m_mbaddrspace[SERVO_ENCODER_Z] != 0X100; }
    // A轴是否选择编码器
    static bool GetServoEncoderA(void) { return m_mbaddrspace[SERVO_ENCODER_A] != 0X100; }
    // B轴是否选择编码器
    static bool GetServoEncoderB(void) { return m_mbaddrspace[SERVO_ENCODER_B] != 0X100; }
    // C轴是否选择编码器
    static bool GetServoEncoderC(void) { return m_mbaddrspace[SERVO_ENCODER_C] != 0X100; }
    //pyq end
    int8_t ReadServo(void);                                                 // 读取伺服参数设置
    static void GetServo(ServoParameter &srvPar);							// 得到伺服参数设置
    static uint8_t GetHomeVel(void);
    static bool GetFunctions(quint32 mask);									// 得到系统功能支持状态
    void ChangeSafePos_Inmold_Outmold(bool home_inmold);
    // *** 读取IO映射表 ***
    int8_t ReadIoBmp(void);
    // ********************************************
	// 参数写接口
	// ********************************************
	int8_t WriteLanguage(uint8_t lan);										// 写入系统语言设置
	int8_t WritePwd(const uint8_t user, QByteArray &pwd);					// 写入指定用户的密码
	int8_t WriteFactory(uint16_t faID);										// 写入厂商ID
	int8_t WriteHome(const quint16 home[HOME_DEF_MAX]);                     // 写入原点复归设置
	int8_t WriteSystem(const SystemParameter &psp, quint64 modify);			// 写入系统参数设置
	int8_t WriteServo(const ServoParameter &psp, quint64 modify);           // 写入伺服参数设置
	int8_t WritePaHorMacDistance(uint32_t distance);					// 写入正副臂原点距离
    int8_t WriteProductCode(const ProductCode &proc);    // 写入产品密钥
    int8_t WriteRegistrationCode(const RegistrationCode &regc); // 写入激活码
	// 写入指定位置和指定数量的机器代码
    int8_t WriteCodes(quint16 *pcode, const uint16_t startIdx, const uint16_t count);
	// 写入指定位置和指定数量的机器代码参数
	int8_t WriteCodeParas(uint32_t *ppara, const uint16_t startIdx, const uint16_t count);
    // ********************************************
    // 用户变量访问接口
    // ********************************************
    int8_t WriteUserVar(quint32 *pvalue, int varidx, int counts);
    int8_t ReadUserVar(int varidx, int counts);

    // ********************************************
    // MB空间访问接口
    // ********************************************
    uint16_t ReadReg16(uint16_t regaddr);
    uint16_t ReadReg16_MB2(uint16_t regaddr);
	uint32_t ReadReg32(uint16_t regaddr);
    uint32_t ReadReg32_MB2(uint16_t regaddr);
    static uint16_t GetSystemAlarm() { return m_mbaddrspace[IMM_SYS_ALARM]; }
    static QString XMLFileVersion(void);
signals:
	void signal_PgmChange(const QString &name);
    void signal_PeriodPoll(quint32 alarm);
	void signal_SysStateChange(uint16_t input);
	void signal_RunStateChange(uint16_t input);
	void signal_RunTypeChange(uint16_t input);
	void signal_HomeStateChange(uint16_t input);
    void signal_XPosChange(qint32 input);
    void signal_YPosChange(qint32 input);
    void signal_ZPosChange(qint32 input);
    void signal_APosChange(qint32 input);
    void signal_BPosChange(qint32 input);
    void signal_CPosChange(qint32 input);
    void signal_PhorSrvUseChange(void);
    void signal_ExtSrvUseChange(void);
    void signal_RverSrvUseChange(void);
	void signal_RhorSrvUseChange(void);
	void signal_doubleArmChange(void);
	void signal_TotalMoldChange(uint32_t input);
	void signal_TotalPlanChange(uint32_t input);
	void signal_TotalRejectChange(uint16_t input);
    void signal_MessageChange(uint16_t input);
    void signal_AlarmChange(qint16 idx, quint32 alarm);

    void signal_PeriodTimeChange(uint32_t input, uint16_t idx);
    void signal_InmoldTimeChange(uint32_t input, uint16_t idx);
    void signal_PC_Pointer(uint16_t input, uint16_t idx);
    void signal_active_remainTime(uint32_t time);

    void signal_InputChange(void);
    void signal_OutputChange(void);
    //pyq 实时扭矩 实时转速
    void signal_Actual_Servo(int16_t actualTrqX,int16_t actualTrqY,int16_t actualTrqZ,int16_t actualTrqA,int16_t actualTrqB,int16_t actualTrqC
       ,int16_t actualSpeedX,int16_t actualSpeedY,int16_t actualSpeedZ,int16_t actualSpeedA,int16_t actualSpeedB,int16_t actualSpeedC);


private slots:
	void MBPeriodPoll();

private:
	// *** 当前程序名称 ***
	static QString curPgmName;
    static QString alfaPgmName;
	// *** 系统版本 ***
	static VersionParameter sysVersion;
	static uint8_t pirateFlag;
    static uint32_t functionsList;
	// *** 用户管理 ***
	uint16_t factoryId;
	uint8_t curUser;
	// *** 状态轮询定时器 ***
	QTimer *pTimer;
	// *** 系统状态 ***
	static bool typeMate;				// 操作器与主控模块类型匹配
	bool ComState;						// 通讯状态
    quint32 Alarms[ALARM_MAX];			// 系统报警状态
	quint32 sysMessage;				// 系统消息状态
	static uint64_t InputMain;			// 主板输入状态
	static uint16_t InputEm1;			// 扩展模块1输入状态
	static uint16_t InputEm2;			// 扩展模块2输入状态
	static uint16_t InputEm3;			// 扩展模块3输入状态
	static uint16_t InputEm4;			// 扩展模块4输入状态
    static uint64_t OutputMain;			// 主板输出状态
	static uint16_t OutputEm1;			// 扩展模块1输出状态
	static uint16_t OutputEm2;			// 扩展模块2输出状态
	static uint16_t OutputEm3;			// 扩展模块3输出状态
	static uint16_t OutputEm4;			// 扩展模块4输出状态
    static qint32 svPhorPos;			// 正臂引拔伺服位置
    static qint32 svPverPos;			// 正臂上下伺服位置
    static qint32 svTrvPos;			// 横行伺服位置
    static qint32 svRhorPos;			// 副臂引拔轴位置
    static qint32 svRverPos;			// 副臂上下轴位置
    static qint32 svExtPos;			// 扩展轴位置
	static uint16_t ExtBoardState;		// 扩展模块状态
	static uint16_t SystemState;		// 系统工作状态,0:手动,1:自动,2:错误
    static uint16_t RunningState;				// 系统运行状态,0:暂停,1:运行
    static uint16_t RunningType;				// 系统运行类型,0:全自动,1:单步,2:单循环
	uint16_t HomeState;
	uint32_t productSum;				// 生产总模数
	uint32_t productPlan;				// 计划生产数
	static quint8 srvSpeed;				// 伺服相对速度
    static quint8 manualSpeed;			// 伺服手动速度
    static double servoScale;			// 伺服刻度
    static quint8 adjustSpeed;          // 调位速度
    static bool switchUse;              // 安全开关使用
    static bool alwaysOn;               // 原点归位时安全开关长按
    static bool templateUse;            // 非教导模式使用
    static bool alfamode;               // 天行模式使用

    uint32_t productPeriod;				// 生产周期时间
    uint32_t inmoldTime;                // 模内時間
    static uint16_t programPc;					// 程序指令指针

    uint32_t productPeriod2;            // 生产周期时间2
    uint32_t inmoldTime2;               // 模内时间2
    uint16_t programPc2;                // 程序指令指针2
    uint32_t productPeriod3;            // 生产周期时间3
    uint32_t inmoldTime3;               // 模内时间3
    uint16_t programPc3;                // 程序指令指针3

    uint32_t productPeriod4;            // 生产周期时间4
    uint32_t inmoldTime4;               // 模内时间4
    uint16_t programPc4;                // 程序指令指针4

    uint32_t activeRemainTime;          // 激活剩余时间
    uint16_t keypressed;
    //pyq 实时扭矩，实时转速
    int16_t actualTrqX;
    int16_t actualTrqY;
    int16_t actualTrqZ;
    int16_t actualTrqA;
    int16_t actualTrqB;
    int16_t actualTrqC;
    int16_t actualSpeedX;
    int16_t actualSpeedY;
    int16_t actualSpeedZ;
    int16_t actualSpeedA;
    int16_t actualSpeedB;
    int16_t actualSpeedC;
    //pyq end

    static quint8 InSignal[256];
    static quint8 OutSignal[256];
	// ********************************************
	// Modbus
	// ********************************************
    int8_t ClearProcCode(int8_t procid);
    int8_t SendMsg(uint16_t begin, uint16_t end, uint8_t read = TRUE, int retry=5);
    int8_t SendMsg2(uint16_t begin, uint16_t end, uint8_t read = TRUE, int retry=5);
	modbus_t * m_modbus;
	static quint16 m_mbaddrspace[MODBUS_ADDRESS_MAX];
	static quint16 m_mbaddrspace2[MODBUS_ADDRESS_MAX];
};

#endif // CMBPROTOCOL_H
