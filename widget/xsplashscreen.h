#ifndef XSPLASHSCREEN_H
#define XSPLASHSCREEN_H

#include <QSplashScreen>

class QLabel;
class QVBoxLayout;

class xSplashScreen : public QSplashScreen
{
	Q_OBJECT
public:
	explicit xSplashScreen(const QPixmap & pixmap = QPixmap(), Qt::WindowFlags f = 0);
	~xSplashScreen();

public slots:
	void clearMessage(void);
	void showMessage(const QString &message, int alignment = Qt::AlignLeft, const QColor &color = Qt::black);

private:
	QLabel *pLabel;
	QVBoxLayout *pLayout;
};

#endif // XSPLASHSCREEN_H
