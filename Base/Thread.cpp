#include <unistd.h>
#include "Thread.h"

void *CThread::ThreadFunction(void * pParm)
{
	CThread *pThread = static_cast<CThread*>(pParm);
	if (nullptr == pThread)
		return nullptr;

	pThread->SetStatus(THREAD_STATUS_RUNNING);
	while (pThread->Run())
	{
		usleep(pThread->m_uSleepMill);
	}

	pThread->SetStatus(THREAD_STATUS_EXIT);
	pThread->Exit();

	return nullptr;
}

CThread::~CThread()
{
	m_tID = 0;
}

bool CThread::Start()
{
	if (THREAD_STATUS_READY != m_btStatus)
		return false;

	return 0 == pthread_create(&m_tID, nullptr, ThreadFunction, this);
}

pthread_t CThread::GetThreadID () const
{
	return m_tID;
}

unsigned char CThread::GetStatus()
{
	return m_btStatus;
}

bool CThread::IsRun()
{
	if (THREAD_STATUS_RUNNING == m_btStatus)
		return true;
	return false;
}

bool CThread::IsClose()
{
	return (THREAD_STATUS_EXIT == m_btStatus || THREAD_STATUS_EXITING == m_btStatus);
}

bool CThread::Exit()
{
	pthread_exit(nullptr);
}

void CThread::Join()
{
	pthread_join(m_tID, nullptr);
}

void CThread::SetStatus(unsigned char btStatus)
{
	m_btStatus = btStatus;
}

bool CThread::Run()
{
	if (IsClose())
		return false;
	return true;
}
