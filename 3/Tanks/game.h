#pragma once

#include "Player/iplayer.h"
#include "Shell/ishell.h"
#include "Tank/iTank.h"
#include "Landscape/iLandscapeGenerator.h"
#include <QObject>
#include <QVector>
#include <QKeyEvent>

class Game : public QObject
{
	Q_OBJECT
public:
	static Game *instance();

	void keyPressed(QKeyEvent *key);
signals:
	void newGame(const QVector<IPlayer *> &players);
	void newStep(const IPlayer *player);

public slots:
	void startNewGame();
private:
	enum class GameState
	{
		notInGame,
		gameInProgress,
		shooting,
		endOfGame
	};

	static Game *_instance;
	const double minGunAngle = 0;
	const double maxGunAngle = 90;
	GameState state = GameState::notInGame;
	QVector<IPlayer *> players;
	QVector<IPlayer *>::const_iterator currentPlayer;
	ILandscapeGenerator *landscape = nullptr;
	IShell *currentShell = nullptr;

	explicit Game(QObject *parent = 0);

	void clearLastGame();
	void checkGun(ITank *tank);
	void mapTank(ITank *tank);
	void setUpPlayer(IPlayer *player);

private slots:
	void playerMoving();
	void playerShooting(IShell *shell);
	void shellUpdate();
	bool shellInGame();
	void removeShell();
};
