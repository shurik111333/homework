#include "shellStandart.h"
#include <QPainter>
#include <QtMath>

ShellStandart::ShellStandart(double x, double y, double angle, double speed) :
    IShell(x, y, angle),
    width(10),
    heigth(3)
{
	setPos(x, y);
	setRotation(angle);
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
