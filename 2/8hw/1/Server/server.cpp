#include "server.h"

Server::Server(QObject *parent):
    QObject(parent)
{
	tcpServer = new QTcpServer(this);
	/*myIP = getIP();
	if (!tcpServer->listen(myIP, myPort))
	{
		if (!tcpServer->listen(myIP))
			qDebug() << "Server cannot listen";
		else
		{
			myPort = tcpServer->serverPort();
			qDebug() << "Server listen at port" << myPort;
		}
	}
	else
		qDebug() << "Server listen at default port";*/
	if (!tcpServer->listen(QHostAddress(QHostAddress::LocalHost)))
		qDebug() << "Server cannot listen";
	else
	{
		myIP = tcpServer->serverAddress();
		myPort = tcpServer->serverPort();
		connect(tcpServer, &QTcpServer::newConnection,
		        this, &Server::getClient);
		qDebug() << "Server listen at" << myIP.toString() << ":" << myPort;
	}

	tcpSocket = new QTcpSocket(this);
	tcpSocket->connectToHost(myIP, myPort);
	connect(tcpSocket, &QTcpSocket::readyRead,
	        this, &Server::getMessage);
}

QString Server::getMyIP() const
{
	return myIP.toString();
}

quint16 Server::getMyPort() const
{
	return myPort;
}

void Server::sendMessage(const QString msg)
{
	qDebug() << "Try to send:" << msg;

	if (clientPort == 0)
	{
		//throw QString("No client was found");
		qDebug() << "No client was found";
		return;
	}

	qDebug() << "Last peer:"
	         << clientIP.toString() + ":" + QString::number(clientPort);

	QByteArray data = msg.toUtf8();
	QDataStream out(&data, QIODevice::WriteOnly);
	out << (quint16)data.length() << data;

	auto client = new QTcpSocket();
	client->connectToHost(clientIP, clientPort);

	connect(client, &QTcpSocket::disconnected,
	        client, &QTcpSocket::deleteLater);

	client->write(data);
	client->disconnectFromHost();

	qDebug() << "Data was send:" << data;
}

QHostAddress Server::getIP() const
{
	QString ip;
	QList<QHostAddress> adresses = QNetworkInterface::allAddresses();
	for (auto adress : adresses)
	{
		if (adress.protocol() == QAbstractSocket::IPv4Protocol)
			return adress;
	}
	return QHostAddress(QHostAddress::LocalHost);
}

void Server::getMessage()
{
//	clientIP = tcpSocket->peerAddress();
//	clientPort = tcpSocket->peerPort();

	qDebug() << "New data from"
	         << clientIP.toString() + ":" + QString::number(clientPort);

	QDataStream in(tcpSocket);
	if (dataSize == 0)
	{
		if (tcpSocket->bytesAvailable() < sizeof(quint16))
			return;
		else
			in >> dataSize;
	}

	if (tcpSocket->bytesAvailable() < dataSize)
		return;

	qDebug() << "New message from"
	         << clientIP.toString() + ":" + QString::number(clientPort);

	char *data = new char[dataSize + 1];
	tcpSocket->read(data, dataSize);
	emit newMessaage(QString(data));

	if (tcpSocket->bytesAvailable() > 0)
		getMessage();
}

void Server::getClient()
{
	client = tcpServer->nextPendingConnection();
	clientIP = client->peerAddress();
	clientPort = client->peerPort();
}
