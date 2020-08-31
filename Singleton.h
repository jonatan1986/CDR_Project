/*
 * Singleton.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include<mutex>


template<class T>
class Singleton
{
public:
	static T* GetIntstance()
	{
		if(m_singleton == nullptr)
		{
			std::lock_guard<std::mutex>lk(m_mutex);
			if(m_singleton == nullptr)
			{
				m_singleton = new T;
			}
		}
		return m_singleton;
	}
private:
	~Singleton();
	Singleton& operator=(Singleton& other);
	Singleton(Singleton& other);
	static T *m_singleton;
	static std::mutex m_mutex;


};

template<class T>
T* Singleton<T>::m_singleton = nullptr;

template<class T>
std::mutex Singleton<T>:: m_mutex;

#endif /* SINGLETON_H_ */
