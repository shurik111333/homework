#pragma once

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

protected:
	double gunAngle = 45;
	double gunStep = 3;

	ITank()
	{}
};
