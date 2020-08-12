/*
 * parser.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef EPARSER_H_
#define EPARSER_H_

#include <string>
#include <atomic>
#include <condition_variable>
#include "SafeQueue.h"
#include "ThreadArgs.h"

class eParser
{
public:
  virtual void Parse(ThreadArgs &threadArgs) = 0;
};

class cdrParser: public eParser
{
public:

  cdrParser()
  {}
  virtual void Parse(ThreadArgs &threadArgs)override;
private:
};



#endif /* EsPARSER_H_ */
