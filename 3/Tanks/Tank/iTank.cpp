#include "iTank.h"
#include "../Shell/shellStandart.h"
#include <QTransform>
#include <QtMath>
#include <algorithm>

using std::max;

double ITank::getGunAngle() const
{
	return gunAngle;
}

void ITank::setGunAngle(double angle)
{
	gunAngle = angle;
	update();
}

void ITank::moveGunUp()
{
	gunAngle += gunStep;
	update();
}

void ITank::moveGunDown()
{
	gunAngle -= gunStep;
	update();
}

ITank::Direction ITank::getDirection() const
{
	return direction;
}

void ITank::setDirection(Direction value)
{
	if (value != direction)
		changeDirection();
}

void ITank::changeDirection()
{
	direction = (Direction) (-(int) direction);
	QTransform t;
	t.scale((int) direction, 1);
	setTransform(t);
	moveBy(-(int) direction * base().width(), 0);
}

void ITank::moveLeft()
{
	move(Direction::left);
}

void ITank::moveRight()
{
	move(Direction::right);
}

void ITank::move(ITank::Direction dir)
{
	if (dir != direction)
		changeDirection();
	else
		move((int) direction * moveStep);
}

void ITank::setShell(IShellType *type)
{
	shellType = type;
}

IShellType *ITank::getShell() const
{
	return shellType;
}

int ITank::getHealthPoints() const
{
	return hp;
}

void ITank::hit(int damage)
{
	hp = max(0, hp - damage);
}

void ITank::setHealthPoints(int newHp)
{
	hp = newHp;
}

bool ITank::isDestroyed() const
{
	return hp == 0;
}

void ITank::move(double step)
{
	double ang = qDegreesToRadians((int) direction * rotation());
	setPos(pos() + QPointF(step * qCos(ang), step * qSin(ang)));
}
