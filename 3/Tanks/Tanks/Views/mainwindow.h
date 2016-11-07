#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	QVBoxLayout *mainLayout = nullptr;
	QGraphicsScene scene;
	QGraphicsView *view = nullptr;

	void drawLandscape(const QList<QPointF> &land);
};
