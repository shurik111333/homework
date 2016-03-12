#pragma once

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

	enum class Hash
	{
		polynominal,
		linear
	};

	struct Settings
	{
		Hash currentHash;
		int startSize;

		bool operator != (const Settings &settings) const
		{
			return (currentHash != settings.currentHash || startSize != settings.startSize);
		}
	};

	Settings getSettings();
	Hash getHash();
	QString getHashByIndex(int index);
	int getStartSize();

signals:
	void newSettings(Settings settings);

private:
	Ui::SettingsWidget *ui;
	Settings settings;

	Settings getNewSettings();
	int getNewStartSize();
	SettingsWidget::Hash getNewHash();
	void closeEvent(QCloseEvent *event);

private slots:
	void saveSettings();
	void restoreSettings();
	void closeSettings(QAbstractButton *button);
};
