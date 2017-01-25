#include <cstdio>
#include "../../Base/HttpServer.h"
#include <iostream>
#include <string>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (CHttpServer::Instance()->InitServer("127.0.0.1", 6666))
		CHttpServer::Instance()->Start();

	while (true)
	{
		usleep(5);
	}
	return 0;
}