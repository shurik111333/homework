#include "mainwindow.h"
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	auto sizeWindow = QSize(1000, 500);
	this->setMaximumSize(sizeWindow);
	this->setMinimumSize(sizeWindow);

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
}

MainWindow::~MainWindow()
{
	delete mainLayout;
	delete view;
}
