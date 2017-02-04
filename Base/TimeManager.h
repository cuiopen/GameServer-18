#ifndef _TimeManager_H
#define _TimeManager_H

#include "Singleton.h"
#include <string>

class CTimeManager : public Singleton<CTimeManager>
{
public:
	unsigned long GetYYYYMMDD();
	std::string GetYYYYMMDDString();
	std::string GetYYYYMMDDHHMMSSString();
};

#endif // !_TimeManager_H

