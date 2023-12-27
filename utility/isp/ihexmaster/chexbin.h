#ifndef CHEXBIN_H
#define CHEXBIN_H

#include <QObject>

class CHexBin : public QObject
{
    Q_OBJECT
public:
    explicit CHexBin(QObject *parent = 0);
    int Hex2Bin(QString hexfile);
//    QByteArray Hex2Bin(QByteArray hexArray);

    int Bin2Hex(QString hexfile);
//    QByteArray Bin2Hex(QByteArray hexArray);

    quint32 GetBaseAddress(void);
    void SetBaseAddress(quint32 BaseAddr);

    QByteArray GetDataBuffer(void);
    void SetDataBuffer(QByteArray &buf);
signals:
    
public slots:
    
};

#endif // CHEXBIN_H
