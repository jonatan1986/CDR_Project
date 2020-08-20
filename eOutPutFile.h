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

struct FileDetails
{
  FileDetails(std::string &sFileName, int nFileIndex = 0):m_sFileName(sFileName){}
  FileDetails(){}
  std::string m_sFileName;
  int m_nFileIndex = 0;
};

class eOutPutFile
{
public:
  virtual void WriteToFile(eCdrDetails& cdrDetails) = 0;
protected:
  std::unordered_map<std::string,FileDetails> fileMap;
};

class SingleFile: public eOutPutFile
{
public:
  SingleFile():m_fileName("SingleFile.txt")
  {
    FileDetails l_FileDetails(m_fileName);
    fileMap[m_fileName] = std::move(l_FileDetails);
  }
  void WriteToFile(eCdrDetails& cdrDetails)override
  {
    std::lock_guard<std::mutex>lk(m_mutex);
    m_file.open(m_fileName,std::ios::app | std::ios::out);
    m_file<<"IMSI="<<cdrDetails.m_imsi
    <<" Date="<<cdrDetails.m_date<<" Downlink="<<cdrDetails.m_downlink
    <<" Uplink="<<cdrDetails.m_uplink<<std::endl;
    m_file.close();
  }
private:
  std::string m_fileName;
  std::mutex m_mutex;
  std::ofstream m_file;

};

class MultipleFile : public eOutPutFile
{
public:
  void WriteToFile(eCdrDetails& cdrDetails)override
  {
    std::string l_sImsi = cdrDetails.m_imsi;
    if (fileMap.find(l_sImsi) == fileMap.end())
    {
      std::string sFileName = std::to_string(m_index) + ".txt";
      FileDetails l_FileDetails(sFileName,m_index-1);
      ++m_index;
      fileMap[l_sImsi] = std::move(l_FileDetails);
    }
    FileDetails l_FileDetails = fileMap[l_sImsi];
    int l_nIndex = l_FileDetails.m_nFileIndex;
    std::string l_sFileName = l_FileDetails.m_sFileName;
    std::lock_guard<std::mutex>lk(m_mutex[l_nIndex]);
    m_file[l_nIndex].open(l_sFileName,std::ios::app | std::ios::out);
    m_file[l_nIndex]<<"IMSI="<<cdrDetails.m_imsi
    <<" Date="<<cdrDetails.m_date<<" Downlink="<<cdrDetails.m_downlink
    <<" Uplink="<<cdrDetails.m_uplink<<std::endl;
    m_file[l_nIndex].close();
  }
private:
  int m_index = 1;
  std::mutex m_mutex[20];
  std::ofstream m_file[20];

};

#endif /* EOUTPUTFILE_H_ */
