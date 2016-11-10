#pragma once

#include "Model/Player/iplayer.h"
#include "Model/Landscape/iLandscapeGenerator.h"
#include <QObject>
#include <QList>
#include <QPoint>
#include <QVector>

class GameController : public QObject
{
	Q_OBJECT
public:
	explicit GameController(QObject *parent = 0);

	QList<QPointF> getLandscape() const;

	const QVector<IPlayer *> &getPlayers() const;

private:
	ILandscapeGenerator *landscape = nullptr;
	QVector<IPlayer*> players;

	/**
	 * @brief createCannon Create cannon in random place on the input segment
	 * @param x0 left x-coordinate
	 * @param x1 right x-coordinate
	 * @return Cannon
	 */
	ICannon *createCannon(double x0, double x1, const QBrush &brush) const;

signals:
	void newGame();

public slots:
	void startGame();
};
