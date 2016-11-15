#pragma once

#include "Model/Player/iplayer.h"
#include "Model/Landscape/iLandscapeGenerator.h"
#include <QObject>
#include <QList>
#include <QPoint>
#include <QVector>
#include <iterator>

class GameController : public QObject
{
	Q_OBJECT
public:
	explicit GameController(QObject *parent = 0);

	const QList<QPointF> &getLandscape() const;
	const QVector<IPlayer *> &getPlayers() const;

private:
	ILandscapeGenerator *landscape = nullptr;
	QVector<IPlayer *> players;
	QVector<IPlayer *>::const_iterator player;
	double step = 3;

	/**
	 * @brief createCannon Create cannon in random place on the input segment
	 * @param x0 left x-coordinate
	 * @param x1 right x-coordinate
	 * @return Cannon
	 */
	ITank *createCannon(double x0, double x1, const QBrush &brush) const;
	void moveRight(ITank *cannon) const;
	void moveLeft(ITank *cannon) const;
	void moveCannon(ITank *cannon, double step) const;
	void shoot() const;
	double rand(double x0, double x1) const;

signals:
	void newGame();

public slots:
	void startGame();
	void keyPress(Qt::Key key);
};
