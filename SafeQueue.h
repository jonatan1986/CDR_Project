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
#include<shared_mutex>
#include<mutex>

template <class T>
class SafeQueue
{
  public:
    // std::queue<T>& GetQueue()const{return  m_queue;}
    // SafeQueue(std::mutex &mtx):
    // SafeQueue(std::mutex &mtx):m_mutex(mtx){}
    SafeQueue(){}
    SafeQueue(const SafeQueue& other)
    {
      std::cout<<"cp ctor "<<std::endl;
    }
    void PrintMutex()
    {
      // std::cout<<&m_mutex<<std::endl;
    }
  private:
    // std::mutex m_mutex;
    mutable std::shared_mutex mutex_;
    std::queue<T> m_queue;

};


#endif /* SAFEQUEUE_H_ */
