#include "gameController.h"
#include "Model/Landscape/landscapeGeneratorFixed.h"
#include "Model/Player/localplayer.h"
#include "Model/Tank/tankSimple.h"
#include <algorithm>
#include <QBrush>
#include <ctime>
#include <QDebug>
#include <QGraphicsScene>

QDEBUG_H

GameController::GameController(QObject *parent)
    : QObject(parent),
      landscape(LandscapeGeneratorFixed::getInstance())
{
	qsrand(5);
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
	players.append(new LocalPlayer(createCannon(land[0].x(), land[1].x(), Qt::red), Qt::red, "Player1"));
	players.append(new LocalPlayer(createCannon(land[land.length() - 2].x(),
	                               land[land.length() - 1].x(), Qt::blue), Qt::blue, "Player2"));
	player = players.end();
	player--;
	state = State::waiting;
	emit newGame();
	setNextPlayer();
}

void GameController::keyPress(Qt::Key key)
{
	if (state == State::shooting)
		return;
	ITank *tank = (*player)->getTank();
	switch (key)
	{
		case Qt::Key_D:
			moveRight(tank);
			break;
		case Qt::Key_A:
			moveLeft(tank);
			break;
		case Qt::Key_W:
			tank->moveGunUp();
			break;
		case Qt::Key_S:
			tank->moveGunDown();
			break;
		case Qt::Key_Q:
			shoot();
		default:
			return;
	}
}

void GameController::updateShoot()
{
	time += 0.1;
	shell->updatePos(time);
	//if (!shell->scene()->sceneRect().contains(shell->pos()))
	if (shell->pos().y() < 0)
	{
		disconnect(&shootTimer, &QTimer::timeout, this, &GameController::updateShoot);
		shootTimer.stop();
		shell->scene()->removeItem(shell);
		delete shell;
		state = State::waiting;
		setNextPlayer();
		return;
	}
}

const QVector<IPlayer *> &GameController::getPlayers() const
{
	return players;
}

ITank *GameController::createCannon(double x0, double x1, const QBrush &brush) const
{
	auto land = getLandscape();

	double x = rand(std::max(land[0].x(), x0), std::min(land[land.length() - 1].x(), x1));

	auto p = landscape->getPoint(x);
	auto tank = new TankSimple(p.x(), p.y(), brush);
	tank->setTransformOriginPoint(tank->boundingRect().center().x(), 0);
	return tank;
}

void GameController::moveRight(ITank *tank) const
{
	moveTank(tank, step);
}

void GameController::moveLeft(ITank *tank) const
{
	moveTank(tank, -step);
}

void GameController::moveTank(ITank *tank, double step) const
{
	double dx = tank->boundingRect().center().x();
	auto p = landscape->toLandscape(landscape->getPoint(tank->pos().x() + dx + step));
	tank->setPos(p.x() - dx, p.y());
	tank->setRotation(landscape->getLandscapeAngle(p));
}

void GameController::shoot()
{
	state = State::shooting;
	shootTimer.stop();
	ITank *tank = (*player)->getTank();
	shell = tank->getShell();
	tank->scene()->addItem(shell);
	connect(&shootTimer, &QTimer::timeout, this, &GameController::updateShoot);
	time = 0;
	shootTimer.start(20);
}

void GameController::setNextPlayer()
{
	player++;
	if (player == players.end())
		player = players.constBegin();
	emit nextPlayer(*player);
}

double GameController::rand(double x0, double x1) const
{
	double d = (double) qrand() / RAND_MAX;
	return x0 + d * (x1 - x0);
}
