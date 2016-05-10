#include <iostream>

using namespace std;

class A
{
public:
	~A()
	{
		cout << "Remove A" << endl;
	}
};

class B : public A
{
public:
	~B()
	{
		cout << "Remove B" << endl;
	}
};

void f()
{
	B b;
	throw 1;
}

int main()
{
	try
	{
		f();
	}
	catch (int)
	{
		cout << "Catched" << endl;
	}
	return 0;
}
