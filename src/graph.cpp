//This code has been modified to be used for remodel
//http://www.geeksforgeeks.org/detect-cycle-in-a-graph/
// A C++ program to print topological sorting of a DAG

#include<iostream>
#include <queue>
#include <map>

using namespace std;

#include "production.h"
#include "graph.h"
#include "stringutil.h"

gmap graph::get_graph()
{
  return _graph_map;
}

void graph::print()
{
  cout << "printing graph" << endl;
  for( gmap::iterator i=_graph_map.begin(); i!=_graph_map.end(); ++i)
    {
      string key = (*i).first;
      cout << "Target.. "<<key << endl;
      cout <<"     child:: " << _graph_map[key]->dependency << endl;

      // for(map<string, node*>::iterator j = _graph_map[key].begin(); j!=_graph_map[key].end(); ++j)
      // 	{
      // 	  cout <<"     child:: " << (*j).first << endl;
      // 	}
    }
  cout << "printing graph.. ends" << endl;
}

void graph::insert_edge(production prod_stmt)
{
  string target_csv = prod_stmt.getTargetFilesCSV();
  string dependency_csv = prod_stmt.getDependencyFilesCSV();
  //cout << target_csv << " : " << dependency_csv << endl;
  
  gmap::iterator itr = _graph_map.begin();
  itr = _graph_map.find(target_csv);
  node *vertex = new node(target_csv, dependency_csv, prod_stmt);
 
  if(itr == _graph_map.end())
    {
      //if the target is not found
      //map<string, node*> dependent_map; 
      //dependent_map[dependency_csv] = v;
      //_graph_map[target_csv] = dependent_map;
      //      _graph_map[target_csv] = vertex;
      //_graph_map.insert(make_pair(targe_csv, vertex));
    } 
  else 
    {
      //target is found - duplicate targets... overide
      cout<<"Warning: overiding commands for target: '"<< target_csv <<"'"<<endl;
      // _graph_map[target_csv] = vertex;
      // map<string, node *> dependent_map = _graph_map[target_csv];
      // map<string, node *>::iterator d_itr = dependent_map.begin();
      // d_itr = dependent_map.find(dependency_csv);

      // if(d_itr == dependent_map.end()) 
      // 	{
      // 	  //target was not found // add the new node
      // 	  dependent_map[dependency_csv]= v;
      // 	  _graph_map[target_csv] = dependent_map;
      // 	}
      // else 
      // 	{
      // 	  //if it was found... ignore the redundant
      // 	  cout << "Found and ignored repeating target-dependents in the grammar!" << endl;
      // 	  cout << target_csv << " " << dependency_csv << endl << endl;
      // 	}
    }
  _graph_map.insert(make_pair(target_csv, vertex));
  //productions that are not part of the program doesn't get executed;: same as make!
}

void graph::topological_sort_graph(string vertex, map<string, bool> &visited_map, queue<string> &queue)
{
  //Check to see if not leaf... 
  gmap::iterator vitr = _graph_map.begin();
  vitr = _graph_map.find(vertex);
  if(vitr == _graph_map.end())
    {
      //leaf node ---  e.g. bar.o <- bar.cpp and bar.cpp is the leaf node... 
      //cout << vertex << endl;
      //check by breaking it up.... 
      
      //if more than one dependency... visit them separately..
      vector<string> target_files = stringutil::split(vertex, ",");	  
      //cout << target_files.size() << " Size" << endl;
      if(target_files.size()>1)
	{
	  for(unsigned int k = 0; k < target_files.size();k++)
	    {
	      if (!visited_map[target_files[k]])
		{
		  topological_sort_graph(target_files[k], visited_map, queue);
		}
	    }
	}

      return;
    }

  // Mark the current node as visited.
  visited_map[vertex] = true;
  
  //  cout << "Visiting " << vertex << endl;
  //since there can't be duplicate targets: a<-b a<-c is not allowed
  
  node* node =  _graph_map[vertex];
  string dependency = node->dependency;
  if (!visited_map[dependency])
    {
      // cout << "     Visiting " << (*i).first << endl;
      topological_sort_graph(dependency, visited_map, queue);
    }

  // cout << "Visiting " << vertex  << " ends" << endl;
  // Push current vertex to stack which stores result
  queue.push(vertex);
}

