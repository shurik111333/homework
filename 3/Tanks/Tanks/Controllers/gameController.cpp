#include "gameController.h"
#include "Model/Landscape/landscapeGeneratorFixed.h"
#include "Model/Player/localplayer.h"
#include "Model/Tank/tankSimple.h"
#include <algorithm>
#include <QBrush>
#include <ctime>
#include <QDebug>
#include <QGraphicsScene>
#include <QPolygonF>
#include <QVector>
#include <QPoint>

QDEBUG_H

GameController::GameController(QObject *parent)
    : QObject(parent),
      landscape(LandscapeGeneratorFixed::getInstance())
{
	qsrand(std::time(0));
}

GameController::~GameController()
{
	removeShell();
	//delete shellCursor;
}

const QList<QPointF> &GameController::getLandscape() const
{
	return landscape->getLandscape();
}

void GameController::startGame()
{
	removeShell();
//	removeShellCursor();
	for (auto p : players)
		delete p;
	players.clear();
	auto land = getLandscape();
	//shellCursor = createShellCursor();
	players.append(new LocalPlayer(createTank(land[0].x(), land[1].x(), Qt::red), Qt::red, "Player1"));
	players.back()->getTank()->setDirection(AbstractTank::Direction::right);
	players.append(new LocalPlayer(createTank(land[land.length() - 2].x(),
	                               land[land.length() - 1].x(), Qt::blue), Qt::blue, "Player2"));
	players.back()->getTank()->setDirection(AbstractTank::Direction::left);
	state = State::waiting;
	emit newGame();
	player = players.end();
	player--;
	setNextPlayer();
}

void GameController::keyPress(Qt::Key key)
{
	if (state == State::shooting || state == State::notInGame)
		return;
	AbstractTank *tank = (*player)->getTank();
	switch (key)
	{
		case Qt::Key_D:
			tank->moveRight();
			//moveRight(tank);
			break;
		case Qt::Key_A:
			tank->moveLeft();
			//moveLeft(tank);
			break;
		case Qt::Key_W:
			tank->moveGunUp();
			if (tank->getGunAngle() > maxGunAngle)
				tank->setGunAngle(maxGunAngle);
			break;
		case Qt::Key_S:
			tank->moveGunDown();
			if (tank->getGunAngle() < minGunAngle)
				tank->setGunAngle(minGunAngle);
			break;
		case Qt::Key_Q:
			shoot();
			break;
		default:
			return;
	}
	double ang = (int) tank->getDirection() * landscape->getLandscapeAngle(tank->baseCenter());
	tank->setRotation(ang);
	tank->setPos(landscape->getPoint(tank->baseCenter().x()) + tank->pos() - tank->baseCenter());
}

void GameController::checkShell()
{
	if (!shellInGame())
	{
		disconnect(shell, &AbstractShell::updatingPos, this, &GameController::checkShell);
		removeShell();
		state = State::waiting;
		setNextPlayer();
		return;
	}
	if (!shell->scene()->sceneRect().contains(shell->pos()))
	{
		shell->showCursor();
		return;
	}
	shell->hideCursor();
}

const QVector<IPlayer *> &GameController::getPlayers() const
{
	return players;
}

AbstractTank *GameController::createTank(double x0, double x1, const QBrush &brush) const
{
	auto land = getLandscape();

	double x = rand(qMax(land[0].x(), x0), qMin(land[land.length() - 1].x(), x1));

	auto p = landscape->getPoint(x);
	auto tank = new TankSimple(p.x(), p.y(), brush);
	tank->setTransformOriginPoint(tank->boundingRect().center().x(), 0);
	return tank;
}

void GameController::moveRight(AbstractTank *tank) const
{
	moveTank(tank, step);
}

void GameController::moveLeft(AbstractTank *tank) const
{
	moveTank(tank, -step);
}

void GameController::moveTank(AbstractTank *tank, double step) const
{
	double dx = tank->boundingRect().center().x();
	auto p = landscape->toLandscape(landscape->getPoint(tank->pos().x() + dx + step));
	tank->setPos(p.x() - dx, p.y());
	tank->setRotation(landscape->getLandscapeAngle(p));
}

void GameController::shoot()
{
	state = State::shooting;
	AbstractTank *tank = (*player)->getTank();
	shell = tank->shoot();
	tank->scene()->addItem(shell);
	connect(shell, &AbstractShell::updatingPos, this, &GameController::checkShell);
}

void GameController::setNextPlayer()
{
	player++;
	if (player == players.end())
		player = players.constBegin();
	emit nextPlayer(*player);
}

bool GameController::shellInGame() const
{
	auto rect = shell->scene()->sceneRect();
	auto p = shell->pos();
	return p.y() >= rect.top() && p.x() >= rect.left() && p.x() <= rect.right();
}

bool GameController::shellOnLandscape() const
{
	return true;
}

void GameController::removeShell()
{
	if (shell == nullptr)
		return;
	shell->cancelShoot();
	shell->scene()->removeItem(shell);
	delete shell;
	shell = nullptr;
}

/*void GameController::removeShellCursor()
{
	if (shellCursor == nullptr)
		return;
	shellCursor->hide();
	shellCursor->scene()->removeItem(shellCursor);
}*/

QGraphicsPolygonItem *GameController::createShellCursor()
{
	QPointF ver(0, 0);
	auto points = QVector<QPointF> { ver, ver - QPointF(10, 10), ver + QPointF(10, -10) };
	auto res = new QGraphicsPolygonItem(QPolygonF(points));
	res->hide();
	return res;
}

double GameController::rand(double x0, double x1) const
{
	double d = (double) qrand() / RAND_MAX;
	return x0 + d * (x1 - x0);
}
