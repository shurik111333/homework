#pragma once

#include <QtCore/QObject>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QAbstractSocket>

class TcpMessenger : public QObject
{
	Q_OBJECT
public:
	explicit TcpMessenger(QObject *parent = 0);

	void send(QTcpSocket *tcp, const QString &msg) const;
	void get(QTcpSocket *tcp);

signals:
	void newMessage(const QString msg);

public slots:

private:
	quint16 dataSize = 0;
};
