/*
 * ThreadArgs.h
 *
 *  Created on: Aug 11, 2020
 *      Author: yonathan
 */

#ifndef SHARED_RESOURCE_H_
#define SHARED_RESOURCE_H_

#include <condition_variable>
#include <atomic>
#include "eCdrDetails.h"
#include "SafeQueue.h"



struct SharedResource
{
    SharedResource():m_bExitParseThread(false),m_bExitWriteThread(false){}
    std::mutex m_parseQueueMutex;
    std::mutex m_writeQueueMutex;
    std::atomic<bool> m_bExitParseThread;
    std::atomic<bool> m_bExitWriteThread;
    std::condition_variable m_parseQueueCV;
    std::condition_variable m_writeQueueCV;
    SafeQueue<std::string> m_queueToParse;
    SafeQueue<eCdrDetails> m_queueToWrite;
};

class SharedResourceWrapper
{
public:
  SharedResource& GetResourceByIndex(size_t index)
  {return m_SharedResourceArray[index];}
private:
   SharedResource m_SharedResourceArray[5];
};



#endif /* SHARED_RESOURCE_H_ */
