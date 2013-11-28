#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "production.h"
#include "graph.h"

void graph::create_dependency_graph(vector<production> productions) 
{
  if(_production_graph.size()!=0) _production_graph.clear();
  cout << "here" << endl;
  for(unsigned int i = 0; i < _production_graph.size(); i++) 
    {
      
    }
}
