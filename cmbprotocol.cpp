#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QSettings>
#include <QWSServer>
#include "xconfig.h"
#include "SignalNum.h"
#include "xKeyPad.h"
#include "safeswitch.h"
#include "indicatorled.h"
#include "xioport.h"
#include "cmbprotocol.h"
#include "modbus-private.h"
#include "xstringresource.h"
#include "xpermissions.h"
#include "xsystemlog.h"
#include "xmessagebox.h"
#include "xmessageboxIP.h"
#include "xtopinfo.h"
#include "xtranslator.h"
#include "HalBoard.h"
//输入信号映射表
// (信易&&非欧规)

extern HardwareInterface *board;
const uint8_t inputtabshinieuro[256] =
{
    /////////////////////////////////////////////主板1
    InSignalNum_MOP,
    InSignalNum_MCP,
    InSignalNum_DOOR,
    InSignalNum_AUTO,
    InSignalNum_REJECT,
    InSignalNum_IMMEMG,
    InSignalNum_MID,
    InSignalNum_LOW,
    InSignalNum_ZSAFE,
// #if (FACTORY == FA_SHINI)&&(!ISEUROMAP)
//    InSignalNum_EEB,
//    InSignalNum_EEF,
//    0,
//#else
//    0,0,0,
//#endif

    InSignalNum_EEB,
    InSignalNum_EEF,
    0,

    InSignalNum_ADVSAFE,
    InSignalNum_DESSAFE,
    InSignalNum_EMG,
    InSignalNum_PWROFF,
    /////////////////////////////////////////////主板2
    InSignalNum_IMOP,
    InSignalNum_EEF,
    InSignalNum_EEB,
    InSignalNum_C1P1,
    InSignalNum_C1P2,
    InSignalNum_C2P1,
    InSignalNum_C2P2,
    0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    /////////////////////////////////////////////主板3
    InSignalNum_XCWL,
    InSignalNum_YCWL,
    InSignalNum_ZCWL,
    InSignalNum_ACWL,
    InSignalNum_BCWL,
    InSignalNum_CCWL,
    0xFF,0xFF,
    InSignalNum_XCCWL,
    InSignalNum_YCCWL,
    InSignalNum_ZCCWL,
    InSignalNum_ACCWL,
    InSignalNum_BCCWL,
    InSignalNum_CCCWL,
    0xFF,0xFF,
    /////////////////////////////////////////////主板4
    InSignalNum_XALM,
    InSignalNum_YALM,
    InSignalNum_ZALM,
    InSignalNum_AALM,
    InSignalNum_BALM,
    InSignalNum_CALM,
    0xFF,0xFF,
    InSignalNum_XORG,
    InSignalNum_YORG,
    InSignalNum_ZORG,
    InSignalNum_AORG,
    InSignalNum_BORG,
    InSignalNum_CORG,
    0xFF,0xFF,
    /////////////////////////////////////////////IO板1
    InSignalNum_PHOR,
    InSignalNum_PVER,
    InSignalNum_VAC1,
    InSignalNum_VAC2,
    InSignalNum_GRIP1,
    InSignalNum_GRIP2,
    InSignalNum_GRIP3,
    InSignalNum_GRIP4,
    InSignalNum_OIL,
    InSignalNum_RHOR,
    InSignalNum_RVER,
    0,
    InSignalNum_RASC,
    InSignalNum_RDES,
    InSignalNum_RADV,
    InSignalNum_RRET,
    /////////////////////////////////////////////IO板2
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /////////////////////////////////////////////IO板3
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /////////////////////////////////////////////IO板4
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /////////////////////////////////////////////保留
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};
//
const uint8_t inputtab[256] =
{
    /////////////////////////////////////////////主板1
    InSignalNum_MOP,
    InSignalNum_MCP,
    InSignalNum_DOOR,
    InSignalNum_AUTO,
    InSignalNum_REJECT,
    InSignalNum_IMMEMG,
    InSignalNum_MID,
    InSignalNum_LOW,
    InSignalNum_ZSAFE,
    0,0,0,

    InSignalNum_ADVSAFE,
    InSignalNum_DESSAFE,
    InSignalNum_EMG,
    InSignalNum_PWROFF,
    /////////////////////////////////////////////主板2
    InSignalNum_IMOP,
    InSignalNum_EEF,
    InSignalNum_EEB,
    InSignalNum_C1P1,
    InSignalNum_C1P2,
    InSignalNum_C2P1,
    InSignalNum_C2P2,
    0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    /////////////////////////////////////////////主板3
    InSignalNum_XCWL,
    InSignalNum_YCWL,
    InSignalNum_ZCWL,
    InSignalNum_ACWL,
    InSignalNum_BCWL,
    InSignalNum_CCWL,
    0xFF,0xFF,
    InSignalNum_XCCWL,
    InSignalNum_YCCWL,
    InSignalNum_ZCCWL,
    InSignalNum_ACCWL,
    InSignalNum_BCCWL,
    InSignalNum_CCCWL,
    0xFF,0xFF,
    /////////////////////////////////////////////主板4
    InSignalNum_XALM,
    InSignalNum_YALM,
    InSignalNum_ZALM,
    InSignalNum_AALM,
    InSignalNum_BALM,
    InSignalNum_CALM,
    0xFF,0xFF,
    InSignalNum_XORG,
    InSignalNum_YORG,
    InSignalNum_ZORG,
    InSignalNum_AORG,
    InSignalNum_BORG,
    InSignalNum_CORG,
    0xFF,0xFF,
    /////////////////////////////////////////////IO板1
    InSignalNum_PHOR,
    InSignalNum_PVER,
    OutSignalNum_VAC1,
    OutSignalNum_VAC2,
    OutSignalNum_GRIP1,
    OutSignalNum_GRIP2,
    OutSignalNum_GRIP3,
    OutSignalNum_GRIP4,
    InSignalNum_OIL,
    InSignalNum_RHOR,
    InSignalNum_RVER,
    0,
    InSignalNum_RASC,
    InSignalNum_RDES,
    InSignalNum_RADV,
    InSignalNum_RRET,
    /////////////////////////////////////////////IO板2
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /////////////////////////////////////////////IO板3
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /////////////////////////////////////////////IO板4
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /////////////////////////////////////////////保留
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

//输出信号映射表
const uint8_t outputtab[256] =
{
    /////////////////////////////////////////////主板1
    OutSignalNum_EMO,
    OutSignalNum_EMC,
    OutSignalNum_MAF,
    OutSignalNum_EEF,
    OutSignalNum_HEMC,
    OutSignalNum_HMAF,
    OutSignalNum_ALM,
#if (FACTORY == FA_SHINI)
    OutSignalNum_EEB,
#else
    OutSignalNum_BEEP,
#endif
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    /////////////////////////////////////////////主板2
    OutSignalNum_XON,
    OutSignalNum_YON,
    OutSignalNum_ZON,
    OutSignalNum_AON,
    OutSignalNum_BON,
    OutSignalNum_CON,
    0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    /////////////////////////////////////////////主板3
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    /////////////////////////////////////////////主板4
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    /////////////////////////////////////////////IO板1
    OutSignalNum_PHOR,
    OutSignalNum_PVER,
    0,0,0,0,0,0,0,
    OutSignalNum_RHOR,
    OutSignalNum_RVER,
    OutSignalNum_OIL,
    OutSignalNum_RDES,
    OutSignalNum_RRET,
    OutSignalNum_RADJASC,
    OutSignalNum_RADJADV,
    /////////////////////////////////////////////IO板2
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /////////////////////////////////////////////IO板3
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /////////////////////////////////////////////IO板4
    OutSignalNum_ROB,
    OutSignalNum_EEB,
    OutSignalNum_C1P1,
    OutSignalNum_C1P2,
    OutSignalNum_C2P1,
    OutSignalNum_C2P2,
    0,0,
    0,0,0,0,0,0,0,0,
    /////////////////////////////////////////////保留
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

bool CMBProtocol::typeMate;					// 操作器与主控模块类型匹配
QString CMBProtocol::curPgmName("");		// 当前程序名称
QString CMBProtocol::alfaPgmName("");		// alfa程序名称
uint64_t CMBProtocol::InputMain;			// 主板输入状态
uint16_t CMBProtocol::InputEm1;				// 扩展模块1输入状态
uint16_t CMBProtocol::InputEm2;				// 扩展模块2输入状态
uint16_t CMBProtocol::InputEm3;				// 扩展模块3输入状态
uint16_t CMBProtocol::InputEm4;				// 扩展模块4输入状态
uint64_t CMBProtocol::OutputMain;			// 主板输出状态
uint16_t CMBProtocol::OutputEm1;			// 扩展模块1输出状态
uint16_t CMBProtocol::OutputEm2;			// 扩展模块2输出状态
uint16_t CMBProtocol::OutputEm3;			// 扩展模块3输出状态
uint16_t CMBProtocol::OutputEm4;			// 扩展模块4输出状态
qint32 CMBProtocol::svPhorPos;             // 正臂引拔伺服位置
qint32 CMBProtocol::svPverPos;             // 正臂上下伺服位置
qint32 CMBProtocol::svTrvPos;				// 横行伺服位置
qint32 CMBProtocol::svRhorPos;             // 副臂引拔伺服位置
qint32 CMBProtocol::svRverPos;             // 副臂上下伺服位置
qint32 CMBProtocol::svExtPos;				// 扩展伺服位置
uint16_t CMBProtocol::ExtBoardState;		// 扩展模块状态
uint16_t CMBProtocol::SystemState;			// 系统工作状态,0:手动,1:自动,2:错误
VersionParameter CMBProtocol::sysVersion;	// 版本信息
uint8_t CMBProtocol::pirateFlag;			// 授权信息
uint64_t CMBProtocol::functionsList;		// 系统功能列表
quint8 CMBProtocol::srvSpeed;				// 伺服相对速度
quint8 CMBProtocol::manualSpeed;			// 伺服手动速度
quint8 CMBProtocol::adjustSpeed;            // 调位速度
double CMBProtocol::servoScale;             // 伺服刻度
bool CMBProtocol::switchUse;
bool CMBProtocol::alwaysOn;
bool CMBProtocol::templateUse;
bool CMBProtocol::alfamode;
uint16_t CMBProtocol::RunningState;				// 系统运行状态,0:暂停,1:运行
uint16_t CMBProtocol::RunningType;				// 系统运行类型,0:全自动,1:单步,2:单循环
uint16_t CMBProtocol::programPc;					// 程序指令指针

uint16_t CMBProtocol::m_mbaddrspace[MODBUS_ADDRESS_MAX];
uint16_t CMBProtocol::m_mbaddrspace2[MODBUS_ADDRESS_MAX];
// ************************************************
// ModBus
// ************************************************
// 构造 ModBus 对象
CMBProtocol::CMBProtocol(QObject *parent) : QObject(parent)
{
#if PENDANT_PROTOCOL
#if CONNECT_BY_NET
    // 从配置文件读取主板IP地址
    QString IP;
    char *charIP;
    quint32 tmpIP;
RETRY:
    QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
    tmpIP = settings.value(XPAD_SET_IP, QString("")).toUInt();
    IP = QString::number((quint8)(tmpIP>>24)) + "." + QString::number((quint8)(tmpIP>>16)) + "." +
         QString::number((quint8)(tmpIP>>8)) + "." + QString::number((quint8)(tmpIP));

    QByteArray temp = IP.toLatin1();
    charIP=temp.data();

    timeval val;
//    val.tv_sec = 1;   // 原超时时间1秒，偶尔出现连不上，改为2秒，2019-01-23
    val.tv_sec = 2;
    val.tv_usec = 0;
    m_modbus = modbus_new_tcp(charIP, 502);
    modbus_set_error_recovery(m_modbus, (modbus_error_recovery_mode)((1<<1) | (1<<2)));
    modbus_set_response_timeout(m_modbus, &val);
    if( modbus_connect(m_modbus) == -1 )
    {
        modbus_free(m_modbus);
        xMessageBoxIP BoxIP;
        BoxIP.DoForm();
        goto RETRY;
    }
#else
#if defined(Q_WS_QWS)
	m_modbus = modbus_new_rtu(board->get_MB_PORT(), MB_BAUD, MB_PARITY, MB_DATABITS, MB_STOPBITS);
#else
    m_modbus = modbus_new_rtu(MB_PORT, MB_BAUD, MB_PARITY, MB_DATABITS, MB_STOPBITS);
#endif
    if( modbus_connect(m_modbus) == -1 )
    {
        xMessageBox::DoWarning(tr("系统警告"), tr("无法连接通讯端口！"));
    }
#endif
    modbus_set_slave(m_modbus, 1);
#endif
    pTimer = new QTimer(this);
//    StopPeriodTimer();
    connect(pTimer, SIGNAL(timeout()), this, SLOT(MBPeriodPoll()));
    ComState = true;
    memset(Alarms, ALMRES_NO_ALARM, sizeof(Alarms));
    sysMessage = ALMRES_NO_ALARM;
}
// 析构 ModBus 对象
CMBProtocol::~CMBProtocol()
{
#if PENDANT_PROTOCOL
    if (m_modbus)
		modbus_free(m_modbus);
#endif
	delete pTimer;
}
// 启动状态轮询定时器
void CMBProtocol::StartPeriodTimer(void)
{
    pTimer->start(100);
}
// 停止状态轮询定时器
void CMBProtocol::StopPeriodTimer(void)
{
	pTimer->stop();
}
// 关闭通讯串口
void CMBProtocol::CloseSerialPort(void)
{
#if PENDANT_PROTOCOL
	modbus_close(m_modbus);
#endif
}

int8_t CMBProtocol::ReadRunState(void)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
	ret = SendMsg(SYSTEM_STATE, HOME_STATE);
	if (ret == SENDMSG_RET_ACK)
	{
		if (m_mbaddrspace[SYSTEM_STATE] != SystemState)
		{
			SystemState = m_mbaddrspace[SYSTEM_STATE];
		}
		if (m_mbaddrspace[RUN_STATE] != RunningState)
		{
			RunningState = m_mbaddrspace[RUN_STATE];
		}
		if (m_mbaddrspace[RUN_TYPE] != RunningType)
		{
			RunningType = m_mbaddrspace[RUN_TYPE];
		}
		if (m_mbaddrspace[HOME_STATE] != HomeState)
		{
			HomeState = m_mbaddrspace[HOME_STATE];
		}
	}
#endif
    return ret;
}

int16_t CMBProtocol::ReadSDOPara()
{
#if PENDANT_PROTOCOL
    if(SendMsg(COMMAND_SDO_RDDATA,COMMAND_SDO_RDOK,TRUE) == SENDMSG_RET_ACK)
    {
        qDebug()<<m_mbaddrspace[COMMAND_SDO_RDOK]<<' '<<m_mbaddrspace[COMMAND_SDO_RDDATA];
        SendMsg(COMMAND_SDO_RDOK,COMMAND_SDO_RDOK,FALSE);
        if(m_mbaddrspace[COMMAND_SDO_RDOK])
        {
            m_mbaddrspace[COMMAND_SDO_RDOK]=0;
            return true;
        }
        else
            return false;
    }
#endif
}

// 消息发送
int8_t CMBProtocol::SendMsg(uint16_t begin, uint16_t end, uint8_t read, int retry)
{
    int retryCount = retry;
	int ret = 0;
#if PENDANT_PROTOCOL
	if (begin >= MODBUS_ADDRESS_MAX) return SENDMSG_RET_REGADDR_ERR;
	if (end >= MODBUS_ADDRESS_MAX) return SENDMSG_RET_REGADDR_ERR;
RETRY:
	modbus_flush(m_modbus);
	modbus_set_slave(m_modbus, 1);
	if (read)
	{
		ret = modbus_read_registers(m_modbus, begin, end-begin+1, &m_mbaddrspace[begin]);
	}
	else
	{
        ret = modbus_write_registers(m_modbus, begin, end-begin+1, &m_mbaddrspace[begin]);
	}
	if (ret < 0)
	{
		if (retryCount > 0)
		{
			retryCount--;
			goto RETRY;
		}
		return SENDMSG_RET_NACK;
	}
	else
#endif
        return SENDMSG_RET_ACK;
}
int8_t CMBProtocol::SendMsg2(uint16_t begin, uint16_t end, uint8_t read, int retry)
{
    int retryCount = retry;
    int ret = 0;
#if PENDANT_PROTOCOL
    if (begin >= MODBUS_ADDRESS_MAX) return SENDMSG_RET_REGADDR_ERR;
    if (end >= MODBUS_ADDRESS_MAX) return SENDMSG_RET_REGADDR_ERR;
RETRY:
    modbus_flush(m_modbus);
    modbus_set_slave(m_modbus, 2);
    if (read)
    {
        ret = modbus_read_registers(m_modbus, begin, end-begin+1, &m_mbaddrspace2[begin]);
    }
    else
    {
        ret = modbus_write_registers(m_modbus, begin, end-begin+1, &m_mbaddrspace2[begin]);
    }
	if (ret < 0)
    {
        if (retryCount > 0)
        {
            retryCount--;
            goto RETRY;
        }
        return SENDMSG_RET_NACK;
    }
    else
#endif
        return SENDMSG_RET_ACK;
}
// 读取16位数据
uint16_t CMBProtocol::ReadReg16(uint16_t regaddr)
{
	if (regaddr < MODBUS_ADDRESS_MAX)
		return m_mbaddrspace[regaddr];
	else
		return 0;
}
// 读取16位数据
uint16_t CMBProtocol::ReadReg16_MB2(uint16_t regaddr)
{
    if (regaddr < MODBUS_ADDRESS_MAX)
        return m_mbaddrspace2[regaddr];
    else
        return 0;
}
// 读取32位数据
uint32_t CMBProtocol::ReadReg32(uint16_t regaddr)
{
	uint32_t ret = 0;
	if ((regaddr + 1) < MODBUS_ADDRESS_MAX)
	{
		ret = m_mbaddrspace[regaddr + 1];
		ret <<= 16;
		ret |= m_mbaddrspace[regaddr];
	}
	return ret;
}
// 读取32位数据
uint32_t CMBProtocol::ReadReg32_MB2(uint16_t regaddr)
{
    uint32_t ret = 0;
    if ((regaddr + 1) < MODBUS_ADDRESS_MAX)
    {
        ret = m_mbaddrspace2[regaddr];
        ret <<= 16;
        ret |= m_mbaddrspace[regaddr];
    }
    return ret;
}

QString CMBProtocol::XMLFileVersion(void)
{
    return XML_VERSION100;
}

// 初始化系统通讯状态数据
uint8_t CMBProtocol::InitSystemStatus(void)
{
    // 核对操作器和主控模块类型和软件版本
	if (ReadVersion() != SENDMSG_RET_ACK)
        return COM_INIT_COM_ERR;    
    typeMate = false;
    if (sysVersion.m_soft_extra == ROBOTARM_TYPE_SIXSV_PAD_YZ)
        typeMate = true;
    if ((sysVersion.m_soft_extra_new == ROBOTARM_TYPE_SIXSV_PAD_YZ)&&(sysVersion.m_soft_extra == 0xFF))
        typeMate = true;
    if ((sysVersion.m_soft_extra_new == ROBOTARM_TYPE_SIXSV_PAD_E4) || (sysVersion.m_soft_extra_new == ROBOTARM_TYPE_SIXSV_PAD_E3))
        typeMate = true;
    if (sysVersion.m_soft_extra_new == ROBOTARM_TYPE_SIXSV_PAD_E0)
        typeMate = true;
    if ((sysVersion.m_soft_extra_new == ROBOTARM_TYPE_SIXSV_PAD_F4) || (sysVersion.m_soft_extra_new == ROBOTARM_TYPE_SIXSV_PAD_F3))
        typeMate = true;
    // 读取系统授权信息
	if (ReadPirate() != SENDMSG_RET_ACK)
        return COM_INIT_COM_ERR;
    // 查询系统功能列表
    if (WriteFunctions() != SENDMSG_RET_ACK)
        return COM_INIT_COM_ERR;
	// 读取系统功能列表
	if (ReadFunctions() != SENDMSG_RET_ACK)
		return COM_INIT_COM_ERR;
	// 读取厂商代码
	if (ReadFactory() != SENDMSG_RET_ACK)
		return COM_INIT_COM_ERR;
	// 读取原点复归设置
	if (ReadHome() != SENDMSG_RET_ACK)
		return COM_INIT_COM_ERR;
	// 读取系统参数设置
	if (ReadSystem() != SENDMSG_RET_ACK)
		return COM_INIT_COM_ERR;
	// 读取伺服参数设置
	if (ReadServo() != SENDMSG_RET_ACK)
		return COM_INIT_COM_ERR;
    // 读取IO映射表
    bool haveiobmp = false;
    if (GetFunctions(SUB_FUN2_IO_BMP))
    {
        if (ReadIoBmp() == SENDMSG_RET_ACK)
        {
            haveiobmp = true;
            xIoPort::UpdateIn2Fun((qint8*)&m_mbaddrspace[IN_BMP_BEG]);
            xIoPort::UpdateOut2Fun((qint8*)&m_mbaddrspace[OUT_BMP_BEG]);
        }
    }
    if (!haveiobmp)
    {
        if ((FACTORY == FA_SHINI) && GetFunctions(SUB_FUN_EUROMAP))
            xIoPort::UpdateIn2Fun((qint8*)inputtabshinieuro);
        else
            xIoPort::UpdateIn2Fun((qint8*)inputtab);
        xIoPort::UpdateOut2Fun((qint8*)outputtab);
    }
    CommandFUNUI(FUN_UI_WAIT_VALID_TIME);
	// 读取系统当前程序设置
    QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
    curPgmName = settings.value(XPAD_SET_CURPGM, QString("")).toString();
    switchUse = settings.value(XPAD_SET_SWITCHUSE, SAFE_SWITCH_USE).toBool();
    alwaysOn = settings.value(XPAD_SET_ALWAYSON, SAFE_SWITCH_USE).toBool();
	templateUse = settings.value(XPAD_SET_TEMPLATE, false).toBool();

    alfamode = settings.value(XPAD_SET_ALFAMODE, false).toBool();
    alfamode = false;
    alfaPgmName = settings.value(XPAD_SET_ALFAPGM, QString("")).toString();
    // 初始化周期轮询数据
	if (PeriodRead() != SENDMSG_RET_ACK)
        return COM_INIT_COM_ERR;
	// Initialize the servo position
	svPhorPos = (quint32)ReadReg16(SERVO_X_POS) | ((quint32)ReadReg16(SERVO_X_POS_EXT) << 16);
	svPverPos = (quint32)ReadReg16(SERVO_Y_POS) | ((quint32)ReadReg16(SERVO_Y_POS_EXT) << 16);
	svTrvPos = (quint32)ReadReg16(SERVO_Z_POS) | ((quint32)ReadReg16(SERVO_Z_POS_EXT) << 16);
	svRhorPos = (quint32)ReadReg16(SERVO_B_POS) | ((quint32)ReadReg16(SERVO_B_POS_EXT) << 16);
	svRverPos = (quint32)ReadReg16(SERVO_A_POS) | ((quint32)ReadReg16(SERVO_A_POS_EXT) << 16);
	svExtPos = (quint32)ReadReg16(SERVO_C_POS) | ((quint32)ReadReg16(SERVO_C_POS_EXT) << 16);
	// Initialize the input ports
	InputMain = ReadReg32(MAIN_BOARD_INPUT_LOW) | ((uint64_t)ReadReg32(MAIN_BOARD_INPUT_EXT_LOW) << 32);
	InputEm1 = ReadReg16(EXT1_BOARD_INPUT);
	InputEm2 = ReadReg16(EXT2_BOARD_INPUT);
	InputEm3 = ReadReg16(EXT3_BOARD_INPUT);
	InputEm4 = ReadReg16(EXT4_BOARD_INPUT);
	// Initialize the output ports
    OutputMain = (ReadReg32(MAIN_BOARD_OUTPUT_LOW) | ((uint64_t)ReadReg32(MAIN_BOARD_OUTPUT_EXT_LOW)<<32));
	OutputEm1 = ReadReg16(EXT1_BOARD_OUTPUT);
	OutputEm2 = ReadReg16(EXT2_BOARD_OUTPUT);
	OutputEm3 = ReadReg16(EXT3_BOARD_OUTPUT);
	OutputEm4 = ReadReg16(EXT4_BOARD_OUTPUT);
	// initialize the system working state
	SystemState = ReadReg16(SYSTEM_STATE);
	RunningState = ReadReg16(RUN_STATE);
	RunningType = ReadReg16(RUN_TYPE);
	HomeState = ReadReg16(HOME_STATE);
	// Initialize the production information;
	productSum = ReadReg32(TOTAL_MOLDS_LOW);
	productPlan = ReadReg32(TOTAL_PLAN_LOW);
//	productPeriod = ReadReg16(PERIOD_TIME);
//    inmoldTime = ReadReg16(INMOLD_TIME);
	programPc = ReadReg16(PC_POINTER);
    productPeriod = (quint32)ReadReg16(PERIOD_TIME) | ((quint32)ReadReg16(PERIOD_TIME1_H) << 16);
    inmoldTime = (quint32)ReadReg16(INMOLD_TIME) | ((quint32)ReadReg16(INMOLD_TIME1_H) << 16);

//    if (GetProcUse(1))
    {
        productPeriod2 = (quint32)ReadReg16(PERIOD_TIME2) | ((quint32)ReadReg16(PERIOD_TIME2_H) << 16);
        inmoldTime2 = (quint32)ReadReg16(INMOLD_TIME2) | ((quint32)ReadReg16(INMOLD_TIME2_H) << 16);
        programPc2 = ReadReg16(PC_POINTER2);
    }
//    if (GetProcUse(2))
    {
        productPeriod3 = (quint32)ReadReg16(PERIOD_TIME3) | ((quint32)ReadReg16(PERIOD_TIME3_H) << 16);
        inmoldTime3 = (quint32)ReadReg16(INMOLD_TIME3) | ((quint32)ReadReg16(INMOLD_TIME3_H) << 16);
        programPc3 = ReadReg16(PC_POINTER3);
    }
    // Initialize the extended board connection state
	ExtBoardState = ReadReg16(EXT_BOARD_STATE);

    keypressed = ReadReg16(KEY_PRESSED);
    //pyq 初始化实时扭矩，转速
    actualTrqX = ReadReg16(ACTUAL_TRQ_X);
    actualTrqY = ReadReg16(ACTUAL_TRQ_Y);
    actualTrqZ = ReadReg16(ACTUAL_TRQ_Z);
    actualTrqA = ReadReg16(ACTUAL_TRQ_A);
    actualTrqB = ReadReg16(ACTUAL_TRQ_B);
    actualTrqC = ReadReg16(ACTUAL_TRQ_C);
    actualSpeedX = ReadReg16(ACTUAL_SPEED_X);
    actualSpeedY = ReadReg16(ACTUAL_SPEED_Y);
    actualSpeedZ = ReadReg16(ACTUAL_SPEED_Z);
    actualSpeedA = ReadReg16(ACTUAL_SPEED_A);
    actualSpeedB = ReadReg16(ACTUAL_SPEED_B);
    actualSpeedC = ReadReg16(ACTUAL_SPEED_C);
    //pyq end
    //
    if (SystemState == SYS_STATE_JOG)
        SetSysState(SYS_STATE_MANUAL);
	return COM_INIT_OK;
}
// ************************************************
// 周期轮循接口
// ************************************************
int8_t CMBProtocol::PeriodRead(void)
{
#if PENDANT_PROTOCOL
    return SendMsg(MAIN_BOARD_INPUT_LOW, POWER_ALARM);
#else
	return SENDMSG_RET_ACK;
#endif
}
// 更新系统轮询状态数据
void CMBProtocol::MBPeriodPoll()
{
    int i;
	quint8 sysstatechanged = 0;
	quint8 oldsysstate = ((SystemState&3)<<3) | ((RunningState&1)<<2) | (RunningType&3);
	if (SystemState==SYS_STATE_AUTO) sysstatechanged ++;
	if (RunningState==RUN_STATE_PAUSE) sysstatechanged ++;
	if ((RunningType==RUN_TYPE_LOOP)||(RunningType==RUN_TYPE_SINGLE)) sysstatechanged ++;
	if (!GetTypeMatch())
		return;
    quint32 ret;
	bool writeLog = false;
    qint32 posTmp;
    uint64_t inputTmp, outputTmp, stateTmp;
    uint64_t mainInputTmp;
	quint32 srvPos[6];
    uint32_t alm;
	ret = PeriodRead();
	if (ret != SENDMSG_RET_ACK)
    {
		// 通讯错误
        // 如果通讯状态发生变化则更新通讯状态
        if (ComState != false)
        {
            ComState = false;
			if (pTopInfo->isVisible())
				pTopInfo->hide();
			srvPos[AXIS_IDX_PHOR] = 0, srvPos[AXIS_IDX_PVER] = 0, srvPos[AXIS_IDX_TRV] = 0;
			srvPos[AXIS_IDX_RHOR] = 0, srvPos[AXIS_IDX_RVER] = 0, srvPos[AXIS_IDX_EXT] = 0;
			pTopInfo->ShowInformation(QPixmap(":/img/48X48/ComError.png"), tr("错误"), tr("系统通讯错误：\n操作器与主控模块无法正常通讯，请关闭系统然后检查通讯链路是否正常。"), false);
			xSysLog::AddRecord(SYSLOG_TYPE_ALM, 255, QString(""), QByteArray((char*)srvPos, sizeof(srvPos)));
			xSysLog::SaveChange();
		}
		return;
    }
    // 如果通讯状态发生变化则更新通讯状态
    if (ComState != true)
    {
        ComState = true;
		if (pTopInfo->isVisible())
			pTopInfo->hide();
		ReadHome();
		ReadSystem();
		ReadServo();
	}
	if (ret == SENDMSG_RET_ACK)
    {
		// 更新伺服位置
        posTmp = ((qint32)ReadReg16(SERVO_X_POS)) | ((qint32)ReadReg16(SERVO_X_POS_EXT) << 16);
		if (posTmp != svPhorPos)
        {
            svPhorPos = posTmp;
            srvPos[AXIS_IDX_PHOR] = svPhorPos;
            emit signal_XPosChange(svPhorPos);
        }
        posTmp = ((qint32)ReadReg16(SERVO_Y_POS)) | ((qint32)ReadReg16(SERVO_Y_POS_EXT) << 16);
		if (posTmp != svPverPos)
        {
            svPverPos = posTmp;
            srvPos[AXIS_IDX_PVER] = svPverPos;
            emit signal_YPosChange(svPverPos);
        }
        posTmp = ((qint32)ReadReg16(SERVO_Z_POS)) | ((qint32)ReadReg16(SERVO_Z_POS_EXT) << 16);
		if (posTmp != svTrvPos)
        {
            svTrvPos = posTmp;
            srvPos[AXIS_IDX_TRV] = svTrvPos;
            emit signal_ZPosChange(svTrvPos);
        }
        posTmp = ((qint32)ReadReg16(SERVO_B_POS)) | ((qint32)ReadReg16(SERVO_B_POS_EXT) << 16);
		if (posTmp != svRhorPos)
		{
            svRhorPos = posTmp;
            srvPos[AXIS_IDX_RHOR] = svRhorPos;
            emit signal_BPosChange(svRhorPos);
		}
        posTmp = ((qint32)ReadReg16(SERVO_A_POS)) | ((qint32)ReadReg16(SERVO_A_POS_EXT) << 16);
		if (posTmp != svRverPos)
		{
            svRverPos = posTmp;
            srvPos[AXIS_IDX_RVER] = svRverPos;
            emit signal_APosChange(svRverPos);
		}
        posTmp = ((qint32)ReadReg16(SERVO_C_POS)) | ((qint32)ReadReg16(SERVO_C_POS_EXT) << 16);
		if (posTmp != svExtPos)
		{
            svExtPos = posTmp;
            srvPos[AXIS_IDX_EXT] = svExtPos;
            emit signal_CPosChange(svExtPos);
		}
        // //////////////////////////////////////////////////////////////////////////////////////////////////
		// 更新系统输入状态
        mainInputTmp = ((uint64_t)ReadReg32(MAIN_BOARD_INPUT_LOW) | ((uint64_t)ReadReg32(MAIN_BOARD_INPUT_EXT_LOW) << 32));
        if (mainInputTmp != InputMain)
        {
           InputMain = mainInputTmp; emit signal_InputChange();
        }
        inputTmp = ReadReg16(EXT1_BOARD_INPUT);
        if (inputTmp != InputEm1)
        {
            InputEm1 = inputTmp; emit signal_InputChange();
        }
        inputTmp = ReadReg16(EXT2_BOARD_INPUT);
        if (inputTmp != InputEm2)
        {
            InputEm2 = inputTmp; emit signal_InputChange();
        }
        inputTmp = ReadReg16(EXT3_BOARD_INPUT);
        if (inputTmp != InputEm3)
        {
            InputEm3 = inputTmp; emit signal_InputChange();
        }
        inputTmp = ReadReg16(EXT4_BOARD_INPUT);
        if (inputTmp != InputEm4)
        {
            InputEm4 = inputTmp; emit signal_InputChange();
        }
		// 更新系统输出状态
        outputTmp = ((uint64_t)ReadReg32(MAIN_BOARD_OUTPUT_LOW) | ((uint64_t)ReadReg32(MAIN_BOARD_OUTPUT_EXT_LOW)<<32));
        if (outputTmp != OutputMain)
        {
            OutputMain = outputTmp; emit signal_OutputChange();
        }
        outputTmp = ReadReg16(EXT1_BOARD_OUTPUT);
        if (outputTmp != OutputEm1)
        {
            OutputEm1 = outputTmp; emit signal_OutputChange();
        }
        outputTmp = ReadReg16(EXT2_BOARD_OUTPUT);
        if (outputTmp != OutputEm2)
        {
            OutputEm2 = outputTmp; emit signal_OutputChange();
        }
        outputTmp = ReadReg16(EXT3_BOARD_OUTPUT);
        if (outputTmp != OutputEm3)
        {
            OutputEm3 = outputTmp; emit signal_OutputChange();
        }
        outputTmp = ReadReg16(EXT4_BOARD_OUTPUT);
        if (outputTmp != OutputEm4)
        {
            OutputEm4 = outputTmp; emit signal_OutputChange();
        }
        // ////////////////////////////////////////////////////////////////////////////////////
		// 更新系统工作状态
        stateTmp = ReadReg16(SYSTEM_STATE);
        if (stateTmp != SystemState)
        {
			SystemState = stateTmp; emit signal_SysStateChange(SystemState);
        }
        stateTmp = ReadReg16(RUN_STATE);
        if (stateTmp != RunningState)
        {
			RunningState = stateTmp;
			if (RunningState==RUN_STATE_RUN)   sysstatechanged ++;
			emit signal_RunStateChange(RunningState);
        }
        stateTmp = ReadReg16(RUN_TYPE);
        if (stateTmp != RunningType)
        {
			RunningType = stateTmp; emit signal_RunTypeChange(RunningType);
        }
		if (sysstatechanged>3)
		{
			quint16 value = ((SystemState&3)<<3) | ((RunningState&1)<<2) | (RunningType&3);
			value <<= 8;
			value |= oldsysstate;
            srvPos[AXIS_IDX_PHOR] = svPhorPos, srvPos[AXIS_IDX_PVER] = svPverPos, srvPos[AXIS_IDX_TRV] = svTrvPos;
            srvPos[AXIS_IDX_RHOR] = svRhorPos, srvPos[AXIS_IDX_RVER] = svRverPos, srvPos[AXIS_IDX_EXT] = svExtPos;
            xSysLog::AddRecord(SYSLOG_TYPE_STATE_CHG, value, tr("" /*"系统状态改变"*/), QByteArray((char*)srvPos, sizeof(srvPos)));
			writeLog = true;
		}
		stateTmp = ReadReg16(HOME_STATE);
		if (stateTmp != HomeState)
		{
            HomeState = stateTmp;
            emit signal_HomeStateChange(HomeState);
		}
		// 更新系统报警状态
		srvPos[AXIS_IDX_PHOR] = svPhorPos, srvPos[AXIS_IDX_PVER] = svPverPos, srvPos[AXIS_IDX_TRV] = svTrvPos;
		srvPos[AXIS_IDX_RHOR] = svRhorPos, srvPos[AXIS_IDX_RVER] = svRverPos, srvPos[AXIS_IDX_EXT] = svExtPos;

        int almmbaddr[ALARM_MAX];
        almmbaddr[ALARM_IMM_SYS] = IMM_SYS_ALARM;
        almmbaddr[ALARM_PRO_ARM] = PRODUCTER_ALARM;
        almmbaddr[ALARM_IOEXT_1] = EXT1_BOARD_EXT_ALARM;
        almmbaddr[ALARM_IOEXT_2] = EXT2_BOARD_EXT_ALARM;
        almmbaddr[ALARM_IOEXT_3] = EXT3_BOARD_EXT_ALARM;
        almmbaddr[ALARM_IOEXT_4] = EXT4_BOARD_EXT_ALARM;
        almmbaddr[ALARM_SV_PHOR] = SERVOX_ALARM;
        almmbaddr[ALARM_SV_PVER] = SERVOY_ALARM;
        almmbaddr[ALARM_SV_TRAV] = SERVOZ_ALARM;
        almmbaddr[ALARM_SV_RVER] = SERVOA_ALARM;
        almmbaddr[ALARM_SV_RHOR] = SERVOB_ALARM;
        almmbaddr[ALARM_SV_EXTE] = SERVOC_ALARM;
        almmbaddr[ALARM_RUN_ARM] = RUNNER_DES_ASC_ALARM;
        almmbaddr[ALARM_POWER] = POWER_ALARM;
        for (i=0; i<ALARM_MAX; i++)
        {
            if((i == ALARM_SV_PHOR))
            {
                if (Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOX_ALARM_H) << 16)))
                {
                    ret = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOX_ALARM_H) << 16));
                    if ((ret & 0xffff) != ALMRES_NO_ALARM)
                    {
                        xSysLog::AddRecord(SYSLOG_TYPE_ALM, (quint16)ret, QString(""), QByteArray((char*)srvPos, sizeof(srvPos)),(quint16)(ret >> 16));
                        writeLog = true;
                    }
                }
            }
            else if((i == ALARM_SV_PVER))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOY_ALARM_H) << 16)))
                {
                    ret = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOY_ALARM_H) << 16));
                    if ((ret & 0xffff) != ALMRES_NO_ALARM)
                    {
                        xSysLog::AddRecord(SYSLOG_TYPE_ALM, (quint16)ret, QString(""), QByteArray((char*)srvPos, sizeof(srvPos)),(quint16)(ret >> 16));
                        writeLog = true;
                    }
                }
            }
            else if((i == ALARM_SV_TRAV))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOZ_ALARM_H) << 16)))
                {
                    ret = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOZ_ALARM_H) << 16));
                    if ((ret & 0xffff) != ALMRES_NO_ALARM)
                    {
                        xSysLog::AddRecord(SYSLOG_TYPE_ALM, (quint16)ret, QString(""), QByteArray((char*)srvPos, sizeof(srvPos)),(quint16)(ret >> 16));
                        writeLog = true;
                    }
                }
            }
            else if((i == ALARM_SV_RVER))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOA_ALARM_H) << 16)))
                {
                    ret = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOA_ALARM_H) << 16));
                    if ((ret & 0xffff) != ALMRES_NO_ALARM)
                    {
                        xSysLog::AddRecord(SYSLOG_TYPE_ALM, (quint16)ret, QString(""), QByteArray((char*)srvPos, sizeof(srvPos)),(quint16)(ret >> 16));
                        writeLog = true;
                    }
                }
            }
            else if((i == ALARM_SV_RHOR))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOB_ALARM_H) << 16)))
                {
                    ret = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOB_ALARM_H) << 16));
                    if ((ret & 0xffff) != ALMRES_NO_ALARM)
                    {
                        xSysLog::AddRecord(SYSLOG_TYPE_ALM, (quint16)ret, QString(""), QByteArray((char*)srvPos, sizeof(srvPos)),(quint16)(ret >> 16));
                        writeLog = true;
                    }
                }
            }
            else if((i == ALARM_SV_EXTE))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOC_ALARM_H) << 16)))
                {
                    ret = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOC_ALARM_H) << 16));
                    if ((ret & 0xffff) != ALMRES_NO_ALARM)
                    {
                        xSysLog::AddRecord(SYSLOG_TYPE_ALM, (quint16)ret, QString(""), QByteArray((char*)srvPos, sizeof(srvPos)),(quint16)(ret >> 16));
                        writeLog = true;
                    }
                }
            }
            else if((i == ALARM_POWER))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | DVS_BUS_DRIVER_ALARM_FLAG))//这个地址拿的一定是驱动器报警，直接把高位取标志位
                {
                    Alarms[i] = (((quint32)ReadReg16(almmbaddr[i])) | DVS_BUS_DRIVER_ALARM_FLAG);
                    if ((ret & 0xffff) != ALMRES_NO_ALARM)
                    {
//                        if((CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS))
//                        {
//                            srvPos[AXIS_IDX_type] = 0;
//                        }
                        xSysLog::AddRecord(SYSLOG_TYPE_ALM, (quint16)ret, QString(""), QByteArray((char*)srvPos, sizeof(srvPos)),(quint16)(ret >> 16));
                        writeLog = true;
                    }
                }
            }
            else
            {
            if (Alarms[i] != ReadReg16(almmbaddr[i]))
            {
                ret = ReadReg16(almmbaddr[i]);
                    if ((ret & 0xffff) != ALMRES_NO_ALARM)
                {
                        xSysLog::AddRecord(SYSLOG_TYPE_ALM, (quint16)ret, QString(""), QByteArray((char*)srvPos, sizeof(srvPos)),(quint16)(ret >> 16));
                    writeLog = true;
                }
            }
        }
        }
        if (writeLog)
            xSysLog::SaveChange();
        for (i=0; i<ALARM_MAX; i++)
        {           
            if((i == ALARM_SV_PHOR))
            {
                if (Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOX_ALARM_H) << 16)))
                {
                    Alarms[i] = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOX_ALARM_H) << 16));
                    emit signal_AlarmChange(i, Alarms[i]);
                }
            }
            else if((i == ALARM_SV_PVER))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOY_ALARM_H) << 16)))
                {
                    Alarms[i] = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOY_ALARM_H) << 16));
                    emit signal_AlarmChange(i, Alarms[i]);
                }
            }
            else if((i == ALARM_SV_TRAV))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOZ_ALARM_H) << 16)))
                {
                    Alarms[i] = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOZ_ALARM_H) << 16));
                    emit signal_AlarmChange(i, Alarms[i]);
                }
            }
            else if((i == ALARM_SV_RVER))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOA_ALARM_H) << 16)))
                {
                    Alarms[i] = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOA_ALARM_H) << 16));
                    emit signal_AlarmChange(i, Alarms[i]);
                }
            }
            else if((i == ALARM_SV_RHOR))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOB_ALARM_H) << 16)))
                {
                    Alarms[i] = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOB_ALARM_H) << 16));
                    emit signal_AlarmChange(i, Alarms[i]);
                }
            }
            else if((i == ALARM_SV_EXTE))
            {
                if(Alarms[i] != (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOC_ALARM_H) << 16)))
                {
                    Alarms[i] = (((quint32)ReadReg16(almmbaddr[i])) | ((quint32)ReadReg16(SERVOC_ALARM_H) << 16));
                    emit signal_AlarmChange(i, Alarms[i]);
                }
            }
            else if((i == ALARM_POWER))
            {
                if(Alarms[i] != ((quint32)ReadReg16(almmbaddr[i]) | DVS_BUS_DRIVER_ALARM_FLAG))
                {
                    Alarms[i] = ((quint32)ReadReg16(almmbaddr[i]) | DVS_BUS_DRIVER_ALARM_FLAG);
                    emit signal_AlarmChange(i, Alarms[i]);
                }
            }
            else
            {
                if (Alarms[i] != ReadReg16(almmbaddr[i]))
                {
                    Alarms[i] = ReadReg16(almmbaddr[i]);
                    emit signal_AlarmChange(i, Alarms[i]);
                }
            }
        }

        // 更新系统消息状态
        sysMessage = (((quint32)ReadReg16(MESSAGE)) | ((quint32)ReadReg16(PC_POINTER4)<<16));
        // 更新系统激活剩余时间
        if (activeRemainTime  != (((quint32)ReadReg16(SYS_SERVICE_TICK_LOW)) | ((quint32)ReadReg16(SYS_SERVICE_TICK_HIGH) << 16)))
        {
            activeRemainTime  = (((quint32)ReadReg16(SYS_SERVICE_TICK_LOW)) | ((quint32)ReadReg16(SYS_SERVICE_TICK_HIGH) << 16));
            emit signal_active_remainTime(activeRemainTime);
        }
		// 更新系统统计信息
        if (productSum != ReadReg32(TOTAL_MOLDS_LOW))
        {
			productSum = ReadReg32(TOTAL_MOLDS_LOW); emit signal_TotalMoldChange(productSum);
        }
        if (productPlan != ReadReg32(TOTAL_PLAN_LOW))
        {
			productPlan = ReadReg32(TOTAL_PLAN_LOW); emit signal_TotalPlanChange(productPlan);
        }
