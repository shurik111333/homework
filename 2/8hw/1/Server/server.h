#pragma once

#include <QtCore/QObject>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QAbstractSocket>
#include <QList>

class Server : public QObject
{
	Q_OBJECT

public:
	explicit Server(QObject *parent = 0);

	QString getMyIP() const;
	quint16 getMyPort() const;

signals:
	void newMessaage(const QString msg);

public slots:
	void sendMessage(const QString msg);

private:
	QTcpServer *tcpServer;
	QTcpSocket *tcpSocket;
	QTcpSocket *client;
	QHostAddress myIP;
	QHostAddress clientIP;
	quint16 myPort = 48999;
	quint16 clientPort = 0;
	quint16 dataSize = 0;

	QHostAddress getIP() const;

private slots:
	void getMessage();
};
