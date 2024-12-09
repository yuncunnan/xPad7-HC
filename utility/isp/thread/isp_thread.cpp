#include "isp_thread.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include <time.h>
#include "stm32_crc32.h"
#include "crc16.h"
#include "chexbin.h"
#include "errtype.h"
#include "lpcprog.h"

extern unsigned char FastIAP_LPC2XXX_Code[];
extern unsigned char FastIAP_LPC43XX_Code[];
extern unsigned long GetLPC43XXCodeLen(void);
extern quint8 GetLPC43XXCode(quint32 offset);
extern unsigned long GetLPC2XXXCodeLen(void);
extern quint8 GetLPC2XXXCode(quint32 offset);

/***************************** NXP Download *********************************/
/**  Download the file from the internal memory image to the NXP microcontroller.
*/
unsigned long ISP_thread::GetTick()
{
#if defined(Q_WS_WIN)
    return GetTickCount();
#else
    timeval timetmp;
    unsigned long start;
    gettimeofday(&timetmp, NULL);
    start = timetmp.tv_sec*1000;
    start += (timetmp.tv_usec/1000);
    return start;
#endif
}

ISP_thread::ISP_thread(QObject *parent) :
    QThread(parent)
{
}

void ISP_thread::InitISP_Ethernet(QString serverip, quint16 port, QString file, quint8 DetectType)
{
    m_serverip = serverip;
    m_eth_port = port;
    m_filename = file;
    m_eth_burn = true;
    m_check_retry = 5;
    m_DetectType = DetectType;
}

void ISP_thread::InitISP_Serial(QString port, BaudRateType bandrate, QString file, quint8 DetectType)
{
    m_serial_port = port;
    m_bandrate = bandrate;
    m_filename = file;
    m_eth_burn = false;
    m_check_retry = 5;
    m_DetectType = DetectType;
}

//判断是不是测试程序
bool ISP_thread::IsTestProgramARM7(void)//判断ARM7程序是不是测试程序
{
    unsigned long testflag;
    testflag = m_BinaryContent[0x17];
    testflag <<= 8;
    testflag |= m_BinaryContent[0x16];
    testflag <<= 8;
    testflag |= m_BinaryContent[0x15];
    testflag <<= 8;
    testflag |= m_BinaryContent[0x14];
    if (testflag==0x20061003) return true;
    return false;
}

bool ISP_thread::IsTestProgramCortexM(void)//判断CortexM程序是不是测试程序
{
    APP_INFO_BLOCK * pappinfoblock = (APP_INFO_BLOCK*)(m_BinaryContent.data()+0x1000);
    if ((pappinfoblock->m_flag1==0x51FA1BF0)&&(pappinfoblock->m_flag2==0x51FA1BF0))
    {
        if ((pappinfoblock->m_type & 0x0000FF00) == 0x0000FF00)	// 剔除测试程序
            return true;
    }
    return false;
}

void ISP_thread::run()
{
    CHexBin hexbin;
    time_t tStartUpload=0;
    int ret;

    emit EnableControl(false);
    tStartUpload = time(NULL);

    //Hex文件转换为Bin文件
    emit FindMessage(tr("文件转换..."));
    ret = hexbin.Hex2Bin(m_filename);
    if (ret)
    {
        emit FindMessage(tr("文件转换...错误"));
        goto error_open;
    }

    m_BinaryContent = hexbin.GetDataBuffer();
    m_appbase = hexbin.GetBaseAddress();
    //判断是不是测试程序
    m_istestprogram = IsTestProgramARM7();//ARM7 LPC2xxx芯片测试程序判断
    qDebug() << "hex base address: 0x" << QString::number((uint)hexbin.GetBaseAddress(), 16);
    qDebug() << "bin file length: " << QString::number(m_BinaryContent.size());
    if (!m_istestprogram)
        m_istestprogram = IsTestProgramCortexM();//CortexM芯片测试程序判断

    ///////////////////////////////////////////////
    emit FindMessage(tr("打开端口..."));
    ret = OpenCommunication();
    if (ret)
    {
        emit FindMessage(tr("打开端口...错误"));
        goto error_open;
    }

    //test begin
//    int i;
//    int len;
//    char buf[1024];
//    for (i=0; i<1024; i++) buf[i] = i;
//    for (i=0; i<10000; i++)
//    {
//        m_udpSocket->writeDatagram(buf, 1024, QHostAddress(m_serverip), m_eth_port);
//        while (!m_udpSocket->hasPendingDatagrams());
//        len = m_udpSocket->readDatagram(buf, 1024);
//    }
    //test end
    //检测设备，对新bootloader查询UID
    emit FindMessage(tr("检测芯片..."));
    ret = DetectChip();
    if (ret)
    {
        emit FindMessage(tr("检测芯片...错误"));
        goto error_open;
    }

    if (m_newbootloader)
        qDebug() << "NXP bootloader, chip: " << m_whatareyou;
    else
        qDebug() << "NXP bootloader, chip: " << GetChipString(m_DetectedDevice);

    //检查程序和设备的类型及地址是否一致
    //并对Bin映像进行调整，对齐，加UID，加CRC32等
    emit FindMessage(tr("检测程序..."));
    ret = CheckImage();
    if (ret)
    {
        emit FindMessage(tr("检测程序...错误"));
        goto error_open;
    }

    //擦除芯片
    emit FindMessage(tr("擦除芯片..."));
    ret = EraseChip();
    if (ret)
    {
        emit FindMessage(tr("擦除芯片...错误"));
        goto error_open;
    }

    //为NXP的bootloader下载IAP程序并运行，为了快速烧写
    emit FindMessage(tr("程序下载..."));
    if (!m_newbootloader)
    {
        ret = DownIAPPrg();
        if (ret)
        {
            emit FindMessage(tr("程序下载...错误"));
            goto error_open;
        }
    }

    //快速下载程序映像
    ret = FastISP();                //快速下载
    if (ret)
    {
        emit FindMessage(tr("程序下载...错误"));
        goto error_open;
    }

    CloseCommunication();

    //保存HEX到bin文件开始 for测试
    if (0)
    {
        QString binfilename = m_filename.mid(0, m_filename.length()-3);
        binfilename += "bin";
        QFile fbin(binfilename);
        if (fbin.open(QFile::Truncate | QFile::ReadWrite))
        {
            if (m_appbase==0x1A000000)
                m_BinaryContent.resize(0x10000);
            fbin.write(m_BinaryContent);
            fbin.close();
        }
    }
    //保存HEX到bin文件结束

    //界面更新
    emit UpdateTime(time(NULL) - tStartUpload);
    emit EnableControl(true);
    emit ProgramFinished(0);
    emit FindMessage(tr("程序下载...成功"));
    return;

error_open:
    CloseCommunication();
error_no_open:
	emit DialogMessage(GetError(ret));
    emit EnableControl(true);
}