/*
        if (productPeriod != ReadReg16(PERIOD_TIME))
        {
            productPeriod = ReadReg16(PERIOD_TIME);  emit signal_PeriodTimeChange(productPeriod, 0);
        }
        if (inmoldTime != ReadReg16(INMOLD_TIME))
        {
            inmoldTime = ReadReg16(INMOLD_TIME);     emit signal_InmoldTimeChange(inmoldTime, 0);
        }
*/
        if (productPeriod != (((quint32)ReadReg16(PERIOD_TIME)) | ((quint32)ReadReg16(PERIOD_TIME1_H) << 16)))
        {
            productPeriod = (((quint32)ReadReg16(PERIOD_TIME)) | ((quint32)ReadReg16(PERIOD_TIME1_H) << 16));
            emit signal_PeriodTimeChange(productPeriod, 0);
        }
        if (inmoldTime != (((quint32)ReadReg16(INMOLD_TIME)) | ((quint32)ReadReg16(INMOLD_TIME1_H) << 16)))
        {
            inmoldTime = (((quint32)ReadReg16(INMOLD_TIME)) | ((quint32)ReadReg16(INMOLD_TIME1_H) << 16));
            emit signal_InmoldTimeChange(inmoldTime, 0);
        }
        if (programPc != ReadReg16(PC_POINTER))
        {
            programPc = ReadReg16(PC_POINTER); emit signal_PC_Pointer(programPc, 0);
        }
        if (GetProcUse(1))
        {
            if (productPeriod2 != (((quint32)ReadReg16(PERIOD_TIME2)) | ((quint32)ReadReg16(PERIOD_TIME2_H) << 16)))
            {
                productPeriod2 = (((quint32)ReadReg16(PERIOD_TIME2)) | ((quint32)ReadReg16(PERIOD_TIME2_H) << 16));
                emit signal_PeriodTimeChange(productPeriod2, 1);
            }
            if (inmoldTime2 != (((quint32)ReadReg16(INMOLD_TIME2)) | ((quint32)ReadReg16(INMOLD_TIME2_H) << 16)))
            {
                inmoldTime2 = (((quint32)ReadReg16(INMOLD_TIME2)) | ((quint32)ReadReg16(INMOLD_TIME2_H) << 16));
                emit signal_InmoldTimeChange(inmoldTime2, 1);
            }
            if (programPc2 != ReadReg16(PC_POINTER2))
            {
                programPc2 = ReadReg16(PC_POINTER2);
                emit signal_PC_Pointer(programPc2, 1);
            }
        }
        if (GetProcUse(2))
        {
            if (productPeriod3 != (((quint32)ReadReg16(PERIOD_TIME3)) | ((quint32)ReadReg16(PERIOD_TIME3_H) << 16)))
            {
                productPeriod3 = (((quint32)ReadReg16(PERIOD_TIME3)) | ((quint32)ReadReg16(PERIOD_TIME3_H) << 16));
                emit signal_PeriodTimeChange(productPeriod3, 2);
            }
            if (inmoldTime3 != (((quint32)ReadReg16(INMOLD_TIME3)) | ((quint32)ReadReg16(INMOLD_TIME3_H) << 16)))
            {
                inmoldTime3 = (((quint32)ReadReg16(INMOLD_TIME3)) | ((quint32)ReadReg16(INMOLD_TIME3_H) << 16));
                emit signal_InmoldTimeChange(inmoldTime3, 2);
            }
            if (programPc3 != ReadReg16(PC_POINTER3))
            {
                programPc3 = ReadReg16(PC_POINTER3); emit signal_PC_Pointer(programPc3, 2);
            }
        }
        //pyq 轮询跳转 实时扭矩 实时转速
        if((actualTrqX != ReadReg16(ACTUAL_TRQ_X))||
           (actualTrqY != ReadReg16(ACTUAL_TRQ_Y))||
           (actualTrqZ != ReadReg16(ACTUAL_TRQ_Z))||
           (actualTrqA != ReadReg16(ACTUAL_TRQ_A))||
           (actualTrqB != ReadReg16(ACTUAL_TRQ_B))||
           (actualTrqC != ReadReg16(ACTUAL_TRQ_C))||
           (actualSpeedX != ReadReg16(ACTUAL_SPEED_X))||
           (actualSpeedY != ReadReg16(ACTUAL_SPEED_Y))||
           (actualSpeedZ != ReadReg16(ACTUAL_SPEED_Z))||
           (actualSpeedA != ReadReg16(ACTUAL_SPEED_A))||
           (actualSpeedB != ReadReg16(ACTUAL_SPEED_B))||
           (actualSpeedC != ReadReg16(ACTUAL_SPEED_C)))
        {
            actualTrqX = ReadReg16(ACTUAL_TRQ_X);
            actualTrqY = ReadReg16(ACTUAL_TRQ_Y);
            actualTrqZ = ReadReg16(ACTUAL_TRQ_Z);
            actualTrqA = ReadReg16(ACTUAL_TRQ_A);
            actualTrqB = ReadReg16(ACTUAL_TRQ_B);
            actualTrqC = ReadReg16(ACTUAL_TRQ_C);
            actualSpeedX = ReadReg16(ACTUAL_SPEED_X);
            actualSpeedY = ReadReg16(ACTUAL_SPEED_Y);
            actualSpeedZ = ReadReg16(ACTUAL_SPEED_Z);
            actualSpeedA = ReadReg16(ACTUAL_SPEED_A);
            actualSpeedB = ReadReg16(ACTUAL_SPEED_B);
            actualSpeedC = ReadReg16(ACTUAL_SPEED_C);
            emit signal_Actual_Servo(actualTrqX, actualTrqY,actualTrqZ,actualTrqA,actualTrqB,actualTrqC,
                                     actualSpeedX,actualSpeedY,actualSpeedZ,actualSpeedA,actualSpeedB,actualSpeedC);
        }
                //pyq end
        //控制按钮功能，主板X11为原点按钮；X10为停止按钮；X9为运行按钮
		if (keypressed != ReadReg16(KEY_PRESSED))
		{
			uint16_t tmp = keypressed;
			keypressed = ReadReg16(KEY_PRESSED);
			tmp ^= keypressed;
			if (GetExtraControl())
            {
                if (PROTOCOL_KEY_STOP&tmp)
                {
                    if (keypressed&PROTOCOL_KEY_STOP)
                    {
                        //QKeyEvent* KeyRelease = new QKeyEvent(QEvent::KeyRelease, KEY_STOP, Qt::NoModifier);
                        //qApp->postEvent(qApp, KeyRelease);
#if defined(Q_WS_QWS)
						qwsServer->sendKeyEvent(0, KEY_SCAN_STOP, Qt::KeypadModifier, true, false);
#endif
                    }
                    else
                    {
#if defined(Q_WS_QWS)
						qwsServer->sendKeyEvent(0, KEY_SCAN_STOP, Qt::KeypadModifier, false, false);
#endif
                    }
                }
                else
                if (PROTOCOL_KEY_HOME&tmp)
                {
                    if (keypressed&PROTOCOL_KEY_HOME)
                    {
#if defined(Q_WS_QWS)
						if (GetFirstAlarm(alm)>=0)
							CommandClearAlarm();
						else
						qwsServer->sendKeyEvent(0, KEY_SCAN_HOME, Qt::KeypadModifier, true, false);
#endif
                    }
                    else
                    {
#if defined(Q_WS_QWS)
						qwsServer->sendKeyEvent(0, KEY_SCAN_HOME, Qt::KeypadModifier, false, false);
#endif
                    }
                }
                else
                if (PROTOCOL_KEY_RUN&tmp)
                {
                    if (keypressed&PROTOCOL_KEY_RUN)
                    {
#if defined(Q_WS_QWS)
						qwsServer->sendKeyEvent(0, KEY_SCAN_RUN, Qt::KeypadModifier, true, false);
#endif
                    }
                    else
                    {
#if defined(Q_WS_QWS)
						qwsServer->sendKeyEvent(0, KEY_SCAN_RUN, Qt::KeypadModifier, false, false);
#endif
                    }
				}
			}
			if (PROTOCOL_KEY_DOOR_RESET&tmp)
			{
				if (keypressed&PROTOCOL_KEY_DOOR_RESET)
				{
#if defined(Q_WS_QWS)
					qwsServer->sendKeyEvent(0, VKEY_SCAN_DOOR_RESET, Qt::KeypadModifier, true, false);
#endif
				}
				else
				{
#if defined(Q_WS_QWS)
					qwsServer->sendKeyEvent(0, VKEY_SCAN_DOOR_RESET, Qt::KeypadModifier, false, false);
#endif
				}
			}
            //询问
            if (PROTOCOL_KEY_DOOR_QUERY&tmp)
            {
                if (keypressed&PROTOCOL_KEY_DOOR_QUERY)
                {
#if defined(Q_WS_QWS)
                    qwsServer->sendKeyEvent(0, VKEY_SCAN_DOOR_QUERY, Qt::KeypadModifier, true, false);
#endif
                }
                else
                {
#if defined(Q_WS_QWS)
                    qwsServer->sendKeyEvent(0, VKEY_SCAN_DOOR_QUERY, Qt::KeypadModifier, false, false);
#endif
                }
            }
		}
		// 更新扩展模块连接状态
		ExtBoardState = ReadReg16(EXT_BOARD_STATE);
		// 更新安全开关状态
		xSafeSw->ReadSwitch();
		// Update the select switch state
		xLed->ReadSwitch();
		// 调用周期函数
        emit signal_PeriodPoll(sysMessage);
    }
}
// 得到第一个报警位置
// 返回值小于0表示没有报警
int8_t CMBProtocol::GetFirstAlarm(uint32_t &alm)
{
    uint8_t i;
    for (i = 0; i < ALARM_MAX; i ++)
    {
        if ((Alarms[i] & 0xffff) != ALMRES_NO_ALARM)
        {
            alm = Alarms[i];
            return i;
        }
    }
    return -1;
}
// 得到指定位置的报警
uint32_t CMBProtocol::GetAlmByPos(uint8_t pos)
{
    if (pos >= ALARM_MAX)
        return ALMRES_NO_ALARM;
    else
        return Alarms[pos];
}
// 清除系统消息提示
int8_t CMBProtocol::ClrMessage(void)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[MESSAGE] = 0;
    return SendMsg(MESSAGE, MESSAGE, FALSE);
