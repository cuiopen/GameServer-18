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

	printf("[Success]WebServer Start OK!");

	while (true)
	{
		usleep(5);
	}
}

int main(int argc, char *argv[])
{
	StarServer(argc, argv);
	
	return 0;
}