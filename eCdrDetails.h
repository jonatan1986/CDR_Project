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
  // eCdrDetails(){}
  // eCdrDetails(eCdrDetails& other):
  // m_imsi(other.m_imsi),
  // m_date(other.m_date),
  // m_downlink(other.m_downlink),
  // m_uplink(other.m_uplink){}
  //
  // eCdrDetails& operator = (const eCdrDetails& other)
  // {
  //   m_imsi = other.m_imsi;
  //   m_date = other.m_date;
  //   m_downlink = other.m_downlink;
  //   m_uplink = other.m_uplink;
  //   return *this;
  // }
  //
  // eCdrDetails(eCdrDetails&& other):
  // m_imsi(other.m_imsi),
  // m_date(other.m_date),
  // m_downlink(other.m_downlink),
  // m_uplink(other.m_uplink){}
  // eCdrDetails() = default;
};

struct CdrDetails :  eCdrDetails
{

};




#endif /* ECDRDETAILS_H_ */