#else
    return SENDMSG_RET_ACK;
#endif
}
// 返回当前伺服各轴位置
void CMBProtocol::GetServoPos(uint32_t &pHor, uint32_t &pVer, uint32_t &trv, uint32_t &rHor, uint32_t &rVer, uint32_t &ext)
{
	pHor = svPhorPos, pVer = svPverPos, trv = svTrvPos, rHor = svRhorPos, rVer = svRverPos, ext = svExtPos;
}
// ************************************************
// 手动操作接口
// ************************************************
int8_t CMBProtocol::ClearProcCode(int8_t procid)
{
    int8_t ret = SENDMSG_RET_ACK;
    if (procid<MAX_PROCESS)
    {
        m_mbaddrspace[NEW_CODE_BEG + MAX_CODES*procid] = CODE_END;
        m_mbaddrspace[NEW_CODE_BEG + MAX_CODES*procid+1] = CODE_END;
        m_mbaddrspace[NEW_CODE_BEG + MAX_CODES*procid+2] = CODE_END;
        m_mbaddrspace[NEW_PARA_BEG + MAX_CODES*procid] = 0;
        m_mbaddrspace[NEW_PARA_BEG + MAX_CODES*procid+1] = 0;
        m_mbaddrspace[NEW_PARA_BEG + MAX_CODES*procid+2] = 0;
        ret = SendMsg(NEW_CODE_BEG + MAX_CODES*procid, NEW_CODE_BEG + MAX_CODES*procid+1, FALSE);
        if (ret != SENDMSG_RET_ACK)
            goto HOM_CTRL_RETURN;
        ret = SendMsg(NEW_PARA_BEG + MAX_CODES*procid, NEW_PARA_BEG + MAX_CODES*procid+1, FALSE);
        if (ret != SENDMSG_RET_ACK)
            goto HOM_CTRL_RETURN;
    }
HOM_CTRL_RETURN:
    return ret;
}
// 原点复归操作
int8_t CMBProtocol::ManualHome(quint8 spd)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    // 准备代码和参数
    quint16 codeAdr = NEW_CODE_BEG;
    quint16 paraAdr = NEW_PARA_BEG;
    quint16 actIdx = HOME_DEF_00;
    quint16 i;
    ClearProcCode(1);
    ClearProcCode(2);
    ClearProcCode(3);
    for (i = 0; i < HOME_DEF_MAX; i ++)
    {
        if (m_mbaddrspace[actIdx] == CUSTOMER_FUN_END)
        {
            m_mbaddrspace[codeAdr] = CODE_END;
            m_mbaddrspace[paraAdr] = 0;
            m_mbaddrspace2[paraAdr] = 0;
            break;
        }
        else
        {
			m_mbaddrspace[codeAdr] = CODE_CUSTOMER;
			m_mbaddrspace[paraAdr] = ((m_mbaddrspace[actIdx] << 8) | spd);
			m_mbaddrspace2[paraAdr] = 0;
		}
        codeAdr ++;
        paraAdr ++;
        actIdx ++;
    }
    if (i >= HOME_DEF_MAX)
    {
        m_mbaddrspace[NEW_CODE_BEG + HOME_DEF_MAX - 1] = CODE_END;
        m_mbaddrspace[NEW_PARA_BEG + HOME_DEF_MAX - 1] = 0;
        m_mbaddrspace2[NEW_PARA_BEG + HOME_DEF_MAX - 1] = 0;
    }
    ret = SendMsg(NEW_CODE_BEG, NEW_CODE_BEG + HOME_DEF_MAX - 1, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto HOM_CTRL_RETURN;
    ret = SendMsg(NEW_PARA_BEG, NEW_PARA_BEG + HOME_DEF_MAX - 1, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto HOM_CTRL_RETURN;
    ret = SendMsg2(NEW_PARA_BEG, NEW_PARA_BEG + HOME_DEF_MAX - 1, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto HOM_CTRL_RETURN;
    // 刷新代码和参数
    m_mbaddrspace[COMMAND] = COMMAND_UPDATE_PRG;
    m_mbaddrspace[COMMAND_PARA1] = CMD_UPDATE_PARA1;
    ret = SendMsg(COMMAND_PARA1, COMMAND, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto HOM_CTRL_RETURN;
    // 设置运行
    m_mbaddrspace[RUN_STATE] = RUN_STATE_RUN;
    m_mbaddrspace[RUN_TYPE] = RUN_TYPE_SINGLE;
    ret = SendMsg(RUN_STATE, RUN_TYPE, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto HOM_CTRL_RETURN;
    // 写入系统日志

    xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_SRVHOME);
    xSysLog::SaveChange();
HOM_CTRL_RETURN:
#endif
	return ret;
}
// 正臂手动操作
int8_t CMBProtocol::ManualPro(uint8_t act)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    // 组织代码和参数
    ClearProcCode(1);
    ClearProcCode(2);
    ClearProcCode(3);
    m_mbaddrspace[NEW_CODE_BEG] = CODE_PROARM;
    m_mbaddrspace[NEW_PARA_BEG] = act;
    m_mbaddrspace2[NEW_PARA_BEG] = 0;
    m_mbaddrspace[NEW_CODE_BEG+1] = CODE_END;
    m_mbaddrspace[NEW_PARA_BEG+1] = 0;
    m_mbaddrspace2[NEW_PARA_BEG+1] = 0;
    ret = SendMsg(NEW_CODE_BEG, NEW_CODE_BEG+1, FALSE);
    if (ret == SENDMSG_RET_ACK)
    {
        ret = SendMsg2(NEW_CODE_BEG, NEW_CODE_BEG+1, FALSE);
    }
    if (ret != SENDMSG_RET_ACK)
        goto PARM_CTRL_RETURN;
    ret = SendMsg(NEW_PARA_BEG, NEW_PARA_BEG+1, FALSE);
    if (ret == SENDMSG_RET_ACK)
    {
        ret = SendMsg2(NEW_PARA_BEG, NEW_PARA_BEG+1, FALSE);
    }
    if (ret != SENDMSG_RET_ACK)
        goto PARM_CTRL_RETURN;
    // 刷新代码和参数
    m_mbaddrspace[COMMAND_PARA1] = CMD_UPDATE_PARA1;
    m_mbaddrspace[COMMAND] = COMMAND_UPDATE_PRG;
    ret = SendMsg(COMMAND_PARA1, COMMAND, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto PARM_CTRL_RETURN;
    // 设置运行
    m_mbaddrspace[RUN_STATE] = RUN_STATE_RUN;
    m_mbaddrspace[RUN_TYPE] = RUN_TYPE_SINGLE;
    ret = SendMsg(RUN_STATE, RUN_TYPE, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto PARM_CTRL_RETURN;
	// 写入系统日志
	if (act == PRO_ACT_VERTIACL)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_ROTVER);
	else
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_ROTHOR);
	xSysLog::SaveChange();	
PARM_CTRL_RETURN:
#endif
	return ret;
}
// 注塑机手动操作
int8_t CMBProtocol::ManualIMM(uint8_t act)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    // 组织代码和参数
    ClearProcCode(1);
    ClearProcCode(2);
    ClearProcCode(3);
    m_mbaddrspace[NEW_CODE_BEG] = CODE_IMM;
    m_mbaddrspace[NEW_PARA_BEG] = act;
    m_mbaddrspace2[NEW_PARA_BEG] = 0;
    m_mbaddrspace[NEW_CODE_BEG+1] = CODE_END;
    m_mbaddrspace[NEW_PARA_BEG+1] = 0;
    m_mbaddrspace2[NEW_PARA_BEG+1] = 0;
    ret = SendMsg(NEW_CODE_BEG, NEW_CODE_BEG+1, FALSE);
    if (ret == SENDMSG_RET_ACK)
        ret = SendMsg2(NEW_CODE_BEG, NEW_CODE_BEG+1, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto IMM_CTRL_RETURN;
    ret = SendMsg(NEW_PARA_BEG, NEW_PARA_BEG+1, FALSE);
    if (ret == SENDMSG_RET_ACK)
        ret = SendMsg2(NEW_PARA_BEG, NEW_PARA_BEG+1, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto IMM_CTRL_RETURN;
    // 刷新代码和参数
    m_mbaddrspace[COMMAND_PARA1] = CMD_UPDATE_PARA1;
    m_mbaddrspace[COMMAND] = COMMAND_UPDATE_PRG;
    ret = SendMsg(COMMAND_PARA1, COMMAND, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto IMM_CTRL_RETURN;
    // 设置运行
    m_mbaddrspace[RUN_STATE] = RUN_STATE_RUN;
    m_mbaddrspace[RUN_TYPE] = RUN_TYPE_SINGLE;
    ret = SendMsg(RUN_STATE, RUN_TYPE, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto IMM_CTRL_RETURN;
    // 写入系统日志
	if (act == IMMOUT_EMO)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMEMO);
	else if (act == IMMOUT_EMC)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMEMC);
	else if (act == IMMOUT_EEF)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMEEF);
	else if (act == IMMOUT_EEB)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMEEB);
	else if (act == IMMOUT_C1P1)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMC1P1);
	else if (act == IMMOUT_C1P2)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMC1P2);
	else if (act == IMMOUT_C2P1)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMC2P1);
	else if (act == IMMOUT_C2P2)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMC2P2);
	else if (act == IMMOUT_EEF_OFF)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMEEF_OFF);
	else if (act == IMMOUT_EEB_OFF)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMEEB_OFF);
	else if (act == IMMOUT_C1P1_OFF)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMC1P1_OFF);
	else if (act == IMMOUT_C1P2_OFF)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMC1P2_OFF);
	else if (act == IMMOUT_C2P1_OFF)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMC2P1_OFF);
	else if (act == IMMOUT_C2P2_OFF)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_IMMC2P2_OFF);
	xSysLog::SaveChange();
IMM_CTRL_RETURN:
#endif
	return ret;
}
// 副臂手动操作
int8_t CMBProtocol::ManualRun(uint8_t act)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    // 组织代码和参数
    ClearProcCode(1);
    ClearProcCode(2);
    ClearProcCode(3);
    m_mbaddrspace[NEW_CODE_BEG] = CODE_RUNARM;
    m_mbaddrspace[NEW_PARA_BEG] = act;
    m_mbaddrspace2[NEW_PARA_BEG] = 0;
    m_mbaddrspace[NEW_CODE_BEG+1] = CODE_END;
    m_mbaddrspace[NEW_PARA_BEG+1] = 0;
    m_mbaddrspace2[NEW_PARA_BEG+1] = 0;
    ret = SendMsg(NEW_CODE_BEG, (NEW_CODE_BEG+1), FALSE);
    if (ret ==SENDMSG_RET_ACK)
        ret = SendMsg2(NEW_CODE_BEG, (NEW_CODE_BEG+1), FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto RARM_CTRL_RETURN;
    ret = SendMsg(NEW_PARA_BEG, (NEW_PARA_BEG+1), FALSE);
    if (ret ==SENDMSG_RET_ACK)
        ret = SendMsg2(NEW_PARA_BEG, (NEW_PARA_BEG+1), FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto RARM_CTRL_RETURN;
    // 刷新代码和参数
    m_mbaddrspace[COMMAND_PARA1] = CMD_UPDATE_PARA1;
    m_mbaddrspace[COMMAND] = COMMAND_UPDATE_PRG;
    ret = SendMsg(COMMAND_PARA1, COMMAND, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto RARM_CTRL_RETURN;
    // 设置运行
    m_mbaddrspace[RUN_STATE] = RUN_STATE_RUN;
    m_mbaddrspace[RUN_TYPE] = RUN_TYPE_SINGLE;
    ret = SendMsg(RUN_STATE, RUN_TYPE, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto RARM_CTRL_RETURN;
	// 写入系统日志
	if (act == RUN_ACT_ASCENT)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_RASC);
	else if (act == RUN_ACT_DESCENT)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_RDES);
	else if (act == RUN_ACT_ADVANCE)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_RADV);
	else if (act == RUN_ACT_RETURN)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_RRET);
	xSysLog::SaveChange();
RARM_CTRL_RETURN:
#endif
	return ret;
}

// 扩展输出手动操作
int8_t CMBProtocol::ManualExt(uint8_t on_off, uint16_t out)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    // 组织代码和参数
    ClearProcCode(1);
    ClearProcCode(2);
    ClearProcCode(3);
    m_mbaddrspace[NEW_CODE_BEG] = CODE_EXT_OUT;
    m_mbaddrspace[NEW_PARA_BEG] = ((on_off << 12) | (out & 0xFFF));
    m_mbaddrspace[NEW_CODE_BEG+1] = CODE_CONST;
    m_mbaddrspace[NEW_PARA_BEG+1] = 0;
    m_mbaddrspace[NEW_CODE_BEG+2] = CODE_END;
    m_mbaddrspace[NEW_PARA_BEG+2] = 0;
    ret = SendMsg(NEW_CODE_BEG, (NEW_CODE_BEG+2), FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto EXT_CTRL_RETURN;
    ret = SendMsg(NEW_PARA_BEG, (NEW_PARA_BEG+2), FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto EXT_CTRL_RETURN;
    // 刷新代码和参数
    m_mbaddrspace[COMMAND_PARA1] = CMD_UPDATE_PARA1;
    m_mbaddrspace[COMMAND] = COMMAND_UPDATE_PRG;
    ret = SendMsg(COMMAND_PARA1, COMMAND, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto EXT_CTRL_RETURN;
    // 设置运行
    m_mbaddrspace[RUN_STATE] = RUN_STATE_RUN;
    m_mbaddrspace[RUN_TYPE] = RUN_TYPE_SINGLE;
    ret = SendMsg(RUN_STATE, RUN_TYPE, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto EXT_CTRL_RETURN;
	// 写入系统日志
	if (on_off)
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_EOUTON, xStringResource::GetVarName(out));
	else
		xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_EOUTOFF, xStringResource::GetVarName(out));
	xSysLog::SaveChange();
EXT_CTRL_RETURN:
#endif
	return ret;
}

int8_t CMBProtocol::ManualVacuum(uint8_t on_off, uint16_t outbmp)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    if (GetFunctions(SUB_VACUUM))
    {
        // 组织代码和参数
        ClearProcCode(1);
        ClearProcCode(2);
        ClearProcCode(3);
        m_mbaddrspace[NEW_CODE_BEG] = CODE_VACUUM;
        m_mbaddrspace[NEW_PARA_BEG] = outbmp;
        m_mbaddrspace2[NEW_PARA_BEG] = 0;
        m_mbaddrspace[NEW_CODE_BEG+1] = CODE_CONST;
        m_mbaddrspace[NEW_PARA_BEG+1] = 0;
        m_mbaddrspace2[NEW_PARA_BEG+1] = on_off;
        m_mbaddrspace[NEW_CODE_BEG+2] = CODE_CONST;
        m_mbaddrspace[NEW_PARA_BEG+2] = 0;
        m_mbaddrspace2[NEW_PARA_BEG+2] = 0;
        m_mbaddrspace[NEW_CODE_BEG+3] = CODE_END;
        m_mbaddrspace[NEW_PARA_BEG+3] = 0;
        m_mbaddrspace2[NEW_PARA_BEG+3] = 0;
        ret = SendMsg(NEW_CODE_BEG, (NEW_CODE_BEG+3), FALSE);
        if (ret != SENDMSG_RET_ACK)
            goto EXT_CTRL_RETURN;
        ret = SendMsg(NEW_PARA_BEG, (NEW_PARA_BEG+3), FALSE);
        if (ret != SENDMSG_RET_ACK)
            goto EXT_CTRL_RETURN;
        ret = SendMsg2(NEW_PARA_BEG, (NEW_PARA_BEG+3), FALSE);
        if (ret != SENDMSG_RET_ACK)
            goto EXT_CTRL_RETURN;
        // 刷新代码和参数
        m_mbaddrspace[COMMAND_PARA1] = CMD_UPDATE_PARA1;
        m_mbaddrspace[COMMAND] = COMMAND_UPDATE_PRG;
        ret = SendMsg(COMMAND_PARA1, COMMAND, FALSE);
        if (ret != SENDMSG_RET_ACK)
            goto EXT_CTRL_RETURN;
        // 设置运行
        m_mbaddrspace[RUN_STATE] = RUN_STATE_RUN;
        m_mbaddrspace[RUN_TYPE] = RUN_TYPE_SINGLE;
        ret = SendMsg(RUN_STATE, RUN_TYPE, FALSE);
        if (ret != SENDMSG_RET_ACK)
            goto EXT_CTRL_RETURN;
        // 写入系统日志
        if (on_off)
            xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_VACUUMON, QString::number((uint)outbmp, 16));
        else
            xSysLog::AddRecord(SYSLOG_TYPE_NOR, LOG_MANUL_VACUUMOFF, QString::number((uint)outbmp, 16));
        xSysLog::SaveChange();
    }
EXT_CTRL_RETURN:

#endif
    return ret;
}

