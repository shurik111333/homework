#include "gameController.h"
#include "Model/Landscape/landscapeGeneratorFixed.h"
#include "Model/Player/localplayer.h"
#include "Model/Cannon/cannonSimple.h"
#include <algorithm>
#include <QBrush>
#include <ctime>

GameController::GameController(QObject *parent)
    : QObject(parent),
      landscape(LandscapeGeneratorFixed::getInstance())
{

}

QList<QPointF> GameController::getLandscape() const
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
	emit newGame();
}

const QVector<IPlayer *> &GameController::getPlayers() const
{
	return players;
}

ICannon *GameController::createCannon(double x0, double x1, const QBrush &brush) const
{
	qsrand(time(0));
	auto land = getLandscape();
	x0 = std::max(land[0].x(), x0);
	x1 = std::min(land[land.length() - 1].x(), x1);
	double d = (double) qrand() / RAND_MAX;
	double x = x0 + d * (x1 - x0);  //generate random x in [x0; x1]
	QPointF left = land[0];
	QPointF right;
	for (auto p : land)
	{
		if (p.x() < x)
			left = p;
		else
		{
			right = p;
			break;
		}
	}
	double y = left.y() + (right.y() - left.y()) * ((x - left.x()) / (right.x() - left.x()));
	return new CannonSimple(x, y, brush);
}
