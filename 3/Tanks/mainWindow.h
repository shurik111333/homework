#pragma once

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

private slots:
	void localGame();
	void netServerGame();
	void connectToGame();
	void onGameWindowClose();
};
