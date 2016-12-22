#pragma once

#include "../Shell/ishell.h"
#include <QGraphicsItem>

class ITank : public QGraphicsItem
{
public:
	virtual ~ITank() {}

	virtual double getGunAngle() const;
	virtual void setGunAngle(double angle);
	/**
	 * @brief moveGunUp Increase gun's angle by step
	 */
	virtual void moveGunUp();
	/**
	 * @brief moveGunDown Decrease gun's angle by step
	 */
	virtual void moveGunDown();
	virtual IShell *shoot() const = 0;

	enum class Direction
	{
		left = -1,
		right = 1
	};

	virtual QPointF baseCenter() const = 0;
	virtual Direction getDirection() const;
	virtual void setDirection(Direction value);
	virtual void changeDirection();
	virtual void moveLeft();
	virtual void moveRight();
	virtual void move(Direction dir);

protected:
	Direction direction = Direction::right;
	double gunAngle = 45;
	double gunStep = 2;
	double moveStep = 3;

	ITank()
	{

	}

	virtual void move(double step);
};
