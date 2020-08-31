#include <iostream>
#include "eParser.h"
#include "Singleton.h"


using namespace std;

void cdrParser::ParseLine(std::string &i_sLine,eCdrDetails& o_cdrDetails)const
{
    // consider to make library for this function
    size_t startPos = 0,currPos = 0;
    vector<string> cdrDetailsVec;
    while((currPos = i_sLine.find_first_of("|",startPos)) != std::string::npos)
    {
      string str = i_sLine.substr(startPos,currPos-startPos);
      startPos = currPos + 1;
      cdrDetailsVec.push_back(std::move(str));
    }
    string str = i_sLine.substr(startPos,currPos-startPos);
    cdrDetailsVec.push_back(std::move(str));

    o_cdrDetails.m_sImsi  = cdrDetailsVec[0];
    o_cdrDetails.m_sDate  = cdrDetailsVec[1];
    o_cdrDetails.m_sDownlink = cdrDetailsVec[2];
    o_cdrDetails.m_sUplink = cdrDetailsVec[3];
    o_cdrDetails.m_sDuration = cdrDetailsVec[4];
}

void cdrParser::GetLineFromQueue(std::string &o_sLine,SharedResource &i_sharedResource)const
{
  unique_lock<mutex> lk(i_sharedResource.m_rawDataQueueMutex);
  auto now = std::chrono::system_clock::now();
  i_sharedResource.m_rawDataQueueCV.wait_until(lk,now + 100ms,[&i_sharedResource](){return i_sharedResource.m_rawDataQueue.Size() > 0;});
  if (i_sharedResource.m_bExitParseThread == true && i_sharedResource.m_rawDataQueue.Size() == 0)
  {
     return;
  }
  o_sLine = i_sharedResource.m_rawDataQueue.Remove();
}

void cdrParser::InsertCdrDetailsToQueue(eCdrDetails& i_cdrDetails,SharedResource &i_sharedResource)const
{
    i_sharedResource.m_CdrDataQueue.Insert(i_cdrDetails);
    i_sharedResource.m_CdrDataQueueCV.notify_one();
}

void cdrParser::Parse(int i_threanNum)const
{
  SharedResourceWrapper *l_sharedResourceWrapper =
  Singleton<SharedResourceWrapper>::GetIntstance();
  SharedResource& l_sharedResource =
  l_sharedResourceWrapper->GetResourceByIndex(i_threanNum);

  while(true)
  {
      string l_sLine = " ";
      {
        GetLineFromQueue(l_sLine,l_sharedResource);
        // cout<<" Parse "<<l_sLine<<endl;
        CdrDetails l_cdrDetails;
        ParseLine(l_sLine,l_cdrDetails);
        InsertCdrDetailsToQueue(l_cdrDetails,l_sharedResource);
      }

      if (l_sharedResource.m_bExitParseThread && l_sharedResource.m_rawDataQueue.Size() == 0)
      {
          break;
      }
  }
  l_sharedResource.m_bExitWriteThread = true;
  l_sharedResource.m_CdrDataQueueCV.notify_one();
}
