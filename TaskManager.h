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
// #include "SingleTone.h"
#include "ThreadPool.h"

class TaskManager
{
public:
    TaskManager(int numOfThreads,const std::string& filename, int fileSize);
    void CreateThreads();
    // ~threadManager(){}
private:
    int m_numOfThreads;
    std::string m_filename;
    int m_fileSize;
};



#endif /* THREADMANAGER_H_ */
