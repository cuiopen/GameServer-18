#ifndef _Thread_H
#define _Thread_H
#include <pthread.h>
#include "Uncopiable.h"

class CThread : Uncopiable
{
	enum ThreadStatus
	{
		TREAD_STATUS_READY = 1,	// 当前线程处于准备状态
		TREAD_STATUS_RUNNING,	// 处于运行状态
		TREAD_STATUS_SUSPEND,	// 线程挂起暂停
		TREAD_STATUS_EXITING,	// 线程正在退出
		TREAD_STATUS_EXIT		// 已经退出 
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

