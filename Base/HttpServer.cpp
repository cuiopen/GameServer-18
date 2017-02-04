#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "HttpServer.h"
#include "CommonDefine.h"
#include <cstdio>
#include "Log.h"

CHttpServer::~CHttpServer()
{
	AutoLock lock(m_lockHttpServer);
	for (auto i = m_deqFreeHttpPacket.begin(), e = m_deqFreeHttpPacket.end(); i != e; ++i)
	{
		SAFE_DELETE(*i);
	}
	m_deqFreeHttpPacket.clear();

	for (auto i = m_deqHttpRequest.begin(), e = m_deqHttpRequest.end(); i != e; ++i)
	{
		SAFE_DELETE(*i);
	}
	m_deqHttpRequest.clear();
}

bool CHttpServer::InitServer(const char * pszIP, unsigned short int nPort)
{

	if (nullptr == pszIP || 0 == pszIP[0] || 0 == nPort)
		return false;

	m_socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (-1 == m_socketServer)
		return false;

	struct sockaddr_in server_sockaddr = { 0 };
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(nPort);
	server_sockaddr.sin_addr.s_addr = inet_addr(pszIP);

	if (-1 == bind(m_socketServer, (struct sockaddr*)&server_sockaddr, sizeof(struct sockaddr)))
	{ 
		printf("[Error]Server Bind Failed! Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
		close(m_socketServer);
		return false;
	}

	if (-1 == listen(m_socketServer, SOMAXCONN))
	{
		printf("[Error]Server Listen Failed! Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
		close(m_socketServer);
		return false;
	}

	unsigned short nTimeout = 5000;
	setsockopt(m_socketServer, SOL_SOCKET, SO_RCVTIMEO, (const char*)&nTimeout, sizeof(nTimeout));

	return true;
}

bool CHttpServer::Start()
{
	if (0 != pthread_create(&m_tThreadReciveID, nullptr, ThreadRecive, this))
	{
		printf("[Error]ThreadRecive Start Failed! Function:%s, Line:%d\n", __FUNCTION__, __LINE__);
		return false;
	}
	return CThread::Start();
}

void CHttpServer::ProcessLogic()
{
	ProcessMessage();
}

void CHttpServer::ProcessReciveMessage()
{
	int nReadLenght = 0;
	socklen_t nlenght = 0;

	struct sockaddr_in fd_client;
	nlenght = sizeof(struct sockaddr_in);
	HttpPacket *pPacket = nullptr;
	while (true)
	{
		if (IsClose())
			break;

		if (nullptr == pPacket)
			pPacket = PoPFreeHttpPacket();
		if (nullptr == pPacket)
			continue;

		pPacket->m_clientSocket = accept(m_socketServer, (struct sockaddr*)&fd_client, &nlenght);
		if (-1 == pPacket->m_clientSocket)
		{
			SaveAssertLog("HttpServer Accept Failed!");
			close(pPacket->m_clientSocket);
			this->AddFreeHttpPacket(pPacket);
			continue;
		}

		nReadLenght = recv(pPacket->m_clientSocket, pPacket->m_szBuffer, sizeof(pPacket->m_szBuffer), 0);
		if (-1 == nReadLenght)
		{
			SaveAssertLog("HttpServer Recv Failed!");
			close(pPacket->m_clientSocket);
			continue;
		}

		pPacket->m_btHandleType = 0;
		pPacket->m_nPacketSize = nReadLenght;

		if (nReadLenght > 0)
		{
			AddHttpPacket(pPacket);
			pPacket = nullptr;
		}
		else
		{
			close(pPacket->m_clientSocket);
		}
	}
}

void CHttpServer::ProcessMessage()
{
	HttpPacket *pPacket = PoPHttpPacket();
	if (nullptr == pPacket)
		return;

	pPacket->Execute();
	AddFreeHttpPacket(pPacket);
}

bool CHttpServer::Run()
{
	if (!IsClose())
	{
		ProcessLogic();
	}

	return CThread::Run();
}

void *CHttpServer::ThreadRecive(void * pParm)
{
	CHttpServer *pHttpServer = static_cast<CHttpServer*>(pParm);
	if (nullptr == pHttpServer)
		return nullptr;
	pHttpServer->ProcessReciveMessage();
	return nullptr;
}

void CHttpServer::AddFreeHttpPacket(HttpPacket * pPacket)
{
	AutoLock lock(m_lockHttpServer);
	m_deqFreeHttpPacket.push_back(pPacket);
}

HttpPacket * CHttpServer::PoPFreeHttpPacket()
{
	AutoLock lock(m_lockHttpServer);
	if (!m_deqFreeHttpPacket.empty())
	{
		HttpPacket *pPacket = m_deqFreeHttpPacket.front();
		m_deqFreeHttpPacket.pop_front();
		pPacket->Rest();
		return pPacket;
	}

	HttpPacket *pPacket = new HttpPacket();
	if (nullptr == pPacket)
		return nullptr;
	return pPacket;
}

void CHttpServer::AddHttpPacket(HttpPacket * pPacket)
{
	AutoLock lock(m_lockHttpServer);
	m_deqHttpRequest.push_back(pPacket);
}

HttpPacket * CHttpServer::PoPHttpPacket()
{
	AutoLock lock(m_lockHttpServer);
	if (m_deqHttpRequest.empty())
		return nullptr;
	HttpPacket *pPacket = m_deqHttpRequest.front();
	m_deqHttpRequest.pop_front();
	return pPacket;
}

size_t CHttpServer::GetHttpPacketSize()
{
	AutoLock lock(m_lockHttpServer);
	return m_deqHttpRequest.size();
}
