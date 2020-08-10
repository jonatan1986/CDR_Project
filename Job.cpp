#include<iostream>
#include"Job.h"
using namespace std;


Job::Job(const std::string& filename,int startLine,int endLine)
:m_filename(filename),m_startline(startLine),m_endline(endLine)
{
  m_writer = make_unique<cdrWriter>();
  m_parser = make_unique<cdrParser>();
  m_reader = make_unique<cdrReader>(filename,startLine,endLine);
}

void ReadFunc(std::unique_ptr<eReader> &reader,SafeQueue<std::string>& queueToParse)
{
  reader->Read(ref(queueToParse));
}

void ParseFunc(std::unique_ptr<eParser> &parser,SafeQueue<std::string>& queueToParse
,SafeQueue<std::string>& queueToOutput)
{
  parser->Parse(ref(queueToParse),ref(queueToOutput));
}

void WriteFunc(std::unique_ptr<eWriter> &writer,SafeQueue<std::string>& queueToOutput)
{
  writer->Write(ref(queueToOutput));
}

void Job::Run()
{
  m_threadPool.AddThread(&ReadFunc,ref(m_reader),ref(m_queueToParse));
  m_threadPool.AddThread(&ParseFunc,ref(m_parser),ref(m_queueToParse),ref(m_queueToOutput));
  m_threadPool.AddThread(&WriteFunc,ref(m_writer),ref(m_queueToOutput));
}
