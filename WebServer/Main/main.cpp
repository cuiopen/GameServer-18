#include <cstdio>
#include "../../Base/HttpServer.h"
#include <iostream>
#include <string>
#include <unistd.h>

void StarServer(int argc, char *argv[])
{
	if (CHttpServer::Instance()->InitServer("192.168.210.129", 6666))
	{
		if (!CHttpServer::Instance()->Start())
		{
			printf("[Error]Server Start failed! Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
			return;
		}

	}
	else
	{
		printf("[Error]Server Init failed! Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
		return;
	}

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