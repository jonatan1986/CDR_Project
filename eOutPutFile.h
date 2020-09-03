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
#include <memory>
// #include <stdio.h>
// #include <unistd.h>
#include "eCdrDetails.h"
#include "Config.h"
#include "Singleton.h"

/*
FileDetails - simple struct which holds the name of the file and the index
*/
struct FileDetails
{
  FileDetails(std::string &sFileName, int nFileIndex = 0):m_sFileName(sFileName){}
  FileDetails(){}
  std::string m_sFileName;
  int m_nFileIndex = 0;
};
/*
class eOutPutFile is polymorphic. it has 2 derived classes. the aim of this
class to print literally the output result to the output file.
this is done thread safe and this class is SingleTone so all threads
print to the same file - they share the mutex among them
*/
class eOutPutFile
{
public:
  eOutPutFile();
  virtual void WriteToFile(eCdrDetails& cdrDetails) = 0;
  virtual ~eOutPutFile(){}
protected:
  // virtual ~eOutPutFile(){} // output file cannot be  deleted since it is a SingleTone
  std::unordered_map<std::string,FileDetails> m_fileMap;
  std::string m_sRelPath = "output";
};

/*
writes to a signle file - all imsis are in the same file
*/
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
  void WriteToFile(eCdrDetails& i_cdrDetails)override;
private:
  std::string m_sFileName;
  std::mutex m_mutex;
  std::ofstream m_file;

};
/*
writes to multiple files - each file is mapped to IMSI
*/
class MultipleFile : public eOutPutFile
{
public:
  MultipleFile();
  void Init();
  void WriteToFile(eCdrDetails& i_cdrDetails)override;
private:
  int m_nIndex = 1;
  std::unique_ptr<std::mutex[]> m_mutex;
  std::unique_ptr<std::ofstream[]> m_file;

};

#endif /* EOUTPUTFILE_H_ */
