#ifndef XSYSTEMLOG_H
#define XSYSTEMLOG_H

#include <QSqlTableModel>
#include <QtSql/QtSql>
#include <QVector>

#define SYSLOG_TYPE_NOR			0		// 普通日志记录
#define SYSLOG_TYPE_MSG			1		// 提醒日志记录
#define SYSLOG_TYPE_ALM			2		// 报警日志记录
#define SYSLOG_TYPE_SYS			3		// 系统参数日志记录
#define SYSLOG_TYPE_SRV			4		// 伺服参数日志记录
#define SYSLOG_TYPE_UI			5		// 界面参数日志记录
#define SYSLOG_TYPE_STATE_CHG	6		// 系统状态改变日志记录

#define LOG_NOR_START			0		// 操作器软件启动完成
#define LOG_NOR_SRVHOME			1		// 手动控制机械手开始复归操作
#define LOG_NOR_PGMLOAD			2		// 载入当前程序
#define LOG_NOR_PGMNEW			3		// 创建新程序文件
#define LOG_NOR_PGMRENAME		4		// 重命名程序文件
#define LOG_NOR_PGMCOPY			5		// 复制程序文件
#define LOG_NOR_PGMDEL			6		// 删除程序文件
#define LOG_NOR_PGMEXPORT		7		// 导出程序文件到USB存储器
#define LOG_NOR_PGMIMPORT		8		// 从USB存储器导入程序文件
#define LOG_NOR_OPRLOG			9		// 登录操作员
#define LOG_NOR_ADVOPRLOG		10		// 登录高级操作员
#define LOG_NOR_ADMLOG			11		// 登录管理员
#define LOG_NOR_ADVADMLOG		12		// 登录高级管理员
#define LOG_NOR_SULOG			13		// 登录超级用户
#define LOG_NOR_LOGOUT			14		// 注销当前用户，以操作员登录
#define LOG_NOR_ADVOPRPWD		15		// 修改高级操作员密码
#define LOG_NOR_ADMPWD			16		// 修改管理员密码
#define LOG_TIME_CHG			17		// 修改系统时间
#define LOG_WAIT2MANUL			18		// 系统从自动待机进入手动操作
#define LOG_RUN2WAIT			19		// 停止程序自动运行，进入自动待机状态
#define LOG_PERIOD2WAIT			20		// 停止程序单周期运行，进入自动待机状态
#define LOG_STEP2WAIT			21		// 停止程序单步运行，进入自动待机状态
#define LOG_MANUL2AUTO			22		// 系统从手动操作进入自动待机
#define LOG_WAIT2RUN			23		// 系统从自动待机进入自动运行
#define LOG_WAIT2PERIOD			24		// 执行程序单周期运行
#define LOG_WAIT2STEP			25		// 执行程序单步运行
#define LOG_PAR_SYS				26		// 修改系统参数
#define LOG_PAR_SRV				27		// 修改伺服参数
#define LOG_PAR_UI				28		// 修改操作器界面设置
#define LOG_ADJ_PHORCHG			29		// 伺服调位操作：正臂引拔轴位置改变
#define LOG_ADJ_PVERCHG			30		// 伺服调位操作：正臂引拔轴位置改变
#define LOG_ADJ_TRVCHG			31		// 伺服调位操作：正臂上下轴位置改变
#define LOG_ADJ_RHORCHG			32		// 伺服调位操作：正臂上下轴位置改变
#define LOG_ADJ_RVERCHG			33		// 伺服调位操作：横行轴位置改变
#define LOG_ADJ_EXTCHG			34		// 伺服调位操作：横行轴位置改变
#define LOG_LD_SPLASH			35		// 导入开机画面：
#define LOG_LD_WPAPER			36		// 导入待机画面：
#define LOG_LD_INFOR			37		// 导入厂商信息：
#define LOG_LD_PORTNAME			38		// 导入端口名称定义：
#define LOG_RST_PORTNAME		39		// 重置端口名称为出厂默认值
#define LOG_UPDATE				40		// 升级操作器软件：
#define LOG_RESTORE				41		// 恢复备份的操作器软件
#define LOG_RESTART				42		// 操作器软件重新启动
#define LOG_PAR_EXPORT			43		// 导出系统参数和伺服参数设置
#define LOG_PAR_IMPORT			44		// 导入系统参数和伺服参数设置
#define LOG_MANUL_ROTVER		45		// 手动控制正臂倒角垂直
#define LOG_MANUL_ROTHOR		46		// 手动控制正臂倒角水平
#define LOG_MANUL_IMMEMO		47		// 手动控制注塑机允许开模
#define LOG_MANUL_IMMEMC		48		// 手动控制注塑机允许关模
#define LOG_MANUL_IMMEEF		49		// 手动控制注塑机允许顶针前进
#define LOG_MANUL_IMMEEB		50		// 手动控制注塑机允许顶针后退
#define LOG_MANUL_IMMC1P1		51		// 手动控制注塑机允许抽芯1位置1
#define LOG_MANUL_IMMC1P2		52		// 手动控制注塑机允许抽芯1位置2
#define LOG_MANUL_IMMC2P1		53		// 手动控制注塑机允许抽芯2位置1
#define LOG_MANUL_IMMC2P2		54		// 手动控制注塑机允许抽芯2位置2
#define LOG_MANUL_EOUTON		55		// 手动控制扩展输出打开：
#define LOG_MANUL_EOUTOFF		56		// 手动控制扩展输出关闭：
#define LOG_MANUL_SRVCTRL		57		// 手动控制伺服运转
#define LOG_MANUL_IMMEEF_OFF	58		// 手动控制注塑机允许顶针前进
#define LOG_MANUL_IMMEEB_OFF	59		// 手动控制注塑机允许顶针后退
#define LOG_MANUL_IMMC1P1_OFF	60		// 手动控制注塑机允许抽芯1位置1
#define LOG_MANUL_IMMC1P2_OFF	61		// 手动控制注塑机允许抽芯1位置2
#define LOG_MANUL_IMMC2P1_OFF	62		// 手动控制注塑机允许抽芯2位置1
#define LOG_MANUL_IMMC2P2_OFF	63		// 手动控制注塑机允许抽芯2位置2
#define LOG_MANUL_RASC			64		// 手动控制副臂上行
#define LOG_MANUL_RDES			65		// 手动控制副臂下行
#define LOG_MANUL_RADV			66		// 手动控制副臂引拔前进
#define LOG_MANUL_RRET			67		// 手动控制副臂引拔后退
#define LOG_TEACH_SAVE			68		// 保存教导程序
#define LOG_RESET_SYSPAR		69		// 重置系统参数设置
#define LOG_RESET_SRVPAR		70		// 重置伺服参数设置
#define LOG_RESET_PWD			71		// 重置系统密码设置
#define LOG_CLEAR_SUM			72		// 清除生产总模数
#define LOG_PRODUCT_ID          73      // 产品密钥改变
#define LOG_ACTIVATION          74      // 激活码改变
#define LOG_CLEAR_ALARM         75      // 报警复位
#define LOG_SET_ABS_HOME        76      // 设置绝对值编码器原点
#define LOG_CLR_ABS_HOME        77      // 清除绝对值编码器原点
#define LOG_MANUL_VACUUMON		78		// 手动控制冶具组打开：
#define LOG_MANUL_VACUUMOFF		79		// 手动控制冶具组关闭：


