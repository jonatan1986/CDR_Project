
#include<iostream>
#include <random>
#include <ctime>


#include "FileGenerator.h"
#include "Config.h"
#include "SingleTone.h"

using namespace std;

void  FileGenerator::InitImsi()
{
  size_t i = 0;
  Config *l_config = SingleTone<Config>::GetIntstance();
  string l_sAmountOfSubs = l_config->GetAmountOfSubscribers();
  m_nAmountOfSubscribers = l_sAmountOfSubs.length() > 0 ?
  stoi(l_sAmountOfSubs) : AMOUNT_OF_SUBS;
  // cout<<"l_sAmountOfSubs "<<l_sAmountOfSubs<<endl;
  while(i < m_nAmountOfSubscribers)
  {
    imsiVec.push_back(GenerateImsi());
    ++i;
  }
  cout<<i<<endl;
}

int  FileGenerator::GenerateImsi()const
{
   std::random_device rd;  //Will be used to obtain a seed for the random number engine
   std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
   std::uniform_int_distribution<> distrib(123456789, 999999999);
   int num = distrib(gen);
   return num;
}

void FileGenerator::GenerateFile()
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, m_nAmountOfSubscribers-1);
  Config *l_config = SingleTone<Config>::GetIntstance();
  string l_sAmountOfLines = l_config->GetAmountOfLines();
  int l_nAmountOfLines = l_config->GetAmountOfLines().length() > 0 ?
  stoi(l_sAmountOfLines) : AMOUNT_OF_LINES;
  for(int i = 0 ; i < l_nAmountOfLines ; ++i)
  {
    if (m_file.is_open())
    {
      m_file<<imsiVec[distrib(gen)]<<"|"<<GenerateDate()<<
      "|"<<GenerateDownLink()<<"|"<<GenerateUpLink()
      <<"|"<<GenerateCallsDuration()<<endl;
    }
    else
    {
      string str = " file for cdr's  datafile.txt is not open";
      throw str;
    }
  }

  m_file.close();
}


string FileGenerator::GenerateUpLink()const
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(200, 900);
  string str  = to_string(distrib(gen));
  return str;
}

string FileGenerator::GenerateDownLink()const
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(200, 900);
  string str  = to_string(distrib(gen));
  return str;
}

string FileGenerator::GenerateDate()const
{
  string str = "";
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(1, 31);
  string year = "2020";
  string month  = to_string(distrib(gen)%12 + 1);
  string day = "";
  int dayInt = 0;
  switch (stoi(month))
  {
    case 1:{
      dayInt = distrib(gen) % 31 + 1;
    }break;
    case 2:
    dayInt = distrib(gen) % 28 + 1;
    break;
    case 3:
      dayInt = distrib(gen) % 31 + 1;
    break;
    case 4:
    dayInt = distrib(gen) % 30 + 1;
    break;
    case 5:
    dayInt = distrib(gen) % 31 + 1;
    break;
    case 6:
    dayInt = distrib(gen) % 30 + 1;
    break;
    case 7:
    dayInt = distrib(gen) % 31 + 1;
    break;
    case 8:
    dayInt = distrib(gen) % 31 + 1;
    break;
    case 9:
    dayInt = distrib(gen) % 31 + 1;
    break;
    case 10:
    dayInt = distrib(gen) % 31 + 1;
    break;
    case 11:
    dayInt = distrib(gen) % 30 + 1;
    break;
    case 12:
    dayInt = distrib(gen) % 31 + 1;
    break;
  }
  day = to_string(dayInt);
  str = day + "/" + month + "/" +year;
  return str;
}


string  FileGenerator::GenerateCallsDuration()const
{
  string str = " ";
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(1, 60);
  string l_sHour = '0' + to_string(distrib(gen)%6);
  int l_nMin = distrib(gen)%60;
  string l_sMinute = l_nMin < 10 ? '0' + to_string(l_nMin) : to_string(l_nMin);
  string l_sSecond = to_string(distrib(gen)%60);
  str = l_sHour + ":" + l_sMinute + ":" + l_sSecond;
  return str;
}
