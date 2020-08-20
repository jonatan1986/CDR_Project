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
#include "eCdrDetails.h"

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
  std::unordered_map<std::string,FileDetails> m_fileMap;
  std::string m_sRelPath = "output";
};

class SingleFile: public eOutPutFile
{
public:
  SingleFile():m_fileName("SingleFile.txt")
  {
    FileDetails l_FileDetails(m_fileName);
    m_fileMap[m_fileName] = std::move(l_FileDetails);
  }
  void WriteToFile(eCdrDetails& cdrDetails)override;
private:
  std::string m_fileName;
  std::mutex m_mutex;
  std::ofstream m_file;

};

class MultipleFile : public eOutPutFile
{
public:
  void WriteToFile(eCdrDetails& cdrDetails)override;
private:
  int m_index = 1;
  std::mutex m_mutex[20];
  std::ofstream m_file[20];

};

#endif /* EOUTPUTFILE_H_ */
