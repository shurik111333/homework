#pragma once

#include "Player/iplayer.h"
#include <QObject>
#include <QVector>

class Settings : public QObject
{
	Q_OBJECT
public:
	static Settings *instance();

	void newLocalGame();
	QVector<IPlayer *> getPlayers() const;
signals:

public slots:
private:
	static Settings *_instance;
	IPlayer *player = nullptr;
	IPlayer *opponent = nullptr;

	explicit Settings(QObject *parent = 0);

	void clear();
};
