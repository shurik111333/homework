#include "game.h"
#include "settings.h"
#include <QVector>
#include <QGraphicsScene>
#include <QtMath>
#include <QGraphicsLineItem>
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

void Game::releaseTanks()
{
	for (IPlayer *player : players)
	{
		auto scene = player->getTank()->scene();
		if (scene != nullptr)
		{
			scene->removeItem(player->getTank());
		}
	}
}

void Game::startNewGame()
{
	Settings::instance()->resetPlayers();
	players = Settings::instance()->getPlayers();
	landscape = Settings::instance()->getLandscape();

	for (auto p : players)
	{
		setUpPlayer(p);
	}

	currentPlayer = players.constBegin();
	connectToPlayer(*currentPlayer);

	emit newGame(players);
	emit newStep(*currentPlayer);
	state = GameState::gameInProgress;
}

Game::Game(QObject *parent) : QObject(parent)
{

}

void Game::clearLastGame()
{
	disconnectFromPlayer(*currentPlayer);
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
	if (tank->baseCenter().x() < landscape->getLeftBorder().x())
	{
		mapTank(tank, landscape->getLeftBorder());
		return;
	}
	if (tank->baseCenter().x() > landscape->getRightBorder().x())
	{
		mapTank(tank, landscape->getRightBorder());
		return;
	}
	mapTank(tank, tank->baseCenter());
}

void Game::mapTank(ITank *tank, const QPointF &point)
{
	double ang = (int) tank->getDirection() * landscape->getLandscapeAngle(point);

	tank->setRotation(ang);
	tank->setPos(landscape->getPoint(point.x()) + tank->pos() - tank->baseCenter());
}

void Game::setUpPlayer(IPlayer *player)
{
	auto tank = player->getTank();
	tank->setTransformOriginPoint(tank->base().width() / 2, 0);
}

void Game::playerMoving(Action action)
{
	auto tank = (*currentPlayer)->getTank();
	checkGun(tank);
	mapTank(tank);
}

void Game::playerShooting(IShell *shell)
{
	state = GameState::shooting;
	currentShell = shell;
	connect(currentShell, &IShell::updatingPos, this, &Game::shellUpdate);
}

void Game::shellUpdate()
{
	if (isShellCollidesPlayers())
	{
		getCollidedPlayer()->getTank()->setHealthPoints(0);
		endGame();
		return;
	}
	if (isShellCollidesLandscape())
	{
		currentShell->explode();
		if (isShellHitsPlayers())
		{
			getHitedPlayer()->getTank()->setHealthPoints(0);
			endGame();
			return;
		}
	}
	if (!shellInGame() || isShellCollidesLandscape())
	{
		endStep();
		state = GameState::gameInProgress;
		return;
	}
	if (!currentShell->scene()->sceneRect().contains(currentShell->pos()))
	{
		currentShell->showCursor();
		return;
	}
	currentShell->hideCursor();
}

bool Game::shellInGame()
{
	auto rect = currentShell->scene()->sceneRect();
	auto p = currentShell->pos();
	return p.y() >= rect.top() && p.x() >= rect.left() && p.x() <= rect.right();
}

void Game::removeShell()
{
	currentShell->hideCursor();
	currentShell->cancelShoot();
	delete currentShell;
	currentShell = nullptr;
}

void Game::nextPlayer()
{
	disconnectFromPlayer(*currentPlayer);

	setNextPlayer();

	connectToPlayer(*currentPlayer);
	emit newStep(*currentPlayer);
}

void Game::setNextPlayer()
{
	currentPlayer++;
	if (currentPlayer == players.end())
		currentPlayer = players.constBegin();
}

bool Game::isShellCollides() const
{
	return isShellCollidesLandscape() || isShellCollidesPlayers();
}

bool Game::isShellCollidesLandscape() const
{
	auto segment = landscape->getSegment(currentShell->pos().x());
	QGraphicsLineItem line(QLineF(segment.first, segment.second));
	return currentShell->collidesWithItem(&line, Qt::IntersectsItemShape);
}

bool Game::isShellCollidesPlayers() const
{
	return getCollidedPlayer() != nullptr;
}

IPlayer *Game::getCollidedPlayer() const
{
	IPlayer *res = nullptr;
	for (IPlayer *player : players)
	{
		if (player->getTank()->collidesWithShell(currentShell))
		{
			res = player;
			break;
		}
	}
	return res;
}

bool Game::isShellHitsPlayers() const
{
	return getHitedPlayer() != nullptr;
}

IPlayer *Game::getHitedPlayer() const
{
	IPlayer *res = nullptr;
	for (IPlayer *player : players)
	{
		if (player->getTank()->hitsByShell(currentShell))
		{
			res = player;
			break;
		}
	}
	return res;
}

void Game::endStep()
{
	disconnect(currentShell, &IShell::updatingPos, this, &Game::shellUpdate);
	removeShell();
	nextPlayer();
}

void Game::endGame()
{
	endStep();
	state = GameState::endOfGame;
	clearLastGame();
	emit endOfGame(getWinner());
}

IPlayer *Game::getWinner()
{
	for (IPlayer *p : players)
	{
		if (!p->getTank()->isDestroyed())
			return p;
	}
	return nullptr;
}

void Game::connectToPlayer(IPlayer *player)
{
	connect(player, &IPlayer::moveAction, this, &Game::playerMoving);
	connect(player, &IPlayer::shootAction, this, &Game::playerShooting);
	connect(player, &IPlayer::setNewShell, this, &Game::newShell);
}

void Game::disconnectFromPlayer(IPlayer *player)
{
	disconnect(player, &IPlayer::moveAction, this, &Game::playerMoving);
	disconnect(player, &IPlayer::shootAction, this, &Game::playerShooting);
	disconnect(player, &IPlayer::setNewShell, this, &Game::newShell);
}
