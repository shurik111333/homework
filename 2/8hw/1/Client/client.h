#pragma once

#include <QtCore/QObject>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QAbstractSocket>
#include <QList>

class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);

signals:

public slots:
	void connectToServer(const QString &host, quint16 port);
	void send(const QString &msg);

private:
	QTcpSocket *server = nullptr;
};
