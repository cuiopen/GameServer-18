#include <cstdio>
#include <pthread.h>
#include "Base/Lock.h"
#include <sys/socket.h>

int main(int argc, char *argv[])
{
	char sz[128] = { 0 };
	sprintf(sz, "Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
	printf(sz);
	return 0;
}