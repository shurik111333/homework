#pragma once

#include "iTank.h"
#include <QDebug>
#include <QBrush>

class TankSimple : public ITank
{
public:
	/**
	 * @brief CannonSimple Simple tank for game
	 * @param x x-coordinate of center
	 * @param y y-coordinate of center
	 * @param brush Tank's brush
	 * @param width Width of tank's body
	 */
	TankSimple(double x, double y, const QBrush &brush, double width = defaultWIdth);
	~TankSimple()
	{
	}

	// QGraphicsItem interface
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	// ITank interface
	virtual IShell *shoot() const override;
	virtual QPointF baseCenter() const override;

private:
	const static double defaultWIdth;
	double scale = 1;
	double bodyw = 0;
	double bodyh = 0;
	double gunw = 0;
	double gunh = 0;
	QBrush brush;

	void drawGun(QPainter *painter);
	void drawBody(QPainter *painter);
	QPointF getGunCoordinates() const;
};
