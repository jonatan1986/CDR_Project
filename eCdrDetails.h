/*
 * eCdrDetails.h
 *
 *  Created on: Aug 16, 2020
 *      Author: yonathan
 */

#ifndef ECDRDETAILS_H_
#define ECDRDETAILS_H_

struct eCdrDetails
{
  std::string m_sImsi;
  std::string m_sDate;
  std::string m_sDownlink;
  std::string m_sUplink;
  std::string m_sDuration;
};

struct CdrDetails :  eCdrDetails
{

};




#endif /* ECDRDETAILS_H_ */
