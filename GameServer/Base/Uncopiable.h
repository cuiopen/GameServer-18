#ifndef _Uncopiable_H
#define _Uncopiable_H

#include <pthread.h>

class Uncopiable
{
public:
	Uncopiable() {}
	~Uncopiable() {}

private:
	Uncopiable(const Uncopiable&);
	Uncopiable& operator =(const Uncopiable&);
};

#endif
