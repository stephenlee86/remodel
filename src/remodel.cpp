#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <queue>
#include <cstring>
#include <fstream>
using namespace std;

#include "stringutil.h"
#include "parser.h"
#include "graph.h"
#include "commandutil.h"
#include "tree.h"

//TODO Sanity check of the grammar -- case where command can be any random query

int main(int argc, char* argv[]) 
{ 
  string root = "DEFAULT";
  char filename[]  = "remodel_makefile";
  //multiple target 'foo.o, boo.o'<= sfsdf :::  clean cout code ::: 
  //check if remmake presesnnts system.exit"""
  if(argc == 2) 
    {
      root = string(argv[1]);
    }
  if(argc == 3)
    {
      strcpy(filename, argv[2]);
    }
  if(!ifstream(filename)) {
    cout << "Remode Makefile not found: " << filename << endl;
    return 0;
  }
  
  
  //default name
  
  
  parser program(filename);
  vector<production> productions = program.parse();

  cout << productions.size() << " production statements found." << endl;
  
  graph graph;

  for (unsigned int i = 0; i < productions.size(); i++)
    {
      graph.insert_edge(productions[i]);
    }

  //check for cycles
  if(graph.is_cyclic()) 
    {
    cout << "Graph contains cycle! Check the remodel_makefile" << endl;
    return 0;
    }
  else 
    {
      cout << "Graph doesn't contain cycle" << endl;
    }

  gmap graph_map = graph.get_graph();
  

  ///match a label in case of multiple labels

  for(gmap::iterator it = graph_map.begin(); it != graph_map.end() ;it++)
    {
      //      cout << root <<(*it).first<< endl;
      string roots = (*it).first;
      vector<string> root_list;
      if(root.compare("DEFAULT")==0) 
	{
	  roots = graph_map[root]->dependency;
	  root_list = stringutil::split(roots, ",");
	  for (unsigned int i = 0; i< root_list.size();i++)
	    {
	      //cout << root_list[i] << endl;
	      graph.create_tree_graph(root_list[i]);
	    }
	  break;
	} 
      else 
	{
	  root_list = stringutil::split((*it).first, ",");
	  //search for a label
	  for(unsigned int i = 0; i < root_list.size(); i++)
	    {
	      if(root_list[i].compare(root) == 0) {
		graph.create_tree_graph((*it).first);
		break;
	      }
	    }
	}


  }

  commandutil::exec_in_parallel(graph);
  return 0;
}
