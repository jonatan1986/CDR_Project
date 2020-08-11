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
      threadList.push_back(std::move(l_thread));
    }
    ~ThreadPool()
    {
      while(threadList.size())
      {
         std::thread threadToDelete = std::move(threadList.front());
         threadToDelete.join();
         threadList.pop_front();
      }
    }
private:
    std::list<std::thread > threadList;

};



#endif /* THREADPOOL_H_ */
