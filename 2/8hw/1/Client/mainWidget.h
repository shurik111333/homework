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

	/// Add message to text box
	void addMessage(const QString &sender, const QString &msg);
	/// Return server host in format IP:port
	QString getServerHost() const;

private slots:
	void send();
	void connectToServer();
	void getMessage(const QString msg);
	/// Calls after succes connect to server
	void succesfullConnection();
};

