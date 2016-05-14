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

private slots:
	void send();
	void connectToServer();
};

