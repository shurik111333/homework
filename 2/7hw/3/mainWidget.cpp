#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include "mainWidget.h"
#include "ui_mainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
	//ui->setupUi(this);
	auto layout = new QGridLayout(this);

	const auto buttonNewGame = new QPushButton("New game");
	const auto spinBoxFieldSize = new QSpinBox();
	spinBoxFieldSize->setMaximum(maxSize);
	spinBoxFieldSize->setMinimum(minSize);

	layout->addWidget(buttonNewGame, 1, 1);
	layout->addWidget(spinBoxFieldSize, 1, 2);
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::drawField()
{

}
