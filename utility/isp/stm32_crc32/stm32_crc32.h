#ifndef STM32_CRC32_H
#define STM32_CRC32_H

#include <QObject>

#define POLYNOMIAL          0x04C11DB7
#define INITIAL_REMAINDER   0xFFFFFFFF
#define FINAL_XOR_VALUE     0x00000000

typedef quint32 width_t;
#define WIDTH (8 * sizeof(width_t))
#define TOPBIT (1 << (WIDTH - 1))

class STM32_CRC32 : public QObject
{
    Q_OBJECT
    static width_t m_crcTable[256];
public:
    explicit STM32_CRC32(QObject *parent = 0);
    static void GenCRCTable(void);
	static quint32 stm32crc32(quint32 * message, unsigned int nWords, quint32 remainder=0xFFFFFFFF);
signals:
    
public slots:
    
};

#endif // STM32_CRC32_H
