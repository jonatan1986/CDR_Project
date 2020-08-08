/*
 * parser.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef EPARSER_H_
#define EPARSER_H_

#include <string>
#include "SafeQueue.h"

class eParser
{
public:
  virtual void Parse() = 0;
};

class cdrParser: public eParser
{
public:

  cdrParser(  SafeQueue<std::string> & queueToParse, SafeQueue<std::string>& queueToOutput)
  :m_queueToParse(queueToParse),m_queueToOutput(queueToOutput)
  {}
  virtual void Parse()override;
private:
  SafeQueue<std::string> m_queueToParse;
  SafeQueue<std::string> m_queueToOutput;
};



#endif /* EsPARSER_H_ */
