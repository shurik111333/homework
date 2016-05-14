#include "mainWidget.h"
#include "ui_mainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
	ui->setupUi(this);

	this->setWindowTitle("Server");
	server = new Server();
}

MainWidget::~MainWidget()
{
	delete ui;
	delete server;
}
