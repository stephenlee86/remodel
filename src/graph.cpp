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

      for(map<string, node*>::iterator j = _graph_map[key].begin(); j!=_graph_map[key].end(); ++j)
	{
	  cout <<"     child:: " << (*j).first << endl;
	}
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
  node *v;
  v = new node(target_csv, dependency_csv, prod_stmt);
 
  if(itr == _graph_map.end())
    {
      //if the target is not found
      map<string, node*> dependent_map; 
      dependent_map[dependency_csv] = v;
      _graph_map[target_csv] = dependent_map;
    } 
  else 
    {
      //target is found // check if the dependent exists
      map<string, node *> dependent_map = _graph_map[target_csv];
      map<string, node *>::iterator d_itr = dependent_map.begin();
      d_itr = dependent_map.find(dependency_csv);

      if(d_itr == dependent_map.end()) 
	{
	  //target was not found // add the new node
	  dependent_map[dependency_csv]= v;
	  _graph_map[target_csv] = dependent_map;
	}
      else 
	{
	  //if it was found... ignore the redundant
	  cout << "Found and ignored repeating target-dependents in the grammar!" << endl;
	  cout << target_csv << " " << dependency_csv << endl << endl;
	}
    }
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
  for(map<string, node*>::iterator i = _graph_map[vertex].begin(); i != _graph_map[vertex].end(); ++i)
    {
      if (!visited_map[(*i).first])
	{
	  // cout << "     Visiting " << (*i).first << endl;
	  topological_sort_graph((*i).first, visited_map, queue);
	}
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

bool graph::is_marked(string vertex, map<string, bool> mmap)
{
  bool flag = false;
  for( map<string, bool>::iterator i = mmap.begin();  i!=mmap.end();++i)
    {
      //cout << "v : " << (*i).first << "  current_vertex:" << vertex << endl;
      if ( (*i).first.find(vertex)!=string::npos || vertex.find((*i).first)!=string::npos)
	{
	  flag = mmap[(*i).first] || flag;
	}
    }
  return flag;
}

bool graph::is_cyclic_graph(string vertex, map<string, bool> visited_map, map<string, bool> recursion_map)
{
  
  gmap::iterator vitr = _graph_map.begin();
  vitr = _graph_map.find(vertex);
  if(vitr == _graph_map.end())
    {
      //leaf node ---  e.g. bar.o <- bar.cpp and bar.cpp is the leaf node... 
      //cout << vertex << endl;
      return false;
    }
  
  if(visited_map[vertex] == false)
    {
      //need to check if the vertex has been visited
      //other vertex is also visited
      //if the subset is there mark subset -- foo, bar <- foo.cpp, bar.cpp
      //foo.o <- some other stuff
      //cout << "VISIT true:" << vertex<<":" << endl;
      //mark(vertex, visited_map,  true);
      //mark(vertex, recursion_map,  true);
      visited_map[vertex] = true;
      recursion_map[vertex] = true;
      // Recur for all the vertices adjacent to this vertex
      //list<int>::iterator i;
      for(map<string, node*>::iterator j = _graph_map[vertex].begin(); j != _graph_map[vertex].end(); ++j)
        {
	  string target = (*j).first; 
	  //mark((*i).first, visited_map,  false);
	  //mark((*i).first, recursion_map,  false);
	  
	  // bool visited_flag = is_marked((*i).first, visited_map);
	  // bool recursion_flag = is_marked((*i).first, recursion_map);
	  bool visited_flag = visited_map[target];
	  bool recursion_flag = recursion_map[target];
	  //	  cout << "      Visiting adjacent vertex " <<target << "  "  << visited_flag << recursion_flag << endl; 
	  if (!visited_flag && is_cyclic_graph(target, visited_map, recursion_map)) 
	    return true;
	  else if (recursion_flag)
	    return true;

	  
	  //if more than one target... visit them separately..
	  vector<string> target_files = stringutil::split(target, ",");	  
	  //cout << target_files.size() << " Size" << endl;
	  if(target_files.size()>1)
	    {
	      for(unsigned int k = 0; k < target_files.size();k++)
	  	{
		  //cout << "                      target files:" << target_files[k] << endl;
	  	  visited_flag = is_marked(target_files[k], visited_map);
	  	  recursion_flag = is_marked(target_files[k], recursion_map);

	  	  if (!visited_flag && is_cyclic_graph(target_files[k], visited_map, recursion_map)) 
	  	    return true;
	  	  else if (recursion_flag)
	  	    return true;
	  	}
	    }
	  //cout << "      Visiting adjacent vertex complete"<< endl;
	}
    }
  //cout << "     VISIT complete - false" << vertex  << endl;
  recursion_map[vertex] = false;  // remove the vertex from recursion stack
  return false;
}

bool graph::is_cyclic()
{

  // Mark all the vertices as not visited and not part of recursion
  // stack
  map<string, bool> visited_map;
  map<string, bool> recursion_map;
  //make all visited false
  
  for( gmap::iterator i=_graph_map.begin(); i!=_graph_map.end(); ++i)
    {
      visited_map[(*i).first] = false;
      recursion_map[(*i).first] = false;
    }
  
  // for(map<string, bool> :: iterator i = visited_map.begin(); i!=visited_map.end();++i)
  //   {
  //     cout << "visited_map: " << (*i).first << "=" << visited_map[(*i).first]<< endl;
  //   }
  
  for( gmap::iterator i = _graph_map.begin(); i!=_graph_map.end(); ++i)
    {
      //cout << "Traversing .. "<< (*i).first << endl;
      if (is_cyclic_graph((*i).first, visited_map, recursion_map))
	return true;
    }
  
  return false;
}

node* graph::find(string vertex)
{

  gmap::iterator itr = _graph_map.begin();
  itr = _graph_map.find(vertex);
  if(itr != _graph_map.end()) 
    {
        
      map<string, node*> dep_map =  _graph_map[vertex];
      if(dep_map.size()>1) cout<<"something wrong??"<<endl;
      for( map<string, node*>::iterator i=dep_map.begin(); i!=dep_map.end(); ++i)
	{
	  return (*i).second;
	}
    }

  cout << vertex << " not found!.. something must be wrong.." << endl;
  return NULL;
  // for( gmap::iterator i=_graph_map.begin(); i!=_graph_map.end(); ++i)
  //   {
  //     //      for(map<string, node*>::iterator j=_graph_map[(*i).first].begin(); j!=_graph_map[(*i).first].end(); ++j)
  // 	// {
  // 	//   cout << vertex << " " << (*j).first<< endl;
  // 	//   //if (vertex == (*j).first)
  // 	//   //return (*j).second;
  // 	// }
      

  //   }

}

