#include <iostream>
#include "eWriter.h"
#include "Factory.h"

using namespace std;




cdrWriter::cdrWriter()
{
    OutPutFileFactory outPutFileFactory;
    eOutPutFile* m_outPutFile = outPutFileFactory.Create();
    cout<<m_outPutFile<<endl;
}

void cdrWriter::GetCdrDetailsFromQueue(ThreadArgs &threadArgs,
CdrDetails &cdrDetails)
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
  cdrDetails = threadArgs.m_queueToWrite.Remove();
}


void cdrWriter::WriteToFile(CdrDetails &cdrDetails)
{

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
      cout<<i<<"Write l_cdrDetails "<<l_cdrDetails.m_imsi<<endl;
      ++i;
   }

  cout<<"Write"<<endl;
}
