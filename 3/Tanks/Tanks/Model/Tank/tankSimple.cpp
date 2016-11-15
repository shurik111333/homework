#include "tankSimple.h"
#include <QPen>
#include <QPainter>

const double TankSimple::defaultWIdth = 30;

TankSimple::TankSimple(double x, double y, const QBrush &brush, double width) :
    bodyw(defaultWIdth),
    bodyh(defaultWIdth / 2),
    gunw(bodyw / 2),
    gunh(5),
    brush(brush)
{
	setPos(x, y); //it is needed for matching cannon's and scene's coordinate systems
}

QRectF TankSimple::boundingRect() const
{
	return QRectF(0, 0, bodyw, bodyh + gunw);
}

void TankSimple::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen(Qt::black, 1);
	painter->setPen(pen);

	drawBody(painter);
	drawGun(painter);
}

void TankSimple::drawGun(QPainter *painter)
{
	QRectF gun(0, 0, gunw, gunh);
	double dx = bodyw / 2 + gunh / 2;
	double dy = bodyh - gunh / 2;
	painter->translate(dx, dy);
	painter->rotate(gunAngle);
	painter->fillRect(gun, brush);
	painter->drawRect(gun);
	painter->rotate(-gunAngle);
	painter->translate(-dx, -dy);
}

void TankSimple::drawBody(QPainter *painter)
{
	QRectF body(0, 0, bodyw, bodyh);
	painter->fillRect(body, brush);
	painter->drawRect(body);
}
