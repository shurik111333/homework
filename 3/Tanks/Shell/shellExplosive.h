#pragma once

#include "ishell.h"

class ShellExplosive : public IShell
{
public:
	ShellExplosive(double x, double y, double angle);

	// QGraphicsItem interface
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	virtual QPainterPath shape() const override;

	// IShell interface
	virtual void showCursor() override;
	virtual void hideCursor() override;
	virtual double getExplosiveRadius() override;
	virtual void explode() override;

protected:
	virtual double getWeight() override;
	virtual QGraphicsItem *getCursor() const override;

private:
	QGraphicsPolygonItem *cursor = nullptr;
	const double weight = 11;
	const double explosiveRadius = 40;
	int r = 3;
	double penWidth = 1;

	void createCursor();
};
