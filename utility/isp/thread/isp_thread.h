#ifndef ISP_THREAD_H
#define ISP_THREAD_H

#include <QThread>
#include <QUdpSocket>
#include "qextserialport.h"

#define SOFT_VERSION               "V2.15"
typedef enum
{
    PROGRAM_MODE,
    RUN_MODE
} TARGET_MODE;

typedef struct
{
    quint32 m_flag1;
    quint32 m_type;
    quint32 m_size;
    quint32 m_uid1;
    quint32 m_uid2;
    quint32 m_uid3;
    quint32 m_flag2;
}
APP_INFO_BLOCK;

class ISP_thread : public QThread
{
    Q_OBJECT

private:
    QUdpSocket m_udpSocket; //网络烧写类
    QextSerialPort m_serial;//串口烧写类
    BaudRateType m_bandrate;//串口烧写的波特率
    QString m_serial_port;  //串口烧写的端口号
    QString m_filename;     //被烧写的文件名
    QString m_serverip;     //设备的IP地址
    quint16 m_eth_port;     //网络烧写的端口号
    bool m_eth_burn;        //通过网络烧写
    ///////////////////////////////////////////////////////////////////
    int m_check_retry;      //检测次数，发送？字符串的次数
    bool m_need_boot_ver;   //需要发送BOOTVER命令
    bool m_need_fast_cmd;   //需要发送FAST命令才能进入FastIsp，NXP4337的芯片需要
    bool m_need_check_mark; //FastIsp需要检测主板的MARK标志，STM32的芯片不用检测
    bool m_need_select_bank;//FastIsp需要选择BANK命令，NXP4337的芯片需要
    bool m_istestprogram;   //测试程序标志
    bool m_newbootloader;   //stm32新bootloader
    quint8 m_DetectType;    //0表示外部没有检测；1表示外部检测为NXP_ISP；2表示外部检测为NEW Bootloader
    int m_DetectedDevice;   //设备索引 如果m_newbootloader为0，设备从m_DetectedDevice判断，如果m_newbootloader为1，m_DetectedDevice为0
    quint32 m_uid1, m_uid2, m_uid3;
    quint32 m_dev_appbase;  //设备需要的应用程序基址
    quint32 m_dev_apptype; //如果m_newbootloader为1，设备从m_apptype和m_appbase判断
    ///////////////////////////////////////////////////////////////////
    QByteArray m_BinaryContent;
    quint32 m_appbase;      //应用程序基址
    QString m_whatareyou;   //测试用
    ///////////////////////////////////////////////////////////////////
    void SaveUID(char* buf);
    void GetAPPInfo(char* buf);
    bool IsTestProgramARM7(void);
    bool IsTestProgramCortexM(void);

    ///////////////////////////////////////////////////////////////////
    void ResetTarget(TARGET_MODE mode);
    int SendAndVerify(const char *Command, char *AnswerBuffer, int AnswerLength, unsigned timeout = 2000);
    ///////////////////////////////////////////////////////////////////
    int OpenCommunication(void);    //开打通讯
    int ClearCommunication(void);   //清除通讯缓冲
    int SendString(const char *str);//发送字符串
    int SendBuffer(const char *buf, int len);//发送buffer
    int Receive(char *preceive, quint32 maxsize, ulong *realsize, quint32 want = 1, quint32 timeout = 2000);//接收指定数量数据，阻塞式的
    int ReceiveNr0x0A(char *preceive, quint32 maxsize, ulong *realsize, quint32 WantedNr0x0A, quint32 timeout = 2000);//接收指定行数的数据，阻塞式的
    int CloseCommunication(void);   //关闭通讯

    ///////////////////////////////////////////////////////////////////
    int DetectChip(void);           //检测芯片，如果是新bootloader查询UID
    int CheckImage(void);           //检查平台和映像是否一致，调整为4字节对齐长度并加入CRC32长度
    int EraseChip(void);            //擦除芯片对应区域
    int DownIAPPrg(void);           //为NXP的bootloader下载快速IAP烧写程序
    int FastISP();                  //快速下载
    bool NeedRetry(void);

public:
    QString GetError(int err);
    unsigned long GetTick();
public:
    explicit ISP_thread(QObject *parent = 0);
    void InitISP_Serial(QString port, BaudRateType bandrate, QString file, quint8 DetectType = 0);
    void InitISP_Ethernet(QString serverip, quint16 port, QString file, quint8 DetectType = 0);

protected:
    void run();

signals:
    void ChangePercent(int percent);
    void EnableControl(bool enable);
    void FindDevice(QString dev);
    void FindMessage(QString msg);
    void FindBootVer(unsigned int ver);
    void UpdateTime(unsigned int t);
    void DialogMessage(QString msg);
    void ProgramFinished(bool fail);
};

#endif // ISP_THREAD_H
