/*
 * reader.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef EREADER_H_
#define EREADER_H_

#include <string>
#include <atomic>
#include <condition_variable>
#include"ThreadArgs.h"

class eReader
{
public:
  virtual void Read(ThreadArgs &threadArgs) const = 0;
  virtual ~eReader(){}
};

class cdrReader: public eReader
{
public:
  cdrReader(const std::string& filename,int nStartLine,int nEndLine):
  m_filename(filename),m_nStartLine(nStartLine),m_nEndLine(nEndLine){}
  void Read(ThreadArgs &threadArgs) const override;
private:
  const std::string m_filename;
  const int m_nStartLine;
  const int m_nEndLine;

};



#endif /* EREADER_H_ */
