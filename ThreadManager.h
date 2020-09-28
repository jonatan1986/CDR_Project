/*
 * ThreadPool.h
 *
 *  Created on: Aug 8, 2020
 *      Author: yonathan
 */

#ifndef THREAD_MANAGER_H_
#define THREAD_MANAGER_H_


#include <list>
#include <thread>

class ThreadManager
{
public:
    template< class Function, class... Args >
    void AddThread(Function&& f, Args&&... args )
    {
      std::thread l_thread(f,args...);
      m_threadList.push_back(std::move(l_thread));
    }
    ~ThreadManager()
    {
      while(m_threadList.size())
      {
         std::thread l_threadToJoin = std::move(m_threadList.front());
         l_threadToJoin.join();
         m_threadList.pop_front();
      }
    }
private:
    std::list<std::thread > m_threadList;

};



#endif /* THREAD_MANAGER_H_ */
