#ifndef _PRODUCTION_H
#define _PRODUCTION_H

class production{

 private:
  vector<string> _target_files;
  vector<string> _dependency_files;
  string _command;

 public:
  production();
  production(vector<string> target_files, vector<string> dependency_files, string command);
  ~production();
  
  vector<string>& getTargetFiles();
  vector<string>& getDependencyFiles();
  string& getCommand();
  string getTargetFilesCSV();
  string getDependencyFilesCSV();
  void print_production_stmt();
};

#endif
