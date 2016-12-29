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
    QMainWindow(parent),
    shellTitle("1 - Standart shell\n2 - Explosive shell\nCurrent shell: %1")
{
	mainLayout = new QVBoxLayout();
	widget = new QWidget(this);
	widget->setLayout(mainLayout);
	setCentralWidget(widget);

	buttonNewGame = new QPushButton("New game");
	shellLabel = new QLabel(shellTitle.arg(""));
	headerLayout = new QHBoxLayout();
	headerLayout->addWidget(buttonNewGame);
	headerLayout->addWidget(shellLabel);
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
	connect(Game::instance(), &Game::newStep, this, &GameWindow::newStep);
	connect(Game::instance(), &Game::newShell, this, &GameWindow::newShell);
}

GameWindow::~GameWindow()
{
	disconnect(buttonNewGame, &QPushButton::clicked, Game::instance(), &Game::startNewGame);
	disconnect(Game::instance(), &Game::newGame, this, &GameWindow::newGame);
	disconnect(Game::instance(), &Game::endOfGame, this, &GameWindow::endOfGame);
	disconnect(Game::instance(), &Game::newStep, this, &GameWindow::newStep);
	disconnect(Game::instance(), &Game::newShell, this, &GameWindow::newShell);
	Game::instance()->releaseTanks();
	delete widget;
}

void GameWindow::localGame()
{
	// ignore
}

void GameWindow::serverGame(const QHostAddress &address, quint16 port)
{
	buttonNewGame->setVisible(false);
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
	Game::instance()->startNewGame();
}

void GameWindow::newStep(const IPlayer *player)
{
	newShell(player->getTank()->getShell());
}

void GameWindow::newShell(IShellType *type)
{
	shellLabel->setText(shellTitle.arg(type->name()));
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
