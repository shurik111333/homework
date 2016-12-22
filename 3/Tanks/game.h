#pragma once

#include <QObject>

class Game : public QObject
{
	Q_OBJECT
public:
	static Game *instance();

signals:

public slots:
	void newGame();
private:
	static Game *_instance;
	explicit Game(QObject *parent = 0);
};
