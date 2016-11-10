#include "landscapeGeneratorFixed.h"

LandscapeGeneratorFixed *LandscapeGeneratorFixed::instance = nullptr;
QList<QPointF> LandscapeGeneratorFixed::landscape = {{0, 60}, {300, 60}, {500, 250},
                                                      {700, 60}, {1000, 60}};

LandscapeGeneratorFixed *LandscapeGeneratorFixed::getInstance()
{
	return instance != nullptr ? instance : instance = new LandscapeGeneratorFixed();
}

QList<QPointF> LandscapeGeneratorFixed::getLandscape() const
{
	return landscape;
}

LandscapeGeneratorFixed::LandscapeGeneratorFixed()
{
}
