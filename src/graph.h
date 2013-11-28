#include "production.h"

#ifndef _GRAPH_H
#define _GRAPH_H

class node 
{
 private:  
  node* _parent;
  vector<node> _child;
  production _prod_stmt;

 public:
  node();
  ~node();
  void setParent(node* parent);
  void setChild(vector<node> child);
  void setProductionStmt(production prod_stmt);
  node* getParent();
  vector<node>& getChild();
  production getProductionStmt();

};

node::node()
{
}

node* node::getParent()
{
  return _parent;
}
vector<node>& node::getChild()
{
  return _child;
}
production node::getProductionStmt(){
  return _prod_stmt;
}

node::~node() 
{
}

class graph 
{

 private:
  vector<vector<node> > _production_graph;

 public:
  void create_dependency_graph(vector<production> productions);

};

#endif
