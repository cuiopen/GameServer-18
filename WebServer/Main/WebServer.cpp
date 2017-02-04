#include "WebServer.h"
#include "../../Base/HttpServer.h"
#include "../../Base/Log.h"

CWebServer::~CWebServer()
{

}

bool CWebServer::InitServer(int argc, char * argv[])
{
	if (!CLog::Instance()->Init("WebServer"))
	{
		printf("[Error]Log Init Failed! Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
		return false;
	}

	if (!CHttpServer::Instance()->InitServer("127.0.0.1", 6666))
	{
		printf("[Error]HttpServer Init Failed! Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
		return false;
	}

	return true;
}

bool CWebServer::Start()
{
	if (!CHttpServer::Instance()->Start())
	{
		printf("[Error]HttpServer Start Failed! Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
		return false;
	}

	return CThread::Start();
}

void CWebServer::ProcessLogic()
{
}

bool CWebServer::Run()
{
	if (!IsClose())
	{
		ProcessLogic();
	}

	return CThread::Run();
}
