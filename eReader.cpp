#include <iostream>
#include <string>
#include <fstream>
#include "eReader.h"
#include "SingleTone.h"
using namespace std;



void cdrReader::Read(int i_threanNum)const
{
    SharedResourceWrapper *l_sharedResourceWrapper =
    SingleTone<SharedResourceWrapper>::GetIntstance();
    SharedResource& l_sharedResource =
    l_sharedResourceWrapper->GetResourceByIndex(i_threanNum);

    ifstream l_inputfile(m_filename);
    string line;

    // lambda Function - get to the line in the file from which it should read
    auto GetToLine = [](ifstream& i_inputfile,string& i_sLine,int i_nStartLine)
    {
      for(int i = 1 ; i < i_nStartLine  ; ++i)
      {
        getline(i_inputfile,i_sLine);
      }
    };
    GetToLine(l_inputfile, line, m_nStartLine); // go the line from thread should read
    for(int i = m_nStartLine ; i <= m_nEndLine  ; ++i)
    {
      getline(l_inputfile,line);
      l_sharedResource.m_rawDataQueue.Insert(line);
      l_sharedResource.m_rawDataQueueCV.notify_one();
    }
    l_sharedResource.m_bExitParseThread = true;
}
