#ifndef BUZZER_H
#define BUZZER_H

#include <QObject>

class Buzzer : public QObject
{
	Q_OBJECT
public:
	explicit Buzzer(QObject *parent = 0);
	~Buzzer(void);
	void KeyBeep(void);
	void TouchBeep(void);
	void SetKeyBellUsage(bool use);
	void SetTouchBellUsage(bool use);
    void Beep(void);
public slots:

private:
	static bool useKeyBell;
	static bool useTouchBell;
};

extern Buzzer *xBuzzer;

#endif // BUZZER_H
