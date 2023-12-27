#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include "xclock.h"

xClock::xClock(QWidget *parent) : QWidget(parent)
{
	// 创建定时器
	 pTimer = new QTimer(this);
	 // 连接信号槽
	 connect(pTimer,SIGNAL(timeout()),this,SLOT(update()));
}

xClock::~xClock()
{
	delete pTimer;
}

void xClock::StartClock(bool start)
{
	if (start == true)
		pTimer->start(1000);
	else
		pTimer->stop();
}

void xClock::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	int side = qMin(width(), height());
	painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
	painter.setWindow(0, 0, 250, 250);	// 设置(0，0)为新的坐标原点
	draw(&painter);
}

void xClock::draw(QPainter *painter)
{
	//下面三个数组用来定义表针的三个顶点，以便后面的填充
	static const QPoint hour[4] =
	{
		QPoint(0, 16),
		QPoint(3, 8),
		QPoint(0, -40),
		QPoint(-3, 8)
	};
	static const QPoint min[4] =
	{
		QPoint(0, 16),
		QPoint(3, 8),
		QPoint(0, -70),
		QPoint(-3, 8)
	};
	static const QPoint sed[4] =
	{
		QPoint(0, 16),
		QPoint(3, 8),
		QPoint(0, -90),
		QPoint(-3, 8)
	};
	// 绘制表盘
	painter->drawPixmap(0, 0, 250, 250, QPixmap(":/img/widget/ClockDial.png"));
	// 获取当前时间
	QTime time = QTime::currentTime();
	// 重新设定坐标原点
	painter->translate(125,125);
	// 绘制时针
	painter->setBrush(Qt::black);
	painter->setPen(Qt::darkGray);
	painter->save();
	painter->rotate(30.0 * (time.hour() + time.minute() / 60.0));
	painter->drawConvexPolygon(hour, 4);
	painter->restore();
	// 绘制分针
//	painter->setBrush(Qt::darkGray);
//	painter->setPen(Qt::gray);
	painter->save();
	painter->rotate(6.0 * (time.minute() + time.second() / 60.0));
	painter->drawConvexPolygon(min, 4);
	painter->restore();
	// 绘制秒针
	painter->setBrush(Qt::red);
	painter->setPen(Qt::red);
	painter->save();						// 保存坐标系，防止坐标系跑偏了
	painter->rotate(6.0 * time.second());	// 注意是6.0，不是6
	painter->drawConvexPolygon(sed, 4);
	painter->restore();						// 复位之前的坐标系
}
