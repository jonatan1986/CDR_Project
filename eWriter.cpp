#include <iostream>
#include "eWriter.h"
#include "Factory.h"


#include <sys/types.h>
#include <unistd.h>
using namespace std;




cdrWriter::cdrWriter()
{
    // OutPutFileFactory outPutFileFactory;
    m_outPutFile = SingleTone<OutPutFileFactory>::GetIntstance()->Create();
}

void cdrWriter::GetCdrDetailsFromQueue(ThreadArgs &threadArgs,
CdrDetails &o_cdrDetails)const
{
  unique_lock<mutex> lk(threadArgs.m_writeQueueMutex);
  auto now = std::chrono::system_clock::now();
  threadArgs.m_writeQueueCV.wait_until(lk,now + 100ms,[&threadArgs](){return threadArgs.m_queueToWrite.Size() > 0;});
  if (threadArgs.m_bExitWriteThread == true && threadArgs.m_queueToWrite.Size() == 0)
  {
      // if both parser and reader finish writing to/ reading from the queue
      // but writer entered function after threadArgs.m_bExitWriteThread
      // was modified by parser, queue might be empty and program might crash
      return;
  }
  o_cdrDetails = threadArgs.m_queueToWrite.Remove();
}


void cdrWriter::WriteToFile(CdrDetails &cdrDetails)const
{
    m_outPutFile->WriteToFile(cdrDetails);
}

void cdrWriter::Write(ThreadArgs &threadArgs)const
{
   int i = 0;
   while(true)
   {
      CdrDetails l_cdrDetails;
      GetCdrDetailsFromQueue(threadArgs,l_cdrDetails);
      WriteToFile(l_cdrDetails);
      if (threadArgs.m_bExitWriteThread && threadArgs.m_queueToWrite.Size() == 0)
      {
         cout<<" break Write"<<endl;
         break;
      }
      if (i == 0)
        cout<<i<<"Write l_cdrDetails "<<l_cdrDetails.m_sImsi<<" "<<pthread_self()<<endl;
      ++i;
   }

  cout<<"Write"<<endl;
}