class DialogLogIo;
class DialogLogPar;
class DialogLogDetail;

class xSqlTableModel : public QSqlTableModel
{
	Q_OBJECT
public:
	explicit xSqlTableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	QVariant data(const QModelIndex &idx, int role) const;

private:
};

#define LOG_INPUT_SIZE				8
#define LOG_OUTPUT_SIZE				6
// ********************************************
// 定义系统参数缓冲区(quint16)
#define LOG_ALARM_TIMES				0
#define LOG_ALARM_INTERVAL			1
#define LOG_LANGUAGE				2
#define LOG_ROTATE_OUT_AT_ORIGIN	3
#define LOG_PAUSE_OPEN_DOOR			4
#define LOG_PLAN_MOLDING_LOW		5
#define LOG_PLAN_MOLDING_HIGH		6
#define LOG_PLAN_ALARM_LOW			7
#define LOG_PLAN_ALARM_HIGH			8
#define LOG_REJECT_ALARM			9
#define LOG_MOLD_CLOSED_USE			10
#define LOG_EXT_SERVO_USE			11
#define LOG_RHOR_SERVO_USE			12
#define LOG_ROTATE_INMOLD_USE		13
#define LOG_MAIN_POLARY				14
#define LOG_EXT1_POLARY				15
#define LOG_EXT2_POLARY				16
#define LOG_EXT3_POLARY				17
#define LOG_EXT4_POLARY				18
#define LOG_MAIN_IGNORE				19
#define LOG_EXT1_IGNORE				20
#define LOG_EXT2_IGNORE				21
#define LOG_EXT3_IGNORE				22
#define LOG_EXT4_IGNORE				23
#define LOG_INTERMOLD_DOWN_USE		24
#define LOG_MID_OPEN_USE			25
#define LOG_WAIT_OUTMOULD			26
#define LOG_MAIN_NOALM				27
#define LOG_EXT1_NOALM				28
#define LOG_EXT2_NOALM				29
#define LOG_EXT3_NOALM				30
#define LOG_EXT4_NOALM				31
#define LOG_JIG_USE					32
#define LOG_RUNNER_USE				33
#define LOG_RUNNER_DOWN_USE			34
#define LOG_ADJUST_USE				35
#define LOG_RVER_SERVO_USE			36
#define LOG_HOME_INMOLD             37
#define LOG_PROC2_USE               38
#define LOG_PROC3_USE               39
#define LOG_IP_LOW                  40
#define LOG_IP_HIGH                 41
#define LOG_SUBMASK_LOW             42
#define LOG_SUBMASK_HIGH            43
#define LOG_GATEWAY_LOW             44
#define LOG_GATEWAY_HIGH            45
#define LOG_OIL_INTERVAL_LOW        46
#define LOG_OIL_INTERVAL_HIGH       47
#define LOG_OIL_TIME_LOW            48
#define LOG_OIL_TIME_HIGH           49
#define LOG_OIL_USE                 50
#define LOG_RUNNER_ADVANCE_USE		51
#define LOG_RUNNER_RETURN_USE		52
#define LOG_ROTATE_USE              53
#define LOG_RUN_ROTATE_USE          54
#define LOG_DOOR_RESET_USE          55
#define LOG_EXT1_OUTPOLARY			56
#define LOG_EXT2_OUTPOLARY			57
#define LOG_EXT3_OUTPOLARY			58
#define LOG_EXT4_OUTPOLARY			59
#define LOG_EXTEND_BIT_USE          60
#define LOG_OIL_USE_CTRL            61
#define LOG_MAIN_OUTPOLARY			62
#define LOG_SYS_IO_CLR				63
#define LOG_VISION1_IP_LOW          64
#define LOG_VISION1_IP_HIGH         65
#define LOG_VISION2_IP_LOW          66
#define LOG_VISION2_IP_HIGH         67
#define LOG_VISION3_IP_LOW          68
#define LOG_VISION3_IP_HIGH         69
#define LOG_VISION4_IP_LOW          70
#define LOG_VISION4_IP_HIGH         71
#define LOG_VISION5_IP_LOW          72
#define LOG_VISION5_IP_HIGH         73
#define LOG_VISION6_IP_LOW          74
#define LOG_VISION6_IP_HIGH         75
#define LOG_VISION7_IP_LOW          76
#define LOG_VISION7_IP_HIGH         77
#define LOG_VISION8_IP_LOW          78
#define LOG_VISION8_IP_HIGH         79
#define LOG_VISION1_PORT            80
#define LOG_VISION2_PORT            81
#define LOG_VISION3_PORT            82
#define LOG_VISION4_PORT            83
#define LOG_VISION5_PORT            84
#define LOG_VISION6_PORT            85
#define LOG_VISION7_PORT            86
#define LOG_VISION8_PORT            87
#define LOG_VISION1_TRIGGER         88
#define LOG_VISION2_TRIGGER         89
#define LOG_VISION3_TRIGGER         90
#define LOG_VISION4_TRIGGER         91
#define LOG_VISION5_TRIGGER         92
#define LOG_VISION6_TRIGGER         93
#define LOG_VISION7_TRIGGER         94
#define LOG_VISION8_TRIGGER         95
#define LOG_VISION1_OUTVAR          96
#define LOG_VISION2_OUTVAR          97
#define LOG_VISION3_OUTVAR          98
#define LOG_VISION4_OUTVAR          99
#define LOG_VISION5_OUTVAR          100
#define LOG_VISION6_OUTVAR          101
#define LOG_VISION7_OUTVAR          102
#define LOG_VISION8_OUTVAR          103
#define LOG_MOP_ABD_TIME_LOW        104
#define LOG_MOP_ABD_TIME_HIGH       105
#define LOG_PROC_USE                106
#define LOG_MAIN2_POLARY			107
#define LOG_MAIN3_POLARY			108
#define LOG_MAIN4_POLARY			109
#define LOG_MAIN2_OUTPOLARY			110
#define LOG_MAIN3_OUTPOLARY			111
#define LOG_MAIN4_OUTPOLARY			112
#define LOG_MAIN2_IGNORE			113
#define LOG_MAIN3_IGNORE			114
#define LOG_MAIN4_IGNORE			115
#define LOG_MAIN2_NOALM				116
#define LOG_MAIN3_NOALM				117
#define LOG_MAIN4_NOALM				118



