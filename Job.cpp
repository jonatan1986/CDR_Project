#include<iostream>
#include <atomic>
#include <condition_variable>
#include"Job.h"
using namespace std;


Job::Job(const std::string& filename,int startLine,int endLine)
:m_filename(filename),m_startline(startLine),m_endline(endLine)
{
  ReaderFactory readerFactory(filename,startLine,endLine);
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

void Job::Run()
{
  m_threadPool.AddThread(&ReadFunc,ref(m_reader),ref(m_threadArgs));
  m_threadPool.AddThread(&ParseFunc,ref(m_parser),ref(m_threadArgs));
  m_threadPool.AddThread(&WriteFunc,ref(m_writer),ref(m_threadArgs));
  // cout<<"finished run"<<endl;
}
