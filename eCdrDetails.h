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
  std::string m_imsi;
  std::string m_date;
  std::string m_downlink;
  std::string m_uplink;
};

struct CdrDetails :  eCdrDetails
{

};




#endif /* ECDRDETAILS_H_ */
