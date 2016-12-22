#include "localplayer.h"
#include "../Tank/tankSimple.h"

LocalPlayer::LocalPlayer(Qt::GlobalColor color, const QString &name) :
    IPlayer(new TankSimple(0, 0, color), color, name)
{
}
