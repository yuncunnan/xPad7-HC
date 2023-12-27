#ifndef XUSB_H
#define XUSB_H

#include <QObject>

class xUsb : public QObject
{
	Q_OBJECT
public:
	explicit xUsb(QObject *parent = 0);
	static bool CheckInsert(void);
	
signals:
	
public slots:
	
};

#endif // XUSB_H
