#include <QSettings>
#include "xconfig.h"
#include "motor.h"
#if defined(Q_OS_LINUX)
#include <sys/ioctl.h>
#include <fcntl.h>
#endif

Motor *xMotor = 0;

#if defined(Q_WS_QWS)

void Motor::offmotor(void)
{
	if (fd < 0)
		return;
	quint8 out = '0';
	lseek(fd, 0, SEEK_SET);
	write(fd, &out, sizeof(out));
}


#endif

int Motor::fd = -1;
bool Motor::useShake = false;

Motor::Motor(QObject *parent) :	QObject(parent)
{
	xMotor = this;
#if defined(Q_WS_QWS)
	int fdCfg = -1;
	quint8 setCfg = '1';
	// 配置Motor设备
	fdCfg = open(DEV_LAMP_CFG4, O_WRONLY);
	if (fdCfg >= 0)
	{
		write(fdCfg, &setCfg, sizeof(setCfg));
		close(fdCfg);
	}
	fd = open(DEV_LAMP_DATA4, O_RDWR);
	m_timer = new QTimer();
	m_timer->setSingleShot(true);
	connect(m_timer,SIGNAL(timeout()),this,SLOT(offmotor()));

	if (fd < 0)
		return;
	// 从配置文件中读取振动反馈设置
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	useShake = settings.value(XPAD_SET_USESHAKE, false).toBool();
#endif
}

Motor::~Motor(void)
{
#if defined(Q_WS_QWS)
	if (fd >= 0)
		close(fd);
	if (m_timer)
		delete m_timer;

#endif
}

void Motor::StartMotor(quint8 delay, bool test)
{
	if (test == false)
	{
		if (useShake == false)
			return;
	}
	if (delay == 0)
		return;
	else
	if (delay > 50)
		delay = 50;

#if defined(Q_WS_QWS)
	if (fd < 0)
		return;
	quint8 out = '1';
	lseek(fd, 0, SEEK_SET);
	write(fd, &out, sizeof(out));
	m_timer->start(200);

#endif
}
