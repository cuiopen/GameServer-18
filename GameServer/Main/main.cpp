#include <cstdio>
#include "../Base/HttpServer.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	CHttpServer::Instance()->InitServer("192.168.21.129", 6666);
	CHttpServer::Instance()->Start();
	std::string strCMD;
	while (true)
	{
		std::cin >> strCMD;
		if (strCMD == "exit")
			return 0;
	}
	return 0;
}