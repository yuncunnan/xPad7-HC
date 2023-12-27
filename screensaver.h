#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include "xpermissions.h"
#include "formbacklight.h"

#if defined(Q_WS_QWS)
#include <QWSScreenSaver>

class ScreenSaver : public QWSScreenSaver
{
public:
	ScreenSaver(xPermissions *perm, FormBacklight *bklight);
	~ScreenSaver();
    void InitScreenSaver(void);
	virtual bool save(int level);
	void setInterval(int delay);
	virtual void restore();
private:
	xPermissions *pPerm;
	FormBacklight *pBklght;
};

extern ScreenSaver *xSaver;

#endif

#endif // SCREENSAVER_H
