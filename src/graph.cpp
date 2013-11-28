//This code has been modified to be used for remodel
//http://www.geeksforgeeks.org/detect-cycle-in-a-graph/
// A C++ program to print topological sorting of a DAG

#include<iostream>
#include <list>
#include <stack>
#include <map>
#include <vector>
using namespace std;

#include "production.h"
#include "graph.h"
#include "stringutil.h"

Graph::Graph(int V)
{
  this->V = V;
  adj = new list<int>[V];
}

Graph::Graph()
{

}

void Graph::addEdge(int v, int w)
{
  adj[v].push_back(w); // Add w to v’s list.
}

void Graph::insert_edge(production prod_stmt)
{
  string target_csv = prod_stmt.getTargetFilesCSV();
  string dependency_csv = prod_stmt.getDependencyFilesCSV();
  cout << target_csv << " : " << dependency_csv << endl;
  gmap::iterator itr = graph_map.begin();
  itr = graph_map.find(target_csv);
  node *v;
  v = new node(target_csv, dependency_csv, prod_stmt);
 
  if(itr == graph_map.end())
    {
      //if the target is not found
      map<string, node*> dependent_map; 
      dependent_map[dependency_csv] = v;
      graph_map[target_csv] = dependent_map;
    } 
  else 
    {
      //target is found // check if the dependent exists
      map<string, node *> dependent_map = graph_map[target_csv];
      map<string, node *>::iterator d_itr = dependent_map.begin();
      d_itr = dependent_map.find(dependency_csv);

      if(d_itr == dependent_map.end()) 
	{
	  //target was not found // add the new node
	  dependent_map[dependency_csv]= v;
	  graph_map[target_csv] = dependent_map;
	}
      else 
	{
	  //if it was found... ignore the redundant
	  cout << "Found and ignored repeating target-dependents in the grammar!" << endl;
	  cout << target_csv << " " << dependency_csv << endl << endl;
	}
    }
  //productions that are not part of the program doesn't get executed;
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, map<int, bool> visited, stack<int> &Stack)
{
  // Mark the current node as visited.
  visited[v] = true;

  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      topologicalSortUtil(*i, visited, Stack);

  // Push current vertex to stack which stores result
  Stack.push(v);
}

// The function to do Topological Sort. It uses recursive topologicalSortUtil()
void Graph::topologicalSort()
{
  stack<int> Stack;

  // Mark all the vertices as not visited
  map<int, bool> visited;
  for (int i = 0; i < V; i++)
    
    visited[i] = false;

  // Call the recursive helper function to store Topological Sort
  // starting from all vertices one by one
  for (int i = 0; i < V; i++)
    if (visited[i] == false)
      topologicalSortUtil(i, visited, Stack);

  // Print contents of stack
  while (Stack.empty() == false)
    {
      cout << Stack.top() << " ";
      Stack.pop();
    }
}

// This function is a variation of DFSUytil() in http://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclicUtil(int v, map<int, bool> visited, bool *recStack)
{
  if(visited[v] == false)
    {
      // Mark the current node as visited and part of recursion stack
      visited[v] = true;
      recStack[v] = true;

      // Recur for all the vertices adjacent to this vertex
      list<int>::iterator i;
      for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
	  cout << *i << ":: cyclicutil:: " << visited[*i]<< endl;
	  //if cycle presents
	  if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
	    
	    return true;
	  //if already visited
	  else if (recStack[*i])
	    return true;

        }

    }
  recStack[v] = false;  // remove the vertex from recursion stack
  return false;
}

// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in http://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclic()
{
  // Mark all the vertices as not visited and not part of recursion
  // stack
  map<int, bool> visited;
  bool *recStack = new bool[V];

  for(int i = 0; i < V; i++)
    {
      visited[i] = false;
      recStack[i] = false;
    }

  // Call the recursive helper function to detect cycle in different
  // DFS trees
  for(int i = 0; i < V; i++)
    {
      cout << "checking vertex.. " <<  i << endl;
      if (isCyclicUtil(i, visited, recStack))
	return true;
    }
  return false;
}

void Graph::mark(string vertex, map<string, bool> &mmap, bool value)
{
  mmap[vertex]= value;
  //  for( map<string, bool>::iterator i = mmap.begin();  i!=mmap.end();++i)
  //{
  //cout << "v : " << (*i).first << "  current_vertex:" << vertex << endl;
  // if ( (*i).first.find(vertex)!=string::npos || vertex.find((*i).first)!=string::npos)
  //	{
  // mmap[(*i).first] = true;
  //	  cout << "  Marking vertex.." << (*i).first << ":" <<vertex<<":" << endl;
  //	}
  //}
}

