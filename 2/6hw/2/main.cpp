#include <iostream>
#include "UniqueListTest.h"

using namespace std;

int main(int argc, char *argv[])
{
	UniqueListTest test;
	QTest::qExec(&test);
	return 0;
}
