
#include <iostream>
#include <fstream>
#include "Config.h"
using namespace std;


void Config::Init()
{
  ifstream l_file;
  l_file.open("cdrconfig.txt");
  string l_sLine = "";
  size_t l_nPos = 0;
  while(getline(l_file,l_sLine))
  {
    l_nPos = l_sLine.find_first_of(' ',0);
    if (l_nPos == string::npos)
    {
      string l_sError = "cdrconfig.txt is invalid";
      throw  l_sError;
    }
    string key = l_sLine.substr(0,l_nPos);
    string value = l_sLine.substr(l_nPos + 1,l_sLine.length() - l_nPos);
    m_configMap[key] = value;
  }
  l_file.close();
}

Config::Config()
{
    Init();
}
