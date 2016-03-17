#pragma once

#include "settings.h"
#include <QWidget>
#include <QAbstractButton>
#include <QEvent>

namespace Ui {
	class SettingsWidget;
}

class SettingsWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SettingsWidget(Settings *settings, QWidget *parent = 0);
	~SettingsWidget();

signals:
	void newSettings();

protected:
	void closeEvent(QCloseEvent *e);

private:
	Ui::SettingsWidget *ui;
	Settings *settings;

	void saveSettings();
	void restoreSettings();

private slots:
	void saveAndClose();
};
