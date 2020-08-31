/*
 * SharedResource.h
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
#include "Singleton.h"

/*
this  struct is a shared resouce between the threads eWriter,eReader and eParser.
@ m_parseQueueMutex - locks the access of the parser, till  m_queueToParse is not empty
@ m_writeQueueMutex - locks the access of the writer, till  m_queueToWrite is not empty
@ m_bExitParseThread - boolean var which indicates that parser should finish it's job once it emptied all
element from m_queueToParse. initialized to false
@ m_bExitWriteThread - boolean var which indicates that eWriter should finish it's job once it emptied all
element from m_queueToWrite. initialized to false
@ m_queueToParse - shared queue among eReader and eParser. eReader inserts, eParser removes.
@ m_queueToWrite - shared queue among eWriter and eParser. eParser inserts, eWriter removes.
*/
struct SharedResource
{
    SharedResource():m_bExitParseThread(false),m_bExitWriteThread(false)
    {
    }
    std::mutex m_rawDataQueueMutex;
    std::mutex m_cdrDataQueueMutex;
    std::atomic<bool> m_bExitParseThread;
    std::atomic<bool> m_bExitWriteThread;
    std::condition_variable m_rawDataQueueCV;
    std::condition_variable m_CdrDataQueueCV;
    SafeQueue<std::string> m_rawDataQueue;
    SafeQueue<eCdrDetails> m_CdrDataQueue;
};
/*
this class wraps "SharedResource". since the shared resources should have global access it should be wrapped with singleTone.
however there is more then one thread which has sub-threads(eReader,eWriter,eParser) so one instance of SharedResource will
not be a good solution(SingleTone provides only one instance),thus SharedResourceWrapper contains an array of "SharedResource"
so "SharedResourceWrapper" is wrapped by SingleTone - and each group of subthreads share an element of the array(of type "SharedResource").
*/
class SharedResourceWrapper
{
public:
  SharedResourceWrapper()
  {
    Config *l_config = Singleton<Config>::GetIntstance();
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
