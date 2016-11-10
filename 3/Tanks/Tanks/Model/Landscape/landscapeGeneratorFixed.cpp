#include "landscapeGeneratorFixed.h"

LandscapeGeneratorFixed *LandscapeGeneratorFixed::instance = nullptr;

LandscapeGeneratorFixed *LandscapeGeneratorFixed::getInstance()
{
	return instance != nullptr ? instance : instance = new LandscapeGeneratorFixed();
}

const QList<QPointF> &LandscapeGeneratorFixed::nextLandscape()
{
	return getLandscape();
}

const QList<QPointF> &LandscapeGeneratorFixed::getLandscape() const
{
	return landscape;
}

LandscapeGeneratorFixed::LandscapeGeneratorFixed()
{
	landscape = {{0, 60}, {300, 60}, {500, 250}, {700, 60}, {1000, 60}};
}
