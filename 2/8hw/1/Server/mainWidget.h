#pragma once

#include <QWidget>
#include "server.h"

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
	Server *server;

private slots:
	void sendMsg();
};
