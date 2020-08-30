#include <iostream>
#include "eWriter.h"
#include "Factory.h"
#include "SingleTone.h"

#include <sys/types.h>
#include <unistd.h>
using namespace std;




cdrWriter::cdrWriter()
{
    m_outPutFile = SingleTone<OutPutFileFactory>::GetIntstance()->Create();
}

void cdrWriter::GetCdrDetailsFromQueue(SharedResource& i_sharedResource,
eCdrDetails &o_cdrDetails)const
{
  unique_lock<mutex> lk(i_sharedResource.m_cdrDataQueueMutex);
  auto now = std::chrono::system_clock::now();
  i_sharedResource.m_CdrDataQueueCV.wait_until(lk,now + 100ms,[&i_sharedResource](){return i_sharedResource.m_CdrDataQueue.Size() > 0;});
  if (i_sharedResource.m_bExitWriteThread == true && i_sharedResource.m_CdrDataQueue.Size() == 0)
  {
      // if both parser and reader finish writing to/ reading from the queue
      // but writer entered function after threadArgs.m_bExitWriteThread
      // was modified by parser, queue might be empty and program might crash
      return;
  }
  o_cdrDetails = i_sharedResource.m_CdrDataQueue.Remove();
}


void cdrWriter::WriteToFile(eCdrDetails &i_cdrDetails)const
{
    m_outPutFile->WriteToFile(i_cdrDetails);
}

void cdrWriter::Write(int i_threanNum)const
{
   SharedResourceWrapper *l_sharedResourceWrapper =
   SingleTone<SharedResourceWrapper>::GetIntstance();
   SharedResource& l_sharedResource = l_sharedResourceWrapper->GetResourceByIndex(i_threanNum);
   while(true)
   {
      CdrDetails l_cdrDetails;
      GetCdrDetailsFromQueue(l_sharedResource,l_cdrDetails);
      WriteToFile(l_cdrDetails);
      if (l_sharedResource.m_bExitWriteThread && l_sharedResource.m_CdrDataQueue.Size() == 0)
      {
         break;
      }
   }
}
