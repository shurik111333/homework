#include "localplayer.h"

LocalPlayer::LocalPlayer(AbstractTank *tank, Qt::GlobalColor color, const QString &name) :
    IPlayer(tank, color, name)
{
}
