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

	if (!tcpServer->listen(getIP()) && !tcpServer->listen(QHostAddress(QHostAddress::LocalHost)))
		qDebug() << "Server cannot listen";
	else
	{
		myIP = tcpServer->serverAddress();
		myPort = tcpServer->serverPort();
		connect(tcpServer, &QTcpServer::newConnection,
		        this, &Server::newConnection);
		qDebug() << "Server listen at" << myIP.toString() << ":" << myPort;
	}

	/*tcpSocket = new QTcpSocket(this);
	tcpSocket->connectToHost(myIP, myPort);
	connect(tcpSocket, &QTcpSocket::readyRead,
	        this, &Server::getMessage);*/
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

	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
//	out << (quint16)data.length() << msg.toUtf8();

	out << (quint16)0 << msg;
	out.device()->seek(0);
	quint16 size = (quint16)(data.size() - sizeof(quint16));
	out << size;
//	auto client = new QTcpSocket();
//	client->connectToHost(clientIP, clientPort);

//	connect(client, &QTcpSocket::disconnected,
//	        client, &QTcpSocket::deleteLater);

	tcpSocket->write(data);
	//tcpSocket->disconnectFromHost();

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
		in >> dataSize;
		qDebug() << "Data size:" << dataSize;
	}

	if (tcpSocket->bytesAvailable() < dataSize)
		return;

	qDebug() << "New message from"
	         << clientIP.toString() + ":" + QString::number(clientPort);

//	char *data = new char[dataSize + 1];
//	tcpSocket->read(data, dataSize);
//	data[dataSize] = '\0';
	QString data;
	in >> data;
//	for (; dataSize > 0; dataSize--)
//		data.append();
	qDebug() << data;
	emit newMessaage(data);
	dataSize = 0;
	if (tcpSocket->bytesAvailable() > 0)
		getMessage();
}

void Server::newConnection()
{
	tcpSocket = tcpServer->nextPendingConnection();
	clientIP = tcpSocket->peerAddress();
	clientPort = tcpSocket->peerPort();

	connect(tcpSocket, &QTcpSocket::readyRead,
	        this, &Server::getMessage);

	qDebug() << "New connection from" << clientIP.toString() << ":" << QString::number(clientPort);

	/*QString response = "OK";
	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
	quint16 size = response.length() + 1;
	out << size << response.toUtf8() << '\0';
	qDebug() << "Send" << size << "bytes:" << data;
	client->write(data);*/
}
