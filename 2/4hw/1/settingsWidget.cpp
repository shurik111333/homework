#include "settingsWidget.h"
#include "ui_settingsWidget.h"
#include <QCloseEvent>
#include <QCheckBox>
#include <QStringList>
#include <QSignalMapper>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
	ui->setupUi(this);
	ui->boxHash->addItems(Settings::getHashNames());

	Settings::init(ui->boxHash->currentText());
	//settings = new Settings();
	const auto checkBoxes = Settings::getCheckBoxNames();
	int index = 0;
	for (auto name : checkBoxes)
	{
		QCheckBox *box = new QCheckBox(name);
		box->setChecked(true);
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
	//delete settings;
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
		Settings::setCheckInformationState(box->text(), box->isChecked());
	}
	Settings::setHash(ui->boxHash->currentText());
	emit newSettings();
}

void SettingsWidget::restoreSettings()
{
	for (int i = 0; i < ui->layoutCheckBoxToShow->count(); i++)
	{
		QCheckBox *box = static_cast<QCheckBox*>(ui->layoutCheckBoxToShow->itemAt(i)->widget());
		box->setChecked(Settings::getCheckInformationState(box->text()));
	}
	ui->boxHash->setCurrentText(Settings::getCurrentHash());
}

void SettingsWidget::saveAndClose()
{
	saveSettings();
	this->close();
}