#define LOG_SYSPAR_MOFIGYLL         119
#define LOG_SYSPAR_MOFIGYLH         120
#define LOG_SYSPAR_MOFIGYHL         121
#define LOG_SYSPAR_MOFIGYHH         122
#define LOG_SYSPAR_SIZE             123
// ********************************************
// 定义伺服参数缓冲区(quint16)
#define LOG_MACHINE_MAX_LEN_X		0
#define LOG_MIN_SAFE_DIS_X_B		1
#define LOG_SOFTWARE_MAX_LEN_Y		2
#define LOG_SOFTWARE_MAX_LEN_Z		3
#define LOG_SOFTWARE_MAX_LEN_A		4
#define LOG_SOFTWARE_MAX_LEN_C		5
#define LOG_ORIGIN_OFFSET_X			6
#define LOG_ORIGIN_OFFSET_Y			7
#define LOG_ORIGIN_OFFSET_Z			8
#define LOG_ORIGIN_OFFSET_A			9
#define LOG_ORIGIN_OFFSET_B			10
#define LOG_ORIGIN_OFFSET_C			11
#define LOG_MAX_WAIT_POS_INMOLD_Y	12
#define LOG_MAX_WAIT_POS_INMOLD_A	13
#define LOG_MIN_SAFE_POS_OUTMOLD_Z	14
#define LOG_MAX_SAFE_POS_OUTMOLD_Z	15
#define LOG_MIN_SAFE_POS_INMOLD_Z	16
#define LOG_MAX_SAFE_POS_INMOLD_Z	17
#define LOG_MIN_SAFE_POS_INMOLD_X	18
#define LOG_MAX_SAFE_POS_INMOLD_X	19
#define LOG_MIN_SAFE_POS_INMOLD_B	20
#define LOG_MAX_SAFE_POS_INMOLD_B	21
#define LOG_XMAX_SPEED				22
#define LOG_XMAX_ACCELERATION		23
#define LOG_YMAX_SPEED				24
#define LOG_YMAX_ACCELERATION		25
#define LOG_ZMAX_SPEED				26
#define LOG_ZMAX_ACCELERATION		27
#define LOG_AMAX_SPEED				28
#define LOG_AMAX_ACCELERATION		29
#define LOG_BMAX_SPEED				30
#define LOG_BMAX_ACCELERATION		31
#define LOG_CMAX_SPEED				32
#define LOG_CMAX_ACCELERATION		33
#define LOG_X_UNITS                 34
#define LOG_X_PLUSES                35
#define LOG_Y_UNITS                 36
#define LOG_Y_PLUSES                37
#define LOG_Z_UNITS                 38
#define LOG_Z_PLUSES                39
#define LOG_A_UNITS                 40
#define LOG_A_PLUSES                41
#define LOG_B_UNITS                 42
#define LOG_B_PLUSES                43
#define LOG_C_UNITS                 44
#define LOG_C_PLUSES                45
#define LOG_ANGLE_BMP               46
#define LOG_HOME_MODE               47
#define LOG_HOME_VEL                48
#define LOG_RAMP_BMP                49
#define LOG_MIN_SAFE_ROT            50
#define LOG_MAX_SAFE_ROT            51
#define LOG_MIN_SAFE_TRV            52
#define LOG_MAX_SAFE_TRV            53
#define LOG_ENCODER_X               54
#define LOG_ENCODER_Y               55
#define LOG_ENCODER_Z               56
#define LOG_ENCODER_A               57
#define LOG_ENCODER_B               58
#define LOG_ENCODER_C               59
#define LOG_HOME_WAIT_X             60
#define LOG_HOME_WAIT_Y             61
#define LOG_HOME_WAIT_Z             62
#define LOG_HOME_WAIT_A             63
#define LOG_HOME_WAIT_B             64
#define LOG_HOME_WAIT_C             65
#define LOG_MOD_X                   66
#define LOG_MOD_Y                   67
#define LOG_MOD_Z                   68
#define LOG_MOD_A                   69
#define LOG_MOD_B                   70
#define LOG_MOD_C                   71
#define LOG_MIN_SAFE_POS_OUTMOLD2_Z	72
#define LOG_MAX_SAFE_POS_OUTMOLD2_Z	73
#define LOG_MIN_SAFE_POS_INMOLD_Z_A 74
#define LOG_MAX_SAFE_POS_INMOLD_Z_A 75
#define LOG_XMAX_JERK               76
#define LOG_YMAX_JERK               77
#define LOG_ZMAX_JERK               78
#define LOG_AMAX_JERK               79
#define LOG_BMAX_JERK               80
#define LOG_CMAX_JERK               81
#define LOG_HOME_VEL_SLOW           82
#define LOG_MIN_B_TRAVE             83
#define LOG_MAX_B_TRAVE             84
#define LOG_MIN_C_TRAVE             85
#define LOG_MAX_C_TRAVE             86
#define LOG_MIN_C_INMOLD            87
#define LOG_MAX_C_INMOLD            88
#define LOG_MIN_X_TRAVE             89
#define LOG_MAX_X_TRAVE             90

