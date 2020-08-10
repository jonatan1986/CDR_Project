/*
 * SafeQueue.h
 *
 *  Created on: Aug 7, 2020
 *      Author: yonathan
 */

#ifndef SAFEQUEUE_H_
#define SAFEQUEUE_H_

#include <queue>
#include<iostream>
#include<mutex>

template <class T>
class SafeQueue
{
  public:

    SafeQueue(){}
    void PrintMutex()
    {
      std::cout<<&m_mutex<<std::endl;
    }
    void Insert(T &t)
    {
      std::lock_guard<std::mutex> lk(m_mutex);
      m_queue.push(t);
    }
    void Remove(T &t)
    {
      std::lock_guard<std::mutex> lk(m_mutex);
      m_queue.pop(t);
    }
  private:
    std::mutex m_mutex;
    std::queue<T> m_queue;

};


#endif /* SAFEQUEUE_H_ */
