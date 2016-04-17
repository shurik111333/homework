#include <iostream>
#include "priorityqueuetest.h"

using namespace std;

int main(int argc, char *argv[])
{
	PriorityQueueTest test;
	QTest::qExec(&test);
	return 0;
}