bool Graph::is_marked(string vertex, map<string, bool> mmap)
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

bool Graph::is_cyclic_graph(string vertex, map<string, bool> visited_map, map<string, bool> recursion_map)
{
  
  if(visited_map[vertex] == false)
    {
      //need to check if the vertex has been visited
      //other vertex is also visited
      //if the subset is there mark subset -- foo, bar <- foo.cpp, bar.cpp
      //foo.o <- some other stuff
      cout << "VISIT true:" << vertex<<":" << endl;
      //mark(vertex, visited_map,  true);
      //mark(vertex, recursion_map,  true);
      visited_map[vertex] = true;
      recursion_map[vertex] = true;
      // Recur for all the vertices adjacent to this vertex
      //list<int>::iterator i;
      for(map<string, node*>::iterator i = graph_map[vertex].begin(); i != graph_map[vertex].end(); ++i)
        {
	  string target = (*i).first; 
	  //mark((*i).first, visited_map,  false);
	  //mark((*i).first, recursion_map,  false);
	  
	  // bool visited_flag = is_marked((*i).first, visited_map);
	  // bool recursion_flag = is_marked((*i).first, recursion_map);
	  bool visited_flag = visited_map[target];
	  bool recursion_flag = recursion_map[target];
	  cout << "      Visiting adjacent vertex " <<target << "  "  << visited_flag << recursion_flag << endl; 
	  if (!visited_flag && is_cyclic_graph(target, visited_map, recursion_map)) 
	    return true;
	  else if (recursion_flag)
	    return true;

	  
	  //if more than one target... visit them separately..
	  vector<string> target_files = stringutil::split(target, ",");	  
	  cout << target_files.size() << " Size" << endl;
	  if(target_files.size()>1)
	    {
	      for(unsigned int k = 0; k < target_files.size();k++)
	  	{
		  cout << "                      target files:" << target_files[k] << endl;
	  	  visited_flag = is_marked(target_files[k], visited_map);
	  	  recursion_flag = is_marked(target_files[k], recursion_map);

	  	  if (!visited_flag && is_cyclic_graph(target_files[k], visited_map, recursion_map)) 
	  	    return true;
	  	  else if (recursion_flag)
	  	    return true;
	  	}
	    }
	  cout << "      Visiting adjacent vertex complete"<< endl;
	}
    }
  cout << "     VISIT complete - false" << vertex  << endl;
  recursion_map[vertex] = false;  // remove the vertex from recursion stack
  return false;
}

bool Graph::is_cyclic()
{

  // Mark all the vertices as not visited and not part of recursion
  // stack
  map<string, bool> visited_map;
  map<string, bool> recursion_map;
  //make all visited false
  
  for( gmap::iterator i=graph_map.begin(); i!=graph_map.end(); ++i)
    {
      cout << (*i).first << endl;
      map<string, node*> dependency_map = graph_map[(*i).first];

      for(map<string, node*>::iterator j = dependency_map.begin(); j!=dependency_map.end(); ++j)
	{
	  visited_map[(*j).first] = false;
	  recursion_map[(*j).first] = false;
	}

      visited_map[(*i).first] = false;
      recursion_map[(*i).first] = false;
    }
  
  // for(map<string, bool> :: iterator i = visited_map.begin(); i!=visited_map.end();++i)
  //   {
  //     cout << "visited_map: " << (*i).first << "=" << visited_map[(*i).first]<< endl;
  //   }

  for( gmap::iterator i = graph_map.begin(); i!=graph_map.end(); ++i)
    {
      cout << "Traversing .. "<< (*i).first << endl;
      if (is_cyclic_graph((*i).first, visited_map, recursion_map))
	return true;
    }

  return false;
}

// Driver program to test above functions
// int main()
// {
//   // Create a graph given in the above diagram
//   Graph g(6);
//   g.addEdge(5, 2);
//   g.addEdge(5, 0);

//   g.addEdge(4, 0);
//   g.addEdge(4, 1);
//   g.addEdge(2, 3);
//   g.addEdge(3, 1);

//   g.addEdge(3, 5);
//   if(g.isCyclic())
//     cout << "Graph contains cycle" << endl;
//   else
//     cout << "Graph doesn't contain cycle" << endl;


//   cout << "Following is a Topological Sort of the given graph \n";
//   g.topologicalSort();

//   return 0;
// }

