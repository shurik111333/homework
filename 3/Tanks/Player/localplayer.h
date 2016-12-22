#pragma once

#include "iplayer.h"

class LocalPlayer : public IPlayer
{
public:
	LocalPlayer(Qt::GlobalColor color, const QString &name);
};
