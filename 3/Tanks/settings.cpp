#include "settings.h"
#include "Player/localplayer.h"
#include "Player/networkplayer.h"
#include "Player/localplayerproxy.h"
#include "Landscape/landscapeGeneratorFixed.h"

Settings *Settings::_instance = nullptr;

Settings *Settings::instance()
{
	if (_instance == nullptr)
		_instance = new Settings();
	return _instance;
}

void Settings::newLocalGame()
{
	clear();

	player = new LocalPlayer(Qt::red, "Plyaer Red");
	opponent = new LocalPlayer(Qt::blue, "Player Blue");
	resetPlayers();
}

void Settings::newServerGame()
{
	clear();

	server = new Server();

	auto pl = new LocalPlayerProxy(Qt::red, "You");
	auto op = new NetworkPlayer(Qt::blue, "Opponent");

	connect(server, &Server::newClient, pl, &LocalPlayerProxy::setSocket);
	connect(server, &Server::newClient, op, &NetworkPlayer::setSocket);
	connect(server, &Server::newClient, this, &Settings::clientConnected);

	player = pl;
	opponent = op;
}

void Settings::newClientGame(const QHostAddress &address, quint16 port)
{
	clear();

	auto socket = new QTcpSocket();
	socket->connectToHost(address, port);

	auto pl = new NetworkPlayer(Qt::blue, "Opponent");
	auto op = new LocalPlayerProxy(Qt::red, "You");

	pl->setSocket(socket);
	op->setSocket(socket);

	player = pl;
	opponent = op;
}

QVector<IPlayer *> Settings::getPlayers() const
{
	QVector<IPlayer *> res;
	res.push_back(player);
	res.push_back(opponent);
	return res;
}

ILandscapeGenerator *Settings::getLandscape() const
{
	return landscape;
}

void Settings::resetPlayers()
{
	resetTank(player->getTank());
	player->getTank()->setDirection(ITank::Direction::right);
	player->getTank()->setPos(landscape->getLeftBorder());

	resetTank(opponent->getTank());
	opponent->getTank()->setDirection(ITank::Direction::left);
	opponent->getTank()->setPos(landscape->getRightBorder());
}

QHostAddress Settings::getIP() const
{
	return server->getMyIP();
}

quint16 Settings::getPort() const
{
	return server->getMyPort();
}

Settings::Settings(QObject *parent) : QObject(parent)
{
	landscape = LandscapeGeneratorFixed::getInstance();
}

void Settings::clear()
{
	delete server;
	server = nullptr;
	delete player;
	player = nullptr;
	delete opponent;
	opponent = nullptr;
}

void Settings::resetTank(ITank *tank)
{
	tank->setRotation(0);
	tank->setGunAngle(45);
	tank->setHealthPoints(100);
}
