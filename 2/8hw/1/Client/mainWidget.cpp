#include "mainWidget.h"
#include "ui_mainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
	ui->setupUi(this);

	client = new Client();

	connect(ui->buttonConnect, &QPushButton::pressed,
	        this, &MainWidget::connectToServer);
	connect(ui->buttonSend, &QPushButton::pressed,
	        this, &MainWidget::send);
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::send()
{
	client->send(ui->lineMessage->text());
}

void MainWidget::connectToServer()
{
	client->connectToServer(ui->lineIP->text(), ui->linePort->text().toInt());
}
