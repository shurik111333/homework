#include <iostream>

#include "network.h"

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Enter count" << endl;
	int n = 0;
	cin >> n;
	Network net(n);

	while (net.getInfectedCount() < n)
	{
		auto comps = net.getComputers();
		cout << "Infected : ";
		for (int i = 0; i < n; i++)
			if (comps[i].isInfected())
				cout << i + 1 << ' ';
		cout << "\n";
		net.nextStep();
	}
	return 0;
}
