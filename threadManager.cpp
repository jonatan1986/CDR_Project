
#include <iostream>
#include <memory>
#include"threadManager.h"
#include"Job.h"

using namespace std;
int i  = 0;



threadManager::threadManager(int numOfThreads,const string& filename,int fileSize):m_numOfThreads(numOfThreads),
m_filename(filename),m_fileSize(fileSize)
{
}


void Run(const string& fileName, int startLine, int endLine)
{
  Job job(fileName,startLine,endLine);
  job.Run();
}

void threadManager::CreateThreads()
{
  int startLine = 1,endLine = 2000;
  for(int i = 0; i < 1/*m_numOfThreads*/; ++i)
  {
      threadPool.AddThread(&Run,m_filename,startLine,endLine);
      startLine = endLine + 1;
      endLine += 2000;
  }
}

threadManager::~threadManager()
{
}
