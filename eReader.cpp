#include "eReader.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


void cdrReader::Read(SafeQueue<std::string>& queueToParse)
{
    ifstream inputfile(m_filename);
    string line;
    for(int i = 0 ; i < m_endLine ; ++i)
    {
      getline(inputfile,line);
      queueToParse.Insert(line);
    }
    cout<<"line "<<line<<endl;
}
