#ifndef STRUTIL_H
#define STRUTIL_H
//http://www.cplusplus.com/articles/1UqpX9L8/

class stringutil
{

 public:
  static string& ltrim(string &s);
  static string& rtrim(string &s);
  static string& trim(string &s);
  static const vector<string> split(string str, string delimiter, int rep=0);
};
#endif
