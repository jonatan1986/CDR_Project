#include <iostream>
#include "eParser.h"
#include "CdrDetails.h"


using namespace std;


void cdrParser::Parse(SafeQueue<string>& queueToParse
,SafeQueue<string>& queueToOutput, ThreadArgs &threadArgs)
{
  int i =  0;
  cout<<" parser "<<&threadArgs.m_parseQueueCV<<endl;
  while(true)
  {
      string line = " ";
      {
           unique_lock<mutex> lk(threadArgs.m_parseQueueMutex);
           threadArgs.m_parseQueueCV.wait(lk,[&queueToParse](){return queueToParse. Size() > 0;});
           line = queueToParse.Remove();
      }
      cout<<i<<" parser "<<line<<endl;
      ++i;

      if (threadArgs.m_bExitParseThread && queueToParse. Size() == 0)
      {
        break;
      }
  }
  cout<<" finished parsing"<<endl;
}
