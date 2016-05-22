#include "ticTacToe.h"
#include <bits/stdc++.h>
#include <QDebug>
using std::cerr;

TicTacToe::TicTacToe(QObject *parent):
    QObject(parent)
{
	connect(this, &TicTacToe::gameOver,
	        this, &TicTacToe::endGame);
}

char TicTacToe::getPlayer() const
{
	return player[currentPlayer];
}

char TicTacToe::getStartPlayer() const
{
	return player[0];
}

void TicTacToe::newGame(int size, int winChain)
{
	isStart = true;
	isOver = false;
	win = winChain;
	this->size = size;
	currentPlayer = 0;

}

void TicTacToe::doStep(int x, int y)
{
	if (isStart)
		createField();
	if (isOver || field[x][y] != emptyCell)
		return;
	lastX = x;
	lastY = y;
	field[x][y] = getPlayer();
	emit stepIsDone(x, y, getPlayer());
	checkWin();
	currentPlayer = (currentPlayer + 1) % 2;
}

void TicTacToe::createField()
{
	field.clear();
	for (int i = 0; i < size; i++)
	{
		field.push_back(QList<char>());
		for (int j = 0; j < size; j++)
			field[i].push_back(emptyCell);
	}
	isStart = false;
}

void TicTacToe::checkWin() const
{
	checkChain(-1, -1);
	checkChain(1, -1);
	checkChain(1, 0);
	checkChain(0, 1);
}

void TicTacToe::checkChain(int dx, int dy) const
{
	int cnt = 0;
	int x = lastX + dx;
	int y = lastY + dy;
	for (; inField(x, y) && field[x][y] == getPlayer(); x += dx, y += dy)
		cnt++;

	x = lastX - dx;
	y = lastY - dy;
	for (; inField(x, y) && field[x][y] == getPlayer(); x -= dx, y -= dy)
		cnt++;

	if (cnt + 1 == win)
		emit gameOver(getPlayer());
}

bool TicTacToe::inField(int x, int y) const
{
	return (x >= 0 && x < size && y >= 0 && y < size);
}

void TicTacToe::endGame()
{
	isOver = true;
}
