#pragma once

#include "../Tank/iTank.h"
#include "../Shell/ishell.h"
#include <QString>
#include <QObject>
#include <QKeyEvent>

class IPlayer : public QObject
{
	Q_OBJECT
public:
	virtual ~IPlayer()
	{
		delete tank;
	}

	virtual QString getName() const
	{
		return name;
	}

	virtual ITank *getTank() const
	{
		return tank;
	}

	virtual Qt::GlobalColor getColor() const
	{
		return color;
	}

	virtual void keyPressed(const QKeyEvent *key) = 0;

signals:
	void moveAction();
	void shootAction(IShell *shell);

protected:
	explicit IPlayer(ITank *tank, Qt::GlobalColor color, const QString &name, QObject *parent = 0) :
	    QObject(parent),
	    tank(tank),
	    name(name),
	    color(color)
	{}

	ITank *tank = nullptr;
	QString name;
	Qt::GlobalColor color;
};
