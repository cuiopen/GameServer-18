#ifndef _SocketServer_H
#define _SocketServer_H

#include "Singleton.h"

class CSocketServer : public Singleton<CSocketServer>
{
public:
	~CSocketServer();
	bool Init();
};

#endif // !_SocketServer_H



