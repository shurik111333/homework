#include "mainWindow.h"
#include "ui_mainWindow.h"
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
	connect(box, &QMessageBox::accepted, box, &QMessageBox::deleteLater);
	box->exec();
}

void MainWindow::localGame() const
{
	comingSoon();
}

void MainWindow::netGame() const
{
	comingSoon();
}

void MainWindow::createMap() const
{
	comingSoon();
}
