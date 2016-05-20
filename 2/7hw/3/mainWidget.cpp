#include "mainWidget.h"
#include "ui_mainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    //ui(new Ui::MainWidget),
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
	labelPlayerSign = new QLabel(QString(game->getPlayer()));

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

	connect(buttonNewGame, &QPushButton::pressed,
	        this, &MainWidget::startNewGame);
	connect(boxFieldSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &MainWidget::startNewGame);
	connect(boxToWin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &MainWidget::startNewGame);
	connect(this, &MainWidget::newGame,
	        this, &MainWidget::setMaxChainToWin);
	connect(buttonsMapper, static_cast<void (QSignalMapper::*)(QWidget*)>(&QSignalMapper::mapped),
	        this, &MainWidget::step);
	connect(this, &MainWidget::newGame,
	        game, &TicTacToe::newGame);
	connect(game, &TicTacToe::gameOver,
	        this, &MainWidget::gameOver);

	winMsg = new QMessageBox(QMessageBox::Information, QString("Game over"), QString(),
	                         QMessageBox::Ok);
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
			button->setVisible(false);
			buttonsLayout->addWidget(button, i, j);
			buttons.push_back(button);

			buttonsMapper->setMapping(button, button);
			connect(button, &CellButton::pressed,
			        buttonsMapper, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
		}
	}
	buttonsLayout->setSizeConstraint(QLayout::SetFixedSize);
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
	emit newGame(boxFieldSize->value(), boxToWin->value());
}

void MainWidget::setMaxChainToWin(int size)
{
	boxToWin->setMaximum(size);
}

void MainWidget::gameOver(char winner)
{
	qDebug() << winner << " wins!\n";
	winMsg->setText("Player " + QString(winner) + " wins!");
	winMsg->show();
}

void MainWidget::step(QWidget *widget)
{
	CellButton *button = static_cast<CellButton*>(widget);
	button->setText(QString(game->getPlayer()));
	button->setEnabled(false);
	game->doStep(button->x(), button->y());
	labelPlayerSign->setText(QString(game->getPlayer()));
}
