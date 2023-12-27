#include <QPainter>
#include "xspeedometer.h"

xSpeedometer::xSpeedometer(QWidget *parent) : QWidget(parent)
{
	speed = 50;
}

void xSpeedometer::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
	int side = qMin(width(), height());
	painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
	painter.setWindow(0, 0, 180, 180);	// 设置(0，0)为新的坐标原点
	draw(&painter);
}

void xSpeedometer::SetSpeed(int var)
{
	if (var < 0)
		var = 0;
	else if (var > 100)
		var = 100;
	if (speed == var)
		return;
	speed = var;
	update();
}

void xSpeedometer::draw(QPainter *painter)
{
	static const QPoint pointer[4] =
	{
		QPoint(0, 16),
		QPoint(8, 8),
		QPoint(0, -40),
		QPoint(-8, 8)
	};
	// 绘制表盘
	painter->drawPixmap(0, 0, 180, 180, QPixmap(":/img/widget/Dashboard.png"));
	// 重新设定坐标原点
	painter->translate(89,88);
	// 绘制表针
	painter->rotate((speed - 50.0) * (11.8 / 5.0));
	painter->setBrush(Qt::white);
	painter->setPen(Qt::white);
	painter->drawConvexPolygon(pointer, 4);
}
