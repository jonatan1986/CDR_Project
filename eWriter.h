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
#include "eOutPutFile.h"

class eWriter
{
public:
  virtual void Write(ThreadArgs &threadArgs)const = 0;
};

class cdrWriter: public eWriter
{
public:
  cdrWriter();
  void Write(ThreadArgs &threadArgs)const override;
  void GetCdrDetailsFromQueue(ThreadArgs &threadArgs,CdrDetails &cdrDetails)const ;
  void WriteToFile(CdrDetails &cdrDetails)const;
private:
  eOutPutFile* m_outPutFile;
};





#endif /* WRITER_H_ */
