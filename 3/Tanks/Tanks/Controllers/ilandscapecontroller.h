#pragma once

#include <QList>
#include <QPoint>

class ILandscapeController
{
public:
	/**
	 * @brief getLandscape Generate landscape of the map that represented by polygonal chain.
	 * @return List of vertices of the polygonal chain.
	 * First vertex located at the left border of the map, last - at the right border.
	 */
	virtual QList<QPointF> getLandscape() const = 0;

protected:
	ILandscapeController()
	{}
};
