#pragma once

#include <QtCore/QObject>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QAbstractSocket>
#include <QList>
#include "../TcpMessenger/tcpMessenger.h"

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
	void newMessaage(const QString msg);
	void newClient();

public slots:
	void sendMessage(const QString msg);

private:
	QTcpServer *tcpServer = nullptr;
	QTcpSocket *tcpClient = nullptr;
	TcpMessenger *messenger = nullptr;
	quint16 myPort = 48999;

//	QTcpSocket *client;
//	QHostAddress myIP;
//	QHostAddress clientIP;
//	quint16 clientPort = 0;
//	quint16 dataSize = 0;

	QHostAddress getIP() const;

private slots:
	void getMessage(const QString msg);
	void newConnection();
	void requestMessage();
	void removeClient();
};
