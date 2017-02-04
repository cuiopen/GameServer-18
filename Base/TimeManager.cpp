#include "TimeManager.h"
#include <time.h>
#include <string.h>

unsigned long CTimeManager::GetYYYYMMDD()
{
	struct tm objNew;
	time_t tCurrentTime = time(NULL);
	memcpy(&objNew, localtime(&tCurrentTime), sizeof(struct tm));
	return ((objNew.tm_year + 1900) * 10000 + (objNew.tm_mon + 1) * 100 + objNew.tm_mday);
}

std::string CTimeManager::GetYYYYMMDDString()
{
	char szTime[32] = { 0 };
	struct tm objNew = { 0 };
	time_t tCurTime = time(NULL);
	memcpy(&objNew, localtime(&tCurTime), sizeof(struct tm));
	sprintf(szTime, "%04d-%02d-%02d", (objNew.tm_year + 1900), (objNew.tm_mon + 1), objNew.tm_mday);
	return szTime;
}

std::string CTimeManager::GetYYYYMMDDHHMMSSString()
{
	char szTime[64];
	time_t tCurrentTime = time(NULL);
	struct tm objNew = { 0 };
	memcpy(&objNew, localtime(&tCurrentTime), sizeof(struct tm));
	sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", (objNew.tm_year + 1900), objNew.tm_mon + 1, objNew.tm_mday, objNew.tm_hour, objNew.tm_min, objNew.tm_sec);
	return szTime;
}
