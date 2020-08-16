
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include<iostream>
#include <fstream>


class FileGenerator
{
public:
  FileGenerator(std::string name):m_name(name)
  {
    m_file.open(name,std::ios::app | std::ios::out);
    InitImsi();
  }
  void GenerateFile();
  std::string GenerateDate();
  int  GenerateImsi();
  std::string GenerateUpLink();
  std::string GenerateDownLink();
  void  InitImsi();
  ~FileGenerator()
  {
    if (m_file.is_open())
    {
      m_file.close();
    }
  }
  const int GetFileSize()const;
private:
  std::ofstream m_file;
  std::string m_name;
  std::vector<int> imsiVec;

};

#endif // FILE_MANAGER_H
