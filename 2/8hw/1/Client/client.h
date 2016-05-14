#pragma once

#include <QtCore/QObject>
#include <QList>
#include "../TcpMessenger/tcpMessenger.h"

class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);
	~Client();

	QString getServerIP() const;
	quint16 getServerPort() const;

signals:
	void newMessage(const QString msg);
	void connected();

public slots:
	void connectToServer(const QString &host, quint16 port);
	void send(const QString &msg);

private:
	TcpMessenger *messenger;
	quint16 dataSize = 0;
	QTcpSocket *tcpServer = nullptr;

private slots:
	void getMessage(const QString msg);
	void removeSocket();
	void requestMessage();
	void succesfullConnected();
};
