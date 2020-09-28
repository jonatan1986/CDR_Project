#include<iostream>
#include"Task.h"
using namespace std;


Task::Task(const std::string& sFilename,int nStartline,int nEndLine, int threadNum)
:m_sFilename(sFilename),m_threanNum(threadNum)
{
  ReaderFactory readerFactory(sFilename,nStartline,nEndLine);
  ParserFactory parserFactory;
  WriterFactory writerFactory;
  m_reader = readerFactory.Create();
  m_parser = parserFactory.Create();
  m_writer = writerFactory.Create();
}

void ReadFunc(std::unique_ptr<eReader> &reader,
int i_threadNum)
{
  reader->Read(i_threadNum);
}

void ParseFunc(std::unique_ptr<eParser> &parser, int i_threadNum)
{
  parser->Parse(i_threadNum);
}

void WriteFunc(std::unique_ptr<eWriter> &writer, int i_threadNum)
{
  writer->Write(i_threadNum);
}

void Task::Run()
{
  ThreadManager l_threadManager;
  l_threadManager.AddThread(&ReadFunc,ref(m_reader),m_threanNum);
  l_threadManager.AddThread(&ParseFunc,ref(m_parser),m_threanNum);
  l_threadManager.AddThread(&WriteFunc,ref(m_writer),m_threanNum);
}
