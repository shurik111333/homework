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
	static TcpMessenger *instance();

	void send(QTcpSocket *tcpSocket, int command) const noexcept;

signals:
	/// Emits when all data will be get from socket
	void newCommand(int command);

public slots:
	void get(QTcpSocket *tcp) noexcept;

private:
	static TcpMessenger *_instance;
	/// Keep size of expected data, or 0 if no size was received
	quint16 dataSize = 0;

	explicit TcpMessenger(QObject *parent = 0) noexcept;
};