// 伺服手动操作
int8_t CMBProtocol::ManualPos(uint8_t speed, uint8_t axesbmp, uint32_t pos, uint8_t mode, bool rel)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    // 得到全局速度
    quint8 relSpd = GetSrvSpeed();
    //组织代码和参数
    ClearProcCode(1);
    ClearProcCode(2);
    ClearProcCode(3);
    memset(m_mbaddrspace+NEW_PARA_BEG, 0, sizeof(quint16)*(200));
    memset(m_mbaddrspace2+NEW_PARA_BEG, 0, sizeof(quint16)*(200));
    m_mbaddrspace[NEW_CODE_BEG] = CODE_POS;
    m_mbaddrspace[NEW_PARA_BEG] = ((mode << 6) | (axesbmp & 0x3F));
    m_mbaddrspace[NEW_PARA_BEG] <<= 1;
    if (rel == true)
    {
        m_mbaddrspace[NEW_PARA_BEG] |= 1;
    }
    m_mbaddrspace[NEW_PARA_BEG] <<= 7;
    m_mbaddrspace[NEW_PARA_BEG] |= (speed*relSpd/100) & 0x7F;
    m_mbaddrspace2[NEW_PARA_BEG] = 0;
    m_mbaddrspace[NEW_CODE_BEG+1] = CODE_CONST;
    m_mbaddrspace[NEW_PARA_BEG+1] = pos;
    m_mbaddrspace2[NEW_PARA_BEG+1] = pos >> 16;
    m_mbaddrspace[NEW_CODE_BEG+2] = CODE_END;
    m_mbaddrspace[NEW_PARA_BEG+2] = 0;
    ret = SendMsg(NEW_CODE_BEG, NEW_CODE_BEG+2, FALSE);
    if (ret == SENDMSG_RET_ACK)
        ret = SendMsg(NEW_PARA_BEG, NEW_PARA_BEG+2, FALSE);
    if (ret == SENDMSG_RET_ACK)
        ret = SendMsg2(NEW_PARA_BEG, NEW_PARA_BEG+2, FALSE);
    // 刷新代码和参数
    m_mbaddrspace[COMMAND_PARA1] = CMD_UPDATE_PARA1;
    m_mbaddrspace[COMMAND] = COMMAND_UPDATE_PRG;
    ret = SendMsg(COMMAND_PARA1, COMMAND, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto SRV_CTRL_RETURN;
    // 设置运行
    m_mbaddrspace[RUN_STATE] = RUN_STATE_RUN;
    m_mbaddrspace[RUN_TYPE] = RUN_TYPE_SINGLE;
    ret = SendMsg(RUN_STATE, RUN_TYPE, FALSE);
    if (ret != SENDMSG_RET_ACK)
        goto SRV_CTRL_RETURN;
SRV_CTRL_RETURN:
#endif
    return ret;
}

int8_t CMBProtocol::SetRun()
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    // 设置运行
    m_mbaddrspace[RUN_STATE] = RUN_STATE_RUN;
    m_mbaddrspace[RUN_TYPE] = RUN_TYPE_SINGLE;
    ret = SendMsg(RUN_STATE, RUN_TYPE, FALSE);
#endif
    return ret;
}
// ************************************************
// 命令接口
// ************************************************
// 数据复位命令
int8_t CMBProtocol::CommandReset(uint16_t resetflag)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND_PARA1] = resetflag;
    m_mbaddrspace[COMMAND] = COMMAND_RESET_PARA;
    return SendMsg(COMMAND_PARA1, COMMAND, FALSE);
#else
	return SENDMSG_RET_ACK;
#endif
}
int8_t CMBProtocol::CommandEncoder(uint8_t speed, uint8_t axesbmp, qint16 scale, bool cw, uint8_t mode)
{
#if PENDANT_PROTOCOL
    if (!cw)
    {
        scale *= -1;
    }
    m_mbaddrspace[COMMAND_PARA3] = mode;
    m_mbaddrspace[COMMAND_PARA2] = scale;
    m_mbaddrspace[COMMAND_PARA1] = axesbmp|(speed<<8);
    m_mbaddrspace[COMMAND] = COMMAND_ENCODER;
    return SendMsg(COMMAND_PARA3, COMMAND, FALSE);
#else
    return SENDMSG_RET_ACK;
#endif
}
// 报警复位按钮
int8_t CMBProtocol::CommandClearAlarm(void)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND] = COMMAND_CLEAR_ALARM;
    return SendMsg(COMMAND, COMMAND, FALSE);
#else
    return SENDMSG_RET_ACK;
#endif
}
// 编码器归原按钮
int8_t CMBProtocol::CommandEncoderHome(uint16_t encoder, uint8_t mode)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND_PARA1] = encoder;
    m_mbaddrspace[COMMAND_PARA2] = mode;
    m_mbaddrspace[COMMAND] = COMMAND_ABS_HOME;
    return SendMsg(COMMAND_PARA2, COMMAND, FALSE);
#else
    return SENDMSG_RET_ACK;
#endif
}
// 写数据命令
int8_t CMBProtocol::CommandWrite(uint16_t writeflag)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND_PARA1] = writeflag;
    m_mbaddrspace[COMMAND] = COMMAND_WRITE_PARA;
    return SendMsg(COMMAND_PARA1, COMMAND, FALSE);
#else
	return SENDMSG_RET_ACK;
#endif
}
// 更新数据命令
int8_t CMBProtocol::CommandUpdate(uint16_t updateflag)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND_PARA1] = updateflag;
    m_mbaddrspace[COMMAND] = COMMAND_UPDATE_PRG;
    return SendMsg(COMMAND_PARA1, COMMAND, FALSE);
#else
	return SENDMSG_RET_ACK;
#endif
}
// 停止伺服命令
int8_t CMBProtocol::CommandStop(void)
{
#if PENDANT_PROTOCOL
//    m_mbaddrspace[COMMAND] = COMMAND_STOP_SERVO;
    return SendMsg(COMMAND, COMMAND, FALSE);
#else
	return SENDMSG_RET_ACK;
#endif
}
int8_t CMBProtocol::CommandAdjustMotor(uint8_t motoridx, uint8_t ccw)
{
#if PENDANT_PROTOCOL
	uint16_t tmp = motoridx;
	if (ccw) tmp |= 0x8000;
	m_mbaddrspace[COMMAND_PARA1] = tmp;
	m_mbaddrspace[COMMAND] = COMMAND_ADJUST_MOTOR;
	return SendMsg(COMMAND_PARA1, COMMAND, FALSE);
#else
	return SENDMSG_RET_ACK;
#endif
}
// 主控模块进入ISP模式命令
int8_t CMBProtocol::CommandEnterIsp(void)
{
#if PENDANT_PROTOCOL
	m_mbaddrspace[COMMAND] = COMMAND_ENTRY_ISP;
    return SendMsg(COMMAND, COMMAND, FALSE, 0);
#else
	return SENDMSG_RET_ACK;
#endif
}
// 安全门复位,1复位，0不复位
int8_t CMBProtocol::CommandDoorReset(bool reset)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND_PARA1] = reset;
    m_mbaddrspace[COMMAND] = COMMAND_DOOR_RESET;
    return SendMsg(COMMAND_PARA1, COMMAND, FALSE);
#else
    return SENDMSG_RET_ACK;
#endif
}
int8_t CMBProtocol::CommandDoorQuery()
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND_PARA1] = 0;
    m_mbaddrspace[COMMAND] = COMMAND_DOOR_QUERY;
    return SendMsg(COMMAND_PARA1, COMMAND, FALSE);
#else
    return SENDMSG_RET_ACK;
#endif
}
int8_t CMBProtocol::CommandVisionTest(quint16 idx)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND_PARA1] = idx;
    m_mbaddrspace[COMMAND] = COMMAND_VISION;
    return SendMsg(COMMAND_PARA1, COMMAND, FALSE);
#else
    return SENDMSG_RET_ACK;
#endif
}
int8_t CMBProtocol::CommandIMMOut(uint8_t on)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND_PARA1] = on;
    m_mbaddrspace[COMMAND] = COMMAND_ALLIMMOUT;
    return SendMsg(COMMAND_PARA1, COMMAND, FALSE);
#else
    return SENDMSG_RET_ACK;
#endif
}

int8_t CMBProtocol::CommandFUNUI(quint32 idx)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND_PARA1] = idx;
    m_mbaddrspace[COMMAND_PARA2] = idx>>16;
    m_mbaddrspace[COMMAND] = COMMAND_FUN_UI;
    return SendMsg(COMMAND_PARA2, COMMAND, FALSE);
#else
    return SENDMSG_RET_ACK;
#endif
}

int8_t CMBProtocol::CommandDVS_CanRtu(uint16_t adr, uint16_t data, uint16_t cmd, uint16_t servoID)
{
#if PENDANT_PROTOCOL
    m_mbaddrspace[COMMAND_PARA4] = servoID;//轴地址
    m_mbaddrspace[COMMAND_PARA3] = cmd;//命令
    m_mbaddrspace[COMMAND_PARA2] = data;//内容
    m_mbaddrspace[COMMAND_PARA1] = adr;//地址
    m_mbaddrspace[COMMAND] = COMMAND_SDO_RTU;
    return SendMsg(COMMAND_PARA4, COMMAND, FALSE);
#else
    return SENDMSG_RET_ACK;
#endif
}

void CMBProtocol::ChangeSafePos_Inmold_Outmold(bool home_inmold)
{
    uint16_t temp1, temp2, temp3, temp4;
    int8_t ret = SENDMSG_RET_ACK;
    {
        temp1 = m_mbaddrspace[SERVO_MIN_SAFE_POS_OUTMOLD_Z];
        temp2 = m_mbaddrspace[SERVO_MAX_SAFE_POS_OUTMOLD_Z];
        temp3 = m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_Z];
        temp4 = m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_Z];
        m_mbaddrspace[SERVO_MIN_SAFE_POS_OUTMOLD_Z] = temp3;
        m_mbaddrspace[SERVO_MAX_SAFE_POS_OUTMOLD_Z] = temp4;
        m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_Z] = temp1;
        m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_Z] = temp2;

        temp1 = m_mbaddrspace2[SERVO_MIN_SAFE_POS_OUTMOLD_Z];
        temp2 = m_mbaddrspace2[SERVO_MAX_SAFE_POS_OUTMOLD_Z];
        temp3 = m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_Z];
        temp4 = m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_Z];
        m_mbaddrspace2[SERVO_MIN_SAFE_POS_OUTMOLD_Z] = temp3;
        m_mbaddrspace2[SERVO_MAX_SAFE_POS_OUTMOLD_Z] = temp4;
        m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_Z] = temp1;
        m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_Z] = temp2;
    }
#if PENDANT_PROTOCOL
    ret = SendMsg(SERVO_MIN_SAFE_POS_OUTMOLD_Z, SERVO_MAX_SAFE_POS_INMOLD_Z, FALSE);
    if (ret == SENDMSG_RET_ACK)
    {
        ret = SendMsg2(SERVO_MIN_SAFE_POS_OUTMOLD_Z, SERVO_MAX_SAFE_POS_INMOLD_Z, FALSE);
        if (ret == SENDMSG_RET_ACK)
        {
            CommandWrite(CMD_WRITE_SERVO);
#endif
#if PENDANT_PROTOCOL
        }
    }
#endif

}

// ********************************************
// 读取指定用户的密码
int8_t CMBProtocol::ReadPwd(const uint8_t user, QByteArray &pwd)
{
    pwd.clear();
#if PENDANT_PROTOCOL
    int8_t ret = SENDMSG_RET_ACK;
    if (user == xPermissions::AdvOperater)
    {
        // 读取高级操作员密码
        ret = SendMsg(USER_DATA_00_, (USER_DATA_00_+7));
        if (ret == SENDMSG_RET_ACK)
        {
            pwd[0] = ReadReg16(USER_DATA_00_);
            pwd[1] = ReadReg16(USER_DATA_00_+1);
            pwd[2] = ReadReg16(USER_DATA_00_+2);
            pwd[3] = ReadReg16(USER_DATA_00_+3);
            pwd[4] = ReadReg16(USER_DATA_00_+4);
            pwd[5] = ReadReg16(USER_DATA_00_+5);
            pwd[6] = ReadReg16(USER_DATA_00_+6);
            pwd[7] = ReadReg16(USER_DATA_00_+7);
            pwd[8] = '\0';
        }
        return ret;
    }
    else if (user == xPermissions::Administrator)
    {
        // 读取管理员密码
        ret = SendMsg((USER_DATA_00_+8), (USER_DATA_00_+15));
        if (ret == SENDMSG_RET_ACK)
        {
            pwd[0] = ReadReg16(USER_DATA_00_+8);
            pwd[1] = ReadReg16(USER_DATA_00_+9);
            pwd[2] = ReadReg16(USER_DATA_00_+10);
            pwd[3] = ReadReg16(USER_DATA_00_+11);
            pwd[4] = ReadReg16(USER_DATA_00_+12);
            pwd[5] = ReadReg16(USER_DATA_00_+13);
            pwd[6] = ReadReg16(USER_DATA_00_+14);
            pwd[7] = ReadReg16(USER_DATA_00_+15);
            pwd[8] = '\0';
        }
        return ret;
    }
    else if (user == xPermissions::AdvAdministrator)
    {
        // 高级管理员密码
        xPermissions::DefaultPwd(user, pwd);
        return ret;
    }
    return ret;
#else
    xPermissions::DefaultPwd(user, pwd);
    return SENDMSG_RET_ACK;
#endif
}
// 读取版本信息
int8_t CMBProtocol::ReadVersion(void)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    ret =  SendMsg(VERSION_HARD_MAJOR, SERVO_DEV_NOT_EXIST);
	sysVersion.m_hard_major = ReadReg16(VERSION_HARD_MAJOR);
	sysVersion.m_hard_minor = ReadReg16(VERSION_HARD_MINOR);
	sysVersion.m_soft_major = ReadReg16(VERSION_SOFT_MAJOR);
	sysVersion.m_soft_minor = ReadReg16(VERSION_SOFT_MINOR);
    sysVersion.m_soft_extra = ReadReg16(VERSION_SOFT_EXTRA);
    sysVersion.m_soft_extra_new = ReadReg16(VERSION_SOFT_EXTRA_NEW);
    sysVersion.m_soft_Ecat = ReadReg16(VERSION_SOFT_EXTRA_NEW)>>8;
    sysVersion.m_m0_major = ReadReg16(VERSION_M0SOFT_MAJOR);
    sysVersion.m_m0_minor = ReadReg16(VERSION_M0SOFT_MINOR);
    sysVersion.m_servo_not_exist = ReadReg16(SERVO_DEV_NOT_EXIST);
#else
	sysVersion.m_hard_major = 0x01;
	sysVersion.m_hard_minor = 0x00;
	sysVersion.m_soft_major = 0x01;
	sysVersion.m_soft_minor = 0x00;
    sysVersion.m_soft_extra = ROBOTARM_TYPE_SIXSV_PAD_F3;
    sysVersion.m_soft_extra_new = ROBOTARM_TYPE_SIXSV_PAD_F3;
    sysVersion.m_m0_major = 0x01;
    sysVersion.m_m0_minor = 0x00;
    m_mbaddrspace[VERSION_SUB_FUN] = SUB_VACUUM;
#endif
	return ret;
}
// 读产品密钥
void CMBProtocol::GetProductCode(ProductCode &proc)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    ret = SendMsg(PRODUCT_ID1, PRODUCT_ID5);
#endif
    if (ret == SENDMSG_RET_ACK)
    {
        proc.m_product_id1 = m_mbaddrspace[PRODUCT_ID1];
        proc.m_product_id2 = m_mbaddrspace[PRODUCT_ID2];
        proc.m_product_id3 = m_mbaddrspace[PRODUCT_ID3];
        proc.m_product_id4 = m_mbaddrspace[PRODUCT_ID4];
        proc.m_product_id5 = m_mbaddrspace[PRODUCT_ID5];
//        proc.m_product_id6 = m_mbaddrspace[PRODUCT_ID6];
    }
}
// 读激活码及机器码
void CMBProtocol::GetRegistrationCode(RegistrationCode &regc)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    ret = SendMsg(SYSTEM_UID1, ACTIVATION8);
#endif
    if (ret == SENDMSG_RET_ACK)
    {
        regc.m_system_uid1 = m_mbaddrspace[SYSTEM_UID1];
        regc.m_system_uid2 = m_mbaddrspace[SYSTEM_UID2];
        regc.m_system_uid3 = m_mbaddrspace[SYSTEM_UID3];
        regc.m_system_uid4 = m_mbaddrspace[SYSTEM_UID4];
        regc.m_system_uid5 = m_mbaddrspace[SYSTEM_UID5];
        regc.m_system_uid6 = m_mbaddrspace[SYSTEM_UID6];
        regc.m_system_uid7 = m_mbaddrspace[SYSTEM_UID7];
        regc.m_system_uid8 = m_mbaddrspace[SYSTEM_UID8];
        regc.m_activation_1 = m_mbaddrspace[ACTIVATION1];
        regc.m_activation_2 = m_mbaddrspace[ACTIVATION2];
        regc.m_activation_3 = m_mbaddrspace[ACTIVATION3];
        regc.m_activation_4 = m_mbaddrspace[ACTIVATION4];
        regc.m_activation_5 = m_mbaddrspace[ACTIVATION5];
        regc.m_activation_6 = m_mbaddrspace[ACTIVATION6];
        regc.m_activation_7 = m_mbaddrspace[ACTIVATION7];
        regc.m_activation_8 = m_mbaddrspace[ACTIVATION8];
    }
}

// 读取授权信息
int8_t CMBProtocol::ReadPirate(void)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
	ret = SendMsg(VERSION_PIRATE, VERSION_PIRATE);
	if (ret == SENDMSG_RET_ACK)
		pirateFlag = ReadReg16(VERSION_PIRATE);
	else
		pirateFlag = LICENSE_PREVER;
#else
	pirateFlag = LICENSE_LEGAL;
#endif
	return ret;
}

// 查询系统功能列表
int8_t CMBProtocol::WriteFunctions()
{
    int8_t ret = SENDMSG_RET_ACK;
    quint64 fun = ((quint64)(SUB_FUN_TMC429 | SUB_FUN_ENCODER | SUB_FUN_EUROMAP | SUB_FUN_LOCK_ALARM
                             | SUB_FUN_KEYMAP | SUB_FUN_SDIR | SUB_LOOP_INTERVAL | SUB_VACUUM
                             | SUB_DOOR_RESET | SUB_3_AXES | SUB_IN_ANTI_CHECK_HOME_TAIL_LOOP_FREE
                             | SUB_FUN2_JERK | SUB_FUN2_IO_BMP | SUB_FUN2_WAIT_VAR2 | SUB_FUN2_EXT_POS
                             | SUB_FUN2_ROTATE | SUB_FUN2_X_B_TRAVE_SAFE | SUB_FUN2_VISION | SUB_FUN2_IFTIME
                             | SUB_FUN2_CAN_IMM | SUB_FUN2_MBVISION | SUB_FUN2_LOOP_MATRIX
                             | SUB_FUN2_LOOP_MATRIX_EXT | SUB_DOOR_QUERY | SUB_FUN2_MAIN64_BITS
                             | SUB_FUN2_LOOP_FREE_200));
#if PENDANT_PROTOCOL
    m_mbaddrspace[VERSION_SUB_FUN] = fun;
    m_mbaddrspace[VERSION_SUB_FUN2] = fun>>16;
    m_mbaddrspace[VERSION_SUB_FUN3] = fun>>32;
    ret = SendMsg(VERSION_SUB_FUN, VERSION_SUB_FUN3,false);
#endif
    return ret;
}

// 读取系统功能列表
int8_t CMBProtocol::ReadFunctions(void)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    ret = SendMsg(VERSION_SUB_FUN, VERSION_SUB_FUN3);
	if (ret == SENDMSG_RET_ACK)
        functionsList = ((quint64)ReadReg16(VERSION_SUB_FUN) | ((quint64)ReadReg16(VERSION_SUB_FUN2) << 16) | ((quint64)ReadReg16(VERSION_SUB_FUN3) << 32));
	else
		functionsList = 0;
#else
	functionsList = 0;
#endif
	return ret;
}

// 读取厂商ID
int8_t CMBProtocol::ReadFactory(void)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
	ret =  SendMsg(FACTORY_ID_L, FACTORY_ID_H);
	if (ret == SENDMSG_RET_ACK)
		factoryId = (ReadReg16(FACTORY_ID_H) << 8) | ReadReg16(FACTORY_ID_L);
#else
	factoryId = FACTORY;
#endif
	return ret;
}
// 读取原点复归设置
int8_t CMBProtocol::ReadHome(void)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
	ret =  SendMsg(HOME_DEF_00, HOME_DEF_00 + HOME_DEF_MAX - 1);
#endif
	return ret;
}
// 得到原点复归设置
void CMBProtocol::GetHome(quint16 (&home)[HOME_DEF_MAX])
{
	quint16 codeIdx = HOME_DEF_00;
	for (int i = 0; i < HOME_DEF_MAX; i ++)
	{
		home[i] = m_mbaddrspace[codeIdx];
		codeIdx ++;
	}
}
// 复位原点复归表
void CMBProtocol::ResetHome()
{
    m_mbaddrspace[HOME_DEF_00] = CUSTOMER_FUN_Y_HOME;       //主臂上下
    m_mbaddrspace[HOME_DEF_01] = CUSTOMER_FUN_A_HOME;       //副臂上下
    m_mbaddrspace[HOME_DEF_02] = CUSTOMER_FUN_RUN_VER;      //气动上下
    m_mbaddrspace[HOME_DEF_03] = CUSTOMER_FUN_PRO_ROT;      //主臂倒角
    m_mbaddrspace[HOME_DEF_04] = CUSTOMER_FUN_RUN_ROT;      //副臂倒角
    m_mbaddrspace[HOME_DEF_05] = CUSTOMER_FUN_RUN_HOR;      //气动横行
    m_mbaddrspace[HOME_DEF_06] = CUSTOMER_FUN_Z_HOME;       //横行轴
    m_mbaddrspace[HOME_DEF_07] = CUSTOMER_FUN_X_HOME;       //引拔轴
    m_mbaddrspace[HOME_DEF_08] = CUSTOMER_FUN_B_HOME;       //副引拔轴
    m_mbaddrspace[HOME_DEF_09] = CUSTOMER_FUN_C_HOME;       //扩展轴
    m_mbaddrspace[HOME_DEF_10] = CUSTOMER_FUN_CLR_EXT;      //扩展轴
}
// 检查原点复归
bool CMBProtocol::CheckHome()
{
	quint16 bmp = 0;
    for (int i = HOME_DEF_00; i <= HOME_DEF_10; ++i)
	{
		if (m_mbaddrspace[i] == CUSTOMER_FUN_Y_HOME)
			bmp |= (1<<0);
		if (m_mbaddrspace[i] == CUSTOMER_FUN_A_HOME)
			bmp |= (1<<1);
		if (m_mbaddrspace[i] == CUSTOMER_FUN_PRO_ROT)
			bmp |= (1<<2);
        if (m_mbaddrspace[i] == CUSTOMER_FUN_RUN_ROT)
			bmp |= (1<<3);
        if (m_mbaddrspace[i] == CUSTOMER_FUN_Z_HOME)
			bmp |= (1<<4);
		if (m_mbaddrspace[i] == CUSTOMER_FUN_X_HOME)
			bmp |= (1<<5);
		if (m_mbaddrspace[i] == CUSTOMER_FUN_B_HOME)
			bmp |= (1<<6);
		if (m_mbaddrspace[i] == CUSTOMER_FUN_C_HOME)
			bmp |= (1<<7);
        if (m_mbaddrspace[i] == CUSTOMER_FUN_RUN_VER)
			bmp |= (1<<8);
        if (m_mbaddrspace[i] == CUSTOMER_FUN_RUN_HOR)
            bmp |= (1<<9);
        if (m_mbaddrspace[i] == CUSTOMER_FUN_CLR_EXT)
            bmp |= (1<<10);
	}
    if (bmp!=0x7FF)
		return false;
	else
		return true;
}
// 读取系统参数
int8_t CMBProtocol::ReadSystem(void)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    ret =  SendMsg(SYS_ALARM_TIMES, SYS_MOP_ABD_TIME_HIGH);
	if (ret == SENDMSG_RET_ACK)
        ret =  SendMsg(SYS_VISION0_IP_LOW, SYS_MAIN4_INMOLD_NOALM);
    if (ret == SENDMSG_RET_ACK)
	{
		QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
		quint8 lan = settings.value(XPAD_SET_LANGUAGE, LAN_CHINESE_S).toUInt();
		if (lan != m_mbaddrspace[SYS_LANGUAGE])
		{
			settings.setValue(XPAD_SET_LANGUAGE, m_mbaddrspace[SYS_LANGUAGE]);
			settings.sync();
#if defined(Q_OS_LINUX)
			sync();
#endif
			xLan->SetLanguage(m_mbaddrspace[SYS_LANGUAGE]);
		}
	}
#endif
#if IS_XEDITOR
    m_mbaddrspace[SYS_EXT_SERVO_USE] = true;
    m_mbaddrspace[SYS_RHOR_SERVO_USE] = true;
    m_mbaddrspace[SYS_RVER_SERVO_USE] = true;
    m_mbaddrspace[SYS_RUNNER_USE] = true;
    m_mbaddrspace[SYS_JIG_USE] = false;
