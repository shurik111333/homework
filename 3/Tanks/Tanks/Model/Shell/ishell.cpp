#include "ishell.h"
#include <QtMath>

QPointF IShell::getPoint(double time) const
{
	return QPointF(startX + time * speed * qCos(startAngle),
	               startY + time * speed * qSin(startAngle) - 1.0 / 2 * g * time * time);
}

void IShell::updatePos(double time)
{
	QPointF p1 = getPoint(time);
	QPointF p2 = getPoint(time + 1e-7);
	setPos(p1);
	setRotation(qRadiansToDegrees(qAtan((p2.y() - p1.y()) / (p2.x() - p1.x()))));
}

IShell::IShell(QObject *parent) :
    QObject(parent)
{}

IShell::IShell(double x, double y, double angle, double speed, QObject *parent) :
    QObject(parent),
    startX(x),
    startY(y),
    startAngle(qDegreesToRadians(angle)),
    speed(speed),
    g(9.8)
{}
