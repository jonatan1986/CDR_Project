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


#include<stdio.h>
#include<unistd.h>

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
  virtual ~eOutPutFile(){} // output file cannot be  deleted since it is a SingleTone
  std::unordered_map<std::string,FileDetails> m_fileMap;
  std::string m_sRelPath = "output";
};

class SingleFile: public eOutPutFile
{
public:
  SingleFile():m_sFileName("SingleFile.txt")
  {
    FileDetails l_FileDetails(m_sFileName);
    m_fileMap[m_sFileName] = std::move(l_FileDetails);
    //delete file if exists
    const std::string l_sCommand = "rm -rf " + m_sRelPath + "/*.txt";
    system(l_sCommand.c_str());
  }
  void WriteToFile(eCdrDetails& cdrDetails)override;
private:
  std::string m_sFileName;
  std::mutex m_mutex;
  std::ofstream m_file;

};

class MultipleFile : public eOutPutFile
{
public:
  MultipleFile()
  {
    const std::string l_sCommand = "rm -rf " + m_sRelPath + "/*.txt";
    system(l_sCommand.c_str());
  }
  void WriteToFile(eCdrDetails& cdrDetails)override;
private:
  int m_nIndex = 1;
  std::mutex m_mutex[20];
  std::ofstream m_file[20];

};

#endif /* EOUTPUTFILE_H_ */
