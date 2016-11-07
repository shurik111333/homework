#include "mainwindow.h"
#include "Controllers/landscapecontrollerfixed.h"
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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

	view->setFixedSize(1000, 500);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->scale(1, -1);
	scene.setSceneRect(0, 0, 1000, 500);

	drawLandscape(LandscapeControllerFixed::getInstance()->getLandscape());

	adjustSize();
	setFixedSize(geometry().width(), geometry().height());
}

MainWindow::~MainWindow()
{
	delete mainLayout;
	delete view;
}

void MainWindow::drawLandscape(const QList<QPointF> &land)
{
	for (int i = 1; i < land.length(); i++)
	{
		scene.addLine(QLineF(land[i - 1], land[i]));
	}
}
