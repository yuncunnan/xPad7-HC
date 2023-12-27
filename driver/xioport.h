#ifndef XIOPORT_H
#define XIOPORT_H

#include <QtGlobal>
#include <QMap>
#include "xconfig.h"
#include "modbusaddr.h"

#define GET_POLARITY(x, idx)			(((x >> idx) & 0x01) != 0)
#define SET_POLARITY(x, idx, v)		(x = ((x & ~(0x0000000000000001 << idx)) | (v << idx)))
#define GET_IGNORE(x, idx)			GET_POLARITY(x, idx)
#define SET_IGNORE(x, idx, v)		SET_POLARITY(x, idx, v)
#define	GET_NOALM(x, idx)			GET_POLARITY(x, idx)
#define	SET_NOALM(x, idx, v)		SET_POLARITY(x, idx, v)
#define GET_OUTPOLARITY(x, idx)		(((x >> idx) & 0x01) != 0)
#define SET_OUTPOLARITY(x, idx, v)	(x = ((x & ~(0x0000000000000001 << idx)) | (v << idx)))

class xIoPort
{
    static quint8 m_in2fun[MAX_IN_BMP*2];
    static quint8 m_out2fun[MAX_OUT_BMP*2];
    static QMap<quint32, quint32> m_fun2in;
    static QMap<quint32, quint32> m_fun2out;

public:
    static void UpdateIn2Fun(qint8 *tab);
    static void UpdateOut2Fun(qint8 * tab);
    static bool GetIn(quint32 idx, quint16 * inbuf = NULL);
    static bool GetOut(quint32 idx, quint16 * outbuf = NULL);
    static QString GetInSuffix(quint32 idx);
    static QString GetOutSuffix(quint32 idx);
    static bool IsVisibleExtIn(quint32 varidx);
    static bool IsVisibleExtOut(quint32 varidx);
    static bool IsVisibleInSignal(quint32 varidx);
    static bool IsVisibleOutSignal(quint32 varidx);
};

#endif // XIOPORT_H
