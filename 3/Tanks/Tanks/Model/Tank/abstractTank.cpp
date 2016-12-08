#include "abstractTank.h"
#include "Model/Shell/shellStandart.h"
#include <QTransform>
#include <QtMath>

double AbstractTank::getGunAngle() const
{
	return gunAngle;
}

void AbstractTank::setGunAngle(double angle)
{
	gunAngle = angle;
	update();
}

void AbstractTank::moveGunUp()
{
	gunAngle += gunStep;
	update();
}

void AbstractTank::moveGunDown()
{
	gunAngle -= gunStep;
	update();
}

AbstractTank::Direction AbstractTank::getDirection() const
{
	return direction;
}

void AbstractTank::setDirection(Direction value)
{
	if (value != direction)
		changeDirection();
}

void AbstractTank::changeDirection()
{
	direction = (Direction) (-(int) direction);
	QTransform t;
	t.scale((int) direction, 1);
	setTransform(t);
	moveBy(-(int) direction * boundingRect().size().width(), 0);

}

void AbstractTank::moveLeft()
{
	move(Direction::left);
}

void AbstractTank::moveRight()
{
	move(Direction::right);
}

void AbstractTank::move(AbstractTank::Direction dir)
{
	if (dir != direction)
		changeDirection();
	else
		move((int) direction * moveStep);
}

void AbstractTank::move(double step)
{
	double ang = qDegreesToRadians((int) direction * rotation());
	setPos(pos() + QPointF(step * qCos(ang), step * qSin(ang)));
}