#define LOG_SRVPAR_MODIFYLL			91
#define LOG_SRVPAR_MODIFYLH			92
#define LOG_SRVPAR_MODIFYHL			93
#define LOG_SRVPAR_MODIFYHH			94
#define LOG_SRVPAR_SIZE				95
// ********************************************
// 定义界面参数缓冲区(quint16)
#define LOG_UI_LAN					0
#define LOG_UI_SCRSAVER				1
#define LOG_UI_BKLIGHT				2
#define LOG_UI_SH0CK				3
#define LOG_UI_KEYBELL				4
#define LOG_UI_TOUCHBELL			5
#define LOG_UI_BELLFREQ				6
#define LOG_UI_SWITCHUSE			7
#define LOG_UI_ALWAYSON				8

#define LOG_UIPAR_MODIFY			9
#define LOG_UIPAR_SIZE				10
//*********************************************

class xSysLog : public QObject
{
	Q_OBJECT

public:
	enum LogSeg
	{
		logTime = 0,			// 日志记录时间
		logType = 1,			// 日志记录类型
		logUser = 2,			// 日志记录用户
		logValue = 3,			// 日志记录内容
		logExt = 4,				// 日志记录扩展内容
		logID = 5,				// 日志记录唯一ID
		input = 6,				// 系统输入状态
		output = 7,				// 系统输出状态
		parameter = 8			// 参数状态
	};
	xSysLog(QObject *parent = 0);
	~xSysLog();
    static bool OpenSysLog(void);
	static void DestroySysLog(void);
	static xSqlTableModel *GetModel(void);
    static void AddRecord(quint8 type, quint16 value, QString ext = QString(""), QByteArray par = QByteArray(),quint16 value2 = 0);
	static bool SaveChange(void);
	static int DoDiaIo(const QDateTime &time, const quint16 (&input)[LOG_INPUT_SIZE], const quint16 (&output)[LOG_OUTPUT_SIZE]);
	static int DoDiaPar(const QDateTime &time, const QByteArray &par, const quint8 type);
	static int DoDiaDetail(const QString &time, const QIcon &type, const QString &user, const QString &detail);

private:
	static xSqlTableModel *pModel;
	static DialogLogIo *pDiaIo;
	static DialogLogPar *pDiaPar;
	static DialogLogDetail *pDiaDetail;
};

#endif // XSYSTEMLOG_H
