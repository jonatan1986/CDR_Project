#include"FileGenerator.h"
#include"threadManager.h"

using namespace std;
#define filename "datafile.txt"





int main(int argc, char const *argv[]) {

  FileGenerator fileGenerator(filename);
  threadManager threadmanager(5,filename,fileGenerator.GetFileSize());
  threadmanager.CreateThreads();
  return 0;
}
