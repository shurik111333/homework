#pragma once

#include "Player/iplayer.h"
#include "Landscape/iLandscapeGenerator.h"
#include "Server/server.h"
#include <QObject>
#include <QVector>
#include <QtNetwork/QHostAddress>

class Settings : public QObject
{
	Q_OBJECT
public:
	static Settings *instance();

	/**
	 * @brief newLocalGame Creates players for new local game.
	 */
	void newLocalGame();
	void newServerGame();
	void newClientGame(const QHostAddress &address, quint16 port);
	QVector<IPlayer *> getPlayers() const;
	ILandscapeGenerator *getLandscape() const;
	/**
	 * @brief resetPlayers Reset players to it initial state.
	 */
	void resetPlayers();
	QHostAddress getIP() const;
	quint16 getPort() const;

signals:
	void clientConnected();

public slots:
private:
	static Settings *_instance;
	Server *server = nullptr;
	IPlayer *player = nullptr;
	IPlayer *opponent = nullptr;
	ILandscapeGenerator *landscape = nullptr;

	explicit Settings(QObject *parent = 0);

	/**
	 * @brief clear Clean up before new game.
	 */
	void clear();
	/**
	 * @brief resetTank Reset tank to it initial state.
	 * @param tank
	 */
	void resetTank(ITank *tank);
};
