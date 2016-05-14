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

signals:
	/// Emits when new message was received
	void newMessaage(const QString msg);
	void newClient();

public slots:
	void sendMessage(const QString msg);

private:
	QTcpServer *tcpServer = nullptr;
	QTcpSocket *tcpClient = nullptr;
	TcpMessenger *messenger = nullptr;
	//quint16 myPort = 48999;

	/// Return IP ofthis PC
	QHostAddress getIP() const;
	bool tryToListen(const QHostAddress &address);

private slots:
	void getMessage(const QString msg);
	/// Emits when new client has been connected
	void newConnection();
	void requestMessage();
	/// Set tcpCliaent as nullptr when its destryed
	void removeClient();
};
