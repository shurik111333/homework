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
	connect(ui->buttonServerNetGame, &QPushButton::clicked, this, &MainWindow::netServerGame);
	connect(ui->buttonConnect, &QPushButton::clicked, this, &MainWindow::connectToGame);
}

MainWindow::~MainWindow()
{
	disconnect(ui->buttonLocalGame, &QPushButton::clicked, this, &MainWindow::localGame);
	disconnect(ui->buttonServerNetGame, &QPushButton::clicked, this, &MainWindow::netServerGame);
	disconnect(ui->buttonConnect, &QPushButton::clicked, this, &MainWindow::connectToGame);
	delete ui;
}

void MainWindow::comingSoon() const
{
	auto box = new QMessageBox(QMessageBox::Information, "", "Coming soon!", QMessageBox::Ok);
	box->setAttribute(Qt::WA_DeleteOnClose);
	box->show();
}

void MainWindow::localGame()
{
	Settings::instance()->newLocalGame();
	auto game = new GameWindow();
	game->setAttribute(Qt::WA_DeleteOnClose);
	game->show();
	setEnabled(false);
	connect(game, &GameWindow::destroyed, this, &MainWindow::onGameWindowClose);
}

void MainWindow::netServerGame() const
{
	comingSoon();
}

void MainWindow::connectToGame() const
{
	comingSoon();
}

void MainWindow::onGameWindowClose()
{
	setEnabled(true);
}
