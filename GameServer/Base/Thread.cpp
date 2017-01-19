#include <unistd.h>
#include "Thread.h"

void *CThread::ThreadFunction(void * pParm)
{
	CThread *pThread = static_cast<CThread*>(pParm);
	if (nullptr == pThread)
		return nullptr;

	pThread->SetStatus(TREAD_STATUS_RUNNING);
	while (pThread->Run())
	{
		usleep(pThread->m_uSleepMill);
	}

	pThread->SetStatus(TREAD_STATUS_EXIT);

	return nullptr;
}

CThread::~CThread()
{
	m_tID = 0;
}

bool CThread::Start()
{
	if (TREAD_STATUS_READY != m_btStatus)
		return false;

	return 0 == pthread_create(&m_tID, nullptr, ThreadFunction, this);
}

pthread_t CThread::GetThreadID () const
{
	return m_tID;
}

unsigned char CThread::GetStatus() const
{
	return m_btStatus;
}

bool CThread::Exit()
{
	pthread_exit(nullptr);
	m_btStatus = TREAD_STATUS_EXIT;
}

void CThread::Join()
{
	pthread_join(m_tID, nullptr);
}

void CThread::SetStatus(unsigned char btStatus)
{
	m_btStatus = btStatus;
}
