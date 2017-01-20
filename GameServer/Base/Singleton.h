#ifndef _Singleton_H
#define _Singleton_H

template <class T>
class Singleton
{
public:
	virtual ~Singleton()
	{
		delete m_sPInstance;
		m_sPInstance = nullptr;
	}

	static T* Instance()
	{
		if (nullptr == m_sPInstance)
		{
			m_sPInstance = new T;
		}
		return m_sPInstance;
	}

	static void DestroyInstance()
	{
		delete m_sPInstance;
		m_sPInstance = nullptr;
	}

private:
	static T* m_sPInstance;
};

template<class T> T* Singleton<T>::m_sPInstance = nullptr;

#endif // !_Singleton_H
