#include "gameWindow.h"
#include <QPushButton>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
	mainLayout = new QVBoxLayout();
	widget = new QWidget(this);
	widget->setLayout(mainLayout);
	setCentralWidget(widget);

	auto btNewGame = new QPushButton("New game");
	auto headerLayout = new QHBoxLayout();
	headerLayout->addWidget(btNewGame);
	headerLayout->addStretch();

	view = new QGraphicsView(&scene);
	mainLayout->addLayout(headerLayout);
	mainLayout->addWidget(view);

	view->setFixedSize(sceneSize + viewOffset);
	view->scale(1, -1);
	scene.setSceneRect(QRect(QPoint(0, 0), sceneSize));

	adjustSize();
	setFixedSize(geometry().size());
}

GameWindow::~GameWindow()
{
	delete widget;
}
