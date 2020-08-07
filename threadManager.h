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
#include "singletone.h"

class threadManager
{
public:
    threadManager(int numOfThreads,const std::string& filename, int fileSize);
    void CreateThreads();
    ~threadManager();
private:
    // void Run(int startline,int endline);
    int m_numOfThreads;
    std::list<std::thread *> threadList;
    std::string m_filename;
    int m_fileSize;
};



#endif /* THREADMANAGER_H_ */
