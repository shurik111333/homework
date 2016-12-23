#include "gameWindow.h"
#include "settings.h"
#include "game.h"
#include <QPushButton>
#include <QList>
#include <QEvent>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
	mainLayout = new QVBoxLayout();
	widget = new QWidget(this);
	widget->setLayout(mainLayout);
	setCentralWidget(widget);

	buttonNewGame = new QPushButton("New game");
	labelWinner = new QLabel();
	auto headerLayout = new QHBoxLayout();
	headerLayout->addWidget(buttonNewGame);
	headerLayout->addWidget(labelWinner);
	headerLayout->addStretch();

	view = new QGraphicsView(&scene);
	mainLayout->addLayout(headerLayout);
	mainLayout->addWidget(view);

	view->setFixedSize(sceneSize + viewOffset);
	view->scale(1, -1);
	scene.setSceneRect(QRect(QPoint(0, 0), sceneSize));

	adjustSize();
	setFixedSize(geometry().size());

	scene.installEventFilter(this);

	connect(buttonNewGame, &QPushButton::clicked, Game::instance(), &Game::startNewGame);
	connect(Game::instance(), &Game::newGame, this, &GameWindow::newGame);
	connect(Game::instance(), &Game::endOfGame, this, &GameWindow::endOfGame);
}

GameWindow::~GameWindow()
{
	disconnect(buttonNewGame, &QPushButton::clicked, Game::instance(), &Game::startNewGame);
	disconnect(Game::instance(), &Game::newGame, this, &GameWindow::newGame);
	disconnect(Game::instance(), &Game::endOfGame, this, &GameWindow::endOfGame);
	Game::instance()->releaseTanks();
	delete widget;
}

void GameWindow::drawLandscape(const QVector<QPointF> &land)
{
	for (int i = 1; i < land.length(); i++)
	{
		scene.addLine(QLineF(land[i - 1], land[i]));
	}
}

void GameWindow::endOfGame(IPlayer *winner)
{
	labelWinner->setText("Game over. " + winner->getName() + " win!");
}

void GameWindow::newGame(const QVector<IPlayer *> &players)
{
	if (scene.items().empty())
	{
		drawLandscape(Settings::instance()->getLandscape()->getLandscape());
		for (auto player : players)
		{
			scene.addItem(player->getTank());
		}
	}
}

bool GameWindow::eventFilter(QObject *watched, QEvent *event)
{
	if (watched != &scene)
		return QMainWindow::eventFilter(watched, event);
	if (event->type() != QEvent::KeyPress)
		return false;
	Game::instance()->keyPressed(static_cast<QKeyEvent *>(event));
	return true;
}
