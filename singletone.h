/*
 * singletone.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef SINGLETONE_H_
#define SINGLETONE_H_

#include<mutex>


template<class T>
class singletone
{
public:
	static T* GetIntstance()
	{
		if(m_singleTone == nullptr)
		{
			std::lock_guard<std::mutex>lk(m_mutex);
			if(m_singleTone == nullptr)
			{
				m_singleTone = new T;
			}
		}
		return m_singleTone;
	}
private:
	~singletone();
	singletone& operator=(singletone& other);
	singletone(singletone& other);
	static T *m_singleTone;
	static std::mutex m_mutex;


};

template<class T>
T* singletone<T>::m_singleTone = nullptr;

template<class T>
std::mutex singletone<T>:: m_mutex;
#endif /* SINGLETONE_H_ */
