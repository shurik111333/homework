#pragma once

#include "settings.h"
#include <QWidget>
#include <QAbstractButton>

namespace Ui {
	class SettingsWidget;
}

class SettingsWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SettingsWidget(QWidget *parent = 0);
	~SettingsWidget();

private:
	Ui::SettingsWidget *ui;
};
