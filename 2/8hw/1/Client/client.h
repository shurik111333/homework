#pragma once

#include <QtCore/QObject>
#include <QList>
#include "../TcpMessenger/tcpMessenger.h"

/// Represents client, which connect to server and communicate with it
class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0) noexcept;
	~Client();

	QString getServerIP() const noexcept;
	quint16 getServerPort() const noexcept;
	/// @return Return true if client connected with server
	bool isConnected() const noexcept;

signals:
	/// Emits when new message was received
	void newMessage(const QString msg);
	/// Emits when connection has been established
	void connected();
	void serverDisconnected();

public slots:
	void connectToServer(const QString &host, quint16 port) throw(QString);
	/// Send messgae to server
	void send(const QString &msg) throw(QString);

private:
	TcpMessenger *messenger = nullptr;
	QTcpSocket *socketServer = nullptr;

private slots:
	/// Set pointer to socket as nullptr, when socket destroyed
	void removeSocket() noexcept;
	void requestMessage() const throw(QString);
};
