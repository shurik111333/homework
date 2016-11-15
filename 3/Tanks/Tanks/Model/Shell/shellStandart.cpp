#include "shellStandart.h"
#include <QPainter>
#include <QtMath>

ShellStandart::ShellStandart(double x, double y, double angle, double speed) :
    IShell(x, y, angle, speed),
    width(10),
    heigth(3)
{
	setPos(x, y);
	setRotation(angle);
}

QRectF ShellStandart::boundingRect() const
{
	double ang = qDegreesToRadians(rotation());
	QPointF leftTop(heigth * qCos(M_PI / 2 - ang), heigth * qSin(M_PI / 2 - ang));
	QPointF rightBottom(width * qCos(ang), width * qSin(ang));
	QPointF rightTop = rightBottom + leftTop;

	double leftx = qMin(0.0, qMin(leftTop.x(), qMin(rightBottom.x(), rightTop.x())));
	double lefty = qMin(0.0, qMin(leftTop.y(), qMin(rightBottom.y(), rightTop.y())));
	//return QRectF(-width, -width, width * 2, width * 2);
	return QRectF(leftx, lefty, width * 2, width * 2);
}

void ShellStandart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen(Qt::black, 1);
	painter->setPen(pen);

	painter->fillRect(0, 0, width, heigth, Qt::black);
	painter->drawRect(0, 0, width, heigth);
}
