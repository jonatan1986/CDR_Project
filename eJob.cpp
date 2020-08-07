#include<iostream>
#include"eJob.h"
using namespace std;


threadPoolJob::threadPoolJob(const std::string& filename,int startline,int endline)
:m_filename(filename),m_startline(startline),m_endline(endline)
{
  // writer = make_shared<cdrWriter>(filename,startline,endline);
  // parser = make_shared<cdrParser>(filename,startline,endline);
  // reader = make_shared<cdrReader>(filename,startline,endline);
}

void threadPoolJob::Run()
{

}
