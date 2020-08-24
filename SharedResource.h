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
#include "Config.h"
#include "SingleTone.h"

struct SharedResource
{
    SharedResource():m_bExitParseThread(false),m_bExitWriteThread(false)
    {
    }
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
  SharedResourceWrapper()
  {
    Config *l_config = SingleTone<Config>::GetIntstance();
    std::string l_sAmountOfChunks  = l_config->GetAmountOfChunks();
    size_t l_nAmountOfChunks =  l_sAmountOfChunks.length() > 0 ?
    stoi(l_sAmountOfChunks) : AMOUNT_OF_CHUNKS;
    m_SharedResourceArray = std::make_unique<SharedResource[]>(l_nAmountOfChunks);
  }
  SharedResource& GetResourceByIndex(size_t index)
  {return m_SharedResourceArray[index];}
private:
   std::unique_ptr<SharedResource[]> m_SharedResourceArray;
};



#endif /* SHARED_RESOURCE_H_ */
