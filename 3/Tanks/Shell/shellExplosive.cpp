#include "shellExplosive.h"
#include <QPainter>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QDebug>

QDEBUG_H

ShellExplosive::ShellExplosive(double x, double y, double angle) :
    IShell(x, y, angle)
{
	createCursor();
}

QRectF ShellExplosive::boundingRect() const
{
	int width = 2 * r + 2 * penWidth;
	return QRectF(-penWidth, -penWidth, width, width);
}

void ShellExplosive::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	qDebug() << "pos:" << pos();
	QPen pen(Qt::black, penWidth);
	painter->setPen(pen);
	painter->setBrush(Qt::black);

	painter->drawEllipse(QRectF(0, 0, 2 * r, 2 * r));
}

QPainterPath ShellExplosive::shape() const
{
	QGraphicsEllipseItem c(boundingRect());
	c.moveBy(x(), y());
	c.setRotation(rotation());
	return c.shape();
}

void ShellExplosive::showCursor()
{
	if (cursor->scene() == nullptr)
		scene()->addItem(cursor);
	cursor->show();
}

void ShellExplosive::hideCursor()
{
	cursor->hide();
}

double ShellExplosive::getExplosiveRadius()
{
	return explosiveRadius;
}

double ShellExplosive::getWeight()
{
	return weight;
}

QGraphicsItem *ShellExplosive::getCursor() const
{
	return cursor;
}

void ShellExplosive::createCursor()
{
	QPointF ver(0, 0);
	auto points = QVector<QPointF> { ver, ver - QPointF(10, 10), ver + QPointF(10, -10) };
	cursor = new QGraphicsPolygonItem(QPolygonF(points));
	hideCursor();
}
