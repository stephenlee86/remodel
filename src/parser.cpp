#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;

#include "stringutil.h"
#include "parser.h"

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
      string temp = str;
      if (stringutil::trim(str).empty()) continue;


      vector<string> flds = stringutil::split(str, "<-");
      
      if(flds.size() != 2) 
	{
	  cout << "error in grammar(statement should contain only one '<-'):" << temp << endl;
	  exit (EXIT_FAILURE);
	}
  
      //target files
      vector<string> target_files = stringutil::split(flds[0], ",");

      //dependency : command
      vector<string> dc_stmt = stringutil::split(flds[1], ":");

      //sanity check
      if(dc_stmt.size() == 0 || dc_stmt.size() > 2)  
	{
	  //error in grammar!
	  //TODO..command parsing properly .. may contain arbitrary command in quotes
	  cout << "error in grammar(statement should contain atleast one dependency and no more than one command): " << temp << endl;
	  exit (EXIT_FAILURE);
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

