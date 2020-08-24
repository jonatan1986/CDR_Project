/*
 * Task.h
 *
 *  Created on: Aug 11, 2020
 *      Author: yonathan
 */
#ifndef ETASK_H_
#define ETASK_H_

#include <memory>
#include <string>
#include "Factory.h"
#include "SafeQueue.h"
#include "ThreadPool.h"
/*
this class is the main thread which activates the eReader,eParser,and eWriter.
member function "Run()" activates the eReader,eParser,and eWriter.
*/

class Task
{
  public:
    Task(const std::string& filename, int nStartline, int nEndline, int threanNum);
    void Run();
  private:
    const std::string m_sFilename;
    const int m_threanNum;
    // ThreadArgs m_threadArgs;
    std::unique_ptr<eWriter> m_writer;
    std::unique_ptr<eParser> m_parser;
    std::unique_ptr<eReader> m_reader;
};



#endif /* ETASK_H_ */
