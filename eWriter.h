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
#include"ThreadArgs.h"

class eWriter
{
public:
  virtual void Write(SafeQueue<std::string>& queueToOutput) = 0;
};

class cdrWriter: public eWriter
{
public:
  cdrWriter(){}
  void Write(SafeQueue<std::string>& queueToOutput)override;
private:
};





#endif /* WRITER_H_ */
