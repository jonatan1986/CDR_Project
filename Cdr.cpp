#include"FileGenerator.h"
#include "TaskManager.h"
#include "SingleTone.h"
#include "Config.h"

using namespace std;






int main(int argc, char const *argv[]) {

  try
  {
    Config *config = SingleTone<Config>::GetIntstance();
    int l_nAmoutOfChunks =  config->GetAmountOfChunks().length() > 0 ?
    stoi(config->GetAmountOfChunks()) : AMOUNT_OF_CHUNKS;

    string l_sFileName = config->GetFileName().length() > 0 ?
    config->GetFileName() : FILE_NAME;

    TaskManager taskManager(l_nAmoutOfChunks,l_sFileName);
    taskManager.CreateThreads();
  }
  catch(string &str)
  {
    cout<<str<<endl;
  }
  // TaskManager taskManager(5,FILE_NAME);
  // try
  // {
  //    taskManager.CreateThreads();
  // }
  // catch(string &str)
  // {
  //   cout<<str<<endl;
  // }

  return 0;
}
