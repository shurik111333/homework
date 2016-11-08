#include "mainwindowController.h"
#include "landscapeGeneratorFixed.h"

MainWindowController::MainWindowController(QObject *parent)
    : QObject(parent),
      landscape(LandscapeGeneratorFixed::getInstance())
{

}

QList<QPointF> MainWindowController::getLandscape() const
{
	return landscape->getLandscape();
}
