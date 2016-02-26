#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QObject::connect(ui->horizontalSlider, &ui->horizontalSlider->valueChanged,
	                 ui->progressBar, &ui->progressBar->setValue);
}

MainWindow::~MainWindow()
{
	delete ui;
}
