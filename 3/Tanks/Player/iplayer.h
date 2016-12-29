#pragma once

#include "../Tank/iTank.h"
#include "../Shell/ishell.h"
#include "../action.h"
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

	/**
	 * @brief keyPressed Process user key pressing.
	 * @param key
	 */
	virtual void keyPressed(const QKeyEvent *key) = 0;

signals:
	void moveAction(Action action);
	void shootAction(IShell *shell);
	void setNewShell(IShellType *type);

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