#endif
	return ret;
}
// 得到系统参数设置
void CMBProtocol::GetSystem(SystemParameter &par)
{
    par.m_oil_interval = ReadReg32(SYS_OIL_INTERVAL_LOW);
    par.m_oil_time = ReadReg32(SYS_OIL_TIME_LOW);
    par.m_oil_use = ReadReg16(SYS_OIL_USE);
    par.m_oil_ctrl_use = ReadReg16(SYS_OIL_USE_CTRL);
	par.m_alarm_times = ReadReg16(SYS_ALARM_TIMES);
	par.m_alarm_interval = ReadReg16(SYS_ALARM_INTERVAL);
	par.m_service_moldings = ReadReg32(SYS_SERVICE_MOLDINGS_LOW);
	par.m_language = ReadReg16(SYS_LANGUAGE);
	par.m_rotate_out_at_origin = ReadReg16(SYS_ROTATE_OUT_AT_ORIGIN);
	par.m_pause_open_door = ReadReg16(SYS_PAUSE_OPEN_DOOR);
	par.m_plan_molding = ReadReg32(SYS_PLAN_MOLDING_LOW);
	par.m_plan_alarm = ReadReg32(SYS_PLAN_ALARM_LOW);
	par.m_reject_alarm = ReadReg16(SYS_REJECT_ALARM);
	par.m_mold_closed_use = ReadReg16(SYS_MOLD_CLOSED_USE);
	par.m_imop_dwn_use = ReadReg16(SYS_INTERMOLD_DOWN_USE);
	par.m_mid_open_use = ReadReg16(SYS_MID_OPEN_USE);
	par.m_ext_servo_use = ReadReg16(SYS_EXT_SERVO_USE);
    par.m_extend_bit_use = ReadReg16(SYS_EXTRA_CTRL_BIT_USE);
	par.m_rhor_servo_use = ReadReg16(SYS_RHOR_SERVO_USE);
	par.m_rver_servo_use = ReadReg16(SYS_RVER_SERVO_USE);
	par.m_runner_use = ReadReg16(SYS_RUNNER_USE);
	par.m_runner_down_use = ReadReg16(SYS_RUN_DOWN_USE);
    par.m_runner_advance_use = ReadReg16(SYS_RUN_ADVANCE_USE);
    par.m_runner_return_use = ReadReg16(SYS_RUN_RETURN_USE);
	par.m_adjust_use = ReadReg16(SYS_ADJUST_USE);
    par.m_home_inmold = ReadReg16(SYS_HOME_INMOLD);
	par.m_rotate_inmold_use = ReadReg16(SYS_ROTATE_INMOLD_USE);
	par.m_wait_outmould = ReadReg16(SYS_WAIT_OUTMOULD);
    par.m_polary[0] = ((uint64_t)ReadReg16(SYS_MAIN1_POLARY) | ((uint64_t)ReadReg16(SYS_MAIN2_POLARY)<<16) | ((uint64_t)ReadReg16(SYS_MAIN3_POLARY)<<32) | ((uint64_t)ReadReg16(SYS_MAIN4_POLARY)<<48));
    par.m_polary[1] = ReadReg16(SYS_EXT1_POLARY);
    par.m_polary[2] = ReadReg16(SYS_EXT2_POLARY);
    par.m_polary[3] = ReadReg16(SYS_EXT3_POLARY);
    par.m_polary[4] = ReadReg16(SYS_EXT4_POLARY);
    par.m_outputpolary[0] = ((uint64_t)ReadReg16(SYS_MAIN1_OUTPOLARY) | ((uint64_t)ReadReg16(SYS_MAIN2_OUTPOLARY)<<16) | ((uint64_t)ReadReg16(SYS_MAIN3_OUTPOLARY)<<32) | ((uint64_t)ReadReg16(SYS_MAIN4_OUTPOLARY)<<48));
    par.m_outputpolary[1] = ReadReg16(SYS_EXT1_OUTPOLARY);
    par.m_outputpolary[2] = ReadReg16(SYS_EXT2_OUTPOLARY);
    par.m_outputpolary[3] = ReadReg16(SYS_EXT3_OUTPOLARY);
    par.m_outputpolary[4] = ReadReg16(SYS_EXT4_OUTPOLARY);
    par.m_ignore[0] = ((uint64_t)ReadReg16(SYS_MAIN1_IGNORE) | ((uint64_t)ReadReg16(SYS_MAIN2_IGNORE)<<16) | ((uint64_t)ReadReg16(SYS_MAIN3_IGNORE)<<32) | ((uint64_t)ReadReg16(SYS_MAIN4_IGNORE)<<48));
	par.m_ignore[1] = ReadReg16(SYS_EXT1_IGNORE);
	par.m_ignore[2] = ReadReg16(SYS_EXT2_IGNORE);
	par.m_ignore[3] = ReadReg16(SYS_EXT3_IGNORE);
	par.m_ignore[4] = ReadReg16(SYS_EXT4_IGNORE);
    par.m_noalm[0] = ((uint64_t)ReadReg16(SYS_MAIN1_INMOLD_NOALM) | ((uint64_t)ReadReg16(SYS_MAIN2_INMOLD_NOALM)<<16) | ((uint64_t)ReadReg16(SYS_MAIN3_INMOLD_NOALM)<<32) | ((uint64_t)ReadReg16(SYS_MAIN4_INMOLD_NOALM)<<48));
	par.m_noalm[1] = ReadReg16(SYS_EXT1_INMOLD_NOALM);
	par.m_noalm[2] = ReadReg16(SYS_EXT2_INMOLD_NOALM);
	par.m_noalm[3] = ReadReg16(SYS_EXT3_INMOLD_NOALM);
	par.m_noalm[4] = ReadReg16(SYS_EXT4_INMOLD_NOALM);
	par.m_jig_use = ReadReg16(SYS_JIG_USE);
    par.m_proc2_use = ReadReg16(SYS_PROC2_USE);
    par.m_proc3_use = ReadReg16(SYS_PROC3_USE);
    par.m_proc_use = ReadReg16(SYS_PROC_USE);
    par.m_ip = ReadReg32(SYS_NET_IP_ADDR_LOW);
    par.m_submask = ReadReg32(SYS_NET_IP_MASK_LOW);
    par.m_gateway = ReadReg32(SYS_NET_IP_GATE_LOW);
    par.m_rotate_use = ReadReg16(SYS_ROTATE_USE);
    par.m_run_rotate_use = ReadReg16(SYS_RUN_ROTATE_USE);
    par.m_door_reset_use = ReadReg16(SYS_DOOR_RESET_USE);
	par.m_sys_io_clr = ReadReg16(SYS_IO_CLR);
    par.m_visionip1 = ReadReg32(SYS_VISION0_IP_LOW);
    par.m_visionip2 = ReadReg32(SYS_VISION1_IP_LOW);
    par.m_visionip3 = ReadReg32(SYS_VISION2_IP_LOW);
    par.m_visionip4 = ReadReg32(SYS_VISION3_IP_LOW);
    par.m_visionip5 = ReadReg32(SYS_VISION4_IP_LOW);
    par.m_visionip6 = ReadReg32(SYS_VISION5_IP_LOW);
    par.m_visionip7 = ReadReg32(SYS_VISION6_IP_LOW);
    par.m_visionip8 = ReadReg32(SYS_VISION7_IP_LOW);
    par.m_vision1port = ReadReg16(SYS_VISION0_PORT);
    par.m_vision2port = ReadReg16(SYS_VISION1_PORT);
    par.m_vision3port = ReadReg16(SYS_VISION2_PORT);
    par.m_vision4port = ReadReg16(SYS_VISION3_PORT);
    par.m_vision5port = ReadReg16(SYS_VISION4_PORT);
    par.m_vision6port = ReadReg16(SYS_VISION5_PORT);
    par.m_vision7port = ReadReg16(SYS_VISION6_PORT);
    par.m_vision8port = ReadReg16(SYS_VISION7_PORT);
    par.m_vision1_trigger = ReadReg16(SYS_VISION0_TYPE_TRIGGER);
    par.m_vision2_trigger = ReadReg16(SYS_VISION1_TYPE_TRIGGER);
    par.m_vision3_trigger = ReadReg16(SYS_VISION2_TYPE_TRIGGER);
    par.m_vision4_trigger = ReadReg16(SYS_VISION3_TYPE_TRIGGER);
    par.m_vision5_trigger = ReadReg16(SYS_VISION4_TYPE_TRIGGER);
    par.m_vision6_trigger = ReadReg16(SYS_VISION5_TYPE_TRIGGER);
    par.m_vision7_trigger = ReadReg16(SYS_VISION6_TYPE_TRIGGER);
    par.m_vision8_trigger = ReadReg16(SYS_VISION7_TYPE_TRIGGER);
    par.m_vision1_outvar = ReadReg16(SYS_VISION0_OUTVAR);
    par.m_vision2_outvar = ReadReg16(SYS_VISION1_OUTVAR);
    par.m_vision3_outvar = ReadReg16(SYS_VISION2_OUTVAR);
    par.m_vision4_outvar = ReadReg16(SYS_VISION3_OUTVAR);
    par.m_vision5_outvar = ReadReg16(SYS_VISION4_OUTVAR);
    par.m_vision6_outvar = ReadReg16(SYS_VISION5_OUTVAR);
    par.m_vision7_outvar = ReadReg16(SYS_VISION6_OUTVAR);
    par.m_vision8_outvar = ReadReg16(SYS_VISION7_OUTVAR);
}
// 读取伺服参数
int8_t CMBProtocol::ReadServo(void)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    ret =  SendMsg(SERVO_MACHINE_MAX_LEN_X, SERVO_MAX_X_TRAVE);
	if (ret == SENDMSG_RET_ACK)
        ret =  SendMsg2(SERVO_MACHINE_MAX_LEN_X, SERVO_MAX_X_TRAVE);

    ret =  SendMsg(SERVO_PA5_X, SERVO_PA63_B);
        if (ret == SENDMSG_RET_ACK)
            ret =  SendMsg2(SERVO_PA5_X, SERVO_PA63_B);
#endif
	return ret;
}
int8_t CMBProtocol::ReadIoBmp(void)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    ret =  SendMsg(IN_BMP_BEG, IN_BMP_BEG+MAX_IN_BMP/2-1);
    if (ret != SENDMSG_RET_ACK) return ret;
    ret =  SendMsg(IN_BMP_BEG+MAX_IN_BMP/2, IN_BMP_END);
    if (ret != SENDMSG_RET_ACK) return ret;

    ret =  SendMsg(OUT_BMP_BEG, OUT_BMP_BEG+MAX_OUT_BMP/2-1);
    if (ret != SENDMSG_RET_ACK) return ret;
    ret =  SendMsg(OUT_BMP_BEG+MAX_OUT_BMP/2, OUT_BMP_END);
#endif
    return ret;
}

// 得到伺服参数设置
void CMBProtocol::GetServo(ServoParameter &srvPar)
{
	// 引拔轴设置
	srvPar.m_machine_max_len_x = ((uint32_t)m_mbaddrspace[SERVO_MACHINE_MAX_LEN_X]) | (((uint32_t)m_mbaddrspace2[SERVO_MACHINE_MAX_LEN_X]) << 16);
	srvPar.m_min_safe_dis_x_b = ((uint32_t)m_mbaddrspace[SERVO_MIN_SAFE_DIS_X_B]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_SAFE_DIS_X_B]) << 16);
	// 软件最大行程
	srvPar.m_software_max_len_y = ((uint32_t)m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_Y]) | (((uint32_t)m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_Y]) << 16);
	srvPar.m_software_max_len_z = ((uint32_t)m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_Z]) | (((uint32_t)m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_Z]) << 16);
	srvPar.m_software_max_len_a = ((uint32_t)m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_A]) | (((uint32_t)m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_A]) << 16);
	srvPar.m_software_max_len_c = ((uint32_t)m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_C]) | (((uint32_t)m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_C]) << 16);
	// 原点偏移
//	srvPar.m_origin_offset_x = ((uint32_t)m_mbaddrspace[SERVO_ORIGIN_OFFSET_X]) | (((uint32_t)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_X]) << 16);
//	srvPar.m_origin_offset_y = ((uint32_t)m_mbaddrspace[SERVO_ORIGIN_OFFSET_Y]) | (((uint32_t)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_Y]) << 16);
//	srvPar.m_origin_offset_z = ((uint32_t)m_mbaddrspace[SERVO_ORIGIN_OFFSET_Z]) | (((uint32_t)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_Z]) << 16);
//	srvPar.m_origin_offset_a =((uint32_t) m_mbaddrspace[SERVO_ORIGIN_OFFSET_A]) | (((uint32_t)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_A]) << 16);
//	srvPar.m_origin_offset_b = ((uint32_t)m_mbaddrspace[SERVO_ORIGIN_OFFSET_B]) | (((uint32_t)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_B]) << 16);
//	srvPar.m_origin_offset_c = ((uint32_t)m_mbaddrspace[SERVO_ORIGIN_OFFSET_C]) | (((uint32_t)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_C]) << 16);
	// 安全区
	srvPar.m_max_wait_pos_inmold_y = ((uint32_t)m_mbaddrspace[SERVO_MAX_WAIT_POS_INMOLD_Y]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_WAIT_POS_INMOLD_Y]) << 16);
	srvPar.m_max_wait_pos_inmold_a = ((uint32_t)m_mbaddrspace[SERVO_MAX_WAIT_POS_INMOLD_A]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_WAIT_POS_INMOLD_A]) << 16);
	srvPar.m_min_safe_pos_outmold_z = ((uint32_t)m_mbaddrspace[SERVO_MIN_SAFE_POS_OUTMOLD_Z]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_SAFE_POS_OUTMOLD_Z]) << 16);
	srvPar.m_max_safe_pos_outmold_z = ((uint32_t)m_mbaddrspace[SERVO_MAX_SAFE_POS_OUTMOLD_Z]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_SAFE_POS_OUTMOLD_Z]) << 16);
	srvPar.m_min_safe_pos_inmold_z = ((uint32_t)m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_Z]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_Z]) << 16);
	srvPar.m_max_safe_pos_inmold_z = ((uint32_t)m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_Z]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_Z]) << 16);
    srvPar.m_min_safe_pos_outmold2_z = ((uint32_t)m_mbaddrspace[SERVO_MIN_SAFE_POS_OUTMOLD2_Z]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_SAFE_POS_OUTMOLD2_Z]) << 16);
    srvPar.m_max_safe_pos_outmold2_z = ((uint32_t)m_mbaddrspace[SERVO_MAX_SAFE_POS_OUTMOLD2_Z]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_SAFE_POS_OUTMOLD2_Z]) << 16);
    srvPar.m_min_a_trv =  ((uint32_t)m_mbaddrspace[SERVO_MIN_A_TRAVE]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_A_TRAVE]) << 16);
    srvPar.m_max_a_trv =  ((uint32_t)m_mbaddrspace[SERVO_MAX_A_TRAVE]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_A_TRAVE]) << 16);
    srvPar.m_min_a_inmold =  ((uint32_t)m_mbaddrspace[SERVO_MIN_A_INMOLD]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_A_INMOLD]) << 16);
    srvPar.m_max_a_inmold =  ((uint32_t)m_mbaddrspace[SERVO_MAX_A_INMOLD]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_A_INMOLD]) << 16);

	srvPar.m_min_safe_pos_inmold_x = ((uint32_t)m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_X]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_X]) << 16);
	srvPar.m_max_safe_pos_inmold_x = ((uint32_t)m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_X]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_X]) << 16);
	srvPar.m_min_safe_pos_inmold_b = ((uint32_t)m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_B]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_B]) << 16);
	srvPar.m_max_safe_pos_inmold_b = ((uint32_t)m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_B]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_B]) << 16);
    srvPar.m_min_safe_pos_inmold_z_a = ((uint32_t)m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_Z_A]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_Z_A]) << 16);
    srvPar.m_max_safe_pos_inmold_z_a = ((uint32_t)m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_Z_A]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_Z_A]) << 16);

    srvPar.m_min_b_trave = ((uint32_t)m_mbaddrspace[SERVO_MIN_B_TRAVE]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_B_TRAVE]) << 16);
    srvPar.m_max_b_trave = ((uint32_t)m_mbaddrspace[SERVO_MAX_B_TRAVE]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_B_TRAVE]) << 16);
    srvPar.m_min_c_trave = ((uint32_t)m_mbaddrspace[SERVO_MIN_C_TRAVE]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_C_TRAVE]) << 16);
    srvPar.m_max_c_trave = ((uint32_t)m_mbaddrspace[SERVO_MAX_C_TRAVE]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_C_TRAVE]) << 16);
    srvPar.m_min_c_inmold = ((uint32_t)m_mbaddrspace[SERVO_MIN_C_INMOLD]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_C_INMOLD]) << 16);
    srvPar.m_max_c_inmold = ((uint32_t)m_mbaddrspace[SERVO_MAX_C_INMOLD]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_C_INMOLD]) << 16);
    srvPar.m_min_x_trave = ((uint32_t)m_mbaddrspace[SERVO_MIN_X_TRAVE]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_X_TRAVE]) << 16);
    srvPar.m_max_x_trave = ((uint32_t)m_mbaddrspace[SERVO_MAX_X_TRAVE]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_X_TRAVE]) << 16);
   // 正臂引拔轴速度/加速度
	srvPar.m_xmax_speed = m_mbaddrspace[SERVO_XMAX_SPEED];
	srvPar.m_xmax_acceleration = m_mbaddrspace[SERVO_XMAX_ACCELERATION];
	// 正臂上下轴速度/加速度
	srvPar.m_ymax_speed = m_mbaddrspace[SERVO_YMAX_SPEED];
	srvPar.m_ymax_acceleration = m_mbaddrspace[SERVO_YMAX_ACCELERATION];
	// 横行轴速度/加速度
	srvPar.m_zmax_speed = m_mbaddrspace[SERVO_ZMAX_SPEED];
	srvPar.m_zmax_acceleration = m_mbaddrspace[SERVO_ZMAX_ACCELERATION];
	// 副臂上下轴速度/加速度
	srvPar.m_amax_speed = m_mbaddrspace[SERVO_AMAX_SPEED];
	srvPar.m_amax_acceleration = m_mbaddrspace[SERVO_AMAX_ACCELERATION];
	// 副臂引拔轴速度/加速度
	srvPar.m_bmax_speed = m_mbaddrspace[SERVO_BMAX_SPEED];
	srvPar.m_bmax_acceleration = m_mbaddrspace[SERVO_BMAX_ACCELERATION];
	// 扩展轴速度/加速度
	srvPar.m_cmax_speed = m_mbaddrspace[SERVO_CMAX_SPEED];
	srvPar.m_cmax_acceleration = m_mbaddrspace[SERVO_CMAX_ACCELERATION];
    // 原点偏移
    srvPar.m_origin_offset_x = ((qint32)m_mbaddrspace[SERVO_ORIGIN_OFFSET_X]) | (((qint32)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_X]) << 16);
    srvPar.m_origin_offset_y = ((qint32)m_mbaddrspace[SERVO_ORIGIN_OFFSET_Y]) | (((qint32)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_Y]) << 16);
    srvPar.m_origin_offset_z = ((qint32)m_mbaddrspace[SERVO_ORIGIN_OFFSET_Z]) | (((qint32)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_Z]) << 16);
    srvPar.m_origin_offset_a = ((qint32)m_mbaddrspace[SERVO_ORIGIN_OFFSET_A]) | (((qint32)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_A]) << 16);
    srvPar.m_origin_offset_b = ((qint32)m_mbaddrspace[SERVO_ORIGIN_OFFSET_B]) | (((qint32)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_B]) << 16);
    srvPar.m_origin_offset_c = ((qint32)m_mbaddrspace[SERVO_ORIGIN_OFFSET_C]) | (((qint32)m_mbaddrspace2[SERVO_ORIGIN_OFFSET_C]) << 16);
    // 原点待机点
    srvPar.m_home_pos_x = ((qint32)m_mbaddrspace[SERVO_HOME_POS_X]) | (((qint32)m_mbaddrspace2[SERVO_HOME_POS_X]) << 16);
    srvPar.m_home_pos_y = ((qint32)m_mbaddrspace[SERVO_HOME_POS_Y]) | (((qint32)m_mbaddrspace2[SERVO_HOME_POS_Y]) << 16);
    srvPar.m_home_pos_z = ((qint32)m_mbaddrspace[SERVO_HOME_POS_Z]) | (((qint32)m_mbaddrspace2[SERVO_HOME_POS_Z]) << 16);
    srvPar.m_home_pos_a = ((qint32)m_mbaddrspace[SERVO_HOME_POS_A]) | (((qint32)m_mbaddrspace2[SERVO_HOME_POS_A]) << 16);
    srvPar.m_home_pos_b = ((qint32)m_mbaddrspace[SERVO_HOME_POS_B]) | (((qint32)m_mbaddrspace2[SERVO_HOME_POS_B]) << 16);
    srvPar.m_home_pos_c = ((qint32)m_mbaddrspace[SERVO_HOME_POS_C]) | (((qint32)m_mbaddrspace2[SERVO_HOME_POS_C]) << 16);
    // 模
    srvPar.m_mod_x = ((qint32)m_mbaddrspace[SERVO_MOD_X]) | (((qint32)m_mbaddrspace2[SERVO_MOD_X]) << 16);
    srvPar.m_mod_y = ((qint32)m_mbaddrspace[SERVO_MOD_Y]) | (((qint32)m_mbaddrspace2[SERVO_MOD_Y]) << 16);
    srvPar.m_mod_z = ((qint32)m_mbaddrspace[SERVO_MOD_Z]) | (((qint32)m_mbaddrspace2[SERVO_MOD_Z]) << 16);
    srvPar.m_mod_a = ((qint32)m_mbaddrspace[SERVO_MOD_A]) | (((qint32)m_mbaddrspace2[SERVO_MOD_A]) << 16);
    srvPar.m_mod_b = ((qint32)m_mbaddrspace[SERVO_MOD_B]) | (((qint32)m_mbaddrspace2[SERVO_MOD_B]) << 16);
    srvPar.m_mod_c = ((qint32)m_mbaddrspace[SERVO_MOD_C]) | (((qint32)m_mbaddrspace2[SERVO_MOD_C]) << 16);
    // 编码器
    srvPar.m_encoder_x = m_mbaddrspace[SERVO_ENCODER_X];
    srvPar.m_encoder_y = m_mbaddrspace[SERVO_ENCODER_Y];
    srvPar.m_encoder_z = m_mbaddrspace[SERVO_ENCODER_Z];
    srvPar.m_encoder_a = m_mbaddrspace[SERVO_ENCODER_A];
    srvPar.m_encoder_b = m_mbaddrspace[SERVO_ENCODER_B];
    srvPar.m_encoder_c = m_mbaddrspace[SERVO_ENCODER_C];
    // JERK
    srvPar.m_xmax_jerk = m_mbaddrspace[SERVO_XMAX_JERK];
    srvPar.m_ymax_jerk = m_mbaddrspace[SERVO_YMAX_JERK];
    srvPar.m_zmax_jerk = m_mbaddrspace[SERVO_ZMAX_JERK];
    srvPar.m_amax_jerk = m_mbaddrspace[SERVO_AMAX_JERK];
    srvPar.m_bmax_jerk = m_mbaddrspace[SERVO_BMAX_JERK];
    srvPar.m_cmax_jerk = m_mbaddrspace[SERVO_CMAX_JERK];

    // 马达转动
    uint32_t tmp;
    tmp= m_mbaddrspace2[SERVO_X_REV_UNITS];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_X_REV_UNITS];
    srvPar.m_x_units = *(float*)(&tmp);
    tmp = m_mbaddrspace2[SERVO_X_REV_PULSES];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_X_REV_PULSES];
    srvPar.m_x_pluses = *(float*)(&tmp);

    tmp= m_mbaddrspace2[SERVO_Y_REV_UNITS];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_Y_REV_UNITS];
    srvPar.m_y_units = *(float*)(&tmp);
    tmp = m_mbaddrspace2[SERVO_Y_REV_PULSES];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_Y_REV_PULSES];
    srvPar.m_y_pluses = *(float*)(&tmp);

    tmp= m_mbaddrspace2[SERVO_Z_REV_UNITS];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_Z_REV_UNITS];
    srvPar.m_z_units = *(float*)(&tmp);
    tmp = m_mbaddrspace2[SERVO_Z_REV_PULSES];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_Z_REV_PULSES];
    srvPar.m_z_pluses = *(float*)(&tmp);

    tmp= m_mbaddrspace2[SERVO_A_REV_UNITS];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_A_REV_UNITS];
    srvPar.m_a_units = *(float*)(&tmp);
    tmp = m_mbaddrspace2[SERVO_A_REV_PULSES];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_A_REV_PULSES];
    srvPar.m_a_pluses = *(float*)(&tmp);

    tmp= m_mbaddrspace2[SERVO_B_REV_UNITS];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_B_REV_UNITS];
    srvPar.m_b_units = *(float*)(&tmp);
    tmp = m_mbaddrspace2[SERVO_B_REV_PULSES];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_B_REV_PULSES];
    srvPar.m_b_pluses = *(float*)(&tmp);

    tmp= m_mbaddrspace2[SERVO_C_REV_UNITS];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_C_REV_UNITS];
    srvPar.m_c_units = *(float*)(&tmp);
    tmp = m_mbaddrspace2[SERVO_C_REV_PULSES];
    tmp <<= 16;
    tmp |= m_mbaddrspace[SERVO_C_REV_PULSES];
    srvPar.m_c_pluses = *(float*)(&tmp);
    // 轴类型 方向
    srvPar.m_angle_type = m_mbaddrspace[SERVO_ANGLE_BMP];
    // 减速类型
    srvPar.m_dec_type = m_mbaddrspace[SERVO_RAMP_BMP_HOME_TAIL];
    // 原点归位模式
    srvPar.m_home_mode = m_mbaddrspace[SERVO_HOME_MODE];
    srvPar.m_home_vel = m_mbaddrspace[SERVO_HOME_VEL];
    srvPar.m_home_vel_slow = m_mbaddrspace[SERVO_HOME_LOWVEL];

    //伺服驱动器参数
    srvPar.m_pa5_x = m_mbaddrspace[SERVO_PA5_X];
    srvPar.m_pa5_y = m_mbaddrspace[SERVO_PA5_Y];
    srvPar.m_pa5_z = m_mbaddrspace[SERVO_PA5_Z];
    srvPar.m_pa5_a = m_mbaddrspace[SERVO_PA5_A];
    srvPar.m_pa5_b = m_mbaddrspace[SERVO_PA5_B];

    srvPar.m_pa6_x = m_mbaddrspace[SERVO_PA6_X];
    srvPar.m_pa6_y = m_mbaddrspace[SERVO_PA6_Y];
    srvPar.m_pa6_z = m_mbaddrspace[SERVO_PA6_Z];
    srvPar.m_pa6_a = m_mbaddrspace[SERVO_PA6_A];
    srvPar.m_pa6_b = m_mbaddrspace[SERVO_PA6_B];

    srvPar.m_pa7_x = m_mbaddrspace[SERVO_PA7_X];
    srvPar.m_pa7_y = m_mbaddrspace[SERVO_PA7_Y];
    srvPar.m_pa7_z = m_mbaddrspace[SERVO_PA7_Z];
    srvPar.m_pa7_a = m_mbaddrspace[SERVO_PA7_A];
    srvPar.m_pa7_b = m_mbaddrspace[SERVO_PA7_B];

    srvPar.m_pa8_x = m_mbaddrspace[SERVO_PA8_X];
    srvPar.m_pa8_y = m_mbaddrspace[SERVO_PA8_Y];
    srvPar.m_pa8_z = m_mbaddrspace[SERVO_PA8_Z];
    srvPar.m_pa8_a = m_mbaddrspace[SERVO_PA8_A];
    srvPar.m_pa8_b = m_mbaddrspace[SERVO_PA8_B];

    srvPar.m_pa9_x = m_mbaddrspace[SERVO_PA9_X];
    srvPar.m_pa9_y = m_mbaddrspace[SERVO_PA9_Y];
    srvPar.m_pa9_z = m_mbaddrspace[SERVO_PA9_Z];
    srvPar.m_pa9_a = m_mbaddrspace[SERVO_PA9_A];
    srvPar.m_pa9_b = m_mbaddrspace[SERVO_PA9_B];

    srvPar.m_pa19_x = m_mbaddrspace[SERVO_PA19_X];
    srvPar.m_pa19_y = m_mbaddrspace[SERVO_PA19_Y];
    srvPar.m_pa19_z = m_mbaddrspace[SERVO_PA19_Z];
    srvPar.m_pa19_a = m_mbaddrspace[SERVO_PA19_A];
    srvPar.m_pa19_b = m_mbaddrspace[SERVO_PA19_B];

    srvPar.m_pa63_x = m_mbaddrspace[SERVO_PA63_X];
    srvPar.m_pa63_y = m_mbaddrspace[SERVO_PA63_Y];
    srvPar.m_pa63_z = m_mbaddrspace[SERVO_PA63_Z];
    srvPar.m_pa63_a = m_mbaddrspace[SERVO_PA63_A];
    srvPar.m_pa63_b = m_mbaddrspace[SERVO_PA63_B];
}
uint8_t CMBProtocol::GetHomeVel(void)
{
    return m_mbaddrspace[SERVO_HOME_VEL];
}
uint32_t CMBProtocol::GetHorLen(void)
{
	return ((uint32_t)m_mbaddrspace[SERVO_MACHINE_MAX_LEN_X]) | (((uint32_t)m_mbaddrspace2[SERVO_MACHINE_MAX_LEN_X]) << 16);
}
uint32_t CMBProtocol::GetHorInt(void)
{
	return ((uint32_t)m_mbaddrspace[SERVO_MIN_SAFE_DIS_X_B]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_SAFE_DIS_X_B]) << 16);
}
uint32_t CMBProtocol::GetPaVerLen(void)
{
	return ((uint32_t)m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_Y]) | (((uint32_t)m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_Y]) << 16);
}
uint32_t CMBProtocol::GetTravLen(void)
{
	return ((uint32_t)m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_Z]) | (((uint32_t)m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_Z]) << 16);
}
uint32_t CMBProtocol::GetRaVerLen(void)
{
	return ((uint32_t)m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_A]) | (((uint32_t)m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_A]) << 16);
}
uint32_t CMBProtocol::GetExteLen(void)
{
	return ((uint32_t)m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_C]) | (((uint32_t)m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_C]) << 16);
}
uint32_t CMBProtocol::GetPaHorSafeBegin(void)
{
	return ((uint32_t)m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_X]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_X]) << 16);
}
uint32_t CMBProtocol::GetPaHorSafeEnd(void)
{
	return ((uint32_t)m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_X]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_X]) << 16);
}
uint32_t CMBProtocol::GetRaHorSafeBegin(void)
{
	return ((uint32_t)m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_B]) | (((uint32_t)m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_B]) << 16);
}
uint32_t CMBProtocol::GetRaHorSafeEnd(void)
{
	return ((uint32_t)m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_B]) | (((uint32_t)m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_B]) << 16);
}
// ********************************************
// 参数写接口
// ********************************************
// 写入系统语言设置
int8_t CMBProtocol::WriteLanguage(uint8_t lan)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    m_mbaddrspace[SYS_LANGUAGE] = lan;
    ret = SendMsg(SYS_LANGUAGE, SYS_LANGUAGE, FALSE);
    if (ret == SENDMSG_RET_ACK)
    {
        m_mbaddrspace[COMMAND_PARA1] = CMD_WRITE_SYSTEM;
        m_mbaddrspace[COMMAND] = COMMAND_WRITE_PARA;
        ret =  SendMsg(COMMAND_PARA1, COMMAND, FALSE);
    }
