#include "HttpPacket.h"
#include <string.h>
#include <unistd.h>

void HttpPacket::Rest()
{
	m_btHandleType = 0;
	m_nPacketSize = 0;
	m_clientSocket = 0;
	memset(&m_szBuffer, 0, sizeof(m_szBuffer));
}

bool HttpPacket::Execute()
{
	close(m_clientSocket);
	return false;
}