int ISP_thread::SendAndVerify(const char *Command, char *AnswerBuffer, int AnswerLength, unsigned timeout)
{
    unsigned long realsize;
    int cmdlen;

    SendString(Command);
    ReceiveNr0x0A(AnswerBuffer, AnswerLength - 1, &realsize, 2, timeout);
    cmdlen = strlen(Command);
    return (strncmp(AnswerBuffer, Command, cmdlen) == 0 && strcmp(AnswerBuffer + cmdlen, "0\r\n") == 0);
}

void ISP_thread::ResetTarget(TARGET_MODE mode)
{
    switch (mode)
    {
    /* Reset and jump to boot loader. */
    case PROGRAM_MODE:
        m_serial.setDtr();
        m_serial.setRts();
         msleep(10);
        ClearCommunication();
        msleep(10);
        m_serial.setDtr(false);
        msleep(10);
        m_serial.setRts(false);
        break;

    /* Reset and start uploaded program */
    case RUN_MODE:
        m_serial.setDtr();
        m_serial.setRts(false);
        msleep(10);
        ClearCommunication();
        msleep(10);
        m_serial.setDtr(false);
        msleep(10);
        break;
    }
}

int ISP_thread::OpenCommunication(void)//开打通讯
{
    if (m_eth_burn)
    {
        m_udpSocket.bind(m_udpSocket.localAddress(), m_eth_port);
    }
    else
    {
        m_serial.setPortName(m_serial_port);
        m_serial.setBaudRate(m_bandrate);
        m_serial.setFlowControl(FLOW_OFF);
        m_serial.setParity(PAR_NONE);
        m_serial.setDataBits(DATA_8);
        m_serial.setStopBits(STOP_1);
        m_serial.setQueryMode(QextSerialPort::Polling);
        m_serial.setTimeout(1);
        if (!m_serial.open(QIODevice::ReadWrite))
            return ERROR_COM_SERIAL_OPEN;
        //主板进入ISP编程模式
        ResetTarget(PROGRAM_MODE);
    }
    return 0;
}

int ISP_thread::ClearCommunication(void)//清除通讯缓冲
{
     if (m_eth_burn)
    {
        m_udpSocket.flush();
        if (m_udpSocket.hasPendingDatagrams())
        {
            char *buf = new char[m_udpSocket.pendingDatagramSize()];
            m_udpSocket.readDatagram(buf, m_udpSocket.pendingDatagramSize());
            delete buf;
        }
    }
    else
    {
        m_serial.flush();
        m_serial.readAll();
    }
    return 0;
}

int ISP_thread::SendString(const char *str)//发送字符串
{
    if (m_eth_burn)
    {
        m_udpSocket.writeDatagram(str, strlen(str), QHostAddress(m_serverip), m_eth_port);
    }
    else
    {
        m_serial.write(str, strlen(str));
    }
    return 0;
}

int ISP_thread::SendBuffer(const char *buf, int len)//发送buffer
{
    if (m_eth_burn)
    {
        int pos = 0;
        int sendlen;
        while (pos < len)
        {
            sendlen = len-pos;
            if (sendlen>1024) sendlen = 1024;//主板不能接收太大的UDP包，所以大与1024要分多次发送
            m_udpSocket.writeDatagram(buf+pos, sendlen, QHostAddress(m_serverip), m_eth_port);
            pos += sendlen;
            if (pos<len) msleep(10);//两次发送之间要有延时让主板有处理时间
        }
    }
    else
    {
        m_serial.write(buf, len);
    }
    return 0;
}

int ISP_thread::Receive(char *preceive, quint32 maxsize, ulong *realsize, quint32 want, quint32 timeout)//接收指定数量数据，阻塞式的
{
    unsigned long start;
    unsigned long retry = timeout;
    (*realsize) = 0;
    start = GetTick();
    if (m_eth_burn)
    {
        do
        {
            if (m_udpSocket.hasPendingDatagrams())
            {//网络烧写UDP只收一个包就返回，这个会不会有问题？？
                int len = m_udpSocket.pendingDatagramSize();
                char *buf = new char[len];
                m_udpSocket.readDatagram(buf, len);
                if (len>maxsize)
                {
                    memcpy(preceive, buf, maxsize);
                    (*realsize) = maxsize;
                }
                else
                {
                    memcpy(preceive, buf, len);
                    (*realsize) = len;
                }
                delete buf;
                break;
            }
        } while (((*realsize) < maxsize) && ((start+retry)>GetTick()) && ((*realsize) < want));
    }
    else
    {
        do
        {
            if (m_serial.read((char*)(preceive+(*realsize)), 1))
            {
                (*realsize)++;
            }
        } while (((*realsize) < maxsize) && ((start+retry)>GetTick()) && ((*realsize) < want));
    }

    ((char*)preceive)[(*realsize)] = 0;

	if ((*realsize) >= maxsize) return ERROR_COM_BUFFER_OVER;
    if (((*realsize) < want) && ((start+retry)<GetTick())) return ERROR_COM_RECE_TIMEOUT;

    return 0;
}

int ISP_thread::ReceiveNr0x0A(char *preceive, quint32 maxsize, ulong *realsize, quint32 WantedNr0x0A, quint32 timeout)//接收指定行数的数据，阻塞式的
{
    unsigned long start;
    unsigned long retry = timeout;
    unsigned long nr_of_0x0A = 0;

    (*realsize) = 0;
    start = GetTick();
    if (m_eth_burn)
    {
        do
        {
            if (m_udpSocket.hasPendingDatagrams())
            {//网络烧写UDP只收一个包就返回，这个会不会有问题？？
                int len = m_udpSocket.pendingDatagramSize();
                char *buf = new char[len];
                m_udpSocket.readDatagram(buf, len);
                if (len>maxsize)
                {
                    memcpy(preceive, buf, maxsize);
                    (*realsize) = maxsize;
                }
                else
                {
                    memcpy(preceive, buf, len);
                    (*realsize) = len;
                }
                delete buf;
                break;
            }
        } while (((*realsize) < maxsize) && (nr_of_0x0A < WantedNr0x0A) && ((start+retry)>GetTick()));
    }
    else
    {
        do
        {
            if (m_serial.read((char*)(preceive+(*realsize)), 1))
            {
                if (preceive[(*realsize)] == 0x0a)
                {
                    nr_of_0x0A++;
                }
                (*realsize)++;
            }

        } while (((*realsize) < maxsize) && (nr_of_0x0A < WantedNr0x0A) && ((start+retry)>GetTick()));
    }
    ((char*)preceive)[(*realsize)] = 0;

	if ((*realsize) >= maxsize) return ERROR_COM_BUFFER_OVER;
    if ((nr_of_0x0A < WantedNr0x0A) && ((start+retry)<GetTick())) return ERROR_COM_RECE_TIMEOUT;

    return 0;
}

