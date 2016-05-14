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

	connect(server, &Server::newClient,
	        this, &MainWidget::newClient);
	connect(server, &Server::newMessaage,
	        this, &MainWidget::getMessage);
	connect(server, &Server::clientDisconnected,
	        this, &MainWidget::clientDisconnected);

	connect(ui->buttonSend, &QPushButton::pressed,
	        this, &MainWidget::sendMsg);
	connect(ui->buttonSend, &QPushButton::pressed,
	        ui->lineMessage, &QLineEdit::clear);
}

MainWidget::~MainWidget()
{
	delete ui;
	delete server;
}

void MainWidget::addMessage(const QString &sender, const QString &msg)
{
	ui->textMessages->append(sender);
	ui->textMessages->append(msg + "\n");
}

QString MainWidget::getClientHost() const
{
	return server->getClientIP() + ":" + QString::number(server->getClientPort());
}

void MainWidget::sendMsg()
{
	QString msg = ui->lineMessage->text();
	server->sendMessage(msg);
	addMessage("You", msg);
}

void MainWidget::getMessage(const QString msg)
{
	addMessage("Client | " + getClientHost(), msg);
}

void MainWidget::newClient()
{
	ui->textMessages->append("New client: " + getClientHost() + "\n");
}

void MainWidget::clientDisconnected()
{
	ui->textMessages->append("Client has been disconnected.");
}
