#include "icannon.h"

double ICannon::getGunAngle() const
{
	return gunAngle;
}

void ICannon::setGunAngle(double angle)
{
	gunAngle = angle;
	update();
}

void ICannon::moveGunUp()
{
	gunAngle += gunStep;
	update();
}

void ICannon::moveGunDown()
{
	gunAngle -= gunStep;
	update();
}