int ISP_thread::CloseCommunication(void)   //关闭通讯
{
    if (m_eth_burn)
    {
        m_udpSocket.close();
    }
    else
    {
        //设备进入运行模式
        ResetTarget(RUN_MODE);
        m_serial.close();
    }
    return 0;
}

QString ISP_thread::GetError(int err)
{
    QString tmp;
    switch(err)
    {
    case ERROR_HEXBIN_FILEOPEN://   0x1000
        tmp = tr("HEX文件-打开错误");
        break;
    case ERROR_HEXBIN_CRC://        0x1001
        tmp = tr("HEX文件-检验错误");
        break;
    case ERROR_HEXBIN_LINE://       0x1002
        tmp = tr("HEX文件-行长度错误");
        break;

    case ERROR_DETECT_NOFOUND://    0x2000
        tmp = tr("检测-没有发现支持的设备");
        break;
    case ERROR_DETECT_NOSYNC://     0x2001
        tmp = tr("检测-设备不能同步");
        break;
    case ERROR_DETECT_NOOCS://      0x2002
        tmp = tr("检测-设置OSC错误");
        break;
    case ERROR_DETECT_NOBOOTVER://  0x2003
        tmp = tr("检测-读Boot版本错误");
        break;
    case ERROR_DETECT_NOPARTID://   0x2004
        tmp = tr("检测-读Partid错误");
        break;
    case ERROR_DETECT_UNKNOWN://    0x2005
        tmp = tr("检测-设备不支持");
        break;

    case ERROR_COM_SERIAL_OPEN://   0x3000
        tmp = tr("通讯-打开串口错误");
        break;
    case ERROR_COM_ETHERNET_OPEN:// 0x3001
        tmp = tr("通讯-打开网络错误");
        break;
    case ERROR_COM_RECE_TIMEOUT://  0x3002
        tmp = tr("通讯-接收超时");
        break;
    case ERROR_COM_BUFFER_OVER://   0x3003
        tmp = tr("通讯-接收缓冲溢出");
        break;

    case ERROR_DOWNIAP_UNSUPPORT:// 0x4000
        tmp = tr("下载IAP-不支持本设备");
        break;
    case ERROR_DOWNIAP_CRC://       0x4001
        tmp = tr("下载IAP-错误CRC");
        break;
    case ERROR_DOWNIAP_CRC2://      0x4002
        tmp = tr("下载IAP-错误CRC2");
        break;

    case ERROR_NXPISP_UNLOCK://     0x7000
        tmp = tr("NXPISP-设备解锁错误");
        break;
    case ERROR_NXPISP_WRITE://      0x7001
        tmp = tr("NXPISP-设备写错误");
        break;
    case ERROR_NXPISP_PREPARE://    0x7002
        tmp = tr("NXPISP-设备准备错误");
        break;
    case ERROR_NXPISP_ERASE://      0x7003
        tmp = tr("NXPISP-设备擦除错误");
        break;
    case ERROR_NEWISP_ERASE://      0x7004
        tmp = tr("NEWISP-设备擦除错误");
        break;

    case ERROR_CHECK_UNMATCH1://    0x5000
        tmp = tr("检查-这个程序需要V5.X硬件版本，但操作器硬件不是V5.X");
        break;
    case ERROR_CHECK_UNMATCH2://    0x5001
        tmp = tr("检查-这个程序需要V4.X及以下硬件版本，但操作器硬件是V5.X");
        break;
    case ERROR_CHECK_UNMATCH3://    0x5002
        tmp = tr("检查-平台和程序类型不匹配，这个程序不能在此平台运行");
        break;
    case ERROR_CHECK_INTERNAL://    0x5003
        tmp = tr("检查-内部错误");
        break;

//    case ERROR_FAST_NOTEST://       0x6000
//        tmp = tr("快速下载-设备没有测试");
//        break;
    case ERROR_FAST_SETBANK://      0x6001
        tmp = tr("快速下载-设置BANK错误");
        break;
    case ERROR_FAST_SETADDR://      0x6002
        tmp = tr("快速下载-设置地址长度错误");
        break;
    case ERROR_FAST_SETDATA://      0x6003
        tmp = tr("快速下载-数据错误");
        break;
    }

    return tmp;
}

void ISP_thread::SaveUID(char* buf)//根据应答字符串取出UID
{
    if (strlen(buf)>24)
    {
        buf[24] = 0;
        m_uid1 = strtoul(buf+16, NULL, 16);
        buf[16] = 0;
        m_uid2 = strtoul(buf+8, NULL, 16);
        buf[8] = 0;
        m_uid3 = strtoul(buf, NULL, 16);
    }
}

void ISP_thread::GetAPPInfo(char* buf)//根据应答字符串取出应用类型和基址
{
    if (strlen(buf)>32)
    {
        buf[31] = 0;
        m_dev_apptype = strtoul(buf+23, NULL, 16);
        buf[21] = 0;
        m_dev_appbase = strtoul(buf+13, NULL, 16);
    }
}

