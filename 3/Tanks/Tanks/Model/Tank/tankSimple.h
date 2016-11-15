#pragma once

#include "iTank.h"
#include <QDebug>
#include <QBrush>

class TankSimple : public ITank
{
public:
	/**
	 * @brief CannonSimple Simple cannon for game
	 * @param x x-coordinate of center
	 * @param y y-coordinate of center
	 * @param brush Cannon's brush
	 * @param width Width of cannon's body
	 */
	TankSimple(double x, double y, const QBrush &brush, double width = defaultWIdth);
	~TankSimple()
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
	QBrush brush;

	void drawGun(QPainter *painter);
	void drawBody(QPainter *painter);
};
