#include "xKeypad.h"
#include "HalBoard.h"

extern HardwareInterface *board;

xKeypad::xKeypad()
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
