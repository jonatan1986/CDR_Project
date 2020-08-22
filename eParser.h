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
  virtual void Parse(ThreadArgs &threadArgs)const = 0;
  virtual ~eParser(){}
};

class cdrParser: public eParser
{
public:

  cdrParser()
  {}
  void Parse(ThreadArgs &threadArgs)const override;
  void ParseLine(std::string &line,CdrDetails& cdrDetails)const;
  void GetLineFromQueue(std::string &line,ThreadArgs &threadArgs)const;
  void InsertCdrDetailsToQueue(CdrDetails& cdrDetails,ThreadArgs &threadArgs)const;
private:
};



#endif /* EsPARSER_H_ */
