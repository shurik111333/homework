#pragma once

#include <QtCore/QObject>
#include <QList>
#include "../TcpMessenger/tcpMessenger.h"

class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);

signals:
	void newMessage(const QString msg);

public slots:
	void connectToServer(const QString &host, quint16 port);
	void send(const QString &msg);

private:
	quint16 dataSize = 0;
	QTcpSocket *server = nullptr;

private slots:
	void getMessage();
};
