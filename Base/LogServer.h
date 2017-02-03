#ifndef _HttpServer_H
#define _HttpServer_H

#include <vector>
#include "Singleton.h"
#include "Thread.h"
#include <string>

#define MAX_LOG_CACHE_SIZE  1024 * 1024 * 4

enum
{
	Log_Debug,
	Log_Assert,
	Log_Player,
	Log_Mail,
	Log_Recharge,
	Log_Num,
};

class CLogServer : public Singleton<CLogServer>
{
public:
	~CLogServer();
	bool InitServer(const char* pszName);
	bool SaveLogEx(unsigned char usLogType, char * pszFunction, unsigned long unLine, pthread_t unThreadID, char * pszLog, ...);

private:
	void SaveLogToCache(unsigned char btLogType, char* pszBuffer, size_t nLength);

private:
	MyLock m_objLockLog[Log_Num];
	std::vector<std::string> m_vecLogFile;
	std::string m_strProcessName;
	unsigned char m_LogSaveFlag[Log_Num] = { 0 };
	unsigned char m_LogPrintFlag[Log_Num] = { 0 };
	char *m_LogCache[Log_Num] = { nullptr };
};

//传入的msgLog必须是字符串
#define SaveDebugLog(msgLog, ...)	(CLogServer::Instance()->SaveLogEx( Log_Debug, __FUNCTION__, __LINE__, pthread_self(), msgLog, ##__VA_ARGS__))
#define SaveAssertLog(msgLog, ...)	(CLogServer::Instance()->SaveLogEx( Log_Assert, __FUNCTION__, __LINE__, pthread_self(), msgLog, ##__VA_ARGS__))
#define SavePlayerLog(msgLog, ...)	(CLogServer::Instance()->SaveLogEx( Log_Player, __FUNCTION__, __LINE__, pthread_self(), msgLog, ##__VA_ARGS__))
#define SaveMailLog(msgLog, ...)	(CLogServer::Instance()->SaveLogEx( Log_Mail, __FUNCTION__, __LINE__, pthread_self(), msgLog, ##__VA_ARGS__))
#define SaveRechargeLog(msgLog, ...)	(CLogServer::Instance()->SaveLogEx( Log_Recharge, __FUNCTION__, __LINE__, pthread_self(), msgLog, ##__VA_ARGS__))

#endif // !_HttpServer_H

