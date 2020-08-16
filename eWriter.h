/*
 * writer.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <string>
#include"ThreadArgs.h"
#include"eOutPutFile.h"

class eWriter
{
public:
  virtual void Write(ThreadArgs &threadArgs) = 0;
  int num  = 3;
};

class cdrWriter: public eWriter
{
public:
  cdrWriter(){}
  void Write(ThreadArgs &threadArgs)override;
  void GetCdrDetailsFromQueue(ThreadArgs &threadArgs,CdrDetails &cdrDetails);

private:
};





#endif /* WRITER_H_ */
