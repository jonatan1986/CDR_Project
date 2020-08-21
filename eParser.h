/*
 * parser.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef EPARSER_H_
#define EPARSER_H_

#include <string>
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
  void Parse(ThreadArgs &threadArgs);
  void ParseLine(std::string &line,CdrDetails& cdrDetails);
  void GetLineFromQueue(std::string &line,ThreadArgs &threadArgs);
  void InsertCdrDetailsToQueue(CdrDetails& cdrDetails,ThreadArgs &threadArgs);
private:
};



#endif /* EsPARSER_H_ */
