#pragma once

#include <QtCore/QObject>
#include <QList>

/// Represents game logic in TicTacToe game.
class TicTacToe : public QObject
{
	Q_OBJECT

public:
	explicit TicTacToe(QObject *parent = 0);

	/// @return Sign of current player
	char getPlayer() const;
	/// @return Sign of player, which start game
	char getStartPlayer() const;

signals:
	/**
	 * @brief gameOver Emits, when game is over
	 * @param winner Sign of winning player
	 */
	void gameOver(char winner) const;
	/**
	 * @brief stepIsDone Emits when step has confirmed
	 * @param x x-coordinate on field of current step
	 * @param y y-coordinate on field of current step
	 * @param player Sign of player, that do current step
	 */
	void stepIsDone(int x, int y, char player) const;

public slots:
	/// @brief Start new game with new parameters
	void newGame(int size, int winChain);
	/// @brief Do step in cell with input coordinates.
	/// It creates field on the first step in the game.
	void doStep(int x, int y);

private:
	QList<QList<char>> field;
	int currentPlayer = 0;
	const char emptyCell = '.';
	const char player[2] = {'X', 'O'};
	// length of chain to win
	int win = 0;
	int size = 0;
	// coordiantes of the last step, include current
	int lastX = 0;
	int lastY = 0;
	// true before first step in the game and false after
	bool isStart = true;
	// true, if game is over
	bool isOver = false;

	/// @brief Creates new game field
	void createField();
	/// @brief Checks end of the game after step.
	/// Emits gameOver() if one of the players wins
	void checkWin() const;
	/// @brief Checks length of chain, which passes through (lastX, lastY) in directions (dx, dy) and (-dx, -dy)
	void checkChain(int dx, int dy) const;
	/// @brief Checks, that point (x, y) is in game field
	bool inField(int x, int y) const;

private slots:
	/// @brief Calls when game is over
	void endGame();
};
