#include <cstdio>
#include "Base/Thread.h"
#include <iostream>
#include <string>

class MyClass : public CThread
{
public:
	bool Run()
	{
		printf("Hello World!");
		return true;
	}
};


int main(int argc, char *argv[])
{
	MyClass myThread;
	myThread.Start();

	std::string strCMD;
	while (true)
	{
		std::cin >> strCMD;
	}
	return 0;
}