int ISP_thread::DownIAPPrg(void)//为LPC2XXX芯片下载IAP快速烧写代码
{
    unsigned long realsize;
    char Answer[128];
    char tmpString[128];
    char uuencode_table[64];
    int Line;
    unsigned long tmpStringPos;
    unsigned long BlockOffset;
    unsigned long Block;
    unsigned long Pos;
    unsigned long CopyLength;
    int k=0,i;
    unsigned char c;
    unsigned long block_CRC;

    int repeat = 0;
    // Puffer for data to resend after "RESEND\r\n" Target responce
    char sendbuf0[128];
    char sendbuf1[128];
    char sendbuf2[128];
    char sendbuf3[128];
    char sendbuf4[128];
    char sendbuf5[128];
    char sendbuf6[128];
    char sendbuf7[128];
    char sendbuf8[128];
    char sendbuf9[128];
    char sendbuf10[128];
    char sendbuf11[128];
    char sendbuf12[128];
    char sendbuf13[128];
    char sendbuf14[128];
    char sendbuf15[128];
    char sendbuf16[128];
    char sendbuf17[128];
    char sendbuf18[128];
    char sendbuf19[128];

    char * sendbuf[20] = {
                            sendbuf0,  sendbuf1,  sendbuf2,  sendbuf3,  sendbuf4,
                            sendbuf5,  sendbuf6,  sendbuf7,  sendbuf8,  sendbuf9,
                            sendbuf10, sendbuf11, sendbuf12, sendbuf13, sendbuf14,
                            sendbuf15, sendbuf16, sendbuf17, sendbuf18, sendbuf19
                         };

    if(GetChipVariant(m_DetectedDevice) != CHIP_VARIANT_LPC2XXX &&
       GetChipVariant(m_DetectedDevice) != CHIP_VARIANT_LPC43XX)
    {
        return ERROR_DOWNIAP_UNSUPPORT;
    }
    // Build up uuencode table
    uuencode_table[0] = 0x60;           // 0x20 is translated to 0x60 !

    for (i = 1; i < 64; i++)
    {
        uuencode_table[i] = (char)(0x20 + i);
    }

    ClearCommunication();
    ///////////////////////////////////////////////////////////////////////////////////
    block_CRC = 0;
    Line = 0;
    if (GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC43XX)
        CopyLength = GetLPC43XXCodeLen();//sizeof(Fast_LPC43_Code);
    else
        CopyLength = GetLPC2XXXCodeLen();
    if ((CopyLength % (45 * 4)) != 0)
    {
        CopyLength += ((45 * 4) - (CopyLength % (45 * 4)));
    }

    if (!SendAndVerify("U 23130\r\n", Answer, sizeof Answer)) return ERROR_NXPISP_UNLOCK;

    if (GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC43XX)
        sprintf(tmpString, "W 268436224 %lu\r\n", CopyLength);//0x10000300
    else
        sprintf(tmpString, "W 1073742592 %lu\r\n", CopyLength);//0x40000300

    if (!SendAndVerify(tmpString, Answer, sizeof Answer)) return ERROR_NXPISP_WRITE;

    for (Pos = 0; Pos < CopyLength; Pos += (45 * 4))
    {
        for (Block = 0; Block < 4; Block++)  // Each block 45 bytes
        {
            // Uuencode one 45 byte block
            tmpStringPos = 0;

            sendbuf[Line][tmpStringPos++] = (char)(' ' + 45);    // Encode Length of block

            for (BlockOffset = 0; BlockOffset < 45; BlockOffset++)
            {
                if (GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC43XX)
                    c = GetLPC43XXCode(Pos + Block * 45 + BlockOffset);//Fast_LPC43_Code[Pos + Block * 45 + BlockOffset];
                else
                    c = GetLPC2XXXCode(Pos + Block * 45 + BlockOffset);

                block_CRC += c;

                k = (k << 8) + (c & 255);

                if ((BlockOffset % 3) == 2)   // Collecting always 3 Bytes, then do processing in 4 Bytes
                {
                    sendbuf[Line][tmpStringPos++] = uuencode_table[(k >> 18) & 63];
                    sendbuf[Line][tmpStringPos++] = uuencode_table[(k >> 12) & 63];
                    sendbuf[Line][tmpStringPos++] = uuencode_table[(k >>  6) & 63];
                    sendbuf[Line][tmpStringPos++] = uuencode_table[ k        & 63];
                }
            }

            sendbuf[Line][tmpStringPos++] = '\r';
            sendbuf[Line][tmpStringPos++] = '\n';
            sendbuf[Line][tmpStringPos++] = 0;

            ClearCommunication();
            SendString(sendbuf[Line]);
            // receive only for debug proposes
            ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 1);
            Line++;

            if (Line == 20)
            {
                for (repeat = 0; repeat < 3; repeat++)
                {

                    sprintf(tmpString, "%lu\r\n", block_CRC);

                    ClearCommunication();
                    SendString(tmpString);

                    ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 2);

                    sprintf(tmpString, "%lu\r\nOK\r\n", block_CRC);

                    if (strcmp(Answer, tmpString) != 0)
                    {
                        for (i = 0; i < Line; i++)
                        {
                            SendString(sendbuf[i]);
                            ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 1);
                        }
                    }
                    else
                        break;
                }

                if (repeat >= 3)return ERROR_DOWNIAP_CRC;
                Line = 0;
                block_CRC = 0;
            }
        }
    }
    if (Line != 0)
    {
        for (repeat = 0; repeat < 3; repeat++)
        {
            sprintf(tmpString, "%lu\r\n", block_CRC);

            ClearCommunication();
            SendString(tmpString);

            ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 2);

            sprintf(tmpString, "%lu\r\nOK\r\n", block_CRC);

            if (strcmp(Answer, tmpString) != 0)
            {
                for (i = 0; i < Line; i++)
                {
                    SendString(sendbuf[i]);
                    ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 1);
                }
            }
            else
               break;
        }

        if (repeat >= 3)return (ERROR_DOWNIAP_CRC2);
    }

    if (GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC43XX)
        sprintf(tmpString, "G 268436656 T\r\n");//0x100004B0
    else
        sprintf(tmpString, "G 1073742592 A\r\n");//0x40000300

    SendString(tmpString); //goto 0 : run this fresh new downloaded code code
    ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 2);

    return 0;
}

