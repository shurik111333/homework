#include "mainWidget.h"
#include "ui_mainWidget.h"
#include <QPalette>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
	ui->setupUi(this);
	auto set = new SettingsWidget();
	set->show();
}

Widget::~Widget()
{
	delete ui;
}
