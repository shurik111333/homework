#pragma once

#include "Shell/ishell.h"
#include "Shell/ShellType/ishelltype.h"
#include "Player/iplayer.h"
#include "Tank/iTank.h"
#include "Landscape/iLandscapeGenerator.h"
#include "action.h"
#include <QObject>
#include <QVector>
#include <QKeyEvent>

class Game : public QObject
{
	Q_OBJECT
public:
	static Game *instance();

	/**
	 * @brief keyPressed Process user key pressing
	 * @param key
	 */
	void keyPressed(QKeyEvent *key);
	/**
	 * @brief releaseTanks Removes tanks from the graphic scene.
	 */
	void releaseTanks();

signals:
	void newGame(const QVector<IPlayer *> &players);
	void newStep(const IPlayer *player);
	void endOfGame(IPlayer *winner);
	void newShell(IShellType *type);

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

	/**
	 * @brief clearLastGame Clean up after game.
	 */
	void clearLastGame();
	/**
	 * @brief checkGun Checks that tank's gun has correct angle.
	 * @param tank
	 */
	void checkGun(ITank *tank);
	/**
	 * @brief mapTank Mapping tank to the landscape according to it coordinates.
	 * @param tank
	 */
	void mapTank(ITank *tank);
	void mapTank(ITank *tank, const QPointF &point);
	/**
	 * @brief setUpPlayer Configuring player for game.
	 * @param player
	 */
	void setUpPlayer(IPlayer *player);
	void removeShell();
	/**
	 * @brief nextPlayer Set up next player.
	 */
	void nextPlayer();
	void setNextPlayer();
	bool isShellCollides() const;
	/**
	 * @brief isShellCollidesLandscape
	 * @return True, if shell colliding with landscape.
	 */
	bool isShellCollidesLandscape() const;
	bool isShellCollidesPlayers() const;
	IPlayer *getCollidedPlayer() const;
	bool isShellHitsPlayers() const;
	IPlayer *getHitedPlayer() const;
	void endStep();
	void endGame();
	IPlayer *getWinner();
	void connectToPlayer(IPlayer *player);
	void disconnectFromPlayer(IPlayer *player);

private slots:
	void playerMoving(Action action);
	void playerShooting(IShell *shell);
	void shellUpdate();
	bool shellInGame();

};
