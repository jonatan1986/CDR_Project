/*
 * threadObj.h
 *
 *  Created on: Aug 7, 2020
 *      Author: yonathan
 */

#ifndef THREADOBJ_H_
#define THREADOBJ_H_
#include <thread>

class ThreadObj
{
public:
  template< class Function, class... Args >
  explicit ThreadObj( Function&& f, Args&&... args )
  // :m_thread(f,args ...)
  {
    m_thread = std::thread(f,args ...);
  }
  ThreadObj(ThreadObj &&other)
  {
    m_thread = std::move(other.GetThread());
  }
  ~ThreadObj()
  {
    m_thread.join();
  }
  std::thread& GetThread() { return m_thread; }
private:
    std::thread m_thread;
    ThreadObj& operator= (ThreadObj &other);
    ThreadObj (ThreadObj &other);
};



#endif /* THREADOBJ_H_ */
