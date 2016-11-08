#pragma once

#include "iLandscapeGenerator.h"

/// Landscape controller that always returns the same landscape
class LandscapeGeneratorFixed final : public ILandscapeGenerator
{
public:
	static LandscapeGeneratorFixed *getInstance();
	virtual QList<QPointF> getLandscape() const;

private:
	static LandscapeGeneratorFixed *instance;
	static QList<QPointF> landscape;

	LandscapeGeneratorFixed();
};
