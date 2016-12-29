#pragma once

#include "ishell.h"
#include <QGraphicsPolygonItem>

class ShellStandart : public IShell
{
public:
	ShellStandart(double x, double y, double angle);
	~ShellStandart();

	// QGraphicsItem interface
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	// IShell interface
	virtual double getExplosiveRadius() override;
	virtual void explode() override;

protected:
	virtual double getWeight() override;
	virtual void showCursor() override;
	virtual void hideCursor() override;
	virtual QGraphicsItem *getCursor() const override;

private:
	const double weight = 9;
	double width = 0;
	double heigth = 0;
	QGraphicsPolygonItem *cursor = nullptr;

	void createCursor();
};
