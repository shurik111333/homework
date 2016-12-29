#pragma once

#include "Player/iplayer.h"
#include "Tank/iTank.h"
#include "Landscape/iLandscapeGenerator.h"
#include "Shell/ShellType/ishelltype.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLineEdit>
#include <QVector>
#include <QLabel>
#include <QString>
#include <QHostAddress>

namespace Ui {
	class GameWindow;
}

class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit GameWindow(QWidget *parent = 0);
	~GameWindow();

	void localGame();
	void serverGame(const QHostAddress &address, quint16 port);
	void clientGame();

signals:
	void closing();

	// QWidget interface
protected:
	virtual void closeEvent(QCloseEvent *event) override;

private:
	QWidget *widget = nullptr;
	QVBoxLayout *mainLayout = nullptr;
	QGraphicsScene scene;
	QGraphicsView *view = nullptr;
	QGraphicsTextItem *playerName = nullptr;
	QPushButton *buttonNewGame = nullptr;
	QLabel *labelAddress = nullptr;
	QHBoxLayout *headerLayout = nullptr;
	QLineEdit *address = nullptr;
	QLabel *shellLabel = nullptr;
	QString shellTitle;
	QSize sceneSize = QSize(1000, 500);
	QSize viewOffset = QSize(3, 3);
	bool f = false;

	void drawLandscape(const QVector<QPointF> &land);
	void endOfGame(IPlayer *winner);
	QHBoxLayout *getNetworkInterface();

private slots:
	void newGame(const QVector<IPlayer *> &players);
	QString getWinnerMessage(IPlayer *winner);
	void clientConnected();
	void newStep(const IPlayer *player);
	void newShell(IShellType *type);

	// QObject interface
public:
	virtual bool eventFilter(QObject *watched, QEvent *event) override;
};
