
// #include <iostream>

#include"FileGenerator.h"

using namespace std;
#define filename "datafile.txt"





int main(int argc, char const *argv[]) {
  /* code */
  FileGenerator fileGenerator(filename);
  try
  {
      fileGenerator.GenerateFile();
  }
  catch(string& str)
  {
    cout<<str<<endl;
  }

  return 0;
}
