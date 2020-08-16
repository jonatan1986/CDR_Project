/*
 * eOutPutFile.h
 *
 *  Created on: Aug 16, 2020
 *      Author: yonathan
 */

#ifndef EOUTPUTFILE_H_
#define EOUTPUTFILE_H_
#include <mutex>
#include <unordered_map>
#include <fstream>

struct Ofstream
{
  void Init(std::string &fileName)
  {
    m_fileName = fileName;
  }
  std::string m_fileName;
  std::ofstream m_file;
};

class eOutPutFile
{
public:
  virtual void WriteToFile(eCdrDetails& cdrDetails) = 0;
protected:
  std::unordered_map<std::string,Ofstream> fileMap;
};

class SingleFile: public eOutPutFile
{
public:
  SingleFile():m_fileName("SingleFile.txt")
  {
    Ofstream l_Ofstream;
    fileMap[m_fileName] = std::move(l_Ofstream);
  }
  void WriteToFile(eCdrDetails& cdrDetails)override
  {
    std::lock_guard<std::mutex>lk(m_mutex);
    fileMap[m_fileName].m_file.open(m_fileName,std::ios::app | std::ios::out);
    fileMap[m_fileName].m_file<<"IMSI="<<cdrDetails.m_imsi
    <<" Date="<<cdrDetails.m_date<<" Downlink="<<cdrDetails.m_downlink
    <<" Uplink="<<cdrDetails.m_uplink<<std::endl;
    fileMap[m_fileName].m_file.close();
  }
private:
  std::string m_fileName;
  std::mutex m_mutex;

};

class MultipleFile : public eOutPutFile
{
public:
  void WriteToFile(eCdrDetails& cdrDetails)override
  {}
private:
  int m_counter = 0;

};

#endif /* EOUTPUTFILE_H_ */
