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
//	clientIP = tcpSocket->peerAddress();
//	clientPort = tcpSocket->peerPort();

	qDebug() << "New data from server";
	         //<< clientIP.toString() + ":" + QString::number(clientPort);

	QDataStream in(server);
	if (dataSize == 0)
	{
		if (server->bytesAvailable() < sizeof(quint16))
			return;
		in >> dataSize;
		qDebug() << "Data size:" << dataSize;
	}

	if (server->bytesAvailable() < dataSize)
		return;

	qDebug() << "New message from server";
	         //<< clientIP.toString() + ":" + QString::number(clientPort);

//	char *data = new char[dataSize + 1];
//	tcpSocket->read(data, dataSize);
//	data[dataSize] = '\0';
	QString data;
	in >> data;
	qDebug() << data;
	emit newMessage(data);
	dataSize = 0;
	if (server->bytesAvailable() > 0)
		getMessage();
}

void Client::send(const QString &msg)
{
	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
	out << (quint16)0 << msg;
	out.device()->seek(0);
	quint16 size = (quint16)(data.size() - sizeof(quint16));
	out << size;
	server->write(data);
	qDebug() << "Send. Size:" << size << ", data:" << data;
}
