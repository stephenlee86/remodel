#include<iostream>
#include <queue>
#include <map>

using namespace std;

#ifndef _NODE_H
#define _NODE_H

struct node{
  
  production _prod_stmt;
  string _target;
  string _dependency;

  node(string target, string dependency, production prod_stmt)
  {
    _target = target;
    _dependency = dependency;
    _prod_stmt = prod_stmt;
  }
};

#endif

#ifndef _GRAPHN_H
#define _GRAPHN_H

// Class to represent a graph
class graph
{
  typedef map<string, map<string, node *> > gmap;
  gmap graph_map;
  bool is_cyclic_graph(string , map<string, bool>, map<string, bool>);
  void topological_sort_graph(string vertex, map<string, bool> &visited_map, queue<string> &stack);
public:
  graph();
  void insert_edge(production);
  bool is_cyclic();
  bool is_marked(string vertex, map<string, bool> mmap);
  void topological_sort();
  void print();
};
#endif
