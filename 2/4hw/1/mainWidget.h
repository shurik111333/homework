#pragma once

#include "settingsWidget.h"
#include <QWidget>

namespace Ui {
	class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

signals:
	void mapChanged();

public slots:
	void setNewSettings(SettingsWidget::Settings newSettings);

private slots:
	void addToMap();
	void removeFromMap();
	void findInMap();
	void updateInformation();
	void openSettings();

private:
	Ui::Widget *ui;
	SettingsWidget *settingsWidget;
	SettingsWidget::Settings settings;
};
