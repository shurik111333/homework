#include "client.h"

Client::Client(QObject *parent):
    QObject(parent)
{

}

void Client::connectToServer(const QString &host, quint16 port)
{
	if (server != nullptr)
		server->disconnectFromHost();
	qDebug() << "Connect to" << host << ":" << port;
	server = new QTcpSocket();
	server->connectToHost(QHostAddress(host), port);
	connect(server, &QTcpSocket::readyRead,
	        this, &Client::getMessage);
	connect(server, &QTcpSocket::disconnected,
	        server, &QTcpSocket::deleteLater);
}

void Client::getMessage()
{

}

void Client::send(const QString &msg)
{

}
