#include <string>
#include <queue>

using namespace std;

#include "production.h"
#include "graph.h"

#ifndef _CMD_UTIL
#define _CMD_UTIL

class commandutil
{
 public:
  static string exec(string cmd);
  static bool exec_all(queue<string> queue, graph graph);
  static void exec_thread(string cmd);
};
#endif
