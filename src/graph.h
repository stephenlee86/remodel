#include<iostream>
#include <list>
#include <stack>
#include <map>
#include <vector>
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
class Graph
{
  int V;    // No. of vertices'

  // Pointer to an array containing adjacency listsList
  list<int> *adj;

  // A function used by topologicalSort
  void topologicalSortUtil(int v, map<int, bool> visited, stack<int> &Stack);
  bool isCyclicUtil(int v, map<int, bool> visited, bool *rs);  // used by isCyclic()

  

  //Root node  
  typedef map<string, map<string, node *> > gmap;
  gmap graph_map;
  bool is_cyclic_graph(string , map<string, bool>, map<string, bool>);

public:
  Graph(int V);   // Constructor
  Graph();
  // function to add an edge to graph
  void addEdge(int v, int w);
  void insert_edge(production);

  // prints a Topological Sort of the complete graph
  void topologicalSort();
  bool isCyclic();
  bool is_cyclic();

  void mark(string vertex, map<string, bool> &mmap, bool value);
  bool is_marked(string vertex, map<string, bool> mmap);
};
#endif
