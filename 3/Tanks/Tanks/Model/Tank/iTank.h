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
	virtual IShell *getShell() const = 0;

protected:
	double gunAngle = 45;
	double gunStep = 3;

	ITank()
	{}
};
