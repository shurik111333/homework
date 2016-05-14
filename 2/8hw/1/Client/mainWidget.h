#pragma once

#include <QWidget>
#include "client.h"

namespace Ui {
	class MainWidget;
}

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MainWidget(QWidget *parent = 0);
	~MainWidget();

private:
	Ui::MainWidget *ui;
	Client *client;

	void addMessage(const QString &sender, const QString &msg);
	QString getClientHost() const;

private slots:
	void send();
	void connectToServer();
	void getMessage(const QString msg);
	void succesfullConnection();
};

