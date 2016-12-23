#include "localplayer.h"
#include "../Tank/tankSimple.h"

LocalPlayer::LocalPlayer(Qt::GlobalColor color, const QString &name) :
    IPlayer(new TankSimple(0, 0, color), color, name)
{
}

void LocalPlayer::keyPressed(const QKeyEvent *key)
{
	switch (key->key())
	{
		case Qt::Key_Right:
			getTank()->moveRight();
			emit moveAction(Action::moveRight);
			break;
		case Qt::Key_Left:
			getTank()->moveLeft();
			emit moveAction(Action::moveLeft);
			break;
		case Qt::Key_Up:
			getTank()->moveGunUp();
			emit moveAction(Action::gunUp);
			break;
		case Qt::Key_Down:
			getTank()->moveGunDown();
			emit moveAction(Action::gunDown);
			break;
		case Qt::Key_Enter:
		case Qt::Key_Return:
			emit shootAction(getTank()->shoot());
	}
}
