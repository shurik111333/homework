#include "settingsWidget.h"
#include "ui_settingsWidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
	ui->setupUi(this);
}

SettingsWidget::~SettingsWidget()
{
	delete ui;
}
