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

/*
the class eWriter writes cdr details to an output file/s
*/
class eWriter
{
public:
  virtual void Write(ThreadArgs &threadArgs)const = 0;
  virtual ~eWriter(){}
};
/*
cdrWriter:
Function :void Write(ThreadArgs &threadArgs)const
brief: writes the cdr details in file

Function : void GetCdrDetailsFromQueue(ThreadArgs &threadArgs,CdrDetails &o_cdrDetails)const
brief :the function reads data from queue
@ CdrDetails &o_cdrDetails - struct of details written removed from the queue

void WriteToFile(CdrDetails &cdrDetails)const;
brief : the function prints data to the file
@ CdrDetails &o_cdrDetails - struct of details printed to the file
*/


class cdrWriter: public eWriter
{
public:
  cdrWriter(); //ctor
  void Write(ThreadArgs &threadArgs)const override;
  void GetCdrDetailsFromQueue(ThreadArgs &threadArgs,eCdrDetails &o_cdrDetails)const ;
  void WriteToFile(eCdrDetails &i_cdrDetails)const;
private:
  eOutPutFile* m_outPutFile;
};





#endif /* WRITER_H_ */
