#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include "ticTacToe.h"

class TicTacToeTest : public QObject
{
	Q_OBJECT

public:
	explicit TicTacToeTest(QObject *parent = 0):
	    QObject(parent)
	{
		connect(&game, &TicTacToe::gameOver,
		        this, &TicTacToeTest::getWinner);
	}

public slots:
	void getWinner(char winner)
	{
		this->winner = winner;
	}

private:
	TicTacToe game;
	char winner = '\0';
	int size = 10;
	int winLength = 4;

private slots:
	void init()
	{
		game.newGame(size, winLength);
	}

	void cleanup()
	{
		winner = '\0';
	}

	// Player X --------------

	void testWinHorizontalChainPlayerX()
	{
		for (int i = 0; i < winLength; i++)
		{
			game.doStep(0, i);
			game.doStep(1, i);
			if (i < winLength - 1)
				QCOMPARE(winner, '\0');
			else
				QCOMPARE(winner, 'X');
		}
	}

	void testWinVerticalChainPlayerX()
	{
		for (int i = 0; i < winLength; i++)
		{
			game.doStep(i, 3);
			game.doStep(i, 4);
			if (i < winLength - 1)
				QCOMPARE(winner, '\0');
			else
				QCOMPARE(winner, 'X');
		}
	}

	void testMainDiagonalChainPlayerX()
	{
		for (int i = 0; i < winLength; i++)
		{
			game.doStep(i, i);
			game.doStep(i + 1, i);
			if (i < winLength - 1)
				QCOMPARE(winner, '\0');
			else
				QCOMPARE(winner, 'X');
		}
	}

	void testMinorDiagonalChainPlayerX()
	{
		for (int i = 0; i < winLength; i++)
		{
			game.doStep(size - 1 - i, i);
			game.doStep(size - 2 - i, i);
			if (i < winLength - 1)
				QCOMPARE(winner, '\0');
			else
				QCOMPARE(winner, 'X');
		}
	}

	// Player O -----------------------

	void testWinHorizontalChainPlayerO()
	{
		for (int i = 0; i < winLength; i++)
		{
			if (i < winLength - 1)
				game.doStep(0, i);
			else
				game.doStep(size - 1, size - 1);
			game.doStep(1, i);
			if (i < winLength - 1)
				QCOMPARE(winner, '\0');
			else
				QCOMPARE(winner, 'O');
		}
	}

	void testWinVerticalChainPlayerO()
	{
		for (int i = 0; i < winLength; i++)
		{
			if (i < winLength - 1)
				game.doStep(i, 3);
			else
				game.doStep(size - 1, size - 1);
			game.doStep(i, 4);
			if (i < winLength - 1)
				QCOMPARE(winner, '\0');
			else
				QCOMPARE(winner, 'O');
		}
	}

	void testMainDiagonalChainPlayerO()
	{
		for (int i = 0; i < winLength; i++)
		{
			if (i < winLength - 1)
				game.doStep(i, i);
			else
				game.doStep(size - 1, size - 1);
			game.doStep(i + 1, i);
			if (i < winLength - 1)
				QCOMPARE(winner, '\0');
			else
				QCOMPARE(winner, 'O');
		}
	}

	void testMinorDiagonalChainPlayerO()
	{
		for (int i = 0; i < winLength; i++)
		{
			if (i < winLength - 1)
				game.doStep(size - 1 - i, i);
			else
				game.doStep(size - 1, size - 1);

			game.doStep(size - 2 - i, i);
			if (i < winLength - 1)
				QCOMPARE(winner, '\0');
			else
				QCOMPARE(winner, 'O');
		}
	}
};
