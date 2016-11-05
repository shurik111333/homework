#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Network/network.h"
#include "Computer/computer.h"
#include "Computer/oswindows.h"
#include "Computer/oslinux.h"
#include "Computer/osmac.h"
#include "Virus/randomvirus.h"

#include "Tests/networktest.h"

using namespace std;

vector<Computer*> *getComputers(int count)
{
	srand(time(0));
	auto computers = new vector<Computer*>(count);
	for (int i = 0; i < count; i++)
	{
		int x = rand() % 3;
		OS *os = nullptr;
		switch (x)
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
		computers->at(i) = new Computer(os, i);
	}
	return computers;
}

void printComputers(const vector<Computer*> &computers)
{
	cout << "Computers:";
	for (auto c : computers)
	{
		cout << " " << c->getOs()->getName();
	}
	cout << "\n";
}

int main(int argc, char *argv[])
{
	NetworkTest test;
	QTest::qExec(&test);

	int n = 0;
	while (n <= 0)
	{
		cout << "Enter positive number of computers" << endl;
		cin >> n;
	}
	auto computers = getComputers(n);
	printComputers(*computers);

	computers->at(rand() % n)->setInfected(true);
	Network net(*computers, new RandomVirus());

	net.printStatus(cout);
	while (net.getInfectedCount() < n)
	{
		net.nextStep();
		net.printStatus(cout);
	}
	return 0;
}
