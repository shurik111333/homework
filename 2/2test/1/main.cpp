#include <iostream>
#include "bubblesortertest.h"

using namespace std;

int main(int argc, char *argv[])
{
	BubbleSorterTest test;
	QTest::qExec(&test);
	return 0;
}
