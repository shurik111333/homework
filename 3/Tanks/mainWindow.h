#pragma once

#include "gameWindow.h"
#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	void comingSoon() const;
	void showGameWindow(GameWindow *window);

private slots:
	void localGame();
	void netServerGame();
	void connectToGame();
};
