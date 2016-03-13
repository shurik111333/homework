#include "mainWidget.h"
#include "ui_mainWidget.h"
#include <QPalette>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
	ui->setupUi(this);
	settingsWidget = new SettingsWidget();
	setNewSettings(settingsWidget->getSettings());
	
	QObject::connect(ui->buttonAdd, &QPushButton::pressed,
	                 this, &Widget::addToMap);
	QObject::connect(ui->buttonRemove, &QPushButton::pressed,
	                 this, &Widget::removeFromMap);
	QObject::connect(ui->buttonFind, &QPushButton::pressed,
	                 this, &Widget::findInMap);
	QObject::connect(ui->buttonSettings, &QPushButton::pressed,
	                 this, &Widget::openSettings);
	QObject::connect(this, &Widget::mapChanged,
	                 this, &Widget::updateInformation);
	QObject::connect(settingsWidget, &SettingsWidget::newSettings,
	                 this, &Widget::setNewSettings);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::setNewSettings(SettingsWidget::Settings newSettings)
{
	settings = newSettings;
	updateInformation();
}

void Widget::addToMap()
{
	
}

void Widget::removeFromMap()
{
	
}

void Widget::findInMap()
{
	
}

void Widget::updateInformation()
{
	ui->textInformation->setText("Hash function: " + 
	                             settingsWidget->getHashByIndex((int)(settings.currentHash)));
}

void Widget::openSettings()
{
	settingsWidget->show();
}
