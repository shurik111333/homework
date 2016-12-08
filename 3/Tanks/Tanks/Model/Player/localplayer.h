#pragma once

#include "iplayer.h"
#include "../Tank/abstractTank.h"

class LocalPlayer : public IPlayer
{
public:
	LocalPlayer(AbstractTank *tank, Qt::GlobalColor color, const QString &name);
};
