#include "tankSimple.h"
#include "../Shell/shellStandart.h"
#include "../Shell/shellExplosive.h"
#include <QPen>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QGraphicsScene>

QDEBUG_H

const double TankSimple::defaultWIdth = 20;

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

TankSimple::~TankSimple()
{
}

QRectF TankSimple::boundingRect() const
{
	return QRectF(0, 0, bodyw + gunh / 2 + 1, bodyh + gunw);
}

void TankSimple::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen(Qt::black, 1);
	painter->setPen(pen);

	drawGun(painter);
	drawBody(painter);
}

IShell *TankSimple::shoot() const
{
	double ang = getGunAngle() + rotation();
	if (getDirection() == Direction::left)
		ang = 180 - ang;
	auto rang = qDegreesToRadians(ang);
	auto p = QPointF(getGunCoordinates().x() + qCos(rang) * gunw,
	                 getGunCoordinates().y() + qSin(rang) * gunw);

	IShell *shell = shellType->create(p.x(), p.y(), ang);

	scene()->addItem(shell);
	shell->shoot(1000);
	return shell;
}

QPointF TankSimple::baseCenter() const
{
	return pos() + QPointF((int) getDirection() * bodyw / 2, 0);
}

QRectF TankSimple::base() const
{
	return QRectF(0, 0, bodyw, bodyh);
}

bool TankSimple::collidesWithShell(IShell *shell)
{
	QGraphicsRectItem base(this->base());
	base.moveBy(x(), y());
	base.setRotation(rotation());
	if (getDirection() == Direction::left)
		base.moveBy(-this->base().width(), 0);
	return base.collidesWithItem(shell, Qt::IntersectsItemShape);
}

bool TankSimple::hitsByShell(IShell *shell)
{
	QGraphicsRectItem base(this->base());
	base.moveBy(x(), y());
	base.setRotation(rotation());
	if (getDirection() == Direction::left)
		base.moveBy(-this->base().width(), 0);
	qDebug() << "base:" << base.pos() << base.boundingRect();

	qDebug() << "shell:" << shell->pos() << shell->boundingRect();
	auto c = shell->boundingRect().center() + shell->pos();
	auto r = shell->getExplosiveRadius();
	QGraphicsEllipseItem explosion(0, 0, 2 * r, 2 * r);
	explosion.moveBy(c.x() - r, c.y() - r);
	qDebug() << "explosion:" << explosion.pos() << explosion.boundingRect();

	return base.collidesWithItem(&explosion, Qt::IntersectsItemShape);
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

QPointF TankSimple::getGunCoordinates() const
{
	int dir = (int) getDirection();
	QPointF res = QPointF(dir * (bodyw / 2 + gunh / 2), (bodyh - dir * gunh / 2));
	double ang = qDegreesToRadians(dir * rotation());
	return scenePos() + QPointF(res.x() * qCos(ang) - res.y() * qSin(ang),
	                            res.x() * qSin(ang) + res.y() * qCos(ang));
}
