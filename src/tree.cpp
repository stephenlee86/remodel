#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

#include "tree.h"

void tree_util::printLevelOrder(tree* root)
{
  int h = height(root);
  //  cout <<"height:"<< h << endl;
  int i;
  for(i=1; i <= h; i++) {

    printGivenLevel(root, i);
        cout << endl;
  }
}     


void tree_util::printGivenLevel(tree *node, int level)
{
  if(node == NULL)
    return;

  if(level == 1)
    cout <<" a: " << node->data;

  else if (level > 1)
    {
      for(unsigned int i = 0; i < node->child.size(); i++)
	{
	  printGivenLevel(node->child[i], level-1);
	  
	}
    }
}


int tree_util::height(tree* node)
{
  
  if (node==NULL) 
    {
      return 0;
    } 
  else if(node->child.size()==0)
    {
      return 1;
    }
  else
    {
      set<int> heights;
      //      cout << node->name << node->child.size() << endl;

      for (unsigned int x = 0; x < node->child.size(); ++x)
	{
	  heights.insert(height(node->child[x]));
	  // cout << node->child[x]->data;
	}
     
     
      return 1 + *heights.rbegin();
    }
} 

tree*& tree_util::find(tree* &node, int data) 
{
  static tree *temp = NULL;
  if(node->data == data)
    {
      cout << "topL"<< node->data << " ds:" <<data;
      return node;
    }
  else 
    {
      temp = new tree("null", -1);
      cout << " size " << node->child.size() << "  :" << temp->data;

      for(unsigned int i = 0 ;i < node->child.size(); i++)
	{
	  
	  cout << " inside node: " << node->data << " child..." << node->child[i]->data ;
	  temp = find(node->child[i], data);
	  //cout <<"i" << i  << " node:" << node->data << " temp:"<< temp->data;
	  if(temp->data != -1) break;//return temp;
	}
      return temp;
    }

  
}

void tree_util::add_edge(vector<tree*> &graph, int target, int dependency)
{
  bool flag = false;
  tree* target_tree;
  tree* child = NULL;
  //find the right vertex
  cout << "Adding target:" << target <<  " dependency: " << dependency << endl; 
  for (unsigned int i = 0; i < graph.size(); i++) 
    {
      
      target_tree = find(graph[i], target);
      
      cout << "      found? " << target_tree->data<<endl ;
      //if target is found
      if(target_tree->data != -1)
	{
	  cout<<" graph size  " << graph.size();
	  for (unsigned int j =0; j < graph.size();j++)
	    {
	      cout<< "inside";
	      if(j!=i) {
		child = find(graph[j], dependency);
		if(child->data != -1) {
		  break;
		}
	      }
	    }

	  //depndency is found
	  
	  if(child != NULL && child->data != -1) {
	    cout << "Found depe"<< child->data << child->child[0]->data << endl;
	    target_tree->child.push_back(child);
	  } else 
	    {
	      cout <<"Add new edge:" << target_tree->data << dependency  << endl;
	    child = add_edge(target_tree, dependency);
	  }
	  
	  flag = true;
	  break;
	}
    }

  cout << "Adding target:" << target <<  " dependency: " << dependency <<  " status 0==" << flag <<endl; 
  if(flag == false)
    {
      target_tree = new tree("t", target);
      child = add_edge(target_tree, dependency);
      graph.push_back(target_tree);
    }

  //if dependency is present as a target.. delete
  vector<int> toErase;
  for(unsigned int i = 0; i < graph.size(); i++) {
    //this node in the graph is equivalent to the child in target_tree 
    if(graph[i]->data == dependency)
      {
	// tree* dependency = graph[i];
	// //linking done
	// target_tree->child.push_back(dependency);
	toErase.push_back(i);
      }
  }
  for(unsigned int i = 0; i < toErase.size(); i++) {
    cout << "erasing .. " << toErase[i] << endl;
    cout << "before graph size" << graph.size() << endl;
    graph.erase(graph.begin()+toErase[i]);
    cout << "after graph size" << graph.size() << endl;
  }
  
}

tree* tree_util::add_edge(tree *t, int data) 
{
  tree *child = new tree("child", data);
  t->child.push_back(child);
  return child;
}


// /* Driver program to test above functions*/
// int main()
// {
//   tree_util t;
//   vector<tree*> graph;
//   t.add_edge(graph, 1, 2);
//   t.add_edge(graph, 1, 3);
//   t.add_edge(graph, 3, 4);
//   t.add_edge(graph, 2, 3);
//   t.add_edge(graph, 5, 6);
//   t.add_edge(graph, 4, 5);
//   //t.add_edge(graph, 4, 5);
//   t.add_edge(graph, 6, 7);
//   t.add_edge(graph, 9, 8);
//   t.add_edge(graph, 6, 9);
//   t.add_edge(graph, 3, 10);
// t.add_edge(graph, 3, 12);
//   for(unsigned int i = 0; i < graph.size(); i++) 
//     {
//       t.printLevelOrder(graph[i]);
//       cout <<"hheee" << endl;
//       // t.printGivenLevel(graph[i], 2);
//       // cout << endl;
//       // t.printGivenLevel(graph[i], 3);
//       // cout << endl;
//       // t.printGivenLevel(graph[i], 4);
//       // cout << endl;
//       // t.printGivenLevel(graph[i], 5);
//       // cout << endl;
//       // t.printGivenLevel(graph[i], 6);
//       // cout << endl;
//       // t.printGivenLevel(graph[i], 7);
//       // cout << endl;
//     }
//   // tree *root = new tree("root", 0);
//   // tree *child1 = add_edge(root, 1);
//   // tree *child2 = add_edge(root, 2);
  
//   // add_edge(child1, 3);
//   // add_edge(child1, 4);
  // add_edge(child2, 5);
  // add_edge(child2, 6);

  // printf("Level Order traversal of binary tree is \n");
  // printLevelOrder(root);
  // tree* res = find(root, 6);
  // add_edge(res, 7);
  // res = find(root, 3);
  // add_edge(res, 21);
  // cout << endl;
  // printLevelOrder(root);
  // cout<< endl;
  // printGivenLevel(root, 4);
  // cout<< "\nout" << res->data<< endl;

//   return 0;
// }
