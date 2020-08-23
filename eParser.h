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

/*
this class pull raw strings from a queue, parses the strings
and inserts them to another queue as a struct(eCdrDetails.h)
*/

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
  void ParseLine(std::string &i_sLine,eCdrDetails& o_cdrDetails)const;
  void GetLineFromQueue(std::string &o_sLine,ThreadArgs &threadArgs)const;
  void InsertCdrDetailsToQueue(eCdrDetails& i_cdrDetails,ThreadArgs &threadArgs)const;
private:
};



#endif /* EsPARSER_H_ */
