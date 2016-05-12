#include <iostream>
#include "vectorTest.h"

using namespace std;

int main(int argc, char *argv[])
{
	VectorTest test;
	QTest::qExec(&test);
	return 0;
}
