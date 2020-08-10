/*
 * writer.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <string>
#include "SafeQueue.h"

class eWriter
{
public:
  virtual void Write() = 0;
};

class cdrWriter: public eWriter
{
public:
  cdrWriter(SafeQueue<std::string>& queueToOutput):
  m_queueToOutput(queueToOutput){}
  // const SafeQueue<std::string> &GetQueue()const{return m_queueToOutput;}
  virtual void Write()override;
private:
  SafeQueue<std::string> m_queueToOutput;
};





#endif /* WRITER_H_ */
