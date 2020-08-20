
#include <iostream>
#include <memory>
#include"TaskManager.h"
#include"Task.h"

using namespace std;



TaskManager::TaskManager(int numOfThreads,const string& filename,int fileSize):m_numOfThreads(numOfThreads),
m_filename(filename),m_fileSize(fileSize)
{
}


void Run(const string& fileName, int startLine, int endLine)
{
  Task task(fileName,startLine,endLine);
  task.Run();
}

void TaskManager::CreateThreads()
{
  int startLine = 1,endLine = 2000;
  ThreadPool l_threadPool;
  for(int i = 0; i < m_numOfThreads; ++i)
  {
      l_threadPool.AddThread(&Run,m_filename,startLine,endLine);
      startLine = endLine + 1;
      endLine += 2000;
  }
}
