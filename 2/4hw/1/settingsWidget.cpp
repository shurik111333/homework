#include "settingsWidget.h"
#include "ui_settingsWidget.h"
#include <QCloseEvent>
#include <QCheckBox>
#include <QStringList>
#include <QSignalMapper>

SettingsWidget::SettingsWidget(Settings *settings, QWidget *parent) :
    QWidget(parent),
    settings(settings),
    ui(new Ui::SettingsWidget)
{
	ui->setupUi(this);
	ui->boxHash->addItems(Settings::getHashNames());
	const auto checkBoxes = Settings::getCheckBoxNames();
	int index = 0;
	for (auto name : checkBoxes)
	{
		QCheckBox *box = new QCheckBox(name);
		box->setChecked(settings->getCheckInformationState(box->text()));
		ui->layoutCheckBoxToShow->insertWidget(index, box);
		index++;
	}
	connect(ui->buttonsExit, &QDialogButtonBox::accepted,
	        this, &SettingsWidget::saveAndClose);
	connect(ui->buttonsExit, &QDialogButtonBox::rejected,
	        this, &SettingsWidget::close);
}

SettingsWidget::~SettingsWidget()
{
	delete ui;
}

void SettingsWidget::closeEvent(QCloseEvent *e)
{
	restoreSettings();
	e->accept();
}

void SettingsWidget::saveSettings()
{
	for (int i = 0; i < ui->layoutCheckBoxToShow->count(); i++)
	{
		QCheckBox *box = static_cast<QCheckBox*>(ui->layoutCheckBoxToShow->itemAt(i)->widget());
		settings->setCheckInformationState(box->text(), box->isChecked());
	}
	settings->setHash(ui->boxHash->currentText());
	emit newSettings();
}

void SettingsWidget::restoreSettings()
{
	for (int i = 0; i < ui->layoutCheckBoxToShow->count(); i++)
	{
		QCheckBox *box = static_cast<QCheckBox*>(ui->layoutCheckBoxToShow->itemAt(i)->widget());
		box->setChecked(settings->getCheckInformationState(box->text()));
	}
	ui->boxHash->setCurrentText(settings->getCurrentHash());
}

void SettingsWidget::saveAndClose()
{
	saveSettings();
	this->close();
}
