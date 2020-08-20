#include"FileGenerator.h"
#include "TaskManager.h"

using namespace std;
#define filename "datafile.txt"





int main(int argc, char const *argv[]) {

  FileGenerator fileGenerator(filename);
  TaskManager taskManager(5,filename,fileGenerator.GetFileSize());
  taskManager.CreateThreads();
  return 0;
}
