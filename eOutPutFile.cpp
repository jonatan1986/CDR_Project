// #include <experimental/filesystem>
#include <iostream>
#include "eOutPutFile.h"

using namespace std;


void MultipleFile::WriteToFile(eCdrDetails& cdrDetails)
{
  string l_sImsi = cdrDetails.m_imsi;
  if (m_fileMap.find(l_sImsi) == m_fileMap.end())
  {
    string sFileName = to_string(m_index) + ".txt";
    FileDetails l_FileDetails(sFileName,m_index-1);
    ++m_index;
    m_fileMap[l_sImsi] = move(l_FileDetails);
    //delete file in case it exists
  }
  FileDetails l_FileDetails = m_fileMap[l_sImsi];
  int l_nIndex = l_FileDetails.m_nFileIndex;
  string l_sFileName = l_FileDetails.m_sFileName;
  lock_guard<mutex>lk(m_mutex[l_nIndex]);
  string l_sAbsPath = m_sRelPath + "/" + l_sFileName;
  m_file[l_nIndex].open(l_sAbsPath,ios::app | ios::out);
  m_file[l_nIndex]<<"IMSI="<<cdrDetails.m_imsi
  <<" Date="<<cdrDetails.m_date<<" Downlink="<<cdrDetails.m_downlink
  <<" Uplink="<<cdrDetails.m_uplink<<endl;
  m_file[l_nIndex].close();
}


void SingleFile::WriteToFile(eCdrDetails& cdrDetails)
{
  lock_guard<mutex>lk(m_mutex);
  string l_sAbsPath = m_sRelPath + "/" + m_fileName;
  m_file.open(l_sAbsPath,ios::app | ios::out);
  m_file<<"IMSI="<<cdrDetails.m_imsi
  <<" Date="<<cdrDetails.m_date<<" Downlink="<<cdrDetails.m_downlink
  <<" Uplink="<<cdrDetails.m_uplink<<endl;
  m_file.close();
}
