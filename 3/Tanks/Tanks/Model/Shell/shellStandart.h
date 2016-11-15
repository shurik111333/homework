#pragma once

#include "ishell.h"

class ShellStandart : public IShell
{
public:
	ShellStandart(double x, double y, double angle, double speed);

	// QGraphicsItem interface
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
	double width = 0;
	double heigth = 0;
};
