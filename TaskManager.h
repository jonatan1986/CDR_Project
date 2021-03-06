/*
 * threadManager.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef THREADMANAGER_H_
#define THREADMANAGER_H_
#include <thread>
#include <queue>
#include <list>
#include <string>
// #include "ThreadPool.h"

class TaskManager
{
public:
    TaskManager(int numOfChunks,const std::string& filename);
    void CreateThreads();
    friend int GetAmountOfLines(TaskManager &taskManager);
private:
    int m_nNumOfChunks;
    std::string m_sFileName;
};



#endif /* THREADMANAGER_H_ */
