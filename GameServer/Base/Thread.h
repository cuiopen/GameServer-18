#ifndef _Thread_H
#define _Thread_H
#include <pthread.h>
#include "Uncopiable.h"
#include "Lock.h"

class CThread : Uncopiable
{
	enum ThreadStatus
	{
		THREAD_STATUS_READY = 1,	// ��ǰ�̴߳���׼��״̬
		THREAD_STATUS_RUNNING,	// ��������״̬
		THREAD_STATUS_SUSPEND,	// �̹߳�����ͣ
		THREAD_STATUS_EXITING,	// �߳������˳�
		THREAD_STATUS_EXIT		// �Ѿ��˳� 
	};

public:
	pthread_t GetThreadID() const;
	unsigned char GetStatus();
	bool IsRun();
	bool IsClose();

	virtual ~CThread();
	virtual bool Start();
	virtual bool Run();
	virtual bool Exit();
	virtual void Join();

private:
	static void *ThreadFunction(void *pParm);
	void SetStatus(unsigned char btStatus);

public:
	typedef CThread Parrent;

private:
	pthread_t m_tID = 0;
	unsigned char m_btStatus = THREAD_STATUS_READY;
	unsigned int m_uSleepMill = 0;
	MyLock m_lockStatus;
};

#endif // _Thread_H

