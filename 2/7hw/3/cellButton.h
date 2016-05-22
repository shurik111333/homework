#pragma once

#include <QtCore/QObject>
#include <QPushButton>

/// Button for a Tic Tac Toe game field
class CellButton : public QPushButton
{
public:
	CellButton(const int x, const int y);

	int x() const;
	int y() const;
	/// @brief Reset button to default state
	void reset();

signals:
	void mySignal();

private:
	// Button's coordinates on field
	int cellX;
	int cellY;
};
