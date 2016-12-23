#pragma once

#include "iplayer.h"
#include "localplayer.h"
#include <QtNetwork/QTcpSocket>

class LocalPlayerProxy : public IPlayer
{
public:
	LocalPlayerProxy(Qt::GlobalColor color, const QString &name);
	~LocalPlayerProxy();

	// IPlayer interface
	virtual void keyPressed(const QKeyEvent *key) override;
	virtual ITank *getTank() const override;

public slots:
	void setSocket(QTcpSocket *socket);

private:
	LocalPlayer *player = nullptr;
	QTcpSocket *socket = nullptr;

private slots:
	void action(Action action);
	void shoot();
};
