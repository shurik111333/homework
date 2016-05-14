#pragma once

#include <QtCore/QObject>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QAbstractSocket>
#include <QList>
#include "../TcpMessenger/tcpMessenger.h"

/// Represents server, that waiting for client for communicate
class Server : public QObject
{
	Q_OBJECT

public:
	explicit Server(QObject *parent = 0);
	~Server();

	QString getMyIP() const;
	quint16 getMyPort() const;
	QString getClientIP() const;
	quint16 getClientPort() const;
	/// @return Return true if server connected with client
	bool isConnected() const;

signals:
	/// Emits when new message was received
	void newMessaage(const QString msg);
	void newClient();
	void clientDisconnected();

public slots:
	void sendMessage(const QString msg);

private:
	QTcpServer *tcpServer = nullptr;
	QTcpSocket *socketClient = nullptr;
	TcpMessenger *messenger = nullptr;

	/// @return Return false, if server cannot listen input address.
	/// Otherwise, server start listening.
	bool tryToListen(const QHostAddress &address);

private slots:
	/// Calls when new client has been connected. Emits newClient
	void newConnection();
	void requestMessage();
	/// Set tcpCliaent as nullptr when its destryed
	void removeClient();
};
