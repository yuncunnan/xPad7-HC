#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include "xsplashscreen.h"

xSplashScreen::xSplashScreen(const QPixmap &pixmap, Qt::WindowFlags f) : QSplashScreen(pixmap, f)
{
	if (pixmap.width()!=800)
	{
		QPixmap p = QPixmap(800, 1280);
		p.fill(Qt::darkGreen);
		setPixmap(p);
	}
	pLabel = new QLabel;
	pLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	pLabel->setMargin(5);
#if SIMULATOR
    pLabel->setFont(QFont("Microsoft YaHei", 10));
#else
	pLabel->setFont(QFont("Microsoft YaHei", 20));
#endif
	pLabel->setStyleSheet("QLabel" \
								"{" \
								"color: white;" \
								"background-color: rgba(0, 0, 0, 180);" \
								"font-size:28px;"\
								"}");
	pLayout = new QVBoxLayout;
	pLayout->setContentsMargins(0, 0, 0, 0);
	pLayout->addStretch();
	pLayout->addWidget(pLabel);
	setLayout(pLayout);
}

xSplashScreen::~xSplashScreen()
{
	delete pLayout;
	delete pLabel;
}

void xSplashScreen::clearMessage(void)
{
	pLabel->setText(QString(""));
	pLabel->repaint();
}

void xSplashScreen::showMessage(const QString &message, int alignment, const QColor &color)
{
	pLabel->setAlignment((Qt::Alignment)alignment);
	pLabel->setText(message);
	pLabel->repaint();
}
