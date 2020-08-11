#include "eReader.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


void cdrReader::Read(SafeQueue<std::string>& queueToParse, ThreadArgs &threadArgs)
{
    ifstream inputfile(m_filename);
    string line;
    for(int i = m_startLine ; i <= m_endLine  ; ++i)
    {
      getline(inputfile,line);
      cout<<i<<" reader  "<<line<<endl;
      queueToParse.Insert(line);
      threadArgs.m_parseQueueCV.notify_one();
    }
    threadArgs.m_bExitParseThread = true;
    cout<<"Read Finish "<<endl;
}
