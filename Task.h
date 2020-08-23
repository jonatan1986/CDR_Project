
#ifndef ETASK_H_
#define ETASK_H_

#include <memory>
#include <string>
#include "Factory.h"
#include "SafeQueue.h"
#include "ThreadPool.h"


class Task
{
  public:
    Task(const std::string& filename,int startline,int endline);
    void Run();
  private:
    const std::string m_filename;
    ThreadArgs m_threadArgs;
    std::unique_ptr<eWriter> m_writer;
    std::unique_ptr<eParser> m_parser;
    std::unique_ptr<eReader> m_reader;
};



#endif /* ETASK_H_ */
