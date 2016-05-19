#pragma once

#include <QtCore/QObject>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>
#include <QSpinBox>
#include "cellButton.h"

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
	Ui::MainWidget *ui;
	QSpinBox *boxFieldSize;
	QSpinBox *boxToWin;
	QVBoxLayout *mainLayout;
	QGridLayout *buttonsLayout;
	QList<CellButton*> buttons;
	int size;
	static const int minSize = 3;
	static const int maxSize = 10;

	void drawField();
	void removeField();
	void createButtons();

private slots:
	void setNewSize();
	void startNewGame();
	void setMaxChainToWin(int size);
};