int ISP_thread::DetectChip(void)
{
    unsigned long realsize;
    unsigned long Pos;
    char Answer[128];
    char *strippedAnswer, *endPtr;
    int  strippedsize;
    int nQuestionMarks;
    int found;

    //清除串口缓存
    ClearCommunication();
    if (m_DetectType == 0)//从头开始发?查询芯片，NXP的bootloader会发回Synchronized\r\n，我们自己的bootloader会发回Synchronized-Sinrobot\r\n
    {
        for (nQuestionMarks = found = 0; (!found) && (nQuestionMarks < m_check_retry); nQuestionMarks++)
        {
            SendString("?");

            memset(Answer,0,sizeof(Answer));
            ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 1);

            strippedAnswer = Answer;
            strippedsize = realsize;

            while ((strippedsize > 0) && ((*strippedAnswer == '?') || (*strippedAnswer == 0)))
            {
                strippedAnswer++;
                strippedsize--;
            }
            if ((strcmp(strippedAnswer, "Synchronized\r\n") == 0)||
                (strcmp(strippedAnswer, "Synchronized-Sinrobot\r\n") == 0))
                found = 1;
        }
    }
    else
    if (m_DetectType == 1)//?由外部程序发送，且是NXP的bootloader
    {
        strippedAnswer = Answer;
        sprintf(strippedAnswer, "Synchronized\r\n");
        found = 1;
    }
    else//?由外部程序发送，且是我们自己的New bootloader
    {
        strippedAnswer = Answer;
        sprintf(strippedAnswer, "Synchronized-Sinrobot\r\n");
        found = 1;
    }
    if (!found) return ERROR_DETECT_NOFOUND;

    m_need_check_mark = true;//需要检查芯片MARK标志
    if (m_istestprogram) m_need_check_mark = false;//测试程序不需要检查芯片MARK标志

    m_need_select_bank = false;//不需要选择芯片BANK
    m_need_fast_cmd = false;//不需要发送FAST命令进入快速烧写

    m_need_boot_ver = true;
    //for nxp bootloader
    if (strcmp(strippedAnswer, "Synchronized\r\n") == 0)
    {
        m_newbootloader = false;
        SendString("Synchronized\r\n");
        ReceiveNr0x0A(Answer, sizeof(Answer) - 1, &realsize, 2);
        if (strcmp(Answer, "Synchronized\r\nOK\r\n") != 0) return ERROR_DETECT_NOSYNC;

        SendString("12000\r\n");
        ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 2);
        if (strcmp(Answer, "12000\r\nOK\r\n") != 0) return ERROR_DETECT_NOOCS;

        if (m_need_boot_ver)
        {
            SendString("K\r\n");
            ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 4);
            if (strncmp(Answer, "K\r\n", strlen("K\r\n")) != 0) return ERROR_DETECT_NOBOOTVER;
            if (strncmp(Answer + strlen("K\r\n"), "0\r\n", 3) == 0) strippedAnswer = Answer + strlen("K\r\n") + 3;
            strippedAnswer = Answer + 5;

            Pos = strtoul(strippedAnswer, &endPtr, 10);
            endPtr += 2;
            Pos |= strtoul(endPtr, NULL, 10)<<8;
            emit FindBootVer(Pos);
        }

        SendString("J\r\n");
        ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 3);
        if (strncmp(Answer, "J\r\n", strlen("J\r\n")) != 0) return ERROR_DETECT_NOPARTID;
        strippedAnswer = (strncmp(Answer, "J\r\n0\r\n", 5) == 0) ? Answer + 5 : Answer;
        Pos = strtoul(strippedAnswer, &endPtr, 10);
        *endPtr = '\0'; /* delete \r\n */

        emit FindDevice(GetDeviceInfo(Pos, &m_DetectedDevice));
    }
    //for new bootloader
    if (strcmp(strippedAnswer, "Synchronized-Sinrobot\r\n") == 0)
    {
        m_newbootloader = true;
        m_DetectedDevice = 0;
        m_need_boot_ver = false;

        SendString("WhoAreYou\r\n");
        memset(Answer,0,sizeof(Answer));
        ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 3);
        m_whatareyou = Answer;
        GetAPPInfo(Answer);
        Answer[11] = 0;

        switch (m_dev_apptype)
        {
        case 0x80004000://单轴一体机主板 GD32F305VC
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(trUtf8("-单轴一体机主板")));
            break;
        case 0x80000001://六轴主板 LPC4337
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-6轴主板")));
            break;
        case 0x80000002://两轴主板 LPC4337
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-2轴主板")));
            break;
        case 0x80000003://三轴主板 LPC4337
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-3轴主板")));
            break;
        case 0x8000000F://PLC主板 LPC4337
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-PLC主板")));
            break;
        case 0x80009035://六轴主板 STM32H730VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-六轴单总线主板")));
            break;
        case 0x80009045://fivebox主板 STM32H730VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(trUtf8("-5合1主板")));
            break;
        case 0x80005001://六轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-六轴主板")));
            break;
        case 0x80005005://五轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-5轴主板")));
            break;
        case 0x80005011://ECAT六轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-6轴ECAT主板")));
            break;
        case 0x80005012://ECAT二轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-2轴ECAT主板")));
            break;
        case 0x80005013://ECAT三轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-3轴ECAT主板")));
            break;
        case 0x8000501F://ECAT-PLC主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-PLC-ECAT主板")));
            break;
        case 0x80005021://DVS六轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(trUtf8("-6轴DVS主板")));
            break;
        case 0x80005022://DVS二轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(trUtf8("-2轴DVS主板")));
            break;
        case 0x80005023://DVS三轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(trUtf8("-3轴DVS主板")));
            break;
        case 0x8000502F://DVS-PLC主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(trUtf8("-PLC-DVS主板")));
            break;
        case 0x80005031://Canopen六轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(trUtf8("-6轴Canopen主板")));
            break;
        case 0x80005032://Canopen二轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(trUtf8("-2轴Canopen主板")));
            break;
        case 0x80005033://Canopen三轴主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(trUtf8("-3轴Canopen主板")));
            break;
        case 0x8000503F://Canopen-PLC主板 STM32H750VB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(trUtf8("-PLC-Canopen主板")));
            break;
        case 0x0000600F://八寸屏主板 STM32H750XB
            m_need_select_bank = true;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-8寸屏主板")));
            break;
        case 0x80003011://ECAT六轴主板 STM32F427IGH
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-6轴ECAT主板")));
            break;
        case 0x80003012://ECAT两轴主板 STM32F427IGH
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-2轴ECAT主板")));
            break;
        case 0x80003013://ECAT三轴主板 STM32F427IGH
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-3轴ECAT主板")));
            break;
        case 0x8000301F://ECATPLC主板 STM32F427IGH
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-PLC-ECAT主板")));
            break;
