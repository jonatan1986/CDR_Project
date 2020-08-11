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
#include "SafeQueue.h"
#include"ThreadArgs.h"

class eReader
{
public:
  virtual void Read(SafeQueue<std::string>& queueToParse, ThreadArgs &threadArgs) = 0;
};

class cdrReader: public eReader
{
public:
  cdrReader(const std::string& filename,
  int startLine,int endLine):
  m_filename(filename),m_startLine(startLine),m_endLine(endLine){}
  void Read(SafeQueue<std::string>& queueToParse,ThreadArgs &threadArgs)override;
private:
  const std::string m_filename;
  const int m_startLine;
  const int m_endLine;

};



#endif /* EREADER_H_ */
