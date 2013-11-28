#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
using namespace std;

#include "stringutil.h"
#include "parser.h"
#include "graph.h"

parser::parser(char* filename)
{
  _filename = filename;
  cout << "Parsing " << filename << endl;
}

parser::~parser() 
{
  cout << "The End." << endl;
}

vector<production>& parser::parse()
{
  if (!_productions.empty()) _productions.clear();
  
  string str;
  ifstream infile(_filename);

  while(!infile.eof())
    {
      getline(infile,str); 

      if (stringutil::trim(str).empty()) continue;


      vector<string> flds = stringutil::split(str, "<-");
      
      if(flds.size() != 2) 
	{
	  cout << "error in grammar :" << str << endl;
	}
  
      //target files
      vector<string> target_files = stringutil::split(flds[0], ",");

      //dependency : command
      vector<string> dc_stmt = stringutil::split(flds[1], ":");

      //sanity check
      if(dc_stmt.size() == 0 || dc_stmt.size() > 2)  
	{
	  //error in grammar! TODO handle this? exit/9
	}
  
      vector<string> dependency_files = stringutil::split(dc_stmt[0], ",");
  
      //command exists
      string command;
      if(dc_stmt.size() == 2) 
	{
	  command = dc_stmt[1];
	}

      production obj(target_files, dependency_files, command);
      _productions.push_back(obj);

    }

  return _productions;
}


int main() 
{  
  //default name
  char filename[] = "makefile_re";
  //char filename[] = "test_cases/cyclic_make_testcase_2";
  parser program(filename);
  vector<production> productions = program.parse();
  
  cout << productions.size() << " statements found." << endl;
  
  //Graph graph;
  //graph.create_dependency_graph(productions);

  Graph graph;
  for (unsigned int i = 0; i < productions.size(); i++)
    {
      //productions[i].print_production_stmt();
      cout << "inserting edge.. " << endl;
      graph.insert_edge(productions[i]);
    }

  

  
  if(graph.is_cyclic())
    cout << "Graph contains cycle" << endl;
  else
    cout << "Graph doesn't contain cycle" << endl;

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

  return 0;
}
