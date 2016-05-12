#pragma once

#include <QWidget>
#include "bash.h"

namespace Ui {
	class MainWidget;
}

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MainWidget(QWidget *parent = 0);
	~MainWidget();

signals:
	void newPos();

private:
	Ui::MainWidget *ui;
	Bash *bash;
	QMap<QString, QList<QString> > *content = nullptr;
	int currentPosition = 0;

	void setPos(int pos);

public slots:
	void newContent(QMap<QString, QList<QString> > &content);
	void updateButtons();
	void updateContent();
};