#endif
    return ret;
}
// 写入指定用户的密码
int8_t CMBProtocol::WritePwd(const uint8_t user, QByteArray &pwd)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    uint16_t base, i, pwdSize;
    pwdSize = pwd.size();
    if (user == xPermissions::AdvOperater)
    {
        // 写入高级操作员密码
        base = USER_DATA_00_;
    }
    else if (user == xPermissions::Administrator)
    {
        // 写入管理员密码
        base = (USER_DATA_00_+8);
    }
    else
        return SENDMSG_RET_ACK;
    // 发送密码
    for (i = 0; i < MAX_PWD_LEN; i++)
    {
        if (i < pwdSize)
            m_mbaddrspace[base + i] = pwd.at(i);
        else
            m_mbaddrspace[base + i] = 0;
    }
	ret =  SendMsg(base, base + MAX_PWD_LEN - 1, FALSE);
    // 写入密码
	if (ret == SENDMSG_RET_ACK)
    {
        m_mbaddrspace[COMMAND_PARA1] = CMD_WRITE_USER;
        m_mbaddrspace[COMMAND] = COMMAND_WRITE_PARA;
		ret =  SendMsg(COMMAND_PARA1, COMMAND, FALSE);
    }
#endif
    return ret;
}
// 写入厂商ID
int8_t CMBProtocol::WriteFactory(uint16_t faID)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
	m_mbaddrspace[FACTORY_ID_L] = faID & 0xFF;
	m_mbaddrspace[FACTORY_ID_H] = faID >> 8;
	ret = SendMsg(FACTORY_ID_L, FACTORY_ID_H, FALSE);
	if (ret == SENDMSG_RET_ACK)
	{
		m_mbaddrspace[COMMAND_PARA1] = CMD_WRITE_USER;
		m_mbaddrspace[COMMAND] = COMMAND_WRITE_PARA;
		ret =  SendMsg(COMMAND_PARA1, COMMAND, FALSE);
		if (ret == SENDMSG_RET_ACK)
			factoryId = faID;
	}
#endif
	return ret;
}
// 写入原点复归设置
int8_t CMBProtocol::WriteHome(const quint16 home[HOME_DEF_MAX])
{
	int8_t ret = SENDMSG_RET_ACK;
	quint16 codeIdx = HOME_DEF_00;
	for (int i = 0; i < HOME_DEF_MAX; i ++)
	{
		m_mbaddrspace[codeIdx] = home[i];
		codeIdx ++;
	}
#if PENDANT_PROTOCOL
	ret = SendMsg(HOME_DEF_00, HOME_DEF_00 + HOME_DEF_MAX - 1, FALSE);
#endif
	return ret;
}
// 写入产品密钥
int8_t CMBProtocol::WriteProductCode(const ProductCode &proc)
{
    int8_t ret = SENDMSG_RET_ACK;
    m_mbaddrspace[PRODUCT_ID1] = proc.m_product_id1;
    m_mbaddrspace[PRODUCT_ID2] = proc.m_product_id2;
    m_mbaddrspace[PRODUCT_ID3] = proc.m_product_id3;
    m_mbaddrspace[PRODUCT_ID4] = proc.m_product_id4;
    m_mbaddrspace[PRODUCT_ID5] = proc.m_product_id5;
    // 参数修改标志
#if PENDANT_PROTOCOL
    // 发送数据
    ret =  SendMsg(PRODUCT_ID1, PRODUCT_ID5, FALSE);
#endif
    return ret;
}
// 写入激活码
int8_t CMBProtocol::WriteRegistrationCode(const RegistrationCode &regc)
{
    int8_t ret = SENDMSG_RET_ACK;
    m_mbaddrspace[ACTIVATION1] = regc.m_activation_1;
    m_mbaddrspace[ACTIVATION2] = regc.m_activation_2;
    m_mbaddrspace[ACTIVATION3] = regc.m_activation_3;
    m_mbaddrspace[ACTIVATION4] = regc.m_activation_4;
    m_mbaddrspace[ACTIVATION5] = regc.m_activation_5;
    m_mbaddrspace[ACTIVATION6] = regc.m_activation_6;
    m_mbaddrspace[ACTIVATION7] = regc.m_activation_7;
    m_mbaddrspace[ACTIVATION8] = regc.m_activation_8;
    // 参数修改标志
#if PENDANT_PROTOCOL
    // 发送数据
    ret =  SendMsg(ACTIVATION1, ACTIVATION8, FALSE);
#endif
    return ret;
}

// 写入系统参数
int8_t CMBProtocol::WriteSystem(const SystemParameter &psp, quint64 modify)
{
	int8_t ret = SENDMSG_RET_ACK;
	quint16 logBuf[LOG_SYSPAR_SIZE];
	logBuf[LOG_ALARM_TIMES] =				m_mbaddrspace[SYS_ALARM_TIMES] =			psp.m_alarm_times;
	logBuf[LOG_ALARM_INTERVAL] =			m_mbaddrspace[SYS_ALARM_INTERVAL] =			psp.m_alarm_interval;
											m_mbaddrspace[SYS_SERVICE_MOLDINGS_LOW] =	psp.m_service_moldings;
											m_mbaddrspace[SYS_SERVICE_MOLDINGS_HIGH] =	psp.m_service_moldings >> 16;
	logBuf[LOG_LANGUAGE] =					m_mbaddrspace[SYS_LANGUAGE] =				psp.m_language;
	logBuf[LOG_ROTATE_OUT_AT_ORIGIN] =		m_mbaddrspace[SYS_ROTATE_OUT_AT_ORIGIN] =	psp.m_rotate_out_at_origin;
	logBuf[LOG_PAUSE_OPEN_DOOR] =			m_mbaddrspace[SYS_PAUSE_OPEN_DOOR] =		psp.m_pause_open_door;
	logBuf[LOG_PLAN_MOLDING_LOW] =			m_mbaddrspace[SYS_PLAN_MOLDING_LOW] =		psp.m_plan_molding;
	logBuf[LOG_PLAN_MOLDING_HIGH] =			m_mbaddrspace[SYS_PLAN_MOLDING_HIGH] =		psp.m_plan_molding >> 16;
	logBuf[LOG_PLAN_ALARM_LOW] =			m_mbaddrspace[SYS_PLAN_ALARM_LOW] =			psp.m_plan_alarm;
	logBuf[LOG_PLAN_ALARM_HIGH] =			m_mbaddrspace[SYS_PLAN_ALARM_HIGH] =		psp.m_plan_alarm >> 16;
	logBuf[LOG_REJECT_ALARM] =				m_mbaddrspace[SYS_REJECT_ALARM] =			psp.m_reject_alarm;
	logBuf[LOG_MOLD_CLOSED_USE] =			m_mbaddrspace[SYS_MOLD_CLOSED_USE] =		psp.m_mold_closed_use;
	logBuf[LOG_EXT_SERVO_USE] =				m_mbaddrspace[SYS_EXT_SERVO_USE] =			psp.m_ext_servo_use;
    logBuf[LOG_EXTEND_BIT_USE] =            m_mbaddrspace[SYS_EXTRA_CTRL_BIT_USE] =     psp.m_extend_bit_use;
	logBuf[LOG_RHOR_SERVO_USE] =			m_mbaddrspace[SYS_RHOR_SERVO_USE] =			psp.m_rhor_servo_use;
	logBuf[LOG_RVER_SERVO_USE] =			m_mbaddrspace[SYS_RVER_SERVO_USE] =			psp.m_rver_servo_use;
    logBuf[LOG_RUNNER_USE] =				m_mbaddrspace[SYS_RUNNER_USE] =				psp.m_runner_use;
	logBuf[LOG_RUNNER_DOWN_USE] =			m_mbaddrspace[SYS_RUN_DOWN_USE] =			psp.m_runner_down_use;
    logBuf[LOG_RUNNER_ADVANCE_USE] =		m_mbaddrspace[SYS_RUN_ADVANCE_USE] =		psp.m_runner_advance_use;
    logBuf[LOG_RUNNER_RETURN_USE] =			m_mbaddrspace[SYS_RUN_RETURN_USE] =			psp.m_runner_return_use;
	logBuf[LOG_ADJUST_USE] =				m_mbaddrspace[SYS_ADJUST_USE] =				psp.m_adjust_use;
                                            //m_mbaddrspace[SYS_SERVICE_TICK_LOW] =		psp.m_service_tick;
                                            //m_mbaddrspace[SYS_SERVICE_TICK_HIGH] =		psp.m_service_tick >> 16;
	logBuf[LOG_ROTATE_INMOLD_USE] =			m_mbaddrspace[SYS_ROTATE_INMOLD_USE] =		psp.m_rotate_inmold_use;
    logBuf[LOG_HOME_INMOLD] =               m_mbaddrspace[SYS_HOME_INMOLD] =            psp.m_home_inmold;
	logBuf[LOG_WAIT_OUTMOULD] =				m_mbaddrspace[SYS_WAIT_OUTMOULD] =			psp.m_wait_outmould;
	logBuf[LOG_JIG_USE]			=			m_mbaddrspace[SYS_JIG_USE] =				psp.m_jig_use;
    logBuf[LOG_PROC2_USE]       =           m_mbaddrspace[SYS_PROC2_USE] =              psp.m_proc2_use;
    logBuf[LOG_PROC3_USE]       =           m_mbaddrspace[SYS_PROC3_USE] =              psp.m_proc3_use;
    logBuf[LOG_PROC_USE]       =            m_mbaddrspace[SYS_PROC_USE] =               psp.m_proc_use;
    logBuf[LOG_MAIN_POLARY] =				m_mbaddrspace[SYS_MAIN1_POLARY] =			psp.m_polary[0];
    logBuf[LOG_MAIN2_POLARY] =				m_mbaddrspace[SYS_MAIN2_POLARY] =			psp.m_polary[0]>>16;
    logBuf[LOG_MAIN3_POLARY] =				m_mbaddrspace[SYS_MAIN3_POLARY] =			psp.m_polary[0]>>32;
    logBuf[LOG_MAIN4_POLARY] =				m_mbaddrspace[SYS_MAIN4_POLARY] =			psp.m_polary[0]>>48;
    logBuf[LOG_EXT1_POLARY] =				m_mbaddrspace[SYS_EXT1_POLARY] =			psp.m_polary[1];
    logBuf[LOG_EXT2_POLARY] =				m_mbaddrspace[SYS_EXT2_POLARY] =			psp.m_polary[2];
    logBuf[LOG_EXT3_POLARY] =				m_mbaddrspace[SYS_EXT3_POLARY] =			psp.m_polary[3];
    logBuf[LOG_EXT4_POLARY] =				m_mbaddrspace[SYS_EXT4_POLARY] =			psp.m_polary[4];
    logBuf[LOG_MAIN_OUTPOLARY] =			m_mbaddrspace[SYS_MAIN1_OUTPOLARY] =		psp.m_outputpolary[0];
    logBuf[LOG_MAIN2_OUTPOLARY] =			m_mbaddrspace[SYS_MAIN2_OUTPOLARY] =		psp.m_outputpolary[0]>>16;
    logBuf[LOG_MAIN3_OUTPOLARY] =			m_mbaddrspace[SYS_MAIN3_OUTPOLARY] =		psp.m_outputpolary[0]>>32;
    logBuf[LOG_MAIN4_OUTPOLARY] =			m_mbaddrspace[SYS_MAIN4_OUTPOLARY] =		psp.m_outputpolary[0]>>48;
    logBuf[LOG_EXT1_OUTPOLARY] =			m_mbaddrspace[SYS_EXT1_OUTPOLARY] =			psp.m_outputpolary[1];
    logBuf[LOG_EXT2_OUTPOLARY] =			m_mbaddrspace[SYS_EXT2_OUTPOLARY] =			psp.m_outputpolary[2];
    logBuf[LOG_EXT3_OUTPOLARY] =			m_mbaddrspace[SYS_EXT3_OUTPOLARY] =			psp.m_outputpolary[3];
    logBuf[LOG_EXT4_OUTPOLARY] =			m_mbaddrspace[SYS_EXT4_OUTPOLARY] =			psp.m_outputpolary[4];
    logBuf[LOG_MAIN_NOALM] =				m_mbaddrspace[SYS_MAIN1_INMOLD_NOALM] =		psp.m_noalm[0];
    logBuf[LOG_MAIN2_NOALM] =				m_mbaddrspace[SYS_MAIN2_INMOLD_NOALM] =		psp.m_noalm[0]>>16;
    logBuf[LOG_MAIN3_NOALM] =				m_mbaddrspace[SYS_MAIN3_INMOLD_NOALM] =		psp.m_noalm[0]>>32;
    logBuf[LOG_MAIN4_NOALM] =				m_mbaddrspace[SYS_MAIN4_INMOLD_NOALM] =		psp.m_noalm[0]>>48;
	logBuf[LOG_EXT1_NOALM] =				m_mbaddrspace[SYS_EXT1_INMOLD_NOALM] =		psp.m_noalm[1];
	logBuf[LOG_EXT2_NOALM] =				m_mbaddrspace[SYS_EXT2_INMOLD_NOALM] =		psp.m_noalm[2];
	logBuf[LOG_EXT3_NOALM] =				m_mbaddrspace[SYS_EXT3_INMOLD_NOALM] =		psp.m_noalm[3];
	logBuf[LOG_EXT4_NOALM] =				m_mbaddrspace[SYS_EXT4_INMOLD_NOALM] =		psp.m_noalm[4];
    logBuf[LOG_MAIN_IGNORE] =				m_mbaddrspace[SYS_MAIN1_IGNORE] =			psp.m_ignore[0];
    logBuf[LOG_MAIN2_IGNORE] =				m_mbaddrspace[SYS_MAIN2_IGNORE] =			psp.m_ignore[0]>>16;
    logBuf[LOG_MAIN3_IGNORE] =				m_mbaddrspace[SYS_MAIN3_IGNORE] =			psp.m_ignore[0]>>32;
    logBuf[LOG_MAIN4_IGNORE] =				m_mbaddrspace[SYS_MAIN4_IGNORE] =			psp.m_ignore[0]>>48;
	logBuf[LOG_EXT1_IGNORE] =				m_mbaddrspace[SYS_EXT1_IGNORE] =			psp.m_ignore[1];
	logBuf[LOG_EXT2_IGNORE] =				m_mbaddrspace[SYS_EXT2_IGNORE] =			psp.m_ignore[2];
	logBuf[LOG_EXT3_IGNORE] =				m_mbaddrspace[SYS_EXT3_IGNORE] =			psp.m_ignore[3];
	logBuf[LOG_EXT4_IGNORE] =				m_mbaddrspace[SYS_EXT4_IGNORE] =			psp.m_ignore[4];
	logBuf[LOG_INTERMOLD_DOWN_USE] =		m_mbaddrspace[SYS_INTERMOLD_DOWN_USE] =		psp.m_imop_dwn_use;
	logBuf[LOG_MID_OPEN_USE] =				m_mbaddrspace[SYS_MID_OPEN_USE] =			psp.m_mid_open_use;
    logBuf[LOG_IP_LOW] =                    m_mbaddrspace[SYS_NET_IP_ADDR_LOW]=         psp.m_ip;
    logBuf[LOG_IP_HIGH] =                   m_mbaddrspace[SYS_NET_IP_ADDR_HIGH]=        psp.m_ip>>16;
    logBuf[LOG_SUBMASK_LOW] =               m_mbaddrspace[SYS_NET_IP_MASK_LOW]=         psp.m_submask;
    logBuf[LOG_SUBMASK_HIGH] =              m_mbaddrspace[SYS_NET_IP_MASK_HIGH]=        psp.m_submask>>16;
    logBuf[LOG_GATEWAY_LOW] =               m_mbaddrspace[SYS_NET_IP_GATE_LOW]=         psp.m_gateway;
    logBuf[LOG_GATEWAY_HIGH] =              m_mbaddrspace[SYS_NET_IP_GATE_HIGH]=        psp.m_gateway>>16;
    logBuf[LOG_OIL_INTERVAL_LOW] =          m_mbaddrspace[SYS_OIL_INTERVAL_LOW] =       psp.m_oil_interval;
    logBuf[LOG_OIL_INTERVAL_HIGH] =         m_mbaddrspace[SYS_OIL_INTERVAL_HIGH] =      psp.m_oil_interval >> 16;
    logBuf[LOG_OIL_TIME_LOW] =              m_mbaddrspace[SYS_OIL_TIME_LOW] =           psp.m_oil_time;
    logBuf[LOG_OIL_TIME_HIGH] =             m_mbaddrspace[SYS_OIL_TIME_HIGH] =          psp.m_oil_time >> 16;
    logBuf[LOG_OIL_USE] =                   m_mbaddrspace[SYS_OIL_USE] =                psp.m_oil_use;
    logBuf[LOG_ROTATE_USE] =                m_mbaddrspace[SYS_ROTATE_USE] =             psp.m_rotate_use;
    logBuf[LOG_RUN_ROTATE_USE] =            m_mbaddrspace[SYS_RUN_ROTATE_USE] =         psp.m_run_rotate_use;
    logBuf[LOG_DOOR_RESET_USE] =            m_mbaddrspace[SYS_DOOR_RESET_USE] =         psp.m_door_reset_use;
    logBuf[LOG_OIL_USE_CTRL] =              m_mbaddrspace[SYS_OIL_USE_CTRL] =           psp.m_oil_ctrl_use;

	logBuf[LOG_SYS_IO_CLR] =				m_mbaddrspace[SYS_IO_CLR] =					psp.m_sys_io_clr;
    logBuf[LOG_VISION1_IP_LOW] =            m_mbaddrspace[SYS_VISION0_IP_LOW]=         psp.m_visionip1;
    logBuf[LOG_VISION1_IP_HIGH] =           m_mbaddrspace[SYS_VISION0_IP_HIGH]=        psp.m_visionip1>>16;
    logBuf[LOG_VISION2_IP_LOW] =            m_mbaddrspace[SYS_VISION1_IP_LOW]=         psp.m_visionip2;
    logBuf[LOG_VISION2_IP_HIGH] =           m_mbaddrspace[SYS_VISION1_IP_HIGH]=        psp.m_visionip2>>16;
    logBuf[LOG_VISION3_IP_LOW] =            m_mbaddrspace[SYS_VISION2_IP_LOW]=         psp.m_visionip3;
    logBuf[LOG_VISION3_IP_HIGH] =           m_mbaddrspace[SYS_VISION2_IP_HIGH]=        psp.m_visionip3>>16;
    logBuf[LOG_VISION4_IP_LOW] =            m_mbaddrspace[SYS_VISION3_IP_LOW]=         psp.m_visionip4;
    logBuf[LOG_VISION4_IP_HIGH] =           m_mbaddrspace[SYS_VISION3_IP_HIGH]=        psp.m_visionip4>>16;
    logBuf[LOG_VISION5_IP_LOW] =            m_mbaddrspace[SYS_VISION4_IP_LOW]=         psp.m_visionip5;
    logBuf[LOG_VISION5_IP_HIGH] =           m_mbaddrspace[SYS_VISION4_IP_HIGH]=        psp.m_visionip5>>16;
    logBuf[LOG_VISION6_IP_LOW] =            m_mbaddrspace[SYS_VISION5_IP_LOW]=         psp.m_visionip6;
    logBuf[LOG_VISION6_IP_HIGH] =           m_mbaddrspace[SYS_VISION5_IP_HIGH]=        psp.m_visionip6>>16;
    logBuf[LOG_VISION7_IP_LOW] =            m_mbaddrspace[SYS_VISION6_IP_LOW]=         psp.m_visionip7;
    logBuf[LOG_VISION7_IP_HIGH] =           m_mbaddrspace[SYS_VISION6_IP_HIGH]=        psp.m_visionip7>>16;
    logBuf[LOG_VISION8_IP_LOW] =            m_mbaddrspace[SYS_VISION7_IP_LOW]=         psp.m_visionip8;
    logBuf[LOG_VISION8_IP_HIGH] =           m_mbaddrspace[SYS_VISION7_IP_HIGH]=        psp.m_visionip8>>16;
    logBuf[LOG_VISION1_PORT] =              m_mbaddrspace[SYS_VISION0_PORT]=           psp.m_vision1port;
    logBuf[LOG_VISION2_PORT] =              m_mbaddrspace[SYS_VISION1_PORT]=           psp.m_vision2port;
    logBuf[LOG_VISION3_PORT] =              m_mbaddrspace[SYS_VISION2_PORT]=           psp.m_vision3port;
    logBuf[LOG_VISION4_PORT] =              m_mbaddrspace[SYS_VISION3_PORT]=           psp.m_vision4port;
    logBuf[LOG_VISION5_PORT] =              m_mbaddrspace[SYS_VISION4_PORT]=           psp.m_vision5port;
    logBuf[LOG_VISION6_PORT] =              m_mbaddrspace[SYS_VISION5_PORT]=           psp.m_vision6port;
    logBuf[LOG_VISION7_PORT] =              m_mbaddrspace[SYS_VISION6_PORT]=           psp.m_vision7port;
    logBuf[LOG_VISION8_PORT] =              m_mbaddrspace[SYS_VISION7_PORT]=           psp.m_vision8port;
    logBuf[LOG_VISION1_TRIGGER] =           m_mbaddrspace[SYS_VISION0_TYPE_TRIGGER] =  psp.m_vision1_trigger;
    logBuf[LOG_VISION2_TRIGGER] =           m_mbaddrspace[SYS_VISION1_TYPE_TRIGGER] =  psp.m_vision2_trigger;
    logBuf[LOG_VISION3_TRIGGER] =           m_mbaddrspace[SYS_VISION2_TYPE_TRIGGER] =  psp.m_vision3_trigger;
    logBuf[LOG_VISION4_TRIGGER] =           m_mbaddrspace[SYS_VISION3_TYPE_TRIGGER] =  psp.m_vision4_trigger;
    logBuf[LOG_VISION5_TRIGGER] =           m_mbaddrspace[SYS_VISION4_TYPE_TRIGGER] =  psp.m_vision5_trigger;
    logBuf[LOG_VISION6_TRIGGER] =           m_mbaddrspace[SYS_VISION5_TYPE_TRIGGER] =  psp.m_vision6_trigger;
    logBuf[LOG_VISION7_TRIGGER] =           m_mbaddrspace[SYS_VISION6_TYPE_TRIGGER] =  psp.m_vision7_trigger;
    logBuf[LOG_VISION8_TRIGGER] =           m_mbaddrspace[SYS_VISION7_TYPE_TRIGGER] =  psp.m_vision8_trigger;
    logBuf[LOG_VISION1_OUTVAR] =            m_mbaddrspace[SYS_VISION0_OUTVAR] =        psp.m_vision1_outvar;
    logBuf[LOG_VISION2_OUTVAR] =            m_mbaddrspace[SYS_VISION1_OUTVAR] =        psp.m_vision2_outvar;
    logBuf[LOG_VISION3_OUTVAR] =            m_mbaddrspace[SYS_VISION2_OUTVAR] =        psp.m_vision3_outvar;
    logBuf[LOG_VISION4_OUTVAR] =            m_mbaddrspace[SYS_VISION3_OUTVAR] =        psp.m_vision4_outvar;
    logBuf[LOG_VISION5_OUTVAR] =            m_mbaddrspace[SYS_VISION4_OUTVAR] =        psp.m_vision5_outvar;
    logBuf[LOG_VISION6_OUTVAR] =            m_mbaddrspace[SYS_VISION5_OUTVAR] =        psp.m_vision6_outvar;
    logBuf[LOG_VISION7_OUTVAR] =            m_mbaddrspace[SYS_VISION6_OUTVAR] =        psp.m_vision7_outvar;
    logBuf[LOG_VISION8_OUTVAR] =            m_mbaddrspace[SYS_VISION7_OUTVAR] =        psp.m_vision8_outvar;

	// 参数修改标志
	logBuf[LOG_SYSPAR_MOFIGYLL] = modify & 0xFFFF;
	modify >>= 16;
	logBuf[LOG_SYSPAR_MOFIGYLH] = modify & 0xFFFF;
	modify >>= 16;
	logBuf[LOG_SYSPAR_MOFIGYHL] = modify & 0xFFFF;
	modify >>= 16;
	logBuf[LOG_SYSPAR_MOFIGYHH] = modify & 0xFFFF;
#if PENDANT_PROTOCOL
	// 发送数据
    ret =  SendMsg(SYS_ALARM_TIMES, SYS_MOP_ABD_TIME_HIGH, FALSE);
    if (ret == SENDMSG_RET_ACK)
    {
        ret =  SendMsg(SYS_VISION0_IP_LOW, SYS_MAIN4_INMOLD_NOALM, FALSE);
    }
#endif
	if (ret == SENDMSG_RET_ACK)
	{
        emit signal_PhorSrvUseChange();
        emit signal_RverSrvUseChange();
        emit signal_ExtSrvUseChange();
		emit signal_RhorSrvUseChange();
		emit signal_doubleArmChange();
		// 写入系统日志
		xSysLog::AddRecord(SYSLOG_TYPE_SYS, LOG_PAR_SYS, QString(""), QByteArray((char*)logBuf, sizeof(logBuf)));
		xSysLog::SaveChange();
	}
	return ret;
}

