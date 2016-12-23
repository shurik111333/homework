#pragma once

#include "Player/iplayer.h"
#include "Tank/iTank.h"
#include "Landscape/iLandscapeGenerator.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QVector>
#include <QLabel>
#include <QString>

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
	QPushButton *buttonNewGame = nullptr;
	QLabel *labelWinner = nullptr;
	QSize sceneSize = QSize(1000, 500);
	QSize viewOffset = QSize(3, 3);
	bool f = false;

	void drawLandscape(const QVector<QPointF> &land);
	void endOfGame(IPlayer *winner);


private slots:
	void newGame(const QVector<IPlayer *> &players);
	QString getWinnerMessage(IPlayer *winner);
	// QObject interface
public:
	virtual bool eventFilter(QObject *watched, QEvent *event) override;
};
