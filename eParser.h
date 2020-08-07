/*
 * parser.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef EPARSER_H_
#define EPARSER_H_

#include <queue>
#include <string>

class eParser
{
public:
  virtual void Parse() = 0;
};

class cdrParser: public eParser
{
public:
  
  virtual void Parse()override;
private:
  std::queue<std::string> queueToParse;
  std::queue<std::string> queueToOutput;
};



#endif /* EsPARSER_H_ */
