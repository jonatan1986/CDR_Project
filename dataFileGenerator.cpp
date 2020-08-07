
#include <cstdlib>
#include <iostream>
// #include <thread>
#include <fstream>
#include <random>

#include"fileManager.h"
#include"threadManager.h"

using namespace std;
#define filename "datafile.txt"





int main(int argc, char const *argv[]) {
  /* code */
  fileManager filemanager(filename);
  // filemanager.GenerateFile();
  string str(filename);
  threadManager threadmanager(5,filename,filemanager.GetFileSize());
  threadmanager.CreateThreads();
  return 0;
}
