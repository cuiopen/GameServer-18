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
