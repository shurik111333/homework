#include "tcpMessenger.h"

TcpMessenger::TcpMessenger(QObject *parent):
    QObject(parent)
{}

void TcpMessenger::send(QTcpSocket *tcp, const QString &msg) const
{
	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
	out << (quint16)0 << msg;
	out.device()->seek(0);
	quint16 size = (quint16)(data.size() - sizeof(quint16));
	out << size;
	tcp->write(data);
	qDebug() << "Send data. Size:" << size << ", data:" << data.toStdString().c_str();
}

void TcpMessenger::get(QTcpSocket *tcp)
{
	qDebug() << "New data from"
	         << tcp->peerAddress().toString() << ":"
	         << QString::number(tcp->peerPort());

	QDataStream in(tcp);
	if (dataSize == 0)
	{
		if (tcp->bytesAvailable() < sizeof(quint16))
			return;
		in >> dataSize;
		qDebug() << "Data size:" << dataSize;
	}

	if (tcp->bytesAvailable() < dataSize)
		return;

	qDebug() << "New message from"
	         << tcp->peerAddress().toString() << ":"
	         << QString::number(tcp->peerPort());

	QString data;
	in >> data;
	qDebug() << data;
	emit newMessage(data);
	dataSize = 0;
}
