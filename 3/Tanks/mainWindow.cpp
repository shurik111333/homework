#include "mainWindow.h"
#include "ui_mainWindow.h"
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

void MainWindow::showGameWindow(GameWindow *window)
{
	window->setAttribute(Qt::WA_DeleteOnClose);
	window->show();
	hide();
	connect(window, &GameWindow::closing, this, &MainWindow::show);
}

void MainWindow::localGame()
{
	Settings::instance()->newLocalGame();
	auto game = new GameWindow();
	showGameWindow(game);
}

void MainWindow::netServerGame()
{
	Settings::instance()->newServerGame();
	auto game = new GameWindow();
	game->serverGame(Settings::instance()->getIP(), Settings::instance()->getPort());
	showGameWindow(game);
}

void MainWindow::connectToGame()
{
	Settings::instance()->newClientGame(QHostAddress(ui->lineIP->text()),
	                                    ui->linePort->text().toInt());
	auto game = new GameWindow();
	game->clientGame();
	showGameWindow(game);
}
