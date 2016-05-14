#include "client.h"

Client::Client(QObject *parent):
    QObject(parent),
    messenger(new TcpMessenger())
{
	connect(messenger, &TcpMessenger::newMessage,
	        this, &Client::newMessage);
}

Client::~Client()
{
	delete messenger;
	delete socketServer;
}

QString Client::getServerIP() const
{
	if (socketServer == nullptr)
		return "";
	return socketServer->peerAddress().toString();
}

quint16 Client::getServerPort() const
{
	if (socketServer == nullptr)
		return 0;
	return socketServer->peerPort();
}

bool Client::isConnected() const
{
	return socketServer != nullptr;
}

void Client::connectToServer(const QString &host, quint16 port)
{
	qDebug() << "Connect to" << host << ":" << port;

	if (socketServer != nullptr)
		socketServer->disconnectFromHost();
	socketServer = new QTcpSocket();

	connect(socketServer, &QTcpSocket::connected,
	        this, &Client::connected);

	socketServer->connectToHost(QHostAddress(host), port);

	connect(socketServer, &QTcpSocket::readyRead,
	        this, &Client::requestMessage);
	connect(socketServer, &QTcpSocket::disconnected,
	        this, &Client::serverDisconnected);
	connect(socketServer, &QTcpSocket::disconnected,
	        socketServer, &QTcpSocket::deleteLater);
	connect(socketServer, &QTcpSocket::destroyed,
	        this, &Client::removeSocket);
}

void Client::send(const QString &msg)
{
	messenger->send(socketServer, msg);
}

void Client::removeSocket()
{
	qDebug() << "Remove socket";
	socketServer = nullptr;
}

void Client::requestMessage()
{
	messenger->get(socketServer);
}
