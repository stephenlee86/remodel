#include "production.h"

#ifndef PARSER_H
#define PARSER_H

class parser
{
private:
  char* _filename;
  vector<production> _productions;

public:
  parser(char* filename);
  vector<production>& parse();
  ~parser();
};

#endif
