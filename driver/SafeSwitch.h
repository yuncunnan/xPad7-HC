#ifndef SAFESWITCH_H
#define SAFESWITCH_H

#include <QObject>

class SafeSwitch : public QObject
{
	Q_OBJECT
public:
	explicit SafeSwitch(QObject *parent = 0);
	~SafeSwitch(void);
	quint8 GetSafeSwState(void);
    quint8 ReadSafeSwitch(void);

    void UseSwitch(bool use);

signals:
	void SafeSwitchOn(void);
	void SafeSwitchOff(void);

public slots:
	
private:
	static quint8 keyState;
	static quint8 keyStateBak;
};

extern SafeSwitch *xSafeSw;

#endif // SAFESWITCH_H
