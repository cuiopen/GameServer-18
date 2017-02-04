#include <cstdio>
#include "WebServer.h"
#include <iostream>
#include <string>
#include <unistd.h>

void StarServer(int argc, char *argv[])
{
	if (!CWebServer::Instance()->InitServer(argc, argv))
	{
		printf("[Error]WebServer Init Failed! Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
		return;
	}

	if (!CWebServer::Instance()->Start())
	{
		printf("[Error]WebServer Start Failed! Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
		return;
	}

	printf("[Success]WebServer Start OK! PID:%d\n", getpid());

	std::string strCMD;
	while (true)
	{
		std::cin >> strCMD;
		if (strCMD == "exit")
			exit(0);
	}
}

int main(int argc, char *argv[])
{
	StarServer(argc, argv);
	
	return 0;
}