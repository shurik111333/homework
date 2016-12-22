#include "settings.h"
#include "Player/localplayer.h"
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

Settings::Settings(QObject *parent) : QObject(parent)
{
	landscape = LandscapeGeneratorFixed::getInstance();
}

void Settings::clear()
{
	delete player;
	delete opponent;
}

void Settings::resetTank(ITank *tank)
{
	tank->setRotation(0);
	tank->setGunAngle(45);
}
