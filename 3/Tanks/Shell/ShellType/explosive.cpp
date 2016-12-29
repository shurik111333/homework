#include "explosive.h"
#include "../shellExplosive.h"

Explosive *Explosive::_instance = nullptr;

Explosive *Explosive::instance()
{
	if (_instance == nullptr)
		_instance = new Explosive();
	return _instance;
}

IShell *Explosive::create(double x, double y, double ang) const
{
	return new ShellExplosive(x, y, ang);
}

QString Explosive::name() const
{
	return "Explosive shell";
}

Action Explosive::action() const
{
	return Action::setExplosiveShell;
}

IShell::Type Explosive::type() const
{
	return IShell::Type::explosive;
}

Explosive::Explosive()
{

}
