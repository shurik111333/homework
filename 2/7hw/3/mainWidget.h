#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>

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
	QVBoxLayout *mainLayout;
	QGridLayout *buttonsLayout;
	QList<QList<QPushButton*>> buttons;
	int size;
	static const int minSize = 3;
	static const int maxSize = 10;

	void drawField();
	void createButtons();

private slots:
	void newSize(int newSize);
};
