#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Controllers/gameController.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	QVBoxLayout *mainLayout = nullptr;
	QGraphicsScene scene;
	QGraphicsView *view = nullptr;
	GameController *controller = nullptr;
	QGraphicsTextItem *playerName = nullptr;

	void drawLandscape(const QList<QPointF> &land);

private slots:
	void newGame();
	void nextPlayer(IPlayer *player);
};
