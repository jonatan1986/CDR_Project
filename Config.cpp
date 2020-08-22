
#include <iostream>
#include <fstream>
#include "Config.h"
using namespace std;


void Config::Init()
{
  ifstream l_file;
  l_file.open("cdrconfig.txt");
  string l_sLine = "";
  size_t pos = 0;
  while(getline(l_file,l_sLine))
  {
    pos = l_sLine.find_first_of(' ',0);
    if (pos == string::npos)
    {
      string s_error = "cdrconfig.txt is invalid";
      throw  s_error;
    }
    string key = l_sLine.substr(0,pos);
    string value = l_sLine.substr(pos + 1,l_sLine.length() - pos);
    // cout<<" key:"<<key <<" value:"<<value<<":end"<<endl;
    m_configMap[key] = value;
  }
  l_file.close();
}

Config::Config()
{
    std::cout<<" ctor Config"<<std::endl;
    Init();
}
