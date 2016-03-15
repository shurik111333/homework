#include "settingsWidget.h"
#include "ui_settingsWidget.h"
#include <QCloseEvent>
#include <QCheckBox>
#include <QStringList>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
	ui->setupUi(this);
	ui->boxHash->addItems(Settings::getHashNames());
	const auto checkBoxes = Settings::getCheckBoxNames();
	int index = 0;
	for (auto name : checkBoxes)
	{
		const auto box = new QCheckBox(name);
		box->setChecked(true);
		ui->layoutCheckBoxToShow->insertWidget(index, box);
		index++;
	}
}

SettingsWidget::~SettingsWidget()
{
	delete ui;
}
