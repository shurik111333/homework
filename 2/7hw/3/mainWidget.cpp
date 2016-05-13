#include <QSpinBox>
#include "mainWidget.h"
#include "ui_mainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    size(3)
{
	//ui->setupUi(this);
	mainLayout = new QVBoxLayout(this);
	buttonsLayout = new QGridLayout();
	auto panelLayout = new QHBoxLayout();

	const auto buttonNewGame = new QPushButton("New game");
	const auto spinBoxFieldSize = new QSpinBox();
	spinBoxFieldSize->setMaximum(maxSize);
	spinBoxFieldSize->setMinimum(minSize);

	panelLayout->addWidget(buttonNewGame);
	panelLayout->addWidget(spinBoxFieldSize);

	mainLayout->addLayout(panelLayout);
	mainLayout->addLayout(buttonsLayout);

	//	connect(spinBoxFieldSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	//	        this, &MainWidget::newSize);
	drawField();
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::drawField()
{
	//	for (int i = 0; i < maxSize; i++)
	//		for (int j = 0; j < maxSize; j++)
	//		{
	//			buttons[i][j]->setVisible(i < size && j < size);
	//		}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			buttonsLayout->addWidget(new QPushButton(), i, j);
		}
	}
}

void MainWidget::createButtons()
{
	for (int i = 0; i < maxSize; i++)
	{
		buttons.push_back(QList<QPushButton*>());
		for (int j = 0; j < maxSize; j++)
		{
			buttons[i].push_back(new QPushButton());
			buttons[i][j]->setVisible(false);
			buttonsLayout->addWidget(buttons[i][j], i + 1, j);
		}
	}
}

void MainWidget::newSize(int newSize)
{
	size = newSize;
	drawField();
}
