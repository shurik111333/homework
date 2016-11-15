#include "iTank.h"

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
