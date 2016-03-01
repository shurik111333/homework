#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QObject::connect(ui->horizontalSlider, &QSlider::valueChanged,
	                 ui->progressBar, &QProgressBar::setValue);
}

MainWindow::~MainWindow()
{
	delete ui;
}
