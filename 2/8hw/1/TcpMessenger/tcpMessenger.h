#pragma once

#include <QtCore/QObject>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QAbstractSocket>

/// Represents interface for send and get messages through tcp
class TcpMessenger : public QObject
{
	Q_OBJECT
public:
	explicit TcpMessenger(QObject *parent = 0);

	void send(QTcpSocket *tcp, const QString &msg) const;

signals:
	/// Emits when all data will be get from socket
	void newMessage(const QString msg);

public slots:
	void get(QTcpSocket *tcp);

private:
	/// Keep size of expected data, or 0 if no size was received
	quint16 dataSize = 0;
};
