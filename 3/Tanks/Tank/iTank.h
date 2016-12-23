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

	/**
	 * @return Rect, that contains tank's body.
	 */
	virtual QRectF base() const = 0;
	/**
	 * @return Point in the middle of the bottom side of base.
	 */
	virtual QPointF baseCenter() const = 0;
	virtual Direction getDirection() const;
	virtual void setDirection(Direction value);
	/**
	 * @brief changeDirection Changes current direction to opposite.
	 */
	virtual void changeDirection();
	/**
	 * @brief moveLeft Moves tank to the left, if tank has left direction.
	 * Changes direction otherwise.
	 */
	virtual void moveLeft();
	/**
	 * @brief moveRight Moves tank to the right, if tank has right direction.
	 * Changes direction otherwise.
	 */
	virtual void moveRight();
	/**
	 * @brief move Moves tank to the passed direction, if tank has the same direction.
	 * Changes direction otherwise.
	 * @param dir Direction to move
	 */
	virtual void move(Direction dir);

protected:
	Direction direction = Direction::right;
	double gunAngle = 45;
	double gunStep = 2;
	double moveStep = 3;

	ITank()
	{}

	virtual void move(double step);
};
