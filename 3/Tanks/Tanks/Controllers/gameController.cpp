#include "gameController.h"
#include "Model/Landscape/landscapeGeneratorFixed.h"
#include "Model/Player/localplayer.h"
#include "Model/Cannon/cannonSimple.h"
#include <algorithm>
#include <QBrush>
#include <ctime>
#include <QDebug>

QDEBUG_H

GameController::GameController(QObject *parent)
    : QObject(parent),
      landscape(LandscapeGeneratorFixed::getInstance())
{
	qsrand(time(0));
}

const QList<QPointF> &GameController::getLandscape() const
{
	return landscape->getLandscape();
}

void GameController::startGame()
{
	for (auto p : players)
		delete p;
	players.clear();
	auto land = getLandscape();
	players.append(new LocalPlayer(createCannon(land[0].x(), land[1].x(), Qt::red), "Player1"));
	players.append(new LocalPlayer(createCannon(land[land.length() - 2].x(),
	                               land[land.length() - 1].x(), Qt::blue), "Player2"));
	player = players.constBegin();
	emit newGame();
}

void GameController::keyPress(Qt::Key key)
{
	ICannon *cannon = (*player)->getCannon();
	switch (key)
	{
		case Qt::Key_D:
			moveRight(cannon);
			break;
		case Qt::Key_A:
			moveLeft(cannon);
			break;
		case Qt::Key_W:
			cannon->moveGunUp();
			break;
		case Qt::Key_S:
			cannon->moveGunDown();
		case Qt::Key_Q:
			shoot();
		default:
			return;
	}
}

const QVector<IPlayer *> &GameController::getPlayers() const
{
	return players;
}

ICannon *GameController::createCannon(double x0, double x1, const QBrush &brush) const
{
	auto land = getLandscape();

	double x = rand(std::max(land[0].x(), x0), std::min(land[land.length() - 1].x(), x1));

	auto p = landscape->getPoint(x);
	auto cannon = new CannonSimple(p.x(), p.y(), brush);
	cannon->setTransformOriginPoint(cannon->boundingRect().center().x(), 0);
	return cannon;
}

void GameController::moveRight(ICannon *cannon) const
{
	moveCannon(cannon, step);
}

void GameController::moveLeft(ICannon *cannon) const
{
	moveCannon(cannon, -step);
}

void GameController::moveCannon(ICannon *cannon, double step) const
{
	double dx = cannon->boundingRect().center().x();
	auto p = landscape->toLandscape(landscape->getPoint(cannon->pos().x() + dx + step));
	cannon->setPos(p.x() - dx, p.y());
	cannon->setRotation(landscape->getLandscapeAngle(p));
}

void GameController::shoot() const
{

}

double GameController::rand(double x0, double x1) const
{
	double d = (double) qrand() / RAND_MAX;
	return x0 + d * (x1 - x0);
}
