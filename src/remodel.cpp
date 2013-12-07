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
  string root = "test_cases/bar.o";

  //char filename[] = "test_cases/cyclic_make_testcase_2";
  parser program(filename);
  vector<production> productions = program.parse();

  cout << productions.size() << " production statements found." << endl;
  
  graph graph;

  for (unsigned int i = 0; i < productions.size(); i++)
    {
      graph.insert_edge(productions[i]);
    }
  //if DEFAULT
  gmap graph_map = graph.get_graph();
  cout << root<< endl;
  gmap::iterator it = graph_map.find(root);
  if(it != graph_map.end()) {
    
    if(root.compare("DEFAULT")==0) {
      string roots = graph_map[root]->dependency;
      vector<string> root_list = stringutil::split(roots, ",");
      for (unsigned int i = 0; i< root_list.size();i++) 
	{
	  //cout << root_list[i] << endl;
	  graph.create_tree_graph(root_list[i]);
	}
    } else {
      graph.create_tree_graph(root);
    }

    
    if(graph.is_cyclic())
      cout << "Graph contains cycle" << endl;
    else
      cout << "Graph doesn't contain cycle" << endl;

 
    commandutil::exec_in_parallel(graph);
  }
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

  vector<tree*> tree_graph =  graph.get_tree_graph();
  for(unsigned int i = 0; i < tree_graph.size(); i++) 
    {
      tree_util::print_level_order(tree_graph[i]);
      cout << "dss" << endl;
      int height = tree_util::height(tree_graph[i]);
      cout << "height in parallel:" << height << endl;
  
      for(int k = height; k > 2; k--) {
    
      	vector<string> targets;
      	tree_util::get_given_level(tree_graph[k], 1, targets);
    
      	for(unsigned int j = 0; j < targets.size(); j++)
      	  {
      	    cout << "For "<<  ":" << targets[j] << endl;
      	  }
      }
    }

  
  //commandutil::exec_in_parallel(tree_graph, graph);
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
