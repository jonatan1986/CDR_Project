#include <iostream>
#include "eParser.h"



using namespace std;

void cdrParser::ParseLine(std::string &line,CdrDetails& o_cdrDetails)const
{
    // consider to make library for this function
    size_t startPos = 0,currPos = 0;
    vector<string> cdrDetailsVec;
    while((currPos = line.find_first_of("|",startPos)) != std::string::npos)
    {
      string str = line.substr(startPos,currPos-startPos);
      startPos = currPos + 1;
      cdrDetailsVec.push_back(std::move(str));
    }
    string str = line.substr(startPos,currPos-startPos);
    cdrDetailsVec.push_back(std::move(str));

    o_cdrDetails.m_sImsi  = cdrDetailsVec[0];
    o_cdrDetails.m_sDate  = cdrDetailsVec[1];
    o_cdrDetails.m_sDownlink = cdrDetailsVec[2];
    o_cdrDetails.m_sUplink = cdrDetailsVec[3];
    o_cdrDetails.m_sDuration = cdrDetailsVec[4];
}

void cdrParser::GetLineFromQueue(std::string &o_sLine,ThreadArgs &threadArgs)const
{
  unique_lock<mutex> lk(threadArgs.m_parseQueueMutex);
  auto now = std::chrono::system_clock::now();
  threadArgs.m_parseQueueCV.wait_until(lk,now + 100ms,[&threadArgs](){return threadArgs.m_queueToParse.Size() > 0;});
  if (threadArgs.m_bExitParseThread == true && threadArgs.m_queueToParse.Size() == 0)
  {
     return;
  }
  o_sLine = threadArgs.m_queueToParse.Remove();
}

void cdrParser::InsertCdrDetailsToQueue(CdrDetails& cdrDetails,ThreadArgs &threadArgs)const
{
    threadArgs.m_queueToWrite.Insert(cdrDetails);
    threadArgs.m_writeQueueCV.notify_one();
}

void cdrParser::Parse(ThreadArgs &threadArgs)const
{
  int i =  0;
  while(true)
  {
      string l_sLine = " ";
      {
        GetLineFromQueue(l_sLine,threadArgs);
        // cout<<" Parse "<<l_sLine<<endl;
        CdrDetails l_cdrDetails;
        ParseLine(l_sLine,l_cdrDetails);
        InsertCdrDetailsToQueue(l_cdrDetails,threadArgs);
      }
      ++i;

      if (threadArgs.m_bExitParseThread && threadArgs.m_queueToParse.Size() == 0)
      {
          break;
      }
  }
  cout<<" parserr finished "<<endl;
  threadArgs.m_bExitWriteThread = true;
  threadArgs.m_writeQueueCV.notify_one();
}
