#include<vector>
#ifndef _TREE_H
#define _TREE_H

struct tree
{
  int data;
  string name;
  vector<tree*> child;

  tree(string n, int d)
  {
    data = d;
    name = n;
  }
};

class tree_util {
 public:

  static void print_given_level(struct tree* root, int level);
  static  void print_level_order(tree* root);
  
  static  int height(struct tree* node);
  static  void add_edge(vector<tree*> &graph, string target, string dependency);
  static  tree* add_edge(tree *t, string data);
  static  tree*& find(tree* &node, string data);

  static  void get_given_level(tree *node, int level, vector<string> &result);
};
#endif
