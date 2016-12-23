#pragma once

#include "iLandscapeGenerator.h"

/// Landscape controller that always returns the same landscape
class LandscapeGeneratorFixed final : public ILandscapeGenerator
{
public:
	static LandscapeGeneratorFixed *getInstance();
	/**
	 * @brief nextLandscape This method only calls getLandscape()
	 * @return Landscape
	 */
	virtual const QVector<QPointF> &nextLandscape();
	virtual const QVector<QPointF> &getLandscape() const;

private:
	static LandscapeGeneratorFixed *instance;

	LandscapeGeneratorFixed();
};
