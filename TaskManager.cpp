
#include <iostream>
#include <memory>
#include"TaskManager.h"
#include"Task.h"
/*
this class is the resonsible for createing threads who get "Run" function as a
parameter, each thread handles a chunk of the file.
*/
using namespace std;



TaskManager::TaskManager(int nNumOfChunks,const string& sFilename):m_nNumOfChunks(nNumOfChunks),
m_sFileName(sFilename)
{
}


void Run(const string& i_sFileName, int i_nStartLine, int i_nEndLine, int i_threanNum)
{
  Task task(i_sFileName,i_nStartLine,i_nEndLine,i_threanNum);
  task.Run();
}

int GetAmountOfLines(TaskManager &taskManager)
{
    ifstream l_fin(taskManager.m_sFileName);
    if (l_fin.peek() == ifstream::traits_type::eof())
    {
      string l_sThrowMessage = "input file \"datafile.txt\" is empty";
      throw l_sThrowMessage;
    }
    string l_sLine = " ";
    int l_nAmountOfLines = 0;
    while(getline(l_fin,l_sLine))
    {
      ++l_nAmountOfLines;
    }
    return l_nAmountOfLines;
}
void TaskManager::CreateThreads()
{
  int l_nAmountOfLinesInFile = GetAmountOfLines(*this);
  int l_nStartLine = 1,l_nEndLine = l_nAmountOfLinesInFile/m_nNumOfChunks, l_nDiff = l_nAmountOfLinesInFile/5;
  ThreadManager l_threadManager;
  int l_threadNum = 0;
  while(l_nEndLine <= l_nAmountOfLinesInFile)
  {
    if (l_nStartLine - 1 + 2 * l_nDiff >  l_nAmountOfLinesInFile)
    {
        //if amunt of lines is not round - last thread will
        // handle the "carry of lines", in addition to the lines it should
        // treat
        l_nEndLine = l_nAmountOfLinesInFile;
        l_threadManager.AddThread(&Run,m_sFileName,l_nStartLine,l_nEndLine,l_threadNum);
        break;
    }
    l_threadManager.AddThread(&Run,m_sFileName,l_nStartLine,l_nEndLine,l_threadNum);
    l_nStartLine = l_nEndLine + 1;
    l_nEndLine += l_nDiff;

    ++l_threadNum;
  }
}
