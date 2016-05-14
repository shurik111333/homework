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
	connect(server, &QTcpSocket::disconnected,
	        server, &QTcpSocket::deleteLater);
}

void Client::send(const QString &msg)
{
	quint16 size = msg.length() + 1;
	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
	out << size << msg.toUtf8() << '\0';
	server->write(data);
	qDebug() << "Send. Size:" << size << ", data:" << data;
}
