#include"FileGenerator.h"
#include "TaskManager.h"
#include "SingleTone.h"
#include "Config.h"

using namespace std;






int main(int argc, char const *argv[]) {

  try
  {
    Config *l_config = SingleTone<Config>::GetIntstance();
    int l_nAmoutOfChunks =  l_config->GetAmountOfChunks().length() > 0 ?
    stoi(l_config->GetAmountOfChunks()) : AMOUNT_OF_CHUNKS;

    string l_sFileName = l_config->GetFileName().length() > 0 ?
    l_config->GetFileName() : FILE_NAME;

    TaskManager l_taskManager(l_nAmoutOfChunks,l_sFileName);
    l_taskManager.CreateThreads();
  }
  catch(string &str)
  {
    cout<<str<<endl;
  }
  return 0;
}
