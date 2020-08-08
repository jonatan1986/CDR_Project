#include<iostream>
#include"Job.h"
using namespace std;


Job::Job(const std::string& filename,int startLine,int endLine)
:m_filename(filename),m_startline(startLine),m_endline(endLine)
{
  writer = make_unique<cdrWriter>(m_queueToOutput);
  parser = make_unique<cdrParser>(m_queueToParse,m_queueToOutput);
  reader = make_unique<cdrReader>(m_queueToParse,filename,startLine,endLine);
}

void Job::Run()
{
  // cout<<"Run"<<&writer <<" "<<endl;
}
