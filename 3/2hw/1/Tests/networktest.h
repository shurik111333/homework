#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <vector>
#include <fstream>

#include "Network/network.h"
#include "testvirus.h"
#include "testnetworkgenerator.h"
#include "Computer/computer.h"
#include "Computer/oslinux.h"
#include "Computer/osmac.h"
#include "Computer/oswindows.h"

using std::vector;
using std::ifstream;

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

	void testNetworkWithTestVirus()
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

	void testCorrectInfection()
	{
		int count = 10;
		computers.resize(count);
		for (int i = 0; i < count; i++)
		{
			OS *os = nullptr;
			switch (i % 3)
			{
				case 0:
					os = new OSWindows();
					break;
				case 1:
					os = new OSLinux();
					break;
				case 2:
					os = new OSMac();
					break;
			}
			computers.at(i) = new Computer(os, i);
		}
		computers.at(0)->setInfected(true);
		net = new Network(computers, new TestVirus(), new TestNetworkGenerator("testChain10.txt"));
		for (int i = 1; i < count; i++)
		{
			QVERIFY(!computers.at(i)->isInfected());
			net->nextStep();
		}
	}

	void testIsolatedNetwork()
	{
		int count = 10;
		computers.resize(count);
		for (int i = 0; i < count; i++)
		{
			computers[i] = new Computer(new OSLinux(), i);
		}
		computers[0]->setInfected(true);
		net = new Network(computers, new TestVirus(), new TestNetworkGenerator("testIsolated.txt"));
		for (int i = 0; i < 20; i++)
		{
			net->nextStep();
			QVERIFY(net->getInfectedCount() == 1);
		}
	}
};
