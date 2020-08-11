
// #include <iostream>

#include"FileGenerator.h"

using namespace std;
#define filename "datafile.txt"





int main(int argc, char const *argv[]) {
  /* code */
  FileGenerator fileGenerator(filename);
  fileGenerator.GenerateFile();
  return 0;
}
