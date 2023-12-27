#include <QtGlobal>

#ifndef __CRC16_H__
#define __CRC16_H__

typedef unsigned char   uint8_t;
typedef unsigned short   uint16_t;

class CCRC16                    //模块测试完成
{
    static const uint16_t crctab[256];
public:
    static unsigned short GetCRC16_buf(unsigned char *buf, unsigned short count);
    static uint16_t GetCRC16(uint16_t crc, uint8_t data);
    static uint16_t MBCRC16( uint8_t * pucFrame, uint16_t usLen );
    static uint16_t GetCRC16(uint8_t *buf, uint16_t count);		//得到count个uint8的buf的CRC值
};

#endif

