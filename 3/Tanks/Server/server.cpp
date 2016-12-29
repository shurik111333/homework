#include "server.h"

Server::Server(QObject *parent) throw(QString):
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
		throw QString("Cannot listen yor network devices. Please, check it and try again.");
}

Server::~Server()
{
	delete tcpServer;
	delete socketClient;
}

QHostAddress Server::getMyIP() const noexcept
{
	return tcpServer->serverAddress();
}

quint16 Server::getMyPort() const noexcept
{
	return tcpServer->serverPort();
}

QString Server::getClientIP() const noexcept
{
	if (!isConnected())
		return "";
	return socketClient->peerAddress().toString();
}

quint16 Server::getClientPort() const noexcept
{
	if (!isConnected())
		return 0;
	return socketClient->peerPort();
}

bool Server::isConnected() const noexcept
{
	return socketClient != nullptr;
}

QTcpServer *Server::getServer() const
{
	return tcpServer;
}

bool Server::tryToListen(const QHostAddress &address) const noexcept
{
	if (!tcpServer->listen(address))
		return false;
	connect(tcpServer, &QTcpServer::newConnection,
	        this, &Server::newConnection);
	qDebug() << "Server listen at" << tcpServer->serverAddress().toString()
	         << ":" << tcpServer->serverPort();
	return true;
}

void Server::newConnection() noexcept
{
	if (!tcpServer->hasPendingConnections())
		return;
	socketClient = tcpServer->nextPendingConnection();

	connect(socketClient, &QTcpSocket::disconnected,
	        this, &Server::clientDisconnected);
	connect(socketClient, &QTcpSocket::disconnected,
	        socketClient, &QTcpSocket::deleteLater);
	connect(socketClient, &QTcpSocket::destroyed,
	        this, &Server::removeClient);

	emit newClient(socketClient);

	qDebug() << "New connection from" << socketClient->peerAddress().toString()
	         << ":" << QString::number(socketClient->peerPort());
}

void Server::removeClient() noexcept
{
	socketClient = nullptr;
}
