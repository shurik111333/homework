#pragma once

#include "iplayer.h"
#include "../Cannon/icannon.h"

class LocalPlayer : public IPlayer
{
public:
	LocalPlayer(ICannon *cannon, const QString &name);

};
