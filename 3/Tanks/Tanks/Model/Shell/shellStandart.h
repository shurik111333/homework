#pragma once

#include "abstractShell.h"

class ShellStandart : public AbstractShell
{
public:
	ShellStandart(double x, double y, double angle, double speed);

	// QGraphicsItem interface
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	// AbstractShell interface
protected:
	virtual double getWeight() override;

private:
	const double weight = 10;
	double width = 0;
	double heigth = 0;
};
