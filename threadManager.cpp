
#include <iostream>
#include <memory>
#include"threadManager.h"
#include"eJob.h"

using namespace std;




threadManager::threadManager(int numOfThreads,const string& filename,int fileSize):m_numOfThreads(numOfThreads),
m_filename(filename),m_fileSize(fileSize)
{
}


void Run(const string& filename, int startline, int endline)
{
  shared_ptr<eJob> job = make_shared<threadPoolJob>(filename,startline,endline);
  job->Run();
}

void threadManager::CreateThreads()
{
  int startLine = 1,endLine = 2000;
  for(int i = 0; i < m_numOfThreads; ++i)
  {
      thread *l_thread = new thread(&Run,ref(m_filename),ref(startLine),ref(endLine));
      threadList.push_back(l_thread);
  }
}

threadManager::~threadManager()
{
  while(threadList.size())
  {
     thread *threadToDelete = threadList.front();
     threadList.pop_front();
     threadToDelete->join();
     delete threadToDelete;
  }
}
