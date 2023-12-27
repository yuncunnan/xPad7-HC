#ifndef SAFESWITCH_H
#define SAFESWITCH_H

#include <QObject>

#define SAFE_SWITCH_ON	1
#define SAFE_SWITCH_OFF	0

class SafeSwitch : public QObject
{
	Q_OBJECT
public:
	explicit SafeSwitch(QObject *parent = 0);
	~SafeSwitch(void);
	quint8 GetSafeSwState(void);
	quint8 ReadSwitch(void);

    void UseSwitch(bool use);

signals:
	void SafeSwitchOn(void);
	void SafeSwitchOff(void);

public slots:
	
private:
	static int fd;
	static quint8 keyState;
	static quint8 keyStateBak;
};

extern SafeSwitch *xSafeSw;

#endif // SAFESWITCH_H
