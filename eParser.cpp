#include <iostream>
#include "eParser.h"
#include "CdrDetails.h"


using namespace std;


void cdrParser::Parse(ThreadArgs &threadArgs)
{
  int i =  0;
  cout<<" parser "<<&threadArgs.m_parseQueueCV<<endl;
  while(true)
  {
      string line = " ";
      {
           unique_lock<mutex> lk(threadArgs.m_parseQueueMutex);
           threadArgs.m_parseQueueCV.wait(lk,[&threadArgs](){return threadArgs.m_queueToParse.Size() > 0;});
           line = threadArgs.m_queueToParse.Remove();
      }
      cout<<i<<" parser "<<line<<endl;
      ++i;

      if (threadArgs.m_bExitParseThread && threadArgs.m_queueToParse.Size() == 0)
      {
        break;
      }
  }
  cout<<" finished parsing"<<endl;
}
