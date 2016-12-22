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

	void newLocalGame();
	QVector<IPlayer *> getPlayers() const;
	ILandscapeGenerator *getLandscape() const;
	void resetPlayers();

signals:

public slots:
private:
	static Settings *_instance;
	IPlayer *player = nullptr;
	IPlayer *opponent = nullptr;
	ILandscapeGenerator *landscape = nullptr;

	explicit Settings(QObject *parent = 0);

	void clear();
	void resetTank(ITank *tank);
};
