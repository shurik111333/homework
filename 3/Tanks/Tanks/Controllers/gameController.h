#pragma once

#include "Model/Player/iplayer.h"
#include "Model/Shell/abstractShell.h"
#include "Model/Landscape/iLandscapeGenerator.h"
#include <QObject>
#include <QList>
#include <QPoint>
#include <QVector>
#include <iterator>
#include <QTimer>

class GameController : public QObject
{
	Q_OBJECT
public:
	explicit GameController(QObject *parent = 0);
	~GameController();

	const QList<QPointF> &getLandscape() const;
	const QVector<IPlayer *> &getPlayers() const;

private:
	enum class State
	{
		notInGame,
		waiting,
		shooting
	};

	ILandscapeGenerator *landscape = nullptr;
	QVector<IPlayer *> players;
	QVector<IPlayer *>::const_iterator player;
	AbstractShell *shell = nullptr;
	//QGraphicsPolygonItem *shellCursor = nullptr;
	const double minGunAngle = 0;
	const double maxGunAngle = 90;
	double step = 3;
	State state = State::notInGame;

	/**
	 * @brief createCannon Create cannon in random place on the input segment
	 * @param x0 left x-coordinate
	 * @param x1 right x-coordinate
	 * @return Cannon
	 */
	AbstractTank *createTank(double x0, double x1, const QBrush &brush) const;
	void moveRight(AbstractTank *cannon) const;
	void moveLeft(AbstractTank *cannon) const;
	void moveTank(AbstractTank *cannon, double step) const;
	void shoot();
	void setNextPlayer();
	inline bool shellInGame() const;
	inline bool shellOnLandscape() const;
	inline void removeShell();
	inline void removeShellCursor();
	inline QGraphicsPolygonItem *createShellCursor();
	double rand(double x0, double x1) const;

signals:
	void newGame();
	void nextPlayer(IPlayer *player);

public slots:
	void startGame();
	void keyPress(Qt::Key key);

private slots:
	void checkShell();
};
