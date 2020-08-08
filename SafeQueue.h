/*
 * SafeQueue.h
 *
 *  Created on: Aug 7, 2020
 *      Author: yonathan
 */

#ifndef SAFEQUEUE_H_
#define SAFEQUEUE_H_

#include<mutex>
#include <queue>

template <class T>
class SafeQueue
{
  public:
    std::queue<T>& GetQueue()const{return  m_queue;}
  private:
    std::queue<T> m_queue;
};


#endif /* SAFEQUEUE_H_ */
