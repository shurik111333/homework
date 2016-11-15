#pragma once

#include <QObject>
#include <QGraphicsItem>

class IShell : public QObject, public QGraphicsItem
{
public:
	virtual QPointF getPoint(double time) const;
	virtual void updatePos(double time);

protected:
	explicit IShell(QObject *parent = 0);
	explicit IShell(double x, double y, double angle, double speed, QObject *parent = 0);

private:
	double g = 9.8;
	double speed = 0;
	double startX = 0;
	double startY = 0;
	double startAngle = 0;
};
