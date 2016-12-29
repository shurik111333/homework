#pragma once

#include "../ishell.h"
#include "action.h"
#include <QString>

class IShellType
{
public:
	virtual ~IShellType()
	{}

	virtual IShell *create(double x, double y, double ang) const = 0;
	virtual QString name() const = 0;
	virtual Action action() const = 0;
	virtual IShell::Type type() const = 0;

protected:
	IShellType()
	{}
};
