#include <QLabel>
#include <QDialogButtonBox>
#include "mainWidget.h"
#include "ui_mainWidget.h"
#include <bits/stdc++.h>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    size(3)
{
	mainLayout = new QVBoxLayout(this);
	buttonsLayout = new QGridLayout();
	auto panelLayout = new QHBoxLayout();

	const auto buttonNewGame = new QPushButton("New game");
	const auto labelSize = new QLabel("Size:");
	boxFieldSize = new QSpinBox();
	const auto labelToWin = new QLabel("Length of chain to win:");
	boxToWin = new QSpinBox();

	boxFieldSize->setMinimum(minSize);
	boxFieldSize->setMaximum(maxSize);
	boxToWin->setMinimum(minSize);
	boxToWin->setMaximum(boxFieldSize->value());

	panelLayout->addWidget(buttonNewGame);
	panelLayout->addWidget(labelSize);
	panelLayout->addWidget(boxFieldSize);
	panelLayout->addWidget(labelToWin);
	panelLayout->addWidget(boxToWin);
	panelLayout->addStretch();

	mainLayout->addLayout(panelLayout);
	mainLayout->addLayout(buttonsLayout);

	connect(boxFieldSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &MainWidget::startNewGame);
	connect(this, &MainWidget::newGame,
	        this, &MainWidget::setMaxChainToWin);
	createButtons();
	startNewGame();
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::drawField()
{
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			auto button = new CellButton(i, j);
//			buttonsLayout->addWidget(button, i, j);
//			buttons.push_back(button);
//		}
//	}
	for (auto button : buttons)
	{
		button->setVisible(button->x() < size && button->y() < size);
	}
}

void MainWidget::removeField()
{
//	for (auto button : buttons)
//		delete button;
//	buttons.clear();
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
		}
	}
}

void MainWidget::setNewSize()
{
	size = boxFieldSize->value();
}

void MainWidget::startNewGame()
{
	removeField();
	setNewSize();
	drawField();
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	emit newGame(boxFieldSize->value(), boxToWin->value());
}

void MainWidget::setMaxChainToWin(int size)
{
	boxToWin->setMaximum(size);
}
