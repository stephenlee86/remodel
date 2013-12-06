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
#include "tree.h"

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

  // vector<node*> leafnodes = graph.findAllLeafNodes();
  // for(unsigned int i = 0; i < leafnodes.size();i++)
  //   {
  //     cout<<"Target:" << leafnodes[i]->target << endl;
  //   }
  // //check for syntax and there is going to be only one root.

  // // graph.print();
  // queue<string> queue = graph.topological_sort();
  

  // while (!queue.empty())
  //   {
  //     cout<< "FROM QUEUE:" << queue.front() << " " << endl;
  //     queue.pop();
  //   }


  // for(unsigned int i = 0; i < tree_graph.size(); i++) 
  //   {
  //     //tree_util::print_level_order(tree_graph[i]);
  //     //cout << "dss" << endl;
  //     // int height = tree_util::height(tree_graph[i]);
  //     // cout << "height in parallel:" << height << endl;
  //     // for(int k = height; k > 2; k--) {
  //     // 	vector<string> targets;
  //     // 	tree_util::get_given_level(tree_graph[k], 1, targets);
  //     // 	for(unsigned int j = 0; j < targets.size(); j++)
  //     // 	  {
  //     // 	    cout << "For "<<  ":" << targets[j] << endl;
  //     // 	  }
  //     // }
  //   }
  //  vector<tree*> tree_graph =  graph.get_tree_graph();
  commandutil::exec_in_parallel(graph);

  return 0;
}