// 写入伺服参数
int8_t CMBProtocol::WriteServo(const ServoParameter &psp, quint64 modify)
{
	int8_t ret = SENDMSG_RET_ACK;
    quint32 logBuf[LOG_SRVPAR_SIZE];

	// 引拔轴设置
	m_mbaddrspace[SERVO_MACHINE_MAX_LEN_X] =		psp.m_machine_max_len_x;
	m_mbaddrspace[SERVO_MIN_SAFE_DIS_X_B] =			psp.m_min_safe_dis_x_b;
	// 软件最大行程
    m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_X] =		psp.m_machine_max_len_x;
//    m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_B] =		psp.m_min_safe_dis_x_b;
    m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_Y] =		psp.m_software_max_len_y;
	m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_Z] =		psp.m_software_max_len_z;
	m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_A] =		psp.m_software_max_len_a;
	m_mbaddrspace[SERVO_SOFTWARE_MAX_LEN_C] =		psp.m_software_max_len_c;
	// 原点偏移
	m_mbaddrspace[SERVO_ORIGIN_OFFSET_X] =			psp.m_origin_offset_x;
	m_mbaddrspace[SERVO_ORIGIN_OFFSET_Y] =			psp.m_origin_offset_y;
	m_mbaddrspace[SERVO_ORIGIN_OFFSET_Z] =			psp.m_origin_offset_z;
	m_mbaddrspace[SERVO_ORIGIN_OFFSET_A] =			psp.m_origin_offset_a;
	m_mbaddrspace[SERVO_ORIGIN_OFFSET_B] =			psp.m_origin_offset_b;
	m_mbaddrspace[SERVO_ORIGIN_OFFSET_C] =			psp.m_origin_offset_c;
    // 原点待机点
    m_mbaddrspace[SERVO_HOME_POS_X] = psp.m_home_pos_x;
    m_mbaddrspace[SERVO_HOME_POS_Y] = psp.m_home_pos_y;
    m_mbaddrspace[SERVO_HOME_POS_Z] = psp.m_home_pos_z;
    m_mbaddrspace[SERVO_HOME_POS_A] = psp.m_home_pos_a;
    m_mbaddrspace[SERVO_HOME_POS_B] = psp.m_home_pos_b;
    m_mbaddrspace[SERVO_HOME_POS_C] = psp.m_home_pos_c;
    // 模
    m_mbaddrspace[SERVO_MOD_X] = psp.m_mod_x;
    m_mbaddrspace[SERVO_MOD_Y] = psp.m_mod_y;
    m_mbaddrspace[SERVO_MOD_Z] = psp.m_mod_z;
    m_mbaddrspace[SERVO_MOD_A] = psp.m_mod_a;
    m_mbaddrspace[SERVO_MOD_B] = psp.m_mod_b;
    m_mbaddrspace[SERVO_MOD_C] = psp.m_mod_c;
	// 安全区
	m_mbaddrspace[SERVO_MAX_WAIT_POS_INMOLD_Y] =	psp.m_max_wait_pos_inmold_y;
	m_mbaddrspace[SERVO_MAX_WAIT_POS_INMOLD_A] =	psp.m_max_wait_pos_inmold_a;
    m_mbaddrspace[SERVO_MIN_SAFE_POS_OUTMOLD_Z] =	psp.m_min_safe_pos_outmold_z;
    m_mbaddrspace[SERVO_MAX_SAFE_POS_OUTMOLD_Z] =	psp.m_max_safe_pos_outmold_z;
    m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_Z] =	psp.m_min_safe_pos_inmold_z;
    m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_Z] =	psp.m_max_safe_pos_inmold_z;
    m_mbaddrspace[SERVO_MIN_SAFE_POS_OUTMOLD2_Z] =	psp.m_min_safe_pos_outmold2_z;
    m_mbaddrspace[SERVO_MAX_SAFE_POS_OUTMOLD2_Z] =	psp.m_max_safe_pos_outmold2_z;
	m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_X] =	psp.m_min_safe_pos_inmold_x;
	m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_X] =	psp.m_max_safe_pos_inmold_x;
	m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_B] =	psp.m_min_safe_pos_inmold_b;
    m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_B] =	psp.m_max_safe_pos_inmold_b;
    m_mbaddrspace[SERVO_MIN_A_TRAVE] =	psp.m_min_a_trv;
    m_mbaddrspace[SERVO_MAX_A_TRAVE] =	psp.m_max_a_trv;
    m_mbaddrspace[SERVO_MIN_A_INMOLD] =	psp.m_min_a_inmold;
    m_mbaddrspace[SERVO_MAX_A_INMOLD] =	psp.m_max_a_inmold;
    m_mbaddrspace[SERVO_MIN_SAFE_POS_INMOLD_Z_A] =	psp.m_min_safe_pos_inmold_z_a;
    m_mbaddrspace[SERVO_MAX_SAFE_POS_INMOLD_Z_A] =	psp.m_max_safe_pos_inmold_z_a;

	// 引拔轴设置
	m_mbaddrspace2[SERVO_MACHINE_MAX_LEN_X] =		psp.m_machine_max_len_x >> 16;
	m_mbaddrspace2[SERVO_MIN_SAFE_DIS_X_B] =		psp.m_min_safe_dis_x_b >> 16;
	// 软件最大行程
    m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_X] =		psp.m_machine_max_len_x >> 16;
//    m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_B] =		psp.m_min_safe_dis_x_b >> 16;
    m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_Y] =		psp.m_software_max_len_y >> 16;
	m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_Z] =		psp.m_software_max_len_z >> 16;
	m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_A] =		psp.m_software_max_len_a >> 16;
	m_mbaddrspace2[SERVO_SOFTWARE_MAX_LEN_C] =		psp.m_software_max_len_c >> 16;
	// 原点偏移
