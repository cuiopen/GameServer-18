#ifndef _TimeManager_H
#define _TimeManager_H

#include "Singleton.h"

class CTimeManager : public Singleton<CTimeManager>
{
public:
	unsigned long GetYYYYMMDD();
};

#endif // !_TimeManager_H

