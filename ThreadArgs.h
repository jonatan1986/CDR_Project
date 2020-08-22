/*
 * ThreadArgs.h
 *
 *  Created on: Aug 11, 2020
 *      Author: yonathan
 */

#ifndef THREADARGS_H_
#define THREADARGS_H_

#include <condition_variable>
#include <atomic>
#include "eCdrDetails.h"
#include "SafeQueue.h"



struct ThreadArgs
{
    ThreadArgs():m_bExitParseThread(false),m_bExitWriteThread(false){}
    std::mutex m_parseQueueMutex;
    std::mutex m_writeQueueMutex;
    std::atomic<bool> m_bExitParseThread;
    std::atomic<bool> m_bExitWriteThread;
    std::condition_variable m_parseQueueCV;
    std::condition_variable m_writeQueueCV;
    SafeQueue<std::string> m_queueToParse;
    SafeQueue<CdrDetails> m_queueToWrite;
};

class SharedResourceWrapper
{
public:
  const ThreadArgs& GetResourceByIndex(size_t index) const
  {return m_ThreadArgsArray[index];}
private:
   ThreadArgs m_ThreadArgsArray[5];
};



#endif /* THREADARGS_H_ */
