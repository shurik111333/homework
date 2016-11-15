#include "mainwindow.h"
#include "Model/Landscape/landscapeGeneratorFixed.h"
#include "Model/Tank/tankSimple.h"
#include <QGraphicsLineItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QtAlgorithms>
#include <QKeyEvent>

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
	qDeleteAll(scene.items());
	drawLandscape(controller->getLandscape());
	auto players = controller->getPlayers();
	for (auto p : players)
	{
		scene.addItem(p->getCannon());
	}
}