//	m_mbaddrspace2[SERVO_ORIGIN_OFFSET_X] =			psp.m_origin_offset_x >> 16;
//	m_mbaddrspace2[SERVO_ORIGIN_OFFSET_Y] =			psp.m_origin_offset_y >> 16;
//	m_mbaddrspace2[SERVO_ORIGIN_OFFSET_Z] =			psp.m_origin_offset_z >> 16;
//	m_mbaddrspace2[SERVO_ORIGIN_OFFSET_A] =			psp.m_origin_offset_a >> 16;
//	m_mbaddrspace2[SERVO_ORIGIN_OFFSET_B] =			psp.m_origin_offset_b >> 16;
//	m_mbaddrspace2[SERVO_ORIGIN_OFFSET_C] =			psp.m_origin_offset_c >> 16;
	// 安全区
	m_mbaddrspace2[SERVO_MAX_WAIT_POS_INMOLD_Y] =	psp.m_max_wait_pos_inmold_y >> 16;
	m_mbaddrspace2[SERVO_MAX_WAIT_POS_INMOLD_A] =	psp.m_max_wait_pos_inmold_a >> 16;
    m_mbaddrspace2[SERVO_MIN_SAFE_POS_OUTMOLD_Z] =	psp.m_min_safe_pos_outmold_z >> 16;
    m_mbaddrspace2[SERVO_MAX_SAFE_POS_OUTMOLD_Z] =	psp.m_max_safe_pos_outmold_z >> 16;
    m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_Z] =	psp.m_min_safe_pos_inmold_z >> 16;
    m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_Z] =	psp.m_max_safe_pos_inmold_z >> 16;
    m_mbaddrspace2[SERVO_MIN_SAFE_POS_OUTMOLD2_Z] =	psp.m_min_safe_pos_outmold2_z >> 16;
    m_mbaddrspace2[SERVO_MAX_SAFE_POS_OUTMOLD2_Z] =	psp.m_max_safe_pos_outmold2_z >> 16;
	m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_X] =	psp.m_min_safe_pos_inmold_x >> 16;
	m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_X] =	psp.m_max_safe_pos_inmold_x >> 16;
	m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_B] =	psp.m_min_safe_pos_inmold_b >> 16;
	m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_B] =	psp.m_max_safe_pos_inmold_b >> 16;
    m_mbaddrspace2[SERVO_MIN_A_TRAVE] =     psp.m_min_a_trv >> 16;
    m_mbaddrspace2[SERVO_MAX_A_TRAVE] =     psp.m_max_a_trv >> 16;
    m_mbaddrspace2[SERVO_MIN_A_INMOLD] =	psp.m_min_a_inmold >> 16;
    m_mbaddrspace2[SERVO_MAX_A_INMOLD] =	psp.m_max_a_inmold >> 16;
    m_mbaddrspace2[SERVO_MIN_SAFE_POS_INMOLD_Z_A] =	psp.m_min_safe_pos_inmold_z_a >> 16;
    m_mbaddrspace2[SERVO_MAX_SAFE_POS_INMOLD_Z_A] =	psp.m_max_safe_pos_inmold_z_a >> 16;
    // 原点偏移
    m_mbaddrspace2[SERVO_ORIGIN_OFFSET_X] =			psp.m_origin_offset_x >> 16;
    m_mbaddrspace2[SERVO_ORIGIN_OFFSET_Y] =			psp.m_origin_offset_y >> 16;
    m_mbaddrspace2[SERVO_ORIGIN_OFFSET_Z] =			psp.m_origin_offset_z >> 16;
    m_mbaddrspace2[SERVO_ORIGIN_OFFSET_A] =			psp.m_origin_offset_a >> 16;
    m_mbaddrspace2[SERVO_ORIGIN_OFFSET_B] =			psp.m_origin_offset_b >> 16;
    m_mbaddrspace2[SERVO_ORIGIN_OFFSET_C] =			psp.m_origin_offset_c >> 16;
    // 原点待机点
    m_mbaddrspace2[SERVO_HOME_POS_X] = psp.m_home_pos_x >> 16;
    m_mbaddrspace2[SERVO_HOME_POS_Y] = psp.m_home_pos_y >> 16;
    m_mbaddrspace2[SERVO_HOME_POS_Z] = psp.m_home_pos_z >> 16;
    m_mbaddrspace2[SERVO_HOME_POS_A] = psp.m_home_pos_a >> 16;
    m_mbaddrspace2[SERVO_HOME_POS_B] = psp.m_home_pos_b >> 16;
    m_mbaddrspace2[SERVO_HOME_POS_C] = psp.m_home_pos_c >> 16;
    // 模
    m_mbaddrspace2[SERVO_MOD_X] = psp.m_mod_x >> 16;
    m_mbaddrspace2[SERVO_MOD_Y] = psp.m_mod_y >> 16;
    m_mbaddrspace2[SERVO_MOD_Z] = psp.m_mod_z >> 16;
    m_mbaddrspace2[SERVO_MOD_A] = psp.m_mod_a >> 16;
    m_mbaddrspace2[SERVO_MOD_B] = psp.m_mod_b >> 16;
    m_mbaddrspace2[SERVO_MOD_C] = psp.m_mod_c >> 16;
    // 编码器
    m_mbaddrspace[SERVO_ENCODER_X] = psp.m_encoder_x;
    m_mbaddrspace[SERVO_ENCODER_Y] = psp.m_encoder_y;
    m_mbaddrspace[SERVO_ENCODER_Z] = psp.m_encoder_z;
    m_mbaddrspace[SERVO_ENCODER_A] = psp.m_encoder_a;
    m_mbaddrspace[SERVO_ENCODER_B] = psp.m_encoder_b;
    m_mbaddrspace[SERVO_ENCODER_C] = psp.m_encoder_c;

    m_mbaddrspace[SERVO_MIN_B_TRAVE] =	psp.m_min_b_trave;
    m_mbaddrspace[SERVO_MAX_B_TRAVE] =	psp.m_max_b_trave;
    m_mbaddrspace[SERVO_MIN_C_TRAVE] =	psp.m_min_c_trave;
    m_mbaddrspace[SERVO_MAX_C_TRAVE] =	psp.m_max_c_trave;
    m_mbaddrspace[SERVO_MIN_C_INMOLD] =	psp.m_min_c_inmold;
    m_mbaddrspace[SERVO_MAX_C_INMOLD] =	psp.m_max_c_inmold;
    m_mbaddrspace[SERVO_MIN_X_TRAVE] =	psp.m_min_x_trave;
    m_mbaddrspace[SERVO_MAX_X_TRAVE] =	psp.m_max_x_trave;
    m_mbaddrspace2[SERVO_MIN_B_TRAVE] =	psp.m_min_b_trave >> 16;
    m_mbaddrspace2[SERVO_MAX_B_TRAVE] =	psp.m_max_b_trave >> 16;
    m_mbaddrspace2[SERVO_MIN_C_TRAVE] =	psp.m_min_c_trave >> 16;
    m_mbaddrspace2[SERVO_MAX_C_TRAVE] =	psp.m_max_c_trave >> 16;
    m_mbaddrspace2[SERVO_MIN_C_INMOLD] = psp.m_min_c_inmold >> 16;
    m_mbaddrspace2[SERVO_MAX_C_INMOLD] = psp.m_max_c_inmold >> 16;
    m_mbaddrspace2[SERVO_MIN_X_TRAVE] = psp.m_min_x_trave >> 16;
    m_mbaddrspace2[SERVO_MAX_X_TRAVE] = psp.m_max_x_trave >> 16;

    //伺服驱动器参数
    m_mbaddrspace[SERVO_PA5_X] =  psp.m_pa5_x;
    m_mbaddrspace[SERVO_PA5_Y] =  psp.m_pa5_y;
    m_mbaddrspace[SERVO_PA5_Z] =  psp.m_pa5_z;
    m_mbaddrspace[SERVO_PA5_A] =  psp.m_pa5_a;
    m_mbaddrspace[SERVO_PA5_B] =  psp.m_pa5_b;

    m_mbaddrspace[SERVO_PA6_X] =  psp.m_pa6_x;
    m_mbaddrspace[SERVO_PA6_Y] =  psp.m_pa6_y;
    m_mbaddrspace[SERVO_PA6_Z] =  psp.m_pa6_z;
    m_mbaddrspace[SERVO_PA6_A] =  psp.m_pa6_a;
    m_mbaddrspace[SERVO_PA6_B] =  psp.m_pa6_b;

    m_mbaddrspace[SERVO_PA7_X] =  psp.m_pa7_x;
    m_mbaddrspace[SERVO_PA7_Y] =  psp.m_pa7_y;
    m_mbaddrspace[SERVO_PA7_Z] =  psp.m_pa7_z;
    m_mbaddrspace[SERVO_PA7_A] =  psp.m_pa7_a;
    m_mbaddrspace[SERVO_PA7_B] =  psp.m_pa7_b;

    m_mbaddrspace[SERVO_PA8_X] =  psp.m_pa8_x;
    m_mbaddrspace[SERVO_PA8_Y] =  psp.m_pa8_y;
    m_mbaddrspace[SERVO_PA8_Z] =  psp.m_pa8_z;
    m_mbaddrspace[SERVO_PA8_A] =  psp.m_pa8_a;
    m_mbaddrspace[SERVO_PA8_B] =  psp.m_pa8_b;

    m_mbaddrspace[SERVO_PA9_X] =  psp.m_pa9_x;
    m_mbaddrspace[SERVO_PA9_Y] =  psp.m_pa9_y;
    m_mbaddrspace[SERVO_PA9_Z] =  psp.m_pa9_z;
    m_mbaddrspace[SERVO_PA9_A] =  psp.m_pa9_a;
    m_mbaddrspace[SERVO_PA9_B] =  psp.m_pa9_b;

    m_mbaddrspace[SERVO_PA19_X] =  psp.m_pa19_x;
    m_mbaddrspace[SERVO_PA19_Y] =  psp.m_pa19_y;
    m_mbaddrspace[SERVO_PA19_Z] =  psp.m_pa19_z;
    m_mbaddrspace[SERVO_PA19_A] =  psp.m_pa19_a;
    m_mbaddrspace[SERVO_PA19_B] =  psp.m_pa19_b;

    m_mbaddrspace[SERVO_PA63_X] =  psp.m_pa63_x;
    m_mbaddrspace[SERVO_PA63_Y] =  psp.m_pa63_y;
    m_mbaddrspace[SERVO_PA63_Z] =  psp.m_pa63_z;
    m_mbaddrspace[SERVO_PA63_A] =  psp.m_pa63_a;
    m_mbaddrspace[SERVO_PA63_B] =  psp.m_pa63_b;
	// 引拔轴设置
	logBuf[LOG_MACHINE_MAX_LEN_X] = psp.m_machine_max_len_x;
	logBuf[LOG_MIN_SAFE_DIS_X_B] =  psp.m_min_safe_dis_x_b;
	// 软件最大行程
	logBuf[LOG_SOFTWARE_MAX_LEN_Y] = psp.m_software_max_len_y;
	logBuf[LOG_SOFTWARE_MAX_LEN_Z] = psp.m_software_max_len_z;
	logBuf[LOG_SOFTWARE_MAX_LEN_A] = psp.m_software_max_len_a;
	logBuf[LOG_SOFTWARE_MAX_LEN_C] = psp.m_software_max_len_c;
	// 原点偏移
	logBuf[LOG_ORIGIN_OFFSET_X] =	psp.m_origin_offset_x;
	logBuf[LOG_ORIGIN_OFFSET_Y] =	psp.m_origin_offset_y;
	logBuf[LOG_ORIGIN_OFFSET_Z] =	psp.m_origin_offset_z;
	logBuf[LOG_ORIGIN_OFFSET_A] =	psp.m_origin_offset_a;
	logBuf[LOG_ORIGIN_OFFSET_B] =	psp.m_origin_offset_b;
	logBuf[LOG_ORIGIN_OFFSET_C] =	psp.m_origin_offset_c;
    // 原点待机点
    logBuf[LOG_HOME_WAIT_X] = psp.m_home_pos_x;
    logBuf[LOG_HOME_WAIT_Y] = psp.m_home_pos_y;
    logBuf[LOG_HOME_WAIT_Z] = psp.m_home_pos_z;
    logBuf[LOG_HOME_WAIT_A] = psp.m_home_pos_a;
    logBuf[LOG_HOME_WAIT_B] = psp.m_home_pos_b;
    logBuf[LOG_HOME_WAIT_C] = psp.m_home_pos_c;
    // 模
    logBuf[LOG_MOD_X] = psp.m_mod_x;
    logBuf[LOG_MOD_Y] = psp.m_mod_y;
    logBuf[LOG_MOD_Z] = psp.m_mod_z;
    logBuf[LOG_MOD_A] = psp.m_mod_a;
    logBuf[LOG_MOD_B] = psp.m_mod_b;
    logBuf[LOG_MOD_C] = psp.m_mod_c;
    // 编码器
    logBuf[LOG_ENCODER_X] = psp.m_encoder_x;
    logBuf[LOG_ENCODER_Y] = psp.m_encoder_y;
    logBuf[LOG_ENCODER_Z] = psp.m_encoder_z;
    logBuf[LOG_ENCODER_A] = psp.m_encoder_a;
    logBuf[LOG_ENCODER_B] = psp.m_encoder_b;
    logBuf[LOG_ENCODER_C] = psp.m_encoder_c;
	// 安全区
	logBuf[LOG_MAX_WAIT_POS_INMOLD_Y] =	psp.m_max_wait_pos_inmold_y;
	logBuf[LOG_MAX_WAIT_POS_INMOLD_A] =	psp.m_max_wait_pos_inmold_a;    
    logBuf[LOG_MIN_SAFE_POS_OUTMOLD_Z] = psp.m_min_safe_pos_outmold_z;
    logBuf[LOG_MAX_SAFE_POS_OUTMOLD_Z] = psp.m_max_safe_pos_outmold_z;
    logBuf[LOG_MIN_SAFE_POS_INMOLD_Z] =	psp.m_min_safe_pos_inmold_z;
    logBuf[LOG_MAX_SAFE_POS_INMOLD_Z] =	psp.m_max_safe_pos_inmold_z;
    logBuf[LOG_MIN_SAFE_POS_OUTMOLD2_Z] = psp.m_min_safe_pos_outmold2_z;
    logBuf[LOG_MAX_SAFE_POS_OUTMOLD2_Z] = psp.m_max_safe_pos_outmold2_z;
	logBuf[LOG_MIN_SAFE_POS_INMOLD_X] =	psp.m_min_safe_pos_inmold_x;
	logBuf[LOG_MAX_SAFE_POS_INMOLD_X] =	psp.m_max_safe_pos_inmold_x;
	logBuf[LOG_MIN_SAFE_POS_INMOLD_B] =	psp.m_min_safe_pos_inmold_b;
    logBuf[LOG_MAX_SAFE_POS_INMOLD_B] =	psp.m_max_safe_pos_inmold_b;

    logBuf[LOG_MIN_SAFE_ROT] =	psp.m_min_a_trv;
    logBuf[LOG_MAX_SAFE_ROT] =	psp.m_max_a_trv;
    logBuf[LOG_MIN_SAFE_TRV] =	psp.m_min_a_inmold;
    logBuf[LOG_MAX_SAFE_TRV] =	psp.m_max_a_inmold;
    logBuf[LOG_MIN_SAFE_POS_INMOLD_Z_A] =	psp.m_min_safe_pos_inmold_z_a;
    logBuf[LOG_MIN_SAFE_POS_INMOLD_Z_A] =	psp.m_max_safe_pos_inmold_z_a;

    logBuf[LOG_MIN_B_TRAVE] = psp.m_min_b_trave;
    logBuf[LOG_MAX_B_TRAVE] = psp.m_max_b_trave;
    logBuf[LOG_MIN_C_TRAVE] =	psp.m_min_c_trave;
    logBuf[LOG_MAX_C_TRAVE] =	psp.m_max_c_trave;
    logBuf[LOG_MIN_C_INMOLD] = psp.m_min_c_inmold;
    logBuf[LOG_MAX_C_INMOLD] = psp.m_max_c_inmold;
    logBuf[LOG_MIN_X_TRAVE] =	psp.m_min_x_trave;
    logBuf[LOG_MAX_X_TRAVE] =	psp.m_max_x_trave;
   // 正臂引拔轴速度/加速度
	logBuf[LOG_XMAX_SPEED] =						m_mbaddrspace[SERVO_XMAX_SPEED] =				psp.m_xmax_speed;
	logBuf[LOG_XMAX_ACCELERATION] =					m_mbaddrspace[SERVO_XMAX_ACCELERATION] = 		psp.m_xmax_acceleration;
    logBuf[LOG_XMAX_JERK] =             m_mbaddrspace[SERVO_XMAX_JERK] =            psp.m_xmax_jerk;
	// 正臂上下轴速度/加速度
	logBuf[LOG_YMAX_SPEED] =						m_mbaddrspace[SERVO_YMAX_SPEED] =				psp.m_ymax_speed;
	logBuf[LOG_YMAX_ACCELERATION] =					m_mbaddrspace[SERVO_YMAX_ACCELERATION] = 		psp.m_ymax_acceleration;
    logBuf[LOG_YMAX_JERK] =             m_mbaddrspace[SERVO_YMAX_JERK] =            psp.m_ymax_jerk;
	// 横行轴速度/加速度
	logBuf[LOG_ZMAX_SPEED] =						m_mbaddrspace[SERVO_ZMAX_SPEED] =				psp.m_zmax_speed;
	logBuf[LOG_ZMAX_ACCELERATION] =					m_mbaddrspace[SERVO_ZMAX_ACCELERATION] = 		psp.m_zmax_acceleration;
    logBuf[LOG_ZMAX_JERK] =             m_mbaddrspace[SERVO_ZMAX_JERK] =            psp.m_zmax_jerk;
	// 副臂上下轴速度/加速度
	logBuf[LOG_AMAX_SPEED] =						m_mbaddrspace[SERVO_AMAX_SPEED] =				psp.m_amax_speed;
	logBuf[LOG_AMAX_ACCELERATION] =					m_mbaddrspace[SERVO_AMAX_ACCELERATION] = 		psp.m_amax_acceleration;
    logBuf[LOG_AMAX_JERK] =             m_mbaddrspace[SERVO_AMAX_JERK] =            psp.m_amax_jerk;
	// 副臂引拔轴速度/加速度
	logBuf[LOG_BMAX_SPEED] =						m_mbaddrspace[SERVO_BMAX_SPEED] =				psp.m_bmax_speed;
	logBuf[LOG_BMAX_ACCELERATION] =					m_mbaddrspace[SERVO_BMAX_ACCELERATION] = 		psp.m_bmax_acceleration;
    logBuf[LOG_BMAX_JERK] =             m_mbaddrspace[SERVO_BMAX_JERK] =            psp.m_bmax_jerk;
	// 扩展轴速度/加速度
	logBuf[LOG_CMAX_SPEED] =						m_mbaddrspace[SERVO_CMAX_SPEED] =				psp.m_cmax_speed;
	logBuf[LOG_CMAX_ACCELERATION] =					m_mbaddrspace[SERVO_CMAX_ACCELERATION] = 		psp.m_cmax_acceleration;
    logBuf[LOG_CMAX_JERK] =             m_mbaddrspace[SERVO_CMAX_JERK] =            psp.m_cmax_jerk;
    // 马达
    uint32_t tmp;
    tmp = *(uint32_t*)(&psp.m_x_units);
    m_mbaddrspace[SERVO_X_REV_UNITS] =	tmp;
    m_mbaddrspace2[SERVO_X_REV_UNITS] =	tmp >> 16;
    logBuf[LOG_X_UNITS] = *(uint32_t*)(&psp.m_x_units);
    tmp = *(uint32_t*)(&psp.m_x_pluses);
    m_mbaddrspace[SERVO_X_REV_PULSES] =	tmp;
    m_mbaddrspace2[SERVO_X_REV_PULSES] = tmp >> 16;
    logBuf[LOG_X_PLUSES] = *(uint32_t*)(&psp.m_x_pluses);

    tmp = *(uint32_t*)(&psp.m_y_units);
    m_mbaddrspace[SERVO_Y_REV_UNITS] =	tmp;
    m_mbaddrspace2[SERVO_Y_REV_UNITS] =	tmp >> 16;
    logBuf[LOG_Y_UNITS] = *(uint32_t*)(&psp.m_y_units);
    tmp = *(uint32_t*)(&psp.m_y_pluses);
    m_mbaddrspace[SERVO_Y_REV_PULSES] =	tmp;
    m_mbaddrspace2[SERVO_Y_REV_PULSES] = tmp >> 16;
    logBuf[LOG_Y_PLUSES] = *(uint32_t*)(&psp.m_y_pluses);

    tmp = *(uint32_t*)(&psp.m_z_units);
    m_mbaddrspace[SERVO_Z_REV_UNITS] =	tmp;
    m_mbaddrspace2[SERVO_Z_REV_UNITS] =	tmp >> 16;
    logBuf[LOG_Z_UNITS] = *(uint32_t*)(&psp.m_z_units);
    tmp = *(uint32_t*)(&psp.m_z_pluses);
    m_mbaddrspace[SERVO_Z_REV_PULSES] =	tmp;
    m_mbaddrspace2[SERVO_Z_REV_PULSES] = tmp >> 16;
    logBuf[LOG_Z_PLUSES] = *(uint32_t*)(&psp.m_z_pluses);

    tmp = *(uint32_t*)(&psp.m_b_units);
    m_mbaddrspace[SERVO_B_REV_UNITS] =	tmp;
    m_mbaddrspace2[SERVO_B_REV_UNITS] =	tmp >> 16;
    logBuf[LOG_B_UNITS] = *(uint32_t*)(&psp.m_b_units);
    tmp = *(uint32_t*)(&psp.m_b_pluses);
    m_mbaddrspace[SERVO_B_REV_PULSES] =	tmp;
    m_mbaddrspace2[SERVO_B_REV_PULSES] = tmp >> 16;
    logBuf[LOG_B_PLUSES] = *(uint32_t*)(&psp.m_b_pluses);

    tmp = *(uint32_t*)(&psp.m_a_units);
    m_mbaddrspace[SERVO_A_REV_UNITS] =	tmp;
    m_mbaddrspace2[SERVO_A_REV_UNITS] =	tmp >> 16;
    logBuf[LOG_A_UNITS] = *(uint32_t*)(&psp.m_a_units);
    tmp = *(uint32_t*)(&psp.m_a_pluses);
    m_mbaddrspace[SERVO_A_REV_PULSES] =	tmp;
    m_mbaddrspace2[SERVO_A_REV_PULSES] = tmp >> 16;
    logBuf[LOG_A_PLUSES] = *(uint32_t*)(&psp.m_a_pluses);

    tmp = *(uint32_t*)(&psp.m_c_units);
    m_mbaddrspace[SERVO_C_REV_UNITS] =	tmp;
    m_mbaddrspace2[SERVO_C_REV_UNITS] =	tmp >> 16;
    logBuf[LOG_C_UNITS] = *(uint32_t*)(&psp.m_c_units);
    tmp = *(uint32_t*)(&psp.m_c_pluses);
    m_mbaddrspace[SERVO_C_REV_PULSES] =	tmp;
    m_mbaddrspace2[SERVO_C_REV_PULSES] = tmp >> 16;
    logBuf[LOG_C_PLUSES] = *(uint32_t*)(&psp.m_c_pluses);
    // 轴类型
    logBuf[LOG_ANGLE_BMP] = m_mbaddrspace[SERVO_ANGLE_BMP] = psp.m_angle_type;
    // 轴类型
    logBuf[LOG_RAMP_BMP] = m_mbaddrspace[SERVO_RAMP_BMP_HOME_TAIL] = psp.m_dec_type;
    // 原点归位模式
    logBuf[LOG_HOME_MODE] = m_mbaddrspace[SERVO_HOME_MODE] = psp.m_home_mode;

    logBuf[LOG_HOME_VEL] = m_mbaddrspace[SERVO_HOME_VEL] = psp.m_home_vel;
    logBuf[LOG_HOME_VEL_SLOW] = m_mbaddrspace[SERVO_HOME_LOWVEL] = psp.m_home_vel_slow;
    // 参数修改标志
	logBuf[LOG_SRVPAR_MODIFYLL] = modify & 0xFFFF;
	modify >>= 16;
	logBuf[LOG_SRVPAR_MODIFYLH] = modify & 0xFFFF;
	modify >>= 16;
	logBuf[LOG_SRVPAR_MODIFYHL] = modify & 0xFFFF;
	modify >>= 16;
	logBuf[LOG_SRVPAR_MODIFYHH] = modify & 0xFFFF;
#if PENDANT_PROTOCOL
    ret = SendMsg(SERVO_MACHINE_MAX_LEN_X, SERVO_MAX_X_TRAVE, FALSE);
	if (ret == SENDMSG_RET_ACK)
	{
        ret = SendMsg2(SERVO_MACHINE_MAX_LEN_X, SERVO_MAX_X_TRAVE, FALSE);
        ret = SendMsg(SERVO_PA5_X, SERVO_PA63_B, FALSE);
        ret = SendMsg2(SERVO_PA5_X, SERVO_PA5_X, FALSE);
		if (ret == SENDMSG_RET_ACK)
		{
#endif
			// 写入系统日志
			xSysLog::AddRecord(SYSLOG_TYPE_SRV, LOG_PAR_SRV, QString(""), QByteArray((char*)logBuf, sizeof(logBuf)));
			xSysLog::SaveChange();
#if PENDANT_PROTOCOL
		}
	}
#endif
	return ret;
}
// 写入正副臂引拔轴原点距离
int8_t CMBProtocol::WritePaHorMacDistance(uint32_t distance)
{
	int8_t ret = SENDMSG_RET_ACK;
	m_mbaddrspace[SERVO_MACHINE_MAX_LEN_X] = distance;
	m_mbaddrspace2[SERVO_MACHINE_MAX_LEN_X] = distance >> 16;
#if PENDANT_PROTOCOL
	ret = SendMsg(SERVO_MACHINE_MAX_LEN_X, SERVO_MACHINE_MAX_LEN_X, FALSE);
	if (ret == SENDMSG_RET_ACK)
		return SendMsg2(SERVO_MACHINE_MAX_LEN_X, SERVO_MACHINE_MAX_LEN_X, FALSE);
#endif
	return ret;
}
int8_t CMBProtocol::ReadUserVar(int varidx, int counts)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    uint16_t i;
    if ((varidx+counts)> MAX_USER_VARS)
        return SENDMSG_RET_REGADDR_ERR;

    i = 0;
    while (i < counts)
    {
        if (counts >= i + 100)
        {
            ret = SendMsg(INIT_USER_BEG + varidx + i, INIT_USER_BEG + varidx + i + 100 - 1, TRUE);
            if (ret == SENDMSG_RET_ACK)
                return SendMsg2(INIT_USER_BEG + varidx + i, INIT_USER_BEG + varidx + i + 100 - 1, TRUE);
            i += 100;
        }
        else
        {
            ret = SendMsg(INIT_USER_BEG + varidx + i, INIT_USER_BEG + varidx + counts - 1, TRUE);
            if (ret == SENDMSG_RET_ACK)
                return SendMsg2(INIT_USER_BEG + varidx + i, INIT_USER_BEG + varidx + counts - 1, TRUE);
            i = counts;
        }
        if (ret != SENDMSG_RET_ACK)
            break;
    }
#endif
    return ret;

}

int8_t CMBProtocol::WriteUserVar(quint32 *pvalue, int varidx, int counts)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    uint16_t i;
    // 如果变量数量超出了最大值则出错返回
    if ((varidx+counts) > MAX_USER_VARS)
        return SENDMSG_RET_REGADDR_ERR;

     // 写入机器代码
    for (i = 0; i < counts; i++)
    {
        m_mbaddrspace[INIT_USER_BEG + varidx + i] = pvalue[i];
        m_mbaddrspace2[INIT_USER_BEG + varidx + i] = pvalue[i]>>16;
    }
    i = 0;
    while (i < counts)
    {
        if (counts >= i + 100)
        {
            ret = SendMsg(INIT_USER_BEG + varidx + i, INIT_USER_BEG + varidx + i + 100 - 1, FALSE);
            if (ret == SENDMSG_RET_ACK)
                return SendMsg2(INIT_USER_BEG + varidx + i, INIT_USER_BEG + varidx + i + 100 - 1, FALSE);
            i += 100;
        }
        else
        {
            ret = SendMsg(INIT_USER_BEG + varidx + i, INIT_USER_BEG + varidx + counts - 1, FALSE);
            if (ret == SENDMSG_RET_ACK)
                return SendMsg2(INIT_USER_BEG + varidx + i, INIT_USER_BEG + varidx + counts - 1, FALSE);
            i = counts;
        }
        if (ret != SENDMSG_RET_ACK)
            break;
    }
#endif
    return ret;

}

// 写入指定位置和指定数量的机器代码
int8_t CMBProtocol::WriteCodes(quint16 *pcode, const uint16_t startIdx, const uint16_t count)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    uint16_t i;
    // 如果指定的机器代码超出了机器代码对应的寄存器空间则出错返回
    if (count > MAX_CODES)
        return SENDMSG_RET_REGADDR_ERR;
    // 写入机器代码
    for (i = 0; i < count; i++)
        m_mbaddrspace[NEW_CODE_BEG + startIdx + i] = pcode[i];
    i = 0;
    while (i < count)
    {
        if (count >= i + 100)
        {
            ret = SendMsg(NEW_CODE_BEG + startIdx + i, NEW_CODE_BEG + startIdx + i + 100 - 1, FALSE);
            i += 100;
        }
        else
        {
            ret = SendMsg(NEW_CODE_BEG + startIdx + i, NEW_CODE_BEG + startIdx + count - 1, FALSE);
            i = count;
        }
        if (ret != SENDMSG_RET_ACK)
            break;
    }
#endif
    return ret;
}
// 写入指定位置和指定数量的机器代码参数
int8_t CMBProtocol::WriteCodeParas(uint32_t *ppara, const uint16_t startIdx, const uint16_t count)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    uint16_t i;
    // 如果指定的机器代码参数超出了机器代码对应的寄存器空间则出错返回
    if (count > MAX_CODES)
        return SENDMSG_RET_REGADDR_ERR;
    // 写入机器代码参数
    for (i = 0; i < count; i++)
	{
        m_mbaddrspace[NEW_PARA_BEG + startIdx + i] = ppara[i];
        m_mbaddrspace2[NEW_PARA_BEG + startIdx + i] = ppara[i]>>16;
	}
	i = 0;
    while (i < count)
    {
        if (count >= i + 100)
        {
            ret = SendMsg(NEW_PARA_BEG + startIdx + i, NEW_PARA_BEG + startIdx + i + 100 - 1, FALSE);
			if (ret==SENDMSG_RET_ACK)
			{
                ret = SendMsg2(NEW_PARA_BEG + startIdx + i, NEW_PARA_BEG + startIdx + i + 100 - 1, FALSE);
			}
			i += 100;
		}
        else
        {
            ret = SendMsg(NEW_PARA_BEG + startIdx + i, NEW_PARA_BEG + startIdx + count - 1, FALSE);
			if (ret==SENDMSG_RET_ACK)
			{
                ret = SendMsg2(NEW_PARA_BEG + startIdx + i, NEW_PARA_BEG + startIdx + count - 1, FALSE);
			}
			i = count;
	   }
        if (ret != SENDMSG_RET_ACK)
            break;
    }
#endif
    return ret;
}
// 设定系统状态
int8_t CMBProtocol::SetSysState(uint8_t state)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    m_mbaddrspace[SYSTEM_STATE] = state;
	ret = SendMsg(SYSTEM_STATE, SYSTEM_STATE, FALSE);
#endif
	return ret;
}
// 设定运行状态
int8_t CMBProtocol::SetRunState(uint8_t runstate)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    m_mbaddrspace[RUN_STATE] = runstate;
	ret = SendMsg(RUN_STATE, RUN_STATE, FALSE);
#endif
	return ret;
}

int8_t CMBProtocol::SetRunType(uint8_t type)
{
	int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    m_mbaddrspace[RUN_TYPE] = type;
	ret = SendMsg(RUN_TYPE, RUN_TYPE, FALSE);
#endif
	return ret;
}
// ************************************************
// 设置当前程序名称
// ************************************************
/*QString CMBProtocol::GetCurPgmName(void)
{
    if (alfamode)
        return alfaPgmName;
    else
        return curPgmName;
}*/

void CMBProtocol::SetCurPgmName(const QString &name)
{
	if (name.isEmpty())
		return;
/*    if (alfamode)
    {
        if (alfaPgmName != name)
        {
            alfaPgmName = name;
            QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
            settings.setValue(XPAD_SET_ALFAPGM, alfaPgmName);
            settings.sync();
            emit signal_PgmChange(name);
        }
    }
    else*/
    {
        if (curPgmName != name)
        {
            curPgmName = name;
            QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
            settings.setValue(XPAD_SET_CURPGM, curPgmName);
            settings.sync();
#if (FACTORY == FA_JINBOYUE_SPECIAL)
            QFileInfo fileInfo(curPgmName);
            QFile::copy(curPgmName, QDir::currentPath().append("/"TEMP_PATH"/") + fileInfo.baseName() + ".xpgm");
#endif
            emit signal_PgmChange(name);
        }
    }
#if defined(Q_OS_LINUX)
	sync();
#endif
}
void CMBProtocol::SetAlfaPgmName(const QString &name)
{
    if (name.isEmpty())
        return;
    if (alfaPgmName != name)
    {
        alfaPgmName = name;
        QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
        settings.setValue(XPAD_SET_ALFAPGM, alfaPgmName);
        settings.sync();
        emit signal_PgmChange(name);
    }
#if defined(Q_OS_LINUX)
    sync();
#endif
}

bool CMBProtocol::SetALFAMode(bool use)
{
    if (alfamode != use)
    {
        alfamode = use;
        if (alfamode)
            emit signal_PgmChange(alfaPgmName);
        else
            emit signal_PgmChange(curPgmName);
    }
    return true;
}
int CMBProtocol::GetSysType(void)
{
    return sysVersion.m_soft_extra_new;
}

int CMBProtocol::GetSysTypeHigh()
{
    return sysVersion.m_soft_Ecat;
}

bool CMBProtocol::GetProcUse(int procid)
{
    if (procid == 0) return true;
    if (procid == 1) return m_mbaddrspace[SYS_PROC2_USE] != 0;
    if (procid == 2) return m_mbaddrspace[SYS_PROC3_USE] != 0;
    return false;
}
// 得到系统功能支持状态
bool CMBProtocol::GetFunctions(quint64 mask)
{
    return ((m_mbaddrspace[VERSION_SUB_FUN] & mask) | (m_mbaddrspace[VERSION_SUB_FUN2] & (mask >> 16)) | (m_mbaddrspace[VERSION_SUB_FUN3] & (mask >> 32))) != 0;
}

int CMBProtocol::ReadVisionTestData(quint8 visionidx)
{
    int8_t ret = SENDMSG_RET_ACK;
#if PENDANT_PROTOCOL
    ret =  SendMsg(VISION1_MATCH1_DATA1+visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1), VISION1_MATCH3_DATA4+visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1));
    if(ret == SENDMSG_RET_ACK)
        ret =  SendMsg2(VISION1_MATCH1_DATA1+visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1), VISION1_MATCH3_DATA4+visionidx*(VISION1_MATCH3_DATA4-VISION1_MATCH1_DATA1+1));
#endif
    return ret;
}
