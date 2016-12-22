#include "game.h"
#include "settings.h"
#include <QVector>
#include <QDebug>

QDEBUG_H

Game *Game::_instance = nullptr;

Game *Game::instance()
{
	if (_instance == nullptr)
		_instance = new Game();
	return _instance;
}

void Game::keyPressed(QKeyEvent *key)
{
	if (state != GameState::gameInProgress)
		return;
	(*currentPlayer)->keyPressed(key);
}

void Game::startNewGame()
{
	Settings::instance()->resetPlayers();
	players = Settings::instance()->getPlayers();
	landscape = Settings::instance()->getLandscape();
	for (auto player : players)
	{
		setUpPlayer(player);
	}
	currentPlayer = players.constBegin();
	emit newGame(players);
	emit newStep(*currentPlayer);
	state = GameState::gameInProgress;
}

Game::Game(QObject *parent) : QObject(parent)
{

}

void Game::clearLastGame()
{
	for (auto player : players)
	{
		disconnect(player, &IPlayer::moveAction, this, &Game::playerMoving);
		disconnect(player, &IPlayer::shootAction, this, &Game::playerShooting);
	}
}

void Game::checkGun(ITank *tank)
{
	if (tank->getGunAngle() > maxGunAngle)
		tank->setGunAngle(maxGunAngle);
	if (tank->getGunAngle() < minGunAngle)
		tank->setGunAngle(minGunAngle);
}

void Game::mapTank(ITank *tank)
{
	double ang = (int) tank->getDirection() * landscape->getLandscapeAngle(tank->baseCenter());

	tank->setRotation(ang);
	tank->setPos(landscape->getPoint(tank->baseCenter().x()) + tank->pos() - tank->baseCenter());
}

void Game::setUpPlayer(IPlayer *player)
{
	connect(player, &IPlayer::moveAction, this, &Game::playerMoving);
	connect(player, &IPlayer::shootAction, this, &Game::playerShooting);
	player->getTank()->setTransformOriginPoint(player->getTank()->baseCenter().x(), 0);
}

void Game::playerMoving()
{
	auto tank = (*currentPlayer)->getTank();
	checkGun(tank);
	mapTank(tank);
}

void Game::playerShooting(IShell *shell)
{

}