case 0x80003001://六轴主板 STM32F427IGH
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-6轴主板")));
            break;
        case 0x80003002://两轴主板 STM32F427IGH
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-2轴主板")));
            break;
        case 0x80003003://三轴主板 STM32F427IGH
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-3轴主板")));
            break;
        case 0x8000300F://PLC主板 STM32F427IGH
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-PLC主板")));
            break;
        case 0x80002001://六轴主板 STM32F407VG
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-6轴主板")));
            break;
        case 0x80002002://两轴主板 STM32F407VG
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-2轴主板")));
            break;
        case 0x80002003://三轴主板 STM32F407VG
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-3轴主板")));
            break;
        case 0x8000200F://PLC主板 STM32F407VG
            m_need_select_bank = false;
            m_need_fast_cmd = true;
            m_need_boot_ver = true;
            emit FindDevice(QString(Answer)+QString(tr("-PLC主板")));
            break;
        case 0x00000001://旋臂512KB操作器
        case 0x00000002://旋臂768KB操作器
        case 0x00000003://旋臂1024KB操作器
            m_need_check_mark = false;
            emit FindDevice(QString(Answer)+QString(tr("-SWING//TRAV操作器")));
            break;
        case 0x00000101://单轴512KB操作器
        case 0x00000102://单轴768KB操作器
        case 0x00000103://单轴1024KB操作器
            m_need_check_mark = false;
            emit FindDevice(QString(Answer)+QString(tr("-单轴操作器")));
            break;
        case 0x00000201://两轴512KB操作器
        case 0x00000202://两轴768KB操作器
        case 0x00000203://两轴1024KB操作器
            m_need_check_mark = false;
            emit FindDevice(QString(Answer)+QString(tr("-两轴操作器")));
            break;
        case 0x00000301://三轴512KB操作器
        case 0x00000302://三轴768KB操作器
        case 0x00000303://三轴1024KB操作器
            m_need_check_mark = false;
            emit FindDevice(QString(Answer)+QString(tr("-三轴操作器")));
            break;
        case 0x00000401://OEM512KB操作器
        case 0x00000402://OEM768KB操作器
        case 0x00000403://OEM1024KB操作器
            m_need_check_mark = false;
            emit FindDevice(QString(Answer)+QString(tr("-非标操作器")));
            break;
        default:
            emit FindDevice(QString(Answer)+QString(("-UNKNOWN")));
            return ERROR_DETECT_UNKNOWN;
        }

        //如果是新bootloader查询UID
        SendString("UID\r\n");
        memset(Answer,0,sizeof(Answer));
        ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 2);
        SaveUID(Answer);

        if (m_need_boot_ver)
        {
            SendString("K\r\n");
            ReceiveNr0x0A(Answer, sizeof(Answer)-1, &realsize, 4);
            if (strncmp(Answer, "K\r\n", strlen("K\r\n")) != 0) return ERROR_DETECT_NOBOOTVER;
            if (strncmp(Answer + strlen("K\r\n"), "0\r\n", 3) == 0) strippedAnswer = Answer + strlen("K\r\n") + 3;
            strippedAnswer = Answer + 5;

            Pos = strtoul(strippedAnswer, &endPtr, 10);
            endPtr += 2;
            Pos |= strtoul(endPtr, NULL, 10)<<8;
            emit FindBootVer(Pos);
        }
    }
    return 0;
}

int ISP_thread::CheckImage(void)
{
    int i;
    quint32 * p;
    unsigned long ivt_CRC;          // CRC over interrupt vector table
    APP_INFO_BLOCK * pappinfoblock;
    if (m_newbootloader)
    {
        //检查平台和映像是否一致
        //新的平台是自己的bootloader，对应的应用程序都有APP_INFO_BLOCK(应用程序信息块)
        pappinfoblock = (APP_INFO_BLOCK*)(m_BinaryContent.data()+0x1000);
        if ((pappinfoblock->m_flag1!=0x51FA1BF0)||(pappinfoblock->m_flag2!=0x51FA1BF0))
            return ERROR_CHECK_UNMATCH2;
        if (m_istestprogram)
            pappinfoblock->m_type = m_dev_apptype;
        if ((pappinfoblock->m_type==0x80001000)&&m_need_select_bank)
        {
            //M0程序不用检查类型
        }
        else
        {
            if ((pappinfoblock->m_type != m_dev_apptype)&&(!m_istestprogram)) return ERROR_CHECK_UNMATCH3;
        }

        //调整映像
        //调整为4字节对齐长度并加入CRC32长度
        i = m_BinaryContent.size()+3+4;
        i &= 0xFFFFFFFC;

        //APP_INFO_BLOCK(应用程序信息块)加入UID,长度。尾部加入CRC32
        pappinfoblock->m_size = i;
        pappinfoblock->m_uid1 = m_uid1;
        pappinfoblock->m_uid2 = m_uid2;
        pappinfoblock->m_uid3 = m_uid3;

        m_BinaryContent.resize(i);//resize可能会改变数据的地址，所以pappinfoblock指针在resize后可能会指向非法地址导致崩溃，现在把它移到下面

        *(quint32*)(m_BinaryContent.data()+i-4) = STM32_CRC32::stm32crc32((quint32*)m_BinaryContent.data(), (i/4)-1);
    }
    else
    {
        //检查平台和映像是否一致
        //老的平台没有自己的bootloader，对应的应用程序也没有APP_INFO_BLOCK(应用程序信息块)
        //这个分支主要有：LPC2136、LPC2138、LPC2220、LPC2210、LPC2214平台的所有程序
        //另外还有LPC4337平台的自己bootloader程序
        pappinfoblock = (APP_INFO_BLOCK*)(m_BinaryContent.data()+0x1000);
        if ((pappinfoblock->m_flag1==0x51FA1BF0)&&(pappinfoblock->m_flag2==0x51FA1BF0))
            return ERROR_CHECK_UNMATCH1;

        //调整映像
        //生成中断向量表的CheckSum
        p = (quint32*)m_BinaryContent.data();
        if(GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC2XXX)
        {
            ivt_CRC = 0;
            // Clear the vector at 0x14 so it doesn't affect the checksum:
            for (i = 0; i < 4; i++) m_BinaryContent[i + 0x14] = 0;
            // Calculate a native checksum of the little endian vector table:
            for (i = 0; i < 8; i++) ivt_CRC += p[i];
            // Negate the result and place in the vector at 0x14 as little endian
            // again. The resulting vector table should checksum to 0.
            ivt_CRC = (unsigned long) (0 - ivt_CRC);
            for (i = 0; i < 4; i++) m_BinaryContent[i + 0x14] = (unsigned char)(ivt_CRC >> (8 * i));
        }
        else
        if(GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC17XX ||
           GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC13XX ||
           GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC43XX ||
           GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC11XX)
        {
            // Patch 0x1C, otherwise it is not running and jumps to boot mode
            ivt_CRC = 0;
            // Clear the vector at 0x1C so it doesn't affect the checksum:
            for (i = 0; i < 4; i++) m_BinaryContent[i + 0x1C] = 0;
            // Calculate a native checksum of the little endian vector table:
            for (i = 0; i < 8; i++) ivt_CRC += p[i];
            // Negate the result and place in the vector at 0x1C as little endian
            // again. The resulting vector table should checksum to 0.
            ivt_CRC = (unsigned long) (0 - ivt_CRC);
            for (i = 0; i < 4; i++) m_BinaryContent[i + 0x1C] = (unsigned char)(ivt_CRC >> (8 * i));
        }
        else
        {
          return ERROR_CHECK_INTERNAL;
        }
    }
    return 0;
}

