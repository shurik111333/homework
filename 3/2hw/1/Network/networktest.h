#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <vector>

#include "network.h"
#include "Virus/testvirus.h"
#include "Computer/computer.h"
#include "Computer/oslinux.h"
#include "Computer/osmac.h"
#include "Computer/oswindows.h"

using std::vector;

class NetworkTest : public QObject
{
	Q_OBJECT

public:
	explicit NetworkTest(QObject *parent = 0) :
	    QObject(parent)
	{}
private:
	vector<Computer*> computers;
	Network *net = nullptr;

private slots:
	void init()
	{

	}

	void cleanup()
	{
		delete net;
		net = nullptr;
	}

	void testUninfectedNetwork()
	{
		computers = {new Computer(), new Computer(), new Computer()};
		net = new Network(computers, new TestVirus());
		for (int i = 0; i < 10; i++)
		{
			net->nextStep();
			for (auto c : computers)
				QVERIFY(!(c->isInfected()));
		}
	}

	void textNetworkWithTestVirus()
	{
		computers = {new Computer(new OSLinux(), 0), new Computer(new OSMac(), 1), new Computer(new OSWindows(), 2)};
		computers[0]->setInfected(true);
		net = new Network(computers, new TestVirus());
		net->nextStep();
		for (auto c : computers)
		{
			QVERIFY(c->isInfected());
		}
	}
};
