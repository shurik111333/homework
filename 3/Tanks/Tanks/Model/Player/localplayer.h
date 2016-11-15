#pragma once

#include "iplayer.h"
#include "../Tank/iTank.h"

class LocalPlayer : public IPlayer
{
public:
	LocalPlayer(ITank *cannon, const QString &name);
};
