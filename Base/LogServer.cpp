#include "LogServer.h"
#include "CommonDefine.h"
#include "TimeManager.h"
#include <cstdio>
#include <string.h>
#include <unistd.h>
#include <string>

CLogServer::~CLogServer()
{
	
}

bool CLogServer::InitServer(const char * pszName)
{
	if (nullptr == pszName || strlen(pszName) < 1)
	{
		char strProcessPath[1024] = { 0 };
		if (readlink("/proc/self/exe", strProcessPath, sizeof(strProcessPath)) <= 0)
		{
			return false;
		}
		char *strProcessName = strrchr(strProcessPath, '/');
		m_strProcessName = ++strProcessName;
	}
	m_strProcessName = pszName;

	m_vecLogFile.resize(Log_Num);
	m_vecLogFile[Log_Debug] = "./Log/Debug";
	m_vecLogFile[Log_Assert] = "./Log/Assert";
	m_vecLogFile[Log_Player] = "./Log/Player";
	m_vecLogFile[Log_Mail] = "./Log/Mail";
	m_vecLogFile[Log_Recharge] = "./Log/Recharge";

	for (size_t i = 0; i < Log_Num; ++i)
	{
		m_LogSaveFlag[i] = 1;
	}
}

bool CLogServer::SaveLogEx(unsigned char usLogType, char * pszFunction, unsigned long unLine, pthread_t unThreadID, char * pszLog, ...)
{
	char szTemLogFormat[4096] = { 0 };
	va_list argptr;
	va_start(argptr, pszLog);
	vsprintf(szTemLogFormat, pszLog, argptr);
	va_end(argptr);

	time_t tCurrentTime = time(NULL);
	struct tm objNew;
	memset(&objNew, 0, sizeof(struct tm));
	memcpy(&objNew, localtime(&tCurrentTime), sizeof(struct tm));
	char szTime[1024];
	sprintf(szTime, "Thread: %d  Func: [%s]  Line: [%d] Log: Time: %04d-%02d-%02d %02d:%02d:%02d  \n", unThreadID, pszFunction, unLine, (objNew.tm_year + 1900), objNew.tm_mon + 1, objNew.tm_mday, objNew.tm_hour, objNew.tm_min, objNew.tm_sec);
	strcat(szTemLogFormat, szTime);

	return false;
}

void CLogServer::SaveLogToCache(unsigned char btLogType, char * pszBuffer, size_t nLength)
{

}
