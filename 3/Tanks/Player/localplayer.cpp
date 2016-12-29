#include "localplayer.h"
#include "../Tank/tankSimple.h"
#include "../Shell/ishell.h"
#include "../Shell/ShellType/standart.h"
#include "../Shell/ShellType/explosive.h"

LocalPlayer::LocalPlayer(Qt::GlobalColor color, const QString &name) :
    IPlayer(new TankSimple(0, 0, color), color, name)
{
}

void LocalPlayer::keyPressed(const QKeyEvent *key)
{
	IShellType *type = nullptr;
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
			break;
		case Qt::Key_1:
			type = Standart::instance();
			getTank()->setShell(type);
			emit setNewShell(type);
			break;
		case Qt::Key_2:
			type = Explosive::instance();
			getTank()->setShell(type);
			emit setNewShell(type);
			break;
	}
}
