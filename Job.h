
#ifndef EJOB_H_
#define EJOB_H_

#include <memory>
#include <string>

#include"eWriter.h"
#include"eParser.h"
#include"eReader.h"
#include "SafeQueue.h"

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
      ~Job(){}
  private:
    const std::string m_filename;
    const int m_startline;
    const int m_endline;
    SafeQueue<std::string> m_queueToParse;
    SafeQueue<std::string> m_queueToOutput;
    std::unique_ptr<eWriter> writer;//(queueToOutput);
    std::unique_ptr<eParser> parser;
    std::unique_ptr<eReader> reader;
};



#endif /* EJOB_H_ */
