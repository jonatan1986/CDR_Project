#include <iostream>
#include "eWriter.h"

using namespace std;


void cdrWriter::GetCdrDetailsFromQueue(ThreadArgs &threadArgs,
CdrDetails &cdrDetails)
{
  unique_lock<mutex> lk(threadArgs.m_writeQueueMutex);
  auto now = std::chrono::system_clock::now();
  threadArgs.m_writeQueueCV.wait_until(lk,now + 100ms,[&threadArgs](){return threadArgs.m_queueToWrite.Size() > 0;});
  if (threadArgs.m_bExitWriteThread == true && threadArgs.m_queueToWrite.Size() == 0)
  {
      // if both parser and resder finish writer to/ reading from the queue
      // but writer entered function after threadArgs.m_bExitWriteThread
      // was modified by parser, queue might be empty which might
      return;
  }
  cdrDetails = threadArgs.m_queueToWrite.Remove();
}

void cdrWriter::Write(ThreadArgs &threadArgs)
{

   int i = 0;
   while(true)
   {
     CdrDetails l_cdrDetails;
      GetCdrDetailsFromQueue(threadArgs,l_cdrDetails);
      if (threadArgs.m_bExitWriteThread && threadArgs.m_queueToWrite.Size() == 0)
      {
         cout<<" break Write"<<endl;
         break;
      }
      cout<<"Write l_cdrDetails "<<l_cdrDetails.m_imsi<<endl;
      ++i;
   }

  cout<<"Write"<<endl;
}
