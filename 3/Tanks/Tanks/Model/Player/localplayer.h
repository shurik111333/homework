#pragma once

#include "iplayer.h"
#include "../Tank/iTank.h"

class LocalPlayer : public IPlayer
{
public:
	LocalPlayer(ITank *tank, Qt::GlobalColor color, const QString &name);
};
