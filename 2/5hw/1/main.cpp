#include <iostream>
#include "testtree.h"

using namespace std;

const int maxLen = 256;

int main()
{
	TestTree test;
	QTest::qExec(&test);
	return 0;
}
