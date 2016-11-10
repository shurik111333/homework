#pragma once

#include "icannon.h"
#include <QDebug>
#include <QBrush>

class CannonSimple : public ICannon
{
public:
	/**
	 * @brief CannonSimple Simple cannon for game
	 * @param x x-coordinate of center
	 * @param y y-coordinate of center
	 * @param brush Cannon's brush
	 * @param width Width of cannon's body
	 */
	CannonSimple(double x, double y, const QBrush &brush, double width = defaultWIdth);
	~CannonSimple()
	{
	}


	// QGraphicsItem interface
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
	const static double defaultWIdth;
	double bodyw = 0;
	double bodyh = 0;
	double gunw = 0;
	double gunh = 0;
	QPointF center;
	QRectF body;
	QRectF gun;
	QBrush brush;
};
