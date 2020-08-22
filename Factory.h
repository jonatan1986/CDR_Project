


#ifndef FACTORY_H
#define FACTORY_H

#include <type_traits>

#include"eWriter.h"
#include"eParser.h"
#include"eReader.h"
#include"eOutPutFile.h"
#include"SingleTone.h"
#include "Config.h"


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

class ParserFactory
{
public:
  std::unique_ptr<eParser> Create()
  {
    return std::make_unique<cdrParser>();
  }
};

class WriterFactory
{
public:
  std::unique_ptr<eWriter> Create()
  {
    return std::make_unique<cdrWriter>();
  }
};


class OutPutFileFactory
{
public:
  OutPutFileFactory()
  {
    Config *config = SingleTone<Config>::GetIntstance();
    if ( config->GetOutputType() == "MultipleOutput")
    {
        m_eOutPutFile = SingleTone<MultipleFile>::GetIntstance();
    }
    else
    {
        m_eOutPutFile = SingleTone<SingleFile>::GetIntstance();
    }

  }
  eOutPutFile* Create()
  {
      return m_eOutPutFile;
  }
private:
  eOutPutFile* m_eOutPutFile = nullptr;
};

// eOutputType OutPutFileFactory::m_eOutputType;

#endif // FACTORY_H
