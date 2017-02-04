#ifndef _WebServer_H
#define _WebServer_H

#include "../../Base/Singleton.h"
#include "../../Base/Thread.h"

class CWebServer : public CThread, public Singleton<CWebServer>
{
public:
	~CWebServer();
	bool InitServer(int argc, char *argv[]);
	bool Start();

private:
	void ProcessLogic();
	bool Run();
};

#endif // !_WebServer_H

