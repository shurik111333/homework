#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>

class IShell : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	virtual ~IShell();
	virtual QPointF getPoint(double time) const;
	virtual double getAngle(double time) const;
	virtual void shoot(double impuls);
	virtual void cancelShoot();

signals:
	void updatingPos();

protected:
	IShell(double x, double y, double angle, QObject *parent = 0);
	virtual double getWeight() = 0;

protected slots:
	virtual void updatePos();

private:
	const double g = 9.8;
	double speed = 0;
	double startX = 0;
	double startY = 0;
	double startAngle = 0;
	double time = 0;
	int fps = 60;
	double dt = 3.0 / fps;
	QTimer timer;
};
