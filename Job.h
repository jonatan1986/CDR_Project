
#ifndef EJOB_H_
#define EJOB_H_

#include <memory>
#include <string>
#include"eWriter.h"
#include"eParser.h"
#include"eReader.h"
#include "SafeQueue.h"
#include "ThreadPool.h"

// class eJob
// {
// public:
//   virtual void Run() = 0;
//   virtual ~eJob(){}
// private:
//
// };



class Job
{
  public:
    Job(const std::string& filename,int startline,int endline);
    void Run();
  private:
    const std::string m_filename;
    const int m_startline;
    const int m_endline;
    ThreadArgs m_threadArgs;
    std::unique_ptr<eWriter> m_writer;
    std::unique_ptr<eParser> m_parser;
    std::unique_ptr<eReader> m_reader;
    ThreadPool m_threadPool;

};



#endif /* EJOB_H_ */
