#include "shellStandart.h"
#include <QPainter>
#include <QtMath>
#include <QGraphicsScene>

ShellStandart::ShellStandart(double x, double y, double angle, double speed) :
    IShell(x, y, angle),
    width(10),
    heigth(3)
{
	setPos(x, y);
	setRotation(angle);
	createCursor();
}

ShellStandart::~ShellStandart()
{
	if (cursor->scene() != nullptr)
		scene()->removeItem(cursor);
	scene()->removeItem(this);
}

QRectF ShellStandart::boundingRect() const
{
	return QRectF(0, 0, width, heigth);
}

void ShellStandart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen(Qt::black, 1);
	painter->setPen(pen);

	painter->fillRect(0, 0, width, heigth, Qt::black);
}

double ShellStandart::getWeight()
{
	return weight;
}

void ShellStandart::showCursor()
{
	if (cursor->scene() == nullptr)
		scene()->addItem(cursor);
	cursor->show();
}

void ShellStandart::hideCursor()
{
	cursor->hide();
}

QGraphicsItem *ShellStandart::getCursor() const
{
	return cursor;
}

void ShellStandart::createCursor()
{
	QPointF ver(0, 0);
	auto points = QVector<QPointF> { ver, ver - QPointF(10, 10), ver + QPointF(10, -10) };
	cursor = new QGraphicsPolygonItem(QPolygonF(points));
	hideCursor();
}