bool ISP_thread::NeedRetry(void)
{
//    if ((m_dev_apptype==0x80002001)||
//        (m_dev_apptype==0x80002002)||
//        (m_dev_apptype==0x80002003)||
//        (m_dev_apptype==0x8000200F)||
//        (m_dev_apptype==0x80004000))
        return true;
//    return false;
}

int ISP_thread::EraseChip(void)
{
    int retry = 0;
    quint32 addr;
    unsigned long realsize;
    char Answer[128];
    char tmpString[128];

    ClearCommunication();

    if (m_newbootloader)
    {
        switch (m_dev_apptype)
        {
        case 0x80000001://六轴主板 LPC4337
        case 0x80000002://两轴主板 LPC4337
        case 0x80000003://三轴主板 LPC4337
        case 0x8000000F://PLC主板 LPC4337
            if ((m_appbase>>24)==0x1A)
                sprintf(tmpString, "E\r\n0000\r\n");
            else
                sprintf(tmpString, "E\r\n0001\r\n");
            break;
        case 0x80009035://5轴Can主板 STM32H730VB
        case 0x80009045://fivebox主板 STM32H730VB
        case 0x80005001://六轴主板 STM32H750VB
        case 0x80005005://五轴主板 STM32H750VB
        case 0x80005011://ECAT六轴主板 STM32H750VB
        case 0x80005012://ECAT两轴主板 STM32H750VB
        case 0x80005013://ECAT三轴主板 STM32H750VB
        case 0x8000501F://ECAT-PLC主板 STM32H750VB
        case 0x80005021://DVS六轴主板 STM32H750VB
        case 0x80005022://DVS两轴主板 STM32H750VB
        case 0x80005023://DVS三轴主板 STM32H750VB
        case 0x8000502F://DVS-PLC主板 STM32H750VB
        case 0x80005031://Canopen六轴主板 STM32H750VB
        case 0x80005032://Canopen两轴主板 STM32H750VB
        case 0x80005033://Canopen三轴主板 STM32H750VB
        case 0x8000503F://Canopen-PLC主板 STM32H750VB
            if ((m_appbase>>24)==0x08)
                sprintf(tmpString, "E\r\n0000\r\n");//Flash中运行
            else
                sprintf(tmpString, "E\r\n0001\r\n");//AXISRAM中运行
            break;
        case 0x80003011://ECAT六轴主板 STM32F427IG
        case 0x80003012://ECAT两轴主板 STM32F427IG
        case 0x80003013://ECAT三轴主板 STM32F427IG
        case 0x8000301F://ECAT-PLC主板 STM32F427IG
        case 0x80003001://六轴主板 STM32F427IG
        case 0x80003002://两轴主板 STM32F427IG
        case 0x80003003://三轴主板 STM32F427IG
        case 0x8000300F://PLC主板 STM32F427IG
        case 0x80002001://六轴主板 STM32F407VG
        case 0x80002002://两轴主板 STM32F407VG
        case 0x80002003://三轴主板 STM32F407VG
        case 0x8000200F://PLC主板 STM32F407VG
        case 0x80004000://单轴一体机主板 GD32F305VC
            sprintf(tmpString, "E\r\n0000\r\n");
            break;
        case 0x00000001://旋臂512KB操作器
        case 0x00000002://旋臂768KB操作器
        case 0x00000003://旋臂1024KB操作器
        case 0x00000101://单轴512KB操作器
        case 0x00000102://单轴768KB操作器
        case 0x00000103://单轴1024KB操作器
        case 0x00000201://两轴512KB操作器
        case 0x00000202://两轴768KB操作器
        case 0x00000203://两轴1024KB操作器
        case 0x00000301://三轴512KB操作器
        case 0x00000302://三轴768KB操作器
        case 0x00000303://三轴1024KB操作器
        case 0x00000401://OEM512KB操作器
        case 0x00000402://OEM768KB操作器
        case 0x00000403://OEM1024KB操作器
            addr = m_BinaryContent.size()/2048;
            if (addr*2048<(quint32)m_BinaryContent.size()) addr++;
            sprintf(tmpString, "E\r\n%04d\r\n", addr);
            break;
        }
        SendString(tmpString);
        ReceiveNr0x0A(Answer, sizeof(Answer) - 1, &realsize, 3, 20000);
        int cmdlen = strlen(tmpString);
        if (!(strncmp(Answer, tmpString, cmdlen) == 0 && strcmp(Answer + cmdlen, "0\r\n") == 0)) return ERROR_NEWISP_ERASE;

        if (m_need_fast_cmd)
        {
needretryagain:
            retry ++;
            qDebug() << "fast";
            sprintf(tmpString, "FAST\r\n"); //新bootloader中STM32不需要发FAST命令，STM32芯片是通过CDC的波特率改变为115200进入FAST模式的
            SendString(tmpString);
            int cmdlen = strlen(tmpString);
            if (NeedRetry())
                ReceiveNr0x0A(Answer, sizeof(Answer) - 1, &realsize, 2, 100);
            else
            ReceiveNr0x0A(Answer, sizeof(Answer) - 1, &realsize, 2, 10000);
            if (!(strncmp(Answer, tmpString, cmdlen) == 0 && strcmp(Answer + cmdlen, "0\r\n") == 0))
            {
                if (NeedRetry())
                {
                    if (retry < 10)
                    goto needretryagain;
                }
                return ERROR_NEWISP_ERASE;
            }
        }
    }//m_newbootloader end
    else
    {//nxp isp
        if (GetChipFlashSize(m_DetectedDevice)!=0)
        {
            if (!SendAndVerify("U 23130\r\n", Answer, sizeof Answer)) return ERROR_NXPISP_UNLOCK;

            if (GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC43XX)
            {
                if ((m_appbase>>24)==0x1A)
                    sprintf(tmpString, "P %d %d 0\r\n", 0, GetChipFlashSectors(m_DetectedDevice)-1);
                else
                    sprintf(tmpString, "P %d %d 1\r\n", 0, GetChipFlashSectors(m_DetectedDevice)-1);
            }
            else
            {
                sprintf(tmpString, "P %d %d\r\n", 0, GetChipFlashSectors(m_DetectedDevice)-1);
            }

            if (!SendAndVerify(tmpString, Answer, sizeof Answer)) return ERROR_NXPISP_PREPARE;

            if (GetChipVariant(m_DetectedDevice) == CHIP_VARIANT_LPC43XX)
            {
                if ((m_appbase>>24)==0x1A)
                    sprintf(tmpString, "E %d %d 0\r\n", 0, GetChipFlashSectors(m_DetectedDevice)-1);
                else
                    sprintf(tmpString, "E %d %d 1\r\n", 0, GetChipFlashSectors(m_DetectedDevice)-1);
            }
            else
            {
                sprintf(tmpString, "E %d %d\r\n", 0, GetChipFlashSectors(m_DetectedDevice)-1);
            }

            if (!SendAndVerify(tmpString, Answer, sizeof Answer)) return ERROR_NXPISP_ERASE;
        }
    }

    return 0;
}

