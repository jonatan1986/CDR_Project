/*
 * writer.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <queue>
#include <string>

class eWriter
{
public:
  virtual void Write() = 0;
};

class cdrWriter: public eWriter
{
public:
  cdrWriter(std::queue<std::string>& queueToOutput):
  m_queueToOutput(queueToOutput){}
  virtual void Write()override;
private:
  std::queue<std::string> m_queueToOutput;
};





#endif /* WRITER_H_ */
