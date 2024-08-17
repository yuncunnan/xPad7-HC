#ifndef XSTRINGRESOURCE_H
#define XSTRINGRESOURCE_H

#include <QtGlobal>
#include <QObject>
#include <QVector>
#include <QMap>

// 字符串资源索引
#define STRRES_NO_STRING						0
#define STRRES_WARN_TITLE						1
#define STRRES_SERVO_NO_MANUAL					2
#define STRRES_QUERY_PARA_ERROR					3
#define STRRES_SAVE_PARA_ERROR					4
#define STRRES_SAVETIP							5
#define STRRES_MANUAL							6
#define STRRES_STOP								7
#define STRRES_AUTO								8
#define STRRES_RUN								9
#define STRRES_NO_PERMISSIONS					10
#define STRRES_USRCHG_DENY						11
#define STRRES_NO_CURPGM						12
#define STRRES_HAS_SAVED						13
#define STRRES_MATE_ERROR						14
#define STRRES_SAFESW_TIP						15
#define STRRES_SELSW_STOP						16
#define STRRES_SYSTEM_NO_MANUAL					17
// 报警资源索引
#define ALMRES_NO_ALARM							0
#define ALMRES_EXT_IN							48

class xStringResource : public QObject
{
	Q_OBJECT
public:
	explicit xStringResource(QObject *parent = 0);
	~xStringResource();

	static void retranslateRes(quint8 lan);
	static const QString GetString(int idx);
    static const QString GetAlarm(quint32 idx);
    static const QString GetAlarmSolution(quint16 idx);
    static const QString GetType(quint8 id);
	static const QString GetVarName(quint16 var);
    static const QString GetUserVarName(quint16 var);
	static const QString GetUsrName(quint8 user);
	static const QString GetLogString(quint16 value);
	static const QString GetSysStateString(quint8 value);
    static const QString GetModifyPortName(quint16 var);
    static const QString GetEtherCATErrorName(quint16 var);
    static QString GetLanString();

protected:
	void changeEvent(QEvent *e);

private:
	static QVector<QString> StringResource;			// 系统字符串资源
    static QVector<QString> AlarmResource;			// 系统报警字符串资源
    static QVector<QString> AlarmSolutionResource;	// 系统报警说明字符串资源
    static QMap<quint8, QString> sysType;			// 系统类型字符串资源
	static QMap<quint16, QString> inputVarName;		// 输入变量名字符串资源
    static QMap<quint16, QString> inputModifyVarName;		//修改的输入变量名字符串资源
	static QMap<quint16, QString> outputVarName;	// 输出变量名字符串资源
    static QMap<quint16, QString> outputModifyVarName;	// 修改的输出变量名字符串资源
	static QVector<QString> logString;				// 日志记录字符串资源
    static QMap<quint16, QString> EtherCATErrorName;	// Ecat总线错误内容字符串资源
    static QVector<QString> DvsErrorName;			// 六轴驱控一体总线错误内容字符串资源
    static QVector<QString> HCFAErrorName;			// 禾川驱控一体总线错误内容字符串资源

	static void initSysTypeRes(void);				// 初始化系统类型字符串资源
	static void initStringRes(void);				// 初始化系统通用字符串资源
    static void initAlarmRes(void);					// 初始化系统报警字符串资源
    static void initAlarmSolutionRes(void);			// 初始化系统报警说明字符串资源
    static void initIoVarRes(quint8 lan);			// 初始化IO变量名字字符串资源
    static void ReadModifyPortName(quint8 lan);		// 得到修改的端口名称字符串资源
	static void initLogString(void);
    static void initECatERRRes(void);				// 初始化Ecat总线错误内容字符串资源
    static void initDvsERRRes(void);				// 初始化六轴驱控一体总线错误内容字符串资源
    static void initHCFAERRRes(void);				// 初始化禾川驱控一体总线错误内容字符串资源

signals:
	
public slots:
	
};

#endif // XSTRINGRESOURCE_H
