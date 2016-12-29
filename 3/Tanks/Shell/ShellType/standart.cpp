#include "standart.h"
#include "../shellStandart.h"

Standart *Standart::_instance = nullptr;


Standart *Standart::instance()
{
	if (_instance == nullptr)
		_instance = new Standart();
	return _instance;
}

IShell *Standart::create(double x, double y, double ang) const
{
	return new ShellStandart(x, y, ang);
}

QString Standart::name() const
{
	return "Standart shell";
}

Action Standart::action() const
{
	return Action::setSimpleShell;
}

IShell::Type Standart::type() const
{
	return IShell::Type::simple;
}

Standart::Standart()
{
}
