#pragma once

#include <QDebug>
#include <QMessageBox>
#include <QtCore/QObject>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>
#include <QSpinBox>
#include <QSignalMapper>
#include "cellButton.h"
#include "ticTacToe.h"

namespace Ui {
	class MainWidget;
}

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MainWidget(QWidget *parent = 0);
	~MainWidget();

signals:
	void newGame(int size, int chainToWin);

private:
	QSpinBox *boxFieldSize;
	QSpinBox *boxToWin;
	QVBoxLayout *mainLayout;
	QGridLayout *buttonsLayout;
	QLabel *labelPlayerSign;
	QList<CellButton*> buttons;
	TicTacToe *game;
	QSignalMapper *buttonsMapper;
	QMessageBox *winMsg;

	int size;
	static const int minSize = 3;
	static const int maxSize = 10;

	void drawField();
	void createButtons();

private slots:
	void setNewSize();
	void startNewGame();
	void setMaxChainToWin(int size);
	void gameOver(char winner);
	void step(QWidget *widget);
};
