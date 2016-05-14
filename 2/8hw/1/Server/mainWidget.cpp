#include "mainWidget.h"
#include "ui_mainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
	ui->setupUi(this);

	this->setWindowTitle("Server");
	server = new Server();

	ui->lineIP->setText(server->getMyIP());
	ui->linePort->setText(QString::number(server->getMyPort()));

	connect(server, &Server::newMessaage,
	        ui->textMessages, &QTextEdit::setText);
	connect(ui->buttonSend, &QPushButton::pressed,
	        this, &MainWidget::sendMsg);
}

MainWidget::~MainWidget()
{
	delete ui;
	delete server;
}

void MainWidget::sendMsg()
{
	server->sendMessage(ui->lineMessage->text());
}
