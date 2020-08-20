
#include <iostream>
#include <memory>
#include"TaskManager.h"
#include"Task.h"

using namespace std;



TaskManager::TaskManager(int numOfChunks,const string& filename):m_numOfChunks(numOfChunks),
m_filename(filename)
{
}


void Run(const string& fileName, int startLine, int endLine)
{
  Task task(fileName,startLine,endLine);
  task.Run();
}

int GetAmountOfLines(TaskManager &taskManager)
{
    ifstream l_fin(taskManager.m_filename);
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
  int l_nStartLine = 1,l_nEndLine = l_nAmountOfLinesInFile/m_numOfChunks, l_nDiff = l_nAmountOfLinesInFile/5;
  ThreadPool l_threadPool;
  while(l_nEndLine <= l_nAmountOfLinesInFile)
  {
    if (l_nStartLine - 1 + 2 * l_nDiff >  l_nAmountOfLinesInFile)
    {
        //if amunt of lines is not round - last thread will
        // handle the "carry of lines", in addition to the lines it should
        // treat
        l_nEndLine = l_nAmountOfLinesInFile;
        l_threadPool.AddThread(&Run,m_filename,l_nStartLine,l_nEndLine);
        break;
    }
    l_threadPool.AddThread(&Run,m_filename,l_nStartLine,l_nEndLine);
    l_nStartLine = l_nEndLine + 1;
    l_nEndLine += l_nDiff;
  }
}
