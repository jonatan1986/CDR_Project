#include"FileGenerator.h"
#include "TaskManager.h"
#include "Config.h"

using namespace std;






int main(int argc, char const *argv[]) {

  TaskManager taskManager(5,FILE_NAME);
  try
  {
     taskManager.CreateThreads();
  }
  catch(string &str)
  {
    cout<<str<<endl;
  }

  return 0;
}
