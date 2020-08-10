
#include <cstdlib>
#include <iostream>
// #include <thread>
#include <fstream>
#include <random>

#include"FileGenerator.h"
#include"threadManager.h"

using namespace std;
#define filename "datafile.txt"





int main(int argc, char const *argv[]) {
  /* code */
  FileGenerator fileGenerator(filename);
  fileGenerator.GenerateFile();
  return 0;
}
