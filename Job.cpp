#include<iostream>
#include"Job.h"
using namespace std;


Job::Job(const std::string& filename,int startLine,int endLine)
:m_filename(filename),m_startline(startLine),m_endline(endLine)
{
  m_writer = make_unique<cdrWriter>(m_queueToOutput);
  m_parser = make_unique<cdrParser>(m_queueToParse,m_queueToOutput);
  m_reader = make_unique<cdrReader>(m_queueToParse,filename,startLine,endLine);
}

void ReadFunc(std::unique_ptr<eReader> &reader)
{
  reader->Read();
}

void ParseFunc(std::unique_ptr<eParser> &parser)
{
  parser->Parse();
}

void WriteFunc(std::unique_ptr<eWriter> &writer)
{
  writer->Write();
}

void Job::Run()
{
  m_threadPool.AddThread(&ReadFunc,ref(m_reader));
  m_threadPool.AddThread(&ParseFunc,ref(m_parser));
  m_threadPool.AddThread(&WriteFunc,ref(m_writer));
}
