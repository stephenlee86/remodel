#include<vector>
#ifndef _TREE_H
#define _TREE_H

struct tree
{
  
  int data;
  string name;
  vector<tree*> child;

  tree(string name, int d)
  {
    data = d;
  }
};

class tree_util {
 public:
  /*Function protoypes*/
  void printGivenLevel(struct tree* root, int level);
  void printLevelOrder(tree* root);
  int height(struct tree* node);
  void add_edge(vector<tree*> &graph, int target, int dependency);
  tree* add_edge(tree *t, int data);
  tree*& find(tree* &node, int data);
};
#endif
