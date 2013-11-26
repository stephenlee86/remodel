#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

#include "stringutil.h"
#include "parser.h"

parser::parser(char*  filename)
{
  _filename = filename;
  cout << "Parsing " << filename << endl;
}

parser::~parser() 
{
  cout << "The End." << endl;
}

void parser::print_production_stmt(vector<string> target_files, vector<string> dependency_files, string command)
{
  cout << "Target Files:" << endl;
  for (int k = 0; k < target_files.size(); k++)
    cout << k << " => " << target_files[k] << endl;

  cout << "Dependency Files:" << endl;
  for (int k = 0; k < dependency_files.size(); k++)
    cout << k << " => " << dependency_files[k] << endl;

  cout << "Command: " << command << endl;
}

void parser::parse()
{

  string str;
  ifstream infile(_filename);
  while(!infile.eof())
    {
      getline(infile,str); 
     
      stringutil production(str);
      vector<string> flds = production.split("<-");

  
      if(flds.size() != 2) 
	{
	  cout << "error in grammar:" << str << endl;
	}
  
      //target files
      stringutil targets(flds[0]);
      vector<string> target_files = targets.split(",");

      //dependency : command
      stringutil dependency_command(flds[1]);
      vector<string> dc_stmt = dependency_command.split(":");

      //sanity check
      if(dc_stmt.size() == 0 || dc_stmt.size() > 2)  {
	//error!
      }
  
      stringutil dependency(dc_stmt[0]);
      vector<string> dependency_files = dependency.split(",");
  
      //command exists
      string command;
      if(dc_stmt.size() == 2) {
	command = dc_stmt[1];
  }

  
  cout << "---------------" <<endl;
  print_production_stmt(target_files, dependency_files, command);

    }
}

int main() 
{  
  //default name
  char filename[] = "makefile_re";
  parser program(filename);
  program.parse();

  
  return 0;
}
