#include <fcntl.h>
#include <QCoreApplication>
#include "xconfig.h"
#include "xKeypad.h"
#include "buzzer.h"
#include <QDebug>
#include <QWSServer>
#include "HalBoard.h"


#include <QSocketNotifier>
#if defined(Q_WS_QWS)
#include <linux/input.h>
#endif
extern HardwareInterface *board;


xKeypad::xKeypad(QApplication *app, QObject *parent) : QObject(parent)
{
#if defined(Q_WS_QWS)
	board->xKey_Init();
#endif
}

xKeypad::~xKeypad(void)
{
#if defined(Q_WS_QWS)
	board->ReadKeys(false);
#endif
}
