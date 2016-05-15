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
	/// Emits when index of current quote was changed
	void newQuote();

private:
	Ui::MainWidget *ui;
	Bash *bash;
	/// Index of displayed quote
	int currentQuote = 0;
	/// Change index of current quote
	void setQuote(int index);

private slots:
	/// Reset interface to first quote
	void reset();
	/// Update button state(enabled/disabled)
	void updateButtons();
	void updateContent();
	void nextQuote();
	void prevQuote();
	void rateUp();
	void rateDown();
	void rateBayan();
};
