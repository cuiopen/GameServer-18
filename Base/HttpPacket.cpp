#include "HttpPacket.h"
#include <string.h>
#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>

void HttpPacket::Rest()
{
	m_btHandleType = 0;
	m_nPacketSize = 0;
	m_clientSocket = 0;
	memset(&m_szBuffer, 0, sizeof(m_szBuffer));
}

bool HttpPacket::Execute()
{
	printf(m_szBuffer);

	char html[] =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html;charset=utf-8\r\n"
		"\r\n"
		"%d\r\n";

	char szBuffer[512] = { 0 };
	sprintf(szBuffer, html, 6666);
	int nLength = strlen(szBuffer);
	send(m_clientSocket, szBuffer, nLength, 0);
	/////////关闭本次连接
	close(m_clientSocket);
	return false;
}
