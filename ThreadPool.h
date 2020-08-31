/*
 * ThreadPool.h
 *
 *  Created on: Aug 8, 2020
 *      Author: yonathan
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <list>
#include <thread>

class ThreadPool
{
public:
    template< class Function, class... Args >
    void AddThread(Function&& f, Args&&... args )
    {
      std::thread l_thread(f,args...);
      m_threadList.push_back(std::move(l_thread));
    }
    ~ThreadPool()
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



#endif /* THREADPOOL_H_ */
