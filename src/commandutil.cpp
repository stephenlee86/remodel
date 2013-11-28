#include <string>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <cstring> 
#include <thread>

using namespace std;

#include "commandutil.h"
#include "graph.h"

string commandutil::exec(string u) 
{
  char cmd[u.length()-1];
  strcpy(cmd,u.c_str());

  FILE* pipe = popen(cmd, "r");
  if (!pipe) return "ERROR";

  char buffer[128];
  std::string result = "";

  while(!feof(pipe)) {
    if(fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }

  pclose(pipe);
  return result;
}

void commandutil::exec_thread(string cmd)
{
  thread t1(exec, cmd);
  t1.join();
}

bool commandutil::exec_all(queue<string> queue, graph graph)
{
  while(!queue.empty())
    {
      string target = queue.front();

      node* node= graph.find(target);

      //check if dependency exists
      cout<< target << " " << node->_prod_stmt.getCommand() << endl;
      
      string cmd = node->_prod_stmt.getCommand() ;
      
      exec_thread(cmd);

      //Makes the main thread wait for the new thread to finish execution, therefore blocks execution.

      //exec(u);

      queue.pop();
    }
  //  thread.join();
  return 0;
}
