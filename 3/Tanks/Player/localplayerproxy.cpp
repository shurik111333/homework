#include "localplayerproxy.h"
#include "../TcpMessenger/tcpMessenger.h"

LocalPlayerProxy::LocalPlayerProxy(Qt::GlobalColor color, const QString &name) :
    IPlayer(nullptr, color, name)
{
	player = new LocalPlayer(color, name);
	connect(player, &LocalPlayer::moveAction, this, &LocalPlayerProxy::action);
	connect(player, &LocalPlayer::shootAction, this, &LocalPlayerProxy::shoot);
	connect(player, &LocalPlayer::setNewShell, this, &LocalPlayerProxy::setNewShell);

	connect(player, &LocalPlayer::moveAction, this, &LocalPlayerProxy::moveAction);
	connect(player, &LocalPlayer::shootAction, this, &LocalPlayerProxy::shootAction);
	connect(player, &LocalPlayer::setNewShell, this, &LocalPlayerProxy::newShell);
}

LocalPlayerProxy::~LocalPlayerProxy()
{
	disconnect(player, &LocalPlayer::moveAction, this, &LocalPlayerProxy::action);
	disconnect(player, &LocalPlayer::shootAction, this, &LocalPlayerProxy::shoot);
	disconnect(player, &LocalPlayer::setNewShell, this, &LocalPlayerProxy::setNewShell);

	disconnect(player, &LocalPlayer::moveAction, this, &LocalPlayerProxy::moveAction);
	disconnect(player, &LocalPlayer::shootAction, this, &LocalPlayerProxy::shootAction);
	disconnect(player, &LocalPlayer::setNewShell, this, &LocalPlayerProxy::newShell);

	delete player;
}

void LocalPlayerProxy::keyPressed(const QKeyEvent *key)
{
	player->keyPressed(key);
}

ITank *LocalPlayerProxy::getTank() const
{
	return player->getTank();
}

void LocalPlayerProxy::setSocket(QTcpSocket *socket)
{
	this->socket = socket;
}

void LocalPlayerProxy::action(Action action)
{
	TcpMessenger::instance()->send(socket, (int) action);
}

void LocalPlayerProxy::shoot()
{
	action(Action::shoot);
}

void LocalPlayerProxy::newShell(IShellType *type)
{
	action(type->action());
}
