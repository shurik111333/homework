#include "mainwindow.h"
#include "Model/Landscape/landscapeGeneratorFixed.h"
#include "Model/Tank/tankSimple.h"
#include <QGraphicsLineItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QtAlgorithms>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QTransform>

QDEBUG_H

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      controller(new GameController())
{
	mainLayout = new QVBoxLayout();
	auto widget = new QWidget(this);
	widget->setLayout(mainLayout);
	setCentralWidget(widget);

	auto btNewGame = new QPushButton("New game");
	auto headerLayout = new QHBoxLayout();
	headerLayout->addWidget(btNewGame);
	headerLayout->addStretch();

	view = new QGraphicsView(&scene);
	mainLayout->addLayout(headerLayout);
	mainLayout->addWidget(view);

	view->setFixedSize(1003, 503);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->scale(1, -1);
	scene.setSceneRect(0, 0, 1000, 500);

	adjustSize();
	setFixedSize(geometry().width(), geometry().height());

	connect(controller, &GameController::newGame, this, &MainWindow::newGame);
	connect(btNewGame, &QPushButton::clicked, controller, &GameController::startGame);
	connect(controller, &GameController::nextPlayer, this, &MainWindow::nextPlayer);
	controller->startGame();
}

MainWindow::~MainWindow()
{
	delete mainLayout;
	delete view;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	controller->keyPress((Qt::Key)event->key());
}

void MainWindow::drawLandscape(const QList<QPointF> &land)
{
	for (int i = 1; i < land.length(); i++)
	{
		scene.addLine(QLineF(land[i - 1], land[i]));
	}
}

void MainWindow::newGame()
{
	scene.clear();
	drawLandscape(controller->getLandscape());
	auto players = controller->getPlayers();
	for (auto p : players)
	{
		scene.addItem(p->getTank());
	}
}

void MainWindow::nextPlayer(IPlayer *player)
{
	/*scene.removeItem(playerName);
	delete playerName;
	playerName = scene.addText(player->getName());
	//playerName->setRotation(180);
	//playerName->setTransform(QTransform(1, 0, -1, 0, 0 ,0));
	playerName->setPos(100, 100);
	playerName->setDefaultTextColor(player->getColor());*/
}
