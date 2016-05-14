#include "client.h"

Client::Client(QObject *parent):
    QObject(parent),
    messenger(new TcpMessenger())
{
	connect(messenger, &TcpMessenger::newMessage,
	        this, &Client::getMessage);
}

Client::~Client()
{
	delete messenger;
	if (tcpServer != nullptr)
		tcpServer->disconnectFromHost();
}

QString Client::getServerIP() const
{
	if (tcpServer == nullptr)
		return "";
	return tcpServer->peerAddress().toString();
}

quint16 Client::getServerPort() const
{
	if (tcpServer == nullptr)
		return 0;
	return tcpServer->peerPort();
}

void Client::connectToServer(const QString &host, quint16 port)
{
	qDebug() << "Connect to" << host << ":" << port;

	if (tcpServer != nullptr)
		tcpServer->disconnectFromHost();
	tcpServer = new QTcpSocket();
	connect(tcpServer, &QTcpSocket::connected,
	        this, &Client::succesfullConnected);
	tcpServer->connectToHost(QHostAddress(host), port);

	connect(tcpServer, &QTcpSocket::readyRead,
	        this, &Client::requestMessage);
	connect(tcpServer, &QTcpSocket::disconnected,
	        tcpServer, &QTcpSocket::deleteLater);
	connect(tcpServer, &QTcpSocket::destroyed,
	        this, &Client::removeSocket);
}

void Client::getMessage(const QString msg)
{
	emit newMessage(msg);
}

void Client::send(const QString &msg)
{
	messenger->send(tcpServer, msg);
}

void Client::removeSocket()
{
	tcpServer = nullptr;
}

void Client::requestMessage()
{
	messenger->get(tcpServer);
}

void Client::succesfullConnected()
{
	emit connected();
}
