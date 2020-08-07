/*
 * reader.h
 *
 *  Created on: Aug 6, 2020
 *      Author: yonathan
 */

#ifndef EREADER_H_
#define EREADER_H_

#include <queue>
#include <string>

class eReader
{
public:
  virtual void Read() = 0;
};

class cdrReader: public eReader
{
public:
  virtual void Read()override;
private:
  std::queue<std::string> queueToParse;
};



#endif /* EREADER_H_ */
