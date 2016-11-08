#pragma once

#include "iLandscapeGenerator.h"
#include <QObject>
#include <QList>
#include <QPoint>

class MainWindowController : public QObject
{
	Q_OBJECT
public:
	explicit MainWindowController(QObject *parent = 0);

	QList<QPointF> getLandscape() const;

private:
	ILandscapeGenerator *landscape = nullptr;
signals:

public slots:
};
