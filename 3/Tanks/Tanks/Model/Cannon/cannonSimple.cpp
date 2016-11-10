#include "cannonSimple.h"
#include <QPen>
#include <QPainter>

const double CannonSimple::defaultWIdth = 30;

CannonSimple::CannonSimple(double x, double y, const QBrush &brush, double width) :
    bodyw(defaultWIdth),
    bodyh(defaultWIdth / 2),
    gunw(bodyw / 2),
    gunh(5),
    brush(brush)
{
	body = QRectF(x - bodyw / 2, y, bodyw, bodyh);
	gun = QRectF(body.left() + bodyw / 2, body.top() + bodyh - gunh / 2, gunw, gunh);
}

QRectF CannonSimple::boundingRect() const
{
	return QRectF(body.left(), body.top(), body.width(), body.height() + gun.width());
}

void CannonSimple::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen(Qt::black, 1);
	painter->setPen(pen);
	double dx = gun.left();
	double dy = gun.top() + gun.height() / 2;
	painter->translate(dx, dy);
	painter->rotate(45);
	painter->translate(-dx, -dy);
	painter->fillRect(gun, brush);
	painter->drawRect(gun);
	painter->translate(dx, dy);
	painter->rotate(-45);
	painter->translate(-dx, -dy);
	painter->fillRect(body, brush);
	painter->drawRect(body);
}
