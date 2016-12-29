#pragma once

#include "iplayer.h"
#include "../Server/server.h"
#include "../action.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class NetworkPlayer : public IPlayer
{
public:
	NetworkPlayer(Qt::GlobalColor color, const QString &name);
	~NetworkPlayer();

	// IPlayer interface
	virtual void keyPressed(const QKeyEvent *key) override;

public slots:
	void setSocket(QTcpSocket *socket);

private:
	QTcpSocket *socket = nullptr;

private slots:
	void newCommandReady();
	void newCommand(int command);
};
