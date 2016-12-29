#include "networkplayer.h"
#include "Tank/tankSimple.h"
#include "../TcpMessenger/tcpMessenger.h"
#include "../Shell/ShellType/standart.h"
#include "../Shell/ShellType/explosive.h"

NetworkPlayer::NetworkPlayer(Qt::GlobalColor color, const QString &name) :
    IPlayer(new TankSimple(0, 0, color), color, name)
{
	connect(TcpMessenger::instance(), &TcpMessenger::newCommand,
	        this, &NetworkPlayer::newCommand);
}

NetworkPlayer::~NetworkPlayer()
{
	disconnect(TcpMessenger::instance(), &TcpMessenger::newCommand,
	        this, &NetworkPlayer::newCommandReady);
}

void NetworkPlayer::keyPressed(const QKeyEvent *key)
{
	// ignore
}

void NetworkPlayer::setSocket(QTcpSocket *socket)
{
	if (this->socket != nullptr)
		disconnect(this->socket, &QTcpSocket::readyRead, this, &NetworkPlayer::newCommandReady);
	this->socket = socket;
	connect(this->socket, &QTcpSocket::readyRead, this, &NetworkPlayer::newCommandReady);
}

void NetworkPlayer::newCommandReady()
{
	TcpMessenger::instance()->get(socket);
}

void NetworkPlayer::newCommand(int command)
{
	IShellType *type = nullptr;
	switch ((Action) command)
	{
		case Action::moveRight:
			getTank()->moveRight();
			emit moveAction(Action::moveRight);
			break;
		case Action::moveLeft:
			getTank()->moveLeft();
			emit moveAction(Action::moveLeft);
			break;
		case Action::gunUp:
			getTank()->moveGunUp();
			emit moveAction(Action::gunUp);
			break;
		case Action::gunDown:
			getTank()->moveGunDown();
			emit moveAction(Action::gunDown);
			break;
		case Action::shoot:
			emit shootAction(getTank()->shoot());
			break;
		case Action::setSimpleShell:
			type = Standart::instance();
			getTank()->setShell(type);
			emit setNewShell(type);
			break;
		case Action::setExplosiveShell:
			type = Explosive::instance();
			getTank()->setShell(type);
			emit setNewShell(type);
			break;
	}
}
