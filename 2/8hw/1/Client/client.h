#pragma once

#include <QtCore/QObject>
#include <QList>
#include "../TcpMessenger/tcpMessenger.h"

/// Represents client, which connect to server and communicate with it
class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);
	~Client();

	QString getServerIP() const;
	quint16 getServerPort() const;

signals:
	/// Emits when new message was received
	void newMessage(const QString msg);
	/// Emits when connection has been established
	void connected();

public slots:
	void connectToServer(const QString &host, quint16 port);
	/// Send messgae to server
	void send(const QString &msg);

private:
	TcpMessenger *messenger;
	QTcpSocket *tcpServer = nullptr;

private slots:
	/// Tries get message from socket
	void getMessage(const QString msg);
	/// Set pointer to socket as nullptr, when socket destroyed
	void removeSocket();
	void requestMessage();
	void succesfullConnected();
};
