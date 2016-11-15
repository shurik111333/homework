#pragma once

#include "Model/Tank/iTank.h"
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

	virtual ITank *getCannon() const
	{
		return cannon;
	}

protected:
	explicit IPlayer(ITank *cannon, const QString &name = "Player", QObject *parent = 0) :
	    QObject(parent),
	    cannon(cannon)
	{}

	ITank *cannon = nullptr;
	QString name;
};
