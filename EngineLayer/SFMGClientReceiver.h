#pragma once
#include "asios.h"
#include <map>

class SFMGClientReceiver : public INetworkReceiver
{
	typedef std::map<long, ASSOCKDESCEX> SessionMap;
public:
	SFMGClientReceiver(void);
	virtual ~SFMGClientReceiver(void);

	virtual void notifyRegisterSocket(ASSOCKDESCEX& sockdesc, SOCKADDR_IN& ip) override;
	virtual void notifyReleaseSocket(ASSOCKDESCEX& sockdesc) override;
	virtual void notifyMessage(ASSOCKDESCEX& sockdesc, size_t length, char* data) override;
	virtual void notifyConnectingResult(INT32 requestID, ASSOCKDESCEX& sockdesc, DWORD error);

	BOOL Send(int Serial, USHORT PacketID, char* pMessage, int BufSize );
	BOOL Send(int Serial, SFPacket* pPacket);

protected:

private:
//��Ƽ������� �����ؼ�
	SessionMap m_SessionMap;
	CriticalSectionLock m_SessionLock;
	ASSOCKDESCEX m_SocketDesc;

	SFPacketAnalyzer<SFCompressLzf> m_BufferAnalyzer;
};
