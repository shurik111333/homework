#include "abstractShell.h"
#include <QtMath>
#include <QGraphicsScene>
#include <QDebug>

QDEBUG_H

AbstractShell::~AbstractShell()
{
	disconnect(&timer, &QTimer::timeout, this, &AbstractShell::updatePos);
	delete cursor;
}

QPointF AbstractShell::getPoint(double time) const
{
	return QPointF(startX + time * speed * qCos(startAngle),
	               startY + time * speed * qSin(startAngle) - g * time * time / 2);
}

double AbstractShell::getAngle(double time) const
{
	double dx = speed * qCos(startAngle);
	double dy = speed * qSin(startAngle) - g * time;
	return qRadiansToDegrees(qAtan(dy / dx)) + (dx < 0 ? 180 : 0);
}

void AbstractShell::updatePos()
{
	time += dt;
	auto p = getPoint(time);
	setPos(p);
	if (cursor != nullptr && cursor->isVisible())
		cursor->setPos(p.x(), scene()->sceneRect().bottom());
	setRotation(getAngle(time));
	emit updatingPos();
}

void AbstractShell::createCursor()
{
	if (cursor != nullptr)
		return;
	QPointF ver(0, 0);
	auto points = QVector<QPointF> { ver, ver - QPointF(10, 10), ver + QPointF(10, -10) };
	cursor = new QGraphicsPolygonItem(QPolygonF(points));
	cursor->hide();
	scene()->addItem(cursor);
}

void AbstractShell::shoot(double impuls)
{
	timer.stop();
	time = 0;
	speed = impuls / getWeight();
	timer.start(1000 / fps);
}

void AbstractShell::cancelShoot()
{
	timer.stop();
}

void AbstractShell::showCursor()
{
	createCursor();
	cursor->show();
}

void AbstractShell::hideCursor()
{
	if (cursor == nullptr)
		return;
	cursor->hide();
}

AbstractShell::AbstractShell(double x, double y, double angle, QObject *parent) :
    QObject(parent),
    startX(x),
    startY(y),
    startAngle(qDegreesToRadians(angle))
{
	connect(&timer, &QTimer::timeout, this, &AbstractShell::updatePos);
}
