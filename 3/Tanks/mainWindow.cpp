#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "gameWindow.h"
#include "settings.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->buttonLocalGame, &QPushButton::clicked, this, &MainWindow::localGame);
	connect(ui->buttonNetGame, &QPushButton::clicked, this, &MainWindow::netGame);
	connect(ui->buttonCreateMap, &QPushButton::clicked, this, &MainWindow::createMap);
}

MainWindow::~MainWindow()
{
	disconnect(ui->buttonLocalGame, &QPushButton::clicked, this, &MainWindow::localGame);
	disconnect(ui->buttonNetGame, &QPushButton::clicked, this, &MainWindow::netGame);
	disconnect(ui->buttonCreateMap, &QPushButton::clicked, this, &MainWindow::createMap);
	delete ui;
}

void MainWindow::comingSoon() const
{
	auto box = new QMessageBox(QMessageBox::Information, "", "Coming soon!", QMessageBox::Ok);
	box->setAttribute(Qt::WA_DeleteOnClose);
	box->show();
}

void MainWindow::localGame() const
{
	Settings::instance()->newLocalGame();
	auto game = new GameWindow();
	game->setAttribute(Qt::WA_DeleteOnClose);
	game->show();
}

void MainWindow::netGame() const
{
	comingSoon();
}

void MainWindow::createMap() const
{
	comingSoon();
}
