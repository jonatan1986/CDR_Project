#include "eReader.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;



void cdrReader::Read(ThreadArgs &threadArgs)const
{
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
      threadArgs.m_queueToParse.Insert(line);
      threadArgs.m_parseQueueCV.notify_one();
    }
    threadArgs.m_bExitParseThread = true;
    cout<<"Read Finish "<<endl;
}
