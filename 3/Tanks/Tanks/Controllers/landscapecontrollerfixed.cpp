#include "landscapecontrollerfixed.h"

LandscapeControllerFixed *LandscapeControllerFixed::instance = nullptr;
QList<QPointF> LandscapeControllerFixed::landscape = {{0, 60}, {300, 60}, {500, 250},
                                                      {700, 60}, {1000, 60}};

LandscapeControllerFixed *LandscapeControllerFixed::getInstance()
{
	return instance != nullptr ? instance : instance = new LandscapeControllerFixed();
}

QList<QPointF> LandscapeControllerFixed::getLandscape() const
{
	return landscape;
}

LandscapeControllerFixed::LandscapeControllerFixed()
{
}
