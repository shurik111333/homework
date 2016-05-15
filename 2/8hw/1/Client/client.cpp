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
	if (!isConnected())
		return "";
	return socketServer->peerAddress().toString();
}

quint16 Client::getServerPort() const
{
	if (!isConnected())
		return 0;
	return socketServer->peerPort();
}

bool Client::isConnected() const
{
	return socketServer != nullptr;// && socketServer->isValid();
}

void Client::connectToServer(const QString &host, quint16 port)
{
	qDebug() << "Connect to" << host << ":" << port;

	if (socketServer != nullptr)
		socketServer->disconnectFromHost();
	socketServer = new QTcpSocket();

//	connect(socketServer, &QTcpSocket::connected,
//	        this, &Client::connected);
//	connect(socketServer, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),
//	        this, &Client::connectionError);

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

void Client::send(const QString &msg)
{
	if (!isConnected())
		throw QString("You did not connected to server");
	messenger->send(socketServer, msg);
}

void Client::removeSocket()
{
	qDebug() << "Remove socket";
	socketServer = nullptr;
}

void Client::requestMessage()
{
	if (!isConnected())
		throw QString("You did not connected to server");
	messenger->get(socketServer);
}

void Client::connectionError(const QAbstractSocket::SocketError error)
{
	//throw QString("Cannot connect to the server.");
	delete socketServer;
}