//This is printing in reverse order ... need to order them correctly.
const queue<string> graph::topological_sort()
{
  queue<string> queue;
  map<string, bool> visited_map;

  // Mark all the vertices as not visited
  for( gmap::iterator i = _graph_map.begin(); i != _graph_map.end(); ++i)
    {
      //cout << "Targets: " << (*i).first << endl;
      visited_map[(*i).first] = false;
    }
  
  for( gmap::iterator i=_graph_map.begin(); i!=_graph_map.end(); ++i)
    {
      string target = (*i).first;
      if (!visited_map[target])
	{
	  topological_sort_graph(target, visited_map, queue);
	}
    }

  // Print contents of stack
  //topological sorted graph in a stack
  // while (!queue.empty())
  //   {
  //     cout<< "FROM QUEUE:" << queue.front() << " " << endl;
  //     queue.pop();
  //   }
  return queue;
}



void graph::add_edge(map<string, string> &graph_map, string target, string dependency)
{
  graph_map[target] = dependency;
}

bool graph::is_cyclic_graph(map<string, string> graph_map, string v, map<string, bool> visited, map<string,bool> &rec_stack)
{
  
  //  cout << "Vertex: " << v << visited[v] <<endl ;
  
  map<string, string>::iterator itr = graph_map.begin();
  itr = graph_map.find(v);
  if(itr == graph_map.end())
    {
      //if leaf node
      return false;
    }
  //cout << "Vertex: " << v << visited[v] <<endl ;
  if(visited[v] == false)
    {
      // Mark the current node as visited and part of recursion stack
      visited[v] = true;
      rec_stack[v] = true;

      // Recur for all the vertices adjacent to this vertex

      //        for(map<string, string> i = _adj_graph.begin(); i != adj[v].end(); ++i)
      //{
      string dependency = graph_map[v];
      //  cout << "      Dependency(false): " << v << endl;
      if ( !visited[dependency] && is_cyclic_graph(graph_map, dependency, visited, rec_stack) )
	return true;
      else if (rec_stack[dependency])
	return true;
      //}

    }
  rec_stack[v] = false;  // remove the vertex from recursion stack
  return false;
}

bool graph::is_cyclic()
{
  map<string, bool> visited;
  map<string, bool> rec_stack;
  map<string, string> graph_map;

  ///create a graph, 
  for(gmap::iterator i=_graph_map.begin(); i!= _graph_map.end();i++)
    {
      add_edge(graph_map, _graph_map[(*i).first]->target,_graph_map[(*i).first]->dependency);
      //cout <<"saddedge:" << _graph_map[(*i).first]->target <<":" << _graph_map[(*i).first]->dependency<<":" << endl;
      ///not regarding dependency because if dependency is not in target then it wont be cyclic
      visited[_graph_map[(*i).first]->target] = false;
      rec_stack[_graph_map[(*i).first]->target] = false;

      vector<string> target_csv = stringutil::split(_graph_map[(*i).first]->target, ",");
      vector<string> dependency_csv = stringutil::split(_graph_map[(*i).first]->dependency, ",");

      if(target_csv.size() > 1 || dependency_csv.size() >1)
	{
	  for(unsigned int j = 0; j < target_csv.size();j++)
	    { 
	      for(unsigned int k = 0; k < dependency_csv.size(); k++)
		{
		  add_edge(graph_map, target_csv[j], dependency_csv[k]);

		  visited[target_csv[j]] = false;
		  rec_stack[target_csv[j]] = false;
		  // cout <<"addedge:" << target_csv[j] <<":" << dependency_csv[k]<<":" << endl;
		}
	    }
	}
    }
  //check for cyclicity
  for(map<string, string>::iterator i=graph_map.begin(); i != graph_map.end(); i++)
    if (is_cyclic_graph(graph_map, (*i).first, visited, rec_stack))
      return true;

  return false;

  
}

node* graph::find(string vertex)
{

  gmap::iterator itr = _graph_map.begin();
  itr = _graph_map.find(vertex);
  if(itr != _graph_map.end()) 
    {
        
      return _graph_map[vertex];
      // if(dep_map.size()>1) cout<<"something wrong??"<<endl;
      // for( map<string, node*>::iterator i=dep_map.begin(); i!=dep_map.end(); ++i)
      // 	{
      // 	  return (*i).second;
      // 	}
    }

  cout << vertex << " not found!.. something must be wrong.." << endl;
  return NULL;

}

