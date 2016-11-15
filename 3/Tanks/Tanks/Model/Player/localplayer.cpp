#include "localplayer.h"

LocalPlayer::LocalPlayer(ITank *tank, Qt::GlobalColor color, const QString &name) :
    IPlayer(tank, color, name)
{
}
