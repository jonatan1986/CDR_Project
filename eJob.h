
#ifndef EJOB_H_
#define EJOB_H_

#include <memory>
#include <queue>
#include <string>

#include"eWriter.h"
#include"eParser.h"
#include"eReader.h"

class eJob
{
public:
  virtual void Run() = 0;
  virtual ~eJob(){}
private:

};

class threadPoolJob : public eJob
{
  public:
    threadPoolJob(const std::string& filename,int startline,int endline);
    void Run()override;
      ~threadPoolJob(){}
  private:
    const std::string m_filename;
    const int m_startline;
    const int m_endline;
    std::queue<std::string> queueToParse;
    std::queue<std::string> queueToOutput;
    std::shared_ptr<eWriter> writer;//(queueToOutput);
    std::shared_ptr<eParser> parser;
    std::shared_ptr<eReader> reader;
};



#endif /* EJOB_H_ */
