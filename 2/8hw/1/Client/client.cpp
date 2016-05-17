#include "client.h"

Client::Client(QObject *parent) noexcept:
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

QString Client::getServerIP() const noexcept
{
	if (!isConnected())
		return "";
	return socketServer->peerAddress().toString();
}

quint16 Client::getServerPort() const noexcept
{
	if (!isConnected())
		return 0;
	return socketServer->peerPort();
}

bool Client::isConnected() const noexcept
{
	return socketServer != nullptr;
}

void Client::connectToServer(const QString &host, quint16 port) throw(QString)
{
	qDebug() << "Connect to" << host << ":" << port;

	if (socketServer != nullptr)
		socketServer->disconnectFromHost();
	socketServer = new QTcpSocket();
	socketServer->connectToHost(QHostAddress(host), port);
	if (!socketServer->waitForConnected())
		throw QString("Cannot connect to the server");

	connect(socketServer, &QTcpSocket::readyRead,
	        this, &Client::requestMessage);
	connect(socketServer, &QTcpSocket::disconnected,
	        this, &Client::serverDisconnected);
	connect(socketServer, &QTcpSocket::disconnected,
	        socketServer, &QTcpSocket::deleteLater);
	connect(socketServer, &QTcpSocket::destroyed,
	        this, &Client::removeSocket);
}

void Client::send(const QString &msg) throw(QString)
{
	if (!isConnected())
		throw QString("You did not connected to server");
	messenger->send(socketServer, msg);
}

void Client::removeSocket() noexcept
{
	qDebug() << "Remove socket";
	socketServer = nullptr;
}

void Client::requestMessage() const throw(QString)
{
	if (!isConnected())
		throw QString("You did not connected to server");
	messenger->get(socketServer);
}
