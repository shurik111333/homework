#include "settingsWidget.h"
#include "ui_settingsWidget.h"
#include <QCloseEvent>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
	ui->setupUi(this);
	saveSettings();
	QObject::connect(ui->buttonsExit, &QDialogButtonBox::clicked,
	                 this, &SettingsWidget::closeSettings);
}

SettingsWidget::~SettingsWidget()
{
	delete ui;
}

SettingsWidget::Settings SettingsWidget::getSettings()
{
	return settings;
}

SettingsWidget::Hash SettingsWidget::getHash()
{
	return settings.currentHash;
}

QString SettingsWidget::getHashByIndex(int index)
{
	if (index == -1)
		return "";
	return ui->boxHash->itemText(index);
}

int SettingsWidget::getStartSize()
{
	return settings.startSize;
}

SettingsWidget::Settings SettingsWidget::getNewSettings()
{
	return Settings {getNewHash(), getNewStartSize()};
}

SettingsWidget::Hash SettingsWidget::getNewHash()
{
	Hash hash[2] = {Hash::polynominal, Hash::linear};
	int i = ui->boxHash->currentIndex();
	return hash[i];
}

void SettingsWidget::closeEvent(QCloseEvent *event)
{
	restoreSettings();
	event->accept();
}

void SettingsWidget::saveSettings()
{
	Settings oldSettings = settings;
	settings = getNewSettings();
	if (oldSettings != settings)
		emit newSettings(settings);
}

void SettingsWidget::restoreSettings()
{
	ui->boxHash->setCurrentIndex((int)(settings.currentHash));
	ui->boxSize->setValue(settings.startSize);
}

void SettingsWidget::closeSettings(QAbstractButton *button)
{
	if (button->text() == "OK")
		saveSettings();
	this->close();
}

int SettingsWidget::getNewStartSize()
{
	return ui->boxSize->value();
}
