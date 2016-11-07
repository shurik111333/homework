#pragma once

#include "ilandscapecontroller.h"

/// Landscape controller that always returns the same landscape
class LandscapeControllerFixed final : public ILandscapeController
{
public:
	static LandscapeControllerFixed *getInstance();
	virtual QList<QPointF> getLandscape() const;

private:
	static LandscapeControllerFixed *instance;
	static QList<QPointF> landscape;

	LandscapeControllerFixed();
};
