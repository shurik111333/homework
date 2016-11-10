#pragma once

#include "Model/Cannon/icannon.h"
#include <QString>
#include <QObject>

class IPlayer : public QObject
{
	Q_OBJECT
public:
	virtual ~IPlayer() {}

	virtual QString getName() const
	{
		return name;
	}

	virtual ICannon *getCannon() const
	{
		return cannon;
	}

protected:
	explicit IPlayer(ICannon *cannon, const QString &name = "Player", QObject *parent = 0) :
	    QObject(parent),
	    cannon(cannon)
	{}

	ICannon *cannon = nullptr;
	QString name;
};
