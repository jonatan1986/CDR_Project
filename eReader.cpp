#include "eReader.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;



void cdrReader::Read(ThreadArgs &threadArgs)const
{
    ifstream inputfile(m_filename);
    string line;

    // lambda Function - get to the line in the file from which it should read
    auto GetToLine = [](ifstream& inputfile,string& line,int startLine)
    {
      for(int i = 1 ; i < startLine  ; ++i)
      {
        getline(inputfile,line);
      }
    };
    GetToLine(inputfile, line, m_startLine); // go the line from thread should read
    for(int i = m_startLine ; i <= m_endLine  ; ++i)
    {
      getline(inputfile,line);
      threadArgs.m_queueToParse.Insert(line);
      threadArgs.m_parseQueueCV.notify_one();
    }
    threadArgs.m_bExitParseThread = true;
    cout<<"Read Finish "<<endl;
}
