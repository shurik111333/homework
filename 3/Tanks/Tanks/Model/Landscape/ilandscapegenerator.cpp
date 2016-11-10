#include "iLandscapeGenerator.h"

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
