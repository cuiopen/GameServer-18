#ifndef _Thread_H
#define _Thread_H
#include <pthread.h>
#include "Uncopiable.h"

class CThread : Uncopiable
{
	enum ThreadStatus
	{
		TREAD_STATUS_READY = 1,	// ��ǰ�̴߳���׼��״̬
		TREAD_STATUS_RUNNING,	// ��������״̬
		TREAD_STATUS_SUSPEND,	// �̹߳�����ͣ
		TREAD_STATUS_EXITING,	// �߳������˳�
		TREAD_STATUS_EXIT		// �Ѿ��˳� 
	};

public:
	virtual ~CThread();
	virtual bool Start();
	pthread_t GetThreadID() const;
	unsigned char GetStatus() const;
	virtual bool Run() = 0;
	virtual bool Exit();
	virtual void Join();
private:
	static void *ThreadFunction(void *pParm);
	void SetStatus(unsigned char btStatus);
private:
	pthread_t m_tID = 0;
	unsigned char m_btStatus = TREAD_STATUS_READY;
	unsigned int m_uSleepMill = 5;

};

#endif // _Thread_H

