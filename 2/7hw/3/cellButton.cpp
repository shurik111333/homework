#include "cellButton.h"

CellButton::CellButton(const int x, const int y):
    cellX(x),
    cellY(y)
{}

int CellButton::x() const
{
	return cellX;
}

int CellButton::y() const
{
	return cellY;
}

void CellButton::reset()
{
	setText("");
	setEnabled(true);
}
