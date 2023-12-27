#include <QFile>
#include "errtype.h"
#include "chexbin.h"
#include "kk_ihex_read.h"
#include "kk_ihex_write.h"

static int ghandleerror;
static QByteArray gbuf;
static quint32 gbaseaddress;
static QFile * m_file;

CHexBin::CHexBin(QObject *parent) :
    QObject(parent)
{
}

quint32 CHexBin::GetBaseAddress(void)
{
    return gbaseaddress;
}
void CHexBin::SetBaseAddress(quint32 BaseAddr)
{
    gbaseaddress = BaseAddr;
}

QByteArray CHexBin::GetDataBuffer(void)
{
    return gbuf;
}
void CHexBin::SetDataBuffer(QByteArray & buf)
{
    gbuf = buf;
}

int CHexBin::Hex2Bin(QString hexfile)
{
    static struct ihex_state ihex;
    QFile file(hexfile);
    ghandleerror = 0;
    gbaseaddress = 0xFFFFFFFF;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QByteArray line = file.readLine();
            ihex_read_bytes(&ihex, line, line.size());
            if (ghandleerror!=0) break;
        }
        if (ghandleerror == 0)
            ihex_end_read(&ihex);
        file.close();
    }
    else
    {
        ghandleerror = ERROR_HEXBIN_FILEOPEN;
    }
    return ghandleerror;
}

int CHexBin::Bin2Hex(QString hexfile)
{
    static struct ihex_state ihex;
    ghandleerror = 0;
    m_file = new QFile(hexfile);
    if (m_file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Text))
    {
        ihex_init(&ihex);
        ihex_write_at_address(&ihex, gbaseaddress);
        if (0)
        {
            ihex.flags |= IHEX_FLAG_ADDRESS_OVERFLOW;
        }
        ihex_write_bytes(&ihex, gbuf.data(), gbuf.size());
        ihex_end_write(&ihex);
    }
    else
    {
        ghandleerror = ERROR_HEXBIN_FILEOPEN;
    }
    m_file->close();
    return ghandleerror;
}

extern "C" void ihex_flush_buffer(struct ihex_state *ihex, char *buffer, char *eptr)
{
    *eptr = '\0';
    m_file->write(buffer, strlen(buffer));
}

extern "C" ihex_bool_t ihex_data_read(struct ihex_state *ihex, ihex_record_type_t type, ihex_bool_t checksum_mismatch)
{
    if (checksum_mismatch) //CRC错误
    {
        ghandleerror = ERROR_HEXBIN_CRC;
        return false;
    }
    if (ihex->length < ihex->line_length) //长度错误
    {
        ghandleerror = ERROR_HEXBIN_LINE;
        return false;
    }
    if (type == IHEX_DATA_RECORD) //HEX数据
    {
        quint32 address = (unsigned long) IHEX_LINEAR_ADDRESS(ihex);
        if (gbaseaddress==0xFFFFFFFF)
        {
            gbaseaddress = address;
        }
        gbuf.resize(address-gbaseaddress);
        gbuf.append((const char *)ihex->data, ihex->length);
    }
    else
    if (type == IHEX_END_OF_FILE_RECORD) //HEX文件结束
    {
    }
    return true;
}
