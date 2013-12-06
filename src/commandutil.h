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
  static void exec_cmd(string cmd);
  static void exec_tree_in_parallel(tree* order_graph, graph graph) ;
  static void exec_in_parallel(graph graph); 
  static void copy_output(graph graph, vector<string> targets, map<string, bool> &change_tracker, int i, int height);
  static void convertToCharArray( string str, char c[]);
  /*
  static void exec_in_recursive_parallel(tree*& tree, graph &graph, map<string, bool> &val);
  static void exec_in_recursive_parallel(graph graph);
  static void run_u(node* node);
  */
};
#endif
