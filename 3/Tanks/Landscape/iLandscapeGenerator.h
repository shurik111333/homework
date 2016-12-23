#pragma once

#include <QVector>
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
	virtual const QVector<QPointF> &nextLandscape() = 0;
	/**
	 * @brief getLandscape Generate landscape of the map that represented by polygonal chain.
	 * @return List of vertices of the polygonal chain.
	 * First vertex located at the left border of the map, last - at the right border.
	 */
	virtual const QVector<QPointF> &getLandscape() const = 0;
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
	/**
	 * @return Point on the left border of the landscape
	 */
	virtual QPointF getLeftBorder() const;
	/**
	 * @return Point on the right border on the landscape
	 */
	virtual QPointF getRightBorder() const;
	/**
	 * @brief inLandscape Checks if x-coordinate stay in landscape
	 * @param x
	 * @return True, if x-coordinate stay in landscape
	 */
	virtual bool inLandscape(double x) const;
	/**
	 * @brief toLandscape Look at toLandscape(QPointF)
	 */
	virtual QPointF toLandscape(double x, double y) const;
	/**
	 * @brief toLandscape
	 * @param p
	 * @return
	 */
	virtual QPointF toLandscape(const QPointF &p) const;
	virtual double getLandscapeAngle(const QPointF &p) const;

protected:
	QVector<QPointF> landscape;

	ILandscapeGenerator()
	{}
};
