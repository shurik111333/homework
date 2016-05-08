#include <iostream>
#include "sharedptr.h"
#include "sharedptrtest.h"

using namespace std;

int main(int argc, char *argv[])
{
	SharedPtrTest test;
	QTest::qExec(&test);
	return 0;
}
