#include <stdlib.h>
#include <QFile>
#include <QTextStream>
#include "xconfig.h"
#include "xusb.h"

xUsb::xUsb(QObject *parent) : QObject(parent)
{
}

bool xUsb::CheckInsert(void)
{
	bool ret = false;
#if defined(Q_WS_QWS)
	QFile mounts("/proc/mounts");
	if (!mounts.open(QIODevice::ReadOnly))
		return false;
	QTextStream in(&mounts);
    QString line;
	do
	{
        line = in.readLine();
        if (!line.isNull())
        {
            if (line.contains("/mnt/usb/sda1", Qt::CaseSensitive))
            {
                ret = true;
                break;
            }
        }
    } while (!in.atEnd());
#else
	ret = true;
#endif
	return ret;
}
