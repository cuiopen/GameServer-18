#include "Log.h"
#include "CommonDefine.h"
#include "TimeManager.h"
#include <cstdio>
#include <string.h>
#include <unistd.h>
#include <string>
#include <stdarg.h>

CLog::~CLog()
{
}

bool CLog::Init(const char * pszName)
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
	return true;
}

void CLog::SaveLogEx(unsigned char btLogType, const char * pszFunction, unsigned long unLine, pthread_t unThreadID, const char * pszLog, ...)
{
	char szTemLogFormat[4096] = { 0 };
	va_list argptr;
	va_start(argptr, pszLog);
	vsprintf(szTemLogFormat, pszLog, argptr);
	va_end(argptr);

	char szTime[1024];
	sprintf(szTime, "Thread: %ld  Func: [%s]  Line: [%ld] Log: Time: %s  \n", unThreadID, pszFunction, unLine, CTimeManager::Instance()->GetYYYYMMDDHHMMSSString().c_str());
	strcat(szTemLogFormat, szTime);

	SaveLogToCache(btLogType, szTemLogFormat, strlen(szTemLogFormat));
}

void CLog::SaveLogToCache(unsigned char btLogType, char * pszBuffer, size_t nLength)
{
	if (nullptr == pszBuffer)
	{
		printf("[Error] SaveLogToCache, pszBuffer is null, Function:%s, Line:%d ", __FUNCTION__, __LINE__);
		return;
	}

	if (btLogType > Log_Num)
		return;

	if (Log_Assert == btLogType)
		FlushLogToFile(Log_Num);

	if (1 == m_LogPrintFlag[btLogType])
	{

	}

	if (1 == m_LogSaveFlag[btLogType])
	{
		if (nullptr == m_LogCache[btLogType])
			m_LogCache[btLogType] = new std::atomic_char[MAX_LOG_CACHE_SIZE];
		if (nullptr == m_LogCache[btLogType])
			printf("[Error] Log Cache New Buffer Error, LogType:%hhd, Function:%s, Line:%d ", btLogType, __FUNCTION__, __LINE__);
		m_LogPos[btLogType] = 0;
	}

	if (MAX_LOG_CACHE_SIZE - m_LogPos[btLogType] < nLength)
	{
		this->FlushLogToFile(btLogType);
	}

	memcpy(&m_LogCache[btLogType][m_LogPos[btLogType]], pszBuffer, nLength);
	m_LogPos[btLogType] += nLength;

	if (Log_Assert == btLogType)
		FlushLogToFile(btLogType);
}

void CLog::FlushLogToFile(unsigned char btLogType)
{
	if (btLogType > Log_Num)
		return;

	std::string strFile = "";
	if (Log_Num != btLogType)
	{
		if (0 == m_LogSaveFlag[btLogType])
			return;
		
		if (nullptr == m_LogCache[btLogType] || 0 == m_LogPos)
			return;

		strFile = m_vecLogFile[btLogType] + "_" + m_strProcessName +"_" + CTimeManager::Instance()->GetYYYYMMDDString() + ".log";
		FILE *pFile = fopen(strFile.c_str(), "a+");
		if (nullptr == pFile)
		{
			printf("[Error] Open LogFile Fail! FileName:%s, Function:%s, Line:%d ", strFile.c_str(), __FUNCTION__, __LINE__);
			m_LogPos[btLogType] = 0;
			return;
		}

		fwrite(m_LogCache[btLogType], 1, m_LogPos[btLogType], pFile);
		m_LogPos[btLogType] = 0;
		fclose(pFile);
		return;
	}
	else
	{
		for (size_t i = 0; i < Log_Num; ++i)
		{
			if (0 == m_LogSaveFlag[i])
				continue;

			if (nullptr == m_LogCache[i] || 0 == m_LogPos)
				continue;

			strFile = m_vecLogFile[i] + "_" + CTimeManager::Instance()->GetYYYYMMDDString() + ".log";
			FILE *pFile = fopen(strFile.c_str(), "a+");
			if (nullptr == pFile)
			{
				printf("[Error] Open LogFile Fail! FileName:%s, Function:%s, Line:%d ", strFile.c_str(), __FUNCTION__, __LINE__);
				continue;
			}

			fwrite(m_LogCache[i], 1, m_LogPos[i], pFile);
			m_LogPos[i] = 0;
			fclose(pFile);
		}
	}
}
