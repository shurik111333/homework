#include "iLandscapeGenerator.h"
#include <QtMath>

QPair<QPointF, QPointF> ILandscapeGenerator::getSegment(double x) const
{
	QPointF left = landscape[0];
	QPointF right;
	for (auto p : landscape)
	{
		right = p;
		if (p.x() < x)
		{
			left = p;
			continue;
		}
		break;
	}
	if (left == right)
		right = landscape[1];
	return { left, right };
}

QPointF ILandscapeGenerator::getPoint(double x) const
{
	auto seg = getSegment(x);
	QPointF left = seg.first;
	QPointF right = seg.second;

	double y = left.y() + (right.y() - left.y()) * ((x - left.x()) / (right.x() - left.x()));
	return QPointF(x, y);
}

QPointF ILandscapeGenerator::getLeftBorder() const
{
	return landscape[0];
}

QPointF ILandscapeGenerator::getRightBorder() const
{
	return landscape[landscape.length() - 1];
}

bool ILandscapeGenerator::inLandscape(double x) const
{
	return x >= getLeftBorder().x() && x <= getRightBorder().x();
}

QPointF ILandscapeGenerator::toLandscape(double x, double y) const
{
	return toLandscape(QPointF(x, y));
}

QPointF ILandscapeGenerator::toLandscape(const QPointF &p) const
{
	if (inLandscape(p.x()))
		return p;
	if (p.x() < getLeftBorder().x())
		return getLeftBorder();
	return getRightBorder();
}

double ILandscapeGenerator::getLandscapeAngle(const QPointF &p) const
{
	auto seg = getSegment(p.x());
	double tg = (double)(seg.second.y() - seg.first.y()) / (seg.second.x() - seg.first.x());
	return qRadiansToDegrees(qAtan(tg));
}
