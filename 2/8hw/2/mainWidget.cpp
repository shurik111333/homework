#include "mainWidget.h"
#include "ui_mainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    bash(new Bash())
{
	ui->setupUi(this);

	connect(bash, &Bash::newContent,
	        this, &MainWidget::newContent);
	connect(this, &MainWidget::newPos,
	        this, &MainWidget::updateButtons);
	connect(this, &MainWidget::newPos,
	        this, &MainWidget::updateContent);

	bash->update();
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::setPos(int pos)
{
	currentPosition = pos;
	emit newPos();
}

void MainWidget::newContent(QMap<QString, QList<QString> > &content)
{
	this->content = &content;
	setPos(0);
}

void MainWidget::updateButtons()
{
	if (currentPosition == 0)
		ui->buttonPrevious->setDisabled(true);
	else
		ui->buttonPrevious->setDisabled(false);

	if (currentPosition == content->size() - 1)
		ui->buttonNext->setDisabled(true);
	else
		ui->buttonNext->setDisabled(false);
}

void MainWidget::updateContent()
{
	ui->textEditContent->setText((*content)["description"][currentPosition]);
}
