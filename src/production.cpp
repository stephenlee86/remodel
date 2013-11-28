#include<vector>
#include<string>
#include<iostream>
#include<sstream>

using namespace std;
#include "production.h"

production::production() 
{
}
production::~production()
{
}

production::production(vector<string> target_files, vector<string> dependency_files, string command) 
{
  _target_files = target_files;
  _dependency_files = dependency_files;
  _command = command;
}
vector<string>& production::getTargetFiles()
{
  return _target_files;
}
vector<string>& production::getDependencyFiles()
{
  return _dependency_files;
}
string& production::getCommand()
{
  return _command;
}

string production::getTargetFilesCSV()
{
  std::stringstream ss;
  for (unsigned int i = 0; i < _target_files.size(); i++)
    ss << _target_files[i] << ",";
  return ss.str().substr(0, ss.str().size()-1 );
}

string production::getDependencyFilesCSV()
{
  std::stringstream ss;
  for (unsigned int i = 0; i < _dependency_files.size(); i++)
    ss << _dependency_files[i] << ",";
  return ss.str().substr(0, ss.str().size()-1 );
}
void production::print_production_stmt()
{
  cout << "Target Files:" << endl;
  for (unsigned int i = 0; i < _target_files.size(); i++)
    cout << i << " => " << _target_files[i] << endl;

  cout << "Dependency Files:" << endl;
  for (unsigned int i = 0; i < _dependency_files.size(); i++)
    cout << i << " => " << _dependency_files[i] << endl;

  cout << "Command: " << _command << endl;
}


