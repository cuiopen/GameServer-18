#ifndef _HttpPacket_H
#define _HttpPacket_H

class HttpPacket
{
public:
	void Rest();
	bool Execute();

public:
	unsigned char m_btHandleType = 0;
	unsigned short m_nPacketSize = 0;
	int m_clientSocket = 0;
	char m_szBuffer[1024] = { 0 };
};

#endif // _HttpPacket_H

