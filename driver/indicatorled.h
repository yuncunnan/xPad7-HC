#ifndef INDICATORLED_H
#define INDICATORLED_H

#include <QObject>

#define SELSW_STOP			0
#define SELSW_AUTO			1
#define SELSW_MANUAL		2

class IndicatorLed : public QObject
{
	Q_OBJECT
public:
	explicit IndicatorLed(QObject *parent = 0);
	~IndicatorLed(void);
	quint8 ReadSwitch(void);
	quint8 GetSwitch(void) { return swStatusBk; }

signals:
	void SwitchChanged(quint8 status);
	
private:

    static int fdData0;
    static int fdData1;

    static int data0;
    static int data1;

	static quint8 swStatus0;
	static quint8 swStatus1;
	static quint8 swStatusBk;
};

extern IndicatorLed *xLed;

#endif // INDICATORLED_H
