#include "mainWidget.h"
#include "ui_mainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    bash(new Bash())
{
	ui->setupUi(this);

	connect(bash, &Bash::newContent,
	        this, &MainWidget::reset);
	connect(this, &MainWidget::newQuote,
	        this, &MainWidget::updateButtons);
	connect(this, &MainWidget::newQuote,
	        this, &MainWidget::updateContent);

	connect(ui->buttonNext, &QPushButton::pressed,
	        this, &MainWidget::nextQuote);
	connect(ui->buttonPrevious, &QPushButton::pressed,
	        this, &MainWidget::prevQuote);
	connect(ui->buttonUpdate, &QPushButton::pressed,
	        bash, &Bash::update);

	connect(ui->buttonRateUp, &QPushButton::pressed,
	        this, &MainWidget::rateUp);
	connect(ui->buttonRateDown, &QPushButton::pressed,
	        this, &MainWidget::rateDown);
	connect(ui->buttonRateBayan, &QPushButton::pressed,
	        this, &MainWidget::rateBayan);

	bash->update();
}

MainWidget::~MainWidget()
{
	delete ui;
	delete bash;
}

void MainWidget::setQuote(int index)
{
	currentQuote = index;
	if (index < 0 || index >= bash->getCount())
		currentQuote = 0;
	emit newQuote();
}

void MainWidget::nextQuote()
{
	setQuote(currentQuote + 1);
}

void MainWidget::prevQuote()
{
	setQuote(currentQuote - 1);
}

void MainWidget::rateUp()
{
	bash->rateUp(currentQuote);
}

void MainWidget::rateDown()
{
	bash->rateDown(currentQuote);
}

void MainWidget::rateBayan()
{
	bash->rateBayan(currentQuote);
}

void MainWidget::reset()
{
	setQuote(0);
}

void MainWidget::refresh()
{
	bash->update();
}

void MainWidget::updateButtons()
{
	ui->buttonPrevious->setDisabled(currentQuote == 0);
	ui->buttonNext->setDisabled(currentQuote == bash->getCount() - 1);
}

void MainWidget::updateContent()
{
	this->setWindowTitle("Quote #" + bash->getValue(currentQuote, "id"));
	ui->textContent->setText(bash->getValue(currentQuote, "description"));
}
