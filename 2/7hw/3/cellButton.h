#pragma once

#include <QtCore/QObject>
#include <QPushButton>

class CellButton : public QPushButton
{
public:
	CellButton(const int x, const int y);

	int x() const;
	int y() const;
	void reset();

signals:
	void mySignal();

private:
	int cellX;
	int cellY;
};
