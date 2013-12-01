/*

  (md5diff(oldA,newA) => everything that depends on A must be rebuilt)

  while not complete {

  move through the topo sort array; 
 
  check if dependency available then compile... ??

  cp target to .remodel/target

  if target output is different than remodel output
  then compile upward dependencies again.. ??
  --- mark upward dependencies as not compiled
 
  mark current as compiled

  }
*/

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <queue>

using namespace std;

#include "stringutil.h"
#include "parser.h"
#include "graph.h"
#include "commandutil.h"

//TODO Sanity check of the grammar -- case where command can be any random query

int main() 
{  
  //default name
  char filename[] = "makefile_re";
  //char filename[] = "test_cases/cyclic_make_testcase_2";
  parser program(filename);
  vector<production> productions = program.parse();
  
  cout << productions.size() << " production statements found." << endl;
  
  graph graph;
  for (unsigned int i = 0; i < productions.size(); i++)
    {
      graph.insert_edge(productions[i]);
    }

  if(graph.is_cyclic())
    cout << "Graph contains cycle" << endl;
  else
    cout << "Graph doesn't contain cycle" << endl;

  //check for syntax and there is going to be only one root.

  //graph.print();
  queue<string> queue = graph.topological_sort();
  while (!queue.empty())
    {
      cout<< "FROM QUEUE:" << queue.front() << " " << endl;
      queue.pop();
    }
  //commandutil::exec_all(queue, graph);
  return 0;

}

 // Graph g(6);
  // g.addEdge(0, 1);
  // g.addEdge(1, 2);
  // g.addEdge(2,2);
  // g.addEdge(4, 0);
  // g.addEdge(4, 1);
  // g.addEdge(2, 3);
  // g.addEdge(3, 1);
  // if(g.isCyclic())
  //   cout << "Graph contains cycle" << endl;
  // else
  //   cout << "Graph doesn't contain cycle" << endl;



  // g.addEdge(3, 5);


  // cout << "Following is a Topological Sort of the given graph \n";
  // g.topologicalSort();
