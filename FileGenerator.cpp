
#include<iostream>
#include <random>
#include <ctime>


#include"FileGenerator.h"

using namespace std;



int  FileGenerator::GenerateImsi()
{
   std::random_device rd;  //Will be used to obtain a seed for the random number engine
   std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
   std::uniform_int_distribution<> distrib(123456789, 999999999);
   int num = distrib(gen);
   std::cout <<num<< ' ';
   return num;
}

void FileGenerator::GenerateFile()
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, 19);
  for(int i = 0 ; i < 10000 ; ++i)
  {
    m_file << imsiVec[distrib(gen)] << ' ';
    m_file<<imsiVec[distrib(gen)]<<" | "<<GenerateDate()<<
    " | "<<GenerateDownLink()<<" | "<<GenerateUpLink()<<endl;
  }

  m_file.close();
}

void  FileGenerator::InitImsi()
{
  int i = 0;
  while(i < 20)
  {
    imsiVec.push_back(GenerateImsi());
    ++i;
  }
  cout<<endl<<endl;
}

string FileGenerator::GenerateUpLink()
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(200, 900);
  string str  = to_string(distrib(gen));
  return str;
}

string FileGenerator::GenerateDownLink()
{
  std::srand(std::time(nullptr)); // use current time as seed for random generator
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(200, 900);
  string str  = to_string(distrib(gen));
  return str;
}

string FileGenerator::GenerateDate()
{
  string str = " ";
  std::srand(std::time(nullptr)); // use current time as seed for random generator
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(1, 12);
  // std::cout << distrib(gen) << ' ';
  string year = "2020";
  string month  = to_string(distrib(gen));
  string day = "";
  int dayInt = 0;
  switch (stoi(month))
  {
    case 1:{
      std::uniform_int_distribution<> distrib(1, 31);
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



const int FileGenerator::GetFileSize()const
{
  std::ifstream in_file(m_name, std::ios::binary);
  in_file.seekg(0, std::ios::end);
  int file_size = in_file.tellg();
  return file_size;
}
