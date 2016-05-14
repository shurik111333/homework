#include "server.h"

Server::Server(QObject *parent):
    QObject(parent)
{
	tcpServer = new QTcpServer(this);

	QList<QHostAddress> adresses = QNetworkInterface::allAddresses();
	for (auto adress : adresses)
	{
		if (adress.protocol() == QAbstractSocket::IPv4Protocol)
			if (tryToListen(adress))
				break;
	}
	if (!tcpServer->isListening())
		tryToListen(QHostAddress(QHostAddress::LocalHost));

	messenger = new TcpMessenger();
	connect(messenger, &TcpMessenger::newMessage,
	        this, &Server::getMessage);
}

Server::~Server()
{
	delete messenger;
	delete tcpServer;
	delete tcpClient;
}

QString Server::getMyIP() const
{
	return tcpServer->serverAddress().toString();
}

quint16 Server::getMyPort() const
{
	return tcpServer->serverPort();
}

QString Server::getClientIP() const
{
	if (tcpClient == nullptr)
		return "";
	return tcpClient->peerAddress().toString();
}

quint16 Server::getClientPort() const
{
	if (tcpClient == nullptr)
		return 0;
	return tcpClient->peerPort();
}

void Server::sendMessage(const QString msg)
{
	messenger->send(tcpClient, msg);
}

QHostAddress Server::getIP() const
{
	QList<QHostAddress> adresses = QNetworkInterface::allAddresses();
	for (auto adress : adresses)
	{
		if (adress.protocol() == QAbstractSocket::IPv4Protocol)
			return adress;
	}
	return QHostAddress(QHostAddress::LocalHost);
}

bool Server::tryToListen(const QHostAddress &address)
{
	if (!tcpServer->listen(address))
		return false;
	connect(tcpServer, &QTcpServer::newConnection,
	        this, &Server::newConnection);
	qDebug() << "Server listen at" << tcpServer->serverAddress().toString()
	         << ":" << tcpServer->serverPort();
	return true;
}

void Server::getMessage(const QString msg)
{
	emit newMessaage(msg);
}

void Server::newConnection()
{
	tcpClient = tcpServer->nextPendingConnection();

	connect(tcpClient, &QTcpSocket::readyRead,
	        this, &Server::requestMessage);

	connect(tcpClient, &QTcpSocket::disconnected,
	        tcpClient, &QTcpSocket::deleteLater);
	connect(tcpClient, &QTcpSocket::destroyed,
	        this, &Server::removeClient);

	emit newClient();

	qDebug() << "New connection from" << tcpClient->peerAddress().toString()
	         << ":" << QString::number(tcpClient->peerPort());
}

void Server::requestMessage()
{
	messenger->get(tcpClient);
}

void Server::removeClient()
{
	tcpClient = nullptr;
}
