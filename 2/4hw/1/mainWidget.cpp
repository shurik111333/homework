#include "mainWidget.h"
#include "ui_mainWidget.h"
#include <QPalette>

const QString Widget::successAdd = "Pair {key, value} was added succesfully.";
const QString Widget::successRemove = "Pair {key, value} was removed succesfully.";
const QString Widget::successFind = "Done.";
const QString Widget::nonIntegerValue = "Value must be an integer.";
const QString Widget::findNothing = "No values was found.";
const QString Widget::emptyKey = "Key is empty.";

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
	ui->setupUi(this);
	settings = new Settings();
	settingsUi = new SettingsWidget(settings);

	updateInformation();
	connect(ui->buttonAdd, &QPushButton::pressed,
	        this, &Widget::addToMap);
	connect(ui->buttonRemove, &QPushButton::pressed,
	        this, &Widget::removeFromMap);
	connect(ui->buttonFind, &QPushButton::pressed,
	        this, &Widget::findInMap);
	connect(ui->buttonSettings, &QPushButton::pressed,
	        this, &Widget::showSettings);
	connect(settingsUi, &SettingsWidget::newSettings,
	        this, &Widget::updateInformation);
	connect(settings, &Settings::mapChanged,
	        this, &Widget::updateInformation);
}

Widget::~Widget()
{
	delete ui;
	delete settings;
	delete settingsUi;
}

int Widget::getValue()
{
	bool isNumber = false;
	int value = ui->lineValue->text().toInt(&isNumber);
	if (!isNumber)
		throw nonIntegerValue;
	return value;
}

QString Widget::getKey()
{
	if (ui->lineKey->text().isEmpty())
		throw emptyKey;
	return ui->lineKey->text();
}

void Widget::showSettings()
{
	settingsUi->show();
}

void Widget::updateInformation()
{
	ui->textInformation->setText(settings->getInformation());
}

void Widget::addToMap()
{
	try
	{
		settings->insert(getKey(), getValue());
		successfulMessage(successAdd);
	}
	catch (const QString &error)
	{
		errorMessage(error);
	}
}

void Widget::removeFromMap()
{
	try
	{
		settings->remove(getKey(), getValue());
		successfulMessage(successRemove);
	}
	catch (const QString &error)
	{
		errorMessage(error);
	}
}

void Widget::findInMap()
{
	try
	{
		int value = settings->find(getKey());
		successfulMessage(successFind);
		ui->lineValue->setText(QString::number(value));
	}
	catch (const QString &error)
	{
		errorMessage(error);
	}
}

void Widget::successfulMessage(const QString &m)
{
	ui->labelMessage->setText(m);
	ui->labelMessage->setStyleSheet("QLabel {color : green}");
}

void Widget::errorMessage(const QString &m)
{
	ui->labelMessage->setText(m);
	ui->labelMessage->setStyleSheet("QLabel {color : red}");
}
