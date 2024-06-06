#ifndef XKEYPAD_H
#define XKEYPAD_H

#define KEY_NULL			0

#define VKEY_SCAN_DOOR_RESET			(0x100+50)//复位
#define VKEY_SCAN_DOOR_QUERY			(0x100+51)//查询

//#if defined(Q_WS_WIN)
//#define ENCODER_CW      '?'
//#define ENCODER_CCW     ','
//#else
//#define ENCODER_CW      0x3C
//#define ENCODER_CCW     0x3B
//#endif

#include <QObject>
#include <QApplication>
#include <QKeyEvent>
#include "xconfig.h"
#include <QThread>

class xKeypad : public QObject
{
	Q_OBJECT
public:
	explicit xKeypad(QApplication* app, QObject *parent = 0);
	~xKeypad(void);
};


#endif // XKEYPAD_H
