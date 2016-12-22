#pragma once

#include "Player/iplayer.h"
#include "Tank/iTank.h"
#include "Landscape/iLandscapeGenerator.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>

namespace Ui {
	class GameWindow;
}

class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit GameWindow(QWidget *parent = 0);
	~GameWindow();

private:
	QWidget *widget = nullptr;
	QVBoxLayout *mainLayout = nullptr;
	QGraphicsScene scene;
	QGraphicsView *view = nullptr;
	QGraphicsTextItem *playerName = nullptr;
	QSize sceneSize = QSize(1000, 500);
	QSize viewOffset = QSize(3, 3);
	bool f = false;

	void drawLandscape(const QList<QPointF> &land);
	void clearScene();

private slots:
	void newGame(const QVector<IPlayer *> &players);
	void newGameCLicked();

	// QObject interface
public:
	virtual bool eventFilter(QObject *watched, QEvent *event) override;
};
