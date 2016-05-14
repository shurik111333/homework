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

	/// Add message to text box
	void addMessage(const QString &sender, const QString &msg);
	/// @return Return client host in format IP:port
	QString getClientHost() const;

private slots:
	void sendMsg();
	void getMessage(const QString msg);
	/// This calls, when new client has been connected
	void newClient();
	void clientDisconnected();
};
