#include <iostream>
#include "bagTest.h"

using namespace std;

int main()
{
	BagTest test;
	QTest::qExec(&test);
	return 0;
}
