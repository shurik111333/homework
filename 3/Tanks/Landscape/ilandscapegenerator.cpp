#include "iLandscapeGenerator.h"
#include <QtMath>
#include <QSet>

QPair<QPointF, QPointF> ILandscapeGenerator::getSegment(double x) const
{
	if (x <= landscape[0].x())
		return { landscape[0], landscape[1] };
	if (x > landscape.last().x())
		return { landscape[landscape.size() - 2], landscape.last() };
	int l = 0;
	int r = landscape.size() - 1;
	while (r - l > 1)
	{
		int m = (l + r) / 2;
		if (x <= landscape[m].x())
			r = m;
		else
			l = m;
	}
	if (x <= landscape[r].x())
		return { landscape[l], landscape[l + 1] };
	else
		return { landscape[r], landscape[r + 1] };
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
