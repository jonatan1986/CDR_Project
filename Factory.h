


#ifndef FACTORY_H
#define FACTORY_H

#include <type_traits>

#include"eWriter.h"
#include"eParser.h"
#include"eReader.h"
#include"eOutPutFile.h"




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
  std::unique_ptr<eOutPutFile> Create()
  {
    return std::make_unique<SingleFile>();
  }
};
// template<class T>
// class Factory
// {
// public:
//     template<class T>
//     AbstractFactory* CreateFactory()
//     {
//       if (std::is_same<T, WriterFactory>::value)
//       {
//         std::cout<<" write factory"<<std::endl;
//         // WriterFactory writerFactory;
//         return new WriterFactory;
//       }
//       throw "invalid class type";
//     }
// };

#endif // FACTORY_H
