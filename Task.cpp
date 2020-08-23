#include<iostream>
#include <atomic>
#include <condition_variable>
#include"Task.h"
using namespace std;


Task::Task(const std::string& sFilename,int nStartline,int nEndLine)
:m_sFilename(sFilename)
{
  ReaderFactory readerFactory(sFilename,nStartline,nEndLine);
  ParserFactory parserFactory;
  WriterFactory writerFactory;
  m_reader = readerFactory.Create();
  m_parser = parserFactory.Create();
  m_writer = writerFactory.Create();
}

void ReadFunc(std::unique_ptr<eReader> &reader,
ThreadArgs &threadArgs)
{
  reader->Read(threadArgs);
}

void ParseFunc(std::unique_ptr<eParser> &parser,ThreadArgs &threadArgs)
{
  parser->Parse(threadArgs);
}

void WriteFunc(std::unique_ptr<eWriter> &writer,ThreadArgs &threadArgs)
{
  writer->Write(threadArgs);
}

void Task::Run()
{
  ThreadPool l_threadPool;
  l_threadPool.AddThread(&ReadFunc,ref(m_reader),ref(m_threadArgs));
  l_threadPool.AddThread(&ParseFunc,ref(m_parser),ref(m_threadArgs));
  l_threadPool.AddThread(&WriteFunc,ref(m_writer),ref(m_threadArgs));
}