int ISP_thread::FastISP()
{
    int retry = 0;
    unsigned int k = 0;
    unsigned long realsize;
    unsigned int tmp;
    unsigned short crc;
    char tmpString[128];
    char Answer[128];
    unsigned long len;
    long i;
    unsigned char buf[4100];

    if (!m_eth_burn) m_serial.setBaudRate(BAUD115200); //调整Baud为115200
    msleep(10);
    ClearCommunication();       //清除串口缓存
    ////////////////////////////////////////////////////////

    if (m_need_check_mark)//检查芯片MARK标志
    {
Mretryagain:
        retry++;
        tmpString[0] = 'M';
        ClearCommunication();       //清除串口缓存
        SendBuffer(tmpString, 1);
        Receive(Answer, sizeof(Answer)-1, &realsize, 5);
        if (Answer[0]!='A')
        {
//            if (NeedRetry())
            {
                if (retry < 10)
                goto Mretryagain;
            }
        }
        tmp = Answer[3];
        tmp <<= 8;
        tmp |= Answer[2];
        tmp <<= 8;
        tmp |= Answer[1];
        tmp <<= 8;
        tmp |= Answer[0];
//        if (tmp==0)
//            return ERROR_FAST_NOTEST;
    }

    if (m_need_select_bank)//选择芯片BANK
    {
        retry = 0;
Aretryagain:
        ClearCommunication();
        switch (m_dev_apptype)
        {
        case 0x80000001://六轴主板 LPC4337
        case 0x80000002://两轴主板 LPC4337
        case 0x80000003://三轴主板 LPC4337
        case 0x8000000F://PLC主板 LPC4337
        if ((m_appbase>>24)==0x1A)
            tmpString[0] = 'A';
        else
            tmpString[0] = 'O';
            break;
        case 0x80009035://5轴Can主板 STM32H730VB
        case 0x80009045://fivebox主板 STM32H730VB
        case 0x80005001://六轴主板 STM32H750VB
        case 0x80005005://五轴主板 STM32H750VB
        case 0x80005011://ECAT六轴主板 STM32H750VB
        case 0x80005012://ECAT两轴主板 STM32H750VB
        case 0x80005013://ECAT三轴主板 STM32H750VB
        case 0x8000501F://ECAT-PLC主板 STM32H750VB
        case 0x80005021://DVS六轴主板 STM32H750VB
        case 0x80005022://DVS两轴主板 STM32H750VB
        case 0x80005023://DVS三轴主板 STM32H750VB
        case 0x8000502F://DVS-PLC主板 STM32H750VB
        case 0x80005031://Canopen六轴主板 STM32H750VB
        case 0x80005032://Canopen两轴主板 STM32H750VB
        case 0x80005033://Canopen三轴主板 STM32H750VB
        case 0x8000503F://Canopen-PLC主板 STM32H750VB
            if ((m_appbase>>24)==0x08)
                tmpString[0] = 'A';
            else
                tmpString[0] = 'O';
            break;
        }
        SendBuffer(tmpString, 1);
        Receive(Answer, 1, &realsize);
        if (Answer[0]!='A')
        {
//            if (NeedRetry())
            {
                if (retry < 10)
                goto Aretryagain;
            }
            return ERROR_FAST_SETBANK;
    }
    }
    ////////////////////////////////////////////////////////
    for (i=(m_BinaryContent.size()/4096)*4096; i>=0; )
    {
        emit ChangePercent(((m_BinaryContent.size()-i)*100)/m_BinaryContent.size());
        memset(buf, 0xFF, 4100);
        len = m_BinaryContent.size()-i;
        if (len>4096) len = 4096;
        ///////////////////////////////////////////////////////
        memcpy(buf, m_BinaryContent.data()+i, len);
        if (GetChipFlashSize(m_DetectedDevice)!=0) len = 4096;
        crc = CCRC16::GetCRC16_buf(buf, len);
        buf[len] = crc;
        buf[len+1] = crc>>8;
        ///////////////////////////////////////////////////////
        tmpString[0] = 'C';//发送命令
        tmp = i;
        memcpy(tmpString+1, (void*)&tmp, 4);//发送长度
        crc = len+2;
        memcpy(tmpString+5, (void*)&crc, 2);//发送CRC16
        ///////////////////////////////////////////////////////
        retry = 0;
needretryagain:
        retry++;
        ClearCommunication();
        SendBuffer(tmpString, 7);//发送命令+长度+CRC16
        if (NeedRetry())
            Receive(Answer, sizeof(Answer)-1, &realsize, 1, 100);//接收应答
        else
        Receive(Answer, sizeof(Answer)-1, &realsize);//接收应答
        if (Answer[0]!='A')
        {
            if (NeedRetry())
            {
                if (retry < 10)
                goto needretryagain;
            }
            return ERROR_FAST_SETADDR;
        }
        ///////////////////////////////////////////////////////
        ClearCommunication();
        SendBuffer((char*)buf, len+2);//发送数据
        Receive(Answer, sizeof(Answer)-1, &realsize);//接收应答
        if (Answer[0]!='A')
        {
            for(k = 0;k < 65536;k++)
            {
                tmpString[0] = 'N';
                ClearCommunication();
                SendBuffer(tmpString, 1);//发送命令
                Receive(Answer, sizeof(Answer)-1, &realsize,1,2);//接收应答
                if(Answer[0]=='N')
                    break;
            }
            if(Answer[0]!='N')
            return ERROR_FAST_SETDATA;
            continue;
        }
        ///////////////////////////////////////////////////////
        i -= 4096;
    }

    tmpString[0] = 'B';//发送复位重启命令
    SendBuffer(tmpString, 1);
//    Receive(Answer, sizeof(Answer)-1, &realsize);
    emit ChangePercent(100);

    return 0;
}
