#ifndef _Log_H
#define _Log_H

#include <vector>
#include "Singleton.h"
#include "Thread.h"
#include <string>
#include <atomic>

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

class CLog : public Singleton<CLog>
{
public:
	~CLog();
	bool Init(const char* pszName);
	void SaveLogEx(unsigned char btLogType, const char * pszFunction, unsigned long unLine, pthread_t unThreadID, const char * pszLog, ...);

private:
	void SaveLogToCache(unsigned char btLogType, char* pszBuffer, size_t nLength);
	void FlushLogToFile(unsigned char btLogType);

private:
	std::vector<std::string> m_vecLogFile;
	std::string m_strProcessName;
	unsigned char m_LogSaveFlag[Log_Num] = { 0 };
	unsigned char m_LogPrintFlag[Log_Num] = { 0 };
	std::atomic_char* m_LogCache[Log_Num] = { nullptr };
	unsigned long m_LogPos[Log_Num] = { 0 };
};

//传入的msgLog必须是字符串
#define SaveDebugLog(msgLog, ...)	(CLog::Instance()->SaveLogEx( Log_Debug, __FUNCTION__, __LINE__, pthread_self(), msgLog, ##__VA_ARGS__))
#define SaveAssertLog(msgLog, ...)	(CLog::Instance()->SaveLogEx( Log_Assert, __FUNCTION__, __LINE__, pthread_self(), msgLog, ##__VA_ARGS__))
#define SavePlayerLog(msgLog, ...)	(CLog::Instance()->SaveLogEx( Log_Player, __FUNCTION__, __LINE__, pthread_self(), msgLog, ##__VA_ARGS__))
#define SaveMailLog(msgLog, ...)	(CLog::Instance()->SaveLogEx( Log_Mail, __FUNCTION__, __LINE__, pthread_self(), msgLog, ##__VA_ARGS__))
#define SaveRechargeLog(msgLog, ...)	(CLog::Instance()->SaveLogEx( Log_Recharge, __FUNCTION__, __LINE__, pthread_self(), msgLog, ##__VA_ARGS__))

#endif // _Log_H

