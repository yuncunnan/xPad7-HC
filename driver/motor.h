#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include <QTimer>

class Motor : public QObject
{
	Q_OBJECT
public:
	explicit Motor(QObject *parent = 0);
	~Motor(void);
	void StartMotor(quint8 delay, bool test = false);
	void SetMotorUsage(bool use) { useShake = use;}
	
signals:
	
private slots:
#if defined(Q_WS_QWS)
	void offmotor(void);
#endif

private:
	QTimer * m_timer;
	static int fd;
	static bool useShake;
};

extern Motor *xMotor;

#endif // MOTOR_H
