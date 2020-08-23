// #include <experimental/filesystem>
#include <iostream>
#include "eOutPutFile.h"

using namespace std;


void MultipleFile::WriteToFile(eCdrDetails& i_cdrDetails)
{
  string l_sImsi = i_cdrDetails.m_sImsi;
  if (m_fileMap.find(l_sImsi) == m_fileMap.end())
  {
    string l_sFileName = to_string(m_nIndex) + ".txt";
    FileDetails l_FileDetails(l_sFileName,m_nIndex-1);
    ++m_nIndex;
    m_fileMap[l_sImsi] = move(l_FileDetails);
    //delete file in case it exists
  }
  FileDetails l_FileDetails = m_fileMap[l_sImsi];
  int l_nIndex = l_FileDetails.m_nFileIndex;
  string l_sFileName = l_FileDetails.m_sFileName;
  lock_guard<mutex>lk(m_mutex[l_nIndex]);
  string l_sAbsPath = m_sRelPath + "/" + l_sFileName;
  m_file[l_nIndex].open(l_sAbsPath,ios::app | ios::out);
  m_file[l_nIndex]<<"IMSI="<<i_cdrDetails.m_sImsi
  <<" Date="<<i_cdrDetails.m_sDate<<" Downlink="<<i_cdrDetails.m_sDownlink
  <<" Uplink="<<i_cdrDetails.m_sUplink<<" Duration="
  <<i_cdrDetails.m_sDuration<<endl;
  m_file[l_nIndex].close();
}


void SingleFile::WriteToFile(eCdrDetails& i_cdrDetails)
{
  lock_guard<mutex>lk(m_mutex);
  string l_sAbsPath = m_sRelPath + "/" + m_sFileName;
  m_file.open(l_sAbsPath,ios::app | ios::out);
  m_file<<"IMSI="<<i_cdrDetails.m_sImsi
  <<" Date="<<i_cdrDetails.m_sDate<<" Downlink="<<i_cdrDetails.m_sDownlink
  <<" Uplink="<<i_cdrDetails.m_sUplink<<" Duration="<<i_cdrDetails.m_sDuration<<endl;
  m_file.close();
}
