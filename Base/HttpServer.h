#ifndef _HttpServer_H
#define _HttpServer_H

#include <deque>
#include "Singleton.h"
#include "Thread.h"
#include "HttpPacket.h"

class CHttpServer : public CThread, public Singleton<CHttpServer>
{
public:
	~CHttpServer();
	bool InitServer(const char* pszIP, unsigned short int nPort);
	bool Start();
private:
	void ProcessLogic();
	void ProcessReciveMessage();
	void ProcessMessage();
	bool Run();
	static void *ThreadRecive(void *pParm);

	void AddFreeHttpPacket(HttpPacket *pPacket);
	HttpPacket *PoPFreeHttpPacket();
	void AddHttpPacket(HttpPacket *pPacket);
	HttpPacket *PoPHttpPacket();
	size_t GetHttpPacketSize();

private:
	int m_socketServer = 0;
	pthread_t m_tThreadReciveID = 0;
	std::deque<HttpPacket*> m_deqHttpRequest;
	std::deque<HttpPacket*> m_deqFreeHttpPacket;
	MyLock m_lockHttpServer;
	
};

#endif // !_HttpServer_H

