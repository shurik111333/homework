#pragma once

#include "Player/iplayer.h"
#include "Landscape/iLandscapeGenerator.h"
#include <QObject>
#include <QVector>

class Settings : public QObject
{
	Q_OBJECT
public:
	static Settings *instance();

	/**
	 * @brief newLocalGame Creates players for new local game.
	 */
	void newLocalGame();
	QVector<IPlayer *> getPlayers() const;
	ILandscapeGenerator *getLandscape() const;
	/**
	 * @brief resetPlayers Reset players to it initial state.
	 */
	void resetPlayers();

signals:

public slots:
private:
	static Settings *_instance;
	IPlayer *player = nullptr;
	IPlayer *opponent = nullptr;
	ILandscapeGenerator *landscape = nullptr;

	explicit Settings(QObject *parent = 0);

	/**
	 * @brief clear Removes players.
	 */
	void clear();
	/**
	 * @brief resetTank Reset tank to it initial state.
	 * @param tank
	 */
	void resetTank(ITank *tank);
};
