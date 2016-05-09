#pragma once
#include <QWidget>

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
	static const int minSize = 3;
	static const int maxSize = 10;

private slots:
	void drawField();
};
