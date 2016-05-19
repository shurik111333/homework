#pragma once

#include <QtCore/QObject>
#include <QList>

class TicTacToe : public QObject
{
	Q_OBJECT
public:
	explicit TicTacToe(QObject *parent = 0);

	char getPlayer() const;

signals:
	void gameOver(char winner) const;

public slots:
	void newGame(int size, int winChain);
	void doStep(int x, int y);

private:
	QList<QList<char>> field;
	int currentPlayer = 0;
	const char emptyCell = '.';
	const char player[2] = {'X', 'O'};
	int win = 0;
	int size = 0;
	int lastX = 0;
	int lastY = 0;
	bool isFirst = true;

	void createField();
	void checkWin() const;
	void checkChain(int dx, int dy) const;
	bool inField(int x, int y) const;
};
