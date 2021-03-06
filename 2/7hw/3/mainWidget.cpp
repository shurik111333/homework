#include "mainWidget.h"
#include "ui_mainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    game(new TicTacToe(this)),
    buttonsMapper(new QSignalMapper(this)),
    size(minSize)
{
	mainLayout = new QVBoxLayout(this);
	buttonsLayout = new QGridLayout();
	auto panelLayout = new QHBoxLayout();

	const auto buttonNewGame = new QPushButton("New game");
	const auto labelSize = new QLabel("Size:");
	boxFieldSize = new QSpinBox();
	const auto labelToWin = new QLabel("Chain to win:");
	boxToWin = new QSpinBox();
	const auto labelPlayer = new QLabel("Player");
	labelPlayerSign = new QLabel();

	boxFieldSize->setMinimum(minSize);
	boxFieldSize->setMaximum(maxSize);
	boxToWin->setMinimum(minSize);
	boxToWin->setMaximum(boxFieldSize->value());

	panelLayout->addWidget(buttonNewGame);
	panelLayout->addWidget(labelSize);
	panelLayout->addWidget(boxFieldSize);
	panelLayout->addWidget(labelToWin);
	panelLayout->addWidget(boxToWin);
	panelLayout->addWidget(labelPlayer);
	panelLayout->addWidget(labelPlayerSign);
	panelLayout->addStretch();

	mainLayout->addLayout(panelLayout);
	mainLayout->addLayout(buttonsLayout);

	winMsg = new QMessageBox(QMessageBox::Information, QString("Game over"), QString(),
	                         QMessageBox::Ok);

	connect(buttonNewGame, &QPushButton::pressed,
	        this, &MainWidget::startNewGame);
	connect(boxFieldSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &MainWidget::startNewGame);
	connect(boxToWin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &MainWidget::startNewGame);

	connect(this, &MainWidget::newGame,
	        this, &MainWidget::setMaxChainToWin);
	connect(this, &MainWidget::newGame,
	        game, &TicTacToe::newGame);

	connect(buttonsMapper, static_cast<void (QSignalMapper::*)(QWidget*)>(&QSignalMapper::mapped),
	        this, &MainWidget::step);

	connect(game, &TicTacToe::gameOver,
	        this, &MainWidget::gameOver);
	connect(game, &TicTacToe::stepIsDone,
	        this, &MainWidget::doStep);

	connect(winMsg, &QMessageBox::accepted, winMsg, &QMessageBox::close);

	createButtons();
	startNewGame();
}

MainWidget::~MainWidget()
{
	delete boxFieldSize;
	delete boxToWin;
	for (auto button : buttons)
		delete button;
	delete buttonsLayout;
	delete mainLayout;
	delete game;
	delete winMsg;
}

void MainWidget::drawField()
{
	for (auto button : buttons)
	{
		button->reset();
		button->setVisible(button->x() < size && button->y() < size);
	}
}

void MainWidget::createButtons()
{
	for (int i = 0; i < maxSize; i++)
	{
		for (int j = 0; j < maxSize; j++)
		{
			auto button = new CellButton(i, j);
			button->setFixedSize(50, 50);
			button->setVisible(false);
			buttonsLayout->addWidget(button, i, j);
			buttons.push_back(button);

			buttonsMapper->setMapping(button, button);
			connect(button, &CellButton::pressed,
			        buttonsMapper, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
		}
	}
}

void MainWidget::setNewSize()
{
	size = boxFieldSize->value();
}

void MainWidget::startNewGame()
{
	setNewSize();
	drawField();
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	labelPlayerSign->setText(QString(game->getStartPlayer()));
	emit newGame(boxFieldSize->value(), boxToWin->value());
}

void MainWidget::setMaxChainToWin(int size)
{
	boxToWin->setMaximum(size);
}

void MainWidget::gameOver(char winner)
{
	winMsg->setText("Player " + QString(winner) + " wins!");
	winMsg->show();
}

void MainWidget::step(QWidget *widget)
{
	CellButton *button = static_cast<CellButton*>(widget);
	game->doStep(button->x(), button->y());
	labelPlayerSign->setText(QString(game->getPlayer()));
}

void MainWidget::doStep(int x, int y, char player) const
{
	CellButton *button = buttons[x * maxSize + y];
	button->setText(QString(player));
	button->setEnabled(false);
}
