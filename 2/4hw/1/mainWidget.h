#pragma once

#include "settingsWidget.h"
#include "hashmap.h"
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

private:
	Ui::Widget *ui;
	Settings *settings;
	SettingsWidget *settingsUi;
	static const QString successAdd;
	static const QString successRemove;
	static const QString successFind;
	static const QString nonIntegerValue;
	static const QString findNothing;
	static const QString emptyKey;

	int getValue();
	QString getKey();
	void successfulMessage(const QString &m);
	void errorMessage(const QString &m);

private slots:
	void showSettings();
	void updateInformation();
	void addToMap();
	void removeFromMap();
	void findInMap();
};
