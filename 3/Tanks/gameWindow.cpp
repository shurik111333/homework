#include "gameWindow.h"
#include "settings.h"
#include "game.h"
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
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
	headerLayout = new QHBoxLayout();
	headerLayout->addWidget(buttonNewGame);
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

void GameWindow::localGame()
{
	// ignore
}

void GameWindow::serverGame(const QHostAddress &address, quint16 port)
{
	buttonNewGame->setEnabled(false);
	headerLayout->addWidget(new QLabel("IP"));
	headerLayout->addWidget(new QLineEdit(address.toString()));
	headerLayout->addWidget(new QLabel("Port"));
	headerLayout->addWidget(new QLineEdit(QString::number(port)));
	connect(Settings::instance(), &Settings::clientConnected, this, &GameWindow::clientConnected);
}

void GameWindow::clientGame()
{
	buttonNewGame->setVisible(false);
	Game::instance()->startNewGame();
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
	auto box = new QMessageBox(QMessageBox::Information, "", getWinnerMessage(winner), QMessageBox::Ok);
	box->setAttribute(Qt::WA_DeleteOnClose);
	box->show();
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

QString GameWindow::getWinnerMessage(IPlayer *winner)
{
	return "Game over. " + winner->getName() + " win!";
}

void GameWindow::clientConnected()
{
	buttonNewGame->setEnabled(true);
	Game::instance()->startNewGame();
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
