#include "tcpMessenger.h"

TcpMessenger *TcpMessenger::_instance = nullptr;

TcpMessenger::TcpMessenger(QObject *parent) noexcept:
    QObject(parent)
{}

TcpMessenger *TcpMessenger::instance()
{
	if (_instance == nullptr)
		_instance = new TcpMessenger();
	return _instance;
}

void TcpMessenger::send(QTcpSocket *tcpSocket, int command) const noexcept
{
	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
	out << command;
	tcpSocket->write(data);
	qDebug() << "Send command:" << command;
}

void TcpMessenger::get(QTcpSocket *tcp) noexcept
{
	qDebug() << "New data from"
	         << tcp->peerAddress().toString() << ":"
	         << QString::number(tcp->peerPort());

	if (tcp->bytesAvailable() < sizeof(int))
		return;
	QDataStream in(tcp);
	int command = 0;
	in >> command;

	qDebug() << "New command from"
	         << tcp->peerAddress().toString() << ":"
	         << command;

	emit newCommand(command);
}
