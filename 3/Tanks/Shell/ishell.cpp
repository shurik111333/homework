#include "ishell.h"
#include <QtMath>
#include <QGraphicsScene>
#include <QDebug>

QDEBUG_H

IShell::~IShell()
{
	disconnect(&timer, &QTimer::timeout, this, &IShell::updatePos);
}

QPointF IShell::getPoint(double time) const
{
	return QPointF(startX + time * speed * qCos(startAngle),
	               startY + time * speed * qSin(startAngle) - g * time * time / 2);
}

double IShell::getAngle(double time) const
{
	double dx = speed * qCos(startAngle);
	double dy = speed * qSin(startAngle) - g * time;
	return qRadiansToDegrees(qAtan(dy / dx)) + (dx < 0 ? 180 : 0);
}

void IShell::updatePos()
{
	time += dt;
	setPos(getPoint(time));
	getCursor()->setPos(getPoint(time).x(), scene()->sceneRect().bottom());
	setRotation(getAngle(time));
	emit updatingPos();
}

void IShell::shoot(double impuls)
{
	timer.stop();
	time = 0;
	speed = impuls / getWeight();
	timer.start(1000 / fps);
}

void IShell::cancelShoot()
{
	timer.stop();
}

IShell::IShell(double x, double y, double angle, QObject *parent) :
    QObject(parent),
    startX(x),
    startY(y),
    startAngle(qDegreesToRadians(angle))
{
	setPos(x, y);
	setRotation(angle);
	connect(&timer, &QTimer::timeout, this, &IShell::updatePos);
}
