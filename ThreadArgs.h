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


struct ThreadArgs
{
    std::mutex m_parseQueueMutex;
    std::atomic<bool> m_bExitParseThread;
    std::condition_variable m_parseQueueCV;
};




#endif /* THREADARGS_H_ */
