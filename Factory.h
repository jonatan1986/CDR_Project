


#ifndef FACTORY_H
#define FACTORY_H

#include <type_traits>

#include"eWriter.h"
#include"eParser.h"
#include"eReader.h"
#include"eOutPutFile.h"
#include"Singleton.h"
#include "Config.h"
/*
creates unique_ptr for eReader
*/
class ReaderFactory
{
public:
  ReaderFactory(const std::string filename,const int startLine,
  const int endLine):m_filename(filename),m_startLine(startLine),m_endLine(endLine){}
  std::unique_ptr<eReader> Create()
  {
    return std::make_unique<cdrReader>(m_filename, m_startLine, m_endLine);
  }
private:
  const std::string m_filename;
  const int m_startLine;
  const int m_endLine;
};

/*
creates unique_ptr for eParser
*/
class ParserFactory
{
public:
  std::unique_ptr<eParser> Create()
  {
    return std::make_unique<cdrParser>();
  }
};

/*
creates unique_ptr for eWriter
*/
class WriterFactory
{
public:
  std::unique_ptr<eWriter> Create()
  {
    return std::make_unique<cdrWriter>();
  }
};

/*
  this class is a bit complex : class eOutPutFile(member of OutPutFileFactory) is
  polymorphic and can be written to singlefile or multiple files(if multiple - each file
  is classified by the IMSI(internation mobile subscriber identity))
  so the OutPutFileFactory creates the  eOutPutFile* according to Config
  class. the consturctor decides the type of "eOutPutFile" according
  to the configuration. the function create returns the  relevant type
  of eOutPutFile. Since more then on thread has this class(OutPutFileFactory),
  this class is wrapped by a SingleTone. constructor is called only once
  and   eOutPutFile* is shared among the threads(which write to the output)
  since it contains shared data
*/
class OutPutFileFactory
{
public:
  OutPutFileFactory()
  {
    Config *l_config = Singleton<Config>::GetIntstance();
    if (l_config->GetOutputType() == "MultipleOutput")
    {
        m_eOutPutFile = Singleton<MultipleFile>::GetIntstance();
    }
    else
    {
        m_eOutPutFile = Singleton<SingleFile>::GetIntstance();
    }

  }
  eOutPutFile* Create()
  {
      return m_eOutPutFile;
  }
private:
  ~OutPutFileFactory();
  eOutPutFile* m_eOutPutFile = nullptr;
};


#endif // FACTORY_H
