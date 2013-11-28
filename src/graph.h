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

typedef map<string, map<string, node *> > gmap;
// Class to represent a graph
class graph
{
 private:
  gmap _graph_map;
  bool is_cyclic_graph(string , map<string, bool>, map<string, bool>);
  void topological_sort_graph(string vertex, map<string, bool> &visited_map, queue<string> &queue);

 public:
  void insert_edge(production);
  bool is_cyclic();
  bool is_marked(string vertex, map<string, bool> mmap);
  const queue<string> topological_sort();
  void print();
  gmap get_graph();
  node* find(string vertex);
};
#endif
