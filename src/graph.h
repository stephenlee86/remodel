#include<iostream>
#include <queue>
#include <map>

using namespace std;

#ifndef _NODE_H
#define _NODE_H

struct node
{  
  production prod_stmt;
  string target;
  string dependency;

  node(string tgt, string dep, production pstmt)
  {
    target = tgt;
    dependency = dep;
    prod_stmt = pstmt;
  }
};

#endif

#ifndef _GRAPHN_H
#define _GRAPHN_H

typedef map<string, node* > gmap;
// Class to represent a graph
class graph
{
 private:
  gmap _graph_map;
  void topological_sort_graph(string vertex, map<string, bool> &visited_map, queue<string> &queue);
  
  //  map<string, string> _adj_map;    // Pointer to an array containing adjacency lists
  void add_edge(map<string,string> &, string target, string dependency);
  bool is_cyclic_graph(map<string, string>, string , map<string, bool> , map<string,bool> &);  // used by isCyclic()
  

 public:
  void insert_edge(production);
  bool is_cyclic();

  /* bool is_marked(string vertex, map<string, bool> mmap); */
  const queue<string> topological_sort();
  void print();

  gmap get_graph();
  node* find(string vertex);
};
#endif
