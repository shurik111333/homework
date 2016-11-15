#include "tankSimple.h"
#include "../Shell/shellStandart.h"
#include <QPen>
#include <QPainter>

const double TankSimple::defaultWIdth = 30;

TankSimple::TankSimple(double x, double y, const QBrush &brush, double width) :
    scale(width / defaultWIdth),
    bodyw(width),
    bodyh(bodyw / 2),
    gunw(bodyw / 2),
    gunh(5 * scale),
    brush(brush)
{
	setPos(x, y); //it is needed for matching tank's and scene's coordinate systems
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

IShell *TankSimple::getShell() const
{
	double dx = bodyw / 2 + gunh / 2;
	double dy = bodyh - gunh / 2;
	return new ShellStandart(pos().x() + dx, pos().y() + dy, getGunAngle() + rotation(), 100);
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
