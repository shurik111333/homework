#pragma once

#include "Player/iplayer.h"
#include <QObject>

class Settings : public QObject
{
	Q_OBJECT
public:
	static Settings *instance();

	void newLocalGame();
signals:

public slots:
private:
	static Settings *_instance;
	IPlayer *player = nullptr;
	IPlayer *opponent = nullptr;

	explicit Settings(QObject *parent = 0);

	void clear();
};
