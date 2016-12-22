#include "settings.h"
#include "Player/localplayer.h"

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
	opponent = new LocalPlayer(Qt::blue, "Player Blue");
}

QVector<IPlayer *> Settings::getPlayers() const
{
	QVector<IPlayer *> res;
	res.push_back(player);
	res.push_back(opponent);
	return res;
}

Settings::Settings(QObject *parent) : QObject(parent)
{
	player = new LocalPlayer(Qt::red, "Plyaer Red");
}

void Settings::clear()
{
	delete opponent;
}
