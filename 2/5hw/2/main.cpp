#include <iostream>
#include <string>
#include "setTest.h"

using namespace std;

int main()
{
	SetTest test;
	QTest::qExec(&test);
	return 0;
}
