#pragma once

#include <QList>
#include <QPoint>
#include <QPair>

class ILandscapeGenerator
{
public:
	virtual ~ILandscapeGenerator() {}
	/**
	 * @brief nextLandscape Generate new landscape
	 * @return New landscape
	 */
	virtual const QList<QPointF> &nextLandscape() = 0;
	/**
	 * @brief getLandscape Generate landscape of the map that represented by polygonal chain.
	 * @return List of vertices of the polygonal chain.
	 * First vertex located at the left border of the map, last - at the right border.
	 */
	virtual const QList<QPointF> &getLandscape() const = 0;
	/**
	 * @brief getSegment Find segment of landscape, that contains point with input x-coordinate.
	 * @param x x-coordinate of point
	 * @return Segment, that contains point.
	 * If several segments contains point, returns leftmost segment.
	 */
	virtual QPair<QPointF, QPointF> getSegment(double x) const;
	/**
	 * @brief getPoint Find point on landscape with input x-coordinate
	 * @param x x-coordinate
	 * @return Point on landscape
	 */
	virtual QPointF getPoint(double x) const;

protected:
	QList<QPointF> landscape;

	ILandscapeGenerator()
	{}
};
