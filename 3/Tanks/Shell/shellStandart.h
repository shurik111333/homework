#pragma once

#include "ishell.h"
#include <QGraphicsPolygonItem>

class ShellStandart : public IShell
{
public:
	ShellStandart(double x, double y, double angle, double speed);
	~ShellStandart();

	// QGraphicsItem interface
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	// IShell interface
protected:
	virtual double getWeight() override;
	virtual void showCursor() override;
	virtual void hideCursor() override;
	virtual QGraphicsItem *getCursor() const override;

private:
	const double weight = 10;
	double width = 0;
	double heigth = 0;
	QGraphicsPolygonItem *cursor = nullptr;

	void createCursor();
};
