#include "mainWidget.h"
#include "ui_mainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
	ui->setupUi(this);

	this->setWindowTitle("Client");
	ui->lineIP->setText("127.0.0.1");

	client = new Client();

	connect(ui->buttonConnect, &QPushButton::pressed,
	        this, &MainWidget::connectToServer);
	connect(ui->buttonSend, &QPushButton::pressed,
	        this, &MainWidget::send);
	connect(ui->buttonSend, &QPushButton::pressed,
	        ui->lineMessage, &QLineEdit::clear);
	connect(client, &Client::newMessage,
	        this, &MainWidget::getMessage);
	connect(client, &Client::connected,
	        this, &MainWidget::succesfullConnection);
	connect(client, &Client::serverDisconnected,
	        this, &MainWidget::serverDisconnected);
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::addMessage(const QString &sender, const QString &msg)
{
	ui->textMessages->append(sender);
	ui->textMessages->append(msg + "\n");
}

QString MainWidget::getServerHost() const
{
	return client->getServerIP() + ":" + QString::number(client->getServerPort());
}

void MainWidget::send()
{
	QString msg = ui->lineMessage->text();
	client->send(msg);
	addMessage("You", msg);
}

void MainWidget::connectToServer()
{
	ui->textMessages->append("Connecting...");
	client->connectToServer(ui->lineIP->text(), ui->linePort->text().toInt());
}

void MainWidget::getMessage(const QString msg)
{
	addMessage("Server | " + getServerHost(), msg);
}

void MainWidget::succesfullConnection()
{
	ui->textMessages->append("Connected to " + getServerHost() + "\n");
}

void MainWidget::serverDisconnected()
{
	ui->textMessages->append("Connection with server was lost.");
}
