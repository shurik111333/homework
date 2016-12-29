#pragma once

#include "ishelltype.h"

class Standart : public IShellType
{
public:
	static Standart *instance();

	// IShellType interface
	virtual IShell *create(double x, double y, double ang) const override;
	virtual QString name() const override;
	virtual Action action() const override;
	virtual IShell::Type type() const override;

private:
	static Standart *_instance;
	Standart();
};
