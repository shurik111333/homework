#pragma once

#include "Model/Tank/abstractTank.h"
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

	virtual AbstractTank *getTank() const
	{
		return tank;
	}

	virtual Qt::GlobalColor getColor() const
	{
		return color;
	}

protected:
	explicit IPlayer(AbstractTank *tank, Qt::GlobalColor color, const QString &name = "Player", QObject *parent = 0) :
	    QObject(parent),
	    tank(tank),
	    name(name),
	    color(color)
	{}

	AbstractTank *tank = nullptr;
	QString name;
	Qt::GlobalColor color;
};
