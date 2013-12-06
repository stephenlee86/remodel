#include <string>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <cstring> 

#include <thread>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
using namespace std;

#include "commandutil.h"
#include "graph.h"
#include "tree.h"
#include "stringutil.h"
#include <openssl/md5.h>
#include "md5diff.h"

string commandutil::exec(string u) 
{
  //  char cmd[u.length()-1];
  //  strcpy(cmd,u.c_str());
  char cmd[1024];
  strncpy(cmd, u.c_str(), sizeof(cmd));
  cmd[sizeof(cmd) - 1] = 0;

  FILE* pipe = popen(cmd, "r");
  if (!pipe) return "ERROR";

  char buffer[128];
  std::string result = "";

  while(!feof(pipe)) {
    if(fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }

  pclose(pipe);
  return result;
}

// bool dir_exists( const char* dir_path )
// {
//     if ( dir_path == NULL) return false;

//     DIR *dir;
//     bool dir_exists = false;

//     dir = opendir (dir_path);

//     if (dir != NULL)
//       {
//         dir_exists = true;    
//         (void) closedir (dir);
//       }
//     return dir_exists;
// }

void commandutil::exec_cmd(string cmd_str)
{
  // thread t1(exec, cmd);
  // t1.join();
  char cmd[1024];
  convertToCharArray(cmd_str, cmd);
  system(cmd);
}

void commandutil::convertToCharArray( string str, char c[])
{
  strncpy(c, str.c_str(), 1024);
  c[1024 - 1] = 0;
  //return c;
}
void commandutil::create_sub_directories(string filename)
{
  
  const size_t last_slash_idx = filename.rfind('/');
  if (std::string::npos != last_slash_idx)
    {
      string directory = ".remodel/" + filename.substr(0, last_slash_idx) ;
      const char *dir;
      dir = strdup(directory.c_str());
      mkdir(dir, 0755);

    }
  
}
void commandutil::copy_output(graph graph, vector<string> targets, map<string, bool> &change_tracker, int i, int height)
{
  mkdir(".remodel", 0755);
  //targets=level
  for(unsigned int j = 0; j < targets.size(); j++)
    {
      //      if(i == height) {
      vector<string> targets_csv = stringutil::split(targets[j], ",");
      for(unsigned int k = 0; k < targets_csv.size();k++)
	{
	  //if object does not exist in remodel copy
	  char old_file[1024];
	  convertToCharArray(".remodel/"+targets_csv[k], old_file);
	  create_sub_directories(targets_csv[k]);
  
	  if(ifstream(old_file)){
	    //file exists .. check md5
	    md5diff md5diff1;

	    char new_file[1024];
	    convertToCharArray(targets_csv[k], new_file);
	    
	    
	    if(md5diff1.diff(new_file, old_file) == false)
	      {
		//
		cout << "cp "<< targets_csv[k] << "  .remodel/" << targets_csv[k]<< endl;
		char cmd[1024];
		convertToCharArray("cp "+ targets_csv[k] + "  .remodel/"+ targets_csv[k], cmd);
		system(cmd);
		change_tracker[targets_csv[k]] = true;
	      }
	    else 
	      {
		change_tracker[targets_csv[k]] = false;
		cout<<"Not copying.. " << targets_csv[k] <<endl;
	      }
	  } else {
	    cout << "cp "<< targets_csv[k] << "  .remodel/" << targets_csv[k]<< endl;
	    char cmd[1024];
	    convertToCharArray("cp "+ targets_csv[k] + "  .remodel/"+ targets_csv[k], cmd);
	    system(cmd);
	    change_tracker[targets_csv[k]] = true;
	  }
	}
    }
}

bool commandutil::isModified(map<string, bool> changes_list, string dependency)
{
  
  bool flag = false;
  
  vector<string> dep_list = stringutil::split(dependency,",");
  cout << dependency << endl;
  for(unsigned int i = 0; i < dep_list.size(); i++)
    {
     
      map<string, bool>::iterator it = changes_list.find(dep_list[i]);
      if(it != changes_list.end()) {
	cout << " This --> target" << changes_list[(*it).first] << (*it).second << endl;

	flag = flag || (*it).second;
      }

      //if file doesn't exist //compile the code
      

    }

  flag = flag || changes_list[dependency];
  return flag;
}
bool commandutil::targetExists(string target)
{
  bool flag = true;
  
  vector<string> tar_list = stringutil::split(target,",");
  for(unsigned int i = 0; i < tar_list.size(); i++)
    {
      if(!ifstream(tar_list[i]))
	{
	  flag = false;
	}
    }

  return flag;
}

void commandutil::exec_tree_in_parallel(tree* order_graph, graph graph) 
{
  int height = tree_util::height(order_graph);
  cout << "height in parallel:" << height << endl;
  map<string, bool> changes_list;

  //cos last ones will be ending with dependency like .cpp.. 
  for(int i = height; i > 0; i--) {
    
    vector<string> targets;
    tree_util::get_given_level(order_graph, i, targets);

    vector<thread*> tree_threads;
    
    cout << "executing these in parallel" << endl;
    for(unsigned int j = 0; j < targets.size(); j++)
      {
	//if leaf node .. 
	if(i == height)
	  {
	    //execute the commands in parallel;
	    node* node = graph.findTargets(targets[j]);
	    if(node != NULL) 
	      {
		string cmd = node->prod_stmt.getCommand() ;
		if(cmd.compare("") != 0)
		  cmd = cmd.substr(1,cmd.length()-2);
		//cout<< targets[j] << " " << cmd << endl;
		tree_threads.push_back(new thread(exec_cmd, cmd));
	      }
	    else
	      {
		cout << targets[j] << " not found!" << endl;
	      }
	  }
	//up in the hierarchy
	else 
	  {
	    //need to check if there is a change md5 check
	    //if dependency got copied execute command?
	    
	    node* node= graph.find(targets[j]);
	    if(node != NULL) 
	      {
		cout << "Should the command be executed? "<< node->dependency << isModified(changes_list,  node->dependency) << endl;
		cout << targetExists(node->target)  << node->target;
		

		if (isModified(changes_list,  node->dependency) == true || !targetExists(node->target)) {
		  string cmd = node->prod_stmt.getCommand() ;
		
		  if(cmd.compare("") != 0)
		    cmd = cmd.substr(1,cmd.length()-2);
		  cout<< targets[j] << " " << cmd << endl;
		  if(i != 1)
		    tree_threads.push_back(new thread(exec_cmd, cmd));
		  else {
		    cout << "rename karo" << targets[j] << endl;
		  }
		}
		else 
		  {
		    cout << " Not executed cos dependency was not modified" << endl;
		  }
	      } 
	    else 
	      {
		cout << targets[j] << " not found!" << endl;
	      }
	  }
      }

    //vector<string, bool> changed_target;
    for(unsigned int k = 0; k < tree_threads.size(); k++) {
      tree_threads[k]->join();
    }

    
    //check for changes
    copy_output(graph, targets, changes_list, i, height);
    
    cout << " executing these in parallel .. ends" << endl;

    cout<< endl;
  }
}

void commandutil::exec_in_parallel(graph graph) 
{

  vector<tree*> order_graph = graph.get_tree_graph();
  vector<thread*> thread_pool;
  cout << order_graph.size() << endl;
  for(unsigned int i = 0; i< order_graph.size() ;i++)
    {
      thread_pool.push_back(new thread(exec_tree_in_parallel, order_graph[i], graph));
      break;
    }
  for(unsigned int i = 0; i < thread_pool.size();i++)
    {
      thread_pool[i]->join();
    }
  //TODO do something
}
/*
void commandutil::run_u(node* node) 
{
  if(node != NULL) 
    {
      string cmd = node->prod_stmt.getCommand() ;
      if(cmd.compare("") != 0)
	cmd = cmd.substr(1,cmd.length()-2);
      cout<< node->target << " " << cmd << endl;
      //tree_threads.push_back(new thread(exec_cmd, cmd));
    } 
  else 
    {
      //cout << targets[j] << " not found!" << endl;
    }

}

void commandutil::exec_in_recursive_parallel(tree* &tree, graph& graph, map<string, bool> &val) {
  
  //  bool flag = false;
  //base condition
  if(tree->child.size()== 0)
    {
      node* node = graph.findTargets(tree->name);
      run_u(node);
      copy_output();
      val[tree->name] = true;
    }
  else 
    {
      vector<thread*> thread_pool;
      for(unsigned int i = 0; i < tree->child.size(); i++)
	{
	  //check it as false
	  val[tree->child[i]->name] = false;
	  thread_pool.push_back(thread(std::bind(exec_in_recursive_parallel, tree->child[i], graph, val)));
	}
		     
      for(unsigned int i = 0; i <thread_pool.size();i++)
	{
	  thread_pool[i]->join();
	}

      for(map<string, bool>::iterator itr = val.begin(); itr!= val.end();itr++)
	{
	  
	  cout<< (*itr).second << "  :  ";
	}
      cout << endl;
      
    }
}

void commandutil::exec_in_recursive_parallel(graph graph) {
  vector<tree*> order_graph = graph.get_tree_graph();
  vector<thread*> thread_pool;
  cout << order_graph.size() << endl;
  for(unsigned int i = 0; i< order_graph.size() ;i++)
    {
      map<string, bool> val;
      thread_pool.push_back(new thread(exec_tree_in_parallel, order_graph[i], graph, val));
      break;
    }
  for(unsigned int i = 0; i < thread_pool.size();i++)
    {
      thread_pool[i]->join();
    }
}
*/
bool commandutil::exec_all(queue<string> queue, graph graph)
{
  while(!queue.empty())
    {
      string target = queue.front();

      node* node= graph.find(target);

      //check if dependency exists
      
      
      string cmd = node->prod_stmt.getCommand() ;
      cmd = cmd.substr(1,cmd.length()-2);
      cout<< target << " " << cmd << endl;
      exec_cmd(cmd);

      //Makes the main thread wait for the new thread to finish execution, therefore blocks execution.

      //exec(u);

      queue.pop();
    }
  //  thread.join();
  return 0;
}
